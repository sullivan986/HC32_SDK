/**
 *******************************************************************************
 * @file  driver.h
 * @brief HC32F005 驱动库 - 聚合头文件 (声明/类型/宏) [自动生成, 勿手改]
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

#ifndef __HC32F005_DRIVER_H__
#define __HC32F005_DRIVER_H__

/******************************************************************************/
/* 板级配置 (外部相关, 按「机制/策略」分层)
 *
 * 驱动中的时钟计算 (sysctrl.c) 必须知道板上实际焊接的晶振频率, 故自动包含
 * 同目录下的 config.h.
 *
 *   config.h       板级配置「机制」: Config 类型 / 预设 / 校验 (HAL 提供)
 *   board_config.h 板级配置「策略」: 晶振频率 + 生效配置 (app 提供)
 *                  config.h 会自动 #include 它 (若在 include path 上)
 *
 * 若确实不用 board_config.h, 也可用编译选项传入:
 *   -DSYSTEM_XTH=<值>
 *   -DHC32_BOARD_CONFIG=::hc32::board::<预设名>
 */
/******************************************************************************/
#if defined(__has_include)
#  if __has_include("config.h")
#    include "config.h"
#  endif
#endif
#if !defined(SYSTEM_XTH)
#  error "SYSTEM_XTH 未定义: 请在 app 的 inc 目录创建 board_config.h, 给出外部高速晶振频率(Hz)"
#endif


/* ========================================================================== */
/*  系统头                                                                       */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

/* ========================================================================== */
/*  基础类型 (base_types.h)                                                       */
/* ========================================================================== */

/******************************************************************************/
/** \file base_types.h
 **
 ** base type common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2019-03-01  1.0  Lux First version.
 **
 ******************************************************************************/


/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/


/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#ifndef TRUE
  /** Value is true (boolean_t type) */
  #define TRUE        ((boolean_t) 1u)
#endif

#ifndef FALSE
  /** Value is false (boolean_t type) */
  #define FALSE       ((boolean_t) 0u)
#endif

/** Returns the minimum value out of two values */
#define MINIMUM( X, Y )  ((X) < (Y) ? (X) : (Y))

/** Returns the maximum value out of two values */
#define MAXIMUM( X, Y )  ((X) > (Y) ? (X) : (Y))

/** Returns the dimension of an array */
#define ARRAY_SZ( X )  (sizeof(X) / sizeof((X)[0]))

#ifdef __DEBUG_ASSERT
    #define ASSERT(x) do{ assert((x)> 0u) ; }while(0);
#else
    #define ASSERT(x) {}
#endif
/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/** logical datatype (only values are TRUE and FALSE) */
typedef uint8_t      boolean_t;

/** single precision floating point number (4 byte) */
typedef float        float32_t;

/** double precision floating point number (8 byte) */
typedef double       float64_t;

/** ASCII character for string generation (8 bit) */
typedef char         char_t;

/** function pointer type to void/void function */
typedef void         (*func_ptr_t)(void);

/** function pointer type to void/uint8_t function */
typedef void         (*func_ptr_arg1_t)(uint8_t u8Param);

/** generic error codes */
typedef enum en_result
{
    Ok                          = 0u,  ///< No error
    Error                       = 1u,  ///< Non-specific error code
    ErrorAddressAlignment       = 2u,  ///< Address alignment does not match
    ErrorAccessRights           = 3u,  ///< Wrong mode (e.g. user/system) mode is set
    ErrorInvalidParameter       = 4u,  ///< Provided parameter is not valid
    ErrorOperationInProgress    = 5u,  ///< A conflicting or requested operation is still in progress
    ErrorInvalidMode            = 6u,  ///< Operation not allowed in current mode
    ErrorUninitialized          = 7u,  ///< Module (or part of it) was not initialized properly
    ErrorBufferFull             = 8u,  ///< Circular buffer can not be written because the buffer is full
    ErrorTimeout                = 9u,  ///< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.)
    ErrorNotReady               = 10u, ///< A requested final state is not reached
    OperationInProgress         = 11u  ///< Indicator for operation in progress
} en_result_t;

/* ========================================================================== */
/*  CMSIS 内核配置 + 中断号 (hc32f005.h 前置段, 必须早于内核核心头)                              */
/* ========================================================================== */

/******************************************************************************/
/** \\file HC32F005.h
**
** Auto generate.
** Headerfile for HC32F005 series MCU
**
** History:
**
**   - 2019-06-30  0.1   Lux First version.
**
******************************************************************************/



/******************************************************************************
* Configuration of the Cortex-M0P Processor and Core Peripherals
******************************************************************************/
#define __MPU_PRESENT           0 /* No MPU                                       */
#define __NVIC_PRIO_BITS        2 /* M0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0 /* Set to 1 if different SysTick Config is used */

/******************************************************************************
* Interrupt Number Definition
******************************************************************************/
typedef enum IRQn
{
    NMI_IRQn            = -14, /*  2 Non Maskable                            */
    HardFault_IRQn      = -13, /*  3 Hard Fault                              */
    SVC_IRQn            = -5,  /* 11 SV Call                                 */
    PendSV_IRQn         = -2,  /* 14 Pend SV                                 */
    SysTick_IRQn        = -1,  /* 15 System Tick                             */

    PORT0_IRQn          = 0 ,
    PORT1_IRQn          = 1 ,
    PORT2_IRQn          = 2 ,
    PORT3_IRQn          = 3 ,
    UART0_IRQn          = 6 ,
    UART1_IRQn          = 7 ,
    SPI_IRQn            = 10,
    I2C_IRQn            = 12,
    TIM0_IRQn           = 14,
    TIM1_IRQn           = 15,
    TIM2_IRQn           = 16,
    ADTIM4_IRQn         = 18,
    ADTIM5_IRQn         = 19,
    ADTIM6_IRQn         = 20,
    PCA_IRQn            = 21,
    WDT_IRQn            = 22,
    ADC_IRQn            = 24,
    VC0_IRQn            = 26,
    VC1_IRQn            = 27,
    LVD_IRQn            = 28,
    FLASH_RAM_IRQn      = 30,
    CLKTRIM_IRQn        = 31,


} IRQn_Type;


#include <core_cm0plus.h>
#include <stdint.h>

/* ========================================================================== */
/*  器件寄存器 / 位定义 / 外设基址 (hc32f005.h)                                           */
/* ========================================================================== */


#define SUCCESS         (0)
#define ERROR           (-1)

#ifndef NULL
#define NULL            (0)
#endif


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    __IO uint32_t ADCEN                     : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t CLKSEL                    : 2;
    __IO uint32_t SEL                       : 4;
    __IO uint32_t SREF                      : 2;
    __IO uint32_t BUFEN                     : 1;
    __IO uint32_t SAM                       : 2;
    uint32_t RESERVED13                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t STATERST                  : 1;
} stc_adc_cr0_field_t;

typedef struct
{
    __IO uint32_t TRIGS0                    : 5;
    __IO uint32_t TRIGS1                    : 5;
    __IO uint32_t CT                        : 1;
    __IO uint32_t RACC_EN                   : 1;
    __IO uint32_t LTCMP                     : 1;
    __IO uint32_t HTCMP                     : 1;
    __IO uint32_t REGCMP                    : 1;
    __IO uint32_t RACC_CLR                  : 1;
} stc_adc_cr1_field_t;

typedef struct
{
    __IO uint32_t CH0EN                     : 1;
    __IO uint32_t CH1EN                     : 1;
    __IO uint32_t CH2EN                     : 1;
    __IO uint32_t CH3EN                     : 1;
    __IO uint32_t CH4EN                     : 1;
    __IO uint32_t CH5EN                     : 1;
    __IO uint32_t CH6EN                     : 1;
    __IO uint32_t CH7EN                     : 1;
    __IO uint32_t ADCCNT                    : 8;
} stc_adc_cr2_field_t;

typedef struct
{
    __IO uint32_t RESULT0                   :12;
} stc_adc_result0_field_t;

typedef struct
{
    __IO uint32_t RESULT1                   :12;
} stc_adc_result1_field_t;

typedef struct
{
    __IO uint32_t RESULT2                   :12;
} stc_adc_result2_field_t;

typedef struct
{
    __IO uint32_t RESULT3                   :12;
} stc_adc_result3_field_t;

typedef struct
{
    __IO uint32_t RESULT4                   :12;
} stc_adc_result4_field_t;

typedef struct
{
    __IO uint32_t RESULT5                   :12;
} stc_adc_result5_field_t;

typedef struct
{
    __IO uint32_t RESULT6                   :12;
} stc_adc_result6_field_t;

typedef struct
{
    __IO uint32_t RESULT7                   :12;
} stc_adc_result7_field_t;

typedef struct
{
    __IO uint32_t RESULT8                   :12;
} stc_adc_result8_field_t;

typedef struct
{
    __IO uint32_t RESULT_ACC                :20;
} stc_adc_result_acc_field_t;

typedef struct
{
    __IO uint32_t HT                        :12;
} stc_adc_ht_field_t;

typedef struct
{
    __IO uint32_t LT                        :12;
} stc_adc_lt_field_t;

typedef struct
{
    __IO uint32_t LLT_INTF                  : 1;
    __IO uint32_t HHT_INTF                  : 1;
    __IO uint32_t REG_INTF                  : 1;
    __IO uint32_t CONT_INTF                 : 1;
} stc_adc_ifr_field_t;

typedef struct
{
    __IO uint32_t LLT_INTC                  : 1;
    __IO uint32_t HHT_INTC                  : 1;
    __IO uint32_t REG_INTC                  : 1;
    __IO uint32_t CONT_INTC                 : 1;
} stc_adc_iclr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_result_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_cnter_field_t;

