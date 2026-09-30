/**
 *******************************************************************************
 * @file  driver.cpp
 * @brief HC32F005 驱动库 - 聚合实现 [自动生成, 勿手改]
 *
 * 本文件由 XHSC HC32F005 DDL 自动聚合生成, 请勿逐模块手工修改.
 * 重新生成: python3 tools/merge_driver.py            (会覆盖本文件的修改)
 *
 * 聚合来源: temp/HC32F005_DDL_Rev2.0.0/
 *   driver/inc//                       驱动模块 (inc + src 同名目录)
 *   mcu/common//                       器件头 / 中断框架
 *
 * 未纳入本文件的部分 (与板级/外部强相关, 按「机制/策略」分层):
 *   hal/hc32f005/config.h          板级配置「机制」: 类型 / 预设 / 校验
 *   hal/hc32f005/config.cpp        时钟初始化实现 (SystemInit)
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
/** \file ddl.c
 **
 ** Common API of DDL.
 ** @link ddlGroup Some description @endlink
 **
 **   - 2019-03-03
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup DDL Common Functions
 ******************************************************************************/
//@{

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
/* C++/picolibc: 原厂借 __DEBUG 打开 MDK 风格 fputc 重定向.
 * picolibc 的 printf 走 FILE 回调而非 fputc, 该重定向无效,
 * 且强定义 fputc 有与 libc 归档成员冲突的风险; 其依赖的
 * Debug_Output 也已被原厂注释成空操作. 故保持 __DEBUG 未定义. */
#undef __DEBUG






uint32_t Log2(uint32_t u32Val)
{
    uint32_t u32V1 = 0;

    if(0u == u32Val)
    {
        return 0;
    }

    while(u32Val > 1u)
    {
        u32V1++;
        u32Val /=2;
    }

    return u32V1;
}


/**
 *******************************************************************************
 ** \brief Memory clear function for DDL_ZERO_STRUCT()
 ******************************************************************************/
void ddl_memclr(void *pu8Address, uint32_t u32Count)
{
    uint8_t *pu8Addr = (uint8_t *)pu8Address;

    if(NULL == pu8Addr)
    {
        return;
    }

    while (u32Count--)
    {
        *pu8Addr++ = 0;
    }
}

/**
 *****************************************************************************
 ** \brief Hook function, which is called in polling loops
 *****************************************************************************/
void DDL_WAIT_LOOP_HOOK(void)
{
    // Place code for triggering Watchdog counters here, if needed
}

/**
 *****************************************************************************
 ** \brief debug printf function.
 *****************************************************************************/
void Debug_UartInit(void)
{
#ifdef __DEBUG
    //uint32_t u32Pclk1 =  0;
    //volatile uint32_t u32ReloadVal = 0;
    //
    //// UART0_TXD/P35, 19200bps
    //M0P_GPIO->P3ADS_f.P35 = 0;
    //M0P_GPIO->P35_SEL_f.SEL = 3;
    //M0P_GPIO->P3DIR_f.P35 = 0;
    //
    //u32Pclk1 = Sysctrl_GetPClkFreq();
    //u32ReloadVal = 65536 - u32Pclk1 * 2 / 19200 / 32;
    //
    //M0P_BT0->CR_f.CT = 0;
    //M0P_BT0->CR_f.MD = 1;
    //M0P_BT0->CR_f.TOG_EN = 1;
    //M0P_BT0->ARR = u32ReloadVal;
    //M0P_BT0->CNT = u32ReloadVal;
    //M0P_BT0->CR_f.TR = 1;
    //
    //M0P_UART0->SCON_f.DBAUD = 1;
    //M0P_UART0->SCON_f.SM01 = 1;
#endif
}

void Debug_Output(uint8_t u8Data)
{
    //M0P_UART0->SCON_f.REN = 0;
    //M0P_UART0->SBUF = u8Data;
    //
    //while (TRUE != M0P_UART0->ISR_f.TI)
    //{
    //    ;
    //}
    //M0P_UART0->ICR_f.TICLR = 0;
}

//#ifdef __DEBUG
///**
// ******************************************************************************
// ** \brief  Re-target putchar function
// ******************************************************************************/
//int fputc(int ch, FILE *f)
//{

//    if (((uint8_t)ch) == '\n')
//    {
//        Debug_Output('\r');
//    }
//    Debug_Output(ch);

//    return ch;
//}
//#endif



extern void Debug_UartInit(void);
extern void Debug_Output(uint8_t u8Data);

#if defined (__CC_ARM)          //KEIL
#pragma import(__use_no_semihosting)
void _sys_exit(int x)
{
    x = x;
}
struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
/* is required. */
};
/* FILE is typedef?d in stdio.h. */
FILE __stdout;

#endif

#ifdef __DEBUG
/**
 ******************************************************************************
 ** \brief  Re-target putchar function
 ******************************************************************************/
int fputc(int ch, FILE *f)
{

    if (((uint8_t)ch) == '\n')
    {
        Debug_Output('\r');
    }
    Debug_Output(ch);

    return ch;
}
#endif

void _ttywrch(int c)
{
}


int __backspace(void)
{
    return 0;
}



/**
 * \brief   delay1ms
 *          delay approximately 1ms.
 * \param   [in]  u32Cnt
 * \retval  void
 */
void delay1ms(uint32_t u32Cnt)
{
    uint32_t u32end;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while(u32Cnt-- > 0)
    {
        SysTick->VAL  = 0;
        u32end = 0x1000000 - SystemCoreClock/1000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

/**
 * \brief   delay100us
 *          delay approximately 100us.
 * \param   [in]  u32Cnt
 * \retval  void
 */
void delay100us(uint32_t u32Cnt)
{
    uint32_t u32end;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/10000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

/**
 * \brief   delay10us
 *          delay approximately 10us.
 * \param   [in]  u32Cnt
 * \retval  void
 */
void delay10us(uint32_t u32Cnt)
{
    uint32_t u32end;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/100000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

/**
 * \brief   set register bit
 *
 * \param   [in]  addr
 * \param   [in]  offset
 * \retval  void
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
 * \brief   get register bit
 *
 * \param   [in]  addr
 * \param   [in]  offset
 * \retval  void
 */
boolean_t GetBit(uint32_t addr, uint32_t offset)
{
    return ((((*((volatile uint32_t *)(addr))) >> (offset)) & 1u) > 0) ? TRUE : FALSE;
}
//@} // DDL Functions

/* ========================================================================== */
/*  adc.c                                                                     */
/* ========================================================================== */

/******************************************************************************/
/** \file adc.c
 **
 ** ADC driver API.
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{

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
 * \brief
 *          获取ADC中断状态
 *
 * \param   [in]  pstcAdcIrqState  ADC中断状态指针
 *
 * \retval  无
 */
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState)
{
    pstcAdcIrqState->bAdcIrq = M0P_ADC->IFR_f.CONT_INTF;
    pstcAdcIrqState->bAdcRegCmp = M0P_ADC->IFR_f.REG_INTF;
    pstcAdcIrqState->bAdcHhtCmp = M0P_ADC->IFR_f.HHT_INTF;
    pstcAdcIrqState->bAdcLltCmp = M0P_ADC->IFR_f.LLT_INTF;
}

/**
 * \brief
 *          清除ADC CONT中断状态
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_ClrContIrqState(void)
{
    M0P_ADC->ICLR = ~(1<<3);
}

/**
 * \brief
 *          清除ADC REG中断状态
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_ClrRegIrqState(void)
{
    M0P_ADC->ICLR = ~(1<<2);
}

/**
 * \brief
 *          清除ADC HHT中断状态
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_ClrHhtIrqState(void)
{
    M0P_ADC->ICLR = ~(1<<1);
}

/**
 * \brief
 *          清除ADC LLT中断状态
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_ClrIrqLltState(void)
{
    M0P_ADC->ICLR = ~1;
}


/**
 * \brief
 *          ADC中断使能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_EnableIrq(void)
{
    M0P_ADC->CR0_f.IE = 1u;
}

/**
 * \brief
 *          ADC比较使能
 *
 * \param   [in]  pstcAdcIrqCfg  ADC比较配置
 *
 * \retval  无
 */
void Adc_CmpCfg(stc_adc_irq_t* pstcAdcIrqCfg)
{
    if (TRUE == pstcAdcIrqCfg->bAdcRegCmp)
    {
        M0P_ADC->CR1_f.REGCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.REGCMP = 0u;
    }

    if (TRUE == pstcAdcIrqCfg->bAdcHhtCmp)
    {
        M0P_ADC->CR1_f.HTCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.HTCMP = 0u;
    }

    if (TRUE == pstcAdcIrqCfg->bAdcLltCmp)
    {
        M0P_ADC->CR1_f.LTCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.LTCMP = 0u;
    }

}

/**
 * \brief
 *          ADC中断除能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_DisableIrq(void)
{
    uint32_t u32Cr1;

    M0P_ADC->CR0_f.IE = 0u;

    u32Cr1 = M0P_ADC->CR1 | (1<<15);    // must write 1 to bit 15 to avoid clear ADC_result_acc
    u32Cr1 &= ~((1u<<12)|(1u<<13)|(1u<<14));
    M0P_ADC->CR1 = u32Cr1;
}

/**
 * \brief
 *          ADC初始化
 *
 * \param   [in]  pstcAdcConfig  ADC配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig)
{
    if (NULL == pstcAdcConfig)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0_f.CLKSEL = pstcAdcConfig->enAdcClkSel;
    M0P_ADC->CR0_f.SAM = pstcAdcConfig->enAdcSampTimeSel;
    M0P_ADC->CR0_f.SREF = pstcAdcConfig->enAdcRefVolSel;
    M0P_ADC->CR0_f.BUFEN = pstcAdcConfig->bAdcInBufEn;
    M0P_ADC->HT_f.HT = pstcAdcConfig->u32AdcRegHighThd;
    M0P_ADC->LT_f.LT = pstcAdcConfig->u32AdcRegLowThd;
    M0P_ADC->CR1_f.TRIGS0 = pstcAdcConfig->enAdcTrig0Sel;
    M0P_ADC->CR1_f.TRIGS1 = pstcAdcConfig->enAdcTrig1Sel;
    M0P_ADC->CR0_f.IE = 0u;
    M0P_ADC->CR1_f.REGCMP = 0u;
    M0P_ADC->CR1_f.HTCMP = 0u;
    M0P_ADC->CR1_f.LTCMP = 0u;

    return Ok;
}

/**
 * \brief
 *          ADC Deinit
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_DeInit(void)
{
    Adc_DisableIrq();
    EnableNvic(ADC_IRQn, IrqLevel3, FALSE);

    M0P_ADC->CR0_f.ADCEN = 0u;

    M0P_ADC->CR0_f.IE = 0u;
    M0P_ADC->CR1_f.REGCMP = 0u;
    M0P_ADC->CR1_f.HTCMP = 0u;
    M0P_ADC->CR1_f.LTCMP = 0u;
    M0P_ADC->ICLR_f.CONT_INTC = 0u;
    M0P_ADC->ICLR_f.REG_INTC = 0u;
    M0P_ADC->ICLR_f.HHT_INTC = 0u;
    M0P_ADC->ICLR_f.LLT_INTC = 0u;

    M0P_ADC->CR0_f.CLKSEL = 0u;
    M0P_ADC->CR0_f.SAM = 0x2u;
    M0P_ADC->CR0_f.SREF = 0x3u;
    M0P_ADC->CR0_f.SEL = 0xFu;
    M0P_ADC->CR0_f.BUFEN = 0u;
    M0P_ADC->HT_f.HT = 0xFFFu;
    M0P_ADC->LT_f.LT = 0u;
    M0P_ADC->CR1_f.TRIGS0 = 0u;
    M0P_ADC->CR1_f.TRIGS1 = 0u;
}

/**
 * \brief
 *          ADC转换开始
 *
 * \param   无
 *
 * \retval  无
 */

void Adc_Start(void)
{
    M0P_ADC->ICLR_f.CONT_INTC = 0u;
    M0P_ADC->CR0_f.STATERST = 1u;
    M0P_ADC->CR0_f.START = 1u;
}

/**
 * \brief
 *          ADC转换停止
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_Stop(void)
{
    M0P_ADC->CR0_f.START = 0u;
}

/**
 * \brief
 *          ADC使能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_Enable(void)
{
    M0P_ADC->CR0_f.ADCEN = 1u;
}

/**
 * \brief
 *          ADC除能
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_Disable(void)
{
    M0P_ADC->CR0_f.ADCEN = 0u;
}

/**
 * \brief
 *          配置普通转换模式
 *
 * \param   [in]  pstcAdcConfig   ADC配置指针
 * \param   [in]  pstcAdcNormCfg  普通转换模式配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_ConfigNormMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_norm_cfg_t* pstcAdcNormCfg)
{
    if ((NULL == pstcAdcNormCfg) || (NULL == pstcAdcConfig))
    {
        return ErrorInvalidParameter;
    }

    pstcAdcConfig->enAdcOpMode = AdcNormalMode;
    M0P_ADC->CR1_f.CT = 0u;
    M0P_ADC->CR0_f.SEL = pstcAdcNormCfg->enAdcNormModeCh;
    M0P_ADC->CR1_f.RACC_EN = pstcAdcNormCfg->bAdcResultAccEn;

    return Ok;
}

/**
 * \brief
 *          配置连续转换模式
 *
 * \param   [in]  pstcAdcConfig   ADC配置指针
 * \param   [in]  pstcAdcNormCfg  连续转换模式配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_ConfigContMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_cont_cfg_t* pstcAdcContCfg)
{
    if ((NULL == pstcAdcContCfg) || (NULL == pstcAdcConfig))
    {
        return ErrorInvalidParameter;
    }

    pstcAdcConfig->enAdcOpMode = AdcContMode;
    M0P_ADC->CR1_f.CT = 1u;
    M0P_ADC->CR0_f.SEL = pstcAdcContCfg->enAdcContModeCh;
    M0P_ADC->CR1_f.RACC_EN = pstcAdcContCfg->bAdcResultAccEn;
    if (pstcAdcContCfg->bAdcResultAccEn)
    {
        M0P_ADC->CR1_f.RACC_CLR = 1u;
    }
    M0P_ADC->CR2 = 1<<pstcAdcContCfg->enAdcContModeCh;
    M0P_ADC->CR2_f.ADCCNT = pstcAdcContCfg->u8AdcSampCnt;

    return Ok;
}

/**
 * \brief
 *          配置扫描转换模式
 *
 * \param   [in]  pstcAdcConfig   ADC配置指针
 * \param   [in]  pstcAdcNormCfg  扫描转换模式配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_ConfigScanMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_scan_cfg_t* pstcAdcScanCfg)
{
    if ((NULL == pstcAdcScanCfg) || (NULL == pstcAdcConfig))
    {
        return ErrorInvalidParameter;
    }

    pstcAdcConfig->enAdcOpMode = AdcScanMode;
    M0P_ADC->CR1_f.CT = 1u;
    M0P_ADC->CR2 = pstcAdcScanCfg->u8AdcScanModeCh;
    M0P_ADC->CR2_f.ADCCNT = pstcAdcScanCfg->u8AdcSampCnt;

    return Ok;
}

/**
 * \brief
 *          查询ADC转换状态
 *
 * \param   none
 *
 * \retval  boolean_t  TRUE:  ADC转换中
 * \retval  boolean_t  FALSE: ADC转换完成
 */
boolean_t Adc_PollBusyState(void)
{
    return M0P_ADC->CR0_f.START;
}

/**
 * \brief
 *          获取采样值
 *
 * \param   [out] pu16AdcResult  采样值指针
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_GetResult(uint16_t* pu16AdcResult)
{
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

    *pu16AdcResult = M0P_ADC->RESULT_f.RESULT;

    return Ok;
}

/**
 * \brief
 *          获取累加采样值
 *
 * \param   [out] pu32AdcAccResult  累加采样值指针
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult)
{
    if (NULL == pu32AdcAccResult)
    {
        return ErrorInvalidParameter;
    }

    *pu32AdcAccResult = M0P_ADC->RESULT_ACC_f.RESULT_ACC;

    return Ok;
}

/**
 * \brief
 *          清零累加采样值
 *
 * \param   无
 *
 * \retval  无
 */
void Adc_ClrAccResult(void)
{
    M0P_ADC->CR1_f.RACC_CLR = 0u;
}

/**
 * \brief
 *          获取扫描采样模式下指定通道的采样值
 *
 * \param   [in]  u8Channel  通道号
 * \param   [out] pu16AdcResult  采样值指针
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_GetScanResult(uint8_t u8Channel, uint16_t* pu16AdcResult)
{
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

    switch (u8Channel)
    {
        case AdcExInputCH0:
            *pu16AdcResult = M0P_ADC->RESULT0_f.RESULT0;
            break;
        case AdcExInputCH1:
            *pu16AdcResult = M0P_ADC->RESULT1_f.RESULT1;
            break;
        case AdcExInputCH2:
            *pu16AdcResult = M0P_ADC->RESULT2_f.RESULT2;
            break;
        case AdcExInputCH3:
            *pu16AdcResult = M0P_ADC->RESULT3_f.RESULT3;
            break;
        case AdcExInputCH4:
            *pu16AdcResult = M0P_ADC->RESULT4_f.RESULT4;
            break;
        case AdcExInputCH5:
            *pu16AdcResult = M0P_ADC->RESULT5_f.RESULT5;
            break;
        case AdcExInputCH6:
            *pu16AdcResult = M0P_ADC->RESULT6_f.RESULT6;
            break;
        case AdcExInputCH7:
            *pu16AdcResult = M0P_ADC->RESULT7_f.RESULT7;
            break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}
/**
 * \brief
 *          获取ch8的采样值
 * \param   [out] pu16AdcResult  采样值指针
 *
 * \retval  en_result_t  Ok:  成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_GetCH8Result(uint16_t* pu16AdcResult)
{
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }
    *pu16AdcResult = M0P_ADC->RESULT8_f.RESULT8;
    return Ok;
}

/**
 * \brief
 *          设置ADC参考电压
 *
 * \param   [in]  enAdcRefVolSel  ADC参考电压
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel)
{
    if (enAdcRefVolSel > RefVolSelAVDD)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0_f.SREF = enAdcRefVolSel;
    return Ok;
}

//@} // AdcGroup

/* ========================================================================== */
/*  adt.c                                                                     */
/* ========================================================================== */

/******************************************************************************/
/** \file adt.c
 **
 ** Low Voltage Detect driver API.
 ** @link Lvd Group Some description @endlink
 **
 **   - 2019-04-19 Husj    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup AdtGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_ADT_STATE(x)         (  AdtCMAF == (x)||\
                                         AdtCMBF == (x)||\
                                         AdtCMCF == (x)||\
                                         AdtCMDF == (x)||\
                                         AdtOVFF == (x)||\
                                         AdtUDFF == (x)||\
                                         AdtDTEF == (x)||\
                                         AdtCMSAUF == (x)||\
                                         AdtCMSADF == (x)||\
                                         AdtCMSBUF == (x)||\
                                         AdtCMSBDF == (x)||\
                                         AdtCntDir == (x) )
#define ADTIM_HW_STASTPCLR_EN            31
#define ADTIM_HW_STASTPCLR_DIS           0x7FFFFFFF
#define ADTIM_SS_TIM4                    1
#define ADTIM_SS_TIM5                    2
#define ADTIM_SS_TIM6                    4
#define ADTIM_PORT_BKE_NUM               15
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



/*****************************************************************
 * \brief
 *          配置中断
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtIrq         中断类型
 * \param   [in]  bEn              中断使能/禁止
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ****************************************************************/
en_result_t Adt_CfgIrq(M0P_ADTIM_TypeDef *ADTx,
                          en_adt_irq_type_t enAdtIrq,
                          boolean_t bEn)
{
    uint32_t u32Val;

    u32Val = ADTx->ICONR;
    if (bEn)
    {
        u32Val |= 1u<<enAdtIrq;
    }
    else
    {
        u32Val &= ~(1u<<enAdtIrq);
    }
    ADTx->ICONR = u32Val;
    return Ok;
}

/*******************************************************************
 * \brief
 *          获取中断标志
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtIrq         中断类型
 *
 *
 * \retval  TRUE/FALSE
 *
 *****************************************************************/
boolean_t Adt_GetIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                           en_adt_irq_type_t enAdtIrq)
{
    uint32_t u32Val;
    boolean_t bEn;

    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));

    u32Val = ADTx->IFR;
    bEn = (u32Val>>enAdtIrq) & 0x1;

    return bEn;
}

