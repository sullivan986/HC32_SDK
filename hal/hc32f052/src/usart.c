/**
 *******************************************************************************
 * @file  usart.c
 * @brief This file provides firmware functions to manage the USART.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usart.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */
/**
 * @defgroup DDL_USART USART子模块驱动库
 * @brief USART Driver Library USART子模块驱动库
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Functions USART全局函数定义
 * @{
 */

/**
 * @brief  USART 波特率初始化函数
 * @param  [in] USARTx:             USART类型定义      @ref USART_TypeDef
 * @param  [in] u32BaudRateSetMode: 波特率设置模式选择 @ref USART_BAUD_RATE_SET_MODE
 * @param  [in] u32BaudRate:        UART波特率
 * @param  [in] u32PCLK:            PCLK时钟
 * @param  [in] u32SampMode:        采样次数选择       @ref USART_SAMPLE_BITS_SET （时钟同步模式、红外通信模式）
 *                                                     @ref USART_Over_Sampling   （UART模式、LIN模式）
 *                                                     @ref USART_SC_BCN_SET      （智能卡接口模式）
 * @retval uint32_t：               计算的波特率
 *         - 0：                    配置失败
 *         - 非0：                  计算的波特率
 */
uint32_t USART_BaudRateCal(USART_TypeDef* USARTx, uint32_t u32BaudRateSetMode, uint32_t u32BaudRate, uint32_t u32PCLK, uint32_t u32SampMode)
{
    uint64_t u64PCLK, u64BoudRate, u64Temp, u64TempCal, u64MinOffset;
    uint32_t u32Sample         = 0U;   /* Sampel value */
    uint64_t u64TempDIVI[4]    = {0U}; /* DIVI */
    uint64_t u64TempDIVF[4]    = {0U}; /* DIVF */
    uint64_t u64CalBaudRate[4] = {0U}; /* Calculated Baud Rate */
    uint32_t u32TempIdx        = 0U;   /* Index for u32TempDIVI & u32TempDIVF */
    uint32_t u32BaudRateIdx    = 0U;   /* Index for Baud Rate */

    u64PCLK     = (uint64_t)u32PCLK;
    u64BoudRate = (uint64_t)u32BaudRate;

    if (0U != u64BoudRate)
    {
        switch (u32BaudRateSetMode)
        {
            case USART_BAUD_RATE_UART:
            case USART_BAUD_RATE_LIN:
                /* BPS = (PCLK×(128+DIVF))/(4^psc×8×(2-OVER8)×(DIVI+1)×256) */
                if (USART_OVERSAMPLING_16 == u32SampMode)
                {
                    u32Sample = 2U * 8U; /* (2-OVER8) = 2 */
                }
                else
                {
                    u32Sample = 1U * 8U; /* (2-OVER8) = 1 */
                }
                break;
            case USART_BAUD_RATE_CLKSYNC:
            case USART_BAUD_RATE_IR:
                /* CLKSYNC BPS = (PCLK×(128+DIVF))/(4^psc×4×(DIVI+1)×256) */
                /* IR      BPS = (PCLK×(128+DIVF))/(4^psc×16×(DIVI+1)×256) */
                u32Sample = u32SampMode;
                break;
            case USART_BAUD_RATE_SC:
                /* BPS = (PCLK×(128+DIVF))/(4^psc×2×BCN×(DIVI+1)×256) */
                u32Sample = 2U * u32SampMode;
                break;
            default:
                break;
        }

        if (u32Sample == 0U)
        {
            /* Invalid setting*/
            return 0U;
        }

        u64Temp = u64PCLK / (u64BoudRate * u32Sample); /* = PCLK / (BPS * 8 * (2-OVER8) */
        if (0U == u64Temp)
        {
            /* Invalid setting*/
            return 0U;
        }
        for (u32TempIdx = 0U; u32TempIdx < 4U; u32TempIdx++)
        {
            /* Cal DIVI */
            u64TempDIVI[u32TempIdx] = u64Temp >> (2U * u32TempIdx); /* = / 4^psc */
            if (256U < u64TempDIVI[u32TempIdx])                     /* DIVI <= 256 */
            {
                u64TempDIVI[u32TempIdx] = 0U;
            }
            if (0U != u64TempDIVI[u32TempIdx])
            {
                /* Cal DIVF */
                u64TempCal = u32Sample * u64TempDIVI[u32TempIdx];
                u64TempDIVF[u32TempIdx] =
                    ((((u64BoudRate * u64TempCal * 256U) << (2U * u32TempIdx)) * 10U / u64PCLK) + 5U) / 10U - 128U; /* with round up */
                if (127U < u64TempDIVF[u32TempIdx])
                {
                    /* Calcualte baud rate: DIVF is disabled */
                    u64CalBaudRate[u32TempIdx] = u64PCLK / (u64TempCal << (2U * u32TempIdx));
                }
                else
                {
                    /* Calcualte baud rate: DIVF is enabled */
                    u64CalBaudRate[u32TempIdx] = u64PCLK * (128U + u64TempDIVF[u32TempIdx]) / (u64TempCal << (2U * u32TempIdx)) / 256U;
                }
            }
        }

        /* Out of range check */
        for (u32TempIdx = 0U; u32TempIdx < 4U; u32TempIdx++)
        {
            if (u64TempDIVI[u32TempIdx] != 0U)
            {
                break;
            }
            if (u32TempIdx == 3U)
            {
                /* Invalid setting*/
                return 0U;
            }
        }

        /* Find best fit baud rate */
        u64MinOffset = 0xFFFFFFFFU;
        for (u32TempIdx = 0U; u32TempIdx < 4U; u32TempIdx++)
        {
            if (0U != u64TempDIVI[u32TempIdx])
            {
                u64Temp = (u64CalBaudRate[u32TempIdx] > u32BaudRate) ? (u64CalBaudRate[u32TempIdx] - u32BaudRate) :
                                                                       (u32BaudRate - u64CalBaudRate[u32TempIdx]);
                if (u64Temp < u64MinOffset)
                {
                    u64MinOffset   = u64Temp;
                    u32BaudRateIdx = u32TempIdx;
                }
            }
        }

        if (u32BaudRateSetMode == USART_BAUD_RATE_CLKSYNC)
        {
            /* 时钟同步最高波特率 >= PCLK/8 */
            if ((0U == u32BaudRateIdx) && (1U == u64TempDIVI[0U]))
            {
                /* Invalid setting*/
                return 0U;
            }
        }

        /* Set BRR register */
        if (128U <= u64TempDIVF[u32BaudRateIdx])
        {
            REG_WRITE(USARTx->BRR, (u32BaudRateIdx << 16U) | ((u64TempDIVI[u32BaudRateIdx] - 1U) << 8U));
        }
        else
        {
            REG_WRITE(USARTx->BRR, (u32BaudRateIdx << 16U) | ((u64TempDIVI[u32BaudRateIdx] - 1U) << 8U) | u64TempDIVF[u32BaudRateIdx] | 0x80U);
        }

        /* Feedback best fit baud rate */
        return (uint32_t)u64CalBaudRate[u32BaudRateIdx];
    }
    else
    {
        /* Invalid setting*/
        return 0U;
    }
}