typedef struct
{
    __IO uint32_t PERA                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_perar_field_t;

typedef struct
{
    __IO uint32_t PERB                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_perbr_field_t;

typedef struct
{
    __IO uint32_t GCMA                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_gcmar_field_t;

typedef struct
{
    __IO uint32_t GCMB                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_gcmbr_field_t;

typedef struct
{
    __IO uint32_t GCMC                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_gcmcr_field_t;

typedef struct
{
    __IO uint32_t GCMD                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_gcmdr_field_t;

typedef struct
{
    __IO uint32_t DTUA                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_dtuar_field_t;

typedef struct
{
    __IO uint32_t DTDA                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_dtdar_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 3;
    __IO uint32_t CKDIV                     : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED9                      : 7;
    __IO uint32_t ZMSKREV                   : 1;
    __IO uint32_t ZMSKPOS                   : 1;
    __IO uint32_t ZMSK                      : 2;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_adtim_gconr_field_t;

typedef struct
{
    __IO uint32_t INTENA                    : 1;
    __IO uint32_t INTENB                    : 1;
    __IO uint32_t INTENC                    : 1;
    __IO uint32_t INTEND                    : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INTENOVF                  : 1;
    __IO uint32_t INTENUDF                  : 1;
    __IO uint32_t INTENDE                   : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_adtim_iconr_field_t;

typedef struct
{
    __IO uint32_t CAPCA                     : 1;
    __IO uint32_t STACA                     : 1;
    __IO uint32_t STPCA                     : 1;
    __IO uint32_t STASTPSA                  : 1;
    __IO uint32_t CMPCA                     : 2;
    __IO uint32_t PERCA                     : 2;
    __IO uint32_t OUTENA                    : 1;
    __IO uint32_t DISSELA                   : 2;
    __IO uint32_t DISVALA                   : 2;
    uint32_t RESERVED13                     : 3;
    __IO uint32_t CAPCB                     : 1;
    __IO uint32_t STACB                     : 1;
    __IO uint32_t STPCB                     : 1;
    __IO uint32_t STASTPSB                  : 1;
    __IO uint32_t CMPCB                     : 2;
    __IO uint32_t PERCB                     : 2;
    __IO uint32_t OUTENB                    : 1;
    __IO uint32_t DISSELB                   : 2;
    __IO uint32_t DISVALB                   : 2;
    uint32_t RESERVED29                     : 2;
    __IO uint32_t RSV                       : 1;
} stc_adtim_pconr_field_t;

typedef struct
{
    __IO uint32_t BENA                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t BENB                      : 1;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t BENP                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_adtim_bconr_field_t;

typedef struct
{
    __IO uint32_t DTCEN                     : 1;
    uint32_t RESERVED1                      : 7;
    __IO uint32_t SEPA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_adtim_dconr_field_t;

typedef struct
{
    __IO uint32_t NOFIENGA                  : 1;
    __IO uint32_t NOFICKGA                  : 2;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t NOFIENGB                  : 1;
    __IO uint32_t NOFICKGB                  : 2;
    uint32_t RESERVED7                      : 9;
    __IO uint32_t NOFIENTA                  : 1;
    __IO uint32_t NOFICKTA                  : 2;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t NOFIENTB                  : 1;
    __IO uint32_t NOFICKTB                  : 2;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t NOFIENTC                  : 1;
    __IO uint32_t NOFICKTC                  : 2;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t NOFIENTD                  : 1;
    __IO uint32_t NOFICKTD                  : 2;
    __IO uint32_t RSV                       : 1;
} stc_adtim_fconr_field_t;

typedef struct
{
    __IO uint32_t GEPERIA                   : 1;
    __IO uint32_t GEPERIB                   : 1;
    __IO uint32_t GEPERIC                   : 1;
    __IO uint32_t GEPERID                   : 1;
    uint32_t RESERVED4                      :12;
    __IO uint32_t PCNTE                     : 2;
    __IO uint32_t PCNTS                     : 3;
    uint32_t RESERVED21                     :10;
    __IO uint32_t RSV                       : 1;
} stc_adtim_vperr_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      :12;
    __IO uint32_t VPERNUM                   : 3;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t DIRF                      : 1;
} stc_adtim_stflr_field_t;

typedef struct
{
    __IO uint32_t HSTA0                     : 1;
    __IO uint32_t HSTA1                     : 1;
    __IO uint32_t HSTA2                     : 1;
    __IO uint32_t HSTA3                     : 1;
    __IO uint32_t HSTA4                     : 1;
    __IO uint32_t HSTA5                     : 1;
    __IO uint32_t HSTA6                     : 1;
    __IO uint32_t HSTA7                     : 1;
    __IO uint32_t HSTA8                     : 1;
    __IO uint32_t HSTA9                     : 1;
    __IO uint32_t HSTA10                    : 1;
    __IO uint32_t HSTA11                    : 1;
    __IO uint32_t HSTA12                    : 1;
    __IO uint32_t HSTA13                    : 1;
    __IO uint32_t HSTA14                    : 1;
    __IO uint32_t HSTA15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_adtim_hstar_field_t;

typedef struct
{
    __IO uint32_t HSTP0                     : 1;
    __IO uint32_t HSTP1                     : 1;
    __IO uint32_t HSTP2                     : 1;
    __IO uint32_t HSTP3                     : 1;
    __IO uint32_t HSTP4                     : 1;
    __IO uint32_t HSTP5                     : 1;
    __IO uint32_t HSTP6                     : 1;
    __IO uint32_t HSTP7                     : 1;
    __IO uint32_t HSTP8                     : 1;
    __IO uint32_t HSTP9                     : 1;
    __IO uint32_t HSTP10                    : 1;
    __IO uint32_t HSTP11                    : 1;
    __IO uint32_t HSTP12                    : 1;
    __IO uint32_t HSTP13                    : 1;
    __IO uint32_t HSTP14                    : 1;
    __IO uint32_t HSTP15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STOPS                     : 1;
} stc_adtim_hstpr_field_t;

typedef struct
{
    __IO uint32_t HCEL0                     : 1;
    __IO uint32_t HCEL1                     : 1;
    __IO uint32_t HCEL2                     : 1;
    __IO uint32_t HCEL3                     : 1;
    __IO uint32_t HCEL4                     : 1;
    __IO uint32_t HCEL5                     : 1;
    __IO uint32_t HCEL6                     : 1;
    __IO uint32_t HCEL7                     : 1;
    __IO uint32_t HCEL8                     : 1;
    __IO uint32_t HCEL9                     : 1;
    __IO uint32_t HCEL10                    : 1;
    __IO uint32_t HCEL11                    : 1;
    __IO uint32_t HCEL12                    : 1;
    __IO uint32_t HCEL13                    : 1;
    __IO uint32_t HCEL14                    : 1;
    __IO uint32_t HCEL15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t CLEARS                    : 1;
} stc_adtim_hcelr_field_t;

typedef struct
{
    __IO uint32_t HCPA0                     : 1;
    __IO uint32_t HCPA1                     : 1;
    __IO uint32_t HCPA2                     : 1;
    __IO uint32_t HCPA3                     : 1;
    __IO uint32_t HCPA4                     : 1;
    __IO uint32_t HCPA5                     : 1;
    __IO uint32_t HCPA6                     : 1;
    __IO uint32_t HCPA7                     : 1;
    __IO uint32_t HCPA8                     : 1;
    __IO uint32_t HCPA9                     : 1;
    __IO uint32_t HCPA10                    : 1;
    __IO uint32_t HCPA11                    : 1;
    __IO uint32_t HCPA12                    : 1;
    __IO uint32_t HCPA13                    : 1;
    __IO uint32_t HCPA14                    : 1;
    __IO uint32_t HCPA15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_hcpar_field_t;

typedef struct
{
    __IO uint32_t HCPB0                     : 1;
    __IO uint32_t HCPB1                     : 1;
    __IO uint32_t HCPB2                     : 1;
    __IO uint32_t HCPB3                     : 1;
    __IO uint32_t HCPB4                     : 1;
    __IO uint32_t HCPB5                     : 1;
    __IO uint32_t HCPB6                     : 1;
    __IO uint32_t HCPB7                     : 1;
    __IO uint32_t HCPB8                     : 1;
    __IO uint32_t HCPB9                     : 1;
    __IO uint32_t HCPB10                    : 1;
    __IO uint32_t HCPB11                    : 1;
    __IO uint32_t HCPB12                    : 1;
    __IO uint32_t HCPB13                    : 1;
    __IO uint32_t HCPB14                    : 1;
    __IO uint32_t HCPB15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_hcpbr_field_t;

typedef struct
{
    __IO uint32_t HCUP0                     : 1;
    __IO uint32_t HCUP1                     : 1;
    __IO uint32_t HCUP2                     : 1;
    __IO uint32_t HCUP3                     : 1;
    __IO uint32_t HCUP4                     : 1;
    __IO uint32_t HCUP5                     : 1;
    __IO uint32_t HCUP6                     : 1;
    __IO uint32_t HCUP7                     : 1;
    __IO uint32_t HCUP8                     : 1;
    __IO uint32_t HCUP9                     : 1;
    __IO uint32_t HCUP10                    : 1;
    __IO uint32_t HCUP11                    : 1;
    __IO uint32_t HCUP12                    : 1;
    __IO uint32_t HCUP13                    : 1;
    __IO uint32_t HCUP14                    : 1;
    __IO uint32_t HCUP15                    : 1;
    __IO uint32_t HCUP16                    : 1;
    __IO uint32_t HCUP17                    : 1;
    __IO uint32_t HCUP18                    : 1;
    __IO uint32_t HCUP19                    : 1;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_adtim_hcupr_field_t;

typedef struct
{
    __IO uint32_t HCDO0                     : 1;
    __IO uint32_t HCDO1                     : 1;
    __IO uint32_t HCDO2                     : 1;
    __IO uint32_t HCDO3                     : 1;
    __IO uint32_t HCDO4                     : 1;
    __IO uint32_t HCDO5                     : 1;
    __IO uint32_t HCDO6                     : 1;
    __IO uint32_t HCDO7                     : 1;
    __IO uint32_t HCDO8                     : 1;
    __IO uint32_t HCDO9                     : 1;
    __IO uint32_t HCDO10                    : 1;
    __IO uint32_t HCDO11                    : 1;
    __IO uint32_t HCDO12                    : 1;
    __IO uint32_t HCDO13                    : 1;
    __IO uint32_t HCDO14                    : 1;
    __IO uint32_t HCDO15                    : 1;
    __IO uint32_t HCDO16                    : 1;
    __IO uint32_t HCDO17                    : 1;
    __IO uint32_t HCDO18                    : 1;
    __IO uint32_t HCDO19                    : 1;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_adtim_hcdor_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLF                     : 1;
    __IO uint32_t SAMHF                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_ifr_field_t;

typedef struct
{
    __IO uint32_t CMAC                      : 1;
    __IO uint32_t CMBC                      : 1;
    __IO uint32_t CMCC                      : 1;
    __IO uint32_t CMDC                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFC                      : 1;
    __IO uint32_t UDFC                      : 1;
    __IO uint32_t DTEC                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLC                     : 1;
    __IO uint32_t SAMHC                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_iclr_field_t;

typedef struct
{
    __IO uint32_t CMAE                      : 1;
    __IO uint32_t CMBE                      : 1;
    __IO uint32_t CMCE                      : 1;
    __IO uint32_t CMDE                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFE                      : 1;
    __IO uint32_t UDFE                      : 1;
    __IO uint32_t DITENA                    : 1;
    __IO uint32_t DITENB                    : 1;
    __IO uint32_t DITENS                    : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_adtim_cr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
    __IO uint32_t BFILTS                    : 2;
    __IO uint32_t BFILTEN                   : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t SOFTBK                    : 1;
    __IO uint32_t SML0                      : 1;
    __IO uint32_t SML1                      : 1;
    __IO uint32_t SML2                      : 1;
    __IO uint32_t SMH0                      : 1;
    __IO uint32_t SMH1                      : 1;
    __IO uint32_t SMH2                      : 1;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_adtim_aossr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_adtim_aoscl_field_t;

typedef struct
{
    __IO uint32_t EN0                       : 1;
    __IO uint32_t EN1                       : 1;
    __IO uint32_t EN2                       : 1;
    __IO uint32_t EN3                       : 1;
    __IO uint32_t EN4                       : 1;
    __IO uint32_t EN5                       : 1;
    __IO uint32_t EN6                       : 1;
    __IO uint32_t EN7                       : 1;
    __IO uint32_t EN8                       : 1;
    __IO uint32_t EN9                       : 1;
    __IO uint32_t EN10                      : 1;
    __IO uint32_t EN11                      : 1;
    __IO uint32_t EN12                      : 1;
    __IO uint32_t EN13                      : 1;
    __IO uint32_t EN14                      : 1;
    __IO uint32_t EN15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_ptbks_field_t;

typedef struct
{
    __IO uint32_t TRIGAS                    : 4;
    __IO uint32_t TRIGBS                    : 4;
    __IO uint32_t TRIGCS                    : 4;
    __IO uint32_t TRIGDS                    : 4;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_ttrig_field_t;

typedef struct
{
    __IO uint32_t IAOS0S                    : 4;
    __IO uint32_t IAOS1S                    : 4;
    __IO uint32_t IAOS2S                    : 4;
    __IO uint32_t IAOS3S                    : 4;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_itrig_field_t;

typedef struct
{
    __IO uint32_t POL0                      : 1;
    __IO uint32_t POL1                      : 1;
    __IO uint32_t POL2                      : 1;
    __IO uint32_t POL3                      : 1;
    __IO uint32_t POL4                      : 1;
    __IO uint32_t POL5                      : 1;
    __IO uint32_t POL6                      : 1;
    __IO uint32_t POL7                      : 1;
    __IO uint32_t POL8                      : 1;
    __IO uint32_t POL9                      : 1;
    __IO uint32_t POL10                     : 1;
    __IO uint32_t POL11                     : 1;
    __IO uint32_t POL12                     : 1;
    __IO uint32_t POL13                     : 1;
    __IO uint32_t POL14                     : 1;
    __IO uint32_t POL15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adtim_ptbkp_field_t;

typedef struct
{
    __IO uint32_t SSTA0                     : 1;
    __IO uint32_t SSTA1                     : 1;
    __IO uint32_t SSTA2                     : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_adtim_sstar_field_t;

typedef struct
{
    __IO uint32_t SSTP0                     : 1;
    __IO uint32_t SSTP1                     : 1;
    __IO uint32_t SSTP2                     : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_adtim_sstpr_field_t;

typedef struct
{
    __IO uint32_t SCLR0                     : 1;
    __IO uint32_t SCLR1                     : 1;
    __IO uint32_t SCLR2                     : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_adtim_sclrr_field_t;

typedef struct
{
    __IO uint32_t BGR_EN                    : 1;
    __IO uint32_t TS_EN                     : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_bgr_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM_START                : 1;
    __IO uint32_t REFCLK_SEL                : 3;
    __IO uint32_t CALCLK_SEL                : 2;
    __IO uint32_t MON_EN                    : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_clk_trim_cr_field_t;

typedef struct
{
    __IO uint32_t RCNTVAL                   :32;
} stc_clk_trim_refcon_field_t;

typedef struct
{
    __IO uint32_t REFCNT                    :32;
} stc_clk_trim_refcnt_field_t;

typedef struct
{
    __IO uint32_t CALCNT                    :32;
} stc_clk_trim_calcnt_field_t;

typedef struct
{
    __IO uint32_t STOP                      : 1;
    __IO uint32_t CALCNT_OF                 : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t XTH_FAULT                 : 1;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_clk_trim_ifr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t XTH_FAULT_CLR             : 1;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_clk_trim_iclr_field_t;

typedef struct
{
    __IO uint32_t CCNTVAL                   :32;
} stc_clk_trim_calcon_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    __IO uint32_t FLAG                      : 1;
} stc_crc_result_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_crc_data_field_t;

typedef struct
{
    __IO uint32_t TIM0                      : 1;
    __IO uint32_t TIM1                      : 1;
    __IO uint32_t TIM2                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t WDT                       : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t TIM3                      : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_debug_active_field_t;

typedef struct
{
    __IO uint32_t TNVS                      : 9;
    __IO uint32_t RSV                       :23;
} stc_flash_tnvs_field_t;

typedef struct
{
    __IO uint32_t TPGS                      : 8;
    __IO uint32_t RSV                       :24;
} stc_flash_tpgs_field_t;

typedef struct
{
    __IO uint32_t TPROG                     : 8;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t RSV                       :23;
} stc_flash_tprog_field_t;

typedef struct
{
    __IO uint32_t TSERASE                   :18;
    __IO uint32_t RSV                       :14;
} stc_flash_tserase_field_t;

typedef struct
{
    __IO uint32_t TMERASE                   :21;
    __IO uint32_t RSV                       :11;
} stc_flash_tmerase_field_t;

typedef struct
{
    __IO uint32_t TPRCV                     :12;
    __IO uint32_t RSV                       :20;
} stc_flash_tprcv_field_t;

typedef struct
{
    __IO uint32_t TSRCV                     :12;
    __IO uint32_t RSV                       :20;
} stc_flash_tsrcv_field_t;

typedef struct
{
    __IO uint32_t TMRCV                     :13;
    uint32_t RESERVED13                     : 1;
    __IO uint32_t RSV                       :18;
} stc_flash_tmrcv_field_t;

typedef struct
{
    __IO uint32_t OP                        : 2;
    __IO uint32_t WAIT                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t IE                        : 2;
    uint32_t RESERVED7                      : 3;
    __IO uint32_t RSV                       :22;
} stc_flash_cr_field_t;

typedef struct
{
    __IO uint32_t IF0                       : 1;
    __IO uint32_t IF1                       : 1;
    __IO uint32_t RSV                       :30;
} stc_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t ICLR0                     : 1;
    __IO uint32_t ICLR1                     : 1;
    __IO uint32_t RSV                       :30;
} stc_flash_iclr_field_t;

typedef struct
{
    __IO uint32_t BYSEQ                     :16;
    __IO uint32_t RSV                       :16;
} stc_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :16;
} stc_flash_slock_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p23_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p24_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p25_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p26_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p27_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p31_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p32_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p33_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p34_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p35_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p36_sel_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0dir_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0od_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0hie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0lie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0rie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0fie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1dir_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1od_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1hie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1lie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1rie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1fie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2dir_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2od_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2hie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2lie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2rie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2fie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3dir_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3od_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3hie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3lie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3rie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3fie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0stat_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3iclr_field_t;

typedef struct
{
    __IO uint32_t IESEL                     : 1;
} stc_gpio_ctrl0_field_t;

typedef struct
{
    __IO uint32_t EXT_CLK_SEL               : 4;
    __IO uint32_t SSN_SEL                   : 4;
    __IO uint32_t PCLK_SEL                  : 2;
    __IO uint32_t HCLK_SEL                  : 2;
    __IO uint32_t PCLK_EN                   : 1;
    __IO uint32_t HCLK_EN                   : 1;
    __IO uint32_t IR_POL                    : 1;
} stc_gpio_ctrl1_field_t;

typedef struct
{
    __IO uint32_t PCA_CAP0_SEL              : 2;
    __IO uint32_t PCA_CAP1_SEL              : 2;
    __IO uint32_t PCA_CAP2_SEL              : 2;
    __IO uint32_t PCA_CAP3_SEL              : 2;
    __IO uint32_t PCA_CAP4_SEL              : 2;
} stc_gpio_ctrl2_field_t;

typedef struct
{
    __IO uint32_t TM4_B_SEL                 : 2;
    __IO uint32_t TM5_B_SEL                 : 2;
    __IO uint32_t TM6_B_SEL                 : 2;
    __IO uint32_t TM4_A_SEL                 : 2;
    __IO uint32_t TM5_A_SEL                 : 2;
    __IO uint32_t TM6_A_SEL                 : 2;
} stc_gpio_ctrl3_field_t;

typedef struct
{
    __IO uint32_t TM0_GATE_SEL              : 2;
    __IO uint32_t TM1_GATE_SEL              : 2;
    __IO uint32_t TM2_GATE_SEL              : 2;
    __IO uint32_t TM3_GATE_SEL              : 2;
} stc_gpio_ctrl4_field_t;

typedef struct
{
    __IO uint32_t TME                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_i2c_tmrun_field_t;

typedef struct
{
    __IO uint32_t TM                        : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_tm_field_t;

typedef struct
{
    __IO uint32_t H1M                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t AA                        : 1;
    __IO uint32_t SI                        : 1;
    __IO uint32_t STO                       : 1;
    __IO uint32_t STA                       : 1;
    __IO uint32_t ENS                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_i2c_cr_field_t;

typedef struct
{
    __IO uint32_t DAT                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_data_field_t;

typedef struct
{
    __IO uint32_t GC                        : 1;
    __IO uint32_t ADR                       : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr_field_t;

typedef struct
{
    __IO uint32_t STA                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_stat_field_t;

typedef struct
{
    __IO uint32_t LVDEN                     : 1;
    __IO uint32_t ACT                       : 1;
    __IO uint32_t SOURCE_SEL                : 2;
    __IO uint32_t VTDS                      : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FTEN                      : 1;
    __IO uint32_t RTEN                      : 1;
    __IO uint32_t HTEN                      : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lvd_cr_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lvd_ifr_field_t;

typedef struct
{
    __IO uint32_t CCF0                      : 1;
    __IO uint32_t CCF1                      : 1;
    __IO uint32_t CCF2                      : 1;
    __IO uint32_t CCF3                      : 1;
    __IO uint32_t CCF4                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t CR                        : 1;
    __IO uint32_t CF                        : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccon_field_t;

typedef struct
{
    __IO uint32_t CFIE                      : 1;
    __IO uint32_t CPS                       : 3;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t WDTE                      : 1;
    __IO uint32_t CIDL                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_cmod_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_pca_cnt_field_t;

typedef struct
{
    __IO uint32_t CCF0                      : 1;
    __IO uint32_t CCF1                      : 1;
    __IO uint32_t CCF2                      : 1;
    __IO uint32_t CCF3                      : 1;
    __IO uint32_t CCF4                      : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t CF                        : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_iclr_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccapm0_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccapm1_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccapm2_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccapm3_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccapm4_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap0h_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap0l_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap1h_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap1l_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap2h_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap2l_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap3h_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap3l_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap4h_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap4l_field_t;

typedef struct
{
    __IO uint32_t CCAPO0                    : 1;
    __IO uint32_t CCAPO1                    : 1;
    __IO uint32_t CCAPO2                    : 1;
    __IO uint32_t CCAPO3                    : 1;
    __IO uint32_t CCAPO4                    : 1;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccapo_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap0_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap1_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap2_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap3_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_pca_ccap4_field_t;

typedef struct
{
    __IO uint32_t CHKEN                     : 1;
    __IO uint32_t IE                        : 1;
} stc_ram_cr_field_t;

typedef struct
{
    __IO uint32_t ERRADDR                   :12;
} stc_ram_erraddr_field_t;

typedef struct
{
    __IO uint32_t ERR                       : 1;
} stc_ram_ifr_field_t;

typedef struct
{
    __IO uint32_t ERRCLR                    : 1;
} stc_ram_iclr_field_t;

typedef struct
{
    __IO uint32_t POR5V                     : 1;
    __IO uint32_t POR15V                    : 1;
    __IO uint32_t LVD                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t LOCKUP                    : 1;
    __IO uint32_t SYSREQ                    : 1;
    __IO uint32_t RSTB                      : 1;
} stc_reset_flag_field_t;

typedef struct
{
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t I2C                       : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPI                       : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BASETIM                   : 1;
    uint32_t RESERVED9                      : 1;
    __IO uint32_t ADVTIM                    : 1;
    uint32_t RESERVED11                     : 3;
    __IO uint32_t PCA                       : 1;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    uint32_t RESERVED18                     : 3;
    __IO uint32_t TRIM                      : 1;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t TICK                      : 1;
    uint32_t RESERVED25                     : 1;
    __IO uint32_t CRC                       : 1;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t GPIO                      : 1;
} stc_reset_peri_field_t;

typedef struct
{
    __IO uint32_t SPR0                      : 1;
    __IO uint32_t SPR1                      : 1;
    __IO uint32_t CPHA                      : 1;
    __IO uint32_t CPOL                      : 1;
    __IO uint32_t MSTR                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPEN                      : 1;
    __IO uint32_t SPR2                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr_field_t;

typedef struct
{
    __IO uint32_t SSN                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_ssn_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t MDF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t WCOL                      : 1;
    __IO uint32_t SPIF                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_stat_field_t;

typedef struct
{
    __IO uint32_t DAT                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_data_field_t;

typedef struct
{
    __IO uint32_t RCH_EN                    : 1;
    __IO uint32_t XTH_EN                    : 1;
    __IO uint32_t RCL_EN                    : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t CLKSW                     : 2;
    __IO uint32_t HCLK_PRS                  : 3;
    __IO uint32_t PCLK_PRS                  : 2;
    uint32_t RESERVED11                     : 4;
    __IO uint32_t WAKEUP_BYRCH              : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t EXTH_EN                   : 1;
    __IO uint32_t EXTL_EN                   : 1;
    __IO uint32_t XTL_ALWAYS_ON             : 1;
    __IO uint32_t CLOCK_FT_EN               : 1;
    __IO uint32_t RTC_LPW                   : 1;
    __IO uint32_t LOCKUP_EN                 : 1;
    __IO uint32_t RES_UIO                   : 1;
    __IO uint32_t SWD_USE_IO                : 1;
    __IO uint32_t RTC_FREQ_ADJUST           : 3;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl1_field_t;

typedef struct
{
    __IO uint32_t SYSCTRL2                  :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl2_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :11;
    __IO uint32_t STABLE                    : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rch_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t XTH_FSEL                  : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xth_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :10;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rcl_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t AMP_SEL                   : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xtl_cr_field_t;

typedef struct
{
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t I2C                       : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPI                       : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BASETIM                   : 1;
    uint32_t RESERVED9                      : 1;
    __IO uint32_t ADVTIM                    : 1;
    uint32_t RESERVED11                     : 3;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    uint32_t RESERVED18                     : 3;
    __IO uint32_t TRIM                      : 1;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t TICK                      : 1;
    uint32_t RESERVED25                     : 1;
    __IO uint32_t CRC                       : 1;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t GPIO                      : 1;
    uint32_t RESERVED29                     : 2;
    __IO uint32_t FLASH                     : 1;
} stc_sysctrl_peri_clken_field_t;

typedef struct
{
    __IO uint32_t STCALIB                   :24;
    __IO uint32_t SKEW                      : 1;
    __IO uint32_t NOREF                     : 1;
    __IO uint32_t CLK_SEL                   : 2;
} stc_sysctrl_systick_cr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_tim_cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim_iclr_field_t;

typedef struct
{
    __IO uint32_t SBUF                      : 8;
} stc_uart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RIEN                      : 1;
    __IO uint32_t TIEN                      : 1;
    __IO uint32_t RB8                       : 1;
    __IO uint32_t TB8                       : 1;
    __IO uint32_t REN                       : 1;
    __IO uint32_t SM2                       : 1;
    __IO uint32_t SM01                      : 2;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t DBAUD                     : 1;
} stc_uart_scon_field_t;

typedef struct
{
    __IO uint32_t SADDR                     : 8;
} stc_uart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
} stc_uart_saden_field_t;

typedef struct
{
    __IO uint32_t RI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TE                        : 1;
} stc_uart_isr_field_t;

typedef struct
{
    __IO uint32_t RICLR                     : 1;
    __IO uint32_t TICLR                     : 1;
    __IO uint32_t FECLR                     : 1;
} stc_uart_icr_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIV_EN                    : 1;
    __IO uint32_t REF2P5_SEL                : 1;
    __IO uint32_t VC0_BIAS_SEL              : 2;
    __IO uint32_t VC0_HYS_SEL               : 2;
    __IO uint32_t VC1_BIAS_SEL              : 2;
    __IO uint32_t VC1_HYS_SEL               : 2;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t P_SEL                     : 3;
    __IO uint32_t N_SEL                     : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc0_cr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t P_SEL                     : 3;
    __IO uint32_t N_SEL                     : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc1_cr_field_t;

typedef struct
{
    __IO uint32_t INV_TIMER                 : 1;
    __IO uint32_t TIM0G                     : 1;
    __IO uint32_t TIM1G                     : 1;
    __IO uint32_t TIM2G                     : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INV_PCA                   : 1;
    __IO uint32_t PCACAP0                   : 1;
    __IO uint32_t PCAECI                    : 1;
    __IO uint32_t INV_TIM4                  : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t INV_TIM5                  : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t INV_TIM6                  : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t BRAKE                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc0_out_cfg_field_t;

typedef struct
{
    __IO uint32_t INV_TIMER                 : 1;
    __IO uint32_t TIM0G                     : 1;
    __IO uint32_t TIM1G                     : 1;
    __IO uint32_t TIM2G                     : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INV_PCA                   : 1;
    __IO uint32_t PCACAP0                   : 1;
    __IO uint32_t PCAECI                    : 1;
    __IO uint32_t INV_TIM4                  : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t INV_TIM5                  : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t INV_TIM6                  : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t BRAKE                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_vc_vc1_out_cfg_field_t;

typedef struct
{
    __IO uint32_t VC0_INTF                  : 1;
    __IO uint32_t VC1_INTF                  : 1;
    __IO uint32_t VC0_FILTER                : 1;
    __IO uint32_t VC1_FILTER                : 1;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_vc_ifr_field_t;

typedef struct
{
    __IO uint32_t RST                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_wdt_rst_field_t;

typedef struct
{
    __IO uint32_t WOV                       : 4;
    __IO uint32_t R                         : 1;
    __IO uint32_t WINT_EN                   : 1;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t INT                       : 1;
    __IO uint32_t WCNTL                     : 8;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_wdt_con_field_t;


typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CR0;
        stc_adc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_adc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_adc_cr2_field_t CR2_f;
    };
    uint8_t RESERVED3[32];
    union
    {
        __IO uint32_t RESULT0;
        stc_adc_result0_field_t RESULT0_f;
    };
    union
    {
        __IO uint32_t RESULT1;
        stc_adc_result1_field_t RESULT1_f;
    };
    union
    {
        __IO uint32_t RESULT2;
        stc_adc_result2_field_t RESULT2_f;
    };
    union
    {
        __IO uint32_t RESULT3;
        stc_adc_result3_field_t RESULT3_f;
    };
    union
    {
        __IO uint32_t RESULT4;
        stc_adc_result4_field_t RESULT4_f;
    };
    union
    {
        __IO uint32_t RESULT5;
        stc_adc_result5_field_t RESULT5_f;
    };
    union
    {
        __IO uint32_t RESULT6;
        stc_adc_result6_field_t RESULT6_f;
    };
    union
    {
        __IO uint32_t RESULT7;
        stc_adc_result7_field_t RESULT7_f;
    };
    union
    {
        __IO uint32_t RESULT8;
        stc_adc_result8_field_t RESULT8_f;
    };
    union
    {
        __IO uint32_t RESULT_ACC;
        stc_adc_result_acc_field_t RESULT_ACC_f;
    };
    union
    {
        __IO uint32_t HT;
        stc_adc_ht_field_t HT_f;
    };
    union
    {
        __IO uint32_t LT;
        stc_adc_lt_field_t LT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_adc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_adc_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_adc_result_field_t RESULT_f;
    };
}M0P_ADC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNTER;
        stc_adtim_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;
        stc_adtim_perar_field_t PERAR_f;
    };
    union
    {
        __IO uint32_t PERBR;
        stc_adtim_perbr_field_t PERBR_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t GCMAR;
        stc_adtim_gcmar_field_t GCMAR_f;
    };
    union
    {
        __IO uint32_t GCMBR;
        stc_adtim_gcmbr_field_t GCMBR_f;
    };
    union
    {
        __IO uint32_t GCMCR;
        stc_adtim_gcmcr_field_t GCMCR_f;
    };
    union
    {
        __IO uint32_t GCMDR;
        stc_adtim_gcmdr_field_t GCMDR_f;
    };
    uint8_t RESERVED7[32];
    union
    {
        __IO uint32_t DTUAR;
        stc_adtim_dtuar_field_t DTUAR_f;
    };
    union
    {
        __IO uint32_t DTDAR;
        stc_adtim_dtdar_field_t DTDAR_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t GCONR;
        stc_adtim_gconr_field_t GCONR_f;
    };
    union
    {
        __IO uint32_t ICONR;
        stc_adtim_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t PCONR;
        stc_adtim_pconr_field_t PCONR_f;
    };
    union
    {
        __IO uint32_t BCONR;
        stc_adtim_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t DCONR;
        stc_adtim_dconr_field_t DCONR_f;
    };
    uint8_t RESERVED14[4];
    union
    {
        __IO uint32_t FCONR;
        stc_adtim_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t VPERR;
        stc_adtim_vperr_field_t VPERR_f;
    };
    union
    {
        __IO uint32_t STFLR;
        stc_adtim_stflr_field_t STFLR_f;
    };
    union
    {
        __IO uint32_t HSTAR;
        stc_adtim_hstar_field_t HSTAR_f;
    };
    union
    {
        __IO uint32_t HSTPR;
        stc_adtim_hstpr_field_t HSTPR_f;
    };
    union
    {
        __IO uint32_t HCELR;
        stc_adtim_hcelr_field_t HCELR_f;
    };
    union
    {
        __IO uint32_t HCPAR;
        stc_adtim_hcpar_field_t HCPAR_f;
    };
    union
    {
        __IO uint32_t HCPBR;
        stc_adtim_hcpbr_field_t HCPBR_f;
    };
    union
    {
        __IO uint32_t HCUPR;
        stc_adtim_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;
        stc_adtim_hcdor_field_t HCDOR_f;
    };
    uint8_t RESERVED24[112];
    union
    {
        __IO uint32_t IFR;
        stc_adtim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_adtim_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_adtim_cr_field_t CR_f;
    };
    uint8_t RESERVED27[4];
    union
    {
        __IO uint32_t AOSSR;
        stc_adtim_aossr_field_t AOSSR_f;
    };
    union
    {
        __IO uint32_t AOSCL;
        stc_adtim_aoscl_field_t AOSCL_f;
    };
    union
    {
        __IO uint32_t PTBKS;
        stc_adtim_ptbks_field_t PTBKS_f;
    };
    union
    {
        __IO uint32_t TTRIG;
        stc_adtim_ttrig_field_t TTRIG_f;
    };
    union
    {
        __IO uint32_t ITRIG;
        stc_adtim_itrig_field_t ITRIG_f;
    };
    union
    {
        __IO uint32_t PTBKP;
        stc_adtim_ptbkp_field_t PTBKP_f;
    };
    uint8_t RESERVED33[716];
    union
    {
        __IO uint32_t SSTAR;
        stc_adtim_sstar_field_t SSTAR_f;
    };
    union
    {
        __IO uint32_t SSTPR;
        stc_adtim_sstpr_field_t SSTPR_f;
    };
    union
    {
        __IO uint32_t SCLRR;
        stc_adtim_sclrr_field_t SCLRR_f;
    };
}M0P_ADTIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_bgr_cr_field_t CR_f;
    };
}M0P_BGR_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_clk_trim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t REFCON;
        stc_clk_trim_refcon_field_t REFCON_f;
    };
    union
    {
        __IO uint32_t REFCNT;
        stc_clk_trim_refcnt_field_t REFCNT_f;
    };
    union
    {
        __IO uint32_t CALCNT;
        stc_clk_trim_calcnt_field_t CALCNT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_clk_trim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_clk_trim_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CALCON;
        stc_clk_trim_calcon_field_t CALCON_f;
    };
}M0P_CLK_TRIM_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t RESULT;
        stc_crc_result_field_t RESULT_f;
    };
    uint8_t RESERVED1[120];
    union
    {
        __IO uint32_t DATA;
        stc_crc_data_field_t DATA_f;
    };
}M0P_CRC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t DEBUG_ACTIVE;
        stc_debug_active_field_t DEBUG_ACTIVE_f;
    };
}M0P_DEBUG_ACTIVE_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TNVS;
        stc_flash_tnvs_field_t TNVS_f;
    };
    union
    {
        __IO uint32_t TPGS;
        stc_flash_tpgs_field_t TPGS_f;
    };
    union
    {
        __IO uint32_t TPROG;
        stc_flash_tprog_field_t TPROG_f;
    };
    union
    {
        __IO uint32_t TSERASE;
        stc_flash_tserase_field_t TSERASE_f;
    };
    union
    {
        __IO uint32_t TMERASE;
        stc_flash_tmerase_field_t TMERASE_f;
    };
    union
    {
        __IO uint32_t TPRCV;
        stc_flash_tprcv_field_t TPRCV_f;
    };
    union
    {
        __IO uint32_t TSRCV;
        stc_flash_tsrcv_field_t TSRCV_f;
    };
    union
    {
        __IO uint32_t TMRCV;
        stc_flash_tmrcv_field_t TMRCV_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_flash_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_flash_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_flash_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t BYPASS;
        stc_flash_bypass_field_t BYPASS_f;
    };
    union
    {
        __IO uint32_t SLOCK;
        stc_flash_slock_field_t SLOCK_f;
    };
}M0P_FLASH_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t P01_SEL;
        stc_gpio_p01_sel_field_t P01_SEL_f;
    };
    union
    {
        __IO uint32_t P02_SEL;
        stc_gpio_p02_sel_field_t P02_SEL_f;
    };
    union
    {
        __IO uint32_t P03_SEL;
        stc_gpio_p03_sel_field_t P03_SEL_f;
    };
    uint8_t RESERVED3[64];
    union
    {
        __IO uint32_t P14_SEL;
        stc_gpio_p14_sel_field_t P14_SEL_f;
    };
    union
    {
        __IO uint32_t P15_SEL;
        stc_gpio_p15_sel_field_t P15_SEL_f;
    };
    uint8_t RESERVED5[52];
    union
    {
        __IO uint32_t P23_SEL;
        stc_gpio_p23_sel_field_t P23_SEL_f;
    };
    union
    {
        __IO uint32_t P24_SEL;
        stc_gpio_p24_sel_field_t P24_SEL_f;
    };
    union
    {
        __IO uint32_t P25_SEL;
        stc_gpio_p25_sel_field_t P25_SEL_f;
    };
    union
    {
        __IO uint32_t P26_SEL;
        stc_gpio_p26_sel_field_t P26_SEL_f;
    };
    union
    {
        __IO uint32_t P27_SEL;
        stc_gpio_p27_sel_field_t P27_SEL_f;
    };
    uint8_t RESERVED10[36];
    union
    {
        __IO uint32_t P31_SEL;
        stc_gpio_p31_sel_field_t P31_SEL_f;
    };
    union
    {
        __IO uint32_t P32_SEL;
        stc_gpio_p32_sel_field_t P32_SEL_f;
    };
    union
    {
        __IO uint32_t P33_SEL;
        stc_gpio_p33_sel_field_t P33_SEL_f;
    };
    union
    {
        __IO uint32_t P34_SEL;
        stc_gpio_p34_sel_field_t P34_SEL_f;
    };
    union
    {
        __IO uint32_t P35_SEL;
        stc_gpio_p35_sel_field_t P35_SEL_f;
    };
    union
    {
        __IO uint32_t P36_SEL;
        stc_gpio_p36_sel_field_t P36_SEL_f;
    };
    uint8_t RESERVED16[36];
    union
    {
        __IO uint32_t P0DIR;
        stc_gpio_p0dir_field_t P0DIR_f;
    };
    union
    {
        __IO uint32_t P0IN;
        stc_gpio_p0in_field_t P0IN_f;
    };
    union
    {
        __IO uint32_t P0OUT;
        stc_gpio_p0out_field_t P0OUT_f;
    };
    union
    {
        __IO uint32_t P0ADS;
        stc_gpio_p0ads_field_t P0ADS_f;
    };
    uint8_t RESERVED20[12];
    union
    {
        __IO uint32_t P0DR;
        stc_gpio_p0dr_field_t P0DR_f;
    };
    union
    {
        __IO uint32_t P0PU;
        stc_gpio_p0pu_field_t P0PU_f;
    };
    union
    {
        __IO uint32_t P0PD;
        stc_gpio_p0pd_field_t P0PD_f;
    };
    uint8_t RESERVED23[4];
    union
    {
        __IO uint32_t P0OD;
        stc_gpio_p0od_field_t P0OD_f;
    };
    union
    {
        __IO uint32_t P0HIE;
        stc_gpio_p0hie_field_t P0HIE_f;
    };
    union
    {
        __IO uint32_t P0LIE;
        stc_gpio_p0lie_field_t P0LIE_f;
    };
    union
    {
        __IO uint32_t P0RIE;
        stc_gpio_p0rie_field_t P0RIE_f;
    };
    union
    {
        __IO uint32_t P0FIE;
        stc_gpio_p0fie_field_t P0FIE_f;
    };
    union
    {
        __IO uint32_t P1DIR;
        stc_gpio_p1dir_field_t P1DIR_f;
    };
    union
    {
        __IO uint32_t P1IN;
        stc_gpio_p1in_field_t P1IN_f;
    };
    union
    {
        __IO uint32_t P1OUT;
        stc_gpio_p1out_field_t P1OUT_f;
    };
    union
    {
        __IO uint32_t P1ADS;
        stc_gpio_p1ads_field_t P1ADS_f;
    };
    uint8_t RESERVED32[12];
    union
    {
        __IO uint32_t P1DR;
        stc_gpio_p1dr_field_t P1DR_f;
    };
    union
    {
        __IO uint32_t P1PU;
        stc_gpio_p1pu_field_t P1PU_f;
    };
    union
    {
        __IO uint32_t P1PD;
        stc_gpio_p1pd_field_t P1PD_f;
    };
    uint8_t RESERVED35[4];
    union
    {
        __IO uint32_t P1OD;
        stc_gpio_p1od_field_t P1OD_f;
    };
    union
    {
        __IO uint32_t P1HIE;
        stc_gpio_p1hie_field_t P1HIE_f;
    };
    union
    {
        __IO uint32_t P1LIE;
        stc_gpio_p1lie_field_t P1LIE_f;
    };
    union
    {
        __IO uint32_t P1RIE;
        stc_gpio_p1rie_field_t P1RIE_f;
    };
    union
    {
        __IO uint32_t P1FIE;
        stc_gpio_p1fie_field_t P1FIE_f;
    };
    union
    {
        __IO uint32_t P2DIR;
        stc_gpio_p2dir_field_t P2DIR_f;
    };
    union
    {
        __IO uint32_t P2IN;
        stc_gpio_p2in_field_t P2IN_f;
    };
    union
    {
        __IO uint32_t P2OUT;
        stc_gpio_p2out_field_t P2OUT_f;
    };
    union
    {
        __IO uint32_t P2ADS;
        stc_gpio_p2ads_field_t P2ADS_f;
    };
    uint8_t RESERVED44[12];
    union
    {
        __IO uint32_t P2DR;
        stc_gpio_p2dr_field_t P2DR_f;
    };
    union
    {
        __IO uint32_t P2PU;
        stc_gpio_p2pu_field_t P2PU_f;
    };
    union
    {
        __IO uint32_t P2PD;
        stc_gpio_p2pd_field_t P2PD_f;
    };
    uint8_t RESERVED47[4];
    union
    {
        __IO uint32_t P2OD;
        stc_gpio_p2od_field_t P2OD_f;
    };
    union
    {
        __IO uint32_t P2HIE;
        stc_gpio_p2hie_field_t P2HIE_f;
    };
    union
    {
        __IO uint32_t P2LIE;
        stc_gpio_p2lie_field_t P2LIE_f;
    };
    union
    {
        __IO uint32_t P2RIE;
        stc_gpio_p2rie_field_t P2RIE_f;
    };
    union
    {
        __IO uint32_t P2FIE;
        stc_gpio_p2fie_field_t P2FIE_f;
    };
    union
    {
        __IO uint32_t P3DIR;
        stc_gpio_p3dir_field_t P3DIR_f;
    };
    union
    {
        __IO uint32_t P3IN;
        stc_gpio_p3in_field_t P3IN_f;
    };
    union
    {
        __IO uint32_t P3OUT;
        stc_gpio_p3out_field_t P3OUT_f;
    };
    union
    {
        __IO uint32_t P3ADS;
        stc_gpio_p3ads_field_t P3ADS_f;
    };
    uint8_t RESERVED56[12];
    union
    {
        __IO uint32_t P3DR;
        stc_gpio_p3dr_field_t P3DR_f;
    };
    union
    {
        __IO uint32_t P3PU;
        stc_gpio_p3pu_field_t P3PU_f;
    };
    union
    {
        __IO uint32_t P3PD;
        stc_gpio_p3pd_field_t P3PD_f;
    };
    uint8_t RESERVED59[4];
    union
    {
        __IO uint32_t P3OD;
        stc_gpio_p3od_field_t P3OD_f;
    };
    union
    {
        __IO uint32_t P3HIE;
        stc_gpio_p3hie_field_t P3HIE_f;
    };
    union
    {
        __IO uint32_t P3LIE;
        stc_gpio_p3lie_field_t P3LIE_f;
    };
    union
    {
        __IO uint32_t P3RIE;
        stc_gpio_p3rie_field_t P3RIE_f;
    };
    union
    {
        __IO uint32_t P3FIE;
        stc_gpio_p3fie_field_t P3FIE_f;
    };
    union
    {
        __IO uint32_t P0STAT;
        stc_gpio_p0stat_field_t P0STAT_f;
    };
    uint8_t RESERVED65[12];
    union
    {
        __IO uint32_t P0ICLR;
        stc_gpio_p0iclr_field_t P0ICLR_f;
    };
    uint8_t RESERVED66[44];
    union
    {
        __IO uint32_t P1STAT;
        stc_gpio_p1stat_field_t P1STAT_f;
    };
    uint8_t RESERVED67[12];
    union
    {
        __IO uint32_t P1ICLR;
        stc_gpio_p1iclr_field_t P1ICLR_f;
    };
    uint8_t RESERVED68[44];
    union
    {
        __IO uint32_t P2STAT;
        stc_gpio_p2stat_field_t P2STAT_f;
    };
    uint8_t RESERVED69[12];
    union
    {
        __IO uint32_t P2ICLR;
        stc_gpio_p2iclr_field_t P2ICLR_f;
    };
    uint8_t RESERVED70[44];
    union
    {
        __IO uint32_t P3STAT;
        stc_gpio_p3stat_field_t P3STAT_f;
    };
    uint8_t RESERVED71[12];
    union
    {
        __IO uint32_t P3ICLR;
        stc_gpio_p3iclr_field_t P3ICLR_f;
    };
    uint8_t RESERVED72[44];
    union
    {
        __IO uint32_t CTRL0;
        stc_gpio_ctrl0_field_t CTRL0_f;
    };
    union
    {
        __IO uint32_t CTRL1;
        stc_gpio_ctrl1_field_t CTRL1_f;
    };
    union
    {
        __IO uint32_t CTRL2;
        stc_gpio_ctrl2_field_t CTRL2_f;
    };
    union
    {
        __IO uint32_t CTRL3;
        stc_gpio_ctrl3_field_t CTRL3_f;
    };
    union
    {
        __IO uint32_t CTRL4;
        stc_gpio_ctrl4_field_t CTRL4_f;
    };
}M0P_GPIO_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TMRUN;
        stc_i2c_tmrun_field_t TMRUN_f;
    };
    union
    {
        __IO uint32_t TM;
        stc_i2c_tm_field_t TM_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_i2c_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_i2c_data_field_t DATA_f;
    };
    union
    {
        __IO uint32_t ADDR;
        stc_i2c_addr_field_t ADDR_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_i2c_stat_field_t STAT_f;
    };
}M0P_I2C_TypeDef;

typedef struct
{
    uint8_t RESERVED0[40];
    union
    {
        __IO uint32_t CR;
        stc_lvd_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lvd_ifr_field_t IFR_f;
    };
}M0P_LVD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CCON;
        stc_pca_ccon_field_t CCON_f;
    };
    union
    {
        __IO uint32_t CMOD;
        stc_pca_cmod_field_t CMOD_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_pca_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_pca_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CCAPM0;
        stc_pca_ccapm0_field_t CCAPM0_f;
    };
    union
    {
        __IO uint32_t CCAPM1;
        stc_pca_ccapm1_field_t CCAPM1_f;
    };
    union
    {
        __IO uint32_t CCAPM2;
        stc_pca_ccapm2_field_t CCAPM2_f;
    };
    union
    {
        __IO uint32_t CCAPM3;
        stc_pca_ccapm3_field_t CCAPM3_f;
    };
    union
    {
        __IO uint32_t CCAPM4;
        stc_pca_ccapm4_field_t CCAPM4_f;
    };
    union
    {
        __IO uint32_t CCAP0H;
        stc_pca_ccap0h_field_t CCAP0H_f;
    };
    union
    {
        __IO uint32_t CCAP0L;
        stc_pca_ccap0l_field_t CCAP0L_f;
    };
    union
    {
        __IO uint32_t CCAP1H;
        stc_pca_ccap1h_field_t CCAP1H_f;
    };
    union
    {
        __IO uint32_t CCAP1L;
        stc_pca_ccap1l_field_t CCAP1L_f;
    };
    union
    {
        __IO uint32_t CCAP2H;
        stc_pca_ccap2h_field_t CCAP2H_f;
    };
    union
    {
        __IO uint32_t CCAP2L;
        stc_pca_ccap2l_field_t CCAP2L_f;
    };
    union
    {
        __IO uint32_t CCAP3H;
        stc_pca_ccap3h_field_t CCAP3H_f;
    };
    union
    {
        __IO uint32_t CCAP3L;
        stc_pca_ccap3l_field_t CCAP3L_f;
    };
    union
    {
        __IO uint32_t CCAP4H;
        stc_pca_ccap4h_field_t CCAP4H_f;
    };
    union
    {
        __IO uint32_t CCAP4L;
        stc_pca_ccap4l_field_t CCAP4L_f;
    };
    union
    {
        __IO uint32_t CCAPO;
        stc_pca_ccapo_field_t CCAPO_f;
    };
    union
    {
        __IO uint32_t CCAP0;
        stc_pca_ccap0_field_t CCAP0_f;
    };
    union
    {
        __IO uint32_t CCAP1;
        stc_pca_ccap1_field_t CCAP1_f;
    };
    union
    {
        __IO uint32_t CCAP2;
        stc_pca_ccap2_field_t CCAP2_f;
    };
    union
    {
        __IO uint32_t CCAP3;
        stc_pca_ccap3_field_t CCAP3_f;
    };
    union
    {
        __IO uint32_t CCAP4;
        stc_pca_ccap4_field_t CCAP4_f;
    };
}M0P_PCA_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_ram_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ERRADDR;
        stc_ram_erraddr_field_t ERRADDR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_ram_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_ram_iclr_field_t ICLR_f;
    };
}M0P_RAM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t RESET_FLAG;
        stc_reset_flag_field_t RESET_FLAG_f;
    };
    uint8_t RESERVED1[8];
    union
    {
        __IO uint32_t PERI_RESET;
        stc_reset_peri_field_t PERI_RESET_f;
    };
}M0P_RESET_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_spi_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t SSN;
        stc_spi_ssn_field_t SSN_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_spi_stat_field_t STAT_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_spi_data_field_t DATA_f;
    };
}M0P_SPI_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SYSCTRL0;
        stc_sysctrl_sysctrl0_field_t SYSCTRL0_f;
    };
    union
    {
        __IO uint32_t SYSCTRL1;
        stc_sysctrl_sysctrl1_field_t SYSCTRL1_f;
    };
    union
    {
        __IO uint32_t SYSCTRL2;
        stc_sysctrl_sysctrl2_field_t SYSCTRL2_f;
    };
    union
    {
        __IO uint32_t RCH_CR;
        stc_sysctrl_rch_cr_field_t RCH_CR_f;
    };
    union
    {
        __IO uint32_t XTH_CR;
        stc_sysctrl_xth_cr_field_t XTH_CR_f;
    };
    union
    {
        __IO uint32_t RCL_CR;
        stc_sysctrl_rcl_cr_field_t RCL_CR_f;
    };
    union
    {
        __IO uint32_t XTL_CR;
        stc_sysctrl_xtl_cr_field_t XTL_CR_f;
    };
    uint8_t RESERVED7[4];
    union
    {
        __IO uint32_t PERI_CLKEN;
        stc_sysctrl_peri_clken_field_t PERI_CLKEN_f;
    };
    uint8_t RESERVED8[16];
    union
    {
        __IO uint32_t SYSTICK_CR;
        stc_sysctrl_systick_cr_field_t SYSTICK_CR_f;
    };
}M0P_SYSCTRL_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_tim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim_iclr_field_t ICLR_f;
    };
}M0P_TIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_uart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_uart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_uart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_uart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_uart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_uart_icr_field_t ICR_f;
    };
}M0P_UART_TypeDef;

typedef struct
{
    uint8_t RESERVED0[16];
    union
    {
        __IO uint32_t CR;
        stc_vc_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t VC0_CR;
        stc_vc_vc0_cr_field_t VC0_CR_f;
    };
    union
    {
        __IO uint32_t VC1_CR;
        stc_vc_vc1_cr_field_t VC1_CR_f;
    };
    union
    {
        __IO uint32_t VC0_OUT_CFG;
        stc_vc_vc0_out_cfg_field_t VC0_OUT_CFG_f;
    };
    union
    {
        __IO uint32_t VC1_OUT_CFG;
        stc_vc_vc1_out_cfg_field_t VC1_OUT_CFG_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_vc_ifr_field_t IFR_f;
    };
}M0P_VC_TypeDef;

typedef struct
{
    uint8_t RESERVED0[128];
    union
    {
        __IO uint32_t RST;
        stc_wdt_rst_field_t RST_f;
    };
    union
    {
        __IO uint32_t CON;
        stc_wdt_con_field_t CON_f;
    };
}M0P_WDT_TypeDef;



#define M0P_PERIPH_BASE                        (0x40000000UL)
#define M0P_ADC_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_ADTIM4_BASE                        (M0P_PERIPH_BASE + 0x00003000UL)
#define M0P_ADTIM5_BASE                        (M0P_PERIPH_BASE + 0x00003400UL)
#define M0P_ADTIM6_BASE                        (M0P_PERIPH_BASE + 0x00003800UL)
#define M0P_BGR_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_CLK_TRIM_BASE                      (M0P_PERIPH_BASE + 0x00001800UL)
#define M0P_CRC_BASE                           (M0P_PERIPH_BASE + 0x00020900UL)
#define M0P_DEBUG_ACTIVE_BASE                  (M0P_PERIPH_BASE + 0x00002038UL)
#define M0P_FLASH_BASE                         (M0P_PERIPH_BASE + 0x00020000UL)
#define M0P_GPIO_BASE                          (M0P_PERIPH_BASE + 0x00020C00UL)
#define M0P_I2C_BASE                           (M0P_PERIPH_BASE + 0x00000400UL)
#define M0P_LVD_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_PCA_BASE                           (M0P_PERIPH_BASE + 0x00001000UL)
#define M0P_RAM_BASE                           (M0P_PERIPH_BASE + 0x00020400UL)
#define M0P_RESET_BASE                         (M0P_PERIPH_BASE + 0x0000201CUL)
#define M0P_SPI_BASE                           (M0P_PERIPH_BASE + 0x00000800UL)
#define M0P_SYSCTRL_BASE                       (M0P_PERIPH_BASE + 0x00002000UL)
#define M0P_TIM0_BASE                          (M0P_PERIPH_BASE + 0x00000C00UL)
#define M0P_TIM1_BASE                          (M0P_PERIPH_BASE + 0x00000C20UL)
#define M0P_TIM2_BASE                          (M0P_PERIPH_BASE + 0x00000C40UL)
#define M0P_UART0_BASE                         (M0P_PERIPH_BASE + 0x00000000UL)
#define M0P_UART1_BASE                         (M0P_PERIPH_BASE + 0x00000100UL)
#define M0P_VC_BASE                            (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_WDT_BASE                           (M0P_PERIPH_BASE + 0x00000C00UL)


#define M0P_ADC                                ((M0P_ADC_TypeDef *)0x40002400UL)
#define M0P_ADTIM4                             ((M0P_ADTIM_TypeDef *)0x40003000UL)
#define M0P_ADTIM5                             ((M0P_ADTIM_TypeDef *)0x40003400UL)
#define M0P_ADTIM6                             ((M0P_ADTIM_TypeDef *)0x40003800UL)
#define M0P_BGR                                ((M0P_BGR_TypeDef *)0x40002400UL)
#define M0P_CLK_TRIM                           ((M0P_CLK_TRIM_TypeDef *)0x40001800UL)
#define M0P_CRC                                ((M0P_CRC_TypeDef *)0x40020900UL)
#define M0P_DEBUG_ACTIVE                       ((M0P_DEBUG_ACTIVE_TypeDef *)0x40002038UL)
#define M0P_FLASH                              ((M0P_FLASH_TypeDef *)0x40020000UL)
#define M0P_GPIO                               ((M0P_GPIO_TypeDef *)0x40020C00UL)
#define M0P_I2C                                ((M0P_I2C_TypeDef *)0x40000400UL)
#define M0P_LVD                                ((M0P_LVD_TypeDef *)0x40002400UL)
#define M0P_PCA                                ((M0P_PCA_TypeDef *)0x40001000UL)
#define M0P_RAM                                ((M0P_RAM_TypeDef *)0x40020400UL)
#define M0P_RESET                              ((M0P_RESET_TypeDef *)0x4000201CUL)
#define M0P_SPI                                ((M0P_SPI_TypeDef *)0x40000800UL)
#define M0P_SYSCTRL                            ((M0P_SYSCTRL_TypeDef *)0x40002000UL)
#define M0P_TIM0                               ((M0P_TIM_TypeDef *)0x40000C00UL)
#define M0P_TIM1                               ((M0P_TIM_TypeDef *)0x40000C20UL)
#define M0P_TIM2                               ((M0P_TIM_TypeDef *)0x40000C40UL)
#define M0P_UART0                              ((M0P_UART_TypeDef *)0x40000000UL)
#define M0P_UART1                              ((M0P_UART_TypeDef *)0x40000100UL)
#define M0P_VC                                 ((M0P_VC_TypeDef *)0x40002400UL)
#define M0P_WDT                                ((M0P_WDT_TypeDef *)0x40000C00UL)



/* ========================================================================== */
/*  C 链接区: 以下全部为 C 符号, 供 C / C++ 共用                                           */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*  驱动模块 (driver/inc, 20 个)                                                   */
/* ========================================================================== */

/******************************************************************************/
/** \file adc.h
 **
 ** Header file for AD Converter functions
 ** @link ADC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/



/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/

//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN模式使用ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN模式使用ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN模式使用ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN模式使用ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN模式使用ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN模式使用ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN模式使用ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN模式使用ADC CH7 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

 /**
 ******************************************************************************
 ** \brief ADC采样模式
 *****************************************************************************/
typedef enum en_adc_op_mode
{
    AdcNormalMode  = 0,        /*!< 单输入通道单次采样模式 */
    AdcContMode    = 1,        /*!< 单输入通道连续采样模式 */
    AdcScanMode    = 2,        /*!< 多输入通道扫描采样模式*/

} en_adc_op_mode_t;

/**
 ******************************************************************************
 ** \brief ADC时钟选择
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcClkSysTDiv1  = 0,        /*!< PCLK */
    AdcClkSysTDiv2  = 1,        /*!< 1/2 PCLK */
    AdcClkSysTDiv4  = 2,        /*!< 1/4 PCLK */
    AdcClkSysTDiv8  = 3,        /*!< 1/8 PCLK */

} en_adc_clk_sel_t;

/**
 ******************************************************************************
 ** \brief ADC参考电压
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    RefVolSelInBgr1p5 = 0,        /*!<内部参考电压1.5V(SPS<=200kHz)*/
    RefVolSelInBgr2p5 = 1,        /*!<内部参考电压2.5V(avdd>3V,SPS<=200kHz)*/
    RefVolSelExtern1  = 2,        /*!<外部输入(max avdd)   P3.6*/
    RefVolSelAVDD     = 3,        /*!<AVDD*/

}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADC采样通道选择
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{
    AdcExInputCH0    =  0,        /*!<使用通道0输入P2.4*/
    AdcExInputCH1    =  1,        /*!<使用通道1输入P2.6*/
    AdcExInputCH2    =  2,        /*!<使用通道2输入P3.2*/
    AdcExInputCH3    =  3,        /*!<使用通道3输入P3.3*/
    AdcExInputCH4    =  4,        /*!<使用通道4输入P3.4*/
    AdcExInputCH5    =  5,        /*!<使用通道5输入P3.5*/
    AdcExInputCH6    =  6,        /*!<使用通道6输入P3.6*/
    AdcExInputCH7    =  7,        /*!<使用通道7输入P0.1*/
    AdcExInputCH8    =  8,        /*!<使用通道8输入P0.2*/
    AdcAVccDiV3Input =  9,        /*!<使用1/3 AVCC(必须使用输入增益)*/
    AdcAiTsInput     =  10,       /*!<使用AI_TS(必须使用输入增益)*/
    AdcVref1P2Input  =  11,       /*!<使用Vref1P2(必须使用输入增益)*/

}en_adc_samp_ch_sel_t;

/**
 ******************************************************************************
 ** \brief ADC采样周期数选择
 *****************************************************************************/
typedef enum en_adc_samp_time_sel
{
    AdcSampTime4Clk  =  0,        /*!<4个采样时钟*/
    AdcSampTime6Clk  =  1,        /*!<6个采样时钟*/
    AdcSampTime8Clk  =  2,        /*!<8个采样时钟*/
    AdcSampTime12Clk =  3,        /*!<12个采样时钟*/

}en_adc_samp_time_sel_t;

/**
 ******************************************************************************
 ** \brief ADC周边模块反射源选择
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcTrigDisable    =  0,         /*!<禁用周边模块反射源*/
    AdcTrigTimer0     =  1,         /*!<选择timer0中断源，自动触发ADC采样*/
    AdcTrigTimer1     =  2,         /*!<选择timer1中断源，自动触发ADC采样*/
    AdcTrigTimer2     =  3,         /*!<选择timer2中断源，自动触发ADC采样*/
    AdcTrigLptimer    =  4,         /*!<选择lptimer中断源，自动触发ADC采样*/
    AdcTrigTimer4     =  5,         /*!<选择timer4中断源，自动触发ADC采样*/
    AdcTrigTimer5     =  6,         /*!<选择timer5中断源，自动触发ADC采样*/
    AdcTrigTimer6     =  7,         /*!<选择timer6中断源，自动触发ADC采样*/
    AdcTrigUart0      =  8,         /*!<选择uart0中断源，自动触发ADC采样*/
    AdcTrigUart1      =  9,         /*!<选择uart1中断源，自动触发ADC采样*/
    AdcTrigLpuart     =  10,        /*!<选择lpuart中断源，自动触发ADC采样*/
    AdcTrigVC1        =  11,        /*!<选择VC1中断源，自动触发ADC采样*/
    AdcTrigVC2        =  12,        /*!<选择VC2中断源，自动触发ADC采样*/
    AdcTrigRTC        =  13,        /*!<选择RTC中断源，自动触发ADC采样*/
    AdcTrigPCA        =  14,        /*!<选择PCA中断源，自动触发ADC采样*/
    AdcTrigSPI        =  15,        /*!<选择SPI中断源，自动触发ADC采样*/
    AdcTrigP01        =  16,        /*!<选择P01中断源，自动触发ADC采样*/
    AdcTrigP02        =  17,        /*!<选择P02中断源，自动触发ADC采样*/
    AdcTrigP03        =  18,        /*!<选择P03中断源，自动触发ADC采样*/
    AdcTrigP14        =  19,        /*!<选择P14中断源，自动触发ADC采样*/
    AdcTrigP15        =  20,        /*!<选择P15中断源，自动触发ADC采样*/
    AdcTrigP23        =  21,        /*!<选择P23中断源，自动触发ADC采样*/
    AdcTrigP24        =  22,        /*!<选择P24中断源，自动触发ADC采样*/
    AdcTrigP25        =  23,        /*!<选择P25中断源，自动触发ADC采样*/
    AdcTrigP26        =  24,        /*!<选择P26中断源，自动触发ADC采样*/
    AdcTrigP27        =  25,        /*!<选择P27中断源，自动触发ADC采样*/
    AdcTrigP31        =  26,        /*!<选择P31中断源，自动触发ADC采样*/
    AdcTrigP32        =  27,        /*!<选择P32中断源，自动触发ADC采样*/
    AdcTrigP33        =  28,        /*!<选择P33中断源，自动触发ADC采样*/
    AdcTrigP34        =  29,        /*!<选择P34中断源，自动触发ADC采样*/
    AdcTrigP35        =  30,        /*!<选择P35中断源，自动触发ADC采样*/
    AdcTrigP36        =  31,        /*!<选择P36中断源，自动触发ADC采样*/

}en_adc_trig_sel_t;

/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC配置
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    /*! ADC操作模式*/
    en_adc_op_mode_t enAdcOpMode;

    /*! ADC时钟选择*/
    en_adc_clk_sel_t  enAdcClkSel;

    /*! ADC采样时间*/
    en_adc_samp_time_sel_t  enAdcSampTimeSel;

    /*! ADC参考电压*/
    en_adc_ref_vol_sel_t    enAdcRefVolSel;

    /*! ADC输入增益使能*/
    boolean_t    bAdcInBufEn;

    /*!ADC区间模式上限值*/
    uint32_t    u32AdcRegHighThd;

    /*!ADC区间模式下限值*/
    uint32_t    u32AdcRegLowThd;

    /*! ADC触发0选择*/
    en_adc_trig_sel_t enAdcTrig0Sel;

    /*! ADC触发1选择*/
    en_adc_trig_sel_t enAdcTrig1Sel;

}stc_adc_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC单次采样模式配置
 *****************************************************************************/
typedef struct stc_adc_norm_cfg
{
    /*! ADC通道选择*/
    en_adc_samp_ch_sel_t    enAdcNormModeCh;
    /*! ADC结果累加使能*/
    boolean_t  bAdcResultAccEn;

}stc_adc_norm_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC单通道连续采样模式配置
 *****************************************************************************/
typedef struct stc_adc_cont_cfg
{
    /*! ADC通道选择*/
    en_adc_samp_ch_sel_t    enAdcContModeCh;
    /*! ADC采样次数*/
    uint8_t    u8AdcSampCnt;
    /*! ADC结果累加使能*/
    boolean_t  bAdcResultAccEn;

}stc_adc_cont_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC扫描采样模式配置
 *****************************************************************************/
typedef struct stc_adc_scan_cfg
{
    /*! ADC通道选择*/
    uint8_t    u8AdcScanModeCh;
    /*! ADC采样次数*/
    uint8_t    u8AdcSampCnt;

}stc_adc_scan_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC中断配置
 *****************************************************************************/
typedef struct stc_adc_irq
{
    /*!<ADC连续采样中断*/
    boolean_t  bAdcIrq;
    /*!ADC区间*/
    boolean_t  bAdcRegCmp;
    /*!ADC上超出区间*/
    boolean_t  bAdcHhtCmp;
    /*!ADC下超出区间*/
    boolean_t  bAdcLltCmp;

}stc_adc_irq_t;


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC initialization
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig);
//ADC de-init
void Adc_DeInit(void);

//ADC conversion start
void Adc_Start(void);
//ADC conversion stop
void Adc_Stop(void);

//ADC conversion enable
void Adc_Enable(void);
//ADC conversion disable
void Adc_Disable(void);

//ADC normal mode configuration
en_result_t Adc_ConfigNormMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_norm_cfg_t* pstcAdcNormCfg);
//ADC continuous mode configuration
en_result_t Adc_ConfigContMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_cont_cfg_t* pstcAdcContCfg);
//ADC scan mode configuration
en_result_t Adc_ConfigScanMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_scan_cfg_t* pstcAdcScanCfg);

//ADC enable IRQ
void Adc_EnableIrq(void);
//ADC disable IRQ
void Adc_DisableIrq(void);
//ADC enable compare
void Adc_CmpCfg(stc_adc_irq_t* pstcAdcIrqCfg);
//ADC get IRQ state
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState);
//ADC clear IRQ states
void Adc_ClrContIrqState(void);
void Adc_ClrRegIrqState(void);
void Adc_ClrHhtIrqState(void);
void Adc_ClrIrqLltState(void);

//查询ADC转换状态
boolean_t Adc_PollBusyState(void);
//获取采样值
en_result_t Adc_GetResult(uint16_t* pu16AdcResult);
//获取累加采样值
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult);
//clear ADC accumulated result
void Adc_ClrAccResult(void);
//get ADC scan channel result
en_result_t Adc_GetScanResult(uint8_t u8Channel, uint16_t* pu16AdcResult);
//获取通道8采样值
en_result_t Adc_GetCH8Result(uint16_t* pu16AdcResult);

en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel);