/****************************************************************
 * \brief
 *          清除中断标志
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtIrq         中断类型
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ****************************************************************/
en_result_t Adt_ClearIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                             en_adt_irq_type_t enAdtIrq)
{
    ADTx->ICLR = ~(1u<<enAdtIrq);
    return Ok;
}

/****************************************************************
 * \brief
 *          清除所有中断标志
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ****************************************************************/
en_result_t Adt_ClearAllIrqFlag(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->ICLR = 0;
    return Ok;
}

/**************************************************************
 * \brief
 *          配置硬件递加事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCntUp     硬件递加事件
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ****************************************************************/
en_result_t Adt_CfgHwCntUp(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntUp)
{
    uint32_t u32Val;


    if (AdtHwCntMax <= enAdtHwCntUp)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCUPR;
    ADTx->HCUPR = u32Val | (1u<<enAdtHwCntUp);
    return Ok;
}

/**************************************************************
 * \brief
 *          清除硬件递加事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ************************************************************/
en_result_t Adt_ClearHwCntUp(M0P_ADTIM_TypeDef *ADTx)
{

    ADTx->HCUPR = 0;
    return Ok;
}


/**********************************************************
 * \brief
 *          配置硬件递减事件
 *
 * \param   [in]  ADTx               ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCntDwn      硬件递减事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***********************************************************/
en_result_t Adt_CfgHwCntDwn(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntDwn)
{
    uint32_t u32Val;


    if(AdtHwCntMax <= enAdtHwCntDwn)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCDOR;
    ADTx->HCDOR = u32Val | (1u<<enAdtHwCntDwn);
    return Ok;
}

/******************************************************************
 * \brief
 *          清除硬件递减事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 *****************************************************************/
en_result_t Adt_ClearHwCntDwn(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCDOR = 0;
    return Ok;
}

/******************************************************************
 * \brief
 *          配置硬件启动事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwStart     硬件启动事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_CfgHwStart(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStart)
{
    uint32_t u32Val;


    if(AdtHwTrigEnd <= enAdtHwStart)
    {
        return ErrorInvalidParameter;
    }
    u32Val = ADTx->HSTAR;
    ADTx->HSTAR = u32Val | (1u<<enAdtHwStart);
    return Ok;
}

/************************************************************************
 * \brief
 *          清除硬件启动事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ***********************************************************************/
en_result_t Adt_ClearHwStart(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HSTAR = 0;
    return Ok;
}

/*********************************************************************
 * \brief
 *          使能硬件启动
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 *********************************************************************/
en_result_t Adt_EnableHwStart(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HSTAR;
    ADTx->HSTAR = u32Val | (1u<<ADTIM_HW_STASTPCLR_EN);
    return Ok;
}

/*************************************************************************
 * \brief
 *          除能硬件启动
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ************************************************************************/
en_result_t Adt_DisableHwStart(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HSTAR;
    ADTx->HSTAR = u32Val & ADTIM_HW_STASTPCLR_DIS;
    return Ok;
}

/****************************************************************
 * \brief
 *          配置硬件停止事件
 *
 * \param   [in]  ADTx            ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwStop     硬件停止事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***************************************************************/
en_result_t Adt_CfgHwStop(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStop)
{
    uint32_t u32Val;

    if(AdtHwTrigEnd <= enAdtHwStop)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HSTPR;
    ADTx->HSTPR = u32Val | (1u<<enAdtHwStop);
    return Ok;
}

/***************************************************************
 * \brief
 *          清除硬件停止事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ***************************************************************/
en_result_t Adt_ClearHwStop(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HSTPR = 0;
    return Ok;
}

/*************************************************************
 * \brief
 *          使能硬件停止
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 **********************************************************/
en_result_t Adt_EnableHwStop(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HSTPR;
    ADTx->HSTPR = u32Val | (1u<<ADTIM_HW_STASTPCLR_EN);
    return Ok;
}

/*****************************************************************************
 * \brief
 *          除能硬件停止
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ***************************************************************************/
en_result_t Adt_DisableHwStop(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HSTPR;
    ADTx->HSTPR = u32Val & ADTIM_HW_STASTPCLR_DIS;
    return Ok;
}

/**************************************************************************
 * \brief
 *          配置硬件清零事件
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwClear      硬件清零事件
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *************************************************************************/
en_result_t Adt_CfgHwClear(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwClear)
{
    uint32_t u32Val;


    if(AdtHwTrigEnd <= enAdtHwClear)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCELR;
    ADTx->HCELR = u32Val | (1u<<enAdtHwClear);
    return Ok;
}

/**************************************************************************
 * \brief
 *          清除硬件清零事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 **************************************************************************/
en_result_t Adt_ClearHwClear(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCELR = 0;
    return Ok;
}

/***************************************************************************
 * \brief
 *          使能硬件清零
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 *************************************************************************/
en_result_t Adt_EnableHwClear(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HCELR;
    ADTx->HCELR = u32Val | (1u<<ADTIM_HW_STASTPCLR_EN);
    return Ok;
}

/************************************************************************
 * \brief
 *          除能硬件清零
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 **********************************************************************/
en_result_t Adt_DisableHwClear(M0P_ADTIM_TypeDef *ADTx)
{
    uint32_t u32Val;

    u32Val = ADTx->HCELR;
    ADTx->HCELR = u32Val & ADTIM_HW_STASTPCLR_DIS;
    return Ok;
}

/*******************************************************************
 * \brief
 *          配置硬件捕获A事件
 *
 * \param   [in]  ADTx               ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCaptureA    硬件捕获A事件选择
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_CfgHwCaptureA(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureA)
{
    uint32_t u32Val;


    if(AdtHwTrigEnd <= enAdtHwCaptureA)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCPAR;
    ADTx->HCPAR = u32Val | (1u<<enAdtHwCaptureA);
    ADTx->PCONR_f.CAPCA = 1;
    return Ok;
}

/************************************************************************
 * \brief
 *          清除硬件捕获A事件
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 ***********************************************************************/
en_result_t Adt_ClearHwCaptureA(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCPAR = 0;
    return Ok;
}

/*********************************************************************
 * \brief
 *          配置硬件捕获B事件
 *
 * \param   [in]  ADTx                ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtHwCaptureB     硬件捕获B事件选择
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ********************************************************************/
en_result_t Adt_CfgHwCaptureB(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureB)
{
    uint32_t u32Val;


    if(AdtHwTrigEnd <= enAdtHwCaptureB)
    {
        return ErrorInvalidParameter;
    }

    u32Val = ADTx->HCPBR;
    ADTx->HCPBR =  u32Val | (1u<<enAdtHwCaptureB);
    ADTx->PCONR_f.CAPCB = 1;
    return Ok;
}

/********************************************************************
 * \brief
 *          清除硬件捕获B事件
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t    Ok:  设置成功
 *
 *******************************************************************/
en_result_t Adt_ClearHwCaptureB(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->HCPBR = 0;
    return Ok;
}

/*****************************************************************
 * \brief
 *          软件同步开始
 *
 * \param   [in]  pstcAdtSwSyncStart    软件同步开始指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***************************************************************/
en_result_t Adt_SwSyncStart(stc_adt_sw_sync_t* pstcAdtSwSyncStart)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncStart)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncStart->bAdTim4)
    {
        u32Val |= ADTIM_SS_TIM4;
    }
    if (pstcAdtSwSyncStart->bAdTim5)
    {
        u32Val |= ADTIM_SS_TIM5;
    }
    if (pstcAdtSwSyncStart->bAdTim6)
    {
        u32Val |= ADTIM_SS_TIM6;
    }

    M0P_ADTIM4->SSTAR = u32Val;
    return Ok;
}

/***************************************************************
 * \brief
 *          软件同步停止
 *
 * \param   [in]  pstcAdtSwSyncStop     软件同步停止指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 ***************************************************************/
en_result_t Adt_SwSyncStop(stc_adt_sw_sync_t* pstcAdtSwSyncStop)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncStop)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncStop->bAdTim4)
    {
        u32Val |= ADTIM_SS_TIM4;
    }
    if (pstcAdtSwSyncStop->bAdTim5)
    {
        u32Val |= ADTIM_SS_TIM5;
    }
    if (pstcAdtSwSyncStop->bAdTim6)
    {
        u32Val |= ADTIM_SS_TIM6;
    }

    M0P_ADTIM4->SSTPR = u32Val;
    return Ok;
}

/*****************************************************************
 * \brief
 *          软件同步清零
 *
 * \param   [in]  pstcAdtSwSyncClear    软件同步清零指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_SwSyncClear(stc_adt_sw_sync_t* pstcAdtSwSyncClear)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncClear)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncClear->bAdTim4)
    {
        u32Val |= ADTIM_SS_TIM4;
    }
    if (pstcAdtSwSyncClear->bAdTim5)
    {
        u32Val |= ADTIM_SS_TIM5;
    }
    if (pstcAdtSwSyncClear->bAdTim6)
    {
        u32Val |= ADTIM_SS_TIM6;
    }

    M0P_ADTIM4->SCLRR = u32Val;
    return Ok;
}

/*******************************************************************
 * \brief
 *          获取软件同步运行状态
 *
 * \param   [in]  pstcAdtSwSyncState    ADV Timer软件同步运行状态指针
 *
 * \retval  en_result_t    Ok:  设置成功
 * \retval  en_result_t    ErrorInvalidParameter:  无效参数
 *******************************************************************/
en_result_t Adt_GetSwSyncState(stc_adt_sw_sync_t* pstcAdtSwSyncState)
{
    if (NULL == pstcAdtSwSyncState)
    {
        return ErrorInvalidParameter;
    }

    if (M0P_ADTIM4->SSTAR & ADTIM_SS_TIM4)
    {
        pstcAdtSwSyncState->bAdTim4 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim4 = FALSE;
    }
    if (M0P_ADTIM4->SSTAR & ADTIM_SS_TIM5)
    {
        pstcAdtSwSyncState->bAdTim5 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim5 = FALSE;
    }
    if (M0P_ADTIM4->SSTAR & ADTIM_SS_TIM6)
    {
        pstcAdtSwSyncState->bAdTim6 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim6 = FALSE;
    }
    return Ok;
}

/************************************************************************
 * \brief
 *          AOS触发配置
 *
 * \param   [in]  pstcAdtAosTrigCfg 触发配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ************************************************************************/
