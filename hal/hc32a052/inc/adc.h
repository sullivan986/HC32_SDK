/**
 *******************************************************************************
 * @file  adc.h
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library.
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

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_ADC ADC模块驱动库
 * @{
 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC全局类型定义
 * @{
 */

/**
 * @brief  ADC转换模式
 */
typedef enum
{
    AdcSglMode         = 0u,           /*!< 单输入通道单次转换模式 */
    AdcScanMode        = 1u,           /*!< 多输入通道顺序扫描单序列转换模式 */
    AdcScanContJqrMode = 2u,           /*!< 多输入通道顺序扫描连续转换/插队扫描转换模式 */
    AdcScanBreakMode   = 3u,           /*!< 多输入通道顺序扫描断续转换模式 */
}en_adc_mode_t;

/**
 * @brief  ADC时钟分频选择
 */
typedef enum
{
    AdcMskClkDiv1   = 7u<<1u,        /*!< PCLK */
    AdcMskClkDiv2   = 0u<<1u,        /*!< PCLK/2  */
    AdcMskClkDiv4   = 1u<<1u,        /*!< PCLK/4  */
    AdcMskClkDiv6   = 2u<<1u,        /*!< PCLK/6  */
    AdcMskClkDiv8   = 3u<<1u,        /*!< PCLK/8  */
    AdcMskClkDiv10  = 4u<<1u,        /*!< PCLK/10  */
    AdcMskClkDiv12  = 5u<<1u,        /*!< PCLK/12  */
    AdcMskClkDiv14  = 6u<<1u,        /*!< PCLK/14  */
} en_adc_clk_div_t;

/**
 * @brief  ADC参考电压
 */
typedef enum
{
    AdcMskRefVolSelInBgr1p5 = 0u<<9,        /*!< 内部参考电压1.5V (avcc>1.8V, SPS<=200kHz) */
    AdcMskRefVolSelInBgr2p5 = 1u<<9,        /*!< 内部参考电压2.5V (avcc>3V, SPS<=200kHz) */
    AdcMskRefVolSelExtern1  = 2u<<9,        /*!< 外部输入(max avcc, 注意电压avcc与采样率的关系) PB01 */
    AdcMskRefVolSelAVDD     = 3u<<9,        /*!< AVDD (注意电压avcc与采样率的关系) */
}en_adc_ref_vol_sel_t;

/**
 * @brief  ADC转换通道选择
 */
typedef enum
{
    AdcExInputCH0    =  0u,        /*!< 使用PA00 */
    AdcExInputCH1    =  1u,        /*!< 使用PA01 */
    AdcExInputCH2    =  2u,        /*!< 使用PA02 */
    AdcExInputCH3    =  3u,        /*!< 使用PA03 */
    AdcExInputCH4    =  4u,        /*!< 使用PA04 */
    AdcExInputCH5    =  5u,        /*!< 使用PA05 */
    AdcExInputCH6    =  6u,        /*!< 使用PA06 */
    AdcExInputCH7    =  7u,        /*!< 使用PA07 */
    AdcExInputCH8    =  8u,        /*!< 使用PB00 */
    AdcExInputCH9    =  9u,        /*!< 使用PB01 */
    AdcExInputCH10   =  10u,       /*!< 使用PB02 */
    AdcExInputCH11   =  11u,       /*!< 使用PB10 */
    AdcExInputCH12   =  12u,       /*!< 使用PB11 */
    AdcExInputCH13   =  13u,       /*!< 使用PB12 */
    AdcExInputCH14   =  14u,       /*!< 使用PB13 */
    AdcExInputCH15   =  15u,       /*!< 使用PB14 */
    AdcAVccdiv3Input =  16u,       /*!< 使用1/3 AVCC(必须使用输入增益) */
    AdcAiTsInput     =  17u,       /*!< 使用内置温度传感器BGR_TS(必须使用输入增益) */
}en_adc_samp_ch_sel_t;

/**
 * @brief  ADC输入信号放大器控制
 */
typedef enum
{
    AdcMskBufEnable  = 1u<<11,          /*!< 打开放大器BUF */
    AdcMskBufDisable = 0u,              /*!< 关闭放大器BUF */  
} en_adc_op_buf_t;