//@}
/******************************************************************************/
/** \file adt.h
 **
 ** Headerfile for Advance Timer functions
 ** @link ADT Group Some description @endlink
 **
 **   - 2018-04-19 Husj    First Version
 **
 ******************************************************************************/


/******************************************************************************
 * Include files
 ******************************************************************************/


/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup AdtGroup Advance Timer (ADT)
  **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/


 /**
 ******************************************************************************
 ** \brief ADT CHx通道定义
 *****************************************************************************/
typedef enum en_adt_CHxX_port
{
    AdtCHxA    = 0u,            ///< CHx A通道
    AdtCHxB    = 1u,            ///< CHx B通道
}en_adt_CHxX_port_t;

 /**
 ******************************************************************************
 ** \brief ADT TRIG端口定义
 *****************************************************************************/
typedef enum en_adt_trig_port
{
    AdtTrigA    = 0u,            ///< TIMx 触发A端口
    AdtTrigB    = 1u,            ///< TIMx 触发B端口
    AdtTrigC    = 2u,            ///< TIMx 触发C端口
    AdtTrigD    = 3u,            ///< TIMx 触发D端口
}en_adt_trig_port_t;

/**
 ******************************************************************************
 ** \brief ADT通用控制 - Z相输入屏蔽周期数
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_gconr_zmsk
{
    AdtZMaskDis   = 0u,      ///< Z相输入屏蔽功能无效
    AdtZMask4Cyl  = 1u,      ///< 位置计数上溢后或下溢后的4个计数周期内的Z相输入被屏蔽
    AdtZMask8Cyl  = 2u,      ///< 位置计数上溢后或下溢后的8个计数周期内的Z相输入被屏蔽
    AdtZMask16Cyl = 3u,      ///< 位置计数上溢后或下溢后的16个计数周期内的Z相输入被屏蔽
}en_adt_gconr_zmsk_t;

/**
 ******************************************************************************
 ** \brief ADT通用控制 - 计数时钟选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_ckdiv
{
    AdtClkPClk0        = 0u,         ///< PCLK0
    AdtClkPClk0Div2    = 1u,         ///< PCLK0/2
    AdtClkPClk0Div4    = 2u,         ///< PCLK0/4
    AdtClkPClk0Div8    = 3u,         ///< PCLK0/8
    AdtClkPClk0Div16   = 4u,         ///< PCLK0/16
    AdtClkPClk0Div64   = 5u,         ///< PCLK0/64
    AdtClkPClk0Div256  = 6u,         ///< PCLK0/256
    AdtClkPClk0Div1024 = 7u,         ///< PCLK0/1024
}en_adt_cnt_ckdiv_t;

/**
 ******************************************************************************
 ** \brief ADT计数模式
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_mode
{
    AdtSawtoothMode  = 0u,          ///< 锯齿波模式
    AdtTriangleModeA = 4u,          ///< 三角波A模式
    AdtTriangleModeB = 5u,          ///< 三角波B模式
}en_adt_cnt_mode_t;

/**
 ******************************************************************************
 ** \brief ADT计数方向
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_dir
{
    AdtCntDown = 0u,      ///< 递减计数
    AdtCntUp   = 1u,      ///< 递加计数
}en_adt_cnt_dir_t;

/**
 ******************************************************************************
 ** \brief ADT通用比较基准
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_compare
{
    AdtCompareA = 0u,            ///< 通用比较基准A
    AdtCompareB = 1u,            ///< 通用比较基准B
    AdtCompareC = 2u,            ///< 通用比较基准C
    AdtCompareD = 3u,            ///< 通用比较基准D
}en_adt_compare_t;

/**
 ******************************************************************************
 ** \brief ADT专用比较基准
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_special_compare
{
    AdtSpclCompA = 0u,            ///< 专用比较基准A
    AdtSpclCompB = 1u,            ///< 专用比较基准B
}en_adt_special_compare_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - TIMx输出状态控制
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_disval
{
    AdtTIMxDisValNorm = 0u,     ///< 强制输出无效条件0~3中被选择的条件成立时，CHx端口正常输出
    AdtTIMxDisValHiZ  = 1u,     ///< 强制输出无效条件0~3中被选择的条件成立时，CHx端口输出高阻态
    AdtTIMxDisValLow  = 2u,     ///< 强制输出无效条件0~3中被选择的条件成立时，CHx端口输出低电平
    AdtTIMxDisValHigh = 3u,     ///< 强制输出无效条件0~3中被选择的条件成立时，CHx端口输出高电平
}en_adt_pconr_disval_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - CHx强制输出无效条件选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_dissel
{
    AdtCHxDisSel0 = 0u,        ///< 选择强制输出无效条件0
    AdtCHxDisSel1 = 1u,        ///< 选择强制输出无效条件1
    AdtCHxDisSel2 = 2u,        ///< 选择强制输出无效条件2
    AdtCHxDisSel3 = 3u,        ///< 选择强制输出无效条件3
}en_adt_pconr_dissel_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - CHx周期值匹配时端口状态设定
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_perc
{
    AdtCHxPeriodLow  = 0u,      ///< 计数器计数值与周期值相等时，CHx端口输出保持为低电平
    AdtCHxPeriodHigh = 1u,      ///< 计数器计数值与周期值相等时，CHx端口输出设定为高电平
    AdtCHxPeriodKeep = 2u,      ///< 计数器计数值与周期值相等时，CHx端口输出设定为先前状态
    AdtCHxPeriodInv  = 3u,      ///< 计数器计数值与周期值相等时，CHx端口输出设定为反转电平
}en_adt_pconr_perc_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - CHx比较值匹配时端口状态设定
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_cmpc
{
    AdtCHxCompareLow  = 0u,     ///< 计数器计数值与GCMxR相等时，CHx端口输出保持为低电平
    AdtCHxCompareHigh = 1u,     ///< 计数器计数值与GCMxR相等时，CHx端口输出设定为高电平
    AdtCHxCompareKeep = 2u,     ///< 计数器计数值与GCMxR相等时，CHx端口输出设定为先前状态
    AdtCHxCompareInv  = 3u,     ///< 计数器计数值与GCMxR相等时，CHx端口输出设定为反转电平
}en_adt_pconr_cmpc_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - CHx端口输出
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_port_out
{
    AdtCHxPortOutLow  = 0u,  ///< CHx端口输出设定为低电平
    AdtCHxPortOutHigh = 1u,  ///< CHx端口输出设定为高电平
}en_adt_pconr_port_out_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - CHx端口功能模式选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_capc
{
    AdtCHxCompareOutput = 0u,   ///< CHx端口设定为比较输出功能
    AdtCHxCompareInput  = 1u,   ///< CHx端口设定为捕获输入功能
}en_adt_pconr_capc_t;

/**
 ******************************************************************************
 ** \brief ADT端口控制 - CHx计数开始停止端口状态选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_stastps
{
    AdtCHxStateSelSS   = 0u,    ///< 计数开始或停止时，CHx端口输出由STACB、STPCB决定
    AdtCHxStateSelKeep = 1u,    ///< 计数开始或停止时，CHx端口输出设定为先前状态
}en_adt_pconr_stastps_t;

/**
 ******************************************************************************
 ** \brief ADT死区控制 - CHx死区分离设定
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_dconr_sepa
{
    AdtCHxDtSeperate = 0u,      ///< DTUAR和DTDAR分别设定
    AdtCHxDtEqual    = 1u,      ///< DTDAR的值和DTUAR的值自动相等
}en_adt_dconr_sepa_t;

/**
 ******************************************************************************
 ** \brief ADT滤波控制 - TRIx/TIMxIx端口滤波采样基准时钟选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_fconr_nofick
{
    AdtFltClkPclk0      = 0u,    ///< PCLK0
    AdtFltClkPclk0Div4  = 1u,    ///< PCLK0/4
    AdtFltClkPclk0Div16 = 2u,    ///< PCLK0/16
    AdtFltClkPclk0Div64 = 3u,    ///< PCLK0/64
}en_adt_fconr_nofick_t;

/**
 ******************************************************************************
 ** \brief ADT有效周期 - TIMx有效周期选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_vperr_pcnts
{
    AdtPeriodCnts0 = 0u,         ///< 有效周期选择功能无效
    AdtPeriodCnts1 = 1u,         ///< 每隔1个周期有效一次
    AdtPeriodCnts2 = 2u,         ///< 每隔2个周期有效一次
    AdtPeriodCnts3 = 3u,         ///< 每隔3个周期有效一次
    AdtPeriodCnts4 = 4u,         ///< 每隔4个周期有效一次
    AdtPeriodCnts5 = 5u,         ///< 每隔5个周期有效一次
    AdtPeriodCnts6 = 6u,         ///< 每隔6个周期有效一次
    AdtPeriodCnts7 = 7u,         ///< 每隔7个周期有效一次
}en_adt_vperr_pcnts_t;

/**
 ******************************************************************************
 ** \brief ADT有效周期 - 计数条件选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_vperr_pcnte
{
    AdtPeriodCnteDisable = 0u,     ///< 有效周期选择功能无效
    AdtPeriodCnteMin     = 1u,     ///< 锯齿波计数上、下溢点或三角波波谷做为计数条件
    AdtPeriodCnteMax     = 2u,     ///< 锯齿波计数上、下溢点或三角波波峰做为计数条件
    AdtPeriodCnteBoth    = 3u,     ///< 锯齿波计数上、下溢点或三角波波峰，波谷做为计数条件
}en_adt_vperr_pcnte_t;

/**
 ******************************************************************************
 ** \brief ADT端口触发控制 - 触发源选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_ttrig_trigxs
{
    AdtTrigxSelP01 = 0u,         ///< P01
    AdtTrigxSelP02 = 1u,         ///< P02
    AdtTrigxSelP03 = 2u,         ///< P03
    AdtTrigxSelP14 = 3u,         ///< P14
    AdtTrigxSelP15 = 4u,         ///< P15
    AdtTrigxSelP23 = 5u,         ///< P23
    AdtTrigxSelP24 = 6u,         ///< P24
    AdtTrigxSelP25 = 7u,         ///< P25
    AdtTrigxSelP26 = 8u,         ///< P26
    AdtTrigxSelP27 = 9u,         ///< P27
    AdtTrigxSelP31 = 10u,        ///< P31
    AdtTrigxSelP32 = 11u,        ///< P32
    AdtTrigxSelP33 = 12u,        ///< P33
    AdtTrigxSelP34 = 13u,        ///< P34
    AdtTrigxSelP35 = 14u,        ///< P35
    AdtTrigxSelP36 = 15u,        ///< P36
}en_adt_ttrig_trigxs_t;

/**
 ******************************************************************************
 ** \brief ADT AOS触发控制 - AOSx触发源选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_itrig_iaosxs
{
    AdtAosxTrigSelTim0Int   = 0u,    ///< TIM0_INT
    AdtAosxTrigSelTim1Int   = 1u,    ///< TIM1_INT
    AdtAosxTrigSelTim2Int   = 2u,    ///< TIM2_INT
    AdtAosxTrigSelLpTimInt  = 3u,    ///< LPTIMER_INT
    AdtAosxTrigSelTim4Int   = 4u,    ///< TIM4_INT
    AdtAosxTrigSelTim5Int   = 5u,    ///< TIM5_INT
    AdtAosxTrigSelTim6Int   = 6u,    ///< TIM6_INT
    AdtAosxTrigSelUart0Int  = 7u,    ///< UART0_INT
    AdtAosxTrigSelUart1Int  = 8u,    ///< UART1_INT
    AdtAosxTrigSelLpUartInt = 9u,    ///< LPUART_INT
    AdtAosxTrigSelVc0Int    = 10u,   ///< VC0_INT
    AdtAosxTrigSelVc1Int    = 11u,   ///< VC1_INT
    AdtAosxTrigSelRtcInt    = 12u,   ///< RTC_INT
    AdtAosxTrigSelPcaInt    = 13u,   ///< PCA_INT
    AdtAosxTrigSelSpiInt    = 14u,   ///< SPI_INT
    AdtAosxTrigSelAdcInt    = 15u,   ///< ADC_INT
}en_adt_itrig_iaosxs_t;

/**
 ******************************************************************************
 ** \brief ADT硬件(启动/停止/清零/捕获)事件触发选择
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_hw_trig
{
    AdtHwTrigAos0        = 0u,       ///< 从AOS来的事件触发0有效
    AdtHwTrigAos1        = 1u,       ///< 从AOS来的事件触发1有效
    AdtHwTrigAos2        = 2u,       ///< 从AOS来的事件触发2有效
    AdtHwTrigAos3        = 3u,       ///< 从AOS来的事件触发3有效
    AdtHwTrigCHxARise    = 4u,       ///< CHxA端口上采样到上升沿
    AdtHwTrigCHxAFall    = 5u,       ///< CHxA端口上采样到下降沿
    AdtHwTrigCHxBRise    = 6u,       ///< CHxB端口上采样到上升沿
    AdtHwTrigCHxBFall    = 7u,       ///< CHxB端口上采样到下降沿
    AdtHwTrigTimTriARise = 8u,       ///< TIMTRIA端口上采样到上升沿
    AdtHwTrigTimTriAFall = 9u,       ///< TIMTRIA端口上采样到下降沿
    AdtHwTrigTimTriBRise = 10u,      ///< TIMTRIB端口上采样到上升沿
    AdtHwTrigTimTriBFall = 11u,      ///< TIMTRIB端口上采样到下降沿
    AdtHwTrigTimTriCRise = 12u,      ///< TIMTRIC端口上采样到上升沿
    AdtHwTrigTimTriCFall = 13u,      ///< TIMTRIC端口上采样到下降沿
    AdtHwTrigTimTriDRise = 14u,      ///< TIMTRID端口上采样到上升沿
    AdtHwTrigTimTriDFall = 15u,      ///< TIMTRID端口上采样到下降沿
    AdtHwTrigEnd         = 16u,
}en_adt_hw_trig_t;

/**
 ******************************************************************************
 ** \brief ADT硬件(递加/递减)事件触发选择
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_hw_cnt
{
    AdtHwCntCHxALowCHxBRise   = 0u,      ///< CHxA端口为低电平时，CHxB端口上采样到上升沿
    AdtHwCntCHxALowCHxBFall   = 1u,      ///< CHxA端口为低电平时，CHxB端口上采样到下降沿
    AdtHwCntCHxAHighCHxBRise  = 2u,      ///< CHxA端口为高电平时，CHxB端口上采样到上升沿
    AdtHwCntCHxAHighCHxBFall  = 3u,      ///< CHxA端口为高电平时，CHxB端口上采样到下降沿
    AdtHwCntCHxBLowCHxARise   = 4u,      ///< CHxB端口为低电平时，CHxA端口上采样到上升沿
    AdtHwCntCHxBLowCHxAFall   = 5u,      ///< CHxB端口为低电平时，CHxA端口上采样到下降沿
    AdtHwCntCHxBHighChxARise  = 6u,      ///< CHxB端口为高电平时，CHxA端口上采样到上升沿
    AdtHwCntCHxBHighCHxAFall  = 7u,      ///< CHxB端口为高电平时，CHxA端口上采样到下降沿
    AdtHwCntTimTriARise       = 8u,      ///< TIMTRIA端口上采样到上升沿
    AdtHwCntTimTriAFall       = 9u,      ///< TIMTRIA端口上采样到下降沿
    AdtHwCntTimTriBRise       = 10u,     ///< TIMTRIB端口上采样到上升沿
    AdtHwCntTimTriBFall       = 11u,     ///< TIMTRIB端口上采样到下降沿
    AdtHwCntTimTriCRise       = 12u,     ///< TIMTRIC端口上采样到上升沿
    AdtHwCntTimTriCFall       = 13u,     ///< TIMTRIC端口上采样到下降沿
    AdtHwCntTimTriDRise       = 14u,     ///< TIMTRID端口上采样到上升沿
    AdtHwCntTimTriDFall       = 15u,     ///< TIMTRID端口上采样到下降沿
    AdtHwCntAos0              = 16u,     ///< 从AOS来的事件触发0有效
    AdtHwCntAos1              = 17u,     ///< 从AOS来的事件触发1有效
    AdtHwCntAos2              = 18u,     ///< 从AOS来的事件触发2有效
    AdtHwCntAos3              = 19u,     ///< 从AOS来的事件触发3有效
    AdtHwCntMax               = 20u,
}en_adt_hw_cnt_t;

/**
 ******************************************************************************
 ** \brief ADT端口刹车极性控制
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_ptbrk_polarity
{
    AdtPtBrkHigh = 0u,     ///< 端口刹车极性高电平有效
    AdtPtBrkLow  = 1u,     ///< 端口刹车极性低电平有效
}en_adt_ptbrk_polarity_t;

/**
 ******************************************************************************
 ** \brief ADT PWM展频计数选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pwm_dither_type
{
    AdtPwmDitherUnderFlow = 0u,    ///< PWM展频计数下溢出
    AdtPwmDitherOverFlow  = 1u,    ///< PWM展频计数上溢出
}en_adt_pwm_dither_type_t;

/**
 ******************************************************************************
 ** \brief ADT中断类型
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_irq_type
{
    AdtCMAIrq  = 0u,     ///< 计数匹配A（或捕获输入）中断
    AdtCMBIrq  = 1u,     ///< 计数匹配B（或捕获输入）中断
    AdtCMCIrq  = 2u,     ///< 计数匹配C中断
    AdtCMDIrq  = 3u,     ///< 计数匹配D中断
    AdtOVFIrq  = 6u,     ///< 上溢匹配中断
    AdtUDFIrq  = 7u,     ///< 下溢匹配中断
    AdtDTEIrq  = 8u,     ///< 死区时间错误中断
}en_adt_irq_type_t;


typedef enum en_adt_state_type
{
    AdtCMAF = 0,           ///< 计数匹配A标志
    AdtCMBF = 1,           ///< 计数匹配B标志
    AdtCMCF = 2,           ///< 计数匹配C标志
    AdtCMDF = 3,           ///< 计数匹配D标志
    AdtOVFF = 6,           ///< 上溢匹配标志
    AdtUDFF = 7,           ///< 下溢匹配标志
    AdtDTEF = 8,           ///< 死区时间错误标志
    AdtCntDir = 31,        ///< 计数方向
}en_adt_state_type_t;

/**
 ******************************************************************************
 ** \brief ADT软件同步配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_sw_sync
{
    boolean_t               bAdTim4;      ///< Timer 4
    boolean_t               bAdTim5;      ///< Timer 5
    boolean_t               bAdTim6;      ///< Timer 6

}stc_adt_sw_sync_t;

/**
 ******************************************************************************
 ** \brief ADT AOS触发配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_aos_trig_cfg
{
    en_adt_itrig_iaosxs_t   enAos0TrigSrc;      ///< AOS0触发源选择
    en_adt_itrig_iaosxs_t   enAos1TrigSrc;      ///< AOS1触发源选择
    en_adt_itrig_iaosxs_t   enAos2TrigSrc;      ///< AOS2触发源选择
    en_adt_itrig_iaosxs_t   enAos3TrigSrc;      ///< AOS3触发源选择
}stc_adt_aos_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT 中断触发配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_irq_trig_cfg
{
    boolean_t   bAdtUnderFlowTrigEn;        ///< 下溢匹配使能触发ADC
    boolean_t   bAdtOverFlowTrigEn;         ///< 上溢匹配使能触发ADC
    boolean_t   bAdtCntMatchDTrigEn;        ///< 计数匹配D使能触发ADC
    boolean_t   bAdtCntMatchCTrigEn;        ///< 计数匹配C使能触发ADC
    boolean_t   bAdtCntMatchBTrigEn;        ///< 计数匹配B使能触发ADC
    boolean_t   bAdtCntMatchATrigEn;        ///< 计数匹配A使能触发ADC
}stc_adt_irq_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Trig端口配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_port_trig_cfg
{
    en_adt_ttrig_trigxs_t   enTrigSrc;      ///< 触发源选择
    boolean_t               bFltEn;         ///< 触发源捕获输入滤波使能
    en_adt_fconr_nofick_t   enFltClk;       ///< 滤波采样基准时钟
}stc_adt_port_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Z相输入屏蔽功能配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_zmask_cfg
{
    en_adt_gconr_zmsk_t     enZMaskCycle;              ///< Z相输入屏蔽计数周期选择
    boolean_t               bFltPosCntMaksEn;          ///< Z相输入时的屏蔽周期内，位置计数器的清零功能不屏蔽（FALSE）或屏蔽(TRUE)
    boolean_t               bFltRevCntMaksEn;          ///< Z相输入时的屏蔽周期内，公转计数器的计数功能不屏蔽（FALSE）或屏蔽(TRUE)
}stc_adt_zmask_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT TIMxX端口配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_TIMxX_port_cfg
{
    en_adt_pconr_capc_t     enCap;      ///< 端口功能模式
    boolean_t               bOutEn;     ///< 输出使能
    en_adt_pconr_perc_t     enPerc;     ///< 周期值匹配时端口状态
    en_adt_pconr_cmpc_t     enCmpc;     ///< 比较值匹配时端口状态
    en_adt_pconr_stastps_t  enStaStp;   ///< 计数开始停止端口状态选择
    en_adt_pconr_port_out_t enStaOut;   ///< 计数开始端口输出状态
    en_adt_pconr_port_out_t enStpOut;   ///< 计数停止端口输出状态
    en_adt_pconr_disval_t   enDisVal;   ///< 强制输出无效时输出状态控制
    en_adt_pconr_dissel_t   enDisSel;   ///< 强制输出无效条件选择
    boolean_t               bFltEn;     ///< 端口捕获输入滤波使能
    en_adt_fconr_nofick_t   enFltClk;   ///< 端口滤波采样基准时钟
}stc_adt_CHxX_port_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT刹车端口配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_break_port_cfg
{
    boolean_t               bPortEn;    ///< 端口使能
    en_adt_ptbrk_polarity_t enPol;      ///< 极性选择
}stc_adt_break_port_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT无效条件3配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_disable_3_cfg
{
    stc_adt_break_port_cfg_t    stcBrkPtCfg[16];    ///< 刹车端口配置
    boolean_t                   bFltEn;             ///< 刹车端口滤波使能
    en_adt_fconr_nofick_t       enFltClk;           ///< 滤波采样基准时钟
}stc_adt_disable_3_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT无效条件1配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_disable_1_cfg
{
    boolean_t   bTim6OutSH;     ///< TIM6输出同高
    boolean_t   bTim5OutSH;     ///< TIM5输出同高
    boolean_t   bTim4OutSH;     ///< TIM4输出同高
    boolean_t   bTim6OutSL;     ///< TIM6输出同低
    boolean_t   bTim5OutSL;     ///< TIM5输出同低
    boolean_t   bTim4OutSL;     ///< TIM4输出同低
}stc_adt_disable_1_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT PWM展频计数配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_pwm_dither_cfg
{
    en_adt_pwm_dither_type_t    enAdtPDType;    ///< PWM展频计数选择
    boolean_t   bTimxBPDEn;                     ///< PWM通道B展频使能
    boolean_t   bTimxAPDEn;                     ///< PWM通道A展频使能
}stc_adt_pwm_dither_cfg_t;


/**
 ******************************************************************************
 ** \brief ADT基本计数配置
 ** \note
 ******************************************************************************/