/**
 * @brief  USART UART初始化函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @param  [in] pstcUARTInit:  UART初始化结构体   @ref stc_usart_uart_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_UART_Init(USART_TypeDef* USARTx, stc_usart_uart_init_t* pstcUARTInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置波特率 */
    u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_UART, pstcUARTInit->u32BaudRate, Sysctrl_GetPClkFreq(), pstcUARTInit->u32SampleMode);
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcUARTInit->stcAdvFeature.u32ClockCtrl | pstcUARTInit->stcAdvFeature.u32TxRxSwap | USART_UART_MODE
                               | pstcUARTInit->stcAdvFeature.u32TxRxPinLevelInvert | pstcUARTInit->stcAdvFeature.u32HWFlowCtrl
                               | pstcUARTInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1, pstcUARTInit->stcAdvFeature.u32TxRxCombine | pstcUARTInit->stcAdvFeature.u32StartBitDetectMode
                               | pstcUARTInit->u32SampleMode | pstcUARTInit->stcAdvFeature.u32MSBFirst | pstcUARTInit->u32StopBits
                               | pstcUARTInit->u32FrameLength | pstcUARTInit->u32Parity);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    /* Tx/Rx 使能 */
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, pstcUARTInit->u32TransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART 同步串口初始化函数
 * @param  [in] USARTx:          USART类型定义      @ref USART_TypeDef
 * @param  [in] pstcClkSyncInit: UART初始化结构体   @ref stc_usart_uart_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_ClkSync_Init(USART_TypeDef* USARTx, stc_usart_clksync_init_t* pstcClkSyncInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 内部波特率生成器生成的时钟 */
    if (USART_CLKSYNC_INT_CLK_OUTPUT_EN == pstcClkSyncInit->stcAdvFeature.u32ClockCtrl)
    {
        /* 设置波特率 */
        u32CalBaudRate =
            USART_BaudRateCal(USARTx, USART_BAUD_RATE_CLKSYNC, pstcClkSyncInit->u32BaudRate, Sysctrl_GetPClkFreq(), USART_SAMPLE_BITS_CLKSYNC);
    }
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcClkSyncInit->stcAdvFeature.u32ClockCtrl | pstcClkSyncInit->stcAdvFeature.u32TxRxSwap | USART_CLKSYNC_MODE
                               | pstcClkSyncInit->stcAdvFeature.u32TxRxPinLevelInvert | pstcClkSyncInit->stcAdvFeature.u32HWFlowCtrl
                               | pstcClkSyncInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1, USART_RX_TX_SEPARATE | USART_START_BIT_RX_EDGE | USART_OVERSAMPLING_16 | pstcClkSyncInit->stcAdvFeature.u32MSBFirst
                               | USART_STOP_1BIT | USART_FRAME_LEN_8BITS | USART_PARITY_NONE);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    /* Tx/Rx 使能 */
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, pstcClkSyncInit->u32TransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART LIN初始化函数
 * @param  [in] USARTx:        USART类型定义    @ref USART_TypeDef
 * @param  [in] pstcLinInit:   LIN初始化结构体  @ref stc_usart_lin_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_LIN_Init(USART_TypeDef* USARTx, stc_usart_lin_init_t* pstcLinInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置波特率 */
    u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_LIN, pstcLinInit->u32BaudRate, Sysctrl_GetPClkFreq(), pstcLinInit->u32SampleMode);
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcLinInit->stcAdvFeature.u32TxRxSwap | USART_UART_MODE | pstcLinInit->stcAdvFeature.u32TxRxPinLevelInvert
                               | pstcLinInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1,
        pstcLinInit->u32SampleMode | pstcLinInit->stcAdvFeature.u32MSBFirst | USART_PARITY_NONE | USART_STOP_1BIT | USART_RX_TX_SEPARATE);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    return u32CalBaudRate;
}

