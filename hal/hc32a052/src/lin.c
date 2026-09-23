/**
 *******************************************************************************
 * @file  lin.c
 * @brief This file provides firmware functions to manage LIN status.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "lin.h"
#include "usart.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_USART_LIN USART_LIN模块驱动库
 * @brief USART_LIN Driver Library USART_LIN模块驱动库
 * @{
 */

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
/**
 * @defgroup USART_LIN_Local_Variables USART_LIN局部变量定义
 * @{
 */
static uint8_t u8LIN_Wakeup_Data = 0x80U;
static uint8_t u8LIN_Sync_Data   = 0x55U;
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USART_LIN_Global_Functions USART_LIN全局函数定义
 * @{
 */

/**
 * @brief  USART LIN唤醒信号帧发送函数
 * @param  [in] USARTx:        USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_LIN_Wakeup_Frame_Sent(USART_TypeDef* USARTx)
{
    /* CR1设置: TE = 1 */
    REG_SETBITS(USARTx->CR1, USART_CR1_TE);

    /* 发送数据0x80 */
    USART_UART_Transmit(USARTx, &u8LIN_Wakeup_Data, 0x1U, LIN_TIMEOUT_VALUE);
}

/**
 * @brief  USART LIN间隔段发送函数
 * @param  [in] USARTx:             USART类型定义         @ref USART_TypeDef
 * @param  [in] u32LowBitsNumbers:  发送持续位的“0”的个数, 数据范围参考TDR寄存器位长
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 * - 为了避免间隔段未发完而新数据又写入发送寄存器，本函数中加了超时定时器用以等待间隔段发送完成
 */