typedef struct stc_adt_basecnt_cfg
{
    en_adt_cnt_mode_t       enCntMode;      ///< 计数模式
    en_adt_cnt_dir_t        enCntDir;       ///< 计数方向
    en_adt_cnt_ckdiv_t      enCntClkDiv;    ///< 计数时钟选择
}stc_adt_basecnt_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT计数状态
 ** \note
 ******************************************************************************/
typedef struct stc_adt_cntstate_cfg
{
    uint16_t         u16Counter;      ///< 当前计数器的计数值
    boolean_t        enCntDir;        ///< 计数方向
    uint8_t          u8ValidPeriod;   ///< 有效周期计数
    boolean_t        bDTEF;           ///< 死区时间错误标志
    boolean_t        bUDFF;           ///< 下溢匹配标志
    boolean_t        bOVFF;           ///< 上溢匹配标志
    boolean_t        bCMDF;           ///< 计数匹配D标志
    boolean_t        bCMCF;           ///< 计数匹配C标志
    boolean_t        bCMBF;           ///< 计数匹配B标志
    boolean_t        bCMAF;           ///< 计数匹配A标志
}stc_adt_cntstate_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT有效计数周期
 ** \note
 ******************************************************************************/
typedef struct stc_adt_validper_cfg
{
    en_adt_vperr_pcnts_t    enValidCnt;     ///< 有效周期选择
    en_adt_vperr_pcnte_t    enValidCdt;     ///< 有效周期计数条件
    boolean_t               bPeriodD;       ///< 通用信号有效周期选择D
    boolean_t               bPeriodC;       ///< 通用信号有效周期选择C
    boolean_t               bPeriodB;       ///< 通用信号有效周期选择B
    boolean_t               bPeriodA;       ///< 通用信号有效周期选择A
}stc_adt_validper_cfg_t;

