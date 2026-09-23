/**
 *******************************************************************************
 * @file  btim.h
 * @brief This file contains all the functions prototypes of the BTIMER driver
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


#ifndef __BTIM_H__
#define __BTIM_H__

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

#ifdef __cplusplus
#endif


#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