en_result_t Adt_AosTrigCfg(stc_adt_aos_trig_cfg_t* pstcAdtAosTrigCfg)
{
    if (NULL == pstcAdtAosTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADTIM4->ITRIG_f.IAOS0S = pstcAdtAosTrigCfg->enAos0TrigSrc;
    M0P_ADTIM4->ITRIG_f.IAOS1S = pstcAdtAosTrigCfg->enAos1TrigSrc;
    M0P_ADTIM4->ITRIG_f.IAOS2S = pstcAdtAosTrigCfg->enAos2TrigSrc;
    M0P_ADTIM4->ITRIG_f.IAOS3S = pstcAdtAosTrigCfg->enAos3TrigSrc;
    return Ok;
}

/**********************************************************************
 * \brief
 *          中断触发配置
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtIrqTrigCfg     触发配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_IrqTrigCfg(M0P_ADTIM_TypeDef *ADTx,
                              stc_adt_irq_trig_cfg_t* pstcAdtIrqTrigCfg)
{
    if(NULL == pstcAdtIrqTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->CR_f.CMAE = pstcAdtIrqTrigCfg->bAdtCntMatchATrigEn;
    ADTx->CR_f.CMBE = pstcAdtIrqTrigCfg->bAdtCntMatchBTrigEn;
    ADTx->CR_f.CMCE = pstcAdtIrqTrigCfg->bAdtCntMatchCTrigEn;
    ADTx->CR_f.CMDE = pstcAdtIrqTrigCfg->bAdtCntMatchDTrigEn;
    ADTx->CR_f.OVFE = pstcAdtIrqTrigCfg->bAdtOverFlowTrigEn;
    ADTx->CR_f.UDFE = pstcAdtIrqTrigCfg->bAdtUnderFlowTrigEn;

    return Ok;
}

/*************************************************************************
 * \brief
 *          端口触发配置
 *
 * \param   [in]  enAdtTrigPort         触发端口
 * \param   [in]  pstcAdtPortTrigCfg    触发配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *************************************************************************/
en_result_t Adt_PortTrigCfg(en_adt_trig_port_t enAdtTrigPort,
                               stc_adt_port_trig_cfg_t* pstcAdtPortTrigCfg)
{
    if (NULL == pstcAdtPortTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    switch (enAdtTrigPort)
    {
        case AdtTrigA:
            M0P_ADTIM4->TTRIG_f.TRIGAS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTA = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTA = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigB:
            M0P_ADTIM4->TTRIG_f.TRIGBS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTB = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTB = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigC:
            M0P_ADTIM4->TTRIG_f.TRIGCS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTC = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTC = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigD:
            M0P_ADTIM4->TTRIG_f.TRIGDS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_ADTIM4->FCONR_f.NOFIENTD = pstcAdtPortTrigCfg->bFltEn;
            M0P_ADTIM4->FCONR_f.NOFICKTD = pstcAdtPortTrigCfg->enFltClk;
            break;

        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief
 *          CHxX端口配置
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort    CHxX端口
 * \param   [in]  pstcAdtCHxXCfg   CHxX端口配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *********************************************************************/
en_result_t Adt_CHxXPortCfg(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                stc_adt_CHxX_port_cfg_t* pstcAdtCHxXCfg)
{
    if(NULL == pstcAdtCHxXCfg)
    {
        return ErrorInvalidParameter;
    }

    switch (enAdtCHxXPort)
    {
        case AdtCHxA:
            ADTx->PCONR_f.CAPCA = pstcAdtCHxXCfg->enCap;
            ADTx->PCONR_f.STACA = pstcAdtCHxXCfg->enStaOut;
            ADTx->PCONR_f.STPCA = pstcAdtCHxXCfg->enStpOut;
            ADTx->PCONR_f.STASTPSA = pstcAdtCHxXCfg->enStaStp;
            ADTx->PCONR_f.CMPCA = pstcAdtCHxXCfg->enCmpc;
            ADTx->PCONR_f.PERCA = pstcAdtCHxXCfg->enPerc;
            ADTx->PCONR_f.OUTENA = pstcAdtCHxXCfg->bOutEn;
            ADTx->PCONR_f.DISSELA = pstcAdtCHxXCfg->enDisSel;
            ADTx->PCONR_f.DISVALA = pstcAdtCHxXCfg->enDisVal;
            ADTx->FCONR_f.NOFIENGA = pstcAdtCHxXCfg->bFltEn;
            ADTx->FCONR_f.NOFICKGA = pstcAdtCHxXCfg->enFltClk;
            break;

        case AdtCHxB:
            ADTx->PCONR_f.CAPCB = pstcAdtCHxXCfg->enCap;
            ADTx->PCONR_f.STACB = pstcAdtCHxXCfg->enStaOut;
            ADTx->PCONR_f.STPCB = pstcAdtCHxXCfg->enStpOut;
            ADTx->PCONR_f.STASTPSB = pstcAdtCHxXCfg->enStaStp;
            ADTx->PCONR_f.CMPCB = pstcAdtCHxXCfg->enCmpc;
            ADTx->PCONR_f.PERCB = pstcAdtCHxXCfg->enPerc;
            ADTx->PCONR_f.OUTENB = pstcAdtCHxXCfg->bOutEn;
            ADTx->PCONR_f.DISSELB = pstcAdtCHxXCfg->enDisSel;
            ADTx->PCONR_f.DISVALB = pstcAdtCHxXCfg->enDisVal;
            ADTx->FCONR_f.NOFIENGB = pstcAdtCHxXCfg->bFltEn;
            ADTx->FCONR_f.NOFICKGB = pstcAdtCHxXCfg->enFltClk;
            break;

        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/************************************************************************
 * \brief
 *          使能端口刹车
 *
 * \param   [in]  port              端口
 * \param   [in]  pstcAdtBrkPtCfg   端口刹车配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ************************************************************************/
en_result_t Adt_EnableBrakePort(uint8_t port, stc_adt_break_port_cfg_t* pstcAdtBrkPtCfg)
{
    uint32_t u32Val;

    if (NULL == pstcAdtBrkPtCfg)
    {
        return ErrorInvalidParameter;
    }

    u32Val = M0P_ADTIM4->PTBKP;
    u32Val &= ~(1u<<port);
    M0P_ADTIM4->PTBKP = u32Val | (pstcAdtBrkPtCfg->enPol<<port);

    u32Val = M0P_ADTIM4->PTBKS;
    M0P_ADTIM4->PTBKS = u32Val | (1u<<port);

    return Ok;
}

/**********************************************************************
 * \brief
 *          清除端口刹车
 *
 * \param   none
 *
 * \retval  none
 **********************************************************************/
void Adt_ClearBrakePort(void)
{
    M0P_ADTIM4->PTBKS = 0;
}

/*********************************************************************
 * \brief
 *          无效条件3配置
 *
 * \param   [in]  pstcAdtDisable3   无效条件3配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ********************************************************************/
en_result_t Adt_Disable3Cfg(stc_adt_disable_3_cfg_t* pstcAdtDisable3)
{
    uint8_t i;

    if (NULL == pstcAdtDisable3)
    {
        return ErrorInvalidParameter;
    }

    Adt_ClearBrakePort();
    for (i = 0; i <= ADTIM_PORT_BKE_NUM; i++)
    {
        if (TRUE == pstcAdtDisable3->stcBrkPtCfg[i].bPortEn)
        {
            Adt_EnableBrakePort(i, &pstcAdtDisable3->stcBrkPtCfg[i]);
        }
    }

    M0P_ADTIM4->AOSSR_f.BFILTEN = pstcAdtDisable3->bFltEn;
    M0P_ADTIM4->AOSSR_f.BFILTS = pstcAdtDisable3->enFltClk;

    return Ok;
}

/*********************************************************************
 * \brief   软件刹车 Enable/Disable(仅适用于无效条件3使能的情况下)
 *
 * \param   [in]  bSwBrk           软件刹车使能/禁止
 *
 * \retval  en_result_t  Ok:  配置成功
 ********************************************************************/
en_result_t Adt_SwBrake(boolean_t bSwBrk)
{
    M0P_ADTIM4->AOSSR_f.SOFTBK = bSwBrk;

    return Ok;
}

/*******************************************************************
 * \brief
 *          获取端口刹车标志
 *
 * \param   none
 *
 * \retval  TRUE or FALSE
 ******************************************************************/
boolean_t Adt_GetPortBrakeFlag(void)
{
    return M0P_ADTIM4->AOSSR_f.FBRAKE;
}

/******************************************************************
 * \brief
 *          清除端口刹车标志
 *
 * \param   none
 *
 * \retval  none
 ******************************************************************/
void Adt_ClearPortBrakeFlag(void)
{
    M0P_ADTIM4->AOSCL_f.FBRAKE = 0;
}

/********************************************************************
 * \brief
 *          无效条件1配置
 *
 * \param   [in]  pstcAdtDisable1   无效条件1配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ********************************************************************/
en_result_t Adt_Disable1Cfg(stc_adt_disable_1_cfg_t* pstcAdtDisable1)
{

    if (NULL == pstcAdtDisable1)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADTIM4->AOSSR_f.SMH2 = pstcAdtDisable1->bTim6OutSH;
    M0P_ADTIM4->AOSSR_f.SMH1 = pstcAdtDisable1->bTim5OutSH;
    M0P_ADTIM4->AOSSR_f.SMH0 = pstcAdtDisable1->bTim4OutSH;
    M0P_ADTIM4->AOSSR_f.SML2 = pstcAdtDisable1->bTim6OutSL;
    M0P_ADTIM4->AOSSR_f.SML1 = pstcAdtDisable1->bTim5OutSL;
    M0P_ADTIM4->AOSSR_f.SML0 = pstcAdtDisable1->bTim4OutSL;

    return Ok;
}

/********************************************************************
 * \brief
 *          获取同高同低刹车标志
 *
 * \param   none
 *
 * \retval  TRUE or FALSE
 ********************************************************************/
boolean_t Adt_GetSameBrakeFlag(void)
{
    return M0P_ADTIM4->AOSSR_f.FSAME;
}

/*********************************************************************
 * \brief
 *          清除同高同低刹车标志
 *
 * \param   none
 *
 * \retval  none
 *********************************************************************/
void Adt_ClearSameBrakeFlag(void)
{
    M0P_ADTIM4->AOSCL_f.FSAME = 0;
}

/********************************************************************
 * \brief
 *          PWM展频配置
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtPwmDitherCfg   PWM展频配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *********************************************************************/
en_result_t Adt_PwmDitherCfg(M0P_ADTIM_TypeDef *ADTx, stc_adt_pwm_dither_cfg_t* pstcAdtPwmDitherCfg)
{


    if (NULL == pstcAdtPwmDitherCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->CR_f.DITENS = pstcAdtPwmDitherCfg->enAdtPDType;
    ADTx->CR_f.DITENB = pstcAdtPwmDitherCfg->bTimxBPDEn;
    ADTx->CR_f.DITENA = pstcAdtPwmDitherCfg->bTimxAPDEn;

    return Ok;
}

/**********************************************************************
 * \brief
 *          ADT初始化
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtBaseCntCfg     计数配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 **********************************************************************/
en_result_t Adt_Init(M0P_ADTIM_TypeDef *ADTx, stc_adt_basecnt_cfg_t* pstcAdtBaseCntCfg)
{


    if(NULL == pstcAdtBaseCntCfg)
    {
        return ErrorInvalidParameter;
    }

    if (AdtTriangleModeB < pstcAdtBaseCntCfg->enCntMode)
    {
        return ErrorInvalidParameter;
    }

    ADTx->GCONR_f.MODE = pstcAdtBaseCntCfg->enCntMode;
    ADTx->GCONR_f.DIR = pstcAdtBaseCntCfg->enCntDir;
    ADTx->GCONR_f.CKDIV = pstcAdtBaseCntCfg->enCntClkDiv;

    return Ok;
}

/************************************************************************
 * \brief
 *          ADT Deinit
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ***********************************************************************/
en_result_t Adt_DeInit(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->GCONR_f.START = 0;
    ADTx->CNTER = 0;
    ADTx->PCONR = 0;
    ADTx->GCONR = 0x00000100;
    ADTx->DCONR = 0;
    ADTx->ICONR = 0;
    ADTx->BCONR = 0;
    ADTx->FCONR = 0;
    ADTx->VPERR = 0;
    ADTx->PERAR = 0xFFFF;
    ADTx->PERBR = 0xFFFF;
    ADTx->GCMAR = 0xFFFF;
    ADTx->GCMBR = 0xFFFF;
    ADTx->GCMCR = 0xFFFF;
    ADTx->GCMDR = 0xFFFF;
    ADTx->DTDAR = 0xFFFF;
    ADTx->DTUAR = 0xFFFF;
    ADTx->HSTAR = 0;
    ADTx->HSTPR = 0;
    ADTx->HCELR = 0;
    ADTx->HCPAR = 0;
    ADTx->HCPBR = 0;
    ADTx->HCUPR = 0;
    ADTx->HCDOR = 0;
    ADTx->SSTAR = 0;
    ADTx->SSTPR = 0;
    ADTx->SCLRR = 0;
    ADTx->IFR = 0;
    ADTx->CR = 0x00000300;
    ADTx->AOSSR = 0;
    ADTx->AOSCL = 0;
    ADTx->PTBKS = 0;
    ADTx->PTBKP = 0;
    ADTx->TTRIG = 0;
    ADTx->ITRIG = 0;

    return Ok;
}

/***********************************************************************
 * \brief
 *          开始计数
 *
 * \param   [in]  ADTx                  ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ***********************************************************************/
en_result_t Adt_StartCount(M0P_ADTIM_TypeDef *ADTx)
{

    ADTx->GCONR_f.START = 1;

    return Ok;
}

/***********************************************************************
 * \brief
 *          停止计数
 *
 * \param   [in]  ADTx        ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 **********************************************************************/
en_result_t Adt_StopCount(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->GCONR_f.START = 0;

    return Ok;
}

/********************************************************************
 * \brief
 *          设置计数值
 *
 * \param   [in]  ADTx           ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Value       计数值
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 *******************************************************************/
en_result_t Adt_SetCount(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Value)
{
    ADTx->CNTER_f.CNT = u16Value;
    return Ok;
}

/********************************************************************
 * \brief
 *          获取计数值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 *
 * \retval  uint16_t  u16Value:  当前计数值
 *
 *******************************************************************/
uint16_t Adt_GetCount(M0P_ADTIM_TypeDef *ADTx)
{
    uint16_t u16Value;

    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));

    u16Value = ADTx->CNTER_f.CNT;

    return u16Value;
}

/**************************************************************************
 * \brief
 *          清除计数值
 *
 * \param   [in]  ADTx        ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 **************************************************************************/
en_result_t Adt_ClearCount(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->CNTER_f.CNT = 0;
    return Ok;
}

/*************************************************************************
 * \brief
 *          获取有效周期计数值
 *
 * \param   [in]  ADTx             ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  uint8_t u8TempCnt:    有效周期值
 *
 *************************************************************************/
uint8_t Adt_GetVperNum(M0P_ADTIM_TypeDef *ADTx)
{
    uint8_t u8TempCnt;


    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));

    u8TempCnt = ADTx->STFLR_f.VPERNUM;

    return u8TempCnt;
}

/*************************************************************************
 * \brief
 *          获取状态标志
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
* \param    [in]  enstate           状态标志类型
 *
 * \retval  TURE/FALSE
 *
 *************************************************************************/
boolean_t Adt_GetState(M0P_ADTIM_TypeDef *ADTx, en_adt_state_type_t enstate)
{


    ASSERT(IS_VALID_ADT_UNIT(enAdtUnit));
    ASSERT(IS_VALID_ADT_STATE(enstate));

    return GetBit(((uint32_t)&ADTx->STFLR), enstate);
}

/***********************************************************************
 * \brief
 *          配置计数周期
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Period         计数周期值
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ***********************************************************************/
en_result_t Adt_SetPeriod(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Period)
{
    ADTx->PERAR = u16Period;

    return Ok;
}

/***********************************************************************
 * \brief
 *          配置计数周期缓冲
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16PeriodBuf      计数周期缓冲值
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ***********************************************************************/
en_result_t Adt_SetPeriodBuf(M0P_ADTIM_TypeDef *ADTx, uint16_t u16PeriodBuf)
{
    ADTx->PERBR = u16PeriodBuf;
    ADTx->BCONR_f.BENP = 1u;

    return Ok;
}

/**********************************************************************
 * \brief
 *          清除计数周期缓冲
 *
 * \param   [in]  ADTx        ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 **********************************************************************/
en_result_t Adt_ClearPeriodBuf(M0P_ADTIM_TypeDef *ADTx)
{
    ADTx->BCONR_f.BENP = 0;
    ADTx->PERBR = 0;

    return Ok;
}

/***********************************************************************
 * \brief
 *          配置有效计数周期
 *
 * \param   [in]  ADTx                     ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtValidPerCfg       有效计数周期配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_SetValidPeriod(M0P_ADTIM_TypeDef *ADTx,
                               stc_adt_validper_cfg_t* pstcAdtValidPerCfg)
{


    if(NULL == pstcAdtValidPerCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->VPERR_f.PCNTS = pstcAdtValidPerCfg->enValidCnt;
    ADTx->VPERR_f.PCNTE = pstcAdtValidPerCfg->enValidCdt;
    ADTx->VPERR_f.GEPERID = pstcAdtValidPerCfg->bPeriodD;
    ADTx->VPERR_f.GEPERIC = pstcAdtValidPerCfg->bPeriodC;
    ADTx->VPERR_f.GEPERIB = pstcAdtValidPerCfg->bPeriodB;
    ADTx->VPERR_f.GEPERIA = pstcAdtValidPerCfg->bPeriodA;

    return Ok;
}

/************************************************************************
 * \brief
 *          配置比较输出计数基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCompare      通用比较基准寄存器
 * \param   [in]  u16Compare        比较基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 *************************************************************************/
en_result_t Adt_SetCompareValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_compare_t enAdtCompare,
                                uint16_t u16Compare)
{
    if (AdtCompareA == enAdtCompare)
    {
        ADTx->GCMAR = u16Compare;
    }
    else if (AdtCompareB == enAdtCompare)
    {
        ADTx->GCMBR = u16Compare;
    }
    else if (AdtCompareC == enAdtCompare)
    {
        ADTx->GCMCR = u16Compare;
    }
    else if (AdtCompareD == enAdtCompare)
    {
        ADTx->GCMDR = u16Compare;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**********************************************************************
 * \brief
 *          配置通用比较值/捕获值缓存传送
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 * \param   [in]  bCompareBufEn     通用比较值缓存传送使能
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 **********************************************************************/
en_result_t Adt_EnableValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                 en_adt_CHxX_port_t enAdtCHxXPort,
                                 boolean_t bCompareBufEn)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        ADTx->BCONR_f.BENA = bCompareBufEn;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        ADTx->BCONR_f.BENB = bCompareBufEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief
 *          清除比较输出计数值/捕获值缓存
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 **********************************************************************/
en_result_t Adt_ClearValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                     en_adt_CHxX_port_t enAdtCHxXPort)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        ADTx->GCMCR = 0;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        ADTx->GCMDR = 0;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief
 *          获取捕获值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 * \param   [in]  pu16Capture       捕获值指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_GetCaptureValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16Capture)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        *pu16Capture = ADTx->GCMAR_f.GCMA;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        *pu16Capture = ADTx->GCMBR_f.GCMB;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}

/**********************************************************************
 * \brief
 *          获取捕获缓存值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  enAdtCHxXPort     TIMxX通道
 * \param   [in]  pu16CaptureBuf    捕获缓存值指针
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 ***********************************************************************/
en_result_t Adt_GetCaptureBuf(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16CaptureBuf)
{
    if (AdtCHxA == enAdtCHxXPort)
    {
        *pu16CaptureBuf = ADTx->GCMCR_f.GCMC;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        *pu16CaptureBuf = ADTx->GCMDR_f.GCMD;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}

/***********************************************************************
 * \brief
 *          设置死区时间上基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Value          死区时间上基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ************************************************************************/
en_result_t Adt_SetDTUA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value)
{
    ADTx->DTUAR = u16Value;

    return Ok;
}

/***********************************************************************
 * \brief
 *          设置死区时间下基准值
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  u16Value          死区时间下基准值
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 ***********************************************************************/
en_result_t Adt_SetDTDA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value)
{
    ADTx->DTDAR = u16Value;

    return Ok;
}

/******************************************************************
 * \brief
 *          配置死区时间功能
 *
 * \param   [in]  ADTx          ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  bDTEn         死区功能使能
 * \param   [in]  bEqual        DTDAR的值和DTUAR的值自动相等
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 *****************************************************************/
en_result_t Adt_CfgDT(M0P_ADTIM_TypeDef *ADTx,
                         boolean_t bDTEn,
                         boolean_t bEqual)
{
    ADTx->DCONR_f.DTCEN = bDTEn;
    ADTx->DCONR_f.SEPA = bEqual;

    return Ok;
}

/*************************************************************************
 * \brief
 *          Z相输入屏蔽设置
 *
 * \param   [in]  ADTx              ADV Timer通道选择(M0P_ADTIM4、M0P_ADTIM5、M0P_ADTIM6)
 * \param   [in]  pstcAdtZMaskCfg   Z相输入屏蔽功能配置指针
 *
 * \retval  en_result_t  Ok:  配置成功
 *
 *************************************************************************/
en_result_t Adt_CfgZMask(M0P_ADTIM_TypeDef *ADTx, stc_adt_zmask_cfg_t* pstcAdtZMaskCfg)
{
    if(NULL == pstcAdtZMaskCfg)
    {
        return ErrorInvalidParameter;
    }

    ADTx->GCONR_f.ZMSK = pstcAdtZMaskCfg->enZMaskCycle;
    ADTx->GCONR_f.ZMSKPOS = pstcAdtZMaskCfg->bFltPosCntMaksEn;
    ADTx->GCONR_f.ZMSKREV = pstcAdtZMaskCfg->bFltRevCntMaksEn;

    return Ok;
}

