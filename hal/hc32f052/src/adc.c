/**
 *******************************************************************************
 * @file  adc.c
 * @brief This file provides firmware functions to manage the ADC.
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
#include "adc.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_ADC ADC模块驱动库
 * @brief ADC Driver Library ADC模块驱动库
 * @{
 */


/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Local_Macros ADC局部宏定义
 * @{
 */
/**
 * @defgroup ADC_TimeoutValue_definition ADC 超时定义
 * @{
 */
#define ADC_RDY_TIMEOUT            (0x10000U)/*!< ADC使能后续32个ADC时钟周期才能启动转换，PCLK时钟最大分频为8 */
/**
 * @}
 */

/**
 * @}
 */

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


/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup ADC_Global_Functions ADC全局函数定义
 * @{
 */

/**
 * @brief  获取ADC中断状态.
 * @param  [in] enAdcIrq: ADC中断类型 @ref en_adc_irq_type_t
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    if(0u != (HC_ADC->IFR & ((uint32_t)enAdcIrq)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  清除ADC中断标志.
 * @param  [in] enAdcIrq: ADC中断类型 @ref en_adc_irq_type_t
 * @retval None.
 */
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    HC_ADC->ICR &= ~(uint32_t)enAdcIrq;
}

/**
 * @brief  ADC中断使能.
 * @param  [in] enAdcIrq: ADC中断类型 @ref en_adc_irq_type_t
 * @retval None.
 */
void Adc_EnableIrq(en_adc_irq_type_t enAdcIrq)
{
    REG_SETBITS(HC_ADC->IER, (uint32_t)enAdcIrq);
}


/**
 * @brief  ADC中断禁止.
 * @param  [in] enAdcIrq: ADC中断类型 @ref en_adc_irq_type_t
 * @retval None.
 */
void Adc_DisableIrq(en_adc_irq_type_t enAdcIrq)
{
    REG_CLEARBITS(HC_ADC->IER, (uint32_t)enAdcIrq);
}

/**
 * @brief  ADC初始化.
 * @param  [in] pstcAdcCfg: ADC配置指针 @ref stc_adc_cfg_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg)
{
    uint32_t u32Timeout = 0U;

    if (NULL == pstcAdcCfg)
    {
        return ErrorInvalidParameter;
    }

    HC_ADC->CR0 = ADC_CR0_EN;    /* ADC 使能并清除配置 */
    HC_ADC->CR1 = 0U;
    delay10us(6u);
    while((HC_ADC->IFR & ADC_IFR_RDY) == 0U)
    {
        u32Timeout ++;
        if(u32Timeout > ADC_RDY_TIMEOUT)
        {
            break;
        }
    }

    HC_ADC->CR0 |= (uint32_t)pstcAdcCfg->enAdcClkDiv       |
                    (uint32_t)pstcAdcCfg->enAdcRefVolSel    |
                    (uint32_t)pstcAdcCfg->enAdcOpBuf        |
                    (uint32_t)pstcAdcCfg->enAdcSampCycleSel;

    if(pstcAdcCfg->enAdcRefVolSel <= AdcMskRefVolSelInBgr2p5)
    {
        delay10us(2u);      /* ADC 选用内部1.5V或者内部2.5V需要等待20us */
    }

    HC_ADC->CR1 |= (uint32_t)pstcAdcCfg->enAdcMode  |
                   (uint32_t)pstcAdcCfg->enAdcAlign |
                   (uint32_t)pstcAdcCfg->enOvMode;

    return Ok;
}


/**
 * @brief  ADC单次转换或者顺序扫描转换外部中断触发源配置.
 * @param  [in] enAdcTrigSel: 触发源选择 @ref en_adc_trig_sel_t
 * @param  [in] enTrigDelay: 触发延时控制 @ref en_adc_trig_delay_t
 * @retval None.
 */
