/**
 *******************************************************************************
 * @file  spi.c
 * @brief This file provides firmware functions to manage the SPI.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-26       MADS             First version
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
#include "spi.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SPI SPI模块驱动库
 * @brief SPI Driver Library SPI模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
 
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup SPI_Global_Functions SPI全局函数定义
 * @{
 */

/**
 * @brief  SPI 总体初始化函数.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] pstcInitCfg: 初始化结构体 @ref stc_spi_init_t
 * @retval en_result_t:
 *         Ok: SPI初始化成功
 */
en_result_t Spi_Init(SPI_TypeDef* SPIx, stc_spi_init_t *pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);
    
    REG_MODIFY(  SPIx->CR0
               , 
                 SPI_CR0_BRR
               | SPI_CR0_CPHA
               | SPI_CR0_CPOL
               | SPI_CR0_MSTR
               | SPI_CR0_LSBF
               | SPI_CR0_WIDTH
               | SPI_CR0_SSM
               | SPI_CR0_CM
               | SPI_CR0_SMP
               , 
                 pstcInitCfg->u32BaudRate                       
               | pstcInitCfg->u32CPHA                           
               | pstcInitCfg->u32CPOL                           
               | pstcInitCfg->u32Mode                           
               | pstcInitCfg->u32BitOrder                       
               | pstcInitCfg->u32DataWidth                      
               | pstcInitCfg->u32NSS                            
               | pstcInitCfg->u32TransferDirection
               | pstcInitCfg->u32SampleDelay
               );                                                                                            
               
    
    REG_MODIFY(SPIx->CR1, (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN), pstcInitCfg->u32DMAReq);
               
    return Ok;
}


/**
 * @brief  开启SPI模块.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void SPI_Enable(SPI_TypeDef *SPIx)
{
    REG_SETBITS(SPIx->CR0, SPI_CR0_EN);
}


/**
 * @brief  禁止SPI模块.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void SPI_Disable(SPI_TypeDef *SPIx)
{
    REG_CLEARBITS(SPIx->CR0, SPI_CR0_EN);   
}

/**
 * @brief  检查SPI模块是否已开启.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval uint32_t:
 *         - 0:   未开启
 *         - 非0: 已开启
 */
uint32_t SPI_IsEnable(SPI_TypeDef *SPIx)
{
    uint32_t res = (REG_READBITS(SPIx->CR0, SPI_CR0_EN) == SPI_CR0_EN)?(1U):(0U);
    return res; 
}

/**
 * @brief  设置SPI模块DMA传输.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u32DMAReq: DMA请求配置 @ref SPI_DMA_TRANSFER_CFG
 * @retval None
 */
void SPI_SetDMAReq(SPI_TypeDef *SPIx, uint32_t u32DMAReq)
{
    REG_MODIFY(SPIx->CR1, (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN), u32DMAReq);
}


/**
 * @brief  获取SPI模块DMA传输.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval uint32_t: DMA请求配置 @ref SPI_DMA_TRANSFER_CFG
 */
uint32_t SPI_GetDMAReq(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR1, (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN)));    
}


/**
 * @brief  设定SPI主机模式波特率.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32BaudRate: 波特率 @ref SPI_BAUDRATE_SELECTION 
 * @retval None
 */
void SPI_SetBaudRate(SPI_TypeDef *SPIx, uint32_t u32BaudRate)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_BRR, u32BaudRate);    
}


/**
 * @brief  设定SPI主机模式波特率.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 波特率 @ref SPI_BAUDRATE_SELECTION 
 */
uint32_t SPI_GetBaudRate(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_BRR));    
}


/**
 * @brief  设定SPI串行时钟相位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ClockPhase: 时钟相位选择 @ref SPI_CLOCK_PHASE_SELECTION 
 * @retval NONE
 */
void SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t u32ClockPhase)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_CPHA, u32ClockPhase); 
}


/**
 * @brief  获取SPI串行时钟相位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 时钟相位选择 @ref SPI_CLOCK_PHASE_SELECTION 
 */
uint32_t SPI_GetClockPhase(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_CPHA));   
}


/**
 * @brief  设定SPI串行时钟极性选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ClockPolarity: 时钟极性选择 @ref SPI_CLOCK_POLARITY_SELECTION 
 * @retval None
 */
void SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t u32ClockPolarity)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_CPOL, u32ClockPolarity);  
}


/**
 * @brief  获取SPI串行时钟极性选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 时钟极性选择 @ref SPI_CLOCK_POLARITY_SELECTION 
 */
uint32_t SPI_GetClockPolarity(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_CPOL));   
}


