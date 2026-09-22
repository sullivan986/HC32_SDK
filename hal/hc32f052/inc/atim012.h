/**
 *******************************************************************************
 * @file  atim012.h
 * @brief This file contains all the functions prototypes of the ATIMER012 driver
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


#ifndef __ATIM012_H__
#define __ATIM012_H__

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
 * @addtogroup DDL_ATIM012 ATIM012模块驱动库
 * @{
 */
    

  
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup ATIM012_Global_Types ATIM012全局类型定义
 * @{
 */
  

/**
 * @brief  ATIM012 定时器选择数据类型重定义
 */
typedef enum
{
    ATIM0    = 0u,           /*!<  Timer0*/
    ATIM1    = 0x400u,       /*!<  Timer1*/
    ATIM2    = 0x800u,       /*!<  Timer2*/
}en_atim_unit_t;


/**
 * @brief  ATIM012 工作模式选择数据类型重定义 (MODE)(模式0/1/23)
 */
typedef enum
{
    AtimWorkMode0  = 0u,         /*!<  模式0:定时器模式*/
    AtimWorkMode1  = 1u,         /*!<  模式1: PWC模式*/
    AtimWorkMode2  = 2u,         /*!<  模式2: 锯齿波模式*/
    AtimWorkMode3  = 3u,         /*!<  模式3: 三角波模式*/
}en_atim_work_mode_t;

/**
 * @brief  ATIM012 极性控制数据类型重定义 (GATE_P)(模式0)
 */
typedef enum
{
    AtimGatePositive = 0u,            /*< 高电平有效*/   
    AtimGateOpposite = 1u,            /*< 低电平有效*/   
}en_atim_m0_gatep_t;


/**
 * @brief  ATIM012 预除频选择 (PRS)(模式0/1/23)
 */
typedef enum
{
    AtimPCLKDiv1   = 0u,           /*!<  Div 1*/
    AtimPCLKDiv2   = 1u,           /*!<  Div 2*/
    AtimPCLKDiv4   = 2u,           /*!<  Div 4*/
    AtimPCLKDiv8   = 3u,           /*!<  Div 8*/
    AtimPCLKDiv16  = 4u,           /*!<  Div 16*/
    AtimPCLKDiv32  = 5u,           /*!<  Div 32*/
    AtimPCLKDiv64  = 6u,           /*!<  Div 64*/
    AtimPCLKDiv256 = 7u,           /*!<  Div 256*/
}en_atim_cr_timclkdiv_t;

/**
 * @brief  ATIM012 计数/定时器功能选择数据类型重定义 (CT)(模式0/1/23)
 */
typedef enum
{
    AtimTimer   = 0u,            /*!<  定时器功能，计数时钟为内部PCLK*/
    AtimCounter = 1u,            /*!<  计数器功能，计数时钟为外部ETR*/
}en_atim_cr_ct_t;

/**
 * @brief  ATIM012 定时器工作模式数据类型重定义 (MD)(模式0)
 */
typedef enum
{
    Atim32bitFreeMode  = 0u,        /*!<  32位计数器/定时器*/
    Atim16bitArrMode  = 1u,         /*!<  自动重载16位计数器/定时器*/
}en_atim_m0cr_md_t;

/**
 * @brief ATIM0/ATIM1/ATIM2中断类型数据类型重定义(模式0/1/23)
 */
typedef enum
{
    AtimUevIrq     = 0u,         /*!<  溢出/事件更新中断*/
    AtimPwcCA0Irq  = 2u,         /*!<  脉宽测量(仅模式1)/捕获or比较中断A(仅模式23存在) */
    AtimCB0Irq     = 5u,         /*!<  捕获or比较中断B(仅模式23存在) */
    AtimCA0E       = 8u,         /*!<  CH0A捕获数据丢失标志(仅模式23存在),不是中断 */
    AtimCB0E       = 11u,        /*!<  CH0B捕获数据丢失标志(仅模式23存在),不是中断 */
    AtimBkIrq      = 14u,        /*!<  刹车中断(仅模式23存在) */
    AtimTrigIrq    = 15u,        /*!<  触发中断(仅模式23存在) */   
    AtimOvIrq      = 16u,        /*!<  上溢中断(仅模式23存在) */
    AtimUndIrq     = 17u,        /*!<  下溢中断(仅模式23存在) */  
}en_atim_irq_type_t;

/**
 * @brief 测量开始结束数据类型重定义 (Edg1stEdg2nd)(模式1)
 */
typedef enum
{
    AtimPwcRiseToRise  = 0u,            /*!<  上升沿到上升沿(周期) */
    AtimPwcFallToRise  = 1u,            /*!<  下降沿到上升沿(低电平) */
    AtimPwcRiseToFall  = 2u,            /*!<  上升沿到下降沿(高电平) */
    AtimPwcFallToFall  = 3u,            /*!<  下降沿到下降沿(周期) */
}en_atim_m1cr_Edge_t;

/**
 * @brief PWC测量测试模式选择数据类型重定义 (Oneshot)(模式1)
 */
typedef enum
{
    AtimPwcCycleDetect    = 0u,         /*!<  PWC循环测量 */
    AtimPwcOneShotDetect  = 1u,         /*!<  PWC单次测量 */
}en_atim_m1cr_oneshot_t;

/**
 * @brief PWC IA0选择数据类型重定义 (IA0S)(模式1)
 */
typedef enum
{
    AtimIA0Input    = 0u,         /*!<  IAO输入 */   
    AtimXORInput    = 1u,         /*!<  IA0 ETR GATE XOR(TIM0/1/2)/IA0 IA1 IA2 XOR(TIM3) */   
}en_atim_m1_mscr_ia0s_t;

/**
 * @brief PWC IB0选择数据类型重定义 (IA0S)(模式1)
 */
typedef enum
{
    AtimIB0Input    = 0u,         /*!<  IBO输入 */   
    AtimTsInput     = 1u,         /*!<  内部触发TS选择信号 */   
}en_atim_m1_mscr_ib0s_t;

/**
 * @brief 输出极性、输入相位 数据类型重定义 (CCPA0/CCPB0/ETP/BKP)(模式1/23)
 */
typedef enum
{
    AtimPortPositive      = 0u,         /*!<  正常输入输出 */   
    AtimPortOpposite      = 1u,         /*!<  反向输入输出 */   
}en_atim_port_polarity_t;

/**
 * @brief 滤波选择数据类型重定义 (FLTET/FLTA0/FLAB0)(模式1/23)
 */
typedef enum
{
    AtimFltNone          = 0u,         /*!<  无滤波 */   
    AtimFltPCLKCnt3      = 4u,         /*!<  PCLK 3个连续有效 */   
    AtimFltPCLKDiv4Cnt3  = 5u,         /*!<  PCLK/4 3个连续有效 */   
    AtimFltPCLKDiv16Cnt3 = 6u,         /*!<  PCLK/16 3个连续有效 */   
    AtimFltPCLKDiv64Cnt3 = 7u,         /*!<  PCLK/64 3个连续有效 */   
}en_atim_flt_t;

/**
 * @brief 通道比较控制 数据类型重定义 (OCMA/OCMB)(模式23)
 */
typedef enum
{
    AtimForceLow      = 0u,         /*!<  强制为0 */   
    AtimForceHigh     = 1u,         /*!<  强制为1 */   
    AtimCMPForceLow   = 2u,         /*!<  比较匹配时强制为0 */   
    AtimCMPForceHigh  = 3u,         /*!<  比较匹配时强制为1 */   
    AtimCMPInverse    = 4u,         /*!<  比较匹配时翻转电平 */   
    AtimCMPOnePrdHigh = 5u,         /*!<  比较匹配时输出一个计数周期的高电平 */   
    AtimPWMMode1      = 6u,         /*!<  通道控制为PWM mode 1 */   
    AtimPWMMode2      = 7u,         /*!<  通道控制为PWM mode 2 */   
}en_atim_m23_fltr_ocm_t;

/**
 * @brief 主从模式TS数据类型重定义 (TS)(模式1/23)
 */
typedef enum
{
    AtimTs0ETR        = 0u,         /*!<  ETR外部输入滤波后的相位选择信号 */
    AtimTs1TIM0TRGO   = 1u,         /*!<  Timer0的TRGO输出信号 */
    AtimTs2TIM1TRGO   = 2u,         /*!<  Timer1的TRGO输出信号 */
    AtimTs3TIM2TRGO   = 3u,         /*!<  Timer2的TRGO输出信号 */
    AtimTs4TIM3TRGO   = 4u,         /*!<  Timer3的TRGO输出信号 */
    AtimTs5IA0ED      = 5u,         /*!<  CH0A的边沿信号 (模式1无效) */
    AtimTs6IAFP       = 6u,         /*!<  CH0A 外部输输入滤波后的相位选择信号 */
    AtimTs7IBFP       = 7u,         /*!<  CH0B 外部输输入滤波后的相位选择信 */
}en_atim_mscr_ts_t;

/**
 * @brief PWM输出模式选择数据类型重定义 (COMP)(模式23)
 */
typedef enum
{
    AtimIndependentPWM      = 0u,         /*!<  独立PWM输出 */   
    AtimComplementaryPWM    = 1u,         /*!<  互补PWM输出 */   
}en_atim_m23cr_comp_t;

/**
 * @brief 计数方向选择数据类型重定义 (DIR)(模式23)
 */
typedef enum
{
    AtimCntUp      = 0u,         /*!<  向上计数 */   
    AtimCntDown    = 1u,         /*!<  向下计数 */   
}en_atim_m23cr_dir_t;

/**
 * @brief 计数方向选择数据类型重定义 (PWM2S)(模式23)
 */
typedef enum
{
    AtimDoublePointCmp      = 0u,         /*!<  双点比较使能, 使用CCRA,CCRB比较控制OCREFA输出 */   
    AtimSinglePointCmp      = 1u,         /*!<  单点比较使能, 使用CCRA比较控制OCREFA输出 */   
}en_atim_m23cr_pwm2s_t;

/**
 * @brief GATE在PWM互补模式下捕获或比较功能 选择数据类型重定义 (CSG)(模式23)
 */
typedef enum
{
     AtimPWMCompGateCmpOut    = 0u,         /*!<  在PWM互补模式下, Gate作为比较输出 */   
     AtimPWMCompGateCapIn     = 1u,         /*!<  在PWM互补模式下, Gate作为捕获输入 */   
}en_atim_m23cr_csg_t;


/**
 * @brief 比较捕获寄存器 数据类型重定义 (CCR0A,CCR0B)(模式23)
 */
typedef enum
{
     AtimCCR0A    = 0u,         /*!<  CCR0A比较捕获寄存器 */   
     AtimCCR0B    = 1u,         /*!<  CCR0B比较捕获寄存器 */   
}en_atim_m23_ccrx_t;

/**
 * @brief  OCREF清除源 选择数据类型重定义 (OCCS)(模式23)
 */
typedef enum
{
     AtimOC_Ref_Clr  = 0u,         /*!<  来自VC的OC_Ref_Clr */   
     AtimETRf        = 1u,         /*!<  外部ETRf */   
}en_atim_m23ce_occs_t;

/**
 * @brief  比较匹配中断模式 选择数据类型重定义 (CIS/CISB)(模式23)
 */
typedef enum
{
     AtimCmpIntNone        = 0u,         /*!<  无比较匹配中断 */   
     AtimCmpIntRise        = 1u,         /*!<  比较匹配上升沿中断 */   
     AtimCmpIntFall        = 2u,         /*!<  比较匹配下降沿中断 */   
     AtimCmpIntRiseFall    = 3u,         /*!<  比较匹配上升沿下降沿中断 */   
}en_atim_m23_cisa_cisb_t;

/**
 * @brief ATIM012端口控制 - 刹车时CHx输出状态控制(BKSA/BKSB)(模式23)
 */
typedef enum
{
    AtimCHxBksHiZ         = 0u,         /*!<  刹车使能时, CHx端口输出高阻态 */   
    AtimCHxBksNorm        = 1u,         /*!<  刹车使能时, CHx端口正常输出 */   
    AtimCHxBksLow         = 2u,         /*!<  刹车使能时, CHx端口输出低电平 */   
    AtimCHxBksHigh        = 3u,         /*!<  刹车使能时, CHx端口输出高电平 */   
}en_atim_m23_crch0_bks_t;

/**
 * @brief ATIM012端口控制 - CHx上升沿下降沿捕获(CRx/CFx)(模式23)
 */
typedef enum
{
    AtimCHxCapNone        = 0u,         /*!<  CHx通道捕获禁止 */   
    AtimCHxCapRise        = 1u,         /*!<  CHx通道上升沿捕获使能 */   
    AtimCHxCapFall        = 2u,         /*!<  CHx通道下降沿捕获使能 */   
    AtimCHxCapFallRise    = 3u,         /*!<  CHx通道上升沿下降沿捕获都使能 */   
}en_atim_m23_crch0_cfx_crx_t;

/**
 * @brief ATIM012端口控制 - CHx比较捕获模式(CSA/CSB)(模式23)
 */
typedef enum
{
    AtimCHxCmpMode        = 0u,         /*!<  CHx通道设置为比较模式 */   
    AtimCHxCapMode        = 1u,         /*!<  CHx通道设置为捕获模式 */   
}en_atim_m23_crch0_csa_csb_t;

/**
 * @brief  比较模式下 DMA比较触发选择 数据类型重定义 (CCDS)(模式23)
 */
typedef enum
{
     AtimCmpTrigDMA  = 0u,         /*!<  比较匹配触发DMA */   
     AtimUEVTrigDMA  = 1u,         /*!<  事件更新代替比较匹配触发DMA */   
}en_atim_m23_mscr_ccds_t;

/**
 * @brief  主从模式选择 数据类型重定义 (MSM)(模式23)
 */
typedef enum
{
     AtimSlaveMode    = 0u,         /*!<  从模式 */   
     AtimMasterMode   = 1u,         /*!<  主模式 */   
}en_atim_m23_mscr_msm_t;

/**
 * @brief  触发主模式输出源 数据类型重定义 (MMS)(模式23)
 */
typedef enum
{
     AtimMasterUG         = 0u,         /*!<  UG(软件更新)源 */   
     AtimMasterCTEN       = 1u,         /*!<  CTEN源 */   
     AtimMasterUEV        = 2u,         /*!<  UEV更新源 */   
     AtimMasterCMPSO      = 3u,         /*!<  比较匹配选择输出源 */   
     AtimMasterOCA0Ref    = 4u,         /*!<  OCA0_Ref源 */   
     AtimMasterOCB0Ref    = 7u,         /*!<  OCB0_Ref源 */   
}en_atim_m23_mscr_mms_t;

/**
 * @brief  触发从模式选择 数据类型重定义 (SMS)(模式23)
 */
typedef enum
{
     AtimSlaveIClk        = 0u,         /*!<  使用内部时钟 */   
     AtimSlaveResetTIM    = 1u,         /*!<  复位功能 */   
     AtimSlaveTrigMode    = 2u,         /*!<  触发模式 */   
     AtimSlaveEClk        = 3u,         /*!<  外部时钟模式 */   
     AtimSlaveCodeCnt1    = 4u,         /*!<  正交编码计数模式1 */   
     AtimSlaveCodeCnt2    = 5u,         /*!<  正交编码计数模式2 */   
     AtimSlaveCodeCnt3    = 6u,         /*!<  正交编码计数模式3 */   
     AtimSlaveGateCtrl    = 7u,         /*!<  门控功能 */   
}en_atim_m23_mscr_sms_t;

/**
 * @brief 定时器运行控制数据类型重定义 (CTEN)
 */
typedef enum
{
    AtimCTENDisable = 0u,            /*!<  停止 */   
    AtimCTENEnable  = 1u,            /*!<  运行 */   
}en_atim_start_t;

/**
 * @brief BaseTimer mode0 配置结构体定义(模式0)
 */
typedef struct
{
    en_atim_work_mode_t     enWorkMode;       /*!<  工作模式设置 */   
    en_atim_m0_gatep_t      enGateP;          /*!<  门控极性控制 */   
    boolean_t               bEnGate;          /*!<  门控使能 */   
    en_atim_cr_timclkdiv_t  enPRS;            /*!<  预除频配置 */   
    boolean_t               bEnTog;           /*!<  翻转输出使能 */   
    en_atim_cr_ct_t         enCT;             /*!<  定时/计数功能选择 */   
    en_atim_m0cr_md_t       enCntMode;        /*!<  计数模式配置 */   
}stc_atim_mode0_cfg_t;

/**
 * @brief BaseTimer mode1 配置结构体定义(模式1)
 */
typedef struct
{
    en_atim_work_mode_t     enWorkMode;       /*!<  工作模式设置 */   
    en_atim_cr_timclkdiv_t  enPRS;            /*!<  预除频配置 */   
    en_atim_cr_ct_t         enCT;             /*!<  定时/计数功能选择 */   
    en_atim_m1cr_oneshot_t  enOneShot;        /*!<  单次测量/循环测量选择 */   
}stc_atim_mode1_cfg_t;

/**
 * @brief PWC输入配置结构体定义(模式1)
 */
typedef struct
{
    en_atim_mscr_ts_t          enTsSel;       /*!<  触发输入源选择 */   
    en_atim_m1_mscr_ia0s_t     enIA0Sel;      /*!<  CHA0输入选择 */   
    en_atim_m1_mscr_ib0s_t     enIB0Sel;      /*!<  CHB0输入选择 */   
    en_atim_port_polarity_t    enETRPhase;    /*!<  ETR相位选择 */   
    en_atim_flt_t              enFltETR;      /*!<  ETR滤波设置 */   
    en_atim_flt_t              enFltIA0;      /*!<  CHA0滤波设置 */   
    en_atim_flt_t              enFltIB0;      /*!<  CHB0滤波设置 */   
}stc_atim_pwc_input_cfg_t;

/**
 * @brief BaseTimer mode23 配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_work_mode_t         enWorkMode;       /*!<  工作模式设置 */   
    en_atim_m23cr_dir_t         enCntDir;         /*!<  计数方向 */   
    en_atim_cr_timclkdiv_t      enPRS;            /*!<  时钟预除频配置 */   
    en_atim_cr_ct_t             enCT;             /*!<  定时/计数功能选择 */   
    en_atim_m23cr_comp_t        enPWMTypeSel;     /*!<  PWM模式选择（独立/互补） */   
    en_atim_m23cr_pwm2s_t       enPWM2sSel;       /*!<  OCREFA双点比较功能选择 */   
    boolean_t                   bOneShot;         /*!<  单次触发模式使能/禁止 */   
    boolean_t                   bURSSel;          /*!<  更新源选择 */   
}stc_atim_mode23_cfg_t;

