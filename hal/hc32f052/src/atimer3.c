/**
 *******************************************************************************
 * @file  atimer3.c
 * @brief This file provides firmware functions to manage the ATIMER3.
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
#include "atimer3.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_ATIM3 ATIM3模块驱动库
 * @brief ATIM3 Driver Library ATIM3模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ATIM3_Local_Macros ATIM3局部宏定义
 * @{
 */
#define ATIM3_CRCH3_INIT_MASK   (ATIM3MODE23_CRCH3A_BUF|ATIM3MODE23_CRCH3A_CD|ATIM3MODE23_CRCH3A_CIS|ATIM3MODE23_CRCH3A_C3AEN)
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
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
 * @defgroup ATIM3_Global_Functions ATIM3全局函数定义
 * @{
 */

/**
 * @brief  Atimer3 中断标志获取(模式0/1/23)
 * @param  [in] enTim3Irq: 中断类型枚举定义 @ref en_tim3_irq_type_t
 *
 * @retval boolean_t: 
 *         - FALSE: 标志未置起
 *         - TRUE: 标志已置起
 */
boolean_t Tim3_GetIntFlag(en_tim3_irq_type_t enTim3Irq)
{
    return REG_READBITS(HC_ATIM3MODE23->IFR, 1u<<((uint32_t)enTim3Irq)) ? TRUE : FALSE;
}

/**
 * @brief  Atimer3 中断标志清除(模式0/1/23)
 * @param  [in] enTim3Irq: 中断类型枚举定义 @ref en_tim3_irq_type_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_ClearIntFlag(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;

    REG_CLEARBITS(HC_ATIM3MODE23->ICLR, 1u<<((uint32_t)enTim3Irq));
    
    return enResult;
}

/**
 * @brief  Atimer3 中断所有标志清除(模式23)
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_ClearAllIntFlag(void)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE23->ICLR = 0u;
    
    return enResult;
}

/**
 * @brief  Atimer3 中断使能(模式0)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode0_EnableIrq(void)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE0->M0CR_f.UIE = TRUE;

    return enResult;
}

/**
 * @brief  Atimer3 中断禁止(模式0)
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode0_DisableIrq(void)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE0->M0CR_f.UIE = FALSE;

    return enResult;
}

/**
 * @brief  Atimer3 中断使能(模式1)
 * @param [in] enTim3Irq:    中断类型定义 @ref en_tim3_irq_type_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode1_EnableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            HC_ATIM3MODE1->M1CR_f.UIE = TRUE;
            break;
        case Tim3PwcCA0Irq:
            HC_ATIM3MODE1->CR0_f.CIEA = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer3 中断禁止(模式1)
 * @param [in] enTim3Irq:    中断类型定义 @ref en_tim3_irq_type_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode1_DisableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            HC_ATIM3MODE1->M1CR_f.UIE = FALSE;
            break;
        case Tim3PwcCA0Irq:
            HC_ATIM3MODE1->CR0_f.CIEA = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer3 中断使能(模式23)
 * @param [in] enTim3Irq:    中断类型定义 @ref en_tim3_irq_type_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode23_EnableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            HC_ATIM3MODE23->M23CR_f.UIE = TRUE;
            break;
        case Tim3PwcCA0Irq:
            HC_ATIM3MODE23->CRCH0_f.CIEA = TRUE;
            break;
        case Tim3CB0Irq:
            HC_ATIM3MODE23->CRCH0_f.CIEB = TRUE;
            break;
        case Tim3CA1Irq:
            HC_ATIM3MODE23->CRCH1_f.CIEA = TRUE;
            break;
        case Tim3CB1Irq:
            HC_ATIM3MODE23->CRCH1_f.CIEB = TRUE;
            break;
        case Tim3CA2Irq:
            HC_ATIM3MODE23->CRCH2_f.CIEA = TRUE;
            break;
        case Tim3CB2Irq:
            HC_ATIM3MODE23->CRCH2_f.CIEB = TRUE;
            break;
        case Tim3BkIrq:
            HC_ATIM3MODE23->M23CR_f.BIE = TRUE;
            break;
        case Tim3TrigIrq:
            HC_ATIM3MODE23->M23CR_f.TIE = TRUE;
            break;
        case Tim3OVIrq:
            HC_ATIM3MODE23->M23CR_f.OVE = TRUE;
            break;
        case Tim3UDIrq:
            HC_ATIM3MODE23->M23CR_f.UDE = TRUE;
            break;
        case Tim3CA3Irq:
            HC_ATIM3MODE23->CRCH3A_f.CI = TRUE;
            break;
        case Tim3CB3Irq:
            HC_ATIM3MODE23->CRCH3B_f.CI = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer3 中断禁止(模式23)
 * @param [in] enTim3Irq:    中断类型定义 @ref en_tim3_irq_type_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode23_DisableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            HC_ATIM3MODE23->M23CR_f.UIE = FALSE;
            break;
        case Tim3PwcCA0Irq:
            HC_ATIM3MODE23->CRCH0_f.CIEA = FALSE;
            break;
        case Tim3CB0Irq:
            HC_ATIM3MODE23->CRCH0_f.CIEB = FALSE;
            break;
        case Tim3CA1Irq:
            HC_ATIM3MODE23->CRCH1_f.CIEA = FALSE;
            break;
        case Tim3CB1Irq:
            HC_ATIM3MODE23->CRCH1_f.CIEB = FALSE;
            break;
        case Tim3CA2Irq:
            HC_ATIM3MODE23->CRCH2_f.CIEA = FALSE;
            break;
        case Tim3CB2Irq:
            HC_ATIM3MODE23->CRCH2_f.CIEB = FALSE;
            break;
        case Tim3BkIrq:
            HC_ATIM3MODE23->M23CR_f.BIE = FALSE;
            break;
        case Tim3TrigIrq:
            HC_ATIM3MODE23->M23CR_f.TIE = FALSE;
            break;
        case Tim3OVIrq:
            HC_ATIM3MODE23->M23CR_f.OVE = FALSE;
            break;
        case Tim3UDIrq:
            HC_ATIM3MODE23->M23CR_f.UDE = FALSE;
            break;
        case Tim3CA3Irq:
            HC_ATIM3MODE23->CRCH3A_f.CI = FALSE;
            break;
        case Tim3CB3Irq:
            HC_ATIM3MODE23->CRCH3B_f.CI = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 * @brief  Atimer3 初始化配置(模式0)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_mode0_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode0_Init(stc_tim3_mode0_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    HC_ATIM3MODE0->M0CR_f.MODE   = pstcCfg->enWorkMode;
    HC_ATIM3MODE0->M0CR_f.GATEP  = pstcCfg->enGateP;
    HC_ATIM3MODE0->M0CR_f.GATE   = pstcCfg->bEnGate;
    HC_ATIM3MODE0->M0CR_f.PRS    = pstcCfg->enPRS;
    HC_ATIM3MODE0->M0CR_f.TOGEN  = pstcCfg->bEnTog;
    HC_ATIM3MODE0->M0CR_f.CT     = pstcCfg->enCT;
    HC_ATIM3MODE0->M0CR_f.MD     = pstcCfg->enCntMode; 
    
    return enResult;
}

/**
 * @brief  Atimer3 启动运行(模式0)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_Run(void)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE0->M0CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer3 停止运行(模式0)
 * 
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_Stop(void)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE0->M0CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 * @brief  Atimer3 端口输出使能/禁止设定(模式0)
 * @param [in] bEnOutput:    翻转输出设定 TRUE:使能, FALSE:禁止
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_Enable_Output(boolean_t bEnOutput)
{
    en_result_t enResult = Ok;
    

    HC_ATIM3MODE0->DTR_f.MOE = bEnOutput;
    
    return enResult;    
}

/**
 * @brief  Atimer3 翻转使能/禁止(低电平)设定(模式0)
 * @param [in] bEnTOG:    翻转输出设定 
 *             - TRUE:使能
 *             - FALSE:禁止
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_EnTOG(boolean_t bEnTOG)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE0->M0CR_f.TOGEN = bEnTOG;
    
    return enResult;  
}

/**
 * @brief  Atimer3 16位计数器初值设置设定(模式0)
 * @param [in] u16Data:    CNT 16位初值
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE0->CNT_f.CNT = u16Data;
 
    return enResult; 
}

/**
 * @brief  Atimer3 16位计数值获取(模式0)
 *
 * @retval uint16_t: 16bits计数值
 */
uint16_t Tim3_M0_Cnt16Get(void)
{
    uint32_t    u32CntData = 0u;
      
    u32CntData = HC_ATIM3MODE0->CNT_f.CNT;
    
    return (uint16_t)u32CntData; 
}

/**
 * @brief  Atimer3 重载值设置(模式0)
 * @param [in] u16Data:    16bits重载值
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_ARRSet(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE0->ARR_f.ARR = u16Data;

    return enResult; 
}

/**
 * @brief  Atimer3 32位计数器初值设置(模式0)
 * @param [in] u32Data:    32位初值
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M0_Cnt32Set(uint32_t u32Data)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE0->CNT32_f.CNT32 = u32Data;
    
    return enResult; 
}

/**
 * @brief  Atimer3 32位计数值获取(模式0)
 *
 * @retval uint32_t: 32bits计数值
 */
uint32_t Tim3_M0_Cnt32Get(void)
{
    return HC_ATIM3MODE0->CNT32_f.CNT32;
}

/**
 * @brief  Atimer3 初始化配置(模式1)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_mode1_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode1_Init(stc_tim3_mode1_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    HC_ATIM3MODE1->M1CR_f.MODE    = pstcCfg->enWorkMode;
    HC_ATIM3MODE1->M1CR_f.PRS     = pstcCfg->enPRS;
    HC_ATIM3MODE1->M1CR_f.CT      = pstcCfg->enCT;
    HC_ATIM3MODE1->M1CR_f.ONESHOT = pstcCfg->enOneShot;
    
    return enResult;
}

/**
 * @brief  Atimer3 PWC 输入配置(模式1)
 * @param [in] pstcCfg:    PWC初始化配置结构体指针 @ref stc_tim3_pwc_input_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M1_Input_Cfg(stc_tim3_pwc_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE1->MSCR_f.TS    = pstcCfg->enTsSel;
    HC_ATIM3MODE1->MSCR_f.IA0S  = pstcCfg->enIA0Sel;
    HC_ATIM3MODE1->MSCR_f.IB0S  = pstcCfg->enIB0Sel;
    HC_ATIM3MODE1->FLTR_f.ETP   = pstcCfg->enETRPhase;
    HC_ATIM3MODE1->FLTR_f.FLTET = pstcCfg->enFltETR;
    if(Tim3FltNone != pstcCfg->enFltIA0)
    {
        HC_ATIM3MODE1->CR0_f.CSA    = 1u;
        HC_ATIM3MODE1->FLTR_f.FLTA0 = pstcCfg->enFltIA0;
    }
    if(Tim3FltNone != pstcCfg->enFltIB0)
    {
        HC_ATIM3MODE1->CR0_f.CSB    = 1u;
        HC_ATIM3MODE1->FLTR_f.FLTB0 = pstcCfg->enFltIB0;
    }
    
    return enResult;
}

/**
 * @brief  Atimer3 PWC 测量边沿起始结束选择(模式1)
 * @param [in] enEdgeSel:    pwc测量起始终止电平定义 @ref en_tim3_m1cr_Edge_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M1_PWC_Edge_Sel(en_tim3_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;
        
    switch (enEdgeSel)
    {
        case 0:                                 /* 上升沿到上升沿(周期) */
            HC_ATIM3MODE1->M1CR_f.EDG1ST = 0u;  /* 上升沿 */
            HC_ATIM3MODE1->M1CR_f.EDG2ND = 0u;  /* 上升沿 */
            break;
        case 1:                                 /* 下降沿到上升沿(低电平) */
            HC_ATIM3MODE1->M1CR_f.EDG1ST = 1u;  /* 下降沿 */
            HC_ATIM3MODE1->M1CR_f.EDG2ND = 0u;  /* 上升沿 */
            break;
        case 2:                                 /* 上升沿到下降沿(高电平) */
            HC_ATIM3MODE1->M1CR_f.EDG1ST = 0u;  /* 上升沿 */
            HC_ATIM3MODE1->M1CR_f.EDG2ND = 1u;  /* 下降沿 */
            break;
        case 3:                                 /* 下降沿到下降沿(周期) */
            HC_ATIM3MODE1->M1CR_f.EDG1ST = 1u;  /* 下降沿 */
            HC_ATIM3MODE1->M1CR_f.EDG2ND = 1u;  /* 下降沿 */
            break;
        default:
            ;
            break;       
    }
    
    return enResult;    
}