en_result_t USART_LIN_Break_Sent(USART_TypeDef* USARTx, uint32_t u32LowBitsNumbers)
{
    uint32_t u32TimeoutCnt = 0U;

    /* CR3设置: BREAK = 1; LINEN = 1 */
    REG_MODIFY(USARTx->CR3, USART_CR3_BREAK | USART_CR3_LINEN, USART_LIN_BREAK_SEND_ENABLE | USART_LIN_ENABLE);

    /* CR1设置: TE = 1 */
    if (USART_MODE_TX != REG_READBITS(USARTx->CR1, USART_CR1_TE))
    {
        /* TE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_TE, USART_MODE_TX);
    }

    USART_ClearFlag(USARTx, USART_FLAG_TC);
    /* 发送低电平到总线 */
    REG_WRITE(USARTx->TDR, u32LowBitsNumbers);

    /* 查询等待SR.TC变为1 */
    while (!USART_GetFlag(USARTx, USART_FLAG_TC))
    {
        u32TimeoutCnt++;
        if (LIN_TIMEOUT_VALUE <= u32TimeoutCnt)
        {
            /* 等待超时 */
            return ErrorTimeout;
        }
    }

    /* 使用TOE功能，加入同步间隔段后等待 */
    USART_ClearFlag(USARTx, USART_FLAG_TO);
    USART_LIN_TOE(USARTx, USART_TOE_General, LIN_TOE_Break_Wait_Time);

    return Ok;
}

/**
 * @brief  USART LIN同步段发送函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 */
en_result_t USART_LIN_Sync_Sent(USART_TypeDef* USARTx)
{
    /* CR3设置: BREAK = 0 */
    REG_CLEARBITS(USARTx->CR3, USART_CR3_BREAK);
    return USART_LIN_Transmit(USARTx, &u8LIN_Sync_Data, 0x1U, LIN_TIMEOUT_VALUE);
}

/**
 * @brief  USART LIN ID段发送函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @param  [in] u8IDValue:     ID值 (8位，包含标识符和奇偶校验符)
 * @retval None
 */
void USART_LIN_ID_Sent(USART_TypeDef* USARTx, uint8_t u8IDValue)
{
    /* 发送数据0x80 */
    USART_UART_Transmit(USARTx, (uint8_t*)&u8IDValue, 0x1U, LIN_TIMEOUT_VALUE);

    /* 使用TOE功能，加入应答间隔段 */
    USART_ClearFlag(USARTx, USART_FLAG_TO);
    USART_LIN_TOE(USARTx, USART_TOE_General, LIN_TOE_Response_Interval_Time);
}

/**
 * @brief  USART LIN发送数据
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] u8Data:      LIN发送数据buffer指针,包含数据和校验和
 * @param  [in] u32Size:     LIN发送数据长度(字节数)
 * @param  [in] u32Timeout:  LIN发送超时时间
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 */
en_result_t USART_LIN_Transmit(USART_TypeDef* USARTx, uint8_t u8Data[], uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t u32SizeIdx    = 0U;
    uint32_t u32TimeoutCnt = 0U;
    for (u32SizeIdx = 0U; u32SizeIdx < u32Size; u32SizeIdx++)
    {
        /* 清除发送完成标志 */
        USART_ClearFlag(USARTx, USART_FLAG_TC);
        /* 写入一帧待发送的数据 */
        REG_WRITE(USARTx->TDR, u8Data[u32SizeIdx]);
        /* 查询等待SR.TC变为1 */
        while (!USART_GetFlag(USARTx, USART_FLAG_TC))
        {
            u32TimeoutCnt++;
            if (u32Timeout <= u32TimeoutCnt)
            {
                /* 等待超时 */
                return ErrorTimeout;
            }
        }
        /* 使用TOE功能，加入字节间间隔段 */
        USART_ClearFlag(USARTx, USART_FLAG_TO);
        USART_LIN_TOE(USARTx, USART_TOE_General, LIN_TOE_Byte_Interval_Time);
    }

    return Ok;
}

/**
 * @brief  USART LIN 字节间间隔和帧间隔　超时定时器设置
 * @param  [in] USARTx:      USART类型定义            @ref USART_TypeDef
 * @param  [in] u32TOEType:  多功能定时器工作模式配置 @ref USART_TOE_Type
 * @param  [in] u32TOEValue: LIN发送超时时间
 * @retval None
 */
void USART_LIN_TOE(USART_TypeDef* USARTx, uint32_t u32TOEType, uint32_t u32TOEValue)
{
    if (USART_TOE_General == u32TOEType)
    {
        /* 停止超时定时器 TOE = 0 */
        REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
        /* 写入超时值 */
        REG_WRITE(USARTx->TOR, u32TOEValue);
        /* 启动超时定时器 TOE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_General);
    }
    else if (USART_TOE_Break == u32TOEType)
    {
        /* 停止超时定时器 TOE = 0 */
        REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
        /* 写入超时值 */
        REG_WRITE(USARTx->TOR, u32TOEValue);
        /* 启动超时定时器 TOE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_Break);
    }
}

/**
 * @brief  USART LIN唤醒信号帧检测函数
 * @param  [in] USARTx:        USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_LIN_Wakeup_Frame_Detect(USART_TypeDef* USARTx)
{
    /* CR1设置: RE = 1 */
    REG_MODIFY(USARTx->CR1, USART_CR1_RE, USART_MODE_RX);
    /* RXD管脚边沿中断使能 */
    USART_EnableIrq(USARTx, USART_FLAG_DWK);
}

/**
 * @brief  USART LIN间隔段检测函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @param  [in] u32LowBitsNumbers: 持续位的“0”的个数，数据需 < 32
 * @retval None
 */
void USART_LIN_Break_Detect(USART_TypeDef* USARTx, uint32_t u32LowBitsNumbers)
{
    uint32_t u32ValTOR;
    uint32_t u32ValDIVI = USARTx->BRR_f.DIVI;
    uint32_t u32ValDIVF = USARTx->BRR_f.DIVF;

    /* CR1设置: RE = 1 */
    if (USART_MODE_RX != REG_READBITS(USARTx->CR1, USART_CR1_RE))
    {
        /* RE = 1 */
        REG_MODIFY(USARTx->CR1, USART_CR1_RE, USART_MODE_RX);
    }

    /* TOR = PCLK / BPS / 4^psc * u32LowBitsNumbers */
    /*     = 16 * (DIVI+1) * 256 / (128+DIVF) * u32LowBitsNumbers */
    if (USARTx->BRR_f.FBME == 0U)
    {
        u32ValTOR = u32LowBitsNumbers * 16U * (u32ValDIVI + 1U);
    }
    else
    {
        u32ValTOR = u32LowBitsNumbers * 16U * 256U * (u32ValDIVI + 1U) / (128U + u32ValDIVF);
    }

    /* TOR value limitation */
    if ((USART_TOR_TOR_Msk >> USART_TOR_TOR_Pos) < u32ValTOR)
    {
        u32ValTOR = USART_TOR_TOR_Msk >> USART_TOR_TOR_Pos;
    }
    /* RXD管脚边沿中断除能 */
    USART_DisableIrq(USARTx, USART_FLAG_DWK);

    USART_ClearFlag(USARTx, USART_FLAG_LBD);
    /* 间隔段中断使能 */
    USART_EnableIrq(USARTx, USART_FLAG_LBD);
    /* 间隔检测使能 */
    REG_SETBITS(USARTx->CR3, USART_CR3_LBDE);
    /* 使用TOE功能为同步间隔段检测，设置间隔段低电平宽度 */
    USART_LIN_TOE(USARTx, USART_TOE_Break, u32ValTOR);
    /* CR3设置: LINEN = 1 */
    REG_SETBITS(USARTx->CR3, USART_CR3_LINEN);
}

/**
 * @brief  USART LIN同步段检测函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_LIN_Sync_Detect(USART_TypeDef* USARTx)
{
    USART_ClearFlag(USARTx, USART_FLAG_ABR);
    /* 自动波特率检测中断使能 */
    USART_EnableIrq(USARTx, USART_FLAG_ABR);
    /* 自动波特率检测使能 */
    REG_SETBITS(USARTx->CR3, USART_CR3_ABRE);
    /* 使用TOE功能为波特率自动检测 */
    REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
    REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_Auto_BaudRate);
}