/**
 * @brief GATE在PWM互补模式下捕获或比较功能 配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_m23cr_csg_t        enGateFuncSel;      /*!<  Gate比较、捕获功能选择 */   
    boolean_t                  bGateRiseCap;       /*!<  GATE作为捕获功能时，上沿捕获有效控制 */   
    boolean_t                  bGateFallCap;       /*!<  GATE作为捕获功能时，下沿捕获有效控制 */   
}stc_atim_m23_gate_cfg_t;

/**
 * @brief CHA/CHB通道比较控制 配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_m23_crch0_csa_csb_t  enCh0ACmpCap;     /*!<  CH0A比较/捕获功能选择 */   
    en_atim_m23_fltr_ocm_t       enCH0ACmpCtrl;    /*!<  CH0A通道比较控制 */   
    en_atim_port_polarity_t      enCH0APolarity;   /*!<  CH0A输出极性控制 */   
    boolean_t                    bCh0ACmpBufEn;    /*!<  比较A缓存功能 使能/禁止 */   
    en_atim_m23_cisa_cisb_t      enCh0ACmpIntSel;  /*!<  CHA比较匹配中断选择 */   
    
    en_atim_m23_crch0_csa_csb_t  enCh0BCmpCap;     /*!<  CH0B比较/捕获功能选择 */   
    en_atim_m23_fltr_ocm_t       enCH0BCmpCtrl;    /*!<  CH0B通道比较控制 */   
    en_atim_port_polarity_t      enCH0BPolarity;   /*!<  CH0B输出极性控制 */   
    boolean_t                    bCH0BCmpBufEn;    /*!<  比较B缓存功能 使能/禁止 */   
    en_atim_m23_cisa_cisb_t      enCH0BCmpIntSel;  /*!<  CHB0比较匹配中断选择 */   
}stc_atim_m23_compare_cfg_t;