/******************************************************************************
 * Global definitions
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
//配置硬件递加事件
en_result_t Adt_CfgHwCntUp(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntUp);
//清除硬件递加事件
en_result_t Adt_ClearHwCntUp(M0P_ADTIM_TypeDef *ADTx);
//配置硬件递减事件
en_result_t Adt_CfgHwCntDwn(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntDwn);
//清除硬件递减事件
en_result_t Adt_ClearHwCntDwn(M0P_ADTIM_TypeDef *ADTx);
//配置硬件启动事件
en_result_t Adt_CfgHwStart(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStart);
//清除硬件启动事件
en_result_t Adt_ClearHwStart(M0P_ADTIM_TypeDef *ADTx);
//使能硬件启动事件
en_result_t Adt_EnableHwStart(M0P_ADTIM_TypeDef *ADTx);
//禁止硬件启动事件
en_result_t Adt_DisableHwStart(M0P_ADTIM_TypeDef *ADTx);
//配置硬件停止事件
en_result_t Adt_CfgHwStop(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStop);
//清除硬件停止事件
en_result_t Adt_ClearHwStop(M0P_ADTIM_TypeDef *ADTx);
//使能硬件停止事件
en_result_t Adt_EnableHwStop(M0P_ADTIM_TypeDef *ADTx);
//禁止硬件停止事件
en_result_t Adt_DisableHwStop(M0P_ADTIM_TypeDef *ADTx);
//配置硬件清零事件
en_result_t Adt_CfgHwClear(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwClear);
//清除硬件清零事件
en_result_t Adt_ClearHwClear(M0P_ADTIM_TypeDef *ADTx);
//使能硬件清零事件
en_result_t Adt_EnableHwClear(M0P_ADTIM_TypeDef *ADTx);
//禁止硬件清零事件
en_result_t Adt_DisableHwClear(M0P_ADTIM_TypeDef *ADTx);
//配置A通道硬件捕获事件
en_result_t Adt_CfgHwCaptureA(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureA);
//清除A通道硬件捕获事件
en_result_t Adt_ClearHwCaptureA(M0P_ADTIM_TypeDef *ADTx);
//配置B通道硬件捕获事件
en_result_t Adt_CfgHwCaptureB(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureB);
//清除B通道硬件捕获事件
en_result_t Adt_ClearHwCaptureB(M0P_ADTIM_TypeDef *ADTx);
//软件同步启动
en_result_t Adt_SwSyncStart(stc_adt_sw_sync_t* pstcAdtSwSyncStart);
//软件同步停止
en_result_t Adt_SwSyncStop(stc_adt_sw_sync_t* pstcAdtSwSyncStop);
//软件同步清零
en_result_t Adt_SwSyncClear(stc_adt_sw_sync_t* pstcAdtSwSyncClear);
//获取软件同步状态
en_result_t Adt_GetSwSyncState(stc_adt_sw_sync_t* pstcAdtSwSyncState);
//AOS触发配置
en_result_t Adt_AosTrigCfg(stc_adt_aos_trig_cfg_t* pstcAdtAosTrigCfg);
//中断触发配置
en_result_t Adt_IrqTrigCfg(M0P_ADTIM_TypeDef *ADTx,
                              stc_adt_irq_trig_cfg_t* pstcAdtIrqTrigCfg);
//端口触发配置
en_result_t Adt_PortTrigCfg(en_adt_trig_port_t enAdtTrigPort,
                               stc_adt_port_trig_cfg_t* pstcAdtPortTrigCfg);
//CHxX端口配置
en_result_t Adt_CHxXPortCfg(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                stc_adt_CHxX_port_cfg_t* pstcAdtCHxXCfg);
//使能端口刹车
en_result_t Adt_EnableBrakePort(uint8_t port, stc_adt_break_port_cfg_t* pstcAdtBrkPtCfg);
//清除端口刹车
void Adt_ClearBrakePort(void);
//无效条件3配置(端口刹车)
en_result_t Adt_Disable3Cfg(stc_adt_disable_3_cfg_t* pstcAdtDisable3);
//软件刹车 Enable/Disable(仅适用于无效条件3使能的情况下)
en_result_t Adt_SwBrake(boolean_t bSwBrk);
//获取端口刹车标志
boolean_t Adt_GetPortBrakeFlag(void);
//清除端口刹车标志
void Adt_ClearPortBrakeFlag(void);
//无效条件1配置(同高同低刹车)
en_result_t Adt_Disable1Cfg(stc_adt_disable_1_cfg_t* pstcAdtDisable1);
//获取同高同低刹车标志
boolean_t Adt_GetSameBrakeFlag(void);
//清除同高同低刹车标志
void Adt_ClearSameBrakeFlag(void);
//PWM展频配置
en_result_t Adt_PwmDitherCfg(M0P_ADTIM_TypeDef *ADTx, stc_adt_pwm_dither_cfg_t* pstcAdtPwmDitherCfg);
//AdvTimer初始化
en_result_t Adt_Init(M0P_ADTIM_TypeDef *ADTx, stc_adt_basecnt_cfg_t* pstcAdtBaseCntCfg);
//AdvTimer去初始化
en_result_t Adt_DeInit(M0P_ADTIM_TypeDef *ADTx);
//AdvTimert启动
en_result_t Adt_StartCount(M0P_ADTIM_TypeDef *ADTx);
//AdvTimert停止
en_result_t Adt_StopCount(M0P_ADTIM_TypeDef *ADTx);
//设置计数值
en_result_t Adt_SetCount(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Value);
//获取计数值
uint16_t Adt_GetCount(M0P_ADTIM_TypeDef *ADTx);
//清除计数值
en_result_t Adt_ClearCount(M0P_ADTIM_TypeDef *ADTx);
//获取有效周期计数值
uint8_t Adt_GetVperNum(M0P_ADTIM_TypeDef *ADTx);
//获取状态标志
boolean_t Adt_GetState(M0P_ADTIM_TypeDef *ADTx, en_adt_state_type_t enstate);
//配置计数周期
en_result_t Adt_SetPeriod(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Period);
//配置计数周期缓冲
en_result_t Adt_SetPeriodBuf(M0P_ADTIM_TypeDef *ADTx, uint16_t u16PeriodBuf);
//清除计数周期缓冲
en_result_t Adt_ClearPeriodBuf(M0P_ADTIM_TypeDef *ADTx);
//配置有效计数周期
en_result_t Adt_SetValidPeriod(M0P_ADTIM_TypeDef *ADTx,
                               stc_adt_validper_cfg_t* pstcAdtValidPerCfg);
//配置比较输出计数基准值
en_result_t Adt_SetCompareValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_compare_t enAdtCompare,
                                uint16_t u16Compare);
//配置通用比较值/捕获值的缓存传送
en_result_t Adt_EnableValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                 en_adt_CHxX_port_t enAdtCHxXPort,
                                 boolean_t bCompareBufEn);
//清除比较输出计数值/捕获值缓存
en_result_t Adt_ClearValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                     en_adt_CHxX_port_t enAdtCHxXPort);
//获取捕获值
en_result_t Adt_GetCaptureValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16Capture);
//获取捕获缓存值
en_result_t Adt_GetCaptureBuf(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16CaptureBuf);
//设置死区时间上基准值
en_result_t Adt_SetDTUA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value);
//设置死区时间下基准值
en_result_t Adt_SetDTDA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value);
//配置死区时间功能
en_result_t Adt_CfgDT(M0P_ADTIM_TypeDef *ADTx,
                         boolean_t bDTEn,
                         boolean_t bEqual);
//配置中断
en_result_t Adt_CfgIrq(M0P_ADTIM_TypeDef *ADTx,
                          en_adt_irq_type_t enAdtIrq,
                          boolean_t bEn);
//获取中断标志
boolean_t Adt_GetIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                         en_adt_irq_type_t enAdtIrq);
//清除中断标志
en_result_t Adt_ClearIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                             en_adt_irq_type_t enAdtIrq);
//清除所有中断标志
en_result_t Adt_ClearAllIrqFlag(M0P_ADTIM_TypeDef *ADTx);
//Z相输入屏蔽设置
en_result_t Adt_CfgZMask(M0P_ADTIM_TypeDef *ADTx,
                            stc_adt_zmask_cfg_t* pstcAdtZMaskCfg);

//@} // ADT Group

/******************************************************************************/
/** \file bgr.h
 **
 ** BGR 数据结构及API声明.
 **
 **   - 2018-04-21  LuX V1.0.
 **
 ******************************************************************************/


/******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup BGR
  **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/


/******************************************************************************
 * Global definitions
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
///<内部温度传感器使能/关闭
void Bgr_TempSensorEnable(void);
void Bgr_TempSensorDisable(void);
///<BGR使能/关闭
void Bgr_BgrEnable(void);
void Bgr_BgrDisable(void);

//@} // BGR Group

/*****************************************************************************/
/** \file bt.h
 **
 ** 基本定时器数据结构及API声明
 ** @link BT Group Some description @endlink
 **
 ** History:
 **   - 2017-05-10   Lux     V1.0
 **
 *****************************************************************************/


/*****************************************************************************
 * Include files
 *****************************************************************************/


/**
 ******************************************************************************
 ** \defgroup BtGroup Base Timer (BT)
  **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief 定时器选择数据类型重定义
 *****************************************************************************/
typedef enum en_bt_unit
{
    TIM0    = 0u,           ///< Timer 0
    TIM1    = 1u,           ///< Timer 1
    TIM2    = 2u,           ///< Timer 2
}en_bt_unit_t;

/**
 ******************************************************************************
 ** \brief 极性控制数据类型重定义 (GATE_P)
 *****************************************************************************/
typedef enum en_bt_gatep
{
    BtPositive = 0u,            ///< 高电平有效
    BtOpposite = 1u,            ///< 低电平有效
}en_bt_gatep_t;

/**
 ******************************************************************************
 ** \brief 定时器门控数据类型重定义 (GATE)
 *****************************************************************************/
typedef enum en_bt_gate
{
    BtGateDisable = 0u,            ///< 无门控
    BtGateEnable  = 1u,            ///< 门控使能
}en_bt_gate_t;

/**
 ******************************************************************************
 ** \brief TIM 预除频选择 (PRS)
 *****************************************************************************/
typedef enum en_bt_timclkdiv
{
    BtPCLKDiv1   = 0u,           ///< Div 1
    BtPCLKDiv2   = 1u,           ///< Div 2
    BtPCLKDiv4   = 2u,           ///< Div 4
    BtPCLKDiv8   = 3u,           ///< Div 8
    BtPCLKDiv16  = 4u,           ///< Div 16
    BtPCLKDiv32  = 5u,           ///< Div 32
    BtPCLKDiv64  = 6u,           ///< Div 64
    BtPCLKDiv256 = 7u,           ///< Div 256
}en_bt_timclkdiv_t;

/**
 ******************************************************************************
 ** \brief 翻转输出使能数据类型重定义 (TOG_EN)
 *****************************************************************************/
typedef enum en_bt_toggle
{
    BtTogDisable = 0u,            ///< 翻转输出禁止
    BtTogEnable  = 1u,            ///< 翻转输出使能
}en_bt_toggle_t;

/**
 ******************************************************************************
 ** \brief 计数/定时器功能选择数据类型重定义 (CT)
 *****************************************************************************/
typedef enum en_bt_function
{
    BtTimer   = 0u,            ///< 定时器功能
    BtCounter = 1u,            ///< 计数器功能
}en_bt_function_t;


/**
 ******************************************************************************
 ** \brief 定时器工作模式数据类型重定义 (MD)
 *****************************************************************************/
typedef enum en_bt_mode
{
    BtMode1  = 0u,         ///< 32位计数器/定时器
    BtMode2  = 1u,         ///< 自动重装载16位计数器/定时器
}en_bt_mode_t;

/**
 ******************************************************************************
 ** \brief 定时器运行控制数据类型重定义 (TR)
 *****************************************************************************/
typedef enum en_bt_start
{
    BtTRDisable = 0u,            ///< 停止
    BtTREnable  = 1u,            ///< 运行
}en_bt_start_t;

/**
 ******************************************************************************
 ** \brief Timer 配置结构体定义
 *****************************************************************************/
typedef struct stc_bt_config
{
    en_bt_gatep_t     enGateP;          ///< 门控极性控制
    en_bt_gate_t      enGate;           ///< 门控使能
    en_bt_timclkdiv_t enPRS;            ///< 预除频配置
    en_bt_toggle_t    enTog;            ///< 反转输出使能
    en_bt_function_t  enCT;             ///< 定时/计数功能选择
    en_bt_mode_t      enMD;             ///< 计数模式配置

}stc_bt_cfg_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//中断相关函数
//中断标志获取
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit);
//中断标志清除
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit);
//中断使能/禁止
en_result_t Bt_EnableIrq (en_bt_unit_t enUnit);
en_result_t Bt_DisableIrq(en_bt_unit_t enUnit);

//初始化及相关功能操作
//timer配置及初始化
en_result_t Bt_Init(en_bt_unit_t enUnit, stc_bt_cfg_t* pstcCfg);
//Lptimer 启动/停止
en_result_t Bt_Run(en_bt_unit_t enUnit);
en_result_t Bt_Stop(en_bt_unit_t enUnit);
//重载值设置
en_result_t Bt_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data);
//16位计数值设置/获取
en_result_t Bt_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_Cnt16Get(en_bt_unit_t enUnit);
//32位计数值设置/获取
en_result_t Bt_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data);
uint32_t Bt_Cnt32Get(en_bt_unit_t enUnit);

//@} // BtGroup

/******************************************************************************/
/** \file crc.h
 **
 ** CRC 数据结构及API声明.
 **
 **   - 2016-05-04  LuX V1.0.
 **
 ******************************************************************************/


/******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup CrcGroup Cyclic Redundancy Check (CRC)
  **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/


/******************************************************************************
 * Global definitions
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
//CRC16 编码值获取
uint16_t CRC16_Get8(uint8_t* pu8Data, uint32_t u32Len);
uint16_t CRC16_Get16(uint16_t* pu16Data, uint32_t u32Len);
uint16_t CRC16_Get32(uint32_t* pu32Data, uint32_t u32Len);
//CRC16 校验
en_result_t CRC16_Check8(uint8_t* pu8Data, uint32_t u32Len, uint16_t u16CRC);
en_result_t CRC16_Check16(uint16_t* pu16Data, uint32_t u32Len, uint16_t u16CRC);
en_result_t CRC16_Check32(uint32_t* pu32Data, uint32_t u32Len, uint16_t u16CRC);

//@} // CRC Group

/******************************************************************************/
/** \file flash.h
 **
 ** FLASH 数据结构及API声明.
 **
 ** - 2017-05-02 LuX V1.0
 **
 ******************************************************************************/


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup FlashGroup Flash Controller (Flash)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 ******************************************************************************
  ** \brief Flash中断类型重定义
 *****************************************************************************/
typedef enum en_flash_int_type
{
    FlashPCInt    = 0x01u,          ///<擦写PC地址报警中断
    FlashSlockInt = 0x02u,          ///<擦写保护报警中断
} en_flash_int_type_t;


/**
 ******************************************************************************
  ** \brief Flash读等待周期类型重定义
 *****************************************************************************/
typedef enum en_flash_waitcycle
{
    FlashWaitCycle0 = 0u,       ///< 读等待周期设置为0（当HCLK小于等于24MHz时）
    FlashWaitCycle1 = 1u,       ///< 读等待周期设置为1（当HCLK大于24MHz时必须至少为1)
} en_flash_waitcycle_t;



/**
 ******************************************************************************
 ** \brief Redefinition of FLASH register structure
 ******************************************************************************/

/******************************************************************************
 * Global definitions
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
///<Flash 初始化配置(编程时间参数置）
en_result_t Flash_Init(uint8_t u8FreqCfg);

///<Flash 页/全片擦除
en_result_t Flash_SectorErase(uint32_t u32SectorAddr);
en_result_t Flash_ChipErase(void);

///<Flash 字节/半字/字写
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t u8Data);
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t u16Data);
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t u32Data);

///<Flash 编程保护加锁/解锁
void Flash_LockAll(void);
void Flash_UnlockAll(void);
en_result_t Flash_LockSet(uint32_t u32LockValue);


///<Flash 读等待周期设定
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle);

///<中断相关函数
///<中断使能/禁止
en_result_t Flash_EnableIrq(en_flash_int_type_t enFlashIntType);
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType);
///<中断标志获取
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType);
///<中断标志清除
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType);

//@} // FlashGroup

/******************************************************************************/
/** \file gpio.h
 **
 ** GPIO driver
 ** @link GPIO Group Some description @endlink
 **
 **   - 2018-04-18
 **
 ******************************************************************************/


/*******************************************************************************
 * Include files
 ******************************************************************************/


/* C binding of definitions if building with C++ compiler */

/**
 *******************************************************************************
 ** \defgroup GpioGroup General Purpose I/O (GPIO)
 **
 **
 ******************************************************************************/
//@{
#define GPIO_GPSZ       (0x40u)

/*******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief GPIO PORT类型定义
 ******************************************************************************/
typedef enum en_gpio_port
{
    GpioPort0 = 0x00u,                 ///< GPIO PORT 0
    GpioPort1 = 0x40u,                 ///< GPIO PORT 1
    GpioPort2 = 0x80u,                 ///< GPIO PORT 2
    GpioPort3 = 0xc0u,                 ///< GPIO PORT 3
}en_gpio_port_t;

/**
 *******************************************************************************
 ** \brief GPIO PIN类型定义
 ******************************************************************************/
typedef enum en_gpio_pin
{
    GpioPin0  = 0u,                 ///< GPIO PIN0
    GpioPin1  = 1u,                 ///< GPIO PIN1
    GpioPin2  = 2u,                 ///< GPIO PIN2
    GpioPin3  = 3u,                 ///< GPIO PIN3
    GpioPin4  = 4u,                 ///< GPIO PIN4
    GpioPin5  = 5u,                 ///< GPIO PIN5
    GpioPin6  = 6u,                 ///< GPIO PIN6
    GpioPin7  = 7u,                 ///< GPIO PIN7
}en_gpio_pin_t;