//@} // AdtGroup

/* ========================================================================== */
/*  bgr.c                                                                     */
/* ========================================================================== */


/** \file bgr.c
 **
 ** Common API of bgr.
 ** @link flashGroup Some description @endlink
 **
 **   - 2018-05-08
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup FlashGroup
 ******************************************************************************/
//@{

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
 *****************************************************************************
 ** \brief BGR 使能
 **
 **
 ** \retval Null
 *****************************************************************************/
void Bgr_BgrEnable(void)
{
    M0P_BGR->CR |= 0x1u;

    delay10us(2);
}

/**
 *****************************************************************************
 ** \brief BGR 禁止
 **
 **
 ** \retval Null
 *****************************************************************************/
void Bgr_BgrDisable(void)
{
    M0P_BGR->CR &= 0x2u;
}

/**
 *****************************************************************************
 ** \brief BGR 温度传感器使能(需要先开启BGR)
 **
 **
 ** \retval Null
 *****************************************************************************/
void Bgr_TempSensorEnable(void)
{
    M0P_BGR->CR |= 0x2u;

    delay10us(2);
}

/**
 *****************************************************************************
 ** \brief BGR 温度传感器禁止
 **
 **
 ** \retval Null
 *****************************************************************************/
void Bgr_TempSensorDisable(void)
{
    M0P_BGR->CR &= 0x1u;
}


//@} // BgrGroup

/* ========================================================================== */
/*  bt.c                                                                      */
/* ========================================================================== */


/** \file bt.c
 **
 ** Common API of base timer.
 ** @link btGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup BtGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_TIM(x)         (TIM0 == (x) ||\
                                 TIM1 == (x) ||\
                                 TIM2 == (x))

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
 *****************************************************************************
 ** \brief Base Timer 中断标志获取
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval TRUE or FALSE
 *****************************************************************************/
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit)
{
    boolean_t bRetVal = FALSE;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            bRetVal = M0P_TIM0->IFR_f.UIF ? TRUE : FALSE;
            break;
        case TIM1:
            bRetVal = M0P_TIM1->IFR_f.UIF ? TRUE : FALSE;
            break;
        case TIM2:
            bRetVal = M0P_TIM2->IFR_f.UIF ? TRUE : FALSE;
            break;
        default:
            bRetVal = FALSE;
            break;
    }

    return bRetVal;
}

/**
 *****************************************************************************
 ** \brief Base Timer 中断标志清除
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->ICLR_f.UIF = FALSE;
            break;
        case TIM1:
            M0P_TIM1->ICLR_f.UIF = FALSE;;
            break;
        case TIM2:
            M0P_TIM2->ICLR_f.UIF = FALSE;;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 中断使能
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_EnableIrq (en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->CR_f.UIE = TRUE;
            break;
        case TIM1:
            M0P_TIM1->CR_f.UIE = TRUE;
            break;
        case TIM2:
            M0P_TIM2->CR_f.UIE = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 中断禁止
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_DisableIrq(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->CR_f.UIE = FALSE;
            break;
        case TIM1:
            M0P_TIM1->CR_f.UIE = FALSE;
            break;
        case TIM2:
            M0P_TIM2->CR_f.UIE = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 初始化配置
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 ** \param [in]  pstcCfg       初始化配置结构体指针
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_Init(en_bt_unit_t enUnit, stc_bt_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            {
                M0P_TIM0->CR_f.GATEP = pstcCfg->enGateP;
                M0P_TIM0->CR_f.GATE   = pstcCfg->enGate;
                M0P_TIM0->CR_f.PRS    = pstcCfg->enPRS;
                M0P_TIM0->CR_f.TOGEN = pstcCfg->enTog;
                M0P_TIM0->CR_f.CT     = pstcCfg->enCT;
                M0P_TIM0->CR_f.MD     = pstcCfg->enMD;

            }
            break;
        case TIM1:
            {
                M0P_TIM1->CR_f.GATEP = pstcCfg->enGateP;
                M0P_TIM1->CR_f.GATE   = pstcCfg->enGate;
                M0P_TIM1->CR_f.PRS    = pstcCfg->enPRS;
                M0P_TIM1->CR_f.TOGEN = pstcCfg->enTog;
                M0P_TIM1->CR_f.CT     = pstcCfg->enCT;
                M0P_TIM1->CR_f.MD     = pstcCfg->enMD;

            }
            break;
        case TIM2:
            {
                M0P_TIM2->CR_f.GATEP = pstcCfg->enGateP;
                M0P_TIM2->CR_f.GATE   = pstcCfg->enGate;
                M0P_TIM2->CR_f.PRS    = pstcCfg->enPRS;
                M0P_TIM2->CR_f.TOGEN = pstcCfg->enTog;
                M0P_TIM2->CR_f.CT     = pstcCfg->enCT;
                M0P_TIM2->CR_f.MD     = pstcCfg->enMD;

            }
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 启动运行
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->CR_f.CTEN = TRUE;
            break;
        case TIM1:
            M0P_TIM1->CR_f.CTEN = TRUE;
            break;
        case TIM2:
            M0P_TIM2->CR_f.CTEN = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 停止运行
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_Stop(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->CR_f.CTEN = FALSE;
            break;
        case TIM1:
            M0P_TIM1->CR_f.CTEN = FALSE;
            break;
        case TIM2:
            M0P_TIM2->CR_f.CTEN = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 重载值设置
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 ** \param [in]  u16Data          16bits重载值
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->ARR_f.ARR = u16Data;
            break;
        case TIM1:
            M0P_TIM1->ARR_f.ARR = u16Data;
            break;
        case TIM2:
            M0P_TIM2->ARR_f.ARR = u16Data;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 16位计数器初值设置
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 ** \param [in]  u16Data          16位初值
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->CNT_f.CNT = u16Data;
            break;
        case TIM1:
            M0P_TIM1->CNT_f.CNT = u16Data;
            break;
        case TIM2:
            M0P_TIM2->CNT_f.CNT = u16Data;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 16位计数值获取
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval 16bits计数值
 *****************************************************************************/
uint16_t Bt_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            u16CntData = M0P_TIM0->CNT_f.CNT;
            break;
        case TIM1:
            u16CntData = M0P_TIM1->CNT_f.CNT;
            break;
        case TIM2:
            u16CntData = M0P_TIM2->CNT_f.CNT;
            break;
        default:
            u16CntData = 0;
            break;
    }

    return u16CntData;
}

/**
 *****************************************************************************
 ** \brief Base Timer 32位计数器初值设置
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 ** \param [in]  u32Data          32位初值
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Bt_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data)
{
    en_result_t enResult = Ok;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0->CNT32_f.CNT32 = u32Data;
            break;
        case TIM1:
            M0P_TIM1->CNT32_f.CNT32 = u32Data;
            break;
        case TIM2:
            M0P_TIM2->CNT32_f.CNT32 = u32Data;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer 32位计数值获取
 **
 **
 ** \param [in]  enUnit           Timer通道选择（TIM0、TIM1、TIM2）
 **
 ** \retval 32bits计数值
 *****************************************************************************/
uint32_t Bt_Cnt32Get(en_bt_unit_t enUnit)
{
    uint32_t    u32CntData = 0;

    ASSERT(IS_VALID_TIM(enUnit));

    switch (enUnit)
    {
        case TIM0:
            u32CntData = M0P_TIM0->CNT32_f.CNT32;
            break;
        case TIM1:
            u32CntData = M0P_TIM1->CNT32_f.CNT32;
            break;
        case TIM2:
            u32CntData = M0P_TIM2->CNT32_f.CNT32;
            break;
        default:
            u32CntData = 0;
            break;
    }

    return u32CntData;
}

//@} // BtGroup

/* ========================================================================== */
/*  crc.c                                                                     */
/* ========================================================================== */


/** \file crc.c
 **
 ** Common API of crc.
 ** @link crcGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup CrcGroup
 ******************************************************************************/
//@{

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
 *****************************************************************************
 ** \brief CRC16 编码(字节填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu8Data          待编码数据指针（字节方式输入）
 ** \param [in]  u32Len           待编码数据长度（字节数）
 **
 ** \retval CRC16                 CRC16编码值.
 *****************************************************************************/
uint16_t CRC16_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    M0P_CRC->RESULT = 0xFFFF;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(半字填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu16Data          待编码数据指针（半字方式输入）
 ** \param [in]  u32Len           待编码数据长度（半字数）
 **
 ** \retval CRC16                 CRC16编码值.
 *****************************************************************************/
uint16_t CRC16_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(字填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu32Data          待编码数据指针（字方式输入）
 ** \param [in]  u32Len            待编码数据长度（字数）
 **
 ** \retval CRC16                  CRC16编码值.
 *****************************************************************************/
uint16_t CRC16_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(字节填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu8Data          待校验数据指针（字节方式输入）
 ** \param [in]  u32Len           待校验数据长度（字节数）
 ** \param [in]  u16CRC           待校验CRC16值
 **
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC16_Check8(uint8_t* pu8Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }

     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((((uint32_t)u16CRC)>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)(((uint32_t)u16CRC>>8)&0xFF);

    enResult = M0P_CRC->RESULT_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(半字填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu16Data         待校验数据指针（半字方式输入）
 ** \param [in]  u32Len           待校验数据长度（半字数）
 ** \param [in]  u16CRC           待校验CRC16值
 **
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC16_Check16(uint16_t* pu16Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }

     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = u16CRC;

    enResult = M0P_CRC->RESULT_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(字填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu32Data         待校验数据指针（字方式输入）
 ** \param [in]  u32Len           待校验数据长度（字数）
 ** \param [in]  u16CRC           待校验CRC16值
 **
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC16_Check32(uint32_t* pu32Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }

     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = u16CRC;

    enResult = M0P_CRC->RESULT_f.FLAG ? Ok : Error;

    return (enResult);
}


//@} // CrcGroup

/* ========================================================================== */
/*  flash.c                                                                   */
/* ========================================================================== */


/** \file flash.c
 **
 ** Common API of flash.
 ** @link flashGroup Some description @endlink
 **
 **   - 2018-05-08
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup FlashGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define FLASH_END_ADDR              (0x00007FFFu)
#define FLASH_BYPASS()              M0P_FLASH->BYPASS = 0x5A5A;\
                                    M0P_FLASH->BYPASS = 0xA5A5;
#define FLASH_IE_TRUE               (0x03)
#define FLASH_IE_FALSE              (0x00)

#define FLASH_TIMEOUT_INIT          (0xFFu)
#define FLASH_TIMEOUT_PGM           (0xFFu)
#define FLASH_TIMEOUT_ERASE         (0xFFu)

#define FLASH_LOCK_ALL              (0u)
#define FLASH_UNLOCK_ALL            (0xFFFFu)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief FLASH OP
 **
 ** Flash 操作控制数据类型重定义
 ******************************************************************************/
typedef enum en_flash_op
{
    Read        = 0u,           ///<读配置值
    Program     = 1u,           ///<编程配置值
    SectorErase = 2u,           ///<扇区擦除配置值
    ChipErase   = 3u,           ///<全片擦除配置值
} en_flash_op_t;

/**
 ******************************************************************************
 ** \brief FLASH 编程时间参数配置
 **
 ** FLASH编程时间参数配置数组定义 (4MHz)
 ******************************************************************************/
const uint32_t pu32PcgTimer4M[] = {
                                    0x20u,          //Tnvs
                                    0x17u,          //Tpgs
                                    0x1Bu,          //Tprog
                                    0x4650u,        //Tserase
                                    0x222E0u,       //Tmerase
                                    0x18u,          //Tprcv
                                    0xF0u,          //Tsrcv
                                    0x3E8u          //Tmrcv
                                  };
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
 *****************************************************************************
 ** \brief Flash中断标志获取
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 **
 ** \retval TRUE or FALSE
 *****************************************************************************/
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType)
{
    boolean_t bRetVal = FALSE;

    if(M0P_FLASH->IFR & enFlashIntType)
    {
        bRetVal =  TRUE;
    }

    return bRetVal;
}

/**
 *****************************************************************************
 ** \brief Flash中断标志清除
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    M0P_FLASH->ICLR &= ~(uint32_t)enFlashIntType;
    enResult = Ok;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Flash中断使能
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Flash_EnableIrq (en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE |= enFlashIntType;

    enResult = Ok;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Flash中断禁止
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE &= ~(uint32_t)enFlashIntType;

    enResult = Ok;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief FLASH 初始化函数——中断服务程序、编程时间配置及低功耗模式
 **
 ** 该函数用于配置中断服务函数、低功耗模式、根据系统时钟配置FLASH编程时间相关寄存器.
 **
 ** \param [in]  u8FreqCfg        FLASH编程时钟频率配置(根据HCLK的频率选择配置值)：
 **                               1      - 4MHz;
 **                               2      - 8MHz;
 **                               4      - 16MHz;
 **                               6      - 24MHz;
 **                               8      - 32MHz;
 **                               other   -  无效值
 ** \param [in] bDpstbEn          TRUE  - 当系统进入DeepSleep模式，FLASH进入低功耗模式;
 **                               FALSE - 当系统进入DeepSleep模式，FLASH不进入低功耗模式;
 **
 ** \retval Ok                    操作成功.
 ** \retval ErrorInvalidParameter 参数无效.
 ** \retval ErrorUninitialized    初始化失败。
 *****************************************************************************/
en_result_t Flash_Init(uint8_t u8FreqCfg)
{
    uint32_t                u32Index  = 0;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_INIT;
    en_result_t             enResult  = Ok;
    uint32_t                u32PrgTimer[8] = {0};
    volatile uint32_t       *pu32PrgTimerReg = (volatile uint32_t*)M0P_FLASH;

    if ((1  != u8FreqCfg) && (2  != u8FreqCfg) &&
        (4  != u8FreqCfg) && (6  != u8FreqCfg) &&
        (8  != u8FreqCfg))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }


    //flash时间参数配置值计算
    for(u32Index=0; u32Index<8; u32Index++)
    {
        u32PrgTimer[u32Index] = u8FreqCfg * pu32PcgTimer4M[u32Index];
    }



    //flash时间参数寄存器配置
    for(u32Index=0; u32Index<8; u32Index++)
    {
        u32TimeOut = FLASH_TIMEOUT_INIT;
        while(pu32PrgTimerReg[u32Index]  != u32PrgTimer[u32Index])
        {
            if(u32TimeOut--)
            {
                FLASH_BYPASS();
                pu32PrgTimerReg[u32Index] = u32PrgTimer[u32Index];
            }
            else
            {
                return ErrorUninitialized;
            }
        }
    }

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 字节写
 **
 ** 用于向FLASH写入1字节数据.
 **
 ** \param [in]  u32Addr          Flash地址
 ** \param [in]  u8Data           1字节数据
 **
 ** \retval Ok                    写入成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t u8Data)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;

    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }

    //Flash 解锁
    Flash_UnlockAll();

    //write data
    *((volatile uint8_t*)u32Addr) = u8Data;

    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 加锁
    Flash_LockAll();

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 半字写
 **
 ** 用于向FLASH写入半字（2字节）数据.
 **
 ** \param [in]  u32Addr         Flash地址
 ** \param [in]  u16Data        半字（2字节）数据
 **
 ** \retval Ok                    写入成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;

    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }

    //Flash 解锁
    Flash_UnlockAll();

    //write data
    *((volatile uint16_t*)u32Addr) = u16Data;

    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 加锁
    Flash_LockAll();

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 字写
 **
 ** 用于向FLASH写入1个字的数据.
 **
 ** \param [in]  u32Addr         Flash地址
 ** \param [in]  u32Data         1个字数据
 **
 ** \retval Ok                    写入成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;

    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 解锁
    Flash_UnlockAll();

    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }

    //write data
    *((volatile uint32_t*)u32Addr) = u32Data;

    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 加锁
    Flash_LockAll();

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 扇区擦除
 **
 ** FLASH 扇区擦除.
 **
 ** \param [in]  u32SectorAddr    所擦除扇区内的地址
 **
 ** \retval Ok                    擦除成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_SectorErase(uint32_t u32SectorAddr)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;

    if (FLASH_END_ADDR < u32SectorAddr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }

    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 解锁
    Flash_UnlockAll();

    //set OP
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(SectorErase != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = SectorErase;
        }
        else
        {
            return ErrorTimeout;
        }
    }

    //write data
    *((volatile uint8_t*)u32SectorAddr) = 0;

    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 加锁
    Flash_LockAll();

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 全片擦除(该函数仅限RAM中运行！！！)
 **
 ** FLASH 全片擦除.
 **
 **
 ** \retval Ok              擦除成功.
 ** \retval ErrorTimeout    操作超时
 **
 *****************************************************************************/
en_result_t Flash_ChipErase(void)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;

    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //set OP
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(ChipErase != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = ChipErase;
        }
        else
        {
            return ErrorTimeout;
        }
    }

    //Flash 解锁
    Flash_UnlockAll();

    //write data
    *((volatile uint8_t*)0) = 0;

    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    //Flash 加锁
    Flash_LockAll();

    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 编程保护加锁
 **
 **
 ** \retval Null
 *****************************************************************************/
void Flash_LockAll(void)
{
    FLASH_BYPASS();
    M0P_FLASH->SLOCK = FLASH_LOCK_ALL;

}

/**
 *****************************************************************************
 ** \brief FLASH 编程保护解锁
 **
 **
 ** \retval Null
 *****************************************************************************/
void Flash_UnlockAll(void)
{

    FLASH_BYPASS();
    M0P_FLASH->SLOCK = FLASH_UNLOCK_ALL;

}

