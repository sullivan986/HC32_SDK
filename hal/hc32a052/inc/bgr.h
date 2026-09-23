/**
 *******************************************************************************
 * @file  bgr.h
 * @brief This file contains all the functions prototypes of the BGR driver
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

#ifndef __BGR_H__
#define __BGR_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_BGR BGR模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)                        
 ******************************************************************************/
/**
 * @addtogroup BGR_Global_Functions BGR全局函数定义
 * @{
 */

/**
 * @brief 内部温度传感器使能
 */
void Bgr_TempSensorEnable(void);

/**
 * @brief 内部温度传感器关闭
 */
void Bgr_TempSensorDisable(void);

/**
 * @brief BGR使能
 */
void Bgr_BgrEnable(void);

/**
 * @brief BGR关闭
 */
void Bgr_BgrDisable(void);

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

#endif /* __BGR_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

