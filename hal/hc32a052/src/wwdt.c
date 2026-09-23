/**
 *******************************************************************************
 * @file  wwdt.c
 * @brief This file provides firmware functions to manage the WWDT.
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
#include "wwdt.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_WWDT WWDT模块驱动库
 * @brief WWDT Driver Library WWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup WWDT_Global_Functions WWDT全局函数定义
 * @{
 */

/**
 * @brief  WWDT 初始化
 * @param  [in] pstcWwdtInit: WWDT初始化          @ref stc_wwdt_init_t
 * @retval en_result_t
 */
en_result_t WWDT_Init(stc_wwdt_init_t* pstcWwdtInit)
{
    REG_WRITE(HC_WWDT->CR1, pstcWwdtInit->u32Prescaler | pstcWwdtInit->u32PreOverInt | pstcWwdtInit->u32Window);

    REG_WRITE(HC_WWDT->CR0, pstcWwdtInit->u32Counter);

    return Ok;
}

/**
 * @brief  WWDT 启动运行
 * @retval None
 */
void WWDT_Start(void)
{
    REG_SETBITS(HC_WWDT->CR0, WWDT_CR0_EN);
}

/**
 * @brief  WWDT 喂狗
 * @param  [in] u32Cnt: 计数器值
 * @retval None
 */
void WWDT_Feed(uint32_t u32Cnt)
{
    REG_WRITE(HC_WWDT->CR0, WWDT_CR0_EN | u32Cnt);
}

/**
 * @brief  WWDT 预溢出标志清除
 * @retval None
 */
void WWDT_ClearPreOverFlag(void)
{
    REG_CLEARBITS(HC_WWDT->SR, WWDT_SR_POV);
}

/**
 * @brief  WWDT 预溢出标志获取
 * @retval boolean_t： 溢出标志位
 *         - TRUE   溢出
 *         - FALSE  无溢出
 */
boolean_t WWDT_GetPreOverFlag(void)
{
    if (REG_READBITS(HC_WWDT->SR, WWDT_SR_POV))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  WWDT 获取当前运行状态
 * @retval boolean_t： 运行状态
 *         - TRUE   正在运行
 *         - FALSE  没有运行
 */
boolean_t WWDT_GetRunFlag(void)
{
    if (REG_READBITS(HC_WWDT->CR0, WWDT_CR0_EN))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  WWDT 获取当前计数值
 * @retval uint32_t：  计数值
 */
uint32_t WWDT_GetCnt(void)
{
    return REG_READBITS(HC_WWDT->CR0, WWDT_CR0_WCNT);
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
