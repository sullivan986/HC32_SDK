/**
 *******************************************************************************
 * @file  driver.cpp
 * @brief HC32A052 DDL 驱动库 - 聚合实现 [自动生成, 勿手改]
 *
 * 本文件由 XHSC HC32A052 DDL 自动聚合生成, 请勿逐模块手工修改.
 * 重新生成: python3 tools/merge_driver.py            (会覆盖本文件的修改)
 *
 * 聚合来源: temp/ 下的厂商 DDL 包 (HC32A052_DLL_xxx)
 *   driver/{inc,src}   驱动模块
 *   mcu/common/        base_types.h / 器件头 / 中断框架
 *
 * 未纳入本文件的部分 (与板级/外部强相关, 按「机制/策略」分层):
 *   hal/hc32a052/config.h          板级配置「机制」: 类型 / 预设 / 校验
 *   hal/hc32a052/config.cpp        时钟初始化实现 (SystemInit)
 *   app/<proj>/inc/board_config.h  板级「策略」: 晶振频率 + 生效配置 + 板载引脚
 *                                  (由 config.h 自动包含, app 侧文件)
 *
 * 所有函数声明统一包裹在一层 extern "C" 内, 保持 C 链接以保证底层寄存器操作
 * 不受 C++ 名称修饰影响; 亦因此本头文件可被 C 与 C++ 同时包含.
 *
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "driver.h"

/* 厂商 C 代码惯用 `volatile 变量--` (超时计数), C++20 起被标记 deprecated.
 * 语义无误, 仅在生成本 TU 内屏蔽该告警, 不影响用户代码. */
#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wdeprecated-volatile"
#endif

/* ========================================================================== */
/*  ddl.c                                                                     */
/* ========================================================================== */


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DDL DDL公共函数库
 * @brief DDL Common Functions库
 * @{
 */

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Global variable definitions (declared in header file with 'extern')        */
/******************************************************************************/

/******************************************************************************/
/* Local type definitions ('typedef')                                         */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                      */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/
#ifndef __DEBUG
#define __DEBUG
//#define __CC_ARM
#endif

/**
 * @defgroup DDL_Global_Functions DDL全局函数定义
 * @{
 */

/**
 * @brief  log2 数学函数
 * @param  [in] u32Val: 32位无符号输入值
 * @retval uint32_t: 32位无符号结果
 */
uint32_t Log2(uint32_t u32Val)
{
    uint32_t u32V1 = 0u;

    if(0u == u32Val)
    {
        return 0u;
    }

    while(u32Val > 1u)
    {
        u32V1++;
        u32Val /=2u;
    }

    return u32V1;
}


/**
 * @brief  ddl memory 清零函数
 * @param  [in] pu8Address: 起始地址
 * @param  [in] u32Count: 清零长度，以字节为单位
 * @retval None
 */
void ddl_memclr(void *pu8Address, uint32_t u32Count)
{
#if 0
    uint8_t *pu8Addr = (uint8_t *)pu8Address;

    if(NULL == pu8Addr)
    {
        return;
    }

    while (u32Count--)
    {
        *pu8Addr++ = 0u;
    }
#else
    memset(pu8Address,0,u32Count);

#endif
}

/**
 * @brief   1ms 延时函数
 * @param   [in]  u32Cnt: 延时时长，单位1ms
 * @retval  None
 */
void delay1ms(uint32_t u32Cnt)
{
    uint32_t ValNow,CNT = 0u;
    uint32_t CntEnd= (u32Cnt*(SystemCoreClock/1000u));
    uint32_t StaVal = SysTick->VAL;

    while(1)
    {
        ValNow=SysTick->VAL;

        if(ValNow != StaVal)
        {
            if(ValNow<StaVal)
            {
                CNT += StaVal -ValNow;
            }
            else
            {
                CNT += SysTick->LOAD - ValNow+StaVal;
            }
            StaVal = ValNow;
            if(CNT >= CntEnd )
            {
                break;
            }
        }
    }
}

/**
 * @brief   100us 延时函数
 * @param   [in]  u32Cnt: 延时时长，单位100us
 * @retval  None
 */
void delay100us(uint32_t u32Cnt)
{
    uint32_t ValNow,CNT = 0u;
    uint32_t CntEnd = (u32Cnt*(SystemCoreClock/10000u));

    uint32_t StaVal = SysTick->VAL;
    while(1)
    {
        ValNow=SysTick->VAL;

        if(ValNow != StaVal)
        {
            if(ValNow<StaVal)
            {
                CNT += StaVal -ValNow;
            }
            else
            {
                CNT += SysTick->LOAD - ValNow+StaVal;
            }
            StaVal = ValNow;
            if(CNT >=CntEnd)
            {
                break;
            }
        }
    }
}

/**
 * @brief   10us 延时函数
 * @param   [in]  u32Cnt: 延时时长，单位10us
 * @retval  None
 */
void delay10us(uint32_t u32Cnt)
{
    uint32_t ValNow,CNT = 0u;
    uint32_t StaVal = SysTick->VAL;

    while(1)
    {
        ValNow=SysTick->VAL;

        if(ValNow != StaVal)
        {
            if(ValNow<StaVal)
            {
                CNT += StaVal -ValNow;
            }
            else
            {
                CNT += SysTick->LOAD - ValNow+StaVal;
            }
            StaVal = ValNow;
            if(CNT >=(u32Cnt*(SystemCoreClock/100000u)))
            {
                break;
            }
        }
    }
}

/**
 * @brief   设置bit位
 * @param   [in]  addr: 地址
 * @param   [in]  offset: 偏移位数
 * @param   [in]  bFlag: 清零或者置位
 * @retval  None
 */
void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag)
{
    if(TRUE == bFlag)
    {
        *((volatile uint32_t *)(addr)) |= ((1UL)<<(offset));
    }
    else
    {
        *((volatile uint32_t *)(addr)) &= (~(1UL<<(offset)));
    }


}


/**
 * @brief   获取bit位
 * @param   [in]  addr: 地址
 * @param   [in]  offset: 偏移位数
 * @retval  boolean_t
 */
boolean_t GetBit(uint32_t addr, uint32_t offset)
{
    return ((((*((volatile uint32_t *)(addr))) >> (offset)) & 1u) > 0u) ? TRUE : FALSE;
}

/* ========================================================================== */
/*  adc.c                                                                     */
/* ========================================================================== */


/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  atim012.c                                                                 */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  atimer3.c                                                                 */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  bgr.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

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

/* ========================================================================== */
/*  btim.c                                                                    */
/* ========================================================================== */



/******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_BTIM BTIM模块驱动库
 * @brief BTIM Driver Library BTIM模块驱动库
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
 * @defgroup BTIM_Global_Functions BTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器BTIMx的初始化配置
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] pstcInitCfg : 初始化BTIMx的结构体
 *              - pstcInitCfg->u32TaskMode:  单次/连续计数模式控制  @ref Btim_Count_Task_Mode
 *              - pstcInitCfg->u32WorkMode:  工作模式控制     @ref Btim_Work_Mode
 *              - pstcInitCfg->u32Prescaler: 预分频时钟选择   @ref Btim_Clock_devide
 *              - pstcInitCfg->u32ToggleEn:  TOG管脚输出使能控制  @ref Btim_Toggle_ourput_control
 *              - pstcInitCfg->u32TriggerSource: 触发源选择  @ref Btim_Trigger_Source_Selection
 *              - pstcInitCfg->u32ExInputPolarity: 外部管脚输入的ETR信号极性选择 @ref  Btim_ETR_Input_Polarity
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
*/
en_result_t Btim_Init(BTIM_TypeDef* BTIMx, stc_btim_init_t* pstcInitCfg)
{
    if (NULL == pstcInitCfg)
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY(BTIMx->CR,
                           BTIM_CR_OST\
                            | BTIM_CR_MD\
                            | BTIM_CR_PRS\
                            | BTIM_CR_TOGEN\
                            | BTIM_CR_TRS\
                            | BTIM_CR_ETP\
                            , \
                            pstcInitCfg->u32TaskMode\
                            | pstcInitCfg->u32WorkMode\
                            | pstcInitCfg->u32Prescaler\
                            | pstcInitCfg->u32ToggleEn\
                            | pstcInitCfg->u32TriggerSource\
                            | pstcInitCfg->u32ExInputPolarity);

    REG_MODIFY(BTIMx->ARR, BTIM_ARR_ARR, (uint16_t)pstcInitCfg->u32AutoReloadVal);

    return Ok;
}

/**
 * @brief  设定BTIMx计数器计数值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u16CntValue  16bit 计数值
 *
 * @retval None
 */
void Btim_SetCounter(BTIM_TypeDef* BTIMx, uint16_t u16CntValue)
{
    REG_WRITE(BTIMx->CNT, (uint32_t)u16CntValue);
}

/**
 * @brief  获取BTIMx计数器计数值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t: BTIMx计数器计数值
 */
uint32_t Btim_GetCounter(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CNT, BTIM_CNT_CNT));
}

/**
 * @brief  设定BTIMx 重载寄存器的值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u16AutoReload: 重载值
 *
 * @retval None
 */
void Btim_SetAutoReload(BTIM_TypeDef* BTIMx, uint16_t u16AutoReload)
{
    REG_WRITE(BTIMx->ARR, (uint32_t)u16AutoReload);
}

/**
 * @brief  获取BTIMx 重载寄存器的值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t: BTIMx重载寄存器的值
 */
uint32_t Btim_GetAutoReload(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->ARR, BTIM_ARR_ARR));
}

/**
 * @brief  开启定时器BTIMx模块
 *
 * @param  [in] BTIMx: BTIM结构体变量
 *
 * @retval None
 */
 void Btim_Enable(BTIM_TypeDef *BTIMx)
{
    REG_SETBITS(BTIMx->CR, BTIM_CR_CEN);
}

/**
 * @brief  禁止定时器BTIMx模块
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval NULL
 */
 void Btim_Disable(BTIM_TypeDef *BTIMx)
{
    REG_CLEARBITS(BTIMx->CR, BTIM_CR_CEN);
}

/**
 * @brief  检查定时器BTIMx模块是否已开启
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval  FALSE:未开启;  TRUE:已开启
 */
 boolean_t Btim_IsEnable(BTIM_TypeDef *BTIMx)
{
    return REG_READBITS(BTIMx->CR, BTIM_CR_CEN) ? TRUE : FALSE;
}

/**
 * @brief  设定定时器BTIMx 工作模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32WorkMode: 选择BTIM工作模式  @ref Btim_Work_Mode
 *
 * @retval None
 */
void Btim_SetWorkMode(BTIM_TypeDef* BTIMx, uint32_t u32WorkMode)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_MD, u32WorkMode);
}

/**
 * @brief  获取定时器BTIMx 工作模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t:BTIM工作模式  @ref Btim_Work_Mode
 *
 */
 uint32_t Btim_GetWorkMode(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_MD));
}



/**
 * @brief  定时器BTIMx TOG输出使能，TOGP和TOGN输出相位相反的信号
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval None
 */
 void Btim_EnableToggle(BTIM_TypeDef *BTIMx)
{
    REG_SETBITS(BTIMx->CR, BTIM_CR_TOGEN);
}

/**
 * @brief  定时器BTIMx TOG输出禁止，TOGP和TOGN同时输出0
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval None
 */
 void Btim_DisableToggle(BTIM_TypeDef *BTIMx)
{
    REG_CLEARBITS(BTIMx->CR, BTIM_CR_TOGEN);
}

/**
 * @brief  检查定时器BTIMx模块 TOG输出 是否已开启
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval boolean_t:
 *           - FALSE: 未开启
 *           - TRUE: 已开启
 */
 boolean_t Btim_IsEnableToggle(BTIM_TypeDef *BTIMx)
{
    return REG_READBITS(BTIMx->CR, BTIM_CR_TOGEN) ? TRUE : FALSE;
}


/**
 * @brief  定时器BTIMx模块 计数时钟预除频
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32CounterClkDiv: 计数时钟预分频选择   @ref Btim_Clock_devide
 *
 * @retval None
 */
void Btim_SetCounterClkDiv(BTIM_TypeDef* BTIMx, uint32_t u32CounterClkDiv)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_PRS, u32CounterClkDiv);
}

/**
 * @brief  获取定时器BTIMx 时钟，此时钟是定时器模块工作时钟，非计数时钟源
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t:计数时钟预分频   @ref Btim_Clock_devide
 */
uint32_t Btim_GetCounterClkDiv(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_PRS));
}


/**
 * @brief  设定BTIMx 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32Mode: 计数模式  @ref Btim_Count_Task_Mode
 *
 * @retval None
 */
void Btim_SetOneShotMode(BTIM_TypeDef* BTIMx, uint32_t u32Mode)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_OST, u32Mode);
}

/**
 * @brief  获取BTIMx 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t: BTIMx 计数模式  @ref Btim_Count_Task_Mode
 */
uint32_t Btim_GetOneShotMode(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_OST));
}



/**
 * @brief  设定定时器BTIMx 触发源
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32TriggerSource: 选择BTIM触发源  @ref Btim_Trigger_Source_Selection
 *
 * @retval None
 */
void Btim_SetTriggerSource(BTIM_TypeDef* BTIMx, uint32_t u32TriggerSource)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_TRS, u32TriggerSource);
}

/**
 * @brief  获取定时器BTIMx 触发源
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t:BTIM 触发源  @ref Btim_Trigger_Source_Selection
 */
uint32_t Btim_GetTriggerSource(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_TRS));
}


/**
 * @brief  设定定时器BTIMx 外部输入ETR极性设定
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32ExInputPolarity: 外部输入ETR极性 @ref Btim_ETR_Input_Polarity
 *
 * @retval None
 */

void Btim_SetExInputPolarity(BTIM_TypeDef* BTIMx, uint32_t u32ExInputPolarity)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_ETP, u32ExInputPolarity);
}

/**
 * @brief  获取定时器BTIMx 外部输入ETR极性设定
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t:外部输入ETR极性  @ref Btim_ETR_Input_Polarity
 */
uint32_t Btim_GetExInputPolarity(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_ETP));
}

/**
 * @brief  BTIMx 中断使能
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag  中断使能禁止定义 @ref Btim_Interrupt_Enable_Disable
 *
 * @retval None
 */
void Btim_EnableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_SETBITS(BTIMx->IER, u32IntClrFlag);
}

/**
 * @brief  BTIMx 中断禁止
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag  中断使能禁止定义 @ref Btim_Interrupt_Enable_Disable
 *
 * @retval None
 */
void Btim_DisableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS(BTIMx->IER, u32IntClrFlag);
}

/**
 * @brief  检查 BTIMx 查询中断 是否已使能
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag  中断使能禁止定义 @ref Btim_Interrupt_Enable_Disable
 *
 * @retval boolean_t:
 *           - FALSE: 未使能
 *           - TRUE: 已使能
 */
boolean_t Btim_IsEnableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    return REG_READBITS(BTIMx->IER, u32IntClrFlag) ? TRUE : FALSE;
}

/**
 * @brief  获取 BTIMx 中断标志
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntFlag    中断置起标志定义  @ref Btim_Interrupt_Flag
 *
 * @retval boolean_t:
 *           - FALSE: 未置起
 *           - TRUE: 已置起
 */
boolean_t Btim_IsActiveFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntFlag)
{
    return REG_READBITS(BTIMx->IFR, u32IntFlag) ? TRUE : FALSE;
}


/**
 * @brief  清除 BTIMx 中断 标志位
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag   中断清零标志定义 @ref Btim_Interrupt_Clear_Types
 *
 * @retval None
 */
void Btim_ClearFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS(BTIMx->ICR, u32IntClrFlag);
}


/**
 * @brief  获取 复合 BTIM 中断标志
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntFlag: BTIM0~BTIM5中断标志 @ref Btim_All_Interrupt_Flags
 *
 * @retval boolean_t:
 *           - FALSE: 未置起
 *           - TRUE: 已置起
 */
boolean_t Btim_AIFR_IsActiveFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntFlag)
{
    return REG_READBITS(BTIMx->AIFR, u32IntFlag) ? TRUE : FALSE;
}


/**
 * @brief  清除 复合 BTIM 中断标志位
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag: BTIM0~BTIM5中断清零标志 @ref Btim_All_Interrupt_Clear_Reg
 *
 * @retval None
 */
void Btim_AICR_ClearFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS(BTIMx->AICR, u32IntClrFlag);
}

/* ========================================================================== */
/*  can.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CAN CAN模块驱动库
 * @brief CAN Driver Library CAN模块驱动库
 * @{
 */


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CAN_Local_Macros CAN局部宏定义
 * @{
 */
/**
 * @defgroup CAN_Reset_definition CAN复位请求
 * @{
 */
#define CAN_RESET_ENABLE()                  do{HC_CAN->CFG_STAT_f.RESET = 1U;}while(0U)/*!< 请求局部复位 */
#define CAN_RESET_DISABLE()                 do{HC_CAN->CFG_STAT_f.RESET = 0U;\
                                            while(HC_CAN->CFG_STAT_f.RESET){}\
                                            }while(0U)/*!< 不请求局部复位 */
/**
 * @}
 */
/**
 * @defgroup ACF_SELMASK_definition 选择筛选器的屏蔽寄存器
 * @{
 */
#define CAN_ACF_ID_REG_SEL                  ((uint8_t)0x00U)/*!< ACF指向筛选器ID寄存器 */
#define CAN_ACF_MASK_REG_SEL                ((uint8_t)0x01U)/*!< ACF指向筛选器MASK寄存器 */
/**
 * @}
 */
/**
 * @defgroup CAN_FLAG_CLEAR_MASK CAN标志位清除屏蔽值
 * @{
 */
#define CAN_IE_CLEAR_MASK                   ((uint32_t)0xFF2A00FFU)/*!< CAN中断标志清除屏蔽值 */
/**
 * @}
 */

/**
 * @defgroup CAN_PARA_CHECK 参数合法性检查
 * @{
 */

/**
 * @brief Parameter validity check for CAN Mode @ref en_can_mode_t
 */
#define IS_CAN_MODE_VALID(CanMode)                                             \
(       (CanExternalLoopBackMode  == (CanMode)) ||                               \
        (CanInternalLoopBackMode  == (CanMode)) ||                               \
        (CanTxSignalPrimaryMode   == (CanMode)) ||                               \
        (CanTxSignalSecondaryMode == (CanMode)) ||                               \
        (CanListenOnlyMode        == (CanMode))                                  \
)

/**
 * @brief Parameter validity check for CAN Tx Cmd @ref en_can_tx_cmd_t
 */
#define IS_TX_CMD_VALID(TxCmd)                                                 \
(       (CanPTBTxCmd      == (TxCmd)) ||                                         \
        (CanPTBTxAbortCmd == (TxCmd)) ||                                         \
        (CanSTBTxOneCmd   == (TxCmd)) ||                                         \
        (CanSTBTxAllCmd   == (TxCmd)) ||                                         \
        (CanSTBTxAbortCmd == (TxCmd))                                            \
)

/**
 * @brief Parameter validity check for CAN status @ref en_can_status_t
 */
#define IS_CAN_STATUS_VALID(enCanStatus)                                       \
(       (CanRxActive == (enCanStatus)) ||                                        \
        (CanTxActive == (enCanStatus)) ||                                        \
        (CanBusoff   == (enCanStatus))                                           \
)

/**
 * @brief Parameter validity check for CAN Irq type @ref en_can_irq_type_t
 */
#define IS_CAN_IRQ_TYPE_VALID(enCanIrqType)                                    \
(       (CanRxIrqEn              == (enCanIrqType)) ||                           \
        (CanRxOverIrqEn          == (enCanIrqType)) ||                           \
        (CanRxBufFullIrqEn       == (enCanIrqType)) ||                           \
        (CanRxBufAlmostFullIrqEn == (enCanIrqType)) ||                           \
        (CanTxPrimaryIrqEn       == (enCanIrqType)) ||                           \
        (CanTxSecondaryIrqEn     == (enCanIrqType)) ||                           \
        (CanErrorIrqEn           == (enCanIrqType)) ||                           \
        (CanErrorPassiveIrqEn    == (enCanIrqType)) ||                           \
        (CanArbiLostIrqEn        == (enCanIrqType)) ||                           \
        (CanBusErrorIrqEn        == (enCanIrqType))                              \
)

/**
 * @brief Parameter validity check for CAN Irq flag type @ref en_can_irq_flag_type_t
 */
#define IS_CAN_IRQ_FLAG_VALID(enCanIrqFLg)                                     \
(       (CanTxBufFullIrqFlg        == (enCanIrqFLg)) ||                          \
        (CanRxIrqFlg               == (enCanIrqFLg)) ||                          \
        (CanRxOverIrqFlg           == (enCanIrqFLg)) ||                          \
        (CanRxBufFullIrqFlg        == (enCanIrqFLg)) ||                          \
        (CanRxBufAlmostFullIrqFlg  == (enCanIrqFLg)) ||                          \
        (CanTxPrimaryIrqFlg        == (enCanIrqFLg)) ||                          \
        (CanTxSecondaryIrqFlg      == (enCanIrqFLg)) ||                          \
        (CanErrorIrqFlg            == (enCanIrqFLg)) ||                          \
        (CanAbortIrqFlg            == (enCanIrqFLg)) ||                          \
        (CanErrorWarningIrqFlg     == (enCanIrqFLg)) ||                          \
        (CanErrorPassivenodeIrqFlg == (enCanIrqFLg)) ||                          \
        (CanErrorPassiveIrqFlg     == (enCanIrqFLg)) ||                          \
        (CanArbiLostIrqFlg         == (enCanIrqFLg)) ||                          \
        (CanBusErrorIrqFlg         == (enCanIrqFLg))                             \
)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CAN_Global_Functions CAN全局函数定义
 * @{
 */

/**
 * @brief  CAN 初始化
 * @param  [in] pstcCanInitCfg: @ref stc_can_init_config_t.
 * @retval None.
 */
void CAN_Init(stc_can_init_config_t *pstcCanInitCfg)
{
    ASSERT(NULL != pstcCanInitCfg);

    CAN_RESET_ENABLE();

    HC_CAN->BT_f.PRESC = pstcCanInitCfg->stcCanBt.PRESC;
    HC_CAN->BT_f.SEG_1 = pstcCanInitCfg->stcCanBt.SEG_1;
    HC_CAN->BT_f.SEG_2 = pstcCanInitCfg->stcCanBt.SEG_2;
    HC_CAN->BT_f.SJW   = pstcCanInitCfg->stcCanBt.SJW;

    CAN_RESET_DISABLE();



    HC_CAN->LIMIT_f.AFWL = pstcCanInitCfg->stcWarningLimit.CanWarningLimitVal;
    HC_CAN->LIMIT_f.EWL  = pstcCanInitCfg->stcWarningLimit.CanErrorWarningLimitVal;

    HC_CAN->TCTRL_f.TSMODE = pstcCanInitCfg->enCanSTBMode;

    HC_CAN->RCTRL_f.RBALL  = pstcCanInitCfg->enCanRxBufAll;
    HC_CAN->RCTRL_f.ROM    = pstcCanInitCfg->enCanRxBufMode;
    HC_CAN->RTIE = 0x00U;
}


/**
 * @brief  CAN 去初始化 (RESET CAN register)
 * @retval None.
 */
void CAN_DeInit(void)
{
    CAN_RESET_ENABLE();
}


/**
 * @brief  CAN 模式配置
 * @param  [in] enMode: 模式. @ref en_can_mode_t
 * @param  [in] enCanSAck: 模式. 自应答 @ref en_can_self_ack_en_t
 * @param  [in] enNewState: TRUE:使能；FLASE:禁止.
 * @retval None.
 */
void CAN_ModeConfig(en_can_mode_t enMode, en_can_self_ack_en_t enCanSAck, boolean_t enNewState)
{
    ASSERT(IS_CAN_MODE_VALID(enMode));
    ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(CanListenOnlyMode == enMode)
    {
        HC_CAN->TCMD_f.LOM = enNewState;
    }else
    {
        if(TRUE == enNewState)
        {
            HC_CAN->CFG_STAT |= enMode;
        }else
        {
            HC_CAN->CFG_STAT &= (uint8_t)(~enMode);
        }
    }

    HC_CAN->RCTRL_f.SACK = enCanSAck;

}


/**
 * @brief  CAN 筛选器配置
 * @param  [in] pstcFilter: 筛选器配置指针 @ref stc_can_filter_t.
 * @param  [in] enNewState: TRUE:使能；FLASE:禁止.
 * @retval None.
 */
void CAN_FilterConfig(stc_can_filter_t *pstcFilter, boolean_t enNewState)
{
    ASSERT(NULL != pstcFilter);
    ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CAN_RESET_ENABLE();

    /* Acceptance filter address */
    HC_CAN->ACFCTRL_f.ACFADR  = pstcFilter->enFilterSel;

    /* ID config */
    HC_CAN->ACFCTRL_f.SELMASK = CAN_ACF_ID_REG_SEL;
    HC_CAN->ACF               = pstcFilter->u32CODE;

    /* MASK config */
    HC_CAN->ACFCTRL_f.SELMASK = CAN_ACF_MASK_REG_SEL;
    HC_CAN->ACF               = pstcFilter->u32MASK;

    /* Frame format config */
    HC_CAN->ACF_f.AIDEE = (((uint32_t)pstcFilter->enAcfFormat >> 1) & 0x01U);
    HC_CAN->ACF_f.AIDE  = ((uint32_t)pstcFilter->enAcfFormat & 0x01U);

    if(TRUE == enNewState)
    {
        HC_CAN->ACFEN |= 1u << pstcFilter->enFilterSel;
    }else
    {
        HC_CAN->ACFEN &= ~(1u << pstcFilter->enFilterSel);
    }

    CAN_RESET_DISABLE();
}


/**
 * @brief  CAN 发送数据帧设置
 * @param  [in] pstcTxFrame: 发送数据帧指针 @ref stc_can_txframe_t.
 * @retval None.
 */
void CAN_SetFrame(stc_can_txframe_t *pstcTxFrame)
{
    ASSERT(NULL != pstcTxFrame);

    HC_CAN->TCMD_f.TBSEL = pstcTxFrame->enBufferSel;
    HC_CAN->TBUF0 = pstcTxFrame->TBUF32_0;
    HC_CAN->TBUF1 = pstcTxFrame->TBUF32_1;
    HC_CAN->TBUF2 = pstcTxFrame->TBUF32_2[0];
    HC_CAN->TBUF3 = pstcTxFrame->TBUF32_2[1];

    if(CanSTBSel == pstcTxFrame->enBufferSel)
    {
        HC_CAN->TCTRL_f.TSNEXT = TRUE;
    }

}


/**
 * @brief  CAN 数据帧发送命令
 * @param  [in] enTxCmd: 数据帧发送命令 @ref en_can_tx_cmd_t.
 * @retval None.
 */
void CAN_TransmitCmd(en_can_tx_cmd_t enTxCmd)
{
    ASSERT(IS_TX_CMD_VALID(enTxCmd));

    HC_CAN->TCMD |= enTxCmd;

}


/**
 * @brief  CAN 发送数据缓冲器状态获取
 * @retval en_can_tx_buf_status_t: CAN 发送数据缓冲器状态 @ref en_can_tx_buf_status_t
 */
en_can_tx_buf_status_t CAN_TxBufStatusGet(void)
{
    return (en_can_tx_buf_status_t)HC_CAN->TCTRL_f.TSSTAT;
}


/**
 * @brief  CAN 数据帧接收
 * @param  [out] pstcRxFrame: 数据帧接收指针 @ref stc_can_rxframe_t.
 * @retval None.
 */
void CAN_Receive(stc_can_rxframe_t *pstcRxFrame)
{
    ASSERT(NULL != pstcRxFrame);

    pstcRxFrame->RBUF32_0    = HC_CAN->RBUF0;
    pstcRxFrame->RBUF32_1    = HC_CAN->RBUF1;
    pstcRxFrame->RBUF32_2[0] = HC_CAN->RBUF2;
    pstcRxFrame->RBUF32_2[1] = HC_CAN->RBUF3;

    HC_CAN->RCTRL_f.RREL = 1U;

}


/**
 * @brief  CAN 接收数据缓冲器状态获取
 * @retval en_can_rx_buf_status_t: Can 接收数据缓冲器状态 @ref en_can_rx_buf_status_t
 */
en_can_rx_buf_status_t CAN_RxBufStatusGet(void)
{
    return (en_can_rx_buf_status_t)HC_CAN->RCTRL_f.RSSTAT;
}


/**
 * @brief  CAN 错误状态获取
 * @retval en_can_error_t: 错误状态 @ref en_can_error_t
 */
en_can_error_t CAN_ErrorStatusGet(void)
{
    if(6U > HC_CAN->EALCAP_f.KOER)
    {
        return (en_can_error_t)HC_CAN->EALCAP_f.KOER;
    }else
    {
        return UNKOWN_ERROR;
    }

}


/**
 * @brief  CAN 通信状态获取
 * @param  [in] enCanStatus: CAN 通信状态 @ref en_can_status_t
 * @retval boolean_t:
 *              - TRUE:对应状态位已置位
 *              - FLASE:对应状态位未置位
 */
boolean_t CAN_StatusGet(en_can_status_t enCanStatus)
{
    ASSERT(IS_CAN_STATUS_VALID(enCanStatus));

    if(HC_CAN->CFG_STAT & enCanStatus)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }
}


/**
 * @brief  CAN 中断使能
 * @param  [in] enCanIrqType: 中断类型 @ref en_can_irq_type_t.
 * @param  [in] enNewState: TRUE:使能；FLASE:禁止.
 * @retval None.
 */
void CAN_IrqCmd(en_can_irq_type_t enCanIrqType, boolean_t enNewState)
{
    volatile uint32_t *u32pIE;

    ASSERT(IS_CAN_IRQ_TYPE_VALID(enCanIrqType));
    ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32pIE = (volatile uint32_t*)(&HC_CAN->RTIE);

    if(TRUE == enNewState)
    {
        *u32pIE |= (uint32_t)enCanIrqType;
    }else
    {
        *u32pIE &= ~(uint32_t)enCanIrqType;
    }

}


/**
 * @brief  CAN 中断标志获取
 * @param  [in] enCanIrqFlgType: 中断标志类型 @ref en_can_irq_flag_type_t.
 * @retval boolean_t:
 *             - TRUE: 发生此中断
 *             - FLASE: 未发生此中断
 */
boolean_t CAN_IrqFlgGet(en_can_irq_flag_type_t enCanIrqFlgType)
{
    volatile uint32_t *u32pIE = NULL;

    ASSERT(IS_CAN_IRQ_FLAG_VALID(enCanIrqFlgType));

    u32pIE = (volatile uint32_t*)(&HC_CAN->RTIE);

    if( *u32pIE & (uint32_t)enCanIrqFlgType)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }

}


/**
 * @brief  CAN 中断标志清除
 * @param  [in] enCanIrqFlgType: 中断标志类型 @ref en_can_irq_flag_type_t.
 * @retval None.
 */
void CAN_IrqFlgClr(en_can_irq_flag_type_t enCanIrqFlgType)
{
    volatile uint32_t *u32pIE = NULL;
    uint32_t u32IETempMsk = CAN_IE_CLEAR_MASK;


    ASSERT(IS_CAN_IRQ_FLAG_VALID(enCanIrqFlgType));

    u32pIE = (volatile uint32_t*)(&HC_CAN->RTIE);

    *u32pIE = (((*u32pIE)&u32IETempMsk) | (uint32_t)enCanIrqFlgType);

}


/**
 * @brief  CAN 接收错误计数值获取
 *
 * @retval uint8_t Error Counter(0~255).
 */
uint8_t CAN_RxErrorCntGet(void)
{
    return HC_CAN->RECNT;
}


/**
 * @brief  CAN 发送错误计数值获取
 *
 * @retval uint8_t Error Counter(0~255).
 */
uint8_t CAN_TxErrorCntGet(void)
{
    return HC_CAN->TECNT;
}


/**
 * @brief  CAN 仲裁捕获
 *
 * @retval uint8_t address(0~31).
 */
uint8_t CAN_ArbitrationLostCap(void)
{
    return HC_CAN->EALCAP_f.ALC;
}

/* ========================================================================== */
/*  crc.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CRC CRC模块驱动库
 * @brief CRC Driver Library CRC模块驱动库
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
 * @defgroup CRC_Global_Functions CRC全局函数定义
 * @{
 */
/**
 * @brief  CRC16 编码(字节填充方式)
 * @param  [in] pu8Data 待编码数据数组（字节方式输入）
 * @param  [in] u32Len 待编码数据长度（字节数）
 * @retval uint16_t: CRC16编码值
 */
uint16_t CRC16_Get8(uint8_t pu8Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
        *((volatile uint8_t*)(&(HC_CRC->DATA)))  = pu8Data[u32Index];
    }

    return REG_READBITS(HC_CRC->RESULT, 0xFFFFU);
}

/**
 * @brief  CRC16 编码(半字填充方式)
 * @param  [in] pu16Data 待编码数据数组（半字方式输入）
 * @param  [in] u32Len 待编码数据长度（半字数）
 * @retval uint16_t: CRC16编码值
 */
uint16_t CRC16_Get16(uint16_t pu16Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }

    return REG_READBITS(HC_CRC->RESULT, 0xFFFFU);
}

/**
 * @brief  CRC16 编码(字填充方式).
 * @param  [in] pu32Data 待编码数据数组（字方式输入）
 * @param  [in] u32Len 待编码数据长度（字数）
 * @retval uint16_t: CRC16编码值
 */