/**
 *******************************************************************************
 ** \brief GPIO 端口复用功能(AF-Alternate function)类型定义
 ** \note  具体功能及含义请参考用户手册GPIO复用表
 ******************************************************************************/
typedef enum en_gpio_af
{
    GpioAf0  = 0u,      ///< GPIO功能
    GpioAf1  = 1u,      ///< GPIO AF1:复用功能1
    GpioAf2  = 2u,      ///< GPIO AF2:复用功能2
    GpioAf3  = 3u,      ///< GPIO AF3:复用功能3
    GpioAf4  = 4u,      ///< GPIO AF4:复用功能4
    GpioAf5  = 5u,      ///< GPIO AF5:复用功能5
    GpioAf6  = 6u,      ///< GPIO AF6:复用功能6
    GpioAf7  = 7u,      ///< GPIO AF7:复用功能7
}en_gpio_af_t;

/**
 *******************************************************************************
 ** \brief GPIO输入输出配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_dir
{
    GpioDirOut = 0u,                ///< GPIO 输出
    GpioDirIn  = 1u,                ///< GPIO 输入
}en_gpio_dir_t;

/**
 *******************************************************************************
 ** \brief GPIO端口上拉配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_pu
{
    GpioPuDisable = 0u,                ///< GPIO无上拉
    GpioPuEnable  = 1u,                ///< GPIO上拉
}en_gpio_pu_t;

/**
 *******************************************************************************
 ** \brief GPIO端口下拉配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_pd
{
    GpioPdDisable = 0u,                ///< GPIO无下拉
    GpioPdEnable  = 1u,                ///< GPIO下拉
}en_gpio_pd_t;
/**
 *******************************************************************************
 ** \brief GPIO端口输出驱动能力配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_drv
{
    GpioDrvH = 0u,                  ///< GPIO高驱动能力
    GpioDrvL = 1u,                  ///< GPIO低驱动能力
}en_gpio_drv_t;

/**
 *******************************************************************************
 ** \brief GPIO端口开漏输出控制数据类型定义
 ******************************************************************************/
typedef enum en_gpio_od
{
    GpioOdDisable = 0u,             ///< GPIO开漏输出关闭
    GpioOdEnable  = 1u,             ///< GPIO开漏输出使能
}en_gpio_od_t;

/**
 *******************************************************************************
 ** \brief GPIO中断触发方式类型定义
 ******************************************************************************/
typedef enum en_gpio_irqtype
{
    GpioIrqHigh     = 0u,           ///< GPIO高电平触发
    GpioIrqLow      = 1u,           ///< GPIO低电平触发
    GpioIrqRising   = 2u,           ///< GPIO上升沿触发
    GpioIrqFalling  = 3u,           ///< GPIO下降沿触发
}en_gpio_irqtype_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）端口中断模式类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_irqmode
{
    GpioSfIrqDpslpMode  = 1u,        ///< Deep Sleep模式
    GpioSfIrqActSlpMode = 0u,        ///< Active/Sleep模式
}en_gpio_sf_irqmode_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）HCLK输出门控类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_hclkout_g
{
    GpioSfHclkOutDisable = 0u,       ///< HCLK输出门控关闭
    GpioSfHclkOutEnable  = 1u,       ///< HCLK输出门控使能
}en_gpio_sf_hclkout_g_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）HCLK输出分频选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_hclkout_div
{
    GpioSfHclkOutDiv1 = 0u,         ///< HCLK
    GpioSfHclkOutDiv2 = 1u,         ///< HCLK/2
    GpioSfHclkOutDiv4 = 2u,         ///< HCLK/4
    GpioSfHclkOutDiv8 = 3u,         ///< HCLK/8
}en_gpio_sf_hclkout_div_t;
/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCLK输出门控类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pclkout_g
{
    GpioSfPclkOutDisable = 0u,       ///< PCLK输出门控关闭
    GpioSfPclkOutEnable  = 1u,       ///< PCLK输出门控使能
}en_gpio_sf_pclkout_g_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCLK输出分频选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pclkout_div
{
    GpioSfPclkOutDiv1 = 0u,         ///< PCLK
    GpioSfPclkOutDiv2 = 1u,         ///< PCLK/2
    GpioSfPclkOutDiv4 = 2u,         ///< PCLK/4
    GpioSfPclkOutDiv8 = 3u,         ///< PCLK/8
}en_gpio_sf_pclkout_div_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）IR输出极性选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_irpol
{
    GpioSfIrP = 0u,                  ///< IR正向输出
    GpioSfIrN = 1u,                  ///< IR反向输出
}en_gpio_sf_irpol_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）SSN与外部时钟输入信号源选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_ssn_extclk
{
    GpioSfSsnExtClkH    = 0u,        ///< 高电平
    GpioSfSsnExtClkP35 = 1u,        ///< P35
    GpioSfSsnExtClkP36 = 2u,        ///< P36
    GpioSfSsnExtClkP01 = 3u,        ///< P01
    GpioSfSsnExtClkP02 = 4u,        ///< P02
    GpioSfSsnExtClkP03 = 5u,        ///< P03
    GpioSfSsnExtClkP15 = 6u,        ///< P15
    GpioSfSsnExtClkP14 = 7u,        ///< P14
    GpioSfSsnExtClkP23 = 8u,        ///< P23
    GpioSfSsnExtClkP24 = 9u,        ///< P24
    GpioSfSsnExtClkP25 = 10u,       ///< P25
    GpioSfSsnExtClkP26 = 11u,       ///< P26
    GpioSfSsnExtClkP27 = 12u,       ///< P27
    GpioSfSsnExtClkP31 = 13u,       ///< P31
    GpioSfSsnExtClkP32 = 14u,       ///< P32
    GpioSfSsnExtClkP33 = 15u,       ///< P33
}en_gpio_sf_ssn_extclk_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器互联功能选择类型定义
 ** \note  具体功能及含义请参考用户手册GPIO辅助寄存器描述
 ******************************************************************************/
typedef enum en_gpio_sf
{
    GpioSf0 = 0u,       ///< SF0:PX_SEL的配置功能
    GpioSf1 = 1u,       ///< SF1:辅助功能1
    GpioSf2 = 2u,       ///< SF2:辅助功能2
    GpioSf3 = 3u,       ///< SF3:辅助功能3
    GpioSf4 = 4u,       ///< SF4:辅助功能4
    GpioSf5 = 5u,       ///< SF5:辅助功能5
    GpioSf6 = 6u,       ///< SF6:辅助功能6
    GpioSf7 = 7u,       ///< SF7:辅助功能7
}en_gpio_sf_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器门控类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_g
{
    GpioSfTim0G  = 0u,                   ///<Tim0定时器GATE输入选择
    GpioSfTim1G  = 2u,                   ///<Tim1定时器GATE输入选择
    GpioSfTim2G  = 4u,                   ///<Tim2定时器GATE输入选择
    GpioSfTim3G  = 6u,                   ///<Tim3定时器GATE输入选择
}en_gpio_sf_tim_g_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器ETR类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_e
{
    GpioSfTim0E  = 0u,                   ///<Tim0定时器ETR输入选择
    GpioSfTim1E  = 3u,                   ///<Tim1定时器ETR输入选择
    GpioSfTim2E  = 6u,                   ///<Tim2定时器ETR输入选择
    GpioSfTim3E  = 9u,                   ///<Tim3定时器ETR输入选择
    GpioSfLpTimE = 12u,                  ///<LPTim定时器ETR输入选择
}en_gpio_sf_tim_e_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器捕获输入类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_c
{
    GpioSfTim4CB = 0u,                   ///<Tim4定时器CHB输入选择
    GpioSfTim5CB = 2u,                   ///<Tim5定时器CHB输入选择
    GpioSfTim6CB = 4u,                   ///<Tim6定时器CHB输入选择
    GpioSfTim4CA = 6u,                   ///<Tim4定时器CHA输入选择
    GpioSfTim5CA = 8u,                   ///<Tim5定时器CHA输入选择
    GpioSfTim6CA = 10u,                  ///<Tim6定时器CHA输入选择
}en_gpio_sf_tim_c_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCA捕获选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pca
{
    GpioSfPcaCapCH0 = 0u,                   ///<PCA捕获通道0信号来源选择
    GpioSfPcaCapCH1 = 2u,                   ///<PCA捕获通道1信号来源选择
    GpioSfPcaCapCH2 = 4u,                   ///<PCA捕获通道2信号来源选择
    GpioSfPcaCapCH3 = 6u,                   ///<PCA捕获通道3信号来源选择
    GpioSfPcaCapCH4 = 8u,                   ///<PCA捕获通道4信号来源选择
}en_gpio_sf_pca_t;

/**
 *******************************************************************************
 ** \brief GPIO 端口配置结构体定义
 ******************************************************************************/
typedef struct
{
    boolean_t           bOutputVal;      ///< 默认端口输出电平
    en_gpio_dir_t       enDir;           ///< 端口方向配置
    en_gpio_drv_t       enDrv;           ///< 端口驱动能力配置
    en_gpio_pu_t        enPu;            ///< 端口上拉配置
    en_gpio_pd_t        enPd;            ///< 端口下拉配置
    en_gpio_od_t        enOD;            ///< 端口开漏输出配置
}stc_gpio_cfg_t;

/*******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
 ///< GPIO IO初始化/去初始化
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_cfg_t *pstcGpioCfg);

///< GPIO 获取端口输入电平
boolean_t   Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort);

///< GPIO 设置端口输出
///< GPIO 端口输出电平配置及获取
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal);
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO 设置端口为模拟功能
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO 设置端口为端口复用功能
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf);

///< GPIO 端口中断控制功能使能/关闭
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
///< GPIO 中断状态获取
boolean_t   Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO 中断标志清除
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO 端口辅助功能配置
///< GPIO 中断模式配置
en_result_t Gpio_SfIrqModeCfg(en_gpio_sf_irqmode_t enIrqMode);
///< GPIO IR输出极性配置
en_result_t Gpio_SfIrPolCfg(en_gpio_sf_irpol_t enIrPolMode);
///< GPIO HCLK输出配置
en_result_t Gpio_SfHClkOutputCfg(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv);
///< GPIO PCLK输出配置
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv);
///< GPIO 外部时钟输入配置
en_result_t Gpio_SfExtClkCfg(en_gpio_sf_ssn_extclk_t enExtClk);
///< GPIO SPI SSN输入配置
en_result_t Gpio_SfSsnCfg(en_gpio_sf_ssn_extclk_t enSsn);
///< GPIO Timer 门控输入配置
en_result_t Gpio_SfTimGCfg(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf);
///< GPIO Timer ETR选择配置
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
///< GPIO Timer 捕获输入配置
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
///< GPIO PCA捕获选择配置
en_result_t Gpio_SfPcaCfg(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf);


//@} // GpioGroup

/*****************************************************************************/
/** \file i2c.h
 **
 ** Headerfile for I2C functions
 **
 **
 ** History:
 **   - 2018-03-1   CJ    First Version
 **
 *****************************************************************************/




/**
 *******************************************************************************
 ** \defgroup I2cGroup Inter-Integrated Circuit (I2C)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/******************************************************************************
 * Global type definitions
 ******************************************************************************/

 /**
 ******************************************************************************
 ** \brief I2C功能配置
 *****************************************************************************/
typedef enum en_i2c_func
{
    I2cModule_En = 6u,  ///<I2C模块使能
    I2cStart_En  = 5u, ///<开始信号
    I2cStop_En   = 4u, ///<结束信号
    I2cAck_En    = 2u, ///<应答信号
    I2cHlm_En    = 0u, ///<高速使能
}en_i2c_func_t;

 /**
 ******************************************************************************
 ** \brief I2C模式配置
 *****************************************************************************/
typedef enum en_i2c_mode
{
    I2cMasterMode = 0x40u,  ///<I2C主机模式
    I2cSlaveMode  = 0x44u,  ///<I2C从机模式
}en_i2c_mode_t;

/**
 ******************************************************************************
 ** \brief I2C初始化配置结构
 *****************************************************************************/
typedef struct stc_i2c_cfg
{
    uint32_t        u32Pclk;        ///<Pclk 设置(Hz)
    uint32_t        u32Baud;        ///<I2C通信波特率(Hz)
    en_i2c_mode_t   enMode;         ///<I2C主从模式配置
    uint8_t         u8SlaveAddr;    ///<从机地址配置(如果需要)
    boolean_t       bGc;            ///<广播地址使能(如果需要)
}stc_i2c_cfg_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
 //I2C初始化函数
 en_result_t I2C_Init(M0P_I2C_TypeDef* I2Cx,stc_i2c_cfg_t *pstcI2CCfg);
 //设置波特率配置寄存器
 en_result_t I2C_SetBaud(M0P_I2C_TypeDef* I2Cx,uint8_t u8Tm);
 //I2C功能设置函数
 en_result_t I2C_SetFunc(M0P_I2C_TypeDef* I2Cx,en_i2c_func_t enFunc);
  //I2C功能清除函数
 en_result_t I2C_ClearFunc(M0P_I2C_TypeDef* I2Cx,en_i2c_func_t enFunc);
 //获取中断标记SI
 boolean_t I2C_GetIrq(M0P_I2C_TypeDef* I2Cx);
  //清除中断标记SI
 en_result_t I2C_ClearIrq(M0P_I2C_TypeDef* I2Cx);
 //获取状态
 uint8_t I2C_GetState(M0P_I2C_TypeDef* I2Cx);

 //字节写函数
 en_result_t I2C_WriteByte(M0P_I2C_TypeDef* I2Cx,uint8_t u8Data);

//字节读函数
uint8_t I2C_ReadByte(M0P_I2C_TypeDef* I2Cx);

//@} // I2cGroup

/*****************************************************************************/
/** \file lpm.h
 **
 ** Lpm 数据结构及API声明
 **
 **
 ** History:
 **   - 2017-06-06   Lux     V1.0
 **
 *****************************************************************************/


/*****************************************************************************
 * Include files
 *****************************************************************************/


/**
 *******************************************************************************
 ** \defgroup LpmGroup Low Power Management (LPM)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************
 ** Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
///<功能配置及操作函数
///<进入普通休眠模式
void Lpm_GotoSleep(boolean_t bOnExit);
///<进入深度休眠模式
void Lpm_GotoDeepSleep(boolean_t bOnExit);

//@} // LpmGroup

/******************************************************************************/
/** \file lvd.h
 **
 ** Headerfile for Low Voltage Detector functions
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/


/******************************************************************************
 * Include files
 ******************************************************************************/


/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup LvdGroup Low Voltage Detector (LVD)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief LVD监测电压源选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_lvd_input_src
{
    LvdInputSrcMskVCC = 0u<<2,                ///< Vcc
    LvdInputSrcMskP03 = 1u<<2,                ///< P03
    LvdInputSrcMskP23 = 2u<<2,                ///< P23
    LvdInputSrcMskP25 = 3u<<2,                ///< P25
}en_lvd_input_src_t;

/**
 ******************************************************************************
 ** \brief LVD阈值电压选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_lvd_threshold
{
    LvdMskTH1_8V = 0u<<4,                  ///< 1.8V
    LvdMskTH1_9V = 1u<<4,                  ///< 1.9V
    LvdMskTH2_0V = 2u<<4,                  ///< 2.0V
    LvdMskTH2_1V = 3u<<4,                  ///< 2.1V
    LvdMskTH2_2V = 4u<<4,                  ///< 2.2V
    LvdMskTH2_3V = 5u<<4,                  ///< 2.3V
    LvdMskTH2_4V = 6u<<4,                  ///< 2.4V
    LvdMskTH2_5V = 7u<<4,                  ///< 2.5V
    LvdMskTH2_6V = 8u<<4,                  ///< 2.6V
    LvdMskTH2_7V = 9u<<4,                  ///< 2.7V
    LvdMskTH2_8V = 10u<<4,                 ///< 2.8V
    LvdMskTH2_9V = 11u<<4,                 ///< 2.9V
    LvdMskTH3_0V = 12u<<4,                 ///< 3.0V
    LvdMskTH3_1V = 13u<<4,                 ///< 3.1V
    LvdMskTH3_2V = 14u<<4,                 ///< 3.2V
    LvdMskTH3_3V = 15u<<4,                 ///< 3.3V
}en_lvd_threshold_t;

/**
 ******************************************************************************
 ** \brief LVD输出滤波时间
 **
 ** \note
 ******************************************************************************/
typedef enum en_lvd_filter_time
{
    LvdFilterMsk7us    = 0u<<9,                   ///< 7us
    LvdFilterMsk14us   = 1u<<9,                   ///< 14us
    LvdFilterMsk28us   = 2u<<9,                   ///< 28us
    LvdFilterMsk112us  = 3u<<9,                   ///< 112us
    LvdFilterMsk450us  = 4u<<9,                   ///< 450us
    LvdFilterMsk1_8ms  = 5u<<9,                   ///< 1.8ms
    LvdFilterMsk7_2ms  = 6u<<9,                   ///< 7.3ms
    LvdFilterMsk28_8ms = 7u<<9,                   ///< 28.8ms
}en_lvd_filter_time_t;

/**
 ******************************************************************************
 ** \brief LVD中断触发方式
 **
 ** \note
 ******************************************************************************/
typedef enum en_lvd_irq_type
{
    LvdIrqMskRiseFall = 3u<<12,                 ///< 上升/下降沿触发
    LvdIrqMskHigh     = 1u<<14,                 ///< 高电平触发
    LvdIrqMskRise     = 1u<<13,                 ///< 上升沿触发
    LvdIrqMskFall     = 1u<<12,                 ///< 下降沿触发
}en_lvd_irq_type_t;

/**
 ******************************************************************************
 ** \brief LVD触发动作选择
 **
 ** \note
 ******************************************************************************/
typedef enum en_lvd_act
{
    LvdActMskReset = 1u<<1,              ///< 系统复位
    LvdActMskInt   = 0u,                 ///< NVIC中断
}en_lvd_act_t;

/**
 ******************************************************************************
 ** \brief LVD数字滤波使能配置
 **
 ** \note
 ******************************************************************************/
typedef enum en_lvd_filter
{
    LvdFilterMskEnable  = 1u<<8,         ///< 数字滤波使能
    LvdFilterMskDisable = 0u,            ///< 数字滤波禁止
}en_lvd_filter_t;

/**
 ******************************************************************************
 ** \brief LVD配置
 ** \note
 ******************************************************************************/
typedef struct stc_lvd_cfg
{
    en_lvd_act_t            enAct;          ///< LVD触发动作
    en_lvd_input_src_t      enInputSrc;     ///< LVD输入电压源
    en_lvd_threshold_t      enThreshold;    ///< LVD监测电压
    en_lvd_filter_t         enFilter;       ///< 是否使用输出滤波
    en_lvd_filter_time_t    enFilterTime;   ///< 输出滤波时间
    en_lvd_irq_type_t       enIrqType;      ///< 中断触发方式
}stc_lvd_cfg_t;


/******************************************************************************
 * Global definitions
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
//irq enable/disable
void Lvd_EnableIrq(void);
void Lvd_DisableIrq(void);

// irq function
void Lvd_ClearIrq(void);
boolean_t Lvd_GetIrqStat(void);

//init/deinit function
void Lvd_Init(stc_lvd_cfg_t *pstcCfg);

//LVD function enable/disable
void Lvd_Enable(void);
void Lvd_Disable(void);

//@} // LvdGroup

/*****************************************************************************/
/** \file pca.h
 **
 ** PCA（可编程计数阵列）数据结构及API声明
 **
 **
 ** History:
 **   - 2019-04-09        First version
 **
 *****************************************************************************/


/*****************************************************************************
 * Include files
 *****************************************************************************/


/**
 ******************************************************************************
 ** \defgroup PcaGroup Programmable Counter Array (PCA)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief PCA  模块选择
 ** \note
 ******************************************************************************/
typedef enum
{
    PcaModule0 = 0,      //  PCA_0
    PcaModule1 = 1,      //  PCA_1
    PcaModule2 = 2,      //  PCA_2
    PcaModule3 = 3,      //  PCA_3
    PcaModule4 = 4       //  PCA_4
}en_pca_module_t;

/**
 *******************************************************************************
 ** \brief PCA  中断标志位  中断清除位
 ** \note           PCA_CCON中的CCF0-CCF4与CF; PCA_ICLR中的CCF0-CCF4与CF
 ******************************************************************************/
typedef enum
{
    PcaCcf0 = 0,
    PcaCcf1 = 1,
    PcaCcf2 = 2,
    PcaCcf3 = 3,
    PcaCcf4 = 4,
    PcaCf   = 7
}en_pca_ccficlr_t;

/**
 *******************************************************************************
 ** \brief PCA  时钟分频选择及时钟源选择
 ** \note       PCA_CMOD   CPS[2:0]
 ******************************************************************************/
typedef enum
{
    PcaPclkdiv32 = 0,      // PCLK/32
    PcaPclkdiv16 = 1,      // PCLK/16
    PcaPclkdiv8  = 2,      // PCLK/8
    PcaPclkdiv4  = 3,      // PCLK/4
    PcaPclkdiv2  = 4,      // PCLK/2
    PcaTim0ovf   = 5,      // timer0 overflow
    PcaTim1ovf   = 6,      // timer1 overflow
    PcaEci       = 7       // ECI外部时钟
}en_pca_clksrc_t;

/**
 *******************************************************************************
 ** \brief PCA  允许比较器功能控制
 ** \note       PCA_CCAPMx   ECOM
 ******************************************************************************/
typedef enum
{
    PcaEcomDisable = 0,
    PcaEcomEnable  = 1
}en_pca_ecom_t;

/**
 *******************************************************************************
 ** \brief PCA  正沿捕获控制位
 ** \note       PCA_CCAPMx  CAPP
 ******************************************************************************/
typedef enum
{
    PcaCappDisable = 0,
    PcaCappEnable  = 1
}en_pca_capp_t;

/**
 *******************************************************************************
 ** \brief PCA  负沿捕获控制位
 ** \note       PCA_CCAPMx  CAPN
 ******************************************************************************/
typedef enum
{
    PcaCapnDisable = 0,
    PcaCapnEnable  = 1
}en_pca_capn_t;

/**
 *******************************************************************************
 ** \brief PCA  匹配控制位
 ** \note       PCA_CCAPMx  MAT
 ******************************************************************************/
typedef enum
{
    PcaMatDisable = 0,
    PcaMatEnable  = 1
}en_pca_mat_t;

/**
 *******************************************************************************
 ** \brief PCA  翻转控制位
 ** \note       PCA_CCAPMx  TOG
 ******************************************************************************/
typedef enum
{
    PcaTogDisable = 0,
    PcaTogEnable  = 1
}en_pca_tog_t;

/**
 *******************************************************************************
 ** \brief PCA  PWM控制位
 ** \note       PCA_CCAPMx  PWM
 ******************************************************************************/
typedef enum
{
    PcaPwm8bitDisable = 0,
    PcaPwm8bitEnable  = 1
}en_pca_pwm8bit_t;

/**
 *******************************************************************************
 ** \brief PCA  EPWM控制位
 ** \note       PCA_EPWM  EPWM
 ******************************************************************************/
typedef enum
{
    PcaEpwmDisable = 0,
    PcaEpwmEnable  = 1
}en_pca_epwm_t;

/**
 *******************************************************************************
 ** \brief PCA  初始化配置的结构体
 ** \note
 ******************************************************************************/
