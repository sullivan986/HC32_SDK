/**
 *******************************************************************************
 * @file  crc.h
 * @brief This file contains all the functions prototypes of the CRC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-21       MADS            First version
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
#ifndef __CRC_H__
#define __CRC_H__

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

#ifdef __cplusplus
}
#endif

#endif /* __CRC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