uint16_t CRC16_Get32(uint32_t pu32Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        HC_CRC->DATA = pu32Data[u32Index];
    }

    return REG_READBITS(HC_CRC->RESULT, 0xFFFFU);
}

/**
 * @brief  CRC16 校验(字节填充方式)，该函数主要用于对数据及CRC16值进行校验.
 * @param  [in] pu8Data 待校验数据数组（字节方式输入）
 * @param  [in] u32Len 待校验数据长度（字节数）
 * @param  [in] u16CRC 待校验CRC16值
 * @retval en_result_t:
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC16_Check8(uint8_t pu8Data[], uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);

    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(HC_CRC->DATA))) = pu8Data[u32Index];
    }

    *((volatile uint16_t*)(&(HC_CRC->DATA))) = u16CRC;

    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;

    return (enResult);
}

/**
 * @brief  CRC16 校验(半字填充方式) 该函数主要用于对数据及CRC16值进行校验.
 * @param  [in] pu16Data 待校验数据数组（半字方式输入）
 * @param  [in] u32Len 待校验数据长度（半字数）
 * @param  [in] u16CRC 待校验CRC16值
 * @retval en_result_t:
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC16_Check16(uint16_t pu16Data[], uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }

    *((volatile uint16_t*)(&(HC_CRC->DATA))) = u16CRC;

    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;

    return (enResult);
}

/**
 * @brief  CRC16 校验(字填充方式) 该函数主要用于对数据及CRC16值进行校验.
 * @param  [in] pu32Data 待校验数据数组（字方式输入）
 * @param  [in] u32Len 待校验数据长度（字数）
 * @param  [in] u16CRC 待校验CRC16值
 * @retval en_result_t:
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC16_Check32(uint32_t pu32Data[], uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(HC_CRC->DATA))) = pu32Data[u32Index];
    }

     *((volatile uint16_t*)(&(HC_CRC->DATA))) = u16CRC;

    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;

    return (enResult);
}

/**
 * @brief  CRC32 编码(字节填充方式) 该函数主要用于生成CRC32编码.
 * @param  [in] pu8Data 待编码数据数组（字节方式输入）
 * @param  [in] u32Len 待编码数据长度（字节数）
 * @retval uint32_t: CRC32编码值
 */
uint32_t CRC32_Get8(uint8_t pu8Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;

    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(HC_CRC->DATA)))  = pu8Data[u32Index];
    }

    return REG_READ(HC_CRC->RESULT);
}

/**
 * @brief  CRC32 编码(半字填充方式) 该函数主要用于生成CRC32编码.
 * @param  [in] pu16Data 待编码数据数组（半字方式输入）
 * @param  [in] u32Len 待编码数据长度（半字数）
 * @retval uint32_t: CRC32编码值
 */
uint32_t CRC32_Get16(uint16_t pu16Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;

    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }

    return REG_READ(HC_CRC->RESULT);
}

/**
 * @brief  CRC32 编码(字填充方式) 该函数主要用于生成CRC32编码.
 * @param  [in] pu32Data 待编码数据数组（字方式输入）
 * @param  [in] u32Len 待编码数据长度（字数）
 * @retval uint32_t: CRC32编码值
 */
uint32_t CRC32_Get32(uint32_t pu32Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;

    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        HC_CRC->DATA = pu32Data[u32Index];
    }

    return REG_READ(HC_CRC->RESULT);
}

/**
 * @brief  CRC32 校验(字节填充方式) 该函数主要用于对数据及CRC32值进行校验.
 * @param  [in] pu8Data 待校验数据数组（字节方式输入）
 * @param  [in] u32Len 待校验数据长度（字节数）
 * @param  [in] u32CRC 待校验CRC32值
 * @retval en_result_t:
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC32_Check8(uint8_t pu8Data[], uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(HC_CRC->DATA))) = pu8Data[u32Index];
    }

    REG_WRITE(HC_CRC->DATA, u32CRC);

    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;

    return (enResult);
}

/**
 * @brief  CRC32 校验(半字填充方式) 该函数主要用于对数据及CRC32值进行校验.
 * @param  [in] pu16Data 待校验数据数组（半字方式输入）
 * @param  [in] u32Len 待校验数据长度（半字数）
 * @param  [in] u32CRC 待校验CRC32值
 * @retval en_result_t:
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC32_Check16(uint16_t pu16Data[], uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }

    REG_WRITE(HC_CRC->DATA, u32CRC);

    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;

    return (enResult);
}

/**
 * @brief  CRC32 校验(字填充方式) 该函数主要用于对数据及CRC32值进行校验.
 * @param  [in] pu32Data 待校验数据数组（字方式输入）
 * @param  [in] u32Len 待校验数据长度（字数）
 * @param  [in] u32CRC 待校验CRC32值
 * @retval en_result_t:
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC32_Check32(uint32_t pu32Data[], uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        REG_WRITE(HC_CRC->DATA, pu32Data[u32Index]);
    }
    REG_WRITE(HC_CRC->DATA, u32CRC);

    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;

    return (enResult);
}

/* ========================================================================== */
/*  ctrim.c                                                                   */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CTRIM CTRIM模块驱动库
 * @brief CTRIM Driver Library CTRIM模块驱动库
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */

/**
 * @brief  CTRIM 时钟校准初始化配置
 * @param  [in] CTRIMx:      TRIM类型定义           @ref CTRIM_TypeDef
 * @param  [in] pstcInitCfg: Trim时钟校准结构体     @ref stc_ctrim_cali_init_t
 * @retval en_result_t
 *         - Ok:                    OK
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CTRIM_CaliInit(CTRIM_TypeDef* CTRIMx, stc_ctrim_cali_init_t* pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    if (((pstcInitCfg->u32Mode & CTRIM_CR1_MD_B1) != 0u) || (pstcInitCfg->u32RefClockDiv == 0u))
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_STEP | CTRIM_CR0_ETRFLT | CTRIM_CR0_SRC,
        pstcInitCfg->u32InitialStep | pstcInitCfg->u32EtrFilter | pstcInitCfg->u32AccurateClock);

    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_MD | CTRIM_CR1_AUTO | CTRIM_CR1_PRS | CTRIM_CR1_OST | CTRIM_CR1_MDRCH,
        pstcInitCfg->u32Mode | pstcInitCfg->u32RefClockDiv | pstcInitCfg->u32OneShot | pstcInitCfg->u32RCHTrimBits);

    CTRIMx->ARR = pstcInitCfg->u16ReloadVal;

    CTRIMx->FLIM = pstcInitCfg->u16CountErrorLimit;

    return Ok;
}

/**
 * @brief  CTRIM 时钟功能初始化配置
 * @param  [in] CTRIMx:      TRIM类型定义             @ref CTRIM_TypeDef
 * @param  [in] pstcInitCfg: Trim时钟初始化结构体     @ref stc_ctrim_timer_init_t
 * @retval en_result_t
 *         - Ok:                    OK
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CTRIM_TimerInit(CTRIM_TypeDef* CTRIMx, stc_ctrim_timer_init_t* pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    if (pstcInitCfg->u32ClockDiv == 0u)
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_ETRFLT | CTRIM_CR0_SRC, pstcInitCfg->u32EtrFilter | pstcInitCfg->u32Clock);

    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_MD | CTRIM_CR1_AUTO | CTRIM_CR1_PRS, CTRIM_CR1_MD_B1 | pstcInitCfg->u32ClockDiv);

    CTRIMx->ARR = pstcInitCfg->u16ReloadVal;

    return Ok;
}

/**
 * @brief  CTRIM 获取误差计数器计数值
 * @param  [in] CTRIMx:      TRIM类型定义             @ref CTRIM_TypeDef
 * @retval uint32_t：        计数器计数值
 */
uint32_t CTRIM_GetCounter(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CNT, CTRIM_CNT_CNT));
}

/**
 * @brief  CTRIM 设定自动装载寄存器的值
 * @param  [in] CTRIMx:        TRIM类型定义             @ref CTRIM_TypeDef
 * @param  [in] u32AutoReload: 重载值 取值范围 0x0 ~ 0xFFFF
 * @retval None
 */
void CTRIM_SetAutoReload(CTRIM_TypeDef* CTRIMx, uint32_t u32AutoReload)
{
    REG_MODIFY(CTRIMx->ARR, CTRIM_ARR_ARR, u32AutoReload);
}

/**
 * @brief  CTRIM 获取自动装载寄存器的值
 * @param  [in] CTRIMx:        TRIM类型定义             @ref CTRIM_TypeDef
 * @retval uint32_t：          自动装载寄存器的值
 */
uint32_t CTRIM_GetAutoReload(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->ARR, CTRIM_ARR_ARR));
}

/**
 * @brief  CTRIM RCH/RCL TRIM初始步进量配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] CTRIMx:        TRIM类型定义      @ref CTRIM_TypeDef
 * @param  [in] u32TrimStep:   初始步进量        @ref CTRIM_INITIAL_STEP_SELECTION
 * @retval None
 */
void CTRIM_SetInitialStep(CTRIM_TypeDef* CTRIMx, uint32_t u32TrimStep)
{
    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_STEP, u32TrimStep);
}

/**
 * @brief  CTRIM 获取TRIM初始步进量
 * @param  [in] CTRIMx:     TRIM类型定义      @ref CTRIM_TypeDef
 * @retval uint32_t:        TRIM初始步进量
 *         - CTRIM_INITIAL_STEP_1
 *         - CTRIM_INITIAL_STEP_2
 *         - CTRIM_INITIAL_STEP_4
 *         - CTRIM_INITIAL_STEP_8
 *         - CTRIM_INITIAL_STEP_16
 *         - CTRIM_INITIAL_STEP_32
 *         - CTRIM_INITIAL_STEP_64
 *         - CTRIM_INITIAL_STEP_128
 */
uint32_t CTRIM_GetInitialStep(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR0, CTRIM_CR0_STEP));
}

/**
 * @brief  CTRIM 外部管脚输入时钟滤波配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] CTRIMx:            TRIM类型定义         @ref CTRIM_TypeDef
 * @param  [in] u32ExClockFilter:  外部输入时钟滤波配置  @ref CTRIM_ETR_CLOCK_FILTER_SELECTION
 * @retval None
 */
void CTRIM_SetEtrClockFilter(CTRIM_TypeDef* CTRIMx, uint32_t u32ExClockFilter)
{
    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_ETRFLT, u32ExClockFilter);
}

/**
 * @brief  CTRIM 获取外部管脚输入时钟滤波配置
 * @param  [in] CTRIMx:            TRIM类型定义         @ref CTRIM_TypeDef
 * @retval uint32_t： 外部输入时钟滤波配置
 *         - CTRIM_ETR_CLOCK_FILTER_NONE:               外部输入时钟无滤波
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV1_CYCLE2:   采样时钟频率为PCLK，滤波宽度小于2个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV1_CYCLE4:   采样时钟频率为PCLK，滤波宽度小于4个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV1_CYCLE6:   采样时钟频率为PCLK，滤波宽度小于6个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV4_CYCLE4:   采样时钟频率为PCLK/4，滤波宽度小于4个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV4_CYCLE6:   采样时钟频率为PCLK/4，滤波宽度小于6个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV8_CYCLE4:   采样时钟频率为PCLK/8，滤波宽度小于4个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV8_CYCLE6:   采样时钟频率为PCLK/8，滤波宽度小于6个采样周期
 */
uint32_t CTRIM_GetEtrClockFilter(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR0, CTRIM_CR0_ETRFLT));
}

/**
 * @brief  CTRIM 精确时钟源选择，必须在CTRIM模块未使能时才可以配置
 * @param  [in] CTRIMx:            TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32ClockSource:    时钟源选择      @ref CTRIM_ACCURATE_CLOCK_SELECTION
 * @retval None
 */
void CTRIM_SetAccurateClock(CTRIM_TypeDef* CTRIMx, uint32_t u32ClockSource)
{
    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_SRC, u32ClockSource);
}

/**
 * @brief  CTRIM 获取精确时钟源选择
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t:           时钟源选择
 *         - CTRIM_ACCURATE_CLOCK_ETR:         精准时钟源选择外部输入时钟
 *         - CTRIM_ACCURATE_CLOCK_XTH:         精准时钟源选择XTH
 *         - CTRIM_ACCURATE_CLOCK_XTL:         精准时钟源选择XTL
 *         - CTRIM_ACCURATE_CLOCK_PCLK:        精准时钟源选择PCLK
 *         - CTRIM_ACCURATE_CLOCK_RCL:         精准时钟源选择RCL
 *         - CTRIM_ACCURATE_CLOCK_RCH:         精准时钟源选择RCH
 *         - CTRIM_ACCURATE_CLOCK_LPTIM_TOG:   精准时钟源选择LPTIM_TOG
 */
uint32_t CTRIM_GetAccurateClock(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR0, CTRIM_CR0_SRC));
}

/**
 * @brief  CTRIM 工作模式配置
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32Mode:       工作模式选择    @ref CTRIM_MODE_SELECTION
 * @retval None
 */
void CTRIM_SetMode(CTRIM_TypeDef* CTRIMx, uint32_t u32Mode)
{
    REG_MODIFY(CTRIMx->CR1, (CTRIM_CR1_AUTO | CTRIM_CR1_MD), u32Mode);
}

/**
 * @brief  CTRIM 获取工作模式配置
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t：          工作模式选择
 *         - CTRIM_MODE_RCH_AUTO_TRIM:    RCH自动校准模式
 *         - CTRIM_MODE_RCL_AUTO_TRIM:    RCL自动校准模式
 *         - CTRIM_MODE_TIMER:            定时器模式
 */
uint32_t CTRIM_GetMode(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, (CTRIM_CR1_AUTO | CTRIM_CR1_MD)));
}

/**
 * @brief  CTRIM RCH Trim Bits配置
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32RchTrimBits: TRIM Bits选择   @ref CTRIM_RCH_TRIM_BITS_SELECTION
 * @retval None
 */
void CTRIM_SetRCHTrimBits(CTRIM_TypeDef* CTRIMx, uint32_t u32RchTrimBits)
{
    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_MDRCH, u32RchTrimBits);
}

/**
 * @brief  CTRIM 获取RCH Trim Bits配置
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t：          工作模式选择
 *         - CTRIM_RCH_TRIM_11bit:   RCH 单次校准 11bit
 *         - CTRIM_RCH_TRIM_5bit:    RCH 粗调校准 5bit
 *         - CTRIM_RCH_TRIM_6bit:    RCH 细调校准 6bit
 */
uint32_t CTRIM_GetRCHTrimBits(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, CTRIM_CR1_MDRCH));
}

/**
 * @brief  CTRIM 参考时钟预分频配置,CTRIMx->CR1.PRS不能配置为0值，否则CTRIM不能正常工作
 * @param  [in] CTRIMx:         TRIM类型定义         @ref CTRIM_TypeDef
 * @param  [in] u32RefClockDiv: 参考时钟预分频配置    @ref CTRIM_REF_CLOCK_DIV_SELECTION
 * @retval None
 */
void CTRIM_SetRefClockDiv(CTRIM_TypeDef* CTRIMx, uint32_t u32RefClockDiv)
{
    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_PRS, u32RefClockDiv);
}

/**
 * @brief  CTRIM 获取参考时钟预分频配置
 * @param  [in] CTRIMx:         TRIM类型定义         @ref CTRIM_TypeDef
 * @retval uint32_t: 参考时钟预分频配置
 *         - CTRIM_REF_CLOCK_DIV2
 *         - CTRIM_REF_CLOCK_DIV4
 *         - CTRIM_REF_CLOCK_DIV8
 *         - CTRIM_REF_CLOCK_DIV16
 *         - CTRIM_REF_CLOCK_DIV32
 *         - CTRIM_REF_CLOCK_DIV64
 *         - CTRIM_REF_CLOCK_DIV128
 *         - CTRIM_REF_CLOCK_DIV512
 *         - CTRIM_REF_CLOCK_DIV1024
 *         - CTRIM_REF_CLOCK_DIV2048
 *         - CTRIM_REF_CLOCK_DIV4096
 *         - CTRIM_REF_CLOCK_DIV8192
 *         - CTRIM_REF_CLOCK_DIV16384
 *         - CTRIM_REF_CLOCK_DIV32768
 */
uint32_t CTRIM_GetRefClockDiv(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, CTRIM_CR1_PRS));
}

/**
 * @brief  CTRIM 校准模式配置
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32OneShotMode: 校准模式配置    @ref CTRIM_ONE_SHOT_SELECTION
 * @retval None
 */
void CTRIM_SetOneShot(CTRIM_TypeDef* CTRIMx, uint32_t u32OneShotMode)
{
    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_OST, u32OneShotMode);
}

/**
 * @brief  CTRIM 获取校准模式配置
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 校准模式配置
 *         - CTRIM_ONE_SHOT_REPETITIVE:    实时校准模式
 *         - CTRIM_ONE_SHOT_SINGLE:        单次校准模式
 */
uint32_t CTRIM_GetOneShot(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, CTRIM_CR1_OST));
}

/**
 * @brief  CTRIM 获取误差计数器计数方向
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 误差计数器计数方向
 *         - CTRIM_ARR_COUNT_DIR_INCREASE:  递增计数，RCH输出频率高于目标频率，或RCL输出频率低于目标频率
 *         - CTRIM_ARR_COUNT_DIR_DECREASE:  递减计数，RCH输出频率低于目标频率，或RCL输出频率高于目标频率
 */
uint32_t CTRIM_GetARRCoutDir(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->ISR, CTRIM_ISR_DIR));
}

/**
 * @brief  CTRIM 获取TrimCode值，及trim结束后的trim校准值
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: TrimCode值
 */
uint32_t CTRIM_GetTrimCode(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->TVAL, CTRIM_TVAL_TVAL));
}

/**
 * @brief  CTRIM 获取计数误差捕获值，校准结束时，ARR寄存器里面的值
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 计数误差捕获值
 */
uint32_t CTRIM_GetCountErrorCapture(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->FCAP, CTRIM_FCAP_FCAP));
}

/**
 * @brief  CTRIM 设置误差允许值， 一个周期计数结束，ARR寄存器里的值小于当前设定值，则认为校验成功
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u16ErrLimit:     误差上限值 取值范围 0x0 ~ 0xFFF
 * @retval None
 */
void CTRIM_SetCountErrorLimit(CTRIM_TypeDef* CTRIMx, uint16_t u16ErrLimit)
{
    REG_MODIFY(CTRIMx->FLIM, CTRIM_FLIM_FLIM, u16ErrLimit);
}

/**
 * @brief  CTRIM 获取误差允许值， 一个周期计数结束，ARR寄存器里的值小于当前设定值，则认为校验成功
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint16_t：  误差上限值
 */
uint16_t CTRIM_GetCountErrorLimit(CTRIM_TypeDef* CTRIMx)
{
    return (uint16_t)(REG_READBITS(CTRIMx->FLIM, CTRIM_FLIM_FLIM));
}

/**
 * @brief  CTRIM 开启模块
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval None
 */
void CTRIM_Enable(CTRIM_TypeDef* CTRIMx)
{
    REG_SETBITS(CTRIMx->CR1, CTRIM_CR1_EN);
}

/**
 * @brief  CTRIM 禁止模块
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval None
 */
void CTRIM_Disable(CTRIM_TypeDef* CTRIMx)
{
    REG_CLEARBITS(CTRIMx->CR1, CTRIM_CR1_EN);
}

/**
 * @brief  CTRIM 检查模块是否已开启
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 状态
 *         - 0：  未开启
 *         - 非0：已开启
 */
boolean_t CTRIM_IsEnable(CTRIM_TypeDef* CTRIMx)
{
    return (REG_READBITS(CTRIMx->CR1, CTRIM_CR1_EN) == CTRIM_CR1_EN) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 中断使能
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32IT:         TRIM类型定义    @ref CTRIM_IT_SELECTION
 * @retval None
 */
void CTRIM_EnableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT)
{
    REG_SETBITS(CTRIMx->IER, u32IT);
}

/**
 * @brief  CTRIM 中断禁止
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32IT:         TRIM类型定义    @ref CTRIM_IT_SELECTION
 * @retval None
 */
void CTRIM_DisableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT)
{
    REG_CLEARBITS(CTRIMx->IER, u32IT);
}

/**
 * @brief  CTRIM 检查中断是否开启
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32IT:         TRIM类型定义    @ref CTRIM_IT_SELECTION
 * @retval uint32_t: 状态
 *         - 0：  未开启
 *         - 非0：已开启
 */
boolean_t CTRIM_IsEnableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT)
{
    return (REG_READBITS(CTRIMx->IER, u32IT) == u32IT) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 获取中断标志
 * @param  [in] CTRIMx:        TRIM类型定义                               @ref CTRIM_TypeDef
 * @param  [in] u32ITFlag:    中断标记,CTRIM_IT_SELECTION值或值相或的组合 @ref CTRIM_IT_SELECTION
 * @retval uint32_t: 状态
 *         - 0：  对应每位的功能
 *         - 非0：对应每位的功能
 */
boolean_t CTRIM_IsActiveFlag(CTRIM_TypeDef* CTRIMx, uint32_t u32ITFlag)
{
    return (REG_READBITS(CTRIMx->ISR, u32ITFlag) == u32ITFlag) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 清除中断标志
 * @param  [in] CTRIMx:        TRIM类型定义                               @ref CTRIM_TypeDef
 * @param  [in] u32ITFlag:     中断标记,CTRIM_IT_SELECTION值或值相或的组合 @ref CTRIM_IT_SELECTION
 * @retval None
 */
void CTRIM_ClearFlag(CTRIM_TypeDef* CTRIMx, uint32_t u32ITFlag)
{
    REG_CLEARBITS(CTRIMx->ICR, u32ITFlag);
}

/**
 * @brief  CTRIM 清除所有标志
 * @param  [in] CTRIMx:        TRIM类型定义                               @ref CTRIM_TypeDef
 * @retval None
 */
void CTRIM_ClearFlag_ALL(CTRIM_TypeDef* CTRIMx)
{
    CTRIMx->ICR = 0u;
}

/* ========================================================================== */
/*  debug.c                                                                   */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DEBUG DEBUG模块驱动库
 * @brief DEBUG Driver Library DEBUG模块驱动库
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
 * @defgroup DEBUG_Global_Functions DEBUG全局函数定义
 * @{
 */

/**
 * @brief  调试模式下模块功能计数使能.
 * @param  [in] enModule: 选择设置的外设模块 @ref en_debug_module_active_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 */
en_result_t Debug_ActiveEnable(en_debug_module_active_t enModule)
{
    HC_SYSCTRL->DBGSTOP &= ~(uint32_t)enModule;

    return Ok;
}


/**
 * @brief  调试模式下模块功能计数暂停.
 * @param  [in] enModule: 选择设置的外设模块 @ref en_debug_module_active_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 */
en_result_t Debug_ActiveDisable(en_debug_module_active_t enModule)
{
    HC_SYSCTRL->DBGSTOP |= (uint32_t)enModule;

    return Ok;
}

/* ========================================================================== */
/*  dmac.c                                                                    */
/* ========================================================================== */


/*******************************************************************************
* Include files
******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DMAC DMAC模块驱动库
 * @brief DMAC Driver Library DMAC模块驱动库
 * @{
 */

/*******************************************************************************
* Local type definitions ('typedef')
******************************************************************************/

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/
/**
 * @defgroup DMAC_Local_Macros DMAC局部宏定义
 * @{
 */

/**
 * @defgroup DMAC_PARA_CHECK 参数合法性检查
 * @{
 */
/**
 * @brief  DMA 通道参数有效性检查 @ref en_dma_channel_t
 */
#define IS_VALID_CH(x)                 \
(   (DmaCh0 == (x))                 || \
    (DmaCh1 == (x))                 || \
    (DmaCh2 == (x))                 || \
    (DmaCh3 == (x))                 || \
    (DmaCh4 == (x)))

/**
 * @brief  DMA 传输数据宽度，参数有效性检查 @ref en_dma_transfer_width_t
 */
#define IS_VALID_TRN_WIDTH(x)                  \
(   (DmaMsk8Bit == (x))                     || \
    (DmaMsk16Bit == (x))                    || \
    (DmaMsk32Bit == (x)))

/**
 * @brief  DMA源地址控制模式，参数有效性检查 @ref en_src_address_mode_t
 */
#define IS_VALID_SRC_ADDR_MODE(x)              \
(   (DmaMskSrcAddrFix == (x))               || \
    (DmaMskSrcAddrInc == (x)))

/**
 * @brief  DMA目的地址控制模式，参数有效性检查 @ref en_dst_address_mode_t
 */
#define IS_VALID_DST_ADDR_MODE(x)              \
(   (DmaMskDstAddrFix == (x))               || \
    (DmaMskDstAddrInc == (x)))

/**
 * @brief  DMA 优先级, 参数有效性检查 @ref en_dma_priority_t
 */
#define IS_VALID_PRIO_MODE(x)                  \
(   (DmaMskPriorityFix == (x))              || \
    (DmaMskPriorityLoop == (x)))

/**
 * @brief  DMA 传输模式，参数有效性检查 @ref en_dma_msk_t
 */
#define IS_VALID_TRANSFER_MODE(x)              \
(   (DmaMskOneTransfer == (x))              || \
    (DmaMskContinuousTransfer == (x)))

/**
 * @brief  DMA 块传输大小，参数有效性检查
 */
#define IS_VALID_BLKSIZE(x)                 ((!((x) & ~(DMAC_CONFA0_BC_Msk >> DMAC_CONFA0_BC_Pos)))&&((x)>0))

/**
 * @brief  DMA 块传输次数，参数有效性检查
 */
#define IS_VALID_TRNCNT(x)                  (!((x) & ~(DMAC_CONFA0_TC_Msk >> DMAC_CONFA0_TC_Pos)))


/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/

/*******************************************************************************
* Local function prototypes ('static')
******************************************************************************/

/*******************************************************************************
* Local variable definitions ('static')
******************************************************************************/

/*******************************************************************************
* Function implementation - global ('extern') and local ('static')
******************************************************************************/
/**
 * @defgroup DMAC_Global_Functions DMAC全局函数定义
 * @{
 */

/**
 * @brief  初始化DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] pstcCfg: DMA通道初始化配置结构体指针 @ref stc_dma_cfg_t
 * @retval en_result_t:
 *           - Ok: 初始化成功
 *           - ErrorInvalidParameter: pstcCfg是空指针
 */
en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg)
{
    volatile uint32_t u32reg;

    ASSERT(IS_VALID_CH(enCh));/* 检查通道值有效性 */
    ASSERT(NULL != pstcCfg);
    ASSERT(IS_VALID_BLKSIZE(pstcCfg->u16BlockSize));
    ASSERT(IS_VALID_TRNCNT(pstcCfg->u16TransferCnt));
    ASSERT(IS_VALID_TRN_WIDTH(pstcCfg->enTransferWidth));
    ASSERT(IS_VALID_SRC_ADDR_MODE(pstcCfg->enSrcAddrMode));
    ASSERT(IS_VALID_DST_ADDR_MODE(pstcCfg->enDstAddrMode));
    ASSERT(IS_VALID_PRIO_MODE(pstcCfg->enPriority));
    ASSERT(IS_VALID_TRANSFER_MODE(pstcCfg->enTransferMode));

    /* 检查通道值有效性和pstcCfg是否空指针 */
    if (NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = 0U;
    *((uint32_t*)u32reg) = (uint32_t)pstcCfg->enMode             |
                                  (uint32_t)pstcCfg->enTransferWidth    |
                                  (uint32_t)pstcCfg->enSrcAddrMode      |
                                  (uint32_t)pstcCfg->enDstAddrMode      |
                                  (uint32_t)pstcCfg->enSrcAddrReloadCtl |
                                  (uint32_t)pstcCfg->enDestAddrReloadCtl|
                                  (uint32_t)pstcCfg->enSrcBcTcReloadCtl |
                                  (uint32_t)pstcCfg->enTransferMode;

    /* 首先把TRI_SEL[6:0]     BC[3:0] TC[15:0]这些位清零，然后再赋值 */
    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= ((uint32_t)~(DMAC_CONFA0_TRISEL_Msk | DMAC_CONFA0_BC_Msk \
                                                | DMAC_CONFA0_TC_Msk));
    *((uint32_t*)u32reg)    |= ((uint32_t)pstcCfg->u16TransferCnt - 1U)    | \
                                   (((uint32_t)pstcCfg->u16BlockSize - 1U) << DMAC_CONFA0_BC_Pos)| \
                                   ((uint32_t)pstcCfg->enRequestNum << DMAC_CONFA0_TRISEL_Pos);

    HC_DMAC->CONF |= (uint32_t)(pstcCfg->enPriority);

    u32reg = (uint32_t)&HC_DMAC->SRCADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = (uint32_t)(pstcCfg->u32SrcAddress);
    u32reg = (uint32_t)&HC_DMAC->DSTADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = (uint32_t)(pstcCfg->u32DstAddress);

  return Ok;
}

/**
 * @brief  DMA模块使能函数，使能所有通道的操作，每个通道按照各自设置工作
 * @retval None
 */
void Dma_Enable(void)
{
    HC_DMAC->CONF |= DMAC_CONF_EN_Msk;
}

/**
 * @brief  DMA模块功能禁止函数，所有通道禁止工作
 * @retval None
 */
void Dma_Disable(void)
{
    HC_DMAC->CONF &= (~DMAC_CONF_EN_Msk);
}

/**
 * @brief  触发指定DMA通道软件传输功能
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_SwStart(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFA0_ST_Msk;
}

/**
 * @brief  停止指定DMA通道软件传输功能
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_SwStop(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFA0_ST_Msk);
}

/**
 * @brief  使能指定DMA通道的（传输完成）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableChannelIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFB0_FISIE_Msk;
}

/**
 * @brief  禁用指定DMA通道的（传输完成）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableChannelIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_FISIE_Msk);
}

/**
 * @brief  使能指定DMA通道的（传输错误）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableChannelErrIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFB0_ERRIE_Msk;
}

/**
 * @brief  禁用指定DMA通道的（传输错误）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableChannelErrIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_ERRIE_Msk);
}

/**
 * @brief  使能指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableChannel(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFA0_ENS_Msk;
}

/**
 * @brief  禁用指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableChannel(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFA0_ENS_Msk);
}

/**
 * @brief  设定指定通道的块(Block)尺寸
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u16BlkSize: 块(Block)尺寸
 * @retval None
 */
void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize)
{
    volatile uint32_t u32reg;
    uint32_t u32val;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    u32val = *((uint32_t*)u32reg) & ((uint32_t)~DMAC_CONFA0_BC_Msk);
    *((uint32_t*)u32reg) = u32val | ((((uint32_t)u16BlkSize-1U)&0x0fU)<<DMAC_CONFA0_BC_Pos);
}

/**
 * @brief  设定指定通道块(Block)传输次数
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u16TrnCnt: 块(Block)传输次数
 * @retval None
 */
void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt)
{
    volatile uint32_t u32reg;
    uint32_t u32val;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    u32val = *((uint32_t*)u32reg) & ((uint32_t)~DMAC_CONFA0_TC_Msk);
    *((uint32_t*)u32reg) = u32val | ((((uint32_t)u16TrnCnt-1U)<<DMAC_CONFA0_TC_Pos));
}

/**
 * @brief  允许指定通道可连续传输，即DMA在传输完成时不清除CONFA:ENS位
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableContinusTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFB0_MSK;
}

/**
 * @brief  禁止指定通道连续传输，即DMA在传输完成时清除CONFA:ENS位
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableContinusTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_MSK);
}

/**
 * @brief  暂停所有DMA通道
 * @retval None
 */
void Dma_HaltTranfer(void)
{
    HC_DMAC->CONF_f.HALT = 0x1U;
}

/**
 * @brief  恢复（之前暂停的）所有DMA通道
 * @retval None
 */
void Dma_RecoverTranfer(void)
{
    HC_DMAC->CONF_f.HALT = 0x0U;
}

/**
 * @brief  暂停指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_PauseChannelTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFA0_PAS_Msk;
}

/**
 * @brief  恢复指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFA0_PAS_Msk);
}

/**
 * @brief  设定指定通道传输数据宽度
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] enWidth: 指定数据宽度 @ref en_dma_transfer_width_t
 * @retval None
 */
void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth)
{
    volatile uint32_t u32reg;
    uint32_t u32val;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    u32val =  *((uint32_t*)u32reg) & ((uint32_t)~DMAC_CONFB0_WIDTH_Msk);
    *((uint32_t*)u32reg) = u32val | ((uint32_t)enWidth);
}

/**
 * @brief  设定DMA通道优先级
 * @param  [in] enPrio: 通道优先级设定参数 @ref en_dma_priority_t
 * @retval None
 */
void Dma_SetChPriority(en_dma_priority_t enPrio)
{
    HC_DMAC->CONF = ((HC_DMAC->CONF)&((uint32_t)~DMAC_CONF_PRIO_Msk))|((uint32_t)enPrio);
}

/**
 * @brief  获取指定DMA通道的状态
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval en_dma_stat_t @ref en_dma_stat_t
 */
en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    return (en_dma_stat_t)((*((uint32_t*)u32reg)&(DMAC_CONFB0_STAT_Msk))>>DMAC_CONFB0_STAT_Pos);
}

/**
 * @brief  清除指定DMA通道的状态值
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_ClrStat(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_STAT_Msk);
}

/**
 * @brief  设定指定通道源地址
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u32Address: 传输源地址
 * @retval None
 */
