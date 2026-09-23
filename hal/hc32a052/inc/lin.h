/**
 *******************************************************************************
 * @file  lin.h
 * @brief This file contains all the functions prototypes of the LIN firmware
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-10-15       MADS            First version
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
#ifndef __LIN_H__
#define __LIN_H__

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

#ifdef __cplusplus
}
#endif

#endif /* __LIN_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
