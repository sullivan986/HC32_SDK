/**
 *******************************************************************************
 * @file  flash.c
 * @brief This file provides firmware functions to manage the FLASH.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-15       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "flash.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_FLASH FLASH模块驱动库
 * @brief FLASH Driver Library FLASH模块驱动库
 * @{
 */


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FLASH_Local_Macros FLASH局部宏定义
 * @{
 */
/**
 * @defgroup FLASH_Value_Define FLASH模式值设置
 * @{
 */
#define FLASH_END_ADDR              (0x0001FFFFu)
#define FLASH_BYPASS()              do{HC_FLASH->BYPASS = (uint32_t)0x5A5A;\
                                       HC_FLASH->BYPASS = (uint32_t)0xA5A5;}while(0) 
#define FLASH_IE_TRUE               (0x03)
#define FLASH_IE_FALSE              (0x00)

#define FLASH_TIMEOUT_INIT          (0xFFFFFFu)
#define FLASH_TIMEOUT_PGM           (0xFFFFFFu)
#define FLASH_TIMEOUT_ERASE         (0xFFFFFFu)

#define FLASH_LOCK_ALL              (0u)
#define FLASH_UNLOCK_ALL            (0xFFFFFFFFu)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FLASH_Local_Types FLASH局部类型定义
 * @{
 */
/**
 * @brief  FLASH OP definition  FLASH操作控制数据类型重定义
 */
typedef enum
{
    FlashOpRead        = 0u,           /*!<  FLASH 读配置值 */
    FlashOpProgram     = 1u,           /*!<  FLASH 编程配置值 */
    FlashOpSectorErase = 2u,           /*!<  FLASH 扇区擦除配置值 */
    FlashOpChipErase   = 3u,           /*!<  FLASH 全片擦除配置值 */
} en_flash_op_t;

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */
 
/**
 * @brief   Flash 整片擦除
 * @note    该函数需要放到RAM中执行
 * @retval  en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
*/ 

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)

#pragma clang section text = "ramfunc"

en_result_t Flash_Chip_Erase(void)
{
	en_result_t enResult = Ok;
	volatile uint32_t u32TimeOut = FLASH_TIMEOUT_PGM;

	while(FlashOpChipErase != HC_FLASH->CR_f.OP)
	{
		HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		HC_FLASH->CR_f.OP = FlashOpChipErase;
			
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}		
	}

    u32TimeOut = FLASH_TIMEOUT_PGM;
	while(0xFFFFFFFFu != HC_FLASH->SLOCK0)
	{
        HC_FLASH->BYPASS = (uint32_t)0x5A5A;
        HC_FLASH->BYPASS = (uint32_t)0xA5A5;	

        HC_FLASH->SLOCK0 = 0xFFFFFFFFu;
			
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}		
	}
    
    u32TimeOut = FLASH_TIMEOUT_PGM;
	while(0xFFFFFFFFu != HC_FLASH->SLOCK1)
	{
        HC_FLASH->BYPASS = (uint32_t)0x5A5A;
        HC_FLASH->BYPASS = (uint32_t)0xA5A5;	

        HC_FLASH->SLOCK1 = 0xFFFFFFFFu;
			
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}		
	}

	*((volatile unsigned int*)0x00000000) = 0;

	u32TimeOut = FLASH_TIMEOUT_PGM;
	while (TRUE == HC_FLASH->IFR_f.BUSY)
	{
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}
    
    u32TimeOut = FLASH_TIMEOUT_PGM;
	while(FlashOpRead != HC_FLASH->CR_f.OP)
	{
		HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		HC_FLASH->BYPASS = (uint32_t)0xA5A5;
		HC_FLASH->CR_f.OP = FlashOpRead;
			
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}		
	}

	enResult = Ok;    
	return (enResult);
}	