typedef struct
{
    en_pca_clksrc_t     pca_clksrc;           // PCA_CMOD CPS[2:0]
    boolean_t           pca_cidl;             // PCA_CMOD CIDL
    en_pca_ecom_t       pca_ecom;             // PCA_CCAPMx ECOM
    en_pca_capp_t       pca_capp;             // PCA_CCAPMx CAPP
    en_pca_capn_t       pca_capn;             // PCA_CCAPMx CAPN
    en_pca_mat_t        pca_mat;              // PCA_CCAPMx MAT
    en_pca_tog_t        pca_tog;              // PCA_CCAPMx TOG
    en_pca_pwm8bit_t    pca_pwm;              // PCA_CCAPMx PWM

    uint16_t            pca_ccap;             // PCA_CCAP
    uint8_t             pca_ccapl;            // PCA_CCAPL  PCA_CCAP的低字节
    uint8_t             pca_ccaph;            // PCA_CCAPH  PCA_CCAP的高字节

}stc_pcacfg_t;
/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
extern boolean_t Pca_GetItStatus(en_pca_ccficlr_t It_Src);
extern void Pca_ClrItStatus(en_pca_ccficlr_t It_Src);
extern void Pca_StartPca(boolean_t NewStatus);
extern void Pca_SetCidl(boolean_t NewStatus);
extern void Pca_Set4Wdte(boolean_t NewStatus);
extern void Pca_ConfPcaIt(boolean_t NewStatus);
extern void Pca_ConfModulexIt(en_pca_module_t Modulex, boolean_t NewStatus);
extern void Pca_M0Init(stc_pcacfg_t* InitStruct);
extern void Pca_M1Init(stc_pcacfg_t* InitStruct);
extern void Pca_M2Init(stc_pcacfg_t* InitStruct);
extern void Pca_M3Init(stc_pcacfg_t* InitStruct);
extern void Pca_M4Init(stc_pcacfg_t* InitStruct);
extern uint16_t Pca_GetCnt(void);
extern void Pca_SetCnt(uint16_t cnt);
extern boolean_t Pca_GetOut(en_pca_module_t Modulex);
extern void Pca_SetCcap(en_pca_module_t Modulex, uint16_t Value);
extern uint16_t Pca_GetCcap(en_pca_module_t Modulex);
extern void Pca_SetCcapHL(en_pca_module_t Modulex, uint8_t ValueH, uint8_t ValueL);
extern void Pca_GetCcapHL(en_pca_module_t Modulex, uint8_t *ValueH, uint8_t *ValueL);

//@} // PcaGroup

/******************************************************************************/
/** \file ram.h
 **
 ** RAM 数据结构及API声明.
 **
 ** - 2019-04-02 LuX V1.0
 **
 ******************************************************************************/


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup RamGroup Ram Controller (Ram)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief Redefinition of RAM register structure
 ******************************************************************************/

/******************************************************************************
 * Global definitions
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


///<中断相关函数
///<中断使能/禁止
extern void Ram_EnableIrq (void);
extern void Ram_DisableIrq(void);
///<中断标志获取
extern boolean_t Ram_GetIntFlag(void);
///<中断标志清除
extern void Ram_ClearIntFlag(void);
///<奇偶校验出错地址获取
extern uint32_t Ram_ErrAddrGet(void);

//@} // RamGroup

/******************************************************************************/
/** \file reset.h
 **
 ** Headerfile for reset functions
 **
 **
 ** History:
 **   - 2018-04-21   Lux     First Version
 **
 ******************************************************************************/


/******************************************************************************
 * Include files
 ******************************************************************************/



/**
 ******************************************************************************
 ** \defgroup ResetGroup Reset (RST)
 **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/*******************************************************************************
 * Global definitions
 ******************************************************************************/


/**
 *******************************************************************************
 ** \brief 外设复位控制类型定义
 ** \note
 ******************************************************************************/
typedef enum en_sysctrl_peripheral
{
    ResetMskUart0      = 1u<<0u,       ///< 串口0
    ResetMskUart1      = 1u<<1u,       ///< 串口1
    ResetMskI2c        = 1u<<4u,       ///< I2C
    ResetMskSpi        = 1u<<6u,       ///< SPI
    ResetMskBaseTim    = 1u<<8u,       ///< 基础定时器TIM0/1/2
    ResetMskAdvTim     = 1u<<10u,      ///< 高级定时器TIM4/5/6
    ResetMskPca        = 1u<<14u,      ///< 可编程计数阵列
    ResetMskAdcBgr     = 1u<<16u,      ///< ADC&BGR
    ResetMskVcLvd      = 1u<<17u,      ///< VC和LVD
    ResetMskTrim       = 1u<<21u,      ///< 时钟校准
    ResetMskTick       = 1u<<24u,      ///< 系统定时器
    ResetMskCrc        = 1u<<26u,      ///< CRC
    ResetMskGpio       = 1u<<28u,      ///< GPIO
}en_reset_peripheral_t;


/**
 *******************************************************************************
 ** \brief 复位源（标识）显示
 **
 ** \note
 ******************************************************************************/
typedef enum en_reset_flag
{
    ResetFlagMskPor5V     = 1u<<0u,         ///< 5V启动复位
    ResetFlagMskPor1_5V   = 1u<<1u,         ///< 1.5V启动复位
    ResetFlagMskLvd       = 1u<<2u,         ///< 低电压检测复位
    ResetFlagMskWdt       = 1u<<3u,         ///< 看门狗复位
    ResetFlagMskPca       = 1u<<4u,         ///< PCA复位
    ResetFlagMskLockup    = 1u<<5u,         ///< 系统异常复位
    ResetFlagMskSysreq    = 1u<<6u,         ///< 软件复位
    ResetFlagMskRstb      = 1u<<7u,         ///< RESET脚 复位
}en_reset_flag_t;

/*******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 获得复位源状态
boolean_t Reset_GetFlag(en_reset_flag_t enRstFlg);
///< 清除复位源状态
void Reset_ClearFlag(en_reset_flag_t enRstFlg);
void Reset_ClearFlagAll(void);

///< 外设模块复位
void Reset_RstPeripheralAll(void);
void Reset_RstPeripheral(en_reset_peripheral_t enPeri);

//@} // ResetGroup

/*****************************************************************************/
/** \file spi.h
 **
 ** Headerfile for SPI functions
 **
 **
 ** History:
 **   - 2017-05-17  1.0  Devi     First Version
 **
 *****************************************************************************/

/******************************************************************************
 * Include files
 *****************************************************************************/


/* C binding of definitions if building with C++ compiler */

//@{

/******************************************************************************
 * Global type definitions
 *****************************************************************************/
 /**
 ******************************************************************************
 ** \brief SPI 功能通道选择设置
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief SPI 功能使能设置
 ******************************************************************************/
typedef enum en_spi_en
{
    SpiMskEnable     = 0x4u,    ///< SPI模块使能
    SpiMskDisable    = 0u,      ///< SPI模块禁止
}en_spi_en_t;
/**
 ******************************************************************************
 ** \brief SPI 模式配置
 ******************************************************************************/
typedef enum en_spi_mode
{
    SpiMskMaster = 0x10u,  ///<主机
    SpiMskSlave  = 0x00u,  ///<从机
}en_spi_mode_t;
/**
 ******************************************************************************
 ** \brief SPI 时钟极性设置
 ******************************************************************************/
typedef enum en_spi_cpol
{
    SpiMskcpollow  = 0u,       ///<极性为低
    SpiMskcpolhigh = 0x08u,    ///<极性为高
}en_spi_cpol_t;
/**
 ******************************************************************************
 ** \brief SPI 时钟相位设置
 ******************************************************************************/
typedef enum en_spi_cpha
{
    SpiMskCphafirst  = 0u,      ///<第一边沿采样
    SpiMskCphasecond = 0x4u,    ///<第二边沿采样
}en_spi_cpha_t;
/**
 ******************************************************************************
 ** \brief SPI 时钟分频配置
 *****************************************************************************/
typedef enum en_spi_clk_div
{
    SpiClkMskDiv2   = 0x00u,   ///<2分频
    SpiClkMskDiv4   = 0x01u,   ///<4分频
    SpiClkMskDiv8   = 0x02u,   ///<8分频
    SpiClkMskDiv16  = 0x03u,   ///<16分频
    SpiClkMskDiv32  = 0x80u,   ///<32分频
    SpiClkMskDiv64  = 0x81u,   ///<64分频
    SpiClkMskDiv128 = 0x82u,   ///<128分频
}en_spi_clk_div_t;

/**
 ******************************************************************************
 ** \brief SPI 片选脚电平选择
 *****************************************************************************/
typedef enum en_spi_cspin
{
    SpiCsLow  = 0u,      ///<片选低电平
    SpiCsHigh = 1u,      ///<片选高电平
}en_spi_cspin_t;

/**
 ******************************************************************************
 ** \brief SPI 状态
 *****************************************************************************/
typedef enum en_spi_status
{
    SpiIf              = 0x80,   ///<传输结束中断标志
    SpiWcol            = 0x40,   ///<写冲突标志
    SpiSserr           = 0x20,   ///<从机模式错误标志
    SpiMdf             = 0x10,   ///<主机模式错误标志
}en_spi_status_t;
/**
 ******************************************************************************
 ** \brief SPI 总体配置结构体
 *****************************************************************************/
typedef struct stc_spi_cfg
{
    en_spi_mode_t       enSpiMode;          ///< 主从模式选择
    en_spi_clk_div_t    enPclkDiv;          ///< PCLK分频系数(波特率分频)
    en_spi_cpol_t       enCPOL;             ///< 时钟极性选择
    en_spi_cpha_t       enCPHA;             ///< 时钟相位选择
}stc_spi_cfg_t;

//SPI 状态获取
boolean_t Spi_GetStatus(M0P_SPI_TypeDef* SPIx,en_spi_status_t enStatus);

///<SPI 中断使能/禁止
en_result_t Spi_IrqEnable(M0P_SPI_TypeDef* SPIx);
en_result_t Spi_IrqDisable(M0P_SPI_TypeDef* SPIx);
//SPI初始化函数
en_result_t Spi_Init(M0P_SPI_TypeDef* SPIx,stc_spi_cfg_t* pstcSpiCfg);
//SPI关闭函数
en_result_t Spi_DeInit(M0P_SPI_TypeDef* SPIx);
//SPI 配置主发送的电平
void Spi_SetCS(M0P_SPI_TypeDef* SPIx,boolean_t bFlag);
//SPI 数据发送
en_result_t Spi_SendData(M0P_SPI_TypeDef* SPIx, uint8_t u8Data);
//SPI 数据接收
uint8_t Spi_ReceiveData(M0P_SPI_TypeDef* SPIx);

//@} // Spi Group

/*****************************************************************************/
/** \file trim.h
 **
 ** TRIM 数据结构及API声明
 **
 **
 ** History:
 **   - 2018-04-21   Lux     V1.0
 **
 *****************************************************************************/


/*****************************************************************************
 * Include files
 *****************************************************************************/



/**
 ******************************************************************************
 ** \defgroup TrimGroup Clock Trimming (TRIM)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 ** Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

 /**
 ******************************************************************************
 ** \brief 监测模式使能枚举重定义    (MON_EN)
 *****************************************************************************/
typedef enum en_trim_monitor
{
    TrimMonDisable = 0u,            ///< 禁止
    TrimMonEnable  = 0x40u,         ///< 使能
}en_trim_monitor_t;

 /**
 ******************************************************************************
 ** \brief 待校准/监测时钟选择枚举重定义 (CALCLK_SEL)
 *****************************************************************************/
typedef enum en_trim_calclksel
{
    TrimCalMskRCH = 0x000u,            ///< RCH
    TrimCalMskXTH = 0x010u,            ///< XTH
    TrimCalMskRCL = 0x020u,            ///< RCL
    TrimCalMskXTL = 0x030u,            ///< XTL
}en_trim_calclksel_t;

/**
 ******************************************************************************
 ** \brief 参考时钟选择枚举重定义 (REFCLK_SEL)
 *****************************************************************************/
typedef enum en_trim_refclksel
{
    TrimRefMskRCH    = 0x0u,            ///< RCH
    TrimRefMskXTH    = 0x2u,            ///< XTH
    TrimRefMskRCL    = 0x4u,            ///< RCL
    TrimRefMskXTL    = 0x6u,            ///< XTL
    TrimRefMskIRC10K = 0x8u,            ///< IRC10K
    TrimRefMskExtClk = 0xau,            ///< 外部输入时钟
}en_trim_refclksel_t;

/**
 ******************************************************************************
 ** \brief 中断标志类型枚举重定义
 *****************************************************************************/
typedef enum en_trim_inttype
{
    TrimStop     = 0x01u,            ///< 参考计数器停止标志
    TrimCalCntOf = 0x02u,            ///< 校准计数器溢出标志
    TrimXTLFault = 0x04u,            ///< XTL 失效标志
    TrimXTHFault = 0x08u,            ///< XTH 失效标志
}en_trim_inttype_t;

/**
 ******************************************************************************
 ** \brief TRIM 配置结构体定义
 *****************************************************************************/
typedef struct stc_trim_cfg
{
    en_trim_monitor_t    enMON;         ///< 监测模式使能
    en_trim_calclksel_t  enCALCLK;      ///< 校准时钟选择
    uint32_t             u32CalCon;     ///< 校准计数器溢出值配置
    en_trim_refclksel_t  enREFCLK;      ///< 参考时钟选择
    uint32_t             u32RefCon;     ///< 参考计数器初值配置
}stc_trim_cfg_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
///<<功能配置及操作函数
///<Trim 配置及初始化
en_result_t Trim_Init(stc_trim_cfg_t* pstcCfg);
///<校准/监测启动/停止
void Trim_Run(void);
void Trim_Stop(void);

///<参考计数器计数值获取
uint32_t Trim_RefCntGet(void);
///<校准计数器计数值获取
uint32_t Trim_CalCntGet(void);

///<中断操作相关函数
///中断使能/禁止
void Trim_EnableIrq(void);
void Trim_DisableIrq(void);
///<中断标志获取
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType);
///<中断标志清除
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType);

//@} // TrimGroup

/*****************************************************************************/
/** \file uart.h
 **
 ** Headerfile for UART functions
 **
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

/*****************************************************************************
 * Include files
 *****************************************************************************/


/**
 ******************************************************************************
 ** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief uart多主机模式地址帧/数据帧或者奇偶校验
 ******************************************************************************/
typedef enum en_uart_mmdorck
{
    UartData = 0u, ///<多主机模式时，数据帧TB8标记
    UartAddr = 1u, ///<多主机模式时，地址帧TB8标记
}en_uart_mmdorck_t;
/**
 ******************************************************************************
 ** \brief uart奇偶校验
 ******************************************************************************/
typedef enum en_uart_check
{
    UartEven = 0u, ///<偶校验
    UartOdd  = 1u, ///<奇校验
}en_uart_check_t;
/**
 ******************************************************************************
 ** \brief uart多主机模式配置
 ******************************************************************************/
typedef enum en_uart_multimode
{
    UartNormal = 0u, ///<正常工作模式
    UartMulti  = 1u, ///<多主机工作模式
}en_uart_multimode_t;
/**
 ******************************************************************************
 ** \brief uart多主机模式及从机地址和地址掩码配置
 ******************************************************************************/

typedef struct stc_uart_multimode
{
    uint8_t             u8SlaveAddr;  ///<从机地址
    uint8_t             u8SaddEn;     ///<从及地址掩码
}stc_uart_multimode_t;

/**
 ******************************************************************************
 ** \brief uart 四种工作模式选择
 ******************************************************************************/

typedef enum en_uart_mode
{
    UartMode0 = 0u, ///<模式0
    UartMode1 = 1u, ///<模式1
    UartMode2 = 2u, ///<模式2
    UartMode3 = 3u, ///<模式3
} en_uart_mode_t;
/**
 ******************************************************************************
 ** \brief uart 发送接收功能使能
 ******************************************************************************/
typedef enum en_uart_func
{
    UartRenFunc    = 4u,    ///<0-TX; ///<1-非mode0模式代表RX&TX ,mode0模式代表RX;
}en_uart_func_t;
/**
 ******************************************************************************
 ** \brief uart发送接收中断使能
 ******************************************************************************/
typedef enum en_uart_irq_sel
{
    UartRxIrq  = 0u,    ///<接收中断使能
    UartTxIrq  = 1u,    ///<发送中断使能
}en_uart_irq_sel_t;

/**
 ******************************************************************************
 ** \brief uart 状态标志位
 ******************************************************************************/
typedef enum en_uart_status
{
    UartRC    = 0u,  ///<接收数据完成标记
    UartTC    = 1u,  ///<发送数据完成标记
    UartFE    = 2u,  ///<帧错误标记

}en_uart_status_t;
/**
 ******************************************************************************
 ** \brief uart 通道地址结构
 ******************************************************************************/
typedef struct stc_uart_instance_data
{
    uint32_t               u32Idx;               ///< 通道号
    M0P_UART_TypeDef       *pstcInstance;        ///< 通道寄存器地址
} stc_uart_instance_data_t;
/**
 ******************************************************************************
 ** \brief uart 通道波特率配置
 ******************************************************************************/
typedef struct stc_uart_baud_cfg
{
    en_uart_mode_t enMode;   ///<四种工作模式
    boolean_t      bDbaud;   ///<是否双倍波特率
    uint32_t       u32Pclk;  ///< PCLK
    uint32_t       u32Baud;  ///<波特率
}stc_uart_baud_cfg_t;

/**
 ******************************************************************************
 ** \uart 总体配置
 ******************************************************************************/
typedef struct stc_uart_cfg
{
    en_uart_mode_t       enRunMode;     ///<四种模式配置
} stc_uart_cfg_t;

//UART初始化
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

///<中断相关设置函数
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);

// 初始化处理
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

// 波特率设置
uint16_t Uart_SetBaudRate(M0P_UART_TypeDef* UARTx,stc_uart_baud_cfg_t* pstcBaud);

///<UART模块多机模式设置函数
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx, stc_uart_multimode_t* pstcMultiCfg);

///< 发送或接收使能和禁止
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);

///< 状态位的获取和清除
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx);
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx);
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);

//数据收发操作
///< 数据查询模式发送
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
en_result_t Uart_SendDataPollTimeOut(M0P_UART_TypeDef* UARTx, uint8_t u8Data, uint32_t u32TimeOut);
///< 数据中断模式发送
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx);
///< 奇偶校验检查
en_result_t Uart_CheckEvenOrOdd(M0P_UART_TypeDef* UARTx, en_uart_check_t enCheck, uint8_t u8Recv);
///< 获取Rb8位
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx);
//< 设置TB8
en_result_t Uart_SetTb8(M0P_UART_TypeDef* UARTx, en_uart_check_t enCheck, uint8_t u8Data);


//@} // UartGroup

/******************************************************************************/
/** \file vc.h
 **
 ** Headerfile for Voltage Comparator functions
 ** @link VC Group Some description @endlink
 **
 **   - 2019-04-10    First Version
 **
 ******************************************************************************/


/******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 ******************************************************************************
 ** \defgroup VcGroup Voltage Comparator (VC)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief VC通道
 *****************************************************************************/
typedef enum en_vc_channel
{
    VcChannel0 = 0u,                 //   通道0
    VcChannel1 = 1u,                 //   通道1

}en_vc_channel_t;


/**
 ******************************************************************************
 ** \brief VC迟滞
 *****************************************************************************/
typedef enum
{
    VcDelayoff  = 0u,            //   迟滞关闭
    VcDelay10mv = 1u,            //   迟滞10mv
    VcDelay20mv = 2u,            //   迟滞20mv
    VcDelay30mv = 3u,            //   迟滞30mv
}en_vc_cmp_delay_t;

/**
 ******************************************************************************
 ** \brief VC偏置电流
 *****************************************************************************/
typedef enum
{
    VcBias300na  = 0u,            //   偏置电流300nA
    VcBias1200na = 1u,            //   偏置电流1.2uA
    VcBias10ua   = 2u,            //   偏置电流10uA
    VcBias20ua   = 3u,            //   偏置电流20uA
}en_vc_bias_current_t;

/**
 ******************************************************************************
 ** \brief VC输出滤波时间
 *****************************************************************************/
typedef enum
{
    VcFilter7us     = 0u,            //   输出滤波时间7us
    VcFilter14us    = 1u,            //   输出滤波时间14us
    VcFilter28us    = 2u,            //   输出滤波时间28us
    VcFilter112us   = 3u,            //   输出滤波时间112us
    VcFilter450us   = 4u,            //   输出滤波时间450us
    VcFilter1800us  = 5u,            //   输出滤波时间1.8ms
    VcFilter7200us  = 6u,            //   输出滤波时间7.2ms
    VcFilter28800us = 7u,            //   输出滤波时间28.8ms
}en_vc_resp_filter_t;

/**
 ******************************************************************************
 ** \brief VC P端输入
 *****************************************************************************/
typedef enum en_vc_input_p_src
{
    VcInPCh0,                ///< 输入通道0 P2.3
    VcInPCh1,                ///< 输入通道1 P2.5
    VcInPCh2,                ///< 输入通道2 P3.2
    VcInPCh3,                ///< 输入通道3 P3.3
    VcInPCh4,                ///< 输入通道4 P3.4
    VcInPCh5,                ///< 输入通道5 P3.5
    VcInPCh6,                ///< 输入通道6 P3.6
    VcInPCh7,                ///< 输入通道7 P0.1
}en_vc_input_p_src_t;

/**
 ******************************************************************************
 ** \brief VC N端输入
 *****************************************************************************/
typedef enum en_vc_input_n_src
{
    VcInNCh0,         ///< 输入通道0 P2.3
    VcInNCh1,         ///< 输入通道1 P2.5
    VcInNCh2,         ///< 输入通道2 P3.2
    VcInNCh3,         ///< 输入通道3 P3.3
    VcInNCh4,         ///< 输入通道4 P3.4
    VcInNCh5,         ///< 输入通道5 P3.5
    VcInNCh6,         ///< 输入通道6 P3.6
    VcInNCh7,         ///< 输入通道7 P0.1
    ResDivOut,        ///< Vcc分压
    AiTs,             ///< 温度传感器
    AiBg1p2,          ///< BGR 1.2V
    AiVcRef2p5,       ///< REF 2.5V
    AiLdo,            ///< LDO
}en_vc_input_n_src_t;

/**
 ******************************************************************************
 ** \brief VC中断触发方式
 *****************************************************************************/
typedef enum en_vc_irq_sel
{
    VcIrqNone = 0u,            ///< 无中断
    VcIrqRise = 1u,            ///< 上升沿触发
    VcIrqFall = 2u,            ///< 下降沿触发
    VcIrqHigh = 3u,            ///< 高电平触发

}en_vc_irq_sel_t;

/**
 ******************************************************************************
 ** \brief VC状态                       VC_IFR
 *****************************************************************************/
typedef enum en_vc_stat
{
    Vc0_Intf    = 0u,          //   VC0中断标志
    Vc1_Intf    = 1u,          //   VC1中断标志
    Vc0_Filter  = 2u,          //   VC0 Filter 后的状态
    Vc1_Filter  = 3u,          //   VC1 Filter 后的状态

}en_vc_ifr_t;

/**
 ******************************************************************************
 ** \brief VC输出配置
 *****************************************************************************/
typedef enum en_vc_output_cfg
{
    VcOutInvTimer,              ///< 结果输出负向到各Timer0,1,2,3
    VcOutTm0Gate,               ///< 结果使能输出到TM0 Gate
    VcOutTm1Gate,               ///< 结果使能输出到TM1 Gate
    VcOutTm2Gate,               ///< 结果使能输出到TM2 Gate
    VcOutTm3Gate,               ///< 结果使能输出到LPTIMER3 Gate
    VcOutTm3ExtClk,             ///< 结果使能输出到LPTIMER 外部时钟
    VcOutInvPca,                ///< 结果输出负向到PCA
    VcOutPcaCap0,               ///< 结果使能输出到PCA 捕获模式0
    VcOutPcaExtClk,             ///< 结果使能输出到PCA 外部时钟
    VcOutInvTm4,                ///< 结果输出负向到Timer4
    VcOutTm4,                   ///< 结果使能输出到TM4 捕获模式
    VcOutInvTm5,                ///< 结果输出负向到Timer5
    VcOutTm5,                   ///< 结果使能输出到TM5 捕获模式
    VcOutInvTm6,                ///< 结果输出负向到Timer6
    VcOutTm6,                   ///< 结果使能输出到TM6 捕获模式
    VcOutBrake,                 ///< 刹车控制
    VcOutDisable,               ///< 结果输出除能
}en_vc_output_cfg_t;

/**
 ******************************************************************************
 ** \brief VC DIV参考电压Vref选择
 *****************************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc = 0u,              ///< AVCC
    VcDivVrefAdc  = 1u,               ///< ADC_CR0 SREF选择参考电压
}en_vc_div_vref_t;

/**
 ******************************************************************************
 ** \brief VC模块配置
 *****************************************************************************/
typedef struct stc_vc_dac_cfg
{
    boolean_t           bDivEn;       //   VC_CR: VC_DIV_EN
    uint8_t             u8DivVal;     //   VC_CR: VC_DIV 范围：0-63
    en_vc_div_vref_t    enDivVref;    //   VC_CR: VC_REF2P5_SEL
}stc_vc_dac_cfg_t;