void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->SRCADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = u32Address;
}

/**
 * @brief  设定指定通道目标地址
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u32Address: 传输源地址
 * @retval None
 */
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->DSTADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = u32Address;
}

/* ========================================================================== */
/*  eau.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_EAU EAU模块驱动库
 * @brief EAU Driver Library EAU模块驱动库
 * @{
 */


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EAU_Local_Macros EAU局部宏定义
 * @{
 */
/**
 * @defgroup EAU_Timeout EAU 超时时间
 * @{
 */
#define EAU_TIMEOUT_SQRT        (17U)   /*!< 开方运算需要17个HCLK周期 */
#define EAU_TIMEOUT_DIV         (35U)   /*!< 除法运算需要2到35个HCLK周期 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EAU_Global_Functions EAU全局函数定义
 * @{
 */


/**
 * @brief  开方运算函数
 * @param  [in] u32A: 被开方数
 * @param  [out] pu32X: 平方根结果输出指针
 * @param  [out] pu32Y: 余数结果输出指针
 * @retval en_eau_status_t: 运算状态 @ref en_eau_status_t
 */
en_eau_status_t EAU_Sqrt(uint32_t u32A, uint32_t *pu32X, uint32_t *pu32Y)
{
    uint16_t timeout = 0U;

    if((pu32X == NULL) || (pu32Y ==NULL))
    {
        return EauErrPara;
    }

    HC_EAU->CSR_f.MODE = EAU_MODE_SQRT;
    HC_EAU->DIVIDEND = u32A;
    while(HC_EAU->CSR_f.BUSY)
    {
        timeout ++;
        if(timeout > EAU_TIMEOUT_SQRT)
        {
            return EauErrTimeout;
        }
    }

    *pu32X = HC_EAU->QUOTIENT;
    *pu32Y = HC_EAU->REMAINDER;

    return EauOk;
}


/**
 * @brief  无符号除法运算函数
 * @param  [in] u32A: 被除数
 * @param  [in] u32B: 除数
 * @param  [out] pu32X: 商结果输出指针
 * @param  [out] pu32Y: 余数结果输出指针
 * @retval en_eau_status_t: 运算状态 @ref en_eau_status_t
 */
en_eau_status_t EAU_UnsignDiv(uint32_t u32A, uint32_t u32B, uint32_t *pu32X, uint32_t *pu32Y)
{
    uint16_t timeout = 0U;

    if((pu32X == NULL) || (pu32Y ==NULL))
    {
        return EauErrPara;
    }

    HC_EAU->CSR_f.MODE = EAU_MODE_UNSIGN_DIV;

#if 0 /* CSR_f.ZERO可以判断除数是否为0 */
    if(u32B == 0U)
    {
        return EauErrZero;
    }
#endif
    HC_EAU->DIVIDEND = u32A;
    HC_EAU->DIVISOR = u32B;
    while(HC_EAU->CSR_f.BUSY)
    {
        timeout ++;
        if(timeout > EAU_TIMEOUT_DIV)
        {
            return EauErrTimeout;
        }
    }

    *pu32X = HC_EAU->QUOTIENT;
    *pu32Y = HC_EAU->REMAINDER;

    if(HC_EAU->CSR_f.ZERO)
    {
        return EauErrZero;
    }

    return EauOk;
}


/**
 * @brief  有符号除法运算函数
 * @param  [in] s32A: 被除数
 * @param  [in] s32B: 除数
 * @param  [out] ps32X: 商结果输出指针
 * @param  [out] ps32Y: 余数结果输出指针
 * @retval en_eau_status_t: 运算状态 @ref en_eau_status_t
 */
en_eau_status_t EAU_SignDiv(int32_t s32A, int32_t s32B, int32_t *ps32X, int32_t *ps32Y)
{
    uint16_t timeout = 0U;

    if((ps32X == NULL) || (ps32Y ==NULL))
    {
        return EauErrPara;
    }

    HC_EAU->CSR_f.MODE = EAU_MODE_SIGN_DIV;

#if 0 /* CSR_f.ZERO可以判断除数是否为0 */
    if(s32B == 0U)
    {
        return EauErrZero;
    }
#endif

    HC_EAU->DIVIDEND = (uint32_t)s32A;
    HC_EAU->DIVISOR = (uint32_t)s32B;
    while(HC_EAU->CSR_f.BUSY)
    {
        timeout ++;
        if(timeout > EAU_TIMEOUT_DIV)
        {
            return EauErrTimeout;
        }
    }

    *ps32X = (int32_t)HC_EAU->QUOTIENT;
    *ps32Y = (int32_t)HC_EAU->REMAINDER;

    if(HC_EAU->CSR_f.ZERO)
    {
        return EauErrZero;
    }
    else if(HC_EAU->CSR_f.OVR)
    {
        return EauErrOverflow;
    }
    else
    {
        return EauOk;
    }
}

/* ========================================================================== */
/*  flash.c                                                                   */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_FLASH FLASH模块驱动库
 * @brief FLASH Driver Library FLASH模块驱动库
 * @{
 */


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FLASH_Local_Macros FLASH局部宏定义
 * @{
 */
/**
 * @defgroup FLASH_Value_Define FLASH模式值设置
 * @{
 */
#define FLASH_END_ADDR              (0x0001FFFFu)
#define FLASH_BYPASS()              do{HC_FLASH->BYPASS = (uint32_t)0x5A5A;\
                                       HC_FLASH->BYPASS = (uint32_t)0xA5A5;}while(0)
#define FLASH_IE_TRUE               (0x03)
#define FLASH_IE_FALSE              (0x00)

#define FLASH_TIMEOUT_INIT          (0xFFFFFFu)
#define FLASH_TIMEOUT_PGM           (0xFFFFFFu)
#define FLASH_TIMEOUT_ERASE         (0xFFFFFFu)

#define FLASH_LOCK_ALL              (0u)
#define FLASH_UNLOCK_ALL            (0xFFFFFFFFu)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FLASH_Local_Types FLASH局部类型定义
 * @{
 */
/**
 * @brief  FLASH OP definition  FLASH操作控制数据类型重定义
 */
typedef enum
{
    FlashOpRead        = 0u,           /*!<  FLASH 读配置值 */
    FlashOpProgram     = 1u,           /*!<  FLASH 编程配置值 */
    FlashOpSectorErase = 2u,           /*!<  FLASH 扇区擦除配置值 */
    FlashOpChipErase   = 3u,           /*!<  FLASH 全片擦除配置值 */
} en_flash_op_t;

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
 * @defgroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */

/**
 * @brief   Flash 整片擦除
 * @note    该函数需要放到RAM中执行
 * @retval  en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
*/

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)

#pragma clang section text = "ramfunc"

en_result_t Flash_Chip_Erase(void)
{
	en_result_t enResult = Ok;
	volatile uint32_t u32TimeOut = FLASH_TIMEOUT_PGM;

	while(FlashOpChipErase != HC_FLASH->CR_f.OP)
	{
		HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		HC_FLASH->CR_f.OP = FlashOpChipErase;

		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

    u32TimeOut = FLASH_TIMEOUT_PGM;
	while(0xFFFFFFFFu != HC_FLASH->SLOCK0)
	{
        HC_FLASH->BYPASS = (uint32_t)0x5A5A;
        HC_FLASH->BYPASS = (uint32_t)0xA5A5;

        HC_FLASH->SLOCK0 = 0xFFFFFFFFu;

		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

    u32TimeOut = FLASH_TIMEOUT_PGM;
	while(0xFFFFFFFFu != HC_FLASH->SLOCK1)
	{
        HC_FLASH->BYPASS = (uint32_t)0x5A5A;
        HC_FLASH->BYPASS = (uint32_t)0xA5A5;

        HC_FLASH->SLOCK1 = 0xFFFFFFFFu;

		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

	*((volatile unsigned int*)0x00000000) = 0;

	u32TimeOut = FLASH_TIMEOUT_PGM;
	while (TRUE == HC_FLASH->IFR_f.BUSY)
	{
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

    u32TimeOut = FLASH_TIMEOUT_PGM;
	while(FlashOpRead != HC_FLASH->CR_f.OP)
	{
		HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		HC_FLASH->BYPASS = (uint32_t)0xA5A5;
		HC_FLASH->CR_f.OP = FlashOpRead;

		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

	enResult = Ok;
	return (enResult);
}


/**
 * @brief  Flash字节连续写 用于向FLASH写入1字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = 0xFFFFFF;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t*)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        u32Addr++;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;
	  }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    enResult = Ok;

    return (enResult);
}

/**
 * @brief  Flash半字连续写 用于向FLASH写入半字（2字节）数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len<<1u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        u32Addr+=2u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
   {
   	  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
     	HC_FLASH->BYPASS = (uint32_t)0xA5A5;

   	  HC_FLASH->CR_f.OP = FlashWriteMode;
   }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    enResult = Ok;
    return (enResult);
}

/**
 * @brief  Flash字连续写 用于向FLASH写入1个字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len<<2u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr+=4u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;
	  }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    enResult = Ok;
    return (enResult);
}

#pragma clang section

#elif defined(__ICCARM__)

__ramfunc 	en_result_t Flash_Chip_Erase(void)
{
	en_result_t enResult = Ok;
	volatile uint32_t u32TimeOut = FLASH_TIMEOUT_PGM;

	while(FlashOpChipErase != HC_FLASH->CR_f.OP)
	{
		HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		HC_FLASH->CR_f.OP = FlashOpChipErase;

		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

	HC_FLASH->BYPASS = (uint32_t)0x5A5A;
	HC_FLASH->BYPASS = (uint32_t)0xA5A5;

	HC_FLASH->SLOCK0 = 0xFFFFFFFFu;

	HC_FLASH->BYPASS = (uint32_t)0x5A5A;
	HC_FLASH->BYPASS = (uint32_t)0xA5A5;

	HC_FLASH->SLOCK1 = 0xFFFFFFFFu;

	if( (0xFFFFFFFFu != HC_FLASH->SLOCK0) || (0xFFFFFFFFu != HC_FLASH->SLOCK1) )
	{
		enResult = Error;
	}

	*((volatile unsigned int*)0x00000000) = 0;

	u32TimeOut = FLASH_TIMEOUT_PGM;
	while (TRUE == HC_FLASH->IFR_f.BUSY)
	{
		if(0u == u32TimeOut--)
		{
			return ErrorTimeout;
		}
	}

	enResult = Ok;
	return (enResult);
}

/**
 * @brief  Flash字节连续写 用于向FLASH写入1字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__ramfunc en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }


    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t*)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr++;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;
	  }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    enResult = Ok;

    return (enResult);
}

/**
 * @brief  Flash半字连续写 用于向FLASH写入半字（2字节）数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__ramfunc en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = 0xFFFFFF;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr+=2u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;
	  }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    enResult = Ok;
    return (enResult);
}

/**
 * @brief  Flash字连续写 用于向FLASH写入1个字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__ramfunc en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = 0xFFFFFF;
    uint32_t                u32Index = 0u;

    if(FlashContWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFF;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr+=4u;
    }

    while(FlashWriteMode != HC_FLASH->CR_f.OP)
	  {
		  HC_FLASH->BYPASS = (uint32_t)0x5A5A;
		  HC_FLASH->BYPASS = (uint32_t)0xA5A5;

		  HC_FLASH->CR_f.OP = FlashWriteMode;
	  }

    /* busy? */
    u32TimeOut = 0xFFFFFF;
    while (HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    enResult = Ok;
    return (enResult);
}

#endif

/**
 * @brief  Flash 编程保护加锁
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_LockAll(void)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->SLOCK0 = FLASH_LOCK_ALL;
    FLASH_BYPASS();
    HC_FLASH->SLOCK1 = FLASH_LOCK_ALL;

    if(FLASH_LOCK_ALL == HC_FLASH->SLOCK0)
    {
        if(FLASH_LOCK_ALL == HC_FLASH->SLOCK1)
        {
            enResult = Ok;
        }
    }

    return enResult;
}

/**
 * @brief  Flash 编程保护解锁
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_UnlockAll(void)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->SLOCK0 = FLASH_UNLOCK_ALL;
    FLASH_BYPASS();
    HC_FLASH->SLOCK1 = FLASH_UNLOCK_ALL;

    if(FLASH_UNLOCK_ALL == HC_FLASH->SLOCK0)
    {
        if(FLASH_UNLOCK_ALL == HC_FLASH->SLOCK1)
        {
            enResult = Ok;
        }
    }

    return enResult;
}

/**
 * @brief  Flash中断标志获取
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t
 * @retval boolean_t:
 *              - TRUE: 标志置位
 *              - FALSE: 标志未置位
 */
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType)
{
    boolean_t bRetVal = FALSE;

    if(HC_FLASH->IFR & enFlashIntType)
    {
        bRetVal =  TRUE;
    }

    return bRetVal;
}

/**
 * @brief  Flash中断标志清除
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    HC_FLASH->ICR &= ~(uint32_t)enFlashIntType;
    enResult = Ok;

    return enResult;
}

/**
 * @brief  Flash中断使能
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_EnableIrq (en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->IER |= enFlashIntType;

    enResult = Ok;

    return enResult;
}

/**
 * @brief  Flash中断禁止
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t
 * @retval en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
 */
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->IER &= ~(uint32_t)enFlashIntType;

    enResult = Ok;

    return enResult;
}


/**
 * @brief  Flash功能设置函数
 * @param  [in] enFunc: Flash 功能设置枚举  @ref en_flash_func_type_t
 * @param  [in] bFlag: bool类型，TRUE or FALSE
 * @retval en_result_t:
 *              - Ok: 设置成功
 *              - Error: 设置失败
 */
en_result_t Flash_FuncSet(en_flash_func_type_t enFunc, boolean_t bFlag)
{
    en_result_t             enResult  = Ok;

    if(TRUE == bFlag)
    {
        FLASH_BYPASS();
        REG_SETBITS(HC_FLASH->CR, enFunc);
    }
    else
    {
        FLASH_BYPASS();
        REG_CLEARBITS(HC_FLASH->CR, (uint32_t)enFunc);
    }

    return (enResult);
}

/**
 * @brief  Flash字节写 用于向FLASH写入1字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 *              - Error: 写入失败
 */
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0u;

    if(FlashWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        if(pu8Data[u32Index] != *((volatile uint8_t*)u32Addr))
        {
            return Error;
        }

        u32Addr++;
    }



    enResult = Ok;
    return (enResult);
}

/**
 * @brief  Flash半字写 用于向FLASH写入半字（2字节）数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 *              - Error: 写入失败
 */
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0u;

    if(FlashWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len<<1u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        if(pu16Data[u32Index] != *((volatile uint16_t*)u32Addr))
        {
            return Error;
        }
        u32Addr+=2u;
    }

    enResult = Ok;
    return (enResult);
}

/**
 * @brief  Flash字写 用于向FLASH写入1个字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 *              - Error: 写入失败
 */
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Error;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0u;

    if(FlashWriteMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len<<2u) - 1u))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for(u32Index=0u; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == HC_FLASH->IFR_f.BUSY)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        if(pu32Data[u32Index] != *((volatile uint32_t*)u32Addr))
        {
            return Error;
        }
        u32Addr+=4u;
    }

    enResult = Ok;
    return (enResult);
}

/**
 * @brief  Flash扇区擦除
 * @param [in]  u32SectorAddr    所擦除扇区内的地址
 * @retval en_result_t:
 *              - Ok: 擦除成功
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_SectorErase(uint32_t u32SectorAddr)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;

    if(FlashSectorEraseMode != HC_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < u32SectorAddr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data */
    *((volatile uint32_t*)u32SectorAddr) = 0u;

    /* busy? */
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == HC_FLASH->IFR_f.BUSY)
    {
        if(0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

/**
 * @brief FLASH 操作模式配置
 *
 * @param [in]  enFlashOpMode    @ref en_flash_op_mode_t
 *
 * @retval Ok                    配置成功
 * @retval Error                 配置失败
 */
en_result_t Flash_OpModeConfig(en_flash_op_mode_t enFlashOpMode)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    HC_FLASH->CR_f.OP = enFlashOpMode;

    if(enFlashOpMode == HC_FLASH->CR_f.OP)
    {
        enResult = Ok;
    }

    return enResult;
}


/**
 * @brief  Flash 读等待周期设置
 * @param [in]  enWaitCycle  插入FLASH读等待周期数枚举类型   @ref en_flash_waitcycle_t
 * @retval en_result_t:
 *              - Ok: 设置成功
 *              - ErrorInvalidParameter: 参数错误
 */
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle)
{
    en_result_t enResult = Ok;

    FLASH_BYPASS();
    HC_FLASH->WAIT_f.WAIT = enWaitCycle;

    return enResult;
}

/**
 * @brief FLASH 低功耗模式配置
 *
 * 该函数用于配置低功耗模式.
 *
 * @param [in] bDpstbEn          TRUE  - 当系统进入DeepSleep模式，FLASH进入低功耗模式;
 *                               FALSE - 当系统进入DeepSleep模式，FLASH不进入低功耗模式;
 *
 * @retval Ok                    操作成功.
 * @retval ErrorInvalidParameter 参数无效.
 * @retval ErrorUninitialized    初始化失败。
 */
en_result_t Flash_EnDpstb(boolean_t bDpstbEn)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;

    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(bDpstbEn != HC_FLASH->CR_f.DPSTBEN)
    {
        FLASH_BYPASS();
        HC_FLASH->CR_f.DPSTBEN = bDpstbEn;

        if(0u == u32TimeOut--)
        {
            enResult = ErrorUninitialized;
            return (enResult);
        }
    }

    enResult = Ok;
    return (enResult);
}


/**
 * @brief  FLASH LOCK 设置
 * @param [in]  enLock  Sector擦写保护寄存器 @ref en_flash_lock_t
 * @param [in]  u32LockValue 32bits，对应bit=0：加锁，对应Sector不允许擦写；对应bit=1：解锁。
 * @note  加解锁范围Sector：[enLock*128 + i*4, enLock*128 + i*4+3]
 *        -i: 表示u32LockValue的bit位置，0~31;
 *        -enLock: 表示枚举编号(FlashLock[n]:n=0~3),并非枚举值;)
 *        例如：enLock = FlashLock1, u32LockValue = 0x00000005,
 *              则FLASH解锁范围为：[Sector128,Sector131]和[Sector136,Sector139]
 * @retval en_result_t:
 *              - Ok: 解锁成功
 */
en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue)
{
    en_result_t enResult = Error;
    volatile uint32_t u32PieAddr;

    u32PieAddr = (uint32_t)(&HC_FLASH->SLOCK0) + (uint32_t)enLock;

    FLASH_BYPASS();
    REG_WRITE(*(volatile uint32_t *)u32PieAddr, u32LockValue);

    if(u32LockValue == *(volatile uint32_t *)u32PieAddr)
    {
        return enResult = Ok;
    }

    return enResult;
}

/**
 * @brief  Flash 获取读保护等级
 * @retval uint8_t:   读保护等级 @ref Flash_Lock_State_Level
 */
uint8_t Flash_ReadProtectLevel(void)
{
    uint8_t u8LevelVal;

    u8LevelVal = (uint8_t)REG_READBITS(HC_FLASH->LOCKST, FLASH_LOCKST_STATE);

    return u8LevelVal;
}

/* ========================================================================== */
/*  gpio.c                                                                    */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_GPIO GPIO模块驱动库
 * @brief GPIO Driver Library GPIO模块驱动库
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


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Variables GPIO局部变量定义
 * @{
 */
/**
 * @brief  引脚位定义.
 */
static const uint32_t au32GpioPinTable[16] = {
                                              0x0001U,  /*!< pin00 */
                                              0x0002U,  /*!< pin01 */
                                              0x0004U,  /*!< pin02 */
                                              0x0008U,  /*!< pin03 */
                                              0x0010U,  /*!< pin04 */
                                              0x0020U,  /*!< pin05 */
                                              0x0040U,  /*!< pin06 */
                                              0x0080U,  /*!< pin07 */
                                              0x0100U,  /*!< pin08 */
                                              0x0200U,  /*!< pin09 */
                                              0x0400U,  /*!< pin10 */
                                              0x0800U,  /*!< pin11 */
                                              0x1000U,  /*!< pin12 */
                                              0x2000U,  /*!< pin13 */
                                              0x4000U,  /*!< pin14 */
                                              0x8000U,  /*!< pin15 */
                                            };
/**
 * @}
 */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Functions GPIO全局函数定义
 * @{
 */

/**
 * @brief  GPIO 初始化
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param [in]  pstcGpioCfg:  IO 配置结构体指针@ref stc_gpio_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_Init(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, stc_gpio_cfg_t  *pstcGpioCfg)
{
    uint32_t val;
    val = au32GpioPinTable[enPin];

    /* 模拟功能清零, 配置为GPIO功能 */
    REG_CLEARBITS(GPIOx->ADS, val);

    if(enPin <= GpioPin7)
    {
        REG_CLEARBITS(GPIOx->AFRL, 0xFu << ((uint32_t)enPin<<2u));
    }
    else
    {
        REG_CLEARBITS(GPIOx->AFRH, 0xFu << (((uint32_t)enPin-8u)<<2u));
    }

    /* 默认输出值配置 */
    REG_MODIFY(GPIOx->OUT, val, ((uint32_t)(pstcGpioCfg->bOutputVal))<<((uint32_t)enPin));

    /* 方向配置 */
    REG_MODIFY(GPIOx->DIR, val, ((uint32_t)(pstcGpioCfg->enDir))<<((uint32_t)enPin));
    /* 驱动能力配置 */
    REG_MODIFY(GPIOx->DRIVER, val, ((uint32_t)(pstcGpioCfg->enDrv))<<((uint32_t)enPin));
    /* 上拉/下拉配置 */
    REG_MODIFY(GPIOx->PUPD, val, ((uint32_t)(pstcGpioCfg->enPu))<<((uint32_t)enPin));
    REG_MODIFY(GPIOx->PUPD, val << 16u, ((uint32_t)pstcGpioCfg->enPd) << ((uint32_t)enPin+16u));
    /* 开漏输出功能 */
    REG_MODIFY(GPIOx->OPENDRAIN, val, ((uint32_t)(pstcGpioCfg->enOD))<<((uint32_t)enPin));

    return Ok;
}

/**
 * @brief  GPIO IO输入值获取
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval boolean_t:
 *           - FALSE: 低电平
 *           - TRUE: 高电平
 */
boolean_t Gpio_GetInputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    return (REG_READBITS(GPIOx->IN, au32GpioPinTable[enPin])) ? TRUE : FALSE;
}

/**
 * @brief  GPIO Port输入数据获取
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 *
 *
 * @retval uint16_t: PORT电平(每bit对应改组一个IO, 1为高电平, 0为低电平)
 */
uint16_t Gpio_GetInputData(GPIO_TypeDef *GPIOx)
{
    return (uint16_t)REG_READ(GPIOx->IN);
}

/**
 * @brief  GPIO PORT整组IO口输出0(低电平)或1(高电平)
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [out] u16Val:        PORT输出值(每bit对应改组一个IO, 1为高电平, 0为低电平)
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_WriteOutputPort(GPIO_TypeDef *GPIOx, uint16_t u16Val)
{
    REG_WRITE(GPIOx->OUT, u16Val);
    return Ok;
}

/**
 * @brief  GPIO IO输出值获取
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval boolean_t:
 *           - FALSE: 低电平
 *           - TRUE: 高电平
 */
boolean_t   Gpio_ReadOutputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    return (REG_READBITS(GPIOx->OUT, au32GpioPinTable[enPin])) ? TRUE : FALSE;
}

/**
 * @brief  GPIO IO Port设置输出1(高电平)，可同时设置一组Port中的多个PIN
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] u16ValMsk:    该Port的16个PIN掩码值,将需要设置的PIN对应的bit写1有效
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk)
{
    REG_WRITE(GPIOx->BSRR, u16ValMsk);

    return Ok;
}

/**
 * @brief  GPIO 单个IO设置输出1(高电平)
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_WRITE(GPIOx->BSRR, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO IO Port清零(低电平)，可同时清零一组Port中的多个PIN
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] u16ValMsk:    该Port的16个PIN掩码值,将需要清零的PIN对应的bit写1有效
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_ClrPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk)
{
    REG_WRITE(GPIOx->BRR, u16ValMsk);

    return Ok;
}

/**
 * @brief  GPIO 单个IO清零(低电平)
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_ClrIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_WRITE(GPIOx->BRR, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO IO Port置位/清零，可同时置位/清零一组Port中的多个PIN
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] u32ValMsk:    高16bits表示该Port的16个PIN清零掩码值,
 *                            低16bits表示该Port的16个PIN置位掩码值,
 *                            将需要设置的PIN对应的bit写1,同一个PIN的掩码同时为1,则该PIN清零。
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetClrPort(GPIO_TypeDef *GPIOx, uint32_t u32ValMsk)
{
    REG_WRITE(GPIOx->BSRR, u32ValMsk);

    return Ok;
}

/**
 * @brief  GPIO IO配置为模拟功能模式
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetAnalogMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_SETBITS(GPIOx->ADS, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO IO复用功能设置
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param  [in] enAf:         复用功能枚举类型选择 @ref en_gpio_af_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetAfMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_af_t enAf)
{
    uint32_t val;

    if(enPin <= GpioPin7)
    {
        val = ((uint32_t)enPin) << 2;
        REG_MODIFY(GPIOx->AFRL, 0x0000000Fu << val, ((uint32_t)enAf) << val);
    }
    else
    {
        val = ((uint32_t)enPin-8u) << 2u;
        REG_MODIFY(GPIOx->AFRH, 0x0000000Fu << val, ((uint32_t)enAf) << val);
    }

    return Ok;
}

/**
 * @brief  GPIO IO中断使能
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param  [in] enType:       中断使能类型 @ref en_gpio_irqtype_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_EnableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = (uint32_t)&GPIOx->HIGHIE + (uint32_t)enType;

    REG_SETBITS(*(volatile uint32_t *)u32PieAddr, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO IO中断关闭
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param  [in] enType:       中断使能类型 @ref en_gpio_irqtype_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_DisableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = (uint32_t)(&GPIOx->HIGHIE) + (uint32_t)enType;

    REG_CLEARBITS(*(volatile uint32_t *)u32PieAddr, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO 获得IO中断状态
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval boolean_t:
 *           - FALSE: 中断请求未产生
 *           - TRUE: 中断请求产生
 */
boolean_t Gpio_GetIrqStatus(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    return REG_READBITS(GPIOx->IFR, au32GpioPinTable[enPin]) ? TRUE : FALSE;
}

/**
 * @brief  GPIO 清除IO中断状态
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_ClearIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_CLEARBITS(GPIOx->ICR, au32GpioPinTable[enPin]);
    return Ok;
}

/**
 * @brief  GPIO 端口辅助功能配置——MCO输出配置
 * @param  [in] ensrc:        MCO输出时钟选择类型定义 @ref en_gpio_sf_mco_src_t
 * @param  [in] endiv:        MCO输出分频选择类型定义 @ref en_gpio_sf_mcoout_div_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfMcoOutputCfg(en_gpio_sf_mco_src_t ensrc,en_gpio_sf_mcoout_div_t endiv)
{
    HC_GPIOAUX->CR0_f.MCOSEL  = ensrc;
    HC_GPIOAUX->CR0_f.MCODIV  = endiv;

    return Ok;
}

/**
 * @brief  GPIO 端口辅助功能配置——PCLK输出配置
 * @param  [in] enDiv:        PCLK输出分频选择类型定义 @ref en_gpio_sf_pclkout_div_t
 *
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_div_t enDiv)
{
    HC_GPIOAUX->CR0_f.PCLKDIV  = enDiv;

    return Ok;
}


/**
 * @brief GPIO 端口辅助功能配置——Timer ETR选择配置
 *
 * @param [in]  enTimE       Timer类型选择枚举
 * @param [in]  enSf         Timer互联功能选择枚举
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf)
{
    REG_MODIFY(HC_GPIOAUX->CR1, GPIOAUX_CR1_ATIM0ETR <<((uint32_t)enTimE), (uint32_t)(((uint32_t)enSf) << ((uint32_t)enTimE)));

    return Ok;
}

/**
 * @brief GPIO 端口辅助功能配置——Timer 捕获输入选择配置
 *
 * @param [in]  enTimC       Timer类型选择枚举
 * @param [in]  enSf         Timer互联功能选择枚举
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf)
{
    REG_MODIFY(HC_GPIOAUX->CR2, GPIOAUX_CR2_ATIM0CAP0 <<((uint32_t)enTimC), (uint32_t)(((uint32_t)enSf) << ((uint32_t)enTimC)));

    return Ok;
}

/* ========================================================================== */
/*  gtim.c                                                                    */
/* ========================================================================== */


/******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_GTIM GTIM模块驱动库
 * @brief GTIM Driver Library GTIM模块驱动库
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
 * @defgroup GTIM_Global_Functions GTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器GTIM的初始化配置
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] pstcInitCfg :                初始化GTIMx的结构体
 * @        pstcInitCfg->u32TaskMode:        定时器计数模式选择  @ref Gtim_Task_Count_Mode
 * @        pstcInitCfg->u32WorkMode:        工作模式            @ref Gtim_Work_Mode
 * @        pstcInitCfg->u32Prescaler:       计数时钟信号分频    @ref Gtim_Clock_Divide
 * @        pstcInitCfg->u32ToggleEn:        Toggle_N和Toggle_P输出使能 @ref Gtim_Tog_Ouput_define
 * @        pstcInitCfg->u32TriggerSource:   触发源选择:                @ref Gtim_Trigger_Source_Sel
 * @        pstcInitCfg->u32ExInputPolarity: 外部输入极性选择           @ref Gtim_ETR_Input_Polarity
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gtim_Init(GTIM_TypeDef* GTIMx, stc_gtim_init_t* pstcInitCfg)
{
    if (NULL == pstcInitCfg)
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY( GTIMx->CR0,\
                     GTIM_CR0_MD\
                            | GTIM_CR0_TOGEN\
                            | GTIM_CR0_PRS\
                            | GTIM_CR0_OST\
                            | GTIM_CR0_TRS\
                            | GTIM_CR0_ETP\
                            , \
                             pstcInitCfg->u32TaskMode
                            | pstcInitCfg->u32WorkMode\
                            | pstcInitCfg->u32Prescaler\
                            | pstcInitCfg->u32ToggleEn\
                            | pstcInitCfg->u32TriggerSource\
                            | pstcInitCfg->u32ExInputPolarity);

    REG_MODIFY( GTIMx->ARR, GTIM_ARR_ARR, (uint16_t)pstcInitCfg->u32AutoReloadVal);

    return Ok;
}

/**
 * @brief  获取GTIM计数器计数值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIMx计数器计数值
 */
uint32_t Gtim_GetCounter(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CNT, GTIM_CNT_CNT));
}

/**
 * @brief  设置GTIM计数器计数值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u16CntValue: 计数值
 *
 * @retval None
 */
void Gtim_SetCounter(GTIM_TypeDef* GTIMx, uint16_t u16CntValue)
{
    REG_WRITE( GTIMx->CNT, (uint32_t)u16CntValue);
}

/**
 * @brief  设定GTIM 重载寄存器的值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u16AutoReload: 重载值
 *
 * @retval None
 */
void Gtim_SetAutoReload(GTIM_TypeDef* GTIMx, uint16_t u16AutoReload)
{
    REG_WRITE(GTIMx->ARR, (uint32_t)u16AutoReload);
}

/**
 * @brief  获取GTIM 重载寄存器的值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIMx重载寄存器的值
 */
uint32_t Gtim_GetAutoReload(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->ARR, GTIM_ARR_ARR));
}

/**
 * @brief  开启定时器GTIM模块
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_Enable(GTIM_TypeDef* GTIMx)
{
    REG_SETBITS( GTIMx->CR0, GTIM_CR0_CEN);
}

/**
 * @brief  禁止定时器GTIM模块
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_Disable(GTIM_TypeDef* GTIMx)
{
    REG_CLEARBITS( GTIMx->CR0, GTIM_CR0_CEN);
}

/**
 * @brief  检查定时器GTIM模块是否已开启
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval boolean_t:
 *           - FALSE: 未开启
 *           - TRUE: 已开启
 */
boolean_t Gtim_IsEnable(GTIM_TypeDef* GTIMx)
{
    return REG_READBITS( GTIMx->CR0, GTIM_CR0_CEN) ? TRUE : FALSE;
}


/**
 * @brief  设定定时器GTIM 工作模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32WorkMode: 选择GTIM工作模式  @ref Gtim_Work_Mode
 *
 * @retval None
 */
void Gtim_SetWorkMode(GTIM_TypeDef* GTIMx, uint32_t u32WorkMode)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_MD, u32WorkMode);
}

/**
 * @brief  获取定时器GTIM 工作模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIM工作模式  @ref Gtim_Work_Mode
 */
uint32_t Gtim_GetWorkMode(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS(GTIMx->CR0, GTIM_CR0_MD));
}

/**
 * @brief  定时器GTIM TOG输出使能，TOGP和TOGN输出相位相反的信号
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_EnableToggle(GTIM_TypeDef* GTIMx)
{
    REG_SETBITS( GTIMx->CR0, GTIM_CR0_TOGEN);
}

/**
 * @brief  定时器GTIM TOG输出禁止，TOGP和TOGN同时输出0
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_DisableToggle(GTIM_TypeDef* GTIMx)
{
    REG_CLEARBITS( GTIMx->CR0, GTIM_CR0_TOGEN);
}

/**
 * @brief  检查定时器GTIM模块 TOG输出 是否已开启
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval boolean_t:
 *           - FALSE: 未开启
 *           - TRUE: 已开启
 */