/**
 * @brief CHA/CHB通道捕获控制 配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_m23_crch0_csa_csb_t  enCh0ACmpCap;     /*!<  CH0A比较/捕获功能选择 */   
    en_atim_m23_crch0_cfx_crx_t  enCH0ACapSel;     /*!<  CH0A捕获边沿选择 */   
    en_atim_flt_t                enCH0AInFlt;      /*!<  CH0A通道捕获滤波控制 */   
    en_atim_port_polarity_t      enCH0APolarity;   /*!<  CH0A输入相位 */   
    
    en_atim_m23_crch0_csa_csb_t  enCh0BCmpCap;     /*!<  CH0B比较/捕获功能选择 */   
    en_atim_m23_crch0_cfx_crx_t  enCH0BCapSel;     /*!<  HC0B捕获边沿选择 */   
    en_atim_flt_t                enCH0BInFlt;      /*!<  CH0B通道捕获滤波控制 */   
    en_atim_port_polarity_t      enCH0BPolarity;   /*!<  CH0B输入相位 */   
    
}stc_atim_m23_input_cfg_t;   

/**
 * @brief ETR输入相位滤波配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_port_polarity_t     enETRPolarity;  /*!<  ETR输入极性设置 */   
    en_atim_flt_t               enETRFlt;       /*!<  ETR滤波设置 */   
}stc_atim_m23_etr_input_cfg_t;

