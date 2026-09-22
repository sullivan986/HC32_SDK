/**
 *******************************************************************************
 * @file  atimer3.h
 * @brief This file contains all the functions prototypes of the ATIM3 driver
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

#ifndef __ATIMER3_H__
#define __ATIMER3_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_ATIM3 ATIM3模块驱动库
 * @{
 */


/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup ATIM3_Global_Types ATIM3全局类型定义
 * @{
 */
 
/**
 * @brief Atimer3 ch012通道定义
 */
typedef enum
{
    Tim3CH0   = 0u,        /*!<  Atimer3通道0 */
    Tim3CH1   = 1u,        /*!<  Atimer3通道1 */
    Tim3CH2   = 2u,        /*!<  Atimer3通道2 */
}en_tim3_channel_t;

/**
 * @brief Atimer3 ch3通道定义
 */
typedef enum
{
    Tim3CH3A  = 0u,        /*!<  Atimer3通道2 */
    Tim3CH3B  = 8u,        /*!<  Atimer3通道2 */
}en_tim3_ch3_t;
/**
 * @brief 工作模式选择数据类型重定义 (MODE)(模式0/1/23)
 */
typedef enum
{
    Tim3WorkMode0  = 0u,         /*!<  定时器模式 */
    Tim3WorkMode1  = 1u,         /*!<  PWC模式 */
    Tim3WorkMode2  = 2u,         /*!<  锯齿波模式 */
    Tim3WorkMode3  = 3u,         /*!<  三角波模式 */
}en_tim3_work_mode_t;

/**
 * @brief 极性控制数据类型重定义 (GATE_P)(模式0)
 */
typedef enum
{
    Tim3GatePositive = 0u,            /*!<  高电平有效 */
    Tim3GateOpposite = 1u,            /*!<  低电平有效 */
}en_tim3_m0cr_gatep_t;

/**
 * @brief TIM3 预除频选择 (PRS)(模式0/1/23)
 */
typedef enum
{
    Tim3PCLKDiv1   = 0u,           /*!<  Div 1 */  
    Tim3PCLKDiv2   = 1u,           /*!<  Div 2 */  
    Tim3PCLKDiv4   = 2u,           /*!<  Div 4 */  
    Tim3PCLKDiv8   = 3u,           /*!<  Div 8 */  
    Tim3PCLKDiv16  = 4u,           /*!<  Div 16 */  
    Tim3PCLKDiv32  = 5u,           /*!<  Div 32 */  
    Tim3PCLKDiv64  = 6u,           /*!<  Div 64 */  
    Tim3PCLKDiv256 = 7u,           /*!<  Div 256 */  
}en_tim3_cr_timclkdiv_t;

/**
 * @brief 计数/定时器功能选择数据类型重定义 (CT)(模式0/1/23)
 */
typedef enum
{
    Tim3Timer   = 0u,            /*!<  定时器功能, 计数时钟为内部PCLK */  
    Tim3Counter = 1u,            /*!<  计数器功能, 计数时钟为外部ETR */  
}en_tim3_cr_ct_t;


/**
 * @brief 定时器工作模式数据类型重定义 (MD)(模式0)
 */
typedef enum
{
    Tim332bitFreeMode  = 0u,         /*!<  32位计数器/定时器 */  
    Tim316bitArrMode  = 1u,         /*!<  自动重装载16位计数器/定时器 */  
}en_tim3_m0cr_md_t;

/**
** \brief TIM3中断类型数据类型重定义(模式0/1/23)
 */
typedef enum 
{
    Tim3UevIrq     = 0u,         /*!<  溢出/事件更新中断 */  
    Tim3PwcCA0Irq  = 2u,         /*!<  脉宽测量(仅模式1)/CH0A捕获or比较中断(仅模式23存在) */  
    Tim3CA1Irq     = 3u,         /*!<  CH1A捕获/比较中断(仅模式23存在) */  
    Tim3CA2Irq     = 4u,         /*!<  CH2A捕获/比较中断(仅模式23存在) */  
    Tim3CB0Irq     = 5u,         /*!<  CH0B捕获/比较中断(仅模式23存在) */  
    Tim3CB1Irq     = 6u,         /*!<  CH1B捕获/比较中断(仅模式23存在) */  
    Tim3CB2Irq     = 7u,         /*!<  CH2B捕获/比较中断(仅模式23存在) */  
    Tim3CA0E       = 8u,         /*!<  CH0A捕获数据丢失标志(仅模式23存在)(不是中断) */  
    Tim3CA1E       = 9u,         /*!<  CH1A捕获数据丢失标志(仅模式23存在)(不是中断) */  
    Tim3CA2E       = 10u,        /*!<  CH2A捕获数据丢失标志(仅模式23存在)(不是中断) */  
    Tim3CB0E       = 11u,        /*!<  CH0B捕获数据丢失标志(仅模式23存在)(不是中断) */  
    Tim3CB1E       = 12u,        /*!<  CH1B捕获数据丢失标志(仅模式23存在)(不是中断) */  
    Tim3CB2E       = 13u,        /*!<  CH2B捕获数据丢失标志(仅模式23存在)(不是中断) */  
    Tim3BkIrq      = 14u,        /*!<  刹车中断(仅模式23存在) */  
    Tim3TrigIrq    = 15u,        /*!<  触发中断(仅模式23存在) */  
    Tim3OVIrq      = 16u,        /*!<  计数上溢中断(仅模式23存在) */  
    Tim3UDIrq      = 17u,        /*!<  计数下溢中断(仅模式23存在) */  
    Tim3CA3Irq     = 18u,        /*!<  CH3A捕获/比较中断(仅模式23存在) */  
    Tim3CB3Irq     = 19u,        /*!<  CH3B捕获/比较中断(仅模式23存在) */  
}en_tim3_irq_type_t;

/**
 * @brief 测量开始结束数据类型重定义 (Edg1stEdg2nd)(模式1)
 */
typedef enum 
{
    Tim3PwcRiseToRise  = 0u,            /*!<  上升沿到上升沿(周期) */  
    Tim3PwcFallToRise  = 1u,            /*!<  下降沿到上升沿(低电平) */  
    Tim3PwcRiseToFall  = 2u,            /*!<  上升沿到下降沿(高电平) */  
    Tim3PwcFallToFall  = 3u,            /*!<  下降沿到下降沿(周期) */  
}en_tim3_m1cr_Edge_t;

/**
 * @brief PWC测量测试模式选择数据类型重定义 (Oneshot)(模式1)
 */
typedef enum 
{
    Tim3PwcCycleDetect    = 0u,         /*!<  PWC循环测量 */  
    Tim3PwcOneShotDetect  = 1u,         /*!<  PWC单次测量 */  
}en_tim3_m1cr_oneshot_t;

/**
 * @brief PWC IA0选择数据类型重定义 (IA0S)(模式1)
 */
typedef enum 
{
    Tim3IA0Input    = 0u,         /*!<  IAO输入 */  
    Tim3XORInput    = 1u,         /*!<  IA0 ETR GATE XOR(TIM0/1/2)/IA0 IA1 IA2 XOR(TIM3) */  
}en_tim3_m1_mscr_ia0s_t;

/**
 * @brief PWC IB0选择数据类型重定义 (IA0S)(模式1)
 */
typedef enum 
{
    Tim3IB0Input    = 0u,         /*!<  IBO输入 */  
    Tim3TsInput     = 1u,         /*!<  内部触发TS选择信号 */  
}en_tim3_m1_mscr_ib0s_t;

/**
 * @brief 输出极性、输入相位 数据类型重定义 (CCPA0/CCPB0/ETP/BKP)(模式1/23)
 */
typedef enum 
{
    Tim3PortPositive      = 0u,         /*!<  正常输入输出 */  
    Tim3PortOpposite      = 1u,         /*!<  反向输入输出 */  
}en_tim3_port_polarity_t;

/**
 * @brief 滤波选择数据类型重定义 (FLTET/FLTA0/FLAB0)(模式1/23)
 */
typedef enum 
{
    Tim3FltNone          = 0u,         /*!<  无滤波 */  
    Tim3FltPCLKCnt3      = 4u,         /*!<  PCLK 3个连续有效 */  
    Tim3FltPCLKDiv4Cnt3  = 5u,         /*!<  PCLK/4 3个连续有效 */  
    Tim3FltPCLKDiv16Cnt3 = 6u,         /*!<  PCLK/16 3个连续有效 */  
    Tim3FltPCLKDiv64Cnt3 = 7u,         /*!<  PCLK/64 3个连续有效 */  
}en_tim3_flt_t;

/**
 * @brief 通道比较控制 数据类型重定义 (OCMA/OCMB)(模式23)
 */
typedef enum 
{
    Tim3ForceLow      = 0u,         /*!<  强制为0 */  
    Tim3ForceHigh     = 1u,         /*!<  强制为1 */  
    Tim3CMPForceLow   = 2u,         /*!<  比较匹配时强制为0 */  
    Tim3CMPForceHigh  = 3u,         /*!<  比较匹配时强制为1 */  
    Tim3CMPInverse    = 4u,         /*!<  比较匹配时翻转电平 */  
    Tim3CMPOnePrdHigh = 5u,         /*!<  比较匹配时输出一个计数周期的高电平 */  
    Tim3PWMMode1      = 6u,         /*!<  通道控制为PWM mode 1 */  
    Tim3PWMMode2      = 7u,         /*!<  通道控制为PWM mode 2 */  
}en_tim3_m23_fltr_ocm_t;

/**
 * @brief 主从模式TS数据类型重定义 (TS)(模式1/23)
 */
typedef enum 
{
    Tim3Ts0ETR        = 0u,         /*!<  ETR外部输入滤波后的相位选择信号 */  
    Tim3Ts1TIM0TRGO   = 1u,         /*!<  Atimer0的TRGO输出信号 */  
    Tim3Ts2TIM1TRGO   = 2u,         /*!<  Atimer1的TRGO输出信号 */  
    Tim3Ts3TIM2TRGO   = 3u,         /*!<  Atimer2的TRGO输出信号 */  
    Tim3Ts4TIM3TRGO   = 4u,         /*!<  Atimer3的TRGO输出信号 */  
    Tim3Ts5IA0ED      = 5u,         /*!<  CH0A的边沿信号 (模式1无效) */
    Tim3Ts6IAFP       = 6u,         /*!<  CH0A 外部输输入滤波后的相位选择信号 */  
    Tim3Ts7IBFP       = 7u,         /*!<  CH0B 外部输输入滤波后的相位选择信号 */  
}en_tim3_mscr_ts_t;

/**
 * @brief PWM输出模式选择数据类型重定义 (COMP)(模式23)
 */
typedef enum 
{
    Tim3IndependentPWM      = 0u,         /*!<  独立PWM输出 */  
    Tim3ComplementaryPWM    = 1u,         /*!<  互补PWM输出 */  
}en_tim3_m23cr_comp_t;

/**
 * @brief 计数方向选择数据类型重定义 (DIR)(模式23)
 */
typedef enum 
{
    Tim3CntUp      = 0u,         /*!<  向上计数 */  
    Tim3CntDown    = 1u,         /*!<  向下计数 */  
}en_tim3_m23cr_dir_t;

/**
 * @brief 计数方向选择数据类型重定义 (PWM2S)(模式23)
 */
typedef enum 
{
    Tim3DoublePointCmp      = 0u,         /*!<  双点比较使能, 使用CCRA,CCRB比较控制OCREFA输出 */  
    Tim3SinglePointCmp      = 1u,         /*!<  单点比较使能, 使用CCRA比较控制OCREFA输出 */  
}en_tim3_m23cr_pwm2s_t;

/**
 * @brief GATE在PWM互补模式下捕获或比较功能 选择数据类型重定义 (CSG)(模式23)
 */
typedef enum 
{
     Tim3PWMCompGateCmpOut    = 0u,         /*!<  在PWM互补模式下,Gate作为比较输出 */  
     Tim3PWMCompGateCapIn     = 1u,         /*!<  在PWM互补模式下,Gate作为捕获输入 */  
}en_tim3_m23cr_csg_t;


/**
 * @brief 比较捕获寄存器 数据类型重定义 (CCR0A,CCR0B)(模式23)
 */
typedef enum 
{
     Tim3CCR0A    = 0u,         /*!<  CCR0A比较捕获寄存器 */  
     Tim3CCR0B    = 4u,         /*!<  CCR0B比较捕获寄存器 */  
     Tim3CCR1A    = 8u,         /*!<  CCR1A比较捕获寄存器 */  
     Tim3CCR1B    = 0xCu,       /*!<  CCR1B比较捕获寄存器 */  
     Tim3CCR2A    = 0x10u,      /*!<  CCR2A比较捕获寄存器 */  
     Tim3CCR2B    = 0x14u,      /*!<  CCR2B比较捕获寄存器 */  
     Tim3CCR3A    = 0x18u,      /*!<  CCR3A比较捕获寄存器 */  
     Tim3CCR3B    = 0x20u,      /*!<  CCR3B比较捕获寄存器 */  
}en_tim3_m23_ccrx_t;

/**
 * @brief  OCREF清除源 选择数据类型重定义 (OCCS)(模式23)
 */
typedef enum 
{
     Tim3OC_Ref_Clr  = 0u,         /*!<  来自VC的OC_Ref_Clr */  
     Tim3ETRf        = 1u,         /*!<  外部ETRf */  
}en_tim3_m23ce_occs_t;

/**
 * @brief  比较匹配(中断)模式 选择数据类型重定义 (CIS/CISB)(模式23)
 */
typedef enum 
{
     Tim3CmpIntNone        = 0u,         /*!<  无比较匹配(中断) */  
     Tim3CmpIntRise        = 1u,         /*!<  上升沿（中断)比较匹配 */  
     Tim3CmpIntFall        = 2u,         /*!<  下降沿(中断)比较匹配 */  
     Tim3CmpIntRiseFall    = 3u,         /*!<  上升沿下降沿(中断)比较匹配 */  
}en_tim3_m23_cisa_cisb_t;

/**
 * @brief TIM3端口控制 - 刹车时CHx输出状态控制(BKSA/BKSB)(模式23)
 */
typedef enum 
{
    Tim3CHxBksHiZ         = 0u,         /*!<  刹车使能时, CHx端口输出高阻态 */  
    Tim3CHxBksNorm        = 1u,         /*!<  刹车使能时,CHx端口正常输出 */  
    Tim3CHxBksLow         = 2u,         /*!<  刹车使能时,CHx端口输出低电平 */  
    Tim3CHxBksHigh        = 3u,         /*!<  刹车使能时,CHx端口输出高电平 */  
}en_tim3_m23_crchx_bks_t;

/**
 * @brief TIM3端口控制 - CHx上升沿下降沿捕获(CRx/CFx)(模式23)
 */
typedef enum 
{
    Tim3CHxCapNone        = 0u,         /*!<  CHx通道捕获禁止 */  
    Tim3CHxCapRise        = 1u,         /*!<  CHx通道上升沿捕获使能 */  
    Tim3CHxCapFall        = 2u,         /*!<  CHx通道下降沿捕获使能 */  
    Tim3CHxCapFallRise    = 3u,         /*!<  CHx通道上升沿下降沿捕获都使能 */  
}en_tim3_m23_crch0_cfx_crx_t;

/**
 * @brief TIM3端口控制 - CHx比较捕获模式(CSA/CSB)(模式23)
 */
typedef enum 
{
    Tim3CHxCmpMode        = 0u,         /*!<  CHx通道设置为比较模式 */  
    Tim3CHxCapMode        = 1u,         /*!<  CHx通道设置为捕获模式 */  
}en_tim3_m23_crch0_csa_csb_t;

/**
 * @brief  比较模式下 DMA比较触发选择 数据类型重定义 (CCDS)(模式23)
 */
typedef enum 
{
     Tim3CmpTrigDMA  = 0u,         /*!<  比较匹配触发DMA */  
     Tim3UEVTrigDMA  = 1u,         /*!<  事件更新代替比较匹配触发DMA */  
}en_tim3_m23_mscr_ccds_t;

/**
 * @brief  主从模式选择 数据类型重定义 (MSM)(模式23)
 */
typedef enum 
{
     Tim3SlaveMode    = 0u,         /*!<  从模式 */  
     Tim3MasterMode   = 1u,         /*!<  主模式 */  
}en_tim3_m23_mscr_msm_t;

/**
 * @brief  触发主模式输出源 数据类型重定义 (MMS)(模式23)
 */
typedef enum 
{
     Tim3MasterUG         = 0u,         /*!<  UG(软件更新)源 */  
     Tim3MasterCTEN       = 1u,         /*!<  CTEN源 */  
     Tim3MasterUEV        = 2u,         /*!<  UEV更新源 */  
     Tim3MasterCMPSO      = 3u,         /*!<  比较匹配选择输出源 */  
     Tim3MasterOCA0Ref    = 4u,         /*!<  OCA0_Ref源 */  
     Tim3MasterOCA1Ref    = 5u,         /*!<  OCA1_Ref源 */  
     Tim3MasterOCA2Ref    = 6u,         /*!<  OCA2_Ref源 */  
     Tim3MasterOCB0Ref    = 7u,         /*!<  OCB0_Ref源 */  
}en_tim3_m23_mscr_mms_t;

/**
 * @brief  触发从模式选择 数据类型重定义 (SMS)(模式23)
 */
typedef enum 
{
     Tim3SlaveIClk        = 0u,         /*!<  使用内部时钟 */  
     Tim3SlaveResetTIM    = 1u,         /*!<  复位功能 */  
     Tim3SlaveTrigMode    = 2u,         /*!<  触发模式 */  
     Tim3SlaveEClk        = 3u,         /*!<  外部时钟模式 */  
     Tim3SlaveCodeCnt1    = 4u,         /*!<  正交编码计数模式1 */  
     Tim3SlaveCodeCnt2    = 5u,         /*!<  正交编码计数模式2 */  
     Tim3SlaveCodeCnt3    = 6u,         /*!<  正交编码计数模式3 */  
     Tim3SlaveGateCtrl    = 7u,         /*!<  门控功能 */  
}en_tim3_m23_mscr_sms_t;

/**
 * @brief 定时器运行控制数据类型重定义 (CTEN)
 */
typedef enum 
{
    Tim3CTENDisable = 0u,            /*!<  停止 */  
    Tim3CTENEnable  = 1u,            /*!<  运行 */  
}en_tim3_start_t;

/**
 * @brief TIM3 mode0 配置结构体定义(模式0)
 */
typedef struct 
{
    en_tim3_work_mode_t     enWorkMode;       /*!<  工作模式设置 */  
    en_tim3_m0cr_gatep_t    enGateP;          /*!<  门控极性控制 */  
    boolean_t               bEnGate;          /*!<  门控使能 */  
    en_tim3_cr_timclkdiv_t  enPRS;            /*!<  预除频配置 */  
    boolean_t               bEnTog;           /*!<  翻转输出使能 */  
    en_tim3_cr_ct_t         enCT;             /*!<  定时/计数功能选择 */  
    en_tim3_m0cr_md_t       enCntMode;        /*!<  计数模式配置 */  
}stc_tim3_mode0_cfg_t;

/**
 * @brief TIM3 mode1 配置结构体定义(模式1)
 */
typedef struct 
{
    en_tim3_work_mode_t     enWorkMode;       /*!<  工作模式设置 */  
    en_tim3_cr_timclkdiv_t  enPRS;            /*!<  预除频配置 */  
    en_tim3_cr_ct_t         enCT;             /*!<  定时/计数功能选择 */  
    en_tim3_m1cr_oneshot_t  enOneShot;        /*!<  单次测量/循环测量选择 */  
}stc_tim3_mode1_cfg_t;

/**
 * @brief PWC输入配置结构体定义(模式1)
 */
typedef struct 
{
    en_tim3_mscr_ts_t          enTsSel;       /*!<  触发输入源选择 */  
    en_tim3_m1_mscr_ia0s_t     enIA0Sel;      /*!<  CHA0输入选择 */  
    en_tim3_m1_mscr_ib0s_t     enIB0Sel;      /*!<  CHB0输入选择 */  
    en_tim3_port_polarity_t    enETRPhase;    /*!<  ETR相位选择 */  
    en_tim3_flt_t              enFltETR;      /*!<  ETR滤波设置 */  
    en_tim3_flt_t              enFltIA0;      /*!<  CHA0滤波设置 */  
    en_tim3_flt_t              enFltIB0;      /*!<  CHB0滤波设置 */  
}stc_tim3_pwc_input_cfg_t;

/**
 * @brief TIM3 mode23 配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_work_mode_t         enWorkMode;       /*!<  工作模式设置 */  
    en_tim3_m23cr_dir_t         enCntDir;         /*!<  计数方向 */  
    en_tim3_cr_timclkdiv_t      enPRS;            /*!<  时钟预除频配置 */  
    en_tim3_cr_ct_t             enCT;             /*!<  定时/计数功能选择 */  
    en_tim3_m23cr_comp_t        enPWMTypeSel;     /*!<  PWM模式选择(独立/互补) */  
    en_tim3_m23cr_pwm2s_t       enPWM2sSel;       /*!<  OCREFA双点比较功能选择 */  
    boolean_t                   bOneShot;         /*!<  单次触发模式使能/禁止 */  
    boolean_t                   bURSSel;          /*!<  更新源选择 */  
}stc_tim3_mode23_cfg_t;