/**
 * @brief  ADC采样周期选择
 */
typedef enum
{
    AdcMskSampCycle4Clk  =  0u<<12,        /*!< 4个采样时钟 */
    AdcMskSampCycle6Clk  =  1u<<12,        /*!< 6个采样时钟 */
    AdcMskSampCycle9Clk  =  2u<<12,        /*!< 9个采样时钟 */
    AdcMskSampCycle10Clk =  3u<<12,        /*!< 10个采样时钟 */

}en_adc_samp_cycle_sel_t;

/**
 * @brief  ADC内部参考电压使能控制
 */
typedef enum
{
    AdcMskOvModeRefreshData  = 1u<<10u,         /*!< ADC过转换时，ADC_Result 覆盖上次数据，保留新的数据 */
    AdcMskOvModeKeepOldData  = 0u,              /*!< ADC过转换时，ADC_Result 保留上次数据，丢弃新的数据 */  
}en_adc_ov_mode_t;

/**
 * @brief  ADC模块触发源选择
 */
typedef enum
{
    AdcMskTrigNone       =  0u,            /*!< 无外设触发 */
    AdcMskTrigAtimer0    =  1u,            /*!< 选择Atimer0中断源，自动触发ADC采样 */
    AdcMskTrigTimer3     =  2u,            /*!< 选择Atimer3中断源，自动触发ADC采样 */
    AdcMskTrigGtimer0    =  3u,            /*!< 选择Gtimer0中断源，自动触发ADC采样 */
    AdcMskTrigGtimer1    =  4u,            /*!< 选择Gtimer1中断源，自动触发ADC采样 */
    AdcMskTrigAtimer2    =  5u,            /*!< 选择Atimer2中断源，自动触发ADC采样 */
    AdcMskTrigUart0      =  6u,            /*!< 选择uart0中断源，自动触发ADC采样 */
    AdcMskTrigUart1      =  7u,            /*!< 选择uart1中断源，自动触发ADC采样 */
    AdcMskTrigLpuart0    =  8u,            /*!< 选择lpuart0中断源，自动触发ADC采样 */
    AdcMskTrigLpuart1    =  9u,            /*!< 选择lpuart1中断源，自动触发ADC采样 */
    AdcMskTrigSPI0       =  10u,           /*!< 选择SPI0中断源，自动触发ADC采样 */
    AdcMskTrigSPI1       =  11u,           /*!< 选择SPI1中断源，自动触发ADC采样 */
    AdcMskTrigDMA        =  12u,           /*!< 选择DMA中断源，自动触发ADC采样 */
    AdcMskTrigVC0        =  13u,           /*!< 选择VC0中断源，自动触发ADC采样 */
    AdcMskTrigVC1        =  14u,           /*!< 选择VC1中断源，自动触发ADC采样 */
    AdcMskTrigLVD        =  15u,           /*!< 选择LVD中断源，自动触发ADC采样 */
    AdcMskTrigPA01       =  16u,           /*!< 选择PA01中断源，自动触发ADC采样 */
    AdcMskTrigPB01       =  17u,           /*!< 选择PB01中断源，自动触发ADC采样 */
    AdcMskTrigPA03       =  18u,           /*!< 选择PA03中断源，自动触发ADC采样 */
    AdcMskTrigPB03       =  19u,           /*!< 选择PB03中断源，自动触发ADC采样 */
    AdcMskTrigPA05       =  20u,           /*!< 选择PA05中断源，自动触发ADC采样 */
    AdcMskTrigPB05       =  21u,           /*!< 选择PB05中断源，自动触发ADC采样 */
    AdcMskTrigPA07       =  22u,           /*!< 选择PA07中断源，自动触发ADC采样 */
    AdcMskTrigPB07       =  23u,           /*!< 选择PB07中断源，自动触发ADC采样 */
    AdcMskTrigPA09       =  24u,           /*!< 选择PA09中断源，自动触发ADC采样 */
    AdcMskTrigPB09       =  25u,           /*!< 选择PB09中断源，自动触发ADC采样 */
    AdcMskTrigPA11       =  26u,           /*!< 选择PA11中断源，自动触发ADC采样 */
    AdcMskTrigPB11       =  27u,           /*!< 选择PB11中断源，自动触发ADC采样 */
    AdcMskTrigPA13       =  28u,           /*!< 选择PA13中断源，自动触发ADC采样 */
    AdcMskTrigPB13       =  29u,           /*!< 选择PB13中断源，自动触发ADC采样 */
    AdcMskTrigPA15       =  30u,           /*!< 选择PA15中断源，自动触发ADC采样 */
    AdcMskTrigPB15       =  31u,           /*!< 选择PB15中断源，自动触发ADC采样 */
}en_adc_trig_sel_t;