boolean_t Gtim_IsEnableToggle(GTIM_TypeDef* GTIMx)
{
    return REG_READBITS( GTIMx->CR0, GTIM_CR0_TOGEN) ? TRUE : FALSE;
}

/**
 * @brief  定时器GTIM模块 计数时钟预除频
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32CounterClkDiv: 计数时钟预分频选择  @ref Gtim_Clock_Divide
 *
 * @retval None
 */
void Gtim_SetCounterClkDiv(GTIM_TypeDef* GTIMx, uint32_t u32CounterClkDiv)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_PRS, u32CounterClkDiv);
}

/**
 * @brief  获取定时器GTIM 时钟，此时钟是定时器模块工作时钟，非计数时钟源
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: 计数时钟预分频   @ref Gtim_Clock_Divide
 */
uint32_t Gtim_GetCounterClkDiv(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_PRS));
}


 /**
 * @brief  设定GTIM 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Mode: 计数模式 @ref Gtim_Task_Count_Mode
 *
 * @retval None
 */
void Gtim_SetTaskMode(GTIM_TypeDef* GTIMx, uint32_t u32Mode)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_OST, u32Mode);
}

/**
 * @brief  获取GTIM 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIM计数模式 @ref Gtim_Task_Count_Mode
 */
uint32_t Gtim_GetTaskMode(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_OST));
}

/**
 * @brief  设定定时器GTIM 触发源
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32TriggerSource: 选择GTIM触发源  @ref Gtim_Trigger_Source_Sel
 *
 * @retval None
 */
void Gtim_SetTriggerSource(GTIM_TypeDef* GTIMx, uint32_t u32TriggerSource)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_TRS, u32TriggerSource);
}

/**
 * @brief  获取定时器GTIM 触发源
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIM 触发源  @ref Gtim_Trigger_Source_Sel
 */
uint32_t Gtim_GetTriggerSource(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_TRS));
}



/**
 * @brief  设定定时器GTIM 外部输入ETR极性设定
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32ExInputPolarity: 外部输入ETR极性 @ref Gtim_ETR_Input_Polarity
 *
 * @retval None
 */
void Gtim_SetExInputPolarity(GTIM_TypeDef* GTIMx, uint32_t u32ExInputPolarity)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_ETP, u32ExInputPolarity);
}

/**
 * @brief  获取定时器GTIM 外部输入ETR极性配置
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: 外部输入ETR极性  @ref Gtim_ETR_Input_Polarity
 */
uint32_t Gtim_GetExInputPolarity(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_ETP));
}

/**
 * @brief  设定定时器GTIM 外部输入ETR滤波时间
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32ExInputFilter: 外部输入ETR滤波时间  @ref Gtim_ETP_External_Input_Filter
 *
 * @retval None
 */
void Gtim_SetExInputFilter(GTIM_TypeDef* GTIMx, uint32_t u32ExInputFilter)
{
    REG_MODIFY( GTIMx->CR1, GTIM_CR1_ETRFLT, u32ExInputFilter);
}

/**
 * @brief  获取定时器GTIM 外部输入ETR滤波时间
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: 外部输入ETR滤波时间  @ref Gtim_ETP_External_Input_Filter
 */
uint32_t Gtim_GetExInputFilter(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR1, GTIM_CR1_ETRFLT));
}

/**
 * @brief  定时器GTIM 捕获比较模式选择
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 * @param  [in] u32CaptureMode: 捕获比较模式选择 @ref Gtim_Capture_Compare_Mode_Config
 *
 * @retval None
 */
void Gtim_SetCompareCaptureMode(GTIM_TypeDef* GTIMx, uint32_t u32Channel, uint32_t u32CaptureMode)
{
    REG_MODIFY(GTIMx->CMMR, GTIM_CMMR_CC0M << u32Channel, u32CaptureMode << u32Channel);
}

/**
 * @brief  获取定时器GTIMx 捕获比较模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 *
 * @retval uint32_t: 捕获比较模式 @ref Gtim_Capture_Compare_Mode_Config
 */
uint32_t Gtim_GetCompareCaptureMode(GTIM_TypeDef* GTIMx, uint32_t u32Channel)
{
    return (uint32_t)((REG_READBITS(GTIMx->CMMR, GTIM_CMMR_CC0M << u32Channel)) >> u32Channel);
}

/**
 * @brief  设定GTIM 比较捕获（寄存器）值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 * @param  [in] u32Capture: 16位比较捕获寄存器值
 *
 * @retval None
 */
void Gtim_SetCompareCaptureReg(GTIM_TypeDef* GTIMx, uint32_t u32Channel, uint32_t u32Capture)
{
    uint32_t u32BaseAdress;

    u32BaseAdress =(uint32_t)(&GTIMx->CCR0) + (uint32_t)u32Channel;

    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, GTIM_CCR0_CCR, u32Capture);
}

/**
 * @brief  获取GTIM 比较捕获（寄存器）值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 *
 * @retval uint32_t: 比较捕获寄存器的值
 */
uint32_t Gtim_GetCompareCaptureReg(GTIM_TypeDef* GTIMx, uint32_t u32Channel)
{
    uint32_t u32BaseAdress;

    u32BaseAdress =(uint32_t)(&GTIMx->CCR0) + u32Channel;

    return (uint32_t)(REG_READBITS(*(volatile uint32_t *)u32BaseAdress, GTIM_CCR0_CCR));
}

/**
 * @brief  禁止所有通道比较捕获功能
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_DisableCompareCaptureAll(GTIM_TypeDef* GTIMx)
{
    REG_CLEAR( GTIMx->CMMR);
}

/**
 * @brief  GTIM 中断或触发DMA/ADC使能
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IT: 中断使能控制位  @ref Gtim_Interrupt_TRIG_Enable_Disable
 *
 * @retval None
 */
void Gtim_EnableIT(GTIM_TypeDef* GTIMx, uint32_t u32IT)
{
    REG_SETBITS( GTIMx->IER, u32IT);
}

/**
 * @brief  GTIM 中断禁止
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IT: 中断使能控制位  @ref Gtim_Interrupt_TRIG_Enable_Disable
 *
 * @retval None
 */
void Gtim_DisableIT(GTIM_TypeDef* GTIMx, uint32_t u32IT)
{
    REG_CLEARBITS( GTIMx->IER, u32IT);
}

/**
 * @brief  检查 GTIM 中断是否已使能
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IntEnableTypes  中断使能类型   @ref Gtim_Interrupt_TRIG_Enable_Disable
 *
 * @retval boolean_t:
 *           - FALSE: 未使能
 *           - TRUE: 已使能
 */
boolean_t Gtim_IsEnableIT(GTIM_TypeDef* GTIMx, uint32_t u32IntEnableTypes)
{
    return (REG_READBITS( GTIMx->IER, u32IntEnableTypes) == u32IntEnableTypes) ? TRUE : FALSE;
}


/**
 * @brief  获取 GTIM 中断标志
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IntFlagTypes     中断标志类型  @ref Gtim_Interrupt_Flag
 *
 * @retval boolean_t:
 *           - FALSE: 未置起
 *           - TRUE: 已置起
 */
boolean_t Gtim_IsActiveFlag(GTIM_TypeDef* GTIMx, uint32_t u32IntFlagTypes)
{
    return (REG_READBITS(GTIMx->IFR, u32IntFlagTypes) == u32IntFlagTypes) ? TRUE : FALSE;
}


/**
 * @brief  清除 GTIM 中断 标志位
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IntClrFlag      中断清除标志定义 @ref Gtim_Interrupt_Clear_Types
 *
 * @retval None
 */
void Gtim_ClearFlag(GTIM_TypeDef* GTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS( GTIMx->ICR, u32IntClrFlag);
}

/* ========================================================================== */
/*  i2c.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_I2C I2C模块驱动库
 * @brief I2C Driver Library I2C模块驱动库
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
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup I2C_Local_Functions I2C局部函数定义
 * @{
 */
 static en_result_t I2C_SetBaud(I2C_TypeDef* I2Cx, uint8_t u8Tm);
/**
 * @}
 */
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup I2C_Local_Functions I2C局部函数定义
 * @{
 */

/**
 * @brief  I2C设置波特率配置寄存器.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] u8Tm: 波特率配置值
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
 static en_result_t I2C_SetBaud(I2C_TypeDef* I2Cx, uint8_t u8Tm)
 {
     en_result_t enRet = Error;

     I2Cx->TM = u8Tm;

     enRet = Ok;
     return enRet;
 }
/**
 * @}
 */


/**
 * @defgroup I2C_Global_Functions I2C全局函数定义
 * @{
 */

/**
 * @brief  I2C功能设置相关函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] enFunc: 功能参数 @ref en_i2c_func_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
en_result_t I2C_SetFunc(I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
{
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, (uint32_t)enFunc, TRUE);

    enRet = Ok;
    return enRet;
}

/**
 * @brief  I2C功能清除相关函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] enFunc: 功能参数 @ref en_i2c_func_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - Error: 配置失败
 */
 en_result_t I2C_ClearFunc(I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
 {
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, (uint32_t)enFunc, FALSE);

    enRet = Ok;
    return enRet;
 }


/**
 * @brief  I2C获取中断标记函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t I2C_GetIrq(I2C_TypeDef* I2Cx)
{
    if(I2Cx->CR&0x8u)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/**
 * @brief  I2C清除中断标记函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 */
en_result_t I2C_ClearIrq(I2C_TypeDef* I2Cx)
{
    en_result_t enRet = Error;

    I2Cx->CR &= ~0x8u;

    enRet = Ok;
    return enRet;
}

/**
 * @brief  I2C获取相关状态.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval uint8_t: I2C状态
 */
uint8_t I2C_GetState(I2C_TypeDef* I2Cx)
{
    uint8_t u8State = 0u;

    u8State = (uint8_t)I2Cx->STAT;

    return u8State;
}


/**
 * @brief  字节数据写函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] u8Data: 数据
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 */
en_result_t I2C_WriteByte(I2C_TypeDef* I2Cx, uint8_t u8Data)
{
    en_result_t enRet = Error;

    I2Cx->DATA = u8Data;

    enRet = Ok;
    return enRet;
}

/**
 * @brief  字节数据读函数.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @retval uint8_t: 数据
 */
uint8_t I2C_ReadByte(I2C_TypeDef* I2Cx)
{
    uint8_t u8Data = 0u;

    u8Data = (uint8_t)I2Cx->DATA;

    return u8Data;
}


/**
 * @brief  I2C模块初始化.
 * @param  [in] I2Cx: I2C模块单元指针 HC_I2C0 或者 HC_I2C1
 * @param  [in] pstcI2CCfg: 初始化结构体指针 @ref stc_i2c_cfg_t
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 */
en_result_t I2C_Init(I2C_TypeDef* I2Cx, stc_i2c_cfg_t *pstcI2CCfg)
{
   en_result_t enRet = Error;
   uint8_t     u8Tm;

   if(HC_I2C0 == I2Cx)
   {
       HC_SYSCTRL->PERIRESET0 &= ~(uint32_t)0x10u;
       HC_SYSCTRL->PERIRESET0 |= (uint32_t)0x10u;
   }
   else
   {
       HC_SYSCTRL->PERIRESET0 &= ~(uint32_t)0x20u;
       HC_SYSCTRL->PERIRESET0 |= (uint32_t)0x20u;
   }

   I2Cx->CR = 0u;
   I2Cx->CR = pstcI2CCfg->enMode;

   if((pstcI2CCfg->u32Baud<<4) > pstcI2CCfg->u32Pclk)
   {
        return Error;
   }

   if(I2cMasterMode == pstcI2CCfg->enMode)
   {
        I2Cx->TMRUN = TRUE;
        /* Fsck = Fpclk/8*(Tm+1) */
        u8Tm = (uint8_t)((pstcI2CCfg->u32Pclk / pstcI2CCfg->u32Baud) >> 3u) - 1u;
        if(9u > u8Tm)
        {
            I2C_SetFunc(I2Cx,I2cHlm_En);
        }
        enRet = I2C_SetBaud(I2Cx, u8Tm);
   }
   else
   {
        I2Cx->TMRUN = FALSE;
        pstcI2CCfg->u8SlaveAddr = (uint8_t)(((uint32_t)pstcI2CCfg->u8SlaveAddr<<1)|(pstcI2CCfg->bGc));
        I2Cx->ADDR0 = pstcI2CCfg->u8SlaveAddr;
   }

   return enRet;
}

/* ========================================================================== */
/*  i2cslv.c                                                                  */
/* ========================================================================== */


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_I2CSLV I2CSLV模块驱动库
 * @brief I2CSLV Driver Library I2CSLV模块驱动库
 * @{
 */

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/

/*******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/

/*******************************************************************************
* Local function prototypes ('static')
******************************************************************************/

/*******************************************************************************
* Local variable definitions ('static')
******************************************************************************/

/*******************************************************************************
* Function implementation - global ('extern') and local ('static')
******************************************************************************/
/**
 * @defgroup I2CSLV_Global_Functions I2CSLV全局函数定义
 * @{
 */

/**
 * @brief  I2CSLV模块主机初始化
 *
 * @param  [in] pstcInitCfg: I2CSLV 初始化结构体
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 *
 */
en_result_t I2CSLV_Init(stc_i2cslv_init_cfg_t *pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

	if (pstcInitCfg->u32TimeOut > 0) /* 需要配置SCL低电平超时 */
    {
		REG_MODIFY(HC_I2CSLV->CR,
					 I2CSLV_CR_FSCLC
				   | I2CSLV_CR_TIMEOUT
				   | I2CSLV_CR_GC
				   | I2CSLV_CR_DMATE
				   | I2CSLV_CR_DMARE
				   ,
					 pstcInitCfg->u32HSMODE
				   | I2CSLV_CR_TIMEOUT
				   | pstcInitCfg->u32Broadcast
				   | pstcInitCfg->u32DMAReq);

		HC_I2CSLV->TOR = pstcInitCfg->u32TimeOut;  /* 设定SCL低电平超时长度值 */
    }else   /* SCL低电平可以无限时间拉低 */
	{
		REG_MODIFY(HC_I2CSLV->CR,
					 I2CSLV_CR_FSCLC
				   | I2CSLV_CR_TIMEOUT
				   | I2CSLV_CR_GC
				   | I2CSLV_CR_DMATE
				   | I2CSLV_CR_DMARE
				   ,
					 pstcInitCfg->u32HSMODE
				   | pstcInitCfg->u32Broadcast
				   | pstcInitCfg->u32DMAReq);
	}

    /* SDA由0变1时总线驱动能力配置 */
    HC_I2CSLV->ODDR = pstcInitCfg->u32DriveStrength;

	/* 接收采样位置配置 */
    HC_I2CSLV->RSR  = pstcInitCfg->u32RxSampleDot;

	/* SDA和SCL输入滤波宽度配置 */
    HC_I2CSLV->FLT  = pstcInitCfg->u32Filter;

	/* 从机地址0配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr0)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR0 = (0x7F & (pstcInitCfg->u32SlaveAddr0));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR0 = I2CSLV_SLADR0_AM | (0x3FF & (pstcInitCfg->u32SlaveAddr0));
	}
	/* 从机地址0掩码配置 */
	HC_I2CSLV->ADMR0 = pstcInitCfg->u32SlaveAddr0Mask | pstcInitCfg->u32AddrClkForceStretch;

	/* 从机地址1配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr1)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR1 = (0x7F & (pstcInitCfg->u32SlaveAddr1));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR1 = I2CSLV_SLADR1_AM | (0x3FF & (pstcInitCfg->u32SlaveAddr1));
	}

	/*  从机地址2配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr2)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR2 = (0x7F & (pstcInitCfg->u32SlaveAddr2));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR2 = I2CSLV_SLADR2_ADDRLEN | (0x3FF & (pstcInitCfg->u32SlaveAddr2));
	}

	/* 从机地址3配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr3)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR3 = (0x7F & (pstcInitCfg->u32SlaveAddr3));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR3 = I2CSLV_SLADR3_ADDRLEN | (0x3FF & (pstcInitCfg->u32SlaveAddr3));
	}

    return Ok;
}


/**
 * @brief  使能 I2CSLV 模块
 *
 * @retval None
 */
void I2CSLV_Enable(void)
{
	REG_SETBITS(HC_I2CSLV->CR, I2CSLV_CR_EN);
}

/**
 * @brief  禁止 I2CSLV 模块
 *
 * @retval None
 */
void I2CSLV_Disable(void)
{
	REG_CLEARBITS(HC_I2CSLV->CR, I2CSLV_CR_EN);
}

/**
 * @brief  检查I2CSLV 模块 是否已开启
 *
 * @retval uint32_t:
 *               - 0：未开启；
 *               -非0：已开启
 */
uint32_t I2CSLV_IsEnable(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_EN) == I2CSLV_CR_EN);
}

/**
 * @brief  I2CSLV 从机响应主机配置
 * @param  [in] u32Ack: 从机响应配置 @ref I2CSLV_ACK_SELECTION
 *              - I2CSLV_ACK    从机响应主机，主机收到ACK
 *              - I2CSLV_NACK   从机不响应主机，主机收到NACK
 *
 * @retval None
 */
void I2CSLV_SetAck(uint32_t u32Ack)
{
	REG_MODIFY(HC_I2CSLV->CR, I2CSLV_CR_BUSY, u32Ack);
}

/**
 * @brief  获取 I2CSLV 从机响应主机配置
 *
 * @retval uint32_t: 从机响应配置 @ref I2CSLV_ACK_SELECTION
 *               - I2CSLV_ACK    从机响应主机，主机收到ACK
 *               - I2CSLV_NACK   从机不响应主机，主机收到NACK
 *
 */
uint32_t I2CSLV_GetAck(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_BUSY));
}

/**
 * @brief  I2CSLV 配置高速模式下，地址匹配后，如果I2CSLV_DOUTR没有数据，是否强制延迟SCL低电平
 * @param  [in] u32ClkForceStretch: 高速模式控制 @ref I2CSLV_HIGH_SPEED_MODE_SELECTION
 *              - I2CSLV_HIGH_SPEED_MODE_DISABLE  I2CSLV_DOUTR没有数据时强制SCL电平延长
 *              - I2CSLV_HIGH_SPEED_MODE_ENABLE   I2CSLV_DOUTR没有数据时不强制SCL电平延长，回复NACK
 *
 * @retval None
 *
 */
void I2CSLV_SetHsmodeForceStretch(uint32_t u32ClkForceStretch)
{
	REG_MODIFY(HC_I2CSLV->CR, I2CSLV_CR_FSCLC, u32ClkForceStretch);
}

/**
 * @brief  获取 I2CSLV 配置高速模式下，地址匹配后，如果I2CSLV_DOUTR没有数据，是否强制延迟SCL低电平
 *
 * @retval uint32_t: 高速模式控制 @ref I2CSLV_HIGH_SPEED_MODE_SELECTION
 *              - I2CSLV_HIGH_SPEED_MODE_DISABLE  I2CSLV_DOUTR没有数据时强制SCL电平延长
 *              - I2CSLV_HIGH_SPEED_MODE_ENABLE   I2CSLV_DOUTR没有数据时不强制SCL电平延长，回复NACK
 *
 */
uint32_t I2CSLV_GetHsmodeForceStretch(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_FSCLC));
}

/**
 * @brief  使能 I2CSLV 广播地址
 *
 * @retval None
 */
void I2CSLV_EnableBroadcast(void)
{
	REG_SETBITS(HC_I2CSLV->CR, I2CSLV_CR_GC);
}

/**
 * @brief  禁止 I2CSLV 广播地址
 *
 * @retval None
 */
void I2CSLV_DisableBroadcast(void)
{
	REG_CLEARBITS(HC_I2CSLV->CR, I2CSLV_CR_GC);
}

/**
 * @brief  检查I2CSLV 广播地址 是否已开启
 *
 * @retval uint32_t:
 *         - 0: 未开启
 *         - 非0: 已开启
 */
uint32_t I2CSLV_IsEnableBroadcast(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_GC) == I2CSLV_CR_GC);
}

/**
 * @brief  I2CSLV 从机DMA请求配置
 * @param  [in] u32DmaReq: 从机DMA请求配置 @ref I2CSLV_DMA_REQUEST_SELECTION
 *              - I2CSLV_DMA_REQUEST_RX_TX_DISABLE 从机TX RX DMA请求禁止
 *              - I2CSLV_DMA_REQUEST_RX_ENABLE     从机RX DMA请求使能
 *              - I2CSLV_DMA_REQUEST_TX_ENABLE     从机TX DMA请求使能
 *              - I2CSLV_DMA_REQUEST_RX_TX_ENABLE  从机TX RX DMA请求使能

 * @retval None
 *
 */
void I2CSLV_SetDMAReq(uint32_t u32DmaReq)
{
	REG_MODIFY(HC_I2CSLV->CR, (I2CSLV_CR_DMARE | I2CSLV_CR_DMATE), u32DmaReq);
}

/**
 * @brief  获取 I2CSLV 从机DMA请求配置
 *
 * @retval uint32_t:从机DMA请求配置 @ref I2CSLV_DMA_REQUEST_SELECTION
 *         - I2CSLV_DMA_REQUEST_RX_TX_DISABLE 从机TX RX DMA请求禁止
 *         - I2CSLV_DMA_REQUEST_RX_ENABLE     从机RX DMA请求使能
 *         - I2CSLV_DMA_REQUEST_TX_ENABLE     从机TX DMA请求使能
 *         - I2CSLV_DMA_REQUEST_RX_TX_ENABLE  从机TX RX DMA请求使能
 *
 */
uint32_t I2CSLV_GetDMAReq(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, (I2CSLV_CR_DMARE | I2CSLV_CR_DMATE)));
}

/**
 * @brief  使能 I2CSLV模块 某一个特定的中断
 * @param  [in] u32IrqCfg: 中断配置 @ref I2CSLV_IT_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_IT_RD
 *         - I2CSLV_IT_WR
 *         - I2CSLV_IT_STOP
 *         - I2CSLV_IT_START
 *         - I2CSLV_IT_NACK
 *         - I2CSLV_IT_I2CINT
 *         - I2CSLV_IT_ACTIVE
 *         - I2CSLV_IT_HSMODE
 *         - I2CSLV_IT_TIMEOUT
 *         - I2CSLV_IT_ACK
 *         - I2CSLV_IT_SLADDR0
 *         - I2CSLV_IT_SLADDR1
 *         - I2CSLV_IT_SLADDR2
 *         - I2CSLV_IT_SLADDR3
 *         - I2CSLV_IT_TXE
 *         - I2CSLV_IT_RXNE
 *         - I2CSLV_IT_GC
 *
 * @retval None
 */
void I2CSLV_EnableIT(uint32_t u32IrqCfg)
{
	REG_SETBITS(HC_I2CSLV->IER, u32IrqCfg);
}

/**
 * @brief  禁止 I2CSLV模块 某一个特定的中断
 * @param  [in] u32IrqCfg: 中断配置 @ref I2CSLV_IT_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_IT_RD
 *         - I2CSLV_IT_WR
 *         - I2CSLV_IT_STOP
 *         - I2CSLV_IT_START
 *         - I2CSLV_IT_NACK
 *         - I2CSLV_IT_I2CINT
 *         - I2CSLV_IT_ACTIVE
 *         - I2CSLV_IT_HSMODE
 *         - I2CSLV_IT_TIMEOUT
 *         - I2CSLV_IT_ACK
 *         - I2CSLV_IT_SLADDR0
 *         - I2CSLV_IT_SLADDR1
 *         - I2CSLV_IT_SLADDR2
 *         - I2CSLV_IT_SLADDR3
 *         - I2CSLV_IT_TXE
 *         - I2CSLV_IT_RXNE
 *         - I2CSLV_IT_GC
 *
 * @retval None
 */
void I2CSLV_DisableIT(uint32_t u32IrqCfg)
{
	REG_CLEARBITS(HC_I2CSLV->IER, u32IrqCfg);
}

/**
 * @brief  检查I2CSLVx模块 某一个特定的中断 是否已开启
 * @param  [in] u32IrqCfg: 中断配置 @ref I2CSLV_IT_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_IT_RD
 *         - I2CSLV_IT_WR
 *         - I2CSLV_IT_STOP
 *         - I2CSLV_IT_START
 *         - I2CSLV_IT_NACK
 *         - I2CSLV_IT_I2CINT
 *         - I2CSLV_IT_ACTIVE
 *         - I2CSLV_IT_HSMODE
 *         - I2CSLV_IT_TIMEOUT
 *         - I2CSLV_IT_ACK
 *         - I2CSLV_IT_SLADDR0
 *         - I2CSLV_IT_SLADDR1
 *         - I2CSLV_IT_SLADDR2
 *         - I2CSLV_IT_SLADDR3
 *         - I2CSLV_IT_TXE
 *         - I2CSLV_IT_RXNE
 *         - I2CSLV_IT_GC
 *
 * @retval uint32_t:
 *         - 0：未开启;
 *         - 非0：已开启
 */
uint32_t I2CSLV_IsEnableIT(uint32_t u32IrqCfg)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->IER, u32IrqCfg) == u32IrqCfg);
}

/**
 * @brief  获取 I2CSLVx 中断标志
 * @param  [in] u32IrqFlag: 中断标记 @ref I2CSLV_FLAG_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_FLAG_RD
 *         - I2CSLV_FLAG_WR
 *         - I2CSLV_FLAG_STOP
 *         - I2CSLV_FLAG_START
 *         - I2CSLV_FLAG_NACK
 *         - I2CSLV_FLAG_I2CINT
 *         - I2CSLV_FLAG_ACTIVE
 *         - I2CSLV_FLAG_HSMODE
 *         - I2CSLV_FLAG_TIMEOUT
 *         - I2CSLV_FLAG_ACK
 *         - I2CSLV_FLAG_SLADDR0
 *         - I2CSLV_FLAG_SLADDR1
 *         - I2CSLV_FLAG_SLADDR2
 *         - I2CSLV_FLAG_SLADDR3
 *         - I2CSLV_FLAG_TXE
 *         - I2CSLV_FLAG_RXNE
 *         - I2CSLV_FLAG_GC
 *
 * @retval uint32_t:
 *         - 0: 未检测到所查询的中断标志
 *         - 1: 已检测到所查询的中断标志
 */
uint32_t I2CSLV_IsActiveFlag(uint32_t u32IrqFlag)
{
	return (REG_READBITS(HC_I2CSLV->SR, u32IrqFlag) == u32IrqFlag);
}

/**
 * @brief  获取 I2CSLV 状态寄存器
 *
 * @retval uint32_t: I2CSLV所有状态标志位
 */
uint32_t I2CSLV_GetState(void)
{
	return (uint32_t)(0xFFFF & (HC_I2CSLV->SR));
}

/**
 * @brief  清除 I2CSLVx 逻辑单元 中断标志
 * @param  [in] u32IrqFlag: 中断标记 @ref I2CSLV_FLAG_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_FLAG_RD
 *         - I2CSLV_FLAG_WR
 *         - I2CSLV_FLAG_STOP
 *         - I2CSLV_FLAG_START
 *         - I2CSLV_FLAG_NACK
 *         - I2CSLV_FLAG_I2CINT
 *         - I2CSLV_FLAG_ACTIVE
 *         - I2CSLV_FLAG_HSMODE
 *         - I2CSLV_FLAG_TIMEOUT
 *         - I2CSLV_FLAG_ACK
 *         - I2CSLV_FLAG_SLADDR0
 *         - I2CSLV_FLAG_SLADDR1
 *         - I2CSLV_FLAG_SLADDR2
 *         - I2CSLV_FLAG_SLADDR3
 *         - I2CSLV_FLAG_TXE
 *         - I2CSLV_FLAG_RXNE
 *         - I2CSLV_FLAG_GC
 *
 * @retval None
 */
void I2CSLV_ClearFlag(uint32_t u32IrqFlag)
{
	REG_CLEARBITS(HC_I2CSLV->ICR, u32IrqFlag);
}

/**
 * @brief  清除 I2CSLVx 所有 中断标志
 *
 * @retval None
 */
void I2CSLV_ClearFlag_ALL(void)
{
	HC_I2CSLV->ICR = I2CSLV_SR_TXE;	/* ICR.TXE不能写零，否则TXE标记会置一 */
}

/**
 * @brief  设置 I2CSLVx TXE标记为1
 *
 * @retval None
 */
void I2CSLV_SetFlag_TXE(void)
{
	REG_CLEARBITS(HC_I2CSLV->ICR, I2CSLV_SR_TXE);
}

 /**
 * @brief  设置 I2CSLV device ID
 * @param  [in] u32RID: 修订标识
 * @param  [in] u32PID: 零件标识
 * @param  [in] u32MID: 制造商标识
 *
 * @retval None
 */
void I2CSLV_SetDeviceID(uint32_t u32RID, uint32_t u32PID, uint32_t u32MID)
{
	HC_I2CSLV->DIDR = ((u32MID<<12) | (u32PID<<3) | u32RID);
}

/**
 * @brief  获取 I2CSLV device ID
 *
 * @retval uint32_t:device ID: bit[2:0]RID, bit[11:3]PID, bit[23:12]RID
 *
 */
uint32_t I2CSLV_GetDeviceID(void)
{
	return (uint32_t)((HC_I2CSLV->DIDR)&0xFFFFFF);
}

/**
 * @brief  设置 I2CSLV 接收采样位置
 * @param  [in] u32SampleDot: 接收采样位置 @ref I2CSLV_RX_SAMPLE_DOT_SELECTION
 *              - I2CSLV_RX_SAMPLE_DOT_0CYCLE   SCL下降沿时采样
 *              - I2CSLV_RX_SAMPLE_DOT_1CYCLE   从SCL下降沿往回计时，第1个PCLK采样
 *              - I2CSLV_RX_SAMPLE_DOT_2CYCLE   从SCL下降沿往回计时，第2个PCLK采样
 *              - I2CSLV_RX_SAMPLE_DOT_3CYCLE   从SCL下降沿往回计时，第3个PCLK采样
 *
 * @retval None
 */
void I2CSLV_SetRxSampleDot(uint32_t u32SampleDot)
{
	REG_MODIFY(HC_I2CSLV->RSR, I2CSLV_RSR_NS, u32SampleDot);
}

/**
 * @brief  获取 I2CSLV 接收采样位置
 *
 * @retval uint32_t: 接收采样位置 @ref I2CSLV_RX_SAMPLE_DOT_SELECTION
 *         - I2CSLV_RX_SAMPLE_DOT_0CYCLE   SCL下降沿时采样
 *         - I2CSLV_RX_SAMPLE_DOT_1CYCLE   从SCL下降沿往回计时，第1个PCLK采样
 *         - I2CSLV_RX_SAMPLE_DOT_2CYCLE   从SCL下降沿往回计时，第2个PCLK采样
 *         - I2CSLV_RX_SAMPLE_DOT_3CYCLE   从SCL下降沿往回计时，第3个PCLK采样
 *
 */
uint32_t I2CSLV_GetRxSampleDot(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->RSR, I2CSLV_RSR_NS));
}

/**
 * @brief  I2CSLV SDA由0变1时总线驱动能力配置
 * @param  [in] u32HighDrive: 驱动能力配置 @ref I2CSLV_HIGH_DRIVE_SELECTION
 *              - I2CSLV_HIGH_DRIVE_NONE    由外部上拉电阻拉高，无强驱
 *              - I2CSLV_HIGH_DRIVE_1PCLK   输出1个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *              - I2CSLV_HIGH_DRIVE_2PCLK   输出2个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *              - I2CSLV_HIGH_DRIVE_4PCLK   输出4个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *
 * @retval None
 */
void I2CSLV_SetDriveStrength(uint32_t u32HighDrive)
{
	REG_MODIFY(HC_I2CSLV->ODDR, I2CSLV_ODDR_ODPU, u32HighDrive);
}

/**
 * @brief  获取 I2CSLV SDA由0变1时总线驱动能力配置
 *
 * @retval uint32_t: 驱动能力配置 @ref I2CSLV_HIGH_DRIVE_SELECTION
 *         - I2CSLV_HIGH_DRIVE_NONE    由外部上拉电阻拉高，无强驱
 *         - I2CSLV_HIGH_DRIVE_1PCLK   输出1个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *         - I2CSLV_HIGH_DRIVE_2PCLK   输出2个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *         - I2CSLV_HIGH_DRIVE_4PCLK   输出4个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *
 */
uint32_t I2CSLV_GetDriveStrength(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->ODDR, I2CSLV_ODDR_ODPU));
}

/**
 * @brief  I2CSLV SCL低电平超时配置，只有CR.EN=0时可配置
 * @param  [in] u32TimeOver: 超时长度设置，超时时间=(u32TimeOver+1)*64*(1/pclk)
 *
 * @retval None
 */
void I2CSLV_SetTimeOut(uint32_t u32TimeOver)
{
	if (u32TimeOver == 0) /*  关闭超时功能 */
	{
		REG_CLEARBITS(HC_I2CSLV->CR, I2CSLV_CR_TIMEOUT);         /*   禁止SCL低电平超时功能 */
	}else
	{
		REG_SETBITS(HC_I2CSLV->CR, I2CSLV_CR_TIMEOUT);           /*  使能SCL低电平超时功能 */
	    REG_MODIFY(HC_I2CSLV->TOR, I2CSLV_TOR_TOR, u32TimeOver); /*  配置超时时长 */
	}
}