/**
 *****************************************************************************
 ** \brief FLASH 读等待周期设置
 **
 ** \param [in]  enWaitCycle  插入FLASH读等待周期数枚举类型
 **
 ** \retval Ok                    解锁成功
 ** \retval ErrorInvalidParameter 参数错误
 *****************************************************************************/
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle)
{
    en_result_t enResult = Ok;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.WAIT = enWaitCycle;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief FLASH LOCK 设置
 **
 ** \param [in]  u32LockValue 32bits，对应bit=0：加锁，对应Sector不允许擦写；对应bit=1：解锁。
 ** \note  加解锁范围Sector：[i*4, i*4+3]
 **        (i表示u32LockValue的bit位置，0~31)
 **        例如：u32LockValue = 0x00000002,
 **              则加解锁范围为：[Sector8,Sector11]
 ** \retval Ok                    解锁成功
 ** \retval ErrorInvalidParameter 参数错误
 *****************************************************************************/
en_result_t Flash_LockSet(uint32_t u32LockValue)
{
    FLASH_BYPASS();
    M0P_FLASH->SLOCK = u32LockValue;

    return Ok;
}
//@} // FlashGroup

/* ========================================================================== */
/*  gpio.c                                                                    */
/* ========================================================================== */

/******************************************************************************/
/** \file Gpio.c
 **
 ** GPIO driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-04-22  1.0  Lux First version
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 *******************************************************************************
 ** \addtogroup GpioGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_PIN(port,pin)      (  )
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
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
 *******************************************************************************
 ** \brief GPIO 初始化
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [in]  pstcGpioCfg     IO 配置结构体指针
 **
 ** \retval Ok         设置成功
 **         其他值     设置失败
 ******************************************************************************/
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_cfg_t  *pstcGpioCfg)
{
    //配置为默认值,GPIO功能
    SetBit((uint32_t)&M0P_GPIO->P0ADS + enPort, enPin, FALSE);
    *((uint32_t*)(((uint32_t)((&(M0P_GPIO->P01_SEL)) - 1u) + enPort) + (((uint32_t)enPin)<<2))) = GpioAf0;

    //默认输出值配置
    SetBit(((uint32_t)&M0P_GPIO->P0OUT + enPort), enPin, pstcGpioCfg->bOutputVal);
    //方向配置
    SetBit(((uint32_t)&M0P_GPIO->P0DIR + enPort), enPin, (boolean_t)(pstcGpioCfg->enDir));
    //驱动能力配置
    SetBit(((uint32_t)&M0P_GPIO->P0DR + enPort), enPin, (boolean_t)(pstcGpioCfg->enDrv));
    //上拉/下拉配置
    SetBit(((uint32_t)&M0P_GPIO->P0PU + enPort), enPin, (boolean_t)(pstcGpioCfg->enPu));
    SetBit(((uint32_t)&M0P_GPIO->P0PD + enPort), enPin, (boolean_t)(pstcGpioCfg->enPd));
    //开漏输出功能
    SetBit(((uint32_t)&M0P_GPIO->P0OD + enPort), enPin, (boolean_t)(pstcGpioCfg->enOD));

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO输入值获取
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval boolean_t            IO电平高低
 ******************************************************************************/
boolean_t Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return GetBit(((uint32_t)&M0P_GPIO->P0IN + enPort), enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port输入数据获取
 **
 ** \param [in]  enPort          IO Port
 **
 ** \retval boolean_t            IO Port数据
 ******************************************************************************/
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort)
{
    return (uint16_t)(*((uint32_t *)((uint32_t)&M0P_GPIO->P0IN + enPort)));
}

/**
 *******************************************************************************
 ** \brief GPIO IO输出值写入
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [out] bVal            输出值
 **
 ** \retval en_result_t          Ok      设置成功
 **                              其他值  设置失败
 ******************************************************************************/
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal)
{
    SetBit(((uint32_t)&M0P_GPIO->P0OUT + enPort), enPin, bVal);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO输出值获取
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval boolean_t            IO电平高低
 ******************************************************************************/
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return GetBit(((uint32_t)&M0P_GPIO->P0OUT + enPort), enPin);
}


/**
 *******************************************************************************
 ** \brief GPIO IO配置为模拟功能模式
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval Ok         设置成功
 **         其他值     设置失败
 ******************************************************************************/
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    SetBit((uint32_t)&M0P_GPIO->P0ADS + enPort, enPin, TRUE);

    return Ok;
}

/**
 *******************************************************************************
** \brief GPIO IO复用功能设置
 **
 ** \param [in]  enPort    IO Port口
 ** \param [in]  enPin     IO Pin脚
 ** \param [in]  enAf      复用功能枚举类型选择
 ** \retval Ok             设置成功
 **         其他值         设置失败
 ******************************************************************************/
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf)
{
    *((uint32_t*)(((uint32_t)((&(M0P_GPIO->P01_SEL)) - 1u) + enPort) + (((uint32_t)enPin)<<2))) = enAf;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO中断使能
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [in]  enType          中断使能类型
 **
 ** \retval      Ok            设置成功
 ******************************************************************************/
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = ((uint32_t)((&M0P_GPIO->P0HIE) + enType)) + enPort;

    SetBit(u32PieAddr, enPin, TRUE);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO中断关闭
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [in]  enType          中断使能类型
 **
 ** \retval      Ok            设置成功
 ******************************************************************************/
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = ((uint32_t)((&M0P_GPIO->P0HIE) + enType)) + enPort;

    SetBit(u32PieAddr, enPin, FALSE);

    return Ok;
}


/**
 *******************************************************************************
 ** \brief GPIO 获得IO中断状态
 **
 ** \param [in]  u8Port          IO Port口
 ** \param [in]  u8Pin           IO Pin脚
 **
 ** \retval      IO中断状态开关
 ******************************************************************************/
boolean_t Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return GetBit((uint32_t)&M0P_GPIO->P0STAT + enPort, enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO 清除IO中断状态
 **
 ** \param [in]  u8Port          IO Port口
 ** \param [in]  u8Pin           IO Pin脚
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    SetBit((uint32_t)&M0P_GPIO->P0ICLR + enPort, enPin, FALSE);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——中断模式配置
 **
 ** \param [in]  enIrqMode          端口中断模式
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfIrqModeCfg(en_gpio_sf_irqmode_t enIrqMode)
{
    M0P_GPIO->CTRL0_f.IESEL = enIrqMode;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——IR输出极性配置
 **
 ** \param [in]  enIrPolMode          IR输出极性配置枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfIrPolCfg(en_gpio_sf_irpol_t enIrPolMode)
{
    M0P_GPIO->CTRL1_f.IR_POL = enIrPolMode;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——HCLK输出配置
 **
 ** \param [in]  enGate         HCLK输出使能
 ** \param [in]  enDiv          输出分频枚举值
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfHClkOutputCfg(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.HCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.HCLK_SEL = enDiv;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——PCLK输出配置
 **
 ** \param [in]  enGate         PCLK输出使能
 ** \param [in]  enDiv          输出分频枚举值
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.PCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.PCLK_SEL = enDiv;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——外部时钟输入来源配置
 **
 ** \param [in]  enExtClk         外部时钟信号来源选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfExtClkCfg(en_gpio_sf_ssn_extclk_t enExtClk)
{
    M0P_GPIO->CTRL1_f.EXT_CLK_SEL  = enExtClk;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——SSN 通道信号来源配置
 **
 ** \param [in]  enSsn         SSN 信号来源选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfSsnCfg(en_gpio_sf_ssn_extclk_t enSsn)
{
    M0P_GPIO->CTRL1_f.SSN_SEL = enSsn;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——Timer 门控输入配置
 **
 ** \param [in]  enTimG       Timer类型选择枚举
 ** \param [in]  enSf         Timer互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfTimGCfg(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf)
{
    M0P_GPIO->CTRL4 &= (uint32_t)(~(0x03U<<enTimG));
    M0P_GPIO->CTRL4 |= (uint32_t)(enSf<<enTimG);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——Timer 捕获输入选择配置
 **
 ** \param [in]  enTimC       Timer类型选择枚举
 ** \param [in]  enSf         Timer互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf)
{
    M0P_GPIO->CTRL3 &= (uint32_t)(~(0x03u<<enTimC));
    M0P_GPIO->CTRL3 |= (uint32_t)(enSf<<enTimC);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——PCA 捕获输入选择配置
 **
 ** \param [in]  enPca        PCA类型选择枚举
 ** \param [in]  enSf         PCA互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfPcaCfg(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf)
{
    M0P_GPIO->CTRL2 &= (uint32_t)(~(0x03u<<enPca));
    M0P_GPIO->CTRL2 |= (uint32_t)(enSf<<enPca);

    return Ok;
}

//@} // GpioGroup

/* ========================================================================== */
/*  i2c.c                                                                     */
/* ========================================================================== */

/******************************************************************************/
/** \file I2C.c
 **
 ** WDT function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2018-03-13  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/**
 *******************************************************************************
 ** \addtogroup I2cGroup
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  I2C设置波特率配置寄存器
 **
 ** \param [in] u8Tm 波特率配置值
 **
 ** \retval enRet 成功或失败
 **
 ******************************************************************************/
 en_result_t I2C_SetBaud(M0P_I2C_TypeDef* I2Cx, uint8_t u8Tm)
 {
     en_result_t enRet = Error;

     I2Cx->TM = u8Tm;

     enRet = Ok;
     return enRet;
 }
 /**
 ******************************************************************************
 ** \brief  I2C功能设置相关函数
 **
 ** \param [in] enFunc功能参数
 **
 ** \retval enRet 成功或失败
 **
 ******************************************************************************/
en_result_t I2C_SetFunc(M0P_I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
{
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, enFunc, TRUE);

    enRet = Ok;
    return enRet;
}
 /**
 ******************************************************************************
 ** \brief  I2C功能清除相关函数
 **
 ** \param [in] enFunc功能参数
 **
 ** \retval enRet 成功或失败
 **
 ******************************************************************************/
 en_result_t I2C_ClearFunc(M0P_I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
 {
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, enFunc, FALSE);

    enRet = Ok;
    return enRet;
 }
 /**
 ******************************************************************************
 ** \brief  I2C获取中断标记函数
 **
 ** \param 无
 **
 ** \retval bIrq中断标记
 **
 ******************************************************************************/
boolean_t I2C_GetIrq(M0P_I2C_TypeDef* I2Cx)
{
    if(I2Cx->CR&0x8)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/**
 ******************************************************************************
 ** \brief  I2C清除中断标记函数
 **
 ** \param 无
 **
 ** \retval bIrq中断标记
 **
 ******************************************************************************/
en_result_t I2C_ClearIrq(M0P_I2C_TypeDef* I2Cx)
{
    en_result_t enRet = Error;

    I2Cx->CR &= ~0x8u;

    enRet = Ok;
    return enRet;
}
 /**
 ******************************************************************************
 ** \brief  I2C获取相关状态
 **
 ** \param 无
 **
 ** \retval I2C状态
 **
 ******************************************************************************/
uint8_t I2C_GetState(M0P_I2C_TypeDef* I2Cx)
{
    uint8_t u8State = 0;

    u8State = I2Cx->STAT;

    return u8State;
}

/**
 ******************************************************************************
 ** \brief  字节数据写函数
 **
 ** \param  u8Data写数据
 **
 ** \retval 写数据是否成功
 **
 ******************************************************************************/
en_result_t I2C_WriteByte(M0P_I2C_TypeDef* I2Cx, uint8_t u8Data)
{
    en_result_t enRet = Error;

    I2Cx->DATA = u8Data;

    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief  字节数据读函数
 **
 ** \param  无
 **
 ** \retval 读取数据
 **
 ******************************************************************************/
uint8_t I2C_ReadByte(M0P_I2C_TypeDef* I2Cx)
{
    uint8_t u8Data = 0;

    u8Data = I2Cx->DATA;

    return u8Data;
}

/**
 ******************************************************************************
 ** \brief  I2C模块初始化
 **
 ** \param pstcI2CCfg初始化配置结构体
 **
 ** \retval 初始化是否成功
 **
 ******************************************************************************/
en_result_t I2C_Init(M0P_I2C_TypeDef* I2Cx, stc_i2c_cfg_t *pstcI2CCfg)
{
   en_result_t enRet = Error;
   uint8_t     u8Tm;

   M0P_RESET->PERI_RESET &= ~(uint32_t)0x10u;
   M0P_RESET->PERI_RESET |= (uint32_t)0x10u;

   I2Cx->CR = 0;
   I2Cx->CR = pstcI2CCfg->enMode;

   if((pstcI2CCfg->u32Baud<<4) > pstcI2CCfg->u32Pclk)
   {
        return Error;
   }

   if(I2cMasterMode == pstcI2CCfg->enMode)
   {
        I2Cx->TMRUN = TRUE;
        ///< Fsck = Fpclk/8*(Tm+1)
        u8Tm = ((pstcI2CCfg->u32Pclk / pstcI2CCfg->u32Baud) >> 3) - 1;
        if(9 > u8Tm)
        {
            I2C_SetFunc(I2Cx,I2cHlm_En);
        }
        enRet = I2C_SetBaud(I2Cx, u8Tm);
   }
   else
   {
        I2Cx->TMRUN = FALSE;
        pstcI2CCfg->u8SlaveAddr = (uint8_t)(((uint32_t)pstcI2CCfg->u8SlaveAddr<<1)|(pstcI2CCfg->bGc));
        I2Cx->ADDR = pstcI2CCfg->u8SlaveAddr;
   }

   return enRet;
}

//@} // I2cGroup

/* ========================================================================== */
/*  lpm.c                                                                     */
/* ========================================================================== */


/** \file lpm.c
 **
 ** Common API of lpm.
 ** @link LpmGroup Some description @endlink
 **
 **   - 2017-06-06
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup LpmGroup
 ******************************************************************************/
//@{

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
 *****************************************************************************
 ** \brief 进入深度睡眠模式
 **
 ** \input bOnExit - TRUE:当退出异常处理后，自动再次进入休眠；
 **                  FALSE：唤醒后不再自动进入休眠
 **
 ** \retval NULL
 *****************************************************************************/
void Lpm_GotoDeepSleep(boolean_t bOnExit)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    SCB->SCR |= 1u<<bOnExit;
    __WFI();
}

/**
 *****************************************************************************
 ** \brief 进入普通睡眠模式
 **
 ** \input bOnExit - TRUE:当退出异常处理后，自动再次进入休眠；
 **                  FALSE：唤醒后不再自动进入休眠
 **
 ** \retval NULL
 *****************************************************************************/
void Lpm_GotoSleep(boolean_t bOnExit)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    SCB->SCR |= 1u<<bOnExit;
    __WFI();
}

//@} // LpmGroup

/* ========================================================================== */
/*  lvd.c                                                                     */
/* ========================================================================== */

/******************************************************************************/
/** \file lvd.c
 **
 ** Low Voltage Detect driver API.
 ** @link Lvd Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup LvdGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_INPUT(x)       ( (x) <= LvdInputP25 )

#define IS_VALID_THRESHOLD(x)   ( (x) <= LvdTH3p3V )

#define IS_VALID_FILTER(x)      ( (x) <= LvdFilter29ms )

#define IS_VALID_IRQTYPE(x)     ( (x) <= LvdIrqFall )


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
// static void LvdEnableNvic(void);
// static void LvdDisableNvic(void);
// static en_result_t LvdEnable(en_lvd_type_t enType, boolean_t bFlag);

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * \brief
 *          使能LVD中断
 *
 * \param   [in]  enType  LVD中断类型
 *
 * \retval  en_result_t  Ok:  设置成功
 * \retval  en_result_t  ErrorInvalidParameter:  无效类型
 */
void Lvd_EnableIrq(void)
{
    M0P_LVD->CR_f.IE = TRUE;
}

/**
 * \brief
 *          除能LVD中断
 *
 * \param   无
 *
 * \retval  无
 */
void Lvd_DisableIrq(void)
{
    M0P_LVD->CR_f.IE = FALSE;
}

/**
 * \brief
 *          LVD初始化
 *
 * \param   [in]  pstcCfg  LVD配置指针
 *
 * \retval  无
 */
void Lvd_Init(stc_lvd_cfg_t *pstcCfg)
{
    M0P_LVD->CR = 0;

    M0P_LVD->CR = (uint32_t)pstcCfg->enAct        |
                  (uint32_t)pstcCfg->enFilter     |
                  (uint32_t)pstcCfg->enFilterTime |
                  (uint32_t)pstcCfg->enInputSrc   |
                  (uint32_t)pstcCfg->enIrqType    |
                  (uint32_t)pstcCfg->enThreshold;
}

/**
 * \brief
 *          使能LVD
 *
 * \param   无
 *
 * \retval  无
 *
 */
void Lvd_Enable(void)
{
    M0P_LVD->CR_f.LVDEN = 1u;
}

/**
 * \brief
 *          除能LVD
 *
 * \param   无
 *
 * \retval  无
 */
void Lvd_Disable(void)
{
    M0P_LVD->CR_f.LVDEN = 0u;
}

/**
 * \brief
 *          获取LVD中断标志
 *
 * \param   无
 *
 * \retval  boolean_t  中断标志
 */
boolean_t Lvd_GetIrqStat(void)
{
    return M0P_LVD->IFR_f.INTF;

}

/**
 * \brief
 *          清除LVD中断标志
 *
 * \param   无
 *
 * \retval  无
 */
void Lvd_ClearIrq(void)
{
    M0P_LVD->IFR_f.INTF = 0u;
}


//@} // LvdGroup

/* ========================================================================== */
/*  pca.c                                                                     */
/* ========================================================================== */

/******************************************************************************/
/** \file pca.c
 **
 ** pca driver API.
 ** @link pcnt Group Some description @endlink
 **
 **   - 2019-04-09       First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup PCNTGroup
 ******************************************************************************/
//@{

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

/**
******************************************************************************
    ** \brief  获取中断源的标志位
    ** @param  IT_Src : 中断源标志位
    ** \retval FALSE 或TRUE
    **
******************************************************************************/
boolean_t Pca_GetItStatus(en_pca_ccficlr_t It_Src)
{
    return (((M0P_PCA->CCON)>>It_Src) & 1) > 0? TRUE : FALSE;
}

/**
******************************************************************************
    ** \brief  清除中断源的标志位
    ** @param  IT_Src : 中断源标志位
    ** \retval 无
    **
******************************************************************************/
void Pca_ClrItStatus(en_pca_ccficlr_t It_Src)
{
    M0P_PCA->ICLR &= ~(uint32_t)(1<<It_Src);
}

/**
******************************************************************************
    ** \brief  PCA 计数器运行控制   PCA_CCON CR控制位
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Pca_StartPca(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CCON)), 6, NewStatus);
}

/**
******************************************************************************
    ** \brief  PCA 空闲模式IDLE下，PCA是否停止工作设置
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Pca_SetCidl(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CMOD)), 7, NewStatus);
}

/**
******************************************************************************
    ** \brief  PCA 模块4的看门狗使能控制
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Pca_Set4Wdte(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CMOD)), 6, NewStatus);
}

/**
******************************************************************************
    ** \brief  PCA 计数器中断控制PCA_CMOD中CFIE，对应的控制中断位PCA_CCON中的CF与PCA_ICLR中的CF
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Pca_ConfPcaIt(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CMOD)), 0, NewStatus);
}

/**
******************************************************************************
    ** \brief  PCA 比较捕获中断使能控制  PCA_CCAPMx的CCIE
    ** @param  Modulex : pca_module0~4
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Pca_ConfModulexIt(en_pca_module_t Modulex, boolean_t NewStatus)
{
    switch(Modulex)
    {
        case PcaModule0:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM0)), 0, NewStatus);
            break;
        case PcaModule1:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM1)), 0, NewStatus);
            break;
        case PcaModule2:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM2)), 0, NewStatus);
            break;
        case PcaModule3:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM3)), 0, NewStatus);
            break;
        case PcaModule4:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM4)), 0, NewStatus);
            break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  PCA 模块0的初始化
    ** @param  InitStruct : PCA初始化配置的结构体
    ** \retval 无
    **
******************************************************************************/
void Pca_M0Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM0_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM0_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM0_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM0_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM0_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM0_f.PWM  = InitStruct->pca_pwm;

    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP0L_f.CCAP0 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP0H_f.CCAP0 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP0_f.CCAP0 = InitStruct->pca_ccap;
    }

}

/**
******************************************************************************
    ** \brief  PCA 模块1的初始化
    ** @param  InitStruct : PCA初始化配置的结构体
    ** \retval 无
    **
******************************************************************************/
void Pca_M1Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM1_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM1_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM1_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM1_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM1_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM1_f.PWM  = InitStruct->pca_pwm;

    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP1L_f.CCAP1 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP1H_f.CCAP1 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP1_f.CCAP1 = InitStruct->pca_ccap;
    }

}

/**
******************************************************************************
    ** \brief  PCA 模块2的初始化
    ** @param  InitStruct : PCA初始化配置的结构体
    ** \retval 无
    **
******************************************************************************/
void Pca_M2Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM2_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM2_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM2_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM2_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM2_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM2_f.PWM  = InitStruct->pca_pwm;

    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP2L_f.CCAP2 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP2H_f.CCAP2 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP2_f.CCAP2 = InitStruct->pca_ccap;
    }

}

/**
******************************************************************************
    ** \brief  PCA 模块3的初始化
    ** @param  InitStruct : PCA初始化配置的结构体
    ** \retval 无
    **
******************************************************************************/
void Pca_M3Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM3_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM3_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM3_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM3_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM3_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM3_f.PWM  = InitStruct->pca_pwm;

    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP3L_f.CCAP3 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP3H_f.CCAP3 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP3_f.CCAP3 = InitStruct->pca_ccap;
    }

}