/**
 * @brief  Atimer3 启动运行(模式1)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M1_Run(void)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE1->M1CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer3 停止运行(模式1)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M1_Stop(void)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE1->M1CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 * @brief  Atimer3 16位计数器初值设置设定(模式1)
 * @param [in] u16Data:    CNT 16位初值
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M1_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    HC_ATIM3MODE1->CNT_f.CNT = u16Data;
    
    return enResult; 
}

/**
 * @brief  Atimer3 16位计数值获取(模式1)
 * 
 * @retval uint16_t: 16bits计数值
 */
uint16_t Tim3_M1_Cnt16Get(void)
{
    uint32_t    u32CntData = 0u;
  
    u32CntData = HC_ATIM3MODE1->CNT_f.CNT;
        
    return (uint16_t)u32CntData; 
}

/**
 * @brief  Atimer3 脉冲宽度测量结果数值获取(模式1)
 *
 * @retval uint16_t: 16bits脉冲宽度测量结果
 */
uint16_t Tim3_M1_PWC_CapValueGet(void)
{
    uint32_t    u32CapData = 0u;
  
    u32CapData = HC_ATIM3MODE1->CCR0A_f.CCR0A;
        
    return (uint16_t)u32CapData; 
}

/**
 * @brief  Atimer3 初始化配置(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_mode23_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_Mode23_Init(stc_tim3_mode23_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    HC_ATIM3MODE23->M23CR_f.MODE    = pstcCfg->enWorkMode;
    
    HC_ATIM3MODE23->M23CR_f.PRS     = pstcCfg->enPRS;
    HC_ATIM3MODE23->M23CR_f.CT      = pstcCfg->enCT;
    HC_ATIM3MODE23->M23CR_f.COMP    = pstcCfg->enPWMTypeSel;
    HC_ATIM3MODE23->M23CR_f.PWM2S   = pstcCfg->enPWM2sSel;
    HC_ATIM3MODE23->M23CR_f.ONESHOT = pstcCfg->bOneShot;
    HC_ATIM3MODE23->M23CR_f.URS     = pstcCfg->bURSSel;
    HC_ATIM3MODE23->M23CR_f.DIR     = pstcCfg->enCntDir;
        
    return enResult;
}

/**
 * @brief  Atimer3 PWM输出使能(模式23)
 * @param [in] bEnOutput:       PWM输出使能/禁止设定
 * @param [in] bEnAutoOutput:   PWM自动输出使能/禁止设定
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->DTR_f.MOE = bEnOutput;
    HC_ATIM3MODE23->DTR_f.AOE = bEnAutoOutput;
    
    return enResult;
}

/**
 * @brief  Atimer3 启动运行(模式23)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_Run(void)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.CTEN = TRUE;
    
    return enResult;
}

/**
 * @brief  Atimer3 停止运行(模式23)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_Stop(void)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 * @brief  Atimer3 重载值设置(模式23)
 * @param [in] u16Data:    16bits重载值
 * @param [in] bArrBufEn:   ARR重载缓存使能(TRUE)/禁止(FALSE)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn)
{
    en_result_t enResult = Ok;
        
     HC_ATIM3MODE23->ARR_f.ARR       = u16Data;
     HC_ATIM3MODE23->M23CR_f.BUFPEN  = bArrBufEn;

    return enResult; 
}

/**
 * @brief  Atimer3 16位计数器初值设置设定(模式23)
 * @param [in] u16Data:    CNT 16位初值
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->CNT_f.CNT = u16Data;

    return enResult; 
}

/**
 * @brief  Atimer3 16位计数值获取(模式23)
 *
 * @retval uint16_t: 16bits计数值
 */
