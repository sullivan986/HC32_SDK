/**
 *******************************************************************************
 * @file  wwdt.h
 * @brief This file contains all the functions prototypes of the WWDT driver
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
#ifndef __WWDT_H__
#define __WWDT_H__

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

#ifdef __cplusplus
}
#endif

#endif /* __WWDT_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
