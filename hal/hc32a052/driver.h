/**
 *******************************************************************************
 * @file  driver.h
 * @brief HC32A052 DDL 驱动库 - 聚合头文件 (声明/类型/宏) [自动生成, 勿手改]
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

#ifndef __HC32A052_DRIVER_H__
#define __HC32A052_DRIVER_H__

/******************************************************************************/
/* 板级配置 (外部相关, 按「机制/策略」分层)
 *
 * 驱动中的时钟计算 (sysctrl.c 的 PLL 与 Sysctrl_GetHClkFreq) 必须知道板上实际
 * 焊接的晶振频率 (SYSTEM_XTH / SYSTEM_XTL), 故自动包含同目录下的 config.h.
 *
 *   config.h       板级配置「机制」: Config 类型 / 预设 / 校验 (HAL 提供)
 *   board_config.h 板级配置「策略」: 晶振频率 + 生效配置 (app 提供)
 *                  config.h 会自动 #include 它 (若在 include path 上)
 *
 * 若确实不用 board_config.h, 也可用编译选项传入:
 *   -DSYSTEM_XTH=8000000 -DSYSTEM_XTL=32768
 *   -DHC32_BOARD_CONFIG=::hc32::board::preset_rch_4mhz
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
#if !defined(SYSTEM_XTL)
#  error "SYSTEM_XTL 未定义: 请在 app 的 inc 目录创建 board_config.h, 给出外部低速晶振频率(Hz)"
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
/*  基础类型 (mcu/common/base_types.h)                                            */
/* ========================================================================== */


/* C binding of definitions if building with C++ compiler */
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
    #define ASSERT(x) do{ assert((x)> 0u) ; }while(0)
#else
    #define ASSERT(x) do{}while(0)
#endif
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @brief  logical datatype (only values are TRUE and FALSE)
 */
typedef uint8_t      boolean_t;

/**
 * @brief  single precision floating point number (4 byte)
 */
typedef float        float32_t;

/**
 * @brief  double precision floating point number (8 byte)
 */
typedef double       float64_t;

/**
 * @brief  ASCII character for string generation (8 bit)
 */
typedef char         char_t;

/**
 * @brief  function pointer type to void/void function
 */
typedef void         (*func_ptr_t)(void);

/**
 * @brief  function pointer type to void/uint8_t function
 */
typedef void         (*func_ptr_arg1_t)(uint8_t u8Param);

/**
 * @brief  generic error codes
 */
typedef enum
{
    Ok                          = 0u,  /*!< No error */
    Error                       = 1u,  /*!< Non-specific error code */
    ErrorAddressAlignment       = 2u,  /*!< Non-specific error code */
    ErrorAccessRights           = 3u,  /*!< Wrong mode (e.g. user/system) mode is set */
    ErrorInvalidParameter       = 4u,  /*!< Provided parameter is not valid */
    ErrorOperationInProgress    = 5u,  /*!< A conflicting or requested operation is still in progress */
    ErrorInvalidMode            = 6u,  /*!< Operation not allowed in current mode */
    ErrorUninitialized          = 7u,  /*!< Module (or part of it) was not initialized properly */
    ErrorBufferFull             = 8u,  /*!< Circular buffer can not be written because the buffer is full */
    ErrorTimeout                = 9u,  /*!< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc. */
    ErrorNotReady               = 10u, /*!< A requested final state is not reached */
    OperationInProgress         = 11u  /*!< Indicator for operation in progress*/
} en_result_t;


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/



/* ========================================================================== */
/*  CMSIS 内核配置 + 中断号 (hc32a052.h 前置段, 必须早于 core_cm0plus.h)                    */
/* ========================================================================== */




/******************************************************************************
* Configuration of the Cortex-M0P Processor and Core Peripherals
******************************************************************************/
#define __MPU_PRESENT           0 /* No MPU                                       */
#define __NVIC_PRIO_BITS        2 /* M0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0 /* Set to 1 if different SysTick Config is used */
/** @} */ /* End of group Configuration_of_CMSIS */

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

    PORTA_IRQn          = 0 ,
    PORTB_IRQn          = 1 ,
    PORTC_IRQn          = 2 ,
    PORTD_IRQn          = 3 ,
    DMAC_IRQn           = 4 ,
    ATIM3_IRQn          = 5 ,
    USART0_IRQn         = 6 ,
    USART1_IRQn         = 7 ,
    LPUART0_IRQn        = 8 ,
    LPUART1_IRQn        = 9 ,
    SPI0_IRQn           = 10,
    SPI1_IRQn           = 11,
    I2C0_IRQn           = 12,
    I2C1_IRQn           = 13,
    ATIM0_IRQn          = 14,
    ATIM1_IRQn          = 15,
    ATIM2_IRQn          = 16,
    LPTIM_IRQn          = 17,
    GTIM0_BTIM0_1_2_IRQn= 18,
    GTIM1_BTIM3_4_5_IRQn= 19,
    I2CSLV_IRQn         = 20,
    WWDT_IRQn           = 21,
    IWDT_IRQn           = 22,
    RTC_IRQn            = 23,
    ADC_IRQn            = 24,
    VC0_VC1_LVD_IRQn    = 26,
    CAN_IRQn            = 28,
    ATIM_BK_IRQn        = 29,
    FLASH_RAM_IRQn      = 30,
    CTRIM_IRQn          = 31,


} IRQn_Type;


#include <core_cm0plus.h>
#include <stdint.h>

/* ========================================================================== */
/*  器件寄存器 / 位定义 / 外设基址 (hc32a052.h)                                           */
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
    __IO uint32_t BGREN                     : 1;
    __IO uint32_t TSEN                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_adc_bgr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t CKDIV                     : 3;
    __IO uint32_t SGLMUX                    : 5;
    __IO uint32_t REF                       : 2;
    __IO uint32_t BUF                       : 1;
    __IO uint32_t SAM                       : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_adc_cr0_field_t;

typedef struct
{
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ALIGN                     : 1;
    __IO uint32_t THCH                      : 5;
    uint32_t RESERVED8                      : 2;
    __IO uint32_t OVMD                      : 1;
    __IO uint32_t RACCEN                    : 1;
    __IO uint32_t LTCMP                     : 1;
    __IO uint32_t HTCMP                     : 1;
    __IO uint32_t REGCMP                    : 1;
    __IO uint32_t RACCCLR                   : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_cr1_field_t;

typedef struct
{
    __IO uint32_t ESG                       : 1;
    __IO uint32_t LTI                       : 1;
    __IO uint32_t HTI                       : 1;
    __IO uint32_t RGI                       : 1;
    __IO uint32_t EOS                       : 1;
    __IO uint32_t EOJ                       : 1;
    __IO uint32_t EOC                       : 1;
    __IO uint32_t DEOC                      : 1;
    __IO uint32_t DEOJ                      : 1;
    __IO uint32_t OV                        : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_adc_ier_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 5;
    __IO uint32_t CH1MUX                    : 5;
    __IO uint32_t CH2MUX                    : 5;
    __IO uint32_t CH3MUX                    : 5;
    __IO uint32_t CH4MUX                    : 5;
    __IO uint32_t CH5MUX                    : 5;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr0_field_t;

typedef struct
{
    __IO uint32_t CH6MUX                    : 5;
    __IO uint32_t CH7MUX                    : 5;
    __IO uint32_t CH8MUX                    : 5;
    __IO uint32_t CH9MUX                    : 5;
    __IO uint32_t CH10MUX                   : 5;
    __IO uint32_t CH11MUX                   : 5;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr1_field_t;

typedef struct
{
    __IO uint32_t CH12MUX                   : 5;
    __IO uint32_t CH13MUX                   : 5;
    __IO uint32_t CH14MUX                   : 5;
    __IO uint32_t CH15MUX                   : 5;
    __IO uint32_t CNT                       : 4;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr2_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 5;
    __IO uint32_t CH1MUX                    : 5;
    __IO uint32_t CH2MUX                    : 5;
    __IO uint32_t CH3MUX                    : 5;
    __IO uint32_t CNT                       : 2;
    uint32_t RESERVED22                     : 9;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult3_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult3_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_result_field_t;

typedef struct
{
    __IO uint32_t RESULTACC                 :20;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_adc_resultacc_field_t;

typedef struct
{
    __IO uint32_t HT                        :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_ht_field_t;

typedef struct
{
    __IO uint32_t LT                        :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_lt_field_t;

typedef struct
{
    __IO uint32_t ESG                       : 1;
    __IO uint32_t LTI                       : 1;
    __IO uint32_t HTI                       : 1;
    __IO uint32_t RGI                       : 1;
    __IO uint32_t EOS                       : 1;
    __IO uint32_t EOJ                       : 1;
    __IO uint32_t EOC                       : 1;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t OV                        : 1;
    __IO uint32_t RDY                       : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_adc_ifr_field_t;

typedef struct
{
    __IO uint32_t ESG                       : 1;
    __IO uint32_t LTI                       : 1;
    __IO uint32_t HTI                       : 1;
    __IO uint32_t RGI                       : 1;
    __IO uint32_t EOS                       : 1;
    __IO uint32_t EOJ                       : 1;
    __IO uint32_t EOC                       : 1;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t OV                        : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_adc_icr_field_t;

typedef struct
{
    __IO uint32_t TRIG                      : 5;
    __IO uint32_t DELAY                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_adc_exttrig0_field_t;

typedef struct
{
    __IO uint32_t TRIG                      : 5;
    __IO uint32_t DELAY                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_adc_exttrig1_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_sglstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrstart_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0                       : 1;
    __IO uint32_t CA1                       : 1;
    __IO uint32_t CA2                       : 1;
    __IO uint32_t CB0                       : 1;
    __IO uint32_t CB1                       : 1;
    __IO uint32_t CB2                       : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    __IO uint32_t CA3A                      : 1;
    __IO uint32_t CA3B                      : 1;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0                       : 1;
    __IO uint32_t CA1                       : 1;
    __IO uint32_t CA2                       : 1;
    __IO uint32_t CB0                       : 1;
    __IO uint32_t CB1                       : 1;
    __IO uint32_t CB2                       : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    __IO uint32_t CA3A                      : 1;
    __IO uint32_t CA3B                      : 1;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0FLTA0                : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0FLTB0                : 3;
    __IO uint32_t CCPB0                     : 1;
    __IO uint32_t OCMA1FLTA1                : 3;
    __IO uint32_t CCPA1                     : 1;
    __IO uint32_t OCMB1FLTB1                : 3;
    __IO uint32_t CCPB1                     : 1;
    __IO uint32_t OCMA2FLTA2                : 3;
    __IO uint32_t CCPA2                     : 1;
    __IO uint32_t OCMB2FLTB2                : 3;
    __IO uint32_t CCPB2                     : 1;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_atim3mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    __IO uint32_t CMA1E                     : 1;
    __IO uint32_t CMA2E                     : 1;
    __IO uint32_t CMB0E                     : 1;
    __IO uint32_t CMB1E                     : 1;
    __IO uint32_t CMB2E                     : 1;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFACRABKSA                : 2;
    __IO uint32_t CFBCRBBKSB                : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t CFACRABKSA                : 2;
    __IO uint32_t CFBCRBBKSB                : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_crch1_field_t;

typedef struct
{
    __IO uint32_t CFACRABKSA                : 2;
    __IO uint32_t CFBCRBBKSB                : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_crch2_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UD                        : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t CCR1A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr1a_field_t;

typedef struct
{
    __IO uint32_t CCR1B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr1b_field_t;

typedef struct
{
    __IO uint32_t CCR2A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr2a_field_t;

typedef struct
{
    __IO uint32_t CCR2B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr2b_field_t;

typedef struct
{
    __IO uint32_t CCR3A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr3a_field_t;

typedef struct
{
    __IO uint32_t BUF                       : 1;
    __IO uint32_t CI                        : 1;
    __IO uint32_t CD                        : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t C3AEN                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_crch3a_field_t;

typedef struct
{
    __IO uint32_t CCR3B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_ccr3b_field_t;

typedef struct
{
    __IO uint32_t BUF                       : 1;
    __IO uint32_t CI                        : 1;
    __IO uint32_t CD                        : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t C3BEN                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_atim3mode23_crch3b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_atimmode0_cnt32_field_t;

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
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_atimmode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_atimmode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_atimmode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atimmode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t PWC                       : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t PWC                       : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_atimmode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CIEA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0                       : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0                       : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0FLTA0                : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0FLTB0                : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_atimmode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFACRABKSA                : 2;
    __IO uint32_t CFBCRBBKSB                : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UD                        : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_rcr_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_atimmode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_btim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_btim_cnt_field_t;

typedef struct
{
    __IO uint32_t CEN                       : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    __IO uint32_t TRS                       : 2;
    __IO uint32_t ETP                       : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_btim_cr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_btim_ier_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_btim_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_btim_icr_field_t;

typedef struct
{
    __IO uint32_t UI03                      : 1;
    __IO uint32_t TI03                      : 1;
    __IO uint32_t UI14                      : 1;
    __IO uint32_t TI14                      : 1;
    __IO uint32_t UI25                      : 1;
    __IO uint32_t TI25                      : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_btim_aifr_field_t;

typedef struct
{
    __IO uint32_t UI03                      : 1;
    __IO uint32_t TI03                      : 1;
    __IO uint32_t UI14                      : 1;
    __IO uint32_t TI14                      : 1;
    __IO uint32_t UI25                      : 1;
    __IO uint32_t TI25                      : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_btim_aicr_field_t;

typedef struct
{
    __IO uint8_t BUSOFF                     : 1;
    __IO uint8_t TACTIVE                    : 1;
    __IO uint8_t RACTIVE                    : 1;
    __IO uint8_t TSSS                       : 1;
    __IO uint8_t TPSS                       : 1;
    __IO uint8_t LBMI                       : 1;
    __IO uint8_t LBME                       : 1;
    __IO uint8_t RESET                      : 1;
} stc_can_cfg_stat_field_t;

typedef struct
{
    __IO uint8_t TSA                        : 1;
    __IO uint8_t TSALL                      : 1;
    __IO uint8_t TSONE                      : 1;
    __IO uint8_t TPA                        : 1;
    __IO uint8_t TPE                        : 1;
    __IO uint8_t STBY                       : 1;
    __IO uint8_t LOM                        : 1;
    __IO uint8_t TBSEL                      : 1;
} stc_can_tcmd_field_t;

typedef struct
{
    __IO uint8_t TSSTAT                     : 2;
    uint8_t RESERVED2                       : 2;
    __IO uint8_t TTTBM                      : 1;
    __IO uint8_t TSMODE                     : 1;
    __IO uint8_t TSNEXT                     : 1;
} stc_can_tctrl_field_t;

typedef struct
{
    __IO uint8_t RSSTAT                     : 2;
    uint8_t RESERVED2                       : 1;
    __IO uint8_t RBALL                      : 1;
    __IO uint8_t RREL                       : 1;
    __IO uint8_t ROV                        : 1;
    __IO uint8_t ROM                        : 1;
    __IO uint8_t SACK                       : 1;
} stc_can_rctrl_field_t;

typedef struct
{
    __IO uint8_t TSFF                       : 1;
    __IO uint8_t EIE                        : 1;
    __IO uint8_t TSIE                       : 1;
    __IO uint8_t TPIE                       : 1;
    __IO uint8_t RAFIE                      : 1;
    __IO uint8_t RFIE                       : 1;
    __IO uint8_t ROIE                       : 1;
    __IO uint8_t RIE                        : 1;
} stc_can_rtie_field_t;

typedef struct
{
    __IO uint8_t AIF                        : 1;
    __IO uint8_t EIF                        : 1;
    __IO uint8_t TSIF                       : 1;
    __IO uint8_t TPIF                       : 1;
    __IO uint8_t RAFIF                      : 1;
    __IO uint8_t RFIF                       : 1;
    __IO uint8_t ROIF                       : 1;
    __IO uint8_t RIF                        : 1;
} stc_can_rtif_field_t;

typedef struct
{
    __IO uint8_t BEIF                       : 1;
    __IO uint8_t BEIE                       : 1;
    __IO uint8_t ALIF                       : 1;
    __IO uint8_t ALIE                       : 1;
    __IO uint8_t EPIF                       : 1;
    __IO uint8_t EPIE                       : 1;
    __IO uint8_t EPASS                      : 1;
    __IO uint8_t EWARN                      : 1;
} stc_can_errint_field_t;

typedef struct
{
    __IO uint8_t EWL                        : 4;
    __IO uint8_t AFWL                       : 4;
} stc_can_limit_field_t;

typedef struct
{
    __IO uint32_t SEG_1                     : 8;
    __IO uint32_t SEG_2                     : 7;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t SJW                       : 7;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t PRESC                     : 8;
} stc_can_bt_field_t;

typedef struct
{
    __IO uint8_t ALC                        : 5;
    __IO uint8_t KOER                       : 3;
} stc_can_ealcap_field_t;

typedef struct
{
    __IO uint8_t ACFADR                     : 4;
    uint8_t RESERVED4                       : 1;
    __IO uint8_t SELMASK                    : 1;
} stc_can_acfctrl_field_t;

typedef struct
{
    __IO uint8_t AE_1                       : 1;
    __IO uint8_t AE_2                       : 1;
    __IO uint8_t AE_3                       : 1;
    __IO uint8_t AE_4                       : 1;
    __IO uint8_t AE_5                       : 1;
    __IO uint8_t AE_6                       : 1;
    __IO uint8_t AE_7                       : 1;
    __IO uint8_t AE_8                       : 1;
} stc_can_acfen_field_t;

typedef struct
{
    __IO uint32_t ACODE_AMASK               :29;
    __IO uint32_t AIDE                      : 1;
    __IO uint32_t AIDEE                     : 1;
} stc_can_acf_field_t;

typedef struct
{
    __IO uint8_t TBPTR                      : 3;
    uint8_t RESERVED3                       : 3;
    __IO uint8_t TBF                        : 1;
    __IO uint8_t TBE                        : 1;
} stc_can_tbslot_field_t;

typedef struct
{
    __IO uint8_t TTEN                       : 1;
    __IO uint8_t T_PRESC                    : 2;
    __IO uint8_t TTIF                       : 1;
    __IO uint8_t TTIE                       : 1;
    __IO uint8_t TEIF                       : 1;
    __IO uint8_t WTIF                       : 1;
    __IO uint8_t WTIE                       : 1;
} stc_can_ttcfg_field_t;

typedef struct
{
    __IO uint32_t REF_ID                    :29;
    uint32_t RESERVED29                     : 2;
    __IO uint32_t REF_IDE                   : 1;
} stc_can_ref_msg_field_t;

typedef struct
{
    __IO uint16_t TTPTR                     : 3;
    uint16_t RESERVED3                      : 5;
    __IO uint16_t TTYPE                     : 3;
    uint16_t RESERVED11                     : 1;
    __IO uint16_t TEW                       : 4;
} stc_can_trg_cfg_field_t;

typedef struct
{
    __IO uint32_t CODE                      : 1;
    __IO uint32_t FLAG                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_crc_csr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :32;
} stc_crc_result_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_crc_data_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cnt_field_t;

typedef struct
{
    __IO uint32_t STEP                      : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t ETRFLT                    : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t SRC                       : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cr0_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t AUTO                      : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    __IO uint32_t MDRCH                     : 2;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cr1_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_ier_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_isr_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_icr_field_t;

typedef struct
{
    __IO uint32_t FCAP                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_fcap_field_t;

typedef struct
{
    __IO uint32_t TVAL                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_tval_field_t;

typedef struct
{
    __IO uint32_t FLIM                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_flim_field_t;

typedef struct
{
    uint32_t RESERVED0                      :24;
    __IO uint32_t HALT                      : 4;
    __IO uint32_t PRIO                      : 1;
    uint32_t RESERVED29                     : 2;
    __IO uint32_t EN                        : 1;
} stc_dmac_conf_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRISEL                    : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa0_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FISIE                     : 1;
    __IO uint32_t ERRIE                     : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb0_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr0_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr0_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRISEL                    : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa1_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FISIE                     : 1;
    __IO uint32_t ERRIE                     : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb1_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr1_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr1_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRISEL                    : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa2_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FISIE                     : 1;
    __IO uint32_t ERRIE                     : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb2_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr2_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr2_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRISEL                    : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa3_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FISIE                     : 1;
    __IO uint32_t ERRIE                     : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb3_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr3_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr3_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRISEL                    : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa4_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FISIE                     : 1;
    __IO uint32_t ERRIE                     : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb4_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr4_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr4_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRISEL                    : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa5_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FISIE                     : 1;
    __IO uint32_t ERRIE                     : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb5_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr5_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr5_field_t;

typedef struct
{
    __IO uint32_t MODE                      : 2;
    __IO uint32_t OVR                       : 1;
    __IO uint32_t ZERO                      : 1;
    __IO uint32_t BUSY                      : 1;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_eau_csr_field_t;

typedef struct
{
    __IO uint32_t DIVIDEND                  :32;
} stc_eau_dividend_field_t;

typedef struct
{
    __IO uint32_t DIVISOR                   :32;
} stc_eau_divisor_field_t;

typedef struct
{
    __IO uint32_t QUOTIENT                  :32;
} stc_eau_quotient_field_t;

typedef struct
{
    __IO uint32_t REMAINDER                 :32;
} stc_eau_remainder_field_t;

typedef struct
{
    __IO uint32_t OP                        : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FWUP                      : 1;
    __IO uint32_t ROMD                      : 1;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t DPSTBEN                   : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_flash_cr_field_t;

typedef struct
{
    __IO uint32_t WAIT                      : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_flash_wait_field_t;

typedef struct
{
    __IO uint32_t STATE                     : 2;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_flash_lockst_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_flash_ier_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t CFDONE                    : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_flash_icr_field_t;

typedef struct
{
    __IO uint32_t BYSEQ                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :32;
} stc_flash_slock0_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :32;
} stc_flash_slock1_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_ads_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_dir_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_opendrain_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_driver_field_t;

typedef struct
{
    __IO uint32_t PUPIN0                    : 1;
    __IO uint32_t PUPIN1                    : 1;
    __IO uint32_t PUPIN2                    : 1;
    __IO uint32_t PUPIN3                    : 1;
    __IO uint32_t PUPIN4                    : 1;
    __IO uint32_t PUPIN5                    : 1;
    __IO uint32_t PUPIN6                    : 1;
    __IO uint32_t PUPIN7                    : 1;
    __IO uint32_t PUPIN8                    : 1;
    __IO uint32_t PUPIN9                    : 1;
    __IO uint32_t PUPIN10                   : 1;
    __IO uint32_t PUPIN11                   : 1;
    __IO uint32_t PUPIN12                   : 1;
    __IO uint32_t PUPIN13                   : 1;
    __IO uint32_t PUPIN14                   : 1;
    __IO uint32_t PUPIN15                   : 1;
    __IO uint32_t PDPIN0                    : 1;
    __IO uint32_t PDPIN1                    : 1;
    __IO uint32_t PDPIN2                    : 1;
    __IO uint32_t PDPIN3                    : 1;
    __IO uint32_t PDPIN4                    : 1;
    __IO uint32_t PDPIN5                    : 1;
    __IO uint32_t PDPIN6                    : 1;
    __IO uint32_t PDPIN7                    : 1;
    __IO uint32_t PDPIN8                    : 1;
    __IO uint32_t PDPIN9                    : 1;
    __IO uint32_t PDPIN10                   : 1;
    __IO uint32_t PDPIN11                   : 1;
    __IO uint32_t PDPIN12                   : 1;
    __IO uint32_t PDPIN13                   : 1;
    __IO uint32_t PDPIN14                   : 1;
    __IO uint32_t PDPIN15                   : 1;
} stc_gpio_pupd_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_in_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_out_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_brr_field_t;

typedef struct
{
    __IO uint32_t BSPIN0                    : 1;
    __IO uint32_t BSPIN1                    : 1;
    __IO uint32_t BSPIN2                    : 1;
    __IO uint32_t BSPIN3                    : 1;
    __IO uint32_t BSPIN4                    : 1;
    __IO uint32_t BSPIN5                    : 1;
    __IO uint32_t BSPIN6                    : 1;
    __IO uint32_t BSPIN7                    : 1;
    __IO uint32_t BSPIN8                    : 1;
    __IO uint32_t BSPIN9                    : 1;
    __IO uint32_t BSPIN10                   : 1;
    __IO uint32_t BSPIN11                   : 1;
    __IO uint32_t BSPIN12                   : 1;
    __IO uint32_t BSPIN13                   : 1;
    __IO uint32_t BSPIN14                   : 1;
    __IO uint32_t BSPIN15                   : 1;
    __IO uint32_t BRPIN0                    : 1;
    __IO uint32_t BRPIN1                    : 1;
    __IO uint32_t BRPIN2                    : 1;
    __IO uint32_t BRPIN3                    : 1;
    __IO uint32_t BRPIN4                    : 1;
    __IO uint32_t BRPIN5                    : 1;
    __IO uint32_t BRPIN6                    : 1;
    __IO uint32_t BRPIN7                    : 1;
    __IO uint32_t BRPIN8                    : 1;
    __IO uint32_t BRPIN9                    : 1;
    __IO uint32_t BRPIN10                   : 1;
    __IO uint32_t BRPIN11                   : 1;
    __IO uint32_t BRPIN12                   : 1;
    __IO uint32_t BRPIN13                   : 1;
    __IO uint32_t BRPIN14                   : 1;
    __IO uint32_t BRPIN15                   : 1;
} stc_gpio_bsrr_field_t;

typedef struct
{
    __IO uint32_t AFSEL0                    : 4;
    __IO uint32_t AFSEL1                    : 4;
    __IO uint32_t AFSEL2                    : 4;
    __IO uint32_t AFSEL3                    : 4;
    __IO uint32_t AFSEL4                    : 4;
    __IO uint32_t AFSEL5                    : 4;
    __IO uint32_t AFSEL6                    : 4;
    __IO uint32_t AFSEL7                    : 4;
} stc_gpio_afrl_field_t;

typedef struct
{
    __IO uint32_t AFSEL8                    : 4;
    __IO uint32_t AFSEL9                    : 4;
    __IO uint32_t AFSEL10                   : 4;
    __IO uint32_t AFSEL11                   : 4;
    __IO uint32_t AFSEL12                   : 4;
    __IO uint32_t AFSEL13                   : 4;
    __IO uint32_t AFSEL14                   : 4;
    __IO uint32_t AFSEL15                   : 4;
} stc_gpio_afrh_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_highie_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_lowie_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_riseie_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_fallie_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_ifr_field_t;

typedef struct
{
    __IO uint32_t PIN0                      : 1;
    __IO uint32_t PIN1                      : 1;
    __IO uint32_t PIN2                      : 1;
    __IO uint32_t PIN3                      : 1;
    __IO uint32_t PIN4                      : 1;
    __IO uint32_t PIN5                      : 1;
    __IO uint32_t PIN6                      : 1;
    __IO uint32_t PIN7                      : 1;
    __IO uint32_t PIN8                      : 1;
    __IO uint32_t PIN9                      : 1;
    __IO uint32_t PIN10                     : 1;
    __IO uint32_t PIN11                     : 1;
    __IO uint32_t PIN12                     : 1;
    __IO uint32_t PIN13                     : 1;
    __IO uint32_t PIN14                     : 1;
    __IO uint32_t PIN15                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_icr_field_t;

typedef struct
{
    __IO uint32_t PCLKDIV                   : 3;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t MCODIV                    : 3;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MCOSEL                    : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_cr0_field_t;

typedef struct
{
    __IO uint32_t ATIM0ETR                  : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t CTIM0ETR                  : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t CTIM1ETR                  : 3;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t ATIM3ETR                  : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_cr1_field_t;

typedef struct
{
    __IO uint32_t ATIM0CAP0                 : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t CTIM0CAP3                 : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t CTIM1CAP3                 : 3;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t ATIM3CAP3                 : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gpioaux_cr2_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cnt_field_t;

typedef struct
{
    __IO uint32_t CC0M                      : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t CC1M                      : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t CC2M                      : 3;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t CC3M                      : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cmmr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t ETRFLT                    : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cr1_field_t;

typedef struct
{
    __IO uint32_t CEN                       : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    __IO uint32_t TRS                       : 2;
    __IO uint32_t ETP                       : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_gtim_cr0_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t CC0                       : 1;
    __IO uint32_t CC1                       : 1;
    __IO uint32_t CC2                       : 1;
    __IO uint32_t CC3                       : 1;
    __IO uint32_t DCC0                      : 1;
    __IO uint32_t DCC1                      : 1;
    __IO uint32_t DCC2                      : 1;
    __IO uint32_t DCC3                      : 1;
    __IO uint32_t OVTRAD                    : 1;
    __IO uint32_t C0TRAD                    : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ier_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t CC0                       : 1;
    __IO uint32_t CC1                       : 1;
    __IO uint32_t CC2                       : 1;
    __IO uint32_t CC3                       : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ifr_field_t;

typedef struct
{
    __IO uint32_t UI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t CC0                       : 1;
    __IO uint32_t CC1                       : 1;
    __IO uint32_t CC2                       : 1;
    __IO uint32_t CC3                       : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_gtim_icr_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr0_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr1_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr2_field_t;

typedef struct
{
    __IO uint32_t CCR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gtim_ccr3_field_t;

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
    __IO uint32_t ADDR0                     : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr0_field_t;

typedef struct
{
    __IO uint32_t STAT                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t ADDR                      : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t ADDR                      : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr2_field_t;

typedef struct
{
    __IO uint32_t AD0F                      : 1;
    __IO uint32_t AD1F                      : 1;
    __IO uint32_t AD2F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_i2c_match_field_t;

typedef struct
{
    __IO uint32_t RD                        : 1;
    __IO uint32_t WR                        : 1;
    __IO uint32_t STOP                      : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t NACK                      : 1;
    __IO uint32_t I2CINT                    : 1;
    __IO uint32_t ACTIVE                    : 1;
    __IO uint32_t HSMODE                    : 1;
    __IO uint32_t TIMEOUT                   : 1;
    __IO uint32_t ACK                       : 1;
    __IO uint32_t SLADDR0                   : 1;
    __IO uint32_t SLADDR1                   : 1;
    __IO uint32_t SLADDR2                   : 1;
    __IO uint32_t SLADDR3                   : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t GC                        : 1;
    uint32_t RESERVED17                     :14;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_sr_field_t;

typedef struct
{
    __IO uint32_t DOUT                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_doutr_field_t;

typedef struct
{
    __IO uint32_t ADIR                      :10;
    __IO uint32_t ADRLEN                    : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_adir_field_t;

typedef struct
{
    __IO uint32_t ADDR                      :10;
    __IO uint32_t AM                        : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_sladr0_field_t;

typedef struct
{
    __IO uint32_t ADDR                      :10;
    __IO uint32_t AM                        : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_sladr1_field_t;

typedef struct
{
    __IO uint32_t ADDR                      :10;
    __IO uint32_t ADDRLEN                   : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_sladr2_field_t;

typedef struct
{
    __IO uint32_t ADDR                      :10;
    __IO uint32_t ADDRLEN                   : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_sladr3_field_t;

typedef struct
{
    __IO uint32_t DIN                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_dinr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t FSCLC                     : 1;
    __IO uint32_t TIMEOUT                   : 1;
    uint32_t RESERVED4                      : 3;
    __IO uint32_t GC                        : 1;
    __IO uint32_t DMATE                     : 1;
    __IO uint32_t DMARE                     : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_cr_field_t;

typedef struct
{
    __IO uint32_t ADDRMASK                  :10;
    __IO uint32_t FACS                      : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_admr0_field_t;

typedef struct
{
    __IO uint32_t FW                        : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_flt_field_t;

typedef struct
{
    __IO uint32_t TOR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_tor_field_t;

typedef struct
{
    __IO uint32_t ODPU                      : 2;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_oddr_field_t;

typedef struct
{
    __IO uint32_t NS                        : 2;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_rsr_field_t;

typedef struct
{
    __IO uint32_t RD                        : 1;
    __IO uint32_t WR                        : 1;
    __IO uint32_t STOP                      : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t NACK                      : 1;
    __IO uint32_t I2CINT                    : 1;
    __IO uint32_t ACTIVE                    : 1;
    __IO uint32_t HSMODE                    : 1;
    __IO uint32_t TIMEOUT                   : 1;
    __IO uint32_t ACK                       : 1;
    __IO uint32_t SLADDR0                   : 1;
    __IO uint32_t SLADDR1                   : 1;
    __IO uint32_t SLADDR2                   : 1;
    __IO uint32_t SLADDR3                   : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t GC                        : 1;
    uint32_t RESERVED17                     :14;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_ier_field_t;

typedef struct
{
    __IO uint32_t RD                        : 1;
    __IO uint32_t WR                        : 1;
    __IO uint32_t STOP                      : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t NACK                      : 1;
    __IO uint32_t I2CINT                    : 1;
    __IO uint32_t ACTIVE                    : 1;
    __IO uint32_t HSMODE                    : 1;
    __IO uint32_t TIMEOUT                   : 1;
    __IO uint32_t ACK                       : 1;
    __IO uint32_t SLADDR0                   : 1;
    __IO uint32_t SLADDR1                   : 1;
    __IO uint32_t SLADDR2                   : 1;
    __IO uint32_t SLADDR3                   : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t GC                        : 1;
    uint32_t RESERVED17                     :14;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_icr_field_t;

typedef struct
{
    __IO uint32_t RID                       : 3;
    __IO uint32_t PID                       : 9;
    __IO uint32_t MID                       :12;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_i2cslv_didr_field_t;

typedef struct
{
    __IO uint32_t KR                        :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_kr_field_t;

typedef struct
{
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t ACTION                    : 1;
    __IO uint32_t PAUSE                     : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_cr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_arr_field_t;

typedef struct
{
    __IO uint32_t PRSF                      : 1;
    __IO uint32_t ARRF                      : 1;
    __IO uint32_t WINRF                     : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t RUN                       : 1;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_sr_field_t;

typedef struct
{
    __IO uint32_t WINR                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_winr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lptim_cnt_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lptim_arr_field_t;

typedef struct
{
    __IO uint32_t CEN                       : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOG_EN                    : 1;
    __IO uint32_t TCK_SEL                   : 2;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t WT_FLAG                   : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATE_P                    : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t PRS                       : 4;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_lptim_cr_field_t;

typedef struct
{
    __IO uint32_t OV                        : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lptim_ifr_field_t;

typedef struct
{
    __IO uint32_t OV                        : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lptim_iclr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t DR8                       : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RCIE                      : 1;
    __IO uint32_t TCIE                      : 1;
    __IO uint32_t DR8CFG                    : 2;
    __IO uint32_t RXEN                      : 1;
    __IO uint32_t ADRDET                    : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t OVER                      : 2;
    __IO uint32_t CLKSRC                    : 2;
    __IO uint32_t PEIE                      : 1;
    __IO uint32_t STOP                      : 2;
    __IO uint32_t DMARXEN                   : 1;
    __IO uint32_t DMATXEN                   : 1;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t CTSIE                     : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t HDSEL                     : 1;
    uint32_t RESERVED23                     : 8;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_scon_field_t;

typedef struct
{
    __IO uint32_t ADDR                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_saden_field_t;

typedef struct
{
    __IO uint32_t RC                        : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t CTSIF                     : 1;
    __IO uint32_t CTS                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_isr_field_t;

typedef struct
{
    __IO uint32_t RC                        : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t FE                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t CTSIF                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_icr_field_t;

typedef struct
{
    __IO uint32_t SCNT                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_scnt_field_t;

typedef struct
{
    __IO uint32_t LVDEN                     : 1;
    __IO uint32_t ACT                       : 1;
    __IO uint32_t SOURCE                    : 2;
    __IO uint32_t VTDS                      : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCETIME              : 3;
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
    __IO uint32_t FILTER                    : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_lvd_sr_field_t;

typedef struct
{
    __IO uint32_t OPAEN                     : 1;
    __IO uint32_t AZEN                      : 1;
    uint32_t RESERVED2                      : 5;
    __IO uint32_t BIASSEL                   : 3;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_opa_cr0_field_t;

typedef struct
{
    __IO uint32_t OPAEN                     : 1;
    __IO uint32_t AZEN                      : 1;
    uint32_t RESERVED2                      : 5;
    __IO uint32_t BIASSEL                   : 3;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_opa_cr1_field_t;

typedef struct
{
    __IO uint32_t ADCTREN                   : 1;
    __IO uint32_t TRIGGER                   : 1;
    __IO uint32_t AZPULSE                   : 1;
    __IO uint32_t CLKSWSET                  : 1;
    __IO uint32_t CLKSEL                    : 4;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_opa_az_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_ram_cr_field_t;

typedef struct
{
    __IO uint32_t ERRADDR                   :14;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_ram_erraddr_field_t;

typedef struct
{
    __IO uint32_t ERR                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_ram_ifr_field_t;

typedef struct
{
    __IO uint32_t ERRCLR                    : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_ram_iclr_field_t;

typedef struct
{
    __IO uint32_t PRDS                      : 3;
    __IO uint32_t AMPM                      : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t HZ1OE                     : 1;
    __IO uint32_t HZ1SEL                    : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t PRDX                      : 6;
    __IO uint32_t PRDSEL                    : 1;
    __IO uint32_t TEST                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr0_field_t;

typedef struct
{
    __IO uint32_t WAIT                      : 1;
    __IO uint32_t WAITF                     : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t CKSEL                     : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr1_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_sec_field_t;

typedef struct
{
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_min_field_t;

typedef struct
{
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_hour_field_t;

typedef struct
{
    __IO uint32_t WEEK                      : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_rtc_week_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_day_field_t;

typedef struct
{
    __IO uint32_t MON                       : 5;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_rtc_mon_field_t;

typedef struct
{
    __IO uint32_t YEARL                     : 4;
    __IO uint32_t YEARH                     : 4;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_rtc_year_field_t;

typedef struct
{
    __IO uint32_t CR                        : 9;
    uint32_t RESERVED9                      : 6;
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_compen_field_t;

typedef struct
{
    __IO uint32_t WUCKSEL                   : 3;
    __IO uint32_t TSEDG                     : 1;
    __IO uint32_t O2SEL                     : 2;
    __IO uint32_t TSE                       : 1;
    __IO uint32_t WUTE                      : 1;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t ALMAE                     : 1;
    __IO uint32_t ALMBE                     : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr2_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    __IO uint32_t MSKS                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    __IO uint32_t MSKM                      : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 1;
    __IO uint32_t MSKH                      : 1;
    __IO uint32_t WEEK                      : 7;
    __IO uint32_t RSV                       : 1;
} stc_rtc_alma_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    __IO uint32_t MSKS                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    __IO uint32_t MSKM                      : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 1;
    __IO uint32_t MSKH                      : 1;
    __IO uint32_t WEEK                      : 7;
    __IO uint32_t RSV                       : 1;
} stc_rtc_almb_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 9;
    __IO uint32_t RSV                       : 1;
} stc_rtc_tstr_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t MON                       : 5;
    __IO uint32_t WEEK                      : 3;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_tsdr_field_t;

typedef struct
{
    __IO uint32_t WUTARR                    :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_wutarr_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_ier_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_ifr_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_icr_field_t;

typedef struct
{
    __IO uint32_t WPR                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_rtc_wpr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t BRR                       : 3;
    __IO uint32_t CPHA                      : 1;
    __IO uint32_t CPOL                      : 1;
    __IO uint32_t MSTR                      : 1;
    __IO uint32_t LSBF                      : 1;
    __IO uint32_t WIDTH                     : 4;
    __IO uint32_t SSM                       : 1;
    __IO uint32_t CM                        : 2;
    __IO uint32_t SMP                       : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr0_field_t;

typedef struct
{
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t RXNEIE                    : 1;
    __IO uint32_t SSFIE                     : 1;
    __IO uint32_t SSRIE                     : 1;
    __IO uint32_t UDFIE                     : 1;
    __IO uint32_t OVFIE                     : 1;
    __IO uint32_t SSERRIE                   : 1;
    __IO uint32_t MODFIE                    : 1;
    __IO uint32_t DMARXEN                   : 1;
    __IO uint32_t DMATXEN                   : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr1_field_t;

typedef struct
{
    __IO uint32_t HDOE                      : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_hdoe_field_t;

typedef struct
{
    __IO uint32_t SSI                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_ssi_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t SSF                       : 1;
    __IO uint32_t SSR                       : 1;
    __IO uint32_t UDF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t MODF                      : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t SSLVL                     : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_spi_sr_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t SSF                       : 1;
    __IO uint32_t SSR                       : 1;
    __IO uint32_t UDF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t MODF                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_icr_field_t;

typedef struct
{
    __IO uint32_t DR                        :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_spi_dr_field_t;

typedef struct
{
    __IO uint32_t CLKSRC                    : 3;
    __IO uint32_t HCLKPRS                   : 3;
    __IO uint32_t PCLKPRS                   : 2;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_cr0_field_t;

typedef struct
{
    __IO uint32_t SWDUSEIO                  : 1;
    __IO uint32_t LOCKUP_EN                 : 1;
    __IO uint32_t WAKEUPBYRCH               : 1;
    __IO uint32_t RTCLPW                    : 1;
    __IO uint32_t RTCADJ                    : 3;
    __IO uint32_t AUTOSWITCH                : 1;
    __IO uint32_t SPIPCTRL                  : 1;
    __IO uint32_t XTHFLT                    : 1;
    __IO uint32_t GTIM0CFG                  : 1;
    __IO uint32_t GTIM1CFG                  : 1;
    __IO uint32_t FASTIOENB                 : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_cr1_field_t;

typedef struct
{
    __IO uint32_t RCH                       : 1;
    __IO uint32_t XTH                       : 1;
    __IO uint32_t RCL                       : 1;
    __IO uint32_t XTL                       : 1;
    __IO uint32_t PLL                       : 1;
    __IO uint32_t EXXTH                     : 1;
    __IO uint32_t EXXTL                     : 1;
    __IO uint32_t XTLLOCK                   : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_cr2_field_t;

typedef struct
{
    __IO uint32_t CR3                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_cr3_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rchcr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t RANGE                     : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t DETEN                     : 1;
    __IO uint32_t DETTIME                   : 1;
    __IO uint32_t DETIE                     : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xthcr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :10;
    __IO uint32_t STARTUP                   : 2;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rclcr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t AMP_SEL                   : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t DETEN                     : 1;
    __IO uint32_t DETTIME                   : 1;
    __IO uint32_t DETIE                     : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xtlcr_field_t;

typedef struct
{
    __IO uint32_t SRC                       : 2;
    __IO uint32_t DIVR                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t WAITCYCLE                 : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t DIVN                      : 7;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t DIVF                      : 3;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t POSTDIV                   : 4;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_pllcr_field_t;

typedef struct
{
    __IO uint32_t TRIML                     : 6;
    __IO uint32_t TRIMH                     : 5;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rchtrim_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :10;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rcltrim_field_t;

typedef struct
{
    __IO uint32_t RCH                       : 1;
    __IO uint32_t XTH                       : 1;
    __IO uint32_t RCL                       : 1;
    __IO uint32_t XTL                       : 1;
    __IO uint32_t PLL                       : 1;
    __IO uint32_t PLLLOCK                   : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t XTHFAIL                   : 1;
    __IO uint32_t XTHFAULT                  : 1;
    __IO uint32_t XTLFAIL                   : 1;
    __IO uint32_t XTLFAULT                  : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_state_field_t;

typedef struct
{
    __IO uint32_t USART0                    : 1;
    __IO uint32_t USART1                    : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t I2C0                      : 1;
    __IO uint32_t I2C1                      : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t ATIM0                     : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t ATIM1                     : 1;
    __IO uint32_t ATIM3                     : 1;
    __IO uint32_t ATIM2                     : 1;
    __IO uint32_t OPA                       : 1;
    __IO uint32_t WWDT                      : 1;
    __IO uint32_t IWDT                      : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VCLVD                     : 1;
    __IO uint32_t I2CSLV                    : 1;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t CTRIM                     : 1;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t TICK                      : 1;
    __IO uint32_t SWD                       : 1;
    __IO uint32_t CRC                       : 1;
    uint32_t RESERVED27                     : 2;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t EAU                       : 1;
    __IO uint32_t FLASH                     : 1;
} stc_sysctrl_periclken0_field_t;

typedef struct
{
    __IO uint32_t GPIOA                     : 1;
    __IO uint32_t GPIOB                     : 1;
    __IO uint32_t GPIOC                     : 1;
    __IO uint32_t GPIOD                     : 1;
    uint32_t RESERVED4                      : 3;
    __IO uint32_t CAN                       : 1;
    __IO uint32_t GTIM0                     : 1;
    __IO uint32_t GTIM1                     : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_periclken1_field_t;

typedef struct
{
    __IO uint32_t USART0                    : 1;
    __IO uint32_t USART1                    : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t I2C0                      : 1;
    __IO uint32_t I2C1                      : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t ATIM0                     : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t ATIM1                     : 1;
    __IO uint32_t ATIM3                     : 1;
    __IO uint32_t ATIM2                     : 1;
    __IO uint32_t OPA                       : 1;
    __IO uint32_t WWDT                      : 1;
    __IO uint32_t IWDT                      : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VCLVD                     : 1;
    __IO uint32_t I2CSLV                    : 1;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t CTRIM                     : 1;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t TICK                      : 1;
    __IO uint32_t SWD                       : 1;
    __IO uint32_t CRC                       : 1;
    uint32_t RESERVED27                     : 2;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t EAU                       : 1;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_perireset0_field_t;

typedef struct
{
    __IO uint32_t GPIOA                     : 1;
    __IO uint32_t GPIOB                     : 1;
    __IO uint32_t GPIOC                     : 1;
    __IO uint32_t GPIOD                     : 1;
    uint32_t RESERVED4                      : 3;
    __IO uint32_t CAN                       : 1;
    __IO uint32_t GTIM0                     : 1;
    __IO uint32_t GTIM1                     : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_perireset1_field_t;

typedef struct
{
    __IO uint32_t POR5V                     : 1;
    __IO uint32_t POR12V                    : 1;
    __IO uint32_t LVD                       : 1;
    __IO uint32_t IWDT                      : 1;
    __IO uint32_t WWDT                      : 1;
    __IO uint32_t LOCKUP                    : 1;
    __IO uint32_t SYSREQ                    : 1;
    __IO uint32_t RSTB                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rstflag_field_t;

typedef struct
{
    __IO uint32_t ATIM0                     : 1;
    __IO uint32_t ATIM1                     : 1;
    __IO uint32_t ATIM2                     : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t GTIM0                     : 1;
    __IO uint32_t GTIM1                     : 1;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t CTRIM                     : 1;
    __IO uint32_t IWDT                      : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t TICK                      : 1;
    __IO uint32_t ATIM3                     : 1;
    __IO uint32_t WWDT                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_dbgstop_field_t;

typedef struct
{
    __IO uint32_t RE                        : 1;
    __IO uint32_t TE                        : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t PCE                       : 1;
    __IO uint32_t CHLEN                     : 1;
    __IO uint32_t STOP                      : 1;
    __IO uint32_t MSB                       : 1;
    __IO uint32_t OVER8                     : 1;
    __IO uint32_t TOE                       : 3;
    __IO uint32_t SBS                       : 1;
    __IO uint32_t COMB                      : 1;
    __IO uint32_t MPE                       : 1;
    __IO uint32_t SLME                      : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_cr1_field_t;

typedef struct
{
    __IO uint32_t RXDMAEN                   : 1;
    __IO uint32_t TXDMAEN                   : 1;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t RXINV                     : 1;
    __IO uint32_t TXINV                     : 1;
    __IO uint32_t SYNC                      : 1;
    __IO uint32_t SWAP                      : 1;
    __IO uint32_t CLKC                      : 2;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_usart_cr2_field_t;

typedef struct
{
    __IO uint32_t LINEN                     : 1;
    __IO uint32_t LBDE                      : 1;
    __IO uint32_t ABRE                      : 1;
    __IO uint32_t BREAK                     : 1;
    __IO uint32_t SCEN                      : 1;
    __IO uint32_t BCN                       : 3;
    __IO uint32_t SMCPU                     : 2;
    uint32_t RESERVED10                     : 3;
    __IO uint32_t IREN                      : 1;
    __IO uint32_t IRCW                      : 1;
    __IO uint32_t IRMOD                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_usart_cr3_field_t;

typedef struct
{
    __IO uint32_t DIVF                      : 7;
    __IO uint32_t FBME                      : 1;
    __IO uint32_t DIVI                      : 8;
    __IO uint32_t PSC                       : 2;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_usart_brr_field_t;

typedef struct
{
    __IO uint32_t TOR                       :20;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_usart_tor_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t OR                        : 1;
    __IO uint32_t TO                        : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t MPB                       : 1;
    __IO uint32_t AM                        : 1;
    __IO uint32_t CTSV                      : 1;
    __IO uint32_t CTS                       : 1;
    __IO uint32_t ABR                       : 1;
    __IO uint32_t LBD                       : 1;
    __IO uint32_t DWK                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_sr_field_t;

typedef struct
{
    __IO uint32_t TDR                       : 9;
    __IO uint32_t MPID                      : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_usart_tdr_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t OR                        : 1;
    __IO uint32_t TO                        : 1;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t AM                        : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t CTS                       : 1;
    __IO uint32_t ABR                       : 1;
    __IO uint32_t LBD                       : 1;
    __IO uint32_t DWK                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_ier_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t OR                        : 1;
    __IO uint32_t TO                        : 1;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t AM                        : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t CTS                       : 1;
    __IO uint32_t ABR                       : 1;
    __IO uint32_t LBD                       : 1;
    __IO uint32_t DWK                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_icr_field_t;

typedef struct
{
    __IO uint32_t RDR                       : 9;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_usart_rdr_field_t;

typedef struct
{
    __IO uint32_t ADDR                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_usart_addr_field_t;

typedef struct
{
    __IO uint32_t ADDM                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_usart_addmr_field_t;

typedef struct
{
    __IO uint32_t BDR                       :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_usart_bdr_field_t;

typedef struct
{
    __IO uint32_t DCNTL                     :11;
    uint32_t RESERVED11                     : 5;
    __IO uint32_t DCNTH                     :11;
    uint32_t RESERVED27                     : 4;
    __IO uint32_t RSV                       : 1;
} stc_usart_ir_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIVEN                     : 1;
    __IO uint32_t REF                       : 1;
    __IO uint32_t BIAS                      : 2;
    __IO uint32_t HYS                       : 2;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr0_field_t;

typedef struct
{
    __IO uint32_t PSEL                      : 4;
    __IO uint32_t NSEL                      : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t FLTTIME                   : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t EN                        : 1;
    __IO uint32_t FLTCLK                    : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr1_field_t;

typedef struct
{
    __IO uint32_t POL                       : 1;
    __IO uint32_t ATIM0CLR                  : 1;
    __IO uint32_t ATIM1CLR                  : 1;
    __IO uint32_t ATIM2CLR                  : 1;
    __IO uint32_t ATIM3CLR                  : 1;
    __IO uint32_t ATIMBK                    : 1;
    __IO uint32_t WINDOW                    : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr2_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FLTV                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_vc_sr_field_t;

typedef struct
{
    __IO uint32_t WCNT                      : 7;
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_wwdt_cr0_field_t;

typedef struct
{
    __IO uint32_t WINR                      : 7;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_wwdt_cr1_field_t;

typedef struct
{
    __IO uint32_t POV                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_wwdt_sr_field_t;


typedef struct
{
    union
    {
        __IO uint32_t BGR;
        stc_adc_bgr_field_t BGR_f;
    };
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
    uint8_t RESERVED3[36];
    union
    {
        __IO uint32_t IER;
        stc_adc_ier_field_t IER_f;
    };
    uint8_t RESERVED4[12];
    union
    {
        __IO uint32_t SQR0;
        stc_adc_sqr0_field_t SQR0_f;
    };
    union
    {
        __IO uint32_t SQR1;
        stc_adc_sqr1_field_t SQR1_f;
    };
    union
    {
        __IO uint32_t SQR2;
        stc_adc_sqr2_field_t SQR2_f;
    };
    union
    {
        __IO uint32_t JQR;
        stc_adc_jqr_field_t JQR_f;
    };
    union
    {
        __IO uint32_t SQRRESULT0;
        stc_adc_sqrresult0_field_t SQRRESULT0_f;
    };
    union
    {
        __IO uint32_t SQRRESULT1;
        stc_adc_sqrresult1_field_t SQRRESULT1_f;
    };
    union
    {
        __IO uint32_t SQRRESULT2;
        stc_adc_sqrresult2_field_t SQRRESULT2_f;
    };
    union
    {
        __IO uint32_t SQRRESULT3;
        stc_adc_sqrresult3_field_t SQRRESULT3_f;
    };
    uint8_t RESERVED12[48];
    union
    {
        __IO uint32_t JQRRESULT0;
        stc_adc_jqrresult0_field_t JQRRESULT0_f;
    };
    union
    {
        __IO uint32_t JQRRESULT1;
        stc_adc_jqrresult1_field_t JQRRESULT1_f;
    };
    union
    {
        __IO uint32_t JQRRESULT2;
        stc_adc_jqrresult2_field_t JQRRESULT2_f;
    };
    union
    {
        __IO uint32_t JQRRESULT3;
        stc_adc_jqrresult3_field_t JQRRESULT3_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_adc_result_field_t RESULT_f;
    };
    union
    {
        __IO uint32_t RESULTACC;
        stc_adc_resultacc_field_t RESULTACC_f;
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
        __IO uint32_t ICR;
        stc_adc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t EXTTRIG0;
        stc_adc_exttrig0_field_t EXTTRIG0_f;
    };
    union
    {
        __IO uint32_t EXTTRIG1;
        stc_adc_exttrig1_field_t EXTTRIG1_f;
    };
    union
    {
        __IO uint32_t SGLSTART;
        stc_adc_sglstart_field_t SGLSTART_f;
    };
    union
    {
        __IO uint32_t SQRSTART;
        stc_adc_sqrstart_field_t SQRSTART_f;
    };
    union
    {
        __IO uint32_t JQRSTART;
        stc_adc_jqrstart_field_t JQRSTART_f;
    };
}ADC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_atim3mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_atim3mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_atim3mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atim3mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atim3mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_atim3mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_atim3mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_atim3mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_atim3mode23_crch0_field_t CRCH0_f;
    };
    union
    {
        __IO uint32_t CRCH1;
        stc_atim3mode23_crch1_field_t CRCH1_f;
    };
    union
    {
        __IO uint32_t CRCH2;
        stc_atim3mode23_crch2_field_t CRCH2_f;
    };
    union
    {
        __IO uint32_t DTR;
        stc_atim3mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_atim3mode23_rcr_field_t RCR_f;
    };
    uint8_t RESERVED13[4];
    union
    {
        __IO uint32_t CCR0A;
        stc_atim3mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_atim3mode23_ccr0b_field_t CCR0B_f;
    };
    union
    {
        __IO uint32_t CCR1A;
        stc_atim3mode23_ccr1a_field_t CCR1A_f;
    };
    union
    {
        __IO uint32_t CCR1B;
        stc_atim3mode23_ccr1b_field_t CCR1B_f;
    };
    union
    {
        __IO uint32_t CCR2A;
        stc_atim3mode23_ccr2a_field_t CCR2A_f;
    };
    union
    {
        __IO uint32_t CCR2B;
        stc_atim3mode23_ccr2b_field_t CCR2B_f;
    };
    union
    {
        __IO uint32_t CCR3A;
        stc_atim3mode23_ccr3a_field_t CCR3A_f;
    };
    union
    {
        __IO uint32_t CRCH3A;
        stc_atim3mode23_crch3a_field_t CRCH3A_f;
    };
    union
    {
        __IO uint32_t CCR3B;
        stc_atim3mode23_ccr3b_field_t CCR3B_f;
    };
    union
    {
        __IO uint32_t CRCH3B;
        stc_atim3mode23_crch3b_field_t CRCH3B_f;
    };
}ATIM3MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_atimmode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_atimmode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_atimmode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_atimmode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atimmode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atimmode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_atimmode0_dtr_field_t DTR_f;
    };
}ATIMMODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_atimmode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_atimmode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atimmode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atimmode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_atimmode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_atimmode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_atimmode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_atimmode1_ccr0a_field_t CCR0A_f;
    };
}ATIMMODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_atimmode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_atimmode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_atimmode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_atimmode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_atimmode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_atimmode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_atimmode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_atimmode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_atimmode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_atimmode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_atimmode23_rcr_field_t RCR_f;
    };
    uint8_t RESERVED11[4];
    union
    {
        __IO uint32_t CCR0A;
        stc_atimmode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_atimmode23_ccr0b_field_t CCR0B_f;
    };
}ATIMMODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_btim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_btim_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[8];
    union
    {
        __IO uint32_t CR;
        stc_btim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_btim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_btim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_btim_icr_field_t ICR_f;
    };
    uint8_t RESERVED6[40];
    union
    {
        __IO uint32_t AIFR;
        stc_btim_aifr_field_t AIFR_f;
    };
    union
    {
        __IO uint32_t AICR;
        stc_btim_aicr_field_t AICR_f;
    };
}BTIM_TypeDef;

typedef struct
{
    __IO uint32_t RBUF0;
    __IO uint32_t RBUF1;
    __IO uint32_t RBUF2;
    __IO uint32_t RBUF3;
    uint8_t RESERVED4[64];
    __IO uint32_t TBUF0;
    __IO uint32_t TBUF1;
    __IO uint32_t TBUF2;
    __IO uint32_t TBUF3;
    uint8_t RESERVED8[64];
    union
    {
        __IO uint8_t CFG_STAT;
        stc_can_cfg_stat_field_t CFG_STAT_f;
    };
    union
    {
        __IO uint8_t TCMD;
        stc_can_tcmd_field_t TCMD_f;
    };
    union
    {
        __IO uint8_t TCTRL;
        stc_can_tctrl_field_t TCTRL_f;
    };
    union
    {
        __IO uint8_t RCTRL;
        stc_can_rctrl_field_t RCTRL_f;
    };
    union
    {
        __IO uint8_t RTIE;
        stc_can_rtie_field_t RTIE_f;
    };
    union
    {
        __IO uint8_t RTIF;
        stc_can_rtif_field_t RTIF_f;
    };
    union
    {
        __IO uint8_t ERRINT;
        stc_can_errint_field_t ERRINT_f;
    };
    union
    {
        __IO uint8_t LIMIT;
        stc_can_limit_field_t LIMIT_f;
    };
    union
    {
        __IO uint32_t BT;
        stc_can_bt_field_t BT_f;
    };
    uint8_t RESERVED17[4];
    union
    {
        __IO uint8_t EALCAP;
        stc_can_ealcap_field_t EALCAP_f;
    };
    uint8_t RESERVED18[1];
    __IO uint8_t RECNT;
    __IO uint8_t TECNT;
    union
    {
        __IO uint8_t ACFCTRL;
        stc_can_acfctrl_field_t ACFCTRL_f;
    };
    uint8_t RESERVED21[1];
    union
    {
        __IO uint8_t ACFEN;
        stc_can_acfen_field_t ACFEN_f;
    };
    uint8_t RESERVED22[1];
    union
    {
        __IO uint32_t ACF;
        stc_can_acf_field_t ACF_f;
    };
    uint8_t RESERVED23[2];
    union
    {
        __IO uint8_t TBSLOT;
        stc_can_tbslot_field_t TBSLOT_f;
    };
    union
    {
        __IO uint8_t TTCFG;
        stc_can_ttcfg_field_t TTCFG_f;
    };
    union
    {
        __IO uint32_t REF_MSG;
        stc_can_ref_msg_field_t REF_MSG_f;
    };
    union
    {
        __IO uint16_t TRG_CFG;
        stc_can_trg_cfg_field_t TRG_CFG_f;
    };
    __IO uint16_t TT_TRIG;
    __IO uint16_t TT_WTRIG;
}CAN_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CSR;
        stc_crc_csr_field_t CSR_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_crc_result_field_t RESULT_f;
    };
    uint8_t RESERVED2[120];
    union
    {
        __IO uint32_t DATA;
        stc_crc_data_field_t DATA_f;
    };
}CRC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_ctrim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_ctrim_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t CR0;
        stc_ctrim_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_ctrim_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_ctrim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_ctrim_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_ctrim_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t FCAP;
        stc_ctrim_fcap_field_t FCAP_f;
    };
    union
    {
        __IO uint32_t TVAL;
        stc_ctrim_tval_field_t TVAL_f;
    };
    union
    {
        __IO uint32_t FLIM;
        stc_ctrim_flim_field_t FLIM_f;
    };
}CTRIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CONF;
        stc_dmac_conf_field_t CONF_f;
    };
    uint8_t RESERVED1[12];
    union
    {
        __IO uint32_t CONFA0;
        stc_dmac_confa0_field_t CONFA0_f;
    };
    union
    {
        __IO uint32_t CONFB0;
        stc_dmac_confb0_field_t CONFB0_f;
    };
    union
    {
        __IO uint32_t SRCADR0;
        stc_dmac_srcadr0_field_t SRCADR0_f;
    };
    union
    {
        __IO uint32_t DSTADR0;
        stc_dmac_dstadr0_field_t DSTADR0_f;
    };
    union
    {
        __IO uint32_t CONFA1;
        stc_dmac_confa1_field_t CONFA1_f;
    };
    union
    {
        __IO uint32_t CONFB1;
        stc_dmac_confb1_field_t CONFB1_f;
    };
    union
    {
        __IO uint32_t SRCADR1;
        stc_dmac_srcadr1_field_t SRCADR1_f;
    };
    union
    {
        __IO uint32_t DSTADR1;
        stc_dmac_dstadr1_field_t DSTADR1_f;
    };
    union
    {
        __IO uint32_t CONFA2;
        stc_dmac_confa2_field_t CONFA2_f;
    };
    union
    {
        __IO uint32_t CONFB2;
        stc_dmac_confb2_field_t CONFB2_f;
    };
    union
    {
        __IO uint32_t SRCADR2;
        stc_dmac_srcadr2_field_t SRCADR2_f;
    };
    union
    {
        __IO uint32_t DSTADR2;
        stc_dmac_dstadr2_field_t DSTADR2_f;
    };
    union
    {
        __IO uint32_t CONFA3;
        stc_dmac_confa3_field_t CONFA3_f;
    };
    union
    {
        __IO uint32_t CONFB3;
        stc_dmac_confb3_field_t CONFB3_f;
    };
    union
    {
        __IO uint32_t SRCADR3;
        stc_dmac_srcadr3_field_t SRCADR3_f;
    };
    union
    {
        __IO uint32_t DSTADR3;
        stc_dmac_dstadr3_field_t DSTADR3_f;
    };
    union
    {
        __IO uint32_t CONFA4;
        stc_dmac_confa4_field_t CONFA4_f;
    };
    union
    {
        __IO uint32_t CONFB4;
        stc_dmac_confb4_field_t CONFB4_f;
    };
    union
    {
        __IO uint32_t SRCADR4;
        stc_dmac_srcadr4_field_t SRCADR4_f;
    };
    union
    {
        __IO uint32_t DSTADR4;
        stc_dmac_dstadr4_field_t DSTADR4_f;
    };
    union
    {
        __IO uint32_t CONFA5;
        stc_dmac_confa5_field_t CONFA5_f;
    };
    union
    {
        __IO uint32_t CONFB5;
        stc_dmac_confb5_field_t CONFB5_f;
    };
    union
    {
        __IO uint32_t SRCADR5;
        stc_dmac_srcadr5_field_t SRCADR5_f;
    };
    union
    {
        __IO uint32_t DSTADR5;
        stc_dmac_dstadr5_field_t DSTADR5_f;
    };
}DMAC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CSR;
        stc_eau_csr_field_t CSR_f;
    };
    union
    {
        __IO uint32_t DIVIDEND;
        stc_eau_dividend_field_t DIVIDEND_f;
    };
    union
    {
        __IO uint32_t DIVISOR;
        stc_eau_divisor_field_t DIVISOR_f;
    };
    union
    {
        __IO uint32_t QUOTIENT;
        stc_eau_quotient_field_t QUOTIENT_f;
    };
    union
    {
        __IO uint32_t REMAINDER;
        stc_eau_remainder_field_t REMAINDER_f;
    };
}EAU_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_flash_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t WAIT;
        stc_flash_wait_field_t WAIT_f;
    };
    union
    {
        __IO uint32_t LOCKST;
        stc_flash_lockst_field_t LOCKST_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_flash_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_flash_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_flash_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t BYPASS;
        stc_flash_bypass_field_t BYPASS_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t SLOCK0;
        stc_flash_slock0_field_t SLOCK0_f;
    };
    union
    {
        __IO uint32_t SLOCK1;
        stc_flash_slock1_field_t SLOCK1_f;
    };
}FLASH_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ADS;
        stc_gpio_ads_field_t ADS_f;
    };
    union
    {
        __IO uint32_t DIR;
        stc_gpio_dir_field_t DIR_f;
    };
    union
    {
        __IO uint32_t OPENDRAIN;
        stc_gpio_opendrain_field_t OPENDRAIN_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t DRIVER;
        stc_gpio_driver_field_t DRIVER_f;
    };
    uint8_t RESERVED4[4];
    union
    {
        __IO uint32_t PUPD;
        stc_gpio_pupd_field_t PUPD_f;
    };
    union
    {
        __IO uint32_t IN;
        stc_gpio_in_field_t IN_f;
    };
    union
    {
        __IO uint32_t OUT;
        stc_gpio_out_field_t OUT_f;
    };
    union
    {
        __IO uint32_t BRR;
        stc_gpio_brr_field_t BRR_f;
    };
    union
    {
        __IO uint32_t BSRR;
        stc_gpio_bsrr_field_t BSRR_f;
    };
    uint8_t RESERVED9[4];
    union
    {
        __IO uint32_t AFRL;
        stc_gpio_afrl_field_t AFRL_f;
    };
    union
    {
        __IO uint32_t AFRH;
        stc_gpio_afrh_field_t AFRH_f;
    };
    union
    {
        __IO uint32_t HIGHIE;
        stc_gpio_highie_field_t HIGHIE_f;
    };
    union
    {
        __IO uint32_t LOWIE;
        stc_gpio_lowie_field_t LOWIE_f;
    };
    union
    {
        __IO uint32_t RISEIE;
        stc_gpio_riseie_field_t RISEIE_f;
    };
    union
    {
        __IO uint32_t FALLIE;
        stc_gpio_fallie_field_t FALLIE_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_gpio_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_gpio_icr_field_t ICR_f;
    };
}GPIO_TypeDef;

typedef struct
{
    uint8_t RESERVED0[112];
    union
    {
        __IO uint32_t CR0;
        stc_gpioaux_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_gpioaux_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_gpioaux_cr2_field_t CR2_f;
    };
}GPIOAUX_TypeDef;

typedef struct
{
    uint8_t RESERVED0[768];
    union
    {
        __IO uint32_t ARR;
        stc_gtim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_gtim_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CMMR;
        stc_gtim_cmmr_field_t CMMR_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_gtim_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR0;
        stc_gtim_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_gtim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_gtim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_gtim_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t CCR0;
        stc_gtim_ccr0_field_t CCR0_f;
    };
    union
    {
        __IO uint32_t CCR1;
        stc_gtim_ccr1_field_t CCR1_f;
    };
    union
    {
        __IO uint32_t CCR2;
        stc_gtim_ccr2_field_t CCR2_f;
    };
    union
    {
        __IO uint32_t CCR3;
        stc_gtim_ccr3_field_t CCR3_f;
    };
}GTIM_TypeDef;

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
        __IO uint32_t ADDR0;
        stc_i2c_addr0_field_t ADDR0_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_i2c_stat_field_t STAT_f;
    };
    uint8_t RESERVED6[8];
    union
    {
        __IO uint32_t ADDR1;
        stc_i2c_addr1_field_t ADDR1_f;
    };
    union
    {
        __IO uint32_t ADDR2;
        stc_i2c_addr2_field_t ADDR2_f;
    };
    union
    {
        __IO uint32_t MATCH;
        stc_i2c_match_field_t MATCH_f;
    };
}I2C_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SR;
        stc_i2cslv_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t DOUTR;
        stc_i2cslv_doutr_field_t DOUTR_f;
    };
    union
    {
        __IO uint32_t ADIR;
        stc_i2cslv_adir_field_t ADIR_f;
    };
    union
    {
        __IO uint32_t SLADR0;
        stc_i2cslv_sladr0_field_t SLADR0_f;
    };
    union
    {
        __IO uint32_t SLADR1;
        stc_i2cslv_sladr1_field_t SLADR1_f;
    };
    union
    {
        __IO uint32_t SLADR2;
        stc_i2cslv_sladr2_field_t SLADR2_f;
    };
    union
    {
        __IO uint32_t SLADR3;
        stc_i2cslv_sladr3_field_t SLADR3_f;
    };
    union
    {
        __IO uint32_t DINR;
        stc_i2cslv_dinr_field_t DINR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_i2cslv_cr_field_t CR_f;
    };
    uint8_t RESERVED9[12];
    union
    {
        __IO uint32_t ADMR0;
        stc_i2cslv_admr0_field_t ADMR0_f;
    };
    uint8_t RESERVED10[12];
    union
    {
        __IO uint32_t FLT;
        stc_i2cslv_flt_field_t FLT_f;
    };
    union
    {
        __IO uint32_t TOR;
        stc_i2cslv_tor_field_t TOR_f;
    };
    union
    {
        __IO uint32_t ODDR;
        stc_i2cslv_oddr_field_t ODDR_f;
    };
    union
    {
        __IO uint32_t RSR;
        stc_i2cslv_rsr_field_t RSR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_i2cslv_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_i2cslv_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t DIDR;
        stc_i2cslv_didr_field_t DIDR_f;
    };
}I2CSLV_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t KR;
        stc_iwdt_kr_field_t KR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_iwdt_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_iwdt_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_iwdt_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t WINR;
        stc_iwdt_winr_field_t WINR_f;
    };
}IWDT_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNT;
        stc_lptim_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_lptim_arr_field_t ARR_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t CR;
        stc_lptim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lptim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_lptim_iclr_field_t ICLR_f;
    };
}LPTIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_lpuart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_lpuart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_lpuart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_lpuart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_lpuart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_lpuart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t SCNT;
        stc_lpuart_scnt_field_t SCNT_f;
    };
}LPUART_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_lvd_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_lvd_sr_field_t SR_f;
    };
}LVD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_opa_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_opa_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t AZ;
        stc_opa_az_field_t AZ_f;
    };
}OPA_TypeDef;

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
}RAM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_rtc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_rtc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SEC;
        stc_rtc_sec_field_t SEC_f;
    };
    union
    {
        __IO uint32_t MIN;
        stc_rtc_min_field_t MIN_f;
    };
    union
    {
        __IO uint32_t HOUR;
        stc_rtc_hour_field_t HOUR_f;
    };
    union
    {
        __IO uint32_t WEEK;
        stc_rtc_week_field_t WEEK_f;
    };
    union
    {
        __IO uint32_t DAY;
        stc_rtc_day_field_t DAY_f;
    };
    union
    {
        __IO uint32_t MON;
        stc_rtc_mon_field_t MON_f;
    };
    union
    {
        __IO uint32_t YEAR;
        stc_rtc_year_field_t YEAR_f;
    };
    uint8_t RESERVED9[12];
    union
    {
        __IO uint32_t COMPEN;
        stc_rtc_compen_field_t COMPEN_f;
    };
    uint8_t RESERVED10[8];
    union
    {
        __IO uint32_t CR2;
        stc_rtc_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t ALMA;
        stc_rtc_alma_field_t ALMA_f;
    };
    union
    {
        __IO uint32_t ALMB;
        stc_rtc_almb_field_t ALMB_f;
    };
    union
    {
        __IO uint32_t TSTR;
        stc_rtc_tstr_field_t TSTR_f;
    };
    union
    {
        __IO uint32_t TSDR;
        stc_rtc_tsdr_field_t TSDR_f;
    };
    union
    {
        __IO uint32_t WUTARR;
        stc_rtc_wutarr_field_t WUTARR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_rtc_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_rtc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_rtc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t WPR;
        stc_rtc_wpr_field_t WPR_f;
    };
}RTC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_spi_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_spi_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t HDOE;
        stc_spi_hdoe_field_t HDOE_f;
    };
    union
    {
        __IO uint32_t SSI;
        stc_spi_ssi_field_t SSI_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_spi_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_spi_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t DR;
        stc_spi_dr_field_t DR_f;
    };
}SPI_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_sysctrl_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_sysctrl_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_sysctrl_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t CR3;
        stc_sysctrl_cr3_field_t CR3_f;
    };
    union
    {
        __IO uint32_t RCHCR;
        stc_sysctrl_rchcr_field_t RCHCR_f;
    };
    union
    {
        __IO uint32_t XTHCR;
        stc_sysctrl_xthcr_field_t XTHCR_f;
    };
    union
    {
        __IO uint32_t RCLCR;
        stc_sysctrl_rclcr_field_t RCLCR_f;
    };
    union
    {
        __IO uint32_t XTLCR;
        stc_sysctrl_xtlcr_field_t XTLCR_f;
    };
    union
    {
        __IO uint32_t PLLCR;
        stc_sysctrl_pllcr_field_t PLLCR_f;
    };
    union
    {
        __IO uint32_t RCHTRIM;
        stc_sysctrl_rchtrim_field_t RCHTRIM_f;
    };
    union
    {
        __IO uint32_t RCLTRIM;
        stc_sysctrl_rcltrim_field_t RCLTRIM_f;
    };
    union
    {
        __IO uint32_t STATE;
        stc_sysctrl_state_field_t STATE_f;
    };
    union
    {
        __IO uint32_t PERICLKEN0;
        stc_sysctrl_periclken0_field_t PERICLKEN0_f;
    };
    union
    {
        __IO uint32_t PERICLKEN1;
        stc_sysctrl_periclken1_field_t PERICLKEN1_f;
    };
    union
    {
        __IO uint32_t PERIRESET0;
        stc_sysctrl_perireset0_field_t PERIRESET0_f;
    };
    union
    {
        __IO uint32_t PERIRESET1;
        stc_sysctrl_perireset1_field_t PERIRESET1_f;
    };
    union
    {
        __IO uint32_t RSTFLAG;
        stc_sysctrl_rstflag_field_t RSTFLAG_f;
    };
    union
    {
        __IO uint32_t DBGSTOP;
        stc_sysctrl_dbgstop_field_t DBGSTOP_f;
    };
}SYSCTRL_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR1;
        stc_usart_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_usart_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t CR3;
        stc_usart_cr3_field_t CR3_f;
    };
    union
    {
        __IO uint32_t BRR;
        stc_usart_brr_field_t BRR_f;
    };
    union
    {
        __IO uint32_t TOR;
        stc_usart_tor_field_t TOR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_usart_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t TDR;
        stc_usart_tdr_field_t TDR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_usart_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_usart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t RDR;
        stc_usart_rdr_field_t RDR_f;
    };
    union
    {
        __IO uint32_t ADDR;
        stc_usart_addr_field_t ADDR_f;
    };
    union
    {
        __IO uint32_t ADDMR;
        stc_usart_addmr_field_t ADDMR_f;
    };
    union
    {
        __IO uint32_t BDR;
        stc_usart_bdr_field_t BDR_f;
    };
    uint8_t RESERVED13[188];
    union
    {
        __IO uint32_t IR;
        stc_usart_ir_field_t IR_f;
    };
}USART_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_vc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_vc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_vc_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_vc_sr_field_t SR_f;
    };
}VC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_wwdt_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_wwdt_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_wwdt_sr_field_t SR_f;
    };
}WWDT_TypeDef;



#define PERIPH_BASE                            (0x40000000UL)
#define ADC_BASE                               (PERIPH_BASE + 0x00002500UL)
#define ATIM0MODE0_BASE                        (PERIPH_BASE + 0x00003000UL)
#define ATIM0MODE1_BASE                        (PERIPH_BASE + 0x00003000UL)
#define ATIM0MODE23_BASE                       (PERIPH_BASE + 0x00003000UL)
#define ATIM1MODE0_BASE                        (PERIPH_BASE + 0x00003400UL)
#define ATIM1MODE1_BASE                        (PERIPH_BASE + 0x00003400UL)
#define ATIM1MODE23_BASE                       (PERIPH_BASE + 0x00003400UL)
#define ATIM2MODE0_BASE                        (PERIPH_BASE + 0x00003800UL)
#define ATIM2MODE1_BASE                        (PERIPH_BASE + 0x00003800UL)
#define ATIM2MODE23_BASE                       (PERIPH_BASE + 0x00003800UL)
#define ATIM3MODE0_BASE                        (PERIPH_BASE + 0x00005800UL)
#define ATIM3MODE1_BASE                        (PERIPH_BASE + 0x00005800UL)
#define ATIM3MODE23_BASE                       (PERIPH_BASE + 0x00005800UL)
#define BTIM0_BASE                             (PERIPH_BASE + 0x00001800UL)
#define BTIM1_BASE                             (PERIPH_BASE + 0x00001900UL)
#define BTIM2_BASE                             (PERIPH_BASE + 0x00001A00UL)
#define BTIM3_BASE                             (PERIPH_BASE + 0x00001C00UL)
#define BTIM4_BASE                             (PERIPH_BASE + 0x00001D00UL)
#define BTIM5_BASE                             (PERIPH_BASE + 0x00001E00UL)
#define CAN_BASE                               (PERIPH_BASE + 0x00030000UL)
#define CRC_BASE                               (PERIPH_BASE + 0x00020800UL)
#define CTRIM_BASE                             (PERIPH_BASE + 0x00005000UL)
#define DMAC_BASE                              (PERIPH_BASE + 0x00021000UL)
#define EAU_BASE                               (PERIPH_BASE + 0x00021800UL)
#define FLASH_BASE                             (PERIPH_BASE + 0x00020000UL)
#define GPIOA_BASE                             (PERIPH_BASE + 0x00020C00UL)
#define GPIOAUX_BASE                           (PERIPH_BASE + 0x00002000UL)
#define GPIOB_BASE                             (PERIPH_BASE + 0x00021C00UL)
#define GPIOC_BASE                             (PERIPH_BASE + 0x00022000UL)
#define GPIOD_BASE                             (PERIPH_BASE + 0x00022400UL)
#define GTIM0_BASE                             (PERIPH_BASE + 0x00001800UL)
#define GTIM1_BASE                             (PERIPH_BASE + 0x00001C00UL)
#define I2C0_BASE                              (PERIPH_BASE + 0x00000400UL)
#define I2C1_BASE                              (PERIPH_BASE + 0x00004400UL)
#define I2CSLV_BASE                            (PERIPH_BASE + 0x00004C00UL)
#define IWDT_BASE                              (PERIPH_BASE + 0x00001080UL)
#define LPTIM_BASE                             (PERIPH_BASE + 0x00000C00UL)
#define LPUART0_BASE                           (PERIPH_BASE + 0x00000000UL)
#define LPUART1_BASE                           (PERIPH_BASE + 0x00004000UL)
#define LVD_BASE                               (PERIPH_BASE + 0x00002480UL)
#define OPA_BASE                               (PERIPH_BASE + 0x00002600UL)
#define RAM_BASE                               (PERIPH_BASE + 0x00020400UL)
#define RTC_BASE                               (PERIPH_BASE + 0x00001400UL)
#define SPI0_BASE                              (PERIPH_BASE + 0x00000800UL)
#define SPI1_BASE                              (PERIPH_BASE + 0x00004800UL)
#define SYSCTRL_BASE                           (PERIPH_BASE + 0x00002000UL)
#define USART0_BASE                            (PERIPH_BASE + 0x00006000UL)
#define USART1_BASE                            (PERIPH_BASE + 0x00006400UL)
#define VC0_BASE                               (PERIPH_BASE + 0x00002400UL)
#define VC1_BASE                               (PERIPH_BASE + 0x00002410UL)
#define WWDT_BASE                              (PERIPH_BASE + 0x00006800UL)


#define HC_ADC                                    ((ADC_TypeDef *)0x40002500UL)
#define HC_ATIM0MODE0                             ((ATIMMODE0_TypeDef *)0x40003000UL)
#define HC_ATIM0MODE1                             ((ATIMMODE1_TypeDef *)0x40003000UL)
#define HC_ATIM0MODE23                            ((ATIMMODE23_TypeDef *)0x40003000UL)
#define HC_ATIM1MODE0                             ((ATIMMODE0_TypeDef *)0x40003400UL)
#define HC_ATIM1MODE1                             ((ATIMMODE1_TypeDef *)0x40003400UL)
#define HC_ATIM1MODE23                            ((ATIMMODE23_TypeDef *)0x40003400UL)
#define HC_ATIM2MODE0                             ((ATIMMODE0_TypeDef *)0x40003800UL)
#define HC_ATIM2MODE1                             ((ATIMMODE1_TypeDef *)0x40003800UL)
#define HC_ATIM2MODE23                            ((ATIMMODE23_TypeDef *)0x40003800UL)
#define HC_ATIM3MODE0                             ((ATIMMODE0_TypeDef *)0x40005800UL)
#define HC_ATIM3MODE1                             ((ATIMMODE1_TypeDef *)0x40005800UL)
#define HC_ATIM3MODE23                            ((ATIM3MODE23_TypeDef *)0x40005800UL)
#define HC_BTIM0                                  ((BTIM_TypeDef *)0x40001800UL)
#define HC_BTIM1                                  ((BTIM_TypeDef *)0x40001900UL)
#define HC_BTIM2                                  ((BTIM_TypeDef *)0x40001A00UL)
#define HC_BTIM3                                  ((BTIM_TypeDef *)0x40001C00UL)
#define HC_BTIM4                                  ((BTIM_TypeDef *)0x40001D00UL)
#define HC_BTIM5                                  ((BTIM_TypeDef *)0x40001E00UL)
#define HC_CAN                                    ((CAN_TypeDef *)0x40030000UL)
#define HC_CRC                                    ((CRC_TypeDef *)0x40020800UL)
#define HC_CTRIM                                  ((CTRIM_TypeDef *)0x40005000UL)
#define HC_DMAC                                   ((DMAC_TypeDef *)0x40021000UL)
#define HC_EAU                                    ((EAU_TypeDef *)0x40021800UL)
#define HC_FLASH                                  ((FLASH_TypeDef *)0x40020000UL)
#define HC_GPIOA                                  ((GPIO_TypeDef *)0x40020C00UL)
#define HC_GPIOAUX                                ((GPIOAUX_TypeDef *)0x40002000UL)
#define HC_GPIOB                                  ((GPIO_TypeDef *)0x40021C00UL)
#define HC_GPIOC                                  ((GPIO_TypeDef *)0x40022000UL)
#define HC_GPIOD                                  ((GPIO_TypeDef *)0x40022400UL)
#define HC_GTIM0                                  ((GTIM_TypeDef *)0x40001800UL)
#define HC_GTIM1                                  ((GTIM_TypeDef *)0x40001C00UL)
#define HC_I2C0                                   ((I2C_TypeDef *)0x40000400UL)
#define HC_I2C1                                   ((I2C_TypeDef *)0x40004400UL)
#define HC_I2CSLV                                 ((I2CSLV_TypeDef *)0x40004C00UL)
#define HC_IWDT                                   ((IWDT_TypeDef *)0x40001080UL)
#define HC_LPTIM                                  ((LPTIM_TypeDef *)0x40000C00UL)
#define HC_LPUART0                                ((LPUART_TypeDef *)0x40000000UL)
#define HC_LPUART1                                ((LPUART_TypeDef *)0x40004000UL)
#define HC_LVD                                    ((LVD_TypeDef *)0x40002480UL)
#define HC_OPA                                    ((OPA_TypeDef *)0x40002600UL)
#define HC_RAM                                    ((RAM_TypeDef *)0x40020400UL)
#define HC_RTC                                    ((RTC_TypeDef *)0x40001400UL)
#define HC_SPI0                                   ((SPI_TypeDef *)0x40000800UL)
#define HC_SPI1                                   ((SPI_TypeDef *)0x40004800UL)
#define HC_SYSCTRL                                ((SYSCTRL_TypeDef *)0x40002000UL)
#define HC_USART0                                 ((USART_TypeDef *)0x40006000UL)
#define HC_USART1                                 ((USART_TypeDef *)0x40006400UL)
#define HC_VC0                                    ((VC_TypeDef *)0x40002400UL)
#define HC_VC1                                    ((VC_TypeDef *)0x40002410UL)
#define HC_WWDT                                   ((WWDT_TypeDef *)0x40006800UL)


//********************    Bits Define For Peripheral ADC    ********************//
// ADC_BGR
#define ADC_BGR_BGREN_Pos                                   (0U)
#define ADC_BGR_BGREN_Msk                                   (0x1UL << ADC_BGR_BGREN_Pos)
#define ADC_BGR_BGREN                                       ADC_BGR_BGREN_Msk
#define ADC_BGR_TSEN_Pos                                    (1U)
#define ADC_BGR_TSEN_Msk                                    (0x1UL << ADC_BGR_TSEN_Pos)
#define ADC_BGR_TSEN                                        ADC_BGR_TSEN_Msk

// ADC_CR0
#define ADC_CR0_EN_Pos                                      (0U)
#define ADC_CR0_EN_Msk                                      (0x1UL << ADC_CR0_EN_Pos)
#define ADC_CR0_EN                                          ADC_CR0_EN_Msk
#define ADC_CR0_CKDIV_Pos                                   (1U)
#define ADC_CR0_CKDIV_Msk                                   (0x7UL << ADC_CR0_CKDIV_Pos)
#define ADC_CR0_CKDIV                                       ADC_CR0_CKDIV_Msk
#define ADC_CR0_SGLMUX_Pos                                  (4U)
#define ADC_CR0_SGLMUX_Msk                                  (0x1FUL << ADC_CR0_SGLMUX_Pos)
#define ADC_CR0_SGLMUX                                      ADC_CR0_SGLMUX_Msk
#define ADC_CR0_REF_Pos                                     (9U)
#define ADC_CR0_REF_Msk                                     (0x3UL << ADC_CR0_REF_Pos)
#define ADC_CR0_REF                                         ADC_CR0_REF_Msk
#define ADC_CR0_BUF_Pos                                     (11U)
#define ADC_CR0_BUF_Msk                                     (0x1UL << ADC_CR0_BUF_Pos)
#define ADC_CR0_BUF                                         ADC_CR0_BUF_Msk
#define ADC_CR0_SAM_Pos                                     (12U)
#define ADC_CR0_SAM_Msk                                     (0x3UL << ADC_CR0_SAM_Pos)
#define ADC_CR0_SAM                                         ADC_CR0_SAM_Msk

// ADC_CR1
#define ADC_CR1_MODE_Pos                                    (0U)
#define ADC_CR1_MODE_Msk                                    (0x3UL << ADC_CR1_MODE_Pos)
#define ADC_CR1_MODE                                        ADC_CR1_MODE_Msk
#define ADC_CR1_ALIGN_Pos                                   (2U)
#define ADC_CR1_ALIGN_Msk                                   (0x1UL << ADC_CR1_ALIGN_Pos)
#define ADC_CR1_ALIGN                                       ADC_CR1_ALIGN_Msk
#define ADC_CR1_THCH_Pos                                    (3U)
#define ADC_CR1_THCH_Msk                                    (0x1FUL << ADC_CR1_THCH_Pos)
#define ADC_CR1_THCH                                        ADC_CR1_THCH_Msk
#define ADC_CR1_OVMD_Pos                                    (10U)
#define ADC_CR1_OVMD_Msk                                    (0x1UL << ADC_CR1_OVMD_Pos)
#define ADC_CR1_OVMD                                        ADC_CR1_OVMD_Msk
#define ADC_CR1_RACCEN_Pos                                  (11U)
#define ADC_CR1_RACCEN_Msk                                  (0x1UL << ADC_CR1_RACCEN_Pos)
#define ADC_CR1_RACCEN                                      ADC_CR1_RACCEN_Msk
#define ADC_CR1_LTCMP_Pos                                   (12U)
#define ADC_CR1_LTCMP_Msk                                   (0x1UL << ADC_CR1_LTCMP_Pos)
#define ADC_CR1_LTCMP                                       ADC_CR1_LTCMP_Msk
#define ADC_CR1_HTCMP_Pos                                   (13U)
#define ADC_CR1_HTCMP_Msk                                   (0x1UL << ADC_CR1_HTCMP_Pos)
#define ADC_CR1_HTCMP                                       ADC_CR1_HTCMP_Msk
#define ADC_CR1_REGCMP_Pos                                  (14U)
#define ADC_CR1_REGCMP_Msk                                  (0x1UL << ADC_CR1_REGCMP_Pos)
#define ADC_CR1_REGCMP                                      ADC_CR1_REGCMP_Msk
#define ADC_CR1_RACCCLR_Pos                                 (15U)
#define ADC_CR1_RACCCLR_Msk                                 (0x1UL << ADC_CR1_RACCCLR_Pos)
#define ADC_CR1_RACCCLR                                     ADC_CR1_RACCCLR_Msk

// ADC_IER
#define ADC_IER_ESG_Pos                                     (0U)
#define ADC_IER_ESG_Msk                                     (0x1UL << ADC_IER_ESG_Pos)
#define ADC_IER_ESG                                         ADC_IER_ESG_Msk
#define ADC_IER_LTI_Pos                                     (1U)
#define ADC_IER_LTI_Msk                                     (0x1UL << ADC_IER_LTI_Pos)
#define ADC_IER_LTI                                         ADC_IER_LTI_Msk
#define ADC_IER_HTI_Pos                                     (2U)
#define ADC_IER_HTI_Msk                                     (0x1UL << ADC_IER_HTI_Pos)
#define ADC_IER_HTI                                         ADC_IER_HTI_Msk
#define ADC_IER_RGI_Pos                                     (3U)
#define ADC_IER_RGI_Msk                                     (0x1UL << ADC_IER_RGI_Pos)
#define ADC_IER_RGI                                         ADC_IER_RGI_Msk
#define ADC_IER_EOS_Pos                                     (4U)
#define ADC_IER_EOS_Msk                                     (0x1UL << ADC_IER_EOS_Pos)
#define ADC_IER_EOS                                         ADC_IER_EOS_Msk
#define ADC_IER_EOJ_Pos                                     (5U)
#define ADC_IER_EOJ_Msk                                     (0x1UL << ADC_IER_EOJ_Pos)
#define ADC_IER_EOJ                                         ADC_IER_EOJ_Msk
#define ADC_IER_EOC_Pos                                     (6U)
#define ADC_IER_EOC_Msk                                     (0x1UL << ADC_IER_EOC_Pos)
#define ADC_IER_EOC                                         ADC_IER_EOC_Msk
#define ADC_IER_DEOC_Pos                                    (7U)
#define ADC_IER_DEOC_Msk                                    (0x1UL << ADC_IER_DEOC_Pos)
#define ADC_IER_DEOC                                        ADC_IER_DEOC_Msk
#define ADC_IER_DEOJ_Pos                                    (8U)
#define ADC_IER_DEOJ_Msk                                    (0x1UL << ADC_IER_DEOJ_Pos)
#define ADC_IER_DEOJ                                        ADC_IER_DEOJ_Msk
#define ADC_IER_OV_Pos                                      (9U)
#define ADC_IER_OV_Msk                                      (0x1UL << ADC_IER_OV_Pos)
#define ADC_IER_OV                                          ADC_IER_OV_Msk

// ADC_SQR0
#define ADC_SQR0_CH0MUX_Pos                                 (0U)
#define ADC_SQR0_CH0MUX_Msk                                 (0x1FUL << ADC_SQR0_CH0MUX_Pos)
#define ADC_SQR0_CH0MUX                                     ADC_SQR0_CH0MUX_Msk
#define ADC_SQR0_CH1MUX_Pos                                 (5U)
#define ADC_SQR0_CH1MUX_Msk                                 (0x1FUL << ADC_SQR0_CH1MUX_Pos)
#define ADC_SQR0_CH1MUX                                     ADC_SQR0_CH1MUX_Msk
#define ADC_SQR0_CH2MUX_Pos                                 (10U)
#define ADC_SQR0_CH2MUX_Msk                                 (0x1FUL << ADC_SQR0_CH2MUX_Pos)
#define ADC_SQR0_CH2MUX                                     ADC_SQR0_CH2MUX_Msk
#define ADC_SQR0_CH3MUX_Pos                                 (15U)
#define ADC_SQR0_CH3MUX_Msk                                 (0x1FUL << ADC_SQR0_CH3MUX_Pos)
#define ADC_SQR0_CH3MUX                                     ADC_SQR0_CH3MUX_Msk
#define ADC_SQR0_CH4MUX_Pos                                 (20U)
#define ADC_SQR0_CH4MUX_Msk                                 (0x1FUL << ADC_SQR0_CH4MUX_Pos)
#define ADC_SQR0_CH4MUX                                     ADC_SQR0_CH4MUX_Msk
#define ADC_SQR0_CH5MUX_Pos                                 (25U)
#define ADC_SQR0_CH5MUX_Msk                                 (0x1FUL << ADC_SQR0_CH5MUX_Pos)
#define ADC_SQR0_CH5MUX                                     ADC_SQR0_CH5MUX_Msk

// ADC_SQR1
#define ADC_SQR1_CH6MUX_Pos                                 (0U)
#define ADC_SQR1_CH6MUX_Msk                                 (0x1FUL << ADC_SQR1_CH6MUX_Pos)
#define ADC_SQR1_CH6MUX                                     ADC_SQR1_CH6MUX_Msk
#define ADC_SQR1_CH7MUX_Pos                                 (5U)
#define ADC_SQR1_CH7MUX_Msk                                 (0x1FUL << ADC_SQR1_CH7MUX_Pos)
#define ADC_SQR1_CH7MUX                                     ADC_SQR1_CH7MUX_Msk
#define ADC_SQR1_CH8MUX_Pos                                 (10U)
#define ADC_SQR1_CH8MUX_Msk                                 (0x1FUL << ADC_SQR1_CH8MUX_Pos)
#define ADC_SQR1_CH8MUX                                     ADC_SQR1_CH8MUX_Msk
#define ADC_SQR1_CH9MUX_Pos                                 (15U)
#define ADC_SQR1_CH9MUX_Msk                                 (0x1FUL << ADC_SQR1_CH9MUX_Pos)
#define ADC_SQR1_CH9MUX                                     ADC_SQR1_CH9MUX_Msk
#define ADC_SQR1_CH10MUX_Pos                                (20U)
#define ADC_SQR1_CH10MUX_Msk                                (0x1FUL << ADC_SQR1_CH10MUX_Pos)
#define ADC_SQR1_CH10MUX                                    ADC_SQR1_CH10MUX_Msk
#define ADC_SQR1_CH11MUX_Pos                                (25U)
#define ADC_SQR1_CH11MUX_Msk                                (0x1FUL << ADC_SQR1_CH11MUX_Pos)
#define ADC_SQR1_CH11MUX                                    ADC_SQR1_CH11MUX_Msk

// ADC_SQR2
#define ADC_SQR2_CH12MUX_Pos                                (0U)
#define ADC_SQR2_CH12MUX_Msk                                (0x1FUL << ADC_SQR2_CH12MUX_Pos)
#define ADC_SQR2_CH12MUX                                    ADC_SQR2_CH12MUX_Msk
#define ADC_SQR2_CH13MUX_Pos                                (5U)
#define ADC_SQR2_CH13MUX_Msk                                (0x1FUL << ADC_SQR2_CH13MUX_Pos)
#define ADC_SQR2_CH13MUX                                    ADC_SQR2_CH13MUX_Msk
#define ADC_SQR2_CH14MUX_Pos                                (10U)
#define ADC_SQR2_CH14MUX_Msk                                (0x1FUL << ADC_SQR2_CH14MUX_Pos)
#define ADC_SQR2_CH14MUX                                    ADC_SQR2_CH14MUX_Msk
#define ADC_SQR2_CH15MUX_Pos                                (15U)
#define ADC_SQR2_CH15MUX_Msk                                (0x1FUL << ADC_SQR2_CH15MUX_Pos)
#define ADC_SQR2_CH15MUX                                    ADC_SQR2_CH15MUX_Msk
#define ADC_SQR2_CNT_Pos                                    (20U)
#define ADC_SQR2_CNT_Msk                                    (0xFUL << ADC_SQR2_CNT_Pos)
#define ADC_SQR2_CNT                                        ADC_SQR2_CNT_Msk

// ADC_JQR
#define ADC_JQR_CH0MUX_Pos                                  (0U)
#define ADC_JQR_CH0MUX_Msk                                  (0x1FUL << ADC_JQR_CH0MUX_Pos)
#define ADC_JQR_CH0MUX                                      ADC_JQR_CH0MUX_Msk
#define ADC_JQR_CH1MUX_Pos                                  (5U)
#define ADC_JQR_CH1MUX_Msk                                  (0x1FUL << ADC_JQR_CH1MUX_Pos)
#define ADC_JQR_CH1MUX                                      ADC_JQR_CH1MUX_Msk
#define ADC_JQR_CH2MUX_Pos                                  (10U)
#define ADC_JQR_CH2MUX_Msk                                  (0x1FUL << ADC_JQR_CH2MUX_Pos)
#define ADC_JQR_CH2MUX                                      ADC_JQR_CH2MUX_Msk
#define ADC_JQR_CH3MUX_Pos                                  (15U)
#define ADC_JQR_CH3MUX_Msk                                  (0x1FUL << ADC_JQR_CH3MUX_Pos)
#define ADC_JQR_CH3MUX                                      ADC_JQR_CH3MUX_Msk
#define ADC_JQR_CNT_Pos                                     (20U)
#define ADC_JQR_CNT_Msk                                     (0x3UL << ADC_JQR_CNT_Pos)
#define ADC_JQR_CNT                                         ADC_JQR_CNT_Msk

// ADC_SQRRESULT0
#define ADC_SQRRESULT0_RESULT_Pos                           (0U)
#define ADC_SQRRESULT0_RESULT_Msk                           (0xFFFFUL << ADC_SQRRESULT0_RESULT_Pos)
#define ADC_SQRRESULT0_RESULT                               ADC_SQRRESULT0_RESULT_Msk

// ADC_SQRRESULT1
#define ADC_SQRRESULT1_RESULT_Pos                           (0U)
#define ADC_SQRRESULT1_RESULT_Msk                           (0xFFFFUL << ADC_SQRRESULT1_RESULT_Pos)
#define ADC_SQRRESULT1_RESULT                               ADC_SQRRESULT1_RESULT_Msk

// ADC_SQRRESULT2
#define ADC_SQRRESULT2_RESULT_Pos                           (0U)
#define ADC_SQRRESULT2_RESULT_Msk                           (0xFFFFUL << ADC_SQRRESULT2_RESULT_Pos)
#define ADC_SQRRESULT2_RESULT                               ADC_SQRRESULT2_RESULT_Msk

// ADC_SQRRESULT3
#define ADC_SQRRESULT3_RESULT_Pos                           (0U)
#define ADC_SQRRESULT3_RESULT_Msk                           (0xFFFFUL << ADC_SQRRESULT3_RESULT_Pos)
#define ADC_SQRRESULT3_RESULT                               ADC_SQRRESULT3_RESULT_Msk

// ADC_JQRRESULT0
#define ADC_JQRRESULT0_RESULT_Pos                           (0U)
#define ADC_JQRRESULT0_RESULT_Msk                           (0xFFFFUL << ADC_JQRRESULT0_RESULT_Pos)
#define ADC_JQRRESULT0_RESULT                               ADC_JQRRESULT0_RESULT_Msk

// ADC_JQRRESULT1
#define ADC_JQRRESULT1_RESULT_Pos                           (0U)
#define ADC_JQRRESULT1_RESULT_Msk                           (0xFFFFUL << ADC_JQRRESULT1_RESULT_Pos)
#define ADC_JQRRESULT1_RESULT                               ADC_JQRRESULT1_RESULT_Msk

// ADC_JQRRESULT2
#define ADC_JQRRESULT2_RESULT_Pos                           (0U)
#define ADC_JQRRESULT2_RESULT_Msk                           (0xFFFFUL << ADC_JQRRESULT2_RESULT_Pos)
#define ADC_JQRRESULT2_RESULT                               ADC_JQRRESULT2_RESULT_Msk

// ADC_JQRRESULT3
#define ADC_JQRRESULT3_RESULT_Pos                           (0U)
#define ADC_JQRRESULT3_RESULT_Msk                           (0xFFFFUL << ADC_JQRRESULT3_RESULT_Pos)
#define ADC_JQRRESULT3_RESULT                               ADC_JQRRESULT3_RESULT_Msk

// ADC_RESULT
#define ADC_RESULT_RESULT_Pos                               (0U)
#define ADC_RESULT_RESULT_Msk                               (0xFFFFUL << ADC_RESULT_RESULT_Pos)
#define ADC_RESULT_RESULT                                   ADC_RESULT_RESULT_Msk

// ADC_RESULTACC
#define ADC_RESULTACC_RESULTACC_Pos                         (0U)
#define ADC_RESULTACC_RESULTACC_Msk                         (0xFFFFFUL << ADC_RESULTACC_RESULTACC_Pos)
#define ADC_RESULTACC_RESULTACC                             ADC_RESULTACC_RESULTACC_Msk

// ADC_HT
#define ADC_HT_HT_Pos                                       (0U)
#define ADC_HT_HT_Msk                                       (0xFFFUL << ADC_HT_HT_Pos)
#define ADC_HT_HT                                           ADC_HT_HT_Msk

// ADC_LT
#define ADC_LT_LT_Pos                                       (0U)
#define ADC_LT_LT_Msk                                       (0xFFFUL << ADC_LT_LT_Pos)
#define ADC_LT_LT                                           ADC_LT_LT_Msk

// ADC_IFR
#define ADC_IFR_ESG_Pos                                     (0U)
#define ADC_IFR_ESG_Msk                                     (0x1UL << ADC_IFR_ESG_Pos)
#define ADC_IFR_ESG                                         ADC_IFR_ESG_Msk
#define ADC_IFR_LTI_Pos                                     (1U)
#define ADC_IFR_LTI_Msk                                     (0x1UL << ADC_IFR_LTI_Pos)
#define ADC_IFR_LTI                                         ADC_IFR_LTI_Msk
#define ADC_IFR_HTI_Pos                                     (2U)
#define ADC_IFR_HTI_Msk                                     (0x1UL << ADC_IFR_HTI_Pos)
#define ADC_IFR_HTI                                         ADC_IFR_HTI_Msk
#define ADC_IFR_RGI_Pos                                     (3U)
#define ADC_IFR_RGI_Msk                                     (0x1UL << ADC_IFR_RGI_Pos)
#define ADC_IFR_RGI                                         ADC_IFR_RGI_Msk
#define ADC_IFR_EOS_Pos                                     (4U)
#define ADC_IFR_EOS_Msk                                     (0x1UL << ADC_IFR_EOS_Pos)
#define ADC_IFR_EOS                                         ADC_IFR_EOS_Msk
#define ADC_IFR_EOJ_Pos                                     (5U)
#define ADC_IFR_EOJ_Msk                                     (0x1UL << ADC_IFR_EOJ_Pos)
#define ADC_IFR_EOJ                                         ADC_IFR_EOJ_Msk
#define ADC_IFR_EOC_Pos                                     (6U)
#define ADC_IFR_EOC_Msk                                     (0x1UL << ADC_IFR_EOC_Pos)
#define ADC_IFR_EOC                                         ADC_IFR_EOC_Msk
#define ADC_IFR_OV_Pos                                      (9U)
#define ADC_IFR_OV_Msk                                      (0x1UL << ADC_IFR_OV_Pos)
#define ADC_IFR_OV                                          ADC_IFR_OV_Msk
#define ADC_IFR_RDY_Pos                                     (10U)
#define ADC_IFR_RDY_Msk                                     (0x1UL << ADC_IFR_RDY_Pos)
#define ADC_IFR_RDY                                         ADC_IFR_RDY_Msk

// ADC_ICR
#define ADC_ICR_ESG_Pos                                     (0U)
#define ADC_ICR_ESG_Msk                                     (0x1UL << ADC_ICR_ESG_Pos)
#define ADC_ICR_ESG                                         ADC_ICR_ESG_Msk
#define ADC_ICR_LTI_Pos                                     (1U)
#define ADC_ICR_LTI_Msk                                     (0x1UL << ADC_ICR_LTI_Pos)
#define ADC_ICR_LTI                                         ADC_ICR_LTI_Msk
#define ADC_ICR_HTI_Pos                                     (2U)
#define ADC_ICR_HTI_Msk                                     (0x1UL << ADC_ICR_HTI_Pos)
#define ADC_ICR_HTI                                         ADC_ICR_HTI_Msk
#define ADC_ICR_RGI_Pos                                     (3U)
#define ADC_ICR_RGI_Msk                                     (0x1UL << ADC_ICR_RGI_Pos)
#define ADC_ICR_RGI                                         ADC_ICR_RGI_Msk
#define ADC_ICR_EOS_Pos                                     (4U)
#define ADC_ICR_EOS_Msk                                     (0x1UL << ADC_ICR_EOS_Pos)
#define ADC_ICR_EOS                                         ADC_ICR_EOS_Msk
#define ADC_ICR_EOJ_Pos                                     (5U)
#define ADC_ICR_EOJ_Msk                                     (0x1UL << ADC_ICR_EOJ_Pos)
#define ADC_ICR_EOJ                                         ADC_ICR_EOJ_Msk
#define ADC_ICR_EOC_Pos                                     (6U)
#define ADC_ICR_EOC_Msk                                     (0x1UL << ADC_ICR_EOC_Pos)
#define ADC_ICR_EOC                                         ADC_ICR_EOC_Msk
#define ADC_ICR_OV_Pos                                      (9U)
#define ADC_ICR_OV_Msk                                      (0x1UL << ADC_ICR_OV_Pos)
#define ADC_ICR_OV                                          ADC_ICR_OV_Msk

// ADC_EXTTRIG0
#define ADC_EXTTRIG0_TRIG_Pos                               (0U)
#define ADC_EXTTRIG0_TRIG_Msk                               (0x1FUL << ADC_EXTTRIG0_TRIG_Pos)
#define ADC_EXTTRIG0_TRIG                                   ADC_EXTTRIG0_TRIG_Msk
#define ADC_EXTTRIG0_DELAY_Pos                              (5U)
#define ADC_EXTTRIG0_DELAY_Msk                              (0x1UL << ADC_EXTTRIG0_DELAY_Pos)
#define ADC_EXTTRIG0_DELAY                                  ADC_EXTTRIG0_DELAY_Msk

// ADC_EXTTRIG1
#define ADC_EXTTRIG1_TRIG_Pos                               (0U)
#define ADC_EXTTRIG1_TRIG_Msk                               (0x1FUL << ADC_EXTTRIG1_TRIG_Pos)
#define ADC_EXTTRIG1_TRIG                                   ADC_EXTTRIG1_TRIG_Msk
#define ADC_EXTTRIG1_DELAY_Pos                              (5U)
#define ADC_EXTTRIG1_DELAY_Msk                              (0x1UL << ADC_EXTTRIG1_DELAY_Pos)
#define ADC_EXTTRIG1_DELAY                                  ADC_EXTTRIG1_DELAY_Msk

// ADC_SGLSTART
#define ADC_SGLSTART_START_Pos                              (0U)
#define ADC_SGLSTART_START_Msk                              (0x1UL << ADC_SGLSTART_START_Pos)
#define ADC_SGLSTART_START                                  ADC_SGLSTART_START_Msk

// ADC_SQRSTART
#define ADC_SQRSTART_START_Pos                              (0U)
#define ADC_SQRSTART_START_Msk                              (0x1UL << ADC_SQRSTART_START_Pos)
#define ADC_SQRSTART_START                                  ADC_SQRSTART_START_Msk

// ADC_JQRSTART
#define ADC_JQRSTART_START_Pos                              (0U)
#define ADC_JQRSTART_START_Msk                              (0x1UL << ADC_JQRSTART_START_Pos)
#define ADC_JQRSTART_START                                  ADC_JQRSTART_START_Msk



//********************    Bits Define For Peripheral ATIM3MODE23    ********************//
// ATIM3MODE23_ARR
#define ATIM3MODE23_ARR_ARR_Pos                             (0U)
#define ATIM3MODE23_ARR_ARR_Msk                             (0xFFFFUL << ATIM3MODE23_ARR_ARR_Pos)
#define ATIM3MODE23_ARR_ARR                                 ATIM3MODE23_ARR_ARR_Msk

// ATIM3MODE23_CNT
#define ATIM3MODE23_CNT_CNT_Pos                             (0U)
#define ATIM3MODE23_CNT_CNT_Msk                             (0xFFFFUL << ATIM3MODE23_CNT_CNT_Pos)
#define ATIM3MODE23_CNT_CNT                                 ATIM3MODE23_CNT_CNT_Msk

// ATIM3MODE23_M23CR
#define ATIM3MODE23_M23CR_CTEN_Pos                          (0U)
#define ATIM3MODE23_M23CR_CTEN_Msk                          (0x1UL << ATIM3MODE23_M23CR_CTEN_Pos)
#define ATIM3MODE23_M23CR_CTEN                              ATIM3MODE23_M23CR_CTEN_Msk
#define ATIM3MODE23_M23CR_COMP_Pos                          (1U)
#define ATIM3MODE23_M23CR_COMP_Msk                          (0x1UL << ATIM3MODE23_M23CR_COMP_Pos)
#define ATIM3MODE23_M23CR_COMP                              ATIM3MODE23_M23CR_COMP_Msk
#define ATIM3MODE23_M23CR_CT_Pos                            (2U)
#define ATIM3MODE23_M23CR_CT_Msk                            (0x1UL << ATIM3MODE23_M23CR_CT_Pos)
#define ATIM3MODE23_M23CR_CT                                ATIM3MODE23_M23CR_CT_Msk
#define ATIM3MODE23_M23CR_PWM2S_Pos                         (3U)
#define ATIM3MODE23_M23CR_PWM2S_Msk                         (0x1UL << ATIM3MODE23_M23CR_PWM2S_Pos)
#define ATIM3MODE23_M23CR_PWM2S                             ATIM3MODE23_M23CR_PWM2S_Msk
#define ATIM3MODE23_M23CR_PRS_Pos                           (4U)
#define ATIM3MODE23_M23CR_PRS_Msk                           (0x7UL << ATIM3MODE23_M23CR_PRS_Pos)
#define ATIM3MODE23_M23CR_PRS                               ATIM3MODE23_M23CR_PRS_Msk
#define ATIM3MODE23_M23CR_BUFPEN_Pos                        (7U)
#define ATIM3MODE23_M23CR_BUFPEN_Msk                        (0x1UL << ATIM3MODE23_M23CR_BUFPEN_Pos)
#define ATIM3MODE23_M23CR_BUFPEN                            ATIM3MODE23_M23CR_BUFPEN_Msk
#define ATIM3MODE23_M23CR_CRG_Pos                           (8U)
#define ATIM3MODE23_M23CR_CRG_Msk                           (0x1UL << ATIM3MODE23_M23CR_CRG_Pos)
#define ATIM3MODE23_M23CR_CRG                               ATIM3MODE23_M23CR_CRG_Msk
#define ATIM3MODE23_M23CR_CFG_Pos                           (9U)
#define ATIM3MODE23_M23CR_CFG_Msk                           (0x1UL << ATIM3MODE23_M23CR_CFG_Pos)
#define ATIM3MODE23_M23CR_CFG                               ATIM3MODE23_M23CR_CFG_Msk
#define ATIM3MODE23_M23CR_UIE_Pos                           (10U)
#define ATIM3MODE23_M23CR_UIE_Msk                           (0x1UL << ATIM3MODE23_M23CR_UIE_Pos)
#define ATIM3MODE23_M23CR_UIE                               ATIM3MODE23_M23CR_UIE_Msk
#define ATIM3MODE23_M23CR_UDE_Pos                           (11U)
#define ATIM3MODE23_M23CR_UDE_Msk                           (0x1UL << ATIM3MODE23_M23CR_UDE_Pos)
#define ATIM3MODE23_M23CR_UDE                               ATIM3MODE23_M23CR_UDE_Msk
#define ATIM3MODE23_M23CR_MODE_Pos                          (12U)
#define ATIM3MODE23_M23CR_MODE_Msk                          (0x3UL << ATIM3MODE23_M23CR_MODE_Pos)
#define ATIM3MODE23_M23CR_MODE                              ATIM3MODE23_M23CR_MODE_Msk
#define ATIM3MODE23_M23CR_ONESHOT_Pos                       (14U)
#define ATIM3MODE23_M23CR_ONESHOT_Msk                       (0x1UL << ATIM3MODE23_M23CR_ONESHOT_Pos)
#define ATIM3MODE23_M23CR_ONESHOT                           ATIM3MODE23_M23CR_ONESHOT_Msk
#define ATIM3MODE23_M23CR_CSG_Pos                           (15U)
#define ATIM3MODE23_M23CR_CSG_Msk                           (0x1UL << ATIM3MODE23_M23CR_CSG_Pos)
#define ATIM3MODE23_M23CR_CSG                               ATIM3MODE23_M23CR_CSG_Msk
#define ATIM3MODE23_M23CR_OCCS_Pos                          (16U)
#define ATIM3MODE23_M23CR_OCCS_Msk                          (0x1UL << ATIM3MODE23_M23CR_OCCS_Pos)
#define ATIM3MODE23_M23CR_OCCS                              ATIM3MODE23_M23CR_OCCS_Msk
#define ATIM3MODE23_M23CR_URS_Pos                           (17U)
#define ATIM3MODE23_M23CR_URS_Msk                           (0x1UL << ATIM3MODE23_M23CR_URS_Pos)
#define ATIM3MODE23_M23CR_URS                               ATIM3MODE23_M23CR_URS_Msk
#define ATIM3MODE23_M23CR_TDE_Pos                           (18U)
#define ATIM3MODE23_M23CR_TDE_Msk                           (0x1UL << ATIM3MODE23_M23CR_TDE_Pos)
#define ATIM3MODE23_M23CR_TDE                               ATIM3MODE23_M23CR_TDE_Msk
#define ATIM3MODE23_M23CR_TIE_Pos                           (19U)
#define ATIM3MODE23_M23CR_TIE_Msk                           (0x1UL << ATIM3MODE23_M23CR_TIE_Pos)
#define ATIM3MODE23_M23CR_TIE                               ATIM3MODE23_M23CR_TIE_Msk
#define ATIM3MODE23_M23CR_BIE_Pos                           (20U)
#define ATIM3MODE23_M23CR_BIE_Msk                           (0x1UL << ATIM3MODE23_M23CR_BIE_Pos)
#define ATIM3MODE23_M23CR_BIE                               ATIM3MODE23_M23CR_BIE_Msk
#define ATIM3MODE23_M23CR_CIS_Pos                           (21U)
#define ATIM3MODE23_M23CR_CIS_Msk                           (0x3UL << ATIM3MODE23_M23CR_CIS_Pos)
#define ATIM3MODE23_M23CR_CIS                               ATIM3MODE23_M23CR_CIS_Msk
#define ATIM3MODE23_M23CR_OCCE_Pos                          (23U)
#define ATIM3MODE23_M23CR_OCCE_Msk                          (0x1UL << ATIM3MODE23_M23CR_OCCE_Pos)
#define ATIM3MODE23_M23CR_OCCE                              ATIM3MODE23_M23CR_OCCE_Msk
#define ATIM3MODE23_M23CR_TG_Pos                            (24U)
#define ATIM3MODE23_M23CR_TG_Msk                            (0x1UL << ATIM3MODE23_M23CR_TG_Pos)
#define ATIM3MODE23_M23CR_TG                                ATIM3MODE23_M23CR_TG_Msk
#define ATIM3MODE23_M23CR_UG_Pos                            (25U)
#define ATIM3MODE23_M23CR_UG_Msk                            (0x1UL << ATIM3MODE23_M23CR_UG_Pos)
#define ATIM3MODE23_M23CR_UG                                ATIM3MODE23_M23CR_UG_Msk
#define ATIM3MODE23_M23CR_BG_Pos                            (26U)
#define ATIM3MODE23_M23CR_BG_Msk                            (0x1UL << ATIM3MODE23_M23CR_BG_Pos)
#define ATIM3MODE23_M23CR_BG                                ATIM3MODE23_M23CR_BG_Msk
#define ATIM3MODE23_M23CR_DIR_Pos                           (27U)
#define ATIM3MODE23_M23CR_DIR_Msk                           (0x1UL << ATIM3MODE23_M23CR_DIR_Pos)
#define ATIM3MODE23_M23CR_DIR                               ATIM3MODE23_M23CR_DIR_Msk
#define ATIM3MODE23_M23CR_OVE_Pos                           (28U)
#define ATIM3MODE23_M23CR_OVE_Msk                           (0x1UL << ATIM3MODE23_M23CR_OVE_Pos)
#define ATIM3MODE23_M23CR_OVE                               ATIM3MODE23_M23CR_OVE_Msk
#define ATIM3MODE23_M23CR_UNDE_Pos                          (29U)
#define ATIM3MODE23_M23CR_UNDE_Msk                          (0x1UL << ATIM3MODE23_M23CR_UNDE_Pos)
#define ATIM3MODE23_M23CR_UNDE                              ATIM3MODE23_M23CR_UNDE_Msk

// ATIM3MODE23_IFR
#define ATIM3MODE23_IFR_UI_Pos                              (0U)
#define ATIM3MODE23_IFR_UI_Msk                              (0x1UL << ATIM3MODE23_IFR_UI_Pos)
#define ATIM3MODE23_IFR_UI                                  ATIM3MODE23_IFR_UI_Msk
#define ATIM3MODE23_IFR_CA0_Pos                             (2U)
#define ATIM3MODE23_IFR_CA0_Msk                             (0x1UL << ATIM3MODE23_IFR_CA0_Pos)
#define ATIM3MODE23_IFR_CA0                                 ATIM3MODE23_IFR_CA0_Msk
#define ATIM3MODE23_IFR_CA1_Pos                             (3U)
#define ATIM3MODE23_IFR_CA1_Msk                             (0x1UL << ATIM3MODE23_IFR_CA1_Pos)
#define ATIM3MODE23_IFR_CA1                                 ATIM3MODE23_IFR_CA1_Msk
#define ATIM3MODE23_IFR_CA2_Pos                             (4U)
#define ATIM3MODE23_IFR_CA2_Msk                             (0x1UL << ATIM3MODE23_IFR_CA2_Pos)
#define ATIM3MODE23_IFR_CA2                                 ATIM3MODE23_IFR_CA2_Msk
#define ATIM3MODE23_IFR_CB0_Pos                             (5U)
#define ATIM3MODE23_IFR_CB0_Msk                             (0x1UL << ATIM3MODE23_IFR_CB0_Pos)
#define ATIM3MODE23_IFR_CB0                                 ATIM3MODE23_IFR_CB0_Msk
#define ATIM3MODE23_IFR_CB1_Pos                             (6U)
#define ATIM3MODE23_IFR_CB1_Msk                             (0x1UL << ATIM3MODE23_IFR_CB1_Pos)
#define ATIM3MODE23_IFR_CB1                                 ATIM3MODE23_IFR_CB1_Msk
#define ATIM3MODE23_IFR_CB2_Pos                             (7U)
#define ATIM3MODE23_IFR_CB2_Msk                             (0x1UL << ATIM3MODE23_IFR_CB2_Pos)
#define ATIM3MODE23_IFR_CB2                                 ATIM3MODE23_IFR_CB2_Msk
#define ATIM3MODE23_IFR_CA0E_Pos                            (8U)
#define ATIM3MODE23_IFR_CA0E_Msk                            (0x1UL << ATIM3MODE23_IFR_CA0E_Pos)
#define ATIM3MODE23_IFR_CA0E                                ATIM3MODE23_IFR_CA0E_Msk
#define ATIM3MODE23_IFR_CA1E_Pos                            (9U)
#define ATIM3MODE23_IFR_CA1E_Msk                            (0x1UL << ATIM3MODE23_IFR_CA1E_Pos)
#define ATIM3MODE23_IFR_CA1E                                ATIM3MODE23_IFR_CA1E_Msk
#define ATIM3MODE23_IFR_CA2E_Pos                            (10U)
#define ATIM3MODE23_IFR_CA2E_Msk                            (0x1UL << ATIM3MODE23_IFR_CA2E_Pos)
#define ATIM3MODE23_IFR_CA2E                                ATIM3MODE23_IFR_CA2E_Msk
#define ATIM3MODE23_IFR_CB0E_Pos                            (11U)
#define ATIM3MODE23_IFR_CB0E_Msk                            (0x1UL << ATIM3MODE23_IFR_CB0E_Pos)
#define ATIM3MODE23_IFR_CB0E                                ATIM3MODE23_IFR_CB0E_Msk
#define ATIM3MODE23_IFR_CB1E_Pos                            (12U)
#define ATIM3MODE23_IFR_CB1E_Msk                            (0x1UL << ATIM3MODE23_IFR_CB1E_Pos)
#define ATIM3MODE23_IFR_CB1E                                ATIM3MODE23_IFR_CB1E_Msk
#define ATIM3MODE23_IFR_CB2E_Pos                            (13U)
#define ATIM3MODE23_IFR_CB2E_Msk                            (0x1UL << ATIM3MODE23_IFR_CB2E_Pos)
#define ATIM3MODE23_IFR_CB2E                                ATIM3MODE23_IFR_CB2E_Msk
#define ATIM3MODE23_IFR_BI_Pos                              (14U)
#define ATIM3MODE23_IFR_BI_Msk                              (0x1UL << ATIM3MODE23_IFR_BI_Pos)
#define ATIM3MODE23_IFR_BI                                  ATIM3MODE23_IFR_BI_Msk
#define ATIM3MODE23_IFR_TI_Pos                              (15U)
#define ATIM3MODE23_IFR_TI_Msk                              (0x1UL << ATIM3MODE23_IFR_TI_Pos)
#define ATIM3MODE23_IFR_TI                                  ATIM3MODE23_IFR_TI_Msk
#define ATIM3MODE23_IFR_OV_Pos                              (16U)
#define ATIM3MODE23_IFR_OV_Msk                              (0x1UL << ATIM3MODE23_IFR_OV_Pos)
#define ATIM3MODE23_IFR_OV                                  ATIM3MODE23_IFR_OV_Msk
#define ATIM3MODE23_IFR_UND_Pos                             (17U)
#define ATIM3MODE23_IFR_UND_Msk                             (0x1UL << ATIM3MODE23_IFR_UND_Pos)
#define ATIM3MODE23_IFR_UND                                 ATIM3MODE23_IFR_UND_Msk
#define ATIM3MODE23_IFR_CA3A_Pos                            (18U)
#define ATIM3MODE23_IFR_CA3A_Msk                            (0x1UL << ATIM3MODE23_IFR_CA3A_Pos)
#define ATIM3MODE23_IFR_CA3A                                ATIM3MODE23_IFR_CA3A_Msk
#define ATIM3MODE23_IFR_CA3B_Pos                            (19U)
#define ATIM3MODE23_IFR_CA3B_Msk                            (0x1UL << ATIM3MODE23_IFR_CA3B_Pos)
#define ATIM3MODE23_IFR_CA3B                                ATIM3MODE23_IFR_CA3B_Msk

// ATIM3MODE23_ICLR
#define ATIM3MODE23_ICLR_UI_Pos                             (0U)
#define ATIM3MODE23_ICLR_UI_Msk                             (0x1UL << ATIM3MODE23_ICLR_UI_Pos)
#define ATIM3MODE23_ICLR_UI                                 ATIM3MODE23_ICLR_UI_Msk
#define ATIM3MODE23_ICLR_CA0_Pos                            (2U)
#define ATIM3MODE23_ICLR_CA0_Msk                            (0x1UL << ATIM3MODE23_ICLR_CA0_Pos)
#define ATIM3MODE23_ICLR_CA0                                ATIM3MODE23_ICLR_CA0_Msk
#define ATIM3MODE23_ICLR_CA1_Pos                            (3U)
#define ATIM3MODE23_ICLR_CA1_Msk                            (0x1UL << ATIM3MODE23_ICLR_CA1_Pos)
#define ATIM3MODE23_ICLR_CA1                                ATIM3MODE23_ICLR_CA1_Msk
#define ATIM3MODE23_ICLR_CA2_Pos                            (4U)
#define ATIM3MODE23_ICLR_CA2_Msk                            (0x1UL << ATIM3MODE23_ICLR_CA2_Pos)
#define ATIM3MODE23_ICLR_CA2                                ATIM3MODE23_ICLR_CA2_Msk
#define ATIM3MODE23_ICLR_CB0_Pos                            (5U)
#define ATIM3MODE23_ICLR_CB0_Msk                            (0x1UL << ATIM3MODE23_ICLR_CB0_Pos)
#define ATIM3MODE23_ICLR_CB0                                ATIM3MODE23_ICLR_CB0_Msk
#define ATIM3MODE23_ICLR_CB1_Pos                            (6U)
#define ATIM3MODE23_ICLR_CB1_Msk                            (0x1UL << ATIM3MODE23_ICLR_CB1_Pos)
#define ATIM3MODE23_ICLR_CB1                                ATIM3MODE23_ICLR_CB1_Msk
#define ATIM3MODE23_ICLR_CB2_Pos                            (7U)
#define ATIM3MODE23_ICLR_CB2_Msk                            (0x1UL << ATIM3MODE23_ICLR_CB2_Pos)
#define ATIM3MODE23_ICLR_CB2                                ATIM3MODE23_ICLR_CB2_Msk
#define ATIM3MODE23_ICLR_CA0E_Pos                           (8U)
#define ATIM3MODE23_ICLR_CA0E_Msk                           (0x1UL << ATIM3MODE23_ICLR_CA0E_Pos)
#define ATIM3MODE23_ICLR_CA0E                               ATIM3MODE23_ICLR_CA0E_Msk
#define ATIM3MODE23_ICLR_CA1E_Pos                           (9U)
#define ATIM3MODE23_ICLR_CA1E_Msk                           (0x1UL << ATIM3MODE23_ICLR_CA1E_Pos)
#define ATIM3MODE23_ICLR_CA1E                               ATIM3MODE23_ICLR_CA1E_Msk
#define ATIM3MODE23_ICLR_CA2E_Pos                           (10U)
#define ATIM3MODE23_ICLR_CA2E_Msk                           (0x1UL << ATIM3MODE23_ICLR_CA2E_Pos)
#define ATIM3MODE23_ICLR_CA2E                               ATIM3MODE23_ICLR_CA2E_Msk
#define ATIM3MODE23_ICLR_CB0E_Pos                           (11U)
#define ATIM3MODE23_ICLR_CB0E_Msk                           (0x1UL << ATIM3MODE23_ICLR_CB0E_Pos)
#define ATIM3MODE23_ICLR_CB0E                               ATIM3MODE23_ICLR_CB0E_Msk
#define ATIM3MODE23_ICLR_CB1E_Pos                           (12U)
#define ATIM3MODE23_ICLR_CB1E_Msk                           (0x1UL << ATIM3MODE23_ICLR_CB1E_Pos)
#define ATIM3MODE23_ICLR_CB1E                               ATIM3MODE23_ICLR_CB1E_Msk
#define ATIM3MODE23_ICLR_CB2E_Pos                           (13U)
#define ATIM3MODE23_ICLR_CB2E_Msk                           (0x1UL << ATIM3MODE23_ICLR_CB2E_Pos)
#define ATIM3MODE23_ICLR_CB2E                               ATIM3MODE23_ICLR_CB2E_Msk
#define ATIM3MODE23_ICLR_BI_Pos                             (14U)
#define ATIM3MODE23_ICLR_BI_Msk                             (0x1UL << ATIM3MODE23_ICLR_BI_Pos)
#define ATIM3MODE23_ICLR_BI                                 ATIM3MODE23_ICLR_BI_Msk
#define ATIM3MODE23_ICLR_TI_Pos                             (15U)
#define ATIM3MODE23_ICLR_TI_Msk                             (0x1UL << ATIM3MODE23_ICLR_TI_Pos)
#define ATIM3MODE23_ICLR_TI                                 ATIM3MODE23_ICLR_TI_Msk
#define ATIM3MODE23_ICLR_OV_Pos                             (16U)
#define ATIM3MODE23_ICLR_OV_Msk                             (0x1UL << ATIM3MODE23_ICLR_OV_Pos)
#define ATIM3MODE23_ICLR_OV                                 ATIM3MODE23_ICLR_OV_Msk
#define ATIM3MODE23_ICLR_UND_Pos                            (17U)
#define ATIM3MODE23_ICLR_UND_Msk                            (0x1UL << ATIM3MODE23_ICLR_UND_Pos)
#define ATIM3MODE23_ICLR_UND                                ATIM3MODE23_ICLR_UND_Msk
#define ATIM3MODE23_ICLR_CA3A_Pos                           (18U)
#define ATIM3MODE23_ICLR_CA3A_Msk                           (0x1UL << ATIM3MODE23_ICLR_CA3A_Pos)
#define ATIM3MODE23_ICLR_CA3A                               ATIM3MODE23_ICLR_CA3A_Msk
#define ATIM3MODE23_ICLR_CA3B_Pos                           (19U)
#define ATIM3MODE23_ICLR_CA3B_Msk                           (0x1UL << ATIM3MODE23_ICLR_CA3B_Pos)
#define ATIM3MODE23_ICLR_CA3B                               ATIM3MODE23_ICLR_CA3B_Msk

// ATIM3MODE23_MSCR
#define ATIM3MODE23_MSCR_MMS_Pos                            (0U)
#define ATIM3MODE23_MSCR_MMS_Msk                            (0x7UL << ATIM3MODE23_MSCR_MMS_Pos)
#define ATIM3MODE23_MSCR_MMS                                ATIM3MODE23_MSCR_MMS_Msk
#define ATIM3MODE23_MSCR_CCDS_Pos                           (3U)
#define ATIM3MODE23_MSCR_CCDS_Msk                           (0x1UL << ATIM3MODE23_MSCR_CCDS_Pos)
#define ATIM3MODE23_MSCR_CCDS                               ATIM3MODE23_MSCR_CCDS_Msk
#define ATIM3MODE23_MSCR_MSM_Pos                            (4U)
#define ATIM3MODE23_MSCR_MSM_Msk                            (0x1UL << ATIM3MODE23_MSCR_MSM_Pos)
#define ATIM3MODE23_MSCR_MSM                                ATIM3MODE23_MSCR_MSM_Msk
#define ATIM3MODE23_MSCR_TS_Pos                             (5U)
#define ATIM3MODE23_MSCR_TS_Msk                             (0x7UL << ATIM3MODE23_MSCR_TS_Pos)
#define ATIM3MODE23_MSCR_TS                                 ATIM3MODE23_MSCR_TS_Msk
#define ATIM3MODE23_MSCR_SMS_Pos                            (8U)
#define ATIM3MODE23_MSCR_SMS_Msk                            (0x7UL << ATIM3MODE23_MSCR_SMS_Pos)
#define ATIM3MODE23_MSCR_SMS                                ATIM3MODE23_MSCR_SMS_Msk
#define ATIM3MODE23_MSCR_IA0S_Pos                           (11U)
#define ATIM3MODE23_MSCR_IA0S_Msk                           (0x1UL << ATIM3MODE23_MSCR_IA0S_Pos)
#define ATIM3MODE23_MSCR_IA0S                               ATIM3MODE23_MSCR_IA0S_Msk
#define ATIM3MODE23_MSCR_IB0S_Pos                           (12U)
#define ATIM3MODE23_MSCR_IB0S_Msk                           (0x1UL << ATIM3MODE23_MSCR_IB0S_Pos)
#define ATIM3MODE23_MSCR_IB0S                               ATIM3MODE23_MSCR_IB0S_Msk

// ATIM3MODE23_FLTR
#define ATIM3MODE23_FLTR_OCMA0FLTA0_Pos                     (0U)
#define ATIM3MODE23_FLTR_OCMA0FLTA0_Msk                     (0x7UL << ATIM3MODE23_FLTR_OCMA0FLTA0_Pos)
#define ATIM3MODE23_FLTR_OCMA0FLTA0                         ATIM3MODE23_FLTR_OCMA0FLTA0_Msk
#define ATIM3MODE23_FLTR_CCPA0_Pos                          (3U)
#define ATIM3MODE23_FLTR_CCPA0_Msk                          (0x1UL << ATIM3MODE23_FLTR_CCPA0_Pos)
#define ATIM3MODE23_FLTR_CCPA0                              ATIM3MODE23_FLTR_CCPA0_Msk
#define ATIM3MODE23_FLTR_OCMB0FLTB0_Pos                     (4U)
#define ATIM3MODE23_FLTR_OCMB0FLTB0_Msk                     (0x7UL << ATIM3MODE23_FLTR_OCMB0FLTB0_Pos)
#define ATIM3MODE23_FLTR_OCMB0FLTB0                         ATIM3MODE23_FLTR_OCMB0FLTB0_Msk
#define ATIM3MODE23_FLTR_CCPB0_Pos                          (7U)
#define ATIM3MODE23_FLTR_CCPB0_Msk                          (0x1UL << ATIM3MODE23_FLTR_CCPB0_Pos)
#define ATIM3MODE23_FLTR_CCPB0                              ATIM3MODE23_FLTR_CCPB0_Msk
#define ATIM3MODE23_FLTR_OCMA1FLTA1_Pos                     (8U)
#define ATIM3MODE23_FLTR_OCMA1FLTA1_Msk                     (0x7UL << ATIM3MODE23_FLTR_OCMA1FLTA1_Pos)
#define ATIM3MODE23_FLTR_OCMA1FLTA1                         ATIM3MODE23_FLTR_OCMA1FLTA1_Msk
#define ATIM3MODE23_FLTR_CCPA1_Pos                          (11U)
#define ATIM3MODE23_FLTR_CCPA1_Msk                          (0x1UL << ATIM3MODE23_FLTR_CCPA1_Pos)
#define ATIM3MODE23_FLTR_CCPA1                              ATIM3MODE23_FLTR_CCPA1_Msk
#define ATIM3MODE23_FLTR_OCMB1FLTB1_Pos                     (12U)
#define ATIM3MODE23_FLTR_OCMB1FLTB1_Msk                     (0x7UL << ATIM3MODE23_FLTR_OCMB1FLTB1_Pos)
#define ATIM3MODE23_FLTR_OCMB1FLTB1                         ATIM3MODE23_FLTR_OCMB1FLTB1_Msk
#define ATIM3MODE23_FLTR_CCPB1_Pos                          (15U)
#define ATIM3MODE23_FLTR_CCPB1_Msk                          (0x1UL << ATIM3MODE23_FLTR_CCPB1_Pos)
#define ATIM3MODE23_FLTR_CCPB1                              ATIM3MODE23_FLTR_CCPB1_Msk
#define ATIM3MODE23_FLTR_OCMA2FLTA2_Pos                     (16U)
#define ATIM3MODE23_FLTR_OCMA2FLTA2_Msk                     (0x7UL << ATIM3MODE23_FLTR_OCMA2FLTA2_Pos)
#define ATIM3MODE23_FLTR_OCMA2FLTA2                         ATIM3MODE23_FLTR_OCMA2FLTA2_Msk
#define ATIM3MODE23_FLTR_CCPA2_Pos                          (19U)
#define ATIM3MODE23_FLTR_CCPA2_Msk                          (0x1UL << ATIM3MODE23_FLTR_CCPA2_Pos)
#define ATIM3MODE23_FLTR_CCPA2                              ATIM3MODE23_FLTR_CCPA2_Msk
#define ATIM3MODE23_FLTR_OCMB2FLTB2_Pos                     (20U)
#define ATIM3MODE23_FLTR_OCMB2FLTB2_Msk                     (0x7UL << ATIM3MODE23_FLTR_OCMB2FLTB2_Pos)
#define ATIM3MODE23_FLTR_OCMB2FLTB2                         ATIM3MODE23_FLTR_OCMB2FLTB2_Msk
#define ATIM3MODE23_FLTR_CCPB2_Pos                          (23U)
#define ATIM3MODE23_FLTR_CCPB2_Msk                          (0x1UL << ATIM3MODE23_FLTR_CCPB2_Pos)
#define ATIM3MODE23_FLTR_CCPB2                              ATIM3MODE23_FLTR_CCPB2_Msk
#define ATIM3MODE23_FLTR_FLTBK_Pos                          (24U)
#define ATIM3MODE23_FLTR_FLTBK_Msk                          (0x7UL << ATIM3MODE23_FLTR_FLTBK_Pos)
#define ATIM3MODE23_FLTR_FLTBK                              ATIM3MODE23_FLTR_FLTBK_Msk
#define ATIM3MODE23_FLTR_BKP_Pos                            (27U)
#define ATIM3MODE23_FLTR_BKP_Msk                            (0x1UL << ATIM3MODE23_FLTR_BKP_Pos)
#define ATIM3MODE23_FLTR_BKP                                ATIM3MODE23_FLTR_BKP_Msk
#define ATIM3MODE23_FLTR_FLTET_Pos                          (28U)
#define ATIM3MODE23_FLTR_FLTET_Msk                          (0x7UL << ATIM3MODE23_FLTR_FLTET_Pos)
#define ATIM3MODE23_FLTR_FLTET                              ATIM3MODE23_FLTR_FLTET_Msk
#define ATIM3MODE23_FLTR_ETP_Pos                            (31U)
#define ATIM3MODE23_FLTR_ETP_Msk                            (0x1UL << ATIM3MODE23_FLTR_ETP_Pos)
#define ATIM3MODE23_FLTR_ETP                                ATIM3MODE23_FLTR_ETP_Msk

// ATIM3MODE23_ADTR
#define ATIM3MODE23_ADTR_UEVE_Pos                           (0U)
#define ATIM3MODE23_ADTR_UEVE_Msk                           (0x1UL << ATIM3MODE23_ADTR_UEVE_Pos)
#define ATIM3MODE23_ADTR_UEVE                               ATIM3MODE23_ADTR_UEVE_Msk
#define ATIM3MODE23_ADTR_CMA0E_Pos                          (1U)
#define ATIM3MODE23_ADTR_CMA0E_Msk                          (0x1UL << ATIM3MODE23_ADTR_CMA0E_Pos)
#define ATIM3MODE23_ADTR_CMA0E                              ATIM3MODE23_ADTR_CMA0E_Msk
#define ATIM3MODE23_ADTR_CMA1E_Pos                          (2U)
#define ATIM3MODE23_ADTR_CMA1E_Msk                          (0x1UL << ATIM3MODE23_ADTR_CMA1E_Pos)
#define ATIM3MODE23_ADTR_CMA1E                              ATIM3MODE23_ADTR_CMA1E_Msk
#define ATIM3MODE23_ADTR_CMA2E_Pos                          (3U)
#define ATIM3MODE23_ADTR_CMA2E_Msk                          (0x1UL << ATIM3MODE23_ADTR_CMA2E_Pos)
#define ATIM3MODE23_ADTR_CMA2E                              ATIM3MODE23_ADTR_CMA2E_Msk
#define ATIM3MODE23_ADTR_CMB0E_Pos                          (4U)
#define ATIM3MODE23_ADTR_CMB0E_Msk                          (0x1UL << ATIM3MODE23_ADTR_CMB0E_Pos)
#define ATIM3MODE23_ADTR_CMB0E                              ATIM3MODE23_ADTR_CMB0E_Msk
#define ATIM3MODE23_ADTR_CMB1E_Pos                          (5U)
#define ATIM3MODE23_ADTR_CMB1E_Msk                          (0x1UL << ATIM3MODE23_ADTR_CMB1E_Pos)
#define ATIM3MODE23_ADTR_CMB1E                              ATIM3MODE23_ADTR_CMB1E_Msk
#define ATIM3MODE23_ADTR_CMB2E_Pos                          (6U)
#define ATIM3MODE23_ADTR_CMB2E_Msk                          (0x1UL << ATIM3MODE23_ADTR_CMB2E_Pos)
#define ATIM3MODE23_ADTR_CMB2E                              ATIM3MODE23_ADTR_CMB2E_Msk
#define ATIM3MODE23_ADTR_ADTE_Pos                           (7U)
#define ATIM3MODE23_ADTR_ADTE_Msk                           (0x1UL << ATIM3MODE23_ADTR_ADTE_Pos)
#define ATIM3MODE23_ADTR_ADTE                               ATIM3MODE23_ADTR_ADTE_Msk

// ATIM3MODE23_CRCH0
#define ATIM3MODE23_CRCH0_CFACRABKSA_Pos                    (0U)
#define ATIM3MODE23_CRCH0_CFACRABKSA_Msk                    (0x3UL << ATIM3MODE23_CRCH0_CFACRABKSA_Pos)
#define ATIM3MODE23_CRCH0_CFACRABKSA                        ATIM3MODE23_CRCH0_CFACRABKSA_Msk
#define ATIM3MODE23_CRCH0_CFBCRBBKSB_Pos                    (2U)
#define ATIM3MODE23_CRCH0_CFBCRBBKSB_Msk                    (0x3UL << ATIM3MODE23_CRCH0_CFBCRBBKSB_Pos)
#define ATIM3MODE23_CRCH0_CFBCRBBKSB                        ATIM3MODE23_CRCH0_CFBCRBBKSB_Msk
#define ATIM3MODE23_CRCH0_CSA_Pos                           (4U)
#define ATIM3MODE23_CRCH0_CSA_Msk                           (0x1UL << ATIM3MODE23_CRCH0_CSA_Pos)
#define ATIM3MODE23_CRCH0_CSA                               ATIM3MODE23_CRCH0_CSA_Msk
#define ATIM3MODE23_CRCH0_CSB_Pos                           (5U)
#define ATIM3MODE23_CRCH0_CSB_Msk                           (0x1UL << ATIM3MODE23_CRCH0_CSB_Pos)
#define ATIM3MODE23_CRCH0_CSB                               ATIM3MODE23_CRCH0_CSB_Msk
#define ATIM3MODE23_CRCH0_BUFEA_Pos                         (6U)
#define ATIM3MODE23_CRCH0_BUFEA_Msk                         (0x1UL << ATIM3MODE23_CRCH0_BUFEA_Pos)
#define ATIM3MODE23_CRCH0_BUFEA                             ATIM3MODE23_CRCH0_BUFEA_Msk
#define ATIM3MODE23_CRCH0_BUFEB_Pos                         (7U)
#define ATIM3MODE23_CRCH0_BUFEB_Msk                         (0x1UL << ATIM3MODE23_CRCH0_BUFEB_Pos)
#define ATIM3MODE23_CRCH0_BUFEB                             ATIM3MODE23_CRCH0_BUFEB_Msk
#define ATIM3MODE23_CRCH0_CIEA_Pos                          (8U)
#define ATIM3MODE23_CRCH0_CIEA_Msk                          (0x1UL << ATIM3MODE23_CRCH0_CIEA_Pos)
#define ATIM3MODE23_CRCH0_CIEA                              ATIM3MODE23_CRCH0_CIEA_Msk
#define ATIM3MODE23_CRCH0_CIEB_Pos                          (9U)
#define ATIM3MODE23_CRCH0_CIEB_Msk                          (0x1UL << ATIM3MODE23_CRCH0_CIEB_Pos)
#define ATIM3MODE23_CRCH0_CIEB                              ATIM3MODE23_CRCH0_CIEB_Msk
#define ATIM3MODE23_CRCH0_CDEA_Pos                          (10U)
#define ATIM3MODE23_CRCH0_CDEA_Msk                          (0x1UL << ATIM3MODE23_CRCH0_CDEA_Pos)
#define ATIM3MODE23_CRCH0_CDEA                              ATIM3MODE23_CRCH0_CDEA_Msk
#define ATIM3MODE23_CRCH0_CDEB_Pos                          (11U)
#define ATIM3MODE23_CRCH0_CDEB_Msk                          (0x1UL << ATIM3MODE23_CRCH0_CDEB_Pos)
#define ATIM3MODE23_CRCH0_CDEB                              ATIM3MODE23_CRCH0_CDEB_Msk
#define ATIM3MODE23_CRCH0_CISB_Pos                          (12U)
#define ATIM3MODE23_CRCH0_CISB_Msk                          (0x3UL << ATIM3MODE23_CRCH0_CISB_Pos)
#define ATIM3MODE23_CRCH0_CISB                              ATIM3MODE23_CRCH0_CISB_Msk
#define ATIM3MODE23_CRCH0_CCGA_Pos                          (14U)
#define ATIM3MODE23_CRCH0_CCGA_Msk                          (0x1UL << ATIM3MODE23_CRCH0_CCGA_Pos)
#define ATIM3MODE23_CRCH0_CCGA                              ATIM3MODE23_CRCH0_CCGA_Msk
#define ATIM3MODE23_CRCH0_CCGB_Pos                          (15U)
#define ATIM3MODE23_CRCH0_CCGB_Msk                          (0x1UL << ATIM3MODE23_CRCH0_CCGB_Pos)
#define ATIM3MODE23_CRCH0_CCGB                              ATIM3MODE23_CRCH0_CCGB_Msk

// ATIM3MODE23_CRCH1
#define ATIM3MODE23_CRCH1_CFACRABKSA_Pos                    (0U)
#define ATIM3MODE23_CRCH1_CFACRABKSA_Msk                    (0x3UL << ATIM3MODE23_CRCH1_CFACRABKSA_Pos)
#define ATIM3MODE23_CRCH1_CFACRABKSA                        ATIM3MODE23_CRCH1_CFACRABKSA_Msk
#define ATIM3MODE23_CRCH1_CFBCRBBKSB_Pos                    (2U)
#define ATIM3MODE23_CRCH1_CFBCRBBKSB_Msk                    (0x3UL << ATIM3MODE23_CRCH1_CFBCRBBKSB_Pos)
#define ATIM3MODE23_CRCH1_CFBCRBBKSB                        ATIM3MODE23_CRCH1_CFBCRBBKSB_Msk
#define ATIM3MODE23_CRCH1_CSA_Pos                           (4U)
#define ATIM3MODE23_CRCH1_CSA_Msk                           (0x1UL << ATIM3MODE23_CRCH1_CSA_Pos)
#define ATIM3MODE23_CRCH1_CSA                               ATIM3MODE23_CRCH1_CSA_Msk
#define ATIM3MODE23_CRCH1_CSB_Pos                           (5U)
#define ATIM3MODE23_CRCH1_CSB_Msk                           (0x1UL << ATIM3MODE23_CRCH1_CSB_Pos)
#define ATIM3MODE23_CRCH1_CSB                               ATIM3MODE23_CRCH1_CSB_Msk
#define ATIM3MODE23_CRCH1_BUFEA_Pos                         (6U)
#define ATIM3MODE23_CRCH1_BUFEA_Msk                         (0x1UL << ATIM3MODE23_CRCH1_BUFEA_Pos)
#define ATIM3MODE23_CRCH1_BUFEA                             ATIM3MODE23_CRCH1_BUFEA_Msk
#define ATIM3MODE23_CRCH1_BUFEB_Pos                         (7U)
#define ATIM3MODE23_CRCH1_BUFEB_Msk                         (0x1UL << ATIM3MODE23_CRCH1_BUFEB_Pos)
#define ATIM3MODE23_CRCH1_BUFEB                             ATIM3MODE23_CRCH1_BUFEB_Msk
#define ATIM3MODE23_CRCH1_CIEA_Pos                          (8U)
#define ATIM3MODE23_CRCH1_CIEA_Msk                          (0x1UL << ATIM3MODE23_CRCH1_CIEA_Pos)
#define ATIM3MODE23_CRCH1_CIEA                              ATIM3MODE23_CRCH1_CIEA_Msk
#define ATIM3MODE23_CRCH1_CIEB_Pos                          (9U)
#define ATIM3MODE23_CRCH1_CIEB_Msk                          (0x1UL << ATIM3MODE23_CRCH1_CIEB_Pos)
#define ATIM3MODE23_CRCH1_CIEB                              ATIM3MODE23_CRCH1_CIEB_Msk
#define ATIM3MODE23_CRCH1_CDEA_Pos                          (10U)
#define ATIM3MODE23_CRCH1_CDEA_Msk                          (0x1UL << ATIM3MODE23_CRCH1_CDEA_Pos)
#define ATIM3MODE23_CRCH1_CDEA                              ATIM3MODE23_CRCH1_CDEA_Msk
#define ATIM3MODE23_CRCH1_CDEB_Pos                          (11U)
#define ATIM3MODE23_CRCH1_CDEB_Msk                          (0x1UL << ATIM3MODE23_CRCH1_CDEB_Pos)
#define ATIM3MODE23_CRCH1_CDEB                              ATIM3MODE23_CRCH1_CDEB_Msk
#define ATIM3MODE23_CRCH1_CISB_Pos                          (12U)
#define ATIM3MODE23_CRCH1_CISB_Msk                          (0x3UL << ATIM3MODE23_CRCH1_CISB_Pos)
#define ATIM3MODE23_CRCH1_CISB                              ATIM3MODE23_CRCH1_CISB_Msk
#define ATIM3MODE23_CRCH1_CCGA_Pos                          (14U)
#define ATIM3MODE23_CRCH1_CCGA_Msk                          (0x1UL << ATIM3MODE23_CRCH1_CCGA_Pos)
#define ATIM3MODE23_CRCH1_CCGA                              ATIM3MODE23_CRCH1_CCGA_Msk
#define ATIM3MODE23_CRCH1_CCGB_Pos                          (15U)
#define ATIM3MODE23_CRCH1_CCGB_Msk                          (0x1UL << ATIM3MODE23_CRCH1_CCGB_Pos)
#define ATIM3MODE23_CRCH1_CCGB                              ATIM3MODE23_CRCH1_CCGB_Msk

// ATIM3MODE23_CRCH2
#define ATIM3MODE23_CRCH2_CFACRABKSA_Pos                    (0U)
#define ATIM3MODE23_CRCH2_CFACRABKSA_Msk                    (0x3UL << ATIM3MODE23_CRCH2_CFACRABKSA_Pos)
#define ATIM3MODE23_CRCH2_CFACRABKSA                        ATIM3MODE23_CRCH2_CFACRABKSA_Msk
#define ATIM3MODE23_CRCH2_CFBCRBBKSB_Pos                    (2U)
#define ATIM3MODE23_CRCH2_CFBCRBBKSB_Msk                    (0x3UL << ATIM3MODE23_CRCH2_CFBCRBBKSB_Pos)
#define ATIM3MODE23_CRCH2_CFBCRBBKSB                        ATIM3MODE23_CRCH2_CFBCRBBKSB_Msk
#define ATIM3MODE23_CRCH2_CSA_Pos                           (4U)
#define ATIM3MODE23_CRCH2_CSA_Msk                           (0x1UL << ATIM3MODE23_CRCH2_CSA_Pos)
#define ATIM3MODE23_CRCH2_CSA                               ATIM3MODE23_CRCH2_CSA_Msk
#define ATIM3MODE23_CRCH2_CSB_Pos                           (5U)
#define ATIM3MODE23_CRCH2_CSB_Msk                           (0x1UL << ATIM3MODE23_CRCH2_CSB_Pos)
#define ATIM3MODE23_CRCH2_CSB                               ATIM3MODE23_CRCH2_CSB_Msk
#define ATIM3MODE23_CRCH2_BUFEA_Pos                         (6U)
#define ATIM3MODE23_CRCH2_BUFEA_Msk                         (0x1UL << ATIM3MODE23_CRCH2_BUFEA_Pos)
#define ATIM3MODE23_CRCH2_BUFEA                             ATIM3MODE23_CRCH2_BUFEA_Msk
#define ATIM3MODE23_CRCH2_BUFEB_Pos                         (7U)
#define ATIM3MODE23_CRCH2_BUFEB_Msk                         (0x1UL << ATIM3MODE23_CRCH2_BUFEB_Pos)
#define ATIM3MODE23_CRCH2_BUFEB                             ATIM3MODE23_CRCH2_BUFEB_Msk
#define ATIM3MODE23_CRCH2_CIEA_Pos                          (8U)
#define ATIM3MODE23_CRCH2_CIEA_Msk                          (0x1UL << ATIM3MODE23_CRCH2_CIEA_Pos)
#define ATIM3MODE23_CRCH2_CIEA                              ATIM3MODE23_CRCH2_CIEA_Msk
#define ATIM3MODE23_CRCH2_CIEB_Pos                          (9U)
#define ATIM3MODE23_CRCH2_CIEB_Msk                          (0x1UL << ATIM3MODE23_CRCH2_CIEB_Pos)
#define ATIM3MODE23_CRCH2_CIEB                              ATIM3MODE23_CRCH2_CIEB_Msk
#define ATIM3MODE23_CRCH2_CDEA_Pos                          (10U)
#define ATIM3MODE23_CRCH2_CDEA_Msk                          (0x1UL << ATIM3MODE23_CRCH2_CDEA_Pos)
#define ATIM3MODE23_CRCH2_CDEA                              ATIM3MODE23_CRCH2_CDEA_Msk
#define ATIM3MODE23_CRCH2_CDEB_Pos                          (11U)
#define ATIM3MODE23_CRCH2_CDEB_Msk                          (0x1UL << ATIM3MODE23_CRCH2_CDEB_Pos)
#define ATIM3MODE23_CRCH2_CDEB                              ATIM3MODE23_CRCH2_CDEB_Msk
#define ATIM3MODE23_CRCH2_CISB_Pos                          (12U)
#define ATIM3MODE23_CRCH2_CISB_Msk                          (0x3UL << ATIM3MODE23_CRCH2_CISB_Pos)
#define ATIM3MODE23_CRCH2_CISB                              ATIM3MODE23_CRCH2_CISB_Msk
#define ATIM3MODE23_CRCH2_CCGA_Pos                          (14U)
#define ATIM3MODE23_CRCH2_CCGA_Msk                          (0x1UL << ATIM3MODE23_CRCH2_CCGA_Pos)
#define ATIM3MODE23_CRCH2_CCGA                              ATIM3MODE23_CRCH2_CCGA_Msk
#define ATIM3MODE23_CRCH2_CCGB_Pos                          (15U)
#define ATIM3MODE23_CRCH2_CCGB_Msk                          (0x1UL << ATIM3MODE23_CRCH2_CCGB_Pos)
#define ATIM3MODE23_CRCH2_CCGB                              ATIM3MODE23_CRCH2_CCGB_Msk

// ATIM3MODE23_DTR
#define ATIM3MODE23_DTR_DTR_Pos                             (0U)
#define ATIM3MODE23_DTR_DTR_Msk                             (0xFFUL << ATIM3MODE23_DTR_DTR_Pos)
#define ATIM3MODE23_DTR_DTR                                 ATIM3MODE23_DTR_DTR_Msk
#define ATIM3MODE23_DTR_BKSEL_Pos                           (8U)
#define ATIM3MODE23_DTR_BKSEL_Msk                           (0x1UL << ATIM3MODE23_DTR_BKSEL_Pos)
#define ATIM3MODE23_DTR_BKSEL                               ATIM3MODE23_DTR_BKSEL_Msk
#define ATIM3MODE23_DTR_DTEN_Pos                            (9U)
#define ATIM3MODE23_DTR_DTEN_Msk                            (0x1UL << ATIM3MODE23_DTR_DTEN_Pos)
#define ATIM3MODE23_DTR_DTEN                                ATIM3MODE23_DTR_DTEN_Msk
#define ATIM3MODE23_DTR_BKE_Pos                             (10U)
#define ATIM3MODE23_DTR_BKE_Msk                             (0x1UL << ATIM3MODE23_DTR_BKE_Pos)
#define ATIM3MODE23_DTR_BKE                                 ATIM3MODE23_DTR_BKE_Msk
#define ATIM3MODE23_DTR_AOE_Pos                             (11U)
#define ATIM3MODE23_DTR_AOE_Msk                             (0x1UL << ATIM3MODE23_DTR_AOE_Pos)
#define ATIM3MODE23_DTR_AOE                                 ATIM3MODE23_DTR_AOE_Msk
#define ATIM3MODE23_DTR_MOE_Pos                             (12U)
#define ATIM3MODE23_DTR_MOE_Msk                             (0x1UL << ATIM3MODE23_DTR_MOE_Pos)
#define ATIM3MODE23_DTR_MOE                                 ATIM3MODE23_DTR_MOE_Msk
#define ATIM3MODE23_DTR_SAFEEN_Pos                          (13U)
#define ATIM3MODE23_DTR_SAFEEN_Msk                          (0x1UL << ATIM3MODE23_DTR_SAFEEN_Pos)
#define ATIM3MODE23_DTR_SAFEEN                              ATIM3MODE23_DTR_SAFEEN_Msk
#define ATIM3MODE23_DTR_VCE_Pos                             (14U)
#define ATIM3MODE23_DTR_VCE_Msk                             (0x1UL << ATIM3MODE23_DTR_VCE_Pos)
#define ATIM3MODE23_DTR_VCE                                 ATIM3MODE23_DTR_VCE_Msk

// ATIM3MODE23_RCR
#define ATIM3MODE23_RCR_RCR_Pos                             (0U)
#define ATIM3MODE23_RCR_RCR_Msk                             (0xFFUL << ATIM3MODE23_RCR_RCR_Pos)
#define ATIM3MODE23_RCR_RCR                                 ATIM3MODE23_RCR_RCR_Msk
#define ATIM3MODE23_RCR_OV_Pos                              (8U)
#define ATIM3MODE23_RCR_OV_Msk                              (0x1UL << ATIM3MODE23_RCR_OV_Pos)
#define ATIM3MODE23_RCR_OV                                  ATIM3MODE23_RCR_OV_Msk
#define ATIM3MODE23_RCR_UD_Pos                              (9U)
#define ATIM3MODE23_RCR_UD_Msk                              (0x1UL << ATIM3MODE23_RCR_UD_Pos)
#define ATIM3MODE23_RCR_UD                                  ATIM3MODE23_RCR_UD_Msk

// ATIM3MODE23_CCR0A
#define ATIM3MODE23_CCR0A_CCR0A_Pos                         (0U)
#define ATIM3MODE23_CCR0A_CCR0A_Msk                         (0xFFFFUL << ATIM3MODE23_CCR0A_CCR0A_Pos)
#define ATIM3MODE23_CCR0A_CCR0A                             ATIM3MODE23_CCR0A_CCR0A_Msk

// ATIM3MODE23_CCR0B
#define ATIM3MODE23_CCR0B_CCR0B_Pos                         (0U)
#define ATIM3MODE23_CCR0B_CCR0B_Msk                         (0xFFFFUL << ATIM3MODE23_CCR0B_CCR0B_Pos)
#define ATIM3MODE23_CCR0B_CCR0B                             ATIM3MODE23_CCR0B_CCR0B_Msk

// ATIM3MODE23_CCR1A
#define ATIM3MODE23_CCR1A_CCR1A_Pos                         (0U)
#define ATIM3MODE23_CCR1A_CCR1A_Msk                         (0xFFFFUL << ATIM3MODE23_CCR1A_CCR1A_Pos)
#define ATIM3MODE23_CCR1A_CCR1A                             ATIM3MODE23_CCR1A_CCR1A_Msk

// ATIM3MODE23_CCR1B
#define ATIM3MODE23_CCR1B_CCR1B_Pos                         (0U)
#define ATIM3MODE23_CCR1B_CCR1B_Msk                         (0xFFFFUL << ATIM3MODE23_CCR1B_CCR1B_Pos)
#define ATIM3MODE23_CCR1B_CCR1B                             ATIM3MODE23_CCR1B_CCR1B_Msk

// ATIM3MODE23_CCR2A
#define ATIM3MODE23_CCR2A_CCR2A_Pos                         (0U)
#define ATIM3MODE23_CCR2A_CCR2A_Msk                         (0xFFFFUL << ATIM3MODE23_CCR2A_CCR2A_Pos)
#define ATIM3MODE23_CCR2A_CCR2A                             ATIM3MODE23_CCR2A_CCR2A_Msk

// ATIM3MODE23_CCR2B
#define ATIM3MODE23_CCR2B_CCR2B_Pos                         (0U)
#define ATIM3MODE23_CCR2B_CCR2B_Msk                         (0xFFFFUL << ATIM3MODE23_CCR2B_CCR2B_Pos)
#define ATIM3MODE23_CCR2B_CCR2B                             ATIM3MODE23_CCR2B_CCR2B_Msk

// ATIM3MODE23_CCR3A
#define ATIM3MODE23_CCR3A_CCR3A_Pos                         (0U)
#define ATIM3MODE23_CCR3A_CCR3A_Msk                         (0xFFFFUL << ATIM3MODE23_CCR3A_CCR3A_Pos)
#define ATIM3MODE23_CCR3A_CCR3A                             ATIM3MODE23_CCR3A_CCR3A_Msk

// ATIM3MODE23_CRCH3A
#define ATIM3MODE23_CRCH3A_BUF_Pos                          (0U)
#define ATIM3MODE23_CRCH3A_BUF_Msk                          (0x1UL << ATIM3MODE23_CRCH3A_BUF_Pos)
#define ATIM3MODE23_CRCH3A_BUF                              ATIM3MODE23_CRCH3A_BUF_Msk
#define ATIM3MODE23_CRCH3A_CI_Pos                           (1U)
#define ATIM3MODE23_CRCH3A_CI_Msk                           (0x1UL << ATIM3MODE23_CRCH3A_CI_Pos)
#define ATIM3MODE23_CRCH3A_CI                               ATIM3MODE23_CRCH3A_CI_Msk
#define ATIM3MODE23_CRCH3A_CD_Pos                           (2U)
#define ATIM3MODE23_CRCH3A_CD_Msk                           (0x1UL << ATIM3MODE23_CRCH3A_CD_Pos)
#define ATIM3MODE23_CRCH3A_CD                               ATIM3MODE23_CRCH3A_CD_Msk
#define ATIM3MODE23_CRCH3A_CIS_Pos                          (3U)
#define ATIM3MODE23_CRCH3A_CIS_Msk                          (0x3UL << ATIM3MODE23_CRCH3A_CIS_Pos)
#define ATIM3MODE23_CRCH3A_CIS                              ATIM3MODE23_CRCH3A_CIS_Msk
#define ATIM3MODE23_CRCH3A_C3AEN_Pos                        (5U)
#define ATIM3MODE23_CRCH3A_C3AEN_Msk                        (0x1UL << ATIM3MODE23_CRCH3A_C3AEN_Pos)
#define ATIM3MODE23_CRCH3A_C3AEN                            ATIM3MODE23_CRCH3A_C3AEN_Msk

// ATIM3MODE23_CCR3B
#define ATIM3MODE23_CCR3B_CCR3B_Pos                         (0U)
#define ATIM3MODE23_CCR3B_CCR3B_Msk                         (0xFFFFUL << ATIM3MODE23_CCR3B_CCR3B_Pos)
#define ATIM3MODE23_CCR3B_CCR3B                             ATIM3MODE23_CCR3B_CCR3B_Msk

// ATIM3MODE23_CRCH3B
#define ATIM3MODE23_CRCH3B_BUF_Pos                          (0U)
#define ATIM3MODE23_CRCH3B_BUF_Msk                          (0x1UL << ATIM3MODE23_CRCH3B_BUF_Pos)
#define ATIM3MODE23_CRCH3B_BUF                              ATIM3MODE23_CRCH3B_BUF_Msk
#define ATIM3MODE23_CRCH3B_CI_Pos                           (1U)
#define ATIM3MODE23_CRCH3B_CI_Msk                           (0x1UL << ATIM3MODE23_CRCH3B_CI_Pos)
#define ATIM3MODE23_CRCH3B_CI                               ATIM3MODE23_CRCH3B_CI_Msk
#define ATIM3MODE23_CRCH3B_CD_Pos                           (2U)
#define ATIM3MODE23_CRCH3B_CD_Msk                           (0x1UL << ATIM3MODE23_CRCH3B_CD_Pos)
#define ATIM3MODE23_CRCH3B_CD                               ATIM3MODE23_CRCH3B_CD_Msk
#define ATIM3MODE23_CRCH3B_CIS_Pos                          (3U)
#define ATIM3MODE23_CRCH3B_CIS_Msk                          (0x3UL << ATIM3MODE23_CRCH3B_CIS_Pos)
#define ATIM3MODE23_CRCH3B_CIS                              ATIM3MODE23_CRCH3B_CIS_Msk
#define ATIM3MODE23_CRCH3B_C3BEN_Pos                        (5U)
#define ATIM3MODE23_CRCH3B_C3BEN_Msk                        (0x1UL << ATIM3MODE23_CRCH3B_C3BEN_Pos)
#define ATIM3MODE23_CRCH3B_C3BEN                            ATIM3MODE23_CRCH3B_C3BEN_Msk



//********************    Bits Define For Peripheral ATIMMODE0    ********************//
// ATIMMODE0_ARR
#define ATIMMODE0_ARR_ARR_Pos                               (0U)
#define ATIMMODE0_ARR_ARR_Msk                               (0xFFFFUL << ATIMMODE0_ARR_ARR_Pos)
#define ATIMMODE0_ARR_ARR                                   ATIMMODE0_ARR_ARR_Msk

// ATIMMODE0_CNT
#define ATIMMODE0_CNT_CNT_Pos                               (0U)
#define ATIMMODE0_CNT_CNT_Msk                               (0xFFFFUL << ATIMMODE0_CNT_CNT_Pos)
#define ATIMMODE0_CNT_CNT                                   ATIMMODE0_CNT_CNT_Msk

// ATIMMODE0_CNT32
#define ATIMMODE0_CNT32_CNT32_Pos                           (0U)
#define ATIMMODE0_CNT32_CNT32_Msk                           (0xFFFFFFFFUL << ATIMMODE0_CNT32_CNT32_Pos)
#define ATIMMODE0_CNT32_CNT32                               ATIMMODE0_CNT32_CNT32_Msk

// ATIMMODE0_M0CR
#define ATIMMODE0_M0CR_CTEN_Pos                             (0U)
#define ATIMMODE0_M0CR_CTEN_Msk                             (0x1UL << ATIMMODE0_M0CR_CTEN_Pos)
#define ATIMMODE0_M0CR_CTEN                                 ATIMMODE0_M0CR_CTEN_Msk
#define ATIMMODE0_M0CR_MD_Pos                               (1U)
#define ATIMMODE0_M0CR_MD_Msk                               (0x1UL << ATIMMODE0_M0CR_MD_Pos)
#define ATIMMODE0_M0CR_MD                                   ATIMMODE0_M0CR_MD_Msk
#define ATIMMODE0_M0CR_CT_Pos                               (2U)
#define ATIMMODE0_M0CR_CT_Msk                               (0x1UL << ATIMMODE0_M0CR_CT_Pos)
#define ATIMMODE0_M0CR_CT                                   ATIMMODE0_M0CR_CT_Msk
#define ATIMMODE0_M0CR_TOGEN_Pos                            (3U)
#define ATIMMODE0_M0CR_TOGEN_Msk                            (0x1UL << ATIMMODE0_M0CR_TOGEN_Pos)
#define ATIMMODE0_M0CR_TOGEN                                ATIMMODE0_M0CR_TOGEN_Msk
#define ATIMMODE0_M0CR_PRS_Pos                              (4U)
#define ATIMMODE0_M0CR_PRS_Msk                              (0x7UL << ATIMMODE0_M0CR_PRS_Pos)
#define ATIMMODE0_M0CR_PRS                                  ATIMMODE0_M0CR_PRS_Msk
#define ATIMMODE0_M0CR_GATE_Pos                             (8U)
#define ATIMMODE0_M0CR_GATE_Msk                             (0x1UL << ATIMMODE0_M0CR_GATE_Pos)
#define ATIMMODE0_M0CR_GATE                                 ATIMMODE0_M0CR_GATE_Msk
#define ATIMMODE0_M0CR_GATEP_Pos                            (9U)
#define ATIMMODE0_M0CR_GATEP_Msk                            (0x1UL << ATIMMODE0_M0CR_GATEP_Pos)
#define ATIMMODE0_M0CR_GATEP                                ATIMMODE0_M0CR_GATEP_Msk
#define ATIMMODE0_M0CR_UIE_Pos                              (10U)
#define ATIMMODE0_M0CR_UIE_Msk                              (0x1UL << ATIMMODE0_M0CR_UIE_Pos)
#define ATIMMODE0_M0CR_UIE                                  ATIMMODE0_M0CR_UIE_Msk
#define ATIMMODE0_M0CR_MODE_Pos                             (12U)
#define ATIMMODE0_M0CR_MODE_Msk                             (0x3UL << ATIMMODE0_M0CR_MODE_Pos)
#define ATIMMODE0_M0CR_MODE                                 ATIMMODE0_M0CR_MODE_Msk

// ATIMMODE0_IFR
#define ATIMMODE0_IFR_UI_Pos                                (0U)
#define ATIMMODE0_IFR_UI_Msk                                (0x1UL << ATIMMODE0_IFR_UI_Pos)
#define ATIMMODE0_IFR_UI                                    ATIMMODE0_IFR_UI_Msk

// ATIMMODE0_ICLR
#define ATIMMODE0_ICLR_UI_Pos                               (0U)
#define ATIMMODE0_ICLR_UI_Msk                               (0x1UL << ATIMMODE0_ICLR_UI_Pos)
#define ATIMMODE0_ICLR_UI                                   ATIMMODE0_ICLR_UI_Msk

// ATIMMODE0_DTR
#define ATIMMODE0_DTR_MOE_Pos                               (12U)
#define ATIMMODE0_DTR_MOE_Msk                               (0x1UL << ATIMMODE0_DTR_MOE_Pos)
#define ATIMMODE0_DTR_MOE                                   ATIMMODE0_DTR_MOE_Msk



//********************    Bits Define For Peripheral ATIMMODE1    ********************//
// ATIMMODE1_CNT
#define ATIMMODE1_CNT_CNT_Pos                               (0U)
#define ATIMMODE1_CNT_CNT_Msk                               (0xFFFFUL << ATIMMODE1_CNT_CNT_Pos)
#define ATIMMODE1_CNT_CNT                                   ATIMMODE1_CNT_CNT_Msk

// ATIMMODE1_M1CR
#define ATIMMODE1_M1CR_CTEN_Pos                             (0U)
#define ATIMMODE1_M1CR_CTEN_Msk                             (0x1UL << ATIMMODE1_M1CR_CTEN_Pos)
#define ATIMMODE1_M1CR_CTEN                                 ATIMMODE1_M1CR_CTEN_Msk
#define ATIMMODE1_M1CR_CT_Pos                               (2U)
#define ATIMMODE1_M1CR_CT_Msk                               (0x1UL << ATIMMODE1_M1CR_CT_Pos)
#define ATIMMODE1_M1CR_CT                                   ATIMMODE1_M1CR_CT_Msk
#define ATIMMODE1_M1CR_PRS_Pos                              (4U)
#define ATIMMODE1_M1CR_PRS_Msk                              (0x7UL << ATIMMODE1_M1CR_PRS_Pos)
#define ATIMMODE1_M1CR_PRS                                  ATIMMODE1_M1CR_PRS_Msk
#define ATIMMODE1_M1CR_EDG1ST_Pos                           (8U)
#define ATIMMODE1_M1CR_EDG1ST_Msk                           (0x1UL << ATIMMODE1_M1CR_EDG1ST_Pos)
#define ATIMMODE1_M1CR_EDG1ST                               ATIMMODE1_M1CR_EDG1ST_Msk
#define ATIMMODE1_M1CR_EDG2ND_Pos                           (9U)
#define ATIMMODE1_M1CR_EDG2ND_Msk                           (0x1UL << ATIMMODE1_M1CR_EDG2ND_Pos)
#define ATIMMODE1_M1CR_EDG2ND                               ATIMMODE1_M1CR_EDG2ND_Msk
#define ATIMMODE1_M1CR_UIE_Pos                              (10U)
#define ATIMMODE1_M1CR_UIE_Msk                              (0x1UL << ATIMMODE1_M1CR_UIE_Pos)
#define ATIMMODE1_M1CR_UIE                                  ATIMMODE1_M1CR_UIE_Msk
#define ATIMMODE1_M1CR_MODE_Pos                             (12U)
#define ATIMMODE1_M1CR_MODE_Msk                             (0x3UL << ATIMMODE1_M1CR_MODE_Pos)
#define ATIMMODE1_M1CR_MODE                                 ATIMMODE1_M1CR_MODE_Msk
#define ATIMMODE1_M1CR_ONESHOT_Pos                          (14U)
#define ATIMMODE1_M1CR_ONESHOT_Msk                          (0x1UL << ATIMMODE1_M1CR_ONESHOT_Pos)
#define ATIMMODE1_M1CR_ONESHOT                              ATIMMODE1_M1CR_ONESHOT_Msk

// ATIMMODE1_IFR
#define ATIMMODE1_IFR_UI_Pos                                (0U)
#define ATIMMODE1_IFR_UI_Msk                                (0x1UL << ATIMMODE1_IFR_UI_Pos)
#define ATIMMODE1_IFR_UI                                    ATIMMODE1_IFR_UI_Msk
#define ATIMMODE1_IFR_PWC_Pos                               (2U)
#define ATIMMODE1_IFR_PWC_Msk                               (0x1UL << ATIMMODE1_IFR_PWC_Pos)
#define ATIMMODE1_IFR_PWC                                   ATIMMODE1_IFR_PWC_Msk

// ATIMMODE1_ICLR
#define ATIMMODE1_ICLR_UI_Pos                               (0U)
#define ATIMMODE1_ICLR_UI_Msk                               (0x1UL << ATIMMODE1_ICLR_UI_Pos)
#define ATIMMODE1_ICLR_UI                                   ATIMMODE1_ICLR_UI_Msk
#define ATIMMODE1_ICLR_PWC_Pos                              (2U)
#define ATIMMODE1_ICLR_PWC_Msk                              (0x1UL << ATIMMODE1_ICLR_PWC_Pos)
#define ATIMMODE1_ICLR_PWC                                  ATIMMODE1_ICLR_PWC_Msk

// ATIMMODE1_MSCR
#define ATIMMODE1_MSCR_TS_Pos                               (5U)
#define ATIMMODE1_MSCR_TS_Msk                               (0x7UL << ATIMMODE1_MSCR_TS_Pos)
#define ATIMMODE1_MSCR_TS                                   ATIMMODE1_MSCR_TS_Msk
#define ATIMMODE1_MSCR_IA0S_Pos                             (11U)
#define ATIMMODE1_MSCR_IA0S_Msk                             (0x1UL << ATIMMODE1_MSCR_IA0S_Pos)
#define ATIMMODE1_MSCR_IA0S                                 ATIMMODE1_MSCR_IA0S_Msk
#define ATIMMODE1_MSCR_IB0S_Pos                             (12U)
#define ATIMMODE1_MSCR_IB0S_Msk                             (0x1UL << ATIMMODE1_MSCR_IB0S_Pos)
#define ATIMMODE1_MSCR_IB0S                                 ATIMMODE1_MSCR_IB0S_Msk

// ATIMMODE1_FLTR
#define ATIMMODE1_FLTR_FLTA0_Pos                            (0U)
#define ATIMMODE1_FLTR_FLTA0_Msk                            (0x7UL << ATIMMODE1_FLTR_FLTA0_Pos)
#define ATIMMODE1_FLTR_FLTA0                                ATIMMODE1_FLTR_FLTA0_Msk
#define ATIMMODE1_FLTR_FLTB0_Pos                            (4U)
#define ATIMMODE1_FLTR_FLTB0_Msk                            (0x7UL << ATIMMODE1_FLTR_FLTB0_Pos)
#define ATIMMODE1_FLTR_FLTB0                                ATIMMODE1_FLTR_FLTB0_Msk
#define ATIMMODE1_FLTR_FLTET_Pos                            (28U)
#define ATIMMODE1_FLTR_FLTET_Msk                            (0x7UL << ATIMMODE1_FLTR_FLTET_Pos)
#define ATIMMODE1_FLTR_FLTET                                ATIMMODE1_FLTR_FLTET_Msk
#define ATIMMODE1_FLTR_ETP_Pos                              (31U)
#define ATIMMODE1_FLTR_ETP_Msk                              (0x1UL << ATIMMODE1_FLTR_ETP_Pos)
#define ATIMMODE1_FLTR_ETP                                  ATIMMODE1_FLTR_ETP_Msk

// ATIMMODE1_CR0
#define ATIMMODE1_CR0_CSA_Pos                               (4U)
#define ATIMMODE1_CR0_CSA_Msk                               (0x1UL << ATIMMODE1_CR0_CSA_Pos)
#define ATIMMODE1_CR0_CSA                                   ATIMMODE1_CR0_CSA_Msk
#define ATIMMODE1_CR0_CSB_Pos                               (5U)
#define ATIMMODE1_CR0_CSB_Msk                               (0x1UL << ATIMMODE1_CR0_CSB_Pos)
#define ATIMMODE1_CR0_CSB                                   ATIMMODE1_CR0_CSB_Msk
#define ATIMMODE1_CR0_CIEA_Pos                              (8U)
#define ATIMMODE1_CR0_CIEA_Msk                              (0x1UL << ATIMMODE1_CR0_CIEA_Pos)
#define ATIMMODE1_CR0_CIEA                                  ATIMMODE1_CR0_CIEA_Msk

// ATIMMODE1_CCR0A
#define ATIMMODE1_CCR0A_CCR0A_Pos                           (0U)
#define ATIMMODE1_CCR0A_CCR0A_Msk                           (0xFFFFUL << ATIMMODE1_CCR0A_CCR0A_Pos)
#define ATIMMODE1_CCR0A_CCR0A                               ATIMMODE1_CCR0A_CCR0A_Msk



//********************    Bits Define For Peripheral ATIMMODE23    ********************//
// ATIMMODE23_ARR
#define ATIMMODE23_ARR_ARR_Pos                              (0U)
#define ATIMMODE23_ARR_ARR_Msk                              (0xFFFFUL << ATIMMODE23_ARR_ARR_Pos)
#define ATIMMODE23_ARR_ARR                                  ATIMMODE23_ARR_ARR_Msk

// ATIMMODE23_CNT
#define ATIMMODE23_CNT_CNT_Pos                              (0U)
#define ATIMMODE23_CNT_CNT_Msk                              (0xFFFFUL << ATIMMODE23_CNT_CNT_Pos)
#define ATIMMODE23_CNT_CNT                                  ATIMMODE23_CNT_CNT_Msk

// ATIMMODE23_M23CR
#define ATIMMODE23_M23CR_CTEN_Pos                           (0U)
#define ATIMMODE23_M23CR_CTEN_Msk                           (0x1UL << ATIMMODE23_M23CR_CTEN_Pos)
#define ATIMMODE23_M23CR_CTEN                               ATIMMODE23_M23CR_CTEN_Msk
#define ATIMMODE23_M23CR_COMP_Pos                           (1U)
#define ATIMMODE23_M23CR_COMP_Msk                           (0x1UL << ATIMMODE23_M23CR_COMP_Pos)
#define ATIMMODE23_M23CR_COMP                               ATIMMODE23_M23CR_COMP_Msk
#define ATIMMODE23_M23CR_CT_Pos                             (2U)
#define ATIMMODE23_M23CR_CT_Msk                             (0x1UL << ATIMMODE23_M23CR_CT_Pos)
#define ATIMMODE23_M23CR_CT                                 ATIMMODE23_M23CR_CT_Msk
#define ATIMMODE23_M23CR_PWM2S_Pos                          (3U)
#define ATIMMODE23_M23CR_PWM2S_Msk                          (0x1UL << ATIMMODE23_M23CR_PWM2S_Pos)
#define ATIMMODE23_M23CR_PWM2S                              ATIMMODE23_M23CR_PWM2S_Msk
#define ATIMMODE23_M23CR_PRS_Pos                            (4U)
#define ATIMMODE23_M23CR_PRS_Msk                            (0x7UL << ATIMMODE23_M23CR_PRS_Pos)
#define ATIMMODE23_M23CR_PRS                                ATIMMODE23_M23CR_PRS_Msk
#define ATIMMODE23_M23CR_BUFPEN_Pos                         (7U)
#define ATIMMODE23_M23CR_BUFPEN_Msk                         (0x1UL << ATIMMODE23_M23CR_BUFPEN_Pos)
#define ATIMMODE23_M23CR_BUFPEN                             ATIMMODE23_M23CR_BUFPEN_Msk
#define ATIMMODE23_M23CR_CRG_Pos                            (8U)
#define ATIMMODE23_M23CR_CRG_Msk                            (0x1UL << ATIMMODE23_M23CR_CRG_Pos)
#define ATIMMODE23_M23CR_CRG                                ATIMMODE23_M23CR_CRG_Msk
#define ATIMMODE23_M23CR_CFG_Pos                            (9U)
#define ATIMMODE23_M23CR_CFG_Msk                            (0x1UL << ATIMMODE23_M23CR_CFG_Pos)
#define ATIMMODE23_M23CR_CFG                                ATIMMODE23_M23CR_CFG_Msk
#define ATIMMODE23_M23CR_UIE_Pos                            (10U)
#define ATIMMODE23_M23CR_UIE_Msk                            (0x1UL << ATIMMODE23_M23CR_UIE_Pos)
#define ATIMMODE23_M23CR_UIE                                ATIMMODE23_M23CR_UIE_Msk
#define ATIMMODE23_M23CR_UDE_Pos                            (11U)
#define ATIMMODE23_M23CR_UDE_Msk                            (0x1UL << ATIMMODE23_M23CR_UDE_Pos)
#define ATIMMODE23_M23CR_UDE                                ATIMMODE23_M23CR_UDE_Msk
#define ATIMMODE23_M23CR_MODE_Pos                           (12U)
#define ATIMMODE23_M23CR_MODE_Msk                           (0x3UL << ATIMMODE23_M23CR_MODE_Pos)
#define ATIMMODE23_M23CR_MODE                               ATIMMODE23_M23CR_MODE_Msk
#define ATIMMODE23_M23CR_ONESHOT_Pos                        (14U)
#define ATIMMODE23_M23CR_ONESHOT_Msk                        (0x1UL << ATIMMODE23_M23CR_ONESHOT_Pos)
#define ATIMMODE23_M23CR_ONESHOT                            ATIMMODE23_M23CR_ONESHOT_Msk
#define ATIMMODE23_M23CR_CSG_Pos                            (15U)
#define ATIMMODE23_M23CR_CSG_Msk                            (0x1UL << ATIMMODE23_M23CR_CSG_Pos)
#define ATIMMODE23_M23CR_CSG                                ATIMMODE23_M23CR_CSG_Msk
#define ATIMMODE23_M23CR_OCCS_Pos                           (16U)
#define ATIMMODE23_M23CR_OCCS_Msk                           (0x1UL << ATIMMODE23_M23CR_OCCS_Pos)
#define ATIMMODE23_M23CR_OCCS                               ATIMMODE23_M23CR_OCCS_Msk
#define ATIMMODE23_M23CR_URS_Pos                            (17U)
#define ATIMMODE23_M23CR_URS_Msk                            (0x1UL << ATIMMODE23_M23CR_URS_Pos)
#define ATIMMODE23_M23CR_URS                                ATIMMODE23_M23CR_URS_Msk
#define ATIMMODE23_M23CR_TDE_Pos                            (18U)
#define ATIMMODE23_M23CR_TDE_Msk                            (0x1UL << ATIMMODE23_M23CR_TDE_Pos)
#define ATIMMODE23_M23CR_TDE                                ATIMMODE23_M23CR_TDE_Msk
#define ATIMMODE23_M23CR_TIE_Pos                            (19U)
#define ATIMMODE23_M23CR_TIE_Msk                            (0x1UL << ATIMMODE23_M23CR_TIE_Pos)
#define ATIMMODE23_M23CR_TIE                                ATIMMODE23_M23CR_TIE_Msk
#define ATIMMODE23_M23CR_BIE_Pos                            (20U)
#define ATIMMODE23_M23CR_BIE_Msk                            (0x1UL << ATIMMODE23_M23CR_BIE_Pos)
#define ATIMMODE23_M23CR_BIE                                ATIMMODE23_M23CR_BIE_Msk
#define ATIMMODE23_M23CR_CIS_Pos                            (21U)
#define ATIMMODE23_M23CR_CIS_Msk                            (0x3UL << ATIMMODE23_M23CR_CIS_Pos)
#define ATIMMODE23_M23CR_CIS                                ATIMMODE23_M23CR_CIS_Msk
#define ATIMMODE23_M23CR_OCCE_Pos                           (23U)
#define ATIMMODE23_M23CR_OCCE_Msk                           (0x1UL << ATIMMODE23_M23CR_OCCE_Pos)
#define ATIMMODE23_M23CR_OCCE                               ATIMMODE23_M23CR_OCCE_Msk
#define ATIMMODE23_M23CR_TG_Pos                             (24U)
#define ATIMMODE23_M23CR_TG_Msk                             (0x1UL << ATIMMODE23_M23CR_TG_Pos)
#define ATIMMODE23_M23CR_TG                                 ATIMMODE23_M23CR_TG_Msk
#define ATIMMODE23_M23CR_UG_Pos                             (25U)
#define ATIMMODE23_M23CR_UG_Msk                             (0x1UL << ATIMMODE23_M23CR_UG_Pos)
#define ATIMMODE23_M23CR_UG                                 ATIMMODE23_M23CR_UG_Msk
#define ATIMMODE23_M23CR_BG_Pos                             (26U)
#define ATIMMODE23_M23CR_BG_Msk                             (0x1UL << ATIMMODE23_M23CR_BG_Pos)
#define ATIMMODE23_M23CR_BG                                 ATIMMODE23_M23CR_BG_Msk
#define ATIMMODE23_M23CR_DIR_Pos                            (27U)
#define ATIMMODE23_M23CR_DIR_Msk                            (0x1UL << ATIMMODE23_M23CR_DIR_Pos)
#define ATIMMODE23_M23CR_DIR                                ATIMMODE23_M23CR_DIR_Msk
#define ATIMMODE23_M23CR_OVE_Pos                            (28U)
#define ATIMMODE23_M23CR_OVE_Msk                            (0x1UL << ATIMMODE23_M23CR_OVE_Pos)
#define ATIMMODE23_M23CR_OVE                                ATIMMODE23_M23CR_OVE_Msk
#define ATIMMODE23_M23CR_UNDE_Pos                           (29U)
#define ATIMMODE23_M23CR_UNDE_Msk                           (0x1UL << ATIMMODE23_M23CR_UNDE_Pos)
#define ATIMMODE23_M23CR_UNDE                               ATIMMODE23_M23CR_UNDE_Msk

// ATIMMODE23_IFR
#define ATIMMODE23_IFR_UI_Pos                               (0U)
#define ATIMMODE23_IFR_UI_Msk                               (0x1UL << ATIMMODE23_IFR_UI_Pos)
#define ATIMMODE23_IFR_UI                                   ATIMMODE23_IFR_UI_Msk
#define ATIMMODE23_IFR_CA0_Pos                              (2U)
#define ATIMMODE23_IFR_CA0_Msk                              (0x1UL << ATIMMODE23_IFR_CA0_Pos)
#define ATIMMODE23_IFR_CA0                                  ATIMMODE23_IFR_CA0_Msk
#define ATIMMODE23_IFR_CB0_Pos                              (5U)
#define ATIMMODE23_IFR_CB0_Msk                              (0x1UL << ATIMMODE23_IFR_CB0_Pos)
#define ATIMMODE23_IFR_CB0                                  ATIMMODE23_IFR_CB0_Msk
#define ATIMMODE23_IFR_CA0E_Pos                             (8U)
#define ATIMMODE23_IFR_CA0E_Msk                             (0x1UL << ATIMMODE23_IFR_CA0E_Pos)
#define ATIMMODE23_IFR_CA0E                                 ATIMMODE23_IFR_CA0E_Msk
#define ATIMMODE23_IFR_CB0E_Pos                             (11U)
#define ATIMMODE23_IFR_CB0E_Msk                             (0x1UL << ATIMMODE23_IFR_CB0E_Pos)
#define ATIMMODE23_IFR_CB0E                                 ATIMMODE23_IFR_CB0E_Msk
#define ATIMMODE23_IFR_BI_Pos                               (14U)
#define ATIMMODE23_IFR_BI_Msk                               (0x1UL << ATIMMODE23_IFR_BI_Pos)
#define ATIMMODE23_IFR_BI                                   ATIMMODE23_IFR_BI_Msk
#define ATIMMODE23_IFR_TI_Pos                               (15U)
#define ATIMMODE23_IFR_TI_Msk                               (0x1UL << ATIMMODE23_IFR_TI_Pos)
#define ATIMMODE23_IFR_TI                                   ATIMMODE23_IFR_TI_Msk
#define ATIMMODE23_IFR_OV_Pos                               (16U)
#define ATIMMODE23_IFR_OV_Msk                               (0x1UL << ATIMMODE23_IFR_OV_Pos)
#define ATIMMODE23_IFR_OV                                   ATIMMODE23_IFR_OV_Msk
#define ATIMMODE23_IFR_UND_Pos                              (17U)
#define ATIMMODE23_IFR_UND_Msk                              (0x1UL << ATIMMODE23_IFR_UND_Pos)
#define ATIMMODE23_IFR_UND                                  ATIMMODE23_IFR_UND_Msk

// ATIMMODE23_ICLR
#define ATIMMODE23_ICLR_UI_Pos                              (0U)
#define ATIMMODE23_ICLR_UI_Msk                              (0x1UL << ATIMMODE23_ICLR_UI_Pos)
#define ATIMMODE23_ICLR_UI                                  ATIMMODE23_ICLR_UI_Msk
#define ATIMMODE23_ICLR_CA0_Pos                             (2U)
#define ATIMMODE23_ICLR_CA0_Msk                             (0x1UL << ATIMMODE23_ICLR_CA0_Pos)
#define ATIMMODE23_ICLR_CA0                                 ATIMMODE23_ICLR_CA0_Msk
#define ATIMMODE23_ICLR_CB0_Pos                             (5U)
#define ATIMMODE23_ICLR_CB0_Msk                             (0x1UL << ATIMMODE23_ICLR_CB0_Pos)
#define ATIMMODE23_ICLR_CB0                                 ATIMMODE23_ICLR_CB0_Msk
#define ATIMMODE23_ICLR_CA0E_Pos                            (8U)
#define ATIMMODE23_ICLR_CA0E_Msk                            (0x1UL << ATIMMODE23_ICLR_CA0E_Pos)
#define ATIMMODE23_ICLR_CA0E                                ATIMMODE23_ICLR_CA0E_Msk
#define ATIMMODE23_ICLR_CB0E_Pos                            (11U)
#define ATIMMODE23_ICLR_CB0E_Msk                            (0x1UL << ATIMMODE23_ICLR_CB0E_Pos)
#define ATIMMODE23_ICLR_CB0E                                ATIMMODE23_ICLR_CB0E_Msk
#define ATIMMODE23_ICLR_BI_Pos                              (14U)
#define ATIMMODE23_ICLR_BI_Msk                              (0x1UL << ATIMMODE23_ICLR_BI_Pos)
#define ATIMMODE23_ICLR_BI                                  ATIMMODE23_ICLR_BI_Msk
#define ATIMMODE23_ICLR_TI_Pos                              (15U)
#define ATIMMODE23_ICLR_TI_Msk                              (0x1UL << ATIMMODE23_ICLR_TI_Pos)
#define ATIMMODE23_ICLR_TI                                  ATIMMODE23_ICLR_TI_Msk
#define ATIMMODE23_ICLR_OV_Pos                              (16U)
#define ATIMMODE23_ICLR_OV_Msk                              (0x1UL << ATIMMODE23_ICLR_OV_Pos)
#define ATIMMODE23_ICLR_OV                                  ATIMMODE23_ICLR_OV_Msk
#define ATIMMODE23_ICLR_UND_Pos                             (17U)
#define ATIMMODE23_ICLR_UND_Msk                             (0x1UL << ATIMMODE23_ICLR_UND_Pos)
#define ATIMMODE23_ICLR_UND                                 ATIMMODE23_ICLR_UND_Msk

// ATIMMODE23_MSCR
#define ATIMMODE23_MSCR_MMS_Pos                             (0U)
#define ATIMMODE23_MSCR_MMS_Msk                             (0x7UL << ATIMMODE23_MSCR_MMS_Pos)
#define ATIMMODE23_MSCR_MMS                                 ATIMMODE23_MSCR_MMS_Msk
#define ATIMMODE23_MSCR_CCDS_Pos                            (3U)
#define ATIMMODE23_MSCR_CCDS_Msk                            (0x1UL << ATIMMODE23_MSCR_CCDS_Pos)
#define ATIMMODE23_MSCR_CCDS                                ATIMMODE23_MSCR_CCDS_Msk
#define ATIMMODE23_MSCR_MSM_Pos                             (4U)
#define ATIMMODE23_MSCR_MSM_Msk                             (0x1UL << ATIMMODE23_MSCR_MSM_Pos)
#define ATIMMODE23_MSCR_MSM                                 ATIMMODE23_MSCR_MSM_Msk
#define ATIMMODE23_MSCR_TS_Pos                              (5U)
#define ATIMMODE23_MSCR_TS_Msk                              (0x7UL << ATIMMODE23_MSCR_TS_Pos)
#define ATIMMODE23_MSCR_TS                                  ATIMMODE23_MSCR_TS_Msk
#define ATIMMODE23_MSCR_SMS_Pos                             (8U)
#define ATIMMODE23_MSCR_SMS_Msk                             (0x7UL << ATIMMODE23_MSCR_SMS_Pos)
#define ATIMMODE23_MSCR_SMS                                 ATIMMODE23_MSCR_SMS_Msk
#define ATIMMODE23_MSCR_IA0S_Pos                            (11U)
#define ATIMMODE23_MSCR_IA0S_Msk                            (0x1UL << ATIMMODE23_MSCR_IA0S_Pos)
#define ATIMMODE23_MSCR_IA0S                                ATIMMODE23_MSCR_IA0S_Msk
#define ATIMMODE23_MSCR_IB0S_Pos                            (12U)
#define ATIMMODE23_MSCR_IB0S_Msk                            (0x1UL << ATIMMODE23_MSCR_IB0S_Pos)
#define ATIMMODE23_MSCR_IB0S                                ATIMMODE23_MSCR_IB0S_Msk

// ATIMMODE23_FLTR
#define ATIMMODE23_FLTR_OCMA0FLTA0_Pos                      (0U)
#define ATIMMODE23_FLTR_OCMA0FLTA0_Msk                      (0x7UL << ATIMMODE23_FLTR_OCMA0FLTA0_Pos)
#define ATIMMODE23_FLTR_OCMA0FLTA0                          ATIMMODE23_FLTR_OCMA0FLTA0_Msk
#define ATIMMODE23_FLTR_CCPA0_Pos                           (3U)
#define ATIMMODE23_FLTR_CCPA0_Msk                           (0x1UL << ATIMMODE23_FLTR_CCPA0_Pos)
#define ATIMMODE23_FLTR_CCPA0                               ATIMMODE23_FLTR_CCPA0_Msk
#define ATIMMODE23_FLTR_OCMB0FLTB0_Pos                      (4U)
#define ATIMMODE23_FLTR_OCMB0FLTB0_Msk                      (0x7UL << ATIMMODE23_FLTR_OCMB0FLTB0_Pos)
#define ATIMMODE23_FLTR_OCMB0FLTB0                          ATIMMODE23_FLTR_OCMB0FLTB0_Msk
#define ATIMMODE23_FLTR_CCPB0_Pos                           (7U)
#define ATIMMODE23_FLTR_CCPB0_Msk                           (0x1UL << ATIMMODE23_FLTR_CCPB0_Pos)
#define ATIMMODE23_FLTR_CCPB0                               ATIMMODE23_FLTR_CCPB0_Msk
#define ATIMMODE23_FLTR_FLTBK_Pos                           (24U)
#define ATIMMODE23_FLTR_FLTBK_Msk                           (0x7UL << ATIMMODE23_FLTR_FLTBK_Pos)
#define ATIMMODE23_FLTR_FLTBK                               ATIMMODE23_FLTR_FLTBK_Msk
#define ATIMMODE23_FLTR_BKP_Pos                             (27U)
#define ATIMMODE23_FLTR_BKP_Msk                             (0x1UL << ATIMMODE23_FLTR_BKP_Pos)
#define ATIMMODE23_FLTR_BKP                                 ATIMMODE23_FLTR_BKP_Msk
#define ATIMMODE23_FLTR_FLTET_Pos                           (28U)
#define ATIMMODE23_FLTR_FLTET_Msk                           (0x7UL << ATIMMODE23_FLTR_FLTET_Pos)
#define ATIMMODE23_FLTR_FLTET                               ATIMMODE23_FLTR_FLTET_Msk
#define ATIMMODE23_FLTR_ETP_Pos                             (31U)
#define ATIMMODE23_FLTR_ETP_Msk                             (0x1UL << ATIMMODE23_FLTR_ETP_Pos)
#define ATIMMODE23_FLTR_ETP                                 ATIMMODE23_FLTR_ETP_Msk

// ATIMMODE23_ADTR
#define ATIMMODE23_ADTR_UEVE_Pos                            (0U)
#define ATIMMODE23_ADTR_UEVE_Msk                            (0x1UL << ATIMMODE23_ADTR_UEVE_Pos)
#define ATIMMODE23_ADTR_UEVE                                ATIMMODE23_ADTR_UEVE_Msk
#define ATIMMODE23_ADTR_CMA0E_Pos                           (1U)
#define ATIMMODE23_ADTR_CMA0E_Msk                           (0x1UL << ATIMMODE23_ADTR_CMA0E_Pos)
#define ATIMMODE23_ADTR_CMA0E                               ATIMMODE23_ADTR_CMA0E_Msk
#define ATIMMODE23_ADTR_CMB0E_Pos                           (4U)
#define ATIMMODE23_ADTR_CMB0E_Msk                           (0x1UL << ATIMMODE23_ADTR_CMB0E_Pos)
#define ATIMMODE23_ADTR_CMB0E                               ATIMMODE23_ADTR_CMB0E_Msk
#define ATIMMODE23_ADTR_ADTE_Pos                            (7U)
#define ATIMMODE23_ADTR_ADTE_Msk                            (0x1UL << ATIMMODE23_ADTR_ADTE_Pos)
#define ATIMMODE23_ADTR_ADTE                                ATIMMODE23_ADTR_ADTE_Msk

// ATIMMODE23_CRCH0
#define ATIMMODE23_CRCH0_CFACRABKSA_Pos                     (0U)
#define ATIMMODE23_CRCH0_CFACRABKSA_Msk                     (0x3UL << ATIMMODE23_CRCH0_CFACRABKSA_Pos)
#define ATIMMODE23_CRCH0_CFACRABKSA                         ATIMMODE23_CRCH0_CFACRABKSA_Msk
#define ATIMMODE23_CRCH0_CFBCRBBKSB_Pos                     (2U)
#define ATIMMODE23_CRCH0_CFBCRBBKSB_Msk                     (0x3UL << ATIMMODE23_CRCH0_CFBCRBBKSB_Pos)
#define ATIMMODE23_CRCH0_CFBCRBBKSB                         ATIMMODE23_CRCH0_CFBCRBBKSB_Msk
#define ATIMMODE23_CRCH0_CSA_Pos                            (4U)
#define ATIMMODE23_CRCH0_CSA_Msk                            (0x1UL << ATIMMODE23_CRCH0_CSA_Pos)
#define ATIMMODE23_CRCH0_CSA                                ATIMMODE23_CRCH0_CSA_Msk
#define ATIMMODE23_CRCH0_CSB_Pos                            (5U)
#define ATIMMODE23_CRCH0_CSB_Msk                            (0x1UL << ATIMMODE23_CRCH0_CSB_Pos)
#define ATIMMODE23_CRCH0_CSB                                ATIMMODE23_CRCH0_CSB_Msk
#define ATIMMODE23_CRCH0_BUFEA_Pos                          (6U)
#define ATIMMODE23_CRCH0_BUFEA_Msk                          (0x1UL << ATIMMODE23_CRCH0_BUFEA_Pos)
#define ATIMMODE23_CRCH0_BUFEA                              ATIMMODE23_CRCH0_BUFEA_Msk
#define ATIMMODE23_CRCH0_BUFEB_Pos                          (7U)
#define ATIMMODE23_CRCH0_BUFEB_Msk                          (0x1UL << ATIMMODE23_CRCH0_BUFEB_Pos)
#define ATIMMODE23_CRCH0_BUFEB                              ATIMMODE23_CRCH0_BUFEB_Msk
#define ATIMMODE23_CRCH0_CIEA_Pos                           (8U)
#define ATIMMODE23_CRCH0_CIEA_Msk                           (0x1UL << ATIMMODE23_CRCH0_CIEA_Pos)
#define ATIMMODE23_CRCH0_CIEA                               ATIMMODE23_CRCH0_CIEA_Msk
#define ATIMMODE23_CRCH0_CIEB_Pos                           (9U)
#define ATIMMODE23_CRCH0_CIEB_Msk                           (0x1UL << ATIMMODE23_CRCH0_CIEB_Pos)
#define ATIMMODE23_CRCH0_CIEB                               ATIMMODE23_CRCH0_CIEB_Msk
#define ATIMMODE23_CRCH0_CDEA_Pos                           (10U)
#define ATIMMODE23_CRCH0_CDEA_Msk                           (0x1UL << ATIMMODE23_CRCH0_CDEA_Pos)
#define ATIMMODE23_CRCH0_CDEA                               ATIMMODE23_CRCH0_CDEA_Msk
#define ATIMMODE23_CRCH0_CDEB_Pos                           (11U)
#define ATIMMODE23_CRCH0_CDEB_Msk                           (0x1UL << ATIMMODE23_CRCH0_CDEB_Pos)
#define ATIMMODE23_CRCH0_CDEB                               ATIMMODE23_CRCH0_CDEB_Msk
#define ATIMMODE23_CRCH0_CISB_Pos                           (12U)
#define ATIMMODE23_CRCH0_CISB_Msk                           (0x3UL << ATIMMODE23_CRCH0_CISB_Pos)
#define ATIMMODE23_CRCH0_CISB                               ATIMMODE23_CRCH0_CISB_Msk
#define ATIMMODE23_CRCH0_CCGA_Pos                           (14U)
#define ATIMMODE23_CRCH0_CCGA_Msk                           (0x1UL << ATIMMODE23_CRCH0_CCGA_Pos)
#define ATIMMODE23_CRCH0_CCGA                               ATIMMODE23_CRCH0_CCGA_Msk
#define ATIMMODE23_CRCH0_CCGB_Pos                           (15U)
#define ATIMMODE23_CRCH0_CCGB_Msk                           (0x1UL << ATIMMODE23_CRCH0_CCGB_Pos)
#define ATIMMODE23_CRCH0_CCGB                               ATIMMODE23_CRCH0_CCGB_Msk

// ATIMMODE23_DTR
#define ATIMMODE23_DTR_DTR_Pos                              (0U)
#define ATIMMODE23_DTR_DTR_Msk                              (0xFFUL << ATIMMODE23_DTR_DTR_Pos)
#define ATIMMODE23_DTR_DTR                                  ATIMMODE23_DTR_DTR_Msk
#define ATIMMODE23_DTR_BKSEL_Pos                            (8U)
#define ATIMMODE23_DTR_BKSEL_Msk                            (0x1UL << ATIMMODE23_DTR_BKSEL_Pos)
#define ATIMMODE23_DTR_BKSEL                                ATIMMODE23_DTR_BKSEL_Msk
#define ATIMMODE23_DTR_DTEN_Pos                             (9U)
#define ATIMMODE23_DTR_DTEN_Msk                             (0x1UL << ATIMMODE23_DTR_DTEN_Pos)
#define ATIMMODE23_DTR_DTEN                                 ATIMMODE23_DTR_DTEN_Msk
#define ATIMMODE23_DTR_BKE_Pos                              (10U)
#define ATIMMODE23_DTR_BKE_Msk                              (0x1UL << ATIMMODE23_DTR_BKE_Pos)
#define ATIMMODE23_DTR_BKE                                  ATIMMODE23_DTR_BKE_Msk
#define ATIMMODE23_DTR_AOE_Pos                              (11U)
#define ATIMMODE23_DTR_AOE_Msk                              (0x1UL << ATIMMODE23_DTR_AOE_Pos)
#define ATIMMODE23_DTR_AOE                                  ATIMMODE23_DTR_AOE_Msk
#define ATIMMODE23_DTR_MOE_Pos                              (12U)
#define ATIMMODE23_DTR_MOE_Msk                              (0x1UL << ATIMMODE23_DTR_MOE_Pos)
#define ATIMMODE23_DTR_MOE                                  ATIMMODE23_DTR_MOE_Msk
#define ATIMMODE23_DTR_SAFEEN_Pos                           (13U)
#define ATIMMODE23_DTR_SAFEEN_Msk                           (0x1UL << ATIMMODE23_DTR_SAFEEN_Pos)
#define ATIMMODE23_DTR_SAFEEN                               ATIMMODE23_DTR_SAFEEN_Msk
#define ATIMMODE23_DTR_VCE_Pos                              (14U)
#define ATIMMODE23_DTR_VCE_Msk                              (0x1UL << ATIMMODE23_DTR_VCE_Pos)
#define ATIMMODE23_DTR_VCE                                  ATIMMODE23_DTR_VCE_Msk

// ATIMMODE23_RCR
#define ATIMMODE23_RCR_RCR_Pos                              (0U)
#define ATIMMODE23_RCR_RCR_Msk                              (0xFFUL << ATIMMODE23_RCR_RCR_Pos)
#define ATIMMODE23_RCR_RCR                                  ATIMMODE23_RCR_RCR_Msk
#define ATIMMODE23_RCR_OV_Pos                               (8U)
#define ATIMMODE23_RCR_OV_Msk                               (0x1UL << ATIMMODE23_RCR_OV_Pos)
#define ATIMMODE23_RCR_OV                                   ATIMMODE23_RCR_OV_Msk
#define ATIMMODE23_RCR_UD_Pos                               (9U)
#define ATIMMODE23_RCR_UD_Msk                               (0x1UL << ATIMMODE23_RCR_UD_Pos)
#define ATIMMODE23_RCR_UD                                   ATIMMODE23_RCR_UD_Msk

// ATIMMODE23_CCR0A
#define ATIMMODE23_CCR0A_CCR0A_Pos                          (0U)
#define ATIMMODE23_CCR0A_CCR0A_Msk                          (0xFFFFUL << ATIMMODE23_CCR0A_CCR0A_Pos)
#define ATIMMODE23_CCR0A_CCR0A                              ATIMMODE23_CCR0A_CCR0A_Msk

// ATIMMODE23_CCR0B
#define ATIMMODE23_CCR0B_CCR0B_Pos                          (0U)
#define ATIMMODE23_CCR0B_CCR0B_Msk                          (0xFFFFUL << ATIMMODE23_CCR0B_CCR0B_Pos)
#define ATIMMODE23_CCR0B_CCR0B                              ATIMMODE23_CCR0B_CCR0B_Msk



//********************    Bits Define For Peripheral BTIM    ********************//
// BTIM_ARR
#define BTIM_ARR_ARR_Pos                                    (0U)
#define BTIM_ARR_ARR_Msk                                    (0xFFFFUL << BTIM_ARR_ARR_Pos)
#define BTIM_ARR_ARR                                        BTIM_ARR_ARR_Msk

// BTIM_CNT
#define BTIM_CNT_CNT_Pos                                    (0U)
#define BTIM_CNT_CNT_Msk                                    (0xFFFFUL << BTIM_CNT_CNT_Pos)
#define BTIM_CNT_CNT                                        BTIM_CNT_CNT_Msk

// BTIM_CR
#define BTIM_CR_CEN_Pos                                     (0U)
#define BTIM_CR_CEN_Msk                                     (0x1UL << BTIM_CR_CEN_Pos)
#define BTIM_CR_CEN                                         BTIM_CR_CEN_Msk
#define BTIM_CR_MD_Pos                                      (1U)
#define BTIM_CR_MD_Msk                                      (0x3UL << BTIM_CR_MD_Pos)
#define BTIM_CR_MD                                          BTIM_CR_MD_Msk
#define BTIM_CR_TOGEN_Pos                                   (3U)
#define BTIM_CR_TOGEN_Msk                                   (0x1UL << BTIM_CR_TOGEN_Pos)
#define BTIM_CR_TOGEN                                       BTIM_CR_TOGEN_Msk
#define BTIM_CR_PRS_Pos                                     (4U)
#define BTIM_CR_PRS_Msk                                     (0xFUL << BTIM_CR_PRS_Pos)
#define BTIM_CR_PRS                                         BTIM_CR_PRS_Msk
#define BTIM_CR_OST_Pos                                     (8U)
#define BTIM_CR_OST_Msk                                     (0x1UL << BTIM_CR_OST_Pos)
#define BTIM_CR_OST                                         BTIM_CR_OST_Msk
#define BTIM_CR_TRS_Pos                                     (9U)
#define BTIM_CR_TRS_Msk                                     (0x3UL << BTIM_CR_TRS_Pos)
#define BTIM_CR_TRS                                         BTIM_CR_TRS_Msk
#define BTIM_CR_ETP_Pos                                     (11U)
#define BTIM_CR_ETP_Msk                                     (0x1UL << BTIM_CR_ETP_Pos)
#define BTIM_CR_ETP                                         BTIM_CR_ETP_Msk

// BTIM_IER
#define BTIM_IER_UI_Pos                                     (0U)
#define BTIM_IER_UI_Msk                                     (0x1UL << BTIM_IER_UI_Pos)
#define BTIM_IER_UI                                         BTIM_IER_UI_Msk
#define BTIM_IER_TI_Pos                                     (1U)
#define BTIM_IER_TI_Msk                                     (0x1UL << BTIM_IER_TI_Pos)
#define BTIM_IER_TI                                         BTIM_IER_TI_Msk

// BTIM_IFR
#define BTIM_IFR_UI_Pos                                     (0U)
#define BTIM_IFR_UI_Msk                                     (0x1UL << BTIM_IFR_UI_Pos)
#define BTIM_IFR_UI                                         BTIM_IFR_UI_Msk
#define BTIM_IFR_TI_Pos                                     (1U)
#define BTIM_IFR_TI_Msk                                     (0x1UL << BTIM_IFR_TI_Pos)
#define BTIM_IFR_TI                                         BTIM_IFR_TI_Msk

// BTIM_ICR
#define BTIM_ICR_UI_Pos                                     (0U)
#define BTIM_ICR_UI_Msk                                     (0x1UL << BTIM_ICR_UI_Pos)
#define BTIM_ICR_UI                                         BTIM_ICR_UI_Msk
#define BTIM_ICR_TI_Pos                                     (1U)
#define BTIM_ICR_TI_Msk                                     (0x1UL << BTIM_ICR_TI_Pos)
#define BTIM_ICR_TI                                         BTIM_ICR_TI_Msk

// BTIM_AIFR
#define BTIM_AIFR_UI03_Pos                                   (0U)
#define BTIM_AIFR_UI03_Msk                                   (0x1UL << BTIM_AIFR_UI03_Pos)
#define BTIM_AIFR_UI03                                       BTIM_AIFR_UI03_Msk
#define BTIM_AIFR_TI03_Pos                                   (1U)
#define BTIM_AIFR_TI03_Msk                                   (0x1UL << BTIM_AIFR_TI03_Pos)
#define BTIM_AIFR_TI03                                       BTIM_AIFR_TI03_Msk
#define BTIM_AIFR_UI14_Pos                                   (2U)
#define BTIM_AIFR_UI14_Msk                                   (0x1UL << BTIM_AIFR_UI14_Pos)
#define BTIM_AIFR_UI14                                       BTIM_AIFR_UI14_Msk
#define BTIM_AIFR_TI14_Pos                                   (3U)
#define BTIM_AIFR_TI14_Msk                                   (0x1UL << BTIM_AIFR_TI14_Pos)
#define BTIM_AIFR_TI14                                       BTIM_AIFR_TI14_Msk
#define BTIM_AIFR_UI25_Pos                                   (4U)
#define BTIM_AIFR_UI25_Msk                                   (0x1UL << BTIM_AIFR_UI25_Pos)
#define BTIM_AIFR_UI25                                       BTIM_AIFR_UI25_Msk
#define BTIM_AIFR_TI25_Pos                                   (5U)
#define BTIM_AIFR_TI25_Msk                                   (0x1UL << BTIM_AIFR_TI25_Pos)
#define BTIM_AIFR_TI25                                       BTIM_AIFR_TI25_Msk

// BTIM_AICR
#define BTIM_AICR_UI03_Pos                                   (0U)
#define BTIM_AICR_UI03_Msk                                   (0x1UL << BTIM_AICR_UI03_Pos)
#define BTIM_AICR_UI03                                       BTIM_AICR_UI03_Msk
#define BTIM_AICR_TI03_Pos                                   (1U)
#define BTIM_AICR_TI03_Msk                                   (0x1UL << BTIM_AICR_TI03_Pos)
#define BTIM_AICR_TI03                                       BTIM_AICR_TI03_Msk
#define BTIM_AICR_UI14_Pos                                   (2U)
#define BTIM_AICR_UI14_Msk                                   (0x1UL << BTIM_AICR_UI14_Pos)
#define BTIM_AICR_UI14                                       BTIM_AICR_UI14_Msk
#define BTIM_AICR_TI14_Pos                                   (3U)
#define BTIM_AICR_TI14_Msk                                   (0x1UL << BTIM_AICR_TI14_Pos)
#define BTIM_AICR_TI14                                       BTIM_AICR_TI14_Msk
#define BTIM_AICR_UI25_Pos                                   (4U)
#define BTIM_AICR_UI25_Msk                                   (0x1UL << BTIM_AICR_UI25_Pos)
#define BTIM_AICR_UI25                                       BTIM_AICR_UI25_Msk
#define BTIM_AICR_TI25_Pos                                   (5U)
#define BTIM_AICR_TI25_Msk                                   (0x1UL << BTIM_AICR_TI25_Pos)
#define BTIM_AICR_TI25                                       BTIM_AICR_TI25_Msk



//********************    Bits Define For Peripheral CAN    ********************//
// CAN_CFG_STAT
#define CAN_CFG_STAT_BUSOFF_Pos                             (0U)
#define CAN_CFG_STAT_BUSOFF_Msk                             (0x1UL << CAN_CFG_STAT_BUSOFF_Pos)
#define CAN_CFG_STAT_BUSOFF                                 CAN_CFG_STAT_BUSOFF_Msk
#define CAN_CFG_STAT_TACTIVE_Pos                            (1U)
#define CAN_CFG_STAT_TACTIVE_Msk                            (0x1UL << CAN_CFG_STAT_TACTIVE_Pos)
#define CAN_CFG_STAT_TACTIVE                                CAN_CFG_STAT_TACTIVE_Msk
#define CAN_CFG_STAT_RACTIVE_Pos                            (2U)
#define CAN_CFG_STAT_RACTIVE_Msk                            (0x1UL << CAN_CFG_STAT_RACTIVE_Pos)
#define CAN_CFG_STAT_RACTIVE                                CAN_CFG_STAT_RACTIVE_Msk
#define CAN_CFG_STAT_TSSS_Pos                               (3U)
#define CAN_CFG_STAT_TSSS_Msk                               (0x1UL << CAN_CFG_STAT_TSSS_Pos)
#define CAN_CFG_STAT_TSSS                                   CAN_CFG_STAT_TSSS_Msk
#define CAN_CFG_STAT_TPSS_Pos                               (4U)
#define CAN_CFG_STAT_TPSS_Msk                               (0x1UL << CAN_CFG_STAT_TPSS_Pos)
#define CAN_CFG_STAT_TPSS                                   CAN_CFG_STAT_TPSS_Msk
#define CAN_CFG_STAT_LBMI_Pos                               (5U)
#define CAN_CFG_STAT_LBMI_Msk                               (0x1UL << CAN_CFG_STAT_LBMI_Pos)
#define CAN_CFG_STAT_LBMI                                   CAN_CFG_STAT_LBMI_Msk
#define CAN_CFG_STAT_LBME_Pos                               (6U)
#define CAN_CFG_STAT_LBME_Msk                               (0x1UL << CAN_CFG_STAT_LBME_Pos)
#define CAN_CFG_STAT_LBME                                   CAN_CFG_STAT_LBME_Msk
#define CAN_CFG_STAT_RESET_Pos                              (7U)
#define CAN_CFG_STAT_RESET_Msk                              (0x1UL << CAN_CFG_STAT_RESET_Pos)
#define CAN_CFG_STAT_RESET                                  CAN_CFG_STAT_RESET_Msk

// CAN_TCMD
#define CAN_TCMD_TSA_Pos                                    (0U)
#define CAN_TCMD_TSA_Msk                                    (0x1UL << CAN_TCMD_TSA_Pos)
#define CAN_TCMD_TSA                                        CAN_TCMD_TSA_Msk
#define CAN_TCMD_TSALL_Pos                                  (1U)
#define CAN_TCMD_TSALL_Msk                                  (0x1UL << CAN_TCMD_TSALL_Pos)
#define CAN_TCMD_TSALL                                      CAN_TCMD_TSALL_Msk
#define CAN_TCMD_TSONE_Pos                                  (2U)
#define CAN_TCMD_TSONE_Msk                                  (0x1UL << CAN_TCMD_TSONE_Pos)
#define CAN_TCMD_TSONE                                      CAN_TCMD_TSONE_Msk
#define CAN_TCMD_TPA_Pos                                    (3U)
#define CAN_TCMD_TPA_Msk                                    (0x1UL << CAN_TCMD_TPA_Pos)
#define CAN_TCMD_TPA                                        CAN_TCMD_TPA_Msk
#define CAN_TCMD_TPE_Pos                                    (4U)
#define CAN_TCMD_TPE_Msk                                    (0x1UL << CAN_TCMD_TPE_Pos)
#define CAN_TCMD_TPE                                        CAN_TCMD_TPE_Msk
#define CAN_TCMD_STBY_Pos                                   (5U)
#define CAN_TCMD_STBY_Msk                                   (0x1UL << CAN_TCMD_STBY_Pos)
#define CAN_TCMD_STBY                                       CAN_TCMD_STBY_Msk
#define CAN_TCMD_LOM_Pos                                    (6U)
#define CAN_TCMD_LOM_Msk                                    (0x1UL << CAN_TCMD_LOM_Pos)
#define CAN_TCMD_LOM                                        CAN_TCMD_LOM_Msk
#define CAN_TCMD_TBSEL_Pos                                  (7U)
#define CAN_TCMD_TBSEL_Msk                                  (0x1UL << CAN_TCMD_TBSEL_Pos)
#define CAN_TCMD_TBSEL                                      CAN_TCMD_TBSEL_Msk

// CAN_TCTRL
#define CAN_TCTRL_TSSTAT_Pos                                (0U)
#define CAN_TCTRL_TSSTAT_Msk                                (0x3UL << CAN_TCTRL_TSSTAT_Pos)
#define CAN_TCTRL_TSSTAT                                    CAN_TCTRL_TSSTAT_Msk
#define CAN_TCTRL_TTTBM_Pos                                 (4U)
#define CAN_TCTRL_TTTBM_Msk                                 (0x1UL << CAN_TCTRL_TTTBM_Pos)
#define CAN_TCTRL_TTTBM                                     CAN_TCTRL_TTTBM_Msk
#define CAN_TCTRL_TSMODE_Pos                                (5U)
#define CAN_TCTRL_TSMODE_Msk                                (0x1UL << CAN_TCTRL_TSMODE_Pos)
#define CAN_TCTRL_TSMODE                                    CAN_TCTRL_TSMODE_Msk
#define CAN_TCTRL_TSNEXT_Pos                                (6U)
#define CAN_TCTRL_TSNEXT_Msk                                (0x1UL << CAN_TCTRL_TSNEXT_Pos)
#define CAN_TCTRL_TSNEXT                                    CAN_TCTRL_TSNEXT_Msk

// CAN_RCTRL
#define CAN_RCTRL_RSSTAT_Pos                                (0U)
#define CAN_RCTRL_RSSTAT_Msk                                (0x3UL << CAN_RCTRL_RSSTAT_Pos)
#define CAN_RCTRL_RSSTAT                                    CAN_RCTRL_RSSTAT_Msk
#define CAN_RCTRL_RBALL_Pos                                 (3U)
#define CAN_RCTRL_RBALL_Msk                                 (0x1UL << CAN_RCTRL_RBALL_Pos)
#define CAN_RCTRL_RBALL                                     CAN_RCTRL_RBALL_Msk
#define CAN_RCTRL_RREL_Pos                                  (4U)
#define CAN_RCTRL_RREL_Msk                                  (0x1UL << CAN_RCTRL_RREL_Pos)
#define CAN_RCTRL_RREL                                      CAN_RCTRL_RREL_Msk
#define CAN_RCTRL_ROV_Pos                                   (5U)
#define CAN_RCTRL_ROV_Msk                                   (0x1UL << CAN_RCTRL_ROV_Pos)
#define CAN_RCTRL_ROV                                       CAN_RCTRL_ROV_Msk
#define CAN_RCTRL_ROM_Pos                                   (6U)
#define CAN_RCTRL_ROM_Msk                                   (0x1UL << CAN_RCTRL_ROM_Pos)
#define CAN_RCTRL_ROM                                       CAN_RCTRL_ROM_Msk
#define CAN_RCTRL_SACK_Pos                                  (7U)
#define CAN_RCTRL_SACK_Msk                                  (0x1UL << CAN_RCTRL_SACK_Pos)
#define CAN_RCTRL_SACK                                      CAN_RCTRL_SACK_Msk

// CAN_RTIE
#define CAN_RTIE_TSFF_Pos                                   (0U)
#define CAN_RTIE_TSFF_Msk                                   (0x1UL << CAN_RTIE_TSFF_Pos)
#define CAN_RTIE_TSFF                                       CAN_RTIE_TSFF_Msk
#define CAN_RTIE_EIE_Pos                                    (1U)
#define CAN_RTIE_EIE_Msk                                    (0x1UL << CAN_RTIE_EIE_Pos)
#define CAN_RTIE_EIE                                        CAN_RTIE_EIE_Msk
#define CAN_RTIE_TSIE_Pos                                   (2U)
#define CAN_RTIE_TSIE_Msk                                   (0x1UL << CAN_RTIE_TSIE_Pos)
#define CAN_RTIE_TSIE                                       CAN_RTIE_TSIE_Msk
#define CAN_RTIE_TPIE_Pos                                   (3U)
#define CAN_RTIE_TPIE_Msk                                   (0x1UL << CAN_RTIE_TPIE_Pos)
#define CAN_RTIE_TPIE                                       CAN_RTIE_TPIE_Msk
#define CAN_RTIE_RAFIE_Pos                                  (4U)
#define CAN_RTIE_RAFIE_Msk                                  (0x1UL << CAN_RTIE_RAFIE_Pos)
#define CAN_RTIE_RAFIE                                      CAN_RTIE_RAFIE_Msk
#define CAN_RTIE_RFIE_Pos                                   (5U)
#define CAN_RTIE_RFIE_Msk                                   (0x1UL << CAN_RTIE_RFIE_Pos)
#define CAN_RTIE_RFIE                                       CAN_RTIE_RFIE_Msk
#define CAN_RTIE_ROIE_Pos                                   (6U)
#define CAN_RTIE_ROIE_Msk                                   (0x1UL << CAN_RTIE_ROIE_Pos)
#define CAN_RTIE_ROIE                                       CAN_RTIE_ROIE_Msk
#define CAN_RTIE_RIE_Pos                                    (7U)
#define CAN_RTIE_RIE_Msk                                    (0x1UL << CAN_RTIE_RIE_Pos)
#define CAN_RTIE_RIE                                        CAN_RTIE_RIE_Msk

// CAN_RTIF
#define CAN_RTIF_AIF_Pos                                    (0U)
#define CAN_RTIF_AIF_Msk                                    (0x1UL << CAN_RTIF_AIF_Pos)
#define CAN_RTIF_AIF                                        CAN_RTIF_AIF_Msk
#define CAN_RTIF_EIF_Pos                                    (1U)
#define CAN_RTIF_EIF_Msk                                    (0x1UL << CAN_RTIF_EIF_Pos)
#define CAN_RTIF_EIF                                        CAN_RTIF_EIF_Msk
#define CAN_RTIF_TSIF_Pos                                   (2U)
#define CAN_RTIF_TSIF_Msk                                   (0x1UL << CAN_RTIF_TSIF_Pos)
#define CAN_RTIF_TSIF                                       CAN_RTIF_TSIF_Msk
#define CAN_RTIF_TPIF_Pos                                   (3U)
#define CAN_RTIF_TPIF_Msk                                   (0x1UL << CAN_RTIF_TPIF_Pos)
#define CAN_RTIF_TPIF                                       CAN_RTIF_TPIF_Msk
#define CAN_RTIF_RAFIF_Pos                                  (4U)
#define CAN_RTIF_RAFIF_Msk                                  (0x1UL << CAN_RTIF_RAFIF_Pos)
#define CAN_RTIF_RAFIF                                      CAN_RTIF_RAFIF_Msk
#define CAN_RTIF_RFIF_Pos                                   (5U)
#define CAN_RTIF_RFIF_Msk                                   (0x1UL << CAN_RTIF_RFIF_Pos)
#define CAN_RTIF_RFIF                                       CAN_RTIF_RFIF_Msk
#define CAN_RTIF_ROIF_Pos                                   (6U)
#define CAN_RTIF_ROIF_Msk                                   (0x1UL << CAN_RTIF_ROIF_Pos)
#define CAN_RTIF_ROIF                                       CAN_RTIF_ROIF_Msk
#define CAN_RTIF_RIF_Pos                                    (7U)
#define CAN_RTIF_RIF_Msk                                    (0x1UL << CAN_RTIF_RIF_Pos)
#define CAN_RTIF_RIF                                        CAN_RTIF_RIF_Msk

// CAN_ERRINT
#define CAN_ERRINT_BEIF_Pos                                 (0U)
#define CAN_ERRINT_BEIF_Msk                                 (0x1UL << CAN_ERRINT_BEIF_Pos)
#define CAN_ERRINT_BEIF                                     CAN_ERRINT_BEIF_Msk
#define CAN_ERRINT_BEIE_Pos                                 (1U)
#define CAN_ERRINT_BEIE_Msk                                 (0x1UL << CAN_ERRINT_BEIE_Pos)
#define CAN_ERRINT_BEIE                                     CAN_ERRINT_BEIE_Msk
#define CAN_ERRINT_ALIF_Pos                                 (2U)
#define CAN_ERRINT_ALIF_Msk                                 (0x1UL << CAN_ERRINT_ALIF_Pos)
#define CAN_ERRINT_ALIF                                     CAN_ERRINT_ALIF_Msk
#define CAN_ERRINT_ALIE_Pos                                 (3U)
#define CAN_ERRINT_ALIE_Msk                                 (0x1UL << CAN_ERRINT_ALIE_Pos)
#define CAN_ERRINT_ALIE                                     CAN_ERRINT_ALIE_Msk
#define CAN_ERRINT_EPIF_Pos                                 (4U)
#define CAN_ERRINT_EPIF_Msk                                 (0x1UL << CAN_ERRINT_EPIF_Pos)
#define CAN_ERRINT_EPIF                                     CAN_ERRINT_EPIF_Msk
#define CAN_ERRINT_EPIE_Pos                                 (5U)
#define CAN_ERRINT_EPIE_Msk                                 (0x1UL << CAN_ERRINT_EPIE_Pos)
#define CAN_ERRINT_EPIE                                     CAN_ERRINT_EPIE_Msk
#define CAN_ERRINT_EPASS_Pos                                (6U)
#define CAN_ERRINT_EPASS_Msk                                (0x1UL << CAN_ERRINT_EPASS_Pos)
#define CAN_ERRINT_EPASS                                    CAN_ERRINT_EPASS_Msk
#define CAN_ERRINT_EWARN_Pos                                (7U)
#define CAN_ERRINT_EWARN_Msk                                (0x1UL << CAN_ERRINT_EWARN_Pos)
#define CAN_ERRINT_EWARN                                    CAN_ERRINT_EWARN_Msk

// CAN_LIMIT
#define CAN_LIMIT_EWL_Pos                                   (0U)
#define CAN_LIMIT_EWL_Msk                                   (0xFUL << CAN_LIMIT_EWL_Pos)
#define CAN_LIMIT_EWL                                       CAN_LIMIT_EWL_Msk
#define CAN_LIMIT_AFWL_Pos                                  (4U)
#define CAN_LIMIT_AFWL_Msk                                  (0xFUL << CAN_LIMIT_AFWL_Pos)
#define CAN_LIMIT_AFWL                                      CAN_LIMIT_AFWL_Msk

// CAN_BT
#define CAN_BT_SEG_1_Pos                                    (0U)
#define CAN_BT_SEG_1_Msk                                    (0xFFUL << CAN_BT_SEG_1_Pos)
#define CAN_BT_SEG_1                                        CAN_BT_SEG_1_Msk
#define CAN_BT_SEG_2_Pos                                    (8U)
#define CAN_BT_SEG_2_Msk                                    (0x7FUL << CAN_BT_SEG_2_Pos)
#define CAN_BT_SEG_2                                        CAN_BT_SEG_2_Msk
#define CAN_BT_SJW_Pos                                      (16U)
#define CAN_BT_SJW_Msk                                      (0x7FUL << CAN_BT_SJW_Pos)
#define CAN_BT_SJW                                          CAN_BT_SJW_Msk
#define CAN_BT_PRESC_Pos                                    (24U)
#define CAN_BT_PRESC_Msk                                    (0xFFUL << CAN_BT_PRESC_Pos)
#define CAN_BT_PRESC                                        CAN_BT_PRESC_Msk

// CAN_EALCAP
#define CAN_EALCAP_ALC_Pos                                  (0U)
#define CAN_EALCAP_ALC_Msk                                  (0x1FUL << CAN_EALCAP_ALC_Pos)
#define CAN_EALCAP_ALC                                      CAN_EALCAP_ALC_Msk
#define CAN_EALCAP_KOER_Pos                                 (5U)
#define CAN_EALCAP_KOER_Msk                                 (0x7UL << CAN_EALCAP_KOER_Pos)
#define CAN_EALCAP_KOER                                     CAN_EALCAP_KOER_Msk

// CAN_ACFCTRL
#define CAN_ACFCTRL_ACFADR_Pos                              (0U)
#define CAN_ACFCTRL_ACFADR_Msk                              (0xFUL << CAN_ACFCTRL_ACFADR_Pos)
#define CAN_ACFCTRL_ACFADR                                  CAN_ACFCTRL_ACFADR_Msk
#define CAN_ACFCTRL_SELMASK_Pos                             (5U)
#define CAN_ACFCTRL_SELMASK_Msk                             (0x1UL << CAN_ACFCTRL_SELMASK_Pos)
#define CAN_ACFCTRL_SELMASK                                 CAN_ACFCTRL_SELMASK_Msk

// CAN_ACFEN
#define CAN_ACFEN_AE_1_Pos                                  (0U)
#define CAN_ACFEN_AE_1_Msk                                  (0x1UL << CAN_ACFEN_AE_1_Pos)
#define CAN_ACFEN_AE_1                                      CAN_ACFEN_AE_1_Msk
#define CAN_ACFEN_AE_2_Pos                                  (1U)
#define CAN_ACFEN_AE_2_Msk                                  (0x1UL << CAN_ACFEN_AE_2_Pos)
#define CAN_ACFEN_AE_2                                      CAN_ACFEN_AE_2_Msk
#define CAN_ACFEN_AE_3_Pos                                  (2U)
#define CAN_ACFEN_AE_3_Msk                                  (0x1UL << CAN_ACFEN_AE_3_Pos)
#define CAN_ACFEN_AE_3                                      CAN_ACFEN_AE_3_Msk
#define CAN_ACFEN_AE_4_Pos                                  (3U)
#define CAN_ACFEN_AE_4_Msk                                  (0x1UL << CAN_ACFEN_AE_4_Pos)
#define CAN_ACFEN_AE_4                                      CAN_ACFEN_AE_4_Msk
#define CAN_ACFEN_AE_5_Pos                                  (4U)
#define CAN_ACFEN_AE_5_Msk                                  (0x1UL << CAN_ACFEN_AE_5_Pos)
#define CAN_ACFEN_AE_5                                      CAN_ACFEN_AE_5_Msk
#define CAN_ACFEN_AE_6_Pos                                  (5U)
#define CAN_ACFEN_AE_6_Msk                                  (0x1UL << CAN_ACFEN_AE_6_Pos)
#define CAN_ACFEN_AE_6                                      CAN_ACFEN_AE_6_Msk
#define CAN_ACFEN_AE_7_Pos                                  (6U)
#define CAN_ACFEN_AE_7_Msk                                  (0x1UL << CAN_ACFEN_AE_7_Pos)
#define CAN_ACFEN_AE_7                                      CAN_ACFEN_AE_7_Msk
#define CAN_ACFEN_AE_8_Pos                                  (7U)
#define CAN_ACFEN_AE_8_Msk                                  (0x1UL << CAN_ACFEN_AE_8_Pos)
#define CAN_ACFEN_AE_8                                      CAN_ACFEN_AE_8_Msk

// CAN_ACF
#define CAN_ACF_ACODE_AMASK_Pos                             (0U)
#define CAN_ACF_ACODE_AMASK_Msk                             (0x1FFFFFFFUL << CAN_ACF_ACODE_AMASK_Pos)
#define CAN_ACF_ACODE_AMASK                                 CAN_ACF_ACODE_AMASK_Msk
#define CAN_ACF_AIDE_Pos                                    (29U)
#define CAN_ACF_AIDE_Msk                                    (0x1UL << CAN_ACF_AIDE_Pos)
#define CAN_ACF_AIDE                                        CAN_ACF_AIDE_Msk
#define CAN_ACF_AIDEE_Pos                                   (30U)
#define CAN_ACF_AIDEE_Msk                                   (0x1UL << CAN_ACF_AIDEE_Pos)
#define CAN_ACF_AIDEE                                       CAN_ACF_AIDEE_Msk

// CAN_TBSLOT
#define CAN_TBSLOT_TBPTR_Pos                                (0U)
#define CAN_TBSLOT_TBPTR_Msk                                (0x7UL << CAN_TBSLOT_TBPTR_Pos)
#define CAN_TBSLOT_TBPTR                                    CAN_TBSLOT_TBPTR_Msk
#define CAN_TBSLOT_TBF_Pos                                  (6U)
#define CAN_TBSLOT_TBF_Msk                                  (0x1UL << CAN_TBSLOT_TBF_Pos)
#define CAN_TBSLOT_TBF                                      CAN_TBSLOT_TBF_Msk
#define CAN_TBSLOT_TBE_Pos                                  (7U)
#define CAN_TBSLOT_TBE_Msk                                  (0x1UL << CAN_TBSLOT_TBE_Pos)
#define CAN_TBSLOT_TBE                                      CAN_TBSLOT_TBE_Msk

// CAN_TTCFG
#define CAN_TTCFG_TTEN_Pos                                  (0U)
#define CAN_TTCFG_TTEN_Msk                                  (0x1UL << CAN_TTCFG_TTEN_Pos)
#define CAN_TTCFG_TTEN                                      CAN_TTCFG_TTEN_Msk
#define CAN_TTCFG_T_PRESC_Pos                               (1U)
#define CAN_TTCFG_T_PRESC_Msk                               (0x3UL << CAN_TTCFG_T_PRESC_Pos)
#define CAN_TTCFG_T_PRESC                                   CAN_TTCFG_T_PRESC_Msk
#define CAN_TTCFG_TTIF_Pos                                  (3U)
#define CAN_TTCFG_TTIF_Msk                                  (0x1UL << CAN_TTCFG_TTIF_Pos)
#define CAN_TTCFG_TTIF                                      CAN_TTCFG_TTIF_Msk
#define CAN_TTCFG_TTIE_Pos                                  (4U)
#define CAN_TTCFG_TTIE_Msk                                  (0x1UL << CAN_TTCFG_TTIE_Pos)
#define CAN_TTCFG_TTIE                                      CAN_TTCFG_TTIE_Msk
#define CAN_TTCFG_TEIF_Pos                                  (5U)
#define CAN_TTCFG_TEIF_Msk                                  (0x1UL << CAN_TTCFG_TEIF_Pos)
#define CAN_TTCFG_TEIF                                      CAN_TTCFG_TEIF_Msk
#define CAN_TTCFG_WTIF_Pos                                  (6U)
#define CAN_TTCFG_WTIF_Msk                                  (0x1UL << CAN_TTCFG_WTIF_Pos)
#define CAN_TTCFG_WTIF                                      CAN_TTCFG_WTIF_Msk
#define CAN_TTCFG_WTIE_Pos                                  (7U)
#define CAN_TTCFG_WTIE_Msk                                  (0x1UL << CAN_TTCFG_WTIE_Pos)
#define CAN_TTCFG_WTIE                                      CAN_TTCFG_WTIE_Msk

// CAN_REF_MSG
#define CAN_REF_MSG_REF_ID_Pos                              (0U)
#define CAN_REF_MSG_REF_ID_Msk                              (0x1FFFFFFFUL << CAN_REF_MSG_REF_ID_Pos)
#define CAN_REF_MSG_REF_ID                                  CAN_REF_MSG_REF_ID_Msk
#define CAN_REF_MSG_REF_IDE_Pos                             (31U)
#define CAN_REF_MSG_REF_IDE_Msk                             (0x1UL << CAN_REF_MSG_REF_IDE_Pos)
#define CAN_REF_MSG_REF_IDE                                 CAN_REF_MSG_REF_IDE_Msk

// CAN_TRG_CFG
#define CAN_TRG_CFG_TTPTR_Pos                               (0U)
#define CAN_TRG_CFG_TTPTR_Msk                               (0x7UL << CAN_TRG_CFG_TTPTR_Pos)
#define CAN_TRG_CFG_TTPTR                                   CAN_TRG_CFG_TTPTR_Msk
#define CAN_TRG_CFG_TTYPE_Pos                               (8U)
#define CAN_TRG_CFG_TTYPE_Msk                               (0x7UL << CAN_TRG_CFG_TTYPE_Pos)
#define CAN_TRG_CFG_TTYPE                                   CAN_TRG_CFG_TTYPE_Msk
#define CAN_TRG_CFG_TEW_Pos                                 (12U)
#define CAN_TRG_CFG_TEW_Msk                                 (0xFUL << CAN_TRG_CFG_TEW_Pos)
#define CAN_TRG_CFG_TEW                                     CAN_TRG_CFG_TEW_Msk



//********************    Bits Define For Peripheral CRC    ********************//
// CRC_CSR
#define CRC_CSR_CODE_Pos                                    (0U)
#define CRC_CSR_CODE_Msk                                    (0x1UL << CRC_CSR_CODE_Pos)
#define CRC_CSR_CODE                                        CRC_CSR_CODE_Msk
#define CRC_CSR_FLAG_Pos                                    (1U)
#define CRC_CSR_FLAG_Msk                                    (0x1UL << CRC_CSR_FLAG_Pos)
#define CRC_CSR_FLAG                                        CRC_CSR_FLAG_Msk

// CRC_RESULT
#define CRC_RESULT_RESULT_Pos                               (0U)
#define CRC_RESULT_RESULT_Msk                               (0xFFFFFFFFUL << CRC_RESULT_RESULT_Pos)
#define CRC_RESULT_RESULT                                   CRC_RESULT_RESULT_Msk

// CRC_DATA
#define CRC_DATA_DATA_Pos                                   (0U)
#define CRC_DATA_DATA_Msk                                   (0xFFFFFFFFUL << CRC_DATA_DATA_Pos)
#define CRC_DATA_DATA                                       CRC_DATA_DATA_Msk



//********************    Bits Define For Peripheral CTRIM    ********************//
// CTRIM_ARR
#define CTRIM_ARR_ARR_Pos                                   (0U)
#define CTRIM_ARR_ARR_Msk                                   (0xFFFFUL << CTRIM_ARR_ARR_Pos)
#define CTRIM_ARR_ARR                                       CTRIM_ARR_ARR_Msk

// CTRIM_CNT
#define CTRIM_CNT_CNT_Pos                                   (0U)
#define CTRIM_CNT_CNT_Msk                                   (0xFFFFUL << CTRIM_CNT_CNT_Pos)
#define CTRIM_CNT_CNT                                       CTRIM_CNT_CNT_Msk

// CTRIM_CR0
#define CTRIM_CR0_STEP_Pos                                  (0U)
#define CTRIM_CR0_STEP_Msk                                  (0x7UL << CTRIM_CR0_STEP_Pos)
#define CTRIM_CR0_STEP                                      CTRIM_CR0_STEP_Msk
#define CTRIM_CR0_ETRFLT_Pos                                (4U)
#define CTRIM_CR0_ETRFLT_Msk                                (0x7UL << CTRIM_CR0_ETRFLT_Pos)
#define CTRIM_CR0_ETRFLT                                    CTRIM_CR0_ETRFLT_Msk
#define CTRIM_CR0_SRC_Pos                                   (8U)
#define CTRIM_CR0_SRC_Msk                                   (0x7UL << CTRIM_CR0_SRC_Pos)
#define CTRIM_CR0_SRC                                       CTRIM_CR0_SRC_Msk

// CTRIM_CR1
#define CTRIM_CR1_EN_Pos                                    (0U)
#define CTRIM_CR1_EN_Msk                                    (0x1UL << CTRIM_CR1_EN_Pos)
#define CTRIM_CR1_EN                                        CTRIM_CR1_EN_Msk
#define CTRIM_CR1_MD_Pos                                    (1U)
#define CTRIM_CR1_MD_Msk                                    (0x3UL << CTRIM_CR1_MD_Pos)
#define CTRIM_CR1_MD                                        CTRIM_CR1_MD_Msk
#define CTRIM_CR1_AUTO_Pos                                  (3U)
#define CTRIM_CR1_AUTO_Msk                                  (0x1UL << CTRIM_CR1_AUTO_Pos)
#define CTRIM_CR1_AUTO                                      CTRIM_CR1_AUTO_Msk
#define CTRIM_CR1_PRS_Pos                                   (4U)
#define CTRIM_CR1_PRS_Msk                                   (0xFUL << CTRIM_CR1_PRS_Pos)
#define CTRIM_CR1_PRS                                       CTRIM_CR1_PRS_Msk
#define CTRIM_CR1_OST_Pos                                   (8U)
#define CTRIM_CR1_OST_Msk                                   (0x1UL << CTRIM_CR1_OST_Pos)
#define CTRIM_CR1_OST                                       CTRIM_CR1_OST_Msk
#define CTRIM_CR1_MDRCH_Pos                                 (9U)
#define CTRIM_CR1_MDRCH_Msk                                 (0x3UL << CTRIM_CR1_MDRCH_Pos)
#define CTRIM_CR1_MDRCH                                     CTRIM_CR1_MDRCH_Msk

// CTRIM_IER
#define CTRIM_IER_UD_Pos                                    (0U)
#define CTRIM_IER_UD_Msk                                    (0x1UL << CTRIM_IER_UD_Pos)
#define CTRIM_IER_UD                                        CTRIM_IER_UD_Msk
#define CTRIM_IER_END_Pos                                   (1U)
#define CTRIM_IER_END_Msk                                   (0x1UL << CTRIM_IER_END_Pos)
#define CTRIM_IER_END                                       CTRIM_IER_END_Msk
#define CTRIM_IER_PS_Pos                                    (2U)
#define CTRIM_IER_PS_Msk                                    (0x1UL << CTRIM_IER_PS_Pos)
#define CTRIM_IER_PS                                        CTRIM_IER_PS_Msk
#define CTRIM_IER_MISS_Pos                                  (3U)
#define CTRIM_IER_MISS_Msk                                  (0x1UL << CTRIM_IER_MISS_Pos)
#define CTRIM_IER_MISS                                      CTRIM_IER_MISS_Msk
#define CTRIM_IER_OV_Pos                                    (4U)
#define CTRIM_IER_OV_Msk                                    (0x1UL << CTRIM_IER_OV_Pos)
#define CTRIM_IER_OV                                        CTRIM_IER_OV_Msk
#define CTRIM_IER_OK_Pos                                    (5U)
#define CTRIM_IER_OK_Msk                                    (0x1UL << CTRIM_IER_OK_Pos)
#define CTRIM_IER_OK                                        CTRIM_IER_OK_Msk

// CTRIM_ISR
#define CTRIM_ISR_UD_Pos                                    (0U)
#define CTRIM_ISR_UD_Msk                                    (0x1UL << CTRIM_ISR_UD_Pos)
#define CTRIM_ISR_UD                                        CTRIM_ISR_UD_Msk
#define CTRIM_ISR_END_Pos                                   (1U)
#define CTRIM_ISR_END_Msk                                   (0x1UL << CTRIM_ISR_END_Pos)
#define CTRIM_ISR_END                                       CTRIM_ISR_END_Msk
#define CTRIM_ISR_PS_Pos                                    (2U)
#define CTRIM_ISR_PS_Msk                                    (0x1UL << CTRIM_ISR_PS_Pos)
#define CTRIM_ISR_PS                                        CTRIM_ISR_PS_Msk
#define CTRIM_ISR_MISS_Pos                                  (3U)
#define CTRIM_ISR_MISS_Msk                                  (0x1UL << CTRIM_ISR_MISS_Pos)
#define CTRIM_ISR_MISS                                      CTRIM_ISR_MISS_Msk
#define CTRIM_ISR_OV_Pos                                    (4U)
#define CTRIM_ISR_OV_Msk                                    (0x1UL << CTRIM_ISR_OV_Pos)
#define CTRIM_ISR_OV                                        CTRIM_ISR_OV_Msk
#define CTRIM_ISR_OK_Pos                                    (5U)
#define CTRIM_ISR_OK_Msk                                    (0x1UL << CTRIM_ISR_OK_Pos)
#define CTRIM_ISR_OK                                        CTRIM_ISR_OK_Msk
#define CTRIM_ISR_DIR_Pos                                   (6U)
#define CTRIM_ISR_DIR_Msk                                   (0x1UL << CTRIM_ISR_DIR_Pos)
#define CTRIM_ISR_DIR                                       CTRIM_ISR_DIR_Msk

// CTRIM_ICR
#define CTRIM_ICR_UD_Pos                                    (0U)
#define CTRIM_ICR_UD_Msk                                    (0x1UL << CTRIM_ICR_UD_Pos)
#define CTRIM_ICR_UD                                        CTRIM_ICR_UD_Msk
#define CTRIM_ICR_END_Pos                                   (1U)
#define CTRIM_ICR_END_Msk                                   (0x1UL << CTRIM_ICR_END_Pos)
#define CTRIM_ICR_END                                       CTRIM_ICR_END_Msk
#define CTRIM_ICR_PS_Pos                                    (2U)
#define CTRIM_ICR_PS_Msk                                    (0x1UL << CTRIM_ICR_PS_Pos)
#define CTRIM_ICR_PS                                        CTRIM_ICR_PS_Msk
#define CTRIM_ICR_MISS_Pos                                  (3U)
#define CTRIM_ICR_MISS_Msk                                  (0x1UL << CTRIM_ICR_MISS_Pos)
#define CTRIM_ICR_MISS                                      CTRIM_ICR_MISS_Msk
#define CTRIM_ICR_OV_Pos                                    (4U)
#define CTRIM_ICR_OV_Msk                                    (0x1UL << CTRIM_ICR_OV_Pos)
#define CTRIM_ICR_OV                                        CTRIM_ICR_OV_Msk
#define CTRIM_ICR_OK_Pos                                    (5U)
#define CTRIM_ICR_OK_Msk                                    (0x1UL << CTRIM_ICR_OK_Pos)
#define CTRIM_ICR_OK                                        CTRIM_ICR_OK_Msk

// CTRIM_FCAP
#define CTRIM_FCAP_FCAP_Pos                                 (0U)
#define CTRIM_FCAP_FCAP_Msk                                 (0xFFFFUL << CTRIM_FCAP_FCAP_Pos)
#define CTRIM_FCAP_FCAP                                     CTRIM_FCAP_FCAP_Msk

// CTRIM_TVAL
#define CTRIM_TVAL_TVAL_Pos                                 (0U)
#define CTRIM_TVAL_TVAL_Msk                                 (0xFFFFUL << CTRIM_TVAL_TVAL_Pos)
#define CTRIM_TVAL_TVAL                                     CTRIM_TVAL_TVAL_Msk

// CTRIM_FLIM
#define CTRIM_FLIM_FLIM_Pos                                 (0U)
#define CTRIM_FLIM_FLIM_Msk                                 (0xFFFUL << CTRIM_FLIM_FLIM_Pos)
#define CTRIM_FLIM_FLIM                                     CTRIM_FLIM_FLIM_Msk



//********************    Bits Define For Peripheral DMAC    ********************//
// DMAC_CONF
#define DMAC_CONF_HALT_Pos                                  (24U)
#define DMAC_CONF_HALT_Msk                                  (0xFUL << DMAC_CONF_HALT_Pos)
#define DMAC_CONF_HALT                                      DMAC_CONF_HALT_Msk
#define DMAC_CONF_PRIO_Pos                                  (28U)
#define DMAC_CONF_PRIO_Msk                                  (0x1UL << DMAC_CONF_PRIO_Pos)
#define DMAC_CONF_PRIO                                      DMAC_CONF_PRIO_Msk
#define DMAC_CONF_EN_Pos                                    (31U)
#define DMAC_CONF_EN_Msk                                    (0x1UL << DMAC_CONF_EN_Pos)
#define DMAC_CONF_EN                                        DMAC_CONF_EN_Msk

// DMAC_CONFA0
#define DMAC_CONFA0_TC_Pos                                  (0U)
#define DMAC_CONFA0_TC_Msk                                  (0xFFFFUL << DMAC_CONFA0_TC_Pos)
#define DMAC_CONFA0_TC                                      DMAC_CONFA0_TC_Msk
#define DMAC_CONFA0_BC_Pos                                  (16U)
#define DMAC_CONFA0_BC_Msk                                  (0xFUL << DMAC_CONFA0_BC_Pos)
#define DMAC_CONFA0_BC                                      DMAC_CONFA0_BC_Msk
#define DMAC_CONFA0_TRISEL_Pos                              (22U)
#define DMAC_CONFA0_TRISEL_Msk                              (0x7FUL << DMAC_CONFA0_TRISEL_Pos)
#define DMAC_CONFA0_TRISEL                                  DMAC_CONFA0_TRISEL_Msk
#define DMAC_CONFA0_ST_Pos                                  (29U)
#define DMAC_CONFA0_ST_Msk                                  (0x1UL << DMAC_CONFA0_ST_Pos)
#define DMAC_CONFA0_ST                                      DMAC_CONFA0_ST_Msk
#define DMAC_CONFA0_PAS_Pos                                 (30U)
#define DMAC_CONFA0_PAS_Msk                                 (0x1UL << DMAC_CONFA0_PAS_Pos)
#define DMAC_CONFA0_PAS                                     DMAC_CONFA0_PAS_Msk
#define DMAC_CONFA0_ENS_Pos                                 (31U)
#define DMAC_CONFA0_ENS_Msk                                 (0x1UL << DMAC_CONFA0_ENS_Pos)
#define DMAC_CONFA0_ENS                                     DMAC_CONFA0_ENS_Msk

// DMAC_CONFB0
#define DMAC_CONFB0_MSK_Pos                                 (0U)
#define DMAC_CONFB0_MSK_Msk                                 (0x1UL << DMAC_CONFB0_MSK_Pos)
#define DMAC_CONFB0_MSK                                     DMAC_CONFB0_MSK_Msk
#define DMAC_CONFB0_STAT_Pos                                (16U)
#define DMAC_CONFB0_STAT_Msk                                (0x7UL << DMAC_CONFB0_STAT_Pos)
#define DMAC_CONFB0_STAT                                    DMAC_CONFB0_STAT_Msk
#define DMAC_CONFB0_FISIE_Pos                               (19U)
#define DMAC_CONFB0_FISIE_Msk                               (0x1UL << DMAC_CONFB0_FISIE_Pos)
#define DMAC_CONFB0_FISIE                                   DMAC_CONFB0_FISIE_Msk
#define DMAC_CONFB0_ERRIE_Pos                               (20U)
#define DMAC_CONFB0_ERRIE_Msk                               (0x1UL << DMAC_CONFB0_ERRIE_Pos)
#define DMAC_CONFB0_ERRIE                                   DMAC_CONFB0_ERRIE_Msk
#define DMAC_CONFB0_RD_Pos                                  (21U)
#define DMAC_CONFB0_RD_Msk                                  (0x1UL << DMAC_CONFB0_RD_Pos)
#define DMAC_CONFB0_RD                                      DMAC_CONFB0_RD_Msk
#define DMAC_CONFB0_RS_Pos                                  (22U)
#define DMAC_CONFB0_RS_Msk                                  (0x1UL << DMAC_CONFB0_RS_Pos)
#define DMAC_CONFB0_RS                                      DMAC_CONFB0_RS_Msk
#define DMAC_CONFB0_RC_Pos                                  (23U)
#define DMAC_CONFB0_RC_Msk                                  (0x1UL << DMAC_CONFB0_RC_Pos)
#define DMAC_CONFB0_RC                                      DMAC_CONFB0_RC_Msk
#define DMAC_CONFB0_FD_Pos                                  (24U)
#define DMAC_CONFB0_FD_Msk                                  (0x1UL << DMAC_CONFB0_FD_Pos)
#define DMAC_CONFB0_FD                                      DMAC_CONFB0_FD_Msk
#define DMAC_CONFB0_FS_Pos                                  (25U)
#define DMAC_CONFB0_FS_Msk                                  (0x1UL << DMAC_CONFB0_FS_Pos)
#define DMAC_CONFB0_FS                                      DMAC_CONFB0_FS_Msk
#define DMAC_CONFB0_WIDTH_Pos                               (26U)
#define DMAC_CONFB0_WIDTH_Msk                               (0x3UL << DMAC_CONFB0_WIDTH_Pos)
#define DMAC_CONFB0_WIDTH                                   DMAC_CONFB0_WIDTH_Msk
#define DMAC_CONFB0_MODE_Pos                                (28U)
#define DMAC_CONFB0_MODE_Msk                                (0x3UL << DMAC_CONFB0_MODE_Pos)
#define DMAC_CONFB0_MODE                                    DMAC_CONFB0_MODE_Msk

// DMAC_SRCADR0
#define DMAC_SRCADR0_SRCADR_Pos                             (0U)
#define DMAC_SRCADR0_SRCADR_Msk                             (0xFFFFFFFFUL << DMAC_SRCADR0_SRCADR_Pos)
#define DMAC_SRCADR0_SRCADR                                 DMAC_SRCADR0_SRCADR_Msk

// DMAC_DSTADR0
#define DMAC_DSTADR0_DSTADR_Pos                             (0U)
#define DMAC_DSTADR0_DSTADR_Msk                             (0xFFFFFFFFUL << DMAC_DSTADR0_DSTADR_Pos)
#define DMAC_DSTADR0_DSTADR                                 DMAC_DSTADR0_DSTADR_Msk

// DMAC_CONFA1
#define DMAC_CONFA1_TC_Pos                                  (0U)
#define DMAC_CONFA1_TC_Msk                                  (0xFFFFUL << DMAC_CONFA1_TC_Pos)
#define DMAC_CONFA1_TC                                      DMAC_CONFA1_TC_Msk
#define DMAC_CONFA1_BC_Pos                                  (16U)
#define DMAC_CONFA1_BC_Msk                                  (0xFUL << DMAC_CONFA1_BC_Pos)
#define DMAC_CONFA1_BC                                      DMAC_CONFA1_BC_Msk
#define DMAC_CONFA1_TRISEL_Pos                              (22U)
#define DMAC_CONFA1_TRISEL_Msk                              (0x7FUL << DMAC_CONFA1_TRISEL_Pos)
#define DMAC_CONFA1_TRISEL                                  DMAC_CONFA1_TRISEL_Msk
#define DMAC_CONFA1_ST_Pos                                  (29U)
#define DMAC_CONFA1_ST_Msk                                  (0x1UL << DMAC_CONFA1_ST_Pos)
#define DMAC_CONFA1_ST                                      DMAC_CONFA1_ST_Msk
#define DMAC_CONFA1_PAS_Pos                                 (30U)
#define DMAC_CONFA1_PAS_Msk                                 (0x1UL << DMAC_CONFA1_PAS_Pos)
#define DMAC_CONFA1_PAS                                     DMAC_CONFA1_PAS_Msk
#define DMAC_CONFA1_ENS_Pos                                 (31U)
#define DMAC_CONFA1_ENS_Msk                                 (0x1UL << DMAC_CONFA1_ENS_Pos)
#define DMAC_CONFA1_ENS                                     DMAC_CONFA1_ENS_Msk

// DMAC_CONFB1
#define DMAC_CONFB1_MSK_Pos                                 (0U)
#define DMAC_CONFB1_MSK_Msk                                 (0x1UL << DMAC_CONFB1_MSK_Pos)
#define DMAC_CONFB1_MSK                                     DMAC_CONFB1_MSK_Msk
#define DMAC_CONFB1_STAT_Pos                                (16U)
#define DMAC_CONFB1_STAT_Msk                                (0x7UL << DMAC_CONFB1_STAT_Pos)
#define DMAC_CONFB1_STAT                                    DMAC_CONFB1_STAT_Msk
#define DMAC_CONFB1_FISIE_Pos                               (19U)
#define DMAC_CONFB1_FISIE_Msk                               (0x1UL << DMAC_CONFB1_FISIE_Pos)
#define DMAC_CONFB1_FISIE                                   DMAC_CONFB1_FISIE_Msk
#define DMAC_CONFB1_ERRIE_Pos                               (20U)
#define DMAC_CONFB1_ERRIE_Msk                               (0x1UL << DMAC_CONFB1_ERRIE_Pos)
#define DMAC_CONFB1_ERRIE                                   DMAC_CONFB1_ERRIE_Msk
#define DMAC_CONFB1_RD_Pos                                  (21U)
#define DMAC_CONFB1_RD_Msk                                  (0x1UL << DMAC_CONFB1_RD_Pos)
#define DMAC_CONFB1_RD                                      DMAC_CONFB1_RD_Msk
#define DMAC_CONFB1_RS_Pos                                  (22U)
#define DMAC_CONFB1_RS_Msk                                  (0x1UL << DMAC_CONFB1_RS_Pos)
#define DMAC_CONFB1_RS                                      DMAC_CONFB1_RS_Msk
#define DMAC_CONFB1_RC_Pos                                  (23U)
#define DMAC_CONFB1_RC_Msk                                  (0x1UL << DMAC_CONFB1_RC_Pos)
#define DMAC_CONFB1_RC                                      DMAC_CONFB1_RC_Msk
#define DMAC_CONFB1_FD_Pos                                  (24U)
#define DMAC_CONFB1_FD_Msk                                  (0x1UL << DMAC_CONFB1_FD_Pos)
#define DMAC_CONFB1_FD                                      DMAC_CONFB1_FD_Msk
#define DMAC_CONFB1_FS_Pos                                  (25U)
#define DMAC_CONFB1_FS_Msk                                  (0x1UL << DMAC_CONFB1_FS_Pos)
#define DMAC_CONFB1_FS                                      DMAC_CONFB1_FS_Msk
#define DMAC_CONFB1_WIDTH_Pos                               (26U)
#define DMAC_CONFB1_WIDTH_Msk                               (0x3UL << DMAC_CONFB1_WIDTH_Pos)
#define DMAC_CONFB1_WIDTH                                   DMAC_CONFB1_WIDTH_Msk
#define DMAC_CONFB1_MODE_Pos                                (28U)
#define DMAC_CONFB1_MODE_Msk                                (0x3UL << DMAC_CONFB1_MODE_Pos)
#define DMAC_CONFB1_MODE                                    DMAC_CONFB1_MODE_Msk

// DMAC_SRCADR1
#define DMAC_SRCADR1_SRCADR_Pos                             (0U)
#define DMAC_SRCADR1_SRCADR_Msk                             (0xFFFFFFFFUL << DMAC_SRCADR1_SRCADR_Pos)
#define DMAC_SRCADR1_SRCADR                                 DMAC_SRCADR1_SRCADR_Msk

// DMAC_DSTADR1
#define DMAC_DSTADR1_DSTADR_Pos                             (0U)
#define DMAC_DSTADR1_DSTADR_Msk                             (0xFFFFFFFFUL << DMAC_DSTADR1_DSTADR_Pos)
#define DMAC_DSTADR1_DSTADR                                 DMAC_DSTADR1_DSTADR_Msk

// DMAC_CONFA2
#define DMAC_CONFA2_TC_Pos                                  (0U)
#define DMAC_CONFA2_TC_Msk                                  (0xFFFFUL << DMAC_CONFA2_TC_Pos)
#define DMAC_CONFA2_TC                                      DMAC_CONFA2_TC_Msk
#define DMAC_CONFA2_BC_Pos                                  (16U)
#define DMAC_CONFA2_BC_Msk                                  (0xFUL << DMAC_CONFA2_BC_Pos)
#define DMAC_CONFA2_BC                                      DMAC_CONFA2_BC_Msk
#define DMAC_CONFA2_TRISEL_Pos                              (22U)
#define DMAC_CONFA2_TRISEL_Msk                              (0x7FUL << DMAC_CONFA2_TRISEL_Pos)
#define DMAC_CONFA2_TRISEL                                  DMAC_CONFA2_TRISEL_Msk
#define DMAC_CONFA2_ST_Pos                                  (29U)
#define DMAC_CONFA2_ST_Msk                                  (0x1UL << DMAC_CONFA2_ST_Pos)
#define DMAC_CONFA2_ST                                      DMAC_CONFA2_ST_Msk
#define DMAC_CONFA2_PAS_Pos                                 (30U)
#define DMAC_CONFA2_PAS_Msk                                 (0x1UL << DMAC_CONFA2_PAS_Pos)
#define DMAC_CONFA2_PAS                                     DMAC_CONFA2_PAS_Msk
#define DMAC_CONFA2_ENS_Pos                                 (31U)
#define DMAC_CONFA2_ENS_Msk                                 (0x1UL << DMAC_CONFA2_ENS_Pos)
#define DMAC_CONFA2_ENS                                     DMAC_CONFA2_ENS_Msk

// DMAC_CONFB2
#define DMAC_CONFB2_MSK_Pos                                 (0U)
#define DMAC_CONFB2_MSK_Msk                                 (0x1UL << DMAC_CONFB2_MSK_Pos)
#define DMAC_CONFB2_MSK                                     DMAC_CONFB2_MSK_Msk
#define DMAC_CONFB2_STAT_Pos                                (16U)
#define DMAC_CONFB2_STAT_Msk                                (0x7UL << DMAC_CONFB2_STAT_Pos)
#define DMAC_CONFB2_STAT                                    DMAC_CONFB2_STAT_Msk
#define DMAC_CONFB2_FISIE_Pos                               (19U)
#define DMAC_CONFB2_FISIE_Msk                               (0x1UL << DMAC_CONFB2_FISIE_Pos)
#define DMAC_CONFB2_FISIE                                   DMAC_CONFB2_FISIE_Msk
#define DMAC_CONFB2_ERRIE_Pos                               (20U)
#define DMAC_CONFB2_ERRIE_Msk                               (0x1UL << DMAC_CONFB2_ERRIE_Pos)
#define DMAC_CONFB2_ERRIE                                   DMAC_CONFB2_ERRIE_Msk
#define DMAC_CONFB2_RD_Pos                                  (21U)
#define DMAC_CONFB2_RD_Msk                                  (0x1UL << DMAC_CONFB2_RD_Pos)
#define DMAC_CONFB2_RD                                      DMAC_CONFB2_RD_Msk
#define DMAC_CONFB2_RS_Pos                                  (22U)
#define DMAC_CONFB2_RS_Msk                                  (0x1UL << DMAC_CONFB2_RS_Pos)
#define DMAC_CONFB2_RS                                      DMAC_CONFB2_RS_Msk
#define DMAC_CONFB2_RC_Pos                                  (23U)
#define DMAC_CONFB2_RC_Msk                                  (0x1UL << DMAC_CONFB2_RC_Pos)
#define DMAC_CONFB2_RC                                      DMAC_CONFB2_RC_Msk
#define DMAC_CONFB2_FD_Pos                                  (24U)
#define DMAC_CONFB2_FD_Msk                                  (0x1UL << DMAC_CONFB2_FD_Pos)
#define DMAC_CONFB2_FD                                      DMAC_CONFB2_FD_Msk
#define DMAC_CONFB2_FS_Pos                                  (25U)
#define DMAC_CONFB2_FS_Msk                                  (0x1UL << DMAC_CONFB2_FS_Pos)
#define DMAC_CONFB2_FS                                      DMAC_CONFB2_FS_Msk
#define DMAC_CONFB2_WIDTH_Pos                               (26U)
#define DMAC_CONFB2_WIDTH_Msk                               (0x3UL << DMAC_CONFB2_WIDTH_Pos)
#define DMAC_CONFB2_WIDTH                                   DMAC_CONFB2_WIDTH_Msk
#define DMAC_CONFB2_MODE_Pos                                (28U)
#define DMAC_CONFB2_MODE_Msk                                (0x3UL << DMAC_CONFB2_MODE_Pos)
#define DMAC_CONFB2_MODE                                    DMAC_CONFB2_MODE_Msk

// DMAC_SRCADR2
#define DMAC_SRCADR2_SRCADR_Pos                             (0U)
#define DMAC_SRCADR2_SRCADR_Msk                             (0xFFFFFFFFUL << DMAC_SRCADR2_SRCADR_Pos)
#define DMAC_SRCADR2_SRCADR                                 DMAC_SRCADR2_SRCADR_Msk

// DMAC_DSTADR2
#define DMAC_DSTADR2_DSTADR_Pos                             (0U)
#define DMAC_DSTADR2_DSTADR_Msk                             (0xFFFFFFFFUL << DMAC_DSTADR2_DSTADR_Pos)
#define DMAC_DSTADR2_DSTADR                                 DMAC_DSTADR2_DSTADR_Msk

// DMAC_CONFA3
#define DMAC_CONFA3_TC_Pos                                  (0U)
#define DMAC_CONFA3_TC_Msk                                  (0xFFFFUL << DMAC_CONFA3_TC_Pos)
#define DMAC_CONFA3_TC                                      DMAC_CONFA3_TC_Msk
#define DMAC_CONFA3_BC_Pos                                  (16U)
#define DMAC_CONFA3_BC_Msk                                  (0xFUL << DMAC_CONFA3_BC_Pos)
#define DMAC_CONFA3_BC                                      DMAC_CONFA3_BC_Msk
#define DMAC_CONFA3_TRISEL_Pos                              (22U)
#define DMAC_CONFA3_TRISEL_Msk                              (0x7FUL << DMAC_CONFA3_TRISEL_Pos)
#define DMAC_CONFA3_TRISEL                                  DMAC_CONFA3_TRISEL_Msk
#define DMAC_CONFA3_ST_Pos                                  (29U)
#define DMAC_CONFA3_ST_Msk                                  (0x1UL << DMAC_CONFA3_ST_Pos)
#define DMAC_CONFA3_ST                                      DMAC_CONFA3_ST_Msk
#define DMAC_CONFA3_PAS_Pos                                 (30U)
#define DMAC_CONFA3_PAS_Msk                                 (0x1UL << DMAC_CONFA3_PAS_Pos)
#define DMAC_CONFA3_PAS                                     DMAC_CONFA3_PAS_Msk
#define DMAC_CONFA3_ENS_Pos                                 (31U)
#define DMAC_CONFA3_ENS_Msk                                 (0x1UL << DMAC_CONFA3_ENS_Pos)
#define DMAC_CONFA3_ENS                                     DMAC_CONFA3_ENS_Msk

// DMAC_CONFB3
#define DMAC_CONFB3_MSK_Pos                                 (0U)
#define DMAC_CONFB3_MSK_Msk                                 (0x1UL << DMAC_CONFB3_MSK_Pos)
#define DMAC_CONFB3_MSK                                     DMAC_CONFB3_MSK_Msk
#define DMAC_CONFB3_STAT_Pos                                (16U)
#define DMAC_CONFB3_STAT_Msk                                (0x7UL << DMAC_CONFB3_STAT_Pos)
#define DMAC_CONFB3_STAT                                    DMAC_CONFB3_STAT_Msk
#define DMAC_CONFB3_FISIE_Pos                               (19U)
#define DMAC_CONFB3_FISIE_Msk                               (0x1UL << DMAC_CONFB3_FISIE_Pos)
#define DMAC_CONFB3_FISIE                                   DMAC_CONFB3_FISIE_Msk
#define DMAC_CONFB3_ERRIE_Pos                               (20U)
#define DMAC_CONFB3_ERRIE_Msk                               (0x1UL << DMAC_CONFB3_ERRIE_Pos)
#define DMAC_CONFB3_ERRIE                                   DMAC_CONFB3_ERRIE_Msk
#define DMAC_CONFB3_RD_Pos                                  (21U)
#define DMAC_CONFB3_RD_Msk                                  (0x1UL << DMAC_CONFB3_RD_Pos)
#define DMAC_CONFB3_RD                                      DMAC_CONFB3_RD_Msk
#define DMAC_CONFB3_RS_Pos                                  (22U)
#define DMAC_CONFB3_RS_Msk                                  (0x1UL << DMAC_CONFB3_RS_Pos)
#define DMAC_CONFB3_RS                                      DMAC_CONFB3_RS_Msk
#define DMAC_CONFB3_RC_Pos                                  (23U)
#define DMAC_CONFB3_RC_Msk                                  (0x1UL << DMAC_CONFB3_RC_Pos)
#define DMAC_CONFB3_RC                                      DMAC_CONFB3_RC_Msk
#define DMAC_CONFB3_FD_Pos                                  (24U)
#define DMAC_CONFB3_FD_Msk                                  (0x1UL << DMAC_CONFB3_FD_Pos)
#define DMAC_CONFB3_FD                                      DMAC_CONFB3_FD_Msk
#define DMAC_CONFB3_FS_Pos                                  (25U)
#define DMAC_CONFB3_FS_Msk                                  (0x1UL << DMAC_CONFB3_FS_Pos)
#define DMAC_CONFB3_FS                                      DMAC_CONFB3_FS_Msk
#define DMAC_CONFB3_WIDTH_Pos                               (26U)
#define DMAC_CONFB3_WIDTH_Msk                               (0x3UL << DMAC_CONFB3_WIDTH_Pos)
#define DMAC_CONFB3_WIDTH                                   DMAC_CONFB3_WIDTH_Msk
#define DMAC_CONFB3_MODE_Pos                                (28U)
#define DMAC_CONFB3_MODE_Msk                                (0x3UL << DMAC_CONFB3_MODE_Pos)
#define DMAC_CONFB3_MODE                                    DMAC_CONFB3_MODE_Msk

// DMAC_SRCADR3
#define DMAC_SRCADR3_SRCADR_Pos                             (0U)
#define DMAC_SRCADR3_SRCADR_Msk                             (0xFFFFFFFFUL << DMAC_SRCADR3_SRCADR_Pos)
#define DMAC_SRCADR3_SRCADR                                 DMAC_SRCADR3_SRCADR_Msk

// DMAC_DSTADR3
#define DMAC_DSTADR3_DSTADR_Pos                             (0U)
#define DMAC_DSTADR3_DSTADR_Msk                             (0xFFFFFFFFUL << DMAC_DSTADR3_DSTADR_Pos)
#define DMAC_DSTADR3_DSTADR                                 DMAC_DSTADR3_DSTADR_Msk

// DMAC_CONFA4
#define DMAC_CONFA4_TC_Pos                                  (0U)
#define DMAC_CONFA4_TC_Msk                                  (0xFFFFUL << DMAC_CONFA4_TC_Pos)
#define DMAC_CONFA4_TC                                      DMAC_CONFA4_TC_Msk
#define DMAC_CONFA4_BC_Pos                                  (16U)
#define DMAC_CONFA4_BC_Msk                                  (0xFUL << DMAC_CONFA4_BC_Pos)
#define DMAC_CONFA4_BC                                      DMAC_CONFA4_BC_Msk
#define DMAC_CONFA4_TRISEL_Pos                              (22U)
#define DMAC_CONFA4_TRISEL_Msk                              (0x7FUL << DMAC_CONFA4_TRISEL_Pos)
#define DMAC_CONFA4_TRISEL                                  DMAC_CONFA4_TRISEL_Msk
#define DMAC_CONFA4_ST_Pos                                  (29U)
#define DMAC_CONFA4_ST_Msk                                  (0x1UL << DMAC_CONFA4_ST_Pos)
#define DMAC_CONFA4_ST                                      DMAC_CONFA4_ST_Msk
#define DMAC_CONFA4_PAS_Pos                                 (30U)
#define DMAC_CONFA4_PAS_Msk                                 (0x1UL << DMAC_CONFA4_PAS_Pos)
#define DMAC_CONFA4_PAS                                     DMAC_CONFA4_PAS_Msk
#define DMAC_CONFA4_ENS_Pos                                 (31U)
#define DMAC_CONFA4_ENS_Msk                                 (0x1UL << DMAC_CONFA4_ENS_Pos)
#define DMAC_CONFA4_ENS                                     DMAC_CONFA4_ENS_Msk

// DMAC_CONFB4
#define DMAC_CONFB4_MSK_Pos                                 (0U)
#define DMAC_CONFB4_MSK_Msk                                 (0x1UL << DMAC_CONFB4_MSK_Pos)
#define DMAC_CONFB4_MSK                                     DMAC_CONFB4_MSK_Msk
#define DMAC_CONFB4_STAT_Pos                                (16U)
#define DMAC_CONFB4_STAT_Msk                                (0x7UL << DMAC_CONFB4_STAT_Pos)
#define DMAC_CONFB4_STAT                                    DMAC_CONFB4_STAT_Msk
#define DMAC_CONFB4_FISIE_Pos                               (19U)
#define DMAC_CONFB4_FISIE_Msk                               (0x1UL << DMAC_CONFB4_FISIE_Pos)
#define DMAC_CONFB4_FISIE                                   DMAC_CONFB4_FISIE_Msk
#define DMAC_CONFB4_ERRIE_Pos                               (20U)
#define DMAC_CONFB4_ERRIE_Msk                               (0x1UL << DMAC_CONFB4_ERRIE_Pos)
#define DMAC_CONFB4_ERRIE                                   DMAC_CONFB4_ERRIE_Msk
#define DMAC_CONFB4_RD_Pos                                  (21U)
#define DMAC_CONFB4_RD_Msk                                  (0x1UL << DMAC_CONFB4_RD_Pos)
#define DMAC_CONFB4_RD                                      DMAC_CONFB4_RD_Msk
#define DMAC_CONFB4_RS_Pos                                  (22U)
#define DMAC_CONFB4_RS_Msk                                  (0x1UL << DMAC_CONFB4_RS_Pos)
#define DMAC_CONFB4_RS                                      DMAC_CONFB4_RS_Msk
#define DMAC_CONFB4_RC_Pos                                  (23U)
#define DMAC_CONFB4_RC_Msk                                  (0x1UL << DMAC_CONFB4_RC_Pos)
#define DMAC_CONFB4_RC                                      DMAC_CONFB4_RC_Msk
#define DMAC_CONFB4_FD_Pos                                  (24U)
#define DMAC_CONFB4_FD_Msk                                  (0x1UL << DMAC_CONFB4_FD_Pos)
#define DMAC_CONFB4_FD                                      DMAC_CONFB4_FD_Msk
#define DMAC_CONFB4_FS_Pos                                  (25U)
#define DMAC_CONFB4_FS_Msk                                  (0x1UL << DMAC_CONFB4_FS_Pos)
#define DMAC_CONFB4_FS                                      DMAC_CONFB4_FS_Msk
#define DMAC_CONFB4_WIDTH_Pos                               (26U)
#define DMAC_CONFB4_WIDTH_Msk                               (0x3UL << DMAC_CONFB4_WIDTH_Pos)
#define DMAC_CONFB4_WIDTH                                   DMAC_CONFB4_WIDTH_Msk
#define DMAC_CONFB4_MODE_Pos                                (28U)
#define DMAC_CONFB4_MODE_Msk                                (0x3UL << DMAC_CONFB4_MODE_Pos)
#define DMAC_CONFB4_MODE                                    DMAC_CONFB4_MODE_Msk

// DMAC_SRCADR4
#define DMAC_SRCADR4_SRCADR_Pos                             (0U)
#define DMAC_SRCADR4_SRCADR_Msk                             (0xFFFFFFFFUL << DMAC_SRCADR4_SRCADR_Pos)
#define DMAC_SRCADR4_SRCADR                                 DMAC_SRCADR4_SRCADR_Msk

// DMAC_DSTADR4
#define DMAC_DSTADR4_DSTADR_Pos                             (0U)
#define DMAC_DSTADR4_DSTADR_Msk                             (0xFFFFFFFFUL << DMAC_DSTADR4_DSTADR_Pos)
#define DMAC_DSTADR4_DSTADR                                 DMAC_DSTADR4_DSTADR_Msk

// DMAC_CONFA5
#define DMAC_CONFA5_TC_Pos                                  (0U)
#define DMAC_CONFA5_TC_Msk                                  (0xFFFFUL << DMAC_CONFA5_TC_Pos)
#define DMAC_CONFA5_TC                                      DMAC_CONFA5_TC_Msk
#define DMAC_CONFA5_BC_Pos                                  (16U)
#define DMAC_CONFA5_BC_Msk                                  (0xFUL << DMAC_CONFA5_BC_Pos)
#define DMAC_CONFA5_BC                                      DMAC_CONFA5_BC_Msk
#define DMAC_CONFA5_TRISEL_Pos                              (22U)
#define DMAC_CONFA5_TRISEL_Msk                              (0x7FUL << DMAC_CONFA5_TRISEL_Pos)
#define DMAC_CONFA5_TRISEL                                  DMAC_CONFA5_TRISEL_Msk
#define DMAC_CONFA5_ST_Pos                                  (29U)
#define DMAC_CONFA5_ST_Msk                                  (0x1UL << DMAC_CONFA5_ST_Pos)
#define DMAC_CONFA5_ST                                      DMAC_CONFA5_ST_Msk
#define DMAC_CONFA5_PAS_Pos                                 (30U)
#define DMAC_CONFA5_PAS_Msk                                 (0x1UL << DMAC_CONFA5_PAS_Pos)
#define DMAC_CONFA5_PAS                                     DMAC_CONFA5_PAS_Msk
#define DMAC_CONFA5_ENS_Pos                                 (31U)
#define DMAC_CONFA5_ENS_Msk                                 (0x1UL << DMAC_CONFA5_ENS_Pos)
#define DMAC_CONFA5_ENS                                     DMAC_CONFA5_ENS_Msk

// DMAC_CONFB5
#define DMAC_CONFB5_MSK_Pos                                 (0U)
#define DMAC_CONFB5_MSK_Msk                                 (0x1UL << DMAC_CONFB5_MSK_Pos)
#define DMAC_CONFB5_MSK                                     DMAC_CONFB5_MSK_Msk
#define DMAC_CONFB5_STAT_Pos                                (16U)
#define DMAC_CONFB5_STAT_Msk                                (0x7UL << DMAC_CONFB5_STAT_Pos)
#define DMAC_CONFB5_STAT                                    DMAC_CONFB5_STAT_Msk
#define DMAC_CONFB5_FISIE_Pos                               (19U)
#define DMAC_CONFB5_FISIE_Msk                               (0x1UL << DMAC_CONFB5_FISIE_Pos)
#define DMAC_CONFB5_FISIE                                   DMAC_CONFB5_FISIE_Msk
#define DMAC_CONFB5_ERRIE_Pos                               (20U)
#define DMAC_CONFB5_ERRIE_Msk                               (0x1UL << DMAC_CONFB5_ERRIE_Pos)
#define DMAC_CONFB5_ERRIE                                   DMAC_CONFB5_ERRIE_Msk
#define DMAC_CONFB5_RD_Pos                                  (21U)
#define DMAC_CONFB5_RD_Msk                                  (0x1UL << DMAC_CONFB5_RD_Pos)
#define DMAC_CONFB5_RD                                      DMAC_CONFB5_RD_Msk
#define DMAC_CONFB5_RS_Pos                                  (22U)
#define DMAC_CONFB5_RS_Msk                                  (0x1UL << DMAC_CONFB5_RS_Pos)
#define DMAC_CONFB5_RS                                      DMAC_CONFB5_RS_Msk
#define DMAC_CONFB5_RC_Pos                                  (23U)
#define DMAC_CONFB5_RC_Msk                                  (0x1UL << DMAC_CONFB5_RC_Pos)
#define DMAC_CONFB5_RC                                      DMAC_CONFB5_RC_Msk
#define DMAC_CONFB5_FD_Pos                                  (24U)
#define DMAC_CONFB5_FD_Msk                                  (0x1UL << DMAC_CONFB5_FD_Pos)
#define DMAC_CONFB5_FD                                      DMAC_CONFB5_FD_Msk
#define DMAC_CONFB5_FS_Pos                                  (25U)
#define DMAC_CONFB5_FS_Msk                                  (0x1UL << DMAC_CONFB5_FS_Pos)
#define DMAC_CONFB5_FS                                      DMAC_CONFB5_FS_Msk
#define DMAC_CONFB5_WIDTH_Pos                               (26U)
#define DMAC_CONFB5_WIDTH_Msk                               (0x3UL << DMAC_CONFB5_WIDTH_Pos)
#define DMAC_CONFB5_WIDTH                                   DMAC_CONFB5_WIDTH_Msk
#define DMAC_CONFB5_MODE_Pos                                (28U)
#define DMAC_CONFB5_MODE_Msk                                (0x3UL << DMAC_CONFB5_MODE_Pos)
#define DMAC_CONFB5_MODE                                    DMAC_CONFB5_MODE_Msk

// DMAC_SRCADR5
#define DMAC_SRCADR5_SRCADR_Pos                             (0U)
#define DMAC_SRCADR5_SRCADR_Msk                             (0xFFFFFFFFUL << DMAC_SRCADR5_SRCADR_Pos)
#define DMAC_SRCADR5_SRCADR                                 DMAC_SRCADR5_SRCADR_Msk

// DMAC_DSTADR5
#define DMAC_DSTADR5_DSTADR_Pos                             (0U)
#define DMAC_DSTADR5_DSTADR_Msk                             (0xFFFFFFFFUL << DMAC_DSTADR5_DSTADR_Pos)
#define DMAC_DSTADR5_DSTADR                                 DMAC_DSTADR5_DSTADR_Msk



//********************    Bits Define For Peripheral EAU    ********************//
// EAU_CSR
#define EAU_CSR_MODE_Pos                                    (0U)
#define EAU_CSR_MODE_Msk                                    (0x3UL << EAU_CSR_MODE_Pos)
#define EAU_CSR_MODE                                        EAU_CSR_MODE_Msk
#define EAU_CSR_OVR_Pos                                     (2U)
#define EAU_CSR_OVR_Msk                                     (0x1UL << EAU_CSR_OVR_Pos)
#define EAU_CSR_OVR                                         EAU_CSR_OVR_Msk
#define EAU_CSR_ZERO_Pos                                    (3U)
#define EAU_CSR_ZERO_Msk                                    (0x1UL << EAU_CSR_ZERO_Pos)
#define EAU_CSR_ZERO                                        EAU_CSR_ZERO_Msk
#define EAU_CSR_BUSY_Pos                                    (4U)
#define EAU_CSR_BUSY_Msk                                    (0x1UL << EAU_CSR_BUSY_Pos)
#define EAU_CSR_BUSY                                        EAU_CSR_BUSY_Msk

// EAU_DIVIDEND
#define EAU_DIVIDEND_DIVIDEND_Pos                           (0U)
#define EAU_DIVIDEND_DIVIDEND_Msk                           (0xFFFFFFFFUL << EAU_DIVIDEND_DIVIDEND_Pos)
#define EAU_DIVIDEND_DIVIDEND                               EAU_DIVIDEND_DIVIDEND_Msk

// EAU_DIVISOR
#define EAU_DIVISOR_DIVISOR_Pos                             (0U)
#define EAU_DIVISOR_DIVISOR_Msk                             (0xFFFFFFFFUL << EAU_DIVISOR_DIVISOR_Pos)
#define EAU_DIVISOR_DIVISOR                                 EAU_DIVISOR_DIVISOR_Msk

// EAU_QUOTIENT
#define EAU_QUOTIENT_QUOTIENT_Pos                           (0U)
#define EAU_QUOTIENT_QUOTIENT_Msk                           (0xFFFFFFFFUL << EAU_QUOTIENT_QUOTIENT_Pos)
#define EAU_QUOTIENT_QUOTIENT                               EAU_QUOTIENT_QUOTIENT_Msk

// EAU_REMAINDER
#define EAU_REMAINDER_REMAINDER_Pos                         (0U)
#define EAU_REMAINDER_REMAINDER_Msk                         (0xFFFFFFFFUL << EAU_REMAINDER_REMAINDER_Pos)
#define EAU_REMAINDER_REMAINDER                             EAU_REMAINDER_REMAINDER_Msk



//********************    Bits Define For Peripheral FLASH    ********************//
// FLASH_CR
#define FLASH_CR_OP_Pos                                     (0U)
#define FLASH_CR_OP_Msk                                     (0x7UL << FLASH_CR_OP_Pos)
#define FLASH_CR_OP                                         FLASH_CR_OP_Msk
#define FLASH_CR_FWUP_Pos                                   (4U)
#define FLASH_CR_FWUP_Msk                                   (0x1UL << FLASH_CR_FWUP_Pos)
#define FLASH_CR_FWUP                                       FLASH_CR_FWUP_Msk
#define FLASH_CR_ROMD_Pos                                   (5U)
#define FLASH_CR_ROMD_Msk                                   (0x1UL << FLASH_CR_ROMD_Pos)
#define FLASH_CR_ROMD                                       FLASH_CR_ROMD_Msk
#define FLASH_CR_DPSTBEN_Pos                                (7U)
#define FLASH_CR_DPSTBEN_Msk                                (0x1UL << FLASH_CR_DPSTBEN_Pos)
#define FLASH_CR_DPSTBEN                                    FLASH_CR_DPSTBEN_Msk

// FLASH_WAIT
#define FLASH_WAIT_WAIT_Pos                                 (0U)
#define FLASH_WAIT_WAIT_Msk                                 (0x7UL << FLASH_WAIT_WAIT_Pos)
#define FLASH_WAIT_WAIT                                     FLASH_WAIT_WAIT_Msk

// FLASH_LOCKST
#define FLASH_LOCKST_STATE_Pos                              (0U)
#define FLASH_LOCKST_STATE_Msk                              (0x3UL << FLASH_LOCKST_STATE_Pos)
#define FLASH_LOCKST_STATE                                  FLASH_LOCKST_STATE_Msk

// FLASH_IER
#define FLASH_IER_PC_Pos                                    (0U)
#define FLASH_IER_PC_Msk                                    (0x1UL << FLASH_IER_PC_Pos)
#define FLASH_IER_PC                                        FLASH_IER_PC_Msk
#define FLASH_IER_PROT_Pos                                  (1U)
#define FLASH_IER_PROT_Msk                                  (0x1UL << FLASH_IER_PROT_Pos)
#define FLASH_IER_PROT                                      FLASH_IER_PROT_Msk

// FLASH_IFR
#define FLASH_IFR_PC_Pos                                    (0U)
#define FLASH_IFR_PC_Msk                                    (0x1UL << FLASH_IFR_PC_Pos)
#define FLASH_IFR_PC                                        FLASH_IFR_PC_Msk
#define FLASH_IFR_PROT_Pos                                  (1U)
#define FLASH_IFR_PROT_Msk                                  (0x1UL << FLASH_IFR_PROT_Pos)
#define FLASH_IFR_PROT                                      FLASH_IFR_PROT_Msk
#define FLASH_IFR_BUSY_Pos                                  (4U)
#define FLASH_IFR_BUSY_Msk                                  (0x1UL << FLASH_IFR_BUSY_Pos)
#define FLASH_IFR_BUSY                                      FLASH_IFR_BUSY_Msk
#define FLASH_IFR_CFDONE_Pos                                (5U)
#define FLASH_IFR_CFDONE_Msk                                (0x1UL << FLASH_IFR_CFDONE_Pos)
#define FLASH_IFR_CFDONE                                    FLASH_IFR_CFDONE_Msk

// FLASH_ICR
#define FLASH_ICR_PC_Pos                                    (0U)
#define FLASH_ICR_PC_Msk                                    (0x1UL << FLASH_ICR_PC_Pos)
#define FLASH_ICR_PC                                        FLASH_ICR_PC_Msk
#define FLASH_ICR_PROT_Pos                                  (1U)
#define FLASH_ICR_PROT_Msk                                  (0x1UL << FLASH_ICR_PROT_Pos)
#define FLASH_ICR_PROT                                      FLASH_ICR_PROT_Msk

// FLASH_BYPASS
#define FLASH_BYPASS_BYSEQ_Pos                              (0U)
#define FLASH_BYPASS_BYSEQ_Msk                              (0xFFFFUL << FLASH_BYPASS_BYSEQ_Pos)
#define FLASH_BYPASS_BYSEQ                                  FLASH_BYPASS_BYSEQ_Msk

// FLASH_SLOCK0
#define FLASH_SLOCK0_SLOCK_Pos                              (0U)
#define FLASH_SLOCK0_SLOCK_Msk                              (0xFFFFFFFFUL << FLASH_SLOCK0_SLOCK_Pos)
#define FLASH_SLOCK0_SLOCK                                  FLASH_SLOCK0_SLOCK_Msk

// FLASH_SLOCK1
#define FLASH_SLOCK1_SLOCK_Pos                              (0U)
#define FLASH_SLOCK1_SLOCK_Msk                              (0xFFFFFFFFUL << FLASH_SLOCK1_SLOCK_Pos)
#define FLASH_SLOCK1_SLOCK                                  FLASH_SLOCK1_SLOCK_Msk



//********************    Bits Define For Peripheral GPIO    ********************//
// GPIO_ADS
#define GPIO_ADS_PIN0_Pos                                   (0U)
#define GPIO_ADS_PIN0_Msk                                   (0x1UL << GPIO_ADS_PIN0_Pos)
#define GPIO_ADS_PIN0                                       GPIO_ADS_PIN0_Msk
#define GPIO_ADS_PIN1_Pos                                   (1U)
#define GPIO_ADS_PIN1_Msk                                   (0x1UL << GPIO_ADS_PIN1_Pos)
#define GPIO_ADS_PIN1                                       GPIO_ADS_PIN1_Msk
#define GPIO_ADS_PIN2_Pos                                   (2U)
#define GPIO_ADS_PIN2_Msk                                   (0x1UL << GPIO_ADS_PIN2_Pos)
#define GPIO_ADS_PIN2                                       GPIO_ADS_PIN2_Msk
#define GPIO_ADS_PIN3_Pos                                   (3U)
#define GPIO_ADS_PIN3_Msk                                   (0x1UL << GPIO_ADS_PIN3_Pos)
#define GPIO_ADS_PIN3                                       GPIO_ADS_PIN3_Msk
#define GPIO_ADS_PIN4_Pos                                   (4U)
#define GPIO_ADS_PIN4_Msk                                   (0x1UL << GPIO_ADS_PIN4_Pos)
#define GPIO_ADS_PIN4                                       GPIO_ADS_PIN4_Msk
#define GPIO_ADS_PIN5_Pos                                   (5U)
#define GPIO_ADS_PIN5_Msk                                   (0x1UL << GPIO_ADS_PIN5_Pos)
#define GPIO_ADS_PIN5                                       GPIO_ADS_PIN5_Msk
#define GPIO_ADS_PIN6_Pos                                   (6U)
#define GPIO_ADS_PIN6_Msk                                   (0x1UL << GPIO_ADS_PIN6_Pos)
#define GPIO_ADS_PIN6                                       GPIO_ADS_PIN6_Msk
#define GPIO_ADS_PIN7_Pos                                   (7U)
#define GPIO_ADS_PIN7_Msk                                   (0x1UL << GPIO_ADS_PIN7_Pos)
#define GPIO_ADS_PIN7                                       GPIO_ADS_PIN7_Msk
#define GPIO_ADS_PIN8_Pos                                   (8U)
#define GPIO_ADS_PIN8_Msk                                   (0x1UL << GPIO_ADS_PIN8_Pos)
#define GPIO_ADS_PIN8                                       GPIO_ADS_PIN8_Msk
#define GPIO_ADS_PIN9_Pos                                   (9U)
#define GPIO_ADS_PIN9_Msk                                   (0x1UL << GPIO_ADS_PIN9_Pos)
#define GPIO_ADS_PIN9                                       GPIO_ADS_PIN9_Msk
#define GPIO_ADS_PIN10_Pos                                  (10U)
#define GPIO_ADS_PIN10_Msk                                  (0x1UL << GPIO_ADS_PIN10_Pos)
#define GPIO_ADS_PIN10                                      GPIO_ADS_PIN10_Msk
#define GPIO_ADS_PIN11_Pos                                  (11U)
#define GPIO_ADS_PIN11_Msk                                  (0x1UL << GPIO_ADS_PIN11_Pos)
#define GPIO_ADS_PIN11                                      GPIO_ADS_PIN11_Msk
#define GPIO_ADS_PIN12_Pos                                  (12U)
#define GPIO_ADS_PIN12_Msk                                  (0x1UL << GPIO_ADS_PIN12_Pos)
#define GPIO_ADS_PIN12                                      GPIO_ADS_PIN12_Msk
#define GPIO_ADS_PIN13_Pos                                  (13U)
#define GPIO_ADS_PIN13_Msk                                  (0x1UL << GPIO_ADS_PIN13_Pos)
#define GPIO_ADS_PIN13                                      GPIO_ADS_PIN13_Msk
#define GPIO_ADS_PIN14_Pos                                  (14U)
#define GPIO_ADS_PIN14_Msk                                  (0x1UL << GPIO_ADS_PIN14_Pos)
#define GPIO_ADS_PIN14                                      GPIO_ADS_PIN14_Msk
#define GPIO_ADS_PIN15_Pos                                  (15U)
#define GPIO_ADS_PIN15_Msk                                  (0x1UL << GPIO_ADS_PIN15_Pos)
#define GPIO_ADS_PIN15                                      GPIO_ADS_PIN15_Msk

// GPIO_DIR
#define GPIO_DIR_PIN0_Pos                                   (0U)
#define GPIO_DIR_PIN0_Msk                                   (0x1UL << GPIO_DIR_PIN0_Pos)
#define GPIO_DIR_PIN0                                       GPIO_DIR_PIN0_Msk
#define GPIO_DIR_PIN1_Pos                                   (1U)
#define GPIO_DIR_PIN1_Msk                                   (0x1UL << GPIO_DIR_PIN1_Pos)
#define GPIO_DIR_PIN1                                       GPIO_DIR_PIN1_Msk
#define GPIO_DIR_PIN2_Pos                                   (2U)
#define GPIO_DIR_PIN2_Msk                                   (0x1UL << GPIO_DIR_PIN2_Pos)
#define GPIO_DIR_PIN2                                       GPIO_DIR_PIN2_Msk
#define GPIO_DIR_PIN3_Pos                                   (3U)
#define GPIO_DIR_PIN3_Msk                                   (0x1UL << GPIO_DIR_PIN3_Pos)
#define GPIO_DIR_PIN3                                       GPIO_DIR_PIN3_Msk
#define GPIO_DIR_PIN4_Pos                                   (4U)
#define GPIO_DIR_PIN4_Msk                                   (0x1UL << GPIO_DIR_PIN4_Pos)
#define GPIO_DIR_PIN4                                       GPIO_DIR_PIN4_Msk
#define GPIO_DIR_PIN5_Pos                                   (5U)
#define GPIO_DIR_PIN5_Msk                                   (0x1UL << GPIO_DIR_PIN5_Pos)
#define GPIO_DIR_PIN5                                       GPIO_DIR_PIN5_Msk
#define GPIO_DIR_PIN6_Pos                                   (6U)
#define GPIO_DIR_PIN6_Msk                                   (0x1UL << GPIO_DIR_PIN6_Pos)
#define GPIO_DIR_PIN6                                       GPIO_DIR_PIN6_Msk
#define GPIO_DIR_PIN7_Pos                                   (7U)
#define GPIO_DIR_PIN7_Msk                                   (0x1UL << GPIO_DIR_PIN7_Pos)
#define GPIO_DIR_PIN7                                       GPIO_DIR_PIN7_Msk
#define GPIO_DIR_PIN8_Pos                                   (8U)
#define GPIO_DIR_PIN8_Msk                                   (0x1UL << GPIO_DIR_PIN8_Pos)
#define GPIO_DIR_PIN8                                       GPIO_DIR_PIN8_Msk
#define GPIO_DIR_PIN9_Pos                                   (9U)
#define GPIO_DIR_PIN9_Msk                                   (0x1UL << GPIO_DIR_PIN9_Pos)
#define GPIO_DIR_PIN9                                       GPIO_DIR_PIN9_Msk
#define GPIO_DIR_PIN10_Pos                                  (10U)
#define GPIO_DIR_PIN10_Msk                                  (0x1UL << GPIO_DIR_PIN10_Pos)
#define GPIO_DIR_PIN10                                      GPIO_DIR_PIN10_Msk
#define GPIO_DIR_PIN11_Pos                                  (11U)
#define GPIO_DIR_PIN11_Msk                                  (0x1UL << GPIO_DIR_PIN11_Pos)
#define GPIO_DIR_PIN11                                      GPIO_DIR_PIN11_Msk
#define GPIO_DIR_PIN12_Pos                                  (12U)
#define GPIO_DIR_PIN12_Msk                                  (0x1UL << GPIO_DIR_PIN12_Pos)
#define GPIO_DIR_PIN12                                      GPIO_DIR_PIN12_Msk
#define GPIO_DIR_PIN13_Pos                                  (13U)
#define GPIO_DIR_PIN13_Msk                                  (0x1UL << GPIO_DIR_PIN13_Pos)
#define GPIO_DIR_PIN13                                      GPIO_DIR_PIN13_Msk
#define GPIO_DIR_PIN14_Pos                                  (14U)
#define GPIO_DIR_PIN14_Msk                                  (0x1UL << GPIO_DIR_PIN14_Pos)
#define GPIO_DIR_PIN14                                      GPIO_DIR_PIN14_Msk
#define GPIO_DIR_PIN15_Pos                                  (15U)
#define GPIO_DIR_PIN15_Msk                                  (0x1UL << GPIO_DIR_PIN15_Pos)
#define GPIO_DIR_PIN15                                      GPIO_DIR_PIN15_Msk

// GPIO_OPENDRAIN
#define GPIO_OPENDRAIN_PIN0_Pos                             (0U)
#define GPIO_OPENDRAIN_PIN0_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN0_Pos)
#define GPIO_OPENDRAIN_PIN0                                 GPIO_OPENDRAIN_PIN0_Msk
#define GPIO_OPENDRAIN_PIN1_Pos                             (1U)
#define GPIO_OPENDRAIN_PIN1_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN1_Pos)
#define GPIO_OPENDRAIN_PIN1                                 GPIO_OPENDRAIN_PIN1_Msk
#define GPIO_OPENDRAIN_PIN2_Pos                             (2U)
#define GPIO_OPENDRAIN_PIN2_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN2_Pos)
#define GPIO_OPENDRAIN_PIN2                                 GPIO_OPENDRAIN_PIN2_Msk
#define GPIO_OPENDRAIN_PIN3_Pos                             (3U)
#define GPIO_OPENDRAIN_PIN3_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN3_Pos)
#define GPIO_OPENDRAIN_PIN3                                 GPIO_OPENDRAIN_PIN3_Msk
#define GPIO_OPENDRAIN_PIN4_Pos                             (4U)
#define GPIO_OPENDRAIN_PIN4_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN4_Pos)
#define GPIO_OPENDRAIN_PIN4                                 GPIO_OPENDRAIN_PIN4_Msk
#define GPIO_OPENDRAIN_PIN5_Pos                             (5U)
#define GPIO_OPENDRAIN_PIN5_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN5_Pos)
#define GPIO_OPENDRAIN_PIN5                                 GPIO_OPENDRAIN_PIN5_Msk
#define GPIO_OPENDRAIN_PIN6_Pos                             (6U)
#define GPIO_OPENDRAIN_PIN6_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN6_Pos)
#define GPIO_OPENDRAIN_PIN6                                 GPIO_OPENDRAIN_PIN6_Msk
#define GPIO_OPENDRAIN_PIN7_Pos                             (7U)
#define GPIO_OPENDRAIN_PIN7_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN7_Pos)
#define GPIO_OPENDRAIN_PIN7                                 GPIO_OPENDRAIN_PIN7_Msk
#define GPIO_OPENDRAIN_PIN8_Pos                             (8U)
#define GPIO_OPENDRAIN_PIN8_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN8_Pos)
#define GPIO_OPENDRAIN_PIN8                                 GPIO_OPENDRAIN_PIN8_Msk
#define GPIO_OPENDRAIN_PIN9_Pos                             (9U)
#define GPIO_OPENDRAIN_PIN9_Msk                             (0x1UL << GPIO_OPENDRAIN_PIN9_Pos)
#define GPIO_OPENDRAIN_PIN9                                 GPIO_OPENDRAIN_PIN9_Msk
#define GPIO_OPENDRAIN_PIN10_Pos                            (10U)
#define GPIO_OPENDRAIN_PIN10_Msk                            (0x1UL << GPIO_OPENDRAIN_PIN10_Pos)
#define GPIO_OPENDRAIN_PIN10                                GPIO_OPENDRAIN_PIN10_Msk
#define GPIO_OPENDRAIN_PIN11_Pos                            (11U)
#define GPIO_OPENDRAIN_PIN11_Msk                            (0x1UL << GPIO_OPENDRAIN_PIN11_Pos)
#define GPIO_OPENDRAIN_PIN11                                GPIO_OPENDRAIN_PIN11_Msk
#define GPIO_OPENDRAIN_PIN12_Pos                            (12U)
#define GPIO_OPENDRAIN_PIN12_Msk                            (0x1UL << GPIO_OPENDRAIN_PIN12_Pos)
#define GPIO_OPENDRAIN_PIN12                                GPIO_OPENDRAIN_PIN12_Msk
#define GPIO_OPENDRAIN_PIN13_Pos                            (13U)
#define GPIO_OPENDRAIN_PIN13_Msk                            (0x1UL << GPIO_OPENDRAIN_PIN13_Pos)
#define GPIO_OPENDRAIN_PIN13                                GPIO_OPENDRAIN_PIN13_Msk
#define GPIO_OPENDRAIN_PIN14_Pos                            (14U)
#define GPIO_OPENDRAIN_PIN14_Msk                            (0x1UL << GPIO_OPENDRAIN_PIN14_Pos)
#define GPIO_OPENDRAIN_PIN14                                GPIO_OPENDRAIN_PIN14_Msk
#define GPIO_OPENDRAIN_PIN15_Pos                            (15U)
#define GPIO_OPENDRAIN_PIN15_Msk                            (0x1UL << GPIO_OPENDRAIN_PIN15_Pos)
#define GPIO_OPENDRAIN_PIN15                                GPIO_OPENDRAIN_PIN15_Msk

// GPIO_DRIVER
#define GPIO_DRIVER_PIN0_Pos                                (0U)
#define GPIO_DRIVER_PIN0_Msk                                (0x1UL << GPIO_DRIVER_PIN0_Pos)
#define GPIO_DRIVER_PIN0                                    GPIO_DRIVER_PIN0_Msk
#define GPIO_DRIVER_PIN1_Pos                                (1U)
#define GPIO_DRIVER_PIN1_Msk                                (0x1UL << GPIO_DRIVER_PIN1_Pos)
#define GPIO_DRIVER_PIN1                                    GPIO_DRIVER_PIN1_Msk
#define GPIO_DRIVER_PIN2_Pos                                (2U)
#define GPIO_DRIVER_PIN2_Msk                                (0x1UL << GPIO_DRIVER_PIN2_Pos)
#define GPIO_DRIVER_PIN2                                    GPIO_DRIVER_PIN2_Msk
#define GPIO_DRIVER_PIN3_Pos                                (3U)
#define GPIO_DRIVER_PIN3_Msk                                (0x1UL << GPIO_DRIVER_PIN3_Pos)
#define GPIO_DRIVER_PIN3                                    GPIO_DRIVER_PIN3_Msk
#define GPIO_DRIVER_PIN4_Pos                                (4U)
#define GPIO_DRIVER_PIN4_Msk                                (0x1UL << GPIO_DRIVER_PIN4_Pos)
#define GPIO_DRIVER_PIN4                                    GPIO_DRIVER_PIN4_Msk
#define GPIO_DRIVER_PIN5_Pos                                (5U)
#define GPIO_DRIVER_PIN5_Msk                                (0x1UL << GPIO_DRIVER_PIN5_Pos)
#define GPIO_DRIVER_PIN5                                    GPIO_DRIVER_PIN5_Msk
#define GPIO_DRIVER_PIN6_Pos                                (6U)
#define GPIO_DRIVER_PIN6_Msk                                (0x1UL << GPIO_DRIVER_PIN6_Pos)
#define GPIO_DRIVER_PIN6                                    GPIO_DRIVER_PIN6_Msk
#define GPIO_DRIVER_PIN7_Pos                                (7U)
#define GPIO_DRIVER_PIN7_Msk                                (0x1UL << GPIO_DRIVER_PIN7_Pos)
#define GPIO_DRIVER_PIN7                                    GPIO_DRIVER_PIN7_Msk
#define GPIO_DRIVER_PIN8_Pos                                (8U)
#define GPIO_DRIVER_PIN8_Msk                                (0x1UL << GPIO_DRIVER_PIN8_Pos)
#define GPIO_DRIVER_PIN8                                    GPIO_DRIVER_PIN8_Msk
#define GPIO_DRIVER_PIN9_Pos                                (9U)
#define GPIO_DRIVER_PIN9_Msk                                (0x1UL << GPIO_DRIVER_PIN9_Pos)
#define GPIO_DRIVER_PIN9                                    GPIO_DRIVER_PIN9_Msk
#define GPIO_DRIVER_PIN10_Pos                               (10U)
#define GPIO_DRIVER_PIN10_Msk                               (0x1UL << GPIO_DRIVER_PIN10_Pos)
#define GPIO_DRIVER_PIN10                                   GPIO_DRIVER_PIN10_Msk
#define GPIO_DRIVER_PIN11_Pos                               (11U)
#define GPIO_DRIVER_PIN11_Msk                               (0x1UL << GPIO_DRIVER_PIN11_Pos)
#define GPIO_DRIVER_PIN11                                   GPIO_DRIVER_PIN11_Msk
#define GPIO_DRIVER_PIN12_Pos                               (12U)
#define GPIO_DRIVER_PIN12_Msk                               (0x1UL << GPIO_DRIVER_PIN12_Pos)
#define GPIO_DRIVER_PIN12                                   GPIO_DRIVER_PIN12_Msk
#define GPIO_DRIVER_PIN13_Pos                               (13U)
#define GPIO_DRIVER_PIN13_Msk                               (0x1UL << GPIO_DRIVER_PIN13_Pos)
#define GPIO_DRIVER_PIN13                                   GPIO_DRIVER_PIN13_Msk
#define GPIO_DRIVER_PIN14_Pos                               (14U)
#define GPIO_DRIVER_PIN14_Msk                               (0x1UL << GPIO_DRIVER_PIN14_Pos)
#define GPIO_DRIVER_PIN14                                   GPIO_DRIVER_PIN14_Msk
#define GPIO_DRIVER_PIN15_Pos                               (15U)
#define GPIO_DRIVER_PIN15_Msk                               (0x1UL << GPIO_DRIVER_PIN15_Pos)
#define GPIO_DRIVER_PIN15                                   GPIO_DRIVER_PIN15_Msk

// GPIO_PUPD
#define GPIO_PUPD_PUPIN0_Pos                                (0U)
#define GPIO_PUPD_PUPIN0_Msk                                (0x1UL << GPIO_PUPD_PUPIN0_Pos)
#define GPIO_PUPD_PUPIN0                                    GPIO_PUPD_PUPIN0_Msk
#define GPIO_PUPD_PUPIN1_Pos                                (1U)
#define GPIO_PUPD_PUPIN1_Msk                                (0x1UL << GPIO_PUPD_PUPIN1_Pos)
#define GPIO_PUPD_PUPIN1                                    GPIO_PUPD_PUPIN1_Msk
#define GPIO_PUPD_PUPIN2_Pos                                (2U)
#define GPIO_PUPD_PUPIN2_Msk                                (0x1UL << GPIO_PUPD_PUPIN2_Pos)
#define GPIO_PUPD_PUPIN2                                    GPIO_PUPD_PUPIN2_Msk
#define GPIO_PUPD_PUPIN3_Pos                                (3U)
#define GPIO_PUPD_PUPIN3_Msk                                (0x1UL << GPIO_PUPD_PUPIN3_Pos)
#define GPIO_PUPD_PUPIN3                                    GPIO_PUPD_PUPIN3_Msk
#define GPIO_PUPD_PUPIN4_Pos                                (4U)
#define GPIO_PUPD_PUPIN4_Msk                                (0x1UL << GPIO_PUPD_PUPIN4_Pos)
#define GPIO_PUPD_PUPIN4                                    GPIO_PUPD_PUPIN4_Msk
#define GPIO_PUPD_PUPIN5_Pos                                (5U)
#define GPIO_PUPD_PUPIN5_Msk                                (0x1UL << GPIO_PUPD_PUPIN5_Pos)
#define GPIO_PUPD_PUPIN5                                    GPIO_PUPD_PUPIN5_Msk
#define GPIO_PUPD_PUPIN6_Pos                                (6U)
#define GPIO_PUPD_PUPIN6_Msk                                (0x1UL << GPIO_PUPD_PUPIN6_Pos)
#define GPIO_PUPD_PUPIN6                                    GPIO_PUPD_PUPIN6_Msk
#define GPIO_PUPD_PUPIN7_Pos                                (7U)
#define GPIO_PUPD_PUPIN7_Msk                                (0x1UL << GPIO_PUPD_PUPIN7_Pos)
#define GPIO_PUPD_PUPIN7                                    GPIO_PUPD_PUPIN7_Msk
#define GPIO_PUPD_PUPIN8_Pos                                (8U)
#define GPIO_PUPD_PUPIN8_Msk                                (0x1UL << GPIO_PUPD_PUPIN8_Pos)
#define GPIO_PUPD_PUPIN8                                    GPIO_PUPD_PUPIN8_Msk
#define GPIO_PUPD_PUPIN9_Pos                                (9U)
#define GPIO_PUPD_PUPIN9_Msk                                (0x1UL << GPIO_PUPD_PUPIN9_Pos)
#define GPIO_PUPD_PUPIN9                                    GPIO_PUPD_PUPIN9_Msk
#define GPIO_PUPD_PUPIN10_Pos                               (10U)
#define GPIO_PUPD_PUPIN10_Msk                               (0x1UL << GPIO_PUPD_PUPIN10_Pos)
#define GPIO_PUPD_PUPIN10                                   GPIO_PUPD_PUPIN10_Msk
#define GPIO_PUPD_PUPIN11_Pos                               (11U)
#define GPIO_PUPD_PUPIN11_Msk                               (0x1UL << GPIO_PUPD_PUPIN11_Pos)
#define GPIO_PUPD_PUPIN11                                   GPIO_PUPD_PUPIN11_Msk
#define GPIO_PUPD_PUPIN12_Pos                               (12U)
#define GPIO_PUPD_PUPIN12_Msk                               (0x1UL << GPIO_PUPD_PUPIN12_Pos)
#define GPIO_PUPD_PUPIN12                                   GPIO_PUPD_PUPIN12_Msk
#define GPIO_PUPD_PUPIN13_Pos                               (13U)
#define GPIO_PUPD_PUPIN13_Msk                               (0x1UL << GPIO_PUPD_PUPIN13_Pos)
#define GPIO_PUPD_PUPIN13                                   GPIO_PUPD_PUPIN13_Msk
#define GPIO_PUPD_PUPIN14_Pos                               (14U)
#define GPIO_PUPD_PUPIN14_Msk                               (0x1UL << GPIO_PUPD_PUPIN14_Pos)
#define GPIO_PUPD_PUPIN14                                   GPIO_PUPD_PUPIN14_Msk
#define GPIO_PUPD_PUPIN15_Pos                               (15U)
#define GPIO_PUPD_PUPIN15_Msk                               (0x1UL << GPIO_PUPD_PUPIN15_Pos)
#define GPIO_PUPD_PUPIN15                                   GPIO_PUPD_PUPIN15_Msk
#define GPIO_PUPD_PDPIN0_Pos                                (16U)
#define GPIO_PUPD_PDPIN0_Msk                                (0x1UL << GPIO_PUPD_PDPIN0_Pos)
#define GPIO_PUPD_PDPIN0                                    GPIO_PUPD_PDPIN0_Msk
#define GPIO_PUPD_PDPIN1_Pos                                (17U)
#define GPIO_PUPD_PDPIN1_Msk                                (0x1UL << GPIO_PUPD_PDPIN1_Pos)
#define GPIO_PUPD_PDPIN1                                    GPIO_PUPD_PDPIN1_Msk
#define GPIO_PUPD_PDPIN2_Pos                                (18U)
#define GPIO_PUPD_PDPIN2_Msk                                (0x1UL << GPIO_PUPD_PDPIN2_Pos)
#define GPIO_PUPD_PDPIN2                                    GPIO_PUPD_PDPIN2_Msk
#define GPIO_PUPD_PDPIN3_Pos                                (19U)
#define GPIO_PUPD_PDPIN3_Msk                                (0x1UL << GPIO_PUPD_PDPIN3_Pos)
#define GPIO_PUPD_PDPIN3                                    GPIO_PUPD_PDPIN3_Msk
#define GPIO_PUPD_PDPIN4_Pos                                (20U)
#define GPIO_PUPD_PDPIN4_Msk                                (0x1UL << GPIO_PUPD_PDPIN4_Pos)
#define GPIO_PUPD_PDPIN4                                    GPIO_PUPD_PDPIN4_Msk
#define GPIO_PUPD_PDPIN5_Pos                                (21U)
#define GPIO_PUPD_PDPIN5_Msk                                (0x1UL << GPIO_PUPD_PDPIN5_Pos)
#define GPIO_PUPD_PDPIN5                                    GPIO_PUPD_PDPIN5_Msk
#define GPIO_PUPD_PDPIN6_Pos                                (22U)
#define GPIO_PUPD_PDPIN6_Msk                                (0x1UL << GPIO_PUPD_PDPIN6_Pos)
#define GPIO_PUPD_PDPIN6                                    GPIO_PUPD_PDPIN6_Msk
#define GPIO_PUPD_PDPIN7_Pos                                (23U)
#define GPIO_PUPD_PDPIN7_Msk                                (0x1UL << GPIO_PUPD_PDPIN7_Pos)
#define GPIO_PUPD_PDPIN7                                    GPIO_PUPD_PDPIN7_Msk
#define GPIO_PUPD_PDPIN8_Pos                                (24U)
#define GPIO_PUPD_PDPIN8_Msk                                (0x1UL << GPIO_PUPD_PDPIN8_Pos)
#define GPIO_PUPD_PDPIN8                                    GPIO_PUPD_PDPIN8_Msk
#define GPIO_PUPD_PDPIN9_Pos                                (25U)
#define GPIO_PUPD_PDPIN9_Msk                                (0x1UL << GPIO_PUPD_PDPIN9_Pos)
#define GPIO_PUPD_PDPIN9                                    GPIO_PUPD_PDPIN9_Msk
#define GPIO_PUPD_PDPIN10_Pos                               (26U)
#define GPIO_PUPD_PDPIN10_Msk                               (0x1UL << GPIO_PUPD_PDPIN10_Pos)
#define GPIO_PUPD_PDPIN10                                   GPIO_PUPD_PDPIN10_Msk
#define GPIO_PUPD_PDPIN11_Pos                               (27U)
#define GPIO_PUPD_PDPIN11_Msk                               (0x1UL << GPIO_PUPD_PDPIN11_Pos)
#define GPIO_PUPD_PDPIN11                                   GPIO_PUPD_PDPIN11_Msk
#define GPIO_PUPD_PDPIN12_Pos                               (28U)
#define GPIO_PUPD_PDPIN12_Msk                               (0x1UL << GPIO_PUPD_PDPIN12_Pos)
#define GPIO_PUPD_PDPIN12                                   GPIO_PUPD_PDPIN12_Msk
#define GPIO_PUPD_PDPIN13_Pos                               (29U)
#define GPIO_PUPD_PDPIN13_Msk                               (0x1UL << GPIO_PUPD_PDPIN13_Pos)
#define GPIO_PUPD_PDPIN13                                   GPIO_PUPD_PDPIN13_Msk
#define GPIO_PUPD_PDPIN14_Pos                               (30U)
#define GPIO_PUPD_PDPIN14_Msk                               (0x1UL << GPIO_PUPD_PDPIN14_Pos)
#define GPIO_PUPD_PDPIN14                                   GPIO_PUPD_PDPIN14_Msk
#define GPIO_PUPD_PDPIN15_Pos                               (31U)
#define GPIO_PUPD_PDPIN15_Msk                               (0x1UL << GPIO_PUPD_PDPIN15_Pos)
#define GPIO_PUPD_PDPIN15                                   GPIO_PUPD_PDPIN15_Msk

// GPIO_IN
#define GPIO_IN_PIN0_Pos                                    (0U)
#define GPIO_IN_PIN0_Msk                                    (0x1UL << GPIO_IN_PIN0_Pos)
#define GPIO_IN_PIN0                                        GPIO_IN_PIN0_Msk
#define GPIO_IN_PIN1_Pos                                    (1U)
#define GPIO_IN_PIN1_Msk                                    (0x1UL << GPIO_IN_PIN1_Pos)
#define GPIO_IN_PIN1                                        GPIO_IN_PIN1_Msk
#define GPIO_IN_PIN2_Pos                                    (2U)
#define GPIO_IN_PIN2_Msk                                    (0x1UL << GPIO_IN_PIN2_Pos)
#define GPIO_IN_PIN2                                        GPIO_IN_PIN2_Msk
#define GPIO_IN_PIN3_Pos                                    (3U)
#define GPIO_IN_PIN3_Msk                                    (0x1UL << GPIO_IN_PIN3_Pos)
#define GPIO_IN_PIN3                                        GPIO_IN_PIN3_Msk
#define GPIO_IN_PIN4_Pos                                    (4U)
#define GPIO_IN_PIN4_Msk                                    (0x1UL << GPIO_IN_PIN4_Pos)
#define GPIO_IN_PIN4                                        GPIO_IN_PIN4_Msk
#define GPIO_IN_PIN5_Pos                                    (5U)
#define GPIO_IN_PIN5_Msk                                    (0x1UL << GPIO_IN_PIN5_Pos)
#define GPIO_IN_PIN5                                        GPIO_IN_PIN5_Msk
#define GPIO_IN_PIN6_Pos                                    (6U)
#define GPIO_IN_PIN6_Msk                                    (0x1UL << GPIO_IN_PIN6_Pos)
#define GPIO_IN_PIN6                                        GPIO_IN_PIN6_Msk
#define GPIO_IN_PIN7_Pos                                    (7U)
#define GPIO_IN_PIN7_Msk                                    (0x1UL << GPIO_IN_PIN7_Pos)
#define GPIO_IN_PIN7                                        GPIO_IN_PIN7_Msk
#define GPIO_IN_PIN8_Pos                                    (8U)
#define GPIO_IN_PIN8_Msk                                    (0x1UL << GPIO_IN_PIN8_Pos)
#define GPIO_IN_PIN8                                        GPIO_IN_PIN8_Msk
#define GPIO_IN_PIN9_Pos                                    (9U)
#define GPIO_IN_PIN9_Msk                                    (0x1UL << GPIO_IN_PIN9_Pos)
#define GPIO_IN_PIN9                                        GPIO_IN_PIN9_Msk
#define GPIO_IN_PIN10_Pos                                   (10U)
#define GPIO_IN_PIN10_Msk                                   (0x1UL << GPIO_IN_PIN10_Pos)
#define GPIO_IN_PIN10                                       GPIO_IN_PIN10_Msk
#define GPIO_IN_PIN11_Pos                                   (11U)
#define GPIO_IN_PIN11_Msk                                   (0x1UL << GPIO_IN_PIN11_Pos)
#define GPIO_IN_PIN11                                       GPIO_IN_PIN11_Msk
#define GPIO_IN_PIN12_Pos                                   (12U)
#define GPIO_IN_PIN12_Msk                                   (0x1UL << GPIO_IN_PIN12_Pos)
#define GPIO_IN_PIN12                                       GPIO_IN_PIN12_Msk
#define GPIO_IN_PIN13_Pos                                   (13U)
#define GPIO_IN_PIN13_Msk                                   (0x1UL << GPIO_IN_PIN13_Pos)
#define GPIO_IN_PIN13                                       GPIO_IN_PIN13_Msk
#define GPIO_IN_PIN14_Pos                                   (14U)
#define GPIO_IN_PIN14_Msk                                   (0x1UL << GPIO_IN_PIN14_Pos)
#define GPIO_IN_PIN14                                       GPIO_IN_PIN14_Msk
#define GPIO_IN_PIN15_Pos                                   (15U)
#define GPIO_IN_PIN15_Msk                                   (0x1UL << GPIO_IN_PIN15_Pos)
#define GPIO_IN_PIN15                                       GPIO_IN_PIN15_Msk

// GPIO_OUT
#define GPIO_OUT_PIN0_Pos                                   (0U)
#define GPIO_OUT_PIN0_Msk                                   (0x1UL << GPIO_OUT_PIN0_Pos)
#define GPIO_OUT_PIN0                                       GPIO_OUT_PIN0_Msk
#define GPIO_OUT_PIN1_Pos                                   (1U)
#define GPIO_OUT_PIN1_Msk                                   (0x1UL << GPIO_OUT_PIN1_Pos)
#define GPIO_OUT_PIN1                                       GPIO_OUT_PIN1_Msk
#define GPIO_OUT_PIN2_Pos                                   (2U)
#define GPIO_OUT_PIN2_Msk                                   (0x1UL << GPIO_OUT_PIN2_Pos)
#define GPIO_OUT_PIN2                                       GPIO_OUT_PIN2_Msk
#define GPIO_OUT_PIN3_Pos                                   (3U)
#define GPIO_OUT_PIN3_Msk                                   (0x1UL << GPIO_OUT_PIN3_Pos)
#define GPIO_OUT_PIN3                                       GPIO_OUT_PIN3_Msk
#define GPIO_OUT_PIN4_Pos                                   (4U)
#define GPIO_OUT_PIN4_Msk                                   (0x1UL << GPIO_OUT_PIN4_Pos)
#define GPIO_OUT_PIN4                                       GPIO_OUT_PIN4_Msk
#define GPIO_OUT_PIN5_Pos                                   (5U)
#define GPIO_OUT_PIN5_Msk                                   (0x1UL << GPIO_OUT_PIN5_Pos)
#define GPIO_OUT_PIN5                                       GPIO_OUT_PIN5_Msk
#define GPIO_OUT_PIN6_Pos                                   (6U)
#define GPIO_OUT_PIN6_Msk                                   (0x1UL << GPIO_OUT_PIN6_Pos)
#define GPIO_OUT_PIN6                                       GPIO_OUT_PIN6_Msk
#define GPIO_OUT_PIN7_Pos                                   (7U)
#define GPIO_OUT_PIN7_Msk                                   (0x1UL << GPIO_OUT_PIN7_Pos)
#define GPIO_OUT_PIN7                                       GPIO_OUT_PIN7_Msk
#define GPIO_OUT_PIN8_Pos                                   (8U)
#define GPIO_OUT_PIN8_Msk                                   (0x1UL << GPIO_OUT_PIN8_Pos)
#define GPIO_OUT_PIN8                                       GPIO_OUT_PIN8_Msk
#define GPIO_OUT_PIN9_Pos                                   (9U)
#define GPIO_OUT_PIN9_Msk                                   (0x1UL << GPIO_OUT_PIN9_Pos)
#define GPIO_OUT_PIN9                                       GPIO_OUT_PIN9_Msk
#define GPIO_OUT_PIN10_Pos                                  (10U)
#define GPIO_OUT_PIN10_Msk                                  (0x1UL << GPIO_OUT_PIN10_Pos)
#define GPIO_OUT_PIN10                                      GPIO_OUT_PIN10_Msk
#define GPIO_OUT_PIN11_Pos                                  (11U)
#define GPIO_OUT_PIN11_Msk                                  (0x1UL << GPIO_OUT_PIN11_Pos)
#define GPIO_OUT_PIN11                                      GPIO_OUT_PIN11_Msk
#define GPIO_OUT_PIN12_Pos                                  (12U)
#define GPIO_OUT_PIN12_Msk                                  (0x1UL << GPIO_OUT_PIN12_Pos)
#define GPIO_OUT_PIN12                                      GPIO_OUT_PIN12_Msk
#define GPIO_OUT_PIN13_Pos                                  (13U)
#define GPIO_OUT_PIN13_Msk                                  (0x1UL << GPIO_OUT_PIN13_Pos)
#define GPIO_OUT_PIN13                                      GPIO_OUT_PIN13_Msk
#define GPIO_OUT_PIN14_Pos                                  (14U)
#define GPIO_OUT_PIN14_Msk                                  (0x1UL << GPIO_OUT_PIN14_Pos)
#define GPIO_OUT_PIN14                                      GPIO_OUT_PIN14_Msk
#define GPIO_OUT_PIN15_Pos                                  (15U)
#define GPIO_OUT_PIN15_Msk                                  (0x1UL << GPIO_OUT_PIN15_Pos)
#define GPIO_OUT_PIN15                                      GPIO_OUT_PIN15_Msk

// GPIO_BRR
#define GPIO_BRR_PIN0_Pos                                   (0U)
#define GPIO_BRR_PIN0_Msk                                   (0x1UL << GPIO_BRR_PIN0_Pos)
#define GPIO_BRR_PIN0                                       GPIO_BRR_PIN0_Msk
#define GPIO_BRR_PIN1_Pos                                   (1U)
#define GPIO_BRR_PIN1_Msk                                   (0x1UL << GPIO_BRR_PIN1_Pos)
#define GPIO_BRR_PIN1                                       GPIO_BRR_PIN1_Msk
#define GPIO_BRR_PIN2_Pos                                   (2U)
#define GPIO_BRR_PIN2_Msk                                   (0x1UL << GPIO_BRR_PIN2_Pos)
#define GPIO_BRR_PIN2                                       GPIO_BRR_PIN2_Msk
#define GPIO_BRR_PIN3_Pos                                   (3U)
#define GPIO_BRR_PIN3_Msk                                   (0x1UL << GPIO_BRR_PIN3_Pos)
#define GPIO_BRR_PIN3                                       GPIO_BRR_PIN3_Msk
#define GPIO_BRR_PIN4_Pos                                   (4U)
#define GPIO_BRR_PIN4_Msk                                   (0x1UL << GPIO_BRR_PIN4_Pos)
#define GPIO_BRR_PIN4                                       GPIO_BRR_PIN4_Msk
#define GPIO_BRR_PIN5_Pos                                   (5U)
#define GPIO_BRR_PIN5_Msk                                   (0x1UL << GPIO_BRR_PIN5_Pos)
#define GPIO_BRR_PIN5                                       GPIO_BRR_PIN5_Msk
#define GPIO_BRR_PIN6_Pos                                   (6U)
#define GPIO_BRR_PIN6_Msk                                   (0x1UL << GPIO_BRR_PIN6_Pos)
#define GPIO_BRR_PIN6                                       GPIO_BRR_PIN6_Msk
#define GPIO_BRR_PIN7_Pos                                   (7U)
#define GPIO_BRR_PIN7_Msk                                   (0x1UL << GPIO_BRR_PIN7_Pos)
#define GPIO_BRR_PIN7                                       GPIO_BRR_PIN7_Msk
#define GPIO_BRR_PIN8_Pos                                   (8U)
#define GPIO_BRR_PIN8_Msk                                   (0x1UL << GPIO_BRR_PIN8_Pos)
#define GPIO_BRR_PIN8                                       GPIO_BRR_PIN8_Msk
#define GPIO_BRR_PIN9_Pos                                   (9U)
#define GPIO_BRR_PIN9_Msk                                   (0x1UL << GPIO_BRR_PIN9_Pos)
#define GPIO_BRR_PIN9                                       GPIO_BRR_PIN9_Msk
#define GPIO_BRR_PIN10_Pos                                  (10U)
#define GPIO_BRR_PIN10_Msk                                  (0x1UL << GPIO_BRR_PIN10_Pos)
#define GPIO_BRR_PIN10                                      GPIO_BRR_PIN10_Msk
#define GPIO_BRR_PIN11_Pos                                  (11U)
#define GPIO_BRR_PIN11_Msk                                  (0x1UL << GPIO_BRR_PIN11_Pos)
#define GPIO_BRR_PIN11                                      GPIO_BRR_PIN11_Msk
#define GPIO_BRR_PIN12_Pos                                  (12U)
#define GPIO_BRR_PIN12_Msk                                  (0x1UL << GPIO_BRR_PIN12_Pos)
#define GPIO_BRR_PIN12                                      GPIO_BRR_PIN12_Msk
#define GPIO_BRR_PIN13_Pos                                  (13U)
#define GPIO_BRR_PIN13_Msk                                  (0x1UL << GPIO_BRR_PIN13_Pos)
#define GPIO_BRR_PIN13                                      GPIO_BRR_PIN13_Msk
#define GPIO_BRR_PIN14_Pos                                  (14U)
#define GPIO_BRR_PIN14_Msk                                  (0x1UL << GPIO_BRR_PIN14_Pos)
#define GPIO_BRR_PIN14                                      GPIO_BRR_PIN14_Msk
#define GPIO_BRR_PIN15_Pos                                  (15U)
#define GPIO_BRR_PIN15_Msk                                  (0x1UL << GPIO_BRR_PIN15_Pos)
#define GPIO_BRR_PIN15                                      GPIO_BRR_PIN15_Msk

// GPIO_BSRR
#define GPIO_BSRR_BSPIN0_Pos                                (0U)
#define GPIO_BSRR_BSPIN0_Msk                                (0x1UL << GPIO_BSRR_BSPIN0_Pos)
#define GPIO_BSRR_BSPIN0                                    GPIO_BSRR_BSPIN0_Msk
#define GPIO_BSRR_BSPIN1_Pos                                (1U)
#define GPIO_BSRR_BSPIN1_Msk                                (0x1UL << GPIO_BSRR_BSPIN1_Pos)
#define GPIO_BSRR_BSPIN1                                    GPIO_BSRR_BSPIN1_Msk
#define GPIO_BSRR_BSPIN2_Pos                                (2U)
#define GPIO_BSRR_BSPIN2_Msk                                (0x1UL << GPIO_BSRR_BSPIN2_Pos)
#define GPIO_BSRR_BSPIN2                                    GPIO_BSRR_BSPIN2_Msk
#define GPIO_BSRR_BSPIN3_Pos                                (3U)
#define GPIO_BSRR_BSPIN3_Msk                                (0x1UL << GPIO_BSRR_BSPIN3_Pos)
#define GPIO_BSRR_BSPIN3                                    GPIO_BSRR_BSPIN3_Msk
#define GPIO_BSRR_BSPIN4_Pos                                (4U)
#define GPIO_BSRR_BSPIN4_Msk                                (0x1UL << GPIO_BSRR_BSPIN4_Pos)
#define GPIO_BSRR_BSPIN4                                    GPIO_BSRR_BSPIN4_Msk
#define GPIO_BSRR_BSPIN5_Pos                                (5U)
#define GPIO_BSRR_BSPIN5_Msk                                (0x1UL << GPIO_BSRR_BSPIN5_Pos)
#define GPIO_BSRR_BSPIN5                                    GPIO_BSRR_BSPIN5_Msk
#define GPIO_BSRR_BSPIN6_Pos                                (6U)
#define GPIO_BSRR_BSPIN6_Msk                                (0x1UL << GPIO_BSRR_BSPIN6_Pos)
#define GPIO_BSRR_BSPIN6                                    GPIO_BSRR_BSPIN6_Msk
#define GPIO_BSRR_BSPIN7_Pos                                (7U)
#define GPIO_BSRR_BSPIN7_Msk                                (0x1UL << GPIO_BSRR_BSPIN7_Pos)
#define GPIO_BSRR_BSPIN7                                    GPIO_BSRR_BSPIN7_Msk
#define GPIO_BSRR_BSPIN8_Pos                                (8U)
#define GPIO_BSRR_BSPIN8_Msk                                (0x1UL << GPIO_BSRR_BSPIN8_Pos)
#define GPIO_BSRR_BSPIN8                                    GPIO_BSRR_BSPIN8_Msk
#define GPIO_BSRR_BSPIN9_Pos                                (9U)
#define GPIO_BSRR_BSPIN9_Msk                                (0x1UL << GPIO_BSRR_BSPIN9_Pos)
#define GPIO_BSRR_BSPIN9                                    GPIO_BSRR_BSPIN9_Msk
#define GPIO_BSRR_BSPIN10_Pos                               (10U)
#define GPIO_BSRR_BSPIN10_Msk                               (0x1UL << GPIO_BSRR_BSPIN10_Pos)
#define GPIO_BSRR_BSPIN10                                   GPIO_BSRR_BSPIN10_Msk
#define GPIO_BSRR_BSPIN11_Pos                               (11U)
#define GPIO_BSRR_BSPIN11_Msk                               (0x1UL << GPIO_BSRR_BSPIN11_Pos)
#define GPIO_BSRR_BSPIN11                                   GPIO_BSRR_BSPIN11_Msk
#define GPIO_BSRR_BSPIN12_Pos                               (12U)
#define GPIO_BSRR_BSPIN12_Msk                               (0x1UL << GPIO_BSRR_BSPIN12_Pos)
#define GPIO_BSRR_BSPIN12                                   GPIO_BSRR_BSPIN12_Msk
#define GPIO_BSRR_BSPIN13_Pos                               (13U)
#define GPIO_BSRR_BSPIN13_Msk                               (0x1UL << GPIO_BSRR_BSPIN13_Pos)
#define GPIO_BSRR_BSPIN13                                   GPIO_BSRR_BSPIN13_Msk
#define GPIO_BSRR_BSPIN14_Pos                               (14U)
#define GPIO_BSRR_BSPIN14_Msk                               (0x1UL << GPIO_BSRR_BSPIN14_Pos)
#define GPIO_BSRR_BSPIN14                                   GPIO_BSRR_BSPIN14_Msk
#define GPIO_BSRR_BSPIN15_Pos                               (15U)
#define GPIO_BSRR_BSPIN15_Msk                               (0x1UL << GPIO_BSRR_BSPIN15_Pos)
#define GPIO_BSRR_BSPIN15                                   GPIO_BSRR_BSPIN15_Msk
#define GPIO_BSRR_BRPIN0_Pos                                (16U)
#define GPIO_BSRR_BRPIN0_Msk                                (0x1UL << GPIO_BSRR_BRPIN0_Pos)
#define GPIO_BSRR_BRPIN0                                    GPIO_BSRR_BRPIN0_Msk
#define GPIO_BSRR_BRPIN1_Pos                                (17U)
#define GPIO_BSRR_BRPIN1_Msk                                (0x1UL << GPIO_BSRR_BRPIN1_Pos)
#define GPIO_BSRR_BRPIN1                                    GPIO_BSRR_BRPIN1_Msk
#define GPIO_BSRR_BRPIN2_Pos                                (18U)
#define GPIO_BSRR_BRPIN2_Msk                                (0x1UL << GPIO_BSRR_BRPIN2_Pos)
#define GPIO_BSRR_BRPIN2                                    GPIO_BSRR_BRPIN2_Msk
#define GPIO_BSRR_BRPIN3_Pos                                (19U)
#define GPIO_BSRR_BRPIN3_Msk                                (0x1UL << GPIO_BSRR_BRPIN3_Pos)
#define GPIO_BSRR_BRPIN3                                    GPIO_BSRR_BRPIN3_Msk
#define GPIO_BSRR_BRPIN4_Pos                                (20U)
#define GPIO_BSRR_BRPIN4_Msk                                (0x1UL << GPIO_BSRR_BRPIN4_Pos)
#define GPIO_BSRR_BRPIN4                                    GPIO_BSRR_BRPIN4_Msk
#define GPIO_BSRR_BRPIN5_Pos                                (21U)
#define GPIO_BSRR_BRPIN5_Msk                                (0x1UL << GPIO_BSRR_BRPIN5_Pos)
#define GPIO_BSRR_BRPIN5                                    GPIO_BSRR_BRPIN5_Msk
#define GPIO_BSRR_BRPIN6_Pos                                (22U)
#define GPIO_BSRR_BRPIN6_Msk                                (0x1UL << GPIO_BSRR_BRPIN6_Pos)
#define GPIO_BSRR_BRPIN6                                    GPIO_BSRR_BRPIN6_Msk
#define GPIO_BSRR_BRPIN7_Pos                                (23U)
#define GPIO_BSRR_BRPIN7_Msk                                (0x1UL << GPIO_BSRR_BRPIN7_Pos)
#define GPIO_BSRR_BRPIN7                                    GPIO_BSRR_BRPIN7_Msk
#define GPIO_BSRR_BRPIN8_Pos                                (24U)
#define GPIO_BSRR_BRPIN8_Msk                                (0x1UL << GPIO_BSRR_BRPIN8_Pos)
#define GPIO_BSRR_BRPIN8                                    GPIO_BSRR_BRPIN8_Msk
#define GPIO_BSRR_BRPIN9_Pos                                (25U)
#define GPIO_BSRR_BRPIN9_Msk                                (0x1UL << GPIO_BSRR_BRPIN9_Pos)
#define GPIO_BSRR_BRPIN9                                    GPIO_BSRR_BRPIN9_Msk
#define GPIO_BSRR_BRPIN10_Pos                               (26U)
#define GPIO_BSRR_BRPIN10_Msk                               (0x1UL << GPIO_BSRR_BRPIN10_Pos)
#define GPIO_BSRR_BRPIN10                                   GPIO_BSRR_BRPIN10_Msk
#define GPIO_BSRR_BRPIN11_Pos                               (27U)
#define GPIO_BSRR_BRPIN11_Msk                               (0x1UL << GPIO_BSRR_BRPIN11_Pos)
#define GPIO_BSRR_BRPIN11                                   GPIO_BSRR_BRPIN11_Msk
#define GPIO_BSRR_BRPIN12_Pos                               (28U)
#define GPIO_BSRR_BRPIN12_Msk                               (0x1UL << GPIO_BSRR_BRPIN12_Pos)
#define GPIO_BSRR_BRPIN12                                   GPIO_BSRR_BRPIN12_Msk
#define GPIO_BSRR_BRPIN13_Pos                               (29U)
#define GPIO_BSRR_BRPIN13_Msk                               (0x1UL << GPIO_BSRR_BRPIN13_Pos)
#define GPIO_BSRR_BRPIN13                                   GPIO_BSRR_BRPIN13_Msk
#define GPIO_BSRR_BRPIN14_Pos                               (30U)
#define GPIO_BSRR_BRPIN14_Msk                               (0x1UL << GPIO_BSRR_BRPIN14_Pos)
#define GPIO_BSRR_BRPIN14                                   GPIO_BSRR_BRPIN14_Msk
#define GPIO_BSRR_BRPIN15_Pos                               (31U)
#define GPIO_BSRR_BRPIN15_Msk                               (0x1UL << GPIO_BSRR_BRPIN15_Pos)
#define GPIO_BSRR_BRPIN15                                   GPIO_BSRR_BRPIN15_Msk

// GPIO_AFRL
#define GPIO_AFRL_AFSEL0_Pos                                (0U)
#define GPIO_AFRL_AFSEL0_Msk                                (0xFUL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL0                                    GPIO_AFRL_AFSEL0_Msk
#define GPIO_AFRL_AFSEL1_Pos                                (4U)
#define GPIO_AFRL_AFSEL1_Msk                                (0xFUL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL1                                    GPIO_AFRL_AFSEL1_Msk
#define GPIO_AFRL_AFSEL2_Pos                                (8U)
#define GPIO_AFRL_AFSEL2_Msk                                (0xFUL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2                                    GPIO_AFRL_AFSEL2_Msk
#define GPIO_AFRL_AFSEL3_Pos                                (12U)
#define GPIO_AFRL_AFSEL3_Msk                                (0xFUL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL3                                    GPIO_AFRL_AFSEL3_Msk
#define GPIO_AFRL_AFSEL4_Pos                                (16U)
#define GPIO_AFRL_AFSEL4_Msk                                (0xFUL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL4                                    GPIO_AFRL_AFSEL4_Msk
#define GPIO_AFRL_AFSEL5_Pos                                (20U)
#define GPIO_AFRL_AFSEL5_Msk                                (0xFUL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL5                                    GPIO_AFRL_AFSEL5_Msk
#define GPIO_AFRL_AFSEL6_Pos                                (24U)
#define GPIO_AFRL_AFSEL6_Msk                                (0xFUL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL6                                    GPIO_AFRL_AFSEL6_Msk
#define GPIO_AFRL_AFSEL7_Pos                                (28U)
#define GPIO_AFRL_AFSEL7_Msk                                (0xFUL << GPIO_AFRL_AFSEL7_Pos)
#define GPIO_AFRL_AFSEL7                                    GPIO_AFRL_AFSEL7_Msk

// GPIO_AFRH
#define GPIO_AFRH_AFSEL8_Pos                                (0U)
#define GPIO_AFRH_AFSEL8_Msk                                (0xFUL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL8                                    GPIO_AFRH_AFSEL8_Msk
#define GPIO_AFRH_AFSEL9_Pos                                (4U)
#define GPIO_AFRH_AFSEL9_Msk                                (0xFUL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL9                                    GPIO_AFRH_AFSEL9_Msk
#define GPIO_AFRH_AFSEL10_Pos                               (8U)
#define GPIO_AFRH_AFSEL10_Msk                               (0xFUL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL10                                   GPIO_AFRH_AFSEL10_Msk
#define GPIO_AFRH_AFSEL11_Pos                               (12U)
#define GPIO_AFRH_AFSEL11_Msk                               (0xFUL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL11                                   GPIO_AFRH_AFSEL11_Msk
#define GPIO_AFRH_AFSEL12_Pos                               (16U)
#define GPIO_AFRH_AFSEL12_Msk                               (0xFUL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL12                                   GPIO_AFRH_AFSEL12_Msk
#define GPIO_AFRH_AFSEL13_Pos                               (20U)
#define GPIO_AFRH_AFSEL13_Msk                               (0xFUL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL13                                   GPIO_AFRH_AFSEL13_Msk
#define GPIO_AFRH_AFSEL14_Pos                               (24U)
#define GPIO_AFRH_AFSEL14_Msk                               (0xFUL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL14                                   GPIO_AFRH_AFSEL14_Msk
#define GPIO_AFRH_AFSEL15_Pos                               (28U)
#define GPIO_AFRH_AFSEL15_Msk                               (0xFUL << GPIO_AFRH_AFSEL15_Pos)
#define GPIO_AFRH_AFSEL15                                   GPIO_AFRH_AFSEL15_Msk

// GPIO_HIGHIE
#define GPIO_HIGHIE_PIN0_Pos                                (0U)
#define GPIO_HIGHIE_PIN0_Msk                                (0x1UL << GPIO_HIGHIE_PIN0_Pos)
#define GPIO_HIGHIE_PIN0                                    GPIO_HIGHIE_PIN0_Msk
#define GPIO_HIGHIE_PIN1_Pos                                (1U)
#define GPIO_HIGHIE_PIN1_Msk                                (0x1UL << GPIO_HIGHIE_PIN1_Pos)
#define GPIO_HIGHIE_PIN1                                    GPIO_HIGHIE_PIN1_Msk
#define GPIO_HIGHIE_PIN2_Pos                                (2U)
#define GPIO_HIGHIE_PIN2_Msk                                (0x1UL << GPIO_HIGHIE_PIN2_Pos)
#define GPIO_HIGHIE_PIN2                                    GPIO_HIGHIE_PIN2_Msk
#define GPIO_HIGHIE_PIN3_Pos                                (3U)
#define GPIO_HIGHIE_PIN3_Msk                                (0x1UL << GPIO_HIGHIE_PIN3_Pos)
#define GPIO_HIGHIE_PIN3                                    GPIO_HIGHIE_PIN3_Msk
#define GPIO_HIGHIE_PIN4_Pos                                (4U)
#define GPIO_HIGHIE_PIN4_Msk                                (0x1UL << GPIO_HIGHIE_PIN4_Pos)
#define GPIO_HIGHIE_PIN4                                    GPIO_HIGHIE_PIN4_Msk
#define GPIO_HIGHIE_PIN5_Pos                                (5U)
#define GPIO_HIGHIE_PIN5_Msk                                (0x1UL << GPIO_HIGHIE_PIN5_Pos)
#define GPIO_HIGHIE_PIN5                                    GPIO_HIGHIE_PIN5_Msk
#define GPIO_HIGHIE_PIN6_Pos                                (6U)
#define GPIO_HIGHIE_PIN6_Msk                                (0x1UL << GPIO_HIGHIE_PIN6_Pos)
#define GPIO_HIGHIE_PIN6                                    GPIO_HIGHIE_PIN6_Msk
#define GPIO_HIGHIE_PIN7_Pos                                (7U)
#define GPIO_HIGHIE_PIN7_Msk                                (0x1UL << GPIO_HIGHIE_PIN7_Pos)
#define GPIO_HIGHIE_PIN7                                    GPIO_HIGHIE_PIN7_Msk
#define GPIO_HIGHIE_PIN8_Pos                                (8U)
#define GPIO_HIGHIE_PIN8_Msk                                (0x1UL << GPIO_HIGHIE_PIN8_Pos)
#define GPIO_HIGHIE_PIN8                                    GPIO_HIGHIE_PIN8_Msk
#define GPIO_HIGHIE_PIN9_Pos                                (9U)
#define GPIO_HIGHIE_PIN9_Msk                                (0x1UL << GPIO_HIGHIE_PIN9_Pos)
#define GPIO_HIGHIE_PIN9                                    GPIO_HIGHIE_PIN9_Msk
#define GPIO_HIGHIE_PIN10_Pos                               (10U)
#define GPIO_HIGHIE_PIN10_Msk                               (0x1UL << GPIO_HIGHIE_PIN10_Pos)
#define GPIO_HIGHIE_PIN10                                   GPIO_HIGHIE_PIN10_Msk
#define GPIO_HIGHIE_PIN11_Pos                               (11U)
#define GPIO_HIGHIE_PIN11_Msk                               (0x1UL << GPIO_HIGHIE_PIN11_Pos)
#define GPIO_HIGHIE_PIN11                                   GPIO_HIGHIE_PIN11_Msk
#define GPIO_HIGHIE_PIN12_Pos                               (12U)
#define GPIO_HIGHIE_PIN12_Msk                               (0x1UL << GPIO_HIGHIE_PIN12_Pos)
#define GPIO_HIGHIE_PIN12                                   GPIO_HIGHIE_PIN12_Msk
#define GPIO_HIGHIE_PIN13_Pos                               (13U)
#define GPIO_HIGHIE_PIN13_Msk                               (0x1UL << GPIO_HIGHIE_PIN13_Pos)
#define GPIO_HIGHIE_PIN13                                   GPIO_HIGHIE_PIN13_Msk
#define GPIO_HIGHIE_PIN14_Pos                               (14U)
#define GPIO_HIGHIE_PIN14_Msk                               (0x1UL << GPIO_HIGHIE_PIN14_Pos)
#define GPIO_HIGHIE_PIN14                                   GPIO_HIGHIE_PIN14_Msk
#define GPIO_HIGHIE_PIN15_Pos                               (15U)
#define GPIO_HIGHIE_PIN15_Msk                               (0x1UL << GPIO_HIGHIE_PIN15_Pos)
#define GPIO_HIGHIE_PIN15                                   GPIO_HIGHIE_PIN15_Msk

// GPIO_LOWIE
#define GPIO_LOWIE_PIN0_Pos                                 (0U)
#define GPIO_LOWIE_PIN0_Msk                                 (0x1UL << GPIO_LOWIE_PIN0_Pos)
#define GPIO_LOWIE_PIN0                                     GPIO_LOWIE_PIN0_Msk
#define GPIO_LOWIE_PIN1_Pos                                 (1U)
#define GPIO_LOWIE_PIN1_Msk                                 (0x1UL << GPIO_LOWIE_PIN1_Pos)
#define GPIO_LOWIE_PIN1                                     GPIO_LOWIE_PIN1_Msk
#define GPIO_LOWIE_PIN2_Pos                                 (2U)
#define GPIO_LOWIE_PIN2_Msk                                 (0x1UL << GPIO_LOWIE_PIN2_Pos)
#define GPIO_LOWIE_PIN2                                     GPIO_LOWIE_PIN2_Msk
#define GPIO_LOWIE_PIN3_Pos                                 (3U)
#define GPIO_LOWIE_PIN3_Msk                                 (0x1UL << GPIO_LOWIE_PIN3_Pos)
#define GPIO_LOWIE_PIN3                                     GPIO_LOWIE_PIN3_Msk
#define GPIO_LOWIE_PIN4_Pos                                 (4U)
#define GPIO_LOWIE_PIN4_Msk                                 (0x1UL << GPIO_LOWIE_PIN4_Pos)
#define GPIO_LOWIE_PIN4                                     GPIO_LOWIE_PIN4_Msk
#define GPIO_LOWIE_PIN5_Pos                                 (5U)
#define GPIO_LOWIE_PIN5_Msk                                 (0x1UL << GPIO_LOWIE_PIN5_Pos)
#define GPIO_LOWIE_PIN5                                     GPIO_LOWIE_PIN5_Msk
#define GPIO_LOWIE_PIN6_Pos                                 (6U)
#define GPIO_LOWIE_PIN6_Msk                                 (0x1UL << GPIO_LOWIE_PIN6_Pos)
#define GPIO_LOWIE_PIN6                                     GPIO_LOWIE_PIN6_Msk
#define GPIO_LOWIE_PIN7_Pos                                 (7U)
#define GPIO_LOWIE_PIN7_Msk                                 (0x1UL << GPIO_LOWIE_PIN7_Pos)
#define GPIO_LOWIE_PIN7                                     GPIO_LOWIE_PIN7_Msk
#define GPIO_LOWIE_PIN8_Pos                                 (8U)
#define GPIO_LOWIE_PIN8_Msk                                 (0x1UL << GPIO_LOWIE_PIN8_Pos)
#define GPIO_LOWIE_PIN8                                     GPIO_LOWIE_PIN8_Msk
#define GPIO_LOWIE_PIN9_Pos                                 (9U)
#define GPIO_LOWIE_PIN9_Msk                                 (0x1UL << GPIO_LOWIE_PIN9_Pos)
#define GPIO_LOWIE_PIN9                                     GPIO_LOWIE_PIN9_Msk
#define GPIO_LOWIE_PIN10_Pos                                (10U)
#define GPIO_LOWIE_PIN10_Msk                                (0x1UL << GPIO_LOWIE_PIN10_Pos)
#define GPIO_LOWIE_PIN10                                    GPIO_LOWIE_PIN10_Msk
#define GPIO_LOWIE_PIN11_Pos                                (11U)
#define GPIO_LOWIE_PIN11_Msk                                (0x1UL << GPIO_LOWIE_PIN11_Pos)
#define GPIO_LOWIE_PIN11                                    GPIO_LOWIE_PIN11_Msk
#define GPIO_LOWIE_PIN12_Pos                                (12U)
#define GPIO_LOWIE_PIN12_Msk                                (0x1UL << GPIO_LOWIE_PIN12_Pos)
#define GPIO_LOWIE_PIN12                                    GPIO_LOWIE_PIN12_Msk
#define GPIO_LOWIE_PIN13_Pos                                (13U)
#define GPIO_LOWIE_PIN13_Msk                                (0x1UL << GPIO_LOWIE_PIN13_Pos)
#define GPIO_LOWIE_PIN13                                    GPIO_LOWIE_PIN13_Msk
#define GPIO_LOWIE_PIN14_Pos                                (14U)
#define GPIO_LOWIE_PIN14_Msk                                (0x1UL << GPIO_LOWIE_PIN14_Pos)
#define GPIO_LOWIE_PIN14                                    GPIO_LOWIE_PIN14_Msk
#define GPIO_LOWIE_PIN15_Pos                                (15U)
#define GPIO_LOWIE_PIN15_Msk                                (0x1UL << GPIO_LOWIE_PIN15_Pos)
#define GPIO_LOWIE_PIN15                                    GPIO_LOWIE_PIN15_Msk

// GPIO_RISEIE
#define GPIO_RISEIE_PIN0_Pos                                (0U)
#define GPIO_RISEIE_PIN0_Msk                                (0x1UL << GPIO_RISEIE_PIN0_Pos)
#define GPIO_RISEIE_PIN0                                    GPIO_RISEIE_PIN0_Msk
#define GPIO_RISEIE_PIN1_Pos                                (1U)
#define GPIO_RISEIE_PIN1_Msk                                (0x1UL << GPIO_RISEIE_PIN1_Pos)
#define GPIO_RISEIE_PIN1                                    GPIO_RISEIE_PIN1_Msk
#define GPIO_RISEIE_PIN2_Pos                                (2U)
#define GPIO_RISEIE_PIN2_Msk                                (0x1UL << GPIO_RISEIE_PIN2_Pos)
#define GPIO_RISEIE_PIN2                                    GPIO_RISEIE_PIN2_Msk
#define GPIO_RISEIE_PIN3_Pos                                (3U)
#define GPIO_RISEIE_PIN3_Msk                                (0x1UL << GPIO_RISEIE_PIN3_Pos)
#define GPIO_RISEIE_PIN3                                    GPIO_RISEIE_PIN3_Msk
#define GPIO_RISEIE_PIN4_Pos                                (4U)
#define GPIO_RISEIE_PIN4_Msk                                (0x1UL << GPIO_RISEIE_PIN4_Pos)
#define GPIO_RISEIE_PIN4                                    GPIO_RISEIE_PIN4_Msk
#define GPIO_RISEIE_PIN5_Pos                                (5U)
#define GPIO_RISEIE_PIN5_Msk                                (0x1UL << GPIO_RISEIE_PIN5_Pos)
#define GPIO_RISEIE_PIN5                                    GPIO_RISEIE_PIN5_Msk
#define GPIO_RISEIE_PIN6_Pos                                (6U)
#define GPIO_RISEIE_PIN6_Msk                                (0x1UL << GPIO_RISEIE_PIN6_Pos)
#define GPIO_RISEIE_PIN6                                    GPIO_RISEIE_PIN6_Msk
#define GPIO_RISEIE_PIN7_Pos                                (7U)
#define GPIO_RISEIE_PIN7_Msk                                (0x1UL << GPIO_RISEIE_PIN7_Pos)
#define GPIO_RISEIE_PIN7                                    GPIO_RISEIE_PIN7_Msk
#define GPIO_RISEIE_PIN8_Pos                                (8U)
#define GPIO_RISEIE_PIN8_Msk                                (0x1UL << GPIO_RISEIE_PIN8_Pos)
#define GPIO_RISEIE_PIN8                                    GPIO_RISEIE_PIN8_Msk
#define GPIO_RISEIE_PIN9_Pos                                (9U)
#define GPIO_RISEIE_PIN9_Msk                                (0x1UL << GPIO_RISEIE_PIN9_Pos)
#define GPIO_RISEIE_PIN9                                    GPIO_RISEIE_PIN9_Msk
#define GPIO_RISEIE_PIN10_Pos                               (10U)
#define GPIO_RISEIE_PIN10_Msk                               (0x1UL << GPIO_RISEIE_PIN10_Pos)
#define GPIO_RISEIE_PIN10                                   GPIO_RISEIE_PIN10_Msk
#define GPIO_RISEIE_PIN11_Pos                               (11U)
#define GPIO_RISEIE_PIN11_Msk                               (0x1UL << GPIO_RISEIE_PIN11_Pos)
#define GPIO_RISEIE_PIN11                                   GPIO_RISEIE_PIN11_Msk
#define GPIO_RISEIE_PIN12_Pos                               (12U)
#define GPIO_RISEIE_PIN12_Msk                               (0x1UL << GPIO_RISEIE_PIN12_Pos)
#define GPIO_RISEIE_PIN12                                   GPIO_RISEIE_PIN12_Msk
#define GPIO_RISEIE_PIN13_Pos                               (13U)
#define GPIO_RISEIE_PIN13_Msk                               (0x1UL << GPIO_RISEIE_PIN13_Pos)
#define GPIO_RISEIE_PIN13                                   GPIO_RISEIE_PIN13_Msk
#define GPIO_RISEIE_PIN14_Pos                               (14U)
#define GPIO_RISEIE_PIN14_Msk                               (0x1UL << GPIO_RISEIE_PIN14_Pos)
#define GPIO_RISEIE_PIN14                                   GPIO_RISEIE_PIN14_Msk
#define GPIO_RISEIE_PIN15_Pos                               (15U)
#define GPIO_RISEIE_PIN15_Msk                               (0x1UL << GPIO_RISEIE_PIN15_Pos)
#define GPIO_RISEIE_PIN15                                   GPIO_RISEIE_PIN15_Msk

// GPIO_FALLIE
#define GPIO_FALLIE_PIN0_Pos                                (0U)
#define GPIO_FALLIE_PIN0_Msk                                (0x1UL << GPIO_FALLIE_PIN0_Pos)
#define GPIO_FALLIE_PIN0                                    GPIO_FALLIE_PIN0_Msk
#define GPIO_FALLIE_PIN1_Pos                                (1U)
#define GPIO_FALLIE_PIN1_Msk                                (0x1UL << GPIO_FALLIE_PIN1_Pos)
#define GPIO_FALLIE_PIN1                                    GPIO_FALLIE_PIN1_Msk
#define GPIO_FALLIE_PIN2_Pos                                (2U)
#define GPIO_FALLIE_PIN2_Msk                                (0x1UL << GPIO_FALLIE_PIN2_Pos)
#define GPIO_FALLIE_PIN2                                    GPIO_FALLIE_PIN2_Msk
#define GPIO_FALLIE_PIN3_Pos                                (3U)
#define GPIO_FALLIE_PIN3_Msk                                (0x1UL << GPIO_FALLIE_PIN3_Pos)
#define GPIO_FALLIE_PIN3                                    GPIO_FALLIE_PIN3_Msk
#define GPIO_FALLIE_PIN4_Pos                                (4U)
#define GPIO_FALLIE_PIN4_Msk                                (0x1UL << GPIO_FALLIE_PIN4_Pos)
#define GPIO_FALLIE_PIN4                                    GPIO_FALLIE_PIN4_Msk
#define GPIO_FALLIE_PIN5_Pos                                (5U)
#define GPIO_FALLIE_PIN5_Msk                                (0x1UL << GPIO_FALLIE_PIN5_Pos)
#define GPIO_FALLIE_PIN5                                    GPIO_FALLIE_PIN5_Msk
#define GPIO_FALLIE_PIN6_Pos                                (6U)
#define GPIO_FALLIE_PIN6_Msk                                (0x1UL << GPIO_FALLIE_PIN6_Pos)
#define GPIO_FALLIE_PIN6                                    GPIO_FALLIE_PIN6_Msk
#define GPIO_FALLIE_PIN7_Pos                                (7U)
#define GPIO_FALLIE_PIN7_Msk                                (0x1UL << GPIO_FALLIE_PIN7_Pos)
#define GPIO_FALLIE_PIN7                                    GPIO_FALLIE_PIN7_Msk
#define GPIO_FALLIE_PIN8_Pos                                (8U)
#define GPIO_FALLIE_PIN8_Msk                                (0x1UL << GPIO_FALLIE_PIN8_Pos)
#define GPIO_FALLIE_PIN8                                    GPIO_FALLIE_PIN8_Msk
#define GPIO_FALLIE_PIN9_Pos                                (9U)
#define GPIO_FALLIE_PIN9_Msk                                (0x1UL << GPIO_FALLIE_PIN9_Pos)
#define GPIO_FALLIE_PIN9                                    GPIO_FALLIE_PIN9_Msk
#define GPIO_FALLIE_PIN10_Pos                               (10U)
#define GPIO_FALLIE_PIN10_Msk                               (0x1UL << GPIO_FALLIE_PIN10_Pos)
#define GPIO_FALLIE_PIN10                                   GPIO_FALLIE_PIN10_Msk
#define GPIO_FALLIE_PIN11_Pos                               (11U)
#define GPIO_FALLIE_PIN11_Msk                               (0x1UL << GPIO_FALLIE_PIN11_Pos)
#define GPIO_FALLIE_PIN11                                   GPIO_FALLIE_PIN11_Msk
#define GPIO_FALLIE_PIN12_Pos                               (12U)
#define GPIO_FALLIE_PIN12_Msk                               (0x1UL << GPIO_FALLIE_PIN12_Pos)
#define GPIO_FALLIE_PIN12                                   GPIO_FALLIE_PIN12_Msk
#define GPIO_FALLIE_PIN13_Pos                               (13U)
#define GPIO_FALLIE_PIN13_Msk                               (0x1UL << GPIO_FALLIE_PIN13_Pos)
#define GPIO_FALLIE_PIN13                                   GPIO_FALLIE_PIN13_Msk
#define GPIO_FALLIE_PIN14_Pos                               (14U)
#define GPIO_FALLIE_PIN14_Msk                               (0x1UL << GPIO_FALLIE_PIN14_Pos)
#define GPIO_FALLIE_PIN14                                   GPIO_FALLIE_PIN14_Msk
#define GPIO_FALLIE_PIN15_Pos                               (15U)
#define GPIO_FALLIE_PIN15_Msk                               (0x1UL << GPIO_FALLIE_PIN15_Pos)
#define GPIO_FALLIE_PIN15                                   GPIO_FALLIE_PIN15_Msk

// GPIO_IFR
#define GPIO_IFR_PIN0_Pos                                   (0U)
#define GPIO_IFR_PIN0_Msk                                   (0x1UL << GPIO_IFR_PIN0_Pos)
#define GPIO_IFR_PIN0                                       GPIO_IFR_PIN0_Msk
#define GPIO_IFR_PIN1_Pos                                   (1U)
#define GPIO_IFR_PIN1_Msk                                   (0x1UL << GPIO_IFR_PIN1_Pos)
#define GPIO_IFR_PIN1                                       GPIO_IFR_PIN1_Msk
#define GPIO_IFR_PIN2_Pos                                   (2U)
#define GPIO_IFR_PIN2_Msk                                   (0x1UL << GPIO_IFR_PIN2_Pos)
#define GPIO_IFR_PIN2                                       GPIO_IFR_PIN2_Msk
#define GPIO_IFR_PIN3_Pos                                   (3U)
#define GPIO_IFR_PIN3_Msk                                   (0x1UL << GPIO_IFR_PIN3_Pos)
#define GPIO_IFR_PIN3                                       GPIO_IFR_PIN3_Msk
#define GPIO_IFR_PIN4_Pos                                   (4U)
#define GPIO_IFR_PIN4_Msk                                   (0x1UL << GPIO_IFR_PIN4_Pos)
#define GPIO_IFR_PIN4                                       GPIO_IFR_PIN4_Msk
#define GPIO_IFR_PIN5_Pos                                   (5U)
#define GPIO_IFR_PIN5_Msk                                   (0x1UL << GPIO_IFR_PIN5_Pos)
#define GPIO_IFR_PIN5                                       GPIO_IFR_PIN5_Msk
#define GPIO_IFR_PIN6_Pos                                   (6U)
#define GPIO_IFR_PIN6_Msk                                   (0x1UL << GPIO_IFR_PIN6_Pos)
#define GPIO_IFR_PIN6                                       GPIO_IFR_PIN6_Msk
#define GPIO_IFR_PIN7_Pos                                   (7U)
#define GPIO_IFR_PIN7_Msk                                   (0x1UL << GPIO_IFR_PIN7_Pos)
#define GPIO_IFR_PIN7                                       GPIO_IFR_PIN7_Msk
#define GPIO_IFR_PIN8_Pos                                   (8U)
#define GPIO_IFR_PIN8_Msk                                   (0x1UL << GPIO_IFR_PIN8_Pos)
#define GPIO_IFR_PIN8                                       GPIO_IFR_PIN8_Msk
#define GPIO_IFR_PIN9_Pos                                   (9U)
#define GPIO_IFR_PIN9_Msk                                   (0x1UL << GPIO_IFR_PIN9_Pos)
#define GPIO_IFR_PIN9                                       GPIO_IFR_PIN9_Msk
#define GPIO_IFR_PIN10_Pos                                  (10U)
#define GPIO_IFR_PIN10_Msk                                  (0x1UL << GPIO_IFR_PIN10_Pos)
#define GPIO_IFR_PIN10                                      GPIO_IFR_PIN10_Msk
#define GPIO_IFR_PIN11_Pos                                  (11U)
#define GPIO_IFR_PIN11_Msk                                  (0x1UL << GPIO_IFR_PIN11_Pos)
#define GPIO_IFR_PIN11                                      GPIO_IFR_PIN11_Msk
#define GPIO_IFR_PIN12_Pos                                  (12U)
#define GPIO_IFR_PIN12_Msk                                  (0x1UL << GPIO_IFR_PIN12_Pos)
#define GPIO_IFR_PIN12                                      GPIO_IFR_PIN12_Msk
#define GPIO_IFR_PIN13_Pos                                  (13U)
#define GPIO_IFR_PIN13_Msk                                  (0x1UL << GPIO_IFR_PIN13_Pos)
#define GPIO_IFR_PIN13                                      GPIO_IFR_PIN13_Msk
#define GPIO_IFR_PIN14_Pos                                  (14U)
#define GPIO_IFR_PIN14_Msk                                  (0x1UL << GPIO_IFR_PIN14_Pos)
#define GPIO_IFR_PIN14                                      GPIO_IFR_PIN14_Msk
#define GPIO_IFR_PIN15_Pos                                  (15U)
#define GPIO_IFR_PIN15_Msk                                  (0x1UL << GPIO_IFR_PIN15_Pos)
#define GPIO_IFR_PIN15                                      GPIO_IFR_PIN15_Msk

// GPIO_ICR
#define GPIO_ICR_PIN0_Pos                                   (0U)
#define GPIO_ICR_PIN0_Msk                                   (0x1UL << GPIO_ICR_PIN0_Pos)
#define GPIO_ICR_PIN0                                       GPIO_ICR_PIN0_Msk
#define GPIO_ICR_PIN1_Pos                                   (1U)
#define GPIO_ICR_PIN1_Msk                                   (0x1UL << GPIO_ICR_PIN1_Pos)
#define GPIO_ICR_PIN1                                       GPIO_ICR_PIN1_Msk
#define GPIO_ICR_PIN2_Pos                                   (2U)
#define GPIO_ICR_PIN2_Msk                                   (0x1UL << GPIO_ICR_PIN2_Pos)
#define GPIO_ICR_PIN2                                       GPIO_ICR_PIN2_Msk
#define GPIO_ICR_PIN3_Pos                                   (3U)
#define GPIO_ICR_PIN3_Msk                                   (0x1UL << GPIO_ICR_PIN3_Pos)
#define GPIO_ICR_PIN3                                       GPIO_ICR_PIN3_Msk
#define GPIO_ICR_PIN4_Pos                                   (4U)
#define GPIO_ICR_PIN4_Msk                                   (0x1UL << GPIO_ICR_PIN4_Pos)
#define GPIO_ICR_PIN4                                       GPIO_ICR_PIN4_Msk
#define GPIO_ICR_PIN5_Pos                                   (5U)
#define GPIO_ICR_PIN5_Msk                                   (0x1UL << GPIO_ICR_PIN5_Pos)
#define GPIO_ICR_PIN5                                       GPIO_ICR_PIN5_Msk
#define GPIO_ICR_PIN6_Pos                                   (6U)
#define GPIO_ICR_PIN6_Msk                                   (0x1UL << GPIO_ICR_PIN6_Pos)
#define GPIO_ICR_PIN6                                       GPIO_ICR_PIN6_Msk
#define GPIO_ICR_PIN7_Pos                                   (7U)
#define GPIO_ICR_PIN7_Msk                                   (0x1UL << GPIO_ICR_PIN7_Pos)
#define GPIO_ICR_PIN7                                       GPIO_ICR_PIN7_Msk
#define GPIO_ICR_PIN8_Pos                                   (8U)
#define GPIO_ICR_PIN8_Msk                                   (0x1UL << GPIO_ICR_PIN8_Pos)
#define GPIO_ICR_PIN8                                       GPIO_ICR_PIN8_Msk
#define GPIO_ICR_PIN9_Pos                                   (9U)
#define GPIO_ICR_PIN9_Msk                                   (0x1UL << GPIO_ICR_PIN9_Pos)
#define GPIO_ICR_PIN9                                       GPIO_ICR_PIN9_Msk
#define GPIO_ICR_PIN10_Pos                                  (10U)
#define GPIO_ICR_PIN10_Msk                                  (0x1UL << GPIO_ICR_PIN10_Pos)
#define GPIO_ICR_PIN10                                      GPIO_ICR_PIN10_Msk
#define GPIO_ICR_PIN11_Pos                                  (11U)
#define GPIO_ICR_PIN11_Msk                                  (0x1UL << GPIO_ICR_PIN11_Pos)
#define GPIO_ICR_PIN11                                      GPIO_ICR_PIN11_Msk
#define GPIO_ICR_PIN12_Pos                                  (12U)
#define GPIO_ICR_PIN12_Msk                                  (0x1UL << GPIO_ICR_PIN12_Pos)
#define GPIO_ICR_PIN12                                      GPIO_ICR_PIN12_Msk
#define GPIO_ICR_PIN13_Pos                                  (13U)
#define GPIO_ICR_PIN13_Msk                                  (0x1UL << GPIO_ICR_PIN13_Pos)
#define GPIO_ICR_PIN13                                      GPIO_ICR_PIN13_Msk
#define GPIO_ICR_PIN14_Pos                                  (14U)
#define GPIO_ICR_PIN14_Msk                                  (0x1UL << GPIO_ICR_PIN14_Pos)
#define GPIO_ICR_PIN14                                      GPIO_ICR_PIN14_Msk
#define GPIO_ICR_PIN15_Pos                                  (15U)
#define GPIO_ICR_PIN15_Msk                                  (0x1UL << GPIO_ICR_PIN15_Pos)
#define GPIO_ICR_PIN15                                      GPIO_ICR_PIN15_Msk



//********************    Bits Define For Peripheral GPIOAUX    ********************//
// GPIOAUX_CR0
#define GPIOAUX_CR0_PCLKDIV_Pos                             (0U)
#define GPIOAUX_CR0_PCLKDIV_Msk                             (0x7UL << GPIOAUX_CR0_PCLKDIV_Pos)
#define GPIOAUX_CR0_PCLKDIV                                 GPIOAUX_CR0_PCLKDIV_Msk
#define GPIOAUX_CR0_MCODIV_Pos                              (8U)
#define GPIOAUX_CR0_MCODIV_Msk                              (0x7UL << GPIOAUX_CR0_MCODIV_Pos)
#define GPIOAUX_CR0_MCODIV                                  GPIOAUX_CR0_MCODIV_Msk
#define GPIOAUX_CR0_MCOSEL_Pos                              (12U)
#define GPIOAUX_CR0_MCOSEL_Msk                              (0x7UL << GPIOAUX_CR0_MCOSEL_Pos)
#define GPIOAUX_CR0_MCOSEL                                  GPIOAUX_CR0_MCOSEL_Msk

// GPIOAUX_CR1
#define GPIOAUX_CR1_ATIM0ETR_Pos                            (0U)
#define GPIOAUX_CR1_ATIM0ETR_Msk                            (0x7UL << GPIOAUX_CR1_ATIM0ETR_Pos)
#define GPIOAUX_CR1_ATIM0ETR                                GPIOAUX_CR1_ATIM0ETR_Msk
#define GPIOAUX_CR1_CTIM0ETR_Pos                            (4U)
#define GPIOAUX_CR1_CTIM0ETR_Msk                            (0x7UL << GPIOAUX_CR1_CTIM0ETR_Pos)
#define GPIOAUX_CR1_CTIM0ETR                                GPIOAUX_CR1_CTIM0ETR_Msk
#define GPIOAUX_CR1_CTIM1ETR_Pos                            (8U)
#define GPIOAUX_CR1_CTIM1ETR_Msk                            (0x7UL << GPIOAUX_CR1_CTIM1ETR_Pos)
#define GPIOAUX_CR1_CTIM1ETR                                GPIOAUX_CR1_CTIM1ETR_Msk
#define GPIOAUX_CR1_ATIM3ETR_Pos                            (12U)
#define GPIOAUX_CR1_ATIM3ETR_Msk                            (0x7UL << GPIOAUX_CR1_ATIM3ETR_Pos)
#define GPIOAUX_CR1_ATIM3ETR                                GPIOAUX_CR1_ATIM3ETR_Msk

// GPIOAUX_CR2
#define GPIOAUX_CR2_ATIM0CAP0_Pos                           (0U)
#define GPIOAUX_CR2_ATIM0CAP0_Msk                           (0x7UL << GPIOAUX_CR2_ATIM0CAP0_Pos)
#define GPIOAUX_CR2_ATIM0CAP0                               GPIOAUX_CR2_ATIM0CAP0_Msk
#define GPIOAUX_CR2_CTIM0CAP3_Pos                           (4U)
#define GPIOAUX_CR2_CTIM0CAP3_Msk                           (0x7UL << GPIOAUX_CR2_CTIM0CAP3_Pos)
#define GPIOAUX_CR2_CTIM0CAP3                               GPIOAUX_CR2_CTIM0CAP3_Msk
#define GPIOAUX_CR2_CTIM1CAP3_Pos                           (8U)
#define GPIOAUX_CR2_CTIM1CAP3_Msk                           (0x7UL << GPIOAUX_CR2_CTIM1CAP3_Pos)
#define GPIOAUX_CR2_CTIM1CAP3                               GPIOAUX_CR2_CTIM1CAP3_Msk
#define GPIOAUX_CR2_ATIM3CAP3_Pos                           (12U)
#define GPIOAUX_CR2_ATIM3CAP3_Msk                           (0x7UL << GPIOAUX_CR2_ATIM3CAP3_Pos)
#define GPIOAUX_CR2_ATIM3CAP3                               GPIOAUX_CR2_ATIM3CAP3_Msk



//********************    Bits Define For Peripheral GTIM    ********************//
// GTIM_ARR
#define GTIM_ARR_ARR_Pos                                    (0U)
#define GTIM_ARR_ARR_Msk                                    (0xFFFFUL << GTIM_ARR_ARR_Pos)
#define GTIM_ARR_ARR                                        GTIM_ARR_ARR_Msk

// GTIM_CNT
#define GTIM_CNT_CNT_Pos                                    (0U)
#define GTIM_CNT_CNT_Msk                                    (0xFFFFUL << GTIM_CNT_CNT_Pos)
#define GTIM_CNT_CNT                                        GTIM_CNT_CNT_Msk

// GTIM_CMMR
#define GTIM_CMMR_CC0M_Pos                                  (0U)
#define GTIM_CMMR_CC0M_Msk                                  (0x7UL << GTIM_CMMR_CC0M_Pos)
#define GTIM_CMMR_CC0M                                      GTIM_CMMR_CC0M_Msk
#define GTIM_CMMR_CC1M_Pos                                  (4U)
#define GTIM_CMMR_CC1M_Msk                                  (0x7UL << GTIM_CMMR_CC1M_Pos)
#define GTIM_CMMR_CC1M                                      GTIM_CMMR_CC1M_Msk
#define GTIM_CMMR_CC2M_Pos                                  (8U)
#define GTIM_CMMR_CC2M_Msk                                  (0x7UL << GTIM_CMMR_CC2M_Pos)
#define GTIM_CMMR_CC2M                                      GTIM_CMMR_CC2M_Msk
#define GTIM_CMMR_CC3M_Pos                                  (12U)
#define GTIM_CMMR_CC3M_Msk                                  (0x7UL << GTIM_CMMR_CC3M_Pos)
#define GTIM_CMMR_CC3M                                      GTIM_CMMR_CC3M_Msk

// GTIM_CR1
#define GTIM_CR1_ETRFLT_Pos                                 (4U)
#define GTIM_CR1_ETRFLT_Msk                                 (0x7UL << GTIM_CR1_ETRFLT_Pos)
#define GTIM_CR1_ETRFLT                                     GTIM_CR1_ETRFLT_Msk

// GTIM_CR0
#define GTIM_CR0_CEN_Pos                                    (0U)
#define GTIM_CR0_CEN_Msk                                    (0x1UL << GTIM_CR0_CEN_Pos)
#define GTIM_CR0_CEN                                        GTIM_CR0_CEN_Msk
#define GTIM_CR0_MD_Pos                                     (1U)
#define GTIM_CR0_MD_Msk                                     (0x3UL << GTIM_CR0_MD_Pos)
#define GTIM_CR0_MD                                         GTIM_CR0_MD_Msk
#define GTIM_CR0_TOGEN_Pos                                  (3U)
#define GTIM_CR0_TOGEN_Msk                                  (0x1UL << GTIM_CR0_TOGEN_Pos)
#define GTIM_CR0_TOGEN                                      GTIM_CR0_TOGEN_Msk
#define GTIM_CR0_PRS_Pos                                    (4U)
#define GTIM_CR0_PRS_Msk                                    (0xFUL << GTIM_CR0_PRS_Pos)
#define GTIM_CR0_PRS                                        GTIM_CR0_PRS_Msk
#define GTIM_CR0_OST_Pos                                    (8U)
#define GTIM_CR0_OST_Msk                                    (0x1UL << GTIM_CR0_OST_Pos)
#define GTIM_CR0_OST                                        GTIM_CR0_OST_Msk
#define GTIM_CR0_TRS_Pos                                    (9U)
#define GTIM_CR0_TRS_Msk                                    (0x3UL << GTIM_CR0_TRS_Pos)
#define GTIM_CR0_TRS                                        GTIM_CR0_TRS_Msk
#define GTIM_CR0_ETP_Pos                                    (11U)
#define GTIM_CR0_ETP_Msk                                    (0x1UL << GTIM_CR0_ETP_Pos)
#define GTIM_CR0_ETP                                        GTIM_CR0_ETP_Msk

// GTIM_IER
#define GTIM_IER_UI_Pos                                     (0U)
#define GTIM_IER_UI_Msk                                     (0x1UL << GTIM_IER_UI_Pos)
#define GTIM_IER_UI                                         GTIM_IER_UI_Msk
#define GTIM_IER_TI_Pos                                     (1U)
#define GTIM_IER_TI_Msk                                     (0x1UL << GTIM_IER_TI_Pos)
#define GTIM_IER_TI                                         GTIM_IER_TI_Msk
#define GTIM_IER_CC0_Pos                                    (2U)
#define GTIM_IER_CC0_Msk                                    (0x1UL << GTIM_IER_CC0_Pos)
#define GTIM_IER_CC0                                        GTIM_IER_CC0_Msk
#define GTIM_IER_CC1_Pos                                    (3U)
#define GTIM_IER_CC1_Msk                                    (0x1UL << GTIM_IER_CC1_Pos)
#define GTIM_IER_CC1                                        GTIM_IER_CC1_Msk
#define GTIM_IER_CC2_Pos                                    (4U)
#define GTIM_IER_CC2_Msk                                    (0x1UL << GTIM_IER_CC2_Pos)
#define GTIM_IER_CC2                                        GTIM_IER_CC2_Msk
#define GTIM_IER_CC3_Pos                                    (5U)
#define GTIM_IER_CC3_Msk                                    (0x1UL << GTIM_IER_CC3_Pos)
#define GTIM_IER_CC3                                        GTIM_IER_CC3_Msk
#define GTIM_IER_DCC0_Pos                                   (6U)
#define GTIM_IER_DCC0_Msk                                   (0x1UL << GTIM_IER_DCC0_Pos)
#define GTIM_IER_DCC0                                       GTIM_IER_DCC0_Msk
#define GTIM_IER_DCC1_Pos                                   (7U)
#define GTIM_IER_DCC1_Msk                                   (0x1UL << GTIM_IER_DCC1_Pos)
#define GTIM_IER_DCC1                                       GTIM_IER_DCC1_Msk
#define GTIM_IER_DCC2_Pos                                   (8U)
#define GTIM_IER_DCC2_Msk                                   (0x1UL << GTIM_IER_DCC2_Pos)
#define GTIM_IER_DCC2                                       GTIM_IER_DCC2_Msk
#define GTIM_IER_DCC3_Pos                                   (9U)
#define GTIM_IER_DCC3_Msk                                   (0x1UL << GTIM_IER_DCC3_Pos)
#define GTIM_IER_DCC3                                       GTIM_IER_DCC3_Msk
#define GTIM_IER_OVTRAD_Pos                                 (10U)
#define GTIM_IER_OVTRAD_Msk                                 (0x1UL << GTIM_IER_OVTRAD_Pos)
#define GTIM_IER_OVTRAD                                     GTIM_IER_OVTRAD_Msk
#define GTIM_IER_C0TRAD_Pos                                 (11U)
#define GTIM_IER_C0TRAD_Msk                                 (0x1UL << GTIM_IER_C0TRAD_Pos)
#define GTIM_IER_C0TRAD                                     GTIM_IER_C0TRAD_Msk

// GTIM_IFR
#define GTIM_IFR_UI_Pos                                     (0U)
#define GTIM_IFR_UI_Msk                                     (0x1UL << GTIM_IFR_UI_Pos)
#define GTIM_IFR_UI                                         GTIM_IFR_UI_Msk
#define GTIM_IFR_TI_Pos                                     (1U)
#define GTIM_IFR_TI_Msk                                     (0x1UL << GTIM_IFR_TI_Pos)
#define GTIM_IFR_TI                                         GTIM_IFR_TI_Msk
#define GTIM_IFR_CC0_Pos                                    (2U)
#define GTIM_IFR_CC0_Msk                                    (0x1UL << GTIM_IFR_CC0_Pos)
#define GTIM_IFR_CC0                                        GTIM_IFR_CC0_Msk
#define GTIM_IFR_CC1_Pos                                    (3U)
#define GTIM_IFR_CC1_Msk                                    (0x1UL << GTIM_IFR_CC1_Pos)
#define GTIM_IFR_CC1                                        GTIM_IFR_CC1_Msk
#define GTIM_IFR_CC2_Pos                                    (4U)
#define GTIM_IFR_CC2_Msk                                    (0x1UL << GTIM_IFR_CC2_Pos)
#define GTIM_IFR_CC2                                        GTIM_IFR_CC2_Msk
#define GTIM_IFR_CC3_Pos                                    (5U)
#define GTIM_IFR_CC3_Msk                                    (0x1UL << GTIM_IFR_CC3_Pos)
#define GTIM_IFR_CC3                                        GTIM_IFR_CC3_Msk

// GTIM_ICR
#define GTIM_ICR_UI_Pos                                     (0U)
#define GTIM_ICR_UI_Msk                                     (0x1UL << GTIM_ICR_UI_Pos)
#define GTIM_ICR_UI                                         GTIM_ICR_UI_Msk
#define GTIM_ICR_TI_Pos                                     (1U)
#define GTIM_ICR_TI_Msk                                     (0x1UL << GTIM_ICR_TI_Pos)
#define GTIM_ICR_TI                                         GTIM_ICR_TI_Msk
#define GTIM_ICR_CC0_Pos                                    (2U)
#define GTIM_ICR_CC0_Msk                                    (0x1UL << GTIM_ICR_CC0_Pos)
#define GTIM_ICR_CC0                                        GTIM_ICR_CC0_Msk
#define GTIM_ICR_CC1_Pos                                    (3U)
#define GTIM_ICR_CC1_Msk                                    (0x1UL << GTIM_ICR_CC1_Pos)
#define GTIM_ICR_CC1                                        GTIM_ICR_CC1_Msk
#define GTIM_ICR_CC2_Pos                                    (4U)
#define GTIM_ICR_CC2_Msk                                    (0x1UL << GTIM_ICR_CC2_Pos)
#define GTIM_ICR_CC2                                        GTIM_ICR_CC2_Msk
#define GTIM_ICR_CC3_Pos                                    (5U)
#define GTIM_ICR_CC3_Msk                                    (0x1UL << GTIM_ICR_CC3_Pos)
#define GTIM_ICR_CC3                                        GTIM_ICR_CC3_Msk

// GTIM_CCR0
#define GTIM_CCR0_CCR_Pos                                   (0U)
#define GTIM_CCR0_CCR_Msk                                   (0xFFFFUL << GTIM_CCR0_CCR_Pos)
#define GTIM_CCR0_CCR                                       GTIM_CCR0_CCR_Msk

// GTIM_CCR1
#define GTIM_CCR1_CCR_Pos                                   (0U)
#define GTIM_CCR1_CCR_Msk                                   (0xFFFFUL << GTIM_CCR1_CCR_Pos)
#define GTIM_CCR1_CCR                                       GTIM_CCR1_CCR_Msk

// GTIM_CCR2
#define GTIM_CCR2_CCR_Pos                                   (0U)
#define GTIM_CCR2_CCR_Msk                                   (0xFFFFUL << GTIM_CCR2_CCR_Pos)
#define GTIM_CCR2_CCR                                       GTIM_CCR2_CCR_Msk

// GTIM_CCR3
#define GTIM_CCR3_CCR_Pos                                   (0U)
#define GTIM_CCR3_CCR_Msk                                   (0xFFFFUL << GTIM_CCR3_CCR_Pos)
#define GTIM_CCR3_CCR                                       GTIM_CCR3_CCR_Msk



//********************    Bits Define For Peripheral I2C    ********************//
// I2C_TMRUN
#define I2C_TMRUN_TME_Pos                                   (0U)
#define I2C_TMRUN_TME_Msk                                   (0x1UL << I2C_TMRUN_TME_Pos)
#define I2C_TMRUN_TME                                       I2C_TMRUN_TME_Msk

// I2C_TM
#define I2C_TM_TM_Pos                                       (0U)
#define I2C_TM_TM_Msk                                       (0xFFUL << I2C_TM_TM_Pos)
#define I2C_TM_TM                                           I2C_TM_TM_Msk

// I2C_CR
#define I2C_CR_H1M_Pos                                      (0U)
#define I2C_CR_H1M_Msk                                      (0x1UL << I2C_CR_H1M_Pos)
#define I2C_CR_H1M                                          I2C_CR_H1M_Msk
#define I2C_CR_AA_Pos                                       (2U)
#define I2C_CR_AA_Msk                                       (0x1UL << I2C_CR_AA_Pos)
#define I2C_CR_AA                                           I2C_CR_AA_Msk
#define I2C_CR_SI_Pos                                       (3U)
#define I2C_CR_SI_Msk                                       (0x1UL << I2C_CR_SI_Pos)
#define I2C_CR_SI                                           I2C_CR_SI_Msk
#define I2C_CR_STO_Pos                                      (4U)
#define I2C_CR_STO_Msk                                      (0x1UL << I2C_CR_STO_Pos)
#define I2C_CR_STO                                          I2C_CR_STO_Msk
#define I2C_CR_STA_Pos                                      (5U)
#define I2C_CR_STA_Msk                                      (0x1UL << I2C_CR_STA_Pos)
#define I2C_CR_STA                                          I2C_CR_STA_Msk
#define I2C_CR_ENS_Pos                                      (6U)
#define I2C_CR_ENS_Msk                                      (0x1UL << I2C_CR_ENS_Pos)
#define I2C_CR_ENS                                          I2C_CR_ENS_Msk

// I2C_DATA
#define I2C_DATA_DAT_Pos                                    (0U)
#define I2C_DATA_DAT_Msk                                    (0xFFUL << I2C_DATA_DAT_Pos)
#define I2C_DATA_DAT                                        I2C_DATA_DAT_Msk

// I2C_ADDR0
#define I2C_ADDR0_GC_Pos                                    (0U)
#define I2C_ADDR0_GC_Msk                                    (0x1UL << I2C_ADDR0_GC_Pos)
#define I2C_ADDR0_GC                                        I2C_ADDR0_GC_Msk
#define I2C_ADDR0_ADDR0_Pos                                 (1U)
#define I2C_ADDR0_ADDR0_Msk                                 (0x7FUL << I2C_ADDR0_ADDR0_Pos)
#define I2C_ADDR0_ADDR0                                     I2C_ADDR0_ADDR0_Msk

// I2C_STAT
#define I2C_STAT_STAT_Pos                                   (0U)
#define I2C_STAT_STAT_Msk                                   (0xFFUL << I2C_STAT_STAT_Pos)
#define I2C_STAT_STAT                                       I2C_STAT_STAT_Msk

// I2C_ADDR1
#define I2C_ADDR1_ADDR_Pos                                  (1U)
#define I2C_ADDR1_ADDR_Msk                                  (0x7FUL << I2C_ADDR1_ADDR_Pos)
#define I2C_ADDR1_ADDR                                      I2C_ADDR1_ADDR_Msk

// I2C_ADDR2
#define I2C_ADDR2_ADDR_Pos                                  (1U)
#define I2C_ADDR2_ADDR_Msk                                  (0x7FUL << I2C_ADDR2_ADDR_Pos)
#define I2C_ADDR2_ADDR                                      I2C_ADDR2_ADDR_Msk

// I2C_MATCH
#define I2C_MATCH_AD0F_Pos                                  (0U)
#define I2C_MATCH_AD0F_Msk                                  (0x1UL << I2C_MATCH_AD0F_Pos)
#define I2C_MATCH_AD0F                                      I2C_MATCH_AD0F_Msk
#define I2C_MATCH_AD1F_Pos                                  (1U)
#define I2C_MATCH_AD1F_Msk                                  (0x1UL << I2C_MATCH_AD1F_Pos)
#define I2C_MATCH_AD1F                                      I2C_MATCH_AD1F_Msk
#define I2C_MATCH_AD2F_Pos                                  (2U)
#define I2C_MATCH_AD2F_Msk                                  (0x1UL << I2C_MATCH_AD2F_Pos)
#define I2C_MATCH_AD2F                                      I2C_MATCH_AD2F_Msk



//********************    Bits Define For Peripheral I2CSLV    ********************//
// I2CSLV_SR
#define I2CSLV_SR_RD_Pos                                    (0U)
#define I2CSLV_SR_RD_Msk                                    (0x1UL << I2CSLV_SR_RD_Pos)
#define I2CSLV_SR_RD                                        I2CSLV_SR_RD_Msk
#define I2CSLV_SR_WR_Pos                                    (1U)
#define I2CSLV_SR_WR_Msk                                    (0x1UL << I2CSLV_SR_WR_Pos)
#define I2CSLV_SR_WR                                        I2CSLV_SR_WR_Msk
#define I2CSLV_SR_STOP_Pos                                  (2U)
#define I2CSLV_SR_STOP_Msk                                  (0x1UL << I2CSLV_SR_STOP_Pos)
#define I2CSLV_SR_STOP                                      I2CSLV_SR_STOP_Msk
#define I2CSLV_SR_START_Pos                                 (3U)
#define I2CSLV_SR_START_Msk                                 (0x1UL << I2CSLV_SR_START_Pos)
#define I2CSLV_SR_START                                     I2CSLV_SR_START_Msk
#define I2CSLV_SR_NACK_Pos                                  (4U)
#define I2CSLV_SR_NACK_Msk                                  (0x1UL << I2CSLV_SR_NACK_Pos)
#define I2CSLV_SR_NACK                                      I2CSLV_SR_NACK_Msk
#define I2CSLV_SR_I2CINT_Pos                                (5U)
#define I2CSLV_SR_I2CINT_Msk                                (0x1UL << I2CSLV_SR_I2CINT_Pos)
#define I2CSLV_SR_I2CINT                                    I2CSLV_SR_I2CINT_Msk
#define I2CSLV_SR_ACTIVE_Pos                                (6U)
#define I2CSLV_SR_ACTIVE_Msk                                (0x1UL << I2CSLV_SR_ACTIVE_Pos)
#define I2CSLV_SR_ACTIVE                                    I2CSLV_SR_ACTIVE_Msk
#define I2CSLV_SR_HSMODE_Pos                                (7U)
#define I2CSLV_SR_HSMODE_Msk                                (0x1UL << I2CSLV_SR_HSMODE_Pos)
#define I2CSLV_SR_HSMODE                                    I2CSLV_SR_HSMODE_Msk
#define I2CSLV_SR_TIMEOUT_Pos                               (8U)
#define I2CSLV_SR_TIMEOUT_Msk                               (0x1UL << I2CSLV_SR_TIMEOUT_Pos)
#define I2CSLV_SR_TIMEOUT                                   I2CSLV_SR_TIMEOUT_Msk
#define I2CSLV_SR_ACK_Pos                                   (9U)
#define I2CSLV_SR_ACK_Msk                                   (0x1UL << I2CSLV_SR_ACK_Pos)
#define I2CSLV_SR_ACK                                       I2CSLV_SR_ACK_Msk
#define I2CSLV_SR_SLADDR0_Pos                               (10U)
#define I2CSLV_SR_SLADDR0_Msk                               (0x1UL << I2CSLV_SR_SLADDR0_Pos)
#define I2CSLV_SR_SLADDR0                                   I2CSLV_SR_SLADDR0_Msk
#define I2CSLV_SR_SLADDR1_Pos                               (11U)
#define I2CSLV_SR_SLADDR1_Msk                               (0x1UL << I2CSLV_SR_SLADDR1_Pos)
#define I2CSLV_SR_SLADDR1                                   I2CSLV_SR_SLADDR1_Msk
#define I2CSLV_SR_SLADDR2_Pos                               (12U)
#define I2CSLV_SR_SLADDR2_Msk                               (0x1UL << I2CSLV_SR_SLADDR2_Pos)
#define I2CSLV_SR_SLADDR2                                   I2CSLV_SR_SLADDR2_Msk
#define I2CSLV_SR_SLADDR3_Pos                               (13U)
#define I2CSLV_SR_SLADDR3_Msk                               (0x1UL << I2CSLV_SR_SLADDR3_Pos)
#define I2CSLV_SR_SLADDR3                                   I2CSLV_SR_SLADDR3_Msk
#define I2CSLV_SR_TXE_Pos                                   (14U)
#define I2CSLV_SR_TXE_Msk                                   (0x1UL << I2CSLV_SR_TXE_Pos)
#define I2CSLV_SR_TXE                                       I2CSLV_SR_TXE_Msk
#define I2CSLV_SR_RXNE_Pos                                  (15U)
#define I2CSLV_SR_RXNE_Msk                                  (0x1UL << I2CSLV_SR_RXNE_Pos)
#define I2CSLV_SR_RXNE                                      I2CSLV_SR_RXNE_Msk
#define I2CSLV_SR_GC_Pos                                    (16U)
#define I2CSLV_SR_GC_Msk                                    (0x1UL << I2CSLV_SR_GC_Pos)
#define I2CSLV_SR_GC                                        I2CSLV_SR_GC_Msk

// I2CSLV_DOUTR
#define I2CSLV_DOUTR_DOUT_Pos                               (0U)
#define I2CSLV_DOUTR_DOUT_Msk                               (0xFFUL << I2CSLV_DOUTR_DOUT_Pos)
#define I2CSLV_DOUTR_DOUT                                   I2CSLV_DOUTR_DOUT_Msk

// I2CSLV_ADIR
#define I2CSLV_ADIR_ADIR_Pos                                (0U)
#define I2CSLV_ADIR_ADIR_Msk                                (0x3FFUL << I2CSLV_ADIR_ADIR_Pos)
#define I2CSLV_ADIR_ADIR                                    I2CSLV_ADIR_ADIR_Msk
#define I2CSLV_ADIR_ADRLEN_Pos                              (10U)
#define I2CSLV_ADIR_ADRLEN_Msk                              (0x1UL << I2CSLV_ADIR_ADRLEN_Pos)
#define I2CSLV_ADIR_ADRLEN                                  I2CSLV_ADIR_ADRLEN_Msk

// I2CSLV_SLADR0
#define I2CSLV_SLADR0_ADDR_Pos                              (0U)
#define I2CSLV_SLADR0_ADDR_Msk                              (0x3FFUL << I2CSLV_SLADR0_ADDR_Pos)
#define I2CSLV_SLADR0_ADDR                                  I2CSLV_SLADR0_ADDR_Msk
#define I2CSLV_SLADR0_AM_Pos                                (10U)
#define I2CSLV_SLADR0_AM_Msk                                (0x1UL << I2CSLV_SLADR0_AM_Pos)
#define I2CSLV_SLADR0_AM                                    I2CSLV_SLADR0_AM_Msk

// I2CSLV_SLADR1
#define I2CSLV_SLADR1_ADDR_Pos                              (0U)
#define I2CSLV_SLADR1_ADDR_Msk                              (0x3FFUL << I2CSLV_SLADR1_ADDR_Pos)
#define I2CSLV_SLADR1_ADDR                                  I2CSLV_SLADR1_ADDR_Msk
#define I2CSLV_SLADR1_AM_Pos                                (10U)
#define I2CSLV_SLADR1_AM_Msk                                (0x1UL << I2CSLV_SLADR1_AM_Pos)
#define I2CSLV_SLADR1_AM                                    I2CSLV_SLADR1_AM_Msk

// I2CSLV_SLADR2
#define I2CSLV_SLADR2_ADDR_Pos                              (0U)
#define I2CSLV_SLADR2_ADDR_Msk                              (0x3FFUL << I2CSLV_SLADR2_ADDR_Pos)
#define I2CSLV_SLADR2_ADDR                                  I2CSLV_SLADR2_ADDR_Msk
#define I2CSLV_SLADR2_ADDRLEN_Pos                           (10U)
#define I2CSLV_SLADR2_ADDRLEN_Msk                           (0x1UL << I2CSLV_SLADR2_ADDRLEN_Pos)
#define I2CSLV_SLADR2_ADDRLEN                               I2CSLV_SLADR2_ADDRLEN_Msk

// I2CSLV_SLADR3
#define I2CSLV_SLADR3_ADDR_Pos                              (0U)
#define I2CSLV_SLADR3_ADDR_Msk                              (0x3FFUL << I2CSLV_SLADR3_ADDR_Pos)
#define I2CSLV_SLADR3_ADDR                                  I2CSLV_SLADR3_ADDR_Msk
#define I2CSLV_SLADR3_ADDRLEN_Pos                           (10U)
#define I2CSLV_SLADR3_ADDRLEN_Msk                           (0x1UL << I2CSLV_SLADR3_ADDRLEN_Pos)
#define I2CSLV_SLADR3_ADDRLEN                               I2CSLV_SLADR3_ADDRLEN_Msk

// I2CSLV_DINR
#define I2CSLV_DINR_DIN_Pos                                 (0U)
#define I2CSLV_DINR_DIN_Msk                                 (0xFFUL << I2CSLV_DINR_DIN_Pos)
#define I2CSLV_DINR_DIN                                     I2CSLV_DINR_DIN_Msk

// I2CSLV_CR
#define I2CSLV_CR_EN_Pos                                    (0U)
#define I2CSLV_CR_EN_Msk                                    (0x1UL << I2CSLV_CR_EN_Pos)
#define I2CSLV_CR_EN                                        I2CSLV_CR_EN_Msk
#define I2CSLV_CR_BUSY_Pos                                  (1U)
#define I2CSLV_CR_BUSY_Msk                                  (0x1UL << I2CSLV_CR_BUSY_Pos)
#define I2CSLV_CR_BUSY                                      I2CSLV_CR_BUSY_Msk
#define I2CSLV_CR_FSCLC_Pos                                 (2U)
#define I2CSLV_CR_FSCLC_Msk                                 (0x1UL << I2CSLV_CR_FSCLC_Pos)
#define I2CSLV_CR_FSCLC                                     I2CSLV_CR_FSCLC_Msk
#define I2CSLV_CR_TIMEOUT_Pos                               (3U)
#define I2CSLV_CR_TIMEOUT_Msk                               (0x1UL << I2CSLV_CR_TIMEOUT_Pos)
#define I2CSLV_CR_TIMEOUT                                   I2CSLV_CR_TIMEOUT_Msk
#define I2CSLV_CR_GC_Pos                                    (7U)
#define I2CSLV_CR_GC_Msk                                    (0x1UL << I2CSLV_CR_GC_Pos)
#define I2CSLV_CR_GC                                        I2CSLV_CR_GC_Msk
#define I2CSLV_CR_DMATE_Pos                                 (8U)
#define I2CSLV_CR_DMATE_Msk                                 (0x1UL << I2CSLV_CR_DMATE_Pos)
#define I2CSLV_CR_DMATE                                     I2CSLV_CR_DMATE_Msk
#define I2CSLV_CR_DMARE_Pos                                 (9U)
#define I2CSLV_CR_DMARE_Msk                                 (0x1UL << I2CSLV_CR_DMARE_Pos)
#define I2CSLV_CR_DMARE                                     I2CSLV_CR_DMARE_Msk

// I2CSLV_ADMR0
#define I2CSLV_ADMR0_ADDRMASK_Pos                           (0U)
#define I2CSLV_ADMR0_ADDRMASK_Msk                           (0x3FFUL << I2CSLV_ADMR0_ADDRMASK_Pos)
#define I2CSLV_ADMR0_ADDRMASK                               I2CSLV_ADMR0_ADDRMASK_Msk
#define I2CSLV_ADMR0_FACS_Pos                               (10U)
#define I2CSLV_ADMR0_FACS_Msk                               (0x1UL << I2CSLV_ADMR0_FACS_Pos)
#define I2CSLV_ADMR0_FACS                                   I2CSLV_ADMR0_FACS_Msk

// I2CSLV_FLT
#define I2CSLV_FLT_FW_Pos                                   (0U)
#define I2CSLV_FLT_FW_Msk                                   (0x7UL << I2CSLV_FLT_FW_Pos)
#define I2CSLV_FLT_FW                                       I2CSLV_FLT_FW_Msk

// I2CSLV_TOR
#define I2CSLV_TOR_TOR_Pos                                  (0U)
#define I2CSLV_TOR_TOR_Msk                                  (0xFFFFUL << I2CSLV_TOR_TOR_Pos)
#define I2CSLV_TOR_TOR                                      I2CSLV_TOR_TOR_Msk

// I2CSLV_ODDR
#define I2CSLV_ODDR_ODPU_Pos                                (0U)
#define I2CSLV_ODDR_ODPU_Msk                                (0x3UL << I2CSLV_ODDR_ODPU_Pos)
#define I2CSLV_ODDR_ODPU                                    I2CSLV_ODDR_ODPU_Msk

// I2CSLV_RSR
#define I2CSLV_RSR_NS_Pos                                   (0U)
#define I2CSLV_RSR_NS_Msk                                   (0x3UL << I2CSLV_RSR_NS_Pos)
#define I2CSLV_RSR_NS                                       I2CSLV_RSR_NS_Msk

// I2CSLV_IER
#define I2CSLV_IER_RD_Pos                                   (0U)
#define I2CSLV_IER_RD_Msk                                   (0x1UL << I2CSLV_IER_RD_Pos)
#define I2CSLV_IER_RD                                       I2CSLV_IER_RD_Msk
#define I2CSLV_IER_WR_Pos                                   (1U)
#define I2CSLV_IER_WR_Msk                                   (0x1UL << I2CSLV_IER_WR_Pos)
#define I2CSLV_IER_WR                                       I2CSLV_IER_WR_Msk
#define I2CSLV_IER_STOP_Pos                                 (2U)
#define I2CSLV_IER_STOP_Msk                                 (0x1UL << I2CSLV_IER_STOP_Pos)
#define I2CSLV_IER_STOP                                     I2CSLV_IER_STOP_Msk
#define I2CSLV_IER_START_Pos                                (3U)
#define I2CSLV_IER_START_Msk                                (0x1UL << I2CSLV_IER_START_Pos)
#define I2CSLV_IER_START                                    I2CSLV_IER_START_Msk
#define I2CSLV_IER_NACK_Pos                                 (4U)
#define I2CSLV_IER_NACK_Msk                                 (0x1UL << I2CSLV_IER_NACK_Pos)
#define I2CSLV_IER_NACK                                     I2CSLV_IER_NACK_Msk
#define I2CSLV_IER_I2CINT_Pos                               (5U)
#define I2CSLV_IER_I2CINT_Msk                               (0x1UL << I2CSLV_IER_I2CINT_Pos)
#define I2CSLV_IER_I2CINT                                   I2CSLV_IER_I2CINT_Msk
#define I2CSLV_IER_ACTIVE_Pos                               (6U)
#define I2CSLV_IER_ACTIVE_Msk                               (0x1UL << I2CSLV_IER_ACTIVE_Pos)
#define I2CSLV_IER_ACTIVE                                   I2CSLV_IER_ACTIVE_Msk
#define I2CSLV_IER_HSMODE_Pos                               (7U)
#define I2CSLV_IER_HSMODE_Msk                               (0x1UL << I2CSLV_IER_HSMODE_Pos)
#define I2CSLV_IER_HSMODE                                   I2CSLV_IER_HSMODE_Msk
#define I2CSLV_IER_TIMEOUT_Pos                              (8U)
#define I2CSLV_IER_TIMEOUT_Msk                              (0x1UL << I2CSLV_IER_TIMEOUT_Pos)
#define I2CSLV_IER_TIMEOUT                                  I2CSLV_IER_TIMEOUT_Msk
#define I2CSLV_IER_ACK_Pos                                  (9U)
#define I2CSLV_IER_ACK_Msk                                  (0x1UL << I2CSLV_IER_ACK_Pos)
#define I2CSLV_IER_ACK                                      I2CSLV_IER_ACK_Msk
#define I2CSLV_IER_SLADDR0_Pos                              (10U)
#define I2CSLV_IER_SLADDR0_Msk                              (0x1UL << I2CSLV_IER_SLADDR0_Pos)
#define I2CSLV_IER_SLADDR0                                  I2CSLV_IER_SLADDR0_Msk
#define I2CSLV_IER_SLADDR1_Pos                              (11U)
#define I2CSLV_IER_SLADDR1_Msk                              (0x1UL << I2CSLV_IER_SLADDR1_Pos)
#define I2CSLV_IER_SLADDR1                                  I2CSLV_IER_SLADDR1_Msk
#define I2CSLV_IER_SLADDR2_Pos                              (12U)
#define I2CSLV_IER_SLADDR2_Msk                              (0x1UL << I2CSLV_IER_SLADDR2_Pos)
#define I2CSLV_IER_SLADDR2                                  I2CSLV_IER_SLADDR2_Msk
#define I2CSLV_IER_SLADDR3_Pos                              (13U)
#define I2CSLV_IER_SLADDR3_Msk                              (0x1UL << I2CSLV_IER_SLADDR3_Pos)
#define I2CSLV_IER_SLADDR3                                  I2CSLV_IER_SLADDR3_Msk
#define I2CSLV_IER_TXE_Pos                                  (14U)
#define I2CSLV_IER_TXE_Msk                                  (0x1UL << I2CSLV_IER_TXE_Pos)
#define I2CSLV_IER_TXE                                      I2CSLV_IER_TXE_Msk
#define I2CSLV_IER_RXNE_Pos                                 (15U)
#define I2CSLV_IER_RXNE_Msk                                 (0x1UL << I2CSLV_IER_RXNE_Pos)
#define I2CSLV_IER_RXNE                                     I2CSLV_IER_RXNE_Msk
#define I2CSLV_IER_GC_Pos                                   (16U)
#define I2CSLV_IER_GC_Msk                                   (0x1UL << I2CSLV_IER_GC_Pos)
#define I2CSLV_IER_GC                                       I2CSLV_IER_GC_Msk

// I2CSLV_ICR
#define I2CSLV_ICR_RD_Pos                                   (0U)
#define I2CSLV_ICR_RD_Msk                                   (0x1UL << I2CSLV_ICR_RD_Pos)
#define I2CSLV_ICR_RD                                       I2CSLV_ICR_RD_Msk
#define I2CSLV_ICR_WR_Pos                                   (1U)
#define I2CSLV_ICR_WR_Msk                                   (0x1UL << I2CSLV_ICR_WR_Pos)
#define I2CSLV_ICR_WR                                       I2CSLV_ICR_WR_Msk
#define I2CSLV_ICR_STOP_Pos                                 (2U)
#define I2CSLV_ICR_STOP_Msk                                 (0x1UL << I2CSLV_ICR_STOP_Pos)
#define I2CSLV_ICR_STOP                                     I2CSLV_ICR_STOP_Msk
#define I2CSLV_ICR_START_Pos                                (3U)
#define I2CSLV_ICR_START_Msk                                (0x1UL << I2CSLV_ICR_START_Pos)
#define I2CSLV_ICR_START                                    I2CSLV_ICR_START_Msk
#define I2CSLV_ICR_NACK_Pos                                 (4U)
#define I2CSLV_ICR_NACK_Msk                                 (0x1UL << I2CSLV_ICR_NACK_Pos)
#define I2CSLV_ICR_NACK                                     I2CSLV_ICR_NACK_Msk
#define I2CSLV_ICR_I2CINT_Pos                               (5U)
#define I2CSLV_ICR_I2CINT_Msk                               (0x1UL << I2CSLV_ICR_I2CINT_Pos)
#define I2CSLV_ICR_I2CINT                                   I2CSLV_ICR_I2CINT_Msk
#define I2CSLV_ICR_ACTIVE_Pos                               (6U)
#define I2CSLV_ICR_ACTIVE_Msk                               (0x1UL << I2CSLV_ICR_ACTIVE_Pos)
#define I2CSLV_ICR_ACTIVE                                   I2CSLV_ICR_ACTIVE_Msk
#define I2CSLV_ICR_HSMODE_Pos                               (7U)
#define I2CSLV_ICR_HSMODE_Msk                               (0x1UL << I2CSLV_ICR_HSMODE_Pos)
#define I2CSLV_ICR_HSMODE                                   I2CSLV_ICR_HSMODE_Msk
#define I2CSLV_ICR_TIMEOUT_Pos                              (8U)
#define I2CSLV_ICR_TIMEOUT_Msk                              (0x1UL << I2CSLV_ICR_TIMEOUT_Pos)
#define I2CSLV_ICR_TIMEOUT                                  I2CSLV_ICR_TIMEOUT_Msk
#define I2CSLV_ICR_ACK_Pos                                  (9U)
#define I2CSLV_ICR_ACK_Msk                                  (0x1UL << I2CSLV_ICR_ACK_Pos)
#define I2CSLV_ICR_ACK                                      I2CSLV_ICR_ACK_Msk
#define I2CSLV_ICR_SLADDR0_Pos                              (10U)
#define I2CSLV_ICR_SLADDR0_Msk                              (0x1UL << I2CSLV_ICR_SLADDR0_Pos)
#define I2CSLV_ICR_SLADDR0                                  I2CSLV_ICR_SLADDR0_Msk
#define I2CSLV_ICR_SLADDR1_Pos                              (11U)
#define I2CSLV_ICR_SLADDR1_Msk                              (0x1UL << I2CSLV_ICR_SLADDR1_Pos)
#define I2CSLV_ICR_SLADDR1                                  I2CSLV_ICR_SLADDR1_Msk
#define I2CSLV_ICR_SLADDR2_Pos                              (12U)
#define I2CSLV_ICR_SLADDR2_Msk                              (0x1UL << I2CSLV_ICR_SLADDR2_Pos)
#define I2CSLV_ICR_SLADDR2                                  I2CSLV_ICR_SLADDR2_Msk
#define I2CSLV_ICR_SLADDR3_Pos                              (13U)
#define I2CSLV_ICR_SLADDR3_Msk                              (0x1UL << I2CSLV_ICR_SLADDR3_Pos)
#define I2CSLV_ICR_SLADDR3                                  I2CSLV_ICR_SLADDR3_Msk
#define I2CSLV_ICR_TXE_Pos                                  (14U)
#define I2CSLV_ICR_TXE_Msk                                  (0x1UL << I2CSLV_ICR_TXE_Pos)
#define I2CSLV_ICR_TXE                                      I2CSLV_ICR_TXE_Msk
#define I2CSLV_ICR_RXNE_Pos                                 (15U)
#define I2CSLV_ICR_RXNE_Msk                                 (0x1UL << I2CSLV_ICR_RXNE_Pos)
#define I2CSLV_ICR_RXNE                                     I2CSLV_ICR_RXNE_Msk
#define I2CSLV_ICR_GC_Pos                                   (16U)
#define I2CSLV_ICR_GC_Msk                                   (0x1UL << I2CSLV_ICR_GC_Pos)
#define I2CSLV_ICR_GC                                       I2CSLV_ICR_GC_Msk

// I2CSLV_DIDR
#define I2CSLV_DIDR_RID_Pos                                 (0U)
#define I2CSLV_DIDR_RID_Msk                                 (0x7UL << I2CSLV_DIDR_RID_Pos)
#define I2CSLV_DIDR_RID                                     I2CSLV_DIDR_RID_Msk
#define I2CSLV_DIDR_PID_Pos                                 (3U)
#define I2CSLV_DIDR_PID_Msk                                 (0x1FFUL << I2CSLV_DIDR_PID_Pos)
#define I2CSLV_DIDR_PID                                     I2CSLV_DIDR_PID_Msk
#define I2CSLV_DIDR_MID_Pos                                 (12U)
#define I2CSLV_DIDR_MID_Msk                                 (0xFFFUL << I2CSLV_DIDR_MID_Pos)
#define I2CSLV_DIDR_MID                                     I2CSLV_DIDR_MID_Msk



//********************    Bits Define For Peripheral IWDT    ********************//
// IWDT_KR
#define IWDT_KR_KR_Pos                                      (0U)
#define IWDT_KR_KR_Msk                                      (0xFFFFUL << IWDT_KR_KR_Pos)
#define IWDT_KR_KR                                          IWDT_KR_KR_Msk

// IWDT_CR
#define IWDT_CR_PRS_Pos                                     (0U)
#define IWDT_CR_PRS_Msk                                     (0x7UL << IWDT_CR_PRS_Pos)
#define IWDT_CR_PRS                                         IWDT_CR_PRS_Msk
#define IWDT_CR_IE_Pos                                      (4U)
#define IWDT_CR_IE_Msk                                      (0x1UL << IWDT_CR_IE_Pos)
#define IWDT_CR_IE                                          IWDT_CR_IE_Msk
#define IWDT_CR_ACTION_Pos                                  (5U)
#define IWDT_CR_ACTION_Msk                                  (0x1UL << IWDT_CR_ACTION_Pos)
#define IWDT_CR_ACTION                                      IWDT_CR_ACTION_Msk
#define IWDT_CR_PAUSE_Pos                                   (6U)
#define IWDT_CR_PAUSE_Msk                                   (0x1UL << IWDT_CR_PAUSE_Pos)
#define IWDT_CR_PAUSE                                       IWDT_CR_PAUSE_Msk

// IWDT_ARR
#define IWDT_ARR_ARR_Pos                                    (0U)
#define IWDT_ARR_ARR_Msk                                    (0xFFFUL << IWDT_ARR_ARR_Pos)
#define IWDT_ARR_ARR                                        IWDT_ARR_ARR_Msk

// IWDT_SR
#define IWDT_SR_PRSF_Pos                                    (0U)
#define IWDT_SR_PRSF_Msk                                    (0x1UL << IWDT_SR_PRSF_Pos)
#define IWDT_SR_PRSF                                        IWDT_SR_PRSF_Msk
#define IWDT_SR_ARRF_Pos                                    (1U)
#define IWDT_SR_ARRF_Msk                                    (0x1UL << IWDT_SR_ARRF_Pos)
#define IWDT_SR_ARRF                                        IWDT_SR_ARRF_Msk
#define IWDT_SR_WINRF_Pos                                   (2U)
#define IWDT_SR_WINRF_Msk                                   (0x1UL << IWDT_SR_WINRF_Pos)
#define IWDT_SR_WINRF                                       IWDT_SR_WINRF_Msk
#define IWDT_SR_OV_Pos                                      (3U)
#define IWDT_SR_OV_Msk                                      (0x1UL << IWDT_SR_OV_Pos)
#define IWDT_SR_OV                                          IWDT_SR_OV_Msk
#define IWDT_SR_RUN_Pos                                     (4U)
#define IWDT_SR_RUN_Msk                                     (0x1UL << IWDT_SR_RUN_Pos)
#define IWDT_SR_RUN                                         IWDT_SR_RUN_Msk

// IWDT_WINR
#define IWDT_WINR_WINR_Pos                                  (0U)
#define IWDT_WINR_WINR_Msk                                  (0xFFFUL << IWDT_WINR_WINR_Pos)
#define IWDT_WINR_WINR                                      IWDT_WINR_WINR_Msk



//********************    Bits Define For Peripheral LPTIM    ********************//
// LPTIM_CNT
#define LPTIM_CNT_CNT_Pos                                   (0U)
#define LPTIM_CNT_CNT_Msk                                   (0xFFFFUL << LPTIM_CNT_CNT_Pos)
#define LPTIM_CNT_CNT                                       LPTIM_CNT_CNT_Msk

// LPTIM_ARR
#define LPTIM_ARR_ARR_Pos                                   (0U)
#define LPTIM_ARR_ARR_Msk                                   (0xFFFFUL << LPTIM_ARR_ARR_Pos)
#define LPTIM_ARR_ARR                                       LPTIM_ARR_ARR_Msk

// LPTIM_CR
#define LPTIM_CR_CEN_Pos                                    (0U)
#define LPTIM_CR_CEN_Msk                                    (0x1UL << LPTIM_CR_CEN_Pos)
#define LPTIM_CR_CEN                                        LPTIM_CR_CEN_Msk
#define LPTIM_CR_MD_Pos                                     (1U)
#define LPTIM_CR_MD_Msk                                     (0x1UL << LPTIM_CR_MD_Pos)
#define LPTIM_CR_MD                                         LPTIM_CR_MD_Msk
#define LPTIM_CR_CT_Pos                                     (2U)
#define LPTIM_CR_CT_Msk                                     (0x1UL << LPTIM_CR_CT_Pos)
#define LPTIM_CR_CT                                         LPTIM_CR_CT_Msk
#define LPTIM_CR_TOG_EN_Pos                                 (3U)
#define LPTIM_CR_TOG_EN_Msk                                 (0x1UL << LPTIM_CR_TOG_EN_Pos)
#define LPTIM_CR_TOG_EN                                     LPTIM_CR_TOG_EN_Msk
#define LPTIM_CR_TCK_SEL_Pos                                (4U)
#define LPTIM_CR_TCK_SEL_Msk                                (0x3UL << LPTIM_CR_TCK_SEL_Pos)
#define LPTIM_CR_TCK_SEL                                    LPTIM_CR_TCK_SEL_Msk
#define LPTIM_CR_WT_FLAG_Pos                                (7U)
#define LPTIM_CR_WT_FLAG_Msk                                (0x1UL << LPTIM_CR_WT_FLAG_Pos)
#define LPTIM_CR_WT_FLAG                                    LPTIM_CR_WT_FLAG_Msk
#define LPTIM_CR_GATE_Pos                                   (8U)
#define LPTIM_CR_GATE_Msk                                   (0x1UL << LPTIM_CR_GATE_Pos)
#define LPTIM_CR_GATE                                       LPTIM_CR_GATE_Msk
#define LPTIM_CR_GATE_P_Pos                                 (9U)
#define LPTIM_CR_GATE_P_Msk                                 (0x1UL << LPTIM_CR_GATE_P_Pos)
#define LPTIM_CR_GATE_P                                     LPTIM_CR_GATE_P_Msk
#define LPTIM_CR_IE_Pos                                     (10U)
#define LPTIM_CR_IE_Msk                                     (0x1UL << LPTIM_CR_IE_Pos)
#define LPTIM_CR_IE                                         LPTIM_CR_IE_Msk
#define LPTIM_CR_PRS_Pos                                    (11U)
#define LPTIM_CR_PRS_Msk                                    (0xFUL << LPTIM_CR_PRS_Pos)
#define LPTIM_CR_PRS                                        LPTIM_CR_PRS_Msk

// LPTIM_IFR
#define LPTIM_IFR_OV_Pos                                    (0U)
#define LPTIM_IFR_OV_Msk                                    (0x1UL << LPTIM_IFR_OV_Pos)
#define LPTIM_IFR_OV                                        LPTIM_IFR_OV_Msk

// LPTIM_ICLR
#define LPTIM_ICLR_OV_Pos                                   (0U)
#define LPTIM_ICLR_OV_Msk                                   (0x1UL << LPTIM_ICLR_OV_Pos)
#define LPTIM_ICLR_OV                                       LPTIM_ICLR_OV_Msk



//********************    Bits Define For Peripheral LPUART    ********************//
// LPUART_SBUF
#define LPUART_SBUF_DATA_Pos                                (0U)
#define LPUART_SBUF_DATA_Msk                                (0xFFUL << LPUART_SBUF_DATA_Pos)
#define LPUART_SBUF_DATA                                    LPUART_SBUF_DATA_Msk
#define LPUART_SBUF_DR8_Pos                                 (8U)
#define LPUART_SBUF_DR8_Msk                                 (0x1UL << LPUART_SBUF_DR8_Pos)
#define LPUART_SBUF_DR8                                     LPUART_SBUF_DR8_Msk

// LPUART_SCON
#define LPUART_SCON_RCIE_Pos                                (0U)
#define LPUART_SCON_RCIE_Msk                                (0x1UL << LPUART_SCON_RCIE_Pos)
#define LPUART_SCON_RCIE                                    LPUART_SCON_RCIE_Msk
#define LPUART_SCON_TCIE_Pos                                (1U)
#define LPUART_SCON_TCIE_Msk                                (0x1UL << LPUART_SCON_TCIE_Pos)
#define LPUART_SCON_TCIE                                    LPUART_SCON_TCIE_Msk
#define LPUART_SCON_DR8CFG_Pos                              (2U)
#define LPUART_SCON_DR8CFG_Msk                              (0x3UL << LPUART_SCON_DR8CFG_Pos)
#define LPUART_SCON_DR8CFG                                  LPUART_SCON_DR8CFG_Msk
#define LPUART_SCON_RXEN_Pos                                (4U)
#define LPUART_SCON_RXEN_Msk                                (0x1UL << LPUART_SCON_RXEN_Pos)
#define LPUART_SCON_RXEN                                    LPUART_SCON_RXEN_Msk
#define LPUART_SCON_ADRDET_Pos                              (5U)
#define LPUART_SCON_ADRDET_Msk                              (0x1UL << LPUART_SCON_ADRDET_Pos)
#define LPUART_SCON_ADRDET                                  LPUART_SCON_ADRDET_Msk
#define LPUART_SCON_MODE_Pos                                (6U)
#define LPUART_SCON_MODE_Msk                                (0x3UL << LPUART_SCON_MODE_Pos)
#define LPUART_SCON_MODE                                    LPUART_SCON_MODE_Msk
#define LPUART_SCON_TXEIE_Pos                               (8U)
#define LPUART_SCON_TXEIE_Msk                               (0x1UL << LPUART_SCON_TXEIE_Pos)
#define LPUART_SCON_TXEIE                                   LPUART_SCON_TXEIE_Msk
#define LPUART_SCON_OVER_Pos                                (9U)
#define LPUART_SCON_OVER_Msk                                (0x3UL << LPUART_SCON_OVER_Pos)
#define LPUART_SCON_OVER                                    LPUART_SCON_OVER_Msk
#define LPUART_SCON_CLKSRC_Pos                              (11U)
#define LPUART_SCON_CLKSRC_Msk                              (0x3UL << LPUART_SCON_CLKSRC_Pos)
#define LPUART_SCON_CLKSRC                                  LPUART_SCON_CLKSRC_Msk
#define LPUART_SCON_PEIE_Pos                                (13U)
#define LPUART_SCON_PEIE_Msk                                (0x1UL << LPUART_SCON_PEIE_Pos)
#define LPUART_SCON_PEIE                                    LPUART_SCON_PEIE_Msk
#define LPUART_SCON_STOP_Pos                                (14U)
#define LPUART_SCON_STOP_Msk                                (0x3UL << LPUART_SCON_STOP_Pos)
#define LPUART_SCON_STOP                                    LPUART_SCON_STOP_Msk
#define LPUART_SCON_DMARXEN_Pos                             (16U)
#define LPUART_SCON_DMARXEN_Msk                             (0x1UL << LPUART_SCON_DMARXEN_Pos)
#define LPUART_SCON_DMARXEN                                 LPUART_SCON_DMARXEN_Msk
#define LPUART_SCON_DMATXEN_Pos                             (17U)
#define LPUART_SCON_DMATXEN_Msk                             (0x1UL << LPUART_SCON_DMATXEN_Pos)
#define LPUART_SCON_DMATXEN                                 LPUART_SCON_DMATXEN_Msk
#define LPUART_SCON_RTSEN_Pos                               (18U)
#define LPUART_SCON_RTSEN_Msk                               (0x1UL << LPUART_SCON_RTSEN_Pos)
#define LPUART_SCON_RTSEN                                   LPUART_SCON_RTSEN_Msk
#define LPUART_SCON_CTSEN_Pos                               (19U)
#define LPUART_SCON_CTSEN_Msk                               (0x1UL << LPUART_SCON_CTSEN_Pos)
#define LPUART_SCON_CTSEN                                   LPUART_SCON_CTSEN_Msk
#define LPUART_SCON_CTSIE_Pos                               (20U)
#define LPUART_SCON_CTSIE_Msk                               (0x1UL << LPUART_SCON_CTSIE_Pos)
#define LPUART_SCON_CTSIE                                   LPUART_SCON_CTSIE_Msk
#define LPUART_SCON_FEIE_Pos                                (21U)
#define LPUART_SCON_FEIE_Msk                                (0x1UL << LPUART_SCON_FEIE_Pos)
#define LPUART_SCON_FEIE                                    LPUART_SCON_FEIE_Msk
#define LPUART_SCON_HDSEL_Pos                               (22U)
#define LPUART_SCON_HDSEL_Msk                               (0x1UL << LPUART_SCON_HDSEL_Pos)
#define LPUART_SCON_HDSEL                                   LPUART_SCON_HDSEL_Msk

// LPUART_SADDR
#define LPUART_SADDR_ADDR_Pos                               (0U)
#define LPUART_SADDR_ADDR_Msk                               (0xFFUL << LPUART_SADDR_ADDR_Pos)
#define LPUART_SADDR_ADDR                                   LPUART_SADDR_ADDR_Msk

// LPUART_SADEN
#define LPUART_SADEN_SADEN_Pos                              (0U)
#define LPUART_SADEN_SADEN_Msk                              (0xFFUL << LPUART_SADEN_SADEN_Pos)
#define LPUART_SADEN_SADEN                                  LPUART_SADEN_SADEN_Msk

// LPUART_ISR
#define LPUART_ISR_RC_Pos                                   (0U)
#define LPUART_ISR_RC_Msk                                   (0x1UL << LPUART_ISR_RC_Pos)
#define LPUART_ISR_RC                                       LPUART_ISR_RC_Msk
#define LPUART_ISR_TC_Pos                                   (1U)
#define LPUART_ISR_TC_Msk                                   (0x1UL << LPUART_ISR_TC_Pos)
#define LPUART_ISR_TC                                       LPUART_ISR_TC_Msk
#define LPUART_ISR_FE_Pos                                   (2U)
#define LPUART_ISR_FE_Msk                                   (0x1UL << LPUART_ISR_FE_Pos)
#define LPUART_ISR_FE                                       LPUART_ISR_FE_Msk
#define LPUART_ISR_TXE_Pos                                  (3U)
#define LPUART_ISR_TXE_Msk                                  (0x1UL << LPUART_ISR_TXE_Pos)
#define LPUART_ISR_TXE                                      LPUART_ISR_TXE_Msk
#define LPUART_ISR_PE_Pos                                   (4U)
#define LPUART_ISR_PE_Msk                                   (0x1UL << LPUART_ISR_PE_Pos)
#define LPUART_ISR_PE                                       LPUART_ISR_PE_Msk
#define LPUART_ISR_CTSIF_Pos                                (5U)
#define LPUART_ISR_CTSIF_Msk                                (0x1UL << LPUART_ISR_CTSIF_Pos)
#define LPUART_ISR_CTSIF                                    LPUART_ISR_CTSIF_Msk
#define LPUART_ISR_CTS_Pos                                  (6U)
#define LPUART_ISR_CTS_Msk                                  (0x1UL << LPUART_ISR_CTS_Pos)
#define LPUART_ISR_CTS                                      LPUART_ISR_CTS_Msk

// LPUART_ICR
#define LPUART_ICR_RC_Pos                                   (0U)
#define LPUART_ICR_RC_Msk                                   (0x1UL << LPUART_ICR_RC_Pos)
#define LPUART_ICR_RC                                       LPUART_ICR_RC_Msk
#define LPUART_ICR_TC_Pos                                   (1U)
#define LPUART_ICR_TC_Msk                                   (0x1UL << LPUART_ICR_TC_Pos)
#define LPUART_ICR_TC                                       LPUART_ICR_TC_Msk
#define LPUART_ICR_FE_Pos                                   (2U)
#define LPUART_ICR_FE_Msk                                   (0x1UL << LPUART_ICR_FE_Pos)
#define LPUART_ICR_FE                                       LPUART_ICR_FE_Msk
#define LPUART_ICR_PE_Pos                                   (4U)
#define LPUART_ICR_PE_Msk                                   (0x1UL << LPUART_ICR_PE_Pos)
#define LPUART_ICR_PE                                       LPUART_ICR_PE_Msk
#define LPUART_ICR_CTSIF_Pos                                (5U)
#define LPUART_ICR_CTSIF_Msk                                (0x1UL << LPUART_ICR_CTSIF_Pos)
#define LPUART_ICR_CTSIF                                    LPUART_ICR_CTSIF_Msk

// LPUART_SCNT
#define LPUART_SCNT_SCNT_Pos                                (0U)
#define LPUART_SCNT_SCNT_Msk                                (0xFFFFUL << LPUART_SCNT_SCNT_Pos)
#define LPUART_SCNT_SCNT                                    LPUART_SCNT_SCNT_Msk



//********************    Bits Define For Peripheral LVD    ********************//
// LVD_CR
#define LVD_CR_LVDEN_Pos                                    (0U)
#define LVD_CR_LVDEN_Msk                                    (0x1UL << LVD_CR_LVDEN_Pos)
#define LVD_CR_LVDEN                                        LVD_CR_LVDEN_Msk
#define LVD_CR_ACT_Pos                                      (1U)
#define LVD_CR_ACT_Msk                                      (0x1UL << LVD_CR_ACT_Pos)
#define LVD_CR_ACT                                          LVD_CR_ACT_Msk
#define LVD_CR_SOURCE_Pos                                   (2U)
#define LVD_CR_SOURCE_Msk                                   (0x3UL << LVD_CR_SOURCE_Pos)
#define LVD_CR_SOURCE                                       LVD_CR_SOURCE_Msk
#define LVD_CR_VTDS_Pos                                     (4U)
#define LVD_CR_VTDS_Msk                                     (0xFUL << LVD_CR_VTDS_Pos)
#define LVD_CR_VTDS                                         LVD_CR_VTDS_Msk
#define LVD_CR_FLTEN_Pos                                    (8U)
#define LVD_CR_FLTEN_Msk                                    (0x1UL << LVD_CR_FLTEN_Pos)
#define LVD_CR_FLTEN                                        LVD_CR_FLTEN_Msk
#define LVD_CR_DEBOUNCETIME_Pos                             (9U)
#define LVD_CR_DEBOUNCETIME_Msk                             (0x7UL << LVD_CR_DEBOUNCETIME_Pos)
#define LVD_CR_DEBOUNCETIME                                 LVD_CR_DEBOUNCETIME_Msk
#define LVD_CR_FTEN_Pos                                     (12U)
#define LVD_CR_FTEN_Msk                                     (0x1UL << LVD_CR_FTEN_Pos)
#define LVD_CR_FTEN                                         LVD_CR_FTEN_Msk
#define LVD_CR_RTEN_Pos                                     (13U)
#define LVD_CR_RTEN_Msk                                     (0x1UL << LVD_CR_RTEN_Pos)
#define LVD_CR_RTEN                                         LVD_CR_RTEN_Msk
#define LVD_CR_HTEN_Pos                                     (14U)
#define LVD_CR_HTEN_Msk                                     (0x1UL << LVD_CR_HTEN_Pos)
#define LVD_CR_HTEN                                         LVD_CR_HTEN_Msk
#define LVD_CR_IE_Pos                                       (15U)
#define LVD_CR_IE_Msk                                       (0x1UL << LVD_CR_IE_Pos)
#define LVD_CR_IE                                           LVD_CR_IE_Msk

// LVD_SR
#define LVD_SR_INTF_Pos                                     (0U)
#define LVD_SR_INTF_Msk                                     (0x1UL << LVD_SR_INTF_Pos)
#define LVD_SR_INTF                                         LVD_SR_INTF_Msk
#define LVD_SR_FILTER_Pos                                   (1U)
#define LVD_SR_FILTER_Msk                                   (0x1UL << LVD_SR_FILTER_Pos)
#define LVD_SR_FILTER                                       LVD_SR_FILTER_Msk



//********************    Bits Define For Peripheral OPA    ********************//
// OPA_CR0
#define OPA_CR0_OPAEN_Pos                                   (0U)
#define OPA_CR0_OPAEN_Msk                                   (0x1UL << OPA_CR0_OPAEN_Pos)
#define OPA_CR0_OPAEN                                       OPA_CR0_OPAEN_Msk
#define OPA_CR0_AZEN_Pos                                    (1U)
#define OPA_CR0_AZEN_Msk                                    (0x1UL << OPA_CR0_AZEN_Pos)
#define OPA_CR0_AZEN                                        OPA_CR0_AZEN_Msk
#define OPA_CR0_BIASSEL_Pos                                 (7U)
#define OPA_CR0_BIASSEL_Msk                                 (0x7UL << OPA_CR0_BIASSEL_Pos)
#define OPA_CR0_BIASSEL                                     OPA_CR0_BIASSEL_Msk

// OPA_CR1
#define OPA_CR1_OPAEN_Pos                                   (0U)
#define OPA_CR1_OPAEN_Msk                                   (0x1UL << OPA_CR1_OPAEN_Pos)
#define OPA_CR1_OPAEN                                       OPA_CR1_OPAEN_Msk
#define OPA_CR1_AZEN_Pos                                    (1U)
#define OPA_CR1_AZEN_Msk                                    (0x1UL << OPA_CR1_AZEN_Pos)
#define OPA_CR1_AZEN                                        OPA_CR1_AZEN_Msk
#define OPA_CR1_BIASSEL_Pos                                 (7U)
#define OPA_CR1_BIASSEL_Msk                                 (0x7UL << OPA_CR1_BIASSEL_Pos)
#define OPA_CR1_BIASSEL                                     OPA_CR1_BIASSEL_Msk

// OPA_AZ
#define OPA_AZ_ADCTREN_Pos                                  (0U)
#define OPA_AZ_ADCTREN_Msk                                  (0x1UL << OPA_AZ_ADCTREN_Pos)
#define OPA_AZ_ADCTREN                                      OPA_AZ_ADCTREN_Msk
#define OPA_AZ_TRIGGER_Pos                                  (1U)
#define OPA_AZ_TRIGGER_Msk                                  (0x1UL << OPA_AZ_TRIGGER_Pos)
#define OPA_AZ_TRIGGER                                      OPA_AZ_TRIGGER_Msk
#define OPA_AZ_AZPULSE_Pos                                  (2U)
#define OPA_AZ_AZPULSE_Msk                                  (0x1UL << OPA_AZ_AZPULSE_Pos)
#define OPA_AZ_AZPULSE                                      OPA_AZ_AZPULSE_Msk
#define OPA_AZ_CLKSWSET_Pos                                 (3U)
#define OPA_AZ_CLKSWSET_Msk                                 (0x1UL << OPA_AZ_CLKSWSET_Pos)
#define OPA_AZ_CLKSWSET                                     OPA_AZ_CLKSWSET_Msk
#define OPA_AZ_CLKSEL_Pos                                   (4U)
#define OPA_AZ_CLKSEL_Msk                                   (0xFUL << OPA_AZ_CLKSEL_Pos)
#define OPA_AZ_CLKSEL                                       OPA_AZ_CLKSEL_Msk



//********************    Bits Define For Peripheral RAM    ********************//
// RAM_CR
#define RAM_CR_IE_Pos                                       (1U)
#define RAM_CR_IE_Msk                                       (0x1UL << RAM_CR_IE_Pos)
#define RAM_CR_IE                                           RAM_CR_IE_Msk

// RAM_ERRADDR
#define RAM_ERRADDR_ERRADDR_Pos                             (0U)
#define RAM_ERRADDR_ERRADDR_Msk                             (0x3FFFUL << RAM_ERRADDR_ERRADDR_Pos)
#define RAM_ERRADDR_ERRADDR                                 RAM_ERRADDR_ERRADDR_Msk

// RAM_IFR
#define RAM_IFR_ERR_Pos                                     (0U)
#define RAM_IFR_ERR_Msk                                     (0x1UL << RAM_IFR_ERR_Pos)
#define RAM_IFR_ERR                                         RAM_IFR_ERR_Msk

// RAM_ICLR
#define RAM_ICLR_ERRCLR_Pos                                 (0U)
#define RAM_ICLR_ERRCLR_Msk                                 (0x1UL << RAM_ICLR_ERRCLR_Pos)
#define RAM_ICLR_ERRCLR                                     RAM_ICLR_ERRCLR_Msk



//********************    Bits Define For Peripheral RTC    ********************//
// RTC_CR0
#define RTC_CR0_PRDS_Pos                                    (0U)
#define RTC_CR0_PRDS_Msk                                    (0x7UL << RTC_CR0_PRDS_Pos)
#define RTC_CR0_PRDS                                        RTC_CR0_PRDS_Msk
#define RTC_CR0_AMPM_Pos                                    (3U)
#define RTC_CR0_AMPM_Msk                                    (0x1UL << RTC_CR0_AMPM_Pos)
#define RTC_CR0_AMPM                                        RTC_CR0_AMPM_Msk
#define RTC_CR0_HZ1OE_Pos                                   (5U)
#define RTC_CR0_HZ1OE_Msk                                   (0x1UL << RTC_CR0_HZ1OE_Pos)
#define RTC_CR0_HZ1OE                                       RTC_CR0_HZ1OE_Msk
#define RTC_CR0_HZ1SEL_Pos                                  (6U)
#define RTC_CR0_HZ1SEL_Msk                                  (0x1UL << RTC_CR0_HZ1SEL_Pos)
#define RTC_CR0_HZ1SEL                                      RTC_CR0_HZ1SEL_Msk
#define RTC_CR0_START_Pos                                   (7U)
#define RTC_CR0_START_Msk                                   (0x1UL << RTC_CR0_START_Pos)
#define RTC_CR0_START                                       RTC_CR0_START_Msk
#define RTC_CR0_PRDX_Pos                                    (8U)
#define RTC_CR0_PRDX_Msk                                    (0x3FUL << RTC_CR0_PRDX_Pos)
#define RTC_CR0_PRDX                                        RTC_CR0_PRDX_Msk
#define RTC_CR0_PRDSEL_Pos                                  (14U)
#define RTC_CR0_PRDSEL_Msk                                  (0x1UL << RTC_CR0_PRDSEL_Pos)
#define RTC_CR0_PRDSEL                                      RTC_CR0_PRDSEL_Msk
#define RTC_CR0_TEST_Pos                                    (15U)
#define RTC_CR0_TEST_Msk                                    (0x1UL << RTC_CR0_TEST_Pos)
#define RTC_CR0_TEST                                        RTC_CR0_TEST_Msk

// RTC_CR1
#define RTC_CR1_WAIT_Pos                                    (0U)
#define RTC_CR1_WAIT_Msk                                    (0x1UL << RTC_CR1_WAIT_Pos)
#define RTC_CR1_WAIT                                        RTC_CR1_WAIT_Msk
#define RTC_CR1_WAITF_Pos                                   (1U)
#define RTC_CR1_WAITF_Msk                                   (0x1UL << RTC_CR1_WAITF_Pos)
#define RTC_CR1_WAITF                                       RTC_CR1_WAITF_Msk
#define RTC_CR1_CKSEL_Pos                                   (8U)
#define RTC_CR1_CKSEL_Msk                                   (0x7UL << RTC_CR1_CKSEL_Pos)
#define RTC_CR1_CKSEL                                       RTC_CR1_CKSEL_Msk

// RTC_SEC
#define RTC_SEC_SECL_Pos                                    (0U)
#define RTC_SEC_SECL_Msk                                    (0xFUL << RTC_SEC_SECL_Pos)
#define RTC_SEC_SECL                                        RTC_SEC_SECL_Msk
#define RTC_SEC_SECH_Pos                                    (4U)
#define RTC_SEC_SECH_Msk                                    (0x7UL << RTC_SEC_SECH_Pos)
#define RTC_SEC_SECH                                        RTC_SEC_SECH_Msk

// RTC_MIN
#define RTC_MIN_MINL_Pos                                    (0U)
#define RTC_MIN_MINL_Msk                                    (0xFUL << RTC_MIN_MINL_Pos)
#define RTC_MIN_MINL                                        RTC_MIN_MINL_Msk
#define RTC_MIN_MINH_Pos                                    (4U)
#define RTC_MIN_MINH_Msk                                    (0x7UL << RTC_MIN_MINH_Pos)
#define RTC_MIN_MINH                                        RTC_MIN_MINH_Msk

// RTC_HOUR
#define RTC_HOUR_HOURL_Pos                                  (0U)
#define RTC_HOUR_HOURL_Msk                                  (0xFUL << RTC_HOUR_HOURL_Pos)
#define RTC_HOUR_HOURL                                      RTC_HOUR_HOURL_Msk
#define RTC_HOUR_HOURH_Pos                                  (4U)
#define RTC_HOUR_HOURH_Msk                                  (0x3UL << RTC_HOUR_HOURH_Pos)
#define RTC_HOUR_HOURH                                      RTC_HOUR_HOURH_Msk

// RTC_WEEK
#define RTC_WEEK_WEEK_Pos                                   (0U)
#define RTC_WEEK_WEEK_Msk                                   (0x7UL << RTC_WEEK_WEEK_Pos)
#define RTC_WEEK_WEEK                                       RTC_WEEK_WEEK_Msk

// RTC_DAY
#define RTC_DAY_DAYL_Pos                                    (0U)
#define RTC_DAY_DAYL_Msk                                    (0xFUL << RTC_DAY_DAYL_Pos)
#define RTC_DAY_DAYL                                        RTC_DAY_DAYL_Msk
#define RTC_DAY_DAYH_Pos                                    (4U)
#define RTC_DAY_DAYH_Msk                                    (0x3UL << RTC_DAY_DAYH_Pos)
#define RTC_DAY_DAYH                                        RTC_DAY_DAYH_Msk

// RTC_MON
#define RTC_MON_MON_Pos                                     (0U)
#define RTC_MON_MON_Msk                                     (0x1FUL << RTC_MON_MON_Pos)
#define RTC_MON_MON                                         RTC_MON_MON_Msk

// RTC_YEAR
#define RTC_YEAR_YEARL_Pos                                  (0U)
#define RTC_YEAR_YEARL_Msk                                  (0xFUL << RTC_YEAR_YEARL_Pos)
#define RTC_YEAR_YEARL                                      RTC_YEAR_YEARL_Msk
#define RTC_YEAR_YEARH_Pos                                  (4U)
#define RTC_YEAR_YEARH_Msk                                  (0xFUL << RTC_YEAR_YEARH_Pos)
#define RTC_YEAR_YEARH                                      RTC_YEAR_YEARH_Msk

// RTC_COMPEN
#define RTC_COMPEN_CR_Pos                                   (0U)
#define RTC_COMPEN_CR_Msk                                   (0x1FFUL << RTC_COMPEN_CR_Pos)
#define RTC_COMPEN_CR                                       RTC_COMPEN_CR_Msk
#define RTC_COMPEN_EN_Pos                                   (15U)
#define RTC_COMPEN_EN_Msk                                   (0x1UL << RTC_COMPEN_EN_Pos)
#define RTC_COMPEN_EN                                       RTC_COMPEN_EN_Msk

// RTC_CR2
#define RTC_CR2_WUCKSEL_Pos                                 (0U)
#define RTC_CR2_WUCKSEL_Msk                                 (0x7UL << RTC_CR2_WUCKSEL_Pos)
#define RTC_CR2_WUCKSEL                                     RTC_CR2_WUCKSEL_Msk
#define RTC_CR2_TSEDG_Pos                                   (3U)
#define RTC_CR2_TSEDG_Msk                                   (0x1UL << RTC_CR2_TSEDG_Pos)
#define RTC_CR2_TSEDG                                       RTC_CR2_TSEDG_Msk
#define RTC_CR2_O2SEL_Pos                                   (4U)
#define RTC_CR2_O2SEL_Msk                                   (0x3UL << RTC_CR2_O2SEL_Pos)
#define RTC_CR2_O2SEL                                       RTC_CR2_O2SEL_Msk
#define RTC_CR2_TSE_Pos                                     (6U)
#define RTC_CR2_TSE_Msk                                     (0x1UL << RTC_CR2_TSE_Pos)
#define RTC_CR2_TSE                                         RTC_CR2_TSE_Msk
#define RTC_CR2_WUTE_Pos                                    (7U)
#define RTC_CR2_WUTE_Msk                                    (0x1UL << RTC_CR2_WUTE_Pos)
#define RTC_CR2_WUTE                                        RTC_CR2_WUTE_Msk
#define RTC_CR2_ALMAE_Pos                                   (9U)
#define RTC_CR2_ALMAE_Msk                                   (0x1UL << RTC_CR2_ALMAE_Pos)
#define RTC_CR2_ALMAE                                       RTC_CR2_ALMAE_Msk
#define RTC_CR2_ALMBE_Pos                                   (10U)
#define RTC_CR2_ALMBE_Msk                                   (0x1UL << RTC_CR2_ALMBE_Pos)
#define RTC_CR2_ALMBE                                       RTC_CR2_ALMBE_Msk

// RTC_ALMA
#define RTC_ALMA_SECL_Pos                                   (0U)
#define RTC_ALMA_SECL_Msk                                   (0xFUL << RTC_ALMA_SECL_Pos)
#define RTC_ALMA_SECL                                       RTC_ALMA_SECL_Msk
#define RTC_ALMA_SECH_Pos                                   (4U)
#define RTC_ALMA_SECH_Msk                                   (0x7UL << RTC_ALMA_SECH_Pos)
#define RTC_ALMA_SECH                                       RTC_ALMA_SECH_Msk
#define RTC_ALMA_MSKS_Pos                                   (7U)
#define RTC_ALMA_MSKS_Msk                                   (0x1UL << RTC_ALMA_MSKS_Pos)
#define RTC_ALMA_MSKS                                       RTC_ALMA_MSKS_Msk
#define RTC_ALMA_MINL_Pos                                   (8U)
#define RTC_ALMA_MINL_Msk                                   (0xFUL << RTC_ALMA_MINL_Pos)
#define RTC_ALMA_MINL                                       RTC_ALMA_MINL_Msk
#define RTC_ALMA_MINH_Pos                                   (12U)
#define RTC_ALMA_MINH_Msk                                   (0x7UL << RTC_ALMA_MINH_Pos)
#define RTC_ALMA_MINH                                       RTC_ALMA_MINH_Msk
#define RTC_ALMA_MSKM_Pos                                   (15U)
#define RTC_ALMA_MSKM_Msk                                   (0x1UL << RTC_ALMA_MSKM_Pos)
#define RTC_ALMA_MSKM                                       RTC_ALMA_MSKM_Msk
#define RTC_ALMA_HOURL_Pos                                  (16U)
#define RTC_ALMA_HOURL_Msk                                  (0xFUL << RTC_ALMA_HOURL_Pos)
#define RTC_ALMA_HOURL                                      RTC_ALMA_HOURL_Msk
#define RTC_ALMA_HOURH_Pos                                  (20U)
#define RTC_ALMA_HOURH_Msk                                  (0x3UL << RTC_ALMA_HOURH_Pos)
#define RTC_ALMA_HOURH                                      RTC_ALMA_HOURH_Msk
#define RTC_ALMA_MSKH_Pos                                   (23U)
#define RTC_ALMA_MSKH_Msk                                   (0x1UL << RTC_ALMA_MSKH_Pos)
#define RTC_ALMA_MSKH                                       RTC_ALMA_MSKH_Msk
#define RTC_ALMA_WEEK_Pos                                   (24U)
#define RTC_ALMA_WEEK_Msk                                   (0x7FUL << RTC_ALMA_WEEK_Pos)
#define RTC_ALMA_WEEK                                       RTC_ALMA_WEEK_Msk

// RTC_ALMB
#define RTC_ALMB_SECL_Pos                                   (0U)
#define RTC_ALMB_SECL_Msk                                   (0xFUL << RTC_ALMB_SECL_Pos)
#define RTC_ALMB_SECL                                       RTC_ALMB_SECL_Msk
#define RTC_ALMB_SECH_Pos                                   (4U)
#define RTC_ALMB_SECH_Msk                                   (0x7UL << RTC_ALMB_SECH_Pos)
#define RTC_ALMB_SECH                                       RTC_ALMB_SECH_Msk
#define RTC_ALMB_MSKS_Pos                                   (7U)
#define RTC_ALMB_MSKS_Msk                                   (0x1UL << RTC_ALMB_MSKS_Pos)
#define RTC_ALMB_MSKS                                       RTC_ALMB_MSKS_Msk
#define RTC_ALMB_MINL_Pos                                   (8U)
#define RTC_ALMB_MINL_Msk                                   (0xFUL << RTC_ALMB_MINL_Pos)
#define RTC_ALMB_MINL                                       RTC_ALMB_MINL_Msk
#define RTC_ALMB_MINH_Pos                                   (12U)
#define RTC_ALMB_MINH_Msk                                   (0x7UL << RTC_ALMB_MINH_Pos)
#define RTC_ALMB_MINH                                       RTC_ALMB_MINH_Msk
#define RTC_ALMB_MSKM_Pos                                   (15U)
#define RTC_ALMB_MSKM_Msk                                   (0x1UL << RTC_ALMB_MSKM_Pos)
#define RTC_ALMB_MSKM                                       RTC_ALMB_MSKM_Msk
#define RTC_ALMB_HOURL_Pos                                  (16U)
#define RTC_ALMB_HOURL_Msk                                  (0xFUL << RTC_ALMB_HOURL_Pos)
#define RTC_ALMB_HOURL                                      RTC_ALMB_HOURL_Msk
#define RTC_ALMB_HOURH_Pos                                  (20U)
#define RTC_ALMB_HOURH_Msk                                  (0x3UL << RTC_ALMB_HOURH_Pos)
#define RTC_ALMB_HOURH                                      RTC_ALMB_HOURH_Msk
#define RTC_ALMB_MSKH_Pos                                   (23U)
#define RTC_ALMB_MSKH_Msk                                   (0x1UL << RTC_ALMB_MSKH_Pos)
#define RTC_ALMB_MSKH                                       RTC_ALMB_MSKH_Msk
#define RTC_ALMB_WEEK_Pos                                   (24U)
#define RTC_ALMB_WEEK_Msk                                   (0x7FUL << RTC_ALMB_WEEK_Pos)
#define RTC_ALMB_WEEK                                       RTC_ALMB_WEEK_Msk

// RTC_TSTR
#define RTC_TSTR_SECL_Pos                                   (0U)
#define RTC_TSTR_SECL_Msk                                   (0xFUL << RTC_TSTR_SECL_Pos)
#define RTC_TSTR_SECL                                       RTC_TSTR_SECL_Msk
#define RTC_TSTR_SECH_Pos                                   (4U)
#define RTC_TSTR_SECH_Msk                                   (0x7UL << RTC_TSTR_SECH_Pos)
#define RTC_TSTR_SECH                                       RTC_TSTR_SECH_Msk
#define RTC_TSTR_MINL_Pos                                   (8U)
#define RTC_TSTR_MINL_Msk                                   (0xFUL << RTC_TSTR_MINL_Pos)
#define RTC_TSTR_MINL                                       RTC_TSTR_MINL_Msk
#define RTC_TSTR_MINH_Pos                                   (12U)
#define RTC_TSTR_MINH_Msk                                   (0x7UL << RTC_TSTR_MINH_Pos)
#define RTC_TSTR_MINH                                       RTC_TSTR_MINH_Msk
#define RTC_TSTR_HOURL_Pos                                  (16U)
#define RTC_TSTR_HOURL_Msk                                  (0xFUL << RTC_TSTR_HOURL_Pos)
#define RTC_TSTR_HOURL                                      RTC_TSTR_HOURL_Msk
#define RTC_TSTR_HOURH_Pos                                  (20U)
#define RTC_TSTR_HOURH_Msk                                  (0x3UL << RTC_TSTR_HOURH_Pos)
#define RTC_TSTR_HOURH                                      RTC_TSTR_HOURH_Msk

// RTC_TSDR
#define RTC_TSDR_DAYL_Pos                                   (0U)
#define RTC_TSDR_DAYL_Msk                                   (0xFUL << RTC_TSDR_DAYL_Pos)
#define RTC_TSDR_DAYL                                       RTC_TSDR_DAYL_Msk
#define RTC_TSDR_DAYH_Pos                                   (4U)
#define RTC_TSDR_DAYH_Msk                                   (0x3UL << RTC_TSDR_DAYH_Pos)
#define RTC_TSDR_DAYH                                       RTC_TSDR_DAYH_Msk
#define RTC_TSDR_MON_Pos                                    (8U)
#define RTC_TSDR_MON_Msk                                    (0x1FUL << RTC_TSDR_MON_Pos)
#define RTC_TSDR_MON                                        RTC_TSDR_MON_Msk
#define RTC_TSDR_WEEK_Pos                                   (13U)
#define RTC_TSDR_WEEK_Msk                                   (0x7UL << RTC_TSDR_WEEK_Pos)
#define RTC_TSDR_WEEK                                       RTC_TSDR_WEEK_Msk

// RTC_WUTARR
#define RTC_WUTARR_WUTARR_Pos                               (0U)
#define RTC_WUTARR_WUTARR_Msk                               (0xFFFFUL << RTC_WUTARR_WUTARR_Pos)
#define RTC_WUTARR_WUTARR                                   RTC_WUTARR_WUTARR_Msk

// RTC_IER
#define RTC_IER_ALMA_Pos                                    (0U)
#define RTC_IER_ALMA_Msk                                    (0x1UL << RTC_IER_ALMA_Pos)
#define RTC_IER_ALMA                                        RTC_IER_ALMA_Msk
#define RTC_IER_ALMB_Pos                                    (1U)
#define RTC_IER_ALMB_Msk                                    (0x1UL << RTC_IER_ALMB_Pos)
#define RTC_IER_ALMB                                        RTC_IER_ALMB_Msk
#define RTC_IER_WU_Pos                                      (2U)
#define RTC_IER_WU_Msk                                      (0x1UL << RTC_IER_WU_Pos)
#define RTC_IER_WU                                          RTC_IER_WU_Msk
#define RTC_IER_TS_Pos                                      (3U)
#define RTC_IER_TS_Msk                                      (0x1UL << RTC_IER_TS_Pos)
#define RTC_IER_TS                                          RTC_IER_TS_Msk
#define RTC_IER_TSOV_Pos                                    (4U)
#define RTC_IER_TSOV_Msk                                    (0x1UL << RTC_IER_TSOV_Pos)
#define RTC_IER_TSOV                                        RTC_IER_TSOV_Msk
#define RTC_IER_PRD_Pos                                     (6U)
#define RTC_IER_PRD_Msk                                     (0x1UL << RTC_IER_PRD_Pos)
#define RTC_IER_PRD                                         RTC_IER_PRD_Msk

// RTC_IFR
#define RTC_IFR_ALMA_Pos                                    (0U)
#define RTC_IFR_ALMA_Msk                                    (0x1UL << RTC_IFR_ALMA_Pos)
#define RTC_IFR_ALMA                                        RTC_IFR_ALMA_Msk
#define RTC_IFR_ALMB_Pos                                    (1U)
#define RTC_IFR_ALMB_Msk                                    (0x1UL << RTC_IFR_ALMB_Pos)
#define RTC_IFR_ALMB                                        RTC_IFR_ALMB_Msk
#define RTC_IFR_WU_Pos                                      (2U)
#define RTC_IFR_WU_Msk                                      (0x1UL << RTC_IFR_WU_Pos)
#define RTC_IFR_WU                                          RTC_IFR_WU_Msk
#define RTC_IFR_TS_Pos                                      (3U)
#define RTC_IFR_TS_Msk                                      (0x1UL << RTC_IFR_TS_Pos)
#define RTC_IFR_TS                                          RTC_IFR_TS_Msk
#define RTC_IFR_TSOV_Pos                                    (4U)
#define RTC_IFR_TSOV_Msk                                    (0x1UL << RTC_IFR_TSOV_Pos)
#define RTC_IFR_TSOV                                        RTC_IFR_TSOV_Msk
#define RTC_IFR_PRD_Pos                                     (6U)
#define RTC_IFR_PRD_Msk                                     (0x1UL << RTC_IFR_PRD_Pos)
#define RTC_IFR_PRD                                         RTC_IFR_PRD_Msk

// RTC_ICR
#define RTC_ICR_ALMA_Pos                                    (0U)
#define RTC_ICR_ALMA_Msk                                    (0x1UL << RTC_ICR_ALMA_Pos)
#define RTC_ICR_ALMA                                        RTC_ICR_ALMA_Msk
#define RTC_ICR_ALMB_Pos                                    (1U)
#define RTC_ICR_ALMB_Msk                                    (0x1UL << RTC_ICR_ALMB_Pos)
#define RTC_ICR_ALMB                                        RTC_ICR_ALMB_Msk
#define RTC_ICR_WU_Pos                                      (2U)
#define RTC_ICR_WU_Msk                                      (0x1UL << RTC_ICR_WU_Pos)
#define RTC_ICR_WU                                          RTC_ICR_WU_Msk
#define RTC_ICR_TS_Pos                                      (3U)
#define RTC_ICR_TS_Msk                                      (0x1UL << RTC_ICR_TS_Pos)
#define RTC_ICR_TS                                          RTC_ICR_TS_Msk
#define RTC_ICR_TSOV_Pos                                    (4U)
#define RTC_ICR_TSOV_Msk                                    (0x1UL << RTC_ICR_TSOV_Pos)
#define RTC_ICR_TSOV                                        RTC_ICR_TSOV_Msk
#define RTC_ICR_PRD_Pos                                     (6U)
#define RTC_ICR_PRD_Msk                                     (0x1UL << RTC_ICR_PRD_Pos)
#define RTC_ICR_PRD                                         RTC_ICR_PRD_Msk

// RTC_WPR
#define RTC_WPR_WPR_Pos                                     (0U)
#define RTC_WPR_WPR_Msk                                     (0xFFUL << RTC_WPR_WPR_Pos)
#define RTC_WPR_WPR                                         RTC_WPR_WPR_Msk



//********************    Bits Define For Peripheral SPI    ********************//
// SPI_CR0
#define SPI_CR0_EN_Pos                                      (0U)
#define SPI_CR0_EN_Msk                                      (0x1UL << SPI_CR0_EN_Pos)
#define SPI_CR0_EN                                          SPI_CR0_EN_Msk
#define SPI_CR0_BRR_Pos                                     (1U)
#define SPI_CR0_BRR_Msk                                     (0x7UL << SPI_CR0_BRR_Pos)
#define SPI_CR0_BRR                                         SPI_CR0_BRR_Msk
#define SPI_CR0_CPHA_Pos                                    (4U)
#define SPI_CR0_CPHA_Msk                                    (0x1UL << SPI_CR0_CPHA_Pos)
#define SPI_CR0_CPHA                                        SPI_CR0_CPHA_Msk
#define SPI_CR0_CPOL_Pos                                    (5U)
#define SPI_CR0_CPOL_Msk                                    (0x1UL << SPI_CR0_CPOL_Pos)
#define SPI_CR0_CPOL                                        SPI_CR0_CPOL_Msk
#define SPI_CR0_MSTR_Pos                                    (6U)
#define SPI_CR0_MSTR_Msk                                    (0x1UL << SPI_CR0_MSTR_Pos)
#define SPI_CR0_MSTR                                        SPI_CR0_MSTR_Msk
#define SPI_CR0_LSBF_Pos                                    (7U)
#define SPI_CR0_LSBF_Msk                                    (0x1UL << SPI_CR0_LSBF_Pos)
#define SPI_CR0_LSBF                                        SPI_CR0_LSBF_Msk
#define SPI_CR0_WIDTH_Pos                                   (8U)
#define SPI_CR0_WIDTH_Msk                                   (0xFUL << SPI_CR0_WIDTH_Pos)
#define SPI_CR0_WIDTH                                       SPI_CR0_WIDTH_Msk
#define SPI_CR0_SSM_Pos                                     (12U)
#define SPI_CR0_SSM_Msk                                     (0x1UL << SPI_CR0_SSM_Pos)
#define SPI_CR0_SSM                                         SPI_CR0_SSM_Msk
#define SPI_CR0_CM_Pos                                      (13U)
#define SPI_CR0_CM_Msk                                      (0x3UL << SPI_CR0_CM_Pos)
#define SPI_CR0_CM                                          SPI_CR0_CM_Msk
#define SPI_CR0_SMP_Pos                                     (15U)
#define SPI_CR0_SMP_Msk                                     (0x1UL << SPI_CR0_SMP_Pos)
#define SPI_CR0_SMP                                         SPI_CR0_SMP_Msk

// SPI_CR1
#define SPI_CR1_TXEIE_Pos                                   (0U)
#define SPI_CR1_TXEIE_Msk                                   (0x1UL << SPI_CR1_TXEIE_Pos)
#define SPI_CR1_TXEIE                                       SPI_CR1_TXEIE_Msk
#define SPI_CR1_RXNEIE_Pos                                  (1U)
#define SPI_CR1_RXNEIE_Msk                                  (0x1UL << SPI_CR1_RXNEIE_Pos)
#define SPI_CR1_RXNEIE                                      SPI_CR1_RXNEIE_Msk
#define SPI_CR1_SSFIE_Pos                                   (2U)
#define SPI_CR1_SSFIE_Msk                                   (0x1UL << SPI_CR1_SSFIE_Pos)
#define SPI_CR1_SSFIE                                       SPI_CR1_SSFIE_Msk
#define SPI_CR1_SSRIE_Pos                                   (3U)
#define SPI_CR1_SSRIE_Msk                                   (0x1UL << SPI_CR1_SSRIE_Pos)
#define SPI_CR1_SSRIE                                       SPI_CR1_SSRIE_Msk
#define SPI_CR1_UDFIE_Pos                                   (4U)
#define SPI_CR1_UDFIE_Msk                                   (0x1UL << SPI_CR1_UDFIE_Pos)
#define SPI_CR1_UDFIE                                       SPI_CR1_UDFIE_Msk
#define SPI_CR1_OVFIE_Pos                                   (5U)
#define SPI_CR1_OVFIE_Msk                                   (0x1UL << SPI_CR1_OVFIE_Pos)
#define SPI_CR1_OVFIE                                       SPI_CR1_OVFIE_Msk
#define SPI_CR1_SSERRIE_Pos                                 (6U)
#define SPI_CR1_SSERRIE_Msk                                 (0x1UL << SPI_CR1_SSERRIE_Pos)
#define SPI_CR1_SSERRIE                                     SPI_CR1_SSERRIE_Msk
#define SPI_CR1_MODFIE_Pos                                  (7U)
#define SPI_CR1_MODFIE_Msk                                  (0x1UL << SPI_CR1_MODFIE_Pos)
#define SPI_CR1_MODFIE                                      SPI_CR1_MODFIE_Msk
#define SPI_CR1_DMARXEN_Pos                                 (8U)
#define SPI_CR1_DMARXEN_Msk                                 (0x1UL << SPI_CR1_DMARXEN_Pos)
#define SPI_CR1_DMARXEN                                     SPI_CR1_DMARXEN_Msk
#define SPI_CR1_DMATXEN_Pos                                 (9U)
#define SPI_CR1_DMATXEN_Msk                                 (0x1UL << SPI_CR1_DMATXEN_Pos)
#define SPI_CR1_DMATXEN                                     SPI_CR1_DMATXEN_Msk

// SPI_HDOE
#define SPI_HDOE_HDOE_Pos                                   (0U)
#define SPI_HDOE_HDOE_Msk                                   (0x1UL << SPI_HDOE_HDOE_Pos)
#define SPI_HDOE_HDOE                                       SPI_HDOE_HDOE_Msk

// SPI_SSI
#define SPI_SSI_SSI_Pos                                     (0U)
#define SPI_SSI_SSI_Msk                                     (0x1UL << SPI_SSI_SSI_Pos)
#define SPI_SSI_SSI                                         SPI_SSI_SSI_Msk

// SPI_SR
#define SPI_SR_TXE_Pos                                      (0U)
#define SPI_SR_TXE_Msk                                      (0x1UL << SPI_SR_TXE_Pos)
#define SPI_SR_TXE                                          SPI_SR_TXE_Msk
#define SPI_SR_RXNE_Pos                                     (1U)
#define SPI_SR_RXNE_Msk                                     (0x1UL << SPI_SR_RXNE_Pos)
#define SPI_SR_RXNE                                         SPI_SR_RXNE_Msk
#define SPI_SR_SSF_Pos                                      (2U)
#define SPI_SR_SSF_Msk                                      (0x1UL << SPI_SR_SSF_Pos)
#define SPI_SR_SSF                                          SPI_SR_SSF_Msk
#define SPI_SR_SSR_Pos                                      (3U)
#define SPI_SR_SSR_Msk                                      (0x1UL << SPI_SR_SSR_Pos)
#define SPI_SR_SSR                                          SPI_SR_SSR_Msk
#define SPI_SR_UDF_Pos                                      (4U)
#define SPI_SR_UDF_Msk                                      (0x1UL << SPI_SR_UDF_Pos)
#define SPI_SR_UDF                                          SPI_SR_UDF_Msk
#define SPI_SR_OVF_Pos                                      (5U)
#define SPI_SR_OVF_Msk                                      (0x1UL << SPI_SR_OVF_Pos)
#define SPI_SR_OVF                                          SPI_SR_OVF_Msk
#define SPI_SR_SSERR_Pos                                    (6U)
#define SPI_SR_SSERR_Msk                                    (0x1UL << SPI_SR_SSERR_Pos)
#define SPI_SR_SSERR                                        SPI_SR_SSERR_Msk
#define SPI_SR_MODF_Pos                                     (7U)
#define SPI_SR_MODF_Msk                                     (0x1UL << SPI_SR_MODF_Pos)
#define SPI_SR_MODF                                         SPI_SR_MODF_Msk
#define SPI_SR_BUSY_Pos                                     (8U)
#define SPI_SR_BUSY_Msk                                     (0x1UL << SPI_SR_BUSY_Pos)
#define SPI_SR_BUSY                                         SPI_SR_BUSY_Msk
#define SPI_SR_SSLVL_Pos                                    (9U)
#define SPI_SR_SSLVL_Msk                                    (0x1UL << SPI_SR_SSLVL_Pos)
#define SPI_SR_SSLVL                                        SPI_SR_SSLVL_Msk

// SPI_ICR
#define SPI_ICR_TXE_Pos                                     (0U)
#define SPI_ICR_TXE_Msk                                     (0x1UL << SPI_ICR_TXE_Pos)
#define SPI_ICR_TXE                                         SPI_ICR_TXE_Msk
#define SPI_ICR_RXNE_Pos                                    (1U)
#define SPI_ICR_RXNE_Msk                                    (0x1UL << SPI_ICR_RXNE_Pos)
#define SPI_ICR_RXNE                                        SPI_ICR_RXNE_Msk
#define SPI_ICR_SSF_Pos                                     (2U)
#define SPI_ICR_SSF_Msk                                     (0x1UL << SPI_ICR_SSF_Pos)
#define SPI_ICR_SSF                                         SPI_ICR_SSF_Msk
#define SPI_ICR_SSR_Pos                                     (3U)
#define SPI_ICR_SSR_Msk                                     (0x1UL << SPI_ICR_SSR_Pos)
#define SPI_ICR_SSR                                         SPI_ICR_SSR_Msk
#define SPI_ICR_UDF_Pos                                     (4U)
#define SPI_ICR_UDF_Msk                                     (0x1UL << SPI_ICR_UDF_Pos)
#define SPI_ICR_UDF                                         SPI_ICR_UDF_Msk
#define SPI_ICR_OVF_Pos                                     (5U)
#define SPI_ICR_OVF_Msk                                     (0x1UL << SPI_ICR_OVF_Pos)
#define SPI_ICR_OVF                                         SPI_ICR_OVF_Msk
#define SPI_ICR_SSERR_Pos                                   (6U)
#define SPI_ICR_SSERR_Msk                                   (0x1UL << SPI_ICR_SSERR_Pos)
#define SPI_ICR_SSERR                                       SPI_ICR_SSERR_Msk
#define SPI_ICR_MODF_Pos                                    (7U)
#define SPI_ICR_MODF_Msk                                    (0x1UL << SPI_ICR_MODF_Pos)
#define SPI_ICR_MODF                                        SPI_ICR_MODF_Msk

// SPI_DR
#define SPI_DR_DR_Pos                                       (0U)
#define SPI_DR_DR_Msk                                       (0xFFFFUL << SPI_DR_DR_Pos)
#define SPI_DR_DR                                           SPI_DR_DR_Msk



//********************    Bits Define For Peripheral SYSCTRL    ********************//
// SYSCTRL_CR0
#define SYSCTRL_CR0_CLKSRC_Pos                              (0U)
#define SYSCTRL_CR0_CLKSRC_Msk                              (0x7UL << SYSCTRL_CR0_CLKSRC_Pos)
#define SYSCTRL_CR0_CLKSRC                                  SYSCTRL_CR0_CLKSRC_Msk
#define SYSCTRL_CR0_HCLKPRS_Pos                             (3U)
#define SYSCTRL_CR0_HCLKPRS_Msk                             (0x7UL << SYSCTRL_CR0_HCLKPRS_Pos)
#define SYSCTRL_CR0_HCLKPRS                                 SYSCTRL_CR0_HCLKPRS_Msk
#define SYSCTRL_CR0_PCLKPRS_Pos                             (6U)
#define SYSCTRL_CR0_PCLKPRS_Msk                             (0x3UL << SYSCTRL_CR0_PCLKPRS_Pos)
#define SYSCTRL_CR0_PCLKPRS                                 SYSCTRL_CR0_PCLKPRS_Msk

// SYSCTRL_CR1
#define SYSCTRL_CR1_SWDUSEIO_Pos                            (0U)
#define SYSCTRL_CR1_SWDUSEIO_Msk                            (0x1UL << SYSCTRL_CR1_SWDUSEIO_Pos)
#define SYSCTRL_CR1_SWDUSEIO                                SYSCTRL_CR1_SWDUSEIO_Msk
#define SYSCTRL_CR1_LOCKUP_EN_Pos                           (1U)
#define SYSCTRL_CR1_LOCKUP_EN_Msk                           (0x1UL << SYSCTRL_CR1_LOCKUP_EN_Pos)
#define SYSCTRL_CR1_LOCKUP_EN                               SYSCTRL_CR1_LOCKUP_EN_Msk
#define SYSCTRL_CR1_WAKEUPBYRCH_Pos                         (2U)
#define SYSCTRL_CR1_WAKEUPBYRCH_Msk                         (0x1UL << SYSCTRL_CR1_WAKEUPBYRCH_Pos)
#define SYSCTRL_CR1_WAKEUPBYRCH                             SYSCTRL_CR1_WAKEUPBYRCH_Msk
#define SYSCTRL_CR1_RTCLPW_Pos                              (3U)
#define SYSCTRL_CR1_RTCLPW_Msk                              (0x1UL << SYSCTRL_CR1_RTCLPW_Pos)
#define SYSCTRL_CR1_RTCLPW                                  SYSCTRL_CR1_RTCLPW_Msk
#define SYSCTRL_CR1_RTCADJ_Pos                              (4U)
#define SYSCTRL_CR1_RTCADJ_Msk                              (0x7UL << SYSCTRL_CR1_RTCADJ_Pos)
#define SYSCTRL_CR1_RTCADJ                                  SYSCTRL_CR1_RTCADJ_Msk
#define SYSCTRL_CR1_AUTOSWITCH_Pos                          (7U)
#define SYSCTRL_CR1_AUTOSWITCH_Msk                          (0x1UL << SYSCTRL_CR1_AUTOSWITCH_Pos)
#define SYSCTRL_CR1_AUTOSWITCH                              SYSCTRL_CR1_AUTOSWITCH_Msk
#define SYSCTRL_CR1_SPIPCTRL_Pos                            (8U)
#define SYSCTRL_CR1_SPIPCTRL_Msk                            (0x1UL << SYSCTRL_CR1_SPIPCTRL_Pos)
#define SYSCTRL_CR1_SPIPCTRL                                SYSCTRL_CR1_SPIPCTRL_Msk
#define SYSCTRL_CR1_XTHFLT_Pos                              (9U)
#define SYSCTRL_CR1_XTHFLT_Msk                              (0x1UL << SYSCTRL_CR1_XTHFLT_Pos)
#define SYSCTRL_CR1_XTHFLT                                  SYSCTRL_CR1_XTHFLT_Msk
#define SYSCTRL_CR1_GTIM0CFG_Pos                            (10U)
#define SYSCTRL_CR1_GTIM0CFG_Msk                            (0x1UL << SYSCTRL_CR1_GTIM0CFG_Pos)
#define SYSCTRL_CR1_GTIM0CFG                                SYSCTRL_CR1_GTIM0CFG_Msk
#define SYSCTRL_CR1_GTIM1CFG_Pos                            (11U)
#define SYSCTRL_CR1_GTIM1CFG_Msk                            (0x1UL << SYSCTRL_CR1_GTIM1CFG_Pos)
#define SYSCTRL_CR1_GTIM1CFG                                SYSCTRL_CR1_GTIM1CFG_Msk
#define SYSCTRL_CR1_FASTIOENB_Pos                           (12U)
#define SYSCTRL_CR1_FASTIOENB_Msk                           (0x1UL << SYSCTRL_CR1_FASTIOENB_Pos)
#define SYSCTRL_CR1_FASTIOENB                               SYSCTRL_CR1_FASTIOENB_Msk

// SYSCTRL_CR2
#define SYSCTRL_CR2_RCH_Pos                                 (0U)
#define SYSCTRL_CR2_RCH_Msk                                 (0x1UL << SYSCTRL_CR2_RCH_Pos)
#define SYSCTRL_CR2_RCH                                     SYSCTRL_CR2_RCH_Msk
#define SYSCTRL_CR2_XTH_Pos                                 (1U)
#define SYSCTRL_CR2_XTH_Msk                                 (0x1UL << SYSCTRL_CR2_XTH_Pos)
#define SYSCTRL_CR2_XTH                                     SYSCTRL_CR2_XTH_Msk
#define SYSCTRL_CR2_RCL_Pos                                 (2U)
#define SYSCTRL_CR2_RCL_Msk                                 (0x1UL << SYSCTRL_CR2_RCL_Pos)
#define SYSCTRL_CR2_RCL                                     SYSCTRL_CR2_RCL_Msk
#define SYSCTRL_CR2_XTL_Pos                                 (3U)
#define SYSCTRL_CR2_XTL_Msk                                 (0x1UL << SYSCTRL_CR2_XTL_Pos)
#define SYSCTRL_CR2_XTL                                     SYSCTRL_CR2_XTL_Msk
#define SYSCTRL_CR2_PLL_Pos                                 (4U)
#define SYSCTRL_CR2_PLL_Msk                                 (0x1UL << SYSCTRL_CR2_PLL_Pos)
#define SYSCTRL_CR2_PLL                                     SYSCTRL_CR2_PLL_Msk
#define SYSCTRL_CR2_EXXTH_Pos                               (5U)
#define SYSCTRL_CR2_EXXTH_Msk                               (0x1UL << SYSCTRL_CR2_EXXTH_Pos)
#define SYSCTRL_CR2_EXXTH                                   SYSCTRL_CR2_EXXTH_Msk
#define SYSCTRL_CR2_EXXTL_Pos                               (6U)
#define SYSCTRL_CR2_EXXTL_Msk                               (0x1UL << SYSCTRL_CR2_EXXTL_Pos)
#define SYSCTRL_CR2_EXXTL                                   SYSCTRL_CR2_EXXTL_Msk
#define SYSCTRL_CR2_XTLLOCK_Pos                             (7U)
#define SYSCTRL_CR2_XTLLOCK_Msk                             (0x1UL << SYSCTRL_CR2_XTLLOCK_Pos)
#define SYSCTRL_CR2_XTLLOCK                                 SYSCTRL_CR2_XTLLOCK_Msk

// SYSCTRL_CR3
#define SYSCTRL_CR3_CR3_Pos                                 (0U)
#define SYSCTRL_CR3_CR3_Msk                                 (0xFFFFUL << SYSCTRL_CR3_CR3_Pos)
#define SYSCTRL_CR3_CR3                                     SYSCTRL_CR3_CR3_Msk

// SYSCTRL_RCHCR
#define SYSCTRL_RCHCR_DIV_Pos                               (0U)
#define SYSCTRL_RCHCR_DIV_Msk                               (0x7UL << SYSCTRL_RCHCR_DIV_Pos)
#define SYSCTRL_RCHCR_DIV                                   SYSCTRL_RCHCR_DIV_Msk

// SYSCTRL_XTHCR
#define SYSCTRL_XTHCR_DRIVER_Pos                            (0U)
#define SYSCTRL_XTHCR_DRIVER_Msk                            (0x3UL << SYSCTRL_XTHCR_DRIVER_Pos)
#define SYSCTRL_XTHCR_DRIVER                                SYSCTRL_XTHCR_DRIVER_Msk
#define SYSCTRL_XTHCR_RANGE_Pos                             (2U)
#define SYSCTRL_XTHCR_RANGE_Msk                             (0x3UL << SYSCTRL_XTHCR_RANGE_Pos)
#define SYSCTRL_XTHCR_RANGE                                 SYSCTRL_XTHCR_RANGE_Msk
#define SYSCTRL_XTHCR_STARTUP_Pos                           (4U)
#define SYSCTRL_XTHCR_STARTUP_Msk                           (0x3UL << SYSCTRL_XTHCR_STARTUP_Pos)
#define SYSCTRL_XTHCR_STARTUP                               SYSCTRL_XTHCR_STARTUP_Msk
#define SYSCTRL_XTHCR_DETEN_Pos                             (6U)
#define SYSCTRL_XTHCR_DETEN_Msk                             (0x1UL << SYSCTRL_XTHCR_DETEN_Pos)
#define SYSCTRL_XTHCR_DETEN                                 SYSCTRL_XTHCR_DETEN_Msk
#define SYSCTRL_XTHCR_DETTIME_Pos                           (7U)
#define SYSCTRL_XTHCR_DETTIME_Msk                           (0x1UL << SYSCTRL_XTHCR_DETTIME_Pos)
#define SYSCTRL_XTHCR_DETTIME                               SYSCTRL_XTHCR_DETTIME_Msk
#define SYSCTRL_XTHCR_DETIE_Pos                             (8U)
#define SYSCTRL_XTHCR_DETIE_Msk                             (0x1UL << SYSCTRL_XTHCR_DETIE_Pos)
#define SYSCTRL_XTHCR_DETIE                                 SYSCTRL_XTHCR_DETIE_Msk

// SYSCTRL_RCLCR
#define SYSCTRL_RCLCR_STARTUP_Pos                           (10U)
#define SYSCTRL_RCLCR_STARTUP_Msk                           (0x3UL << SYSCTRL_RCLCR_STARTUP_Pos)
#define SYSCTRL_RCLCR_STARTUP                               SYSCTRL_RCLCR_STARTUP_Msk

// SYSCTRL_XTLCR
#define SYSCTRL_XTLCR_DRIVER_Pos                            (0U)
#define SYSCTRL_XTLCR_DRIVER_Msk                            (0x3UL << SYSCTRL_XTLCR_DRIVER_Pos)
#define SYSCTRL_XTLCR_DRIVER                                SYSCTRL_XTLCR_DRIVER_Msk
#define SYSCTRL_XTLCR_AMP_SEL_Pos                           (2U)
#define SYSCTRL_XTLCR_AMP_SEL_Msk                           (0x3UL << SYSCTRL_XTLCR_AMP_SEL_Pos)
#define SYSCTRL_XTLCR_AMP_SEL                               SYSCTRL_XTLCR_AMP_SEL_Msk
#define SYSCTRL_XTLCR_STARTUP_Pos                           (4U)
#define SYSCTRL_XTLCR_STARTUP_Msk                           (0x3UL << SYSCTRL_XTLCR_STARTUP_Pos)
#define SYSCTRL_XTLCR_STARTUP                               SYSCTRL_XTLCR_STARTUP_Msk
#define SYSCTRL_XTLCR_DETEN_Pos                             (6U)
#define SYSCTRL_XTLCR_DETEN_Msk                             (0x1UL << SYSCTRL_XTLCR_DETEN_Pos)
#define SYSCTRL_XTLCR_DETEN                                 SYSCTRL_XTLCR_DETEN_Msk
#define SYSCTRL_XTLCR_DETTIME_Pos                           (7U)
#define SYSCTRL_XTLCR_DETTIME_Msk                           (0x1UL << SYSCTRL_XTLCR_DETTIME_Pos)
#define SYSCTRL_XTLCR_DETTIME                               SYSCTRL_XTLCR_DETTIME_Msk
#define SYSCTRL_XTLCR_DETIE_Pos                             (8U)
#define SYSCTRL_XTLCR_DETIE_Msk                             (0x1UL << SYSCTRL_XTLCR_DETIE_Pos)
#define SYSCTRL_XTLCR_DETIE                                 SYSCTRL_XTLCR_DETIE_Msk

// SYSCTRL_PLLCR
#define SYSCTRL_PLLCR_SRC_Pos                               (0U)
#define SYSCTRL_PLLCR_SRC_Msk                               (0x3UL << SYSCTRL_PLLCR_SRC_Pos)
#define SYSCTRL_PLLCR_SRC                                   SYSCTRL_PLLCR_SRC_Msk
#define SYSCTRL_PLLCR_DIVR_Pos                              (2U)
#define SYSCTRL_PLLCR_DIVR_Msk                              (0x1UL << SYSCTRL_PLLCR_DIVR_Pos)
#define SYSCTRL_PLLCR_DIVR                                  SYSCTRL_PLLCR_DIVR_Msk
#define SYSCTRL_PLLCR_WAITCYCLE_Pos                         (4U)
#define SYSCTRL_PLLCR_WAITCYCLE_Msk                         (0x7UL << SYSCTRL_PLLCR_WAITCYCLE_Pos)
#define SYSCTRL_PLLCR_WAITCYCLE                             SYSCTRL_PLLCR_WAITCYCLE_Msk
#define SYSCTRL_PLLCR_DIVN_Pos                              (8U)
#define SYSCTRL_PLLCR_DIVN_Msk                              (0x7FUL << SYSCTRL_PLLCR_DIVN_Pos)
#define SYSCTRL_PLLCR_DIVN                                  SYSCTRL_PLLCR_DIVN_Msk
#define SYSCTRL_PLLCR_DIVF_Pos                              (16U)
#define SYSCTRL_PLLCR_DIVF_Msk                              (0x7UL << SYSCTRL_PLLCR_DIVF_Pos)
#define SYSCTRL_PLLCR_DIVF                                  SYSCTRL_PLLCR_DIVF_Msk
#define SYSCTRL_PLLCR_POSTDIV_Pos                           (20U)
#define SYSCTRL_PLLCR_POSTDIV_Msk                           (0xFUL << SYSCTRL_PLLCR_POSTDIV_Pos)
#define SYSCTRL_PLLCR_POSTDIV                               SYSCTRL_PLLCR_POSTDIV_Msk

// SYSCTRL_RCHTRIM
#define SYSCTRL_RCHTRIM_TRIML_Pos                           (0U)
#define SYSCTRL_RCHTRIM_TRIML_Msk                           (0x3FUL << SYSCTRL_RCHTRIM_TRIML_Pos)
#define SYSCTRL_RCHTRIM_TRIML                               SYSCTRL_RCHTRIM_TRIML_Msk
#define SYSCTRL_RCHTRIM_TRIMH_Pos                           (6U)
#define SYSCTRL_RCHTRIM_TRIMH_Msk                           (0x1FUL << SYSCTRL_RCHTRIM_TRIMH_Pos)
#define SYSCTRL_RCHTRIM_TRIMH                               SYSCTRL_RCHTRIM_TRIMH_Msk

// SYSCTRL_RCLTRIM
#define SYSCTRL_RCLTRIM_TRIM_Pos                            (0U)
#define SYSCTRL_RCLTRIM_TRIM_Msk                            (0x3FFUL << SYSCTRL_RCLTRIM_TRIM_Pos)
#define SYSCTRL_RCLTRIM_TRIM                                SYSCTRL_RCLTRIM_TRIM_Msk

// SYSCTRL_STATE
#define SYSCTRL_STATE_RCH_Pos                               (0U)
#define SYSCTRL_STATE_RCH_Msk                               (0x1UL << SYSCTRL_STATE_RCH_Pos)
#define SYSCTRL_STATE_RCH                                   SYSCTRL_STATE_RCH_Msk
#define SYSCTRL_STATE_XTH_Pos                               (1U)
#define SYSCTRL_STATE_XTH_Msk                               (0x1UL << SYSCTRL_STATE_XTH_Pos)
#define SYSCTRL_STATE_XTH                                   SYSCTRL_STATE_XTH_Msk
#define SYSCTRL_STATE_RCL_Pos                               (2U)
#define SYSCTRL_STATE_RCL_Msk                               (0x1UL << SYSCTRL_STATE_RCL_Pos)
#define SYSCTRL_STATE_RCL                                   SYSCTRL_STATE_RCL_Msk
#define SYSCTRL_STATE_XTL_Pos                               (3U)
#define SYSCTRL_STATE_XTL_Msk                               (0x1UL << SYSCTRL_STATE_XTL_Pos)
#define SYSCTRL_STATE_XTL                                   SYSCTRL_STATE_XTL_Msk
#define SYSCTRL_STATE_PLL_Pos                               (4U)
#define SYSCTRL_STATE_PLL_Msk                               (0x1UL << SYSCTRL_STATE_PLL_Pos)
#define SYSCTRL_STATE_PLL                                   SYSCTRL_STATE_PLL_Msk
#define SYSCTRL_STATE_PLLLOCK_Pos                           (5U)
#define SYSCTRL_STATE_PLLLOCK_Msk                           (0x1UL << SYSCTRL_STATE_PLLLOCK_Pos)
#define SYSCTRL_STATE_PLLLOCK                               SYSCTRL_STATE_PLLLOCK_Msk
#define SYSCTRL_STATE_XTHFAIL_Pos                           (8U)
#define SYSCTRL_STATE_XTHFAIL_Msk                           (0x1UL << SYSCTRL_STATE_XTHFAIL_Pos)
#define SYSCTRL_STATE_XTHFAIL                               SYSCTRL_STATE_XTHFAIL_Msk
#define SYSCTRL_STATE_XTHFAULT_Pos                          (9U)
#define SYSCTRL_STATE_XTHFAULT_Msk                          (0x1UL << SYSCTRL_STATE_XTHFAULT_Pos)
#define SYSCTRL_STATE_XTHFAULT                              SYSCTRL_STATE_XTHFAULT_Msk
#define SYSCTRL_STATE_XTLFAIL_Pos                           (10U)
#define SYSCTRL_STATE_XTLFAIL_Msk                           (0x1UL << SYSCTRL_STATE_XTLFAIL_Pos)
#define SYSCTRL_STATE_XTLFAIL                               SYSCTRL_STATE_XTLFAIL_Msk
#define SYSCTRL_STATE_XTLFAULT_Pos                          (11U)
#define SYSCTRL_STATE_XTLFAULT_Msk                          (0x1UL << SYSCTRL_STATE_XTLFAULT_Pos)
#define SYSCTRL_STATE_XTLFAULT                              SYSCTRL_STATE_XTLFAULT_Msk

// SYSCTRL_PERICLKEN0
#define SYSCTRL_PERICLKEN0_USART0_Pos                       (0U)
#define SYSCTRL_PERICLKEN0_USART0_Msk                       (0x1UL << SYSCTRL_PERICLKEN0_USART0_Pos)
#define SYSCTRL_PERICLKEN0_USART0                           SYSCTRL_PERICLKEN0_USART0_Msk
#define SYSCTRL_PERICLKEN0_USART1_Pos                       (1U)
#define SYSCTRL_PERICLKEN0_USART1_Msk                       (0x1UL << SYSCTRL_PERICLKEN0_USART1_Pos)
#define SYSCTRL_PERICLKEN0_USART1                           SYSCTRL_PERICLKEN0_USART1_Msk
#define SYSCTRL_PERICLKEN0_LPUART0_Pos                      (2U)
#define SYSCTRL_PERICLKEN0_LPUART0_Msk                      (0x1UL << SYSCTRL_PERICLKEN0_LPUART0_Pos)
#define SYSCTRL_PERICLKEN0_LPUART0                          SYSCTRL_PERICLKEN0_LPUART0_Msk
#define SYSCTRL_PERICLKEN0_LPUART1_Pos                      (3U)
#define SYSCTRL_PERICLKEN0_LPUART1_Msk                      (0x1UL << SYSCTRL_PERICLKEN0_LPUART1_Pos)
#define SYSCTRL_PERICLKEN0_LPUART1                          SYSCTRL_PERICLKEN0_LPUART1_Msk
#define SYSCTRL_PERICLKEN0_I2C0_Pos                         (4U)
#define SYSCTRL_PERICLKEN0_I2C0_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_I2C0_Pos)
#define SYSCTRL_PERICLKEN0_I2C0                             SYSCTRL_PERICLKEN0_I2C0_Msk
#define SYSCTRL_PERICLKEN0_I2C1_Pos                         (5U)
#define SYSCTRL_PERICLKEN0_I2C1_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_I2C1_Pos)
#define SYSCTRL_PERICLKEN0_I2C1                             SYSCTRL_PERICLKEN0_I2C1_Msk
#define SYSCTRL_PERICLKEN0_SPI0_Pos                         (6U)
#define SYSCTRL_PERICLKEN0_SPI0_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_SPI0_Pos)
#define SYSCTRL_PERICLKEN0_SPI0                             SYSCTRL_PERICLKEN0_SPI0_Msk
#define SYSCTRL_PERICLKEN0_SPI1_Pos                         (7U)
#define SYSCTRL_PERICLKEN0_SPI1_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_SPI1_Pos)
#define SYSCTRL_PERICLKEN0_SPI1                             SYSCTRL_PERICLKEN0_SPI1_Msk
#define SYSCTRL_PERICLKEN0_ATIM0_Pos                        (8U)
#define SYSCTRL_PERICLKEN0_ATIM0_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_ATIM0_Pos)
#define SYSCTRL_PERICLKEN0_ATIM0                            SYSCTRL_PERICLKEN0_ATIM0_Msk
#define SYSCTRL_PERICLKEN0_LPTIM_Pos                        (9U)
#define SYSCTRL_PERICLKEN0_LPTIM_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_LPTIM_Pos)
#define SYSCTRL_PERICLKEN0_LPTIM                            SYSCTRL_PERICLKEN0_LPTIM_Msk
#define SYSCTRL_PERICLKEN0_ATIM1_Pos                        (10U)
#define SYSCTRL_PERICLKEN0_ATIM1_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_ATIM1_Pos)
#define SYSCTRL_PERICLKEN0_ATIM1                            SYSCTRL_PERICLKEN0_ATIM1_Msk
#define SYSCTRL_PERICLKEN0_ATIM3_Pos                        (11U)
#define SYSCTRL_PERICLKEN0_ATIM3_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_ATIM3_Pos)
#define SYSCTRL_PERICLKEN0_ATIM3                            SYSCTRL_PERICLKEN0_ATIM3_Msk
#define SYSCTRL_PERICLKEN0_ATIM2_Pos                        (12U)
#define SYSCTRL_PERICLKEN0_ATIM2_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_ATIM2_Pos)
#define SYSCTRL_PERICLKEN0_ATIM2                            SYSCTRL_PERICLKEN0_ATIM2_Msk
#define SYSCTRL_PERICLKEN0_OPA_Pos                          (13U)
#define SYSCTRL_PERICLKEN0_OPA_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_OPA_Pos)
#define SYSCTRL_PERICLKEN0_OPA                              SYSCTRL_PERICLKEN0_OPA_Msk
#define SYSCTRL_PERICLKEN0_WWDT_Pos                         (14U)
#define SYSCTRL_PERICLKEN0_WWDT_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_WWDT_Pos)
#define SYSCTRL_PERICLKEN0_WWDT                             SYSCTRL_PERICLKEN0_WWDT_Msk
#define SYSCTRL_PERICLKEN0_IWDT_Pos                         (15U)
#define SYSCTRL_PERICLKEN0_IWDT_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_IWDT_Pos)
#define SYSCTRL_PERICLKEN0_IWDT                             SYSCTRL_PERICLKEN0_IWDT_Msk
#define SYSCTRL_PERICLKEN0_ADC_Pos                          (16U)
#define SYSCTRL_PERICLKEN0_ADC_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_ADC_Pos)
#define SYSCTRL_PERICLKEN0_ADC                              SYSCTRL_PERICLKEN0_ADC_Msk
#define SYSCTRL_PERICLKEN0_VCLVD_Pos                        (17U)
#define SYSCTRL_PERICLKEN0_VCLVD_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_VCLVD_Pos)
#define SYSCTRL_PERICLKEN0_VCLVD                            SYSCTRL_PERICLKEN0_VCLVD_Msk
#define SYSCTRL_PERICLKEN0_I2CSLV_Pos                       (18U)
#define SYSCTRL_PERICLKEN0_I2CSLV_Msk                       (0x1UL << SYSCTRL_PERICLKEN0_I2CSLV_Pos)
#define SYSCTRL_PERICLKEN0_I2CSLV                           SYSCTRL_PERICLKEN0_I2CSLV_Msk
#define SYSCTRL_PERICLKEN0_RTC_Pos                          (20U)
#define SYSCTRL_PERICLKEN0_RTC_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_RTC_Pos)
#define SYSCTRL_PERICLKEN0_RTC                              SYSCTRL_PERICLKEN0_RTC_Msk
#define SYSCTRL_PERICLKEN0_CTRIM_Pos                        (21U)
#define SYSCTRL_PERICLKEN0_CTRIM_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_CTRIM_Pos)
#define SYSCTRL_PERICLKEN0_CTRIM                            SYSCTRL_PERICLKEN0_CTRIM_Msk
#define SYSCTRL_PERICLKEN0_TICK_Pos                         (24U)
#define SYSCTRL_PERICLKEN0_TICK_Msk                         (0x1UL << SYSCTRL_PERICLKEN0_TICK_Pos)
#define SYSCTRL_PERICLKEN0_TICK                             SYSCTRL_PERICLKEN0_TICK_Msk
#define SYSCTRL_PERICLKEN0_SWD_Pos                          (25U)
#define SYSCTRL_PERICLKEN0_SWD_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_SWD_Pos)
#define SYSCTRL_PERICLKEN0_SWD                              SYSCTRL_PERICLKEN0_SWD_Msk
#define SYSCTRL_PERICLKEN0_CRC_Pos                          (26U)
#define SYSCTRL_PERICLKEN0_CRC_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_CRC_Pos)
#define SYSCTRL_PERICLKEN0_CRC                              SYSCTRL_PERICLKEN0_CRC_Msk
#define SYSCTRL_PERICLKEN0_DMA_Pos                          (29U)
#define SYSCTRL_PERICLKEN0_DMA_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_DMA_Pos)
#define SYSCTRL_PERICLKEN0_DMA                              SYSCTRL_PERICLKEN0_DMA_Msk
#define SYSCTRL_PERICLKEN0_EAU_Pos                          (30U)
#define SYSCTRL_PERICLKEN0_EAU_Msk                          (0x1UL << SYSCTRL_PERICLKEN0_EAU_Pos)
#define SYSCTRL_PERICLKEN0_EAU                              SYSCTRL_PERICLKEN0_EAU_Msk
#define SYSCTRL_PERICLKEN0_FLASH_Pos                        (31U)
#define SYSCTRL_PERICLKEN0_FLASH_Msk                        (0x1UL << SYSCTRL_PERICLKEN0_FLASH_Pos)
#define SYSCTRL_PERICLKEN0_FLASH                            SYSCTRL_PERICLKEN0_FLASH_Msk

// SYSCTRL_PERICLKEN1
#define SYSCTRL_PERICLKEN1_GPIOA_Pos                        (0U)
#define SYSCTRL_PERICLKEN1_GPIOA_Msk                        (0x1UL << SYSCTRL_PERICLKEN1_GPIOA_Pos)
#define SYSCTRL_PERICLKEN1_GPIOA                            SYSCTRL_PERICLKEN1_GPIOA_Msk
#define SYSCTRL_PERICLKEN1_GPIOB_Pos                        (1U)
#define SYSCTRL_PERICLKEN1_GPIOB_Msk                        (0x1UL << SYSCTRL_PERICLKEN1_GPIOB_Pos)
#define SYSCTRL_PERICLKEN1_GPIOB                            SYSCTRL_PERICLKEN1_GPIOB_Msk
#define SYSCTRL_PERICLKEN1_GPIOC_Pos                        (2U)
#define SYSCTRL_PERICLKEN1_GPIOC_Msk                        (0x1UL << SYSCTRL_PERICLKEN1_GPIOC_Pos)
#define SYSCTRL_PERICLKEN1_GPIOC                            SYSCTRL_PERICLKEN1_GPIOC_Msk
#define SYSCTRL_PERICLKEN1_GPIOD_Pos                        (3U)
#define SYSCTRL_PERICLKEN1_GPIOD_Msk                        (0x1UL << SYSCTRL_PERICLKEN1_GPIOD_Pos)
#define SYSCTRL_PERICLKEN1_GPIOD                            SYSCTRL_PERICLKEN1_GPIOD_Msk
#define SYSCTRL_PERICLKEN1_CAN_Pos                          (7U)
#define SYSCTRL_PERICLKEN1_CAN_Msk                          (0x1UL << SYSCTRL_PERICLKEN1_CAN_Pos)
#define SYSCTRL_PERICLKEN1_CAN                              SYSCTRL_PERICLKEN1_CAN_Msk
#define SYSCTRL_PERICLKEN1_GTIM0_Pos                        (8U)
#define SYSCTRL_PERICLKEN1_GTIM0_Msk                        (0x1UL << SYSCTRL_PERICLKEN1_GTIM0_Pos)
#define SYSCTRL_PERICLKEN1_GTIM0                            SYSCTRL_PERICLKEN1_GTIM0_Msk
#define SYSCTRL_PERICLKEN1_GTIM1_Pos                        (9U)
#define SYSCTRL_PERICLKEN1_GTIM1_Msk                        (0x1UL << SYSCTRL_PERICLKEN1_GTIM1_Pos)
#define SYSCTRL_PERICLKEN1_GTIM1                            SYSCTRL_PERICLKEN1_GTIM1_Msk

// SYSCTRL_PERIRESET0
#define SYSCTRL_PERIRESET0_USART0_Pos                       (0U)
#define SYSCTRL_PERIRESET0_USART0_Msk                       (0x1UL << SYSCTRL_PERIRESET0_USART0_Pos)
#define SYSCTRL_PERIRESET0_USART0                           SYSCTRL_PERIRESET0_USART0_Msk
#define SYSCTRL_PERIRESET0_USART1_Pos                       (1U)
#define SYSCTRL_PERIRESET0_USART1_Msk                       (0x1UL << SYSCTRL_PERIRESET0_USART1_Pos)
#define SYSCTRL_PERIRESET0_USART1                           SYSCTRL_PERIRESET0_USART1_Msk
#define SYSCTRL_PERIRESET0_LPUART0_Pos                      (2U)
#define SYSCTRL_PERIRESET0_LPUART0_Msk                      (0x1UL << SYSCTRL_PERIRESET0_LPUART0_Pos)
#define SYSCTRL_PERIRESET0_LPUART0                          SYSCTRL_PERIRESET0_LPUART0_Msk
#define SYSCTRL_PERIRESET0_LPUART1_Pos                      (3U)
#define SYSCTRL_PERIRESET0_LPUART1_Msk                      (0x1UL << SYSCTRL_PERIRESET0_LPUART1_Pos)
#define SYSCTRL_PERIRESET0_LPUART1                          SYSCTRL_PERIRESET0_LPUART1_Msk
#define SYSCTRL_PERIRESET0_I2C0_Pos                         (4U)
#define SYSCTRL_PERIRESET0_I2C0_Msk                         (0x1UL << SYSCTRL_PERIRESET0_I2C0_Pos)
#define SYSCTRL_PERIRESET0_I2C0                             SYSCTRL_PERIRESET0_I2C0_Msk
#define SYSCTRL_PERIRESET0_I2C1_Pos                         (5U)
#define SYSCTRL_PERIRESET0_I2C1_Msk                         (0x1UL << SYSCTRL_PERIRESET0_I2C1_Pos)
#define SYSCTRL_PERIRESET0_I2C1                             SYSCTRL_PERIRESET0_I2C1_Msk
#define SYSCTRL_PERIRESET0_SPI0_Pos                         (6U)
#define SYSCTRL_PERIRESET0_SPI0_Msk                         (0x1UL << SYSCTRL_PERIRESET0_SPI0_Pos)
#define SYSCTRL_PERIRESET0_SPI0                             SYSCTRL_PERIRESET0_SPI0_Msk
#define SYSCTRL_PERIRESET0_SPI1_Pos                         (7U)
#define SYSCTRL_PERIRESET0_SPI1_Msk                         (0x1UL << SYSCTRL_PERIRESET0_SPI1_Pos)
#define SYSCTRL_PERIRESET0_SPI1                             SYSCTRL_PERIRESET0_SPI1_Msk
#define SYSCTRL_PERIRESET0_ATIM0_Pos                        (8U)
#define SYSCTRL_PERIRESET0_ATIM0_Msk                        (0x1UL << SYSCTRL_PERIRESET0_ATIM0_Pos)
#define SYSCTRL_PERIRESET0_ATIM0                            SYSCTRL_PERIRESET0_ATIM0_Msk
#define SYSCTRL_PERIRESET0_LPTIM_Pos                        (9U)
#define SYSCTRL_PERIRESET0_LPTIM_Msk                        (0x1UL << SYSCTRL_PERIRESET0_LPTIM_Pos)
#define SYSCTRL_PERIRESET0_LPTIM                            SYSCTRL_PERIRESET0_LPTIM_Msk
#define SYSCTRL_PERIRESET0_ATIM1_Pos                        (10U)
#define SYSCTRL_PERIRESET0_ATIM1_Msk                        (0x1UL << SYSCTRL_PERIRESET0_ATIM1_Pos)
#define SYSCTRL_PERIRESET0_ATIM1                            SYSCTRL_PERIRESET0_ATIM1_Msk
#define SYSCTRL_PERIRESET0_ATIM3_Pos                        (11U)
#define SYSCTRL_PERIRESET0_ATIM3_Msk                        (0x1UL << SYSCTRL_PERIRESET0_ATIM3_Pos)
#define SYSCTRL_PERIRESET0_ATIM3                            SYSCTRL_PERIRESET0_ATIM3_Msk
#define SYSCTRL_PERIRESET0_ATIM2_Pos                        (12U)
#define SYSCTRL_PERIRESET0_ATIM2_Msk                        (0x1UL << SYSCTRL_PERIRESET0_ATIM2_Pos)
#define SYSCTRL_PERIRESET0_ATIM2                            SYSCTRL_PERIRESET0_ATIM2_Msk
#define SYSCTRL_PERIRESET0_OPA_Pos                          (13U)
#define SYSCTRL_PERIRESET0_OPA_Msk                          (0x1UL << SYSCTRL_PERIRESET0_OPA_Pos)
#define SYSCTRL_PERIRESET0_OPA                              SYSCTRL_PERIRESET0_OPA_Msk
#define SYSCTRL_PERIRESET0_WWDT_Pos                         (14U)
#define SYSCTRL_PERIRESET0_WWDT_Msk                         (0x1UL << SYSCTRL_PERIRESET0_WWDT_Pos)
#define SYSCTRL_PERIRESET0_WWDT                             SYSCTRL_PERIRESET0_WWDT_Msk
#define SYSCTRL_PERIRESET0_IWDT_Pos                         (15U)
#define SYSCTRL_PERIRESET0_IWDT_Msk                         (0x1UL << SYSCTRL_PERIRESET0_IWDT_Pos)
#define SYSCTRL_PERIRESET0_IWDT                             SYSCTRL_PERIRESET0_IWDT_Msk
#define SYSCTRL_PERIRESET0_ADC_Pos                          (16U)
#define SYSCTRL_PERIRESET0_ADC_Msk                          (0x1UL << SYSCTRL_PERIRESET0_ADC_Pos)
#define SYSCTRL_PERIRESET0_ADC                              SYSCTRL_PERIRESET0_ADC_Msk
#define SYSCTRL_PERIRESET0_VCLVD_Pos                        (17U)
#define SYSCTRL_PERIRESET0_VCLVD_Msk                        (0x1UL << SYSCTRL_PERIRESET0_VCLVD_Pos)
#define SYSCTRL_PERIRESET0_VCLVD                            SYSCTRL_PERIRESET0_VCLVD_Msk
#define SYSCTRL_PERIRESET0_I2CSLV_Pos                       (18U)
#define SYSCTRL_PERIRESET0_I2CSLV_Msk                       (0x1UL << SYSCTRL_PERIRESET0_I2CSLV_Pos)
#define SYSCTRL_PERIRESET0_I2CSLV                           SYSCTRL_PERIRESET0_I2CSLV_Msk
#define SYSCTRL_PERIRESET0_RTC_Pos                          (20U)
#define SYSCTRL_PERIRESET0_RTC_Msk                          (0x1UL << SYSCTRL_PERIRESET0_RTC_Pos)
#define SYSCTRL_PERIRESET0_RTC                              SYSCTRL_PERIRESET0_RTC_Msk
#define SYSCTRL_PERIRESET0_CTRIM_Pos                        (21U)
#define SYSCTRL_PERIRESET0_CTRIM_Msk                        (0x1UL << SYSCTRL_PERIRESET0_CTRIM_Pos)
#define SYSCTRL_PERIRESET0_CTRIM                            SYSCTRL_PERIRESET0_CTRIM_Msk
#define SYSCTRL_PERIRESET0_TICK_Pos                         (24U)
#define SYSCTRL_PERIRESET0_TICK_Msk                         (0x1UL << SYSCTRL_PERIRESET0_TICK_Pos)
#define SYSCTRL_PERIRESET0_TICK                             SYSCTRL_PERIRESET0_TICK_Msk
#define SYSCTRL_PERIRESET0_SWD_Pos                          (25U)
#define SYSCTRL_PERIRESET0_SWD_Msk                          (0x1UL << SYSCTRL_PERIRESET0_SWD_Pos)
#define SYSCTRL_PERIRESET0_SWD                              SYSCTRL_PERIRESET0_SWD_Msk
#define SYSCTRL_PERIRESET0_CRC_Pos                          (26U)
#define SYSCTRL_PERIRESET0_CRC_Msk                          (0x1UL << SYSCTRL_PERIRESET0_CRC_Pos)
#define SYSCTRL_PERIRESET0_CRC                              SYSCTRL_PERIRESET0_CRC_Msk
#define SYSCTRL_PERIRESET0_DMA_Pos                          (29U)
#define SYSCTRL_PERIRESET0_DMA_Msk                          (0x1UL << SYSCTRL_PERIRESET0_DMA_Pos)
#define SYSCTRL_PERIRESET0_DMA                              SYSCTRL_PERIRESET0_DMA_Msk
#define SYSCTRL_PERIRESET0_EAU_Pos                          (30U)
#define SYSCTRL_PERIRESET0_EAU_Msk                          (0x1UL << SYSCTRL_PERIRESET0_EAU_Pos)
#define SYSCTRL_PERIRESET0_EAU                              SYSCTRL_PERIRESET0_EAU_Msk

// SYSCTRL_PERIRESET1
#define SYSCTRL_PERIRESET1_GPIOA_Pos                        (0U)
#define SYSCTRL_PERIRESET1_GPIOA_Msk                        (0x1UL << SYSCTRL_PERIRESET1_GPIOA_Pos)
#define SYSCTRL_PERIRESET1_GPIOA                            SYSCTRL_PERIRESET1_GPIOA_Msk
#define SYSCTRL_PERIRESET1_GPIOB_Pos                        (1U)
#define SYSCTRL_PERIRESET1_GPIOB_Msk                        (0x1UL << SYSCTRL_PERIRESET1_GPIOB_Pos)
#define SYSCTRL_PERIRESET1_GPIOB                            SYSCTRL_PERIRESET1_GPIOB_Msk
#define SYSCTRL_PERIRESET1_GPIOC_Pos                        (2U)
#define SYSCTRL_PERIRESET1_GPIOC_Msk                        (0x1UL << SYSCTRL_PERIRESET1_GPIOC_Pos)
#define SYSCTRL_PERIRESET1_GPIOC                            SYSCTRL_PERIRESET1_GPIOC_Msk
#define SYSCTRL_PERIRESET1_GPIOD_Pos                        (3U)
#define SYSCTRL_PERIRESET1_GPIOD_Msk                        (0x1UL << SYSCTRL_PERIRESET1_GPIOD_Pos)
#define SYSCTRL_PERIRESET1_GPIOD                            SYSCTRL_PERIRESET1_GPIOD_Msk
#define SYSCTRL_PERIRESET1_CAN_Pos                          (7U)
#define SYSCTRL_PERIRESET1_CAN_Msk                          (0x1UL << SYSCTRL_PERIRESET1_CAN_Pos)
#define SYSCTRL_PERIRESET1_CAN                              SYSCTRL_PERIRESET1_CAN_Msk
#define SYSCTRL_PERIRESET1_GTIM0_Pos                        (8U)
#define SYSCTRL_PERIRESET1_GTIM0_Msk                        (0x1UL << SYSCTRL_PERIRESET1_GTIM0_Pos)
#define SYSCTRL_PERIRESET1_GTIM0                            SYSCTRL_PERIRESET1_GTIM0_Msk
#define SYSCTRL_PERIRESET1_GTIM1_Pos                        (9U)
#define SYSCTRL_PERIRESET1_GTIM1_Msk                        (0x1UL << SYSCTRL_PERIRESET1_GTIM1_Pos)
#define SYSCTRL_PERIRESET1_GTIM1                            SYSCTRL_PERIRESET1_GTIM1_Msk

// SYSCTRL_RSTFLAG
#define SYSCTRL_RSTFLAG_POR5V_Pos                           (0U)
#define SYSCTRL_RSTFLAG_POR5V_Msk                           (0x1UL << SYSCTRL_RSTFLAG_POR5V_Pos)
#define SYSCTRL_RSTFLAG_POR5V                               SYSCTRL_RSTFLAG_POR5V_Msk
#define SYSCTRL_RSTFLAG_POR12V_Pos                          (1U)
#define SYSCTRL_RSTFLAG_POR12V_Msk                          (0x1UL << SYSCTRL_RSTFLAG_POR12V_Pos)
#define SYSCTRL_RSTFLAG_POR12V                              SYSCTRL_RSTFLAG_POR12V_Msk
#define SYSCTRL_RSTFLAG_LVD_Pos                             (2U)
#define SYSCTRL_RSTFLAG_LVD_Msk                             (0x1UL << SYSCTRL_RSTFLAG_LVD_Pos)
#define SYSCTRL_RSTFLAG_LVD                                 SYSCTRL_RSTFLAG_LVD_Msk
#define SYSCTRL_RSTFLAG_IWDT_Pos                            (3U)
#define SYSCTRL_RSTFLAG_IWDT_Msk                            (0x1UL << SYSCTRL_RSTFLAG_IWDT_Pos)
#define SYSCTRL_RSTFLAG_IWDT                                SYSCTRL_RSTFLAG_IWDT_Msk
#define SYSCTRL_RSTFLAG_WWDT_Pos                            (4U)
#define SYSCTRL_RSTFLAG_WWDT_Msk                            (0x1UL << SYSCTRL_RSTFLAG_WWDT_Pos)
#define SYSCTRL_RSTFLAG_WWDT                                SYSCTRL_RSTFLAG_WWDT_Msk
#define SYSCTRL_RSTFLAG_LOCKUP_Pos                          (5U)
#define SYSCTRL_RSTFLAG_LOCKUP_Msk                          (0x1UL << SYSCTRL_RSTFLAG_LOCKUP_Pos)
#define SYSCTRL_RSTFLAG_LOCKUP                              SYSCTRL_RSTFLAG_LOCKUP_Msk
#define SYSCTRL_RSTFLAG_SYSREQ_Pos                          (6U)
#define SYSCTRL_RSTFLAG_SYSREQ_Msk                          (0x1UL << SYSCTRL_RSTFLAG_SYSREQ_Pos)
#define SYSCTRL_RSTFLAG_SYSREQ                              SYSCTRL_RSTFLAG_SYSREQ_Msk
#define SYSCTRL_RSTFLAG_RSTB_Pos                            (7U)
#define SYSCTRL_RSTFLAG_RSTB_Msk                            (0x1UL << SYSCTRL_RSTFLAG_RSTB_Pos)
#define SYSCTRL_RSTFLAG_RSTB                                SYSCTRL_RSTFLAG_RSTB_Msk

// SYSCTRL_DBGSTOP
#define SYSCTRL_DBGSTOP_ATIM0_Pos                           (0U)
#define SYSCTRL_DBGSTOP_ATIM0_Msk                           (0x1UL << SYSCTRL_DBGSTOP_ATIM0_Pos)
#define SYSCTRL_DBGSTOP_ATIM0                               SYSCTRL_DBGSTOP_ATIM0_Msk
#define SYSCTRL_DBGSTOP_ATIM1_Pos                           (1U)
#define SYSCTRL_DBGSTOP_ATIM1_Msk                           (0x1UL << SYSCTRL_DBGSTOP_ATIM1_Pos)
#define SYSCTRL_DBGSTOP_ATIM1                               SYSCTRL_DBGSTOP_ATIM1_Msk
#define SYSCTRL_DBGSTOP_ATIM2_Pos                           (2U)
#define SYSCTRL_DBGSTOP_ATIM2_Msk                           (0x1UL << SYSCTRL_DBGSTOP_ATIM2_Pos)
#define SYSCTRL_DBGSTOP_ATIM2                               SYSCTRL_DBGSTOP_ATIM2_Msk
#define SYSCTRL_DBGSTOP_LPTIM_Pos                           (3U)
#define SYSCTRL_DBGSTOP_LPTIM_Msk                           (0x1UL << SYSCTRL_DBGSTOP_LPTIM_Pos)
#define SYSCTRL_DBGSTOP_LPTIM                               SYSCTRL_DBGSTOP_LPTIM_Msk
#define SYSCTRL_DBGSTOP_GTIM0_Pos                           (4U)
#define SYSCTRL_DBGSTOP_GTIM0_Msk                           (0x1UL << SYSCTRL_DBGSTOP_GTIM0_Pos)
#define SYSCTRL_DBGSTOP_GTIM0                               SYSCTRL_DBGSTOP_GTIM0_Msk
#define SYSCTRL_DBGSTOP_GTIM1_Pos                           (5U)
#define SYSCTRL_DBGSTOP_GTIM1_Msk                           (0x1UL << SYSCTRL_DBGSTOP_GTIM1_Pos)
#define SYSCTRL_DBGSTOP_GTIM1                               SYSCTRL_DBGSTOP_GTIM1_Msk
#define SYSCTRL_DBGSTOP_CTRIM_Pos                           (7U)
#define SYSCTRL_DBGSTOP_CTRIM_Msk                           (0x1UL << SYSCTRL_DBGSTOP_CTRIM_Pos)
#define SYSCTRL_DBGSTOP_CTRIM                               SYSCTRL_DBGSTOP_CTRIM_Msk
#define SYSCTRL_DBGSTOP_IWDT_Pos                            (8U)
#define SYSCTRL_DBGSTOP_IWDT_Msk                            (0x1UL << SYSCTRL_DBGSTOP_IWDT_Pos)
#define SYSCTRL_DBGSTOP_IWDT                                SYSCTRL_DBGSTOP_IWDT_Msk
#define SYSCTRL_DBGSTOP_RTC_Pos                             (9U)
#define SYSCTRL_DBGSTOP_RTC_Msk                             (0x1UL << SYSCTRL_DBGSTOP_RTC_Pos)
#define SYSCTRL_DBGSTOP_RTC                                 SYSCTRL_DBGSTOP_RTC_Msk
#define SYSCTRL_DBGSTOP_TICK_Pos                            (10U)
#define SYSCTRL_DBGSTOP_TICK_Msk                            (0x1UL << SYSCTRL_DBGSTOP_TICK_Pos)
#define SYSCTRL_DBGSTOP_TICK                                SYSCTRL_DBGSTOP_TICK_Msk
#define SYSCTRL_DBGSTOP_ATIM3_Pos                           (11U)
#define SYSCTRL_DBGSTOP_ATIM3_Msk                           (0x1UL << SYSCTRL_DBGSTOP_ATIM3_Pos)
#define SYSCTRL_DBGSTOP_ATIM3                               SYSCTRL_DBGSTOP_ATIM3_Msk
#define SYSCTRL_DBGSTOP_WWDT_Pos                            (12U)
#define SYSCTRL_DBGSTOP_WWDT_Msk                            (0x1UL << SYSCTRL_DBGSTOP_WWDT_Pos)
#define SYSCTRL_DBGSTOP_WWDT                                SYSCTRL_DBGSTOP_WWDT_Msk



//********************    Bits Define For Peripheral USART    ********************//
// USART_CR1
#define USART_CR1_RE_Pos                                    (0U)
#define USART_CR1_RE_Msk                                    (0x1UL << USART_CR1_RE_Pos)
#define USART_CR1_RE                                        USART_CR1_RE_Msk
#define USART_CR1_TE_Pos                                    (1U)
#define USART_CR1_TE_Msk                                    (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_TE                                        USART_CR1_TE_Msk
#define USART_CR1_PS_Pos                                    (2U)
#define USART_CR1_PS_Msk                                    (0x1UL << USART_CR1_PS_Pos)
#define USART_CR1_PS                                        USART_CR1_PS_Msk
#define USART_CR1_PCE_Pos                                   (3U)
#define USART_CR1_PCE_Msk                                   (0x1UL << USART_CR1_PCE_Pos)
#define USART_CR1_PCE                                       USART_CR1_PCE_Msk
#define USART_CR1_CHLEN_Pos                                 (4U)
#define USART_CR1_CHLEN_Msk                                 (0x1UL << USART_CR1_CHLEN_Pos)
#define USART_CR1_CHLEN                                     USART_CR1_CHLEN_Msk
#define USART_CR1_STOP_Pos                                  (5U)
#define USART_CR1_STOP_Msk                                  (0x1UL << USART_CR1_STOP_Pos)
#define USART_CR1_STOP                                      USART_CR1_STOP_Msk
#define USART_CR1_MSB_Pos                                   (6U)
#define USART_CR1_MSB_Msk                                   (0x1UL << USART_CR1_MSB_Pos)
#define USART_CR1_MSB                                       USART_CR1_MSB_Msk
#define USART_CR1_OVER8_Pos                                 (7U)
#define USART_CR1_OVER8_Msk                                 (0x1UL << USART_CR1_OVER8_Pos)
#define USART_CR1_OVER8                                     USART_CR1_OVER8_Msk
#define USART_CR1_TOE_Pos                                   (8U)
#define USART_CR1_TOE_Msk                                   (0x7UL << USART_CR1_TOE_Pos)
#define USART_CR1_TOE                                       USART_CR1_TOE_Msk
#define USART_CR1_SBS_Pos                                   (11U)
#define USART_CR1_SBS_Msk                                   (0x1UL << USART_CR1_SBS_Pos)
#define USART_CR1_SBS                                       USART_CR1_SBS_Msk
#define USART_CR1_COMB_Pos                                  (12U)
#define USART_CR1_COMB_Msk                                  (0x1UL << USART_CR1_COMB_Pos)
#define USART_CR1_COMB                                      USART_CR1_COMB_Msk
#define USART_CR1_MPE_Pos                                   (13U)
#define USART_CR1_MPE_Msk                                   (0x1UL << USART_CR1_MPE_Pos)
#define USART_CR1_MPE                                       USART_CR1_MPE_Msk
#define USART_CR1_SLME_Pos                                  (14U)
#define USART_CR1_SLME_Msk                                  (0x1UL << USART_CR1_SLME_Pos)
#define USART_CR1_SLME                                      USART_CR1_SLME_Msk

// USART_CR2
#define USART_CR2_RXDMAEN_Pos                               (0U)
#define USART_CR2_RXDMAEN_Msk                               (0x1UL << USART_CR2_RXDMAEN_Pos)
#define USART_CR2_RXDMAEN                                   USART_CR2_RXDMAEN_Msk
#define USART_CR2_TXDMAEN_Pos                               (1U)
#define USART_CR2_TXDMAEN_Msk                               (0x1UL << USART_CR2_TXDMAEN_Pos)
#define USART_CR2_TXDMAEN                                   USART_CR2_TXDMAEN_Msk
#define USART_CR2_RTSEN_Pos                                 (2U)
#define USART_CR2_RTSEN_Msk                                 (0x1UL << USART_CR2_RTSEN_Pos)
#define USART_CR2_RTSEN                                     USART_CR2_RTSEN_Msk
#define USART_CR2_CTSEN_Pos                                 (3U)
#define USART_CR2_CTSEN_Msk                                 (0x1UL << USART_CR2_CTSEN_Pos)
#define USART_CR2_CTSEN                                     USART_CR2_CTSEN_Msk
#define USART_CR2_RXINV_Pos                                 (4U)
#define USART_CR2_RXINV_Msk                                 (0x1UL << USART_CR2_RXINV_Pos)
#define USART_CR2_RXINV                                     USART_CR2_RXINV_Msk
#define USART_CR2_TXINV_Pos                                 (5U)
#define USART_CR2_TXINV_Msk                                 (0x1UL << USART_CR2_TXINV_Pos)
#define USART_CR2_TXINV                                     USART_CR2_TXINV_Msk
#define USART_CR2_SYNC_Pos                                  (6U)
#define USART_CR2_SYNC_Msk                                  (0x1UL << USART_CR2_SYNC_Pos)
#define USART_CR2_SYNC                                      USART_CR2_SYNC_Msk
#define USART_CR2_SWAP_Pos                                  (7U)
#define USART_CR2_SWAP_Msk                                  (0x1UL << USART_CR2_SWAP_Pos)
#define USART_CR2_SWAP                                      USART_CR2_SWAP_Msk
#define USART_CR2_CLKC_Pos                                  (8U)
#define USART_CR2_CLKC_Msk                                  (0x3UL << USART_CR2_CLKC_Pos)
#define USART_CR2_CLKC                                      USART_CR2_CLKC_Msk

// USART_CR3
#define USART_CR3_LINEN_Pos                                 (0U)
#define USART_CR3_LINEN_Msk                                 (0x1UL << USART_CR3_LINEN_Pos)
#define USART_CR3_LINEN                                     USART_CR3_LINEN_Msk
#define USART_CR3_LBDE_Pos                                  (1U)
#define USART_CR3_LBDE_Msk                                  (0x1UL << USART_CR3_LBDE_Pos)
#define USART_CR3_LBDE                                      USART_CR3_LBDE_Msk
#define USART_CR3_ABRE_Pos                                  (2U)
#define USART_CR3_ABRE_Msk                                  (0x1UL << USART_CR3_ABRE_Pos)
#define USART_CR3_ABRE                                      USART_CR3_ABRE_Msk
#define USART_CR3_BREAK_Pos                                 (3U)
#define USART_CR3_BREAK_Msk                                 (0x1UL << USART_CR3_BREAK_Pos)
#define USART_CR3_BREAK                                     USART_CR3_BREAK_Msk
#define USART_CR3_SCEN_Pos                                  (4U)
#define USART_CR3_SCEN_Msk                                  (0x1UL << USART_CR3_SCEN_Pos)
#define USART_CR3_SCEN                                      USART_CR3_SCEN_Msk
#define USART_CR3_BCN_Pos                                   (5U)
#define USART_CR3_BCN_Msk                                   (0x7UL << USART_CR3_BCN_Pos)
#define USART_CR3_BCN                                       USART_CR3_BCN_Msk
#define USART_CR3_SMCPU_Pos                                 (8U)
#define USART_CR3_SMCPU_Msk                                 (0x3UL << USART_CR3_SMCPU_Pos)
#define USART_CR3_SMCPU                                     USART_CR3_SMCPU_Msk
#define USART_CR3_IREN_Pos                                  (13U)
#define USART_CR3_IREN_Msk                                  (0x1UL << USART_CR3_IREN_Pos)
#define USART_CR3_IREN                                      USART_CR3_IREN_Msk
#define USART_CR3_IRCW_Pos                                  (14U)
#define USART_CR3_IRCW_Msk                                  (0x1UL << USART_CR3_IRCW_Pos)
#define USART_CR3_IRCW                                      USART_CR3_IRCW_Msk
#define USART_CR3_IRMOD_Pos                                 (15U)
#define USART_CR3_IRMOD_Msk                                 (0x1UL << USART_CR3_IRMOD_Pos)
#define USART_CR3_IRMOD                                     USART_CR3_IRMOD_Msk

// USART_BRR
#define USART_BRR_DIVF_Pos                                  (0U)
#define USART_BRR_DIVF_Msk                                  (0x7FUL << USART_BRR_DIVF_Pos)
#define USART_BRR_DIVF                                      USART_BRR_DIVF_Msk
#define USART_BRR_FBME_Pos                                  (7U)
#define USART_BRR_FBME_Msk                                  (0x1UL << USART_BRR_FBME_Pos)
#define USART_BRR_FBME                                      USART_BRR_FBME_Msk
#define USART_BRR_DIVI_Pos                                  (8U)
#define USART_BRR_DIVI_Msk                                  (0xFFUL << USART_BRR_DIVI_Pos)
#define USART_BRR_DIVI                                      USART_BRR_DIVI_Msk
#define USART_BRR_PSC_Pos                                   (16U)
#define USART_BRR_PSC_Msk                                   (0x3UL << USART_BRR_PSC_Pos)
#define USART_BRR_PSC                                       USART_BRR_PSC_Msk

// USART_TOR
#define USART_TOR_TOR_Pos                                   (0U)
#define USART_TOR_TOR_Msk                                   (0xFFFFFUL << USART_TOR_TOR_Pos)
#define USART_TOR_TOR                                       USART_TOR_TOR_Msk

// USART_SR
#define USART_SR_TXE_Pos                                    (0U)
#define USART_SR_TXE_Msk                                    (0x1UL << USART_SR_TXE_Pos)
#define USART_SR_TXE                                        USART_SR_TXE_Msk
#define USART_SR_TC_Pos                                     (1U)
#define USART_SR_TC_Msk                                     (0x1UL << USART_SR_TC_Pos)
#define USART_SR_TC                                         USART_SR_TC_Msk
#define USART_SR_RC_Pos                                     (2U)
#define USART_SR_RC_Msk                                     (0x1UL << USART_SR_RC_Pos)
#define USART_SR_RC                                         USART_SR_RC_Msk
#define USART_SR_PE_Pos                                     (3U)
#define USART_SR_PE_Msk                                     (0x1UL << USART_SR_PE_Pos)
#define USART_SR_PE                                         USART_SR_PE_Msk
#define USART_SR_FE_Pos                                     (4U)
#define USART_SR_FE_Msk                                     (0x1UL << USART_SR_FE_Pos)
#define USART_SR_FE                                         USART_SR_FE_Msk
#define USART_SR_OR_Pos                                     (5U)
#define USART_SR_OR_Msk                                     (0x1UL << USART_SR_OR_Pos)
#define USART_SR_OR                                         USART_SR_OR_Msk
#define USART_SR_TO_Pos                                     (6U)
#define USART_SR_TO_Msk                                     (0x1UL << USART_SR_TO_Pos)
#define USART_SR_TO                                         USART_SR_TO_Msk
#define USART_SR_MPB_Pos                                    (8U)
#define USART_SR_MPB_Msk                                    (0x1UL << USART_SR_MPB_Pos)
#define USART_SR_MPB                                        USART_SR_MPB_Msk
#define USART_SR_AM_Pos                                     (9U)
#define USART_SR_AM_Msk                                     (0x1UL << USART_SR_AM_Pos)
#define USART_SR_AM                                         USART_SR_AM_Msk
#define USART_SR_CTSV_Pos                                   (10U)
#define USART_SR_CTSV_Msk                                   (0x1UL << USART_SR_CTSV_Pos)
#define USART_SR_CTSV                                       USART_SR_CTSV_Msk
#define USART_SR_CTS_Pos                                    (11U)
#define USART_SR_CTS_Msk                                    (0x1UL << USART_SR_CTS_Pos)
#define USART_SR_CTS                                        USART_SR_CTS_Msk
#define USART_SR_ABR_Pos                                    (12U)
#define USART_SR_ABR_Msk                                    (0x1UL << USART_SR_ABR_Pos)
#define USART_SR_ABR                                        USART_SR_ABR_Msk
#define USART_SR_LBD_Pos                                    (13U)
#define USART_SR_LBD_Msk                                    (0x1UL << USART_SR_LBD_Pos)
#define USART_SR_LBD                                        USART_SR_LBD_Msk
#define USART_SR_DWK_Pos                                    (14U)
#define USART_SR_DWK_Msk                                    (0x1UL << USART_SR_DWK_Pos)
#define USART_SR_DWK                                        USART_SR_DWK_Msk

// USART_TDR
#define USART_TDR_TDR_Pos                                   (0U)
#define USART_TDR_TDR_Msk                                   (0x1FFUL << USART_TDR_TDR_Pos)
#define USART_TDR_TDR                                       USART_TDR_TDR_Msk
#define USART_TDR_MPID_Pos                                  (9U)
#define USART_TDR_MPID_Msk                                  (0x1UL << USART_TDR_MPID_Pos)
#define USART_TDR_MPID                                      USART_TDR_MPID_Msk

// USART_IER
#define USART_IER_TXE_Pos                                   (0U)
#define USART_IER_TXE_Msk                                   (0x1UL << USART_IER_TXE_Pos)
#define USART_IER_TXE                                       USART_IER_TXE_Msk
#define USART_IER_TC_Pos                                    (1U)
#define USART_IER_TC_Msk                                    (0x1UL << USART_IER_TC_Pos)
#define USART_IER_TC                                        USART_IER_TC_Msk
#define USART_IER_RC_Pos                                    (2U)
#define USART_IER_RC_Msk                                    (0x1UL << USART_IER_RC_Pos)
#define USART_IER_RC                                        USART_IER_RC_Msk
#define USART_IER_PE_Pos                                    (3U)
#define USART_IER_PE_Msk                                    (0x1UL << USART_IER_PE_Pos)
#define USART_IER_PE                                        USART_IER_PE_Msk
#define USART_IER_FE_Pos                                    (4U)
#define USART_IER_FE_Msk                                    (0x1UL << USART_IER_FE_Pos)
#define USART_IER_FE                                        USART_IER_FE_Msk
#define USART_IER_OR_Pos                                    (5U)
#define USART_IER_OR_Msk                                    (0x1UL << USART_IER_OR_Pos)
#define USART_IER_OR                                        USART_IER_OR_Msk
#define USART_IER_TO_Pos                                    (6U)
#define USART_IER_TO_Msk                                    (0x1UL << USART_IER_TO_Pos)
#define USART_IER_TO                                        USART_IER_TO_Msk
#define USART_IER_AM_Pos                                    (9U)
#define USART_IER_AM_Msk                                    (0x1UL << USART_IER_AM_Pos)
#define USART_IER_AM                                        USART_IER_AM_Msk
#define USART_IER_CTS_Pos                                   (11U)
#define USART_IER_CTS_Msk                                   (0x1UL << USART_IER_CTS_Pos)
#define USART_IER_CTS                                       USART_IER_CTS_Msk
#define USART_IER_ABR_Pos                                   (12U)
#define USART_IER_ABR_Msk                                   (0x1UL << USART_IER_ABR_Pos)
#define USART_IER_ABR                                       USART_IER_ABR_Msk
#define USART_IER_LBD_Pos                                   (13U)
#define USART_IER_LBD_Msk                                   (0x1UL << USART_IER_LBD_Pos)
#define USART_IER_LBD                                       USART_IER_LBD_Msk
#define USART_IER_DWK_Pos                                   (14U)
#define USART_IER_DWK_Msk                                   (0x1UL << USART_IER_DWK_Pos)
#define USART_IER_DWK                                       USART_IER_DWK_Msk

// USART_ICR
#define USART_ICR_TC_Pos                                    (1U)
#define USART_ICR_TC_Msk                                    (0x1UL << USART_ICR_TC_Pos)
#define USART_ICR_TC                                        USART_ICR_TC_Msk
#define USART_ICR_RC_Pos                                    (2U)
#define USART_ICR_RC_Msk                                    (0x1UL << USART_ICR_RC_Pos)
#define USART_ICR_RC                                        USART_ICR_RC_Msk
#define USART_ICR_PE_Pos                                    (3U)
#define USART_ICR_PE_Msk                                    (0x1UL << USART_ICR_PE_Pos)
#define USART_ICR_PE                                        USART_ICR_PE_Msk
#define USART_ICR_FE_Pos                                    (4U)
#define USART_ICR_FE_Msk                                    (0x1UL << USART_ICR_FE_Pos)
#define USART_ICR_FE                                        USART_ICR_FE_Msk
#define USART_ICR_OR_Pos                                    (5U)
#define USART_ICR_OR_Msk                                    (0x1UL << USART_ICR_OR_Pos)
#define USART_ICR_OR                                        USART_ICR_OR_Msk
#define USART_ICR_TO_Pos                                    (6U)
#define USART_ICR_TO_Msk                                    (0x1UL << USART_ICR_TO_Pos)
#define USART_ICR_TO                                        USART_ICR_TO_Msk
#define USART_ICR_AM_Pos                                    (9U)
#define USART_ICR_AM_Msk                                    (0x1UL << USART_ICR_AM_Pos)
#define USART_ICR_AM                                        USART_ICR_AM_Msk
#define USART_ICR_CTS_Pos                                   (11U)
#define USART_ICR_CTS_Msk                                   (0x1UL << USART_ICR_CTS_Pos)
#define USART_ICR_CTS                                       USART_ICR_CTS_Msk
#define USART_ICR_ABR_Pos                                   (12U)
#define USART_ICR_ABR_Msk                                   (0x1UL << USART_ICR_ABR_Pos)
#define USART_ICR_ABR                                       USART_ICR_ABR_Msk
#define USART_ICR_LBD_Pos                                   (13U)
#define USART_ICR_LBD_Msk                                   (0x1UL << USART_ICR_LBD_Pos)
#define USART_ICR_LBD                                       USART_ICR_LBD_Msk
#define USART_ICR_DWK_Pos                                   (14U)
#define USART_ICR_DWK_Msk                                   (0x1UL << USART_ICR_DWK_Pos)
#define USART_ICR_DWK                                       USART_ICR_DWK_Msk

// USART_RDR
#define USART_RDR_RDR_Pos                                   (0U)
#define USART_RDR_RDR_Msk                                   (0x1FFUL << USART_RDR_RDR_Pos)
#define USART_RDR_RDR                                       USART_RDR_RDR_Msk

// USART_ADDR
#define USART_ADDR_ADDR_Pos                                 (0U)
#define USART_ADDR_ADDR_Msk                                 (0xFFUL << USART_ADDR_ADDR_Pos)
#define USART_ADDR_ADDR                                     USART_ADDR_ADDR_Msk

// USART_ADDMR
#define USART_ADDMR_ADDM_Pos                                (0U)
#define USART_ADDMR_ADDM_Msk                                (0xFFUL << USART_ADDMR_ADDM_Pos)
#define USART_ADDMR_ADDM                                    USART_ADDMR_ADDM_Msk

// USART_BDR
#define USART_BDR_BDR_Pos                                   (0U)
#define USART_BDR_BDR_Msk                                   (0xFFFUL << USART_BDR_BDR_Pos)
#define USART_BDR_BDR                                       USART_BDR_BDR_Msk

// USART_IR
#define USART_IR_DCNTL_Pos                                  (0U)
#define USART_IR_DCNTL_Msk                                  (0x7FFUL << USART_IR_DCNTL_Pos)
#define USART_IR_DCNTL                                      USART_IR_DCNTL_Msk
#define USART_IR_DCNTH_Pos                                  (16U)
#define USART_IR_DCNTH_Msk                                  (0x7FFUL << USART_IR_DCNTH_Pos)
#define USART_IR_DCNTH                                      USART_IR_DCNTH_Msk



//********************    Bits Define For Peripheral VC    ********************//
// VC_CR0
#define VC_CR0_DIV_Pos                                      (0U)
#define VC_CR0_DIV_Msk                                      (0x3FUL << VC_CR0_DIV_Pos)
#define VC_CR0_DIV                                          VC_CR0_DIV_Msk
#define VC_CR0_DIVEN_Pos                                    (6U)
#define VC_CR0_DIVEN_Msk                                    (0x1UL << VC_CR0_DIVEN_Pos)
#define VC_CR0_DIVEN                                        VC_CR0_DIVEN_Msk
#define VC_CR0_REF_Pos                                      (7U)
#define VC_CR0_REF_Msk                                      (0x1UL << VC_CR0_REF_Pos)
#define VC_CR0_REF                                          VC_CR0_REF_Msk
#define VC_CR0_BIAS_Pos                                     (8U)
#define VC_CR0_BIAS_Msk                                     (0x3UL << VC_CR0_BIAS_Pos)
#define VC_CR0_BIAS                                         VC_CR0_BIAS_Msk
#define VC_CR0_HYS_Pos                                      (10U)
#define VC_CR0_HYS_Msk                                      (0x3UL << VC_CR0_HYS_Pos)
#define VC_CR0_HYS                                          VC_CR0_HYS_Msk

// VC_CR1
#define VC_CR1_PSEL_Pos                                     (0U)
#define VC_CR1_PSEL_Msk                                     (0xFUL << VC_CR1_PSEL_Pos)
#define VC_CR1_PSEL                                         VC_CR1_PSEL_Msk
#define VC_CR1_NSEL_Pos                                     (4U)
#define VC_CR1_NSEL_Msk                                     (0xFUL << VC_CR1_NSEL_Pos)
#define VC_CR1_NSEL                                         VC_CR1_NSEL_Msk
#define VC_CR1_FLTEN_Pos                                    (8U)
#define VC_CR1_FLTEN_Msk                                    (0x1UL << VC_CR1_FLTEN_Pos)
#define VC_CR1_FLTEN                                        VC_CR1_FLTEN_Msk
#define VC_CR1_FLTTIME_Pos                                  (9U)
#define VC_CR1_FLTTIME_Msk                                  (0x7UL << VC_CR1_FLTTIME_Pos)
#define VC_CR1_FLTTIME                                      VC_CR1_FLTTIME_Msk
#define VC_CR1_FALLING_Pos                                  (12U)
#define VC_CR1_FALLING_Msk                                  (0x1UL << VC_CR1_FALLING_Pos)
#define VC_CR1_FALLING                                      VC_CR1_FALLING_Msk
#define VC_CR1_RISING_Pos                                   (13U)
#define VC_CR1_RISING_Msk                                   (0x1UL << VC_CR1_RISING_Pos)
#define VC_CR1_RISING                                       VC_CR1_RISING_Msk
#define VC_CR1_LEVEL_Pos                                    (14U)
#define VC_CR1_LEVEL_Msk                                    (0x1UL << VC_CR1_LEVEL_Pos)
#define VC_CR1_LEVEL                                        VC_CR1_LEVEL_Msk
#define VC_CR1_IE_Pos                                       (15U)
#define VC_CR1_IE_Msk                                       (0x1UL << VC_CR1_IE_Pos)
#define VC_CR1_IE                                           VC_CR1_IE_Msk
#define VC_CR1_EN_Pos                                       (16U)
#define VC_CR1_EN_Msk                                       (0x1UL << VC_CR1_EN_Pos)
#define VC_CR1_EN                                           VC_CR1_EN_Msk
#define VC_CR1_FLTCLK_Pos                                   (17U)
#define VC_CR1_FLTCLK_Msk                                   (0x1UL << VC_CR1_FLTCLK_Pos)
#define VC_CR1_FLTCLK                                       VC_CR1_FLTCLK_Msk

// VC_CR2
#define VC_CR2_POL_Pos                                      (0U)
#define VC_CR2_POL_Msk                                      (0x1UL << VC_CR2_POL_Pos)
#define VC_CR2_POL                                          VC_CR2_POL_Msk
#define VC_CR2_ATIM0CLR_Pos                                 (1U)
#define VC_CR2_ATIM0CLR_Msk                                 (0x1UL << VC_CR2_ATIM0CLR_Pos)
#define VC_CR2_ATIM0CLR                                     VC_CR2_ATIM0CLR_Msk
#define VC_CR2_ATIM1CLR_Pos                                 (2U)
#define VC_CR2_ATIM1CLR_Msk                                 (0x1UL << VC_CR2_ATIM1CLR_Pos)
#define VC_CR2_ATIM1CLR                                     VC_CR2_ATIM1CLR_Msk
#define VC_CR2_ATIM2CLR_Pos                                 (3U)
#define VC_CR2_ATIM2CLR_Msk                                 (0x1UL << VC_CR2_ATIM2CLR_Pos)
#define VC_CR2_ATIM2CLR                                     VC_CR2_ATIM2CLR_Msk
#define VC_CR2_ATIM3CLR_Pos                                 (4U)
#define VC_CR2_ATIM3CLR_Msk                                 (0x1UL << VC_CR2_ATIM3CLR_Pos)
#define VC_CR2_ATIM3CLR                                     VC_CR2_ATIM3CLR_Msk
#define VC_CR2_ATIMBK_Pos                                   (5U)
#define VC_CR2_ATIMBK_Msk                                   (0x1UL << VC_CR2_ATIMBK_Pos)
#define VC_CR2_ATIMBK                                       VC_CR2_ATIMBK_Msk
#define VC_CR2_WINDOW_Pos                                   (6U)
#define VC_CR2_WINDOW_Msk                                   (0x1UL << VC_CR2_WINDOW_Pos)
#define VC_CR2_WINDOW                                       VC_CR2_WINDOW_Msk

// VC_SR
#define VC_SR_INTF_Pos                                      (0U)
#define VC_SR_INTF_Msk                                      (0x1UL << VC_SR_INTF_Pos)
#define VC_SR_INTF                                          VC_SR_INTF_Msk
#define VC_SR_FLTV_Pos                                      (1U)
#define VC_SR_FLTV_Msk                                      (0x1UL << VC_SR_FLTV_Pos)
#define VC_SR_FLTV                                          VC_SR_FLTV_Msk



//********************    Bits Define For Peripheral WWDT    ********************//
// WWDT_CR0
#define WWDT_CR0_WCNT_Pos                                   (0U)
#define WWDT_CR0_WCNT_Msk                                   (0x7FUL << WWDT_CR0_WCNT_Pos)
#define WWDT_CR0_WCNT                                       WWDT_CR0_WCNT_Msk
#define WWDT_CR0_EN_Pos                                     (7U)
#define WWDT_CR0_EN_Msk                                     (0x1UL << WWDT_CR0_EN_Pos)
#define WWDT_CR0_EN                                         WWDT_CR0_EN_Msk

// WWDT_CR1
#define WWDT_CR1_WINR_Pos                                   (0U)
#define WWDT_CR1_WINR_Msk                                   (0x7FUL << WWDT_CR1_WINR_Pos)
#define WWDT_CR1_WINR                                       WWDT_CR1_WINR_Msk
#define WWDT_CR1_IE_Pos                                     (9U)
#define WWDT_CR1_IE_Msk                                     (0x1UL << WWDT_CR1_IE_Pos)
#define WWDT_CR1_IE                                         WWDT_CR1_IE_Msk
#define WWDT_CR1_PRS_Pos                                    (11U)
#define WWDT_CR1_PRS_Msk                                    (0x7UL << WWDT_CR1_PRS_Pos)
#define WWDT_CR1_PRS                                        WWDT_CR1_PRS_Msk

// WWDT_SR
#define WWDT_SR_POV_Pos                                     (0U)
#define WWDT_SR_POV_Msk                                     (0x1UL << WWDT_SR_POV_Pos)
#define WWDT_SR_POV                                         WWDT_SR_POV_Msk



/* ========================================================================== */
/*  C 链接区: 以下全部为 C 符号, 供 C / C++ 共用                                           */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*  驱动核心: 公共宏 / 类型 / 系统控制 (ddl.h + sysctrl.h)                                 */
/* ========================================================================== */


/* ========================================================================== */
/*  驱动模块 (driver/inc 其余 28 个)                                                 */
/* ========================================================================== */




/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/


/* C binding of definitions if building with C++ compiler */

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




/*****************************************************************************
 * Include files
 *****************************************************************************/



/**
 * @addtogroup HC32A052_DDL 驱动库
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



/*****************************************************************************
 * Include files
 *****************************************************************************/



/**
 * @addtogroup HC32A052_DDL 驱动库
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



/******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_BGR BGR模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup BGR_Global_Functions BGR全局函数定义
 * @{
 */

/**
 * @brief 内部温度传感器使能
 */
void Bgr_TempSensorEnable(void);

/**
 * @brief 内部温度传感器关闭
 */
void Bgr_TempSensorDisable(void);

/**
 * @brief BGR使能
 */
void Bgr_BgrEnable(void);

/**
 * @brief BGR关闭
 */
void Bgr_BgrDisable(void);

/**
 * @}
 */



/**
 * @}
 */

/**
 * @}
 */




/*****************************************************************************
 * Include files
 *****************************************************************************/



/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_BTIM BTIM模块驱动库
 * @{
 */



/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup BTIM_Global_Types BTIM全局类型定义
 * @{
 */


/**
 * @brief BTIMx 初始化配置的结构体
 * @note
 */
typedef struct stc_btim_init
{
    uint32_t       u32TaskMode;        /*!< 定时器计数模式选择：连续计数模式或单次计数模式 */
    uint32_t       u32WorkMode;        /*!< 工作模式：内部时钟计数、外部输入计数、触发模式、门控模式 */
    uint32_t       u32Prescaler;       /*!< 计数器输入信号分频 */
    uint32_t       u32ToggleEn;        /*!< Toggle_N和Toggle_P输出使能 */
    uint32_t       u32TriggerSource;   /*!< 触发源选择，外部管脚ETR或者上一级BTIM溢出 */
    uint32_t       u32ExInputPolarity; /*!< 外部输入极性选择 */
    uint32_t       u32AutoReloadVal;   /*!< 配置重载寄存器的值 */
}stc_btim_init_t;


/**
  * @}
  */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup BTIM_Global_Macros BTIM全局宏定义
 * @{
 */

/** @defgroup Btim_Count_Task_Mode: Single or Continuous (u32TaskMode)(OST)
  * @{
  */
#define  BTIM_TASK_MODE_CONTINUOUS_COUNTER     (0x00000000UL)  /*!< 连续计数模式 */
#define  BTIM_TASK_MODE_ONESHOT_COUNTER        (BTIM_CR_OST)   /*!< 单次模式 */
/**
  * @}
  */

/** @defgroup Btim_Work_Mode: u32WorkMode (MD)
  * @{
  */
#define  BTIM_WORK_MODE_PCLK           (0x00000000UL)          /*!< 定时器模式 */
#define  BTIM_WORK_MODE_EXTERNAL       (0x1 << BTIM_CR_MD_Pos) /*!< 计数器模式 */
#define  BTIM_WORK_MODE_TRIGGER        (0x2 << BTIM_CR_MD_Pos) /*!< 触发启动模式 */
#define  BTIM_WORK_MODE_GATE           (BTIM_CR_MD)            /*!< 门控模式 */
/**
  * @}
  */

/** @defgroup Btim_Clock_devide: u32Prescaler (PRS)
  * @{
  */
#define  BTIM_COUNTER_CLK_DIV1        (0x00000000UL)            /*!<BTIM  Div 1*/
#define  BTIM_COUNTER_CLK_DIV2        (0x1 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 2*/
#define  BTIM_COUNTER_CLK_DIV4        (0x2 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 4*/
#define  BTIM_COUNTER_CLK_DIV8        (0x3 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 8*/
#define  BTIM_COUNTER_CLK_DIV16       (0x4 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 16*/
#define  BTIM_COUNTER_CLK_DIV32       (0x5 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 32*/
#define  BTIM_COUNTER_CLK_DIV64       (0x6 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 64*/
#define  BTIM_COUNTER_CLK_DIV128      (0x7 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 128*/
#define  BTIM_COUNTER_CLK_DIV256      (0x8 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 256*/
#define  BTIM_COUNTER_CLK_DIV512      (0x9 << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 512*/
#define  BTIM_COUNTER_CLK_DIV1024     (0xA << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 1024*/
#define  BTIM_COUNTER_CLK_DIV2048     (0xB << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 2048*/
#define  BTIM_COUNTER_CLK_DIV4096     (0xC << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 4096*/
#define  BTIM_COUNTER_CLK_DIV8192     (0xD << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 8192*/
#define  BTIM_COUNTER_CLK_DIV16384    (0xE << BTIM_CR_PRS_Pos)  /*!<BTIM  Div 16384*/
#define  BTIM_COUNTER_CLK_DIV32768    (BTIM_CR_PRS)             /*!<BTIM  Div 32768*/
/**
  * @}
  */

/** @defgroup Btim_Toggle_ourput_control: u32ToggleEn (TOGEN)
  * @{
  */

#define  BTIM_TOGGLE_DISABLE        (0x00000000UL)    /*!< TOG禁止，输出电平为0 */
#define  BTIM_TOGGLE_ENABLE         (BTIM_CR_TOGEN)   /*!< TOG输出使能，电平反相 */
/**
  * @}
  */

/** @defgroup Btim_Trigger_Source_Selection: u32TriggerSource (TRS)
  * @{
  */
#define  BTIM_TRIGGER_SOURCE_ETR           (0x00000000UL)             /*!< 外部管脚TER作为计数器触发源，或门控 */
#define  BTIM_TRIGGER_SOURCE_ITR           (0x1 << BTIM_CR_TRS_Pos)   /*!< 上一级BTIM溢出信号,门控模式下不建议选此源作为门控信号 */
/**
  * @}
  */

/** @defgroup Btim_ETR_Input_Polarity: u32ExInputPolarity (ETP)
  * @{
  */
#define  BTIM_ETR_POLARITY_NORMAL            (0x00000000UL)  /*!< 外部输入ETR不反向(触发模式上沿触发,门控模式低电平停止计数) */
#define  BTIM_ETR_POLARITY_INVERTED          (BTIM_CR_ETP)   /*!< 外部输入ETR反向(触发模式下沿触发,门控模式高电平停止计数) */
/**
  * @}
  */

/** @defgroup Btim_Interrupt_Enable_Disable (IER)
  * @{
  */
#define BTIM_IT_UI        (BTIM_IER_UI)     /*!< 溢出中断使能控制 */
#define BTIM_IT_TI        (BTIM_IER_TI)     /*!< 触发中断使能控制 */
/**
  * @}
  */


/** @defgroup Btim_Interrupt_Flag (IFR)
  * @{
  */
#define BTIM_IT_FLAG_UI        (BTIM_IFR_UI)     /*!< 溢出中断标志 */
#define BTIM_IT_FLAG_TI        (BTIM_IFR_TI)     /*!< 触发中断标志 */
/**
  * @}
  */


/** @defgroup Btim_Interrupt_Clear_Types (ICR)
  * @{
  */
#define BTIM_IT_CLR_UI        (BTIM_ICR_UI)     /*!< 清除溢出中断标志 */
#define BTIM_IT_CLR_TI        (BTIM_ICR_TI)     /*!< 清除触发中断标志 */
/**
  * @}
  */

/** @defgroup Btim_All_Interrupt_Flags (BTIM0~BTIM5 AIFR)
  * @{
  */
#define  BTIM03_AIT_FLAG_UI     (BTIM_AIFR_UI03)       /*!< BTIM0或BTIM3溢出中断标志 */
#define  BTIM03_AIT_FLAG_TI     (BTIM_AIFR_TI03)       /*!< BTIM0或BTIM3触发中断标志 */
#define  BTIM14_AIT_FLAG_UI     (BTIM_AIFR_UI14)       /*!< BTIM1或BTIM4溢出中断标志 */
#define  BTIM14_AIT_FLAG_TI     (BTIM_AIFR_TI14)       /*!< BTIM1或BTIM4触发中断标志 */
#define  BTIM25_AIT_FLAG_UI     (BTIM_AIFR_UI25)       /*!< BTIM2或BTIM5溢出中断标志 */
#define  BTIM25_AIT_FLAG_TI     (BTIM_AIFR_TI25)       /*!< BTIM2或BTIM5触发中断标志 */
/**
  * @}
  */

/** @defgroup Btim_All_Interrupt_Clear_Reg (BTIM0~BTIM5 AICR)
  * @{
  */
#define  BTIM03_AIT_CLR_UI     (BTIM_AICR_UI03)        /*!< 清除BTIM0和BTIM3溢出中断标志 */
#define  BTIM03_AIT_CLR_TI     (BTIM_AICR_TI03)        /*!< 清除BTIM0和BTIM3触发中断标志 */
#define  BTIM14_AIT_CLR_UI     (BTIM_AICR_UI14)        /*!< 清除BTIM1和BTIM4溢出中断标志 */
#define  BTIM14_AIT_CLR_TI     (BTIM_AICR_TI14)        /*!< 清除BTIM1和BTIM4触发中断标志 */
#define  BTIM25_AIT_CLR_UI     (BTIM_AICR_UI25)        /*!< 清除BTIM2和BTIM5溢出中断标志 */
#define  BTIM25_AIT_CLR_TI     (BTIM_AICR_TI25)        /*!< 清除BTIM2和BTIM5触发中断标志 */
/**
  * @}
  */

/**
  * @}
  */


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup BTIM_Global_Functions BTIM全局函数定义
 * @{
 */
en_result_t Btim_Init(BTIM_TypeDef* BTIMx, stc_btim_init_t* pstcInitCfg);
void Btim_SetCounter(BTIM_TypeDef* BTIMx, uint16_t u16CntValue);
uint32_t Btim_GetCounter(BTIM_TypeDef* BTIMx);
void Btim_SetAutoReload(BTIM_TypeDef* BTIMx, uint16_t u16AutoReload);
uint32_t Btim_GetAutoReload(BTIM_TypeDef* BTIMx);
void Btim_Enable(BTIM_TypeDef *BTIMx);
void Btim_Disable(BTIM_TypeDef *BTIMx);
boolean_t Btim_IsEnable(BTIM_TypeDef *BTIMx);
void Btim_SetWorkMode(BTIM_TypeDef* BTIMx, uint32_t u32WorkMode);
uint32_t Btim_GetWorkMode(BTIM_TypeDef* BTIMx);
void Btim_EnableToggle(BTIM_TypeDef *BTIMx);
void Btim_DisableToggle(BTIM_TypeDef *BTIMx);
boolean_t Btim_IsEnableToggle(BTIM_TypeDef *BTIMx);
void Btim_SetCounterClkDiv(BTIM_TypeDef* BTIMx, uint32_t u32CounterClkDiv);
uint32_t Btim_GetCounterClkDiv(BTIM_TypeDef* BTIMx);
void Btim_SetOneShotMode(BTIM_TypeDef* BTIMx, uint32_t u32Mode);
uint32_t Btim_GetOneShotMode(BTIM_TypeDef* BTIMx);
void Btim_SetTriggerSource(BTIM_TypeDef* BTIMx, uint32_t u32TriggerSource);
uint32_t Btim_GetTriggerSource(BTIM_TypeDef* BTIMx);
void Btim_SetExInputPolarity(BTIM_TypeDef* BTIMx, uint32_t u32ExInputPolarity);
uint32_t Btim_GetExInputPolarity(BTIM_TypeDef* BTIMx);
void Btim_EnableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag);
void Btim_DisableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag);
boolean_t Btim_IsEnableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag);
boolean_t Btim_IsActiveFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntFlag);
void Btim_ClearFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag);
boolean_t Btim_AIFR_IsActiveFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntFlag);
void Btim_AICR_ClearFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag);

/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_CAN CAN模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CAN_Global_Types CAN全局类型定义
 * @{
 */

/**
 * @brief CAN错误类型定义
 */
typedef enum
{
    NO_ERROR     = 0U, /*!< 无错误 */
    BIT_ERROR    = 1U, /*!< 位错误 */
    FORM_ERROR   = 2U, /*!< 形式错误 */
    STUFF_ERROR  = 3U, /*!< 填充错误 */
    ACK_ERROR    = 4U, /*!< 应答错误 */
    CRC_ERROR    = 5U, /*!< CRC错误 */
    UNKOWN_ERROR = 6U, /*!< 未知错误 */
} en_can_error_t;

/**
 * @brief CAN传输缓冲器选择. (TCMD)
 */
typedef enum
{
    CanPTBSel = 0U, /*!< 主缓冲器选择 */
    CanSTBSel = 1U, /*!< 副缓冲器选择 */
} en_can_buffer_sel_t;

/**
 * @brief CAN 警告限定.(AFWL)
 */
typedef struct
{
    uint8_t CanWarningLimitVal;      /*!< 接收缓冲器将满限定 */
    uint8_t CanErrorWarningLimitVal; /*!< 错误警告限定 */
} stc_can_warning_limit_t;

/**
 * @brief CAN 筛选器类型.(ACF)
 */
typedef enum
{
    CanStdFrames = 0x02u, /*!< 仅接受标准帧 */
    CanExtFrames = 0x03u, /*!< 仅接受扩展帧 */
    CanAllFrames = 0x00u, /*!< 接收标准帧和扩展帧 */
} en_can_acf_format_en_t;

/**
 * @brief CAN 筛选器组使能. (ACFEN)
 */
typedef enum
{
    CanFilterSel1 = 0u, /*!< 筛选器组1使能 */
    CanFilterSel2 = 1u, /*!< 筛选器组2使能 */
    CanFilterSel3 = 2u, /*!< 筛选器组3使能 */
    CanFilterSel4 = 3u, /*!< 筛选器组4使能 */
    CanFilterSel5 = 4u, /*!< 筛选器组5使能 */
    CanFilterSel6 = 5u, /*!< 筛选器组6使能 */
    CanFilterSel7 = 6u, /*!< 筛选器组7使能 */
    CanFilterSel8 = 7u, /*!< 筛选器组8使能 */
} en_can_filter_sel_t;

/**
 * @brief CAN 中断使能.(IE)
 */
typedef enum
{
    /* Can Rx or Tx Irq En */
    CanRxIrqEn              = 0x00000080, /*!< 接收中断使能 */
    CanRxOverIrqEn          = 0x00000040, /*!< 接收上溢中断使能 */
    CanRxBufFullIrqEn       = 0x00000020, /*!< 接收缓冲器满中断使能 */
    CanRxBufAlmostFullIrqEn = 0x00000010, /*!< 接收缓冲器将满中断使能 */
    CanTxPrimaryIrqEn       = 0x00000008, /*!< PTB发送中断使能 */
    CanTxSecondaryIrqEn     = 0x00000004, /*!< STB发送中断使能 */
    CanErrorIrqEn           = 0x00000002, /*!< 错误中断使能 */

    /* Can Error Irq En */
    CanErrorPassiveIrqEn = 0x00200000, /*!< 错误被动中断使能 */
    CanArbiLostIrqEn     = 0x00080000, /*!< 仲裁失败中断使能 */
    CanBusErrorIrqEn     = 0x00020000, /*!< 总线错误中断使能 */

} en_can_irq_type_t;

/**
 * @brief CAN 中断标志.(IF)
 */
typedef enum
{
    CanTxBufFullIrqFlg       = 0x00000001, /*!< 发送缓冲器满标志 */
    CanRxIrqFlg              = 0x00008000, /*!< 接收中断标志 */
    CanRxOverIrqFlg          = 0x00004000, /*!< 接收上溢中断标志 */
    CanRxBufFullIrqFlg       = 0x00002000, /*!< 接收缓冲器满中断标志 */
    CanRxBufAlmostFullIrqFlg = 0x00001000, /*!< 接收缓冲器将满中断标志 */
    CanTxPrimaryIrqFlg       = 0x00000800, /*!< PTB发送中断标志 */
    CanTxSecondaryIrqFlg     = 0x00000400, /*!< STB发送中断标志 */
    CanErrorIrqFlg           = 0x00000200, /*!< 错误中断标志 */
    CanAbortIrqFlg           = 0x00000100, /*!< 取消发送中断标志 */

    CanErrorWarningIrqFlg     = 0x00800000, /*!< 达到错误限定警告标志 */
    CanErrorPassivenodeIrqFlg = 0x00400000, /*!< 错误被动节点标志 */
    CanErrorPassiveIrqFlg     = 0x00100000, /*!< 错误被动中断标志 */
    CanArbiLostIrqFlg         = 0x00040000, /*!< 仲裁失败中断标志 */
    CanBusErrorIrqFlg         = 0x00010000, /*!< 总线错误中断标志 */
} en_can_irq_flag_type_t;

/**
 * @brief CAN 模式.(CFG_STAT)
 */
typedef enum
{
    CanExternalLoopBackMode  = 0x40u, /*!< 外部回环模式 */
    CanInternalLoopBackMode  = 0x20u, /*!< 内部回环模式 */
    CanTxSignalPrimaryMode   = 0x10u, /*!< PTB单次传输模式 */
    CanTxSignalSecondaryMode = 0x08u, /*!< STB单次传输模式 */
    CanListenOnlyMode        = 0xFFu, /*!< 静默模式 */
} en_can_mode_t;

/**
 * @brief CAN 状态.(STAT)
 */
typedef enum
{
    CanRxActive = 0x04, /*!< 接收中状态 */
    CanTxActive = 0x02, /*!< 发送中状态 */
    CanBusoff   = 0x01, /*!< 总线关闭状态 */
} en_can_status_t;

/**
 * @brief CAN 发送命令.(TCMD)
 */
typedef enum
{
    CanPTBTxCmd      = 0x10, /*!< PTB发送命令 */
    CanPTBTxAbortCmd = 0x08, /*!< PTB发送取消命令 */
    CanSTBTxOneCmd   = 0x04, /*!< STB单帧发送命令 */
    CanSTBTxAllCmd   = 0x02, /*!< STB所有帧命令 */
    CanSTBTxAbortCmd = 0x01, /*!< STB发送取消命令 */
} en_can_tx_cmd_t;

/**
 * @brief CAN 副缓冲器发送模式选择.(TCTRL)
 */
typedef enum
{
    CanSTBFifoMode    = 0, /*!< FIFO模式 */
    CanSTBPrimaryMode = 1, /*!< 优先级模式 */
} en_can_stb_mode_t;

/**
 * @brief CAN 自应答.(RCTRL)
 */
typedef enum
{
    CanSelfAckDisable = 0, /*!< 无自应答 */
    CanSelfAckEnable  = 1, /*!< 使能自应答(LBME=1) */
} en_can_self_ack_en_t;

/**
 * @brief CAN 接收缓冲器上溢模式.(RCTRL)
 */
typedef enum
{
    CanRxBufOverwritten = 0, /*!< 最早接收到的数据被覆盖 */
    CanRxBufNotStored   = 1, /*!< 最新接收到的数据不被存储 */
} en_can_rx_buf_mode_en_t;

/**
 * @brief CAN 接收缓冲器数据存储模式.(RCTRL)
 */
typedef enum
{
    CanRxNormal = 0, /*!< 正常模式 */
    CanRxAll    = 1, /*!< 存储所有(包括错误)数据 */
} en_can_rx_buf_all_t;

/**
 * @brief CAN 接收缓冲器状态.(RSTAT)
 */
typedef enum
{
    CanRxBufEmpty         = 0, /*!< 空 */
    CanRxBufnotAlmostFull = 1, /*!< 非空但小于警告限定值 */
    CanRxBufAlmostFull    = 2, /*!< 大于警告限定值但未满 */
    CanRxBufFull          = 3, /*!< 满(上溢) */
} en_can_rx_buf_status_t;

/**
 * @brief CAN 发送缓冲器状态.(TSSTAT)
 */
typedef enum
{
    CanTxBufEmpty       = 0, /*!< 空 */
    CanTxBufnotHalfFull = 1, /*!< 小于等于半满 */
    CanTxBufHalfFull    = 2, /*!< 大于半满 */
    CanTxBufFull        = 3, /*!< 满 */
} en_can_tx_buf_status_t;

/**
 * @brief CAN 筛选器.
 */
typedef struct
{
    uint32_t               u32CODE;     /*!< CODE */
    uint32_t               u32MASK;     /*!< MASK */
    en_can_filter_sel_t    enFilterSel; /*!< 筛选器组选择 */
    en_can_acf_format_en_t enAcfFormat; /*!< 筛选帧格式. */
} stc_can_filter_t;

/**
 * @brief CAN 时序.
 */
typedef struct
{
    uint8_t SEG_1; /*!< 位段1时间(Tseg_1 = (SEG_1 + 2)*TQ) */
    uint8_t SEG_2; /*!< 位段2时间(Tseg_2 = (SEG_2 + 1)*TQ) */
    uint8_t SJW;   /*!< 再同步补偿宽度时间(Tsjw = (SJW + 1)*TQ) */
    uint8_t PRESC; /*!< CAN时钟预分频(TQ) */
} stc_can_bt_t;

/**
 * @brief CAN 发送数据帧控制.
 */
typedef struct
{
    uint32_t DLC : 4;        /*!< Data length code */
    uint32_t RESERVED0 : 2;  /*!< Ignore */
    uint32_t RTR : 1;        /*!< Remote transmission request */
    uint32_t IDE : 1;        /*!< IDentifier extension */
    uint32_t RESERVED1 : 24; /*!< Ignore */
} stc_can_txcontrol_t;

/**
 * @brief CAN 发送数据帧.
 */
typedef struct
{
    union
    {
        uint32_t TBUF32_0; /*!< Ignore */
        uint32_t StdID;    /*!< Standard ID */
        uint32_t ExtID;    /*!< Extended ID */
    };
    union
    {
        uint32_t            TBUF32_1;  /*!< Ignore */
        stc_can_txcontrol_t Control_f; /*!< CAN Tx Control */
    };
    union
    {
        uint32_t TBUF32_2[2]; /*!< Ignore */
        uint8_t  Data[8];     /*!< CAN data */
    };
    en_can_buffer_sel_t enBufferSel; /*!< CAN Tx buffer select */

} stc_can_txframe_t;

/**
 * @brief CAN 接收数据帧控制.
 */
typedef struct
{
    uint8_t DLC : 4;       /*!< Data length code */
    uint8_t RESERVED0 : 2; /*!< Ignore */
    uint8_t RTR : 1;       /*!< Remote transmission request */
    uint8_t IDE : 1;       /*!< IDentifier extension */
} stc_can_rxcontrol_t;

/**
 * @brief CAN 接收数据帧状态.
 */
typedef struct
{
    uint8_t RESERVED0 : 4; /*!< Ignore */
    uint8_t TX : 1;        /*!< TX is set to 1 if the loop back mode is activated */
    uint8_t KOER : 3;      /*!< Kind of error */
} stc_can_status_t;

/**
 * @brief CAN 数据控制、状态、CYCTIM.
 */
typedef struct
{
    stc_can_rxcontrol_t Control_f; /*!< @ref stc_can_rxcontrol_t */
    stc_can_status_t    Status_f;  /*!< @ref stc_can_status_t */
    uint16_t            CycleTime; /*!< TTCAN cycletime */
} stc_can_cst_t;

/**
 * @brief CAN 接收数据帧.
 */
typedef struct
{
    union
    {
        uint32_t RBUF32_0; /*!< Ignore */
        uint32_t StdID;    /*!< Standard ID */
        uint32_t ExtID;    /*!< Extended ID */
    };
    union
    {
        uint32_t      RBUF32_1; /*!< Ignore */
        stc_can_cst_t Cst;      /*!< @ref stc_can_cst_t */
    };
    union
    {
        uint32_t RBUF32_2[2]; /*!< Ignore */
        uint8_t  Data[8];     /*!< CAN data */
    };

} stc_can_rxframe_t;

/**
 * @brief CAN 初始化配置.
 */
typedef struct
{
    en_can_rx_buf_all_t     enCanRxBufAll;   /*!< @ref en_can_rx_buf_all_t */
    en_can_rx_buf_mode_en_t enCanRxBufMode;  /*!< @ref en_can_rx_buf_mode_en_t */
    en_can_stb_mode_t       enCanSTBMode;    /*!< @ref en_can_stb_mode_t */
    stc_can_bt_t            stcCanBt;        /*!< @ref stc_can_bt_t */
    stc_can_warning_limit_t stcWarningLimit; /*!< @ref stc_can_warning_limit_t */
} stc_can_init_config_t;

/**
 * @brief TTCAN 缓冲器选择
 */
typedef enum
{
    CanTTcanPTBSel  = 0x00u, /*!< PTB */
    CanTTcanSTB1Sel = 0x01u, /*!< STB1 */
    CanTTcanSTB2Sel = 0x02u, /*!< STB2 */
    CanTTcanSTB3Sel = 0x03u, /*!< STB3 */
    CanTTcanSTB4Sel = 0x04u, /*!< STB4 */
} en_can_ttcan_tbslot_t;

/**
 * @brief TTCAN 计数器预分频
 */
typedef enum
{
    CanTTcanTprescDiv1 = 0x00u, /*!< Div1 */
    CanTTcanTprescDiv2 = 0x01u, /*!< Div2 */
    CanTTcanTprescDiv3 = 0x02u, /*!< Div3 */
    CanTTcanTprescDiv4 = 0x03u, /*!< Div4 */
} en_can_ttcan_Tpresc_t;

/**
 * @brief TTCAN 触发类型
 */
typedef enum
{
    CanTTcanImmediate  = 0x00, /*!< 立即触发 */
    CanTTcanTime       = 0x01, /*!< 时间触发 */
    CanTTcanSingle     = 0x02, /*!< 单次发送触发 */
    CanTTcanTransStart = 0x03, /*!< 发送开始触发 */
    CanTTcanTransStop  = 0x04, /*!< 发送停止触发 */
} en_can_ttcan_trigger_type_t;

/**
 * @brief TTCAN 触发中断标志
 */
typedef enum
{
    CanTTcanWdtTriggerIrq   = 0x80, /*!< 触发看门中断标志 */
    CanTTcanErrorTriggerIrq = 0x10, /*!< 触发错误中断标志 */
    CanTTcanTimTriggerIrq   = 0x10, /*!< 时间触发中断标志 */
} en_can_ttcan_irq_type_t;

/**
 * @brief TTCAN Reference message
 */
typedef struct
{
    uint8_t u8IDE; /*!< Reference message IDE:1-Extended 0-Standard */
    union          /*!< Reference message ID */
    {
        uint32_t RefStdID; /*!< Reference standard ID */
        uint32_t RefExtID; /*!< Reference Extended ID */
    };
} stc_can_ttcan_ref_msg_t;

/**
 * @brief TTCAN 触发配置
 */
typedef struct
{
    en_can_ttcan_tbslot_t       enTbSlot;         /*!< Transmit trigger TB slot pointer */
    en_can_ttcan_trigger_type_t enTrigType;       /*!< Trigger type */
    en_can_ttcan_Tpresc_t       enTpresc;         /*!< Timer prescaler */
    uint8_t                     u8Tew;            /*!< Transmit enable window */
    uint16_t                    u16TrigTime;      /*!< TTCAN trigger time */
    uint16_t                    u16WatchTrigTime; /*!< TTCAN watch trigger time register */
} stc_can_ttcan_trigger_config_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
Global function prototypes (definition in C source)
******************************************************************************/
/**
 * @addtogroup CAN_Global_Functions CAN全局函数定义
 * @{
 */
void CAN_Init(stc_can_init_config_t *pstcCanInitCfg);
void CAN_DeInit(void);
void CAN_ModeConfig(en_can_mode_t enMode, en_can_self_ack_en_t enCanSAck, boolean_t enNewState);
void CAN_FilterConfig(stc_can_filter_t *pstcFilter, boolean_t enNewState);
void CAN_SetFrame(stc_can_txframe_t *pstcTxFrame);
void CAN_TransmitCmd(en_can_tx_cmd_t enTxCmd);
en_can_tx_buf_status_t CAN_TxBufStatusGet(void);
void CAN_Receive(stc_can_rxframe_t *pstcRxFrame);
en_can_rx_buf_status_t CAN_RxBufStatusGet(void);
en_can_error_t CAN_ErrorStatusGet(void);
boolean_t CAN_StatusGet(en_can_status_t enCanStatus);
void CAN_IrqCmd(en_can_irq_type_t enCanIrqType, boolean_t enNewState);
boolean_t CAN_IrqFlgGet(en_can_irq_flag_type_t enCanIrqFlgType);
void CAN_IrqFlgClr(en_can_irq_flag_type_t enCanIrqFlgType);
uint8_t CAN_RxErrorCntGet(void);
uint8_t CAN_TxErrorCntGet(void);
uint8_t CAN_ArbitrationLostCap(void);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_CRC CRC模块驱动库
 * @{
 */

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
/**
 * @addtogroup CRC_Global_Functions CRC全局函数定义
 * @{
 */
uint16_t CRC16_Get8(uint8_t pu8Data[], uint32_t u32Len);
uint16_t CRC16_Get16(uint16_t pu16Data[], uint32_t u32Len);
uint16_t CRC16_Get32(uint32_t pu32Data[], uint32_t u32Len);

en_result_t CRC16_Check8(uint8_t pu8Data[], uint32_t u32Len, uint16_t u16CRC);
en_result_t CRC16_Check16(uint16_t pu16Data[], uint32_t u32Len, uint16_t u16CRC);
en_result_t CRC16_Check32(uint32_t pu32Data[], uint32_t u32Len, uint16_t u16CRC);

uint32_t CRC32_Get8(uint8_t pu8Data[], uint32_t u32Len);
uint32_t CRC32_Get16(uint16_t pu16Data[], uint32_t u32Len);
uint32_t CRC32_Get32(uint32_t pu32Data[], uint32_t u32Len);

en_result_t CRC32_Check8(uint8_t pu8Data[], uint32_t u32Len, uint32_t u32CRC);
en_result_t CRC32_Check16(uint16_t pu16Data[], uint32_t u32Len, uint32_t u32CRC);
en_result_t CRC32_Check32(uint32_t pu32Data[], uint32_t u32Len, uint32_t u32CRC);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_CTRIM CTRIM模块驱动库
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Macros CTRIM全局宏定义
 * @{
 */

/**
 * @defgroup CTRIM_PINs_Define CTRIM引脚定义
 * @{
 */
#define CTRIM_CR0_STEP_B0   (0x1u << CTRIM_CR0_STEP_Pos)
#define CTRIM_CR0_STEP_B1   (0x2u << CTRIM_CR0_STEP_Pos)
#define CTRIM_CR0_STEP_B2   (0x4u << CTRIM_CR0_STEP_Pos)

#define CTRIM_CR0_ETRFLT_B0 (0x1u << CTRIM_CR0_ETRFLT_Pos)
#define CTRIM_CR0_ETRFLT_B1 (0x2u << CTRIM_CR0_ETRFLT_Pos)
#define CTRIM_CR0_ETRFLT_B2 (0x4u << CTRIM_CR0_ETRFLT_Pos)

#define CTRIM_CR0_SRC_B0    (0x1u << CTRIM_CR0_SRC_Pos)
#define CTRIM_CR0_SRC_B1    (0x2u << CTRIM_CR0_SRC_Pos)
#define CTRIM_CR0_SRC_B2    (0x4u << CTRIM_CR0_SRC_Pos)

#define CTRIM_CR1_MD_B0     (0x1u << CTRIM_CR1_MD_Pos)
#define CTRIM_CR1_MD_B1     (0x2u << CTRIM_CR1_MD_Pos)

#define CTRIM_CR1_MDRCH_B0  (0x1u << CTRIM_CR1_MDRCH_Pos)
#define CTRIM_CR1_MDRCH_B1  (0x2u << CTRIM_CR1_MDRCH_Pos)

#define CTRIM_CR1_PRS_B0    (0x1u << CTRIM_CR1_PRS_Pos)
#define CTRIM_CR1_PRS_B1    (0x2u << CTRIM_CR1_PRS_Pos)
#define CTRIM_CR1_PRS_B2    (0x4u << CTRIM_CR1_PRS_Pos)
#define CTRIM_CR1_PRS_B3    (0x8u << CTRIM_CR1_PRS_Pos)
/**
 * @}
 */

/**
 * @defgroup CTRIM_INITIAL_STEP_SELECTION  TRIM初始步进量选择
 * @{
 */
#define CTRIM_INITIAL_STEP_2   (CTRIM_CR0_STEP_B0)
#define CTRIM_INITIAL_STEP_4   (CTRIM_CR0_STEP_B1)
#define CTRIM_INITIAL_STEP_8   (CTRIM_CR0_STEP_B0 | CTRIM_CR0_STEP_B1)
#define CTRIM_INITIAL_STEP_16  (CTRIM_CR0_STEP_B2)
#define CTRIM_INITIAL_STEP_32  (CTRIM_CR0_STEP_B0 | CTRIM_CR0_STEP_B2)
#define CTRIM_INITIAL_STEP_64  (CTRIM_CR0_STEP_B1 | CTRIM_CR0_STEP_B2)
#define CTRIM_INITIAL_STEP_128 (CTRIM_CR0_STEP_B0 | CTRIM_CR0_STEP_B1 | CTRIM_CR0_STEP_B2)
/**
 * @}
 */

/**
 * @defgroup CTRIM_ETR_CLOCK_FILTER_SELECTION  外部管脚输入时钟滤波配置
 * @{
 */
#define CTRIM_ETR_CLK_FLT_NONE          (0x00000000UL)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV1CYC2 (CTRIM_CR0_ETRFLT_B0)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV1CYC4 (CTRIM_CR0_ETRFLT_B1)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV1CYC6 (CTRIM_CR0_ETRFLT_B0 | CTRIM_CR0_ETRFLT_B1)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV4CYC4 (CTRIM_CR0_ETRFLT_B2)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV4CYC6 (CTRIM_CR0_ETRFLT_B0 | CTRIM_CR0_ETRFLT_B2)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV8CYC4 (CTRIM_CR0_ETRFLT_B1 | CTRIM_CR0_ETRFLT_B2)
#define CTRIM_ETR_CLK_FLT_PCLK_DIV8CYC6 (CTRIM_CR0_ETRFLT_B0 | CTRIM_CR0_ETRFLT_B1 | CTRIM_CR0_ETRFLT_B2)
/**
 * @}
 */

/**
 * @defgroup CTRIM_ACCURATE_CLOCK_SELECTION  精确时钟源选择
 * @{
 */
#define CTRIM_ACCURATE_CLOCK_ETR       (0x00000000UL)
#define CTRIM_ACCURATE_CLOCK_XTH       (CTRIM_CR0_SRC_B0)
#define CTRIM_ACCURATE_CLOCK_XTL       (CTRIM_CR0_SRC_B1)
#define CTRIM_ACCURATE_CLOCK_PCLK      (CTRIM_CR0_SRC_B0 | CTRIM_CR0_SRC_B1)
#define CTRIM_ACCURATE_CLOCK_RCL       (CTRIM_CR0_SRC_B2)
#define CTRIM_ACCURATE_CLOCK_RCH       (CTRIM_CR0_SRC_B0 | CTRIM_CR0_SRC_B2)
#define CTRIM_ACCURATE_CLOCK_LPTIM_TOG (CTRIM_CR0_SRC_B1 | CTRIM_CR0_SRC_B2)
/**
 * @}
 */

/**
 * @defgroup CTRIM_MODE_SELECTION  工作模式选择
 * @{
 */
#define CTRIM_MODE_RCH_AUTO_TRIM (CTRIM_CR1_AUTO)
#define CTRIM_MODE_RCL_AUTO_TRIM ((CTRIM_CR1_AUTO) | (CTRIM_CR1_MD_B0))
#define CTRIM_MODE_TIMER         (CTRIM_CR1_MD_B1)
/**
 * @}
 */

/**
 * @defgroup CTRIM_RCH_TRIM_BITS_SELECTION  RCH校准精度选择
 * @{
 */
#define CTRIM_RCH_TRIM_11bit (0x00000000UL)
#define CTRIM_RCH_TRIM_5bit  (CTRIM_CR1_MDRCH_B1)
#define CTRIM_RCH_TRIM_6bit  ((CTRIM_CR1_MDRCH_B0) | (CTRIM_CR1_MDRCH_B1))
/**
 * @}
 */

/**
 * @defgroup CTRIM_REF_CLOCK_DIV_SELECTION  参考时钟预分频配置
 * @{
 */
#define CTRIM_REF_CLOCK_DIV2     (CTRIM_CR1_PRS_B0)
#define CTRIM_REF_CLOCK_DIV4     (CTRIM_CR1_PRS_B1)
#define CTRIM_REF_CLOCK_DIV8     (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B1)
#define CTRIM_REF_CLOCK_DIV16    (CTRIM_CR1_PRS_B2)
#define CTRIM_REF_CLOCK_DIV32    (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B2)
#define CTRIM_REF_CLOCK_DIV64    (CTRIM_CR1_PRS_B1 | CTRIM_CR1_PRS_B2)
#define CTRIM_REF_CLOCK_DIV128   (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B1 | CTRIM_CR1_PRS_B2)
#define CTRIM_REF_CLOCK_DIV512   (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B3)
#define CTRIM_REF_CLOCK_DIV1024  (CTRIM_CR1_PRS_B1 | CTRIM_CR1_PRS_B3)
#define CTRIM_REF_CLOCK_DIV2048  (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B1 | CTRIM_CR1_PRS_B3)
#define CTRIM_REF_CLOCK_DIV4096  (CTRIM_CR1_PRS_B2 | CTRIM_CR1_PRS_B3)
#define CTRIM_REF_CLOCK_DIV8192  (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B2 | CTRIM_CR1_PRS_B3)
#define CTRIM_REF_CLOCK_DIV16384 (CTRIM_CR1_PRS_B1 | CTRIM_CR1_PRS_B2 | CTRIM_CR1_PRS_B3)
#define CTRIM_REF_CLOCK_DIV32768 (CTRIM_CR1_PRS_B0 | CTRIM_CR1_PRS_B1 | CTRIM_CR1_PRS_B2 | CTRIM_CR1_PRS_B3)
/**
 * @}
 */

/**
 * @defgroup CTRIM_ONE_SHOT_SELECTION  校准模式配置
 * @{
 */
#define CTRIM_ONE_SHOT_REPETITIVE (0x00000000UL)  /*!< 实时校准模式 */
#define CTRIM_ONE_SHOT_SINGLE     (CTRIM_CR1_OST) /*!< 单次校准模式 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_IT_SELECTION  中断控制位使能选择
 * @{
 */
#define CTRIM_IT_UD   (CTRIM_IER_UD)   /*!< 误差计数器下溢 中断 */
#define CTRIM_IT_END  (CTRIM_IER_END)  /*!< 自动Trim结束 中断 */
#define CTRIM_IT_PS   (CTRIM_IER_PS)   /*!< 误差计数器完成(一次计数) 中断 */
#define CTRIM_IT_MISS (CTRIM_IER_MISS) /*!< 计数失败(在GCLK的一个周期内，误差计数器已计数到ARR) 中断 */
#define CTRIM_IT_OV   (CTRIM_IER_OV)   /*!< TrimCode溢出(TrimCode已调整到0或者0x1FF) 中断 */
#define CTRIM_IT_OK   (CTRIM_IER_OK)   /*!< 自动Trim结果在范围内 中断 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_FLAG_SELECTION  中断标志位选择
 * @{
 */
#define CTRIM_FLAG_UD   (CTRIM_ISR_UD)   /*!< 误差计数器下溢 标志 */
#define CTRIM_FLAG_END  (CTRIM_ISR_END)  /*!< 自动Trim结束 标志 */
#define CTRIM_FLAG_PS   (CTRIM_ISR_PS)   /*!< 误差计数器完成(一次计数) 标志 */
#define CTRIM_FLAG_MISS (CTRIM_ISR_MISS) /*!< 计数失败(在GCLK的一个周期内，误差计数器已计数到ARR) 标志 */
#define CTRIM_FLAG_OV   (CTRIM_ISR_OV)   /*!< TrimCode溢出(TrimCode已调整到0或者0x1FF) 标志 */
#define CTRIM_FLAG_OK   (CTRIM_ISR_OK)   /*!< Trim完成时精度满足FLIM要求 标志 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_CLEAR_FLAG_SELECTION  清除中断标志位选择
 * @{
 */
#define CTRIM_CLEAR_FLAG_UD   (CTRIM_ICR_UD)   /*!< 误差计数器下溢 标志 */
#define CTRIM_CLEAR_FLAG_END  (CTRIM_ICR_END)  /*!< 自动Trim结束 标志 */
#define CTRIM_CLEAR_FLAG_PS   (CTRIM_ICR_PS)   /*!< 误差计数器完成(一次计数) 标志 */
#define CTRIM_CLEAR_FLAG_MISS (CTRIM_ICR_MISS) /*!< 计数失败(在GCLK的一个周期内，误差计数器已计数到ARR) 标志 */
#define CTRIM_CLEAR_FLAG_OV   (CTRIM_ICR_OV)   /*!< TrimCode溢出(TrimCode已调整到0或者0x1FF) 标志 */
#define CTRIM_CLEAR_FLAG_OK   (CTRIM_ICR_OK)   /*!< Trim完成时精度满足FLIM要求 标志 */
/**
 * @}
 */

/**
 * @defgroup CTRIM_ARR_COUNT_DIR  误差计数器计数方向
 * @{
 */
#define CTRIM_ARR_COUNT_DIR_INCREASE (0x00000000UL)  /*!< 递增计数，RCH输出频率高于目标频率，或RCL输出频率低于目标频率 */
#define CTRIM_ARR_COUNT_DIR_DECREASE (CTRIM_ISR_DIR) /*!< 递减计数，RCH输出频率低于目标频率，或RCL输出频率高于目标频率 */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Types CTRIM全局类型定义
 * @{
 */

/**
 * @brief  CTRIM 自动校准 配置结构体定义
 */
typedef struct stc_ctrim_cali_init
{
    uint32_t u32Mode;            /*!< 校准模式  @ref CTRIM_MODE_SELECTION */
    uint32_t u32RCHTrimBits;     /*!< 校准模式  @ref CTRIM_RCH_TRIM_BITS_SELECTION */
    uint32_t u32AccurateClock;   /*!< 精确时钟源选择  @ref CTRIM_ACCURATE_CLOCK_SELECTION */
    uint32_t u32RefClockDiv;     /*!< 参考时钟分频  @ref CTRIM_REF_CLOCK_DIV_SELECTION */
    uint32_t u32OneShot;         /*!< 校准模式，实时校准或单次校准  @ref CTRIM_ONE_SHOT_SELECTION */
    uint32_t u32InitialStep;     /*!< TRIM初始步进量  @ref CTRIM_INITIAL_STEP_SELECTION */
    uint32_t u32EtrFilter;       /*!< 外部输入管脚滤波配置  @ref CTRIM_ETR_CLOCK_FILTER_SELECTION */
    uint16_t u16ReloadVal;       /*!< 自动装载寄存器ARR配置值 取值范围 0x0 ~ 0xFFFF */
    uint16_t u16CountErrorLimit; /*!< 误差允许值  取值范围 0x0 ~ 0xFFF */
} stc_ctrim_cali_init_t;

/**
 * @brief  CTRIM 定时器 配置结构体定义
 */
typedef struct stc_ctrim_timer_init
{
    uint32_t u32Clock;     /*!< 时钟源选择  @ref CTRIM_ACCURATE_CLOCK_SELECTION */
    uint32_t u32ClockDiv;  /*!< 时钟分频  @ref CTRIM_REF_CLOCK_DIV_SELECTION */
    uint32_t u32EtrFilter; /*!< 外部输入管脚滤波配置  @ref CTRIM_ETR_CLOCK_FILTER_SELECTION */
    uint32_t u16ReloadVal; /*!< 自动装载寄存器ARR配置值 取值范围 0x0 ~ 0xFFFF */
} stc_ctrim_timer_init_t;
/**
 * @}
 */

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */
en_result_t CTRIM_CaliInit(CTRIM_TypeDef* CTRIMx, stc_ctrim_cali_init_t* pstcInitCfg);
en_result_t CTRIM_TimerInit(CTRIM_TypeDef* CTRIMx, stc_ctrim_timer_init_t* pstcInitCfg);
uint32_t    CTRIM_GetCounter(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetAutoReload(CTRIM_TypeDef* CTRIMx, uint32_t u32AutoReload);
uint32_t    CTRIM_GetAutoReload(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetInitialStep(CTRIM_TypeDef* CTRIMx, uint32_t u32TrimStep);
uint32_t    CTRIM_GetInitialStep(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetEtrClockFilter(CTRIM_TypeDef* CTRIMx, uint32_t u32ExClockFilter);
uint32_t    CTRIM_GetEtrClockFilter(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetAccurateClock(CTRIM_TypeDef* CTRIMx, uint32_t u32ClockSource);
uint32_t    CTRIM_GetAccurateClock(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetMode(CTRIM_TypeDef* CTRIMx, uint32_t u32Mode);
uint32_t    CTRIM_GetMode(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetRCHTrimBits(CTRIM_TypeDef* CTRIMx, uint32_t u32RchTrimBits);
uint32_t    CTRIM_GetRCHTrimBits(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetRefClockDiv(CTRIM_TypeDef* CTRIMx, uint32_t u32RefClockDiv);
uint32_t    CTRIM_GetRefClockDiv(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetOneShot(CTRIM_TypeDef* CTRIMx, uint32_t u32OneShotMode);
uint32_t    CTRIM_GetOneShot(CTRIM_TypeDef* CTRIMx);
uint32_t    CTRIM_GetARRCoutDir(CTRIM_TypeDef* CTRIMx);
uint32_t    CTRIM_GetTrimCode(CTRIM_TypeDef* CTRIMx);
uint32_t    CTRIM_GetCountErrorCapture(CTRIM_TypeDef* CTRIMx);
void        CTRIM_SetCountErrorLimit(CTRIM_TypeDef* CTRIMx, uint16_t u16ErrLimit);
uint16_t    CTRIM_GetCountErrorLimit(CTRIM_TypeDef* CTRIMx);
void        CTRIM_Enable(CTRIM_TypeDef* CTRIMx);
void        CTRIM_Disable(CTRIM_TypeDef* CTRIMx);
boolean_t   CTRIM_IsEnable(CTRIM_TypeDef* CTRIMx);
void        CTRIM_EnableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT);
void        CTRIM_DisableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT);
boolean_t   CTRIM_IsEnableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT);
boolean_t   CTRIM_IsActiveFlag(CTRIM_TypeDef* CTRIMx, uint32_t u32ITFlag);
void        CTRIM_ClearFlag(CTRIM_TypeDef* CTRIMx, uint32_t u32ITFlag);
void        CTRIM_ClearFlag_ALL(CTRIM_TypeDef* CTRIMx);

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
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_DEBUG DEBUG模块驱动库
 * @{
 */

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup DEBUG_Global_Types DEBUG全局类型定义
 * @{
 */

/**
 * @brief  模块选择，设置调试模式下各模块工作状态
 */
typedef enum
{
    DebugMskAtim0   = 0x0001u,    /*!< ATIM0 */
    DebugMskAtim1   = 0x0002u,    /*!< ATIM1 */
    DebugMskAtim2   = 0x0004u,    /*!< ATIM2 */
    DebugMskLpTim   = 0x0008u,    /*!< LPTIM */
    DebugMskCtim0   = 0x0010u,    /*!< CTIM0 */
    DebugMskCtim1   = 0x0020u,    /*!< CTIM1 */
    DebugMskCtrim   = 0x0080u,    /*!< CTRIM */
    DebugMskIwdt    = 0x0100u,    /*!< IWDT */
    DebugMskRtc     = 0x0200u,    /*!< RTC */
    DebugMskTim3    = 0x0800u,    /*!< ATIM3 */
    DebugMskWwdt    = 0x1000u,    /*!< WWDT */
}en_debug_module_active_t;

/**
 * @}
 */
/*******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup DEBUG_Global_Functions DEBUG全局函数定义
 * @{
 */

/**
 * @brief  在SWD调试模式下，使能模块计数功能
 */
en_result_t Debug_ActiveEnable(en_debug_module_active_t enModule);
/**
 * @brief  在SWD调试模式下，暂停模块计数功能
 */
en_result_t Debug_ActiveDisable(en_debug_module_active_t enModule);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */



/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_DMAC DMAC模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DMAC_Global_Types DMAC全局类型定义
 * @{
 */
/**
 * @brief  DMA 通道
 */
typedef enum
{
    DmaCh0      = 0x00U, /*!< DMA 通道0 */
    DmaCh1      = 0x10U, /*!< DMA 通道1 */
    DmaCh2      = 0x20U, /*!< DMA 通道2 */
    DmaCh3      = 0x30U, /*!< DMA 通道3 */
    DmaCh4      = 0x40U, /*!< DMA 通道4 */
} en_dma_channel_t;

/**
 * @brief  DMA 优先级
 */
typedef enum
{
    DmaMskPriorityFix   = 0x00000000U, /*!< DMA 各通道优先级固定 (CH0>CH1) */
    DmaMskPriorityLoop  = 0x10000000U, /*!< DMA 各通道优先级采用轮询方式 */
} en_dma_priority_t;

/**
 * @brief  DMA 传输数据宽度
 */
typedef enum
{
    DmaMsk8Bit      = 0x00000000U, /*!< 8 bit  字节传输 */
    DmaMsk16Bit     = 0x04000000U, /*!< 16 bit 半字传输 */
    DmaMsk32Bit     = 0x08000000U, /*!< 32 bit 字传输 */
} en_dma_transfer_width_t;

/**
 * @brief  DMA 传输模式：块(Block)传输或者突发(Burst)传输
 */
typedef enum
{
    DmaMskBlock     = 0x00000000U, /*!< 块(Block)传输 */
    DmaMskBurst     = 0x10000000U, /*!< 突发(Burst)传输 */
} en_dma_transfer_mode_t;

/**
 * @brief  DMA 传输当前状态
 */
typedef enum
{
    DmaDefault          = 0U, /*!< 初始值 */
    DmaAddOverflow      = 1U, /*!< 传输错误引起中止（地址溢出） */
    DmaHALT             = 2U, /*!< 传输停止请求引起中止（外设停止请求引起的停止或者EB/DE位引起的禁止传输） */
    DmaAccSCRErr        = 3U, /*!< 传输错误引起中止（传输源地址访问错误） */
    DmaAccDestErr       = 4U, /*!< 传输错误引起中止（传输目的地址访问错误） */
    DmaTransferComplete = 5U, /*!< 成功传输完成 */
    DmaTransferPause    = 7U, /*!< 传输暂停 */
} en_dma_stat_t;

/**
 * @brief  DMA 源地址控制模式：自增或固定
 */
typedef enum
{
    DmaMskSrcAddrInc    = 0x00000000U, /*!< 地址自增 */
    DmaMskSrcAddrFix    = 0x02000000U, /*!< 地址固定 */
} en_src_address_mode_t;

/**
 * @brief  DMA 目的地址控制模式：自增或固定
 */
typedef enum
{
    DmaMskDstAddrInc    = 0x00000000U, /*!< 地址自增 */
    DmaMskDstAddrFix    = 0x01000000U, /*!< 地址固定 */
} en_dst_address_mode_t;

/**
 * @brief  DMA CONFA:BC[3:0]和CONFA:TC[15:0]的重载功能
 */
typedef enum
{
    DmaMskBcTcReloadDisable = 0x00000000U, /*!< 禁止重载 */
    DmaMskBcTcReloadEnable  = 0x00800000U, /*!< 使能重载 */
} en_bc_tc_reload_mode_t;

/**
 * @brief  DMA 源地址重载功能：使能或禁止
 */
typedef enum
{
    DmaMskSrcAddrReloadDisable  = 0x00000000U, /*!< 禁止DMA源地址重载 */
    DmaMskSrcAddrReloadEnable   = 0x00400000U, /*!< 使能DMA源地址重载 */
} en_src_address_reload_mode_t;

/**
 * @brief  DMA 目的地址重载功能：使能或禁止
 */
typedef enum
{
    DmaMskDstAddrReloadDisable  = 0x00000000U, /*!< 禁止DMA目的地址重载 */
    DmaMskDstAddrReloadEnable   = 0x00200000U, /*!< 使能DMA目的地址重载 */
} en_dst_address_reload_mode_t;

/**
 * @brief  DMA 连续传输设置
 */
typedef enum
{
    DmaMskOneTransfer           = 0x00000000U, /*!< 传输一次，DMA传输完成时清除CONFA:ENS位 */
    DmaMskContinuousTransfer    = 0x00000001U, /*!< 连续传输，DMA传输完成时不清除CONFA:ENS位 */
} en_dma_msk_t;

/**
 * @brief  DMA 触发源选择
 */
typedef enum
{
    DmaSWTrig           = 0x00U, /*!< 软件触发 */

    DmaUart0TxTrig      = 0x40U, /*!< USART0发送Buf空 */
    DmaUart0RxTrig      = 0x41U, /*!< USART0接收Buf非空 */
    DmaUart1TxTrig      = 0x42U, /*!< USART1发送Buf空 */
    DmaUart1RxTrig      = 0x43U, /*!< USART1接收Buf非空 */
    DmaLpUart0TxTrig    = 0x44U, /*!< LPUART0发送Buf空 */
    DmaLpUart0RxTrig    = 0x45U, /*!< LPUART0接收Buf非空 */
    DmaLpUart1TxTrig    = 0x46U, /*!< LPUART1发送Buf空 */
    DmaLpUart1RxTrig    = 0x47U, /*!< LPUART1接收Buf非空 */
    DmaGtim0Trig        = 0x48U, /*!< GTIM0发生捕获事件或比较事件 */
    DmaGtim1Trig        = 0x49U, /*!< GTIM1发生捕获事件或比较事件 */

    DmaADCJQRTrig       = 0x4CU, /*!< ADC插队转换完成 */
    DmaADCEOCTrig       = 0x4DU, /*!< ADC顺序单次转换完成 */

    DmaSPI0TXTrig       = 0x50U, /*!< SPI0发送Buf空 */
    DmaSPI0RXTrig       = 0x51U, /*!< SPI0接收Buf非空 */
    DmaSPI1TXTrig       = 0x52U, /*!< SPI1发送Buf空 */
    DmaSPI1RXTrig       = 0x53U, /*!< SPI1接收Buf非空 */
    DmaI2CSLVRXTrig     = 0x54U, /*!< I2CSLV接收Buf非空 */
    DmaI2CSLVTXTrig     = 0x55U, /*!< I2CSLV发送Buf空 */

    DmaATIM0ATrig       = 0x58U, /*!< ATIM0 通道A，发生捕获事件或比较事件 */
    DmaATIM0BTrig       = 0x59U, /*!< ATIM0 通道B，发生捕获事件或比较事件 */
    DmaATIM1ATrig       = 0x5AU, /*!< ATIM1 通道A，发生捕获事件或比较事件 */
    DmaATIM1BTrig       = 0x5BU, /*!< ATIM1 通道B，发生捕获事件或比较事件 */
    DmaATIM2ATrig       = 0x5CU, /*!< ATIM2 通道A，发生捕获事件或比较事件 */
    DmaATIM2BTrig       = 0x5DU, /*!< ATIM2 通道B，发生捕获事件或比较事件 */
    DmaATIM3ATrig       = 0x5EU, /*!< ATIM3 通道A，发生捕获事件或比较事件 */
    DmaATIM3BTrig       = 0x5FU, /*!< ATIM3 通道B，发生捕获事件或比较事件 */
}en_dma_trig_sel_t;

/**
 * @brief  DMA 通道初始化配置结构体
 */
typedef struct
{
    en_dma_transfer_mode_t         enMode;              /*!< DMA 传输模式 @ref en_dma_transfer_mode_t */

    uint16_t                       u16BlockSize;        /*!< 块传输个数 */
    uint16_t                       u16TransferCnt;      /*!< 传输块次数 */
    en_dma_transfer_width_t        enTransferWidth;     /*!< 传输数据字节宽度 @ref en_dma_transfer_width_t */

    en_src_address_mode_t          enSrcAddrMode;       /*!< DMA源地址控制模式：自增或固定 @ref en_src_address_mode_t */
    en_dst_address_mode_t          enDstAddrMode;       /*!< DMA目的地址控制模式：自增或固定 @ref en_dst_address_mode_t */

    en_src_address_reload_mode_t   enSrcAddrReloadCtl;  /*!< 源地址重载 @ref en_src_address_reload_mode_t */
    en_dst_address_reload_mode_t   enDestAddrReloadCtl; /*!< 目的地址重载 @ref en_dst_address_reload_mode_t */
    en_bc_tc_reload_mode_t         enSrcBcTcReloadCtl;  /*!< Bc/Tc值重载功能 @ref en_bc_tc_reload_mode_t */

    uint32_t                       u32SrcAddress;       /*!< 源地址 */
    uint32_t                       u32DstAddress;       /*!< 目的地址 */

    en_dma_msk_t                   enTransferMode;      /*!< DMA 连续传输设置 @ref en_dma_msk_t */
    en_dma_priority_t              enPriority;          /*!< DMA 优先级设定 @ref en_dma_priority_t */
    en_dma_trig_sel_t              enRequestNum;        /*!< DMA 触发源选择 @ref en_dma_trig_sel_t */
} stc_dma_cfg_t;


/**
 * @}
 */

  /*******************************************************************************
  * Global pre-processor symbols/macros ('#define')
  ******************************************************************************/

  /*******************************************************************************
  * Global variable definitions ('extern')
  ******************************************************************************/

  /*******************************************************************************
  * Global function prototypes (definition in C source)
  ******************************************************************************/
 /**
 * @addtogroup DMAC_Global_Functions DMAC全局函数定义
 * @{
 */

en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg);

void Dma_Enable(void);
void Dma_Disable(void);

void Dma_SwStart(en_dma_channel_t enCh);
void Dma_SwStop(en_dma_channel_t enCh);

void Dma_EnableChannelIrq(en_dma_channel_t enCh);
void Dma_DisableChannelIrq(en_dma_channel_t enCh);
void Dma_EnableChannelErrIrq(en_dma_channel_t enCh);
void Dma_DisableChannelErrIrq(en_dma_channel_t enCh);

void Dma_EnableChannel(en_dma_channel_t enCh);
void Dma_DisableChannel(en_dma_channel_t enCh);

void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize);
void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt);

void Dma_EnableContinusTranfer(en_dma_channel_t enCh);
void Dma_DisableContinusTranfer(en_dma_channel_t enCh);

void Dma_HaltTranfer(void);
void Dma_RecoverTranfer(void);
void Dma_PauseChannelTranfer(en_dma_channel_t enCh);
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh);

void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth);
void Dma_SetChPriority(en_dma_priority_t enPrio);

en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh);
void Dma_ClrStat(en_dma_channel_t enCh);

void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address);
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address);


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_EAU EAU模块驱动库
 * @{
 */


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EAU_Global_Types EAU全局类型定义
 * @{
 */
/**
 * @brief  EAU 运算状态定义
 */
typedef enum
{
    EauOk           = 0U, /*!< EAU计算正常 */
    EauErrTimeout   = 1U, /*!< EAU计算超时错误 */
    EauErrZero      = 2U, /*!< EAU除法运算除数为0错误 */
    EauErrOverflow  = 3U, /*!< EAU有符号除法运算溢出错误，商超出32位有符号数编码范围 */
    EauErrPara      = 4U, /*!< EAU参数错误 指针为空*/
}en_eau_status_t;



/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EAU_Global_Macros EAU全局宏定义
 * @{
 */


/**
 * @defgroup EAU_Mode EAU 运算模式
 * @{
 */
#define EAU_MODE_UNSIGN_DIV     (0x0U)  /*!< 无符号除法运算 */
#define EAU_MODE_SIGN_DIV       (0x1U)  /*!< 有符号除法运算 */
#define EAU_MODE_SQRT           (0x2U)  /*!< 开方运算 */
/**
 * @}
 */



/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EAU_Global_Functions EAU全局函数定义
 * @{
 */

en_eau_status_t EAU_Sqrt(uint32_t u32A, uint32_t *pu32X, uint32_t *pu32Y);
en_eau_status_t EAU_UnsignDiv(uint32_t u32A, uint32_t u32B, uint32_t *pu32X, uint32_t *pu32Y);
en_eau_status_t EAU_SignDiv(int32_t s32A, int32_t s32B, int32_t *ps32X, int32_t *ps32Y);

/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */



/* C binding of definitions if building with C++ compiler */

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_FLASH FLASH模块驱动库
 * @{
 */


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FLASH_Global_Types FLASH全局类型定义
 * @{
 */

/**
 * @brief  Flash中断类型重定义
 */
typedef enum
{
    FlashPCInt    = 0x01u,          /*!<  FLASH 擦写PC地址报警中断   */
    FlashSlockInt = 0x02u,          /*!<  FLASH 擦写保护报警中断     */
} en_flash_int_type_t;

/**
 * @brief  Flash功能设置类型重定义
 */
typedef enum
{
    FastWkupEn      = 0x10u,          /*!<  FLASH 快速唤醒使能                         */
    FlashReadOnlyEn = 0x20u,          /*!<  FLASH 只读使能                             */
    FlashDpStbEn    = 0x80u,          /*!<  系统进入DeepSleep时，FLASH进入低功耗使能   */
} en_flash_func_type_t;


/**
 * @brief  Flash读等待周期类型重定义
 */
typedef enum
{
    FlashWaitCycle0 = 0u,       /*!<  读等待周期设置为0-即读周期为1（当HCLK小于等于24MHz时）         */
    FlashWaitCycle1 = 1u,       /*!<  读等待周期设置为1-即读周期为2（当HCLK大于24MHz时必须至少为1）  */
    FlashWaitCycle2 = 2u,       /*!<  读等待周期设置为2-即读周期为3（当HCK大于48MHz时必须至少为2）   */
} en_flash_waitcycle_t;


/**
 * @brief  Flash擦写保护范围重定义
 */
typedef enum
{
    FlashLock0 = 0u,           /*!<  SLOCK0 Sector擦写保护寄存器0  */
    FlashLock1 = 4u,           /*!<  SLOCK1 Sector擦写保护寄存器1  */
} en_flash_lock_t;

/**
 * @brief Flash操作模式配置
 */
typedef enum
{
    FlashReadMode        = 0u,           /*!<  Flash 读模式             */
    FlashWriteMode       = 1u,           /*!<  Flash 写（编程）模式     */
    FlashSectorEraseMode = 2u,           /*!<  Flash 扇区（页）擦除模式 */
    FlashChipEraseMode   = 3u,           /*!<  Flash 全片擦除模式       */
    FlashContWriteMode   = 4u,           /*!<  Flash 连续写模式     */
} en_flash_op_mode_t;


/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
 /**
 * @defgroup FLASH_Global_Types FLASH全局类型定义
 * @{
 */
 /** @defgroup  Flash_Lock_State_Level  FLASH_LOCK_LEVLE
  * @{
  */
#define  FLASH_LOCK_STATE_LEVEL0    (0u)   /*!<  Flash Lock Level0，ISP可读写，SWD可读写 */
#define  FLASH_LOCK_STATE_LEVEL1    (1u)   /*!<  Flash Lock Level1，ISP可降级，SWD可降级；数据不可读出 */
#define  FLASH_LOCK_STATE_LEVEL2    (2u)   /*!<  Flash Lock Level2，ISP可降级，SWD无功能；数据不可读出 */
#define  FLASH_LOCK_STATE_LEVEL3    (3u)   /*!<  Flash Lock Level3，ISP无功能，SWD无功能；数据不可读出 */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)
	en_result_t Flash_Chip_Erase(void);
	en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len);
	en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len);
	en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len);
#elif defined(__ICCARM__)
	__ramfunc en_result_t Flash_Chip_Erase(void);
	__ramfunc en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len);
	__ramfunc en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len);
	__ramfunc en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len);
#endif

en_result_t Flash_LockAll(void);
en_result_t Flash_UnlockAll(void);
en_result_t Flash_FuncSet(en_flash_func_type_t enFunc, boolean_t bFlag);
en_result_t Flash_SectorErase(uint32_t u32SectorAddr);
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len);
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len);
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len);
en_result_t Flash_OpModeConfig(en_flash_op_mode_t enFlashOpMode);
en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue);
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle);
en_result_t Flash_EnDpstb(boolean_t bDpstbEn);
uint8_t Flash_ReadProtectLevel(void);
en_result_t Flash_EnableIrq(en_flash_int_type_t enFlashIntType);
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType);
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType);
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType);
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
 * Include files
 ******************************************************************************/


/* C binding of definitions if building with C++ compiler */

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_GPIO GPIO模块驱动库
 * @{
 */


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Types GPIO全局类型定义
 * @{
 */

/**
 * @brief  GPIO PIN类型定义
 */
typedef enum
{
    GpioPin0  = 0u,                 /*!< GPIO PIN0 */
    GpioPin1  = 1u,                 /*!< GPIO PIN1 */
    GpioPin2  = 2u,                 /*!< GPIO PIN2 */
    GpioPin3  = 3u,                 /*!< GPIO PIN3 */
    GpioPin4  = 4u,                 /*!< GPIO PIN4 */
    GpioPin5  = 5u,                 /*!< GPIO PIN5 */
    GpioPin6  = 6u,                 /*!< GPIO PIN6 */
    GpioPin7  = 7u,                 /*!< GPIO PIN7 */
    GpioPin8  = 8u,                 /*!< GPIO PIN8 */
    GpioPin9  = 9u,                 /*!< GPIO PIN9 */
    GpioPin10 = 10u,                /*!< GPIO PIN10 */
    GpioPin11 = 11u,                /*!< GPIO PIN11 */
    GpioPin12 = 12u,                /*!< GPIO PIN12 */
    GpioPin13 = 13u,                /*!< GPIO PIN13 */
    GpioPin14 = 14u,                /*!< GPIO PIN14 */
    GpioPin15 = 15u,                /*!< GPIO PIN15 */
}en_gpio_pin_t;

/**
 * @brief  GPIO 端口复用功能(AF-Alternate function)类型定义
 * @note  具体功能及含义请参考用户手册GPIO复用表或下表(如果用户手册或数据手册有更新，以手册为准)
 */
typedef enum
{
    GpioAf0  = 0u,      /*!< GPIO功能 */
    GpioAf1  = 1u,      /*!< GPIO AF1:复用功能1 */
    GpioAf2  = 2u,      /*!< GPIO AF2:复用功能2 */
    GpioAf3  = 3u,      /*!< GPIO AF3:复用功能3 */
    GpioAf4  = 4u,      /*!< GPIO AF4:复用功能4 */
    GpioAf5  = 5u,      /*!< GPIO AF5:复用功能5 */
    GpioAf6  = 6u,      /*!< GPIO AF6:复用功能6 */
    GpioAf7  = 7u,      /*!< GPIO AF7:复用功能7 */
}en_gpio_af_t;

/*!<||======||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||PSEL  ||   GpioAf1   ||   GpioAf2   ||   GpioAf3   ||   GpioAf4   ||   GpioAf5   ||   GpioAf6   ||   GpioAf7   ||*/
/*!<||======||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||PA00  ||UART1_CTS    ||LPUART1_TXD  ||ATIM0_ETR    ||VC0_OUT      ||ATIM1_CHA    ||ATIM3_ETR    ||ATIM0_CHA    ||*/
/*!<||PA01  ||USART1_RTS   ||LPUART1_RXD  ||ATIM0_CHB    ||ATIM1_ETR    ||ATIM1_CHB    ||HCLK_OUT     ||SPI1_MOSI    ||*/
/*!<||PA02  ||USART1_TXD   ||ATIM0_CHA    ||VC1_OUT      ||ATIM1_CHA    ||ATIM2_CHA    ||ATIM3_CH0A   ||SPI1_MISO    ||*/
/*!<||PA03  ||USART1_RXD   ||ATIM0_GATE   ||ATIM1_CHB    ||ATIM2_CHB    ||SPI1_CS      ||ATIM3_CH0B   ||PCLK_OUT     ||*/
/*!<||PA04  ||SPI0_CS      ||UART1_SCK    ||CTIM1_CH0    ||ATIM2_ETR    ||ATIM3_CH1A   ||USART1_TXD   ||I2CSLV_SCL   ||*/
/*!<||PA05  ||SPI0_SCK     ||ATIM0_ETR    ||CTIM0_ETR    ||ATIM0_CHA    ||ATIM3_CH1B   ||XTL_OUT      ||XTH_OUT      ||*/
/*!<||PA06  ||SPI0_MISO    ||CTIM0_CH0    ||ATIM3_BK     ||ATIM1_CHA    ||VC0_OUT      ||ATIM3_GATE   ||LPUART0_CTS  ||*/
/*!<||PA07  ||SPI0_MOSI    ||CTIM0_CH1    ||HCLK_OUT     ||ATIM3_CH2A   ||ATIM2_CHA    ||VC1_OUT      ||CTIM1_TOG    ||*/
/*!<||PA08  ||USART0_SCK   ||ATIM3_CH0A   ||USART0_TXD   ||CAN_STBY     ||ATIM1_GATE   ||CTIM0_TOGN   ||ATIM3_BK     ||*/
/*!<||PA09  ||USART0_TXD   ||STIM3_CH1A   ||STIM0_BK     ||I2C0_SCL     ||MCO_OUT      ||HCLK_OUT     ||I2CSLV_SCL   ||*/
/*!<||PA10  ||USART0_RXD   ||ATIM3_CH2A   ||ATIM2_BK     ||I2C0_SDA     ||ATIM2_GATE   ||PCLK_OUT     ||I2CSLV_SDA   ||*/
/*!<||PA11  ||USART0_CTS   ||ATIM3_GATE   ||I2C1_SCL     ||CAN_TX       ||VC0_OUT      ||SPI0_MISO    ||ATIM3_CH1B   ||*/
/*!<||PA12  ||USART0_RTS   ||ATIM3_ETR    ||I2C1_SDA     ||CAN_RX       ||VC1_OUT      ||SPI0_MOSI    ||CTIM1_ETR    ||*/
/*!<||PA13  ||USART1_SCK   ||USART0_RXD   ||LVD_OUT      ||ATIM3_ETR    ||RTC_1HZ      ||CTIM1_CH1    ||CTRIM_ETRTOG ||*/
/*!<||PA14  ||USART1_TXD   ||USART0_TXD   ||ATIM3_CH2A   ||LVD_OUT      ||RCH_OUT      ||RCL_OUT      ||PLL_OUT      ||*/
/*!<||PA15  ||SPI0_CS      ||USART1_RXD   ||LPUART1_RTS  ||ATIM0_ETR    ||ATIM0_CHA    ||ATIM3_CH1A   ||CAN_STBY     ||*/
/*!<||PB00  ||CTIM0_CH2    ||CTIM1_TOGN   ||LPUART0_TXD  ||ATIM3_CH2B   ||RCH_OUT      ||RCL_OUT      ||PLL_OUT      ||*/
/*!<||PB01  ||CTIM0_CH3    ||PCLK_OUT     ||I2CSLV_SDA   ||ATIM3_CH1B   ||LPUART0_RTS  ||LPTIM_TOGN   ||USART0_SCK   ||*/
/*!<||PB02  ||LPTIM_TOG    ||CTIM0_ETR    ||LPUART1_TXD  ||ATIM3_CH0B   ||ATIM1_BK     ||ATIM0_BK     ||ATIM2_BK     ||*/
/*!<||PB03  ||SPI0_SCK     ||ATIM0_CHB    ||ATIM1_GATE   ||ATIM3_CH0A   ||LPTIM_GATE   ||XTL_OUT      ||XTH_OUT      ||*/
/*!<||PB04  ||SPI0_MISO    ||CTIM0_CH0    ||ATIM2_BK     ||USART0_CTS   ||ATIM2_GATE   ||ATIM3_CH0B   ||LPTIM_ETR    ||*/
/*!<||PB05  ||SPI0_MOSI    ||ATIM3_BK     ||ATIM1_BK     ||CTIM0_CH1    ||LPTIM_GATE   ||CTRIM_ETRTOG ||USART0_RTS   ||*/
/*!<||PB06  ||I2C0_SCL     ||USART0_TXD   ||ATIM1_CHB    ||ATIM0_CHA    ||LPTIM_ETR    ||ATIM3_CH0A   ||LPTIM_TOG    ||*/
/*!<||PB07  ||I2C0_SDA     ||USART0_RXD   ||ATIM2_CHB    ||LPUART1_CTS  ||ATIM0_CHB    ||LPTIM_TOGN   ||ATIM3_ETR    ||*/
/*!<||PB08  ||I2C0_SCL     ||ATIM1_CHA    ||CAN_RX       ||ATIM2_CHA    ||ATIM0_GATE   ||ATIM3_CH2A   ||USART0_TXD   ||*/
/*!<||PB09  ||I2C0_SDA     ||USART0_SCK   ||SPI1_CS      ||ATIM2_CHA    ||CAN_TX       ||ATIM2_CHB    ||USART0_RXD   ||*/
/*!<||PB10  ||I2C1_SCL     ||SPI1_SCK     ||ATIM1_CHA    ||LPUART0_TXD  ||ATIM3_CH1A   ||LPUART1_RTS  ||USART1_RTS   ||*/
/*!<||PB11  ||I2C1_SDA     ||ATIM1_CHB    ||LPUART0_RXD  ||ATIM2_GATE   ||ATIM3_CH1A   ||LPUART1_CTS  ||USART1_CTS   ||*/
/*!<||PB12  ||SPI1_CS      ||ATIM3_BK     ||LPUART0_TXD  ||ATIM0_BK     ||             ||LPUART0_RTS  ||ATIM3_CH0A   ||*/
/*!<||PB13  ||SPI1_SCK     ||I2C1_SCL     ||ATIM3_CH0B   ||LPUART0_CTS  ||ATIM1_CHA    ||ATIM1_GATE   ||             ||*/
/*!<||PB14  ||SPI1_MISO    ||I2C1_SDA     ||ATIM3_CH1B   ||ATIM0_CHA    ||ATIM3_CH2A   ||LPUART0_RTS  ||ATIM1_BK     ||*/
/*!<||PB15  ||SPI1_MOSI    ||ATIM3_CH2B   ||ATIM0_CHB    ||ATIM0_GATE   ||RTC_1HZ      ||CTIM0_TOG    ||LPUART1_RXD  ||*/
/*!<||PC13  ||CTIM1_ETR    ||RTC_1HZ      ||ATIM3_CH1B   ||CTIM0_TOG    ||             ||             ||             ||*/
/*!<||PC14  ||CTIM1_CH0    ||CTIM0_TOGN   ||LVD_OUT      ||             ||             ||             ||             ||*/
/*!<||PC15  ||CTIM1_CH0    ||             ||             ||             ||             ||             ||             ||*/
/*!<||PD00  ||I2C0_SDA     ||CTRIM_ETRTOG ||USART1_TXD   ||CTIM1_CH2    ||I2CSLV_SCL   ||             ||             ||*/
/*!<||PD01  ||I2C0_SCL     ||ATIM3_CH0B   ||USART1_RXD   ||CTIM1_CH3    ||I2CSLV_SDA   ||             ||             ||*/
/*!<||PD02  ||PCA_ECI      ||LPUART0_RTS  ||TIM1_ETR     ||             ||             ||             ||             ||*/
/*!<||PD03  ||             ||             ||             ||             ||             ||             ||             ||*/
/*!<||PD06  ||I2C1_SCL     ||LPUART1_CTS  ||USART0_CTS   ||RTC_OUT      ||ATIM3_BK     ||CTIM1_CH2    ||             ||*/
/*!<||PD07  ||I2C1_SDA     ||LPUART1_RTS  ||USART0_RTS   ||RTC_TS       ||ATIM3_ETR    ||CTIM1_CH3    ||             ||*/
/*!<||======||=============||=============||=============||=============||=============||=============||=============||*/

/**
 * @brief  GPIO 输入输出配置数据类型定义
 */
typedef enum
{
    GpioDirOut = 0u,                /*!< GPIO 输出 */
    GpioDirIn  = 1u,                /*!< GPIO 输入 */
}en_gpio_dir_t;

/**
 * @brief GPIO端口上拉配置数据类型定义
 */
typedef enum
{
    GpioPuDisable = 0u,                /*!< GPIO无上拉 */
    GpioPuEnable  = 1u,                /*!< GPIO上拉 */
}en_gpio_pu_t;

/**
 * @brief GPIO端口下拉配置数据类型定义
 */
typedef enum
{
    GpioPdDisable = 0u,                /*!< GPIO无下拉 */
    GpioPdEnable  = 1u,                /*!< GPIO下拉 */
}en_gpio_pd_t;
/**
 * @brief GPIO端口输出驱动能力配置数据类型定义
 */
typedef enum
{
    GpioDrvH = 0u,                  /*!< GPIO高驱动能力 */
    GpioDrvL = 1u,                  /*!< GPIO低驱动能力 */
}en_gpio_drv_t;

/**
 * @brief GPIO端口开漏输出控制数据类型定义
 */
typedef enum
{
    GpioOdDisable = 0u,             /*!< GPIO开漏输出关闭 */
    GpioOdEnable  = 1u,             /*!< GPIO开漏输出使能 */
}en_gpio_od_t;

/**
 * @brief GPIO中断触发方式类型定义
 */
typedef enum
{
    GpioIrqHigh     = 0u,           /*!< GPIO高电平触发 */
    GpioIrqLow      = 4u,           /*!< GPIO低电平触发 */
    GpioIrqRising   = 8u,           /*!< GPIO上升沿触发 */
    GpioIrqFalling  = 12u,          /*!< GPIO下降沿触发 */
}en_gpio_irqtype_t;


/**
 * @brief GPIO 辅助功能（SF-Secondary Function）MCO输出时钟选择类型定义
 */
typedef enum
{
    GpioSfMcoSrcRCH    = 0u,      /*!< MCO output RCH */
    GpioSfMcoSrcXTH    = 1u,      /*!< MCO output XTH */
    GpioSfMcoSrcRCL    = 2u,      /*!< MCO output RCL */
    GpioSfMcoSrcPLL    = 4u,      /*!< MCO output PLL */
    GpioSfMcoSrcRC150K = 5u,      /*!< MCO output RC150K */
    GpioSfMcoSrcRC96M  = 7u,      /*!< MCO output RC96M */
}en_gpio_sf_mco_src_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）MCO输出分频选择类型定义
 */
typedef enum
{
    GpioSfMcoOutDisable = 0u,      /*!< MCO output disable */
    GpioSfMcoOutDiv1    = 1u,      /*!< MCO */
    GpioSfMcoOutDiv8    = 2u,      /*!< MCO/2 */
    GpioSfMcoOutDiv64   = 3u,      /*!< MCO/64 */
    GpioSfMcoOutDiv256  = 4u,      /*!< MCO/256 */
}en_gpio_sf_mcoout_div_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）PCLK输出分频选择类型定义
 */
typedef enum
{
    GpioSfPclkOutDisable = 0u,      /*!< PCLK output disable */
    GpioSfPclkOutDiv1    = 1u,      /*!< PCLK */
    GpioSfPclkOutDiv2    = 2u,      /*!< PCLK/2 */
    GpioSfPclkOutDiv4    = 3u,      /*!< PCLK/4 */
    GpioSfPclkOutDiv8    = 4u,      /*!< PCLK/8 */
}en_gpio_sf_pclkout_div_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器ETR类型选择数据类型定义
 */
typedef enum
{
    GpioSfAtim0Etr   = 0u,                   /*!< Atim0定时器ETR输入选择 */
    GpioSfCtim0Etr   = 4u,                   /*!< Ctim0定时器ETR输入选择 */
    GpioSfCtim1Etr   = 8u,                   /*!< Ctim1定时器ETR输入选择 */
    GpioSfAtim3Etr   = 12u,                  /*!< Atim3定时器ETR输入选择 */
}en_gpio_sf_tim_e_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器捕获输入类型选择数据类型定义
 */
typedef enum
{
    GpioSfAtim0Cap0 = 0u,                   /*!< Atim0定时器CH0A输入选择 */
    GpioSfCtim0Cap3 = 4u,                   /*!< Ctim0定时器CH3输入选择 */
    GpioSfCtim1Cap3 = 8u,                   /*!< Ctim1定时器CH3输入选择 */
    GpioSfAtim3Cap2 = 12u,                  /*!< Atim3定时器CH2B输入选择 */
}en_gpio_sf_tim_c_t;


/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器互联功能选择类型定义
 * @note  具体功能及含义请参考用户手册GPIO辅助寄存器描述
 */
typedef enum
{
    GpioSf0 = 0u,       /*!<  SF0:AFRH/AFRL的配置功能 */
    GpioSf1 = 1u,       /*!<  SF1:辅助功能1 */
    GpioSf2 = 2u,       /*!<  SF2:辅助功能2 */
    GpioSf3 = 3u,       /*!<  SF3:辅助功能3 */
    GpioSf4 = 4u,       /*!<  SF4:辅助功能4 */
    GpioSf5 = 5u,       /*!<  SF5:辅助功能5 */
    GpioSf6 = 6u,       /*!<  SF6:辅助功能6 */
    GpioSf7 = 7u,       /*!<  SF7:辅助功能7 */
}en_gpio_sf_t;
/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||   ETR      ||     sf0     ||     sf1     ||     sf2     ||     sf3     ||     sf4     ||     sf5     ||     sf6     ||     sf7     ||*/
/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||CTIM0ETR    ||GTIM0_ETR    ||USART1_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA05         ||PA13         ||PB05         ||*/
/*!<||CTIM1ETR    ||GTIM1_ETR    ||LPUART0_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA06         ||PA14         ||PB06         ||*/
/*!<||ATIM0ETR    ||ATIM0_ETR    ||USART0_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA04         ||PA12         ||PB04         ||*/
/*!<||ATIM3ETR    ||ATIM3_ETR    ||LPUART1_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA07         ||PA15         ||PB07         ||*/


/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||    CAP     ||     sf0     ||     sf1     ||     sf2     ||     sf3     ||     sf4     ||     sf5     ||     sf6     ||     sf7     ||*/
/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||CTIM0CAP3   ||GTIM0_CH3    ||USART1_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA01         ||PA09         ||PB01         ||*/
/*!<||CTIM1CAP3   ||GTIM1_CH3    ||LPUART0_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA02         ||PA10         ||PB02         ||*/
/*!<||ATIM0CAP0   ||ATIM0_CH0A   ||USART0_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA00         ||PA08         ||PB00         ||*/
/*!<||ATIM3CAP2   ||ATIM3_CH2B   ||LPUART1_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA03         ||PA11         ||PB03         ||*/

/**
 * @brief GPIO 端口配置结构体定义
 */
typedef struct
{
    boolean_t           bOutputVal;      /*!< 默认端口输出电平 */
    en_gpio_dir_t       enDir;           /*!< 端口方向配置 */
    en_gpio_drv_t       enDrv;           /*!< 端口驱动能力配置 */
    en_gpio_pu_t        enPu;            /*!< 端口上拉配置 */
    en_gpio_pd_t        enPd;            /*!< 端口下拉配置 */
    en_gpio_od_t        enOD;            /*!< 端口开漏输出配置 */
}stc_gpio_cfg_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Macros GPIO全局宏定义
 * @{
 */


/**
 * @brief GPIO PORT类型定义 GPIO_PORTs_define
 */
#define  GpioPortA   HC_GPIOA             /*!< GPIO PORT A */
#define  GpioPortB   HC_GPIOB             /*!< GPIO PORT B */
#define  GpioPortC   HC_GPIOC             /*!< GPIO PORT C */
#define  GpioPortD   HC_GPIOD             /*!< GPIO PORT D */


/**
 * @defgroup GPIO 复用功能定义
 * @{
 */

/**
 * @defgroup GPIO_AF1 复用功能1
 * @{
 */
#define PA00_USART1_CTS       GpioAf1
#define PA01_USART1_RTS       GpioAf1
#define PA02_USART1_TXD       GpioAf1
#define PA03_USART1_RXD       GpioAf1
#define PA04_SPI0_CS          GpioAf1
#define PA05_SPI0_SCK         GpioAf1
#define PA06_SPI0_MISO        GpioAf1
#define PA07_SPI0_MOSI        GpioAf1
#define PA08_USART0_SCK       GpioAf1
#define PA09_USART0_TXD       GpioAf1
#define PA10_USART0_RXD       GpioAf1
#define PA11_USART0_CTS       GpioAf1
#define PA12_USART0_RTS       GpioAf1
#define PA13_USART1_SCK       GpioAf1
#define PA14_USART1_TXD       GpioAf1
#define PA15_SPI0_CS          GpioAf1
#define PB00_CTIM0_CH2        GpioAf1
#define PB01_CTIM0_CH3        GpioAf1
#define PB02_LPTIM_TOG        GpioAf1
#define PB03_SPI0_SCK         GpioAf1
#define PB04_SPI0_MISO        GpioAf1
#define PB05_SPI0_MOSI        GpioAf1
#define PB06_I2C0_SCL         GpioAf1
#define PB07_I2C0_SDA         GpioAf1
#define PB08_I2C0_SCL         GpioAf1
#define PB09_I2C0_SDA         GpioAf1
#define PB10_I2C1_SCL         GpioAf1
#define PB11_I2C1_SDA         GpioAf1
#define PB12_SPI1_CS          GpioAf1
#define PB13_SPI1_SCK         GpioAf1
#define PB14_SPI1_MISO        GpioAf1
#define PB15_SPI1_MOSI        GpioAf1
#define PC13_CTIM1_ETR        GpioAf1
#define PC14_CTIM1_CH0        GpioAf1
#define PC15_CTIM1_CH0        GpioAf1
#define PD00_I2C0_SDA         GpioAf1
#define PD01_I2C0_SCL         GpioAf1
#define PD03_1x               GpioAf1
#define PD06_I2C1_SCL         GpioAf1
#define PD07_I2C1_SDA         GpioAf1
/**
 * @}
 */
/**
 * @defgroup GPIO_AF2 复用功能2
 * @{
 */
#define PA00_LPUART1_TXD      GpioAf2
#define PA01_LPUART1_RXD      GpioAf2
#define PA02_ATIM0_CHA        GpioAf2
#define PA03_ATIM0_GATE       GpioAf2
#define PA04_USART1_SCK       GpioAf2
#define PA05_ATIM0_ETR        GpioAf2
#define PA06_CTIM0_CH0        GpioAf2
#define PA07_CTIM0_CH1        GpioAf2
#define PA08_ATIM3_CH0A       GpioAf2
#define PA09_ATIM3_CH1A       GpioAf2
#define PA10_ATIM3_CH2A       GpioAf2
#define PA11_ATIM3_GATE       GpioAf2
#define PA12_ATIM3_ETR        GpioAf2
#define PA13_USART0_RXD       GpioAf2
#define PA14_USART0_TXD       GpioAf2
#define PA15_USART1_RXD       GpioAf2
#define PB00_CTIM1_TOGN       GpioAf2
#define PB01_PCLK_OUT         GpioAf2
#define PB02_CTIM0_ETR        GpioAf2
#define PB03_ATIM0_CHB        GpioAf2
#define PB04_CTIM0_CH0        GpioAf2
#define PB05_ATIM3_BK         GpioAf2
#define PB06_USART0_TXD       GpioAf2
#define PB07_USART0_RXD       GpioAf2
#define PB08_ATIM1_CHA        GpioAf2
#define PB09_USART0_SCK       GpioAf2
#define PB10_SPI1_SCK         GpioAf2
#define PB11_ATIM1_CHB        GpioAf2
#define PB12_ATIM3_BK         GpioAf2
#define PB13_I2C1_SCL         GpioAf2
#define PB14_I2C1_SDA         GpioAf2
#define PB15_ATIM3_CH2B       GpioAf2
#define PC13_RTC_1HZ          GpioAf2
#define PC14_CTIM0_TOGN       GpioAf2
#define PC15_2x               GpioAf2
#define PD00_CTRIM_ETRTOG     GpioAf2
#define PD01_ATIM3_CH0B       GpioAf2
#define PD03_2x               GpioAf2
#define PD06_LPUART1_CTS      GpioAf2
#define PD07_LPUART1_RTS      GpioAf2
/**
 * @}
 */
/**
 * @defgroup GPIO_AF3 复用功能3
 * @{
 */
#define PA00_ATIM0_ETR        GpioAf3
#define PA01_ATIM0_CHB        GpioAf3
#define PA02_VC1_OUT          GpioAf3
#define PA03_ATIM1_CHB        GpioAf3
#define PA04_CTIM1_CH0        GpioAf3
#define PA05_CTIM0_ETR        GpioAf3
#define PA06_ATIM3_BK         GpioAf3
#define PA07_HCLK_OUT         GpioAf3
#define PA08_USART0_TXD       GpioAf3
#define PA09_ATIM0_BK         GpioAf3
#define PA10_ATIM2_BK         GpioAf3
#define PA11_I2C1_SCL         GpioAf3
#define PA12_I2C1_SDA         GpioAf3
#define PA13_LVD_OUT          GpioAf3
#define PA14_ATIM3_CH2A       GpioAf3
#define PA15_LPUART1_RTS      GpioAf3
#define PB00_LPUART0_TXD      GpioAf3
#define PB01_I2CSLV_SDA       GpioAf3
#define PB02_LPUART1_TXD      GpioAf3
#define PB03_ATIM1_GATE       GpioAf3
#define PB04_ATIM2_BK         GpioAf3
#define PB05_ATIM1_BK         GpioAf3
#define PB06_ATIM1_CHB        GpioAf3
#define PB07_ATIM2_CHB        GpioAf3
#define PB08_CAN_RX           GpioAf3
#define PB09_SPI1_CS          GpioAf3
#define PB10_ATIM1_CHA        GpioAf3
#define PB11_LPUART0_RXD      GpioAf3
#define PB12_LPUART0_TXD      GpioAf3
#define PB13_ATIM3_CH0B       GpioAf3
#define PB14_ATIM3_CH1B       GpioAf3
#define PB15_ATIM0_CHB        GpioAf3
#define PC13_ATIM3_CH1B       GpioAf3
#define PC14_LVD_OUT          GpioAf3
#define PC15_3x               GpioAf3
#define PD00_USART1_TXD       GpioAf3
#define PD01_USART1_RXD       GpioAf3
#define PD03_3x               GpioAf3
#define PD06_USART0_CTS       GpioAf3
#define PD07_USART0_RTS       GpioAf3
/**
 * @}
 */
/**
 * @defgroup GPIO_AF4 复用功能4
 * @{
 */
#define PA00_VC0_OUT          GpioAf4
#define PA01_ATIM1_ETR        GpioAf4
#define PA02_ATIM1_CHA        GpioAf4
#define PA03_ATIM2_CHB        GpioAf4
#define PA04_ATIM2_ETR        GpioAf4
#define PA05_ATIM0_CHA        GpioAf4
#define PA06_ATIM1_CHA        GpioAf4
#define PA07_ATIM3_CH2A       GpioAf4
#define PA08_CAN_STBY         GpioAf4
#define PA09_I2C0_SCL         GpioAf4
#define PA10_I2C0_SDA         GpioAf4
#define PA11_CAN_TX           GpioAf4
#define PA12_CAN_RX           GpioAf4
#define PA13_ATIM3_ETR        GpioAf4
#define PA14_LVD_OUT          GpioAf4
#define PA15_ATIM0_ETR        GpioAf4
#define PB00_ATIM3_CH2B       GpioAf4
#define PB01_ATIM3_CH1B       GpioAf4
#define PB02_ATIM3_CH0B       GpioAf4
#define PB03_ATIM3_CH0A       GpioAf4
#define PB04_USART0_CTS       GpioAf4
#define PB05_CTIM0_CH1        GpioAf4
#define PB06_ATIM0_CHA        GpioAf4
#define PB07_LPUART1_CTS      GpioAf4
#define PB08_ATIM2_CHA        GpioAf4
#define PB09_ATIM2_CHA        GpioAf4
#define PB10_LPUART0_TXD      GpioAf4
#define PB11_ATIM2_GATE       GpioAf4
#define PB12_ATIM0_BK         GpioAf4
#define PB13_LPUART0_CTS      GpioAf4
#define PB14_ATIM0_CHA        GpioAf4
#define PB15_ATIM0_GATE       GpioAf4
#define PC13_CTIM0_TOG        GpioAf4
#define PC14_4x               GpioAf4
#define PC15_4x               GpioAf4
#define PD00_CTIM1_CH2        GpioAf4
#define PD01_CTIM1_CH3        GpioAf4
#define PD03_4x               GpioAf4
#define PD06_RTC_OUT          GpioAf4
#define PD07_RTC_TS           GpioAf4
/**
 * @}
 */
/**
 * @defgroup GPIO_AF5 复用功能5
 * @{
 */
#define PA00_ATIM1_CHA        GpioAf5
#define PA01_ATIM1_CHB        GpioAf5
#define PA02_ATIM2_CHA        GpioAf5
#define PA03_SPI1_CS          GpioAf5
#define PA04_ATIM3_CH1A       GpioAf5
#define PA05_ATIM3_CH1B       GpioAf5
#define PA06_VC0_OUT          GpioAf5
#define PA07_ATIM2_CHA        GpioAf5
#define PA08_ATIM1_GATE       GpioAf5
#define PA09_MCO_OUT          GpioAf5
#define PA10_ATIM2_GATE       GpioAf5
#define PA11_VC0_OUT          GpioAf5
#define PA12_VC1_OUT          GpioAf5
#define PA13_RTC_1HZ          GpioAf5
#define PA14_RCH_OUT          GpioAf5
#define PA15_ATIM0_CHA        GpioAf5
#define PB00_RCH_OUT          GpioAf5
#define PB01_LPUART0_RTS      GpioAf5
#define PB02_ATIM1_BK         GpioAf5
#define PB03_LPTIM_GATE       GpioAf5
#define PB04_ATIM2_GATE       GpioAf5
#define PB05_LPTIM_GATE       GpioAf5
#define PB06_LPTIM_ETR        GpioAf5
#define PB07_ATIM0_CHB        GpioAf5
#define PB08_ATIM0_GATE       GpioAf5
#define PB09_CAN_TX           GpioAf5
#define PB10_ATIM3_CH2A       GpioAf5
#define PB11_ATIM3_CH1A       GpioAf5
#define PB12_5x               GpioAf5
#define PB13_ATIM1_CHA        GpioAf5
#define PB14_ATIM3_CH2A       GpioAf5
#define PB15_RTC_1HZ          GpioAf5
#define PC13_5x               GpioAf5
#define PC14_5x               GpioAf5
#define PC15_5x               GpioAf5
#define PD00_I2CSLV_SCL       GpioAf5
#define PD01_I2CSLV_SDA       GpioAf5
#define PD03_5x               GpioAf5
#define PD06_ATIM3_BK         GpioAf5
#define PD07_ATIM3_ETR        GpioAf5
/**
 * @}
 */
/**
 * @defgroup GPIO_AF6 复用功能6
 * @{
 */
#define PA00_ATIM3_ETR        GpioAf6
#define PA01_HCLK_OUT         GpioAf6
#define PA02_ATIM3_CH0A       GpioAf6
#define PA03_ATIM3_CH0B       GpioAf6
#define PA04_USART1_TXD       GpioAf6
#define PA05_XTL_OUT          GpioAf6
#define PA06_ATIM3_GATE       GpioAf6
#define PA07_VC1_OUT          GpioAf6
#define PA08_CTIM0_TOGN       GpioAf6
#define PA09_HCLK_OUT         GpioAf6
#define PA10_PCLK_OUT         GpioAf6
#define PA11_SPI0_MISO        GpioAf6
#define PA12_SPI0_MOSI        GpioAf6
#define PA13_CTIM1_CH1        GpioAf6
#define PA14_RCL_OUT          GpioAf6
#define PA15_ATIM3_CH1A       GpioAf6
#define PB00_RCL_OUT          GpioAf6
#define PB01_LPTIM_TOGN       GpioAf6
#define PB02_ATIM0_BK         GpioAf6
#define PB03_XTL_OUT          GpioAf6
#define PB04_ATIM3_CH0B       GpioAf6
#define PB05_CTRIM_ETRTOG     GpioAf6
#define PB06_ATIM3_CH0A       GpioAf6
#define PB07_LPTIM_TOGN       GpioAf6
#define PB08_ATIM3_CH2A       GpioAf6
#define PB09_ATIM2_CHB        GpioAf6
#define PB10_LPUART1_RTS      GpioAf6
#define PB11_LPUART1_CTS      GpioAf6
#define PB12_LPUART0_RTS      GpioAf6
#define PB13_ATIM1_GATE       GpioAf6
#define PB14_LPUART0_RTS      GpioAf6
#define PB15_CTIM0_TOG        GpioAf6
#define PC13_6x               GpioAf6
#define PC14_6x               GpioAf6
#define PC15_6x               GpioAf6
#define PD00_6x               GpioAf6
#define PD01_6x               GpioAf6
#define PD03_6x               GpioAf6
#define PD06_CTIM1_CH2        GpioAf6
#define PD07_CTIM1_CH3        GpioAf6
/**
 * @}
 */
/**
 * @defgroup GPIO_AF7 复用功能7
 * @{
 */
#define PA00_ATIM0_CHA        GpioAf7
#define PA01_SPI1_MOSI        GpioAf7
#define PA02_SPI1_MISO        GpioAf7
#define PA03_PCLK_OUT         GpioAf7
#define PA04_I2CSLV_SCL       GpioAf7
#define PA05_XTH_OUT          GpioAf7
#define PA06_LPUART0_CTS      GpioAf7
#define PA07_CTIM1_TOG        GpioAf7
#define PA08_ATIM3_BK         GpioAf7
#define PA09_I2CSLV_SCL       GpioAf7
#define PA10_I2CSLV_SDA       GpioAf7
#define PA11_ATIM3_CH1B       GpioAf7
#define PA12_CTIM1_ETR        GpioAf7
#define PA13_CTRIM_ETRTOG     GpioAf7
#define PA14_PLL_OUT          GpioAf7
#define PA15_CAN_STBY         GpioAf7
#define PB00_PLL_OUT          GpioAf7
#define PB01_USART0_SCK       GpioAf7
#define PB02_ATIM2_BK         GpioAf7
#define PB03_XTH_OUT          GpioAf7
#define PB04_LPTIM_ETR        GpioAf7
#define PB05_USART0_RTS       GpioAf7
#define PB06_LPTIM_TOG        GpioAf7
#define PB07_ATIM3_ETR        GpioAf7
#define PB08_USART0_TXD       GpioAf7
#define PB09_USART0_RXD       GpioAf7
#define PB10_USART1_RTS       GpioAf7
#define PB11_USART1_CTS       GpioAf7
#define PB12_ATIM3_CH0A       GpioAf7
#define PB13_7x               GpioAf7
#define PB14_ATIM1_BK         GpioAf7
#define PB15_LPUART1_RXD      GpioAf7
#define PC13_7x               GpioAf7
#define PC14_7x               GpioAf7
#define PC15_7x               GpioAf7
#define PD00_7x               GpioAf7
#define PD01_7x               GpioAf7
#define PD03_7x               GpioAf7
#define PD06_7x               GpioAf7
#define PD07_7x               GpioAf7
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
 * Local type definitions ('typedef')
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/


/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup GPIO_Global_Functions GPIO全局函数定义
 * @{
 */
en_result_t Gpio_Init(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, stc_gpio_cfg_t *pstcGpioCfg);
boolean_t   Gpio_GetInputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
uint16_t    Gpio_GetInputData(GPIO_TypeDef *GPIOx);
en_result_t Gpio_WriteOutputPort(GPIO_TypeDef *GPIOx, uint16_t u16Val);
boolean_t   Gpio_ReadOutputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SetPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk);
en_result_t Gpio_SetIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_ClrPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk);
en_result_t Gpio_ClrIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SetClrPort(GPIO_TypeDef *GPIOx, uint32_t u32ValMsk);
en_result_t Gpio_SetAnalogMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SetAfMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_af_t enAf);
en_result_t Gpio_EnableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
en_result_t Gpio_DisableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
boolean_t   Gpio_GetIrqStatus(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_ClearIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_div_t enDiv);
en_result_t Gpio_SfMcoOutputCfg(en_gpio_sf_mco_src_t ensrc,en_gpio_sf_mcoout_div_t endiv);
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
/**
 * @}
 */



/**
 * @}
 */

/**
 * @}
 */




/*****************************************************************************
 * Include files
 *****************************************************************************/



/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_GTIM GTIM模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup GTIM_Global_Types GTIM全局类型定义
 * @{
 */

/**
 * @brief GTIMx 初始化配置的结构体
 */
typedef struct
{
    uint32_t       u32TaskMode;        /*!< 计数模式：连续计数模式或单次计数模式 */
    uint32_t       u32WorkMode;        /*!< 工作模式：内部时钟计数、外部输入计数、触发模式、门控模式 */
    uint32_t       u32Prescaler;       /*!< 计数器输入信号分频 */
    uint32_t       u32ToggleEn;        /*!< Toggle_N和Toggle_P输出使能 */
    uint32_t       u32TriggerSource;   /*!< 触发源选择，外部管脚ETR或者上一级BTIM溢出 */
    uint32_t       u32ExInputPolarity; /*!< 外部输入极性选择 */
    uint32_t       u32AutoReloadVal;   /*!< 配置重载寄存器的值 */
}stc_gtim_init_t;

/**
 * @}
 */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup GTIM_Global_Macros GTIM全局宏定义
 * @{
 */

/** @defgroup Gtim_Task_Count_Mode u32TaskMode (OST)
  * @{
  */
#define  GTIM_TASK_MODE_CONTINUOUS_COUNTER     (0x00000000UL)     /*!< 连续计数模式 */
#define  GTIM_TASK_MODE_ONESHOT_COUNTER        (GTIM_CR0_OST)     /*!< 单次计数模式 */
/**
  * @}
  */


/** @defgroup Gtim_Work_Mode u32CounterMode (MD)
  * @{
  */
#define  GTIM_WORK_MODE_PCLK           (0x00000000UL)               /*!< GTIM 内部时钟计数模式 */
#define  GTIM_WORK_MODE_EXTERNAL       (0x1 << GTIM_CR0_MD_Pos)     /*!< GTIM 外部输入计数模式 */
#define  GTIM_WORK_MODE_TRIGGER        (0x2 << GTIM_CR0_MD_Pos)     /*!< GTIM 触发模式 */
#define  GTIM_WORK_MODE_GATE           (GTIM_CR0_MD)                /*!< GTIM 门控模式  */
/**
  * @}
  */


/** @defgroup Gtim_Clock_Divide u32Prescaler (PRS)
  * @{
  */
#define  GTIM_COUNTER_CLK_DIV1        (0x00000000UL)            /*!<GTIM  Div 1*/
#define  GTIM_COUNTER_CLK_DIV2        (0x1 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 2*/
#define  GTIM_COUNTER_CLK_DIV4        (0x2 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 4*/
#define  GTIM_COUNTER_CLK_DIV8        (0x3 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 8*/
#define  GTIM_COUNTER_CLK_DIV16       (0x4 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 16*/
#define  GTIM_COUNTER_CLK_DIV32       (0x5 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 32*/
#define  GTIM_COUNTER_CLK_DIV64       (0x6 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 64*/
#define  GTIM_COUNTER_CLK_DIV128      (0x7 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 128*/
#define  GTIM_COUNTER_CLK_DIV256      (0x8 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 256*/
#define  GTIM_COUNTER_CLK_DIV512      (0x9 << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 512*/
#define  GTIM_COUNTER_CLK_DIV1024     (0xA << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 1024*/
#define  GTIM_COUNTER_CLK_DIV2048     (0xB << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 2048*/
#define  GTIM_COUNTER_CLK_DIV4096     (0xC << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 4096*/
#define  GTIM_COUNTER_CLK_DIV8192     (0xD << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 8192*/
#define  GTIM_COUNTER_CLK_DIV16384    (0xE << GTIM_CR0_PRS_Pos) /*!<GTIM  Div 16384*/
#define  GTIM_COUNTER_CLK_DIV32768    (GTIM_CR0_PRS)            /*!<GTIM  Div 32768*/
/**
  * @}
  */


/** @defgroup Gtim_Tog_Ouput_define u32ToggleEn (TOGEN)
  * @{
  */
#define  GTIM_TOGGLE_DISABLE        (0x00000000UL)      /*!< TOGP、TOGN输出电平都为0 */
#define  GTIM_TOGGLE_ENABLE         (GTIM_CR0_TOGEN)    /*!< TOGP、TOGN输出电平相反的信号 */
/**
  * @}
  */


/** @defgroup Gtim_Trigger_Source_Sel u32TriggerSource (TRS)
  * @{
  */
#define  GTIM_TRIGGER_SOURCE_ETR           (0x00000000UL)               /*!< ETR管脚输入的信号 */
#define  GTIM_TRIGGER_SOURCE_ITR1          (0x1 << GTIM_CR0_TRS_Pos)    /*!< ITR1内部互联信号 */
#define  GTIM_TRIGGER_SOURCE_ITR2          (0x2 << GTIM_CR0_TRS_Pos)    /*!< ITR2内部互联信号 */
#define  GTIM_TRIGGER_SOURCE_ITR3          (GTIM_CR0_TRS)               /*!< ITR3内部互联信号 */
/**
  * @}
  */

/** @defgroup Gtim_ETR_Input_Polarity u32ExInputPolarity (ETP)
  * @{
  */
#define  GTIM_ETR_POLARITY_NORMAL            (0x00000000UL)  /*!< 外部输入ETR不反向(触发模式上沿触发，门控模式低电平停止计数) */
#define  GTIM_ETR_POLARITY_INVERTED          (GTIM_CR0_ETP)  /*!< 外部输入ETR反向(触发模式下沿触发，门控模式高电平停止计数) */
/**
  * @}
  */


/** @defgroup Gtim_ETP_External_Input_Filter u32ExInputFilter (ETRFLT)
  * @{
  */
#define  GTIM_ETR_FLT_NONE                (0x00000000UL)                 /*!< ETR输入无滤波 */
#define  GTIM_ETR_FLT_PCLK_DIV1_CYCLE2    (0x1 << GTIM_CR1_ETRFLT_Pos)   /*!< ETR输入滤波时钟PCLK，采样点个数2*/
#define  GTIM_ETR_FLT_PCLK_DIV1_CYCLE4    (0x2 << GTIM_CR1_ETRFLT_Pos)   /*!< ETR输入滤波时钟PCLK，采样点个数4*/
#define  GTIM_ETR_FLT_PCLK_DIV1_CYCLE6    (0x3 << GTIM_CR1_ETRFLT_Pos)   /*!< ETR输入滤波时钟PCLK，采样点个数6*/
#define  GTIM_ETR_FLT_PCLK_DIV4_CYCLE4    (0x4 << GTIM_CR1_ETRFLT_Pos)   /*!< ETR输入滤波时钟PCLK/4，采样点个数4*/
#define  GTIM_ETR_FLT_PCLK_DIV4_CYCLE6    (0x5 << GTIM_CR1_ETRFLT_Pos)   /*!< ETR输入滤波时钟PCLK/4，采样点个数6*/
#define  GTIM_ETR_FLT_PCLK_DIV16_CYCLE4   (0x6 << GTIM_CR1_ETRFLT_Pos)   /*!< ETR输入滤波时钟PCLK/16，采样点个数4*/
#define  GTIM_ETR_FLT_PCLK_DIV16_CYCLE6   (GTIM_CR1_ETRFLT)              /*!< ETR输入滤波时钟PCLK/16，采样点个数6*/
/**
  * @}
  */


/** @defgroup Gtim_Capture_Compare_Channel_Sel u32Channel u32Mode (CCMR)
  * @{
  */
#define  GTIM_COMPARE_CAPTURE_CH0                  0u    /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
#define  GTIM_COMPARE_CAPTURE_CH1                  4u    /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
#define  GTIM_COMPARE_CAPTURE_CH2                  8u    /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
#define  GTIM_COMPARE_CAPTURE_CH3                  12u   /*!< GTIM_CCR相对于CC0M的bit偏移位置 */
/**
  * @}
  */

/** @defgroup Gtim_Capture_Compare_Mode_Config u32Channel u32Mode (CCMR)
  * @{
  */
#define  GTIM_COMPARE_CAPTURE_NONE                 (0x00000000UL)               /*!< 无功能 */
#define  GTIM_COMPARE_CAPTURE_RISING               (0x1 << GTIM_CMMR_CC0M_Pos)  /*!< 上升沿捕获 */
#define  GTIM_COMPARE_CAPTURE_FALLING              (0x2 << GTIM_CMMR_CC0M_Pos)  /*!< 下降沿捕获 */
#define  GTIM_COMPARE_CAPTURE_RISING_FALLING       (0x3 << GTIM_CMMR_CC0M_Pos)  /*!< 上下沿同时捕获 */
#define  GTIM_COMPARE_CAPTURE_FORCE_LOW_LEVEL      (0x4 << GTIM_CMMR_CC0M_Pos)  /*!< 强制输出低电平 */
#define  GTIM_COMPARE_CAPTURE_FORCE_HIGH_LEVEL     (0x5 << GTIM_CMMR_CC0M_Pos)  /*!< 强制输出高电平 */
#define  GTIM_COMPARE_CAPTURE_PWM_NORMAL           (0x6 << GTIM_CMMR_CC0M_Pos)  /*!< PWM正向输出(CNT >= CCR0输出高电平)  */
#define  GTIM_COMPARE_CAPTURE_PWM_INVERTED         (GTIM_CMMR_CC0M)             /*!< PWM反向输出(CNT < CCR输出高电平) */
/**
  * @}
  */


/** @defgroup Gtim_Interrupt_TRIG_Enable_Disable (IER)
  * @{
  */
#define GTIM_IT_UI          (GTIM_IER_UI)       /*!< 溢出中断使能控制 */
#define GTIM_IT_TI          (GTIM_IER_TI)       /*!< 触发中断使能控制 */
#define GTIM_IT_CC0         (GTIM_IER_CC0)      /*!< GTIM捕获比较0中断使能控制 */
#define GTIM_IT_CC1         (GTIM_IER_CC1)      /*!< GTIM捕获比较1中断使能控制 */
#define GTIM_IT_CC2         (GTIM_IER_CC2)      /*!< GTIM捕获比较2中断使能控制 */
#define GTIM_IT_CC3         (GTIM_IER_CC3)      /*!< GTIM捕获比较3中断使能控制 */
#define GTIM_CC0_TRIG_DMA   (GTIM_IER_DCC0)     /*!< GTIM CH0触发DMA使能*/
#define GTIM_CC1_TRIG_DMA   (GTIM_IER_DCC1)     /*!< GTIM CH1触发DMA使能 */
#define GTIM_CC2_TRIG_DMA   (GTIM_IER_DCC2)     /*!< GTIM CH2触发DMA使能 */
#define GTIM_CC3_TRIG_DMA   (GTIM_IER_DCC3)     /*!< GTIM CH3触发DMA使能 */
#define GTIM_OV_TRIG_ADC    (GTIM_IER_OVTRAD)   /*!< GTIM 溢出触发ADC使能 */
#define GTIM_CC0_TRIG_ADC   (GTIM_IER_C0TRAD)   /*!< GTIM CH0触发ADC使能 */
/**
  * @}
  */


/** @defgroup Gtim_Interrupt_Flag (IFR)
  * @{
  */
#define GTIM_IT_FLAG_UI       (GTIM_IFR_UI)      /*!< 溢出中断标志 */
#define GTIM_IT_FLAG_TI       (GTIM_IFR_TI)      /*!< 触发中断标志 */
#define GTIM_IT_FLAG_CC0      (GTIM_IFR_CC0)     /*!< GTIM捕获比较0中断标志 */
#define GTIM_IT_FLAG_CC1      (GTIM_IFR_CC1)     /*!< GTIM捕获比较1中断标志 */
#define GTIM_IT_FLAG_CC2      (GTIM_IFR_CC2)     /*!< GTIM捕获比较2中断标志 */
#define GTIM_IT_FLAG_CC3      (GTIM_IFR_CC3)     /*!< GTIM捕获比较3中断标志 */
/**
  * @}
  */


/** @defgroup Gtim_Interrupt_Clear_Types (ICR)
  * @{
  */
#define GTIM_IT_CLR_UI        (GTIM_ICR_UI)    /*!< 清除溢出中断标志 */
#define GTIM_IT_CLR_TI        (GTIM_ICR_TI)    /*!< 清除触发中断标志 */
#define GTIM_IT_CLR_CC0       (GTIM_ICR_CC0)   /*!< 清除GTIM捕获比较0中断标志 */
#define GTIM_IT_CLR_CC1       (GTIM_ICR_CC1)   /*!< 清除GTIM捕获比较1中断标志 */
#define GTIM_IT_CLR_CC2       (GTIM_ICR_CC2)   /*!< 清除GTIM捕获比较2中断标志 */
#define GTIM_IT_CLR_CC3       (GTIM_ICR_CC3)   /*!< 清除GTIM捕获比较3中断标志 */
/**
  * @}
  */

/**
 * @}
 */
/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup GTIM_Global_Functions GTIM全局函数定义
 * @{
 */
en_result_t Gtim_Init(GTIM_TypeDef* GTIMx, stc_gtim_init_t* pstcInitCfg);
void Gtim_SetCounter(GTIM_TypeDef* GTIMx, uint16_t u16CntValue);
uint32_t Gtim_GetCounter(GTIM_TypeDef* GTIMx);
void Gtim_SetAutoReload(GTIM_TypeDef* GTIMx, uint16_t u16AutoReload);
uint32_t Gtim_GetAutoReload(GTIM_TypeDef* GTIMx);
void Gtim_Enable(GTIM_TypeDef* GTIMx);
void Gtim_Disable(GTIM_TypeDef* GTIMx);
boolean_t Gtim_IsEnable(GTIM_TypeDef* GTIMx);
void Gtim_SetWorkMode(GTIM_TypeDef* GTIMx, uint32_t u32WorkMode);
uint32_t Gtim_GetWorkMode(GTIM_TypeDef* GTIMx);
void Gtim_EnableToggle(GTIM_TypeDef* GTIMx);
void Gtim_DisableToggle(GTIM_TypeDef* GTIMx);
boolean_t Gtim_IsEnableToggle(GTIM_TypeDef* GTIMx);
void Gtim_SetCounterClkDiv(GTIM_TypeDef* GTIMx, uint32_t u32CounterClkDiv);
uint32_t Gtim_GetCounterClkDiv(GTIM_TypeDef* GTIMx);
void Gtim_SetTaskMode(GTIM_TypeDef* GTIMx, uint32_t u32Mode);
uint32_t Gtim_GetTaskMode(GTIM_TypeDef* GTIMx);
void Gtim_SetTriggerSource(GTIM_TypeDef* GTIMx, uint32_t u32TriggerSource);
uint32_t Gtim_GetTriggerSource(GTIM_TypeDef* GTIMx);
void Gtim_SetExInputPolarity(GTIM_TypeDef* GTIMx, uint32_t u32ExInputPolarity);
uint32_t Gtim_GetExInputPolarity(GTIM_TypeDef* GTIMx);
void Gtim_SetExInputFilter(GTIM_TypeDef* GTIMx, uint32_t u32ExInputFilter);
uint32_t Gtim_GetExInputFilter(GTIM_TypeDef* GTIMx);
void Gtim_SetCompareCaptureMode(GTIM_TypeDef* GTIMx, uint32_t u32Channel, uint32_t u32CaptureMode);
uint32_t Gtim_GetCompareCaptureMode(GTIM_TypeDef* GTIMx, uint32_t u32Channel);
void Gtim_SetCompareCaptureReg(GTIM_TypeDef* GTIMx, uint32_t u32Channel, uint32_t u32Capture);
uint32_t Gtim_GetCompareCaptureReg(GTIM_TypeDef* GTIMx, uint32_t u32Channel);
void Gtim_DisableCompareCaptureAll(GTIM_TypeDef* GTIMx);
void Gtim_EnableIT(GTIM_TypeDef* GTIMx, uint32_t u32IT);
void Gtim_DisableIT(GTIM_TypeDef* GTIMx, uint32_t u32IT);
boolean_t Gtim_IsEnableIT(GTIM_TypeDef* GTIMx, uint32_t u32IntEnableTypes);
boolean_t Gtim_IsActiveFlag(GTIM_TypeDef* GTIMx, uint32_t u32IntFlagTypes);
void Gtim_ClearFlag(GTIM_TypeDef* GTIMx, uint32_t u32IntClrFlag);
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
 * Include files
 ******************************************************************************/


/* C binding of definitions if building with C++ compiler */

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_I2C I2C模块驱动库
 * @{
 */




/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup I2C_Global_Types I2C全局类型定义
 * @{
 */

/**
 * @brief  I2C功能配置
 */
typedef enum
{
    I2cModule_En = 6u,  /*!<  I2C模块使能 */
    I2cStart_En  = 5u,  /*!<  开始信号 */
    I2cStop_En   = 4u,  /*!<  结束信号 */
    I2cAck_En    = 2u,  /*!<  应答信号 */
    I2cHlm_En    = 0u,  /*!<  高速使能 */
}en_i2c_func_t;

/**
 * @brief  I2C模式配置
 */
typedef enum
{
    I2cMasterMode = 0x40u,  /*!<  I2C主机模式 */
    I2cSlaveMode  = 0x44u,  /*!<  I2C从机模式 */
}en_i2c_mode_t;

/**
 * @brief  I2C初始化配置结构
 */
typedef struct
{
    uint32_t        u32Pclk;        /*!<  Pclk 设置(Hz) */
    uint32_t        u32Baud;        /*!<  I2C通信波特率(Hz) */
    en_i2c_mode_t   enMode;         /*!<  I2C主从模式配置 */
    uint8_t         u8SlaveAddr;    /*!<  从机地址配置(如果需要) */
    boolean_t       bGc;            /*!<  广播地址使能(如果需要) */
}stc_i2c_cfg_t;

/**
 * @}
 */
/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup I2C_Global_Functions I2C全局函数定义
 * @{
 */

 en_result_t I2C_Init(I2C_TypeDef* I2Cx,stc_i2c_cfg_t *pstcI2CCfg);
 en_result_t I2C_SetFunc(I2C_TypeDef* I2Cx,en_i2c_func_t enFunc);
 en_result_t I2C_ClearFunc(I2C_TypeDef* I2Cx,en_i2c_func_t enFunc);
 boolean_t I2C_GetIrq(I2C_TypeDef* I2Cx);
 en_result_t I2C_ClearIrq(I2C_TypeDef* I2Cx);
 uint8_t I2C_GetState(I2C_TypeDef* I2Cx);
 en_result_t I2C_WriteByte(I2C_TypeDef* I2Cx,uint8_t u8Data);
uint8_t I2C_ReadByte(I2C_TypeDef* I2Cx);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */




/* C binding of definitions if building with C++ compiler */

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_I2CSLV I2CSLV模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup I2CSLV_Global_Types I2CSLV全局类型定义
 * @{
 */
/**
 * @brief I2C从机初始化配置结构
 */
typedef struct
{
    uint32_t        u32Filter;              /*!<  滤波配置  @ref I2CSLV_FILTER_SELECTION */
    uint32_t        u32RxSampleDot;         /*!<  接收采样位置配置  @ref I2CSLV_RX_SAMPLE_DOT_SELECTION */
    uint32_t        u32DriveStrength;       /*!<  SDA由0变1时驱动能力配置  @ref I2CSLV_HIGH_DRIVE_SELECTION */
    uint32_t        u32AddrClkForceStretch; /*!<  地址时钟强制延长配置  @ref I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION */
    uint32_t        u32TimeOut;             /*!<  SCL低电平超时配置  超时长度=(u32TimeOut+1)*64*(1/PCLK),详见文档 */
    uint32_t        u32Broadcast;           /*!<  广播地址配置  @ref I2CSLV_BROADCAST_SELECTION */
    uint32_t        u32DMAReq;              /*!<  DMA请求使能配置  @ref I2CSLV_DMA_REQUEST_SELECTION */
    uint32_t        u32HSMODE;              /*!<  高速模式配置  @ref I2CSLV_HIGH_SPEED_MODE_SELECTION */
    uint32_t        u32SlaveAddr0;          /*!<  从机地址0  最长有效地址10bit */
    uint32_t        u32SlaveAddr0Mask;      /*!<  从机地址0掩码  最长有效地址10bit */
    uint32_t        u32SlaveAddr1;          /*!<  从机地址1 最长有效地址10bit */
    uint32_t        u32SlaveAddr2;          /*!<  从机地址2  最长有效地址10bit */
    uint32_t        u32SlaveAddr3;          /*!<  从机地址3  最长有效地址10bit */
}stc_i2cslv_init_cfg_t;
/**
 * @}
 */

/******************************************************************************
 * Global pre-processor symbols/macros ('#define')                            *
 ******************************************************************************/
/**
 * @defgroup I2CSLV_Global_Macros I2CSLV全局宏定义
 * @{
 */

/** @defgroup Bit definition
  * @{
  */
#define  I2CSLV_RSR_NS_0                       (0x1<<I2CSLV_RSR_NS_Pos)
#define  I2CSLV_RSR_NS_1                       (0x2<<I2CSLV_RSR_NS_Pos)

#define  I2CSLV_ODDR_ODPU_0                    (0x1<<I2CSLV_ODDR_ODPU_Pos)
#define  I2CSLV_ODDR_ODPU_1                    (0x2<<I2CSLV_ODDR_ODPU_Pos)

#define  I2CSLV_FLT_FW_0                       (0x1<<I2CSLV_FLT_FW_Pos)
#define  I2CSLV_FLT_FW_1                       (0x2<<I2CSLV_FLT_FW_Pos)
#define  I2CSLV_FLT_FW_2                       (0x4<<I2CSLV_FLT_FW_Pos)
/**
  * @}
  */

/** @defgroup I2CSLV_ACK_SELECTION  从机响应配置
  * @{
  */
#define I2CSLV_ACK                              (0x00000000UL)         /*!<  从机响应主机，主机收到ACK  */
#define I2CSLV_NACK                             (I2CSLV_CR_BUSY)       /*!<  从机不响应主机，主机收到NACK  */
/**
  * @}
  */

/** @defgroup I2CSLV_HIGH_SPEED_MODE_SELECTION  高速模式控制
  * @{
  */
#define  I2CSLV_HIGH_SPEED_MODE_DISABLE         (0x00000000UL)         /*!<  标准和快速模式，I2CSLV_DOUTR没有数据时强制SCL电平延长  */
#define  I2CSLV_HIGH_SPEED_MODE_ENABLE          (I2CSLV_CR_FSCLC)      /*!<  高速模式，I2CSLV_DOUTR没有数据时不强制SCL电平延长，回复NACK  */
/**
  * @}
  */

/** @defgroup I2CSLV_BROADCAST_SELECTION  广播地址是否使能配置
  * @{
  */
#define  I2CSLV_BROADCAST_DISABLE               (0x00000000UL)   /*!<  使能I2CSLV 广播地址  */
#define  I2CSLV_BROADCAST_ENABLE                (I2CSLV_CR_GC)   /*!<  禁止I2CSLV 广播地址  */
/**
  * @}
  */

/** @defgroup I2CSLV_DMA_REQUEST_SELECTION  DMA请求选择
  * @{
  */
#define I2CSLV_DMA_REQUEST_RX_TX_DISABLE        (0x00000000UL)                       /*!<  使能I2CSLV 从机TX RX DMA请求禁止  */
#define I2CSLV_DMA_REQUEST_RX_ENABLE            (I2CSLV_CR_DMARE)                    /*!<  从机RX DMA请求使能  */
#define I2CSLV_DMA_REQUEST_TX_ENABLE            (I2CSLV_CR_DMATE)                    /*!<  从机TX DMA请求使能  */
#define I2CSLV_DMA_REQUEST_RX_TX_ENABLE         (I2CSLV_CR_DMARE | I2CSLV_CR_DMATE)  /*!<  从机TX RX DMA请求使能  */
/**
  * @}
  */

/** @defgroup I2CSLV_IT_SELECTION  中断选择
  * @{
  */
#define I2CSLV_IT_RD                    (I2CSLV_IER_RD)
#define I2CSLV_IT_WR                    (I2CSLV_IER_WR)
#define I2CSLV_IT_STOP                  (I2CSLV_IER_STOP)
#define I2CSLV_IT_START                 (I2CSLV_IER_START)
#define I2CSLV_IT_NACK                  (I2CSLV_IER_NACK)
#define I2CSLV_IT_I2CINT                (I2CSLV_IER_I2CINT)
#define I2CSLV_IT_ACTIVE                (I2CSLV_IER_ACTIVE)
#define I2CSLV_IT_HSMODE                (I2CSLV_IER_HSMODE)
#define I2CSLV_IT_TIMEOUT               (I2CSLV_IER_TIMEOUT)
#define I2CSLV_IT_ACK                   (I2CSLV_IER_ACK)
#define I2CSLV_IT_SLADDR0               (I2CSLV_IER_SLADDR0)
#define I2CSLV_IT_SLADDR1               (I2CSLV_IER_SLADDR1)
#define I2CSLV_IT_SLADDR2               (I2CSLV_IER_SLADDR2)
#define I2CSLV_IT_SLADDR3               (I2CSLV_IER_SLADDR3)
#define I2CSLV_IT_TXE                   (I2CSLV_IER_TXE)
#define I2CSLV_IT_RXNE                  (I2CSLV_IER_RXNE)
#define I2CSLV_IT_GC                    (I2CSLV_IER_GC)
/**
  * @}
  */

/** @defgroup I2CSLV_FLAG_SELECTION  中断标志位选择
  * @{
  */
#define I2CSLV_FLAG_RD                  (I2CSLV_SR_RD)
#define I2CSLV_FLAG_WR                  (I2CSLV_SR_WR)
#define I2CSLV_FLAG_STOP                (I2CSLV_SR_STOP)
#define I2CSLV_FLAG_START               (I2CSLV_SR_START)
#define I2CSLV_FLAG_NACK                (I2CSLV_SR_NACK)
#define I2CSLV_FLAG_I2CINT              (I2CSLV_SR_I2CINT)
#define I2CSLV_FLAG_ACTIVE              (I2CSLV_SR_ACTIVE)
#define I2CSLV_FLAG_HSMODE              (I2CSLV_SR_HSMODE)
#define I2CSLV_FLAG_TIMEOUT             (I2CSLV_SR_TIMEOUT)
#define I2CSLV_FLAG_ACK                 (I2CSLV_SR_ACK)
#define I2CSLV_FLAG_SLADDR0             (I2CSLV_SR_SLADDR0)
#define I2CSLV_FLAG_SLADDR1             (I2CSLV_SR_SLADDR1)
#define I2CSLV_FLAG_SLADDR2             (I2CSLV_SR_SLADDR2)
#define I2CSLV_FLAG_SLADDR3             (I2CSLV_SR_SLADDR3)
#define I2CSLV_FLAG_TXE                 (I2CSLV_SR_TXE)
#define I2CSLV_FLAG_RXNE                (I2CSLV_SR_RXNE)
#define I2CSLV_FLAG_GC                  (I2CSLV_SR_GC)
/**
  * @}
  */

/** @defgroup I2CSLV_RX_SAMPLE_DOT_SELECTION  接收采样位置选择
  * @{
  */
#define  I2CSLV_RX_SAMPLE_DOT_0CYCLE    (0x00000000UL)                      /*!<  SCL下降沿时采样  */
#define  I2CSLV_RX_SAMPLE_DOT_1CYCLE    (I2CSLV_RSR_NS_0)                   /*!<  从SCL下降沿往回计时，第1个PCLK采样  */
#define  I2CSLV_RX_SAMPLE_DOT_2CYCLE    (I2CSLV_RSR_NS_1)                   /*!<  从SCL下降沿往回计时，第2个PCLK采样  */
#define  I2CSLV_RX_SAMPLE_DOT_3CYCLE    (I2CSLV_RSR_NS_0 | I2CSLV_RSR_NS_1) /*!<  从SCL下降沿往回计时，第3个PCLK采样  */
/**
  * @}
  */

/** @defgroup I2CSLV_HIGH_DRIVE_SELECTION  强驱高电平宽度选择
  * @{
  */
#define  I2CSLV_HIGH_DRIVE_NONE         (0x00000000UL)                           /*!<  由外部上拉电阻拉高，无强驱  */
#define  I2CSLV_HIGH_DRIVE_1PCLK        (I2CSLV_ODDR_ODPU_0)                     /*!<  输出1个PCLK宽度的强驱高电平，后续由上拉电阻维持  */
#define  I2CSLV_HIGH_DRIVE_2PCLK        (I2CSLV_ODDR_ODPU_1)                     /*!<  输出2个PCLK宽度的强驱高电平，后续由上拉电阻维持  */
#define  I2CSLV_HIGH_DRIVE_4PCLK        (I2CSLV_ODDR_ODPU_0 | I2CSLV_ODDR_ODPU_1)/*!<  输出4个PCLK宽度的强驱高电平，后续由上拉电阻维持  */
/**
  * @}
  */

/** @defgroup I2CSLV_FILTER_SELECTION  滤波宽度选择
  * @{
  */
#define  I2CSLV_FILTER_NONE             (0x00000000UL)                                          /*!<  无滤波  */
#define  I2CSLV_FILTER_1PCLK            (I2CSLV_FLT_FW_0)                                       /*!<  1个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_2PCLK            (I2CSLV_FLT_FW_1)                                       /*!<  2个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_3PCLK            (I2CSLV_FLT_FW_0 | I2CSLV_FLT_FW_1)                     /*!<  3个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_4PCLK            (I2CSLV_FLT_FW_2)                                       /*!<  4个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_8PCLK            (I2CSLV_FLT_FW_0 | I2CSLV_FLT_FW_2)                     /*!<  8个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_12PCLK           (I2CSLV_FLT_FW_1 | I2CSLV_FLT_FW_2)                     /*!<  12个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_16PCLK           (I2CSLV_FLT_FW_0 | I2CSLV_FLT_FW_1 | I2CSLV_FLT_FW_2)   /*!<  16个PCLK宽度的滤波  */
/**
  * @}
  */

/** @defgroup I2CSLV_ADDR_SELECTION  从机地址号选择
  * @{
  */
#define  I2CSLV_ADDR0   0     /*!<  从机地址0  */
#define  I2CSLV_ADDR1   1     /*!<  从机地址1  */
#define  I2CSLV_ADDR2   2     /*!<  从机地址2  */
#define  I2CSLV_ADDR3   3     /*!<  从机地址3  */
/**
  * @}
  */

/** @defgroup I2CSLV_ADDR_LENGTH_SELECTION  从机地址长度选择
  * @{
  */
#define  I2CSLV_ADDR_LENGTH_7BIT        (0x00000000UL)       /*!<  7位地址长度  */
#define  I2CSLV_ADDR_LENGTH_10BIT       (I2CSLV_SLADR0_AM)   /*!<  10位地址长度  */
/**
  * @}
  */

/** @defgroup I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION  地址匹配后时钟是否强制延长设置
  * @{
  */
#define  I2CSLV_ADDR_CLOCK_FORCE_STRETCH_DISABLE    (0x00000000UL)        /*!<  地址匹配后时钟不强制SCL电平延长  */
#define  I2CSLV_ADDR_CLOCK_FORCE_STRETCH_ENABLE     (I2CSLV_ADMR0_FACS)   /*!<  地址匹配后时钟强制SCL电平延长  */
/**
  * @}
  */

/**
  * @}
  */

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup I2CSLV_Global_Functions I2CSLV全局函数定义
 * @{
 */

en_result_t I2CSLV_Init(stc_i2cslv_init_cfg_t *pstcInitCfg);
void I2CSLV_Enable(void);
void I2CSLV_Disable(void);
uint32_t I2CSLV_IsEnable(void);
void I2CSLV_SetAck(uint32_t u32Ack);
uint32_t I2CSLV_GetAck(void);
void I2CSLV_SetHsmodeForceStretch(uint32_t u32ClkForceStretch);
uint32_t I2CSLV_GetHsmodeForceStretch(void);
void I2CSLV_EnableBroadcast(void);
void I2CSLV_DisableBroadcast(void);
uint32_t I2CSLV_IsEnableBroadcast(void);
void I2CSLV_SetDMAReq(uint32_t u32DmaReq);
uint32_t I2CSLV_GetDMAReq(void);
void I2CSLV_EnableIT(uint32_t u32IrqCfg);
void I2CSLV_DisableIT(uint32_t u32IrqCfg);
uint32_t I2CSLV_IsEnableIT(uint32_t u32IrqCfg);
uint32_t I2CSLV_IsActiveFlag(uint32_t u32IrqFlag);
uint32_t I2CSLV_GetState(void);
void I2CSLV_ClearFlag(uint32_t u32IrqFlag);
void I2CSLV_ClearFlag_ALL(void);
void I2CSLV_SetFlag_TXE(void);
void I2CSLV_SetDeviceID(uint32_t u32RID, uint32_t u32PID, uint32_t u32MID);
uint32_t I2CSLV_GetDeviceID(void);
void I2CSLV_SetRxSampleDot(uint32_t u32SampleDot);
uint32_t I2CSLV_GetRxSampleDot(void);
void I2CSLV_SetDriveStrength(uint32_t u32HighDrive);
uint32_t I2CSLV_GetDriveStrength(void);
void I2CSLV_SetTimeOut(uint32_t u32TimeOver);
uint32_t I2CSLV_GetTimeOut(void);
void I2CSLV_SetFilter(uint32_t u32Filter);
uint32_t I2CSLV_GetFilter(void);
void I2CSLV_SetAddress(uint32_t u32AddrNum, uint32_t u32AddrLength, uint32_t u32Addr);
uint32_t I2CSLV_GetAddress(uint32_t u32AddrNum);
uint32_t I2CSLV_GetAddressLength(uint32_t u32AddrNum);
void I2CSLV_SetAddress0Mask(uint32_t u32Address0Mask);
uint32_t I2CSLV_GetAddress0Mask(void);
uint32_t I2CSLV_GetReceivedAddr(void);
uint32_t I2CSLV_GetReceivedAddrLength(void);
void I2CSLV_SetAddrClockForceStretch(uint32_t u32ClkForceStretch);
uint32_t I2CSLV_GetAddrClockForceStretch(void);
void I2CSLV_WriteByte(uint8_t u8Data);
uint8_t I2CSLV_ReadByte(void);
/**
  * @}
  */

/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_IWDT IWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup IWDT_Global_Types IWDT全局类型定义
 * @{
 */

/**
 * @brief  IWDT Init structure definition
 */
typedef struct
{
    uint32_t u32Action;     /*!< 看门狗休眠模式及溢出后动作配置 @ref IWDT_Action */
    uint32_t u32Prescaler;  /*!< 看门狗计数时钟(RC10K)的分频 @ref IWDT_RC32K_Prescaler */
    uint32_t u32Window;     /*!< 看门狗窗口值配置,取值范围必须为：[0u ~ 0xFFFu] */
    uint32_t u32ArrCounter; /*!< 看门狗重载计数值配置,取值范围必须为：[0u ~ 0xFFFu] */
                            /*!< u32Window < u32ArrCounter时, IWDT工作于窗口看门狗模式 */
                            /*!< u32Window ≥ u32ArrCounter时, IWDT工作于独立看门狗模式 */
} stc_iwdt_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IWDT_Global_Macros IWDT全局宏定义
 * @{
 */

/**
 * @defgroup IWDT_Action IWDT溢出中断复位选择和SleepMode下运行暂停选择
 * @{
 */
#define IWDT_OVER_INT__SLEEPMODE_STOP   (IWDT_CR_ACTION | IWDT_CR_IE | IWDT_CR_PAUSE) /*!< IWDT中断SleepMode停止 */
#define IWDT_OVER_RESET__SLEEPMODE_STOP (IWDT_CR_PAUSE)                               /*!< IWDT复位SleepMode停止 */
#define IWDT_OVER_INT__SLEEPMODE_RUN    (IWDT_CR_ACTION | IWDT_CR_IE)                 /*!< IWDT中断SleepMode运行 */
#define IWDT_OVER_RESET__SLEEPMODE_RUN  (0U)                                          /*!< IWDT复位SleepMode运行 */
/**
 * @}
 */

/** @defgroup IWDT_RC32K_Prescaler IWDT分频选择
 * @{
 */
#define IWDT_RC32K_DIV_4   (0U) /*!< RC 4分频 */
#define IWDT_RC32K_DIV_8   (1U) /*!< RC 8分频 */
#define IWDT_RC32K_DIV_16  (2U) /*!< RC 16分频 */
#define IWDT_RC32K_DIV_32  (3U) /*!< RC 32分频 */
#define IWDT_RC32K_DIV_64  (4U) /*!< RC 64分频 */
#define IWDT_RC32K_DIV_128 (5U) /*!< RC 128分频 */
#define IWDT_RC32K_DIV_256 (6U) /*!< RC 256分频 */
#define IWDT_RC32K_DIV_512 (7U) /*!< RC 512分频 */
/**
 * @}
 */

/** @defgroup IWDT_Flag IWDT状态位
 * @{
 */
#define IWDT_FLAG_PRS  IWDT_SR_PRSF     /*!< CR寄存器更新标志，为0时才可以更新CR寄存器 */
#define IWDT_FLAG_ARR  IWDT_SR_ARRF     /*!< ARR寄存器更新标志，为0时才可以更新ARR寄存器 */
#define IWDT_FLAG_WINR IWDT_SR_WINRF    /*!< WINR寄存器更新标志，为0时才可以更新WINR寄存器 */
#define IWDT_FLAG_OVER IWDT_SR_OV       /*!< IWDT溢出标志 */
#define IWDT_FLAG_RUN  IWDT_SR_RUN      /*!< IWDT运行标志 */
/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup IWDT_Global_Functions IWDT全局函数定义
 * @{
 */
en_result_t IWDT_Init(stc_iwdt_init_t* pstcIwdtInit);
void        IWDT_Start(void);
void        IWDT_Stop(void);
void        IWDT_Feed(void);
boolean_t   IWDT_GetOverFlag(void);
void        IWDT_ClearOverFlag(void);
boolean_t   IWDT_GetRunFlag(void);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_USART_LIN USART_LIN模块驱动库
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_LIN_Global_Macros USART_LIN全局宏定义
 * @{
 */
#define LIN_TIMEOUT_VALUE              20000U /*!< 超时时间(实际超时时间基于指令执行时间)  注：根据需要设置合适的值 */

#define LIN_TOE_Break_Wait_Time        1000U  /*!< 同步间隔段后等待时长，写入TDR寄存器 */
#define LIN_TOE_Byte_Interval_Time     500U   /*!< 字节间间隔时长，写入TDR寄存器 */
#define LIN_TOE_Response_Interval_Time 400U   /*!< 应答间隔时长，写入TDR寄存器 */
/**
 * @}
 */

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup USART_LIN_Global_Functions USART_LIN全局函数定义
 * @{
 */
void        USART_LIN_Wakeup_Frame_Sent(USART_TypeDef* USARTx);
en_result_t USART_LIN_Break_Sent(USART_TypeDef* USARTx, uint32_t u32LowBitsNumbers);
en_result_t USART_LIN_Sync_Sent(USART_TypeDef* USARTx);
void        USART_LIN_ID_Sent(USART_TypeDef* USARTx, uint8_t u8IDValue);
en_result_t USART_LIN_Transmit(USART_TypeDef* USARTx, uint8_t u8Data[], uint32_t u32Size, uint32_t u32Timeout);
void        USART_LIN_TOE(USART_TypeDef* USARTx, uint32_t u32TOEType, uint32_t u32TOEValue);
void        USART_LIN_Wakeup_Frame_Detect(USART_TypeDef* USARTx);
void        USART_LIN_Break_Detect(USART_TypeDef* USARTx, uint32_t u32LowBitsNumbers);
void        USART_LIN_Sync_Detect(USART_TypeDef* USARTx);
void        USART_LIN_BaudRateSet_Detect(USART_TypeDef* USARTx, uint32_t u32BaudRate, uint32_t u32BaudRateOffset);
uint8_t     LIN_Checksum(uint8_t* u8DataBuffer, uint8_t u8DataLen);
uint8_t     LIN_IDParity(uint8_t u8ID);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */




/*****************************************************************************
 * Include files
 *****************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LPM LPM模块驱动库
 * @{
 */

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
/**
 * @addtogroup LPM_Global_Functions LPM全局函数定义
 * @{
 */

/**
 * @brief  进入深度睡眠模式.
 */
void Lpm_GotoSleep(boolean_t bOnExit);

/**
 * @brief  进入普通睡眠模式.
 */
void Lpm_GotoDeepSleep(boolean_t bOnExit);

/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */


/*****************************************************************************
 * Include files
 *****************************************************************************/



/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LPTIM LPTIM模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup LPTIM_Global_Types LPTIM全局类型定义
 * @{
 */


/**
 * @brief  LPTIM  时钟选择
 * @note  LPTIM_CR_TCKSEL
 */
typedef enum
{
    LptimPclk   = 0,
    LptimXtl    = 2,
    LptimRcl    = 3
}en_lptim_tcksel_t;

/**
 * @brief  LPTIM  预除频
 * @note   LPTIM_CR_PRS     在定时器运行时不可以更改该值
 */
typedef enum
{
    LptimPrsDiv1      = 0u,       /*!< 1分频 */
    LptimPrsDiv2      = 1u,       /*!< 2分频 */
    LptimPrsDiv4      = 2u,       /*!< 4分频 */
    LptimPrsDiv8      = 3u,       /*!< 8分频 */
    LptimPrsDiv16     = 4u,       /*!< 16分频 */
    LptimPrsDiv32     = 5u,       /*!< 32分频 */
    LptimPrsDiv64     = 6u,       /*!< 64分频 */
    LptimPrsDiv128    = 7u,       /*!< 128分频 */
    LptimPrsDiv256    = 8u,       /*!< 256分频 */
    LptimPrsDiv512    = 9u,       /*!< 512分频 */
    LptimPrsDiv1024   = 10u,      /*!< 1024分频 */
    LptimPrsDiv2048   = 11u,      /*!< 2048分频 */
    LptimPrsDiv4096   = 12u,      /*!< 4096分频 */
    LptimPrsDiv8192   = 13u,      /*!< 8192分频 */
    LptimPrsDiv16384  = 14u,      /*!< 16384分频 */
    LptimPrsDiv32768  = 15u,      /*!< 32768分频 */
}en_lptim_prs_t;

/**
 * @brief  LPTIM  GATE极性控制位
 * @note   LPTIM_CR_GATEP
 */
typedef enum
{
    LptimGatePLow  = 0,
    LptimGatePHigh = 1
}en_lptim_gatep_t;

/**
 * @brief  LPTIM  门控功能选择
 * @note   LPTIM_CR_GATE
 */
typedef enum
{
    LptimGateDisable  = 0,
    LptimGateEnable = 1
}en_lptim_gate_t;

/**
 * @brief  LPTIM  TOG输出使能位
 * @note   LPTIM_CR_TOG
 */
typedef enum
{
    LptimTogDisLow  = 0,
    LptimTogEnable = 1
}en_lptim_togen_t;

/**
 * @brief  LPTIM  CT计数器/定时器功能选择
 * @note   LPTIM_CR_CT
 */
typedef enum
{
    LptimTimerFun = 0,  /*!< 定时器功能，定时器使用TCK_SEL选择的时钟进行计数 */
    LptimCntFun   = 1   /*!< 计数器功能，计数器使用外部输入的下降沿进行计数，采样时钟使用TCK_SEL选择的时钟 */
}en_lptim_ct_t;

/**
 * @brief  LPTIM  定时器工作模式
 * @note   LPTIM_CR_MD
 */
typedef enum
{
    LptimMode1 = 0,  /*!< 模式1无重载16位计数器/定时器 */
    LptimMode2 = 1   /*!< 模式2自动重载16位计数器/定时器 */
}en_lptim_md_t;

/**
 * @brief  LPTIM  初始化配置的结构体
 */
typedef struct
{
    en_lptim_tcksel_t    enTcksel;
    en_lptim_prs_t       enClkPrs;
    en_lptim_gatep_t     enGatep;
    en_lptim_gate_t      enGate;
    en_lptim_togen_t     enTogen;
    en_lptim_ct_t        enCt;
    en_lptim_md_t        enMd;
    uint16_t             u16Arr;
}stc_lptim_cfg_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup LPTIM_Global_Functions LPTIM全局函数定义
 * @{
 */
void Lptim_ConfIt(LPTIM_TypeDef* Lptimx, boolean_t NewStatus);
void Lptim_Cmd(LPTIM_TypeDef* Lptimx, boolean_t NewStatus);
boolean_t Lptim_GetItStatus(LPTIM_TypeDef* Lptimx);
void Lptim_ClrItStatus(LPTIM_TypeDef* Lptimx);
en_result_t Lptim_Init(LPTIM_TypeDef* Lptimx, stc_lptim_cfg_t* InitStruct);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */



/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LPUART LPUART模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Types LPUART全局类型定义
 * @{
 */

/**
 * @brief lpuart 的sclk时钟源选择
 */
typedef enum
{
    LPUartMskPclk   = 0u<<11, /*!<  pclk */
    LPUartMskXtl    = 2u<<11, /*!<  外部低速晶振 */
    LPUartMskRcl    = 3u<<11, /*!<  内部低速晶振 */
} en_lpuart_sclksel_t;

/**
 * @brief lpuart多机模式地址帧/数据帧或者奇偶校验
 */
typedef enum
{
    LPUartDataOrAddr = 0u,   /*!<  多机模式时，通过读写SBUF[8]决定帧为数据帧或地址帧 */
    LPUartEven       = 0x4u, /*!<  非多机模式偶校验 */
    LPUartOdd        = 0x8u, /*!<  非多机模式奇校验 */
}en_lpuart_mmdorck_t;

/**
 * @brief lpuart多机模式及从机地址和地址掩码配置
 */
typedef struct
{
    uint8_t             u8SlaveAddr;  /*!<  从机地址 */
    uint8_t             u8SaddEn;     /*!<  从及地址掩码 */
}stc_lpuart_multimode_t;

/**
 * @brief lpuart 四种工作模式选择
 */
typedef enum
{
    LPUartMskMode0 = 0x00u, /*!<  模式0 */
    LPUartMskMode1 = 0x40u, /*!<  模式1 */
    LPUartMskMode2 = 0x80u, /*!<  模式2 */
    LPUartMskMode3 = 0xc0u, /*!<  模式3 */
} en_lpuart_mode_t;

/**
 * @brief lpuart stop长度选择
 */
typedef enum
{
    LPUart1bit  = 0x0000u,  /*!<  1位停止位 */
    LPUart1_5bit = 0x4000u, /*!<  1.5位停止位 */
    LPUart2bit  = 0x8000u,  /*!<  2位停止位 */
} en_lpuart_stop_t;

/**
 * @brief lpuart 功能使能
 */
typedef enum
{
    LPUartRenFunc    = 4u,    /*!<  0-TX; 1-非mode0模式代表RX&TX ,mode0模式代表RX; */
    LPUartDmaRxFunc  = 16u,   /*!<  DMA接收功能 */
    LPUartDmaTxFunc  = 17u,   /*!<  DMA发送功能 */
    LPUartRtsFunc    = 18u,   /*!<  硬件流RTS功能 */
    LPUartCtsFunc    = 19u,   /*!<  硬件流CTS功能 */
    LPUartHdFunc     = 22u,   /*!<  单线半双工功能 */
}en_lpuart_func_t;

/**
 * @brief lpuart中断使能控制
 */
typedef enum
{
    LPUartRxIrq  = 0u,    /*!<  接收中断使能 */
    LPUartTxIrq  = 1u,    /*!<  发送中断使能 */
    LPUartTxEIrq = 8u,    /*!<  TX空中断使能 */
    LPUartPEIrq  = 13u,   /*!<  奇偶校验中断使能 */
    LPUartCtsIrq = 20u,   /*!<  CTS信号翻转中断使能 */
    LPUartFEIrq  = 21u,   /*!<  帧错误中断使能  */
}en_lpuart_irq_sel_t;

/**
 * @brief lpuart 状态标志位
 */
typedef enum
{
    LPUartRC    = 0u,  /*!<  接收数据完成标记 */
    LPUartTC    = 1u,  /*!<  发送数据完成标记 */
    LPUartFE    = 2u,  /*!<  帧错误标记 */
    LPUartTxe   = 3u,  /*!<  TXbuff空标记 */
    LPUartPE    = 4u,  /*!<  奇偶校验错误标记 */
    LPUartCtsIf = 5u,  /*!<  CTS中断标记 */
    LPUartCts   = 6u,  /*!<  CTS信号标记 */
}en_lpuart_status_t;

/**
 * @brief lpuart 通道采样分频配置
 */
typedef enum
{
    LPUartMsk16Or32Div = 0u,        /*!<  模式0无效，模式1/3为16分频，模式2为32分频 */
    LPUartMsk8Or16Div  = 0x200u,    /*!<  模式0无效，模式1/3为8分频，模式2为16分频 */
    LPUartMsk4Or8Div   = 0x400u,    /*!<  模式0无效，模式1/3为4分频，模式2为8分频 */
}en_lpuart_clkdiv_t;

/**
 * @brief lpuart 通道Mode1和Mode3波特率计算参数
 */
typedef struct
{
    en_lpuart_sclksel_t  enSclkSel;      /*!<  传输时钟源选择 */
    en_lpuart_clkdiv_t   enSclkDiv;      /*!<  采样分频选择  */
    uint32_t             u32Sclk;        /*!<  sclk */
    uint32_t             u32Baud;        /*!<  波特率 */
} stc_lpuart_baud_t;

/**
 * @brief lpuart 总体配置
 */
typedef struct
{
    en_lpuart_mode_t       enRunMode;      /*!<  四种模式配置 */
    en_lpuart_mmdorck_t    enMmdorCk;      /*!<  校验模式 */
    en_lpuart_stop_t       enStopBit;      /*!<  停止位长度 */
    stc_lpuart_baud_t      stcBaud;        /*!<  Mode1/3波特率配置 */
} stc_lpuart_cfg_t;

/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
/**
 * @addtogroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */
en_result_t LPUart_Init(LPUART_TypeDef* LPUARTx, stc_lpuart_cfg_t* pstcCfg);
void LPUart_HdModeEnable(LPUART_TypeDef* LPUARTx);
void LPUart_HdModeDisable(LPUART_TypeDef* LPUARTx);
boolean_t LPUart_GetRb8(LPUART_TypeDef* LPUARTx);
en_result_t LPUart_EnableIrq(LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_EnableFunc(LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);
boolean_t LPUart_GetStatus(LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus);
en_result_t LPUart_ClrStatus(LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus);
uint8_t LPUart_GetIsr(LPUART_TypeDef* LPUARTx);
en_result_t LPUart_ClrIsr(LPUART_TypeDef* LPUARTx);
en_result_t LPUart_SendData(LPUART_TypeDef* LPUARTx, uint8_t u8Data, uint32_t u32Timeout);
en_result_t LPUart_SendDataIt(LPUART_TypeDef* LPUARTx, uint8_t u8Data);
uint8_t LPUart_ReceiveData(LPUART_TypeDef* LPUARTx);
en_result_t LPUart_MultiModeSendData(LPUART_TypeDef* LPUARTx, uint16_t u16Data, uint32_t u32Timeout);
en_result_t LPUart_MultiModeSendDataIt(LPUART_TypeDef* LPUARTx, uint16_t u16Data);
en_result_t LPUart_SelSclk(LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk);
en_result_t LPUart_SetMultiMode(LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg);
en_result_t LPUart_SetSaddr(LPUART_TypeDef* LPUARTx,uint8_t u8Addr);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* C binding of definitions if building with C++ compiler */

/******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LVD LVD模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup LVD_Global_Types LVD全局类型定义
 * @{
 */

/**
 * @brief  LVD监测电压源选择
 */
typedef enum
{
    LvdInputSrcMskVCC  = 0u<<2,     /*!<  Vcc */
    LvdInputSrcMskPC13 = 1u<<2,     /*!<  PC13 */
    LvdInputSrcMskPB08 = 2u<<2,     /*!<  PB08 */
    LvdInputSrcMskPB07 = 3u<<2,     /*!<  PB07 */
}en_lvd_input_src_t;

/**
 * @brief  LVD阈值电压选择
 */
typedef enum
{
    LvdMskTH1_8V = 0u<<4,         /*!< 1.8V */
    LvdMskTH1_9V = 1u<<4,         /*!< 1.9V */
    LvdMskTH2_0V = 2u<<4,         /*!< 2.0V */
    LvdMskTH2_1V = 3u<<4,         /*!< 2.1V */
    LvdMskTH2_2V = 4u<<4,         /*!< 2.2V */
    LvdMskTH2_3V = 5u<<4,         /*!< 2.3V */
    LvdMskTH2_4V = 6u<<4,         /*!< 2.4V */
    LvdMskTH2_5V = 7u<<4,         /*!< 2.5V */
    LvdMskTH2_6V = 8u<<4,         /*!< 2.6V */
    LvdMskTH2_7V = 9u<<4,         /*!< 2.7V */
    LvdMskTH2_8V = 10u<<4,        /*!< 2.8V */
    LvdMskTH2_9V = 11u<<4,        /*!< 2.9V */
    LvdMskTH3_0V = 12u<<4,        /*!< 3.0V */
    LvdMskTH3_1V = 13u<<4,        /*!< 3.1V */
    LvdMskTH3_2V = 14u<<4,        /*!< 3.2V */
    LvdMskTH3_3V = 15u<<4,        /*!< 3.3V */
}en_lvd_threshold_t;

/**
 * @brief  LVD输出滤波时间
 */
typedef enum
{
    LvdFilterMsk7us    = 0u<<9,         /*!< 7us */
    LvdFilterMsk14us   = 1u<<9,         /*!< 14us */
    LvdFilterMsk28us   = 2u<<9,         /*!< 28us */
    LvdFilterMsk112us  = 3u<<9,         /*!< 112us */
    LvdFilterMsk450us  = 4u<<9,         /*!< 450us */
    LvdFilterMsk1_8ms  = 5u<<9,         /*!< 1.8ms */
    LvdFilterMsk7_2ms  = 6u<<9,         /*!< 7.3ms */
    LvdFilterMsk28_8ms = 7u<<9,         /*!< 28.8ms */
}en_lvd_filter_time_t;

/**
 * @brief  LVD中断触发方式
 */
typedef enum
{
    LvdIrqMskRiseFall = 3u<<12,         /*!< 上升/下降沿触发 */
    LvdIrqMskHigh     = 1u<<14,         /*!< 高电平触发 */
    LvdIrqMskRise     = 1u<<13,         /*!< 上升沿触发 */
    LvdIrqMskFall     = 1u<<12,         /*!< 下降沿触发 */
}en_lvd_irq_type_t;

/**
 * @brief  LVD触发动作选择
 */
typedef enum
{
    LvdActMskReset = 1u<<1,         /*!< 系统复位 */
    LvdActMskInt   = 0u,            /*!< NVIC中断 */
}en_lvd_act_t;

/**
 * @brief  LVD数字滤波使能配置
 */
typedef enum
{
    LvdFilterMskEnable  = 1u<<8,         /*!< 数字滤波使能 */
    LvdFilterMskDisable = 0u,            /*!< 数字滤波禁止 */
}en_lvd_filter_t;

/**
 * @brief  LVD配置
 */
typedef struct
{
    en_lvd_act_t            enAct;          /*!< LVD触发动作 @ref en_lvd_act_t */
    en_lvd_input_src_t      enInputSrc;     /*!< LVD输入电压源 @ref en_lvd_input_src_t */
    en_lvd_threshold_t      enThreshold;    /*!< LVD监测电压 @ref en_lvd_threshold_t */
    en_lvd_filter_t         enFilter;       /*!< 是否使用输出滤波 @ref en_lvd_filter_t */
    en_lvd_filter_time_t    enFilterTime;   /*!< 输出滤波时间 @ref en_lvd_filter_time_t */
    en_lvd_irq_type_t       enIrqType;      /*!< 中断触发方式 @ref en_lvd_irq_type_t */
}stc_lvd_cfg_t;

/**
 * @}
 */

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
/**
 * @addtogroup LVD_Global_Functions LVD全局函数定义
 * @{
 */
void Lvd_EnableIrq(void);
void Lvd_DisableIrq(void);

void Lvd_ClearIrq(void);
boolean_t Lvd_GetIrqStat(void);

boolean_t Lvd_GetFilterResult(void);

void Lvd_Init(stc_lvd_cfg_t *pstcCfg);

void Lvd_Enable(void);
void Lvd_Disable(void);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* C binding of definitions if building with C++ compiler */

/******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_OPA OPA模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup OPA_Global_Types OPA全局类型定义
 * @{
 */
/**
 * @brief  OPA通道选择
 */
typedef enum
{
    OpaChannel0 = 0u,          /*!< OPA0 */
    OpaChannel1 = 4u,          /*!< OPA1 */
}en_opa_ch_sel_t;

/**
 * @brief  自动校准脉冲宽度设置
 */
typedef enum
{
    OpaM1Pclk     = 0u,       /*!< 1个PCLK周期 */
    OpaM2Pclk     = 1u,       /*!< 2个PCLK周期 */
    OpaM4Pclk     = 2u,       /*!< 4个PCLK周期 */
    OpaM8Pclk     = 3u,       /*!< 8个PCLK周期 */
    OpaM16Pclk    = 4u,       /*!< 16个PCLK周期 */
    OpaM32Pclk    = 5u,       /*!< 32个PCLK周期 */
    OpaM64Pclk    = 6u,       /*!< 64个PCLK周期 */
    OpaM128Pclk   = 7u,       /*!< 128个PCLK周期 */
    OpaM256Pclk   = 8u,       /*!< 256个PCLK周期 */
    OpaM512Pclk   = 9u,       /*!< 512个PCLK周期 */
    OpaM1024Pclk  = 10u,      /*!< 1024个PCLK周期 */
    OpaM2048Pclk  = 11u,      /*!< 2048个PCLK周期 */
    OpaM4096Pclk  = 12u       /*!< 4096个PCLK周期 */
}en_opa_clksrc_t;

/**
 * @brief  校零方式选择
 */
typedef enum
{
    enClkSwSet = 3u,          /*!< 软件校准使能 */
    enAzPulse  = 2u,          /*!< 软件校准 */
    enTrigger  = 1u,          /*!< 软件触发自动教零 */
    enAdctr    = 0u           /*!< 使能ADC启动触发OPA自动校准功能 */
}en_opa_set0ctrl_t;

/**
 * @brief  校零配置
 */
typedef struct
{
    boolean_t         bAzen;        /*!< 自动教零配置 */
    boolean_t         bClk_sw_set;  /*!< 自动教零选择 */
    boolean_t         bAz_pulse;    /*!< 软件校准设置 */
    boolean_t         bTrigger;     /*!< 软件触发校准设置 */
    boolean_t         bAdctr_en;    /*!< ADC启动触发OPA自动校准设置 */
    en_opa_clksrc_t   enClksrc;     /*!< 自动校准脉冲宽度设置 */
}stc_opa_zcfg_t;
/**
 * @}
 */

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup OPA_Global_Functions OPA全局函数定义
 * @{
 */
void Opa_Cmd(en_opa_ch_sel_t enOpaChSel, boolean_t NewStatus);
void Opa_SetZero(en_opa_ch_sel_t enOpaChSel, stc_opa_zcfg_t* InitZero);
void Opa_ZeroBitCtrl(en_opa_set0ctrl_t CtrlBit, boolean_t NewState);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/*****************************************************************************
 * Include files
 *****************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_RTC RTC模块驱动库
 * @{
 */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup RTC_Global_Macros RTC全局宏定义
 * @{
 */
/**
 * @defgroup RTC_AlarmDayOfWeek_Sel  RTC闹钟周内选择
 * @{
 */
#define RTC_ALMWEEK_SUNDAY          (0x01U) /*!< 周日 */
#define RTC_ALMWEEK_MONDAY          (0x02U) /*!< 周一 */
#define RTC_ALMWEEK_TUESDAY         (0x04U) /*!< 周二 */
#define RTC_ALMWEEK_WEDNESDAY       (0x08U) /*!< 周三 */
#define RTC_ALMWEEK_THURSDAY        (0x10U) /*!< 周四 */
#define RTC_ALMWEEK_FRIDAY          (0x20U) /*!< 周无 */
#define RTC_ALMWEEK_SATURDAY        (0x40U) /*!< 周六 */
#define RTC_ALMWEEK_ALL             (0x7FU) /*!< 一周全选 */
/**
 * @}
 */

/**
 * @defgroup RTC_IRQ_Flag  RTC中断标志
 * @{
 */
#define RTC_IRQ_ALMA        RTC_IER_ALMA    /*!< 闹钟A */
#define RTC_IRQ_ALMB        RTC_IER_ALMB    /*!< 闹钟B */
#define RTC_IRQ_WU          RTC_IER_WU      /*!< 定时唤醒中断 */
#define RTC_IRQ_TS          RTC_IER_TS      /*!< 时间戳中断 */
#define RTC_IRQ_TSOV        RTC_IER_TSOV    /*!< 时间戳溢出中断 */
#define RTC_IRQ_PRD         RTC_IER_PRD     /*!< 周期中断 */
#define RTC_IRQ_ALL         (RTC_IER_ALMA | \
                            RTC_IER_ALMB | \
                            RTC_IER_WU | \
                            RTC_IER_TS | \
                            RTC_IER_TSOV | \
                            RTC_IER_PRD)    /*!< 所有中断 */
/**
 * @}
 */


/**
 * @}
 */
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Types RTC全局类型定义
 * @{
 */
/**
 * @brief  rtc周期中断的时间间隔 RTC_CR0 PRDS
 */
typedef enum
{
    RtcNone   = 0u, /*!< 无周期中断 */
    Rtc05S    = 1u, /*!< 0.5S中断 */
    Rtc1S     = 2u, /*!< 1秒 */
    Rtc1Min   = 3u, /*!< 1分钟 */
    Rtc1H     = 4u, /*!< 1小时 */
    Rtc1Day   = 5u, /*!< 1天 */
    Rtc1Mon   = 6u  /*!< 1月 */
}en_rtc_prds_t;


/**
 * @brief  rtc 12h制或24h制方式选择 RTC_CR0  AMPM
 */
typedef enum
{
    RtcAmpm12H = 0u,     /*!< 12小时制 */
    RtcAmpm24H = 1u      /*!< 24小时制 */
}en_rtc_ampm_t;

/**
 * @brief  普通精度与高精度1Hz输出  RTC_CR0  HZ1SEL
 */
typedef enum
{
    RtcHz1selGeneralPricision = 0u,    /*!< 普通精度1Hz输出 */
    RtcHz1selHighPricision = 1u        /*!< 高精度1Hz输出 */
}en_rtc_hz1sel_t;

/**
 * @brief  周期中断选择   RTC_CR0  PRDSEL
 */
typedef enum
{
    RtcPrds = 0u,   /*!< 使用PRDS所设定的周期中断事件间隔 */
    RtcPrdx = 1u    /*!< 使用PRDX所设定的周期中断事件间隔 */
}en_rtc_prdsel_t;

/**
 * @brief  rtc的时钟选择   RTC_CR1  CKSEL
 */
typedef enum
{
    RtcClkXtl      = 0u, /*!< 外部低速时钟XTL  32.768k */
    RtcClkRcl      = 2u, /*!< 内部低速时钟RCL  32k     */
    RtcClkXth128   = 4u, /*!< 外部晶振4M       XTH/128 */
    RtcClkXth256   = 5u, /*!< 外部晶振8M       XTH/256 */
    RtcClkXth512   = 6u, /*!< 外部晶振16M      XTH/512 */
    RtcClkXth1024  = 7u  /*!< 外部晶振32M      XTH/1024 */
}en_rtc_cksel_t;

/**
 * @brief  时钟误差补偿使能或禁止   RTC_COMPEN  EN
 */
typedef enum
{
    RtcCompenDisable = 0u, /*!< 禁止时钟误差补偿 */
    RtcCompenEnable  = 1u  /*!< 使能时钟误差补偿 */
}en_rtc_compen_t;

/**
 * @brief  配置PRD中断使能及其周期类型
 */
typedef struct
{
    en_rtc_prdsel_t enPrdsel; /*!< 时钟周期选择  @ref en_rtc_prdsel_t */
    uint8_t         u8Prdx;   /*!< 0~63,设置产生周期中断的时间间隔，(rtcPrdx + 1)*0.5s */
    en_rtc_prds_t   enPrds;   /*!< rtc周期中断的时间间隔  @ref en_rtc_prds_t */
}stc_rtc_prdcfg_t;

/**
 * @brief  闹钟时间配置
 */
typedef struct
{
    uint8_t  u8AlarmSec;    /*!< 闹钟秒钟 BCD码 */
    uint8_t  u8AlarmMinute; /*!< 闹钟分钟 BCD码 */
    uint8_t  u8AlarmHour;   /*!< 闹钟小时 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
    uint8_t  u8AlarmDayOfWeek;   /*!< 闹钟星期选择 @ref RTC_AlarmDayOfWeek_Sel */
    boolean_t bAlarmMskH; /*!< 闹钟小时屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与时位无关 */
    boolean_t bAlarmMskM; /*!< 闹钟分屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与分位无关 */
    boolean_t bAlarmMskS; /*!< 闹钟秒屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与秒位无关 */
}stc_rtc_alarmtime_t;

/**
 * @brief  闹钟通道
 */
typedef enum
{
    RtcAlarmA = 0, /*!< 闹钟A */
    RtcAlarmB = 1, /*!< 闹钟B */
}en_rtc_alarmch_t;


/**
 * @brief  唤醒定时器时钟选择
 */
typedef enum
{
    RtcWuckRTC_Div2 = 0,    /*!< RTC/2 */
    RtcWuckRTC_Div4 = 1,    /*!< RTC/4 */
    RtcWuckRTC_Div8 = 2,    /*!< RTC/8 */
    RtcWuckRTC_Div16 = 3,   /*!< RTC/16 */
    RtcWuckRTC_SecDiv1 = 4, /*!< RTC_Sec/1 */
    RtcWuckRTC_SecDiv2 = 5, /*!< RTC_Sec/2 */
    RtcWuckRTC_SecDiv4 = 6, /*!< RTC_Sec/4 */
    RtcWuckRTC_SecDiv8 = 7, /*!< RTC_Sec/8 */
}en_rtc_wucksel_t;

/**
 * @brief  时间戳边沿选择
 */
typedef enum
{
    RtcTSRising = 0,  /*!< 上升沿 */
    RtcTSFalling = 1, /*!< 下降沿 */
}en_rtc_tsedge_t;

/**
 * @brief  rtc时钟时间戳结构
 */
typedef struct
{
    uint8_t  u8Second;      /*!< 时间：秒 BCD码 */
    uint8_t  u8Minute;      /*!< 时间：分 BCD码 */
    uint8_t  u8Hour;        /*!< 时间：时 BCD码 */
    uint8_t  u8DayOfWeek;   /*!< 时间：周 BCD码 */
    uint8_t  u8Day;         /*!< 时间：日 BCD码 */
    uint8_t  u8Month;       /*!< 时间：月 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
} stc_rtc_ts_t;

/**
 * @brief  rtc时钟年、月、日、时、分、秒读写结构
 */
typedef struct
{
    uint8_t  u8Second;      /*!< 时间：秒 BCD码 */
    uint8_t  u8Minute;      /*!< 时间：分 BCD码 */
    uint8_t  u8Hour;        /*!< 时间：时 BCD码 */
    uint8_t  u8DayOfWeek;   /*!< 时间：周 BCD码 */
    uint8_t  u8Day;         /*!< 时间：日 BCD码 */
    uint8_t  u8Month;       /*!< 时间：月 BCD码 */
    uint8_t  u8Year;        /*!< 时间：年 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
} stc_rtc_time_t;

/**
 * @brief  初始化RTC的结构体
 */
typedef struct
{
    en_rtc_ampm_t         enAmpm;      /*!< 小时的时制 */
    en_rtc_cksel_t        enClksrc;    /*!< 实时时钟的时钟源 */
}stc_rtc_initstruct_t;


/**
 * @}
 */
/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup RTC_Global_Functions RTC全局函数定义
 * @{
 */
void RTC_Unlock(void);
void RTC_Lock(void);

void RTC_Cmd(boolean_t NewState);
void RTC_StartWait(void);
void RTC_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState);

en_result_t RTC_PrdCfg(stc_rtc_prdcfg_t* pstcPrd);

void RTC_AlarmEnalbe(en_rtc_alarmch_t enAlarmX);
void RTC_AlarmDisalbe(en_rtc_alarmch_t enAlarmX);
void RTC_GetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime);
en_result_t RTC_SetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime);

void RTC_WakeupTimerEnable(void);
void RTC_WakeupTimerDisable(void);
void RTC_WakeupTimerClkSel(en_rtc_wucksel_t enWucksel);
void RTC_WakeupTimerSetArr(uint16_t u16Arr);
uint16_t RTC_WakeupTimerGetArr(void);

void RTC_TimestampEnable(void);
void RTC_TimestampDisable(void);
void RTC_TimestampEdgeSel(en_rtc_tsedge_t enEdge);
void RTC_TimestampGet(stc_rtc_ts_t *pstcTs);

boolean_t RTC_GetIrqFlag(uint32_t u32IqrFlag);
void RTC_ClearIrqFlag(uint32_t u32IqrFlag);
boolean_t RTC_GetIrqEn(uint32_t u32IqrFlag);
void RTC_EnableIrq(uint32_t u32IqrFlag);
void RTC_DisableIrq(uint32_t u32IqrFlag);

en_result_t RTC_CalcCompValue(int16_t s16CompUnit, uint16_t *pu16CompValue);
en_result_t RTC_CompCfg(uint16_t u16CompValue, en_rtc_compen_t NewStatus);
en_result_t RTC_ReadDateTime(stc_rtc_time_t* pstcDateTime);
en_result_t RTC_SetDateTime(stc_rtc_time_t* pstcDateTime);
en_rtc_ampm_t RTC_GetAmpmFormat(void);
void RTC_Init(stc_rtc_initstruct_t* pstcRtcInit);


/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */

/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_SPI SPI模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI全局类型定义
 * @{
 */

/**
 * @brief  SPI Init structure definition
 */
typedef struct
{
    uint32_t      u32BaudRate;           /*!<   波特率分频                             @ref SPI_BAUDRATE_SELECTION */
    uint32_t      u32CPHA;               /*!<   时钟相位选择                           @ref SPI_CLOCK_PHASE_SELECTION */
    uint32_t      u32CPOL;               /*!<   时钟极性选择                           @ref SPI_CLOCK_POLARITY_SELECTION */
    uint32_t      u32Mode;               /*!<   主从模式选择                           @ref SPI_MODE_SELECTION */
    uint32_t      u32BitOrder;           /*!<   数据传输高低位顺序选择                 @ref SPI_BIT_ORDER_SELECTION */
    uint32_t      u32DataWidth;          /*!<   每帧的数据宽度                         @ref SPI_DATAWIDTH_SELECTION */
    uint32_t      u32NSS;                /*!<   配置NSS片选信号是硬件控制还是软件控制  @ref SPI_NSS_CFG */
    uint32_t      u32TransferDirection;  /*!<   通信方式选择                           @ref SPI_TRANSFER_DIRECTION_SELECTION */
    uint32_t      u32SampleDelay;        /*!<   主机模式延后采样                       @ref SPI_SAMPLE_DELAY_SELECTION */
    uint32_t      u32DMAReq;             /*!<   DMA传输配置                            @ref SPI_DMA_TRANSFER_CFG */
}stc_spi_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Macros SPI全局宏定义
 * @{
 */

/** @defgroup Bit_definition      SPI_CR0相关位定义
  * @{
  */
#define  SPI_CR0_BRR_0                   (0x1U << SPI_CR0_BRR_Pos)
#define  SPI_CR0_BRR_1                   (0x2U << SPI_CR0_BRR_Pos)
#define  SPI_CR0_BRR_2                   (0x4U << SPI_CR0_BRR_Pos)

#define  SPI_CR0_WIDTH_0                 (0x1U << SPI_CR0_WIDTH_Pos)
#define  SPI_CR0_WIDTH_1                 (0x2U << SPI_CR0_WIDTH_Pos)
#define  SPI_CR0_WIDTH_2                 (0x4U << SPI_CR0_WIDTH_Pos)
#define  SPI_CR0_WIDTH_3                 (0x8U << SPI_CR0_WIDTH_Pos)

#define  SPI_CR0_CM_0                    (0x1U << SPI_CR0_CM_Pos)
#define  SPI_CR0_CM_1                    (0x2U << SPI_CR0_CM_Pos)
/**
  * @}
  */

/** @defgroup SPI_DMA_TRANSFER_CFG  DMA传输配置
  * @{
  */
#define  SPI_DMA_TRANSFER_RX_TX_DISABLE         (0x00000000UL)
#define  SPI_DMA_TRANSFER_RX_ENABLE_TX_DISABLE  (SPI_CR1_DMARXEN)
#define  SPI_DMA_TRANSFER_TX_ENABLE_RX_DISABLE  (SPI_CR1_DMATXEN)
#define  SPI_DMA_TRANSFER_RX_TX_ENABLE          (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN)
/**
  * @}
  */

/** @defgroup SPI_BAUDRATE_SELECTION  SPI主机模式波特率选择
  * @{
  */
#define  SPI_BAUDRATE_PCLK_DIV2          (0x00000000UL)
#define  SPI_BAUDRATE_PCLK_DIV4          (SPI_CR0_BRR_0)
#define  SPI_BAUDRATE_PCLK_DIV8          (SPI_CR0_BRR_1)
#define  SPI_BAUDRATE_PCLK_DIV16         (SPI_CR0_BRR_0 | SPI_CR0_BRR_1)
#define  SPI_BAUDRATE_PCLK_DIV32         (SPI_CR0_BRR_2)
#define  SPI_BAUDRATE_PCLK_DIV64         (SPI_CR0_BRR_0 | SPI_CR0_BRR_2)
#define  SPI_BAUDRATE_PCLK_DIV128        (SPI_CR0_BRR_1 | SPI_CR0_BRR_2)
/**
  * @}
  */

/** @defgroup SPI_CLOCK_PHASE_SELECTION  SPI串行时钟相位选择
  * @{
  */
#define  SPI_CLOCK_PHASE_1EDGE           (0x00000000UL)
#define  SPI_CLOCK_PHASE_2EDGE           (SPI_CR0_CPHA)
/**
  * @}
  */

/** @defgroup SPI_CLOCK_POLARITY_SELECTION  SPI串行时钟极性选择
  * @{
  */
#define  SPI_CLOCK_POLARITY_LOW          (0x00000000UL)
#define  SPI_CLOCK_POLARITY_HIGH         (SPI_CR0_CPOL)
/**
  * @}
  */

/** @defgroup SPI_MODE_SELECTION  SPI工作模式选择
  * @{
  */
#define  SPI_MODE_SLAVE                  (0x00000000UL)        /*!<  从机模式 */
#define  SPI_MODE_MASTER                 (SPI_CR0_MSTR)        /*!<  主机模式 */
/**
  * @}
  */

/** @defgroup SPI_BIT_ORDER_SELECTION  SPI串行数据高低位顺序发送选择
  * @{
  */
#define  SPI_MSB_FIRST                   (0x00000000UL)
#define  SPI_LSB_FIRST                   (SPI_CR0_LSBF)
/**
  * @}
  */

/** @defgroup SPI_DATAWIDTH_SELECTION  SPI串行数据帧宽度选择
  * @{
  */
#define  SPI_DATAWIDTH_4BIT              (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1)
#define  SPI_DATAWIDTH_5BIT              (SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_6BIT              (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_7BIT              (SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_8BIT              (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_9BIT              (SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_10BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_11BIT             (SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_12BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_13BIT             (SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_14BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_15BIT             (SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_16BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
/**
  * @}
  */

/** @defgroup SPI_NSS_CFG  NSS片选信号配置
  * @{
  */
#define  SPI_NSS_HARD_INPUT              (0x00000000UL)           /*!<  NSS IO的外部输入    */
#define  SPI_NSS_HARD_OUTPUT             (SPI_CR0_SSM)            /*!<  主机模式下，由SSI寄存器来决定NSS信号IO的输出值    */
#define  SPI_NSS_SOFT                    (SPI_CR0_SSM)            /*!<  从机模式下，由SSI寄存器值决定NSS信号的输入值    */
/**
  * @}
  */

/** @defgroup SPI_NSS_SOFT_VAL  SPI_SSI设定值
  * @{
  */
#define  SPI_NSS_CONFIG_ENABLE           (0x00000000UL)        /*!<  片选使能    */
#define  SPI_NSS_CONFIG_DISABLE          (SPI_SSI_SSI)         /*!<  片选禁止    */
/**
  * @}
  */

/** @defgroup SPI_NSS_EXT_INPUT_LEVEL  SPI_NSS管脚上输入电平
  * @{
  */
#define  SPI_NSS_EXT_INPUT_LOW_LEVEL     (0x00000000UL)        /*!<  NSS管脚上输入的是低电平    */
#define  SPI_NSS_EXT_INPUT_HIGH_LEVEL    (SPI_SR_SSLVL)        /*!<  NSS管脚上输入的是高电平    */
/**
  * @}
  */

/** @defgroup SPI_TRANSFER_DIRECTION_SELECTION  SPI通讯方式选择
  * @{
  */
#define  SPI_FULL_DUPLEX                 (0x00000000UL)                   /*!<  全双工双向    */
#define  SPI_SIMPLE_TX                   (SPI_CR0_CM_0)                   /*!<  单工只发      */
#define  SPI_SIMPLE_RX                   (SPI_CR0_CM_1)                   /*!<  单工只收      */
#define  SPI_HALF_DUPLEX                 (SPI_CR0_CM_0 | SPI_CR0_CM_1)    /*!<  单线半双工    */
/**
  * @}
  */

/** @defgroup SPI_HALF_DUPLEX_DIRECTION_SELECTION  SPI半双工传输方向选择
  * @{
  */
#define  SPI_HALF_DUPLEX_RX              (0x00000000UL)        /*!<  单线半双工只收    */
#define  SPI_HALF_DUPLEX_TX              (SPI_HDOE_HDOE)       /*!<  单线半双工只发    */
/**
  * @}
  */


/** @defgroup SPI_SAMPLE_DELAY_SELECTION  SPI主机模式延后采样
* @{
*/
#define  SPI_SAMPLE_NORMAL              (0x00000000UL)        /*!<  正常采样    */
#define  SPI_SAMPLE_DELAY               (SPI_CR0_SMP)         /*!<  延后采样    */
/**
  * @}
  */

/** @defgroup SPI_IT_SELECTION  SPI中断使能选择
  * @{
  */
#define SPI_IT_TXE                       (SPI_CR1_TXEIE)      /*!<  发送缓冲空中断  */
#define SPI_IT_RXNE                      (SPI_CR1_RXNEIE)     /*!<  接收缓冲非空中断  */
#define SPI_IT_SSF                       (SPI_CR1_SSFIE)      /*!<  从机选择输入下降沿中断  */
#define SPI_IT_SSR                       (SPI_CR1_SSRIE)      /*!<  从机选择输入上升沿中断  */
#define SPI_IT_UDF                       (SPI_CR1_UDFIE)      /*!<  从机模式下发送缓冲下溢错误中断  */
#define SPI_IT_OVF                       (SPI_CR1_OVFIE)      /*!<  接收缓冲上溢错误  */
#define SPI_IT_SSERR                     (SPI_CR1_SSERRIE)    /*!<  从机模式下的从机选择错误中断  */
#define SPI_IT_MODF                      (SPI_CR1_MODFIE)     /*!<  模式错误中断  */
/**
  * @}
  */

/** @defgroup SPI_FLAG_SELECTION  SPI中断标志位选择
  * @{
  */
#define SPI_FLAG_TXE                     (SPI_SR_TXE)         /*!<  发送缓冲空 标志  */
#define SPI_FLAG_RXNE                    (SPI_SR_RXNE)        /*!<  接收缓冲非空 标志  */
#define SPI_FLAG_SSF                     (SPI_SR_SSF)         /*!<  从机选择输入下降沿 标志  */
#define SPI_FLAG_SSR                     (SPI_SR_SSR)         /*!<  从机选择输入上升沿 标志  */
#define SPI_FLAG_UDF                     (SPI_SR_UDF)         /*!<  从机模式下发送缓冲下溢错误 标志  */
#define SPI_FLAG_OVF                     (SPI_SR_OVF)         /*!<  接收缓冲上溢错误 标志  */
#define SPI_FLAG_SSERR                   (SPI_SR_SSERR)       /*!<  从机模式下的从机选择错误 标志  */
#define SPI_FLAG_MODF                    (SPI_SR_MODF)        /*!<  模式错误 标志  */
#define SPI_FLAG_BUSY                    (SPI_SR_BUSY)        /*!<  总线忙 标志  */
/**
  * @}
  */

/** @defgroup SPI_CLEAR_SELECTION  SPI清除中断标志位选择
  * @{
  */
#define SPI_CLEAR_TXE                    (SPI_ICR_TXE)         /*!<  清除 发送完成 标志  */
#define SPI_CLEAR_RXNE                   (SPI_ICR_RXNE)        /*!<  清除 接收缓冲非空 标志  */
#define SPI_CLEAR_SSF                    (SPI_ICR_SSF)         /*!<  清除 从机选择输入下降沿 标志  */
#define SPI_CLEAR_SSR                    (SPI_ICR_SSR)         /*!<  清除 从机选择输入上升沿 标志  */
#define SPI_CLEAR_UDF                    (SPI_ICR_UDF)         /*!<  清除 从机模式下发送缓冲下溢错误 标志  */
#define SPI_CLEAR_OVF                    (SPI_ICR_OVF)         /*!<  清除 接收缓冲上溢错误 标志  */
#define SPI_CLEAR_SSERR                  (SPI_ICR_SSERR)       /*!<  清除 从机模式下的从机选择错误 标志  */
#define SPI_CLEAR_MODF                   (SPI_ICR_MODF)        /*!<  清除 模式错误 标志  */
/**
  * @}
  */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SPI_Global_Functions SPI全局函数定义
 * @{
 */
en_result_t Spi_Init(SPI_TypeDef* SPIx,stc_spi_init_t* pstcInitCfg);
void SPI_Enable(SPI_TypeDef *SPIx);
void SPI_Disable(SPI_TypeDef *SPIx);
uint32_t SPI_IsEnable(SPI_TypeDef *SPIx);
void SPI_SetBaudRate(SPI_TypeDef *SPIx, uint32_t u32BaudRate);
uint32_t SPI_GetBaudRate(SPI_TypeDef *SPIx);
void SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t u32ClockPhase);
uint32_t SPI_GetClockPhase(SPI_TypeDef *SPIx);
void SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t u32ClockPolarity);
uint32_t SPI_GetClockPolarity(SPI_TypeDef *SPIx);
void SPI_SetMode(SPI_TypeDef *SPIx, uint32_t u32Mode);
uint32_t SPI_GetMode(SPI_TypeDef *SPIx);
void SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t u32TransferBitOrder);
uint32_t SPI_GetTransferBitOrder(SPI_TypeDef *SPIx);
void SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t u32DataWidth);
uint32_t SPI_GetDataWidth(SPI_TypeDef *SPIx);
void SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t u32NSSMode);
uint32_t SPI_GetNSSMode(SPI_TypeDef *SPIx);
void SPI_SlaveNSSConfig(SPI_TypeDef *SPIx, uint32_t u32NSSCfg);
void SPI_MasterNSSOutput(SPI_TypeDef *SPIx, uint32_t u32NSSCfg);
uint32_t SPI_GetNSSSoftValue(SPI_TypeDef *SPIx);
uint32_t SPI_GetNSSExtInput(SPI_TypeDef *SPIx);
void SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection);
uint32_t SPI_GetTransferDirection(SPI_TypeDef *SPIx);
void SPI_SetHalfDuplexDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection);
uint32_t SPI_GetHalfDuplexDirection(SPI_TypeDef *SPIx);
void SPI_EnableIT(SPI_TypeDef* SPIx, uint32_t u32ITEn);
void SPI_DisableIT(SPI_TypeDef* SPIx, uint32_t u32IT);
uint32_t SPI_IsEnableIT(SPI_TypeDef* SPIx, uint32_t u32IT);
uint32_t SPI_IsActiveFlag(SPI_TypeDef* SPIx, uint32_t u32IT);
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint32_t u32IT);
void SPI_ClearFlag_ALL(SPI_TypeDef* SPIx);
void SPI_SetFlag_TXE(SPI_TypeDef* SPIx);
en_result_t Spi_SendData(SPI_TypeDef* SPIx, uint16_t u16Data);
uint16_t Spi_RWByte(SPI_TypeDef* SPIx, uint16_t u16Data);
void Spi_Slave_DummyWriteData(SPI_TypeDef* SPIx, uint16_t u16Data);
en_result_t Spi_Send_Rec_Buf(SPI_TypeDef* SPIx, uint16_t pu16SendBuf[],uint16_t pu16RecBuf[], uint32_t u32Len);
uint16_t Spi_ReceiveData(SPI_TypeDef* SPIx);


/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_USART USART子模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Types USART全局类型定义
 * @{
 */

/**
 * @brief  USART 高级功能初始化配置
 */
typedef struct
{
    uint32_t u32TxRxCombine;        /*!< 收发端口复合使能位  @ref USART_Tx_Rx_Comb            */
    uint32_t u32StartBitDetectMode; /*!< 接收起始位检测模式  @ref USART_Start_Bit_Detect      */
    uint32_t u32MSBFirst;           /*!< MSB/LSB方式选择     @ref USART_MSB_First             */
    uint32_t u32ClockCtrl;          /*!< 时钟控制位          @ref USART_Clk_Control           */
    uint32_t u32TxRxSwap;           /*!< TX/RX引脚互换控制位 @ref USART_Tx_Rx_Swap            */
    uint32_t u32TxRxPinLevelInvert; /*!< 输出信号反向控制位  @ref USART_Tx_Rx_Inv             */
    uint32_t u32HWFlowCtrl;         /*!< 硬件流控            @ref USART_Hardware_Flow_Control */
    uint32_t u32DMATxRxTransfer;    /*!< DMA传输控制         @ref USART_DMA_Tx_Rx             */
} stc_usart_adv_feature_init_t;

/**
 * @brief  USART 多处理机初始化配置
 */
typedef struct
{
    /* Multi Processor Enable Type */
    uint32_t u32MultiProEn; /*!< UART多处理器功能使能控制 @ref USART_UART_Multi_Pro_En          */
    /* Master Type */
    uint32_t u32MultiProID; /*!< UART多处理器ID位         @ref USART_UART_Multi_Pro_ID          */
    /* Slaver Type */
    uint32_t u32MultiProSilentMode; /*!< UART多处理静默模式 @ref USART_UART_Multi_Pro_Silent_Mode */
    uint8_t  u8SlaveAddr;           /*!< 从机地址      取值范围0 ~ 127                            */
    uint8_t  u8SlaveAddrMsk;        /*!< 从机地址掩码  取值范围0 ~ 127                            */
} stc_usart_multi_pro_init_t;

/**
 * @brief  USART UART初始化
 */
typedef struct
{
    /* UART Base Type */
    uint32_t u32BaudRate;    /*!< UART 通信波特率配置(bps) */
    uint32_t u32SampleMode;  /*!< UART 采样模式设定16倍/8倍采样 @ref USART_Over_Sampling */
    uint32_t u32FrameLength; /*!< 数据帧长度8/9bits             @ref USART_Frame_Length  */
    uint32_t u32Parity;      /*!< 奇偶校验选择                  @ref USART_Parity        */
    uint32_t u32StopBits;    /*!< 停止位长度                    @ref USART_Stop_Bits     */
    uint32_t u32TransMode;   /*!< 数据传输方式                  @ref USART_Mode          */

    /* UART Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_uart_init_t;

/**
 * @brief  USART 同步串口初始化
 */
typedef struct
{
    /* Clock Sync Base Type */
    uint32_t u32BaudRate;  /*!< UART 通信波特率配置(bps)                               */
    uint32_t u32TransMode; /*!< 数据传输方式                  @ref USART_Mode          */

    /* Clock Sync Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_clksync_init_t;

/**
 * @brief  USART 红外模式初始化配置
 */
typedef struct
{
    /* IR Base Type */
    uint32_t u32BaudRate;         /*!< UART 通信波特率配置(bps)                              */
    uint32_t u32FrameLength;      /*!< 数据帧长度8/9bits @ref USART_Frame_Length             */
    uint32_t u32Parity;           /*!< 奇偶校验选择      @ref USART_Parity                   */
    uint32_t u32TransMode;        /*!< 数据传输方式      @ref USART_Mode                     */
    uint32_t u32IRMode;           /*!< 红外模式          @ref USART_IR_Mode_Select           */
    uint32_t u32IRMod38K;         /*!< 38K调制方式       @ref USART_IR_38K_Modulation_Select */
    uint32_t u32HighLevelTime38K; /*!< 38K载波高电平维持时间(μs)                             */
    uint32_t u32LowLevelTime38K;  /*!< 38K载波低电平维持时间(μs)                             */

    /* IR Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_ir_init_t;

/**
 * @brief  LIN LIN模式初始化配置
 */
typedef struct
{
    /* LIN Base Type */
    uint32_t u32BaudRate;   /*!< UART 通信波特率配置(bps) */
    uint32_t u32SampleMode; /*!< UART 采样模式设定16倍/8倍采样 @ref USART_Over_Sampling */

    /* UART Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_lin_init_t;

/**
 * @brief  SC 智能卡模式初始化配置
 */
typedef struct
{
    /* SC Base Type */
    uint32_t u32DataBaudRate; /*!< IO上的数据传输波特率配置(bps) */
    uint32_t u32Parity;       /*!< 奇偶校验选择，标准智能卡均采用偶校验      @ref USART_Parity */
    uint32_t u32FiBCN;        /*!< 一位数据传输时的基本时钟数                @ref USART_SC_BCN_SET*/
    uint32_t u32IOPUTime;     /*!< 开漏时强输出CMOS高电平时间，单位:1/pclk   @ref USART_SC_SMCPU_SET*/

    /* SC Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_smart_card_init_t;

/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Macros USART全局宏定义
 * @{
 */

/**
 * @defgroup USART_Mode_Select USART UART和时钟同步模式选择
 * @{
 */
#define USART_UART_MODE    0x00000000U    /*!< UART模式     */
#define USART_CLKSYNC_MODE USART_CR2_SYNC /*!< 时钟同步模式 */
/**
 * @}
 */

/**
 * @defgroup USART_Over_Sampling UART Over Sampling
 * @{
 */
#define USART_OVERSAMPLING_16 0x00000000U     /*!< Oversampling by 16 */
#define USART_OVERSAMPLING_8  USART_CR1_OVER8 /*!< Oversampling by 8  */
/**
 * @}
 */

/**
 * @defgroup USART_Frame_Length  UART Frame Length
 * @{
 */
#define USART_FRAME_LEN_8BITS 0x00000000U     /*!< UART 帧长度 8Bits  */
#define USART_FRAME_LEN_9BITS USART_CR1_CHLEN /*!< UART 帧长度 9Bits  */
/**
 * @}
 */

/**
 * @defgroup USART_Parity  UART Parity
 * @{
 */
#define USART_PARITY_NONE 0x00000000U                    /*!< No parity   */
#define USART_PARITY_EVEN USART_CR1_PCE                  /*!< Even parity */
#define USART_PARITY_ODD  (USART_CR1_PCE | USART_CR1_PS) /*!< Odd parity  */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Bits UART STOP位长选择
 * @{
 */
#define USART_STOP_1BIT  0x00000000U    /*!< USART frame with 1 stop bit  */
#define USART_STOP_2BITS USART_CR1_STOP /*!< USART frame with 2 stop bits */
/**
 * @}
 */

/**
 * @defgroup USART_Mode UART Transfer Mode
 * @{
 */
#define USART_MODE_RX    USART_CR1_RE                  /*!< RX mode        */
#define USART_MODE_TX    USART_CR1_TE                  /*!< TX mode        */
#define USART_MODE_TX_RX (USART_CR1_TE | USART_CR1_RE) /*!< RX and TX mode */
/**
 * @}
 */

/**
 * @defgroup USART_Tx_Rx_COMB UART 收发端口复合使能位
 * @{
 */
#define USART_RX_TX_SEPARATE 0x00000000U    /*!< USART TXD和RXD分开使用                    */
#define USART_RX_TX_COMBINE  USART_CR1_COMB /*!< USART UART单总线模式，TXD和RXD合用TXD端口 */
/**
 * @}
 */

/**
 * @defgroup USART_Start_Bit_Detect UART Start位检测
 * @{
 */
#define USART_START_BIT_RX_EDGE  0x00000000U   /*!< USART Start位检测 接收数据RXD管脚边沿作为起始位 */
#define USART_START_BIT_RX_LEVEL USART_CR1_SBS /*!< USART Start位检测 接收数据RXD管脚电平作为起始位 */
/**
 * @}
 */

/**
 * @defgroup USART_MSB_First   UART Advanced Feature MSB First
 * @{
 */
#define USART_ADV_MSBFIRST_DISABLE 0x00000000U   /*!< Most significant bit sent/received first disable */
#define USART_ADV_MSBFIRST_ENABLE  USART_CR1_MSB /*!< Most significant bit sent/received first enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Clk_Control USART 时钟控制位
 * @{
 */
#define USART_UART_INT_CLK_OUTPUT_DIS   0x00000000U                   /*!< UART: 内部生成的时钟，不输出到CK管脚     */
#define USART_UART_INT_CLK_OUTPUT_EN    (0x1UL << USART_CR2_CLKC_Pos) /*!< UART: 内部生成的时钟，输出到CK管脚       */
#define USART_CLKSYNC_INT_CLK_OUTPUT_EN 0x00000000U                   /*!< 时钟同步：内部生成的时钟，输出到CK管脚   */
#define USART_CLKSYNC_EXT_CLK           (0x2UL << USART_CR2_CLKC_Pos) /*!< 时钟同步：外部输入时钟，频率和波特率相同 */
#define USART_SC7816_INT_CLK_OUTPUT_DIS 0x00000000U                   /*!< 智能卡：内部生成的时钟，不输出到CK管脚   */
#define USART_SC7816_INT_CLK_OUTPUT_EN  (0x1UL << USART_CR2_CLKC_Pos) /*!< 智能卡：内部生成的时钟，输出到CK管脚     */
/**
 * @}
 */

/**
 * @defgroup USART_Tx_Rx_Swap UART Advanced Feature RX TX Pins Swap
 * @{
 */
#define USART_ADV_SWAP_DISABLE 0x00000000U    /*!< TX/RX pins swap disable */
#define USART_ADV_SWAP_ENABLE  USART_CR2_SWAP /*!< TX/RX pins swap enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Tx_Rx_Inv UART Advanced Feature RX Pin Active Level Inversion
 * @{
 */
#define USART_ADV_TX_RX_INV_DISABLE 0x00000000U                         /*!< TX/RX pin active level inversion disable */
#define USART_ADV_TX_INV_ENABLE     USART_CR2_TXINV                     /*!< TX pin active level inversion enable     */
#define USART_ADV_RX_INV_ENABLE     USART_CR2_RXINV                     /*!< RX pin active level inversion enable     */
#define USART_ADV_TX_RX_INV_ENABLE  (USART_CR2_TXINV | USART_CR2_RXINV) /*!< TX/RX pin active level inversion enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Hardware_Flow_Control USART Hardware Flow Control
 * @{
 */
#define USART_HWCONTROL_NONE    0x00000000U                         /*!< No hardware control       */
#define USART_HWCONTROL_RTS     USART_CR2_RTSEN                     /*!< Request To Send           */
#define USART_HWCONTROL_CTS     USART_CR2_CTSEN                     /*!< Clear To Send             */
#define USART_HWCONTROL_RTS_CTS (USART_CR2_RTSEN | USART_CR2_CTSEN) /*!< Request and Clear To Send */
/**
 * @}
 */

/**
 * @defgroup USART_DMA_Tx_Rx    UART DMA Tx
 * @{
 */
#define USART_DMA_TX_RX_DISABLE 0x00000000U                             /*!< UART DMA TX/RX disabled */
#define USART_DMA_TX_ENABLE     USART_CR2_TXDMAEN                       /*!< UART DMA TX enabled     */
#define USART_DMA_RX_ENABLE     USART_CR2_RXDMAEN                       /*!< UART DMA RX enabled     */
#define USART_DMA_TX_RX_ENABLE  (USART_CR2_TXDMAEN | USART_CR2_RXDMAEN) /*!< UART DMA TX/RX enabled  */
/**
 * @}
 */

/**
 * @defgroup USART_Baud_Rate_Pre_Clock_Div USART 波特率生成预分频
 * @{
 */
#define USART_Baud_Rate_Pre_Clock_Div1  0x00000000U                  /*!< 内部时钟源时，预分频器选择 PCLK    */
#define USART_Baud_Rate_Pre_Clock_Div4  (0x1UL << USART_BRR_PSC_Pos) /*!< 内部时钟源时，预分频器选择 PCLK/4  */
#define USART_Baud_Rate_Pre_Clock_Div16 (0x2UL << USART_BRR_PSC_Pos) /*!< 内部时钟源时，预分频器选择 PCLK/16 */
#define USART_Baud_Rate_Pre_Clock_Div64 (0x3UL << USART_BRR_PSC_Pos) /*!< 内部时钟源时，预分频器选择 PCLK/64 */
/**
 * @}
 */

/**
 * @defgroup UART_AutoBaud_Rate_Mode    UART Advanced Feature Auto BaudRate Detection
 * @{
 */
#define USART_ADV_AUTO_BAUDRATE_DISABLE 0x00000000U    /*!< Auto Baud rate detection disable */
#define USART_ADV_AUTO_BAUDRATE_ENABLE  USART_CR3_ABRE /*!< Auto Baud rate detection enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Timer    USART 多功能定时器工作模式配置
 * @{
 */
#define USART_TIMER_STOP              0x00000000U                  /*!< 停止定时计数器                          */
#define USART_GENERAL_TIMER_START     (0x1UL << USART_CR1_TOE_Pos) /*!< 通用定时功能启动                        */
#define USART_RECEIVE_TIMER_START     (0x2UL << USART_CR1_TOE_Pos) /*!< 接收定时功能启动                        */
#define USART_DATA_FRAME_TIMER_START  (0x3UL << USART_CR1_TOE_Pos) /*!< 数据帧间定时功能启动                    */
#define USART_LIN_BREAK_TIMER_START   (0x4UL << USART_CR1_TOE_Pos) /*!< LIN模式下，间隔段计数使能               */
#define USART_AUTO_BAUDRATE_DETECT_EN (0x5UL << USART_CR1_TOE_Pos) /*!< LIN模式或UART模式下，波特率自动检测使能 */
/**
 * @}
 */

/**
 * @defgroup USART_Status_Flags     UART Status Flags
 * @{
 */
#define USART_FLAG_TXE  USART_SR_TXE  /*!< 发送缓存空           */
#define USART_FLAG_TC   USART_SR_TC   /*!< 发送完成             */
#define USART_FLAG_RC   USART_SR_RC   /*!< 接收完成             */
#define USART_FLAG_PE   USART_SR_PE   /*!< 接收数据校验错误     */
#define USART_FLAG_FE   USART_SR_FE   /*!< 接收帧错误           */
#define USART_FLAG_OR   USART_SR_OR   /*!< 接收数据上溢         */
#define USART_FLAG_TO   USART_SR_TO   /*!< 定时器溢出           */
#define USART_FLAG_MPB  USART_SR_MPB  /*!< 多机模式数据、ID标志 */
#define USART_FLAG_AM   USART_SR_AM   /*!< 多机模式地址匹配标志 */
#define USART_FLAG_CTSV USART_SR_CTSV /*!< CTS信号电平值        */
#define USART_FLAG_CTS  USART_SR_CTS  /*!< CTS中断标志          */
#define USART_FLAG_ABR  USART_SR_ABR  /*!< 自动波特率检测标志   */
#define USART_FLAG_LBD  USART_SR_LBD  /*!< LIN模式间隔断检测标志*/
#define USART_FLAG_DWK  USART_SR_DWK  /*!< RXD线唤醒标志        */
#define USART_FLAG_ALL  (0xFFFFU)     /*!< 所有标志             */
/**
 * @}
 */

/**
 * @defgroup USART_UART_Multi_Pro_Silent_Mode USART UART多处理操作静默模式
 * @{
 */
#define USART_UART_NORMAL_MODE 0x00000000U    /*!< 多处理器操作时，正常模式 */
#define USART_UART_SILENT_MODE USART_CR1_SLME /*!< 多处理器操作时，静默模式 */
/**
 * @}
 */

/**
 * @defgroup USART_UART_Multi_Pro_ID USART UART多处理器ID位
 * @{
 */
#define USART_UART_SEND_DATA 0x00000000U    /*!< 多处理器操作时，发送数据 */
#define USART_UART_SEND_ID   USART_TDR_MPID /*!< 多处理器操作时，发送ID   */
/**
 * @}
 */

/**
 * @defgroup USART_UART_Multi_Pro_En USART UART多处理器功能使能控制
 * @{
 */
#define USART_UART_MULTI_PRO_DISABLE 0x00000000U   /*!< 多处理器功能禁止 */
#define USART_UART_MULTI_PRO_ENABLE  USART_CR1_MPE /*!< 多处理器功能使能 */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_ENABLE    USART Local Interconnection Network mode
 * @{
 */
#define USART_LIN_DISABLE 0x00000000U     /*!< Local Interconnect Network disable */
#define USART_LIN_ENABLE  USART_CR3_LINEN /*!< Local Interconnect Network enable  */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Break_Detection  USART LIN Break Detection
 * @{
 */
#define USART_LIN_BREAK_DETECT_DISABLE 0x00000000U    /*!< LIN break detection disable */
#define USART_LIN_BREAK_DETECT_ENABLE  USART_CR3_LBDE /*!< LIN break detection enable  */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Bps_Auto_Detection  USART LIN Auto Bps Detection
 * @{
 */
#define USART_LIN_AUTO_BPS_DETECT_DISABLE 0x00000000U    /*!< LIN auto Bps detection disable */
#define USART_LIN_AUTO_BPS_DETECT_ENABLE  USART_CR3_ABRE /*!< LIN auto Bps detection enable  */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Break_Send  USART LIN Send Break
 * @{
 */
#define USART_LIN_BREAK_SEND_DISABLE 0x00000000U     /*!< LIN break send disable */
#define USART_LIN_BREAK_SEND_ENABLE  USART_CR3_BREAK /*!< LIN break send enable  */
/**
 * @}
 */

/**
 * @defgroup USART_IR_Mode_Select USART IR模式选择
 * @{
 */
#define USART_IR_MODE_3_16 0x00000000U    /*!< 3/16模式    */
#define USART_IR_MODE_38K  USART_CR3_IRCW /*!< 38K载波模式 */
/**
 * @}
 */

/**
 * @defgroup USART_IR_38K_Modulation_Select USART IR 38K调制模式选择
 * @{
 */
#define USART_IR_38K_Mod_0 0x00000000U     /*!< 38K调制模式，数据0输出38K载波 */
#define USART_IR_38K_Mod_1 USART_CR3_IRMOD /*!< 38K载波模式，数据1输出38K载波 */
/**
 * @}
 */

/**
 * @defgroup USART_SC_ENABLE    USART Local Interconnection Network mode
 * @{
 */
#define USART_SC_DISABLE 0x00000000U    /*!< SmartCard mode disable */
#define USART_SC_ENABLE  USART_CR3_SCEN /*!< SmartCard mode enable  */
/**
 * @}
 */
/**
 * @defgroup USART_UART_Error_Code  UART Error Codes
 * @{
 */
#define USART_UART_NoError       0x00000000U /*!< 无错误           */
#define USART_UART_TimeoutError  0xFFFFFFFFU /*!< 超时错误         */
#define USART_UART_ParityError   USART_SR_PE /*!< 接收数据校验错误 */
#define USART_UART_FrameError    USART_SR_FE /*!< 接收帧错误       */
#define USART_UART_OverflowError USART_SR_OR /*!< 接收数据上溢     */
/**
 * @}
 */

/**
 * @defgroup USART_BAUD_RATE_SET_MODE  波特率设置模式选择
 * @{
 */
#define USART_BAUD_RATE_UART    0x00U /*!< UART模式         */
#define USART_BAUD_RATE_CLKSYNC 0x01U /*!< 时钟同步模式     */
#define USART_BAUD_RATE_SC      0x02U /*!< 智能卡接口模式   */
#define USART_BAUD_RATE_IR      0x03U /*!< 红外通信模式     */
#define USART_BAUD_RATE_LIN     0x04U /*!< LIN模式          */
/**
 * @}
 */

/**
 * @defgroup USART_SAMPLE_BITS_SET  采样次数选择
 * @{
 */
#define USART_SAMPLE_BITS_CLKSYNC 0x04U /*!< 时钟同步模式 采样次数 */
#define USART_SAMPLE_BITS_IR      0x10U /*!< 红外通信模式 采样次数 */
/**
 * @}
 */

/**
 * @defgroup USART_SC_SMCPU_SET  智能卡模式输出边沿整型选择
 * @{
 */
#define USART_SC_SMCPU_00 0U /*!< 智能卡模式 输出边沿整形，开漏时强输出无边沿整形             */
#define USART_SC_SMCPU_01 1U /*!< 智能卡模式 输出边沿整形，开漏时强输出1个PCLK周期CMOS高电平  */
#define USART_SC_SMCPU_02 2U /*!< 智能卡模式 输出边沿整形，开漏时强输出2个PCLK周期CMOS高电平  */
#define USART_SC_SMCPU_04 3U /*!< 智能卡模式 输出边沿整形，开漏时强输出4个PCLK周期CMOS高电平  */

/**
 * @defgroup USART_SC_BCN_SET  智能卡模式一位数据传输期间的基本时钟数选择
 * @{
 */
#define USART_SC_BCN_16  16U  /*!< 智能卡模式 BCN=16  */
#define USART_SC_BCN_32  32U  /*!< 智能卡模式 BCN=32  */
#define USART_SC_BCN_64  64U  /*!< 智能卡模式 BCN=64  */
#define USART_SC_BCN_128 128U /*!< 智能卡模式 BCN=128 */
#define USART_SC_BCN_186 186U /*!< 智能卡模式 BCN=186 */
#define USART_SC_BCN_256 256U /*!< 智能卡模式 BCN=256 */
#define USART_SC_BCN_372 372U /*!< 智能卡模式 BCN=372 */
#define USART_SC_BCN_512 512U /*!< 智能卡模式 BCN=512 */

/**
 * @}
 */

/**
 * @defgroup USART_TOE_Type  多功能定时器工作模式配置
 * @{
 */
#define USART_TOE_Stop          0x00000000U                  /*!< 停止定时计数器                          */
#define USART_TOE_General       (0x1UL << USART_CR1_TOE_Pos) /*!< 通用定时功能                            */
#define USART_TOE_Receive       (0x2UL << USART_CR1_TOE_Pos) /*!< 接收定时功能                            */
#define USART_TOE_Data_Frame    (0x3UL << USART_CR1_TOE_Pos) /*!< 数据帧间定时功能                        */
#define USART_TOE_Break         (0x4UL << USART_CR1_TOE_Pos) /*!< LIN模式下，间隔段计数使能               */
#define USART_TOE_Auto_BaudRate (0x5UL << USART_CR1_TOE_Pos) /*!< LIN模式或UART模式下，波特率自动检测使能 */
/**
 * @}
 */

/**
 * @}
 */
/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup USART_Global_Functions USART全局函数定义
 * @{
 */

uint32_t    USART_BaudRateCal(USART_TypeDef* USARTx, uint32_t u32BaudRateSetMode, uint32_t u32BaudRate, uint32_t u32PCLK, uint32_t u32SampMode);
uint32_t    USART_UART_Init(USART_TypeDef* USARTx, stc_usart_uart_init_t* pstcUARTInit);
uint32_t    USART_LIN_Init(USART_TypeDef* USARTx, stc_usart_lin_init_t* pstcLinInit);
uint32_t    USART_IR_Init(USART_TypeDef* USARTx, stc_usart_ir_init_t* pstcIRInit);
uint32_t    USART_SC_Init(USART_TypeDef* USARTx, stc_usart_smart_card_init_t* pstcSmartCardInit);
uint32_t    USART_ClkSync_Init(USART_TypeDef* USARTx, stc_usart_clksync_init_t* pstcClkSyncInit);
en_result_t USART_UART_Transmit(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout);
void        USART_UART_TransmitINT(USART_TypeDef* USARTx, uint8_t* pu8Data);
void        USART_SC_TransmitINT(USART_TypeDef* USARTx, uint8_t *pu8Data);
void        USART_SC_ReceiveINT(USART_TypeDef* USARTx);
uint32_t    USART_UART_Receive(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout);
void        USART_UART_ReceiveINT(USART_TypeDef* USARTx, uint8_t* pu8Data);
void        USART_UART_ABR_Detect(USART_TypeDef* USARTx, uint32_t u32PSC);
void        USART_UART_Detect_ABR_Set(USART_TypeDef* USARTx);
void        USART_SC_CLK_Enable(USART_TypeDef* USARTx, boolean_t bEn);
uint32_t    USART_GetFlag(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_ClearFlag(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_EnableIrq(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_DisableIrq(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_ClearIrq(USART_TypeDef* USARTx, uint32_t u32State);
uint32_t    USART_GetIrqEn(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_IR_EnableIR(USART_TypeDef* USARTx);
void        USART_IR_DisableIR(USART_TypeDef* USARTx);

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
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */

/**
 * @addtogroup HC32A052_DDL 驱动库
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


/* C binding of definitions if building with C++ compiler */

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_WWDT WWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup WWDT_Global_Types WWDT全局类型定义
 * @{
 */

/**
 * @brief  WWDT Init structure definition
 */
typedef struct
{
    uint32_t u32Prescaler;  /*!< 看门狗计数时钟(PCLK)的分频 @ref WWDT_PCLK_Prescaler */
    uint32_t u32Window;     /*!< 看门狗窗口值配置,取值范围必须为：[0x40u ~ 0x7Fu] */
    uint32_t u32Counter;    /*!< 看门狗计数值配置,取值范围必须为：[0x40u ~ 0x7Fu] */
    uint32_t u32PreOverInt; /*!< 预溢出中断控制 @ref WWDT_Pre_Over_Int */
} stc_wwdt_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WWDT_Global_Macros WWDT全局宏定义
 * @{
 */

/**
 * @defgroup WWDT_PCLK_Prescaler WWDT分频选择
 * @{
 */
#define WWDT_PCLK_DIV_4096   (0U << WWDT_CR1_PRS_Pos) /*!< PCLK / 4096 */
#define WWDT_PCLK_DIV_8192   (1U << WWDT_CR1_PRS_Pos) /*!< PCLK / 8192 */
#define WWDT_PCLK_DIV_16384  (2U << WWDT_CR1_PRS_Pos) /*!< PCLK / 16384 */
#define WWDT_PCLK_DIV_32768  (3U << WWDT_CR1_PRS_Pos) /*!< PCLK / 32768 */
#define WWDT_PCLK_DIV_65536  (4U << WWDT_CR1_PRS_Pos) /*!< PCLK / 65536 */
#define WWDT_PCLK_DIV_131072 (5U << WWDT_CR1_PRS_Pos) /*!< PCLK / 131072 */
#define WWDT_PCLK_DIV_262144 (6U << WWDT_CR1_PRS_Pos) /*!< PCLK / 262144 */
#define WWDT_PCLK_DIV_524288 (7U << WWDT_CR1_PRS_Pos) /*!< PCLK / 524288 */
/**
 * @}
 */

/** @defgroup WWDT_Pre_Over_Int WWDT预溢出中断控制
 * @{
 */
#define WWDT_PRE_INT_ENABLE  WWDT_CR1_IE  /*!< 使能WWDT溢出中断 */
#define WWDT_PRE_INT_DISABLE (0U)         /*!< 禁止WWDT溢出中断 */
/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup WWDT_Global_Functions WWDT全局函数定义
 * @{
 */
en_result_t WWDT_Init(stc_wwdt_init_t* pstcWwdtInit);
void        WWDT_Start(void);
void        WWDT_Feed(uint32_t u32Cnt);
uint32_t    WWDT_GetCnt(void);
boolean_t   WWDT_GetPreOverFlag(void);
void        WWDT_ClearPreOverFlag(void);
boolean_t   WWDT_GetRunFlag(void);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/* ========================================================================== */
/*  中断分发框架 (mcu/common/interrupts_hc32a052.h)                                 */
/* ========================================================================== */



/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
/* >>> inlined from ddl.h */


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
/* >>> inlined from system_hc32a052.h */


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

/* <<< end of system_hc32a052.h */
/* >>> inlined from sysctrl.h */


/*******************************************************************************
 * Include files
 ******************************************************************************/



/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @{
 */


/******************************************************************************
 * Global type definitions
 ******************************************************************************/
 /**
 * @defgroup SYSCTRL_Global_Types SYSCTRL全局类型定义
 * @{
 */

/**
 * @brief PLL输入时钟源类型定义
 */
typedef enum
{
    SysctrlPllRch       = 0u,                  /*!< RCH时钟 */
    SysctrlPllXthXtal   = 1u,                  /*!< XTH晶振输入的时钟 */
}en_sysctrl_pll_clksource_t;

/**
 * @brief PLL时钟稳定周期数类型定义
 */
typedef enum
{
    SysctrlPllStableCycle128   = 0x0u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 128个周期数 */
    SysctrlPllStableCycle256   = 0x1u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 256个周期数 */
    SysctrlPllStableCycle512   = 0x2u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 512个周期数 */
    SysctrlPllStableCycle1024  = 0x3u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 1024个周期数 */
    SysctrlPllStableCycle2048  = 0x3u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 2048个周期数 */
    SysctrlPllStableCycle4096  = 0x3u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 4096个周期数 */
    SysctrlPllStableCycle8192  = 0x6u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 8192个周期数 */
    SysctrlPllStableCycle16384 = 0x7u <<SYSCTRL_PLLCR_WAITCYCLE_Pos,                  /*!< 16384个周期数 */
}en_sysctrl_pll_cycle_t;

/**
 * @brief 系统时钟输入源类型定义
 */
typedef enum
{
    SysctrlClkRCH  = 0u,               /*!< 内部高速时钟 */
    SysctrlClkXTH  = 1u,               /*!< 外部高速时钟 */
    SysctrlClkRCL  = 2u,               /*!< 内部低速时钟 */
    SysctrlClkXTL  = 3u,               /*!< 外部低速时钟 */
    SysctrlClkPLL  = 4u,               /*!< PLL时钟 */
}en_sysctrl_clk_source_t;

/**
 * @brief RCH频率值枚举类型定义
 */
typedef enum
{
    SysctrlRchFreq3MHz    = 3u,             /*!< 3MHz */
    SysctrlRchFreq4MHz    = 2u,             /*!< 4MHz */
    SysctrlRchFreq6MHz    = 1u,             /*!< 6MHz */
    SysctrlRchFreq12MHz   = 0u,             /*!< 12MHz */
}en_sysctrl_rch_freq_t;

/**
 * @brief XTAL驱动能力类型定义
 */
typedef enum
{
    SysctrlXtalDriver0 = 0u,                /*!< 最弱驱动能力 */
    SysctrlXtalDriver1 = 1u,                /*!< 弱驱动能力 */
    SysctrlXtalDriver2 = 2u,                /*!< 一般驱动能力 */
    SysctrlXtalDriver3 = 3u,                /*!< 最强驱动能力 */
}en_sysctrl_xtal_driver_t;

/**
 * @brief XTH频率值范围选择类型定义
 */
typedef enum
{
    SysctrlXthFreq8_12MHz   = 0u,          /*!< 8~12MHz */
    SysctrlXthFreq8_16MHz  = 1u,           /*!< 8~16MHz */
    SysctrlXthFreq16_24MHz  = 2u,          /*!< 16~24MHz */
    SysctrlXthFreq20_24MHz  = 3u,          /*!< 20~24MHz */
}en_sysctrl_xth_freq_t;

/**
 * @brief XTH时钟稳定周期数类型定义
 */
typedef enum
{
    SysctrlXthStableCycle256   = 0u,       /*!< 256 个周期数 */
    SysctrlXthStableCycle1024  = 1u,       /*!< 1024 个周期数 */
    SysctrlXthStableCycle4096  = 2u,       /*!< 4096 个周期数 */
    SysctrlXthStableCycle16384 = 3u,       /*!< 16384 个周期数 */
}en_sysctrl_xth_cycle_t;

/**
 * @brief RCL频率值枚举类型定义
 */
typedef enum
{
    SysctrlRclFreq32768    = 0x2u,       /*!< 32.768KHz */
    SysctrlRclFreq38400    = 0x0u,       /*!< 38.4KHz */
}en_sysctrl_rcl_freq_t;

/**
 * @brief RCL时钟稳定周期数类型定义
 */
typedef enum
{
    SysctrlRclStableCycle4   = 0u,       /*!< 4 个周期数 */
    SysctrlRclStableCycle16  = 1u,       /*!< 16 个周期数 */
    SysctrlRclStableCycle64  = 2u,       /*!< 64 个周期数 */
    SysctrlRclStableCycle256 = 3u,       /*!< 256 个周期数 */
}en_sysctrl_rcl_cycle_t;

/**
 * @brief XTL时钟稳定周期数类型定义
 */
typedef enum
{
    SysctrlXtlStableCycle256   = 0u,       /*!< 256 个周期数 */
    SysctrlXtlStableCycle1024  = 1u,       /*!< 1024 个周期数 */
    SysctrlXtlStableCycle4096  = 2u,       /*!< 4096 个周期数 */
    SysctrlXtlStableCycle16384 = 3u,       /*!< 16384 个周期数 */
}en_sysctrl_xtl_cycle_t;

/**
 * @brief XTL晶体振幅枚举类型定义
 */
typedef enum
{
    SysctrlXtlAmp0 = 0u,                /*!< 最小振幅 */
    SysctrlXtlAmp1 = 1u,                /*!< 小振幅 */
    SysctrlXtlAmp2 = 2u,                /*!< 一般振幅 */
    SysctrlXtlAmp3 = 3u,                /*!< 最大振幅 */
}en_sysctrl_xtl_amp_t;


/**
 * @brief HCLK时钟分频系数类型定义
 */
typedef enum
{
    SysctrlHclkDiv1   = 0u,              /*!< SystemClk */
    SysctrlHclkDiv2   = 1u,              /*!< SystemClk/2 */
    SysctrlHclkDiv4   = 2u,              /*!< SystemClk/4 */
    SysctrlHclkDiv8   = 3u,              /*!< SystemClk/8 */
    SysctrlHclkDiv16  = 4u,              /*!< SystemClk/16 */
    SysctrlHclkDiv32  = 5u,              /*!< SystemClk/32 */
    SysctrlHclkDiv64  = 6u,              /*!< SystemClk/64 */
    SysctrlHclkDiv128 = 7u,              /*!< SystemClk/128 */
}en_sysctrl_hclk_div_t;

/**
 * @brief PCLK分频系数
 */
typedef enum
{
    SysctrlPclkDiv1 = 0u,                /*!< HCLK */
    SysctrlPclkDiv2 = 1u,                /*!< HCLK/2 */
    SysctrlPclkDiv4 = 2u,                /*!< HCLK/4 */
    SysctrlPclkDiv8 = 3u,                /*!< HCLK/8 */
}en_sysctrl_pclk_div_t;

/**
 * @brief RTC高速时钟补偿时钟频率数据类型定义
 */
typedef enum
{
    SysctrlRTC4MHz  = 0u,                /*!< 4MHz */
    SysctrlRTC6MHz  = 1u,                /*!< 6MHz */
    SysctrlRTC8MHz  = 2u,                /*!< 8MHz */
    SysctrlRTC12MHz = 3u,                /*!< 12MHz */
    SysctrlRTC16MHz = 4u,                /*!< 16MHz */
    SysctrlRTC20MHz = 5u,                /*!< 20MHz */
    SysctrlRTC24MHz = 6u,                /*!< 24MHz */
    SysctrlRTC32MHz = 7u,                /*!< 32MHz */
}en_sysctrl_rtc_adjust_t;

/**
 * @brief 系统控制模块其他功能数据类型定义
 */
#define _SYSCTRL_FUNC_MSK                       (0x20U)
typedef enum
{
    SysctrlSWDUseIOEn         = 0u,                    /*!< SWD端口设为IO功能 */
    SysctrlCMLockUpEn         = 1u,                    /*!< 使能后CPU执行无效指令会复位MCU */
    SysctrlWakeupByRCH        = 2u,                    /*!< 使能从 Deep Sleep 唤醒后 system clock来源为RCH 原时钟继续使能 */
    SysctrlClkFuncRTCLpmEn    = 3u,                    /*!< 使能RTC低功耗模式 */
    SysctrlAutoSwitchRchEn    = 7u,                    /*!< 使能系统时钟来源为晶体且晶体失效时，自动切换系统时钟来源为RCH,PLL做系统时钟源时候，需要使能 */
    SysctrlSpiPortCtrl        = 8u,                    /*!< SPI 端口方向控制 */
    SysctrlXthNotFilter       = 9u,                    /*!< 不进行XTH时钟滤波 */
    SysctrlGtim0UseAsBtim012  = 10u,                   /*!< Gimer0不使用 Btimer012使用 */
    SysctrlGtim1UseAsBtim345  = 11u,                   /*!< Gimer1不使用 Btimer345使用 */
    SysctrlFastIoNotSet       = 12u,                   /*!< IO总线选择为通用总线，不是FASTIO总线 */
    SysctrlEXTHEn             = 37u,                   /*!< 使能外部高速时钟从输入引脚(PD00)输入 */
    SysctrlEXTLEn             = 38u,                   /*!< 使能外部低速速时钟从输入引脚(PC14)输入 */
    SysctrlXTLLock            = 39u,                   /*!< 使能后XTL_EN只可置位 */
}en_sysctrl_func_t;

/**
 * @brief 外设时钟门控开关类型枚举
 */
#define _PERICLK_REG1_MSK                       (0x20U)
typedef enum
{
    SysctrlPeripheralUsart0       = 0u,       /*!< 串口0 */
    SysctrlPeripheralUsart1       = 1u,       /*!< 串口1 */
    SysctrlPeripheralLpUart0      = 2u,       /*!< 低功耗串口0 */
    SysctrlPeripheralLpUart1      = 3u,       /*!< 低功耗串口1 */
    SysctrlPeripheralI2c0         = 4u,       /*!< I2C0 */
    SysctrlPeripheralI2c1         = 5u,       /*!< I2C1 */
    SysctrlPeripheralSpi0         = 6u,       /*!< SPI0 */
    SysctrlPeripheralSpi1         = 7u,       /*!< SPI1 */
    SysctrlPeripheralAtim0        = 8u,       /*!< 高级定时器ATIM0 */
    SysctrlPeripheralLpTim        = 9u,       /*!< 低功耗定时器 */
    SysctrlPeripheralAtim1        = 10u,      /*!< 高级定时器ATIM1 */
    SysctrlPeripheralTim3         = 11u,      /*!< 高级定时器ATIM3 */
    SysctrlPeripheralAtim2        = 12u,      /*!< 高级定时器ATIM2 */
    SysctrlPeripheralOpa          = 13u,      /*!< OPA */
    SysctrlPeripheralWwt          = 14u,      /*!< 看门狗 */
    SysctrlPeripheralIwt          = 15u,      /*!< 看门狗 */
    SysctrlPeripheralAdcBgr       = 16u,      /*!< ADC&BGR */
    SysctrlPeripheralVcLvd        = 17u,      /*!< VC和LVD */
    SysctrlPeripheralI2cslv       = 18u,      /*!< I2CSLV */
    SysctrlPeripheralRtc          = 20u,      /*!< RTC */
    SysctrlPeripheralCtrim        = 21u,      /*!< 时钟校准 */
    SysctrlPeripheralTick         = 24u,      /*!< 系统定时器 */
    SysctrlPeripheralSwd          = 25u,      /*!< SWD */
    SysctrlPeripheralCrc          = 26u,      /*!< CRC */
    SysctrlPeripheralDma          = 29u,      /*!< DMA */
    SysctrlPeripheralEau          = 30u,      /*!< EAU */
    SysctrlPeripheralFlash        = 31u,      /*!< Flash */


    SysctrlPeripheralGpioA        = 32u,      /*!< GPIOA */
    SysctrlPeripheralGpioB        = 33u,      /*!< GPIOB */
    SysctrlPeripheralGpioC        = 34u,      /*!< GPIOC */
    SysctrlPeripheralGpioD        = 35u,      /*!< GPIOD */
    SysctrlPeripheralCAN          = 39u,      /*!< CAN */
    SysctrlPeripheralGtim0Btim012 = 40u,      /*!< GTIM0_BTIM0_1_2 */
    SysctrlPeripheralGtim1Btim345 = 41u,      /*!< GTIM1_BTIM3_4_5  */
}en_sysctrl_peripheral_gate_t;

/**
 * @brief XTH/XTL失效检测配置结构体定义
 */
typedef struct
{
    uint32_t            u32DetectEn;                   /*!< 失效检查使能 @ref XTH_XTL_Fail_Det_En*/
    uint32_t            u32DetectTime;                 /*!< 失效检测时间 @ref XTH_XTL_Fail_Det_Time*/
    uint32_t            u32DetectIntEn;                /*!< 失效检测中断使能 @ref XTH_XTL_Fail_Det_IntEn*/
}stc_sysctrl_fail_det_cfg_t;

/**
 * @brief PLL初始化配置结构体定义
 */
typedef struct
{
    en_sysctrl_pll_clksource_t  enPllSource;                /*!< PLL时钟源 */
    uint8_t                     u8SourceDiv;                /*!< 时钟源输入分频 */
    en_sysctrl_pll_cycle_t      enStableWaitCycle;          /*!< PLL稳定等待时间 */
    uint8_t                     u8MullN;                    /*!< PLL整数倍频 */
    uint8_t                     u8MullF;                    /*!< PLL小数倍频 */
    uint8_t                     u8OutputDiv;                /*!< PLL输出分频 */
}stc_sysctrl_pll_cfg_t;

/**
 * @brief 芯片信息结构体定义
 */
typedef struct
{
    uint8_t  *pu8UID;                               /*!< 10字节UID(唯一识别号)*/
    char_t   *pcProductNumber;                      /*!< 32字节产品型号"HC32xxx ……" */
    uint32_t u32FlashSize;                          /*!< FLASH容量(Byte)*/
    uint32_t u32RamSize;                            /*!< RAM容量(Byte)*/
    uint16_t u16PinsCounter;                        /*!< 管脚数量*/
}stc_sysctrl_chip_info_t;

/**
 * @}
 */


/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Macros SYSCTRL全局宏定义
 * @{
 */


 /** @defgroup stc_sysctrl_clk_init_t System_Clock_Source
  * @{
  */
#define SYSCTRL_SYSCLK_SOURCE_RCH            (0x0u)  /*!< RCH 为系统时钟源*/
#define SYSCTRL_SYSCLK_SOURCE_XTH            (0x1u)  /*!< XTH 为系统时钟源*/
#define SYSCTRL_SYSCLK_SOURCE_RCL            (0x2u)  /*!< RCL 为系统时钟源*/
#define SYSCTRL_SYSCLK_SOURCE_XTL            (0x3u)  /*!< XTL 为系统时钟源*/
#define SYSCTRL_SYSCLK_SOURCE_PLL            (0x4u)  /*!< PLL 为系统时钟源*/
/**
  * @}
  */

/** @defgroup RCH_Trim_Value RCH_TRIM
  * @{
  */
#define SYSCTRL_RCH_TRIM_12MHz            (*((volatile uint16_t*) (0x00101BE0u)))  /*!< RCH TRIM值*/
/**
  * @}
  */

/** @defgroup RCL_Trim_Value RCL_TRIM
  * @{
  */
#define SYSCTRL_RCL_TRIM_32p8KHz            (*((volatile uint16_t*) (0x00101BEAu))) /*!< RCL 32768 TRIM值*/
#define SYSCTRL_RCL_TRIM_38p4KHz            (*((volatile uint16_t*) (0x00101BE8u))) /*!< RCL 38400 TRIM值*/

/**
  * @}
  */

/** @defgroup XTH_XTL_Fail_Det_Sel  XTH XTL时钟起振和工作失效监测
  * @{
  */
#define SYSCTRL_EXTOSC_FAIL_XTH                    (0u)   /*!< XTH时钟起振和工作失效监测*/
#define SYSCTRL_EXTOSC_FAIL_XTL                    (0x8u) /*!< XTL时钟起振和工作失效监测*/
/**
  * @}
  */

 /** @defgroup XTH_XTL_Fail_Det_En 外部时钟起振和工作失效监测 使能/禁止
  * @{
  */
#define SYSCTRL_EXTOSC_FAIL_DET_DIS                (0u)                    /*!< 外部时钟起振和工作失效监测 禁止*/
#define SYSCTRL_EXTOSC_FAIL_DET_EN                 (SYSCTRL_XTHCR_DETEN)   /*!< 外部时钟起振和工作失效监测 使能*/
/**
  * @}
  */

/** @defgroup XTH_XTL_Fail_Det_Time 外部时钟起振和工作失效监测 时间间隔
  * @{
  */
#define SYSCTRL_EXTOSC_FAIL_DET_TIME_2MS_32        (0u)                      /*!< 外部时钟起振和工作失效监测 时间间隔2ms*/
#define SYSCTRL_EXTOSC_FAIL_DET_TIME_8MS_128       (SYSCTRL_XTHCR_DETTIME)   /*!< 外部时钟起振和工作失效监测 时间间隔8ms*/
/**
  * @}
  */

/** @defgroup XTH_XTL_Fail_Det_IntEn 外部时钟起振和工作失效监测 中断
  * @{
  */
#define SYSCTRL_EXTOSC_FAIL_DET_INT_DIS            (0u)                    /*!< 外部时钟起振和工作失效监测 中断禁止*/
#define SYSCTRL_EXTOSC_FAIL_DET_INT_EN             (SYSCTRL_XTHCR_DETIE)   /*!< 外部时钟起振和工作失效监测 中断使能*/

/**
  * @}
  */

/** @defgroup XTH_XTL_Flag_Type 时钟起振和工作失效标志
  * @{
  */
#define SYSCTRL_XTH_FAIL                           (SYSCTRL_STATE_XTHFAIL)   /*!< XTH起振失效标志*/
#define SYSCTRL_XTH_FAULT                          (SYSCTRL_STATE_XTHFAULT)  /*!< XTH工作失效标志*/
#define SYSCTRL_XTL_FAIL                           (SYSCTRL_STATE_XTLFAIL)   /*!< XTL起振失效标志*/
#define SYSCTRL_XTL_FAULT                          (SYSCTRL_STATE_XTLFAULT)  /*!< XTL工作失效标志*/
/**
  * @}
  */


/** @defgroup Sysctrl_Debug_Module  DEBUG_STOP
  * @{
  */
#define SYSCTRL_DEBUG_STOP_ATIM0                  SYSCTRL_DBGSTOP_ATIM0   /*!< 调试时ATIM0计数功能选择*/
#define SYSCTRL_DEBUG_STOP_ATIM1                  SYSCTRL_DBGSTOP_ATIM1   /*!< 调试时ATIM1计数功能选择*/
#define SYSCTRL_DEBUG_STOP_ATIM2                  SYSCTRL_DBGSTOP_ATIM2   /*!< 调试时ATIM2计数功能选择*/
#define SYSCTRL_DEBUG_STOP_LPTIM                  SYSCTRL_DBGSTOP_LPTIM   /*!< 调试时LPTIM计数功能选择*/
#define SYSCTRL_DEBUG_STOP_GTIM0                  SYSCTRL_DBGSTOP_GTIM0   /*!< 调试时GTIM0计数功能选择*/
#define SYSCTRL_DEBUG_STOP_GTIM1                  SYSCTRL_DBGSTOP_GTIM1   /*!< 调试时GTIM1计数功能选择*/
#define SYSCTRL_DEBUG_STOP_CTRIM                  SYSCTRL_DBGSTOP_CTRIM   /*!< 调试时CTRIM计数功能选择*/
#define SYSCTRL_DEBUG_STOP_IWDT                   SYSCTRL_DBGSTOP_IWDT    /*!< 调试时IWDT计数功能选择*/
#define SYSCTRL_DEBUG_STOP_RTC                    SYSCTRL_DBGSTOP_RTC     /*!< 调试时RTC计数功能选择*/
#define SYSCTRL_DEBUG_STOP_TICK                   SYSCTRL_DBGSTOP_TICK    /*!< 调试时TICK计数功能选择*/
#define SYSCTRL_DEBUG_STOP_ATIM3                  SYSCTRL_DBGSTOP_ATIM3   /*!< 调试时ATIM3计数功能选择*/
#define SYSCTRL_DEBUG_STOP_WWDT                   SYSCTRL_DBGSTOP_WWDT    /*!< 调试时WWDT计数功能选择*/
/**
  * @}
  */

/** @defgroup Sysctrl_Reset_Flag 系统复位标志定义
  * @{
  */
#define SYSCTRL_RESET_FLAG_VCC                      SYSCTRL_RSTFLAG_POR5V   /*!< VCC电源域复位标志*/
#define SYSCTRL_RESET_FLAG_VCORE                    SYSCTRL_RSTFLAG_POR12V  /*!< Vcap域复位标志*/
#define SYSCTRL_RESET_FLAG_LVD                      SYSCTRL_RSTFLAG_LVD     /*!< LVD复位标志*/
#define SYSCTRL_RESET_FLAG_IWDT                     SYSCTRL_RSTFLAG_IWDT    /*!< IWDT复位标志*/
#define SYSCTRL_RESET_FLAG_WWDT                     SYSCTRL_RSTFLAG_WWDT    /*!< WWDT复位标志*/
#define SYSCTRL_RESET_FLAG_LOCKUP                   SYSCTRL_RSTFLAG_LOCKUP  /*!< Cotrex-M0+ CPU Lockup复位标志*/
#define SYSCTRL_RESET_FLAG_SYSREQ                   SYSCTRL_RSTFLAG_SYSREQ  /*!< Cotrex-M0+ CPU 软件复位标志*/
#define SYSCTRL_RESET_FLAG_RSTB                     SYSCTRL_RSTFLAG_RSTB    /*!< RESETB 端口复位标志*/
#define SYSCTRL_RESET_FLAG_ALL                      (0xFFU)
/**
  * @}
  */


/**
 * @}
 */

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/


/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */
en_result_t Sysctrl_ClkDeInit(void);
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq);
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle);
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq);
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver);
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq);
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle);
en_result_t Sysctrl_XTLDriverCfg(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver);
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle);
en_result_t Sysctrl_SetPLLFreq(stc_sysctrl_pll_cfg_t *pstcPLLCfg);
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag);
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource);
en_result_t Sysctrl_ExtOscFailDetCfg(uint32_t u32OscSel, stc_sysctrl_fail_det_cfg_t* pstcCfg);
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv);
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv);
uint32_t Sysctrl_GetHClkFreq(void);
uint32_t Sysctrl_GetPClkFreq(void);
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag);
boolean_t   Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral);
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag);
boolean_t Sysctrl_GetExtOscFlag(uint32_t u32ExtOscFlag);
en_result_t Sysctrl_ClrExtOscFlag(uint32_t u32ExtOscFlag);
en_result_t Sysctrl_SetRTCAdjustClkFreq(en_sysctrl_rtc_adjust_t enRtcAdj);
en_result_t Sysctrl_PeriphReset(en_sysctrl_peripheral_gate_t enPeripheral);
void Sysctrl_ResetFlagClear(uint32_t u32ResetFlag);
uint32_t Sysctrl_ResetFlagGet(uint32_t u32ResetFlag);
void Sysctrl_DebugEnable(uint32_t u32DebugModule);
void Sysctrl_DebugDisable(uint32_t u32DebugModule);

 /**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* <<< end of sysctrl.h */

/* C binding of definitions if building with C++ compiler                     */

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_DDL  DDL公共函数库
 * @{
 */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup DDL_Global_Macros DDL全局宏定义
 * @{
 */

/**
 * @addtogroup Initializing local structures to zero
 * @{
 */
#define DDL_ZERO_STRUCT(x)          ddl_memclr((uint8_t*)&(x), (uint32_t)(sizeof(x)))
/**
 * @}
 */

/**
 * @addtogroup 十进制和二进制转换
 * @{
 */
#define DEC2BCD(x)                  ((((x)/10)<<4) + ((x)%10))
#define BCD2DEC(x)                  ((((x)>>4)*10) + ((x)&0x0F))
/**
 * @}
 */

/**
 * @addtogroup 通用寄存器操作宏定义
 * @{
 */
#define REG_SETBITS(REG, BITS)                  ((REG) |= (BITS)) /*!< 寄存器位置位 */

#define REG_CLEARBITS(REG, BITS)                ((REG) &= ~(BITS)) /*!< 寄存器位清零 */

#define REG_READBITS(REG, BITS)                 ((REG) & (BITS)) /*!< 寄存器位读取 */

#define REG_CLEAR(REG)                          ((REG) = (0x0u)) /*!< 寄存器清零 */

#define REG_WRITE(REG, VAL)                     ((REG) = (VAL)) /*!< 寄存器写入 */

#define REG_READ(REG)                           ((REG)) /*!< 寄存器读取 */

#define REG_MODIFY(REG, CLEARMASK, SETMASK)     REG_WRITE((REG), (((REG_READ(REG)) & (~(CLEARMASK))) | (SETMASK))) /*!< 寄存器修改 */
/**
 * @}
 */

/**
 * @addtogroup 寄存器位掩码
 * @brief BV = Bit Value 寄存器位掩码
 * @{
 */
#define BV(n)                       ((uint32_t)1u << (n))

#define BV0                         ((uint32_t)1u << 0)
#define BV1                         ((uint32_t)1u << 1)
#define BV2                         ((uint32_t)1u << 2)
#define BV3                         ((uint32_t)1u << 3)
#define BV4                         ((uint32_t)1u << 4)
#define BV5                         ((uint32_t)1u << 5)
#define BV6                         ((uint32_t)1u << 6)
#define BV7                         ((uint32_t)1u << 7)
#define BV8                         ((uint32_t)1u << 8)
#define BV9                         ((uint32_t)1u << 9)
#define BV10                        ((uint32_t)1u << 10)
#define BV11                        ((uint32_t)1u << 11)
#define BV12                        ((uint32_t)1u << 12)
#define BV13                        ((uint32_t)1u << 13)
#define BV14                        ((uint32_t)1u << 14)
#define BV15                        ((uint32_t)1u << 15)
#define BV16                        ((uint32_t)1u << 16)
#define BV17                        ((uint32_t)1u << 17)
#define BV18                        ((uint32_t)1u << 18)
#define BV19                        ((uint32_t)1u << 19)
#define BV20                        ((uint32_t)1u << 20)
#define BV21                        ((uint32_t)1u << 21)
#define BV22                        ((uint32_t)1u << 22)
#define BV23                        ((uint32_t)1u << 23)
#define BV24                        ((uint32_t)1u << 24)
#define BV25                        ((uint32_t)1u << 25)
#define BV26                        ((uint32_t)1u << 26)
#define BV27                        ((uint32_t)1u << 27)
#define BV28                        ((uint32_t)1u << 28)
#define BV29                        ((uint32_t)1u << 29)
#define BV30                        ((uint32_t)1u << 30)
#define BV31                        ((uint32_t)1u << 31)
/**
 * @}
 */

/**
 * @addtogroup Global Device Series List
 * @{
 */
#define DDL_DEVICE_SERIES_HC32A052       (0u)
/**
 * @}
 */

/**
 * @addtogroup package definitions of HC device.
 * @{
 */
#define DDL_DEVICE_PACKAGE_HC_C         (0x00u)
#define DDL_DEVICE_PACKAGE_HC_F         (0x10u)
#define DDL_DEVICE_PACKAGE_HC_J         (0x20u)
#define DDL_DEVICE_PACKAGE_HC_K         (0x30u)
/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************/
/* User Device Setting Include file                                           */
/******************************************************************************/
/* >>> inlined from ddl_device.h */


/**
 *******************************************************************************
 ** \brief Global device series definition
 **
 ** \note
 ******************************************************************************/
#define DDL_MCU_SERIES       DDL_DEVICE_SERIES_HC32A052


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
 * @defgroup DDL_Global_Types DDL全局类型定义
 * @{
 */
/**
 * @brief Level
 */
typedef enum
{
    DdlLow      = 0u,  /*!< Low level  '0' */
    DdlHigh     = 1u   /*!< High level '1' */
} en_level_t;

/**
 * @brief Generic Flag Code
 */
typedef enum
{
    DdlClr = 0u,       /*!< Flag clr '0' */
    DdlSet = 1u        /*!< Flag set '1' */
} en_stat_flag_t, en_irq_flag_t;
/**
 * @}
 */

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)            *
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes ('extern', definition in C source)              *
 ******************************************************************************/
/**
 * @addtogroup DDL_Global_Functions DDL全局函数定义
 * @{
 */
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)


void ddl_memclr(void* pu8Address, uint32_t u32Count);
uint32_t Log2(uint32_t u32Val);

void delay1ms(uint32_t u32Cnt);
void delay100us(uint32_t u32Cnt);
void delay10us(uint32_t u32Cnt);
void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag);
boolean_t GetBit(uint32_t addr, uint32_t offset);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

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
#define INT_CALLBACK_PORTA                      INT_CALLBACK_ON
#define INT_CALLBACK_PORTB                      INT_CALLBACK_ON
#define INT_CALLBACK_PORTC                      INT_CALLBACK_ON
#define INT_CALLBACK_PORTD                      INT_CALLBACK_ON
#define INT_CALLBACK_DMAC                       INT_CALLBACK_ON
#define INT_CALLBACK_ATIM3                      INT_CALLBACK_ON
#define INT_CALLBACK_USART0                     INT_CALLBACK_ON
#define INT_CALLBACK_USART1                     INT_CALLBACK_ON
#define INT_CALLBACK_LPUART0                    INT_CALLBACK_ON
#define INT_CALLBACK_LPUART1                    INT_CALLBACK_ON
#define INT_CALLBACK_SPI0                       INT_CALLBACK_ON
#define INT_CALLBACK_SPI1                       INT_CALLBACK_ON
#define INT_CALLBACK_I2C0                       INT_CALLBACK_ON
#define INT_CALLBACK_I2C1                       INT_CALLBACK_ON
#define INT_CALLBACK_ATIM0                      INT_CALLBACK_ON
#define INT_CALLBACK_ATIM1                      INT_CALLBACK_ON
#define INT_CALLBACK_ATIM2                      INT_CALLBACK_ON
#define INT_CALLBACK_LPTIM                      INT_CALLBACK_ON
#define INT_CALLBACK_GTIM0                      INT_CALLBACK_ON
#define INT_CALLBACK_BTIM0                      INT_CALLBACK_ON
#define INT_CALLBACK_BTIM1                      INT_CALLBACK_ON
#define INT_CALLBACK_BTIM2                      INT_CALLBACK_ON
#define INT_CALLBACK_GTIM1                      INT_CALLBACK_ON
#define INT_CALLBACK_BTIM3                      INT_CALLBACK_ON
#define INT_CALLBACK_BTIM4                      INT_CALLBACK_ON
#define INT_CALLBACK_BTIM5                      INT_CALLBACK_ON
#define INT_CALLBACK_I2CSLV                     INT_CALLBACK_ON
#define INT_CALLBACK_WWDT                       INT_CALLBACK_ON
#define INT_CALLBACK_IWDT                       INT_CALLBACK_ON
#define INT_CALLBACK_RTC                        INT_CALLBACK_ON
#define INT_CALLBACK_ADC                        INT_CALLBACK_ON
#define INT_CALLBACK_VC0                        INT_CALLBACK_ON
#define INT_CALLBACK_VC1                        INT_CALLBACK_ON
#define INT_CALLBACK_LVD                        INT_CALLBACK_ON
#define INT_CALLBACK_ATIM_BK                    INT_CALLBACK_ON
#define INT_CALLBACK_FLASH                      INT_CALLBACK_ON
#define INT_CALLBACK_RAM                        INT_CALLBACK_ON
#define INT_CALLBACK_CTRIM                      INT_CALLBACK_ON
#define INT_CALLBACK_FAULT                      INT_CALLBACK_ON


/**
 * @brief 中断优先级数据类型定义
 * @note
 */
typedef enum en_irq_level
{
    IrqLevel0  = 0u,               ///< 优先级0(高)     ||
    IrqLevel1  = 1u,               ///< 优先级1         ||
    IrqLevel2  = 2u,               ///< 优先级2         ||
    IrqLevel3  = 3u,               ///< 优先级3(低)     \/
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
 * interrupts_hc32a052.h 只声明了 EnableNvic(), 下面这些全部没有声明.
 * 单独编译成 .o 时它们是 C 符号; 但合并进 driver.cpp 后用 C++ 编译,
 * 会得到 _Z... 修饰名, 向量表引用的 C 符号名再也匹配不上, 实测后果是
 * 向量表全部落回 startup.s 的 Default_Handler, 中断彻底失效.
 *
 * 另: 回调若是弱未定义 (用户没实现), 入口会跳到地址 0. 使用时请按需实现.
 */
/* 中断回调: 弱符号, 应用层实现同名函数即可覆盖 (41 个) */
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

/* 向量表中断入口: driver 提供强定义, 覆盖 startup.s 的弱默认 (32 个) */
void HardFault_Handler(void);
void SysTick_Handler(void);
void PORTA_IRQHandler(void);
void PORTB_IRQHandler(void);
void PORTC_IRQHandler(void);
void PORTD_IRQHandler(void);
void DMAC_IRQHandler(void);
void ATIM3_IRQHandler(void);
void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void LPUART0_IRQHandler(void);
void LPUART1_IRQHandler(void);
void SPI0_IRQHandler(void);
void SPI1_IRQHandler(void);
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
void ATIM0_IRQHandler(void);
void ATIM1_IRQHandler(void);
void ATIM2_IRQHandler(void);
void LPTIM_IRQHandler(void);
void GTIM0_BTIM0_1_2_IRQHandler(void);
void GTIM1_BTIM3_4_5_IRQHandler(void);
void I2CSLV_IRQHandler(void);
void WWDT_IRQHandler(void);
void IWDT_IRQHandler(void);
void RTC_IRQHandler(void);
void ADC_IRQHandler(void);
void VC0_1_LVD_IRQHandler(void);
void CAN_IRQHandler(void);
void ATIM_BK_IRQHandler(void);
void FLASH_RAM_IRQHandler(void);
void CTRIM_FAULT_IRQHandler(void);

/* ========================================================================== */
/*  系统时钟声明 (mcu/common/system_hc32a052.h)                                     */
/* ========================================================================== */


/* ========================================================================== */
/*  原厂遗漏声明的补全                                                                 */
/* ========================================================================== */

/*
 * 以下符号在源码中有定义, 但原厂头文件从未声明:
 *   - SPI_* / Sysctrl_GetChipInfo: 若不补声明, 聚合到 .cpp 用 C++
 *     编译后会变成 _Z... 修饰名, 与其它 TU 的 C 符号引用不匹配;
 *   - SystemHCLK / SystemPCLK: 全局变量漏声明, 实现见 config.cpp.
 * 校验: clang++ -c driver.cpp && llvm-nm driver.o | grep -w _Z
 */
void     SPI_SetDMAReq(SPI_TypeDef *SPIx, uint32_t u32DMAReq);
uint32_t SPI_GetDMAReq(SPI_TypeDef *SPIx);
void     Sysctrl_GetChipInfo(stc_sysctrl_chip_info_t *pstcChipInfo);
extern uint32_t SystemHCLK;
extern uint32_t SystemPCLK;

#ifdef __cplusplus
}
#endif

#endif /* __HC32A052_DRIVER_H__ */
