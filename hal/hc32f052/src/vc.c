/**
 *******************************************************************************
 * @file  vc.c
 * @brief This file provides firmware functions to manage the VC.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-15       MADS             First version
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
#include "vc.h"


/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_VC VC模块驱动库
 * @brief VC Driver Library VC模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup VC_Global_Functions VC全局函数定义
 * @{
 */

/**
 * @brief  配置VC中断触发方式
 * 
 * @param [in]  Channelx:  Vc模块号:VcChannel0 VcChannel1
 * @param [in]  ItType: 中断触发方式(VcIrqNone, VcIrqRise, VcIrqFall, VcIrqHigh)
 * 
 * @retval None
 */
void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress = (uint32_t)(&HC_VC0->CR1) +  (uint32_t)Channelx;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, \
                VC_CR1_FALLING | VC_CR1_RISING | VC_CR1_LEVEL, \
                (uint32_t)ItType << VC_CR1_FALLING_Pos);
}

/**
 * @brief  VC 中断使能与禁止
 *
 * @param [in]  Channelx:  Vc模块号:VcChannel0 VcChannel1
 * @param [in]  NewStatus : TRUE 或 FALSE
 *
 * @retval None
 */
void  Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress = (uint32_t)(&HC_VC0->CR1) +  (uint32_t)Channelx;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, VC_CR1_IE, (uint32_t)NewStatus << VC_CR1_IE_Pos);
}

/**
 * @brief  VC 比较结果获取，包含中断标志位和滤波结果
 *
 * @param [in]  Channelx:  Vc模块号:VcChannel0 VcChannel1
 * @param [in]  Result : 所要读取的结果 (Vc_Intf, Vc_Filter)
 *
 * @retval boolean_t: TRUE 或  FALSE
 */
boolean_t Vc_GetItStatus(en_vc_channel_t Channelx, en_vc_ifr_t Result)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress = (uint32_t)(&HC_VC0->SR) +  (uint32_t)Channelx;
    
    return REG_READBITS(*(volatile uint32_t *)u32BaseAdress, 1u << ((uint32_t)Result)) ? TRUE : FALSE;
}

/**
 * @brief  VC 清除中断标志位
 *
 * @param [in] Channelx:  Vc模块号:VcChannel0 VcChannel1
 *
 * @retval None
 */
void Vc_ClearItStatus(en_vc_channel_t Channelx)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress = (uint32_t)(&HC_VC0->SR) +  (uint32_t)Channelx;
    
    REG_CLEARBITS(*(volatile uint32_t *)u32BaseAdress, VC_SR_INTF);
}

/**
 * @brief  VC 配置参考电压相关的内容(VC_CR0中 VC_CR0_REF, VC_CR0_DIVEN VC_CR0_DIV)
 *
 * @param [in]  Channelx:  Vc模块号:VcChannel0 VcChannel1
 * @param [in]  pstcDacCfg : 参考电压配置结构体
 *
 * @retval en_result_t: Ok 或 ErrorInvalidParameter
 */
en_result_t Vc_DacInit(en_vc_channel_t Channelx, stc_vc_dac_cfg_t *pstcDacCfg)
{
    uint32_t u32BaseAdress;
        
    if (NULL == pstcDacCfg)
    {
        return ErrorInvalidParameter;
    }
    
    u32BaseAdress = (uint32_t)(&HC_VC0->CR0) +  (uint32_t)Channelx;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, VC_CR0_DIVEN | VC_CR0_REF, \
                         ((uint32_t)pstcDacCfg->bDivEn) << VC_CR0_DIVEN_Pos | \
                          ((uint32_t)pstcDacCfg->enDivVref) << VC_CR0_REF_Pos );

    if (pstcDacCfg->u8DivVal < 0x40u)
    {
        REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, VC_CR0_DIV, ((uint32_t)pstcDacCfg->u8DivVal));
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  VC 输出控制
 *
 * @param [in]  enChannel:  Vc模块号:VcChannel0 VcChannel1
 * @param [in]  pstcOutCfg: 输出配置结构体 @ref stc_vc_output_cfg_t
 *
 * @retval None
 */
void Vc_Output_Cfg(en_vc_channel_t enChannel, stc_vc_output_cfg_t *pstcOutCfg)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress = (uint32_t)(&HC_VC0->CR2) +  (uint32_t)enChannel;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, 0x7Fu, \
                                                    (uint32_t)pstcOutCfg->enVcOutP |\
                                                    ((uint32_t)pstcOutCfg->bAtim0En) << VC_CR2_ATIM0CLR_Pos |\
                                                    ((uint32_t)pstcOutCfg->bAtim1En) << VC_CR2_ATIM1CLR_Pos |\
                                                    ((uint32_t)pstcOutCfg->bAtim2En) << VC_CR2_ATIM2CLR_Pos |\
                                                    ((uint32_t)pstcOutCfg->bAtim3En) << VC_CR2_ATIM3CLR_Pos |\
                                                    ((uint32_t)pstcOutCfg->bAtimBkEn) << VC_CR2_ATIMBK_Pos |\
                                                    ((uint32_t)pstcOutCfg->bVcWindowEn) << VC_CR2_WINDOW_Pos);
}

/**
 * @brief  VC通道初始化
 *
 * @param [in]  pstcChannelCfg : VC初始化配置结构体 @ref stc_vc_channel_cfg_t
 *
 * @retval None
 */
void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg)
{
    uint32_t u32BaseCR0, u32BaseCR1;
  
    u32BaseCR0 = (uint32_t)(&HC_VC0->CR0) + (uint32_t)pstcChannelCfg->enVcChannel;
    u32BaseCR1 = (uint32_t)(&HC_VC0->CR1) + (uint32_t)pstcChannelCfg->enVcChannel;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseCR0, VC_CR0_BIAS | VC_CR0_HYS, \
                                                ((uint32_t)pstcChannelCfg->enVcCmpDly) << VC_CR0_HYS_Pos |\
                                                  ((uint32_t)pstcChannelCfg->enVcBiasCurrent) << VC_CR0_BIAS_Pos);
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseCR1, VC_CR1_PSEL | VC_CR1_NSEL | VC_CR1_FLTEN | VC_CR1_FLTTIME|VC_CR1_FLTCLK, \
                                                ((uint32_t)pstcChannelCfg->enVcInPin_P)    |\
                                                ((uint32_t)pstcChannelCfg->enVcInPin_N) << VC_CR1_NSEL_Pos |\
                                                ((uint32_t)pstcChannelCfg->bFlten) << VC_CR1_FLTEN_Pos |\
                                                ((uint32_t)pstcChannelCfg->enVcFilterTime) << VC_CR1_FLTTIME_Pos|\
                                                ((uint32_t)pstcChannelCfg->enVcFilterSrcClk) << VC_CR1_FLTCLK_Pos);
}

/**
 * @brief  VC 通道使能/禁止
 *
 * @param [in]  enChannel:  Vc模块号:VcChannel0 VcChannel1
 * @param [in]  NewStatus : TRUE FALSE 
 *
 * @retval None
 */
void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress = (uint32_t)(&HC_VC0->CR1) +  (uint32_t)enChannel;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, VC_CR1_EN, ((uint32_t)NewStatus) << VC_CR1_EN_Pos);
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

