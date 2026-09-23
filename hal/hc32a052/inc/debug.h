/**
 *******************************************************************************
 * @file  debug.h
 * @brief This file contains all the functions prototypes of the DEBUG driver
 *        library.
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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_DEBUG DEBUG模块驱动库
 * @{
 */

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup DEBUG_Global_Types DEBUG全局类型定义
 * @{
 */ 

/**
 * @brief  模块选择，设置调试模式下各模块工作状态
 */
typedef enum
{
    DebugMskAtim0   = 0x0001u,    /*!< ATIM0 */
    DebugMskAtim1   = 0x0002u,    /*!< ATIM1 */
    DebugMskAtim2   = 0x0004u,    /*!< ATIM2 */
    DebugMskLpTim   = 0x0008u,    /*!< LPTIM */
    DebugMskCtim0   = 0x0010u,    /*!< CTIM0 */
    DebugMskCtim1   = 0x0020u,    /*!< CTIM1 */
    DebugMskCtrim   = 0x0080u,    /*!< CTRIM */
    DebugMskIwdt    = 0x0100u,    /*!< IWDT */
    DebugMskRtc     = 0x0200u,    /*!< RTC */
    DebugMskTim3    = 0x0800u,    /*!< ATIM3 */
    DebugMskWwdt    = 0x1000u,    /*!< WWDT */
}en_debug_module_active_t;

/**
 * @}
 */
/*******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup DEBUG_Global_Functions DEBUG全局函数定义
 * @{
 */

/**
 * @brief  在SWD调试模式下，使能模块计数功能
 */
en_result_t Debug_ActiveEnable(en_debug_module_active_t enModule);
/**
 * @brief  在SWD调试模式下，暂停模块计数功能
 */
en_result_t Debug_ActiveDisable(en_debug_module_active_t enModule);

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
#endif

#endif /* __DEBUG_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