/**
******************************************************************************
    ** \brief  PCA 模块4的初始化
    ** @param  InitStruct : PCA初始化配置的结构体
    ** \retval 无
    **
******************************************************************************/
void Pca_M4Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM4_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM4_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM4_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM4_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM4_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM4_f.PWM  = InitStruct->pca_pwm;

    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP4L_f.CCAP4 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP4H_f.CCAP4 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP4_f.CCAP4 = InitStruct->pca_ccap;
    }

}

/**
******************************************************************************
    ** \brief  PCA 读取CNT寄存器的数值
    ** @param  无
    ** \retval CNT的低半字值
    **
******************************************************************************/
uint16_t Pca_GetCnt(void)
{
    return (uint16_t)(M0P_PCA->CNT);
}

/**
******************************************************************************
    ** \brief  PCA 向CNT寄存器写入数值
    ** @param  cnt : 所要写入的数值
    ** \retval 无
    **
******************************************************************************/
void Pca_SetCnt(uint16_t cnt)
{
    if(GetBit((uint32_t)(&(M0P_PCA->CCON)), 6)==TRUE)
    {
        Pca_StartPca(FALSE);
        M0P_PCA->CNT_f.CNT = cnt;
        Pca_StartPca(TRUE);
    }
    else
    {
        M0P_PCA->CNT_f.CNT = cnt;
    }

}

/**
******************************************************************************
    ** \brief  PCA 返回指定通道比较高速输出标志寄存器的值
    ** @param  Modulex : 通道号x=0、1、2、3、4
    ** \retval TRUE 或 FALSE
    **
******************************************************************************/
boolean_t Pca_GetOut(en_pca_module_t Modulex)
{
    return GetBit((uint32_t)(&(M0P_PCA->CCAPO)), Modulex);
}

/**
******************************************************************************
    ** \brief  PCA 设置比较捕获16位寄存器CCAPx数值
    ** @param  Modulex : 通道号x=0、1、2、3、4
    ** @param  Value:  所要设置的值
    ** \retval 无
    **
******************************************************************************/
void Pca_SetCcap(en_pca_module_t Modulex, uint16_t Value)
{
    switch(Modulex)
    {
        case 0:
            M0P_PCA->CCAP0_f.CCAP0 = Value;
        break;
        case 1:
            M0P_PCA->CCAP1_f.CCAP1 = Value;
            break;
        case 2:
            M0P_PCA->CCAP2_f.CCAP2 = Value;
            break;
        case 3:
            M0P_PCA->CCAP3_f.CCAP3 = Value;
            break;
        case 4:
            M0P_PCA->CCAP4_f.CCAP4 = Value;
            break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  PCA 读取比较捕获16位寄存器CCAPx数值
    ** @param  Modulex : 通道号x=0、1、2、3、4
    ** \retval CCAPx的值，x=0、1、2、3、4
    **
******************************************************************************/
uint16_t Pca_GetCcap(en_pca_module_t Modulex)
{
    uint16_t tmp;
    switch(Modulex)
    {
        case 0:
            tmp = M0P_PCA->CCAP0_f.CCAP0;
        break;
        case 1:
            tmp = M0P_PCA->CCAP1_f.CCAP1;
            break;
        case 2:
            tmp = M0P_PCA->CCAP2_f.CCAP2;
            break;
        case 3:
            tmp = M0P_PCA->CCAP3_f.CCAP3;
            break;
        case 4:
            tmp = M0P_PCA->CCAP4_f.CCAP4;
            break;
        default:
            break;
    }
    return tmp;
}


/**
******************************************************************************
    ** \brief  PCA 设置比较捕获寄存器的高8位和低8位
    ** @param  Modulex : 通道号x=0、1、2、3、4
    ** @param  ValueH : 要写入高8位的数值
    ** @param  ValueL : 要写入低8位的数值
    ** \retval 无
    **
******************************************************************************/
void Pca_SetCcapHL(en_pca_module_t Modulex, uint8_t ValueH, uint8_t ValueL)
{
    switch(Modulex)
    {
        case 0:
            M0P_PCA->CCAP0H_f.CCAP0 = ValueH;
            M0P_PCA->CCAP0L_f.CCAP0 = ValueL;
            break;
        case 1:
            M0P_PCA->CCAP1H_f.CCAP1 = ValueH;
            M0P_PCA->CCAP1L_f.CCAP1 = ValueL;
            break;
        case 2:
            M0P_PCA->CCAP2H_f.CCAP2 = ValueH;
            M0P_PCA->CCAP2L_f.CCAP2 = ValueL;
            break;
        case 3:
            M0P_PCA->CCAP3H_f.CCAP3 = ValueH;
            M0P_PCA->CCAP3L_f.CCAP3 = ValueL;
            break;
        case 4:
            M0P_PCA->CCAP4H_f.CCAP4 = ValueH;
            M0P_PCA->CCAP4L_f.CCAP4 = ValueL;
            break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  PCA 读取比较捕获寄存器的高8位和低8位
    ** @param  Modulex : 通道号x=0、1、2、3、4
    ** @param  ValueH : CCAPx高8位的数值
    ** @param  ValueL : CCAPx低8位的数值
    ** \retval 无
    **
******************************************************************************/
void Pca_GetCcapHL(en_pca_module_t Modulex, uint8_t *ValueH, uint8_t *ValueL)
{
    switch(Modulex)
    {
        case 0:
            *ValueH = M0P_PCA->CCAP0H_f.CCAP0;
            *ValueL = M0P_PCA->CCAP0L_f.CCAP0;
            break;
        case 1:
            *ValueH = M0P_PCA->CCAP1H_f.CCAP1;
            *ValueL = M0P_PCA->CCAP1L_f.CCAP1;
            break;
        case 2:
            *ValueH = M0P_PCA->CCAP2H_f.CCAP2;
            *ValueL = M0P_PCA->CCAP2L_f.CCAP2;
            break;
        case 3:
            *ValueH = M0P_PCA->CCAP3H_f.CCAP3;
            *ValueL = M0P_PCA->CCAP3L_f.CCAP3;
            break;
        case 4:
            *ValueH = M0P_PCA->CCAP4H_f.CCAP4;
            *ValueL = M0P_PCA->CCAP4L_f.CCAP4;
            break;
        default:
            break;
    }
}

/* ========================================================================== */
/*  ram.c                                                                     */
/* ========================================================================== */


/** \file ram.c
 **
 ** Common API of ram.
 ** @link RamGroup Some description @endlink
 **
 **   - 2018-05-08
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup ramGroup
 ******************************************************************************/
//@{

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
 *****************************************************************************
 ** \brief Ram奇偶校验出错地址获取
 **
 **
 ** \retval ERROR ADDRESS
 *****************************************************************************/
uint32_t Ram_ErrAddrGet(void)
{
    return M0P_RAM->ERRADDR;
}

/**
 *****************************************************************************
 ** \brief Ram中断标志获取
 **
 **
 ** \retval TRUE or FALSE
 *****************************************************************************/
boolean_t Ram_GetIntFlag(void)
{
    if(M0P_RAM->IFR & 0x1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 *****************************************************************************
 ** \brief Ram中断标志清除
 **
 **
 ** \retval Null
 *****************************************************************************/
void Ram_ClearIntFlag(void)
{
    M0P_RAM->ICLR = 0u;
}

/**
 *****************************************************************************
 ** \brief Ram中断使能
 **
 ** \retval Null
 *****************************************************************************/
void Ram_EnableIrq (void)
{
    M0P_RAM->CR |= 0x2u;
}

/**
 *****************************************************************************
 ** \brief ram中断禁止
 **
 ** \retval Null
 *****************************************************************************/
void Ram_DisableIrq(void)
{
    M0P_RAM->CR &= 0x1;
}


//@} // RamGroup

/* ========================================================================== */
/*  reset.c                                                                   */
/* ========================================================================== */


/** \file reset.c
 **
 ** Common API of reset.
 ** @link resetGroup Some description @endlink
 **
 **   - 2017-05-04
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 *******************************************************************************
 ** \addtogroup ResetGroup
 ******************************************************************************/
//@{

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
 *******************************************************************************
 ** \brief 获取复位源类型.
 **
 ** \param [out]  enRstFlg  @ref en_reset_flag_t
 **
 ** \retval  TRUE or FALSE
 ******************************************************************************/
boolean_t Reset_GetFlag(en_reset_flag_t enRstFlg)
{
    if(M0P_RESET->RESET_FLAG&enRstFlg)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 *******************************************************************************
 ** \brief 清除复位源类型.
 **
 ** \param [in]  pstcFlag  @ref en_reset_flag_t
 **
 ** \retval  Null
 ******************************************************************************/
void Reset_ClearFlag(en_reset_flag_t enRstFlg)
{
    M0P_RESET->RESET_FLAG &= ~(uint32_t)enRstFlg;
}

/**
 *******************************************************************************
 ** \brief 清除所有复位源类型.
 **
 ** \param Null
 **
 ** \retval  Null
 ******************************************************************************/
void Reset_ClearFlagAll(void)
{
    M0P_RESET->RESET_FLAG = 0;
}

/**
 *******************************************************************************
 ** \brief 所有模块进行一次复位.
 **
 **
 ** \retval  Null
 ******************************************************************************/
void Reset_RstPeripheralAll(void)
{
    M0P_RESET->PERI_RESET = 0u;
    M0P_RESET->PERI_RESET = 0xFFFFFFFFu;
}

/**
 *******************************************************************************
 ** \brief 对外设源模块进行一次复位.
 **
 ** \param [in]  enPeri  @ref en_reset_peripheral_t
 **
 ** \retval  Null
 ******************************************************************************/
void Reset_RstPeripheral(en_reset_peripheral_t enPeri)
{
    M0P_RESET->PERI_RESET &= ~(uint32_t)enPeri;
    M0P_RESET->PERI_RESET |= (uint32_t)enPeri;
}



//@} // ResetGroup

/* ========================================================================== */
/*  spi.c                                                                     */
/* ========================================================================== */

/*****************************************************************************/
/** \file spi.c
 **
 ** SPI driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-05-17  1.0  Devi First version for Device Driver Library of
 **                      Module.
 **
 *****************************************************************************/

/******************************************************************************
 * Include files
 *****************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup SpiGroup
 *****************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 *****************************************************************************/

#define IS_VALID_STAT(x)            (   SpiIf == (x)||\
                                        SpiWcol == (x)||\
                                        SpiSserr == (x)||\
                                        SpiMdf == (x) )


/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  SPI 请求状态获取
 **
 ** \param [in]SPIx 通道， enStatus 获取请求
 **
 ** \retval 请求状态
 **
 ******************************************************************************/
boolean_t Spi_GetStatus(M0P_SPI_TypeDef* SPIx, en_spi_status_t enStatus)
{
    ASSERT(IS_VALID_STAT(enStatus));

    if(SPIx->STAT&enStatus)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}


/**
 ******************************************************************************
 ** \brief  SPI 总体初始化函数
 **
 ** \param [in] SPIx 通道
 ** \param [in] pstcSpiCfg 初始化结构
 **
 ** \retval Ok初始化成功
 ** \retval ErrorInvalidParameter 初始化错误
 ******************************************************************************/
en_result_t Spi_Init(M0P_SPI_TypeDef* SPIx, stc_spi_cfg_t *pstcSpiCfg)
{
    ASSERT(NULL != pstcSpiCfg);

    SPIx->CR = 0;
    SPIx->CR =  (uint32_t)pstcSpiCfg->enSpiMode |
                (uint32_t)pstcSpiCfg->enPclkDiv |
                (uint32_t)pstcSpiCfg->enCPOL    |
                (uint32_t)pstcSpiCfg->enCPHA    |
                (uint32_t)0x40;

    SPIx->STAT = 0x00;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 配置主发送的电平
 **
 ** \param [in] SPIx 通道选择，bFlag高低电平
 **
 ** \retval 无
 **
 ******************************************************************************/
void Spi_SetCS(M0P_SPI_TypeDef* SPIx, boolean_t bFlag)
{
    SPIx->SSN = bFlag;
}
/**
 ******************************************************************************
 ** \brief  SPI 发送一字节函数
 **
 ** \param [in] SPIx 通道选择，u8Data发送字节
 **
 ** \retval Ok发送成功
 **
 ******************************************************************************/
en_result_t Spi_SendData(M0P_SPI_TypeDef* SPIx, uint8_t u8Data)
{
    SPIx->DATA = u8Data;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 接收一字节函数
 **
 ** \param [in] SPIx接收通道
 **
 ** \retval 接收一字节数据
 **
 ******************************************************************************/
uint8_t Spi_ReceiveData(M0P_SPI_TypeDef* SPIx)
{
    return SPIx->DATA;
}

//@} // SpiGroup

/* ========================================================================== */
/*  sysctrl.c                                                                 */
/* ========================================================================== */


/** \file sysctrl.c
 **
 ** Common API of sysctrl.
 ** @link SysctrlGroup Some description @endlink
 **
 **   - 2018-04-22 Lux
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 *******************************************************************************
 ** \addtogroup SysctrlGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CLK_TIMEOUT             (1000000u)

#define IS_VALID_SRC(x)         (   ClkRCH == (x)||\
                                    ClkXTH == (x)||\
                                    ClkRCL == (x)||\
                                    ClkXTL == (x) )


#define IS_VALID_FUNC(x)        (   ClkFuncWkupRCH == (x)||\
                                    ClkFuncXTHEn == (x)||\
                                    ClkFuncXTLEn == (x)||\
                                    ClkFuncXTLAWSON == (x)||\
                                    ClkFuncFaultEn == (x)||\
                                    ClkFuncRtcLPWEn == (x)||\
                                    ClkFuncLockUpEn == (x)||\
                                    ClkFuncRstPinIOEn == (x)||\
                                    ClkFuncSwdPinIOEn == (x) )

#define RC_TRIM_BASE_ADDR           ((volatile uint16_t*) (0x00100C00ul))
#define RCH_CR_TRIM_24M_VAL         (*((volatile uint16_t*) (0x00100C00ul)))
#define RCH_CR_TRIM_22_12M_VAL      (*((volatile uint16_t*) (0x00100C02ul)))
#define RCH_CR_TRIM_16M_VAL         (*((volatile uint16_t*) (0x00100C04ul)))
#define RCH_CR_TRIM_8M_VAL          (*((volatile uint16_t*) (0x00100C06ul)))
#define RCH_CR_TRIM_4M_VAL          (*((volatile uint16_t*) (0x00100C08ul)))

#define RCL_CR_TRIM_38400_VAL       (*((volatile uint16_t*) (0x00100C20ul)))
#define RCL_CR_TRIM_32768_VAL       (*((volatile uint16_t*) (0x00100C22ul)))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern uint32_t SystemCoreClock;
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
 *******************************************************************************
 ** \brief SYSCTRL0\SYSCTRL1寄存器操作解锁
 **
 ** \retval None
 ******************************************************************************/
static void _SysctrlUnlock(void)
{
    M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
    M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
}

/**
 *******************************************************************************
 ** \brief 系统时钟源使能
 ** \param [in]  enSource   目标时钟源
 ** \param [in]  bFlag      使能1-开/0-关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;

    _SysctrlUnlock();
    bFlag = !!bFlag;

    u32Temp = M0P_SYSCTRL->PERI_CLKEN;
    switch (enSource)
    {
        case SysctrlClkRCH:
            M0P_SYSCTRL->SYSCTRL0_f.RCH_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->RCH_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlClkXTH:
            M0P_SYSCTRL->PERI_CLKEN_f.GPIO = TRUE;
            M0P_GPIO->P0ADS |= 0x06u;
            M0P_SYSCTRL->SYSCTRL0_f.XTH_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->XTH_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlClkRCL:
            M0P_SYSCTRL->SYSCTRL0_f.RCL_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->RCL_CR_f.STABLE))
            {
                ;
            }
            break;

        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    M0P_SYSCTRL->PERI_CLKEN = u32Temp;

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部高速晶振驱动配置
 ** \param [in]  enFreq     外部高速晶振频率范围选择
 ** \param [in]  enDriver   外部高速晶振驱动能力选择
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    M0P_SYSCTRL->XTH_CR_f.DRIVER   = enDriver;

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部高速时钟稳定周期配置
 ** \param [in]  enCycle     外部高速时钟稳定周期设置
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->XTH_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 内部低速时钟稳定周期配置
 ** \param [in]  enCycle     内部低速时钟稳定周期设置
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->RCL_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 时钟源切换，该函数执行后会开启新时钟源
 ** \note  选择时钟源之前，需根据需要配置目标时钟源的频率/驱动参数/使能时钟源等
 ** \param [in]  enSource   新时钟源
 **
 ** \retval      Ok         设定成功
 **              其他       设定失败
 ******************************************************************************/
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource)
{
    en_result_t enRet = Ok;

    en_sysctrl_clk_source_t ClkNew = enSource;

    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.CLKSW = ClkNew;

    //更新Core时钟（HCLK）
    SystemCoreClockUpdate();

    return enRet;
}

/**
 *******************************************************************************
 ** \brief   获得系统时钟（HCLK）频率值
 ** \retval  uint32_t         HCLK频率值
 **
 ******************************************************************************/
uint32_t Sysctrl_GetHClkFreq(void)
{
    uint32_t u32Val = 0;
    const uint32_t u32hcr_tbl[] = { 4000000, 8000000, 16000000, 22120000, 24000000};
    const uint16_t u32lcr_tbl[] = { 32768, 38400};
    en_sysctrl_clk_source_t enSrc;
    uint16_t u16Trim[5] = {0};
    u16Trim[4] = RCH_CR_TRIM_24M_VAL;
    u16Trim[3] = RCH_CR_TRIM_22_12M_VAL;
    u16Trim[2] = RCH_CR_TRIM_16M_VAL;
    u16Trim[1] = RCH_CR_TRIM_8M_VAL;
    u16Trim[0] = RCL_CR_TRIM_38400_VAL;

    //获取当前系统时钟
    enSrc = (en_sysctrl_clk_source_t)(M0P_SYSCTRL->SYSCTRL0_f.CLKSW);

    switch (enSrc)
    {
        case SysctrlClkRCH:
            {

                if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[4]))
                {
                    u32Val = u32hcr_tbl[4];
                }
                else if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[3]))
                {
                    u32Val = u32hcr_tbl[3];
                }
                else if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[2]))
                {
                    u32Val = u32hcr_tbl[2];
                }
                else if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[1]))
                {
                    u32Val = u32hcr_tbl[1];
                }
                else
                {
                    u32Val = u32hcr_tbl[0];
                }
            }
            break;
        case SysctrlClkXTH:
            u32Val = SYSTEM_XTH;
            break;
        case SysctrlClkRCL:
            {
                if(u16Trim[0] == (M0P_SYSCTRL->RCL_CR_f.TRIM))
                {
                    u32Val = u32lcr_tbl[1];
                }
                else
                {
                    u32Val = u32lcr_tbl[0];
                }
            }
            break;
        default:
            u32Val = 0u;
            break;
    }

    u32Val = (u32Val >> M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS);

    return u32Val;
}

