/**
 *******************************************************************************
 * @file  atim012.c
 * @brief This file provides firmware functions to manage the Atimer012.
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
#include "atim012.h"
/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_ATIM012 ATIM012模块驱动库
 * @brief ATIM012 Driver Library ATIM012模块驱动库
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
 * @defgroup ATIM012_Global_Functions ATIM012全局函数定义
 * @{
 */
   
/**
 * @brief  Atimer012 中断标志获取(模式0/1/23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enAtimIrq:  中断类型 @ref en_atim_irq_type_t
 * 
 * @retval boolean_t: 
 *         - FALSE: 标志未置起
 *         - TRUE: 标志已置起
 */
boolean_t Atim_GetIntFlag(en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq)
{
    boolean_t bRetVal = FALSE;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    u32Val = pstcM0PAtim->IFR;
    bRetVal = ((u32Val>>enAtimIrq) & 0x1u) ? TRUE : FALSE;

    return bRetVal;
}

/**
 * @brief  Atimer012 中断标志清除(模式0/1/23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enAtimIrq:  中断类型 @ref en_atim_irq_type_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_ClearIntFlag(en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->ICLR = ~(1u<<enAtimIrq);
    
    return enResult;
}

/**
 * @brief  Atimer012 中断所有标志清除(模式0/1/23)
 * @param  [in] enUnit:    Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_ClearAllIntFlag(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->ICLR  = 0u;
    
    return enResult;
}

/**
 * @brief  Atimer012 中断使能(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode0_EnableIrq(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->M0CR_f.UIE = TRUE;
    
    return enResult;
}

/**
 * @brief  Atimer012 中断禁止(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode0_DisableIrq(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->M0CR_f.UIE = FALSE;

    return enResult;
}

/**
 * @brief  Atimer012 中断使能(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enAtimIrq:  中断类型 @ref en_atim_irq_type_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode1_EnableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    switch (enAtimIrq)
    {
        case AtimUevIrq:
            pstcM0PAtim->M1CR_f.UIE = TRUE;
            break;
        case AtimPwcCA0Irq:
            pstcM0PAtim->CR0_f.CIEA = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer012 中断禁止(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enAtimIrq:  中断类型 @ref en_atim_irq_type_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode1_DisableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);

    switch (enAtimIrq)
    {
        case AtimUevIrq:
            pstcM0PAtim->M1CR_f.UIE = FALSE;
            break;
        case AtimPwcCA0Irq:
            pstcM0PAtim->CR0_f.CIEA = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer012 中断使能(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enAtimIrq:  中断类型 @ref en_atim_irq_type_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败 
 */
