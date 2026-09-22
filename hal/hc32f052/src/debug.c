/**
 *******************************************************************************
 * @file  debug.c
 * @brief This file provides firmware functions to manage the DEBUG.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-08-29       MADS            First version
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
#include "debug.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DEBUG DEBUG模块驱动库
 * @brief DEBUG Driver Library DEBUG模块驱动库
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
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup DEBUG_Global_Functions DEBUG全局函数定义
 * @{
 */

/**
 * @brief  调试模式下模块功能计数使能.
 * @param  [in] enModule: 选择设置的外设模块 @ref en_debug_module_active_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 */
en_result_t Debug_ActiveEnable(en_debug_module_active_t enModule)
{
    HC_SYSCTRL->DBGSTOP &= ~(uint32_t)enModule;

    return Ok;
}


/**
 * @brief  调试模式下模块功能计数暂停.
 * @param  [in] enModule: 选择设置的外设模块 @ref en_debug_module_active_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 */
en_result_t Debug_ActiveDisable(en_debug_module_active_t enModule)
{
    HC_SYSCTRL->DBGSTOP |= (uint32_t)enModule;
    
    return Ok;
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