/**
 *******************************************************************************
 ** \brief 获得外设时钟（PCLK）频率值
 ** \retval uint32_t   PCLK频率值(Hz)
 **
 ******************************************************************************/
uint32_t Sysctrl_GetPClkFreq(void)
{
    uint32_t u32Val = 0;

    u32Val = Sysctrl_GetHClkFreq();
    u32Val = (u32Val >> (M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS));

    return u32Val;
}


/**
 *******************************************************************************
 ** \brief 时钟初始化函数
 ** \param [in]  pstcCfg    初始化配置参数
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_cfg_t *pstcCfg)
{
    en_result_t enRet = Ok;

    //系统时钟参数配置
    switch(pstcCfg->enClkSrc)
    {
        case SysctrlClkRCH:

            break;
        case SysctrlClkXTH:
            Sysctrl_XTHDriverCfg(SysctrlXtalDriver3);
            Sysctrl_SetXTHStableTime(SysctrlXthStableCycle16384);
            break;
        case SysctrlClkRCL:
            Sysctrl_SetRCLStableTime(SysctrlRclStableCycle256);
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    //时钟源使能
    Sysctrl_ClkSourceEnable(pstcCfg->enClkSrc, TRUE);

    //时钟源切换
    Sysctrl_SysClkSwitch(pstcCfg->enClkSrc);

    //时钟分频设置
    Sysctrl_SetHCLKDiv(pstcCfg->enHClkDiv);
    Sysctrl_SetPCLKDiv(pstcCfg->enPClkDiv);

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 时钟去初始化函数
 ** \param [in]
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_ClkDeInit(void)
{
    en_result_t enRet = Ok;

    //配置RCH为内部4Hz
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);

    //时钟源使能
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);

    //时钟源切换
    Sysctrl_SysClkSwitch(SysctrlClkRCH);

    //其它时钟源使能关闭
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, FALSE);

    //时钟分频设置
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 内部高速时钟频率TRIM值加载
 ** \param [in]  enRCHFreq  设定的RCH目标频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败或时钟未稳定
 ******************************************************************************/
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq)
{
    //加载RCH Trim值
    M0P_SYSCTRL->RCH_CR_f.TRIM = *(RC_TRIM_BASE_ADDR + enRCHFreq);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief 外部高速时钟频率范围设定
 ** \param [in]  enXTHFreq  设定的频率值
 ** \retval      Ok         设定成功
 **              其他       设定失败或时钟未稳定
 ******************************************************************************/
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq)
{
    en_result_t enRet = Ok;

    M0P_SYSCTRL->XTH_CR_f.XTH_FSEL = enXTHFreq;

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 内部低速时钟频率TRIM值加载
 ** \param [in]  enRCLFreq  设定的RCL目标频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq)
{
    M0P_SYSCTRL->RCL_CR_f.TRIM = *(RC_TRIM_BASE_ADDR + enRCLFreq);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief 系统时钟（HCLK）分频设定
 ** \param [in]  enHCLKDiv  分频设定值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv)
{
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS = enHCLKDiv;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief 外设时钟（PCLK）分频设定
 ** \param [in]  enPCLKDiv  分频设定值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv)
{
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS = enPCLKDiv;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief 设置外设时钟门控开关
 ** \param [in]  enPeripheral   目标外设
 ** \param [in]  bFlag          使能开关
 ** \retval      Ok             设定成功
 **             其他            设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag)
{

        SetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN)), enPeripheral, bFlag);


    return Ok;
}

/**
 *******************************************************************************
 ** \brief 获得外设时钟门控开关状态
 ** \param [in]  enPeripheral   目标外设
 ** \retval      TRUE           开
 **              FALSE          关
 ******************************************************************************/
boolean_t Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral)
{

        return GetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN)), enPeripheral);


}

/**
 *******************************************************************************
 ** \brief 系统功能设定
 ** \param [in]  enFunc     系统功能枚举类型
 ** \param [in]  bFlag      1-开/0-关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag)
{
    _SysctrlUnlock();
    SetBit((uint32_t)(&(M0P_SYSCTRL->SYSCTRL1)), enFunc, bFlag);

    return Ok;
}

//@} // SysctrlGroup

/* ========================================================================== */
/*  trim.c                                                                    */
/* ========================================================================== */


/** \file trim.c
 **
 ** Common API of trim.
 ** @link trimGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 *******************************************************************************
 ** \addtogroup TrimGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#define IS_VALID_TRIMINT(x)             (TrimStop     == (x) ||\
                                         TrimCalCntOf == (x) ||\
                                         TrimXTLFault == (x) ||\
                                         TrimXTHFault == (x))


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
 *****************************************************************************
 ** \brief Trim中断标志获取
 **
 **
 ** \param [in]  enIntType           中断类型（RefStop、CalCntOf、XTAL32KFault、XTAL32MFault）
 **
 ** \retval TRUE or FALSE
 *****************************************************************************/
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType)
{
    ASSERT(IS_VALID_TRIMINT(enIntType));

    if(M0P_CLK_TRIM->IFR&enIntType)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/**
 *****************************************************************************
 ** \brief Trim中断标志清除
 **
 **
 ** \param [in]  enIntType           中断类型（RefStop、CalCntOf、XTAL32KFault、XTAL32MFault）
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType)
{
    en_result_t enResult = Error;

    ASSERT(IS_VALID_TRIMINT(enIntType));

    M0P_CLK_TRIM->ICLR &= ~(uint32_t)enIntType;

    return enResult;
}



/**
 *****************************************************************************
 ** \brief Trim中断使能
 **
 **
 **
 ** \retval Null
 *****************************************************************************/
void Trim_EnableIrq (void)
{
    M0P_CLK_TRIM->CR_f.IE = TRUE;
}

/**
 *****************************************************************************
 ** \brief Trim中断禁止
 **
 **
 **
 **
 ** \retval Ok or Error
 *****************************************************************************/
void Trim_DisableIrq(void)
{
    M0P_CLK_TRIM->CR_f.IE = FALSE;
}

/**
 *****************************************************************************
 ** \brief Trim初始化配置
 **
 **
 ** \param [in]  pstcCfg           Trim配置结构体指针
 **
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Trim_Init(stc_trim_cfg_t* pstcCfg)
{
    en_result_t enResult = Error;

    M0P_CLK_TRIM->CR = 0;

    M0P_CLK_TRIM->CR = (uint32_t)pstcCfg->enCALCLK |
                       (uint32_t)pstcCfg->enREFCLK |
                       (uint32_t)pstcCfg->enMON;

    M0P_CLK_TRIM->REFCON = pstcCfg->u32RefCon;
    M0P_CLK_TRIM->CALCON = pstcCfg->u32CalCon;

    enResult = Ok;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Trim校准/监测启动运行
 **
 **
 **
 ** \retval Null
 *****************************************************************************/
void Trim_Run(void)
{
    M0P_CLK_TRIM->CR_f.TRIM_START = TRUE;
}

/**
 *****************************************************************************
 ** \brief Trim校准/监测停止
 **
 **
 **
 **
 ** \retval Null
 *****************************************************************************/
void Trim_Stop(void)
{
    M0P_CLK_TRIM->CR_f.TRIM_START = FALSE;
}

/**
 *****************************************************************************
 ** \brief Trim参考计数器计数值获取
 **
 **
 ** \retval u32Data                参考计数器计数值
 *****************************************************************************/
uint32_t Trim_RefCntGet(void)
{
    return (uint32_t)M0P_CLK_TRIM->REFCNT;
}

/**
 *****************************************************************************
 ** \brief Trim校准计数器计数值获取
 **
 **
 **
 **
 ** \retval u32Data                校准计数器计数值
 *****************************************************************************/
uint32_t Trim_CalCntGet(void)
{
    return (uint32_t)M0P_CLK_TRIM->CALCNT;
}

//@} // TrimGroup

/* ========================================================================== */
/*  uart.c                                                                    */
/* ========================================================================== */

/******************************************************************************/
/** \file uart.c
 **
 ** UART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
/**
 ******************************************************************************
 ** \addtogroup UartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

#define IS_VALID_CH(x)          ((UARTCH0 == (x)) ||\
                                 (UARTCH1 == (x)))

#define IS_VALID_IRQSEL(x)      ((UartTxIrq == (x)) ||\
                                 (UartRxIrq == (x)))

#define IS_VALID_MODE(x)        ((UartMode0==(x))||\
                                 (UartMode1==(x))||\
                                 (UartMode2==(x))||\
                                 (UartMode3==(x)))

#define IS_VALID_STATUS(x)      ((UartRFRAMEError == (x))||\
                                 (UartRxFull == (x))||\
                                 (UartTxEmpty == (x)))
/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  UART通信中断使能函数设置
 **
 ** \param [in] UARTx通道号，enIrqSel发送or接收中断使能
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, TRUE);

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通信中断禁止函数设置
 **
 ** \param [in] UARTx通道号，enIrqSel发送or接收中断禁止
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, FALSE);

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道多主机模式配置
 **
 ** \param [in] UARTx通道号，stcMultiCfg多主机模式结构
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx, stc_uart_multimode_t* pstcMultiCfg)
{
    if(NULL != pstcMultiCfg)
    {
        UARTx->SCON_f.SM2 = TRUE;
        UARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        UARTx->SADEN = pstcMultiCfg->u8SaddEn;

    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 ******************************************************************************
 ** \brief 计算接收字节奇偶校验是否正确
 **
 ** \param u8Idx通道，enCheck奇偶校验方式，u8Recv校验数据
 **
 ** \retval Error或者成功Ok
 ******************************************************************************/
en_result_t Uart_CheckEvenOrOdd(M0P_UART_TypeDef* UARTx, en_uart_check_t enCheck, uint8_t u8Recv)
{
	uint8_t cnt=0,i;

	for(i=0;i<8;i++)
	{
		if((u8Recv&0x80)==0x80)
		{
			cnt++;
		}
		u8Recv<<=1;
	}

	if(enCheck == UartEven)
	{
		if(cnt%2!=0)
		{
			if(UARTx->SCON_f.RB8 != 1)
			{
				return Error;
			}
		}
		else
		{
			if(UARTx->SCON_f.RB8 != 0)
			{
				return Error;
			}
		}
	}
	else
	{
		if(cnt%2!=0)
		{
			if(UARTx->SCON_f.RB8 != 0)
			{
				return Error;
			}
		}
		else
		{
			if(UARTx->SCON_f.RB8 != 1)
			{
				return Error;
			}
		}
	}
	return Ok;
}

/**
 ******************************************************************************
 ** \brief 获取RB8数值
 **
 ** \param [in] UARTx通道号
 **
 ** \retval RB8
 ******************************************************************************/
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SCON_f.RB8);
}

/**
 ******************************************************************************
 ** \brief  UART通道多机模式发送数据/地址帧配置TB8
 **
 ** \param [in] UARTx 通道号
 ** \param [in] TRUE-TB8为地址帧标志；FALSE-TB8为数据帧标志；
 **
 ** \retval Null
 ******************************************************************************/
en_result_t Uart_SetTb8(M0P_UART_TypeDef* UARTx, en_uart_check_t enCheck, uint8_t u8Data)
{
	uint8_t cnt=0,i;

	for(i=0;i<8;i++)
	{
		if((u8Data&0x80)==0x80)
		{
			cnt++;
		}
		u8Data<<=1;
	}
	if(enCheck == UartEven)
	{
		if(cnt%2!=0)
		{
			UARTx->SCON_f.TB8 = 1;
		}
		else
		{
			UARTx->SCON_f.TB8 = 0;
		}
	}
	else
	{
		if(cnt%2!=0)
		{
			UARTx->SCON_f.TB8 = 0;
		}
		else
		{
			UARTx->SCON_f.TB8 = 1;
		}
	}

	return Ok;

}

/**
 ******************************************************************************
 ** \brief  UART通道多主机模式从机地址配置函数
 **
 ** \param [in] UARTx通道号，addr地址
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetSaddr(M0P_UART_TypeDef* UARTx,uint8_t u8Addr)
{
    UARTx->SADDR = u8Addr;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道波特率配置
 **
 ** \param [in] u8Idx通道号，u32pclk时钟源，stcBaud波特率配置结构
 **
 ** \retval 定时器配置值
 ** \retval 0,获取值失败
 ******************************************************************************/