void Adc_SglSqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, en_adc_trig_delay_t enTrigDelay)
{
    if(AdcExtTrigDelay == enTrigDelay)
    {
        HC_ADC->EXTTRIG0 = ADC_EXTTRIG0_DELAY | (uint32_t)enAdcTrigSel;
    }
    else
    {
        HC_ADC->EXTTRIG0 = (uint32_t)enAdcTrigSel;
    }
}


/**
 * @brief  ADC插队扫描转换外部中断触发源配置.
 * @param  [in] enAdcTrigSel: 触发源选择 @ref en_adc_trig_sel_t
 * @param  [in] enTrigDelay: 触发延时控制 @ref en_adc_trig_delay_t
 * @retval None.
 */
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, en_adc_trig_delay_t enTrigDelay)
{
    if(AdcExtTrigDelay == enTrigDelay)
    {
        HC_ADC->EXTTRIG1 = ADC_EXTTRIG1_DELAY | (uint32_t)enAdcTrigSel;
    }
    else
    {
        HC_ADC->EXTTRIG1 = (uint32_t)enAdcTrigSel;
    }
}


/**
 * @brief  ADC单次转换开始
 * @retval None.
 */
void Adc_SGL_Start(void)
{
    uint32_t u32Timeout = 0U;

    HC_ADC->CR0 &= (~ADC_CR0_EN);
    HC_ADC->CR0 |= ADC_CR0_EN;
    delay10us(6u);
    while((HC_ADC->IFR & ADC_IFR_RDY) == 0U)
    {
        u32Timeout ++;
        if(u32Timeout > ADC_RDY_TIMEOUT)
        {
            break;
        }
    }
    
    HC_ADC->SGLSTART = 1u;
}


/**
 * @brief  ADC 单次转换停止
 * @retval None.
 */
void Adc_SGL_Stop(void)
{
    HC_ADC->SGLSTART = 0u;
}


/**
 * @brief  ADC 顺序扫描转换开始
 * @retval None.
 */
void Adc_SQR_Start(void)
{
    uint32_t u32Timeout = 0U;

    HC_ADC->CR0 &= (~ADC_CR0_EN);
    HC_ADC->CR0 |= ADC_CR0_EN;
    delay10us(6u);
    while((HC_ADC->IFR & ADC_IFR_RDY) == 0U)
    {
        u32Timeout ++;
        if(u32Timeout > ADC_RDY_TIMEOUT)
        {
            break;
        }
    }

    HC_ADC->SQRSTART = 1u;
}


/**
 * @brief  ADC 顺序扫描转换停止
 * @retval None.
 */
void Adc_SQR_Stop(void)
{
    HC_ADC->SQRSTART = 0u;
}


/**
 * @brief  ADC 插队扫描转换开始
 * @retval None.
 */
void Adc_JQR_Start(void)
{
    uint32_t u32Timeout = 0U;

    HC_ADC->CR0 &= (~ADC_CR0_EN);
    HC_ADC->CR0 |= ADC_CR0_EN;
    delay10us(6u);
    while((HC_ADC->IFR & ADC_IFR_RDY) == 0U)
    {
        u32Timeout ++;
        if(u32Timeout > ADC_RDY_TIMEOUT)
        {
            break;
        }
    }

    HC_ADC->JQRSTART = 1u;
}


/**
 * @brief  ADC 插队扫描转换停止
 * @retval None.
 */
void Adc_JQR_Stop(void)
{
    HC_ADC->JQRSTART = 0u;
}


/**
 * @brief  ADC 使能
 * @retval None.
 */
void Adc_Enable(void)
{
    uint32_t u32Timeout = 0U;

    HC_ADC->CR0 |= ADC_CR0_EN;
    delay10us(6u);
    while((HC_ADC->IFR & ADC_IFR_RDY) == 0U)
    {
        u32Timeout ++;
        if(u32Timeout > ADC_RDY_TIMEOUT)
        {
            break;
        }
    }
}