/**
 * @brief GATE在PWM互补模式下捕获或比较功能 配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_m23cr_csg_t        enGateFuncSel;      /*!<  Gate比较/捕获功能选择 */  
    boolean_t                  bGateRiseCap;       /*!<  GATE作为捕获功能时,上沿捕获有效控制 */  
    boolean_t                  bGateFallCap;       /*!<  GATE作为捕获功能时,下沿捕获有效控制 */  
}stc_tim3_m23_gate_cfg_t;

/**
 * @brief CHA/CHB通道比较控制 配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_m23_crch0_csa_csb_t  enCHxACmpCap;     /*!<  CH0A比较/捕获功能选择 */  
    en_tim3_m23_fltr_ocm_t       enCHxACmpCtrl;    /*!<  CH0A通道比较控制 */  
    en_tim3_port_polarity_t      enCHxAPolarity;   /*!<  CH0A输出极性控制 */  
    boolean_t                    bCHxACmpBufEn;    /*!<  比较A缓存功能 使能/禁止 */  
    en_tim3_m23_cisa_cisb_t      enCHxACmpIntSel;  /*!<  CHA比较匹配中断选择 */  
    
    en_tim3_m23_crch0_csa_csb_t  enCHxBCmpCap;     /*!<  CH0B比较/捕获功能选择 */  
    en_tim3_m23_fltr_ocm_t       enCHxBCmpCtrl;    /*!<  CH0B通道比较控制 */  
    en_tim3_port_polarity_t      enCHxBPolarity;   /*!<  CH0B输出极性控制 */  
    boolean_t                    bCHxBCmpBufEn;    /*!<  比较B缓存功能 使能/禁止 */  
    en_tim3_m23_cisa_cisb_t      enCHxBCmpIntSel;  /*!<  CHB0比较匹配中断选择 */  
}stc_tim3_m23_compare_cfg_t;