/**
 * @brief 刹车BK输入相位滤波配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t                   bEnBrake;         /*!<  刹车使能 */   
    boolean_t                   bEnVCBrake;       /*!<  使能VC0刹车 */   
    boolean_t                   bEnSafetyBk;      /*!<  使能safety刹车 */   
    boolean_t                   bEnBKSync;        /*!<  TIM0/TIM1/TIM2刹车同步使能 */   
    en_atim_m23_crch0_bks_t     enBkCH0AStat;     /*!<  刹车时CHA端口状态设置 */   
    en_atim_m23_crch0_bks_t     enBkCH0BStat;     /*!<  刹车时CHB端口状态设置 */   
    en_atim_port_polarity_t     enBrakePolarity;  /*!<  刹车BK输入极性设置 */   
    en_atim_flt_t               enBrakeFlt;       /*!<  刹车BK滤波设置 */   
}stc_atim_m23_bk_input_cfg_t;

/**
* @brief 死区功能配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t       bEnDeadTime;      /*!<  刹车时CHA端口状态设置 */   
    uint8_t         u8DeadTimeValue;  /*!<  刹车时CHA端口状态设置 */   
}stc_atim_m23_dt_cfg_t;

/**
 * @brief 触发ADC配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t     bEnTrigADC;          /*!<  触发ADC全局控制 */   
    boolean_t     bEnUevTrigADC;       /*!<  事件更新触发ADC */   
    boolean_t     bEnCH0ACmpTrigADC;   /*!<  CH0A比较匹配触发ADC */   
    boolean_t     bEnCH0BCmpTrigADC;   /*!<  CH0B比较匹配触发ADC */   
}stc_atim_m23_adc_trig_cfg_t;