/**
 * @brief  ADC 除能
 * @retval None.
 */
void Adc_Disable(void)
{
    HC_ADC->CR0 &= (~ADC_CR0_EN);
}


/**
 * @brief  配置顺序扫描转换模式.
 * @param  [in] pstcAdcSqrCfg: 顺序扫描转换模式配置指针 @ref stc_adc_sqr_cfg_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg)
{
    uint32_t u32RegValue;

    if ((NULL == pstcAdcSqrCfg) || (pstcAdcSqrCfg->u8SqrCnt > 16u))
    {
        return ErrorInvalidParameter;
    }

    u32RegValue = HC_ADC->CR1;
    u32RegValue &= (~ADC_CR1_RACCCLR); /* ADC转换结果累加寄存器（ADC_ResultAcc）清零 */
    u32RegValue &= (~ADC_CR1_RACCEN);
    u32RegValue |= ((uint32_t)pstcAdcSqrCfg->enResultAcc << ADC_CR1_RACCEN_Pos);
    HC_ADC->CR1 = u32RegValue;

    REG_MODIFY(HC_ADC->IER, ADC_IER_DEOC, (uint32_t)pstcAdcSqrCfg->bSqrDmaTrig << ADC_IER_DEOC_Pos);

    REG_MODIFY(HC_ADC->SQR2, ADC_SQR2_CNT, ((uint32_t)pstcAdcSqrCfg->u8SqrCnt - 1u) << ADC_SQR2_CNT_Pos);

    return Ok;
}


/**
 * @brief  配置插队扫描转换模式.
 * @param  [in] pstcAdcJqrCfg: 插队扫描转换模式配置指针 @ref stc_adc_jqr_cfg_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg)
{
    if ((NULL == pstcAdcJqrCfg) || (pstcAdcJqrCfg->u8JqrCnt > 4u))
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY(HC_ADC->IER, ADC_IER_DEOJ, (uint32_t)pstcAdcJqrCfg->bJqrDmaTrig << ADC_IER_DEOJ_Pos);

    REG_MODIFY(HC_ADC->JQR, ADC_JQR_CNT, ((uint32_t)pstcAdcJqrCfg->u8JqrCnt - 1u) << ADC_JQR_CNT_Pos);

    return Ok;
}


/**
 * @brief  配置单次转换通道.
 * @param  [in] enstcAdcSampCh: 插队扫描转换模式配置指针 @ref en_adc_samp_ch_sel_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 */
en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    REG_MODIFY(HC_ADC->CR0, ADC_CR0_SGLMUX, (uint32_t)enstcAdcSampCh << ADC_CR0_SGLMUX_Pos);

    return Ok;
}


/**
 * @brief  配置顺序扫描转换通道.
 * @param  [in] enstcAdcSqrChMux: 顺序扫描转换通道顺序 @ref en_adc_sqr_chmux_t
 * @param  [in] enstcAdcSampCh: 转换通道 @ref en_adc_samp_ch_sel_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    uint32_t u32val;
    
    if(enstcAdcSqrChMux <= AdcSQRCH5MUX)
    {
        u32val = ((uint32_t)enstcAdcSqrChMux) * 5u;
        REG_MODIFY(HC_ADC->SQR0, 0x0000001Fu << u32val, ((uint32_t)enstcAdcSampCh) << u32val);
    }
    else if(enstcAdcSqrChMux <= AdcSQRCH11MUX)
    {
        u32val = ((uint32_t)enstcAdcSqrChMux - 6u) * 5u;
        REG_MODIFY(HC_ADC->SQR1, 0x0000001Fu << u32val, ((uint32_t)enstcAdcSampCh) << u32val);
    }
    else if(enstcAdcSqrChMux <= AdcSQRCH15MUX)
    {
        u32val = ((uint32_t)enstcAdcSqrChMux - 12u) * 5u;
        REG_MODIFY(HC_ADC->SQR2, 0x0000001Fu << u32val, ((uint32_t)enstcAdcSampCh) << u32val);
    }
    else
    {
        enResult = ErrorInvalidParameter;
    }
    
    return enResult;
}


/**
 * @brief  配置插队扫描转换通道.
 * @param  [in] enstcAdcJqrChMux: 插队扫描转换通道顺序 @ref en_adc_jqr_chmux_t
 * @param  [in] enstcAdcSampCh: 转换通道 @ref en_adc_samp_ch_sel_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    uint32_t u32val;
    
    u32val = ((uint32_t)enstcAdcJqrChMux) * 5u;
    REG_MODIFY(HC_ADC->JQR, 0x0000001Fu << u32val, ((uint32_t)enstcAdcSampCh) << u32val);
    
    return enResult;
}


/**
 * @brief  获取采样值(单次采样结果）.
 * @retval uint32_t: 采样值
 */