/**
 * @brief  Flash字节连续写 用于向FLASH写入1字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = 0xFFFFFF;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t*)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }    
        u32Addr++;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;		
	  }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    } 
	
    enResult = Ok;
	
    return (enResult);
}

/**
 * @brief  Flash半字连续写 用于向FLASH写入半字（2字节）数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + (u32Len<<1u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        u32Addr+=2u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
   {
   	  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
     	HC_FLASH->BYPASS = (uint32_t)0xA5A5;
   
   	  HC_FLASH->CR_f.OP = FlashWriteMode;		
   }
    
    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    } 

    enResult = Ok;    
    return (enResult);
}

/**
 * @brief  Flash字连续写 用于向FLASH写入1个字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + (u32Len<<2u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr+=4u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;		
	  }
    
    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    } 
	
    enResult = Ok;    
    return (enResult);
}

#pragma clang section

#elif defined(__ICCARM__)

__ramfunc 	en_result_t Flash_Chip_Erase(void)
{
	en_result_t enResult = Ok;
	volatile uint32_t u32TimeOut = FLASH_TIMEOUT_PGM;

	while(FlashOpChipErase != HC_FLASH->CR_f.OP)
	{
		HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		HC_FLASH->CR_f.OP = FlashOpChipErase;
			
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}		
	}

	HC_FLASH->BYPASS = (uint32_t)0x5A5A;
	HC_FLASH->BYPASS = (uint32_t)0xA5A5;	

	HC_FLASH->SLOCK0 = 0xFFFFFFFFu;

	HC_FLASH->BYPASS = (uint32_t)0x5A5A;
	HC_FLASH->BYPASS = (uint32_t)0xA5A5;	

	HC_FLASH->SLOCK1 = 0xFFFFFFFFu;

	if( (0xFFFFFFFFu != HC_FLASH->SLOCK0) || (0xFFFFFFFFu != HC_FLASH->SLOCK1) )
	{
		enResult = Error;
	}	

	*((volatile unsigned int*)0x00000000) = 0;

	u32TimeOut = FLASH_TIMEOUT_PGM;
	while (TRUE == HC_FLASH->IFR_f.BUSY)
	{
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

	enResult = Ok;    
	return (enResult);
}	

/**
 * @brief  Flash字节连续写 用于向FLASH写入1字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__ramfunc en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    
    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t*)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        
        u32Addr++;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;		
	  }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    } 
	
    enResult = Ok;
	
    return (enResult);
}

/**
 * @brief  Flash半字连续写 用于向FLASH写入半字（2字节）数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__ramfunc en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = 0xFFFFFF;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr+=2u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;		
	  }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    } 

    enResult = Ok;    
    return (enResult);
}

/**
 * @brief  Flash字连续写 用于向FLASH写入1个字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__ramfunc en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = 0xFFFFFF;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr+=4u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;		
	  }
    
    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    } 
	
    enResult = Ok;    
    return (enResult);
}

#endif

/**
 * @brief  Flash 编程保护加锁
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_LockAll(void)
{ 
    en_result_t enResult = Error;
    
    FLASH_BYPASS();
    HC_FLASH->SLOCK0 = FLASH_LOCK_ALL;
    FLASH_BYPASS();
    HC_FLASH->SLOCK1 = FLASH_LOCK_ALL;  
    
    if(FLASH_LOCK_ALL == HC_FLASH->SLOCK0)
    {
        if(FLASH_LOCK_ALL == HC_FLASH->SLOCK1)
        {
            enResult = Ok;
        }
    }
    
    return enResult;
}

/**
 * @brief  Flash 编程保护解锁
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_UnlockAll(void)
{
    en_result_t enResult = Error;
    
    FLASH_BYPASS();
    HC_FLASH->SLOCK0 = FLASH_UNLOCK_ALL;
    FLASH_BYPASS();
    HC_FLASH->SLOCK1 = FLASH_UNLOCK_ALL;
    
    if(FLASH_UNLOCK_ALL == HC_FLASH->SLOCK0)
    {
        if(FLASH_UNLOCK_ALL == HC_FLASH->SLOCK1)
        {
            enResult = Ok;
        }
    }
    
    return enResult;
}

/**
 * @brief  Flash中断标志获取
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t 
 * @retval boolean_t:
 *              - TRUE: 标志置位
 *              - FALSE: 标志未置位
 */
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType)
{
    boolean_t bRetVal = FALSE;
    
    if(HC_FLASH->IFR & enFlashIntType)
    {
        bRetVal =  TRUE;
    }
    
    return bRetVal;
}

/**
 * @brief  Flash中断标志清除
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t 
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    HC_FLASH->ICR &= ~(uint32_t)enFlashIntType;
    enResult = Ok;
    
    return enResult;
}

/**
 * @brief  Flash中断使能
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t 
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_EnableIrq (en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->IER |= enFlashIntType;
    
    enResult = Ok;

    return enResult;
}

/**
 * @brief  Flash中断禁止
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t 
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->IER &= ~(uint32_t)enFlashIntType;
    
    enResult = Ok;

    return enResult;
}


/**
 * @brief  Flash功能设置函数
 * @param  [in] enFunc: Flash 功能设置枚举  @ref en_flash_func_type_t 
 * @param  [in] bFlag: bool类型，TRUE or FALSE
 * @retval en_result_t:
 *              - Ok: 设置成功
 *              - Error: 设置失败
 */
en_result_t Flash_FuncSet(en_flash_func_type_t enFunc, boolean_t bFlag)
{
    en_result_t             enResult  = Ok;

    if(TRUE == bFlag)
    {
        FLASH_BYPASS();
        REG_SETBITS(HC_FLASH->CR, enFunc);
    }
    else
    {
        FLASH_BYPASS();
        REG_CLEARBITS(HC_FLASH->CR, (uint32_t)enFunc);
    }

    return (enResult);
}

/**
 * @brief  Flash字节写 用于向FLASH写入1字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 *              - Error: 写入失败
 */
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0u;

    if(FlashWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        if(pu8Data[u32Index] != *((volatile uint8_t*)u32Addr))
        {
            return Error;
        }
        
        u32Addr++;
    }
    

    
    enResult = Ok;
    return (enResult);
}