uint16_t Tim3_M23_Cnt16Get(void)
{
    uint32_t    u32CntData = 0u;
        
    u32CntData = HC_ATIM3MODE23->CNT_f.CNT;
    
    return (uint16_t)u32CntData; 
}

/**
 * @brief  Atimer3 比较捕获寄存器CCRxA/CCRxB设置(模式23)
 * @param [in] enCCRSel:  CCRxA/CCRxB设定 @ref en_tim3_m23_ccrx_t
 * @param [in] u16Data:   CCRxA/CCRxB 16位初始值
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_CCR_Set(en_tim3_m23_ccrx_t enCCRSel, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    uint32_t u32BaseAddress;
    
    u32BaseAddress = (uint32_t)(&HC_ATIM3MODE23->CCR0A) + (uint32_t)enCCRSel;
    
    REG_WRITE(*(volatile uint32_t *)u32BaseAddress, u16Data);
    
    return enResult;
}

/**
 * @brief  Atimer3 比较捕获寄存器CCRxA/CCRxB设置(模式23)
 * @param [in] enCCRSel:  CCRxA/CCRxB设定 @ref en_tim3_m23_ccrx_t
 *
 * @retval uint16_t: 16bitsCCRxA/CCRxB捕获值    
 */
uint16_t Tim3_M23_CCR_Get(en_tim3_m23_ccrx_t enCCRSel)
{
    uint32_t u32BaseAddress;
    
    u32BaseAddress = (uint32_t)(&HC_ATIM3MODE23->CCR0A) + (uint32_t)enCCRSel;
    
    return *(volatile uint16_t *)u32BaseAddress; 
}