uint32_t Adc_GetSglResult(void)
{
    return HC_ADC->RESULT;
}


/**
 * @brief  获取顺序扫描采样值.
 * @param  [in] enstcAdcSqrChMux: 顺序扫描通道序号,仅限通道0~通道3 @ref en_adc_sqr_chmux_t
 * @retval uint32_t: 采样值
 */
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux)
{
    uint32_t BaseSqrResultAddress;
    
    if(enstcAdcSqrChMux <= AdcSQRCH3MUX)
    {
        BaseSqrResultAddress = (uint32_t)(&HC_ADC->SQRRESULT0) + ((uint32_t)enstcAdcSqrChMux<<2);
    }
    else
    {
        return 0u;
    }

    return *(volatile uint32_t *)BaseSqrResultAddress;
}


/**
 * @brief  获取插队扫描采样值.
 * @param  [in] enstcAdcJqrChMux: 插队扫描通道序号 @ref en_adc_jqr_chmux_t
 * @retval uint32_t: 采样值
 */
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux)
{
    uint32_t BaseJqrResultAddress;
      
    BaseJqrResultAddress = (uint32_t)(&HC_ADC->JQRRESULT0) + ((uint32_t)enstcAdcJqrChMux<<2);
    
    return *(volatile uint32_t *)BaseJqrResultAddress;
}


/**
 * @brief  获取累加采样值.
 * @retval uint32_t: 累加采样结果
 */
uint32_t Adc_GetAccResult(void)
{
    return HC_ADC->RESULTACC;

}


/**
 * @brief  清零累加采样值.
 * @retval None.
 */
void Adc_ClrAccResult(void)
{
    HC_ADC->CR1 &= (~ADC_CR1_RACCCLR);
}


/**
 * @brief  ADC比较使能(比较中断).
 * @param  [in] pstcAdcThrCfg: ADC比较配置 @ref stc_adc_threshold_cfg_t
 * @retval None.
 */
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg)
{
    uint32_t u32RegValue;

    HC_ADC->HT = pstcAdcThrCfg->u32AdcHighThd;
    HC_ADC->LT = pstcAdcThrCfg->u32AdcLowThd;

    u32RegValue = HC_ADC->CR1;
    u32RegValue &= (~(ADC_CR1_THCH | ADC_CR1_REGCMP | ADC_CR1_HTCMP | ADC_CR1_LTCMP));
    u32RegValue |= ((uint32_t)pstcAdcThrCfg->enSampChSel << ADC_CR1_THCH_Pos);
    u32RegValue |= ((uint32_t)pstcAdcThrCfg->bAdcRegCmp << ADC_CR1_REGCMP_Pos);
    u32RegValue |= ((uint32_t)pstcAdcThrCfg->bAdcHtCmp << ADC_CR1_HTCMP_Pos);
    u32RegValue |= ((uint32_t)pstcAdcThrCfg->bAdcLtCmp << ADC_CR1_LTCMP_Pos);
    HC_ADC->CR1 = u32RegValue;
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

