/**
 *******************************************************************************
 * @file  opa.h
 * @brief This file contains all the functions prototypes of the OPA driver
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
#ifndef __OPA_H__
#define __OPA_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


/**
 * @addtogroup HC32F052_DDL 驱动库
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

#ifdef __cplusplus
#endif

#endif /* __OPA_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