/**
 * @brief  USART IR初始化函数
 * @param  [in] USARTx:        USART类型定义      @ref USART_TypeDef
 * @param  [in] pstcIRInit:    IR初始化结构体   @ref stc_usart_ir_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t USART_IR_Init(USART_TypeDef* USARTx, stc_usart_ir_init_t* pstcIRInit)
{
    uint32_t u32CalBaudRate = 0U;
    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置波特率 */
    u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_IR, pstcIRInit->u32BaudRate, Sysctrl_GetPClkFreq(), USART_SAMPLE_BITS_IR);
    /* 设置38K高低电平维持时间 */
    USARTx->IR_f.DCNTH = pstcIRInit->u32HighLevelTime38K;
    USARTx->IR_f.DCNTL = pstcIRInit->u32LowLevelTime38K;
    /* CR3设置 */
    REG_WRITE(USARTx->CR3, pstcIRInit->u32IRMode | pstcIRInit->u32IRMod38K);
    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcIRInit->stcAdvFeature.u32TxRxSwap | USART_UART_MODE | pstcIRInit->stcAdvFeature.u32TxRxPinLevelInvert
                               | pstcIRInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    REG_WRITE(USARTx->CR1, USART_RX_TX_SEPARATE | USART_START_BIT_RX_EDGE | USART_OVERSAMPLING_16 | pstcIRInit->stcAdvFeature.u32MSBFirst
                               | USART_STOP_1BIT | pstcIRInit->u32FrameLength | pstcIRInit->u32Parity);

    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    /* Tx/Rx 使能 */
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, pstcIRInit->u32TransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART SmartCard初始化函数
 * @param  [in] USARTx:             USART类型定义    @ref USART_TypeDef
 * @param  [in] pstcSmartCardInit:  智能卡初始化结构体  @ref stc_usart_smart_card_init_t
 * @retval uint32_t:                设置的实际波特率
 */
