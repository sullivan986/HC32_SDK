/**
 *******************************************************************************
 * @file  flash.h
 * @brief This file contains all the functions prototypes of the FLASH driver
 *        library.
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

#ifndef __FLASH_H__
#define __FLASH_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_FLASH FLASH模块驱动库
 * @{
 */


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FLASH_Global_Types FLASH全局类型定义
 * @{
 */
   
/**
 * @brief  Flash中断类型重定义
 */
typedef enum
{
    FlashPCInt    = 0x01u,          /*!<  FLASH 擦写PC地址报警中断   */
    FlashSlockInt = 0x02u,          /*!<  FLASH 擦写保护报警中断     */
} en_flash_int_type_t;

/**
 * @brief  Flash功能设置类型重定义
 */
typedef enum
{
    FastWkupEn      = 0x10u,          /*!<  FLASH 快速唤醒使能                         */
    FlashReadOnlyEn = 0x20u,          /*!<  FLASH 只读使能                             */
    FlashDpStbEn    = 0x80u,          /*!<  系统进入DeepSleep时，FLASH进入低功耗使能   */
} en_flash_func_type_t;


/**
 * @brief  Flash读等待周期类型重定义
 */
typedef enum
{
    FlashWaitCycle0 = 0u,       /*!<  读等待周期设置为0-即读周期为1（当HCLK小于等于24MHz时）         */
    FlashWaitCycle1 = 1u,       /*!<  读等待周期设置为1-即读周期为2（当HCLK大于24MHz时必须至少为1）  */
    FlashWaitCycle2 = 2u,       /*!<  读等待周期设置为2-即读周期为3（当HCK大于48MHz时必须至少为2）   */
} en_flash_waitcycle_t;


/**
 * @brief  Flash擦写保护范围重定义
 */
typedef enum
{
    FlashLock0 = 0u,           /*!<  SLOCK0 Sector擦写保护寄存器0  */ 
    FlashLock1 = 4u,           /*!<  SLOCK1 Sector擦写保护寄存器1  */
} en_flash_lock_t;

/**
 * @brief Flash操作模式配置
 */
typedef enum
{
    FlashReadMode        = 0u,           /*!<  Flash 读模式             */
    FlashWriteMode       = 1u,           /*!<  Flash 写（编程）模式     */
    FlashSectorEraseMode = 2u,           /*!<  Flash 扇区（页）擦除模式 */
    FlashChipEraseMode   = 3u,           /*!<  Flash 全片擦除模式       */  
    FlashContWriteMode   = 4u,           /*!<  Flash 连续写模式     */ 
} en_flash_op_mode_t;


/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
 /**
 * @defgroup FLASH_Global_Types FLASH全局类型定义
 * @{
 */
 /** @defgroup  Flash_Lock_State_Level  FLASH_LOCK_LEVLE
  * @{
  */
#define  FLASH_LOCK_STATE_LEVEL0    (0u)   /*!<  Flash Lock Level0，ISP可读写，SWD可读写 */
#define  FLASH_LOCK_STATE_LEVEL1    (1u)   /*!<  Flash Lock Level1，ISP可降级，SWD可降级；数据不可读出 */
#define  FLASH_LOCK_STATE_LEVEL2    (2u)   /*!<  Flash Lock Level2，ISP可降级，SWD无功能；数据不可读出 */
#define  FLASH_LOCK_STATE_LEVEL3    (3u)   /*!<  Flash Lock Level3，ISP无功能，SWD无功能；数据不可读出 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */
 
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)
	en_result_t Flash_Chip_Erase(void);
	en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len);
	en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len);
	en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len);
#elif defined(__ICCARM__)
	__ramfunc en_result_t Flash_Chip_Erase(void);
	__ramfunc en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len);
	__ramfunc en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len);
	__ramfunc en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len);
#endif

en_result_t Flash_LockAll(void);
en_result_t Flash_UnlockAll(void);
en_result_t Flash_FuncSet(en_flash_func_type_t enFunc, boolean_t bFlag);
en_result_t Flash_SectorErase(uint32_t u32SectorAddr);
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len);
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len);
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len);
en_result_t Flash_OpModeConfig(en_flash_op_mode_t enFlashOpMode);
en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue);
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle);
en_result_t Flash_EnDpstb(boolean_t bDpstbEn);
uint8_t Flash_ReadProtectLevel(void);
en_result_t Flash_EnableIrq(en_flash_int_type_t enFlashIntType);
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType);
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType);
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType);
/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __FLASH_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