uint16_t Uart_SetBaudRate(M0P_UART_TypeDef* UARTx,stc_uart_baud_cfg_t* pstcBaud)
{
    uint16_t u16tmload=0;

    UARTx->SCON_f.DBAUD = pstcBaud->bDbaud;

    switch(pstcBaud->enMode)
    {
        case UartMode0:
        case UartMode2:
            break;
        case UartMode1:
        case UartMode3:
            u16tmload = 0x10000-((pstcBaud->u32Pclk*(pstcBaud->bDbaud+1))/(pstcBaud->u32Baud*32));//单双倍波特率，定时器配置
            break;
        default:
            break;
    }

    return u16tmload;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送或接收使能设置
 **
 ** \param [in] u8Idx通道号，enFunc发送或接收
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, TRUE);

    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送或接收等功能禁止设置
 **
 ** \param [in] UARTx通道号，enFunc功能
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, FALSE);

    return Ok;
}


/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] UARTx通道号
 **
 ** \retval 状态值
 ******************************************************************************/
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->ISR);
}

/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] UARTx通道号，enStatus获取哪个状态
 **
 ** \retval 状态值
 ******************************************************************************/
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus)
{
    boolean_t bStatus = FALSE;


    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(UARTx->ISR)), enStatus);

    return bStatus;
}

/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] UARTx通道号
 **
 ** \retval OK
 ** \retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx)
{
    UARTx->ICR = 0u;
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] UARTx通道号，enStatus清除哪个状态
 **
 ** \retval OK
 ** \retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(UARTx->ICR)), enStatus, FALSE);

    return Ok;
}


/**
 ******************************************************************************
 ** \brief  UART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 **
 ** \param [in] UARTx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 ** \retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
    UARTx->SBUF_f.SBUF = u8Data;
    while(FALSE == Uart_GetStatus(UARTx,UartTC))
    {}
    Uart_ClrStatus(UARTx,UartTC);
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 **
 ** \param [in] UARTx通道号，Data发送数据
 **
 ** \retval @ref en_result_t
 ******************************************************************************/
en_result_t Uart_SendDataPollTimeOut(M0P_UART_TypeDef* UARTx, uint8_t u8Data, uint32_t u32TimeOut)
{
    uint32_t u32Cnt = 0;

    UARTx->SBUF_f.SBUF = u8Data;
    while(FALSE == Uart_GetStatus(UARTx,UartTC))
    {
        if(u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;
    }
    Uart_ClrStatus(UARTx,UartTC);
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道发送数据函数,中断方式调用此函数
 **
 ** \param [in] UARTx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 ** \retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
    UARTx->SBUF_f.SBUF = u8Data;

    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道接收数据函数
 **
 ** \param [in] UARTx通道号
 **
 ** \retval 接收数据
 ******************************************************************************/
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.SBUF);
}

/**
 ******************************************************************************
 ** \brief  UART通道初始化函数
 **
 ** \param [in] UARTx通道号，pstcCfg初始化结构体 @ref stc_uart_cfg_t
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg)
{
    UARTx->SCON_f.SM01 = pstcCfg->enRunMode;
    Uart_EnableFunc(UARTx,UartRenFunc);       ///<使能收发

    return Ok;
}
//@} // UartGroup

/* ========================================================================== */
/*  vc.c                                                                      */
/* ========================================================================== */

/******************************************************************************/
/** \file vc.c
 **
 ** voltage comparator driver API.
 ** @link VC Group Some description @endlink
 **
 **   - 2019-04-10   First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 ******************************************************************************
 ** \addtogroup VcGroup
 ******************************************************************************/
//@{

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
******************************************************************************
    ** \brief  配置VC中断触发方式
    **
    ** @param  Channelx : VcChannelx  x=0、1
    ** @param  enSel : VcIrqRise、VcIrqFall、VcIrqHigh
    ** \retval 无
    **
******************************************************************************/
void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType)
{
    stc_vc_vc0_cr_field_t *stcVcnCr;
        switch(Channelx)
        {
            case VcChannel0:
                stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC0_CR_f;
                break;
            case VcChannel1:
                stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC1_CR_f;
                break;

            default:
                break;
        }
    switch (ItType)
    {
        case VcIrqNone:
            stcVcnCr->RISING  = 0u;
            stcVcnCr->FALLING = 0u;
            stcVcnCr->LEVEL   = 0u;
            break;
        case VcIrqRise:
            stcVcnCr->RISING  = 1u;
            break;
        case VcIrqFall:
            stcVcnCr->FALLING = 1u;
            break;
        case VcIrqHigh:
            stcVcnCr->LEVEL   = 1u;
            break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  VC 中断使能与禁止
    **
    ** @param  Channelx : VcChannelx  x=0、1
    ** @param  NewStatus : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void  Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus)
{
    switch(Channelx)
    {
        case VcChannel0:
            SetBit((uint32_t)(&(M0P_VC->VC0_CR)), 15, NewStatus);
        break;
        case VcChannel1:
            SetBit((uint32_t)(&(M0P_VC->VC1_CR)), 15, NewStatus);
        break;
        default:
            break;
    }
}

/**
******************************************************************************
    ** \brief  VC 比较结果获取，包含中断标志位和滤波结果
    **
    ** @param  Result : 所要读取的结果
    ** \retval TRUE 或  FALSE
    **
******************************************************************************/
boolean_t Vc_GetItStatus(en_vc_ifr_t Result)
{
    boolean_t bFlag;
    bFlag = GetBit((uint32_t)(&(M0P_VC->IFR)), Result);
    return bFlag;
}

/**
******************************************************************************
    ** \brief  VC 清除中断标志位
    **
    ** @param  NewStatus : Vc0_Intf、Vc1_Intf、Vc2_Intf
    ** \retval 无
    **
******************************************************************************/
void Vc_ClearItStatus(en_vc_ifr_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_VC->IFR)), NewStatus, 0);
}

/**
******************************************************************************
    ** \brief  VC 配置DAC相关的内容  VC_CR中 VC_REF2P5_SEL VC_DIV_EN VC_DIV
    **
    ** @param  pstcDacCfg :
    ** \retval Ok 或 ErrorInvalidParameter
    **
******************************************************************************/
en_result_t Vc_DacInit(stc_vc_dac_cfg_t *pstcDacCfg)
{
    if (NULL == pstcDacCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_VC->CR_f.DIV_EN = pstcDacCfg->bDivEn;
    M0P_VC->CR_f.REF2P5_SEL = pstcDacCfg->enDivVref;

    if (pstcDacCfg->u8DivVal < 0x40)
    {
        M0P_VC->CR_f.DIV = pstcDacCfg->u8DivVal;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
******************************************************************************
    ** \brief  VC通道初始化
    **
    ** @param  pstcDacCfg :
    ** \retval 无
    **
******************************************************************************/
void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg)
{
    if (VcChannel0 == pstcChannelCfg->enVcChannel)
    {
        M0P_VC->CR_f.VC0_HYS_SEL = pstcChannelCfg->enVcCmpDly;
        M0P_VC->CR_f.VC0_BIAS_SEL = pstcChannelCfg->enVcBiasCurrent;
        M0P_VC->VC0_CR_f.DEBOUNCE_TIME = pstcChannelCfg->enVcFilterTime;
        M0P_VC->VC0_CR_f.P_SEL = pstcChannelCfg->enVcInPin_P;
        M0P_VC->VC0_CR_f.N_SEL = pstcChannelCfg->enVcInPin_N;
                M0P_VC->VC0_CR_f.FLTEN = pstcChannelCfg->bFlten;
        M0P_VC->VC0_OUT_CFG = 1<<pstcChannelCfg->enVcOutCfg;
    }
    else if (VcChannel1 == pstcChannelCfg->enVcChannel)
    {
        M0P_VC->CR_f.VC1_HYS_SEL = pstcChannelCfg->enVcCmpDly;
        M0P_VC->CR_f.VC1_BIAS_SEL = pstcChannelCfg->enVcBiasCurrent;
        M0P_VC->VC1_CR_f.DEBOUNCE_TIME = pstcChannelCfg->enVcFilterTime;
        M0P_VC->VC1_CR_f.P_SEL = pstcChannelCfg->enVcInPin_P;
        M0P_VC->VC1_CR_f.N_SEL = pstcChannelCfg->enVcInPin_N;
                M0P_VC->VC1_CR_f.FLTEN = pstcChannelCfg->bFlten;
        M0P_VC->VC1_OUT_CFG = 1<<pstcChannelCfg->enVcOutCfg;
    }
    else
    {
        ;
    }
}

/**
******************************************************************************
    ** \brief  VC 通道使能
    **
    ** \param  enChannel :  通道号VcChannel0 VcChannel1
    ** \param  NewStatus : TRUE FALSE
    ** \retval NewStatus : TRUE FALSE
    **
******************************************************************************/
void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus)
{
    switch(enChannel)
    {
        case VcChannel0:
            SetBit((uint32_t)(&(M0P_VC->VC0_CR)), 0, NewStatus);
            break;
        case VcChannel1:
            SetBit((uint32_t)(&(M0P_VC->VC1_CR)), 0, NewStatus);
            break;
        default:
            break;
    }
}

//@} // VcGroup

/* ========================================================================== */
/*  wdt.c                                                                     */
/* ========================================================================== */

/******************************************************************************/
/** \file wdt.c
 **
 ** WDT function driver API.
 ** @link WdtGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/**
 ******************************************************************************
 ** \defgroup WdtGroup
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  WDT溢出时间设置函数
 **
 ** \param [in] u8LoadValue 溢出时间
 **
 ** \retval 无
 **
 ******************************************************************************/
void Wdt_WriteWdtLoad(uint8_t u8LoadValue)
{
    M0P_WDT->CON_f.WOV = u8LoadValue;
}
/**
 ******************************************************************************
 ** \brief  WDT初始化函数
 **
 ** \param [in] enFunc @ref en_wdt_func_t
 ** \param [in] enTime @ref en_wdt_time_t
 **
 ** \retval Ok
 **
 ******************************************************************************/
en_result_t Wdt_Init(en_wdt_func_t enFunc, en_wdt_time_t enTime)
{
    en_result_t enRet = Error;

    Wdt_WriteWdtLoad(enTime);
    M0P_WDT->CON_f.WINT_EN = enFunc;
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief  WDT复位及启动函数
 **
 ** \param [in] 无
 **
 ** \retval 无
 **
 ******************************************************************************/
void Wdt_Start(void)
{
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
 ******************************************************************************
 ** \brief  WDT喂狗
 **
 ** \param [in] 无
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_Feed(void)
{
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
 ******************************************************************************
 ** \brief  WDT中断标志清除
 **
 ** \param [in] 无
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_IrqClr(void)
{
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
 ******************************************************************************
 ** \brief  WDT读取当前计数值函数
 **
 ** \param [in] 无
 **
 ** \retval 计数值
 **
 ******************************************************************************/
uint8_t Wdt_ReadWdtValue(void)
{
    uint8_t u8Count;

    u8Count = M0P_WDT->CON_f.WCNTL;

    return u8Count;
}
/**
 ******************************************************************************
 ** \brief  WDT读取当前运行状态
 **
 ** \param [in] 无
 **
 ** \retval 状态值
 **
 ******************************************************************************/
boolean_t Wdt_ReadwdtStatus(void)
{
    if(M0P_WDT->CON&0x10u)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 *******************************************************************************
 ** \brief WDT 中断状态标记获取
 **
 **
 ** \retval  中断状态
 ******************************************************************************/
boolean_t Wdt_GetIrqStatus(void)
{
    if(M0P_WDT->CON&0x80u)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


//@} // WdtGroup

/* ========================================================================== */
/*  interrupts_hc32f005.c (mcu/common)                                        */
/* ========================================================================== */

/******************************************************************************/
/** \file interrupts_hc32f005.c
 **
 ** Interrupt management
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-04-15  1.0  Lux     First version.
 **
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

/*******************************************************************************
 *                       IRQ WEAK DEFINE
 ******************************************************************************/
__WEAK void SysTick_IRQHandler(void);


__WEAK void Port0_IRQHandler(void);
__WEAK void Port1_IRQHandler(void);
__WEAK void Port2_IRQHandler(void);
__WEAK void Port3_IRQHandler(void);
__WEAK void Dmac_IRQHandler(void);
__WEAK void Tim3_IRQHandler(void);
__WEAK void Uart0_IRQHandler(void);
__WEAK void Uart1_IRQHandler(void);
__WEAK void Spi_IRQHandler(void);
__WEAK void I2c_IRQHandler(void);
__WEAK void Tim0_IRQHandler(void);
__WEAK void Tim1_IRQHandler(void);
__WEAK void Tim2_IRQHandler(void);
__WEAK void Tim4_IRQHandler(void);
__WEAK void Tim5_IRQHandler(void);
__WEAK void Tim6_IRQHandler(void);
__WEAK void Pca_IRQHandler(void);
__WEAK void Wdt_IRQHandler(void);
__WEAK void Adc_IRQHandler(void);
__WEAK void Dac_IRQHandler(void);
__WEAK void Pcnt_IRQHandler(void);
__WEAK void Vc0_IRQHandler(void);
__WEAK void Vc1_IRQHandler(void);
__WEAK void Lvd_IRQHandler(void);
__WEAK void Flash_IRQHandler(void);
__WEAK void Ram_IRQHandler(void);
__WEAK void ClkTrim_IRQHandler(void);

/**
 *******************************************************************************
 ** \brief NVIC 中断使能
 **
 ** \param [in]  enIrq          中断号枚举类型
 ** \param [in]  enLevel        中断优先级枚举类型
 ** \param [in]  bEn            中断开关
 ** \retval    Ok       设置成功
 **            其他值   设置失败
 ******************************************************************************/
void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn)
{
    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, enLevel);
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
 *******************************************************************************
 ** \brief NVIC hardware fault 中断实现
 **
 **
 ** \retval
 ******************************************************************************/
void HardFault_Handler(void)
{
    volatile int a = 0;

    while( 0 == a)
    {
        ;
    }

}


/**
 *******************************************************************************
 ** \brief NVIC SysTick 中断实现
 **
 ** \retval
 ******************************************************************************/
void SysTick_Handler(void)
{
   SysTick_IRQHandler();
}

/**
 *******************************************************************************
 ** \brief GPIO Port0 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void PORT0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORT0)
    Port0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief GPIO Port1 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void PORT1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORT1)
    Port1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief GPIO Port2 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void PORT2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORT2)
    Port2_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief GPIO Port3 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void PORT3_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORT3)
    Port3_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief DMAC  中断处理函数
 **
 ** \retval
 ******************************************************************************/
void DMAC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_DMAC)
    Dmac_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM3 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM3_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM3)
    Tim3_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief UART0 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void UART0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_UART0)
    Uart0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief UART1 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void UART1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_UART1)
    Uart1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief SPI 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void SPI_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI)
    Spi_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief I2C 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void I2C_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C)
    I2c_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM0 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM0)
    Tim0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM1 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM1)
    Tim1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM2 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM2)
    Tim2_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM4 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM4_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM4)
    Tim4_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM5 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM5_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM5)
    Tim5_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief TIM6 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void TIM6_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM6)
    Tim6_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief PCA 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void PCA_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PCA)
    Pca_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief WDT 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void WDT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_WDT)
    Wdt_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief ADC 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void ADC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ADC)
    Adc_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief PCNT 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void PCNT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PCNT)
    Pcnt_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief VC0 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void VC0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_VC0)
    Vc0_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief VC1 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void VC1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_VC1)
    Vc1_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief LVD 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void LVD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LVD)
    Lvd_IRQHandler();
#endif
}

/**
 *******************************************************************************
 ** \brief FLASH/RAM 中断处理函数
 **
 ** \retval
 ******************************************************************************/
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
 *******************************************************************************
 ** \brief CLKTRIM 中断处理函数
 **
 ** \retval
 ******************************************************************************/
void CLKTRIM_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_CLKTRIM)
    ClkTrim_IRQHandler();
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
__WEAK void Port0_IRQHandler(void) {}
__WEAK void Port1_IRQHandler(void) {}
__WEAK void Port2_IRQHandler(void) {}
__WEAK void Port3_IRQHandler(void) {}
__WEAK void Dmac_IRQHandler(void) {}
__WEAK void Tim3_IRQHandler(void) {}
__WEAK void Uart0_IRQHandler(void) {}
__WEAK void Uart1_IRQHandler(void) {}
__WEAK void Spi_IRQHandler(void) {}
__WEAK void I2c_IRQHandler(void) {}
__WEAK void Tim0_IRQHandler(void) {}
__WEAK void Tim1_IRQHandler(void) {}
__WEAK void Tim2_IRQHandler(void) {}
__WEAK void Tim4_IRQHandler(void) {}
__WEAK void Tim5_IRQHandler(void) {}
__WEAK void Tim6_IRQHandler(void) {}
__WEAK void Pca_IRQHandler(void) {}
__WEAK void Wdt_IRQHandler(void) {}
__WEAK void Adc_IRQHandler(void) {}
__WEAK void Dac_IRQHandler(void) {}
__WEAK void Pcnt_IRQHandler(void) {}
__WEAK void Vc0_IRQHandler(void) {}
__WEAK void Vc1_IRQHandler(void) {}
__WEAK void Lvd_IRQHandler(void) {}
__WEAK void Flash_IRQHandler(void) {}
__WEAK void Ram_IRQHandler(void) {}
__WEAK void ClkTrim_IRQHandler(void) {}
