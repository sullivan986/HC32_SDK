/**
 *******************************************************************************
 * @file  gtim.h
 * @brief This file contains all the functions prototypes of the GTIMER driver
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


#ifndef __GTIM_H__
#define __GTIM_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
#endif


#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