/**
 * @brief  ADC触发延时控制
 */
typedef enum
{
    AdcExtTrigDirect     =  0u,     /*!< 直接使用TRIG选择信号触发ADC */
    AdcExtTrigDelay      =  1u,     /*!< TRIG选择的触发信号触发GTIM，GTIM信号触发ADC */
}en_adc_trig_delay_t;

/**
 * @brief  ADC顺序转换通道
 */
typedef enum
{
    AdcSQRCH0MUX     =  0u,         /*!< 顺序扫描模式转换通道0 */
    AdcSQRCH1MUX     =  1u,         /*!< 顺序扫描模式转换通道1 */
    AdcSQRCH2MUX     =  2u,         /*!< 顺序扫描模式转换通道2 */
    AdcSQRCH3MUX     =  3u,         /*!< 顺序扫描模式转换通道3 */
    AdcSQRCH4MUX     =  4u,         /*!< 顺序扫描模式转换通道4 */
    AdcSQRCH5MUX     =  5u,         /*!< 顺序扫描模式转换通道5 */
    AdcSQRCH6MUX     =  6u,         /*!< 顺序扫描模式转换通道6 */
    AdcSQRCH7MUX     =  7u,         /*!< 顺序扫描模式转换通道7 */
    AdcSQRCH8MUX     =  8u,         /*!< 顺序扫描模式转换通道8 */
    AdcSQRCH9MUX     =  9u,         /*!< 顺序扫描模式转换通道9 */
    AdcSQRCH10MUX    =  10u,        /*!< 顺序扫描模式转换通道10 */
    AdcSQRCH11MUX    =  11u,        /*!< 顺序扫描模式转换通道11 */
    AdcSQRCH12MUX    =  12u,        /*!< 顺序扫描模式转换通道12 */
    AdcSQRCH13MUX    =  13u,        /*!< 顺序扫描模式转换通道13 */
    AdcSQRCH14MUX    =  14u,        /*!< 顺序扫描模式转换通道14 */
    AdcSQRCH15MUX    =  15u,        /*!< 顺序扫描模式转换通道15 */
}en_adc_sqr_chmux_t;

/**
 * @brief  ADC插队转换通道
 */
typedef enum
{
    AdcJQRCH0MUX     =  0u,         /*!< 转换通道0 */
    AdcJQRCH1MUX     =  1u,         /*!< 转换通道1 */
    AdcJQRCH2MUX     =  2u,         /*!< 转换通道2 */
    AdcJQRCH3MUX     =  3u,         /*!< 转换通道3 */
}en_adc_jqr_chmux_t;

/**
 * @brief  ADC结果对齐方式
 */
typedef enum
{
     AdcAlignRight  = 0u,           /*!< 转换结果右对齐 */
     AdcAlignLeft   = 1u<<2u,       /*!< 转换结果左对齐 */
}en_adc_align_t;

/**
 * @brief  ADC转换结果自动累加功能
 */
typedef enum
{
     AdcResultAccEnable  = 1u,      /*!< 使能ADC转换结果自动累加 */
     AdcResultAccDisable = 0u,      /*!< 禁止ADC转换结果自动累加 */
}en_adc_result_acc_t;

/**
 * @brief  ADC中断类型定义
 */