/**
 * @brief CH3A/CH3B通道比较控制 配置结构体定义(模式23)
 */
typedef struct 
{
    boolean_t                    bCH3CompValBuffEn; /*!<  比较值缓存功能:使能(TRUE)/禁止(FALSE) */  
    boolean_t                    bCH3ComTrigDMAEn;     /*!<  比较(输出)触发DMA功能:使能(TRUE)/禁止(FALSE)*/  
    boolean_t                    bCH3CompEn;        /*!<  通道比较功能:使能(TRUE)/禁止(FALSE) */  
    en_tim3_m23_cisa_cisb_t      enCH3ACmpIntSel;   /*!<  CHA比较匹配(中断)模式选择 */  
}stc_tim3_m23_ch3_cfg_t;

/**
 * @brief CHA/CHB通道输入捕获控制 配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_m23_crch0_csa_csb_t  enCHxACmpCap;     /*!<  CH0A比较/捕获功能选择 */  
    en_tim3_m23_crch0_cfx_crx_t  enCHxACapSel;     /*!<  CH0A捕获边沿选择 */  
    en_tim3_flt_t                enCHxAInFlt;      /*!<  CH0A通道捕获滤波控制 */  
    en_tim3_port_polarity_t      enCHxAPolarity;   /*!<  CH0A输入相位 */  
    
    en_tim3_m23_crch0_csa_csb_t  enCHxBCmpCap;     /*!<  CH0A比较/捕获功能选择 */  
    en_tim3_m23_crch0_cfx_crx_t  enCHxBCapSel;     /*!<  CH0B捕获边沿选择 */  
    en_tim3_flt_t                enCHxBInFlt;      /*!<  CH0B通道捕获滤波控制 */  
    en_tim3_port_polarity_t      enCHxBPolarity;   /*!<  CH0B输入相位 */  
    
}stc_tim3_m23_input_cfg_t;   