/**
 * @brief  设定SPI模式，主机模式或者从机模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32Mode: 模式选择 @ref SPI_MODE_SELECTION 
 * @retval None
 */
void SPI_SetMode(SPI_TypeDef *SPIx, uint32_t u32Mode)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_MSTR, u32Mode);
}


/**
 * @brief  获取SPI模式，主机模式或者从机模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 模式选择 @ref SPI_MODE_SELECTION 
 */
uint32_t SPI_GetMode(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_MSTR));   
}



/**
 * @brief  设定SPI数据传输高低位顺序.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransferBitOrder: 数据传输高低位顺序选择 @ref SPI_BIT_ORDER_SELECTION 
 * @retval None
 */
void SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t u32TransferBitOrder)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_LSBF, u32TransferBitOrder);   
}


/**
 * @brief  获取SPI数据传输高低位顺序.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t:数据传输高低位顺序选择 @ref SPI_BIT_ORDER_SELECTION 
 */
uint32_t SPI_GetTransferBitOrder(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_LSBF));   
}


/**
 * @brief  设定SPI每帧的数据宽度.
 * @param  [in] SPIx :SPI结构体变量                        @ref SPI_TypeDef
 * @param  [in] u32DataWidth : 数据宽度                    @ref SPI_DATAWIDTH_SELECTION 
 * @retval None
 */
void SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t u32DataWidth)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_WIDTH, u32DataWidth); 
}


/**
 * @brief  获取SPI每帧的数据宽度.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 数据宽度 @ref SPI_DATAWIDTH_SELECTION 
 */
uint32_t SPI_GetDataWidth(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_WIDTH));  
}


/**
 * @brief  设定SPI NSS模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSMode:  NSS从机选择 @ref SPI_NSS_CFG 
 * @retval None
 */
void SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t u32NSSMode)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_SSM, u32NSSMode); 
}


/**
 * @brief  获取SPI NSS模式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: NSS从机选择 @ref SPI_NSS_CFG 
 */
uint32_t SPI_GetNSSMode(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_SSM));    
}


/**
 * @brief  SPI模块作为从机时，配置NSS片选使能或禁止，只有当SSM=1，即软件控制(非外部IO管脚输入)时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSCfg: NSS选择 @ref SPI_NSS_CFG 
 * @retval None
 */
void SPI_SlaveNSSConfig(SPI_TypeDef *SPIx, uint32_t u32NSSCfg)
{
    REG_MODIFY(SPIx->SSI, SPI_SSI_SSI, u32NSSCfg);
}


/**
 * @brief  SPI模块作为主机 配置NSS片选输出(到从机)，只有当SSM=1，即硬件控制输出(外部IO管脚NSS输出)时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32NSSCfg: NSS选择 @ref SPI_NSS_CFG 
 * @retval None
 */
void SPI_MasterNSSOutput(SPI_TypeDef *SPIx, uint32_t u32NSSCfg)
{
    REG_MODIFY(SPIx->SSI, SPI_SSI_SSI, u32NSSCfg);
}

/**
 * @brief  获取SPI SSI的值， 只有SSM=1时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 片选使能位状态 @ref SPI_NSS_SOFT_VAL
 */
uint32_t SPI_GetNSSSoftValue(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->SSI, SPI_SSI_SSI));
}


/**
 * @brief  获取SPI SSI的值，只有SSM=1时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 外部NSS管脚返回电平 @ref SPI_NSS_EXT_INPUT_LEVEL
 */
uint32_t SPI_GetNSSExtInput(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->SR, SPI_SR_SSLVL));
}


/**
 * @brief  设定SPI 通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransferDirection: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION 
 * @retval None
 */
void SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection)
{
    REG_MODIFY(SPIx->CR0, SPI_CR0_CM, u32TransferDirection);
}


/**
 * @brief  获取SPI 通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION 
 */
uint32_t SPI_GetTransferDirection(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->CR0, SPI_CR0_CM)); 
}


/**
 * @brief  设定SPI 半双工通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32TransferDirection: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION 
 * @retval None
 */
void SPI_SetHalfDuplexDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection)
{
    REG_MODIFY(SPIx->HDOE, SPI_HDOE_HDOE, u32TransferDirection);
}


/**
 * @brief  获取SPI 半双工通信方式.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval uint32_t: 通信方式选择 @ref SPI_TRANSFER_DIRECTION_SELECTION 
 */
uint32_t SPI_GetHalfDuplexDirection(SPI_TypeDef *SPIx)
{
    return (uint32_t)(REG_READBITS(SPIx->HDOE, SPI_HDOE_HDOE)); 
}


