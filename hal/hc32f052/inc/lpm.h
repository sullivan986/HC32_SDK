/**
 *******************************************************************************
 * @file  lpm.h
 * @brief This file contains all the functions prototypes of the XXX driver
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

#ifndef __LPM_H__
#define __LPM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LPM LPM模块驱动库
 * @{
 */
    
/******************************************************************************
 ** Global pre-processor symbols/macros ('#define')                            
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup LPM_Global_Functions LPM全局函数定义
 * @{
 */

/**
 * @brief  进入深度睡眠模式.
 */
void Lpm_GotoSleep(boolean_t bOnExit);

/**
 * @brief  进入普通睡眠模式.
 */
void Lpm_GotoDeepSleep(boolean_t bOnExit);

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


#endif /* __LPM_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