/**
 * @brief ETR输入相位滤波配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_port_polarity_t     enETRPolarity;  /*!<  ETR输入极性设置 */  
    en_tim3_flt_t               enETRFlt;       /*!<  ETR滤波设置 */  
}stc_tim3_m23_etr_input_cfg_t;

/**
 * @brief 刹车BK输入相位滤波配置结构体定义(模式23)
 */
typedef struct 
{
    boolean_t                   bEnBrake;         /*!<  刹车使能 */  
    boolean_t                   bEnVCBrake;       /*!<  使能VC刹车 */  
    boolean_t                   bEnSafetyBk;      /*!<  使能safety刹车 */  
    boolean_t                   bEnBKSync;        /*!<  ATIM0/ATIM1/ATIM2刹车同步使能 */  
    en_tim3_m23_crchx_bks_t     enBkCH0AStat;     /*!<  刹车时CH0A端口状态设置 */  
    en_tim3_m23_crchx_bks_t     enBkCH0BStat;     /*!<  刹车时CH0B端口状态设置 */  
    en_tim3_m23_crchx_bks_t     enBkCH1AStat;     /*!<  刹车时CH1A端口状态设置 */  
    en_tim3_m23_crchx_bks_t     enBkCH1BStat;     /*!<  刹车时CH1B端口状态设置 */  
    en_tim3_m23_crchx_bks_t     enBkCH2AStat;     /*!<  刹车时CH2A端口状态设置 */  
    en_tim3_m23_crchx_bks_t     enBkCH2BStat;     /*!<  刹车时CH2B端口状态设置 */  
    en_tim3_port_polarity_t     enBrakePolarity;  /*!<  刹车BK输入极性设置 */  
    en_tim3_flt_t               enBrakeFlt;       /*!<  刹车BK滤波设置 */  
}stc_tim3_m23_bk_input_cfg_t;

