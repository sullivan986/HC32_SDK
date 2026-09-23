/**
 *******************************************************************************
 * @file  lpuart.c
 * @brief This file provides firmware functions to manage the LPUART.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "lpuart.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPUART LPUART模块驱动库
 * @brief LPUART Driver Library LPUART模块驱动库
 * @{
 */



/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */

/**
 * @brief  LPUART通信中断使能函数设置
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enIrqSel: 发送or接收中断使能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_EnableIrq(LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enIrqSel, TRUE);

    return Ok;
}
/**
 * @brief  LPUART通信中断禁止函数设置
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enIrqSel: 发送or接收中断禁止
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_DisableIrq(LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enIrqSel, FALSE);

    return Ok;
}
/**
 * @brief lpuart通信时钟源选择
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enSclk: 时钟源选项
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_SelSclk(LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk)
{
    ASSERT(IS_VALID_CLK(enSclk));

    LPUARTx->SCON_f.CLKSRC = (uint32_t)enSclk;

    return Ok;
}

/**
 * @brief  LPUART通道多主机模式配置
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] pstcMultiCfg: 多主机模式结构
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - ErrorInvalidParameter配置失败
 */
en_result_t LPUart_SetMultiMode(LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg)
{

    if(NULL != pstcMultiCfg)
    {
        LPUARTx->SCON_f.ADRDET = TRUE;
        LPUARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        LPUARTx->SADEN = pstcMultiCfg->u8SaddEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  LPUART单线半双工模式使能
 *
 * @param [in] LPUARTx 通道号
 *
 * @retval None
 */
void LPUart_HdModeEnable(LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = TRUE;
}


/**
 * @brief  LPUART单线半双工模式关闭
 *
 * @param [in] LPUARTx 通道号
 *
 * @retval None
 */
void LPUart_HdModeDisable(LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = FALSE;
}

/**
 * @brief  LPUART通道发送或接收等功能使能设置
 *
 * @param [in] LPUARTx:  通道号
 * @param [in] enFunc: 功能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_EnableFunc(LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enFunc, TRUE);

    return Ok;
}

/**
 * @brief  LPUART通道发送或接收等功能禁止设置
 *
 * @param [in] LPUARTx:  通道号
 * @param [in] enFunc: 功能
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_DisableFunc(LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), (uint32_t)enFunc, FALSE);

    return Ok;
}

/**
 * @brief  LPUART通道通信状态获取
 *
 * @param [in] LPUARTx: 通道号
 *
 * @retval uint8_t: 状态值
 */
uint8_t LPUart_GetIsr(LPUART_TypeDef* LPUARTx)
{
    uint32_t u32Val;
    
    u32Val = LPUARTx->ISR;
    
    return (uint8_t)u32Val;
}

/**
 * @brief  LPUART通道通信状态获取
 *
 * @param [in] LPUARTx: 通道号，
 * @param [in] enStatus: 需要获取的状态
 *
 * @retval boolean_t:
 *         - TRUE
 *         - 其他: 配置失败
 */
boolean_t LPUart_GetStatus(LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(LPUARTx->ISR)), (uint32_t)enStatus);

    return bStatus;
}

/**
 * @brief  LPUART通道通信状态全部清除
 *
 * @param [in] LPUARTx:  Lpuart通道号
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_ClrIsr(LPUART_TypeDef* LPUARTx)
{
    LPUARTx->ICR = 0u;
    return Ok;
}

/**
 * @brief  LPUART通道通信状态清除
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] enStatus: 清除哪个状态
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t LPUart_ClrStatus(LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(LPUARTx->ICR)), (uint32_t)enStatus, FALSE);

    return Ok;
}

/**
 * @brief  LPUART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u8Data: 待发送数据
 * @param [in] u32Timeout: 等待标志的超时时间
 *
 * @retval en_result_t:
 *           - Ok: 发送成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUart_SendData(LPUART_TypeDef* LPUARTx, uint8_t u8Data, uint32_t u32Timeout)
{
    uint32_t u32TimeCnt = 0u;
    
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }
    
    LPUARTx->SBUF_f.DATA = u8Data;
    
    u32TimeCnt = 0u;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }
    
    LPUart_ClrStatus(LPUARTx,LPUartTC);
    
    return Ok;
}

/**
 * @brief  LPUART通道发送数据函数,中断方式调用此函数
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u8Data: 待发送数据
 *
 * @retval en_result_t:
 *           - Ok: 发送成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUart_SendDataIt(LPUART_TypeDef* LPUARTx, uint8_t u8Data)
{
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe)){;}
    LPUARTx->SBUF_f.DATA = u8Data;

    return Ok;
}


/**
 * @brief  LPUART通道多主机模式查询发送，中断方式发送不适用
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u16Data: 第8位数据+8bit待发送数据
 * @param [in] u32Timeout: 等待标志的超时时间
 *
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorTimeout: 超时
 */
