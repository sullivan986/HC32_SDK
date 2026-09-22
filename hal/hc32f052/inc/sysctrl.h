/**
 *******************************************************************************
 * @file  sysctrl.h
 * @brief This file contains all the functions prototypes of the SYSCTRL driver
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

#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
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
    SysctrlXthStableCycle8192   = 0u,      /*!< 8192 个周期数 */
    SysctrlXthStableCycle32768  = 1u,      /*!< 32768 个周期数 */
    SysctrlXthStableCycle131072 = 2u,      /*!< 131072 个周期数 */
    SysctrlXthStableCycle262144 = 3u,      /*!< 262144 个周期数 */
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

#ifdef __cplusplus
#endif

#endif /* __SYSCTRL_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


