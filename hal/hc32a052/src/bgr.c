/**
 *******************************************************************************
 * @file  bgr.c
 * @brief This file provides firmware functions to manage the BGR.
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
#include "bgr.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_BGR BGR模块驱动库
 * @brief BGR Driver Library BGR模块驱动库
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
 * @defgroup BGR_Global_Functions BGR全局函数定义
 * @{
 */
   
/**
 * @brief  BGR 使能
 * @retval None
 */
void Bgr_BgrEnable(void)
{    
    HC_ADC->BGR |= 0x1u;
    
    delay10us(6u);
}

/**
 * @brief  BGR 禁止
 * @retval None
 */
void Bgr_BgrDisable(void)
{
    HC_ADC->BGR &= 0x2u;
}

/**
 * @brief  BGR 温度传感器使能(需要先开启BGR)
 * @retval None
 */
void Bgr_TempSensorEnable(void)
{
    HC_ADC->BGR |= 0x2u;
    
    delay10us(6u);  
}

/**
 * @brief  BGR 温度传感器禁止
 * @retval None
 */
void Bgr_TempSensorDisable(void)
{
    HC_ADC->BGR &= 0x1u;
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
