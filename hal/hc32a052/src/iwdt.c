/**
 *******************************************************************************
 * @file  iwdt.c
 * @brief This file provides firmware functions to manage the IWDT.
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
#include "iwdt.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_IWDT IWDT模块驱动库
 * @brief IWDT Driver Library IWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IWDT_Local_Macros IWDT局部宏定义
 * @{
 */
/**
 * @defgroup IWDT_Key_Value_Define IWDT键值设置
 * @{
 */
#define IWDT_KEY_LOCK_RELEASE     (0x5555U) /*!< 解除写保护 */
#define IWDT_KEY_START_VALUE      (0xCCCCU) /*!< 启动IWDT计数器 */
#define IWDT_KEY_RELOAD_VALUE     (0xAAAAU) /*!< 重载IWDT计数器 */
#define IWDT_KEY_STOP_BYPASS_1234 (0x1234U) /*!< 依次写入0x1234和0x5678停止IWDT */
#define IWDT_KEY_STOP_BYPASS_5678 (0x5678U) /*!< 依次写入0x1234和0x5678停止IWDT */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup IWDT_Global_Functions IWDT全局函数定义
 * @{
 */

/**
 * @brief  IWDT 初始化
 * @param  [in] pstcIwdtInit: IWDT初始化 @ref stc_iwdt_init_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t IWDT_Init(stc_iwdt_init_t* pstcIwdtInit)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_START_VALUE);
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_LOCK_RELEASE);

    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_PRSF | IWDT_SR_ARRF | IWDT_SR_WINRF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->CR, pstcIwdtInit->u32Action | pstcIwdtInit->u32Prescaler);
    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_PRSF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->ARR, pstcIwdtInit->u32ArrCounter);
    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_ARRF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->WINR, pstcIwdtInit->u32Window);
    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_WINRF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->KR, IWDT_KEY_RELOAD_VALUE);

    while (!REG_READBITS(HC_IWDT->SR, IWDT_SR_RUN))
    {
        ;
    }

    return Ok;
}

/**
 * @brief  IWDT 启动运行
 *
 * @retval None
 */
void IWDT_Start(void)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_START_VALUE);
}

/**
 * @brief  IWDT 停止运行
 *
 * @retval None
 */
void IWDT_Stop(void)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_STOP_BYPASS_1234);
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_STOP_BYPASS_5678);
}

/**
 * @brief  IWDT 喂狗
 *
 * @retval None
 */
void IWDT_Feed(void)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_RELOAD_VALUE);
}

/**
 * @brief  IWDT 溢出标志清除
 * 
 * @retval None
 */
void IWDT_ClearOverFlag(void)
{
    REG_CLEARBITS(HC_IWDT->SR, IWDT_SR_OV);
}

/**
 * @brief  IWDT 溢出标志获取
 *
 * @retval boolean_t： 溢出标志位
 *         - TRUE   溢出
 *         - FALSE  无溢出
 */
boolean_t IWDT_GetOverFlag(void)
{
    if (REG_READBITS(HC_IWDT->SR, IWDT_SR_OV))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  IWDT 获取当前运行状态
 *
 * @retval boolean_t： 运行状态
 *         - TRUE   正在运行
 *         - FALSE  没有运行
 */
boolean_t IWDT_GetRunFlag(void)
{
    if (REG_READBITS(HC_IWDT->SR, IWDT_SR_RUN))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
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
