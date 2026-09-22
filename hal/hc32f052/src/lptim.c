/**
 *******************************************************************************
 * @file  lptim.c
 * @brief This file provides firmware functions to manage the LPTIM.
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

/******************************************************************************
 * Include files
 ******************************************************************************/

#include "lptim.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPTIM LPTIM模块驱动库
 * @brief LPTIM Driver Library LPTIM模块驱动库
 * @{
 */

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
   
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup LPTIM_Global_Functions LPTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器LPTIMx中断使能控制
 * 
 * @param  Lptimx    : LPTIM0 或LPTIM1
 * @param  NewStatus : TRUE 或 FALSE
 * 
 * @retval None
 */
void Lptim_ConfIt(LPTIM_TypeDef* Lptimx, boolean_t NewStatus)
{
    SetBit((uint32_t)(&(Lptimx->CR)), 10u, NewStatus);
}

/**
 * @brief  定时器LPTIMx的启动/停止控制
 *
 * @param  Lptimx    : LPTIM0 或LPTIM1
 * @param  NewStatus : TRUE 或 FALSE
 *
 * @retval None
 */
void Lptim_Cmd(LPTIM_TypeDef* Lptimx, boolean_t NewStatus)
{
    SetBit((uint32_t)(&(Lptimx->CR)), 0u, NewStatus);
}

/**
 * @brief  定时器LPTIMx的中断标志位获取
 *
 * @param  Lptimx    : LPTIM0 或LPTIM1
 *
 * @retval boolean_t: TRUE 或 FALSE
 */
boolean_t Lptim_GetItStatus(LPTIM_TypeDef* Lptimx)
{
    return GetBit((uint32_t)(&(Lptimx->IFR)), 0u);
}

/**
 * @brief  定时器LPTIMx的中断标志位清除
 *
 * @param  Lptimx    : LPTIM0 或LPTIM1
 *
 * @retval None
 */
void Lptim_ClrItStatus(LPTIM_TypeDef* Lptimx)
{
    SetBit((uint32_t)(&(Lptimx->ICLR)), 0u, 0u);
}

/**
 * @brief  定时器LPTIMx的初始化配置
 *
 * @param  Lptimx    : LPTIM0 或LPTIM1
 * @param  InitStruct : 初始化LPTIMx的结构体
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Lptim_Init(LPTIM_TypeDef* Lptimx, stc_lptim_cfg_t* InitStruct)
{
    uint16_t u16TimeOut;
    u16TimeOut = 0x1000u;

    Lptimx->CR_f.TCK_SEL  = InitStruct->enTcksel;
    Lptimx->CR_f.GATE_P   = InitStruct->enGatep;
    Lptimx->CR_f.GATE     = InitStruct->enGate;
    Lptimx->CR_f.TOG_EN   = InitStruct->enTogen;
    Lptimx->CR_f.CT       = InitStruct->enCt;
    Lptimx->CR_f.MD       = InitStruct->enMd;
    Lptimx->CR_f.PRS      = InitStruct->enClkPrs;
    while(u16TimeOut--)
    {
        if(Lptimx->CR_f.WT_FLAG)
        {
            break;
        }
    
		if(u16TimeOut == 0u)
		{
			return ErrorTimeout;        
		}
	}
    Lptimx->ARR_f.ARR = InitStruct->u16Arr;
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

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
