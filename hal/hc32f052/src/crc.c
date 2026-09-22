/**
 *******************************************************************************
 * @file  crc.c
 * @brief CRC API定义.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "crc.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CRC CRC模块驱动库
 * @brief CRC Driver Library CRC模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CRC_Global_Functions CRC全局函数定义
 * @{
 */
/**
 * @brief  CRC16 编码(字节填充方式)
 * @param  [in] pu8Data 待编码数据数组（字节方式输入）
 * @param  [in] u32Len 待编码数据长度（字节数）
 * @retval uint16_t: CRC16编码值
 */
uint16_t CRC16_Get8(uint8_t pu8Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;
    
    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
        *((volatile uint8_t*)(&(HC_CRC->DATA)))  = pu8Data[u32Index];
    }

    return REG_READBITS(HC_CRC->RESULT, 0xFFFFU);
}

/**
 * @brief  CRC16 编码(半字填充方式)
 * @param  [in] pu16Data 待编码数据数组（半字方式输入）
 * @param  [in] u32Len 待编码数据长度（半字数）
 * @retval uint16_t: CRC16编码值
 */
uint16_t CRC16_Get16(uint16_t pu16Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;
   
    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }

    return REG_READBITS(HC_CRC->RESULT, 0xFFFFU);
}

/**
 * @brief  CRC16 编码(字填充方式).
 * @param  [in] pu32Data 待编码数据数组（字方式输入）
 * @param  [in] u32Len 待编码数据长度（字数）
 * @retval uint16_t: CRC16编码值
 */
uint16_t CRC16_Get32(uint32_t pu32Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;
   
    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        HC_CRC->DATA = pu32Data[u32Index];
    }

    return REG_READBITS(HC_CRC->RESULT, 0xFFFFU);
}

/**
 * @brief  CRC16 校验(字节填充方式)，该函数主要用于对数据及CRC16值进行校验.
 * @param  [in] pu8Data 待校验数据数组（字节方式输入）
 * @param  [in] u32Len 待校验数据长度（字节数）
 * @param  [in] u16CRC 待校验CRC16值
 * @retval en_result_t: 
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC16_Check8(uint8_t pu8Data[], uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;
    
    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(HC_CRC->DATA))) = pu8Data[u32Index];
    }
    
    *((volatile uint16_t*)(&(HC_CRC->DATA))) = u16CRC;
    
    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;
    
    return (enResult); 
}

/**
 * @brief  CRC16 校验(半字填充方式) 该函数主要用于对数据及CRC16值进行校验.
 * @param  [in] pu16Data 待校验数据数组（半字方式输入）
 * @param  [in] u32Len 待校验数据长度（半字数）
 * @param  [in] u16CRC 待校验CRC16值
 * @retval en_result_t: 
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC16_Check16(uint16_t pu16Data[], uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }
    
    *((volatile uint16_t*)(&(HC_CRC->DATA))) = u16CRC;
    
    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;
    
    return (enResult); 
}

/**
 * @brief  CRC16 校验(字填充方式) 该函数主要用于对数据及CRC16值进行校验.
 * @param  [in] pu32Data 待校验数据数组（字方式输入）
 * @param  [in] u32Len 待校验数据长度（字数）
 * @param  [in] u16CRC 待校验CRC16值
 * @retval en_result_t: 
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC16_Check32(uint32_t pu32Data[], uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;

    REG_CLEARBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(HC_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(HC_CRC->DATA))) = u16CRC;
    
    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;
    
    return (enResult);
}

/**
 * @brief  CRC32 编码(字节填充方式) 该函数主要用于生成CRC32编码.
 * @param  [in] pu8Data 待编码数据数组（字节方式输入）
 * @param  [in] u32Len 待编码数据长度（字节数）
 * @retval uint32_t: CRC32编码值
 */
uint32_t CRC32_Get8(uint8_t pu8Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;
    
    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(HC_CRC->DATA)))  = pu8Data[u32Index];
    }

    return REG_READ(HC_CRC->RESULT);
}

/**
 * @brief  CRC32 编码(半字填充方式) 该函数主要用于生成CRC32编码.
 * @param  [in] pu16Data 待编码数据数组（半字方式输入）
 * @param  [in] u32Len 待编码数据长度（半字数）
 * @retval uint32_t: CRC32编码值
 */
uint32_t CRC32_Get16(uint16_t pu16Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;
    
    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return REG_READ(HC_CRC->RESULT);
}

/**
 * @brief  CRC32 编码(字填充方式) 该函数主要用于生成CRC32编码.
 * @param  [in] pu32Data 待编码数据数组（字方式输入）
 * @param  [in] u32Len 待编码数据长度（字数）
 * @retval uint32_t: CRC32编码值
 */
uint32_t CRC32_Get32(uint32_t pu32Data[], uint32_t u32Len)
{
    uint32_t u32Index = 0U;
    
    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        HC_CRC->DATA = pu32Data[u32Index];
    }
  
    return REG_READ(HC_CRC->RESULT);
}

/**
 * @brief  CRC32 校验(字节填充方式) 该函数主要用于对数据及CRC32值进行校验.
 * @param  [in] pu8Data 待校验数据数组（字节方式输入）
 * @param  [in] u32Len 待校验数据长度（字节数）
 * @param  [in] u32CRC 待校验CRC32值
 * @retval en_result_t: 
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC32_Check8(uint8_t pu8Data[], uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;
    
    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(HC_CRC->DATA))) = pu8Data[u32Index];
    }
    
    REG_WRITE(HC_CRC->DATA, u32CRC);
    
    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;
    
    return (enResult); 
}

/**
 * @brief  CRC32 校验(半字填充方式) 该函数主要用于对数据及CRC32值进行校验.
 * @param  [in] pu16Data 待校验数据数组（半字方式输入）
 * @param  [in] u32Len 待校验数据长度（半字数）
 * @param  [in] u32CRC 待校验CRC32值
 * @retval en_result_t: 
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC32_Check16(uint16_t pu16Data[], uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;
    
    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(HC_CRC->DATA))) = pu16Data[u32Index];
    }
    
    REG_WRITE(HC_CRC->DATA, u32CRC);
    
    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;
    
    return (enResult); 
}

/**
 * @brief  CRC32 校验(字填充方式) 该函数主要用于对数据及CRC32值进行校验.
 * @param  [in] pu32Data 待校验数据数组（字方式输入）
 * @param  [in] u32Len 待校验数据长度（字数）
 * @param  [in] u32CRC 待校验CRC32值
 * @retval en_result_t: 
 *         - Ok：CRC校验正确；
 *         - Error：CRC校验错误
 */
en_result_t CRC32_Check32(uint32_t pu32Data[], uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0U;
    
    REG_SETBITS(HC_CRC->CSR, CRC_CSR_CODE);
    REG_WRITE(HC_CRC->RESULT, 0xFFFFFFFFU);
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        REG_WRITE(HC_CRC->DATA, pu32Data[u32Index]);
    }
    REG_WRITE(HC_CRC->DATA, u32CRC);
    
    enResult = REG_READBITS(HC_CRC->CSR, CRC_CSR_FLAG) ? Ok : Error;
    
    return (enResult);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