/**
 * @brief  获取 I2CSLV SCL低电平超时配置
 *
 * @retval uint32_t: 超时长度,长度与时间关系：时间=(TOR+1)*64*(1/pclk)
 *
 */
uint32_t I2CSLV_GetTimeOut(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->TOR, I2CSLV_TOR_TOR));
}

/**
 * @brief  I2CSLV SDA和SCL输入滤波宽度设置
 * @param  [in] u32Filter: 滤波宽度 @ref I2CSLV_FILTER_SELECTION
 *              - I2CSLV_FILTER_NONE    无滤波
 *              - I2CSLV_FILTER_1PCLK   1个PCLK宽度的滤波
 *              - I2CSLV_FILTER_2PCLK   2个PCLK宽度的滤波
 *              - I2CSLV_FILTER_3PCLK   3个PCLK宽度的滤波
 *              - I2CSLV_FILTER_4PCLK   4个PCLK宽度的滤波
 *              - I2CSLV_FILTER_8PCLK   8个PCLK宽度的滤波
 *              - I2CSLV_FILTER_12PCLK  12个PCLK宽度的滤波
 *              - I2CSLV_FILTER_16PCLK  16个PCLK宽度的滤波
 * @retval None
 */
void I2CSLV_SetFilter(uint32_t u32Filter)
{
	REG_MODIFY(HC_I2CSLV->FLT, I2CSLV_FLT_FW, u32Filter);
}

/**
 * @brief  获取 I2CSLV SDA和SCL输入滤波宽度
 * @retval uint32_t: 滤波宽度 @ref I2CSLV_FILTER_SELECTION
 *         - I2CSLV_FILTER_NONE    无滤波
 *         - I2CSLV_FILTER_1PCLK   1个PCLK宽度的滤波
 *         - I2CSLV_FILTER_2PCLK   2个PCLK宽度的滤波
 *         - I2CSLV_FILTER_3PCLK   3个PCLK宽度的滤波
 *         - I2CSLV_FILTER_4PCLK   4个PCLK宽度的滤波
 *         - I2CSLV_FILTER_8PCLK   8个PCLK宽度的滤波
 *         - I2CSLV_FILTER_12PCLK  12个PCLK宽度的滤波
 *         - I2CSLV_FILTER_16PCLK  16个PCLK宽度的滤波
 *
 */
uint32_t I2CSLV_GetFilter(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->FLT, I2CSLV_FLT_FW));
}

/**
 * @brief  I2CSLV 从机地址设置
 * @param  [in] u32AddrNum: 从机地址号 @ref I2CSLV_ADDR_SELECTION
 *         - I2CSLV_ADDR0   从机地址0
 *         - I2CSLV_ADDR1   从机地址1
 *         - I2CSLV_ADDR2   从机地址2
 *         - I2CSLV_ADDR3   从机地址3
 * @param  [in] u32AddrLength: 地址长度
 *         - I2CSLV_ADDR_LENGTH_7BIT    7位地址长度
 *         - I2CSLV_ADDR_LENGTH_10BIT   10位地址长度
 * @param  [in] u32Addr: 从机地址0
 *
 * @retval None
 */
void I2CSLV_SetAddress(uint32_t u32AddrNum, uint32_t u32AddrLength, uint32_t u32Addr)
{
	REG_MODIFY(*(&HC_I2CSLV->SLADR0 + u32AddrNum), (I2CSLV_SLADR0_AM | I2CSLV_SLADR0_ADDR), (u32AddrLength | (0x3FF&u32Addr)));
}

/**
 * @brief  获取 I2CSLV 从机地址
 * @param  [in] u32AddrNum: 从机地址号 @ref I2CSLV_ADDR_SELECTION
 *         - I2CSLV_ADDR0   从机地址0
 *         - I2CSLV_ADDR1   从机地址1
 *         - I2CSLV_ADDR2   从机地址2
 *         - I2CSLV_ADDR3   从机地址3
 *
 * @retval uint32_t: 从机地址
 */
uint32_t I2CSLV_GetAddress(uint32_t u32AddrNum)
{
	if ((*(&HC_I2CSLV->SLADR0 + u32AddrNum) & I2CSLV_SLADR0_AM) != 0)  /*  10位地址长度 */
	{
		return (uint32_t)(0x3FF & (REG_READBITS(*(&HC_I2CSLV->SLADR0 + u32AddrNum), I2CSLV_SLADR0_ADDR)));
	}else
	{
		return (uint32_t)(0x7F & (REG_READBITS(*(&HC_I2CSLV->SLADR0 + u32AddrNum), I2CSLV_SLADR0_ADDR)));
	}
}

/**
 * @brief  获取 I2CSLV 从机地址0长度
 * @param  [in] u32AddrNum: 从机地址号 @ref I2CSLV_ADDR_SELECTION
 *         - I2CSLV_ADDR0   从机地址0
 *         - I2CSLV_ADDR1   从机地址1
 *         - I2CSLV_ADDR2   从机地址2
 *         - I2CSLV_ADDR3   从机地址3
 *
 * @retval uint32_t: 从机地址长度
 */
uint32_t I2CSLV_GetAddressLength(uint32_t u32AddrNum)
{
	return (uint32_t)(0x3FF & (REG_READBITS(*(&HC_I2CSLV->SLADR0 + u32AddrNum), I2CSLV_SLADR0_AM)));
}

/**
 * @brief  I2CSLV 从机地址0屏蔽码设置
 * @param  [in] u32Address0Mask: 从机地址0屏蔽码 10bit有效位
 *
 * @retval None
 */
void I2CSLV_SetAddress0Mask(uint32_t u32Address0Mask)
{
	REG_MODIFY(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_ADDRMASK, u32Address0Mask);
}

/**
 * @brief  获取 I2CSLV 从机地址0屏蔽码
 *
 * @retval uint32_t: 从机地址0屏蔽码
 *
 */
uint32_t I2CSLV_GetAddress0Mask(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_ADDRMASK));
}

/**
 * @brief  获取 I2CSLV 已接收地址
 *
 * @retval uint32_t: 已接收地址
 */
uint32_t I2CSLV_GetReceivedAddr(void)
{
	if ((HC_I2CSLV->ADIR & I2CSLV_ADIR_ADRLEN) != 0)  /*  10位地址长度 */
	{
		return (uint32_t)(0x3FF & (REG_READBITS(HC_I2CSLV->ADIR, I2CSLV_ADIR_ADIR)));
	}else                                           /*  7位地址长度 */
	{
		return (uint32_t)(0x7F & (REG_READBITS(HC_I2CSLV->ADIR, I2CSLV_ADIR_ADIR)));
	}
}

/**
 * @brief  获取 I2CSLV 已接收地址长度
 *
 * @retval uint32_t:已接收地址长度
 */
uint32_t I2CSLV_GetReceivedAddrLength(void)
{
	return (uint32_t)(0x3FF & (REG_READBITS(HC_I2CSLV->ADIR, I2CSLV_ADIR_ADRLEN)));
}

/**
 * @brief  I2CSLV 地址时钟强制延长，在地址匹配并回复ACK后，控制时钟是否强制延长。如果使能，
 *         在回复地址字节的ACK后时钟拉低延长（并且SR.I2CINT置位），等到手动清零SR.I2CINT才释放。
 * @param  [in] u32ClkForceStretch: 配置是否时钟延长 @ref I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION
 *              - I2CSLV_ADDR_CLOCK_FORCE_STRETCH_DISABLE  地址匹配后时钟不强制SCL电平延长
 *              - I2CSLV_ADDR_CLOCK_FORCE_STRETCH_ENABLE   地址匹配后时钟强制SCL电平延长
 *
 * @retval None
 */
void I2CSLV_SetAddrClockForceStretch(uint32_t u32ClkForceStretch)
{
	REG_MODIFY(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_FACS, u32ClkForceStretch);
}

/**
 * @brief  获取 I2CSLV 收到地址数据后 是否具备对SCL时钟有强制延长功能
 *
 * @retval uint32_t:是否时钟延长 @ref I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION
 *         - I2CSLV_CLOCK_FORCE_STRETCH_DISABLE  地址时钟不强制SCL电平延长
 *         - I2CSLV_CLOCK_FORCE_STRETCH_ENABLE   地址时钟强制SCL电平延长
 *
 */
uint32_t I2CSLV_GetAddrClockForceStretch(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_FACS));
}

/**
 * @brief  设置 I2CSLV 数据寄存器，写入待发送的数据
 * @param  [in] u8Data: 8bit数据值
 *
 * @retval None
 *
 */
void I2CSLV_WriteByte(uint8_t u8Data)
{
	REG_MODIFY(HC_I2CSLV->DOUTR, I2CSLV_DOUTR_DOUT, u8Data);
}

/**
 * @brief  获取 I2CSLV 数据寄存器，读出接收到的数据
 *
 * @retval uint8_t:I2CSLV 8bit数据值
 */
uint8_t I2CSLV_ReadByte(void)
{
	return (uint8_t)(REG_READBITS(HC_I2CSLV->DINR, I2CSLV_DINR_DIN));
}

/* ========================================================================== */
/*  iwdt.c                                                                    */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_IWDT IWDT模块驱动库
 * @brief IWDT Driver Library IWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IWDT_Local_Macros IWDT局部宏定义
 * @{
 */
/**
 * @defgroup IWDT_Key_Value_Define IWDT键值设置
 * @{
 */
#define IWDT_KEY_LOCK_RELEASE     (0x5555U) /*!< 解除写保护 */
#define IWDT_KEY_START_VALUE      (0xCCCCU) /*!< 启动IWDT计数器 */
#define IWDT_KEY_RELOAD_VALUE     (0xAAAAU) /*!< 重载IWDT计数器 */
#define IWDT_KEY_STOP_BYPASS_1234 (0x1234U) /*!< 依次写入0x1234和0x5678停止IWDT */
#define IWDT_KEY_STOP_BYPASS_5678 (0x5678U) /*!< 依次写入0x1234和0x5678停止IWDT */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup IWDT_Global_Functions IWDT全局函数定义
 * @{
 */

/**
 * @brief  IWDT 初始化
 * @param  [in] pstcIwdtInit: IWDT初始化 @ref stc_iwdt_init_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t IWDT_Init(stc_iwdt_init_t* pstcIwdtInit)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_START_VALUE);
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_LOCK_RELEASE);

    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_PRSF | IWDT_SR_ARRF | IWDT_SR_WINRF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->CR, pstcIwdtInit->u32Action | pstcIwdtInit->u32Prescaler);
    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_PRSF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->ARR, pstcIwdtInit->u32ArrCounter);
    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_ARRF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->WINR, pstcIwdtInit->u32Window);
    while (REG_READBITS(HC_IWDT->SR, IWDT_SR_WINRF))
    {
        ;
    }

    REG_WRITE(HC_IWDT->KR, IWDT_KEY_RELOAD_VALUE);

    while (!REG_READBITS(HC_IWDT->SR, IWDT_SR_RUN))
    {
        ;
    }

    return Ok;
}

/**
 * @brief  IWDT 启动运行
 *
 * @retval None
 */
void IWDT_Start(void)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_START_VALUE);
}

/**
 * @brief  IWDT 停止运行
 *
 * @retval None
 */
void IWDT_Stop(void)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_STOP_BYPASS_1234);
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_STOP_BYPASS_5678);
}

/**
 * @brief  IWDT 喂狗
 *
 * @retval None
 */
void IWDT_Feed(void)
{
    REG_WRITE(HC_IWDT->KR, IWDT_KEY_RELOAD_VALUE);
}

/**
 * @brief  IWDT 溢出标志清除
 *
 * @retval None
 */
void IWDT_ClearOverFlag(void)
{
    REG_CLEARBITS(HC_IWDT->SR, IWDT_SR_OV);
}

/**
 * @brief  IWDT 溢出标志获取
 *
 * @retval boolean_t： 溢出标志位
 *         - TRUE   溢出
 *         - FALSE  无溢出
 */
boolean_t IWDT_GetOverFlag(void)
{
    if (REG_READBITS(HC_IWDT->SR, IWDT_SR_OV))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  IWDT 获取当前运行状态
 *
 * @retval boolean_t： 运行状态
 *         - TRUE   正在运行
 *         - FALSE  没有运行
 */
boolean_t IWDT_GetRunFlag(void)
{
    if (REG_READBITS(HC_IWDT->SR, IWDT_SR_RUN))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* ========================================================================== */
/*  lin.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_USART_LIN USART_LIN模块驱动库
 * @brief USART_LIN Driver Library USART_LIN模块驱动库
 * @{
 */

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
/**
 * @defgroup USART_LIN_Local_Variables USART_LIN局部变量定义
 * @{
 */
static uint8_t u8LIN_Wakeup_Data = 0x80U;
static uint8_t u8LIN_Sync_Data   = 0x55U;
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USART_LIN_Global_Functions USART_LIN全局函数定义
 * @{
 */

/**
 * @brief  USART LIN唤醒信号帧发送函数
 * @param  [in] USARTx:        USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_LIN_Wakeup_Frame_Sent(USART_TypeDef* USARTx)
{
    /* CR1设置: TE = 1 */
    REG_SETBITS(USARTx->CR1, USART_CR1_TE);

    /* 发送数据0x80 */
    USART_UART_Transmit(USARTx, &u8LIN_Wakeup_Data, 0x1U, LIN_TIMEOUT_VALUE);
}

/**
 * @brief  USART LIN间隔段发送函数
 * @param  [in] USARTx:             USART类型定义         @ref USART_TypeDef
 * @param  [in] u32LowBitsNumbers:  发送持续位的“0”的个数, 数据范围参考TDR寄存器位长
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 * - 为了避免间隔段未发完而新数据又写入发送寄存器，本函数中加了超时定时器用以等待间隔段发送完成
 */
en_result_t USART_LIN_Break_Sent(USART_TypeDef* USARTx, uint32_t u32LowBitsNumbers)
{
    uint32_t u32TimeoutCnt = 0U;

    /* CR3设置: BREAK = 1; LINEN = 1 */
    REG_MODIFY(USARTx->CR3, USART_CR3_BREAK | USART_CR3_LINEN, USART_LIN_BREAK_SEND_ENABLE | USART_LIN_ENABLE);

    /* CR1设置: TE = 1 */
    if (USART_MODE_TX != REG_READBITS(USARTx->CR1, USART_CR1_TE))
    {
        /* TE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_TE, USART_MODE_TX);
    }

    USART_ClearFlag(USARTx, USART_FLAG_TC);
    /* 发送低电平到总线 */
    REG_WRITE(USARTx->TDR, u32LowBitsNumbers);

    /* 查询等待SR.TC变为1 */
    while (!USART_GetFlag(USARTx, USART_FLAG_TC))
    {
        u32TimeoutCnt++;
        if (LIN_TIMEOUT_VALUE <= u32TimeoutCnt)
        {
            /* 等待超时 */
            return ErrorTimeout;
        }
    }

    /* 使用TOE功能，加入同步间隔段后等待 */
    USART_ClearFlag(USARTx, USART_FLAG_TO);
    USART_LIN_TOE(USARTx, USART_TOE_General, LIN_TOE_Break_Wait_Time);

    return Ok;
}

/**
 * @brief  USART LIN同步段发送函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 */
en_result_t USART_LIN_Sync_Sent(USART_TypeDef* USARTx)
{
    /* CR3设置: BREAK = 0 */
    REG_CLEARBITS(USARTx->CR3, USART_CR3_BREAK);
    return USART_LIN_Transmit(USARTx, &u8LIN_Sync_Data, 0x1U, LIN_TIMEOUT_VALUE);
}

/**
 * @brief  USART LIN ID段发送函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @param  [in] u8IDValue:     ID值 (8位，包含标识符和奇偶校验符)
 * @retval None
 */
void USART_LIN_ID_Sent(USART_TypeDef* USARTx, uint8_t u8IDValue)
{
    /* 发送数据0x80 */
    USART_UART_Transmit(USARTx, (uint8_t*)&u8IDValue, 0x1U, LIN_TIMEOUT_VALUE);

    /* 使用TOE功能，加入应答间隔段 */
    USART_ClearFlag(USARTx, USART_FLAG_TO);
    USART_LIN_TOE(USARTx, USART_TOE_General, LIN_TOE_Response_Interval_Time);
}

/**
 * @brief  USART LIN发送数据
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] u8Data:      LIN发送数据buffer指针,包含数据和校验和
 * @param  [in] u32Size:     LIN发送数据长度(字节数)
 * @param  [in] u32Timeout:  LIN发送超时时间
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 */
en_result_t USART_LIN_Transmit(USART_TypeDef* USARTx, uint8_t u8Data[], uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t u32SizeIdx    = 0U;
    uint32_t u32TimeoutCnt = 0U;
    for (u32SizeIdx = 0U; u32SizeIdx < u32Size; u32SizeIdx++)
    {
        /* 清除发送完成标志 */
        USART_ClearFlag(USARTx, USART_FLAG_TC);
        /* 写入一帧待发送的数据 */
        REG_WRITE(USARTx->TDR, u8Data[u32SizeIdx]);
        /* 查询等待SR.TC变为1 */
        while (!USART_GetFlag(USARTx, USART_FLAG_TC))
        {
            u32TimeoutCnt++;
            if (u32Timeout <= u32TimeoutCnt)
            {
                /* 等待超时 */
                return ErrorTimeout;
            }
        }
        /* 使用TOE功能，加入字节间间隔段 */
        USART_ClearFlag(USARTx, USART_FLAG_TO);
        USART_LIN_TOE(USARTx, USART_TOE_General, LIN_TOE_Byte_Interval_Time);
    }

    return Ok;
}

/**
 * @brief  USART LIN 字节间间隔和帧间隔　超时定时器设置
 * @param  [in] USARTx:      USART类型定义            @ref USART_TypeDef
 * @param  [in] u32TOEType:  多功能定时器工作模式配置 @ref USART_TOE_Type
 * @param  [in] u32TOEValue: LIN发送超时时间
 * @retval None
 */
void USART_LIN_TOE(USART_TypeDef* USARTx, uint32_t u32TOEType, uint32_t u32TOEValue)
{
    if (USART_TOE_General == u32TOEType)
    {
        /* 停止超时定时器 TOE = 0 */
        REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
        /* 写入超时值 */
        REG_WRITE(USARTx->TOR, u32TOEValue);
        /* 启动超时定时器 TOE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_General);
    }
    else if (USART_TOE_Break == u32TOEType)
    {
        /* 停止超时定时器 TOE = 0 */
        REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
        /* 写入超时值 */
        REG_WRITE(USARTx->TOR, u32TOEValue);
        /* 启动超时定时器 TOE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_Break);
    }
}

/**
 * @brief  USART LIN唤醒信号帧检测函数
 * @param  [in] USARTx:        USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_LIN_Wakeup_Frame_Detect(USART_TypeDef* USARTx)
{
    /* CR1设置: RE = 1 */
    REG_MODIFY(USARTx->CR1, USART_CR1_RE, USART_MODE_RX);
    /* RXD管脚边沿中断使能 */
    USART_EnableIrq(USARTx, USART_FLAG_DWK);
}

/**
 * @brief  USART LIN间隔段检测函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @param  [in] u32LowBitsNumbers: 持续位的“0”的个数，数据需 < 32
 * @retval None
 */
void USART_LIN_Break_Detect(USART_TypeDef* USARTx, uint32_t u32LowBitsNumbers)
{
    uint32_t u32ValTOR;
    uint32_t u32ValDIVI = USARTx->BRR_f.DIVI;
    uint32_t u32ValDIVF = USARTx->BRR_f.DIVF;

    /* CR1设置: RE = 1 */
    if (USART_MODE_RX != REG_READBITS(USARTx->CR1, USART_CR1_RE))
    {
        /* RE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_RE, USART_MODE_RX);
    }

    /* TOR = PCLK / BPS / 4^psc * u32LowBitsNumbers */
    /*     = 16 * (DIVI+1) * 256 / (128+DIVF) * u32LowBitsNumbers */
    if (USARTx->BRR_f.FBME == 0U)
    {
        u32ValTOR = u32LowBitsNumbers * 16U * (u32ValDIVI + 1U);
    }
    else
    {
        u32ValTOR = u32LowBitsNumbers * 16U * 256U * (u32ValDIVI + 1U) / (128U + u32ValDIVF);
    }

    /* TOR value limitation */
    if ((USART_TOR_TOR_Msk >> USART_TOR_TOR_Pos) < u32ValTOR)
    {
        u32ValTOR = USART_TOR_TOR_Msk >> USART_TOR_TOR_Pos;
    }
    /* RXD管脚边沿中断除能 */
    USART_DisableIrq(USARTx, USART_FLAG_DWK);

    USART_ClearFlag(USARTx, USART_FLAG_LBD);
    /* 间隔段中断使能 */
    USART_EnableIrq(USARTx, USART_FLAG_LBD);
    /* 间隔检测使能 */
    REG_SETBITS(USARTx->CR3, USART_CR3_LBDE);
    /* 使用TOE功能为同步间隔段检测，设置间隔段低电平宽度 */
    USART_LIN_TOE(USARTx, USART_TOE_Break, u32ValTOR);
    /* CR3设置: LINEN = 1 */
    REG_SETBITS(USARTx->CR3, USART_CR3_LINEN);
}

/**
 * @brief  USART LIN同步段检测函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_LIN_Sync_Detect(USART_TypeDef* USARTx)
{
    USART_ClearFlag(USARTx, USART_FLAG_ABR);
    /* 自动波特率检测中断使能 */
    USART_EnableIrq(USARTx, USART_FLAG_ABR);
    /* 自动波特率检测使能 */
    REG_SETBITS(USARTx->CR3, USART_CR3_ABRE);
    /* 使用TOE功能为波特率自动检测 */
    REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
    REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_Auto_BaudRate);
}

/**
 * @brief  USART LIN接收波特率设置函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @param  [in] u32BaudRate:       UART目标波特率
 * @param  [in] u32BaudRateOffset: UART目标波特率Offset
 * @retval None
 */
void USART_LIN_BaudRateSet_Detect(USART_TypeDef* USARTx, uint32_t u32BaudRate, uint32_t u32BaudRateOffset)
{
    uint32_t u32CalBaudRate;
    uint32_t u32BDRValue;
    uint32_t u32BaudRateMin;
    uint32_t u32BaudRateMax;

    /* 计算检测的波特率 */
    u32BDRValue    = USARTx->BDR + 1U;
    u32CalBaudRate = Sysctrl_GetPClkFreq() / (1U << (USARTx->BRR_f.PSC * 2U)) / u32BDRValue;

    /* 目标波特率设置 */
    if (0xFFFFFFFFU - u32BaudRateOffset >= u32BaudRate)
    {
        u32BaudRateMax = u32BaudRate + u32BaudRateOffset;
    }
    else
    {
        u32BaudRateMax = 0xFFFFFFFFU;
    }
    if (u32BaudRate >= u32BaudRateOffset)
    {
        u32BaudRateMin = u32BaudRate - u32BaudRateOffset;
    }
    else
    {
        u32BaudRateMin = 0U;
    }
    if (u32CalBaudRate <= u32BaudRateMax && u32CalBaudRate >= u32BaudRateMin) /* 容错范围内 */
    {
        if (u32BaudRate != u32CalBaudRate)
        {
            REG_CLEARBITS(USARTx->CR1, USART_CR1_RE);
            u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_LIN, u32CalBaudRate, Sysctrl_GetPClkFreq(), USARTx->CR1 & USART_CR1_OVER8);

            REG_SETBITS(USARTx->CR1, USART_CR1_RE);
        }
    }
}

/**
 * @brief  LIN checksum函数
 * @param  [in] u8DataBuffer:  数据buffer
 * @param  [in] u8DataLen:     数据长度
 * @retval None
 */
uint8_t LIN_Checksum(uint8_t* u8DataBuffer, uint8_t u8DataLen)
{
    uint8_t  u8Index      = 0;
    uint16_t u16CheckSum  = 0;
    uint16_t u16CheckSum1 = 0;

    for (u8Index = 0; u8Index < u8DataLen; u8Index++)
    {
        u16CheckSum = u16CheckSum + *(u8DataBuffer + u8Index);

        u16CheckSum1 = u16CheckSum >> 8;
        if (u16CheckSum1 > 0)
        {
            u16CheckSum++;
            u16CheckSum &= ~0x0100;
        }
    }

    return (uint8_t)(~u16CheckSum);
}

/**
 * @brief  LIN ID parity函数
 * @param  [in] u8ID:  IDֵ
 * @retval None
 */
uint8_t LIN_IDParity(uint8_t u8ID)
{
    uint8_t u8Parity = 0;
    uint8_t u8P0     = 0;
    uint8_t u8P1     = 0;

    u8P0 = (u8ID & 0x01) ^ ((u8ID & 0x02) >> 1) ^ ((u8ID & 0x04) >> 2) ^ ((u8ID & 0x10) >> 4);
    u8P0 = u8P0 & 0x01;
    u8P1 = ~(((u8ID & 0x02) >> 1) ^ ((u8ID & 0x08) >> 3) ^ ((u8ID & 0x10) >> 4) ^ ((u8ID & 0x20) >> 5));
    u8P1 = u8P1 & 0x01;

    u8Parity = u8ID | (u8P0 << 6U) | (u8P1 << 7U);
    return u8Parity;
}

/* ========================================================================== */
/*  lpm.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  lptim.c                                                                   */
/* ========================================================================== */


/******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  lpuart.c                                                                  */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPUART LPUART模块驱动库
 * @brief LPUART Driver Library LPUART模块驱动库
 * @{
 */



/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */

/**
 * @brief  LPUART通信中断使能函数设置
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enIrqSel: 发送or接收中断使能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_EnableIrq(LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enIrqSel, TRUE);

    return Ok;
}
/**
 * @brief  LPUART通信中断禁止函数设置
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enIrqSel: 发送or接收中断禁止
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_DisableIrq(LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enIrqSel, FALSE);

    return Ok;
}
/**
 * @brief lpuart通信时钟源选择
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enSclk: 时钟源选项
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_SelSclk(LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk)
{
    ASSERT(IS_VALID_CLK(enSclk));

    LPUARTx->SCON_f.CLKSRC = (uint32_t)enSclk;

    return Ok;
}

/**
 * @brief  LPUART通道多主机模式配置
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] pstcMultiCfg: 多主机模式结构
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - ErrorInvalidParameter配置失败
 */
en_result_t LPUart_SetMultiMode(LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg)
{

    if(NULL != pstcMultiCfg)
    {
        LPUARTx->SCON_f.ADRDET = TRUE;
        LPUARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        LPUARTx->SADEN = pstcMultiCfg->u8SaddEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  LPUART单线半双工模式使能
 *
 * @param [in] LPUARTx 通道号
 *
 * @retval None
 */
void LPUart_HdModeEnable(LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = TRUE;
}


/**
 * @brief  LPUART单线半双工模式关闭
 *
 * @param [in] LPUARTx 通道号
 *
 * @retval None
 */
void LPUart_HdModeDisable(LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = FALSE;
}

/**
 * @brief  LPUART通道发送或接收等功能使能设置
 *
 * @param [in] LPUARTx:  通道号
 * @param [in] enFunc: 功能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_EnableFunc(LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enFunc, TRUE);

    return Ok;
}

/**
 * @brief  LPUART通道发送或接收等功能禁止设置
 *
 * @param [in] LPUARTx:  通道号
 * @param [in] enFunc: 功能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_DisableFunc(LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enFunc, FALSE);

    return Ok;
}

/**
 * @brief  LPUART通道通信状态获取
 *
 * @param [in] LPUARTx: 通道号
 *
 * @retval uint8_t: 状态值
 */
uint8_t LPUart_GetIsr(LPUART_TypeDef* LPUARTx)
{
    uint32_t u32Val;

    u32Val = LPUARTx->ISR;

    return (uint8_t)u32Val;
}

/**
 * @brief  LPUART通道通信状态获取
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enStatus: 需要获取的状态
 *
 * @retval boolean_t:
 *         - TRUE
 *         - 其他: 配置失败
 */
boolean_t LPUart_GetStatus(LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(LPUARTx->ISR)), (uint32_t)enStatus);

    return bStatus;
}

/**
 * @brief  LPUART通道通信状态全部清除
 *
 * @param [in] LPUARTx:  Lpuart通道号
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_ClrIsr(LPUART_TypeDef* LPUARTx)
{
    LPUARTx->ICR = 0u;
    return Ok;
}

/**
 * @brief  LPUART通道通信状态清除
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] enStatus: 清除哪个状态
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_ClrStatus(LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(LPUARTx->ICR)), (uint32_t)enStatus, FALSE);

    return Ok;
}

/**
 * @brief  LPUART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u8Data: 待发送数据
 * @param [in] u32Timeout: 等待标志的超时时间
 *
 * @retval en_result_t:
 *           - Ok: 发送成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUart_SendData(LPUART_TypeDef* LPUARTx, uint8_t u8Data, uint32_t u32Timeout)
{
    uint32_t u32TimeCnt = 0u;

    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }

    LPUARTx->SBUF_f.DATA = u8Data;

    u32TimeCnt = 0u;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }

    LPUart_ClrStatus(LPUARTx,LPUartTC);

    return Ok;
}

/**
 * @brief  LPUART通道发送数据函数,中断方式调用此函数
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u8Data: 待发送数据
 *
 * @retval en_result_t:
 *           - Ok: 发送成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUart_SendDataIt(LPUART_TypeDef* LPUARTx, uint8_t u8Data)
{
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe)){;}
    LPUARTx->SBUF_f.DATA = u8Data;

    return Ok;
}


/**
 * @brief  LPUART通道多主机模式查询发送，中断方式发送不适用
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u16Data: 第8位数据+8bit待发送数据
 * @param [in] u32Timeout: 等待标志的超时时间
 *
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUart_MultiModeSendData(LPUART_TypeDef* LPUARTx, uint16_t u16Data, uint32_t u32Timeout)
{
    uint32_t u32TimeCnt = 0u;

    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }

    LPUARTx->SBUF  = (uint32_t)u16Data;

    u32TimeCnt = 0u;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }

    LPUart_ClrStatus(LPUARTx,LPUartTC);

    return Ok;
}

/**
 * @brief  LPUART通道多主机模式中断发送
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u16Data: 第8位数据+8bit待发送数据
 *
 * @retval en_result_t：
 *         - Ok:配置成功
 *         - 其他:配置失败
 */
en_result_t LPUart_MultiModeSendDataIt(LPUART_TypeDef* LPUARTx, uint16_t u16Data)
{
    LPUARTx->SBUF  = (uint32_t)u16Data;

    return Ok;
}

/**
 * @brief  LPUART通道接收数据函数
 *
 * @param [in] LPUARTx:  Lpuart通道号
 *
 * @retval uint8_t：接收数据
 */
uint8_t LPUart_ReceiveData(LPUART_TypeDef* LPUARTx)
{
    uint32_t u32Val;

    u32Val = LPUARTx->SBUF_f.DATA;

    return (uint8_t)u32Val;
}

/**
 * @brief  LPUART通道初始化函数
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] pstcCfg: 初始化结构体  @ref stc_lpuart_cfg_t
 *
 * @retval en_result_t：
 *         - Ok:配置成功
 *         - 其他:配置失败
 */
en_result_t LPUart_Init(LPUART_TypeDef* LPUARTx,stc_lpuart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    const uint32_t u32Over[3] = {0x4u, 0x3u, 0x2u};
    uint16_t u16OverShift;
    uint32_t u32BaudShift;
    float32_t f32Scnt = 0.0f;

    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    LPUARTx->SCON = 0u;

    LPUARTx->SCON = (uint32_t)pstcCfg->enStopBit          |
                    (uint32_t)pstcCfg->enMmdorCk          |
                    (uint32_t)pstcCfg->stcBaud.enSclkDiv  |
                    (uint32_t)pstcCfg->stcBaud.enSclkSel  |
                    (uint32_t)pstcCfg->enRunMode;

    if(LPUartMskMode0 != pstcCfg->enRunMode)
    {
        if((LPUartMskMode1 == pstcCfg->enRunMode) || (LPUartMskMode3 == pstcCfg->enRunMode))
        {
            u16OverShift = (uint16_t)u32Over[pstcCfg->stcBaud.enSclkDiv/LPUartMsk8Or16Div];
            u32BaudShift = pstcCfg->stcBaud.u32Baud<<u16OverShift;
            f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Sclk)/(float32_t)(u32BaudShift);
            LPUARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
        }
        LPUart_EnableFunc(LPUARTx,LPUartRenFunc);       /* 使能收发 */
    }

    enRet = Ok;
    return enRet;
}


/**
 * @brief 获取RB8数值
 *
 * @param [in] LPUARTx 通道号
 *
 * @retval boolean_t：RB8
 */
boolean_t LPUart_GetRb8(LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->SBUF_f.DR8) ? TRUE : FALSE;
}
/**
 * @brief  LPUART通道多主机模式从机地址配置函数
 *
 * @param [in] LPUARTx: 通道号
 * @param [in] u8Addr: 地址
 *
 * @retval en_result_t：
 *         - Ok:配置成功
 *         - 其他:配置失败
 */
en_result_t LPUart_SetSaddr(LPUART_TypeDef* LPUARTx,uint8_t u8Addr)
{
    LPUARTx->SADDR = u8Addr;

    return Ok;
}

/* ========================================================================== */
/*  lvd.c                                                                     */
/* ========================================================================== */


/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LVD LVD模块驱动库
 * @brief LVD Driver Library LVD模块驱动库
 * @{
 */

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
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
 * @defgroup LVD_Global_Functions LVD全局函数定义
 * @{
 */

/**
 * @brief  使能LVD中断.
 * @retval None.
 */
void Lvd_EnableIrq(void)
{
    HC_LVD->CR_f.IE = TRUE;
}

/**
 * @brief  禁止LVD中断.
 * @retval None.
 */
void Lvd_DisableIrq(void)
{
    HC_LVD->CR_f.IE = FALSE;
}

/**
 * @brief  LVD初始化.
 * @param  [in] pstcCfg: 初始化结构体指针 @ref stc_lvd_cfg_t
 * @retval None.
 */
void Lvd_Init(stc_lvd_cfg_t *pstcCfg)
{
    HC_LVD->CR = 0U;

    HC_LVD->CR = (uint32_t)pstcCfg->enAct        |
                  (uint32_t)pstcCfg->enFilter     |
                  (uint32_t)pstcCfg->enFilterTime |
                  (uint32_t)pstcCfg->enInputSrc   |
                  (uint32_t)pstcCfg->enIrqType    |
                  (uint32_t)pstcCfg->enThreshold;
}


/**
 * @brief  使能LVD.
 * @retval None.
 */
void Lvd_Enable(void)
{
    HC_LVD->CR_f.LVDEN = 1u;
}


/**
 * @brief  禁止LVD.
 * @retval None.
 */
void Lvd_Disable(void)
{
    HC_LVD->CR_f.LVDEN = 0u;
}


/**
 * @brief  获取LVD中断标志.
 * @retval boolean_t:
 *           - TRUE: 已发生中断
 *           - FLASE: 未发生中断
 */
boolean_t Lvd_GetIrqStat(void)
{
    return HC_LVD->SR_f.INTF ? TRUE: FALSE;

}


/**
 * @brief  清除LVD中断标志.
 * @retval None.
 */
void Lvd_ClearIrq(void)
{
    HC_LVD->SR_f.INTF = 0U;
}


/**
 * @brief  获取Filter结果.
 * @retval boolean_t:
 *           - TRUE: 滤波后的信号电平为高
 *           - FLASE: 滤波后的信号电平为低
 */
boolean_t Lvd_GetFilterResult(void)
{
    return (boolean_t)HC_LVD->SR_f.FILTER;
}

/* ========================================================================== */
/*  opa.c                                                                     */
/* ========================================================================== */


/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  rtc.c                                                                     */
/* ========================================================================== */


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_RTC RTC模块驱动库
 * @brief RTC Driver Library RTC模块驱动库
 * @{
 */

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
/**
 * @defgroup RTC_Local_Macros RTC局部宏定义
 * @{
 */
/**
 * @defgroup RTC_WPR_Value RTC WPR Value definition RTC WPR保护序列
 * @{
 */
#define RTC_UNLOCK_VALUE1       (0xCAU) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_UNLOCK_VALUE2       (0x53U) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_LOCK_VALUE          (0xFFU) /*!< 写入其他序列锁定寄存器写，除了WPR与ICR */
/**
 * @}
 */

/**
 * @}
 */


/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
/**
 * @addtogroup RTC_Local_Functions RTC局部函数定义
 * @{
 */
static en_result_t RTC_CheckBCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max);
static boolean_t RTC_IsLeapYear(uint8_t u8year);
/**
 * @}
 */

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/
/**
 * @defgroup RTC_Local_Variables RTC局部变量定义
 * @{
 */
/**
 * @brief  平年每个月最后一天日期表 BCD格式.
 */
const static uint8_t Cnst_Month_Tbl[12]={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
/**
 * @}
 */
/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup RTC_Local_Functions RTC局部函数定义
 * @{
 */
/**
 * @brief  BCD格式检查.
 * @param  [in] u8data: BCD带检查数
 * @param  [in] u8limit_min: BCD最小值
 * @param  [in] u8limit_min: BCD最大值
 * @retval en_result_t:
 *           - Ok: BCD格式正确
 *           - Error: BCD格式错误
 */
static en_result_t RTC_CheckBCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max)
{
    if (((u8data & 0x0FU) > 0x09U) || ((u8data & 0xF0U) > 0x90U)
    ||(u8data > u8limit_max) || (u8data < u8limit_min))
    {
        return Error;
    }
    return Ok;
}


/**
 * @brief  闰年判断.
 * @param  [in] u8year: 2000年后的年份的十位和个位0~99
 * @retval boolean_t:
 *           - TRUE: 是闰年
 *           - FALSE: 不是闰年
 */
static boolean_t RTC_IsLeapYear(uint8_t u8year)
{
    uint16_t u16year;
    u16year = 2000U + u8year;
    if(((u16year%4U == 0U) && (u16year%100U != 0U)) || (u16year%400U == 0U))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
* @}
*/

/**
 * @defgroup RTC_Global_Functions RTC全局函数定义
 * @{
 */
/**
 * @brief  RTC写保护寄存器解锁.
 * @retval None.
 */
void RTC_Unlock(void)
{
    HC_RTC->WPR = RTC_UNLOCK_VALUE1;
    HC_RTC->WPR = RTC_UNLOCK_VALUE2;
}

/**
 * @brief  RTC写保护寄存器锁定.
 * @retval None.
 */
void RTC_Lock(void)
{
    HC_RTC->WPR = RTC_UNLOCK_VALUE1;
    HC_RTC->WPR = RTC_LOCK_VALUE;
}


/**
 * @brief  RTC计数器的使能或停止.
 * @param  [in] NewState: TRUE:使能RTC计数  FALSE:停止RTC计数
 * @retval None.
 */
void RTC_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(HC_RTC->CR0)), RTC_CR0_START_Pos, NewState);
}


/**
 * @brief  RTC计数器启动等待函数，如启动RTC计数器后立即进入低功耗模式，
 *         进入低功耗模式之前需执行此函数，以确保RTC已启动完成.
 * @retval None.
 */
void RTC_StartWait(void)
{
    HC_RTC->CR1_f.WAIT = 1U;
    while (HC_RTC->CR1_f.WAITF != 1U)  /* 等待直到WAITF=1 */
    {
        ;
    }
    HC_RTC->CR1_f.WAIT = 0U;
    while (HC_RTC->CR1_f.WAITF != 0U)  /* 等待直到WAITF=0 */
    {
        ;
    }
}

/**
 * @brief  RTC的1Hz输出的使能或停止.
 * @param  [in] pricision: RtcHz1selGeneralPricision 或 RtcHz1selHighPricision @ref en_rtc_hz1sel_t
 * @param  [in] NewState: FALSE: Hz1o_Disable  TRUE: HZ1o_Enable
 * @retval None.
 */
void RTC_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState)
{
    SetBit((uint32_t)(&(HC_RTC->CR0)), RTC_CR0_HZ1SEL_Pos, pricision);  /* 设置普通精度或者高精度1Hz输出 */
    SetBit((uint32_t)(&(HC_RTC->CR0)), RTC_CR0_HZ1OE_Pos, NewState);   /* 设置1Hz输出使能或禁止 */
}