/**
 ******************************************************************************
 ** \brief VC通道配置
 *****************************************************************************/
typedef struct stc_vc_channel_cfg
{
    en_vc_channel_t         enVcChannel;        //   VC通道选择
    en_vc_cmp_delay_t       enVcCmpDly;         //   VC迟滞
    en_vc_bias_current_t    enVcBiasCurrent;    //   VC功耗选择
    en_vc_resp_filter_t     enVcFilterTime;     //   输出滤波时间
    en_vc_input_p_src_t     enVcInPin_P;        //   P端输入
    en_vc_input_n_src_t     enVcInPin_N;        //   N端输入
    en_vc_output_cfg_t      enVcOutCfg;         //   输出配置
    boolean_t               bFlten;             //   滤波输出使能
}stc_vc_channel_cfg_t;

/******************************************************************************
 * Global definitions
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
extern void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType);
extern void  Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus);
extern boolean_t Vc_GetItStatus(en_vc_ifr_t Result);
extern void Vc_ClearItStatus(en_vc_ifr_t NewStatus);
extern en_result_t Vc_DacInit(stc_vc_dac_cfg_t *pstcDacCfg);
extern void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg);
extern void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus);


//@} // VcGroup

/*****************************************************************************/
/** \file wdt.h
 **
 ** Headerfile for WDT functions
 **
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/




/**
 ******************************************************************************
 ** \defgroup WdtGroup Watchdog Timer (WDT)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief wdt溢出后复位或中断配置
 *****************************************************************************/
typedef enum en_wdt_func
{
    WdtResetEn    = 0,   ///<复位使能
    WdtIntEn      = 1,   ///<中断使能
}en_wdt_func_t;

/**
 ******************************************************************************
 ** \brief wdt当前运行时间配置数据类型定义
 *****************************************************************************/

typedef enum en_wdt_time
{
    WdtT1ms6   = 0u,       ///<1.6ms
    WdtT3ms2   = 1u,       ///<3.2ms
    WdtT6ms4   = 2u,       ///<6.4ms
    WdtT13ms   = 3u,       ///<13ms
    WdtT26ms   = 4u,       ///<26ms
    WdtT51ms   = 5u,       ///<51ms
    WdtT102ms  = 6u,       ///<102ms
    WdtT205ms  = 7u,       ///<205ms
    WdtT500ms  = 8u,       ///<500ms
    WdtT820ms  = 9u,       ///<820ms
    WdtT1s64   = 10u,      ///<1.64s
    WdtT3s28   = 11u,      ///<3.28s
    WdtT6s55   = 12u,      ///<6.55s
    WdtT13s1   = 13u,      ///<13.1s
    WdtT26s2   = 14u,      ///<26.2s
    WdtT52s4   = 15u,      ///<52.4s
}en_wdt_time_t;


//wdt初始化
en_result_t Wdt_Init(en_wdt_func_t enFunc, en_wdt_time_t enTime);

//wdt开始和停止
void Wdt_Start(void);
//喂狗处理
void Wdt_Feed(void);
//喂狗处理
void Wdt_IrqClr(void);
//wdt溢出时间设置
void Wdt_WriteWdtLoad(uint8_t u8LoadValue);
///< 当前计数时间获取
uint8_t Wdt_ReadWdtValue(void);
//< 中断状态获取
boolean_t Wdt_GetIrqStatus(void);
///< 运行状态获取
boolean_t Wdt_ReadwdtStatus(void);

//@} // WdtGroup


/* ========================================================================== */
/*  中断分发框架 (interrupts_hc32f005.h)                                            */
/* ========================================================================== */

/******************************************************************************/
/** \file interrupts_hc32l13x.h
 **
 ** Interrupt common define.
 ** @link IRQGroup Some description @endlink
 **
 **   - 2019-03-01  1.0  Lux     First version.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
/* >>> inlined from ddl.h */
/******************************************************************************/
/** \file ddl.h
 **
 ** DDL common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2019-03-03  1.0  Lux     First version.
 **
 ******************************************************************************/


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
/* >>> inlined from system_hc32f005.h */
/******************************************************************************/
/** \file system_hc3f005.h
 **
 ** A detailed description is available at
 ** @link SampleGroup Some description @endlink
 **
 **   - 2019-03-01  1.0  Lux First version.
 **
 ******************************************************************************/


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/


/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
#define HWWD_DISABLE        (1)



/**
 ******************************************************************************
 ** \brief Clock Setup macro definition
 **
 ** - 0: CLOCK_SETTING_NONE  - User provides own clock setting in application
 ** - 1: CLOCK_SETTING_CMSIS -
 ******************************************************************************/
#define CLOCK_SETTING_NONE  0u
#define CLOCK_SETTING_CMSIS 1u


/******************************************************************************/
/*                                                                            */
/*                      START OF USER SETTINGS HERE                           */
/*                      ===========================                           */
/*                                                                            */
/*                 All lines with '<<<' can be set by user.                   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/


extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)
extern void SystemInit (void);            // Initialize the system
extern void SystemCoreClockUpdate (void); // Update SystemCoreClock variable

/* <<< end of system_hc32f005.h */
/* >>> inlined from sysctrl.h */
/******************************************************************************/
/** \file sysctrl.h
 **
 ** Headerfile for SYSCTRL functions
 ** @link SYSCTRL Group Some description @endlink
 **
 ** History:
 **   - 2018-04-15   Lux     First Version
 **
 ******************************************************************************/


/*******************************************************************************
 * Include files
 ******************************************************************************/



/**
 ******************************************************************************
 ** \defgroup SysCtrlGroup (SYSCTRL)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief 系统时钟输入源类型定义
 ** \note
 ******************************************************************************/
typedef enum en_sysctrl_clk_source
{
    SysctrlClkRCH  = 0u,               ///< 内部高速时钟
    SysctrlClkXTH  = 1u,               ///< 外部高速时钟
    SysctrlClkRCL  = 2u,               ///< 内部低速时钟
    SysctrlClkXTL  = 3u,               ///< 外部低速时钟
}en_sysctrl_clk_source_t;

/**
 *******************************************************************************
 ** \brief RCH频率值枚举类型定义
 ******************************************************************************/
typedef enum en_sysctrl_rch_freq
{
    SysctrlRchFreq4MHz     = 4u,               ///< 4MHz
    SysctrlRchFreq8MHz     = 3u,               ///< 8MHz
    SysctrlRchFreq16MHz    = 2u,               ///< 16MHz
    SysctrlRchFreq22_12MHz = 1u,               ///< 22.12MHz
    SysctrlRchFreq24MHz    = 0u,               ///< 24MHz
}en_sysctrl_rch_freq_t;

/**
 *******************************************************************************
 ** \brief XTAL驱动能力类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xtal_driver
{
    SysctrlXtalDriver0 = 0u,                ///< 最弱驱动能力
    SysctrlXtalDriver1 = 1u,                ///< 弱驱动能力
    SysctrlXtalDriver2 = 2u,                ///< 一般驱动能力
    SysctrlXtalDriver3 = 3u,                ///< 最强驱动能力
}en_sysctrl_xtal_driver_t;

/**
 *******************************************************************************
 ** \brief XTH频率值范围选择类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xth_freq
{
    SysctrlXthFreq4_6MHz   = 0u,                ///< 4~6MHz
    SysctrlXthFreq6_12MHz  = 1u,                ///< 6~12MHz
    SysctrlXthFreq12_20MHz = 2u,                ///< 12~20MHz
    SysctrlXthFreq20_32MHz = 3u,                ///< 20~32MHz
}en_sysctrl_xth_freq_t;

/**
 *******************************************************************************
 ** \brief XTH时钟稳定周期数类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xth_cycle
{
    SysctrlXthStableCycle256   = 0u,              ///< 256 个周期数
    SysctrlXthStableCycle1024  = 1u,              ///< 1024 个周期数
    SysctrlXthStableCycle4096  = 2u,              ///< 4096 个周期数
    SysctrlXthStableCycle16384 = 3u,              ///< 16384 个周期数
}en_sysctrl_xth_cycle_t;

/**
 *******************************************************************************
 ** \brief RCL频率值枚举类型定义
 ******************************************************************************/
typedef enum en_sysctrl_rcl_freq
{
    SysctrlRclFreq32768    = 0x11u,               ///< 32.768KHz
    SysctrlRclFreq38400    = 0x10u,               ///< 38.4KHz
}en_sysctrl_rcl_freq_t;

/**
 *******************************************************************************
 ** \brief RCL时钟稳定周期数类型定义
 ******************************************************************************/
typedef enum en_sysctrl_rcl_cycle
{
    SysctrlRclStableCycle4   = 0u,                  ///< 4 个周期数
    SysctrlRclStableCycle16  = 1u,                  ///< 16 个周期数
    SysctrlRclStableCycle64  = 2u,                  ///< 64 个周期数
    SysctrlRclStableCycle256 = 3u,                  ///< 256 个周期数
}en_sysctrl_rcl_cycle_t;

/**
 *******************************************************************************
 ** \brief HCLK时钟分频系数类型定义
 ******************************************************************************/
typedef enum en_sysctrl_hclk_div
{
    SysctrlHclkDiv1   = 0u,              ///< SystemClk
    SysctrlHclkDiv2   = 1u,              ///< SystemClk/2
    SysctrlHclkDiv4   = 2u,              ///< SystemClk/4
    SysctrlHclkDiv8   = 3u,              ///< SystemClk/8
    SysctrlHclkDiv16  = 4u,              ///< SystemClk/16
    SysctrlHclkDiv32  = 5u,              ///< SystemClk/32
    SysctrlHclkDiv64  = 6u,              ///< SystemClk/64
    SysctrlHclkDiv128 = 7u,              ///< SystemClk/128
}en_sysctrl_hclk_div_t;

/**
 *******************************************************************************
 ** \brief PCLK分频系数
 ******************************************************************************/
typedef enum en_sysctrl_pclk_div
{
    SysctrlPclkDiv1 = 0u,                ///< HCLK
    SysctrlPclkDiv2 = 1u,                ///< HCLK/2
    SysctrlPclkDiv4 = 2u,                ///< HCLK/4
    SysctrlPclkDiv8 = 3u,                ///< HCLK/8
}en_sysctrl_pclk_div_t;

/**
 *******************************************************************************
 ** \brief 系统控制模块其他功能数据类型定义
 ******************************************************************************/
typedef enum en_sysctrl_func
{
    SysctrlEXTHEn           = 1u,                    ///< 使能外部高速时钟从输入引脚输入
    SysctrlCMLockUpEn       = 6u,                    ///< 使能后CPU执行无效指令会复位MCU
    SysctrlSWDUseIOEn       = 8u,                    ///< SWD端口设为IO功能
}en_sysctrl_func_t;

/**
 *******************************************************************************
 ** \brief 外设时钟门控开关类型枚举
 ******************************************************************************/
typedef enum en_sysctrl_peripheral_gate
{
     SysctrlPeripheralUart0      = 0u,       ///< 串口0
     SysctrlPeripheralUart1      = 1u,       ///< 串口1
     SysctrlPeripheralI2c        = 4u,       ///< I2C
     SysctrlPeripheralSpi        = 6u,       ///< SPI
     SysctrlPeripheralBt         = 8u,       ///< 基础时钟
     SysctrlPeripheralAdvTim     = 10u,      ///< 高级时钟
     SysctrlPeripheralPca        = 14u,      ///< 可编程计数阵列
     SysctrlPeripheralWdt        = 15u,      ///< 看门狗
     SysctrlPeripheralAdcBgr     = 16u,      ///< ADC
     SysctrlPeripheralVcLvd      = 17u,      ///< 电压比较和低电压检测
     SysctrlPeripheralTrim       = 21u,      ///< 时钟校准
     SysctrlPeripheralTick       = 24u,      ///< 系统定时器
     SysctrlPeripheralCrc        = 26u,      ///< CRC
     SysctrlPeripheralGpio       = 28u,      ///< GPIO
     SysctrlPeripheralFlash      = 31u,      ///< Flash
}en_sysctrl_peripheral_gate_t;

/**
 *******************************************************************************
 ** \brief 时钟初始化配置结构体定义
 ******************************************************************************/
typedef struct
{
    en_sysctrl_clk_source_t  enClkSrc;       ///< 时钟源选择
    en_sysctrl_hclk_div_t    enHClkDiv;      ///< HCLK分频系数
    en_sysctrl_pclk_div_t    enPClkDiv;      ///< PCLK分频系数
}stc_sysctrl_clk_cfg_t;



/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 系统时钟初始化API:用于上电后，系统工作之前对主频及外设时钟进行初始化；
///< 注意1：使用该初始化函数前需要根据系统，必须优先设置目标内部时钟源的TRIM值或外部时钟源的频率范围，
///< 注意2：XTH、XTL的频率范围设定，需要根据外部晶振决定，
///< 注意3：本驱动默认宏定义：SYSTEM_XTH=32MHz,SYSTEM_XTL=32768Hz,如使用其它外部晶振，必须修改这两个宏定义的值。
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_cfg_t *pstcCfg);

///< 系统时钟去初始化API:恢复为上电默认状态->PCLK=HCLK=SystemClk=RCH4MHz
en_result_t Sysctrl_ClkDeInit(void);

///< 系统时钟模块的基本功能设置
///< 注意：使能需要使用的时钟源之前，必须优先设置目标内部时钟源的TRIM值或外部时钟源的频率范围
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag);

///<外部晶振驱动配置：系统初始化Sysctrl_ClkInit()之后，可根据需要配置外部晶振的驱动能力，时钟初始化Sysctrl_ClkInit()默认为最大值;
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver);

///<时钟稳定周期设置:系统初始化Sysctrl_ClkInit()之后，可根据需要配置时钟开启后的稳定之间，默认为最大值;
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle);
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle);

///<系统时钟源切换并更新系统时钟：如果需要在系统时钟初始化Sysctrl_ClkInit()之后切换主频时钟源，则使用该函数；
///< 时钟切换前后，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2，
///< 注意!!!：当HCLK大于24MHz时，FLASH等待周期插入必须至少为1,否则程序运行可能产生未知错误
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource);

///< 时钟源频率设定：根据系统情况，单独设置不同时钟源的频率值;
///< 时钟频率设置前，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2，
///< 其中XTL的时钟由外部晶振决定，无需设置。
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq);
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq);
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq);

///< 时钟分频设置:根据系统情况，单独设置HCLK、PCLK的分配值;
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv);
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv);

///< 时钟频率获取：根据系统需要，获取当前HCLK及PCLK的频率值
uint32_t Sysctrl_GetHClkFreq(void);
uint32_t Sysctrl_GetPClkFreq(void);

///< 外设门控开关/状态获取：用于控制外设模块的使能，使用该模块的功能之前，必须使能该模块的门控时钟；
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag);
boolean_t   Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral);

///< 系统功能配置：用于设置其他系统相关特殊功能；
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag);


//@} // Sysctrl Group

/* <<< end of sysctrl.h */

/* C binding of definitions if building with C++ compiler                     */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/* Macro for initializing local structures to zero                            */
/******************************************************************************/
#define DDL_ZERO_STRUCT(x)          ddl_memclr((uint8_t*)&(x), (uint32_t)(sizeof(x)))

#define DEC2BCD(x)                  ((((x)/10)<<4) + ((x)%10))
#define BCD2DEC(x)                  ((((x)>>4)*10) + ((x)&0x0F))

/**
 ******************************************************************************
 ** Global Device Series List
 ******************************************************************************/
#define DDL_DEVICE_SERIES_HC32F005       (0u)

/**
 ******************************************************************************
 ** Global Device Package List
 ******************************************************************************/
// package definitions of HC device.
#define DDL_DEVICE_PACKAGE_HC_C         (0x00u)
#define DDL_DEVICE_PACKAGE_HC_F         (0x10u)
#define DDL_DEVICE_PACKAGE_HC_J         (0x20u)
#define DDL_DEVICE_PACKAGE_HC_K         (0x30u)

/******************************************************************************/
/* User Device Setting Include file                                           */
/******************************************************************************/
/* >>> inlined from ddl_device.h */
/******************************************************************************/
/** \file ddl_device.h
 **
 ** Device define
 ** @link SampleGroup Some description @endlink
 **
 **   - 2018-04-15
 **
 *****************************************************************************/


/**
 *******************************************************************************
 ** \brief Global device series definition
 **
 ** \note
 ******************************************************************************/
#define DDL_MCU_SERIES       DDL_DEVICE_SERIES_HC32F005


/**
 *******************************************************************************
 ** \brief Global package definition
 **
 ** \note This definition is used for device package settings
 ******************************************************************************/
#define DDL_MCU_PACKAGE      DDL_DEVICE_PACKAGE_HC_K
/* <<< end of ddl_device.h */

/******************************************************************************/
/* Global type definitions ('typedef')                                        */
/******************************************************************************/
/**
 ******************************************************************************
 ** \brief Level
 **
 ** Specifies levels.
 **
 ******************************************************************************/
typedef enum en_level
{
    DdlLow      = 0u,  ///< Low level  '0'
    DdlHigh     = 1u   ///< High level '1'
} en_level_t;

/**
 ******************************************************************************
 ** \brief Generic Flag Code
 **
 ** Specifies flags.
 **
 ******************************************************************************/
typedef enum en_flag
{
    DdlClr = 0u,       ///< Flag clr '0'
    DdlSet = 1u        ///< Flag set '1'
} en_stat_flag_t, en_irq_flag_t;
/******************************************************************************/
/* Global variable declarations ('extern', definition in C source)            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
extern void ddl_memclr(void* pu8Address, uint32_t u32Count);
uint32_t Log2(uint32_t u32Val);
/**
 *******************************************************************************
 ** This hook is part of wait loops.
 ******************************************************************************/
extern void DDL_WAIT_LOOP_HOOK(void);

void Debug_UartInit(void);

void delay1ms(uint32_t u32Cnt);
void delay100us(uint32_t u32Cnt);
void delay10us(uint32_t u32Cnt);
void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag);
void ClrBit(uint32_t addr, uint32_t offset);
boolean_t GetBit(uint32_t addr, uint32_t offset);
/* <<< end of ddl.h */

/* C binding of definitions if building with C++ compiler */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
#define DDL_IRQ_LEVEL_DEFAULT                   3u

//<<此选项会打开interrupt_hc32xxx.c中的中断回调函数，用户如果需要实现中断服务函数，
//<<可在源码文件中定义该文件中用"__WEAK"声明的同名中断服务函数即可。
#define INT_CALLBACK_ON                                  1u  //<<(默认值)
//<<此选项会关闭interrupt_hc32xxx.c中的中断回调函数，此时用户可在该文件中自行定义中断服务函数的实现。
#define INT_CALLBACK_OFF                                 0u
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
#define INT_CALLBACK_PORT0                       INT_CALLBACK_ON
#define INT_CALLBACK_PORT1                       INT_CALLBACK_ON
#define INT_CALLBACK_PORT2                       INT_CALLBACK_ON
#define INT_CALLBACK_PORT3                       INT_CALLBACK_ON
#define INT_CALLBACK_DMAC                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM3                        INT_CALLBACK_ON
#define INT_CALLBACK_UART0                       INT_CALLBACK_ON
#define INT_CALLBACK_UART1                       INT_CALLBACK_ON
#define INT_CALLBACK_SPI                         INT_CALLBACK_ON
#define INT_CALLBACK_I2C                         INT_CALLBACK_ON
#define INT_CALLBACK_TIM0                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM1                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM2                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM4                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM5                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM6                        INT_CALLBACK_ON
#define INT_CALLBACK_PCA                         INT_CALLBACK_ON
#define INT_CALLBACK_WDT                         INT_CALLBACK_ON
#define INT_CALLBACK_ADC                         INT_CALLBACK_ON
#define INT_CALLBACK_PCNT                        INT_CALLBACK_ON
#define INT_CALLBACK_VC0                         INT_CALLBACK_ON
#define INT_CALLBACK_VC1                         INT_CALLBACK_ON
#define INT_CALLBACK_LVD                         INT_CALLBACK_ON
#define INT_CALLBACK_FLASH                       INT_CALLBACK_ON
#define INT_CALLBACK_RAM                         INT_CALLBACK_ON
#define INT_CALLBACK_CLKTRIM                     INT_CALLBACK_ON


/**
 *******************************************************************************
 ** \brief 中断优先级数据类型定义
 ** \note
 ******************************************************************************/
typedef enum en_irq_level
{
    IrqLevel0  = 0u,               ///< 优先级0
    IrqLevel1  = 1u,               ///< 优先级1
    IrqLevel2  = 2u,               ///< 优先级2
    IrqLevel3  = 3u,               ///< 优先级3
} en_irq_level_t;


/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 系统中断使能开关
extern void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn);



/* ========================================================================== */
/*  中断入口与回调声明 (原厂头文件遗漏, 必须补 C 链接声明)                                           */
/* ========================================================================== */

/*
 * interrupts_hc32f005.c 只声明了 EnableNvic(), 下面这些全部没有声明.
 * 单独编译成 .o 时它们是 C 符号; 但合并进 driver.cpp 后用 C++ 编译,
 * 会得到 _Z... 修饰名, 向量表引用的 C 符号名再也匹配不上, 实测后果是
 * 向量表全部落回 startup.s 的 Default_Handler, 中断彻底失效.
 *
 * 另: 回调若未实现, 由 driver.cpp 末尾的弱空定义兜底, 不会跳地址 0.
 */
/* 中断回调: 应用层实现同名强符号即可覆盖; 未实现时用 driver.cpp 的弱空定义 (28 个) */
void SysTick_IRQHandler(void);
void Port0_IRQHandler(void);
void Port1_IRQHandler(void);
void Port2_IRQHandler(void);
void Port3_IRQHandler(void);
void Dmac_IRQHandler(void);
void Tim3_IRQHandler(void);
void Uart0_IRQHandler(void);
void Uart1_IRQHandler(void);
void Spi_IRQHandler(void);
void I2c_IRQHandler(void);
void Tim0_IRQHandler(void);
void Tim1_IRQHandler(void);
void Tim2_IRQHandler(void);
void Tim4_IRQHandler(void);
void Tim5_IRQHandler(void);
void Tim6_IRQHandler(void);
void Pca_IRQHandler(void);
void Wdt_IRQHandler(void);
void Adc_IRQHandler(void);
void Dac_IRQHandler(void);
void Pcnt_IRQHandler(void);
void Vc0_IRQHandler(void);
void Vc1_IRQHandler(void);
void Lvd_IRQHandler(void);
void Flash_IRQHandler(void);
void Ram_IRQHandler(void);
void ClkTrim_IRQHandler(void);

/* 向量表中断入口: driver 提供强定义, 覆盖 startup.s 的弱默认 (27 个) */
void HardFault_Handler(void);
void SysTick_Handler(void);
void PORT0_IRQHandler(void);
void PORT1_IRQHandler(void);
void PORT2_IRQHandler(void);
void PORT3_IRQHandler(void);
void DMAC_IRQHandler(void);
void TIM3_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void SPI_IRQHandler(void);
void I2C_IRQHandler(void);
void TIM0_IRQHandler(void);
void TIM1_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void TIM6_IRQHandler(void);
void PCA_IRQHandler(void);
void WDT_IRQHandler(void);
void ADC_IRQHandler(void);
void PCNT_IRQHandler(void);
void VC0_IRQHandler(void);
void VC1_IRQHandler(void);
void LVD_IRQHandler(void);
void FLASH_RAM_IRQHandler(void);
void CLKTRIM_IRQHandler(void);

/* ========================================================================== */
/*  原厂遗漏声明的补全                                                                 */
/* ========================================================================== */

/*
 * 以下符号在源码中有定义, 但原厂头文件从未声明; 若不补声明,
 * 聚合到 .cpp 用 C++ 编译后会变成 _Z... 修饰名, 与其它 TU 的
 * C 符号引用不匹配 (实现见 config.cpp 的另有说明).
 * 校验: clang++ -c driver.cpp && llvm-nm driver.o | grep -w _Z
 */
en_result_t Uart_SetSaddr(M0P_UART_TypeDef *UARTx, uint8_t u8Addr);
void Debug_Output(uint8_t u8Data);
void _ttywrch(int c);
int  __backspace(void);

#ifdef __cplusplus
}
#endif

#endif /* __HC32F005_DRIVER_H__ */