/**
 * @brief  DMA触发 配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t                bUevTrigDMA;      /*!<  更新 触发DMA使能 */   
    boolean_t                bTITrigDMA;       /*!<  Trig 触发DMA功能 */   
    boolean_t                bCmpATrigDMA;     /*!<  A捕获比较触发DMA使能 */   
    boolean_t                bCmpBTrigDMA;     /*!<  B捕获比较触发DMA使能 */   
    en_atim_m23_mscr_ccds_t  enCmpUevTrigDMA;  /*!<  比较模式下DMA比较触发选择 */   
}stc_atim_m23_trig_dma_cfg_t;

/**
 * @brief  主从模式 配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_m23_mscr_msm_t      enMasterSlaveSel;  /*!<  主从模式选择 */   
    en_atim_m23_mscr_mms_t      enMasterSrc;       /*!<  主模式触发源选择 */   
    en_atim_m23_mscr_sms_t      enSlaveModeSel;    /*!<  从模式选择 */   
    en_atim_mscr_ts_t           enTsSel;           /*!<  触发输入源选择 */   
}stc_atim_m23_master_slave_cfg_t;

/**
 * @brief  OCREF清除功能 配置结构体定义(模式23)
 */
typedef struct
{
    en_atim_m23ce_occs_t       enOCRefClrSrcSel;  /*!<  OCREF清除源选择 */   
    boolean_t                  bVCClrEn;          /*!<  是否使能来自VC的OCREF_Clr */   
}stc_atim_m23_OCREF_Clr_cfg_t;

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
 * @addtogroup ATIM012_Global_Functions ATIM012全局函数定义
 * @{
 */
boolean_t Atim_GetIntFlag(en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq);
en_result_t Atim_ClearIntFlag(en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq);
en_result_t Atim_ClearAllIntFlag(en_atim_unit_t enUnit);
en_result_t Atim_Mode0_EnableIrq(en_atim_unit_t enUnit);
en_result_t Atim_Mode0_DisableIrq(en_atim_unit_t enUnit);
en_result_t Atim_Mode1_EnableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq);
en_result_t Atim_Mode1_DisableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq);
en_result_t Atim_Mode23_EnableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq);
en_result_t Atim_Mode23_DisableIrq (en_atim_unit_t enUnit, en_atim_irq_type_t enAtimIrq);
en_result_t Atim_Mode0_Init(en_atim_unit_t enUnit, stc_atim_mode0_cfg_t* pstcCfg);
en_result_t Atim_M0_Run(en_atim_unit_t enUnit);
en_result_t Atim_M0_Stop(en_atim_unit_t enUnit);
en_result_t Atim_M0_ARRSet(en_atim_unit_t enUnit, uint16_t u16Data);
en_result_t Atim_M0_Cnt16Set(en_atim_unit_t enUnit, uint16_t u16Data);
uint16_t Atim_M0_Cnt16Get(en_atim_unit_t enUnit);
en_result_t Atim_M0_Cnt32Set(en_atim_unit_t enUnit, uint32_t u32Data);
uint32_t Atim_M0_Cnt32Get(en_atim_unit_t enUnit);
en_result_t Atim_M0_EnTOG_Output(en_atim_unit_t enUnit, boolean_t bEnTOG);
en_result_t Atim_M0_Enable_Output(en_atim_unit_t enUnit, boolean_t bEnOutput);
en_result_t Atim_Mode1_Init(en_atim_unit_t enUnit, stc_atim_mode1_cfg_t* pstcCfg);
en_result_t Atim_M1_Input_Cfg(en_atim_unit_t enUnit, stc_atim_pwc_input_cfg_t* pstcCfg);
en_result_t Atim_M1_PWC_Edge_Sel(en_atim_unit_t enUnit,en_atim_m1cr_Edge_t enEdgeSel);
en_result_t Atim_M1_Run(en_atim_unit_t enUnit);
en_result_t Atim_M1_Stop(en_atim_unit_t enUnit);
en_result_t Atim_M1_Cnt16Set(en_atim_unit_t enUnit, uint16_t u16Data);
uint16_t Atim_M1_Cnt16Get(en_atim_unit_t enUnit);
uint16_t Atim_M1_PWC_CapValueGet(en_atim_unit_t enUnit);
en_result_t Atim_Mode23_Init(en_atim_unit_t enUnit, stc_atim_mode23_cfg_t* pstcCfg);
en_result_t Atim_M23_Run(en_atim_unit_t enUnit);
en_result_t Atim_M23_Stop(en_atim_unit_t enUnit);
en_result_t Atim_M23_EnPWM_Output(en_atim_unit_t enUnit, boolean_t bEnOutput, boolean_t bEnAutoOutput);
en_result_t Atim_M23_ARRSet(en_atim_unit_t enUnit, uint16_t u16Data, boolean_t bArrBufEn);
en_result_t Atim_M23_Cnt16Set(en_atim_unit_t enUnit, uint16_t u16Data);
uint16_t Atim_M23_Cnt16Get(en_atim_unit_t enUnit);
en_result_t Atim_M23_CCR_Set(en_atim_unit_t enUnit, en_atim_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Atim_M23_CCR_Get(en_atim_unit_t enUnit, en_atim_m23_ccrx_t enCCRSel);
en_result_t Atim_M23_GateFuncSel(en_atim_unit_t enUnit,stc_atim_m23_gate_cfg_t* pstcCfg);
en_result_t Atim_M23_MasterSlave_Set(en_atim_unit_t enUnit, stc_atim_m23_master_slave_cfg_t* pstcCfg);
en_result_t Atim_M23_PortOutput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_compare_cfg_t* pstcCfg);
en_result_t Atim_M23_PortInput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_input_cfg_t* pstcCfg);
en_result_t Atim_M23_ETRInput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_etr_input_cfg_t* pstcCfg);
en_result_t Atim_M23_BrakeInput_Cfg(en_atim_unit_t enUnit, stc_atim_m23_bk_input_cfg_t* pstcCfg);
en_result_t Atim_M23_TrigADC_Cfg(en_atim_unit_t enUnit, stc_atim_m23_adc_trig_cfg_t* pstcCfg);
en_result_t Atim_M23_DT_Cfg(en_atim_unit_t enUnit, stc_atim_m23_dt_cfg_t* pstcCfg);
en_result_t Atim_M23_SetValidPeriod(en_atim_unit_t enUnit, uint8_t u8ValidPeriod, boolean_t bOVMaskEn, boolean_t bUDMaskEn);
en_result_t Atim_M23_OCRefClr(en_atim_unit_t enUnit, stc_atim_m23_OCREF_Clr_cfg_t* pstcCfg);
en_result_t Atim_M23_EnDMA(en_atim_unit_t enUnit, stc_atim_m23_trig_dma_cfg_t* pstcCfg);
en_result_t Atim_M23_EnSwTrigCapCmpA(en_atim_unit_t enUnit);
en_result_t Atim_M23_EnSwTrigCapCmpB(en_atim_unit_t enUnit);
en_result_t Atim_M23_EnSwUev(en_atim_unit_t enUnit);
en_result_t Atim_M23_EnSwTrig(en_atim_unit_t enUnit);
en_result_t Atim_M23_EnSwBk(en_atim_unit_t enUnit);
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


#endif /* __atim_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