/**
 * @brief  SPI 中断使能.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32ITEn: SPI中断使能选择位 @ref SPI_IT_SELECTION 
 * @retval None
 */
void SPI_EnableIT(SPI_TypeDef* SPIx, uint32_t u32ITEn)
{
    REG_SETBITS(SPIx->CR1, u32ITEn);
}


/**
 * @brief  SPI中断 禁止.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI中断使能选择位 @ref SPI_IT_SELECTION 
 * @retval None 
 */
void SPI_DisableIT(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    REG_CLEARBITS(SPIx->CR1, u32IT);
}


/**
 * @brief  检查 中断 是否已使能.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI中断使能选择位 @ref SPI_IT_SELECTION  
 * @retval uint32_t :中断状态     
 *         - 0:未开启
 *         - 非0:已开启
 */
uint32_t SPI_IsEnableIT(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    uint32_t res = (REG_READBITS(SPIx->CR1, u32IT) == u32IT)?(1U):(0U);
    return res; 
}


/**
 * @brief  获取 SPI 中断标志位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI中断使能选择位 @ref SPI_FLAG_SELECTION  
 * @retval uint32_t :中断状态     
 *         - 0:未发生中断
 *         - 非0:发生中断
 */
uint32_t SPI_IsActiveFlag(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    uint32_t res = (REG_READBITS(SPIx->SR, u32IT) == u32IT)?(1U):(0U);
    return res;  
}


/**
 * @brief  清除 SPI 中断标志位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] u32IT: SPI清除中断标志位选择 @ref SPI_CLEAR_SELECTION 
 * @retval None 
 */
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint32_t u32IT)
{
    REG_CLEARBITS(SPIx->ICR, u32IT);    
}

/**
 * @brief  清除 SPI 所有中断 标志.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval NONE 
 */
void SPI_ClearFlag_ALL(SPI_TypeDef* SPIx)
{
    SPIx->ICR = (uint32_t)(0);   
}



/**
 * @brief SPI 发送缓冲空标志 置位.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @retval None 
 */
void SPI_SetFlag_TXE(SPI_TypeDef* SPIx)
{
    REG_CLEARBITS(SPIx->ICR, SPI_ICR_TXE);  
}


/**
 * @brief  SPI 发送一数据函数.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data: 发送数据
 * @retval en_result_t:
 *         - Ok: 发送成功
 */
en_result_t Spi_SendData(SPI_TypeDef* SPIx, uint16_t u16Data)
{
    SPIx->DR = u16Data;

    return Ok;
}

/**
 * @brief  SPI 读/写一数据函数.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data: 发送一数据
 * @retval uint8_t:接收一数据
 */
uint16_t Spi_RWByte(SPI_TypeDef* SPIx, uint16_t u16Data)
{
    while(FALSE == SPIx->SR_f.TXE)
    {
     }
    SPIx->DR = u16Data;
    while(FALSE == SPIx->SR_f.RXNE)
    {
    }
    return (uint16_t)(SPIx->DR);
}

/**
 * @brief  SPI 从机预准备第一个数据
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] u16Data: 预准备第一个数据
 * @retval None
 */
void Spi_Slave_DummyWriteData(SPI_TypeDef* SPIx, uint16_t u16Data)
{
    while(FALSE == SPIx->SR_f.TXE)
    {
    }
    SPIx->DR = u16Data;
}


/**
 * @brief  SPI 连续发送接收多个数据函数
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @param  [in] pu16SendBuf: 发送数据指针
 * @param  [in] pu16RecBuf: 接收数据指针
 * @param  [in] u32Len: 发送数据长度
 * @retval en_result_t:
 *         - Ok: SPI初始化成功
 */
en_result_t Spi_Send_Rec_Buf(SPI_TypeDef* SPIx, uint16_t pu16SendBuf[],uint16_t pu16RecBuf[], uint32_t u32Len)
{
    uint32_t u32Index = 0u;

    for(u32Index = 0u; u32Index<u32Len; u32Index++)
    {
        while(FALSE == SPIx->SR_f.TXE)
        {
        }
        
        SPIx->DR = pu16SendBuf[u32Index];
        
        while(FALSE == SPIx->SR_f.RXNE)
        {
        }
        
        pu16RecBuf[u32Index] = (uint16_t)SPIx->DR;
    }

    while(FALSE == SPIx->SR_f.TXE)
    {
    }
    while(TRUE == SPIx->SR_f.BUSY)
    {
    }

    return Ok;
}

/**
 * @brief  SPI 接收一数据函数
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval uint8_t:接收一数据
 */
uint16_t Spi_ReceiveData(SPI_TypeDef* SPIx)
{
    return (uint16_t)SPIx->DR;
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
