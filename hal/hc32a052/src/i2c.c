/**
 *******************************************************************************
 * @file  i2c.c
 * @brief This file provides firmware functions to manage the I2C.
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
#include "i2c.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_I2C I2C模块驱动库
 * @brief I2C Driver Library I2C模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup I2C_Local_Functions I2C局部函数定义
 * @{
 */
 static en_result_t I2C_SetBaud(I2C_TypeDef* I2Cx, uint8_t u8Tm);
/**
 * @}
 */
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup I2C_Local_Functions I2C局部函数定义
 * @{
 */

/**
 * @brief  I2C设置波特率配置寄存器.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] u8Tm: 波特率配置值
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
 static en_result_t I2C_SetBaud(I2C_TypeDef* I2Cx, uint8_t u8Tm)
 {
     en_result_t enRet = Error;

     I2Cx->TM = u8Tm;

     enRet = Ok;
     return enRet;
 }
/**
 * @}
 */


/**
 * @defgroup I2C_Global_Functions I2C全局函数定义
 * @{
 */

/**
 * @brief  I2C功能设置相关函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] enFunc: 功能参数 @ref en_i2c_func_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
en_result_t I2C_SetFunc(I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
{
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, (uint32_t)enFunc, TRUE);

    enRet = Ok;
    return enRet;
}

/**
 * @brief  I2C功能清除相关函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] enFunc: 功能参数 @ref en_i2c_func_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
 en_result_t I2C_ClearFunc(I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
 {
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, (uint32_t)enFunc, FALSE);

    enRet = Ok;
    return enRet;
 }


/**
 * @brief  I2C获取中断标记函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t I2C_GetIrq(I2C_TypeDef* I2Cx)
{
    if(I2Cx->CR&0x8u)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/**
 * @brief  I2C清除中断标记函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 */
en_result_t I2C_ClearIrq(I2C_TypeDef* I2Cx)
{
    en_result_t enRet = Error;

    I2Cx->CR &= ~0x8u;

    enRet = Ok;
    return enRet;
}

/**
 * @brief  I2C获取相关状态.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval uint8_t: I2C状态
 */
uint8_t I2C_GetState(I2C_TypeDef* I2Cx)
{
    uint8_t u8State = 0u;

    u8State = (uint8_t)I2Cx->STAT;

    return u8State;
}


/**
 * @brief  字节数据写函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] u8Data: 数据
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 */
en_result_t I2C_WriteByte(I2C_TypeDef* I2Cx, uint8_t u8Data)
{
    en_result_t enRet = Error;

    I2Cx->DATA = u8Data;

    enRet = Ok;
    return enRet;
}

/**
 * @brief  字节数据读函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval uint8_t: 数据
 */
uint8_t I2C_ReadByte(I2C_TypeDef* I2Cx)
{
    uint8_t u8Data = 0u;

    u8Data = (uint8_t)I2Cx->DATA;

    return u8Data;
}


/**
 * @brief  I2C模块初始化.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] pstcI2CCfg: 初始化结构体指针 @ref stc_i2c_cfg_t
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 */
en_result_t I2C_Init(I2C_TypeDef* I2Cx, stc_i2c_cfg_t *pstcI2CCfg)
{
   en_result_t enRet = Error;
   uint8_t     u8Tm;
   
   if(HC_I2C0 == I2Cx)
   {
       HC_SYSCTRL->PERIRESET0 &= ~(uint32_t)0x10u; 
       HC_SYSCTRL->PERIRESET0 |= (uint32_t)0x10u;   
   }
   else
   {
       HC_SYSCTRL->PERIRESET0 &= ~(uint32_t)0x20u; 
       HC_SYSCTRL->PERIRESET0 |= (uint32_t)0x20u;   
   }
    
   I2Cx->CR = 0u;
   I2Cx->CR = pstcI2CCfg->enMode;

   if((pstcI2CCfg->u32Baud<<4) > pstcI2CCfg->u32Pclk)
   {
        return Error;
   }

   if(I2cMasterMode == pstcI2CCfg->enMode)
   {
        I2Cx->TMRUN = TRUE;
        /* Fsck = Fpclk/8*(Tm+1) */
        u8Tm = (uint8_t)((pstcI2CCfg->u32Pclk / pstcI2CCfg->u32Baud) >> 3u) - 1u;
        if(9u > u8Tm)
        {
            I2C_SetFunc(I2Cx,I2cHlm_En);
        }
        enRet = I2C_SetBaud(I2Cx, u8Tm);
   }
   else
   {
        I2Cx->TMRUN = FALSE;
        pstcI2CCfg->u8SlaveAddr = (uint8_t)(((uint32_t)pstcI2CCfg->u8SlaveAddr<<1)|(pstcI2CCfg->bGc));
        I2Cx->ADDR0 = pstcI2CCfg->u8SlaveAddr;
   }

   return enRet;
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
