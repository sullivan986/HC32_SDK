/**
 *******************************************************************************
 * @file  iwdt.h
 * @brief This file contains all the functions prototypes of the IWDT driver
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
#ifndef __IWDT_H__
#define __IWDT_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

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

#ifdef __cplusplus
}
#endif

#endif /* __IWDT_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