/**
 * @brief  设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX).
 * @param  [in] pstcPrd: 根据结构体的定义设置PRDSEL、PRDS与PRDX @ref stc_rtc_prdcfg_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_PrdCfg(stc_rtc_prdcfg_t* pstcPrd)
{
    en_result_t enRet = Ok;
    HC_RTC->CR0_f.PRDSEL = pstcPrd->enPrdsel;
    if(pstcPrd->enPrdsel == RtcPrds)
    {
        HC_RTC->CR0_f.PRDS = pstcPrd->enPrds;
    }
    else if(pstcPrd->enPrdsel == RtcPrdx)
    {
        if(pstcPrd->u8Prdx>=64U)
        {
            enRet = ErrorInvalidParameter;
            return enRet;
        }
        HC_RTC->CR0_f.PRDX = pstcPrd->u8Prdx;
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }
    return enRet;
}

/**
 * @brief  闹钟使能.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @retval None.
 */
void RTC_AlarmEnalbe(en_rtc_alarmch_t enAlarmX)
{
    if(RtcAlarmA == enAlarmX)
    {
        HC_RTC->CR2 |= RTC_CR2_ALMAE;
    }
    else if(RtcAlarmB == enAlarmX)
    {
        HC_RTC->CR2 |= RTC_CR2_ALMBE;
    }
    else
    {
        ;
    }
}

/**
 * @brief  闹钟失能.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @retval None.
 */
void RTC_AlarmDisalbe(en_rtc_alarmch_t enAlarmX)
{
    if(RtcAlarmA == enAlarmX)
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMAE);
    }
    else if(RtcAlarmB == enAlarmX)
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMBE);
    }
    else
    {
        ;
    }
}


/**
 * @brief  RTC闹钟中断时间获取.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @param  [in] pstcAlarmTime: 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval None.
 */
void RTC_GetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime)
{
    uint32_t u32RegAddr;
    uint8_t u8Hour;

    if(RtcAlarmA == enAlarmX)
    {
        u32RegAddr = (uint32_t)&HC_RTC->ALMA;
    }
    else
    {
        u32RegAddr = (uint32_t)&HC_RTC->ALMB;
    }

    pstcAlarmTime->u8AlarmSec    = (uint8_t)(((*(uint32_t*)u32RegAddr) & (RTC_ALMA_SECL | RTC_ALMA_SECH)) >> RTC_ALMA_SECL_Pos);
    pstcAlarmTime->u8AlarmMinute = (uint8_t)(((*(uint32_t*)u32RegAddr) & (RTC_ALMA_MINL | RTC_ALMA_MINH)) >> RTC_ALMA_MINL_Pos);
    u8Hour   = (uint8_t)(((*(uint32_t*)u32RegAddr) & (RTC_ALMA_HOURL | RTC_ALMA_HOURH)) >> RTC_ALMA_HOURL_Pos);
    pstcAlarmTime->u8AlarmDayOfWeek   = (uint8_t)(((*(uint32_t*)u32RegAddr) & RTC_ALMA_WEEK) >> RTC_ALMA_WEEK_Pos);
    pstcAlarmTime->bAlarmMskH = ((*(uint32_t*)u32RegAddr) & RTC_ALMA_MSKH)? TRUE: FALSE;
    pstcAlarmTime->bAlarmMskM = ((*(uint32_t*)u32RegAddr) & RTC_ALMA_MSKM)? TRUE: FALSE;
    pstcAlarmTime->bAlarmMskS = ((*(uint32_t*)u32RegAddr) & RTC_ALMA_MSKS)? TRUE: FALSE;

    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        pstcAlarmTime->u8AlarmHour = u8Hour;
    }
    else
    {
        pstcAlarmTime->u8AlarmHour = u8Hour & 0x1fU;
        pstcAlarmTime->u8AmPm = (u8Hour & 0x20U)? 1U : 0U;
    }
}


/**
 * @brief  RTC闹钟设置.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @param  [in] pstcAlarmTime: 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval en_result_t:
 *         - Ok: 设置完成.
 *         - ErrorInvalidParameter: 设置失败，时间BCD格式不符合.
 */
en_result_t RTC_SetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime)
{
    en_result_t enRet = Ok;
    uint32_t u32RegValue;
    uint32_t u32Hour;

    if(Ok != RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmSec, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmMinute, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }

    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        enRet = RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmHour, 0x00U, 0x23U); /* 24H */
        u32Hour = pstcAlarmTime->u8AlarmHour;
    }
    else
    {
        enRet = RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmHour&(~0x20U), 0x01U, 0x12U); /* 12H */
        u32Hour = pstcAlarmTime->u8AmPm? (pstcAlarmTime->u8AlarmHour | 0x20U): pstcAlarmTime->u8AlarmHour;
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }


    u32RegValue = (((uint32_t)pstcAlarmTime->u8AlarmSec << RTC_ALMA_SECL_Pos) | \
                    ((uint32_t)pstcAlarmTime->u8AlarmMinute << RTC_ALMA_MINL_Pos) | \
                    ((uint32_t)u32Hour << RTC_ALMA_HOURL_Pos) | \
                    ((uint32_t)pstcAlarmTime->u8AlarmDayOfWeek << RTC_ALMA_WEEK_Pos) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskS << RTC_ALMA_MSKS_Pos) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskM << RTC_ALMA_MSKM_Pos) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskH << RTC_ALMA_MSKH_Pos));

    if(RtcAlarmA == enAlarmX)
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMAE);      /* 闹钟禁止以后再设置闹钟时间 */
        HC_RTC->ALMA = u32RegValue;
        HC_RTC->CR2 |= RTC_CR2_ALMAE;
    }
    else
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMBE);      /* 闹钟禁止以后再设置闹钟时间 */
        HC_RTC->ALMB = u32RegValue;
        HC_RTC->CR2 |= RTC_CR2_ALMBE;
    }

    return Ok;
}



/**
 * @brief  RTC唤醒定时器使能.
 * @retval None.
 */
void RTC_WakeupTimerEnable(void)
{
    HC_RTC->CR2 |= RTC_CR2_WUTE;
}

/**
 * @brief  RTC唤醒定时器失能.
 * @retval None.
 */
void RTC_WakeupTimerDisable(void)
{
    HC_RTC->CR2 &= (~RTC_CR2_WUTE);
}

/**
 * @brief  RTC唤醒定时器时钟选择.
 * @retval None.
 */
void RTC_WakeupTimerClkSel(en_rtc_wucksel_t enWucksel)
{
    uint32_t u32RegValue;

    u32RegValue = HC_RTC->CR2 & (~RTC_CR2_WUCKSEL);
    HC_RTC->CR2 = u32RegValue | (uint32_t)enWucksel;
}


/**
 * @brief  RTC唤醒定时器设置周期值.
 * @param  [in] u16Arr: RTC唤醒定时器周期值
 * @retval None.
 */
void RTC_WakeupTimerSetArr(uint16_t u16Arr)
{
    HC_RTC->WUTARR = (uint32_t)u16Arr;
}

/**
 * @brief  RTC唤醒定时器获取周期值.
 * @retval uint16_t: RTC唤醒定时器周期值
 */
uint16_t RTC_WakeupTimerGetArr(void)
{
    return (uint16_t)HC_RTC->WUTARR;
}


/**
 * @brief  RTC时间戳使能.
 * @retval None.
 */
void RTC_TimestampEnable(void)
{
    HC_RTC->CR2 |= RTC_CR2_TSE;
}

/**
 * @brief  RTC时间戳失能.
 * @retval None.
 */
void RTC_TimestampDisable(void)
{
    HC_RTC->CR2 &= (~RTC_CR2_TSE);
}


/**
 * @brief  RTC时间戳边沿选择.
 * @param  [in] enEdge: RTC时间戳边沿选择 @ref en_rtc_tsedge_t
 * @retval None.
 */
void RTC_TimestampEdgeSel(en_rtc_tsedge_t enEdge)
{
    if(RtcTSFalling == enEdge)
    {
        HC_RTC->CR2 |= RTC_CR2_TSEDG;
    }
    else
    {
        HC_RTC->CR2 &= (~RTC_CR2_TSEDG);
    }
}


/**
 * @brief  RTC时间戳时间读取.
 * @param  [in] pstcTs: RTC时间戳读取指针 @ref stc_rtc_ts_t
 * @retval None.
 */
void RTC_TimestampGet(stc_rtc_ts_t *pstcTs)
{
    uint8_t u8Hour;

    pstcTs->u8Second = (uint8_t)((HC_RTC->TSTR & (RTC_TSTR_SECL | RTC_TSTR_SECH)) >> RTC_TSTR_SECL_Pos);
    pstcTs->u8Minute = (uint8_t)((HC_RTC->TSTR & (RTC_TSTR_MINL | RTC_TSTR_MINH)) >> RTC_TSTR_MINL_Pos);
    u8Hour = (uint8_t)((HC_RTC->TSTR & (RTC_TSTR_HOURL | RTC_TSTR_HOURH)) >> RTC_TSTR_HOURL_Pos);
    pstcTs->u8DayOfWeek = (uint8_t)((HC_RTC->TSDR & RTC_TSDR_WEEK) >> RTC_TSDR_WEEK_Pos);
    pstcTs->u8Day = (uint8_t)((HC_RTC->TSDR & (RTC_TSDR_DAYL | RTC_TSDR_DAYH)) >> RTC_TSDR_DAYL_Pos);
    pstcTs->u8Month = (uint8_t)((HC_RTC->TSDR & RTC_TSDR_MON) >> RTC_TSDR_MON_Pos);

    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        pstcTs->u8Hour = u8Hour;
    }
    else
    {
        pstcTs->u8Hour = u8Hour & 0x1fU;
        pstcTs->u8AmPm = (u8Hour & 0x20U)? 1U : 0U;
    }
}


/**
 * @brief  RTC读取中断标志.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t RTC_GetIrqFlag(uint32_t u32IqrFlag)
{
    return (HC_RTC->IFR & u32IqrFlag)? TRUE: FALSE;
}


/**
 * @brief  RTC清除中断标志.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void RTC_ClearIrqFlag(uint32_t u32IqrFlag)
{
    HC_RTC->ICR = (~u32IqrFlag);
}

/**
 * @brief  RTC读取中断使能状态.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval boolean_t:
 *           - TRUE: 中断使能
 *           - FALSE: 中断未使能
 */
boolean_t RTC_GetIrqEn(uint32_t u32IqrFlag)
{
    return (HC_RTC->IER & u32IqrFlag)? TRUE: FALSE;
}


/**
 * @brief  RTC使能中断.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void RTC_EnableIrq(uint32_t u32IqrFlag)
{
    HC_RTC->IER |= u32IqrFlag;
}


/**
 * @brief  RTC禁用中断.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void RTC_DisableIrq(uint32_t u32IqrFlag)
{
    HC_RTC->IER &= (~u32IqrFlag);
}


/**
 * @brief  计算RTC误差补偿寄存器的值.
 * @param  [in] s16CompUnit: 补偿单位，取值范围 -275 ~ +213，1个单位为(1/32768)*10^6 /32 = 0.96ppm
 * @param  [out] pu16CompValue: 计算结果
 * @retval en_result_t:
 *           - Ok: 计算成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_CalcCompValue(int16_t s16CompUnit, uint16_t *pu16CompValue)
{
    uint16_t u16Res;
    int32_t s32Temp = s16CompUnit;

    if((s16CompUnit < -275) || (s16CompUnit > 213))
    {
        return ErrorInvalidParameter;
    }
    s32Temp = (s32Temp * 32768 * 32 / 1000000) + 32;
    u16Res = (uint16_t)s32Temp;
    u16Res &= 0x1ffU;
    *pu16CompValue = u16Res;

    return Ok;
}


/**
 * @brief  配置RTC的误差补偿寄存器.
 * @param  [in] u16CompValue: 数值的范围为：0-511
 * @param  [in] NewStatus: RtcCompenDisable 或 RtcAmCompenEnable @ref en_rtc_compen_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_CompCfg(uint16_t u16CompValue, en_rtc_compen_t NewStatus)
{
    if(u16CompValue > 0x1ffU)
    {
        return ErrorInvalidParameter;
    }
    else
    {
        HC_RTC->COMPEN_f.EN = NewStatus;
        HC_RTC->COMPEN_f.CR = u16CompValue;
    }

    return Ok;
}


/**
 * @brief  RTC获取时间函数.
 * @param  [in] pstcDateTime: 用于存放读取日期时间的指针 @ref stc_rtc_time_t
 * @retval int32_t:
 *           - Ok: 获取正常
 *           - ErrorTimeout: 超时错误
 */
en_result_t RTC_ReadDateTime(stc_rtc_time_t* pstcDateTime)
{
    uint32_t u32TimeOut;

    ASSERT(NULL != pstcDateTime);

    if(1U == HC_RTC->CR0_f.START)
    {
        HC_RTC->CR1_f.WAIT = 1U;
        u32TimeOut = 1000U;
        while(FALSE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
		}
    }
    pstcDateTime->u8Second  = (uint8_t)HC_RTC->SEC;
    pstcDateTime->u8Minute  = (uint8_t)HC_RTC->MIN;
    if(1U == HC_RTC->CR0_f.AMPM)
    {
        pstcDateTime->u8Hour   = (uint8_t)HC_RTC->HOUR;
    }
    else
    {
        pstcDateTime->u8Hour   = (uint8_t)HC_RTC->HOUR & 0x1fU;
        pstcDateTime->u8AmPm = ((HC_RTC->HOUR & 0x20U)? 1U : 0U);
    }
    pstcDateTime->u8Day       = (uint8_t)HC_RTC->DAY;
    pstcDateTime->u8DayOfWeek = (uint8_t)HC_RTC->WEEK;
    pstcDateTime->u8Month     = (uint8_t)HC_RTC->MON;
    pstcDateTime->u8Year      = (uint8_t)HC_RTC->YEAR;

    HC_RTC->CR1_f.WAIT = 0U;
    if(1U == HC_RTC->CR0_f.START)
    {
        u32TimeOut = 1000U;
        while(TRUE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
    }

    return Ok;
}


/**
 * @brief  向RTC时间寄存器写入时间.
 * @param  [in] pstcDateTime: 用于存放读取日期时间的指针 @ref stc_rtc_time_t
 * @retval en_result_t:
 *           - Ok: 写入正常
 *           - ErrorInvalidParameter: 参数错误
 *           - ErrorTimeout: 时间溢出错误
 */
en_result_t RTC_SetDateTime(stc_rtc_time_t* pstcDateTime)
{
    en_result_t enRet = Ok;
    uint32_t u32TimeOut;
    uint8_t u8MonthIndex;

    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Second, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Minute, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Month, 0x01U, 0x12U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Year, 0x00U, 0x99U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8DayOfWeek, 0x00U, 0x06U))
    {
        return ErrorInvalidParameter;
    }
    u8MonthIndex = ((pstcDateTime->u8Month & 0x10U)? 10U: 0U) + (pstcDateTime->u8Month & 0x0fU) - 1U;
    if(pstcDateTime->u8Month == 0x02U)
    {
        if(RTC_IsLeapYear(pstcDateTime->u8Year))
        {
            enRet = RTC_CheckBCD_Format(pstcDateTime->u8Day, 0x01U, 0x29U); /*!< 闰年2月 */
        }
        else
        {
            enRet = RTC_CheckBCD_Format(pstcDateTime->u8Day, 0x01U, 0x28U); /*!< 平年2月 */
        }
    }
    else
    {
        enRet = RTC_CheckBCD_Format(pstcDateTime->u8Day, 0x01U, Cnst_Month_Tbl[u8MonthIndex]);
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }
    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        enRet = RTC_CheckBCD_Format(pstcDateTime->u8Hour, 0x00U, 0x23U); /*!< 24H */
    }
    else
    {
        enRet = RTC_CheckBCD_Format(pstcDateTime->u8Hour&(~0x20U), 0x01U, 0x12U); /*!< 12H */
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }


    if(HC_RTC->CR0_f.START == 1U)
    {
        HC_RTC->CR1_f.WAIT = 1U;
        u32TimeOut = 1000U;
        while(FALSE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
		}
    }
    HC_RTC->SEC   = pstcDateTime->u8Second;
    HC_RTC->MIN   = pstcDateTime->u8Minute;
    if(1U == HC_RTC->CR0_f.AMPM)
    {
        HC_RTC->HOUR  = pstcDateTime->u8Hour;
    }
    else
    {
        HC_RTC->HOUR  = (uint32_t)pstcDateTime->u8Hour | ((uint32_t)pstcDateTime->u8AmPm<<5U);
    }
    HC_RTC->DAY   = pstcDateTime->u8Day;
    HC_RTC->MON   = pstcDateTime->u8Month;
    HC_RTC->YEAR  = pstcDateTime->u8Year;
    HC_RTC->WEEK  = pstcDateTime->u8DayOfWeek;

    HC_RTC->CR1_f.WAIT = 0U;
    if(HC_RTC->CR0_f.START == 1U)
    {
        u32TimeOut = 1000U;
        while(TRUE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
    }
    enRet = Ok;
    return enRet;
}


/**
 * @brief  读取RTC当前的时间格式 12小时制或者24小时制.
 * @retval en_rtc_ampm_t：  @ref en_rtc_ampm_t
 *           - RtcAmpm12H: 12小时制
 *           - RtcAmpm24H: 24小时制
 */
en_rtc_ampm_t RTC_GetAmpmFormat(void)
{
    return (HC_RTC->CR0 & RTC_CR0_AMPM)? RtcAmpm24H : RtcAmpm12H;
}


/**
 * @brief  初始化RTC.
 * @param  [in] pstcRtcInit: 初始化结构体指针 @ref stc_rtc_initstruct_t
 * @retval None.
 */
void RTC_Init(stc_rtc_initstruct_t* pstcRtcInit)
{
    HC_RTC->CR0 &= (~RTC_CR0_START);                /* 计数停止 */
    HC_RTC->CR0_f.AMPM = pstcRtcInit->enAmpm;        /* 实时时钟小时的时制 */
    HC_RTC->CR1_f.CKSEL = pstcRtcInit->enClksrc;      /* 实时时钟RTC的时钟源 */
    HC_RTC->CR0 |= RTC_CR0_START;                /* 计数开始 */
}

/* ========================================================================== */
/*  spi.c                                                                     */
/* ========================================================================== */


/*******************************************************************************
* Include files
******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SPI SPI模块驱动库
 * @brief SPI Driver Library SPI模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup SPI_Global_Functions SPI全局函数定义
 * @{
 */

/**
 * @brief  SPI 总体初始化函数.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] pstcInitCfg: 初始化结构体 @ref stc_spi_init_t
 * @retval en_result_t:
 *         Ok: SPI初始化成功
 */
en_result_t Spi_Init(SPI_TypeDef* SPIx, stc_spi_init_t *pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    REG_MODIFY(  SPIx->CR0
               ,
                 SPI_CR0_BRR
               | SPI_CR0_CPHA
               | SPI_CR0_CPOL
               | SPI_CR0_MSTR
               | SPI_CR0_LSBF
               | SPI_CR0_WIDTH
               | SPI_CR0_SSM
               | SPI_CR0_CM
               | SPI_CR0_SMP
               ,
                 pstcInitCfg->u32BaudRate
               | pstcInitCfg->u32CPHA
               | pstcInitCfg->u32CPOL
               | pstcInitCfg->u32Mode
               | pstcInitCfg->u32BitOrder
               | pstcInitCfg->u32DataWidth
               | pstcInitCfg->u32NSS
               | pstcInitCfg->u32TransferDirection
               | pstcInitCfg->u32SampleDelay
               );


    REG_MODIFY(SPIx->CR1, (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN), pstcInitCfg->u32DMAReq);

    return Ok;
}


/**
 * @brief  开启SPI模块.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void SPI_Enable(SPI_TypeDef *SPIx)
{
    REG_SETBITS(SPIx->CR0, SPI_CR0_EN);
}


/**
 * @brief  禁止SPI模块.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void SPI_Disable(SPI_TypeDef *SPIx)
{
    REG_CLEARBITS(SPIx->CR0, SPI_CR0_EN);
}

/**
 * @brief  检查SPI模块是否已开启.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval uint32_t:
 *         - 0:   未开启
 *         - 非0: 已开启
 */
uint32_t SPI_IsEnable(SPI_TypeDef *SPIx)
{
    uint32_t res = (REG_READBITS(SPIx->CR0, SPI_CR0_EN) == SPI_CR0_EN)?(1U):(0U);
    return res;
}

/**
 * @brief  设置SPI模块DMA传输.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u32DMAReq: DMA请求配置 @ref SPI_DMA_TRANSFER_CFG
 * @retval None
 */
void SPI_SetDMAReq(SPI_TypeDef *SPIx, uint32_t u32DMAReq)
{
    REG_MODIFY(SPIx->CR1, (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN), u32DMAReq);
}


/**
 * @brief  获取SPI模块DMA传输.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval uint32_t: DMA请求配置 @ref SPI_DMA_TRANSFER_CFG
 */
uint32_t SPI_GetDMAReq(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR1, (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN)));
}


/**
 * @brief  设定SPI主机模式波特率.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32BaudRate: 波特率 @ref SPI_BAUDRATE_SELECTION
 * @retval None
 */
void SPI_SetBaudRate(SPI_TypeDef *SPIx, uint32_t u32BaudRate)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_BRR, u32BaudRate);
}


/**
 * @brief  设定SPI主机模式波特率.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 波特率 @ref SPI_BAUDRATE_SELECTION
 */
uint32_t SPI_GetBaudRate(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_BRR));
}


/**
 * @brief  设定SPI串行时钟相位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ClockPhase: 时钟相位选择 @ref SPI_CLOCK_PHASE_SELECTION
 * @retval NONE
 */
void SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t u32ClockPhase)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_CPHA, u32ClockPhase);
}


/**
 * @brief  获取SPI串行时钟相位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 时钟相位选择 @ref SPI_CLOCK_PHASE_SELECTION
 */
uint32_t SPI_GetClockPhase(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_CPHA));
}


/**
 * @brief  设定SPI串行时钟极性选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ClockPolarity: 时钟极性选择 @ref SPI_CLOCK_POLARITY_SELECTION
 * @retval None
 */
void SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t u32ClockPolarity)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_CPOL, u32ClockPolarity);
}


/**
 * @brief  获取SPI串行时钟极性选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 时钟极性选择 @ref SPI_CLOCK_POLARITY_SELECTION
 */
uint32_t SPI_GetClockPolarity(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_CPOL));
}


/**
 * @brief  设定SPI模式，主机模式或者从机模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32Mode: 模式选择 @ref SPI_MODE_SELECTION
 * @retval None
 */
void SPI_SetMode(SPI_TypeDef *SPIx, uint32_t u32Mode)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_MSTR, u32Mode);
}


/**
 * @brief  获取SPI模式，主机模式或者从机模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 模式选择 @ref SPI_MODE_SELECTION
 */
uint32_t SPI_GetMode(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_MSTR));
}



/**
 * @brief  设定SPI数据传输高低位顺序.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransferBitOrder: 数据传输高低位顺序选择 @ref SPI_BIT_ORDER_SELECTION
 * @retval None
 */
void SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t u32TransferBitOrder)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_LSBF, u32TransferBitOrder);
}


/**
 * @brief  获取SPI数据传输高低位顺序.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t:数据传输高低位顺序选择 @ref SPI_BIT_ORDER_SELECTION
 */
uint32_t SPI_GetTransferBitOrder(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_LSBF));
}


/**
 * @brief  设定SPI每帧的数据宽度.
 * @param  [in] SPIx :SPI结构体变量                        @ref SPI_TypeDef
 * @param  [in] u32DataWidth : 数据宽度                    @ref SPI_DATAWIDTH_SELECTION
 * @retval None
 */
void SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t u32DataWidth)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_WIDTH, u32DataWidth);
}


/**
 * @brief  获取SPI每帧的数据宽度.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 数据宽度 @ref SPI_DATAWIDTH_SELECTION
 */
uint32_t SPI_GetDataWidth(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_WIDTH));
}


/**
 * @brief  设定SPI NSS模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSMode:  NSS从机选择 @ref SPI_NSS_CFG
 * @retval None
 */
void SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t u32NSSMode)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_SSM, u32NSSMode);
}


/**
 * @brief  获取SPI NSS模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: NSS从机选择 @ref SPI_NSS_CFG
 */
uint32_t SPI_GetNSSMode(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_SSM));
}


/**
 * @brief  SPI模块作为从机时，配置NSS片选使能或禁止，只有当SSM=1，即软件控制(非外部IO管脚输入)时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSCfg: NSS选择 @ref SPI_NSS_CFG
 * @retval None
 */
void SPI_SlaveNSSConfig(SPI_TypeDef *SPIx, uint32_t u32NSSCfg)
{
    REG_MODIFY(SPIx->SSI, SPI_SSI_SSI, u32NSSCfg);
}


/**
 * @brief  SPI模块作为主机 配置NSS片选输出(到从机)，只有当SSM=1，即硬件控制输出(外部IO管脚NSS输出)时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSCfg: NSS选择 @ref SPI_NSS_CFG
 * @retval None
 */
void SPI_MasterNSSOutput(SPI_TypeDef *SPIx, uint32_t u32NSSCfg)
{
    REG_MODIFY(SPIx->SSI, SPI_SSI_SSI, u32NSSCfg);
}

/**
 * @brief  获取SPI SSI的值， 只有SSM=1时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 片选使能位状态 @ref SPI_NSS_SOFT_VAL
 */
uint32_t SPI_GetNSSSoftValue(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->SSI, SPI_SSI_SSI));
}


/**
 * @brief  获取SPI SSI的值，只有SSM=1时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 外部NSS管脚返回电平 @ref SPI_NSS_EXT_INPUT_LEVEL
 */
uint32_t SPI_GetNSSExtInput(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->SR, SPI_SR_SSLVL));
}


/**
 * @brief  设定SPI 通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransferDirection: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION
 * @retval None
 */
void SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_CM, u32TransferDirection);
}


/**
 * @brief  获取SPI 通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION
 */
uint32_t SPI_GetTransferDirection(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_CM));
}


/**
 * @brief  设定SPI 半双工通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransferDirection: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION
 * @retval None
 */
void SPI_SetHalfDuplexDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection)
{
    REG_MODIFY(SPIx->HDOE, SPI_HDOE_HDOE, u32TransferDirection);
}


/**
 * @brief  获取SPI 半双工通信方式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION
 */
uint32_t SPI_GetHalfDuplexDirection(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->HDOE, SPI_HDOE_HDOE));
}


/**
 * @brief  SPI 中断使能.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ITEn: SPI中断使能选择位 @ref SPI_IT_SELECTION
 * @retval None
 */
