/**
 *******************************************************************************
 * @file  lpm.c
 * @brief This file provides firmware functions to manage the LPMODE.
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
#include "lpm.h"


/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPM LPM模块驱动库
 * @brief LPM Driver Library LPM模块驱动库
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
 * @defgroup LPM_Global_Functions LPM全局函数定义
 * @{
 */

/**
 * @brief  进入深度睡眠模式.
 * @param  [in] bOnExit: 
 *                      - TRUE: 当退出异常处理后，自动再次进入休眠；
 *                      - FALSE: 唤醒后不再自动进入休眠
 * @retval None.
 */
void Lpm_GotoDeepSleep(boolean_t bOnExit)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	
	if(bOnExit == TRUE)
	{
		SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	}
	else
	{
		SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
	}

    __WFI();
    __NOP();
}


/**
 * @brief  进入普通睡眠模式.
 * @param  [in] bOnExit: 
 *                      - TRUE: 当退出异常处理后，自动再次进入休眠；
 *                      - FALSE: 唤醒后不再自动进入休眠
 * @retval None.
 */
void Lpm_GotoSleep(boolean_t bOnExit)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	
    if(bOnExit == TRUE)
	{
		SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	}
	else
	{
		SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
	}
    __WFI();
    __NOP();
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
