/**
 *******************************************************************************
 * @file  lptim.h
 * @brief This file contains all the functions prototypes of the LPTIM driver
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

#ifndef __LPTIM_H__
#define __LPTIM_H__

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

#ifdef __cplusplus
#endif

#endif //__LPTIM_H__
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