en_result_t Atim_Mode23_EnableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    
    switch (enAtimIrq)
    {
        case AtimUevIrq:
            pstcM0PAtim->M23CR_f.UIE = TRUE;
            break;
        case AtimPwcCA0Irq:
            pstcM0PAtim->CRCH0_f.CIEA = TRUE;
            break;
        case AtimCB0Irq:
            pstcM0PAtim->CRCH0_f.CIEB = TRUE;
            break;
        case AtimBkIrq:
            pstcM0PAtim->M23CR_f.BIE = TRUE;
            break;
        case AtimTrigIrq:
            pstcM0PAtim->M23CR_f.TIE = TRUE;
            break;
        case AtimOvIrq:
            pstcM0PAtim->M23CR_f.OVE = TRUE;
            break;
        case AtimUndIrq:
            pstcM0PAtim->M23CR_f.UNDE = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer012 中断禁止(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enAtimIrq:  中断类型 @ref en_atim_irq_type_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode23_DisableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
        
    switch (enAtimIrq)
    {
        case AtimUevIrq:
            pstcM0PAtim->M23CR_f.UIE = FALSE;
            break;
        case AtimPwcCA0Irq:
            pstcM0PAtim->CRCH0_f.CIEA = FALSE;
            break;
        case AtimCB0Irq:
            pstcM0PAtim->CRCH0_f.CIEB = FALSE;
            break;
        case AtimBkIrq:
            pstcM0PAtim->M23CR_f.BIE = FALSE;
            break;
        case AtimTrigIrq:
            pstcM0PAtim->M23CR_f.TIE = FALSE;
            break;
        case AtimOvIrq:
            pstcM0PAtim->M23CR_f.OVE = FALSE;
            break;
        case AtimUndIrq:
            pstcM0PAtim->M23CR_f.UNDE = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer012 初始化配置(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:   初始化配置结构体指针 @ref stc_atim_mode0_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode0_Init(en_atim_unit_t enUnit, stc_atim_mode0_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->M0CR_f.MODE   = pstcCfg->enWorkMode;
    pstcM0PAtim->M0CR_f.GATEP  = pstcCfg->enGateP;
    pstcM0PAtim->M0CR_f.GATE   = pstcCfg->bEnGate;
    pstcM0PAtim->M0CR_f.PRS    = pstcCfg->enPRS;
    pstcM0PAtim->M0CR_f.TOGEN  = pstcCfg->bEnTog;
    pstcM0PAtim->M0CR_f.CT     = pstcCfg->enCT;
    pstcM0PAtim->M0CR_f.MD     = pstcCfg->enCntMode; 
    
    return enResult;
}

/**
 * @brief  Atimer012 启动运行(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2) @ref en_atim_unit_t
 * 
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_Run(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->M0CR_f.CTEN = 1u;
    
    return enResult;    
}

/**
 * @brief  Atimer012 停止运行(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_Stop(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->M0CR_f.CTEN = 0u;
    
    return enResult;  
}

/**
 * @brief  Atimer012 翻转输出使能/禁止(低电平)设定(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] bEnTOG:     翻转输出设定 TRUE:使能, FALSE:禁止
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_EnTOG_Output(en_atim_unit_t enUnit, boolean_t bEnTOG)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->M0CR_f.TOGEN = bEnTOG;
    
    return enResult;    
}

/**
 * @brief  Atimer012 端口输出使能/禁止设定(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] bEnOutput:  端口输出设定 TRUE:使能, FALSE:禁止
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_Enable_Output(en_atim_unit_t enUnit, boolean_t bEnOutput)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->DTR_f.MOE = bEnOutput;
    
    return enResult;    
}

/**
 * @brief  Atimer012 16位计数器初值设置(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] u16Data:   16位初值
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_Cnt16Set(en_atim_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->CNT_f.CNT = u16Data;
    
    return enResult; 
}

/**
 * @brief  Atimer012 16位计数值获取(模式0)
 * @param  [in] enUnit:     AAtimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval uint16_t：16bits计数值 
 */
uint16_t Atim_M0_Cnt16Get(en_atim_unit_t enUnit)
{
    uint16_t    u16CntData = 0u;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    u16CntData = (uint16_t)pstcM0PAtim->CNT_f.CNT;
    
    return u16CntData; 
}

/**
 * @brief  Atimer012 重载值设置(模式0)
 * @param  [in] enUnit:     AAtimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] u16Data:   16bits重载值
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_ARRSet(en_atim_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->ARR_f.ARR = u16Data;

    return enResult; 
}

/**
 * @brief  Atimer012 32位计数器初值设置(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] u32Data:   32位初值
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M0_Cnt32Set(en_atim_unit_t enUnit, uint32_t u32Data)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    pstcM0PAtim->CNT32_f.CNT32 = u32Data;
    
    return enResult;
}

/**
 * @brief  Atimer012 32位计数值获取(模式0)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 *
 * 
 * @retval uint32_t：32bits计数值 
 */
uint32_t Atim_M0_Cnt32Get(en_atim_unit_t enUnit)
{
    uint32_t    u32CntData = 0u;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE0 + (uint32_t)enUnit;
    volatile ATIMMODE0_TypeDef *pstcM0PAtim = (ATIMMODE0_TypeDef *)(u32Val);
    
    u32CntData = pstcM0PAtim->CNT32_f.CNT32;
    
    return u32CntData;
}

/**
 * @brief  Atimer012 初始化配置(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:    初始化配置结构体指针 @ref stc_atim_mode1_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败 
 */
en_result_t Atim_Mode1_Init(en_atim_unit_t enUnit, stc_atim_mode1_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    pstcM0PAtim->M1CR_f.MODE    = pstcCfg->enWorkMode;
    pstcM0PAtim->M1CR_f.PRS     = pstcCfg->enPRS;
    pstcM0PAtim->M1CR_f.CT      = pstcCfg->enCT;
    pstcM0PAtim->M1CR_f.ONESHOT = pstcCfg->enOneShot;

    
    return enResult;
}

/**
 * @brief  Atimer012 PWC 输入配置(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:    模式1输入配置结构体指针 @ref stc_atim_pwc_input_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M1_Input_Cfg(en_atim_unit_t enUnit, stc_atim_pwc_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    pstcM0PAtim->MSCR_f.TS    = pstcCfg->enTsSel;
    pstcM0PAtim->MSCR_f.IA0S  = pstcCfg->enIA0Sel;
    pstcM0PAtim->MSCR_f.IB0S  = pstcCfg->enIB0Sel;
    pstcM0PAtim->FLTR_f.ETP   = pstcCfg->enETRPhase;
    pstcM0PAtim->FLTR_f.FLTET = pstcCfg->enFltETR;
    if(AtimFltNone != pstcCfg->enFltIA0)
    {
        pstcM0PAtim->CR0_f.CSA    = 1u;
        pstcM0PAtim->FLTR_f.FLTA0 = pstcCfg->enFltIA0;
    }
    if(AtimFltNone != pstcCfg->enFltIB0)
    {
        pstcM0PAtim->CR0_f.CSB    = 1u;
        pstcM0PAtim->FLTR_f.FLTB0 = pstcCfg->enFltIB0;
    }
    
    return enResult;
}

/**
 * @brief  Atimer012 PWC 测量边沿起始结束选择(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enEdgeSel:  pwc测量起始终止电平 @ref en_atim_m1cr_Edge_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M1_PWC_Edge_Sel(en_atim_unit_t enUnit,en_atim_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    REG_MODIFY(pstcM0PAtim->M1CR, ATIMMODE1_M1CR_EDG1ST|ATIMMODE1_M1CR_EDG2ND, (uint32_t)enEdgeSel << ATIMMODE1_M1CR_EDG1ST_Pos);
    
    return enResult;    
}

/**
 * @brief  Atimer012 启动运行(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 *
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M1_Run(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    pstcM0PAtim->M1CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer012 停止运行(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 *
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败 
 */
en_result_t Atim_M1_Stop(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    pstcM0PAtim->M1CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 * @brief  Atimer012  16位计数器初值设置(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] u16Data:    16位初值
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M1_Cnt16Set(en_atim_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    pstcM0PAtim->CNT_f.CNT = u16Data;
    
    return enResult;
}

/**
 * @brief  Atimer012 16位计数值获取(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval uint16_t：16bits计数值 
 */
uint16_t Atim_M1_Cnt16Get(en_atim_unit_t enUnit)
{
    uint16_t    u16CntData = 0u;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    u16CntData = (uint16_t)pstcM0PAtim->CNT_f.CNT;
    
    return u16CntData;
}

/**
 * @brief  Atimer012 脉冲宽度测量结果数值获取(模式1)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval uint16_t：16bits脉冲宽度测量结果 
 */
uint16_t Atim_M1_PWC_CapValueGet(en_atim_unit_t enUnit)
{
    uint16_t    u16CapData = 0u;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE1 + (uint32_t)enUnit;
    volatile ATIMMODE1_TypeDef *pstcM0PAtim = (ATIMMODE1_TypeDef *)(u32Val);
    
    u16CapData = (uint16_t)pstcM0PAtim->CCR0A_f.CCR0A;
    
    return u16CapData;
}

/**
 * @brief  Atimer012  初始化配置(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:    初始化配置结构体指针  @ref stc_atim_mode23_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_Mode23_Init(en_atim_unit_t enUnit, stc_atim_mode23_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.MODE    = pstcCfg->enWorkMode;
    
    pstcM0PAtim->M23CR_f.PRS     = pstcCfg->enPRS;
    pstcM0PAtim->M23CR_f.CT      = pstcCfg->enCT;
    pstcM0PAtim->M23CR_f.COMP    = pstcCfg->enPWMTypeSel;
    pstcM0PAtim->M23CR_f.PWM2S   = pstcCfg->enPWM2sSel;
    pstcM0PAtim->M23CR_f.ONESHOT = pstcCfg->bOneShot;
    pstcM0PAtim->M23CR_f.URS     = pstcCfg->bURSSel;
    pstcM0PAtim->M23CR_f.DIR     = pstcCfg->enCntDir;

    
    return enResult;
}

/**
 * @brief  Atimer012  PWM输出使能/禁止(模式23)
 * @param  [in] enUnit:        Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] bEnOutput:      PWM输出使能/禁止设定
 * @param  [in] bEnAutoOutput:  PWM自动输出使能/禁止设定
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnPWM_Output(en_atim_unit_t enUnit, boolean_t bEnOutput, boolean_t bEnAutoOutput)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->DTR_f.MOE = bEnOutput;
    pstcM0PAtim->DTR_f.AOE = bEnAutoOutput;
    
    return enResult;
}

/**
 * @brief  Atimer012 启动运行(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 *
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_Run(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.CTEN = TRUE;
    
    return enResult;
}

/**
 * @brief  Atimer012 停止运行(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 *
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_Stop(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 * @brief  Atimer012  重载值设置(模式23)
 * @param  [in] enUnit:        Atimer012选择(ATIM0、ATIM1、ATIM2) @ref en_atim_unit_t
 * @param  [in] u16Data:       16bits重载值
 * @param  [in] bArrBufEn:      ARR重载缓存使能TRUE/禁止FALSE
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_ARRSet(en_atim_unit_t enUnit, uint16_t u16Data, boolean_t bArrBufEn)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
     pstcM0PAtim->ARR_f.ARR = u16Data;
     pstcM0PAtim->M23CR_f.BUFPEN  = bArrBufEn;

    return enResult; 
}

/**
 * @brief  Atimer012  16位计数器初值设置(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] u16Data:    16位初值
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_Cnt16Set(en_atim_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->CNT_f.CNT       = u16Data;

    return enResult; 
}

/**
 * @brief  Atimer012 16位计数值获取(模式23)
 * @param  [in] enUnit:     Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * 
 * @retval uint16_t: 16bits计数值 
 */
uint16_t Atim_M23_Cnt16Get(en_atim_unit_t enUnit)
{
    uint16_t    u16CntData = 0u;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    u16CntData = (uint16_t)pstcM0PAtim->CNT_f.CNT;
    
    return u16CntData; 
}

/**
 * @brief  Atimer012  比较捕获寄存器CCR0A/CCR0B设置(模式23)
 * @param  [in] enUnit:        Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enCCRSel:      CCR0A/CCR0B设定  @ref en_atim_m23_ccrx_t
 * @param  [in] u16Data:       CCR0A/CCR0B 16位初始值
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_CCR_Set(en_atim_unit_t enUnit, en_atim_m23_ccrx_t enCCRSel, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    if(AtimCCR0A == enCCRSel)
    {
        pstcM0PAtim->CCR0A_f.CCR0A = u16Data;
    }
    else if(AtimCCR0B == enCCRSel)
    {
        pstcM0PAtim->CCR0B_f.CCR0B = u16Data;
    }
    else
    {
        enResult = Error;
    }
    
    return enResult;
}

/**
 * @brief  Atimer012  比较捕获寄存器CCR0A/CCR0B读取(模式23)
 * @param  [in] enUnit:        Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] enCCRSel:      CCR0A/CCR0B设定  @ref en_atim_m23_ccrx_t
 * 
 * @retval uint16_t: 16bitsCCR0A捕获值
 */
uint16_t Atim_M23_CCR_Get(en_atim_unit_t enUnit, en_atim_m23_ccrx_t enCCRSel)
{
    uint16_t    u16Data = 0u;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);

    if(AtimCCR0A == enCCRSel)
    {
        u16Data = (uint16_t)pstcM0PAtim->CCR0A_f.CCR0A;
    }
    else if(AtimCCR0B == enCCRSel)
    {
        u16Data = (uint16_t)pstcM0PAtim->CCR0B_f.CCR0B;
    }
    else
    {
        u16Data = 0u;
    }
    
    return u16Data; 
}

/**
 * @brief  Atimer012  PWM互补输出模式下，GATE功能选择(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      GATE配置结构体指针  @ref stc_atim_m23_gate_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_GateFuncSel(en_atim_unit_t enUnit,stc_atim_m23_gate_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.CSG = pstcCfg->enGateFuncSel;
    pstcM0PAtim->M23CR_f.CRG = pstcCfg->bGateRiseCap;
    pstcM0PAtim->M23CR_f.CFG = pstcCfg->bGateFallCap;
    
    return enResult;    
}

/**
 * @brief  Atimer012  PWM互补输出模式下，GATE功能选择(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      MS配置结构体指针  @ref stc_atim_m23_master_slave_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_MasterSlave_Set(en_atim_unit_t enUnit, stc_atim_m23_master_slave_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->MSCR_f.MSM = pstcCfg->enMasterSlaveSel;
    pstcM0PAtim->MSCR_f.MMS = pstcCfg->enMasterSrc;
    pstcM0PAtim->MSCR_f.SMS = pstcCfg->enSlaveModeSel;
    pstcM0PAtim->MSCR_f.TS  = pstcCfg->enTsSel;
    
    return enResult;    
}

/**
 * @brief  Atimer012  CH0A/CH0B比较通道输出控制(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      比较输出配置结构体指针  @ref stc_atim_m23_compare_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_PortOutput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_compare_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->CRCH0_f.CSA         = 0u;
    pstcM0PAtim->FLTR_f.OCMA0FLTA0  = pstcCfg->enCH0ACmpCtrl;
    pstcM0PAtim->FLTR_f.CCPA0        = pstcCfg->enCH0APolarity;
    pstcM0PAtim->CRCH0_f.BUFEA       = pstcCfg->bCh0ACmpBufEn;
    pstcM0PAtim->M23CR_f.CIS         = pstcCfg->enCh0ACmpIntSel;
    
    pstcM0PAtim->CRCH0_f.CSB         = 0u;
    pstcM0PAtim->FLTR_f.OCMB0FLTB0  = pstcCfg->enCH0BCmpCtrl;
    pstcM0PAtim->FLTR_f.CCPB0        = pstcCfg->enCH0BPolarity;
    pstcM0PAtim->CRCH0_f.BUFEB       = pstcCfg->bCH0BCmpBufEn;
    pstcM0PAtim->CRCH0_f.CISB        = pstcCfg->enCH0BCmpIntSel;
    
    return enResult;    
}

/**
 * @brief  Atimer012  CH0A/CH0B输入控制(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      输入配置结构体指针  @ref stc_atim_m23_input_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_PortInput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->CRCH0_f.CSA           = 1u;
    pstcM0PAtim->CRCH0_f.CFACRABKSA  = pstcCfg->enCH0ACapSel;
    pstcM0PAtim->FLTR_f.OCMA0FLTA0    = pstcCfg->enCH0AInFlt;
    pstcM0PAtim->FLTR_f.CCPA0          = pstcCfg->enCH0APolarity;
    
    pstcM0PAtim->CRCH0_f.CSB           = 1u;
    pstcM0PAtim->CRCH0_f.CFBCRBBKSB  = pstcCfg->enCH0BCapSel;
    pstcM0PAtim->FLTR_f.OCMB0FLTB0    = pstcCfg->enCH0BInFlt;
    pstcM0PAtim->FLTR_f.CCPB0          = pstcCfg->enCH0BPolarity;
    
    return enResult;    
}

/**
 * @brief  Atimer012  ERT输入控制(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      ETR输入配置结构体指针  @ref stc_atim_m23_etr_input_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_ETRInput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_etr_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->FLTR_f.ETP    = pstcCfg->enETRPolarity;
    pstcM0PAtim->FLTR_f.FLTET  = pstcCfg->enETRFlt;
    
    return enResult;    
}

/**
 * @brief  Atimer012  刹车BK输入控制(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      刹车BK输入配置结构体指针  @ref stc_atim_m23_bk_input_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_BrakeInput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_bk_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->DTR_f.BKE             = pstcCfg->bEnBrake;
    pstcM0PAtim->DTR_f.VCE             = pstcCfg->bEnVCBrake;
    pstcM0PAtim->DTR_f.SAFEEN          = pstcCfg->bEnSafetyBk;
    pstcM0PAtim->DTR_f.BKSEL           = pstcCfg->bEnBKSync;
    pstcM0PAtim->CRCH0_f.CFACRABKSA  = pstcCfg->enBkCH0AStat;
    pstcM0PAtim->CRCH0_f.CFBCRBBKSB  = pstcCfg->enBkCH0BStat;
    pstcM0PAtim->FLTR_f.BKP            = pstcCfg->enBrakePolarity;
    pstcM0PAtim->FLTR_f.FLTBK          = pstcCfg->enBrakeFlt;
    
    return enResult;
}

/**
 * @brief  Atimer012  触发ADC控制(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      触发ADC配置结构体指针  @ref stc_atim_m23_adc_trig_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_TrigADC_Cfg(en_atim_unit_t enUnit, stc_atim_m23_adc_trig_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->ADTR_f.ADTE   = pstcCfg->bEnTrigADC;
    pstcM0PAtim->ADTR_f.UEVE   = pstcCfg->bEnUevTrigADC;
    pstcM0PAtim->ADTR_f.CMA0E  = pstcCfg->bEnCH0ACmpTrigADC;
    pstcM0PAtim->ADTR_f.CMB0E  = pstcCfg->bEnCH0BCmpTrigADC;
    
    return enResult;    
}

/**
 * @brief  Atimer012  死区功能(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      死区功能配置结构体指针  @ref stc_atim_m23_dt_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_DT_Cfg(en_atim_unit_t enUnit, stc_atim_m23_dt_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->DTR_f.DTEN = pstcCfg->bEnDeadTime;
    pstcM0PAtim->DTR_f.DTR  = pstcCfg->u8DeadTimeValue;
    
    return enResult;    
}

/**
 * @brief  Atimer012  重复周期设置(模式23)
 * @param  [in] enUnit:         Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] u8ValidPeriod:  8位重复周期值
 * @param  [in] bOVMaskEn:      屏蔽上溢重复计数使能
 * @param  [in] bUDMaskEn:      屏蔽下溢重复计数使能
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_SetValidPeriod(en_atim_unit_t enUnit, uint8_t u8ValidPeriod, boolean_t bOVMaskEn, boolean_t bUDMaskEn)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->RCR_f.RCR = u8ValidPeriod;
    pstcM0PAtim->RCR_f.OV = bOVMaskEn;
    pstcM0PAtim->RCR_f.UD = bUDMaskEn;
    
    return enResult;    
}

/**
 * @brief  Atimer012  OCREF清除功能(模式23)
 * @param  [in] enUnit:   Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:  OCREF清除功能配置结构体指针  @ref stc_atim_m23_OCREF_Clr_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_OCRefClr(en_atim_unit_t enUnit, stc_atim_m23_OCREF_Clr_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.OCCS = pstcCfg->enOCRefClrSrcSel;
    pstcM0PAtim->M23CR_f.OCCE = pstcCfg->bVCClrEn;
    
    return enResult;    
}

/**
 * @brief  Atimer012  使能DMA传输(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * @param  [in] pstcCfg:      触发DMA功能配置结构体指针  @ref stc_atim_m23_trig_dma_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnDMA(en_atim_unit_t enUnit, stc_atim_m23_trig_dma_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.UDE  = pstcCfg->bUevTrigDMA;
    pstcM0PAtim->M23CR_f.TDE  = pstcCfg->bTITrigDMA;
    pstcM0PAtim->CRCH0_f.CDEA = pstcCfg->bCmpATrigDMA;
    pstcM0PAtim->CRCH0_f.CDEB = pstcCfg->bCmpBTrigDMA;
    pstcM0PAtim->MSCR_f.CCDS  = pstcCfg->enCmpUevTrigDMA;
    
    return enResult;    
}

/**
 * @brief  Atimer012  捕获比较A软件触发(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnSwTrigCapCmpA(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->CRCH0_f.CCGA = TRUE;

    return enResult;    
}

/**
 * @brief  Atimer012  捕获比较B软件触发(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnSwTrigCapCmpB(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->CRCH0_f.CCGB = TRUE;

    return enResult;    
}

/**
 * @brief  Atimer012  软件更新使能(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnSwUev(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.UG = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer012  软件触发使能(模式23)
 * @param  [in] enUnit:       AAtimer012选择(ATIM0、ATIM1、ATIM2)  @ref en_atim_unit_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnSwTrig(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.TG = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer012  软件刹车使能(模式23)
 * @param  [in] enUnit:       Atimer012选择(ATIM0、ATIM1、ATIM2) @ref en_atim_unit_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Atim_M23_EnSwBk(en_atim_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32Val = (uint32_t)HC_ATIM0MODE23 + (uint32_t)enUnit;
    volatile ATIMMODE23_TypeDef *pstcM0PAtim = (ATIMMODE23_TypeDef *)(u32Val);
    
    pstcM0PAtim->M23CR_f.BG = TRUE;
    
    return enResult;    
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
