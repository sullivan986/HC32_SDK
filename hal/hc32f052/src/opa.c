/**
 *******************************************************************************
 * @file  lvd.c
 * @brief This file provides firmware functions to manage the LVD.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-08-10       MADS             First version
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
#include "opa.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_OPA OPA模块驱动库
 * @brief OPA Driver Library OPA模块驱动库
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
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup OPA_Global_Functions OPA全局函数定义
 * @{
 */

/**
 * @brief  OPA 通道使能
 *
 * @param  NewStatus : TRUE FALSE    
 * @retval None
 */
void Opa_Cmd(en_opa_ch_sel_t enOpaChSel, boolean_t NewStatus)
{
    uint32_t u32Val;
    
    u32Val =  (uint32_t)(&HC_OPA->CR0) + (uint32_t)enOpaChSel;
    
    SetBit(u32Val, 0u, NewStatus);
}


/**
 * @brief  OPA零点校准配置
 *
 * @param  InitZero :  
 * @retval None
 */
void Opa_SetZero(en_opa_ch_sel_t enOpaChSel, stc_opa_zcfg_t* InitZero)
{
    uint32_t u32Val;
    
    u32Val =  (uint32_t)(&HC_OPA->CR0) + (uint32_t)enOpaChSel;
    
    SetBit(u32Val, 1u, InitZero->bAzen);
    HC_OPA->AZ_f.CLKSWSET = InitZero->bClk_sw_set;
    HC_OPA->AZ_f.AZPULSE  = InitZero->bAz_pulse;
    HC_OPA->AZ_f.CLKSEL   = InitZero->enClksrc;
    HC_OPA->AZ_f.TRIGGER  = InitZero->bTrigger;
    HC_OPA->AZ_f.ADCTREN  = InitZero->bAdctr_en; 
}

/**
 * @brief  配置校零相关的位
 *
 * @param  CtrlBit : en_opa_set0ctrl_t定义的元素
 * @param  NewState: TRUE 或 FALSE
 * @retval None
 */
void Opa_ZeroBitCtrl(en_opa_set0ctrl_t CtrlBit, boolean_t NewState)
{
    SetBit((uint32_t)(&(HC_OPA->AZ)), CtrlBit, NewState);  
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