/**
 * @brief 死区功能配置结构体定义(模式23)
 */
typedef struct 
{
    boolean_t       bEnDeadTime;      /*!<  使能死区功能 */
    uint8_t         u8DeadTimeValue;  /*!<  死区时间设置 */
}stc_tim3_m23_dt_cfg_t;

/**
 * @brief 触发ADC配置结构体定义(模式23)
 */
typedef struct 
{
    boolean_t     bEnTrigADC;          /*!<  触发ADC全局控制 */  
    boolean_t     bEnUevTrigADC;       /*!<  事件更新触发ADC */  
    boolean_t     bEnCH0ACmpTrigADC;   /*!<  CH0A比较匹配触发ADC */  
    boolean_t     bEnCH0BCmpTrigADC;   /*!<  CH0B比较匹配触发ADC */  
    boolean_t     bEnCH1ACmpTrigADC;   /*!<  CH1A比较匹配触发ADC */  
    boolean_t     bEnCH1BCmpTrigADC;   /*!<  CH1B比较匹配触发ADC */  
    boolean_t     bEnCH2ACmpTrigADC;   /*!<  CH2A比较匹配触发ADC */  
    boolean_t     bEnCH2BCmpTrigADC;   /*!<  CH2B比较匹配触发ADC */  
}stc_tim3_m23_adc_trig_cfg_t;

