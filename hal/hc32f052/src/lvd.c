/**
 *******************************************************************************
 * @file  lvd.c
 * @brief This file provides firmware functions to manage the LVD.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-15       MADS             First version
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

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lvd.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LVD LVD模块驱动库
 * @brief LVD Driver Library LVD模块驱动库
 * @{
 */

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup LVD_Global_Functions LVD全局函数定义
 * @{
 */

/**
 * @brief  使能LVD中断.
 * @retval None.
 */
void Lvd_EnableIrq(void)
{
    HC_LVD->CR_f.IE = TRUE;
}

/**
 * @brief  禁止LVD中断.
 * @retval None.
 */
void Lvd_DisableIrq(void)
{
    HC_LVD->CR_f.IE = FALSE;
}

/**
 * @brief  LVD初始化.
 * @param  [in] pstcCfg: 初始化结构体指针 @ref stc_lvd_cfg_t
 * @retval None.
 */
void Lvd_Init(stc_lvd_cfg_t *pstcCfg)
{
    HC_LVD->CR = 0U;

    HC_LVD->CR = (uint32_t)pstcCfg->enAct        |
                  (uint32_t)pstcCfg->enFilter     |
                  (uint32_t)pstcCfg->enFilterTime |
                  (uint32_t)pstcCfg->enInputSrc   |
                  (uint32_t)pstcCfg->enIrqType    |
                  (uint32_t)pstcCfg->enThreshold;
}


/**
 * @brief  使能LVD.
 * @retval None.
 */
void Lvd_Enable(void)
{
    HC_LVD->CR_f.LVDEN = 1u;
}


/**
 * @brief  禁止LVD.
 * @retval None.
 */
void Lvd_Disable(void)
{
    HC_LVD->CR_f.LVDEN = 0u;
}


/**
 * @brief  获取LVD中断标志.
 * @retval boolean_t:
 *           - TRUE: 已发生中断
 *           - FLASE: 未发生中断
 */
boolean_t Lvd_GetIrqStat(void)
{
    return HC_LVD->SR_f.INTF ? TRUE: FALSE;

}


/**
 * @brief  清除LVD中断标志.
 * @retval None.
 */
void Lvd_ClearIrq(void)
{
    HC_LVD->SR_f.INTF = 0U;
}


/**
 * @brief  获取Filter结果.
 * @retval boolean_t:
 *           - TRUE: 滤波后的信号电平为高
 *           - FLASE: 滤波后的信号电平为低
 */
boolean_t Lvd_GetFilterResult(void)
{
    return (boolean_t)HC_LVD->SR_f.FILTER;
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
 ******************************************************************************/