void SPI_EnableIT(SPI_TypeDef* SPIx, uint32_t u32ITEn)
{
    REG_SETBITS(SPIx->CR1, u32ITEn);
}


/**
 * @brief  SPI中断 禁止.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI中断使能选择位 @ref SPI_IT_SELECTION
 * @retval None
 */
void SPI_DisableIT(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    REG_CLEARBITS(SPIx->CR1, u32IT);
}


/**
 * @brief  检查 中断 是否已使能.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI中断使能选择位 @ref SPI_IT_SELECTION
 * @retval uint32_t :中断状态
 *         - 0:未开启
 *         - 非0:已开启
 */
uint32_t SPI_IsEnableIT(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    uint32_t res = (REG_READBITS(SPIx->CR1, u32IT) == u32IT)?(1U):(0U);
    return res;
}


/**
 * @brief  获取 SPI 中断标志位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI中断使能选择位 @ref SPI_FLAG_SELECTION
 * @retval uint32_t :中断状态
 *         - 0:未发生中断
 *         - 非0:发生中断
 */
uint32_t SPI_IsActiveFlag(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    uint32_t res = (REG_READBITS(SPIx->SR, u32IT) == u32IT)?(1U):(0U);
    return res;
}


/**
 * @brief  清除 SPI 中断标志位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI清除中断标志位选择 @ref SPI_CLEAR_SELECTION
 * @retval None
 */
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    REG_CLEARBITS(SPIx->ICR, u32IT);
}

/**
 * @brief  清除 SPI 所有中断 标志.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval NONE
 */
void SPI_ClearFlag_ALL(SPI_TypeDef* SPIx)
{
    SPIx->ICR = (uint32_t)(0);
}



/**
 * @brief SPI 发送缓冲空标志 置位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval None
 */
void SPI_SetFlag_TXE(SPI_TypeDef* SPIx)
{
    REG_CLEARBITS(SPIx->ICR, SPI_ICR_TXE);
}


/**
 * @brief  SPI 发送一数据函数.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data: 发送数据
 * @retval en_result_t:
 *         - Ok: 发送成功
 */
en_result_t Spi_SendData(SPI_TypeDef* SPIx, uint16_t u16Data)
{
    SPIx->DR = u16Data;

    return Ok;
}

/**
 * @brief  SPI 读/写一数据函数.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data: 发送一数据
 * @retval uint8_t:接收一数据
 */
uint16_t Spi_RWByte(SPI_TypeDef* SPIx, uint16_t u16Data)
{
    while(FALSE == SPIx->SR_f.TXE)
    {
     }
    SPIx->DR = u16Data;
    while(FALSE == SPIx->SR_f.RXNE)
    {
    }
    return (uint16_t)(SPIx->DR);
}

/**
 * @brief  SPI 从机预准备第一个数据
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data: 预准备第一个数据
 * @retval None
 */
void Spi_Slave_DummyWriteData(SPI_TypeDef* SPIx, uint16_t u16Data)
{
    while(FALSE == SPIx->SR_f.TXE)
    {
    }
    SPIx->DR = u16Data;
}


/**
 * @brief  SPI 连续发送接收多个数据函数
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] pu16SendBuf: 发送数据指针
 * @param  [in] pu16RecBuf: 接收数据指针
 * @param  [in] u32Len: 发送数据长度
 * @retval en_result_t:
 *         - Ok: SPI初始化成功
 */
en_result_t Spi_Send_Rec_Buf(SPI_TypeDef* SPIx, uint16_t pu16SendBuf[],uint16_t pu16RecBuf[], uint32_t u32Len)
{
    uint32_t u32Index = 0u;

    for(u32Index = 0u; u32Index<u32Len; u32Index++)
    {
        while(FALSE == SPIx->SR_f.TXE)
        {
        }

        SPIx->DR = pu16SendBuf[u32Index];

        while(FALSE == SPIx->SR_f.RXNE)
        {
        }

        pu16RecBuf[u32Index] = (uint16_t)SPIx->DR;
    }

    while(FALSE == SPIx->SR_f.TXE)
    {
    }
    while(TRUE == SPIx->SR_f.BUSY)
    {
    }

    return Ok;
}

/**
 * @brief  SPI 接收一数据函数
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval uint8_t:接收一数据
 */
uint16_t Spi_ReceiveData(SPI_TypeDef* SPIx)
{
    return (uint16_t)SPIx->DR;
}

/* ========================================================================== */
/*  sysctrl.c                                                                 */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @brief SYSCTRL Driver Library SYSCTRL模块驱动库
 * @{
 */


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Macros SYSCTRL局部宏定义
 * @{
 */

/**
 * @defgroup SYSCTRL_CLK_TIMEOUT 超时定义值
 * @{
 */
#define CLK_TIMEOUT                 (1000000u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_IN_DIV PLL输入时钟源分频倍数范围定义
 * @{
 */
#define SYSCTRL_PLL_IN_DIV_MIN      (1u)
#define SYSCTRL_PLL_IN_DIV_MAX      (2u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_MULLN PLL 整数倍频范围定义
 * @{
 */
#define SYSCTRL_PLL_MULLN_MIN       (2u)
#define SYSCTRL_PLL_MULLN_MAX       (128u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_MULLF PLL 小数倍频范围定义
 * @{
 */
#define SYSCTRL_PLL_MULLF_MIN       (0u)
#define SYSCTRL_PLL_MULLF_MAX       (7u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_OUT_DIV PLL 输出分频定义
 * @{
 */
#define SYSCTRL_PLL_OUT_DIV_MIN     (4u)
#define SYSCTRL_PLL_OUT_DIV_MAX     (34u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_FVCO PLL Fvco范围定义
 * @{
 */
#define SYSCTRL_PLL_FVCO_MIN        (384000000u)
#define SYSCTRL_PLL_FVCO_MAX        (512000000u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_OUT PLL 输出频率范围定义
 * @{
 */
#define SYSCTRL_PLL_OUT_MIN         (15000000u)
#define SYSCTRL_PLL_OUT_MAX         (64000000u)
/**
 * @}
 */
/**
 * @defgroup RCL_CR_TRIM RCL trim值地址定义
 * @{
 */
#define RCL_CR_TRIM_38400_VAL       (0x00101BE8u)
#define RCL_CR_TRIM_32768_VAL       (0x00101BEAu)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Variables SYSCTRL全局变量定义
 * @{
 */
extern uint32_t SystemCoreClock;
/**
 * @}
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Variables SYSCTRL局部变量定义
 * @{
 */

static const uint32_t au32RCHFreqTable[4] = {
                                              1u,
                                              2u,
                                              3u,
                                              4u
                                            };
/**
 * @}
 */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Functions SYSCTRL局部函数定义
 * @{
 */
static void _SysctrlUnlock(void);
/**
* @}
*/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Functions SYSCTRL局部函数定义
 * @{
 */
/**
 * @brief SYSCTRL0\SYSCTRL1寄存器操作解锁
 *
 * @retval None
 */
static void _SysctrlUnlock(void)
{
    HC_SYSCTRL->CR3 = 0x5A5Au;
    HC_SYSCTRL->CR3 = 0xA5A5u;
}
/**
* @}
*/

/**
 * @defgroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */

/**
 * @brief 系统时钟源使能
 * @param [in]  enSource   目标时钟源 @ref en_sysctrl_clk_source_t
 * @param [in]  bFlag      TRUE:开/FALSE:关
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 * - 注意:使能RCH/RCL，优先设置RCH/RCL相关参数!!!
 * - 注意:使能XTH/XTL，必须先设置XTH和XTL频率、驱动能力、稳定时间等参数!!!
 * - 注意:使能PLL之前，需确保PLL配置成功!!!
 */
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;

    bFlag = bFlag  ? TRUE : FALSE;

    u32Temp = HC_SYSCTRL->PERICLKEN1;
    switch (enSource)
    {
        case SysctrlClkRCH:
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.RCH = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.RCH) && bFlag)
            {
                ;
            }
            break;

        case SysctrlClkXTH:
            HC_SYSCTRL->PERICLKEN1_f.GPIOD = 1u;
            HC_GPIOD->ADS |= 3u;
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.XTH = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.XTH) && bFlag)
            {
                ;
            }
			delay1ms(10);
            break;

        case SysctrlClkRCL:
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.RCL = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.RCL) && bFlag)
            {
                ;
            }
            break;

        case SysctrlClkXTL:
            HC_SYSCTRL->PERICLKEN1_f.GPIOC = TRUE;
            HC_GPIOC->ADS |= 0xC000u;
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.XTL = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.XTL) && bFlag)
            {
                ;
            }
            break;

        case SysctrlClkPLL:
            HC_SYSCTRL->PERICLKEN0_f.ADC = TRUE;
            HC_ADC->BGR_f.BGREN = TRUE;
            delay100us(2u);
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.PLL = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.PLL) && bFlag)
            {
                ;
            }
            break;

        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    HC_SYSCTRL->PERICLKEN1 = u32Temp;

    return enRet;
}


/**
 * @brief 内部高速时钟RCH目标频率设置
 *
 * @param [in]  enRCHFreq  设定的RCH目标频率值 @ref en_sysctrl_rch_freq_t
 *
 * @retval  en_result_t:
 *            - Ok:  设定成功
 *            - 其他: 设定失败或时钟未稳定
 */
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq)
{
    /* 加载RCH 分频值 */
    HC_SYSCTRL->RCHCR_f.DIV = enRCHFreq;

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();

    return Ok;
}


/**
 * @brief 内部低速时钟频率TRIM值加载
 *
 * @param [in]  enRCLFreq  设定的RCL目标频率值 @ref en_sysctrl_rcl_freq_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq)
{
    uint16_t u16Val;
    u16Val = ((SysctrlRclFreq38400 == enRCLFreq) ? (*(volatile uint16_t*)(RCL_CR_TRIM_38400_VAL )) :\
                                                   (*(volatile uint16_t*)(RCL_CR_TRIM_32768_VAL )));
    HC_SYSCTRL->RCLTRIM_f.TRIM  = u16Val;

    return Ok;
}

/**
 * @brief 内部低速时钟稳定周期配置
 *
 * @param [in]  enCycle     内部低速时钟稳定周期设置 @ref en_sysctrl_rcl_cycle_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    HC_SYSCTRL->RCLCR_f.STARTUP = enCycle;
    return enRet;
}


/**
 * @brief 外部高速时钟频率范围设定
 *
 * @param [in]  enXTHFreq  设定的频率值 @ref en_sysctrl_xth_freq_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败或时钟未稳定
 */
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq)
{
    en_result_t enRet = Ok;

    HC_SYSCTRL->XTHCR_f.RANGE = enXTHFreq;

    return enRet;
}


/**
 * @brief 外部高速晶振驱动配置
 *
 * @param [in]  enDriver   外部高速晶振驱动能力选择 @ref en_sysctrl_xtal_driver_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    HC_SYSCTRL->XTHCR_f.DRIVER   = enDriver;

    return enRet;
}

/**
 * @brief 外部高速时钟稳定周期配置
 *
 * @param [in]  enCycle     外部高速时钟稳定周期设置 @ref en_sysctrl_xth_cycle_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    HC_SYSCTRL->XTHCR_f.STARTUP = enCycle;
    return enRet;
}

/**
 * @brief 外部低速晶振驱动配置
 *
 * @param [in]  enAmp:      外部低速晶振频率范围选择 @ref en_sysctrl_xtl_amp_t
 * @param [in]  enDriver:   外部低速晶振驱动能力选择 @ref en_sysctrl_xtal_driver_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_XTLDriverCfg(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    HC_SYSCTRL->XTLCR_f.AMP_SEL = enAmp;
    HC_SYSCTRL->XTLCR_f.DRIVER  = enDriver;

    return enRet;
}

/**
 * @brief 外部低速时钟稳定周期配置
 *
 * @param [in]  enCycle     外部低速时钟稳定周期设置 @ref en_sysctrl_xtl_cycle_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    HC_SYSCTRL->XTLCR_f.STARTUP = enCycle;
    return enRet;
}


/**
 * @brief 设置XTH/XTL 失效检测功能
 *
 * @param [in]  u32OscSel      XTH/XTL选择  @ref XTH_XTL_Fail_Det_Sel
 * @param [in]  pstcCfg        失效检测结构体 @ref stc_sysctrl_fail_det_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_ExtOscFailDetCfg(uint32_t u32OscSel, stc_sysctrl_fail_det_cfg_t* pstcCfg)
{
    uint32_t u32BaseAddress;

    u32BaseAddress = (uint32_t)(&HC_SYSCTRL->XTHCR) + u32OscSel;

    REG_MODIFY(*(volatile uint32_t *)u32BaseAddress, \
               SYSCTRL_XTHCR_DETEN | SYSCTRL_XTHCR_DETTIME | SYSCTRL_XTHCR_DETIE,\
               pstcCfg->u32DetectEn | pstcCfg->u32DetectTime | pstcCfg->u32DetectIntEn);

    return Ok;
}

/**
 * @brief PLL时钟配置
 *
 * @param [in]  pstcPLLCfg PLL配置结构体指针  @ref stc_sysctrl_pll_cfg_t
 *              - 注意:调用PLL配置函数需要判断返回值，确保参数配置成功!!!
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败或参数值不匹配
 */
en_result_t Sysctrl_SetPLLFreq(stc_sysctrl_pll_cfg_t *pstcPLLCfg)
{
    en_result_t enRet = Ok;
    uint32_t u32Fin;
    volatile uint32_t u32Fvco, u32PllOut;

    /* PLL最高时钟不能超过64MHz */
    if((pstcPLLCfg->u8SourceDiv < SYSCTRL_PLL_IN_DIV_MIN) || (pstcPLLCfg->u8SourceDiv > SYSCTRL_PLL_IN_DIV_MAX))
    {
        return ErrorInvalidParameter;
    }
    if((pstcPLLCfg->u8MullN < SYSCTRL_PLL_MULLN_MIN) || (pstcPLLCfg->u8MullN > SYSCTRL_PLL_MULLN_MAX))
    {
        return ErrorInvalidParameter;
    }
    if(pstcPLLCfg->u8MullF > SYSCTRL_PLL_MULLF_MAX)
    {
        return ErrorInvalidParameter;
    }
    if((pstcPLLCfg->u8OutputDiv < SYSCTRL_PLL_OUT_DIV_MIN) || (pstcPLLCfg->u8OutputDiv > SYSCTRL_PLL_OUT_DIV_MAX))
    {
        return ErrorInvalidParameter;
    }

    if(0x01u == (pstcPLLCfg->u8OutputDiv & 0x01u))
    {
        return ErrorInvalidParameter;
    }

    if(SysctrlPllRch == pstcPLLCfg->enPllSource)
    {
        u32Fin = 12000000u;
    }
    else
    {
        u32Fin = SYSTEM_XTH;
    }
    u32Fin = u32Fin  / pstcPLLCfg->u8SourceDiv;
    u32Fvco = u32Fin * pstcPLLCfg->u8MullN + ((u32Fin * pstcPLLCfg->u8MullF)>>3u);
    if(u32Fvco < SYSCTRL_PLL_FVCO_MIN)
    {
        return ErrorInvalidParameter;
    }
    if(u32Fvco > SYSCTRL_PLL_FVCO_MAX)
    {
        return ErrorInvalidParameter;
    }
    u32PllOut = u32Fvco / pstcPLLCfg->u8OutputDiv;
    if(u32PllOut < SYSCTRL_PLL_OUT_MIN)
    {
        return ErrorInvalidParameter;
    }
    if(u32PllOut > SYSCTRL_PLL_OUT_MAX)
    {
        return ErrorInvalidParameter;
    }

    REG_WRITE(HC_SYSCTRL->PLLCR, pstcPLLCfg->enPllSource | \
                                  (((uint32_t)pstcPLLCfg->u8SourceDiv-1u)<<SYSCTRL_PLLCR_DIVR_Pos) |\
                                  (((uint32_t)pstcPLLCfg->u8MullN-2u)<<SYSCTRL_PLLCR_DIVN_Pos) | \
                                  (uint32_t)pstcPLLCfg->u8MullF<<SYSCTRL_PLLCR_DIVF_Pos |\
                                  ((((uint32_t)pstcPLLCfg->u8OutputDiv>>1u) -2u)<<SYSCTRL_PLLCR_POSTDIV_Pos));

    REG_MODIFY(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_WAITCYCLE, (uint32_t)pstcPLLCfg->enStableWaitCycle);

    return enRet;
}




/**
 * @brief 时钟源切换，该函数执行后会开启新时钟源
 *
 * @note  选择时钟源之前，需根据需要配置目标时钟源的频率/驱动参数/使能时钟源等!!!
 *
 * @param [in]  enSource   新时钟源  @ref en_sysctrl_clk_source_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 * - 注意1：调用此函数前，必须确保新的系统时钟源的相关参数已经初始化，并且新时钟源已经使能且稳定运行
 * - 注意2: 时钟切换前，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2
 * - 注意3: 当HCLK大于24MHz小于48MH在时，FLASH等待周期插入必须至少为1,否则程序运行可能产生未知错误
 * - 注意4: 当HCLK大于48MHz时，FLASH等待周期插入必须至少为2,否则程序运行可能产生未知错误
 */
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource)
{
    en_result_t enRet = Ok;

    en_sysctrl_clk_source_t ClkNew = enSource;

    _SysctrlUnlock();
    HC_SYSCTRL->CR0_f.CLKSRC = ClkNew;

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();

    return enRet;
}

/**
 * @brief 系统时钟 HCLK 频率获取
 *
 * @retval uint32_t：HCLK频率值(Hz)
 */
uint32_t Sysctrl_GetHClkFreq(void)
{
    uint16_t u16RCL32p8;
    uint32_t u32ValHclk, u32Fin,  u32Fdivn, u32Fdivf;

    u16RCL32p8  = SYSCTRL_RCL_TRIM_32p8KHz;


    /* Update [SystemCoreClock]*/
    if(SYSCTRL_SYSCLK_SOURCE_XTH == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        u32ValHclk = SYSTEM_XTH;
    }

    if(SYSCTRL_SYSCLK_SOURCE_RCL == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        if(u16RCL32p8 == (REG_READBITS(HC_SYSCTRL->RCLTRIM, SYSCTRL_RCLTRIM_TRIM)))
        {
            u32ValHclk = 32768u;
        }
        else
        {
            u32ValHclk = 38400u;
        }
    }

    if(SYSCTRL_SYSCLK_SOURCE_XTL == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        u32ValHclk = SYSTEM_XTL;
    }

    if(SYSCTRL_SYSCLK_SOURCE_PLL == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        if(SysctrlPllRch == REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_SRC))
        {
            u32ValHclk = 12000000u;
        }
        else
        {
            u32ValHclk = SYSTEM_XTH;
        }

        u32Fin = u32ValHclk /((REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_DIVR) >> SYSCTRL_PLLCR_DIVR_Pos) + 1u);
        u32Fdivn = u32Fin * ((REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_DIVN) >> SYSCTRL_PLLCR_DIVN_Pos) + 2u);
        u32Fdivf = (u32Fin * (REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_DIVF) >> SYSCTRL_PLLCR_DIVF_Pos)) >> 3;
        u32ValHclk = ((u32Fdivn + u32Fdivf) / ((REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_POSTDIV) >> SYSCTRL_PLLCR_POSTDIV_Pos) + 2u)) >> 1;
    }

    if(SYSCTRL_SYSCLK_SOURCE_RCH == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        u32ValHclk = 12000000u;

        u32ValHclk = u32ValHclk / au32RCHFreqTable[REG_READBITS(HC_SYSCTRL->RCHCR, SYSCTRL_RCHCR_DIV) >> SYSCTRL_RCHCR_DIV_Pos];

    }

    u32ValHclk = u32ValHclk >> (REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_HCLKPRS) >> SYSCTRL_CR0_HCLKPRS_Pos);

    return u32ValHclk;
}

/**
 * @brief 获得外设时钟（PCLK）频率值
 *
 * @retval uint32_t：PCLK频率值(Hz)
 */
uint32_t Sysctrl_GetPClkFreq(void)
{
    uint32_t u32Val = 0u;

    u32Val = Sysctrl_GetHClkFreq();
    u32Val = (u32Val >> (HC_SYSCTRL->CR0_f.PCLKPRS));

    return u32Val;
}

/**
 * @brief 时钟去初始化函数
 * @恢复为上电默认状态->PCLK=HCLK=SystemClk=RCH4MHz
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_ClkDeInit(void)
{
    en_result_t enRet = Ok;

    /* 配置RCH为内部4Hz */
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);

    /* 时钟源使能 */
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);

    /* 时钟源切换 */
    Sysctrl_SysClkSwitch(SysctrlClkRCH);

    /* 其它时钟源使能关闭 */
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, FALSE);

    /* 时钟分频设置 */
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();

    return enRet;
}



/**
 * @brief 系统时钟（HCLK）分频设定
 *
 * @param [in]  enHCLKDiv  分频设定值 @ref en_sysctrl_hclk_div_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv)
{
    _SysctrlUnlock();
    HC_SYSCTRL->CR0_f.HCLKPRS = enHCLKDiv;

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();

    return Ok;
}

/**
 * @brief 外设时钟（PCLK）分频设定
 *
 * @param [in]  enPCLKDiv  分频设定值  @ref en_sysctrl_pclk_div_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv)
{
    _SysctrlUnlock();
    HC_SYSCTRL->CR0_f.PCLKPRS = enPCLKDiv;

    return Ok;
}


/**
 * @brief 设置外设时钟门控开关
 * @设置外设时钟门控开关:用于控制外设模块的使能,使用该模块的功能之前,必须使能该模块的门控时钟
 * @param [in]  enPeripheral   目标外设  @ref en_sysctrl_peripheral_gate_t
 * @param [in]  bFlag          TRUE:开/FALSE:关
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag)
{
    if(enPeripheral & _PERICLK_REG1_MSK)
    {
        /* C++: 枚举不可直接复合赋值位掩码, 显式转换, 语义与 C 一致 */
        enPeripheral = (en_sysctrl_peripheral_gate_t)((uint32_t)enPeripheral & ~(uint32_t)_PERICLK_REG1_MSK);

        REG_MODIFY(HC_SYSCTRL->PERICLKEN1, 1u<<((uint32_t)enPeripheral), ((uint32_t)bFlag)<<((uint32_t)enPeripheral));

    }
    else
    {
        REG_MODIFY(HC_SYSCTRL->PERICLKEN0, 1u<<((uint32_t)enPeripheral), ((uint32_t)bFlag)<<((uint32_t)enPeripheral));
    }

    return Ok;
}

/**
 * @brief 获得外设时钟门控开关状态 @ref en_sysctrl_peripheral_gate_t
 *
 * @param [in]  enPeripheral   目标外设
 *
 * @retval boolean_t:
 *                - TRUE: 开
 *                - FALSE: 关
 */
boolean_t Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral)
{
    if(enPeripheral&_PERICLK_REG1_MSK)
    {
        /* C++: 枚举不可直接复合赋值位掩码, 显式转换, 语义与 C 一致 */
        enPeripheral = (en_sysctrl_peripheral_gate_t)((uint32_t)enPeripheral & ~(uint32_t)_PERICLK_REG1_MSK);

        return REG_READBITS(HC_SYSCTRL->PERICLKEN1, 1u<<((uint32_t)enPeripheral)) ? TRUE : FALSE;
    }
    else
    {
        return REG_READBITS(HC_SYSCTRL->PERICLKEN0, 1u<<((uint32_t)enPeripheral)) ? TRUE : FALSE;
    }
}

/**
 * @brief 系统功能设定
 *
 * @param [in]  enFunc     系统功能枚举类型  @ref en_sysctrl_func_t
 * @param [in]  bFlag      TRUE:开/FALSE:关
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag)
{
    if(enFunc & _SYSCTRL_FUNC_MSK)
    {
        enFunc = (en_sysctrl_func_t)((uint32_t)enFunc & ~(uint32_t)_SYSCTRL_FUNC_MSK);
        _SysctrlUnlock();
        REG_MODIFY(HC_SYSCTRL->CR2, 1u<<((uint32_t)enFunc), ((uint32_t)bFlag)<<((uint32_t)enFunc));

    }
    else
    {
        _SysctrlUnlock();
        REG_MODIFY(HC_SYSCTRL->CR1, 1u<<((uint32_t)enFunc), ((uint32_t)bFlag)<<((uint32_t)enFunc));
    }
    return Ok;
}


/**
 * @brief 获取外部时钟起振标志
 *
 * @param [in]  u32ExtOscFlag  外部时钟起振标志类型  @ref XTH_XTL_Flag_Type
 *
 * @retval boolean_t:
 *                - TRUE: 失败
 *                - FALSE: 成功
 */
boolean_t Sysctrl_GetExtOscFlag(uint32_t u32ExtOscFlag)
{
    return REG_READBITS(HC_SYSCTRL->STATE, u32ExtOscFlag) ? TRUE : FALSE;
}


/**
 * @brief 清除外部时钟起振标志
 *
 * @param [in]  u32ExtOscFlag  外部时钟起振标志类型  @ref XTH_XTL_Flag_Type
 *
 * @retval boolean_t:
 *                - TRUE: 失败
 *                - FALSE: 成功
 */
en_result_t Sysctrl_ClrExtOscFlag(uint32_t u32ExtOscFlag)
{
    REG_CLEARBITS(HC_SYSCTRL->STATE, u32ExtOscFlag);

    return Ok;
}

/**
 * @brief 设定RTC校准时钟频率
 *
 * @param [in]  enRtcAdj   校准频率 @ref en_sysctrl_rtc_adjust_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetRTCAdjustClkFreq(en_sysctrl_rtc_adjust_t enRtcAdj)
{
    _SysctrlUnlock();
    HC_SYSCTRL->CR1_f.RTCADJ = enRtcAdj;

    return Ok;
}


/**
 * @brief 系统外设复位
 *
 * @param [in]  enPeripheral 系统外设复位 @ref en_sysctrl_peripheral_gate_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_PeriphReset(en_sysctrl_peripheral_gate_t enPeripheral)
{
    en_result_t enRet = Ok;

    if(enPeripheral > SysctrlPeripheralFlash)
    {
        enPeripheral = (en_sysctrl_peripheral_gate_t)((uint32_t)enPeripheral & ~(uint32_t)_PERICLK_REG1_MSK);
        REG_CLEARBITS(HC_SYSCTRL->PERIRESET1, 1u<<((uint32_t)enPeripheral));
        REG_SETBITS(HC_SYSCTRL->PERIRESET1, 1u<<((uint32_t)enPeripheral));
    }
    else if(enPeripheral < SysctrlPeripheralFlash)
    {
        REG_CLEARBITS(HC_SYSCTRL->PERIRESET0, 1u<<((uint32_t)enPeripheral));
        REG_SETBITS(HC_SYSCTRL->PERIRESET0, 1u<<((uint32_t)enPeripheral));
    }
    else
    {
        enRet = Error;
    }

    return enRet;
}

/**
 * @brief 系统复位标志清除
 *
 * @param [in]  u32ResetFlag 系统复位标志 @ref Sysctrl_Reset_Flag
 *
 * @retval None
 */
void Sysctrl_ResetFlagClear(uint32_t u32ResetFlag)
{
    REG_CLEARBITS(HC_SYSCTRL->RSTFLAG, u32ResetFlag);
}


/**
 * @brief 系统复位标志获取
 *
 * @param [in]  u32ResetFlag 系统复位标志 @ref Sysctrl_Reset_Flag
 *
 * @retval uint32_t：复位标志
 */
uint32_t Sysctrl_ResetFlagGet(uint32_t u32ResetFlag)
{
    return REG_READBITS(HC_SYSCTRL->RSTFLAG, u32ResetFlag);
}

/**
 * @brief 系统调试功能控制使能,调试状态下暂停模块计数
 *
 * @param [in]  u32DebugModule 系统调试功能定义 @ref Sysctrl_Debug_Module
 *
 * @retval None
 */
void Sysctrl_DebugEnable(uint32_t u32DebugModule)
{
    REG_SETBITS(HC_SYSCTRL->DBGSTOP, u32DebugModule);
}

/**
 * @brief 系统调试功能控制禁止，调试状态下模块计数继续
 *
 * @param [in]  u32DebugModule 系统复位标志 @ref Sysctrl_Debug_Module
 *
 * @retval None
 */
void Sysctrl_DebugDisable(uint32_t u32DebugModule)
{
    REG_CLEARBITS(HC_SYSCTRL->DBGSTOP, u32DebugModule);
}


/**
 * @brief 获取芯片相关信息
 *
 * @param [in]  pstcChipInfo 芯片信息结构体指针 @ref stc_sysctrl_chip_info_t
 *
 * @retval None
 */
void Sysctrl_GetChipInfo(stc_sysctrl_chip_info_t *pstcChipInfo)
{
    //pstcChipInfo->pu8UID          = (uint8_t*)0x0010xxxx;
    pstcChipInfo->pcProductNumber = (char_t*)0x00101B40;
    pstcChipInfo->u32FlashSize    = *((uint32_t*)0x00101B60);
    pstcChipInfo->u32RamSize      = *((uint32_t*)0x00101B64);
    pstcChipInfo->u16PinsCounter  = *((uint16_t*)0x00101B6A);
}

/* ========================================================================== */
/*  usart.c                                                                   */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */
/**
 * @defgroup DDL_USART USART子模块驱动库
 * @brief USART Driver Library USART子模块驱动库
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Functions USART全局函数定义
 * @{
 */

/**
 * @brief  USART 波特率初始化函数
 * @param  [in] USARTx:             USART类型定义      @ref USART_TypeDef
 * @param  [in] u32BaudRateSetMode: 波特率设置模式选择 @ref USART_BAUD_RATE_SET_MODE
 * @param  [in] u32BaudRate:        UART波特率
 * @param  [in] u32PCLK:            PCLK时钟
 * @param  [in] u32SampMode:        采样次数选择       @ref USART_SAMPLE_BITS_SET （时钟同步模式、红外通信模式）
 *                                                     @ref USART_Over_Sampling   （UART模式、LIN模式）
 *                                                     @ref USART_SC_BCN_SET      （智能卡接口模式）
 * @retval uint32_t：               计算的波特率
 *         - 0：                    配置失败
 *         - 非0：                  计算的波特率
 */
uint32_t USART_BaudRateCal(USART_TypeDef* USARTx, uint32_t u32BaudRateSetMode, uint32_t u32BaudRate, uint32_t u32PCLK, uint32_t u32SampMode)
{
    uint64_t u64PCLK, u64BoudRate, u64Temp, u64TempCal, u64MinOffset;
    uint32_t u32Sample         = 0U;   /* Sampel value */
    uint64_t u64TempDIVI[4]    = {0U}; /* DIVI */
    uint64_t u64TempDIVF[4]    = {0U}; /* DIVF */
    uint64_t u64CalBaudRate[4] = {0U}; /* Calculated Baud Rate */
    uint32_t u32TempIdx        = 0U;   /* Index for u32TempDIVI & u32TempDIVF */
    uint32_t u32BaudRateIdx    = 0U;   /* Index for Baud Rate */

    u64PCLK     = (uint64_t)u32PCLK;
    u64BoudRate = (uint64_t)u32BaudRate;

    if (0U != u64BoudRate)
    {
        switch (u32BaudRateSetMode)
        {
            case USART_BAUD_RATE_UART:
            case USART_BAUD_RATE_LIN:
                /* BPS = (PCLK×(128+DIVF))/(4^psc×8×(2-OVER8)×(DIVI+1)×256) */
                if (USART_OVERSAMPLING_16 == u32SampMode)
                {
                    u32Sample = 2U * 8U; /* (2-OVER8) = 2 */
                }
                else
                {
                    u32Sample = 1U * 8U; /* (2-OVER8) = 1 */
                }
                break;
            case USART_BAUD_RATE_CLKSYNC:
            case USART_BAUD_RATE_IR:
                /* CLKSYNC BPS = (PCLK×(128+DIVF))/(4^psc×4×(DIVI+1)×256) */
                /* IR      BPS = (PCLK×(128+DIVF))/(4^psc×16×(DIVI+1)×256) */
                u32Sample = u32SampMode;
                break;
            case USART_BAUD_RATE_SC:
                /* BPS = (PCLK×(128+DIVF))/(4^psc×2×BCN×(DIVI+1)×256) */
                u32Sample = 2U * u32SampMode;
                break;
            default:
                break;
        }

        if (u32Sample == 0U)
        {
            /* Invalid setting*/
            return 0U;
        }

        u64Temp = u64PCLK / (u64BoudRate * u32Sample); /* = PCLK / (BPS * 8 * (2-OVER8) */
        if (0U == u64Temp)
        {
            /* Invalid setting*/
            return 0U;
        }
        for (u32TempIdx = 0U; u32TempIdx < 4U; u32TempIdx++)
        {
            /* Cal DIVI */
            u64TempDIVI[u32TempIdx] = u64Temp >> (2U * u32TempIdx); /* = / 4^psc */
            if (256U < u64TempDIVI[u32TempIdx])                     /* DIVI <= 256 */
            {
                u64TempDIVI[u32TempIdx] = 0U;
            }
            if (0U != u64TempDIVI[u32TempIdx])
            {
                /* Cal DIVF */
                u64TempCal = u32Sample * u64TempDIVI[u32TempIdx];
                u64TempDIVF[u32TempIdx] =
                    ((((u64BoudRate * u64TempCal * 256U) << (2U * u32TempIdx)) * 10U / u64PCLK) + 5U) / 10U - 128U; /* with round up */
                if (127U < u64TempDIVF[u32TempIdx])
                {
                    /* Calcualte baud rate: DIVF is disabled */
                    u64CalBaudRate[u32TempIdx] = u64PCLK / (u64TempCal << (2U * u32TempIdx));
                }
                else
                {
                    /* Calcualte baud rate: DIVF is enabled */
                    u64CalBaudRate[u32TempIdx] = u64PCLK * (128U + u64TempDIVF[u32TempIdx]) / (u64TempCal << (2U * u32TempIdx)) / 256U;
                }
            }
        }

        /* Out of range check */
        for (u32TempIdx = 0U; u32TempIdx < 4U; u32TempIdx++)
        {
            if (u64TempDIVI[u32TempIdx] != 0U)
            {
                break;
            }
            if (u32TempIdx == 3U)
            {
                /* Invalid setting*/
                return 0U;
            }
        }

        /* Find best fit baud rate */
        u64MinOffset = 0xFFFFFFFFU;
        for (u32TempIdx = 0U; u32TempIdx < 4U; u32TempIdx++)
        {
            if (0U != u64TempDIVI[u32TempIdx])
            {
                u64Temp = (u64CalBaudRate[u32TempIdx] > u32BaudRate) ? (u64CalBaudRate[u32TempIdx] - u32BaudRate) :
                                                                       (u32BaudRate - u64CalBaudRate[u32TempIdx]);
                if (u64Temp < u64MinOffset)
                {
                    u64MinOffset   = u64Temp;
                    u32BaudRateIdx = u32TempIdx;
                }
            }
        }

        if (u32BaudRateSetMode == USART_BAUD_RATE_CLKSYNC)
        {
            /* 时钟同步最高波特率 >= PCLK/8 */
            if ((0U == u32BaudRateIdx) && (1U == u64TempDIVI[0U]))
            {
                /* Invalid setting*/
                return 0U;
            }
        }

        /* Set BRR register */
        if (128U <= u64TempDIVF[u32BaudRateIdx])
        {
            REG_WRITE(USARTx->BRR, (u32BaudRateIdx << 16U) | ((u64TempDIVI[u32BaudRateIdx] - 1U) << 8U));
        }
        else
        {
            REG_WRITE(USARTx->BRR, (u32BaudRateIdx << 16U) | ((u64TempDIVI[u32BaudRateIdx] - 1U) << 8U) | u64TempDIVF[u32BaudRateIdx] | 0x80U);
        }

        /* Feedback best fit baud rate */
        return (uint32_t)u64CalBaudRate[u32BaudRateIdx];
    }
    else
    {
        /* Invalid setting*/
        return 0U;
    }
}