en_result_t LPUart_MultiModeSendData(LPUART_TypeDef* LPUARTx, uint16_t u16Data, uint32_t u32Timeout)
{
    uint32_t u32TimeCnt = 0u;
    
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }
    
    LPUARTx->SBUF  = (uint32_t)u16Data;
    
    u32TimeCnt = 0u;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /*  等待超时 */
            return ErrorTimeout;
        }
    }
    
    LPUart_ClrStatus(LPUARTx,LPUartTC);
    
    return Ok;
}

/**
 * @brief  LPUART通道多主机模式中断发送
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] u16Data: 第8位数据+8bit待发送数据
 *
 * @retval en_result_t：
 *         - Ok:配置成功
 *         - 其他:配置失败
 */
en_result_t LPUart_MultiModeSendDataIt(LPUART_TypeDef* LPUARTx, uint16_t u16Data)
{
    LPUARTx->SBUF  = (uint32_t)u16Data;
    
    return Ok;
}

/**
 * @brief  LPUART通道接收数据函数
 *
 * @param [in] LPUARTx:  Lpuart通道号
 *
 * @retval uint8_t：接收数据
 */
uint8_t LPUart_ReceiveData(LPUART_TypeDef* LPUARTx)
{
    uint32_t u32Val;
    
    u32Val = LPUARTx->SBUF_f.DATA;
    
    return (uint8_t)u32Val;
}

/**
 * @brief  LPUART通道初始化函数
 *
 * @param [in] LPUARTx:  Lpuart通道号
 * @param [in] pstcCfg: 初始化结构体  @ref stc_lpuart_cfg_t
 *
 * @retval en_result_t：
 *         - Ok:配置成功
 *         - 其他:配置失败
 */
en_result_t LPUart_Init(LPUART_TypeDef* LPUARTx,stc_lpuart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    const uint32_t u32Over[3] = {0x4u, 0x3u, 0x2u};
    uint16_t u16OverShift;
    uint32_t u32BaudShift;
    float32_t f32Scnt = 0.0f;

    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    LPUARTx->SCON = 0u;

    LPUARTx->SCON = (uint32_t)pstcCfg->enStopBit          |
                    (uint32_t)pstcCfg->enMmdorCk          |
                    (uint32_t)pstcCfg->stcBaud.enSclkDiv  |
                    (uint32_t)pstcCfg->stcBaud.enSclkSel  |
                    (uint32_t)pstcCfg->enRunMode;

    if(LPUartMskMode0 != pstcCfg->enRunMode)
    {
        if((LPUartMskMode1 == pstcCfg->enRunMode) || (LPUartMskMode3 == pstcCfg->enRunMode))
        {
            u16OverShift = (uint16_t)u32Over[pstcCfg->stcBaud.enSclkDiv/LPUartMsk8Or16Div];
            u32BaudShift = pstcCfg->stcBaud.u32Baud<<u16OverShift;
            f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Sclk)/(float32_t)(u32BaudShift);
            LPUARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
        }    
        LPUart_EnableFunc(LPUARTx,LPUartRenFunc);       /* 使能收发 */		
    }
    
    enRet = Ok;
    return enRet;
}


/**
 * @brief 获取RB8数值
 *
 * @param [in] LPUARTx 通道号
 *
 * @retval boolean_t：RB8
 */
boolean_t LPUart_GetRb8(LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->SBUF_f.DR8) ? TRUE : FALSE;
}
/**
 * @brief  LPUART通道多主机模式从机地址配置函数
 *
 * @param [in] LPUARTx: 通道号
 * @param [in] u8Addr: 地址
 *
 * @retval en_result_t：
 *         - Ok:配置成功
 *         - 其他:配置失败
 */
en_result_t LPUart_SetSaddr(LPUART_TypeDef* LPUARTx,uint8_t u8Addr)
{
    LPUARTx->SADDR = u8Addr;

    return Ok;
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