typedef enum
{
    AdcMskIrqOv =  1u<<9,        /*!< ADC结果被读取前又一次数据结果被存储标志 */
    AdcMskIrqEoc =  1u<<6,        /*!< ADC顺序扫描转换单次完成 */
    AdcMskIrqJqr =  1u<<5,        /*!< ADC插队扫描转换完成 */
    AdcMskIrqSqr =  1u<<4,        /*!< ADC顺序扫描转换完成 */
    AdcMskIrqReg =  1u<<3,        /*!< ADC转换结果比较区间内 */
    AdcMskIrqHt  =  1u<<2,        /*!< ADC转换结果高于HT */
    AdcMskIrqLt  =  1u<<1,        /*!< ADC转换结果低于LT */
    AdcMskIrqSgl =  1u<<0,        /*!< ADC单次转换完成 */
}en_adc_irq_type_t;

/**
 * @brief  ADC初始化配置结构体
 */
typedef struct
{
    en_adc_mode_t           enAdcMode;                  /*!< ADC转换模式 */
    
    en_adc_clk_div_t        enAdcClkDiv;                /*!< ADC时钟选择 */
    en_adc_samp_cycle_sel_t enAdcSampCycleSel;          /*!< ADC采样周期选择 */
    en_adc_ref_vol_sel_t    enAdcRefVolSel;             /*!< ADC参考电压选择 */
    en_adc_op_buf_t         enAdcOpBuf;                 /*!< ADC输入信号放大器控制使能 */
    en_adc_ov_mode_t        enOvMode;                   /*!< ADC过转换时Adc_Result存储方式 */
    en_adc_align_t          enAdcAlign;                 /*!< ADC转换结果对齐控制 */
}stc_adc_cfg_t;

/**
 * @brief  ADC顺序扫描模式配置结构体
 */
typedef struct
{
    uint8_t                 u8SqrCnt;                   /*!< ADC顺序扫描转换次数 */
    en_adc_result_acc_t     enResultAcc;                /*!< ADC转换结果自动累加功能 */
    boolean_t               bSqrDmaTrig;                /*!< ADC顺序扫描转换完成DMA触发使能 */
}stc_adc_sqr_cfg_t;

/**
 * @brief  ADC插队扫描模式配置结构体
 */
typedef struct
{
    uint8_t                 u8JqrCnt;                   /*!< ADC顺序扫描转换次数 */
    boolean_t               bJqrDmaTrig;                /*!< ADC插队扫描转换完成DMA触发使能 */    
}stc_adc_jqr_cfg_t;

/**
 * @brief  ADC比较功能配置结构体
 */
typedef struct
{
    boolean_t bAdcRegCmp ;                  /*!< ADC区间使能 */ 
    boolean_t bAdcHtCmp ;                   /*!< ADC上超出区间使能 */ 
    boolean_t bAdcLtCmp ;                   /*!< ADC下超出区间使能 */
    
    uint32_t u32AdcHighThd;                 /*!< ADC比较上阈值 */
    uint32_t u32AdcLowThd;                  /*!< ADC比较下阈值 */ 
    
    en_adc_samp_ch_sel_t    enSampChSel;    /*!< ADC采样通道选择 */
    
}stc_adc_threshold_cfg_t;

/**
 * @}
 */

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
 

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Macros ADC全局宏定义
 * @{
 */

/**
 * @defgroup ADC_Scan_Channel ADC scan channel enable
 * @{
 */
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN模式使用ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN模式使用ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN模式使用ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN模式使用ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN模式使用ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN模式使用ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN模式使用ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN模式使用ADC CH7 */   
/**
 * @}
 */

/**
 * @}
 */ 

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup ADC_Global_Functions ADC全局函数定义
 * @{
 */

en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg);

void Adc_EnableIrq(en_adc_irq_type_t enAdcIrq);
void Adc_DisableIrq(en_adc_irq_type_t enAdcIrq);

boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq);
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq);

void Adc_Enable(void);
void Adc_Disable(void);

en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg);
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg);

en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh); 
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);

void Adc_SglSqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, en_adc_trig_delay_t enTrigDelay);
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, en_adc_trig_delay_t enTrigDelay);

void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg);

void Adc_SGL_Start(void);
void Adc_SGL_Stop(void);

void Adc_SQR_Start(void);
void Adc_SQR_Stop(void);

void Adc_JQR_Start(void);
void Adc_JQR_Stop(void);

uint32_t Adc_GetSglResult(void);
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux);
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux);

uint32_t Adc_GetAccResult(void);
void Adc_ClrAccResult(void);

/**
 * @}
 */



/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