/**
 * @brief  USART UART初始化函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @param  [in] pstcUARTInit:  UART初始化结构体   @ref stc_usart_uart_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_UART_Init(USART_TypeDef* USARTx, stc_usart_uart_init_t* pstcUARTInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置波特率 */
    u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_UART, pstcUARTInit->u32BaudRate, Sysctrl_GetPClkFreq(), pstcUARTInit->u32SampleMode);
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcUARTInit->stcAdvFeature.u32ClockCtrl | pstcUARTInit->stcAdvFeature.u32TxRxSwap | USART_UART_MODE
                               | pstcUARTInit->stcAdvFeature.u32TxRxPinLevelInvert | pstcUARTInit->stcAdvFeature.u32HWFlowCtrl
                               | pstcUARTInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1, pstcUARTInit->stcAdvFeature.u32TxRxCombine | pstcUARTInit->stcAdvFeature.u32StartBitDetectMode
                               | pstcUARTInit->u32SampleMode | pstcUARTInit->stcAdvFeature.u32MSBFirst | pstcUARTInit->u32StopBits
                               | pstcUARTInit->u32FrameLength | pstcUARTInit->u32Parity);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    /* Tx/Rx 使能 */
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, pstcUARTInit->u32TransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART 同步串口初始化函数
 * @param  [in] USARTx:          USART类型定义      @ref USART_TypeDef
 * @param  [in] pstcClkSyncInit: UART初始化结构体   @ref stc_usart_uart_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_ClkSync_Init(USART_TypeDef* USARTx, stc_usart_clksync_init_t* pstcClkSyncInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 内部波特率生成器生成的时钟 */
    if (USART_CLKSYNC_INT_CLK_OUTPUT_EN == pstcClkSyncInit->stcAdvFeature.u32ClockCtrl)
    {
        /* 设置波特率 */
        u32CalBaudRate =
            USART_BaudRateCal(USARTx, USART_BAUD_RATE_CLKSYNC, pstcClkSyncInit->u32BaudRate, Sysctrl_GetPClkFreq(), USART_SAMPLE_BITS_CLKSYNC);
    }
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcClkSyncInit->stcAdvFeature.u32ClockCtrl | pstcClkSyncInit->stcAdvFeature.u32TxRxSwap | USART_CLKSYNC_MODE
                               | pstcClkSyncInit->stcAdvFeature.u32TxRxPinLevelInvert | pstcClkSyncInit->stcAdvFeature.u32HWFlowCtrl
                               | pstcClkSyncInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1, USART_RX_TX_SEPARATE | USART_START_BIT_RX_EDGE | USART_OVERSAMPLING_16 | pstcClkSyncInit->stcAdvFeature.u32MSBFirst
                               | USART_STOP_1BIT | USART_FRAME_LEN_8BITS | USART_PARITY_NONE);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    /* Tx/Rx 使能 */
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, pstcClkSyncInit->u32TransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART LIN初始化函数
 * @param  [in] USARTx:        USART类型定义    @ref USART_TypeDef
 * @param  [in] pstcLinInit:   LIN初始化结构体  @ref stc_usart_lin_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_LIN_Init(USART_TypeDef* USARTx, stc_usart_lin_init_t* pstcLinInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置波特率 */
    u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_LIN, pstcLinInit->u32BaudRate, Sysctrl_GetPClkFreq(), pstcLinInit->u32SampleMode);
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcLinInit->stcAdvFeature.u32TxRxSwap | USART_UART_MODE | pstcLinInit->stcAdvFeature.u32TxRxPinLevelInvert
                               | pstcLinInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1,
        pstcLinInit->u32SampleMode | pstcLinInit->stcAdvFeature.u32MSBFirst | USART_PARITY_NONE | USART_STOP_1BIT | USART_RX_TX_SEPARATE);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    return u32CalBaudRate;
}

/**
 * @brief  USART IR初始化函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @param  [in] pstcIRInit:    IR初始化结构体   @ref stc_usart_ir_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_IR_Init(USART_TypeDef* USARTx, stc_usart_ir_init_t* pstcIRInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置波特率 */
    u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_IR, pstcIRInit->u32BaudRate, Sysctrl_GetPClkFreq(), USART_SAMPLE_BITS_IR);
    /* 设置38K高低电平维持时间 */
    USARTx->IR_f.DCNTH = pstcIRInit->u32HighLevelTime38K;
    USARTx->IR_f.DCNTL = pstcIRInit->u32LowLevelTime38K;
    /* CR3设置 */
    REG_WRITE(USARTx->CR3, pstcIRInit->u32IRMode | pstcIRInit->u32IRMod38K);
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcIRInit->stcAdvFeature.u32TxRxSwap | USART_UART_MODE | pstcIRInit->stcAdvFeature.u32TxRxPinLevelInvert
                               | pstcIRInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1, USART_RX_TX_SEPARATE | USART_START_BIT_RX_EDGE | USART_OVERSAMPLING_16 | pstcIRInit->stcAdvFeature.u32MSBFirst
                               | USART_STOP_1BIT | pstcIRInit->u32FrameLength | pstcIRInit->u32Parity);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    /* Tx/Rx 使能 */
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, pstcIRInit->u32TransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART SmartCard初始化函数
 * @param  [in] USARTx:             USART类型定义    @ref USART_TypeDef
 * @param  [in] pstcSmartCardInit:  智能卡初始化结构体  @ref stc_usart_smart_card_init_t
 * @retval uint32_t:                设置的实际波特率
 */
uint32_t USART_SC_Init(USART_TypeDef* USARTx, stc_usart_smart_card_init_t* pstcSmartCardInit)
{
    uint32_t u32CalBaudRate = 0U;
    uint32_t u32Parity;
    uint32_t u32Cr3Val = 0U;   /* 原厂 default 分支未赋值, 消除 UB */

    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置时钟源波特率，智能卡模式固定16倍采样，采样计数为2*bcn */
    u32CalBaudRate =
        USART_BaudRateCal(USARTx, USART_BAUD_RATE_SC, pstcSmartCardInit->u32DataBaudRate, Sysctrl_GetPClkFreq(), pstcSmartCardInit->u32FiBCN);

    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcSmartCardInit->stcAdvFeature.u32TxRxSwap | pstcSmartCardInit->stcAdvFeature.u32ClockCtrl
                               | pstcSmartCardInit->stcAdvFeature.u32TxRxPinLevelInvert | pstcSmartCardInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    u32Parity = (USART_PARITY_EVEN == pstcSmartCardInit->u32Parity) ? USART_CR1_PCE : USART_CR1_PS | USART_CR1_PCE;
    REG_WRITE(USARTx->CR1, pstcSmartCardInit->stcAdvFeature.u32MSBFirst | USART_PARITY_NONE | USART_STOP_1BIT | USART_RX_TX_SEPARATE | u32Parity);

    /* CR3设置 */
    switch (pstcSmartCardInit->u32FiBCN)
    {
        case USART_SC_BCN_16:
            u32Cr3Val = (0ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_32:
            u32Cr3Val = (1ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_64:
            u32Cr3Val = (2ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_128:
            u32Cr3Val = (3ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_186:
            u32Cr3Val = (4ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_256:
            u32Cr3Val = (5ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_372:
            u32Cr3Val = (6ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_512:
            u32Cr3Val = (7ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        default:
            break;
    }

    REG_WRITE(USARTx->CR3, u32Cr3Val);
    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    return u32CalBaudRate;
}

/**
 * @brief  USART SmartCard时钟输出使能
 * @param  [in] USARTx: USART类型定义    @ref USART_TypeDef
 * @param  [in] bEn: 输出时钟使能(输出使能：TRUE，输出禁止：FALSE)
 * @retval uint32_t:                设置的实际波特率
 */
void USART_SC_CLK_Enable(USART_TypeDef* USARTx, boolean_t bEn)
{
    if (TRUE == bEn)
    {
        USARTx->CR2_f.CLKC = 1;
    }
    else
    {
        USARTx->CR2_f.CLKC = 0;
    }
}

/**
 * @brief  USART 查询发送数据
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART发送数据buffer指针
 * @param  [in] u32Size:     UART发送数据长度(8-bits数据传送: 字节数据长度; 9-bits数据传送: 半字数据长度)
 * @param  [in] u32Timeout:  UART发送超时时间
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 */
en_result_t USART_UART_Transmit(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t  u32SizeIdx    = 0U;
    uint32_t  u32TimeoutCnt = 0U;
    uint16_t* pu16Data      = (uint16_t*)(pu8Data);
    for (u32SizeIdx = 0U; u32SizeIdx < u32Size; u32SizeIdx++)
    {
        /* 清除发送完成标志 */
        USART_ClearFlag(USARTx, USART_FLAG_TC);
        /* 写入一帧待发送的数据 */
        if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
        {
            REG_WRITE(USARTx->TDR, *pu16Data);
            pu16Data++;
        }
        else
        {
            REG_WRITE(USARTx->TDR, *pu8Data);
            pu8Data++;
        }
        /* 查询等待SR.TC变为1 */
        while (!USART_GetFlag(USARTx, USART_FLAG_TC))
        {
            u32TimeoutCnt++;
            if (u32Timeout <= u32TimeoutCnt)
            {
                /* 等待超时 */
                return ErrorTimeout;
            }
        }
    }
    /* 清除发送完成标志 */
    USART_ClearFlag(USARTx, USART_FLAG_TC);
    return Ok;
}

/**
 * @brief  USART 中断发送
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART发送数据
 * @retval None
 */
void USART_UART_TransmitINT(USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint16_t* pu16Data = (uint16_t*)(pu8Data);
    if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
    {
        REG_WRITE(USARTx->TDR, *pu16Data);
    }
    else
    {
        REG_WRITE(USARTx->TDR, *pu8Data);
    }
}

/**
 * @brief  USART 智能卡中断发送
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     待发送数据地址
 * @retval None
 */
void USART_SC_TransmitINT(USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint32_t i = 0;
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, 2U);
    while((!REG_READBITS(USARTx->CR1, USART_CR1_TE)) && (i++ < 10000)){}
    REG_WRITE(USARTx->TDR, *pu8Data);
}

/**
 * @brief  USART 智能卡中断接收
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @retval None
 */
void USART_SC_ReceiveINT(USART_TypeDef* USARTx)
{
    uint32_t i = 0;
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, 1U);
    while((!REG_READBITS(USARTx->CR1, USART_CR1_RE)) && (i++ < 10000)){}
}

/**
 * @brief  USART 查询接收数据
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART接收数据buffer指针
 * @param  [in] u32Size:     UART接收数据长度(8-bits数据传送: 字节数据长度; 9-bits数据传送: 半字数据长度)
 * @param  [in] u32Timeout:  UART接收超时时间
 * @retval uint32_t          UART接收返回错误码 @ref USART_UART_Error_Code
 *         - USART_UART_NoError:                                   OK
 *         - USART_UART_TimeoutError:                              超时错误
 *         - USART_UART_ParityError | FrameError | OverflowError:  接收数据校验、帧、上溢错误
 */
uint32_t USART_UART_Receive(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t  u32SizeIdx    = 0U;
    uint32_t  u32TimeoutCnt = 0U;
    uint32_t  u32Flag       = 0U;
    uint16_t* pu16Data      = (uint16_t*)(pu8Data);
    for (u32SizeIdx = 0U; u32SizeIdx < u32Size; u32SizeIdx++)
    {
        /* 查询等待SR.RC变为1 */
        while (!USART_GetFlag(USARTx, USART_FLAG_RC))
        {
            /* 检测到RXD管脚边沿，接收开始 */
            if (0U != USART_GetFlag(USARTx, USART_FLAG_DWK))
            {
                USART_ClearFlag(USARTx, USART_FLAG_DWK);
                u32TimeoutCnt = 0U;
            }
            u32TimeoutCnt++;
            if (u32Timeout <= u32TimeoutCnt)
            {
                /* 等待超时 */
                return USART_UART_TimeoutError;
            }
        }
        /* 从RDR寄存器读出数据并保存 */
        if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
        {
            *pu16Data = REG_READ(USARTx->RDR);
            pu16Data++;
        }
        else
        {
            *pu8Data = REG_READ(USARTx->RDR);
            pu8Data++;
        }
        /* 查询是否有奇偶校验错误、帧错误、上溢错误 */
        u32Flag = USART_GetFlag(USARTx, USART_FLAG_PE | USART_FLAG_FE | USART_FLAG_OR);
        if (u32Flag)
        {
            /* 有奇偶校验错误、帧错误、上溢错误其中一种或多种错误 */
            USART_ClearFlag(USARTx, USART_FLAG_PE | USART_FLAG_FE | USART_FLAG_OR);
            return u32Flag;
        }
    }
    return USART_UART_NoError;
}

/**
 * @brief  USART 中断接收
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART接收数据buffer指针
 * @retval None
 */
void USART_UART_ReceiveINT(USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint16_t* pu16Data = (uint16_t*)(pu8Data);
    if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
    {
        *pu16Data = REG_READ(USARTx->RDR);
    }
    else
    {
        *pu8Data = REG_READ(USARTx->RDR);
    }
}

/**
 * @brief  USART 自动波特率检测函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @param  [in] u32PSC:            PSC分频选择                @ref USART_Baud_Rate_Pre_Clock_Div
 * @retval None
 * @note   须根据目标波特率和当前PCLK设置合适的PSC分频值，以避免波特率检测溢出；须避开波特率检测范围的边缘值
 */
void USART_UART_ABR_Detect(USART_TypeDef* USARTx, uint32_t u32PSC)
{
    /* 设置PSC值 */
    REG_MODIFY(USARTx->BRR, USART_BRR_PSC, u32PSC);

    /* 自动波特率检测使能 */
    REG_SETBITS(USARTx->CR3, USART_CR3_ABRE);
    /* 使用TOE功能为波特率自动检测 */
    REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
    REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_Auto_BaudRate);
}

/**
 * @brief  USART 根据自动波特率检测值设置波特率函数
 * @param  [in] USARTx:       USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_UART_Detect_ABR_Set(USART_TypeDef* USARTx)
{
    uint32_t u32CalBaudRate;
    uint32_t u32BDRValue;
    uint32_t u32TXRXEnSta;

    /* 自动波特率检测除能 */
    REG_CLEARBITS(USARTx->CR3, USART_CR3_ABRE);

    /* 计算检测的波特率 */
    u32BDRValue    = USARTx->BDR + 1U;
    u32CalBaudRate = Sysctrl_GetPClkFreq() / (1U << (USARTx->BRR_f.PSC * 2U)) / u32BDRValue;

    /* 目标波特率设置 */
    u32TXRXEnSta = REG_READBITS(USARTx->CR1, USART_CR1_TE | USART_CR1_RE); /* 读取TX、RX使能状态 */
    if (0U == u32TXRXEnSta)                                                /* TX、RX未使能 */
    {
        u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_UART, u32CalBaudRate, Sysctrl_GetPClkFreq(), USARTx->CR1 & USART_CR1_OVER8);
    }
    else /* TX、RX任一使能 */
    {
        REG_CLEARBITS(USARTx->CR1, USART_CR1_TE | USART_CR1_RE);
        u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_UART, u32CalBaudRate, Sysctrl_GetPClkFreq(), USARTx->CR1 & USART_CR1_OVER8);
        REG_SETBITS(USARTx->CR1, u32TXRXEnSta);
    }
}

/**
 * @brief  USART 获取标志位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART状态位     @ref USART_Status_Flags
 * @retval uint32_t： 状态位值
 */
uint32_t USART_GetFlag(USART_TypeDef* USARTx, uint32_t u32State)
{
    return REG_READBITS(USARTx->SR, u32State);
}

/**
 * @brief  USART 清除标志位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART状态位     @ref USART_Status_Flags
 * @retval None
 */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_CLEARBITS(USARTx->ICR, u32State);
}

/**
 * @brief  USART 中断使能
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART中断使能位
 * @retval None
 */
void USART_EnableIrq(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_SETBITS(USARTx->IER, u32State);
}

/**
 * @brief  USART 中断禁止
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART中断使能位
 * @retval None
 */
void USART_DisableIrq(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_CLEARBITS(USARTx->IER, u32State);
}

/**
 * @brief  USART 清除中断标志位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART中断使能位
 * @retval None
 */
void USART_ClearIrq(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_CLEARBITS(USARTx->ICR, u32State);
}

/**
 * @brief  USART 获取中断使能位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART状态位     @ref USART_Status_Flags
 * @retval uint32_t： 状态位值
 */
uint32_t USART_GetIrqEn(USART_TypeDef* USARTx, uint32_t u32State)
{
    return REG_READBITS(USARTx->IER, u32State);
}

/**
 * @brief  USART IR功能开启控制
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @retval None
 */
void USART_IR_EnableIR(USART_TypeDef* USARTx)
{
    REG_SETBITS(USARTx->CR3, USART_CR3_IREN);
}

/**
 * @brief  USART IR功能关闭控制
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @retval None
 */
void USART_IR_DisableIR(USART_TypeDef* USARTx)
{
    REG_CLEARBITS(USARTx->CR3, USART_CR3_IREN);
}

/* ========================================================================== */
/*  vc.c                                                                      */
/* ========================================================================== */


/******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
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

/* ========================================================================== */
/*  wwdt.c                                                                    */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_WWDT WWDT模块驱动库
 * @brief WWDT Driver Library WWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup WWDT_Global_Functions WWDT全局函数定义
 * @{
 */

/**
 * @brief  WWDT 初始化
 * @param  [in] pstcWwdtInit: WWDT初始化          @ref stc_wwdt_init_t
 * @retval en_result_t
 */
en_result_t WWDT_Init(stc_wwdt_init_t* pstcWwdtInit)
{
    REG_WRITE(HC_WWDT->CR1, pstcWwdtInit->u32Prescaler | pstcWwdtInit->u32PreOverInt | pstcWwdtInit->u32Window);

    REG_WRITE(HC_WWDT->CR0, pstcWwdtInit->u32Counter);

    return Ok;
}

/**
 * @brief  WWDT 启动运行
 * @retval None
 */
void WWDT_Start(void)
{
    REG_SETBITS(HC_WWDT->CR0, WWDT_CR0_EN);
}

/**
 * @brief  WWDT 喂狗
 * @param  [in] u32Cnt: 计数器值
 * @retval None
 */
void WWDT_Feed(uint32_t u32Cnt)
{
    REG_WRITE(HC_WWDT->CR0, WWDT_CR0_EN | u32Cnt);
}

/**
 * @brief  WWDT 预溢出标志清除
 * @retval None
 */
void WWDT_ClearPreOverFlag(void)
{
    REG_CLEARBITS(HC_WWDT->SR, WWDT_SR_POV);
}

/**
 * @brief  WWDT 预溢出标志获取
 * @retval boolean_t： 溢出标志位
 *         - TRUE   溢出
 *         - FALSE  无溢出
 */
boolean_t WWDT_GetPreOverFlag(void)
{
    if (REG_READBITS(HC_WWDT->SR, WWDT_SR_POV))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  WWDT 获取当前运行状态
 * @retval boolean_t： 运行状态
 *         - TRUE   正在运行
 *         - FALSE  没有运行
 */
boolean_t WWDT_GetRunFlag(void)
{
    if (REG_READBITS(HC_WWDT->CR0, WWDT_CR0_EN))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief  WWDT 获取当前计数值
 * @retval uint32_t：  计数值
 */
uint32_t WWDT_GetCnt(void)
{
    return REG_READBITS(HC_WWDT->CR0, WWDT_CR0_WCNT);
}

/* ========================================================================== */
/*  interrupts_hc32a052.c (mcu/common)                                        */
/* ========================================================================== */


/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @brief IRQ WEAK DEFINE
 */
__WEAK void SysTick_IRQHandler(void);


__WEAK void PortA_IRQHandler(void);
__WEAK void PortB_IRQHandler(void);
__WEAK void PortC_IRQHandler(void);
__WEAK void PortD_IRQHandler(void);
__WEAK void Dmac_IRQHandler(void);
__WEAK void Tim3_IRQHandler(void);
__WEAK void Usart0_IRQHandler(void);
__WEAK void Usart1_IRQHandler(void);
__WEAK void LpUart0_IRQHandler(void);
__WEAK void LpUart1_IRQHandler(void);
__WEAK void Spi0_IRQHandler(void);
__WEAK void Spi1_IRQHandler(void);
__WEAK void I2c0_IRQHandler(void);
__WEAK void I2c1_IRQHandler(void);
__WEAK void Atim0_IRQHandler(void);
__WEAK void Atim1_IRQHandler(void);
__WEAK void Atim2_IRQHandler(void);
__WEAK void LpTim_IRQHandler(void);
__WEAK void Gtim0_IRQHandler(void);
__WEAK void Gtim1_IRQHandler(void);
__WEAK void Btim0_IRQHandler(void);
__WEAK void Btim1_IRQHandler(void);
__WEAK void Btim2_IRQHandler(void);
__WEAK void Btim3_IRQHandler(void);
__WEAK void Btim4_IRQHandler(void);
__WEAK void Btim5_IRQHandler(void);
__WEAK void I2cslv_IRQHandler(void);
__WEAK void Iwdt_IRQHandler(void);
__WEAK void Wwdt_IRQHandler(void);
__WEAK void Rtc_IRQHandler(void);
__WEAK void Adc_IRQHandler(void);
__WEAK void Vc0_IRQHandler(void);
__WEAK void Vc1_IRQHandler(void);
__WEAK void Lvd_IRQHandler(void);
__WEAK void Can_IRQHandler(void);
__WEAK void Atim_Bk_IRQHandler(void);
__WEAK void Flash_IRQHandler(void);
__WEAK void Ram_IRQHandler(void);
__WEAK void Ctrim_IRQHandler(void);
__WEAK void Fault_IRQHandler(void);

/**
 * @brief NVIC 中断使能
 *
 * @param [in]  enIrq          中断号枚举类型
 * @param [in]  enLevel        中断优先级枚举类型
 * @param [in]  bEn            中断开关 TRUE:使能；FALSE:禁止
 * @retval None
 */
void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn)
{
    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, (uint32_t)enLevel);
    if (TRUE == bEn)
    {
        NVIC_EnableIRQ(enIrq);
    }
    else
    {
        NVIC_DisableIRQ(enIrq);
    }
}

/**
 * @brief NVIC hardware fault 中断实现
 *
 *
 * @retval None
 */
void HardFault_Handler(void)
{
    volatile int a = 0;

    while( 0 == a)
    {
        ;
    }

}


/**
 * @brief NVIC SysTick 中断实现
 *
 * @retval None
 */
void SysTick_Handler(void)
{
   SysTick_IRQHandler();
}

/**
 * @brief GPIO PortA 中断处理函数
 *
 * @retval None
 */
void PORTA_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTA)
    PortA_IRQHandler();
#endif
}

/**
 * @brief GPIO PortB 中断处理函数
 *
 * @retval None
 */
void PORTB_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTB)
    PortB_IRQHandler();
#endif
}

/**
 * @brief GPIO PortC 中断处理函数
 *
 * @retval None
 */
void PORTC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTC)
    PortC_IRQHandler();
#endif
}

/**
 * @brief GPIO PortD 中断处理函数
 *
 * @retval None
 */
void PORTD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTD)
    PortD_IRQHandler();
#endif
}

/**
 * @brief DMAC  中断处理函数
 *
 * @retval None
 */
void DMAC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_DMAC)
    Dmac_IRQHandler();
#endif
}

/**
 * @brief ATIM3 中断处理函数
 *
 * @retval None
 */
void ATIM3_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ATIM3)
    Tim3_IRQHandler();
#endif
}

/**
 * @brief USART0 中断处理函数
 *
 * @retval None
 */
void USART0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_USART0)
    Usart0_IRQHandler();
#endif
}

/**
 * @brief USART1 中断处理函数
 *
 * @retval None
 */
void USART1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_USART1)
    Usart1_IRQHandler();
#endif
}

/**
 * @brief LPUART0 低功耗串口0 中断处理函数
 *
 * @retval None
 */
void LPUART0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART0)
    LpUart0_IRQHandler();
#endif
}

/**
 * @brief LPUART1 低功耗串口1 中断处理函数
 *
 * @retval None
 */
void LPUART1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART1)
    LpUart1_IRQHandler();
#endif
}

/**
 * @brief SPI0 中断处理函数
 *
 * @retval None
 */
void SPI0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI0)
    Spi0_IRQHandler();
#endif
}

/**
 * @brief SPI1 中断处理函数
 *
 * @retval None
 */
void SPI1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI1)
    Spi1_IRQHandler();
#endif
}

/**
 * @brief I2C0 中断处理函数
 *
 * @retval None
 */
void I2C0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C0)
    I2c0_IRQHandler();
#endif
}

/**
 * @brief I2C1 中断处理函数
 *
 * @retval None
 */
void I2C1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C1)
    I2c1_IRQHandler();
#endif
}

/**
 * @brief ATIM0 中断处理函数
 *
 * @retval None
 */
void ATIM0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ATIM0)
    Atim0_IRQHandler();
#endif
}

/**
 * @brief ATIM1 中断处理函数
 *
 * @retval None
 */
void ATIM1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ATIM1)
    Atim1_IRQHandler();
#endif
}

/**
 * @brief ATIM2 中断处理函数
 *
 * @retval None
 */
void ATIM2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ATIM2)
    Atim2_IRQHandler();
#endif
}

/**
 * @brief LPTIM 低功耗定时器中断处理函数
 *
 * @retval None
 */
void LPTIM_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPTIM)
    LpTim_IRQHandler();
#endif
}

/**
 * @brief GTIM0 BTIM0/1/2 中断处理函数
 *
 * @retval None
 */
void GTIM0_BTIM0_1_2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_GTIM0)
    Gtim0_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_BTIM0)
    Btim0_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_BTIM1)
    Btim1_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_BTIM2)
    Btim2_IRQHandler();
#endif
}

/**
 * @brief GTIM1 BTIM3/4/5 中断处理函数
 *
 * @retval None
 */
void GTIM1_BTIM3_4_5_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_GTIM1)
    Gtim1_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_BTIM3)
    Btim3_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_BTIM4)
    Btim4_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_BTIM5)
    Btim5_IRQHandler();
#endif
}

/**
 * @brief I2CSLV 中断处理函数
 *
 * @retval None
 */
void I2CSLV_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2CSLV)
    I2cslv_IRQHandler();
#endif
}

/**
 * @brief WWDT 中断处理函数
 *
 * @retval None
 */
void WWDT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_WWDT)
    Wwdt_IRQHandler();
#endif
}

/**
 * @brief IWDT 中断处理函数
 *
 * @retval None
 */
void IWDT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_IWDT)
    Iwdt_IRQHandler();
#endif
}

/**
 * @brief RTC 中断处理函数
 *
 * @retval None
 */
void RTC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_RTC)
    Rtc_IRQHandler();
#endif
}

/**
 * @brief ADC 中断处理函数
 *
 * @retval None
 */
void ADC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ADC)
    Adc_IRQHandler();
#endif
}

/**
 * @brief VC0/1 LVD 中断处理函数
 *
 * @retval None
 */
void VC0_1_LVD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LVD)
    Lvd_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_VC0)
    Vc0_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_VC1)
    Vc1_IRQHandler();
#endif
}

/**
 * @brief CAN 中断处理函数
 *
 * @retval None
 */
void CAN_IRQHandler(void)
{
    Can_IRQHandler();
}

/**
 * @brief ATIM_BK 中断处理函数
 *
 * @retval None
 */
void ATIM_BK_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ATIM_BK)
    Atim_Bk_IRQHandler();
#endif
}

/**
 * @brief FLASH/RAM 中断处理函数
 *
 * @retval None
 */
void FLASH_RAM_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_FLASH)
    Flash_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_RAM)
    Ram_IRQHandler();
#endif
}

/**
 * @brief CTRIM/FAULT 中断处理函数
 *
 * @retval None
 */
void CTRIM_FAULT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_CTRIM)
    Ctrim_IRQHandler();
#endif

#if (INT_CALLBACK_ON == INT_CALLBACK_FAULT)
    Fault_IRQHandler();
#endif
}

/* ========================================================================== */
/*  中断回调弱定义 (空实现, 应用层可写同名强符号覆盖)                                               */
/* ========================================================================== */

/*
 * 下列回调原厂只有 __WEAK 声明而无定义, 入口处理函数却会调用它们.
 * 补空定义以消除弱未定义符号 (调用行为不再依赖链接器细节).
 * 应用层若要处理该中断, 直接定义同名函数 (非 __WEAK) 即可自动覆盖.
 */
__WEAK void SysTick_IRQHandler(void) {}
__WEAK void PortA_IRQHandler(void) {}
__WEAK void PortB_IRQHandler(void) {}
__WEAK void PortC_IRQHandler(void) {}
__WEAK void PortD_IRQHandler(void) {}
__WEAK void Dmac_IRQHandler(void) {}
__WEAK void Tim3_IRQHandler(void) {}
__WEAK void Usart0_IRQHandler(void) {}
__WEAK void Usart1_IRQHandler(void) {}
__WEAK void LpUart0_IRQHandler(void) {}
__WEAK void LpUart1_IRQHandler(void) {}
__WEAK void Spi0_IRQHandler(void) {}
__WEAK void Spi1_IRQHandler(void) {}
__WEAK void I2c0_IRQHandler(void) {}
__WEAK void I2c1_IRQHandler(void) {}
__WEAK void Atim0_IRQHandler(void) {}
__WEAK void Atim1_IRQHandler(void) {}
__WEAK void Atim2_IRQHandler(void) {}
__WEAK void LpTim_IRQHandler(void) {}
__WEAK void Gtim0_IRQHandler(void) {}
__WEAK void Gtim1_IRQHandler(void) {}
__WEAK void Btim0_IRQHandler(void) {}
__WEAK void Btim1_IRQHandler(void) {}
__WEAK void Btim2_IRQHandler(void) {}
__WEAK void Btim3_IRQHandler(void) {}
__WEAK void Btim4_IRQHandler(void) {}
__WEAK void Btim5_IRQHandler(void) {}
__WEAK void I2cslv_IRQHandler(void) {}
__WEAK void Iwdt_IRQHandler(void) {}
__WEAK void Wwdt_IRQHandler(void) {}
__WEAK void Rtc_IRQHandler(void) {}
__WEAK void Adc_IRQHandler(void) {}
__WEAK void Vc0_IRQHandler(void) {}
__WEAK void Vc1_IRQHandler(void) {}
__WEAK void Lvd_IRQHandler(void) {}
__WEAK void Can_IRQHandler(void) {}
__WEAK void Atim_Bk_IRQHandler(void) {}
__WEAK void Flash_IRQHandler(void) {}
__WEAK void Ram_IRQHandler(void) {}
__WEAK void Ctrim_IRQHandler(void) {}
__WEAK void Fault_IRQHandler(void) {}
