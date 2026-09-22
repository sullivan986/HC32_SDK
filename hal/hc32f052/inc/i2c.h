/**
 *******************************************************************************
 * @file  i2c.h
 * @brief This file contains all the functions prototypes of the I2C driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-08-10       MADS            First version
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

#ifndef __I2C_H__
#define __I2C_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32F052_DDL 驱动库
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

#ifdef __cplusplus
#endif

#endif /* __I2C_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