uint32_t USART_SC_Init(USART_TypeDef* USARTx, stc_usart_smart_card_init_t* pstcSmartCardInit)
{
    uint32_t u32CalBaudRate = 0U;
    uint32_t u32Parity;
    uint32_t u32Cr3Val;

    /* 复位 */
    if (HC_USART0 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart0);
    }
    else if (HC_USART1 == USARTx)
    {
        Sysctrl_PeriphReset(SysctrlPeripheralUsart1);
    }
    else {}

    REG_CLEAR(USARTx->CR1);
    REG_CLEAR(USARTx->CR2);
    REG_CLEAR(USARTx->CR3);

    /* 设置时钟源波特率，智能卡模式固定16倍采样，采样计数为2*bcn */
    u32CalBaudRate =
        USART_BaudRateCal(USARTx, USART_BAUD_RATE_SC, pstcSmartCardInit->u32DataBaudRate, Sysctrl_GetPClkFreq(), pstcSmartCardInit->u32FiBCN);

    /* CR2设置 */
    REG_WRITE(USARTx->CR2, pstcSmartCardInit->stcAdvFeature.u32TxRxSwap | pstcSmartCardInit->stcAdvFeature.u32ClockCtrl
                               | pstcSmartCardInit->stcAdvFeature.u32TxRxPinLevelInvert | pstcSmartCardInit->stcAdvFeature.u32DMATxRxTransfer);
    /* CR1设置 */
    u32Parity = (USART_PARITY_EVEN == pstcSmartCardInit->u32Parity) ? USART_CR1_PCE : USART_CR1_PS | USART_CR1_PCE;
    REG_WRITE(USARTx->CR1, pstcSmartCardInit->stcAdvFeature.u32MSBFirst | USART_PARITY_NONE | USART_STOP_1BIT | USART_RX_TX_SEPARATE | u32Parity);

    /* CR3设置 */
    switch (pstcSmartCardInit->u32FiBCN)
    {
        case USART_SC_BCN_16:
            u32Cr3Val = (0ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_32:
            u32Cr3Val = (1ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_64:
            u32Cr3Val = (2ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_128:
            u32Cr3Val = (3ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_186:
            u32Cr3Val = (4ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_256:
            u32Cr3Val = (5ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_372:
            u32Cr3Val = (6ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case USART_SC_BCN_512:
            u32Cr3Val = (7ul << USART_CR3_BCN_Pos) | (pstcSmartCardInit->u32IOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        default:
            break;
    }

    REG_WRITE(USARTx->CR3, u32Cr3Val);
    /* ICR 清零 */
    REG_CLEAR(USARTx->ICR);

    return u32CalBaudRate;
}

/**
 * @brief  USART SmartCard时钟输出使能
 * @param  [in] USARTx: USART类型定义    @ref USART_TypeDef
 * @param  [in] bEn: 输出时钟使能(输出使能：TRUE，输出禁止：FALSE)
 * @retval uint32_t:                设置的实际波特率
 */
void USART_SC_CLK_Enable(USART_TypeDef* USARTx, boolean_t bEn)
{
    if (TRUE == bEn)
    {
        USARTx->CR2_f.CLKC = 1;
    }
    else
    {
        USARTx->CR2_f.CLKC = 0;
    }
}

/**
 * @brief  USART 查询发送数据
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART发送数据buffer指针
 * @param  [in] u32Size:     UART发送数据长度(8-bits数据传送: 字节数据长度; 9-bits数据传送: 半字数据长度)
 * @param  [in] u32Timeout:  UART发送超时时间
 * @retval en_result_t
 *         - Ok:             OK
 *         - ErrorTimeout:   超时错误
 */
en_result_t USART_UART_Transmit(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t  u32SizeIdx    = 0U;
    uint32_t  u32TimeoutCnt = 0U;
    uint16_t* pu16Data      = (uint16_t*)(pu8Data);
    for (u32SizeIdx = 0U; u32SizeIdx < u32Size; u32SizeIdx++)
    {
        /* 清除发送完成标志 */
        USART_ClearFlag(USARTx, USART_FLAG_TC);
        /* 写入一帧待发送的数据 */
        if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
        {
            REG_WRITE(USARTx->TDR, *pu16Data);
            pu16Data++;
        }
        else
        {
            REG_WRITE(USARTx->TDR, *pu8Data);
            pu8Data++;
        }
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
    }
    /* 清除发送完成标志 */
    USART_ClearFlag(USARTx, USART_FLAG_TC);
    return Ok;
}

/**
 * @brief  USART 中断发送
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART发送数据
 * @retval None
 */
void USART_UART_TransmitINT(USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint16_t* pu16Data = (uint16_t*)(pu8Data);
    if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
    {
        REG_WRITE(USARTx->TDR, *pu16Data);
    }
    else
    {
        REG_WRITE(USARTx->TDR, *pu8Data);
    }
}

/**
 * @brief  USART 智能卡中断发送
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     待发送数据地址
 * @retval None
 */
void USART_SC_TransmitINT(USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint32_t i = 0;
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, 2U);
    while((!REG_READBITS(USARTx->CR1, USART_CR1_TE)) && (i++ < 10000)){}
    REG_WRITE(USARTx->TDR, *pu8Data);
}

/**
 * @brief  USART 智能卡中断接收
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @retval None
 */
void USART_SC_ReceiveINT(USART_TypeDef* USARTx)
{
    uint32_t i = 0;
    REG_MODIFY(USARTx->CR1, USART_CR1_TE | USART_CR1_RE, 1U);
    while((!REG_READBITS(USARTx->CR1, USART_CR1_RE)) && (i++ < 10000)){}
}

/**
 * @brief  USART 查询接收数据
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART接收数据buffer指针
 * @param  [in] u32Size:     UART接收数据长度(8-bits数据传送: 字节数据长度; 9-bits数据传送: 半字数据长度)
 * @param  [in] u32Timeout:  UART接收超时时间
 * @retval uint32_t          UART接收返回错误码 @ref USART_UART_Error_Code
 *         - USART_UART_NoError:                                   OK
 *         - USART_UART_TimeoutError:                              超时错误
 *         - USART_UART_ParityError | FrameError | OverflowError:  接收数据校验、帧、上溢错误
 */
uint32_t USART_UART_Receive(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t  u32SizeIdx    = 0U;
    uint32_t  u32TimeoutCnt = 0U;
    uint32_t  u32Flag       = 0U;
    uint16_t* pu16Data      = (uint16_t*)(pu8Data);
    for (u32SizeIdx = 0U; u32SizeIdx < u32Size; u32SizeIdx++)
    {
        /* 查询等待SR.RC变为1 */
        while (!USART_GetFlag(USARTx, USART_FLAG_RC))
        {
            /* 检测到RXD管脚边沿，接收开始 */
            if (0U != USART_GetFlag(USARTx, USART_FLAG_DWK))
            {
                USART_ClearFlag(USARTx, USART_FLAG_DWK);
                u32TimeoutCnt = 0U;
            }
            u32TimeoutCnt++;
            if (u32Timeout <= u32TimeoutCnt)
            {
                /* 等待超时 */
                return USART_UART_TimeoutError;
            }
        }
        /* 从RDR寄存器读出数据并保存 */
        if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
        {
            *pu16Data = REG_READ(USARTx->RDR);
            pu16Data++;
        }
        else
        {
            *pu8Data = REG_READ(USARTx->RDR);
            pu8Data++;
        }
        /* 查询是否有奇偶校验错误、帧错误、上溢错误 */
        u32Flag = USART_GetFlag(USARTx, USART_FLAG_PE | USART_FLAG_FE | USART_FLAG_OR);
        if (u32Flag)
        {
            /* 有奇偶校验错误、帧错误、上溢错误其中一种或多种错误 */
            USART_ClearFlag(USARTx, USART_FLAG_PE | USART_FLAG_FE | USART_FLAG_OR);
            return u32Flag;
        }
    }
    return USART_UART_NoError;
}

/**
 * @brief  USART 中断接收
 * @param  [in] USARTx:      USART类型定义      @ref USART_TypeDef
 * @param  [in] pu8Data:     UART接收数据buffer指针
 * @retval None
 */
void USART_UART_ReceiveINT(USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint16_t* pu16Data = (uint16_t*)(pu8Data);
    if (USARTx->CR1_f.CHLEN == 1U) /* 9-bit data */
    {
        *pu16Data = REG_READ(USARTx->RDR);
    }
    else
    {
        *pu8Data = REG_READ(USARTx->RDR);
    }
}

/**
 * @brief  USART 自动波特率检测函数
 * @param  [in] USARTx:            USART类型定义              @ref USART_TypeDef
 * @param  [in] u32PSC:            PSC分频选择                @ref USART_Baud_Rate_Pre_Clock_Div
 * @retval None
 * @note   须根据目标波特率和当前PCLK设置合适的PSC分频值，以避免波特率检测溢出；须避开波特率检测范围的边缘值
 */
void USART_UART_ABR_Detect(USART_TypeDef* USARTx, uint32_t u32PSC)
{
    /* 设置PSC值 */
    REG_MODIFY(USARTx->BRR, USART_BRR_PSC, u32PSC);

    /* 自动波特率检测使能 */
    REG_SETBITS(USARTx->CR3, USART_CR3_ABRE);
    /* 使用TOE功能为波特率自动检测 */
    REG_CLEARBITS(USARTx->CR1, USART_CR1_TOE);
    REG_MODIFY(USARTx->CR1, USART_CR1_TOE, USART_TOE_Auto_BaudRate);
}

/**
 * @brief  USART 根据自动波特率检测值设置波特率函数
 * @param  [in] USARTx:       USART类型定义              @ref USART_TypeDef
 * @retval None
 */
void USART_UART_Detect_ABR_Set(USART_TypeDef* USARTx)
{
    uint32_t u32CalBaudRate;
    uint32_t u32BDRValue;
    uint32_t u32TXRXEnSta;

    /* 自动波特率检测除能 */
    REG_CLEARBITS(USARTx->CR3, USART_CR3_ABRE);

    /* 计算检测的波特率 */
    u32BDRValue    = USARTx->BDR + 1U;
    u32CalBaudRate = Sysctrl_GetPClkFreq() / (1U << (USARTx->BRR_f.PSC * 2U)) / u32BDRValue;

    /* 目标波特率设置 */
    u32TXRXEnSta = REG_READBITS(USARTx->CR1, USART_CR1_TE | USART_CR1_RE); /* 读取TX、RX使能状态 */
    if (0U == u32TXRXEnSta)                                                /* TX、RX未使能 */
    {
        u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_UART, u32CalBaudRate, Sysctrl_GetPClkFreq(), USARTx->CR1 & USART_CR1_OVER8);
    }
    else /* TX、RX任一使能 */
    {
        REG_CLEARBITS(USARTx->CR1, USART_CR1_TE | USART_CR1_RE);
        u32CalBaudRate = USART_BaudRateCal(USARTx, USART_BAUD_RATE_UART, u32CalBaudRate, Sysctrl_GetPClkFreq(), USARTx->CR1 & USART_CR1_OVER8);
        REG_SETBITS(USARTx->CR1, u32TXRXEnSta);
    }
}

/**
 * @brief  USART 获取标志位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART状态位     @ref USART_Status_Flags
 * @retval uint32_t： 状态位值
 */
uint32_t USART_GetFlag(USART_TypeDef* USARTx, uint32_t u32State)
{
    return REG_READBITS(USARTx->SR, u32State);
}

/**
 * @brief  USART 清除标志位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART状态位     @ref USART_Status_Flags
 * @retval None
 */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_CLEARBITS(USARTx->ICR, u32State);
}

/**
 * @brief  USART 中断使能
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART中断使能位
 * @retval None
 */
void USART_EnableIrq(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_SETBITS(USARTx->IER, u32State);
}

/**
 * @brief  USART 中断禁止
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART中断使能位
 * @retval None
 */
void USART_DisableIrq(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_CLEARBITS(USARTx->IER, u32State);
}

/**
 * @brief  USART 清除中断标志位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART中断使能位
 * @retval None
 */
void USART_ClearIrq(USART_TypeDef* USARTx, uint32_t u32State)
{
    REG_CLEARBITS(USARTx->ICR, u32State);
}

/**
 * @brief  USART 获取中断使能位
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @param  [in] u32State:    UART状态位     @ref USART_Status_Flags
 * @retval uint32_t： 状态位值
 */
uint32_t USART_GetIrqEn(USART_TypeDef* USARTx, uint32_t u32State)
{
    return REG_READBITS(USARTx->IER, u32State);
}

/**
 * @brief  USART IR功能开启控制
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @retval None
 */
void USART_IR_EnableIR(USART_TypeDef* USARTx)
{
    REG_SETBITS(USARTx->CR3, USART_CR3_IREN);
}

/**
 * @brief  USART IR功能关闭控制
 * @param  [in] USARTx:      USART类型定义  @ref USART_TypeDef
 * @retval None
 */
void USART_IR_DisableIR(USART_TypeDef* USARTx)
{
    REG_CLEARBITS(USARTx->CR3, USART_CR3_IREN);
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