/**
 * @brief  Atimer3 PWM互补输出模式下, GATE功能选择(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_gate_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_GateFuncSel(stc_tim3_m23_gate_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.CSG = pstcCfg->enGateFuncSel;
    HC_ATIM3MODE23->M23CR_f.CRG = pstcCfg->bGateRiseCap;
    HC_ATIM3MODE23->M23CR_f.CFG = pstcCfg->bGateFallCap;
    
    return enResult;    
}

/**
 * @brief  Atimer3 主从模式配置(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_master_slave_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_MasterSlave_Set(stc_tim3_m23_master_slave_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE23->MSCR_f.MSM = pstcCfg->enMasterSlaveSel;
    HC_ATIM3MODE23->MSCR_f.MMS = pstcCfg->enMasterSrc;
    HC_ATIM3MODE23->MSCR_f.SMS = pstcCfg->enSlaveModeSel;
    HC_ATIM3MODE23->MSCR_f.TS  = pstcCfg->enTsSel;
    
    return enResult;    
}

/**
 * @brief  Atimer3 CHxA/CHxB比较通道控制(模式23)(x=0,1,2)
 * @param [in] enTim3Chx:  Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_compare_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_PortOutput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_compare_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    switch (enTim3Chx)
    {
        case Tim3CH0:
            HC_ATIM3MODE23->CRCH0_f.CSA         = 0u;
            HC_ATIM3MODE23->FLTR_f.OCMA0FLTA0  = pstcCfg->enCHxACmpCtrl;
            HC_ATIM3MODE23->FLTR_f.CCPA0        = pstcCfg->enCHxAPolarity;
            HC_ATIM3MODE23->CRCH0_f.BUFEA       = pstcCfg->bCHxACmpBufEn;
            HC_ATIM3MODE23->M23CR_f.CIS         = pstcCfg->enCHxACmpIntSel;
    
            HC_ATIM3MODE23->CRCH0_f.CSB         = 0u;
            HC_ATIM3MODE23->FLTR_f.OCMB0FLTB0  = pstcCfg->enCHxBCmpCtrl;
            HC_ATIM3MODE23->FLTR_f.CCPB0        = pstcCfg->enCHxBPolarity;
            HC_ATIM3MODE23->CRCH0_f.BUFEB       = pstcCfg->bCHxBCmpBufEn;
            HC_ATIM3MODE23->CRCH0_f.CISB        = pstcCfg->enCHxBCmpIntSel;
          break;
        case Tim3CH1:
            HC_ATIM3MODE23->CRCH1_f.CSA         = 0u;
            HC_ATIM3MODE23->FLTR_f.OCMA1FLTA1  = pstcCfg->enCHxACmpCtrl;
            HC_ATIM3MODE23->FLTR_f.CCPA1        = pstcCfg->enCHxAPolarity;
            HC_ATIM3MODE23->CRCH1_f.BUFEA       = pstcCfg->bCHxACmpBufEn;
            HC_ATIM3MODE23->M23CR_f.CIS         = pstcCfg->enCHxACmpIntSel;
    
            HC_ATIM3MODE23->CRCH1_f.CSB         = 0u;
            HC_ATIM3MODE23->FLTR_f.OCMB1FLTB1  = pstcCfg->enCHxBCmpCtrl;
            HC_ATIM3MODE23->FLTR_f.CCPB1        = pstcCfg->enCHxBPolarity;
            HC_ATIM3MODE23->CRCH1_f.BUFEB       = pstcCfg->bCHxBCmpBufEn;
            HC_ATIM3MODE23->CRCH1_f.CISB        = pstcCfg->enCHxBCmpIntSel;
          break;
        case Tim3CH2:
            HC_ATIM3MODE23->CRCH2_f.CSA         = 0u;
            HC_ATIM3MODE23->FLTR_f.OCMA2FLTA2  = pstcCfg->enCHxACmpCtrl;
            HC_ATIM3MODE23->FLTR_f.CCPA2        = pstcCfg->enCHxAPolarity;
            HC_ATIM3MODE23->CRCH2_f.BUFEA       = pstcCfg->bCHxACmpBufEn;
            HC_ATIM3MODE23->M23CR_f.CIS         = pstcCfg->enCHxACmpIntSel;
    
            HC_ATIM3MODE23->CRCH2_f.CSB         = 0u;
            HC_ATIM3MODE23->FLTR_f.OCMB2FLTB2  = pstcCfg->enCHxBCmpCtrl;
            HC_ATIM3MODE23->FLTR_f.CCPB2        = pstcCfg->enCHxBPolarity;
            HC_ATIM3MODE23->CRCH2_f.BUFEB       = pstcCfg->bCHxBCmpBufEn;
            HC_ATIM3MODE23->CRCH2_f.CISB        = pstcCfg->enCHxBCmpIntSel;
          break;
        default:
            enResult = Error;
          break;
    }
    
    return enResult;    
}


/**
 * @brief  Atimer3 CH3A/CH3B比较通道配置(模式23)
 * @param [in] enTim3Chx:  Timer3 CH3通道(Tim3CH3A, Tim3CH3B) @ref en_tim3_ch3_t
 * @param [in] pstcCfg:    配置结构体指针 @ref stc_tim3_m23_ch3_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_Ch3_Cfg(en_tim3_ch3_t enTim3Chx, stc_tim3_m23_ch3_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    uint32_t u32BaseAddress;
    
    u32BaseAddress = (uint32_t)(&HC_ATIM3MODE23->CRCH3A) + (uint32_t)enTim3Chx;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAddress, ATIM3_CRCH3_INIT_MASK, (uint32_t)pstcCfg->bCH3CompValBuffEn |\
                                                                            ((uint32_t)pstcCfg->bCH3ComTrigDMAEn)<<ATIM3MODE23_CRCH3A_CD_Pos |\
                                                                            ((uint32_t)pstcCfg->enCH3ACmpIntSel)<<ATIM3MODE23_CRCH3A_CIS_Pos |\
                                                                            ((uint32_t)pstcCfg->bCH3CompEn)<<ATIM3MODE23_CRCH3A_C3AEN_Pos);
    return enResult;
}
/**
 * @brief  Atimer3 CHxA/CHxB输入控制(模式23)
 * @param [in] enTim3Chx:  Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_input_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_PortInput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;

    switch (enTim3Chx)
    {
        case Tim3CH0:
            HC_ATIM3MODE23->CRCH0_f.CSA           = 1u;
            HC_ATIM3MODE23->CRCH0_f.CFACRABKSA    = pstcCfg->enCHxACapSel;
            HC_ATIM3MODE23->FLTR_f.OCMA0FLTA0     = pstcCfg->enCHxAInFlt;
            HC_ATIM3MODE23->FLTR_f.CCPA0          = pstcCfg->enCHxAPolarity;
    
            HC_ATIM3MODE23->CRCH0_f.CSB           = 1u;
            HC_ATIM3MODE23->CRCH0_f.CFBCRBBKSB    = pstcCfg->enCHxBCapSel;
            HC_ATIM3MODE23->FLTR_f.OCMB0FLTB0     = pstcCfg->enCHxBInFlt;
            HC_ATIM3MODE23->FLTR_f.CCPB0          = pstcCfg->enCHxBPolarity;
          break;
        case Tim3CH1:
            HC_ATIM3MODE23->CRCH1_f.CSA           = 1u;
            HC_ATIM3MODE23->CRCH1_f.CFACRABKSA    = pstcCfg->enCHxACapSel;
            HC_ATIM3MODE23->FLTR_f.OCMA1FLTA1     = pstcCfg->enCHxAInFlt;
            HC_ATIM3MODE23->FLTR_f.CCPA1          = pstcCfg->enCHxAPolarity;
    
            HC_ATIM3MODE23->CRCH1_f.CSB           = 1u;
            HC_ATIM3MODE23->CRCH1_f.CFBCRBBKSB    = pstcCfg->enCHxBCapSel;
            HC_ATIM3MODE23->FLTR_f.OCMB1FLTB1     = pstcCfg->enCHxBInFlt;
            HC_ATIM3MODE23->FLTR_f.CCPB1          = pstcCfg->enCHxBPolarity;
          break;
        case Tim3CH2:
            HC_ATIM3MODE23->CRCH2_f.CSA           = 1u;
            HC_ATIM3MODE23->CRCH2_f.CFACRABKSA    = pstcCfg->enCHxACapSel;
            HC_ATIM3MODE23->FLTR_f.OCMA2FLTA2     = pstcCfg->enCHxAInFlt;
            HC_ATIM3MODE23->FLTR_f.CCPA2          = pstcCfg->enCHxAPolarity;
    
            HC_ATIM3MODE23->CRCH2_f.CSB           = 1u;
            HC_ATIM3MODE23->CRCH2_f.CFBCRBBKSB    = pstcCfg->enCHxBCapSel;
            HC_ATIM3MODE23->FLTR_f.OCMB2FLTB2     = pstcCfg->enCHxBInFlt;
            HC_ATIM3MODE23->FLTR_f.CCPB2          = pstcCfg->enCHxBPolarity;
          break;
        default:
            enResult = Error;
          break;
    }
    return enResult;    
}

/**
 * @brief  Atimer3 ERT输入控制(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_etr_input_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_ETRInput_Cfg(stc_tim3_m23_etr_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->FLTR_f.ETP    = pstcCfg->enETRPolarity;
    HC_ATIM3MODE23->FLTR_f.FLTET  = pstcCfg->enETRFlt;
    
    return enResult;    
}

/**
 * @brief  Atimer3 刹车BK控制(模式23)
 * @param [in] pstcBkCfg:    初始化配置结构体指针 @ref stc_tim3_m23_bk_input_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_BrakeInput_Cfg(stc_tim3_m23_bk_input_cfg_t* pstcBkCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->DTR_f.BKE             = pstcBkCfg->bEnBrake;
    HC_ATIM3MODE23->DTR_f.VCE             = pstcBkCfg->bEnVCBrake;
    HC_ATIM3MODE23->DTR_f.SAFEEN          = pstcBkCfg->bEnSafetyBk;
    HC_ATIM3MODE23->DTR_f.BKSEL           = pstcBkCfg->bEnBKSync;
    HC_ATIM3MODE23->CRCH0_f.CFACRABKSA    = pstcBkCfg->enBkCH0AStat;
    HC_ATIM3MODE23->CRCH0_f.CFBCRBBKSB    = pstcBkCfg->enBkCH0BStat;
    HC_ATIM3MODE23->CRCH1_f.CFACRABKSA    = pstcBkCfg->enBkCH1AStat;
    HC_ATIM3MODE23->CRCH1_f.CFBCRBBKSB    = pstcBkCfg->enBkCH1BStat;
    HC_ATIM3MODE23->CRCH2_f.CFACRABKSA    = pstcBkCfg->enBkCH2AStat;
    HC_ATIM3MODE23->CRCH2_f.CFBCRBBKSB    = pstcBkCfg->enBkCH2BStat;
    HC_ATIM3MODE23->FLTR_f.BKP            = pstcBkCfg->enBrakePolarity;
    HC_ATIM3MODE23->FLTR_f.FLTBK          = pstcBkCfg->enBrakeFlt;
    
    return enResult;    
}

/**
 * @brief  Atimer3 触发ADC控制(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_adc_trig_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_TrigADC_Cfg(stc_tim3_m23_adc_trig_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->ADTR_f.ADTE   = pstcCfg->bEnTrigADC;
    HC_ATIM3MODE23->ADTR_f.UEVE   = pstcCfg->bEnUevTrigADC;
    HC_ATIM3MODE23->ADTR_f.CMA0E  = pstcCfg->bEnCH0ACmpTrigADC;
    HC_ATIM3MODE23->ADTR_f.CMB0E  = pstcCfg->bEnCH0BCmpTrigADC;
    HC_ATIM3MODE23->ADTR_f.CMA1E  = pstcCfg->bEnCH1ACmpTrigADC;
    HC_ATIM3MODE23->ADTR_f.CMB1E  = pstcCfg->bEnCH1BCmpTrigADC;
    HC_ATIM3MODE23->ADTR_f.CMA2E  = pstcCfg->bEnCH2ACmpTrigADC;
    HC_ATIM3MODE23->ADTR_f.CMB2E  = pstcCfg->bEnCH2BCmpTrigADC;
    return enResult;    
}

/**
 * @brief  Atimer3 死区功能(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_dt_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_DT_Cfg(stc_tim3_m23_dt_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->DTR_f.DTEN = pstcCfg->bEnDeadTime;
    HC_ATIM3MODE23->DTR_f.DTR  = pstcCfg->u8DeadTimeValue;
    
    return enResult;    
}

/**
 * @brief  Atimer3 重复周期设置(模式23)
 * @param [in] u8ValidPeriod:    8bit重复周期值
 * @param  [in] bOVMaskEn:      屏蔽上溢重复计数使能
 * @param  [in] bUDMaskEn:      屏蔽下溢重复计数使能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_SetValidPeriod(uint8_t u8ValidPeriod, boolean_t bOVMaskEn, boolean_t bUDMaskEn)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->RCR_f.RCR = u8ValidPeriod;
    HC_ATIM3MODE23->RCR_f.OV = bOVMaskEn;
    HC_ATIM3MODE23->RCR_f.UD = bUDMaskEn;
    
    return enResult;    
}

/**
 * @brief  Atimer3 OCREF清除功能(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_OCREF_Clr_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_OCRefClr(stc_tim3_m23_OCREF_Clr_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.OCCS = pstcCfg->enOCRefClrSrcSel;
    HC_ATIM3MODE23->M23CR_f.OCCE = pstcCfg->bVCClrEn;
    
    return enResult;    
}

/**
 * @brief  Atimer3 使能DMA传输(模式23)
 * @param [in] pstcCfg:    初始化配置结构体指针 @ref stc_tim3_m23_trig_dma_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnDMA(stc_tim3_m23_trig_dma_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.UDE  = pstcCfg->bUevTrigDMA;
    HC_ATIM3MODE23->M23CR_f.TDE  = pstcCfg->bTITrigDMA;
    HC_ATIM3MODE23->CRCH0_f.CDEA = pstcCfg->bCmpA0TrigDMA;
    HC_ATIM3MODE23->CRCH0_f.CDEB = pstcCfg->bCmpB0TrigDMA;
    HC_ATIM3MODE23->CRCH1_f.CDEA = pstcCfg->bCmpA1TrigDMA;
    HC_ATIM3MODE23->CRCH1_f.CDEB = pstcCfg->bCmpB1TrigDMA;
    HC_ATIM3MODE23->CRCH2_f.CDEA = pstcCfg->bCmpA2TrigDMA;
    HC_ATIM3MODE23->CRCH2_f.CDEB = pstcCfg->bCmpB2TrigDMA;
    HC_ATIM3MODE23->MSCR_f.CCDS  = pstcCfg->enCmpUevTrigDMA;
    
    return enResult;    
}

/**
 * @brief  Atimer3 捕获比较A软件触发(模式23)
 * @param [in] enTim3Chx:  Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnSwTrigCapCmpA(en_tim3_channel_t enTim3Chx)
{
    en_result_t enResult = Ok;
    if(Tim3CH0 == enTim3Chx)
    {
        HC_ATIM3MODE23->CRCH0_f.CCGA = TRUE;
    }
    else if(Tim3CH1 == enTim3Chx)
    {
        HC_ATIM3MODE23->CRCH1_f.CCGA = TRUE;
    }
    else if(Tim3CH2 == enTim3Chx)
    {
        HC_ATIM3MODE23->CRCH2_f.CCGA = TRUE;
    }
    else
    {
        enResult = Error;
    }
    return enResult;    
}

/**
 * @brief  Atimer3 捕获比较B软件触发(模式23)
 * @param [in] enTim3Chx:  Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnSwTrigCapCmpB(en_tim3_channel_t enTim3Chx)
{
    en_result_t enResult = Ok;
    if(Tim3CH0 == enTim3Chx)
    {
        HC_ATIM3MODE23->CRCH0_f.CCGB = TRUE;
    }
    else if(Tim3CH1 == enTim3Chx)
    {
        HC_ATIM3MODE23->CRCH1_f.CCGB = TRUE;
    }
    else if(Tim3CH2 == enTim3Chx)
    {
        HC_ATIM3MODE23->CRCH2_f.CCGB = TRUE;
    }
    else
    {
        enResult = Error;
    }
    return enResult;    
}

/**
 * @brief  Atimer3 软件更新使能(模式23)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnSwUev(void)
{
    en_result_t enResult = Ok;
    
    HC_ATIM3MODE23->M23CR_f.UG = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer3 软件触发使能(模式23)
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnSwTrig(void)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.TG = TRUE;
    
    return enResult;    
}

/**
 * @brief  Atimer3 软件刹车使能(模式23)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_EnSwBk(void)
{
    en_result_t enResult = Ok;
        
    HC_ATIM3MODE23->M23CR_f.BG = TRUE;
    
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