/**
 * @brief  Flash半字写 用于向FLASH写入半字（2字节）数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 *              - Error: 写入失败
 */
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0u;

    if(FlashWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + (u32Len<<1u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        if(pu16Data[u32Index] != *((volatile uint16_t*)u32Addr))
        {
            return Error;
        }
        u32Addr+=2u;
    }

    enResult = Ok;    
    return (enResult);
}

/**
 * @brief  Flash字写 用于向FLASH写入1个字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 *              - Error: 写入失败
 */
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0u;

    if(FlashWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < (u32Addr + (u32Len<<2u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        if(pu32Data[u32Index] != *((volatile uint32_t*)u32Addr))
        {
            return Error;
        }
        u32Addr+=4u;
    }

    enResult = Ok;    
    return (enResult);
}

/**
 * @brief  Flash扇区擦除
 * @param [in]  u32SectorAddr    所擦除扇区内的地址
 * @retval en_result_t:
 *              - Ok: 擦除成功
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_SectorErase(uint32_t u32SectorAddr)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;
    
    if(FlashSectorEraseMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }
    
    if (FLASH_END_ADDR < u32SectorAddr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    /* write data */
    *((volatile uint32_t*)u32SectorAddr) = 0u;
    
    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    return (enResult);
}

/**
 * @brief FLASH 操作模式配置
 *
 * @param [in]  enFlashOpMode    @ref en_flash_op_mode_t
 * 
 * @retval Ok                    配置成功
 * @retval Error                 配置失败 
 */
en_result_t Flash_OpModeConfig(en_flash_op_mode_t enFlashOpMode)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->CR_f.OP = enFlashOpMode;
    
    if(enFlashOpMode == HC_FLASH->CR_f.OP)
    {
        enResult = Ok;
    }
    
    return enResult;
}


/**
 * @brief  Flash 读等待周期设置
 * @param [in]  enWaitCycle  插入FLASH读等待周期数枚举类型   @ref en_flash_waitcycle_t 
 * @retval en_result_t:
 *              - Ok: 设置成功
 *              - ErrorInvalidParameter: 参数错误 
 */
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle)
{
    en_result_t enResult = Ok;
    
    FLASH_BYPASS();
    HC_FLASH->WAIT_f.WAIT = enWaitCycle;
    
    return enResult;
}

/**
 * @brief FLASH 低功耗模式配置
 *
 * 该函数用于配置低功耗模式.
 *
 * @param [in] bDpstbEn          TRUE  - 当系统进入DeepSleep模式，FLASH进入低功耗模式;
 *                               FALSE - 当系统进入DeepSleep模式，FLASH不进入低功耗模式;
 * 
 * @retval Ok                    操作成功.
 * @retval ErrorInvalidParameter 参数无效.
 * @retval ErrorUninitialized    初始化失败。
 */
en_result_t Flash_EnDpstb(boolean_t bDpstbEn)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;
    
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(bDpstbEn != HC_FLASH->CR_f.DPSTBEN)
    {
        FLASH_BYPASS();
        HC_FLASH->CR_f.DPSTBEN = bDpstbEn;
        
        if(0u == u32TimeOut--)
        {
            enResult = ErrorUninitialized;
            return (enResult);
        }
    }
    
    enResult = Ok;
    return (enResult);
}


/**
 * @brief  FLASH LOCK 设置
 * @param [in]  enLock  Sector擦写保护寄存器 @ref en_flash_lock_t
 * @param [in]  u32LockValue 32bits，对应bit=0：加锁，对应Sector不允许擦写；对应bit=1：解锁。
 * @note  加解锁范围Sector：[enLock*128 + i*4, enLock*128 + i*4+3]
 *        -i: 表示u32LockValue的bit位置，0~31; 
 *        -enLock: 表示枚举编号(FlashLock[n]:n=0~3),并非枚举值;)
 *        例如：enLock = FlashLock1, u32LockValue = 0x00000005,
 *              则FLASH解锁范围为：[Sector128,Sector131]和[Sector136,Sector139]
 * @retval en_result_t:
 *              - Ok: 解锁成功
 */
en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue)
{
    en_result_t enResult = Error;
    volatile uint32_t u32PieAddr;

    u32PieAddr = (uint32_t)(&HC_FLASH->SLOCK0) + (uint32_t)enLock;
    
    FLASH_BYPASS();
    REG_WRITE(*(volatile uint32_t *)u32PieAddr, u32LockValue);
    
    if(u32LockValue == *(volatile uint32_t *)u32PieAddr)
    {
        return enResult = Ok;
    }
    
    return enResult;
}

/**
 * @brief  Flash 获取读保护等级
 * @retval uint8_t:   读保护等级 @ref Flash_Lock_State_Level
 */
uint8_t Flash_ReadProtectLevel(void)
{
    uint8_t u8LevelVal;
    
    u8LevelVal = (uint8_t)REG_READBITS(HC_FLASH->LOCKST, FLASH_LOCKST_STATE);
    
    return u8LevelVal;
}

/**
 * @}
 */

/**
 * @}
 */

/**
* @}
*/

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