/**
 * @brief  USART LIN接收波特率设置函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @param  [in] u32BaudRate:       UART目标波特率
 * @param  [in] u32BaudRateOffset: UART目标波特率Offset
 * @retval None
 */
void USART_LIN_BaudRateSet_Detect(USART_TypeDef* USARTx, uint32_t u32BaudRate, uint32_t u32BaudRateOffset)
{
    uint32_t u32CalBaudRate;
    uint32_t u32BDRValue;
    uint32_t u32BaudRateMin;
    uint32_t u32BaudRateMax;

    /* 计算检测的波特率 */
    u32BDRValue    = USARTx->BDR + 1U;
    u32CalBaudRate = Sysctrl_GetPClkFreq() / (1U << (USARTx->BRR_f.PSC * 2U)) / u32BDRValue;

    /* 目标波特率设置 */
    if (0xFFFFFFFFU - u32BaudRateOffset >= u32BaudRate)
    {
        u32BaudRateMax = u32BaudRate + u32BaudRateOffset;
    }
    else
    {
        u32BaudRateMax = 0xFFFFFFFFU;
    }
    if (u32BaudRate >= u32BaudRateOffset)
    {
        u32BaudRateMin = u32BaudRate - u32BaudRateOffset;
    }
    else
    {
        u32BaudRateMin = 0U;
    }
    if (u32CalBaudRate <= u32BaudRateMax && u32CalBaudRate >= u32BaudRateMin) /* 容错范围内 */
    {
        if (u32BaudRate != u32CalBaudRate)
        {
            REG_CLEARBITS(USARTx->CR1, USART_CR1_RE);
            u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_LIN, u32CalBaudRate, Sysctrl_GetPClkFreq(), USARTx->CR1 & USART_CR1_OVER8);

            REG_SETBITS(USARTx->CR1, USART_CR1_RE);
        }
    }
}

/**
 * @brief  LIN checksum函数
 * @param  [in] u8DataBuffer:  数据buffer
 * @param  [in] u8DataLen:     数据长度
 * @retval None
 */
uint8_t LIN_Checksum(uint8_t* u8DataBuffer, uint8_t u8DataLen)
{
    uint8_t  u8Index      = 0;
    uint16_t u16CheckSum  = 0;
    uint16_t u16CheckSum1 = 0;

    for (u8Index = 0; u8Index < u8DataLen; u8Index++)
    {
        u16CheckSum = u16CheckSum + *(u8DataBuffer + u8Index);

        u16CheckSum1 = u16CheckSum >> 8;
        if (u16CheckSum1 > 0)
        {
            u16CheckSum++;
            u16CheckSum &= ~0x0100;
        }
    }

    return (uint8_t)(~u16CheckSum);
}

/**
 * @brief  LIN ID parity函数
 * @param  [in] u8ID:  IDֵ
 * @retval None
 */
uint8_t LIN_IDParity(uint8_t u8ID)
{
    uint8_t u8Parity = 0;
    uint8_t u8P0     = 0;
    uint8_t u8P1     = 0;

    u8P0 = (u8ID & 0x01) ^ ((u8ID & 0x02) >> 1) ^ ((u8ID & 0x04) >> 2) ^ ((u8ID & 0x10) >> 4);
    u8P0 = u8P0 & 0x01;
    u8P1 = ~(((u8ID & 0x02) >> 1) ^ ((u8ID & 0x08) >> 3) ^ ((u8ID & 0x10) >> 4) ^ ((u8ID & 0x20) >> 5));
    u8P1 = u8P1 & 0x01;

    u8Parity = u8ID | (u8P0 << 6U) | (u8P1 << 7U);
    return u8Parity;
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