/**
 * @brief  DMA触发 配置结构体定义(模式23)
 */
typedef struct 
{
    boolean_t                bUevTrigDMA;      /*!<  更新 触发DMA使能 */  
    boolean_t                bTITrigDMA;       /*!<  Trig 触发DMA功能 */  
    boolean_t                bCmpA0TrigDMA;    /*!<  CH0A捕获比较触发DMA使能 */  
    boolean_t                bCmpB0TrigDMA;    /*!<  CH0B捕获比较触发DMA使能 */  
    boolean_t                bCmpA1TrigDMA;    /*!<  CH1A捕获比较触发DMA使能 */  
    boolean_t                bCmpB1TrigDMA;    /*!<  CH1B捕获比较触发DMA使能 */  
    boolean_t                bCmpA2TrigDMA;    /*!<  CH2A捕获比较触发DMA使能 */  
    boolean_t                bCmpB2TrigDMA;    /*!<  CH2B捕获比较触发DMA使能 */  
    en_tim3_m23_mscr_ccds_t  enCmpUevTrigDMA;  /*!<  比较模式下DMA比较触发选择 */  
}stc_tim3_m23_trig_dma_cfg_t;

/**
 * @brief  主从模式 配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_m23_mscr_msm_t      enMasterSlaveSel;  /*!<  主从模式选择 */  
    en_tim3_m23_mscr_mms_t      enMasterSrc;       /*!<  主模式触发源选择 */  
    en_tim3_m23_mscr_sms_t      enSlaveModeSel;    /*!<  从模式选择 */  
    en_tim3_mscr_ts_t           enTsSel;           /*!<  触发输入源选择 */  
}stc_tim3_m23_master_slave_cfg_t;

