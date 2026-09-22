/**
 *******************************************************************************
 * @file  vc.h
 * @brief This file contains all the functions prototypes of the VC driver
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
#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_VC VC模块驱动库
 * @{
 */




/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup VC_Global_Types VC全局类型定义
 * @{
 */
  
/**
 * @brief VC通道
 */
typedef enum
{
    VcChannel0 = 0u,             /*!< VC0 */ 
    VcChannel1 = 0x10u,            /*!< VC1 */ 

}en_vc_channel_t;


/**
 * @brief VC迟滞: VC_CR0_HYS
 */
typedef enum 
{
    VcDelayoff  = 0u,            /*!< 迟滞关闭 */ 
    VcDelay10mv = 1u,            /*!< 迟滞10mv */ 
    VcDelay20mv = 2u,            /*!< 迟滞20mv */ 
    VcDelay30mv = 3u,            /*!< 迟滞30mv */ 
}en_vc_cmp_delay_t;

/**
 * @brief VC偏置电流: VC_CR0_BIAS
 */
typedef enum 
{
    VcBias300na  = 0u,            /*!< 偏置电流300nA */ 
    VcBias1200na = 1u,            /*!< 偏置电流1.2uA */ 
    VcBias10ua   = 2u,            /*!< 偏置电流10uA */ 
    VcBias20ua   = 3u,            /*!< 偏置电流20uA */ 
}en_vc_bias_current_t;

/**
 * @brief VC输出滤波时间: VC_CR1_FLTTIME
 */
typedef enum 
{
    VcFilterFltClk1     = 0u,     /*!< 滤除宽度小于1个滤波时钟的信号 */ 
    VcFilterFltClk3     = 1u,     /*!< 滤除宽度小于3个滤波时钟的信号 */ 
    VcFilterFltClk7     = 2u,     /*!< 滤除宽度小于7个滤波时钟的信号 */ 
    VcFilterFltClk15    = 3u,     /*!< 滤除宽度小于15个滤波时钟的信号 */ 
    VcFilterFltClk63    = 4u,     /*!< 滤除宽度小于63个滤波时钟的信号 */ 
    VcFilterFltClk255   = 5u,     /*!< 滤除宽度小于255个滤波时钟的信号 */ 
    VcFilterFltClk1023  = 6u,     /*!< 滤除宽度小于1023个滤波时钟的信号 */ 
    VcFilterFltClk4095  = 7u,     /*!< 滤除宽度小于4095个滤波时钟的信号 */ 
}en_vc_resp_filter_t;

    
/**
 * @brief VC滤波时钟选择: VC_CR1_FLTCLK
 */
typedef enum 
{
    VcFilterClkRc150k  = 0u,            /*!< 内置RC振荡器，频率约150KHz */ 
    VcFilterClkPCLK    = 1u,            /*!< PCLK */ 
}en_vc_filt_clk_t;

/**
 * @brief VC P端输入: VC_CR1_PSEL
 */
typedef enum 
{
    VcInPCh0 = 0u,                /*!< 输入通道0  PA00 */ 
    VcInPCh1 = 1u,                /*!< 输入通道1  PA01 */ 
    VcInPCh2 = 2u,                /*!< 输入通道2  PA02 */ 
    VcInPCh3 = 3u,                /*!< 输入通道3  PA03 */ 
    VcInPCh4 = 4u,                /*!< 输入通道4  PA04 */ 
    VcInPCh5 = 5u,                /*!< 输入通道5  PA05 */ 
    VcInPCh6 = 6u,                /*!< 输入通道6  PB00 */ 
    VcInPCh7 = 7u,                /*!< 输入通道7  PB01 */ 
    VcInPCh8 = 8u,                /*!< 输入通道8  PB12 */ 
    VcInPCh9 = 9u,                /*!< 输入通道9  PB04 */ 
    VcInPCh10 = 10u,              /*!< 输入通道10 PB05 */                     
}en_vc_input_p_src_t;

/**
 * @brief VC N端输入: VC_CR1_NSEL
 */
typedef enum 
{
    VcInNCh0    = 0u,         /*!< 输入通道0  PA00 */ 
    VcInNCh1    = 1u,         /*!< 输入通道1  PA01 */ 
    VcInNCh2    = 2u,         /*!< 输入通道2  PA02 */ 
    VcInNCh3    = 3u,         /*!< 输入通道3  PA03 */ 
    VcInNCh4    = 4u,         /*!< 输入通道4  PA04 */ 
    VcInNCh5    = 5u,         /*!< 输入通道5  PA05 */ 
    VcInNCh6    = 6u,         /*!< 输入通道6  PB00 */ 
    VcInNCh7    = 7u,         /*!< 输入通道7  PB01 */ 
    VcInNCh8    = 8u,         /*!< 输入通道8  PB12 */ 
    VcInNCh9    = 9u,         /*!< 输入通道9  PB04 */ 
    VcInNCh10   = 10u,        /*!< 输入通道10 PB05 */  
    ResDivOut   = 11u,        /*!< 内置电阻分压输出的电压  */
    AiTs        = 12u,        /*!< 内部温度传感器输出电压  */ 
    AiAdcVref   = 14u,        /*!< ADC参考电压VREF         */ 
    AiLdo       = 15u,        /*!< LDO */ 
}en_vc_input_n_src_t;

/**
 * @brief VC中断触发方式: VC_CR1_LEVEL_RISING_FALLING
 */
typedef enum
{
    VcIrqNone = 0u,            /*!< 无中断 */ 
    VcIrqRise = 0x2u,          /*!< 上升沿触发 */ 
    VcIrqFall = 0x1u,          /*!< 下降沿触发 */ 
    VcIrqHigh = 0x4u,          /*!< 高电平触发 */ 
}en_vc_irq_sel_t;

/**
 * @brief VC状态 : VC_SR
 */
typedef enum
{
    Vc_Intf    = 0u,          /*!< VC中断标志 */ 
    Vc_Filter  = 1u,          /*!< VC Filter 后的状态 */                
}en_vc_ifr_t;

/**
 * @brief VC DIV参考电压Vref选择: VC_CR0_REF
 */
typedef enum
{
    VcDivVrefAvcc = 0u,              /*!< AVCC */ 
    VcDivVrefAdc  = 1u,              /*!< ADC_CR0 SREF选择参考电压 */ 
}en_vc_div_vref_t;

/**
 * @brief VC 输出极性控制: VC_CR2_POL
 */
typedef enum
{
    VcOutPolarityNormal = 0u,             /*!< 输出同向 */ 
    VcOutPolarityInv    = 1u,             /*!< 输出反向 */ 
}en_vc_out_polarity_t;

/**
 * @brief VC输出配置: VC_CR2   
 */
typedef struct 
{
    en_vc_out_polarity_t  enVcOutP;     /*!< 结果输出正反向控制 */ 
    boolean_t             bAtim0En;     /*!< 结果输出到TIM0 REFCLR使能控制 */ 
    boolean_t             bAtim1En;     /*!< 结果输出到TIM1 REFCLR使能控制 */ 
    boolean_t             bAtim2En;     /*!< 结果输出到TIM2 REFCLR使能控制 */ 
    boolean_t             bAtim3En;     /*!< 结果输出到TIM3 REFCLR使能控制 */ 
    boolean_t             bAtimBkEn;    /*!< 结果输出到Timer0,1,2,3刹车控制 */ 
    boolean_t             bVcWindowEn;  /*!< 窗口比较功能配置 */ 
}stc_vc_output_cfg_t;

/**
 * @brief VC模块配置: VC_CR1: VC_CR1_REF  VC_CR1_DIV_EN  VC_CR1_DIV
 */
typedef struct
{
    boolean_t           bDivEn;       /*!< VC_CR: VC_DIV_EN */ 
    uint8_t             u8DivVal;     /*!< VC_CR: VC_DIV 范围：0-63 */ 
    en_vc_div_vref_t    enDivVref;    /*!< VC_CR: VC_REF2P5_SEL */ 
}stc_vc_dac_cfg_t;

/**
 * @brief VC初始化
 */
typedef struct
{
    en_vc_channel_t         enVcChannel;        /*!< VC通道选择 */ 
    en_vc_cmp_delay_t       enVcCmpDly;         /*!< VC迟滞 */ 
    en_vc_bias_current_t    enVcBiasCurrent;    /*!< VC功耗选择 */ 
    en_vc_resp_filter_t     enVcFilterTime;     /*!< 输出滤波时间 */ 
    en_vc_input_p_src_t     enVcInPin_P;        /*!< P端输入 */ 
    en_vc_input_n_src_t     enVcInPin_N;        /*!< N端输入 */ 
    en_vc_filt_clk_t        enVcFilterSrcClk;   /*!< 滤波时钟选择 */ 
    boolean_t               bFlten;             /*!< 滤波输出使能 */ 
}stc_vc_channel_cfg_t;

/**
 * @}
 */


/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup VC_Global_Functions VC全局函数定义
 * @{
 */
void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType);
void  Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus);
boolean_t Vc_GetItStatus(en_vc_channel_t Channelx, en_vc_ifr_t Result);
void Vc_ClearItStatus(en_vc_channel_t Channelx);
en_result_t Vc_DacInit(en_vc_channel_t Channelx, stc_vc_dac_cfg_t *pstcDacCfg);
void Vc_Output_Cfg(en_vc_channel_t enChannel, stc_vc_output_cfg_t *pstcOutCfg);
void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg);
void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus);
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

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