/**
 * @brief  OCREF清除功能 配置结构体定义(模式23)
 */
typedef struct 
{
    en_tim3_m23ce_occs_t       enOCRefClrSrcSel;  /*!<  OCREF清除源选择 */  
    boolean_t                  bVCClrEn;          /*!<  是否使能来自VC的OCREF_Clr */  
}stc_tim3_m23_OCREF_Clr_cfg_t;

/**
 * @}
 */
/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/


/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup ATIM3_Global_Functions ATIM3全局函数定义
 * @{
 */
 
boolean_t Tim3_GetIntFlag(en_tim3_irq_type_t enTim3Irq);
en_result_t Tim3_ClearIntFlag(en_tim3_irq_type_t enTim3Irq);
en_result_t Tim3_ClearAllIntFlag(void);
en_result_t Tim3_Mode0_EnableIrq(void);
en_result_t Tim3_Mode0_DisableIrq(void);
en_result_t Tim3_Mode1_EnableIrq (en_tim3_irq_type_t enTim3Irq);
en_result_t Tim3_Mode1_DisableIrq (en_tim3_irq_type_t enTim3Irq);
en_result_t Tim3_Mode23_EnableIrq (en_tim3_irq_type_t enTim3Irq);
en_result_t Tim3_Mode23_DisableIrq (en_tim3_irq_type_t enTim3Irq);
en_result_t Tim3_Mode0_Init(stc_tim3_mode0_cfg_t* pstcCfg);
en_result_t Tim3_M0_Run(void);
en_result_t Tim3_M0_Stop(void);
en_result_t Tim3_M0_ARRSet(uint16_t u16Data);
en_result_t Tim3_M0_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M0_Cnt16Get(void);
en_result_t Tim3_M0_Cnt32Set(uint32_t u32Data);
uint32_t Tim3_M0_Cnt32Get(void);
en_result_t Tim3_M0_Enable_Output(boolean_t bEnOutput);
en_result_t Tim3_M0_EnTOG(boolean_t bEnTOG);
en_result_t Tim3_Mode1_Init(stc_tim3_mode1_cfg_t* pstcCfg);
en_result_t Tim3_M1_Input_Cfg(stc_tim3_pwc_input_cfg_t* pstcCfg);
en_result_t Tim3_M1_PWC_Edge_Sel(en_tim3_m1cr_Edge_t enEdgeSel);
en_result_t Tim3_M1_Run(void);
en_result_t Tim3_M1_Stop(void);
en_result_t Tim3_M1_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M1_Cnt16Get(void);
uint16_t Tim3_M1_PWC_CapValueGet(void);
en_result_t Tim3_Mode23_Init(stc_tim3_mode23_cfg_t* pstcCfg);
en_result_t Tim3_M23_Run(void);
en_result_t Tim3_M23_Stop(void);
en_result_t Tim3_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput);
en_result_t Tim3_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn);
en_result_t Tim3_M23_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M23_Cnt16Get(void);
en_result_t Tim3_M23_CCR_Set(en_tim3_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Tim3_M23_CCR_Get(en_tim3_m23_ccrx_t enCCRSel);
en_result_t Tim3_M23_GateFuncSel(stc_tim3_m23_gate_cfg_t* pstcCfg);
en_result_t Tim3_M23_MasterSlave_Set(stc_tim3_m23_master_slave_cfg_t* pstcCfg);
en_result_t Tim3_M23_PortOutput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_compare_cfg_t* pstcCfg);
en_result_t Tim3_M23_Ch3_Cfg(en_tim3_ch3_t enTim3Chx, stc_tim3_m23_ch3_cfg_t* pstcCfg);
en_result_t Tim3_M23_PortInput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_input_cfg_t* pstcCfg);
en_result_t Tim3_M23_ETRInput_Cfg(stc_tim3_m23_etr_input_cfg_t* pstcCfg);
en_result_t Tim3_M23_BrakeInput_Cfg(stc_tim3_m23_bk_input_cfg_t* pstcBkCfg);
en_result_t Tim3_M23_TrigADC_Cfg(stc_tim3_m23_adc_trig_cfg_t* pstcCfg);
en_result_t Tim3_M23_DT_Cfg(stc_tim3_m23_dt_cfg_t* pstcCfg);
en_result_t Tim3_M23_SetValidPeriod(uint8_t u8ValidPeriod, boolean_t bOVMaskEn, boolean_t bUDMaskEn);
en_result_t Tim3_M23_OCRefClr(stc_tim3_m23_OCREF_Clr_cfg_t* pstcCfg);
en_result_t Tim3_M23_EnDMA(stc_tim3_m23_trig_dma_cfg_t* pstcCfg);
en_result_t Tim3_M23_EnSwTrigCapCmpA(en_tim3_channel_t enTim3Chx);
en_result_t Tim3_M23_EnSwTrigCapCmpB(en_tim3_channel_t enTim3Chx);
en_result_t Tim3_M23_EnSwUev(void);
en_result_t Tim3_M23_EnSwTrig(void);
en_result_t Tim3_M23_EnSwBk(void);

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
#endif


#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


