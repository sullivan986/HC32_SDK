/**
 *******************************************************************************
 * @file  spi.h
 * @brief This file contains all the functions prototypes of the SPI driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-26       MADS            First version
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
#ifndef __SPI_H__
#define __SPI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_SPI SPI模块驱动库
 * @{
 */ 

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI全局类型定义
 * @{
 */
 
/**
 * @brief  SPI Init structure definition
 */
typedef struct
{
    uint32_t      u32BaudRate;           /*!<   波特率分频                             @ref SPI_BAUDRATE_SELECTION */ 
    uint32_t      u32CPHA;               /*!<   时钟相位选择                           @ref SPI_CLOCK_PHASE_SELECTION */  
    uint32_t      u32CPOL;               /*!<   时钟极性选择                           @ref SPI_CLOCK_POLARITY_SELECTION */   
    uint32_t      u32Mode;               /*!<   主从模式选择                           @ref SPI_MODE_SELECTION */
    uint32_t      u32BitOrder;           /*!<   数据传输高低位顺序选择                 @ref SPI_BIT_ORDER_SELECTION */
    uint32_t      u32DataWidth;          /*!<   每帧的数据宽度                         @ref SPI_DATAWIDTH_SELECTION */
    uint32_t      u32NSS;                /*!<   配置NSS片选信号是硬件控制还是软件控制  @ref SPI_NSS_CFG */  
    uint32_t      u32TransferDirection;  /*!<   通信方式选择                           @ref SPI_TRANSFER_DIRECTION_SELECTION */
    uint32_t      u32SampleDelay;        /*!<   主机模式延后采样                       @ref SPI_SAMPLE_DELAY_SELECTION */ 
    uint32_t      u32DMAReq;             /*!<   DMA传输配置                            @ref SPI_DMA_TRANSFER_CFG */
}stc_spi_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Macros SPI全局宏定义
 * @{
 */
 
/** @defgroup Bit_definition      SPI_CR0相关位定义
  * @{
  */
#define  SPI_CR0_BRR_0                   (0x1U << SPI_CR0_BRR_Pos)
#define  SPI_CR0_BRR_1                   (0x2U << SPI_CR0_BRR_Pos)
#define  SPI_CR0_BRR_2                   (0x4U << SPI_CR0_BRR_Pos)

#define  SPI_CR0_WIDTH_0                 (0x1U << SPI_CR0_WIDTH_Pos)
#define  SPI_CR0_WIDTH_1                 (0x2U << SPI_CR0_WIDTH_Pos)
#define  SPI_CR0_WIDTH_2                 (0x4U << SPI_CR0_WIDTH_Pos)
#define  SPI_CR0_WIDTH_3                 (0x8U << SPI_CR0_WIDTH_Pos)

#define  SPI_CR0_CM_0                    (0x1U << SPI_CR0_CM_Pos)
#define  SPI_CR0_CM_1                    (0x2U << SPI_CR0_CM_Pos)
/**
  * @}
  */
  
/** @defgroup SPI_DMA_TRANSFER_CFG  DMA传输配置
  * @{
  */
#define  SPI_DMA_TRANSFER_RX_TX_DISABLE         (0x00000000UL)
#define  SPI_DMA_TRANSFER_RX_ENABLE_TX_DISABLE  (SPI_CR1_DMARXEN)
#define  SPI_DMA_TRANSFER_TX_ENABLE_RX_DISABLE  (SPI_CR1_DMATXEN)
#define  SPI_DMA_TRANSFER_RX_TX_ENABLE          (SPI_CR1_DMARXEN | SPI_CR1_DMATXEN)
/**
  * @}
  */  

/** @defgroup SPI_BAUDRATE_SELECTION  SPI主机模式波特率选择
  * @{
  */
#define  SPI_BAUDRATE_PCLK_DIV2          (0x00000000UL)
#define  SPI_BAUDRATE_PCLK_DIV4          (SPI_CR0_BRR_0)
#define  SPI_BAUDRATE_PCLK_DIV8          (SPI_CR0_BRR_1)
#define  SPI_BAUDRATE_PCLK_DIV16         (SPI_CR0_BRR_0 | SPI_CR0_BRR_1)
#define  SPI_BAUDRATE_PCLK_DIV32         (SPI_CR0_BRR_2)
#define  SPI_BAUDRATE_PCLK_DIV64         (SPI_CR0_BRR_0 | SPI_CR0_BRR_2)
#define  SPI_BAUDRATE_PCLK_DIV128        (SPI_CR0_BRR_1 | SPI_CR0_BRR_2)
/**
  * @}
  */ 

/** @defgroup SPI_CLOCK_PHASE_SELECTION  SPI串行时钟相位选择
  * @{
  */
#define  SPI_CLOCK_PHASE_1EDGE           (0x00000000UL)
#define  SPI_CLOCK_PHASE_2EDGE           (SPI_CR0_CPHA)
/**
  * @}
  */  
  
/** @defgroup SPI_CLOCK_POLARITY_SELECTION  SPI串行时钟极性选择
  * @{
  */
#define  SPI_CLOCK_POLARITY_LOW          (0x00000000UL)
#define  SPI_CLOCK_POLARITY_HIGH         (SPI_CR0_CPOL)
/**
  * @}
  */

/** @defgroup SPI_MODE_SELECTION  SPI工作模式选择
  * @{
  */
#define  SPI_MODE_SLAVE                  (0x00000000UL)        /*!<  从机模式 */
#define  SPI_MODE_MASTER                 (SPI_CR0_MSTR)        /*!<  主机模式 */
/**
  * @}
  */  
  
/** @defgroup SPI_BIT_ORDER_SELECTION  SPI串行数据高低位顺序发送选择
  * @{
  */
#define  SPI_MSB_FIRST                   (0x00000000UL)
#define  SPI_LSB_FIRST                   (SPI_CR0_LSBF)
/**
  * @}
  */  
  
/** @defgroup SPI_DATAWIDTH_SELECTION  SPI串行数据帧宽度选择
  * @{
  */
#define  SPI_DATAWIDTH_4BIT              (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1)
#define  SPI_DATAWIDTH_5BIT              (SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_6BIT              (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_7BIT              (SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_8BIT              (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2)
#define  SPI_DATAWIDTH_9BIT              (SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_10BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_11BIT             (SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_12BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_13BIT             (SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_14BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_15BIT             (SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
#define  SPI_DATAWIDTH_16BIT             (SPI_CR0_WIDTH_0 | SPI_CR0_WIDTH_1 | SPI_CR0_WIDTH_2 | SPI_CR0_WIDTH_3)
/**
  * @}
  */  
  
/** @defgroup SPI_NSS_CFG  NSS片选信号配置
  * @{
  */
#define  SPI_NSS_HARD_INPUT              (0x00000000UL)           /*!<  NSS IO的外部输入    */
#define  SPI_NSS_HARD_OUTPUT             (SPI_CR0_SSM)            /*!<  主机模式下，由SSI寄存器来决定NSS信号IO的输出值    */
#define  SPI_NSS_SOFT                    (SPI_CR0_SSM)            /*!<  从机模式下，由SSI寄存器值决定NSS信号的输入值    */
/**
  * @}
  */  
  
/** @defgroup SPI_NSS_SOFT_VAL  SPI_SSI设定值
  * @{
  */
#define  SPI_NSS_CONFIG_ENABLE           (0x00000000UL)        /*!<  片选使能    */
#define  SPI_NSS_CONFIG_DISABLE          (SPI_SSI_SSI)         /*!<  片选禁止    */
/**
  * @}
  */  
  
/** @defgroup SPI_NSS_EXT_INPUT_LEVEL  SPI_NSS管脚上输入电平
  * @{
  */
#define  SPI_NSS_EXT_INPUT_LOW_LEVEL     (0x00000000UL)        /*!<  NSS管脚上输入的是低电平    */
#define  SPI_NSS_EXT_INPUT_HIGH_LEVEL    (SPI_SR_SSLVL)        /*!<  NSS管脚上输入的是高电平    */
/**
  * @}
  */  
  
/** @defgroup SPI_TRANSFER_DIRECTION_SELECTION  SPI通讯方式选择
  * @{
  */    
#define  SPI_FULL_DUPLEX                 (0x00000000UL)                   /*!<  全双工双向    */
#define  SPI_SIMPLE_TX                   (SPI_CR0_CM_0)                   /*!<  单工只发      */
#define  SPI_SIMPLE_RX                   (SPI_CR0_CM_1)                   /*!<  单工只收      */
#define  SPI_HALF_DUPLEX                 (SPI_CR0_CM_0 | SPI_CR0_CM_1)    /*!<  单线半双工    */
/**
  * @}
  */  
  
/** @defgroup SPI_HALF_DUPLEX_DIRECTION_SELECTION  SPI半双工传输方向选择
  * @{
  */
#define  SPI_HALF_DUPLEX_RX              (0x00000000UL)        /*!<  单线半双工只收    */
#define  SPI_HALF_DUPLEX_TX              (SPI_HDOE_HDOE)       /*!<  单线半双工只发    */
/**
  * @}
  */  
  
  
/** @defgroup SPI_SAMPLE_DELAY_SELECTION  SPI主机模式延后采样
* @{
*/
#define  SPI_SAMPLE_NORMAL              (0x00000000UL)        /*!<  正常采样    */
#define  SPI_SAMPLE_DELAY               (SPI_CR0_SMP)         /*!<  延后采样    */
/**
  * @}
  */ 
  
/** @defgroup SPI_IT_SELECTION  SPI中断使能选择
  * @{
  */
#define SPI_IT_TXE                       (SPI_CR1_TXEIE)      /*!<  发送缓冲空中断  */
#define SPI_IT_RXNE                      (SPI_CR1_RXNEIE)     /*!<  接收缓冲非空中断  */
#define SPI_IT_SSF                       (SPI_CR1_SSFIE)      /*!<  从机选择输入下降沿中断  */
#define SPI_IT_SSR                       (SPI_CR1_SSRIE)      /*!<  从机选择输入上升沿中断  */
#define SPI_IT_UDF                       (SPI_CR1_UDFIE)      /*!<  从机模式下发送缓冲下溢错误中断  */
#define SPI_IT_OVF                       (SPI_CR1_OVFIE)      /*!<  接收缓冲上溢错误  */
#define SPI_IT_SSERR                     (SPI_CR1_SSERRIE)    /*!<  从机模式下的从机选择错误中断  */
#define SPI_IT_MODF                      (SPI_CR1_MODFIE)     /*!<  模式错误中断  */
/**
  * @}
  */  
  
/** @defgroup SPI_FLAG_SELECTION  SPI中断标志位选择
  * @{
  */
#define SPI_FLAG_TXE                     (SPI_SR_TXE)         /*!<  发送缓冲空 标志  */
#define SPI_FLAG_RXNE                    (SPI_SR_RXNE)        /*!<  接收缓冲非空 标志  */
#define SPI_FLAG_SSF                     (SPI_SR_SSF)         /*!<  从机选择输入下降沿 标志  */
#define SPI_FLAG_SSR                     (SPI_SR_SSR)         /*!<  从机选择输入上升沿 标志  */
#define SPI_FLAG_UDF                     (SPI_SR_UDF)         /*!<  从机模式下发送缓冲下溢错误 标志  */
#define SPI_FLAG_OVF                     (SPI_SR_OVF)         /*!<  接收缓冲上溢错误 标志  */
#define SPI_FLAG_SSERR                   (SPI_SR_SSERR)       /*!<  从机模式下的从机选择错误 标志  */
#define SPI_FLAG_MODF                    (SPI_SR_MODF)        /*!<  模式错误 标志  */
#define SPI_FLAG_BUSY                    (SPI_SR_BUSY)        /*!<  总线忙 标志  */
/**                                                          
  * @}                                                       
  */        
  
/** @defgroup SPI_CLEAR_SELECTION  SPI清除中断标志位选择
  * @{                                                       
  */   
#define SPI_CLEAR_TXE                    (SPI_ICR_TXE)         /*!<  清除 发送完成 标志  */
#define SPI_CLEAR_RXNE                   (SPI_ICR_RXNE)        /*!<  清除 接收缓冲非空 标志  */
#define SPI_CLEAR_SSF                    (SPI_ICR_SSF)         /*!<  清除 从机选择输入下降沿 标志  */
#define SPI_CLEAR_SSR                    (SPI_ICR_SSR)         /*!<  清除 从机选择输入上升沿 标志  */
#define SPI_CLEAR_UDF                    (SPI_ICR_UDF)         /*!<  清除 从机模式下发送缓冲下溢错误 标志  */
#define SPI_CLEAR_OVF                    (SPI_ICR_OVF)         /*!<  清除 接收缓冲上溢错误 标志  */
#define SPI_CLEAR_SSERR                  (SPI_ICR_SSERR)       /*!<  清除 从机模式下的从机选择错误 标志  */
#define SPI_CLEAR_MODF                   (SPI_ICR_MODF)        /*!<  清除 模式错误 标志  */
/**
  * @}
  */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SPI_Global_Functions SPI全局函数定义
 * @{
 */
en_result_t Spi_Init(SPI_TypeDef* SPIx,stc_spi_init_t* pstcInitCfg);
void SPI_Enable(SPI_TypeDef *SPIx);
void SPI_Disable(SPI_TypeDef *SPIx);
uint32_t SPI_IsEnable(SPI_TypeDef *SPIx);
void SPI_SetBaudRate(SPI_TypeDef *SPIx, uint32_t u32BaudRate);
uint32_t SPI_GetBaudRate(SPI_TypeDef *SPIx);
void SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t u32ClockPhase);
uint32_t SPI_GetClockPhase(SPI_TypeDef *SPIx);
void SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t u32ClockPolarity);
uint32_t SPI_GetClockPolarity(SPI_TypeDef *SPIx);
void SPI_SetMode(SPI_TypeDef *SPIx, uint32_t u32Mode);
uint32_t SPI_GetMode(SPI_TypeDef *SPIx);
void SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t u32TransferBitOrder);
uint32_t SPI_GetTransferBitOrder(SPI_TypeDef *SPIx);
void SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t u32DataWidth);
uint32_t SPI_GetDataWidth(SPI_TypeDef *SPIx);
void SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t u32NSSMode);
uint32_t SPI_GetNSSMode(SPI_TypeDef *SPIx);
void SPI_SlaveNSSConfig(SPI_TypeDef *SPIx, uint32_t u32NSSCfg);
void SPI_MasterNSSOutput(SPI_TypeDef *SPIx, uint32_t u32NSSCfg);
uint32_t SPI_GetNSSSoftValue(SPI_TypeDef *SPIx);
uint32_t SPI_GetNSSExtInput(SPI_TypeDef *SPIx);
void SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection);
uint32_t SPI_GetTransferDirection(SPI_TypeDef *SPIx);
void SPI_SetHalfDuplexDirection(SPI_TypeDef *SPIx, uint32_t u32TransferDirection);
uint32_t SPI_GetHalfDuplexDirection(SPI_TypeDef *SPIx);
void SPI_EnableIT(SPI_TypeDef* SPIx, uint32_t u32ITEn);
void SPI_DisableIT(SPI_TypeDef* SPIx, uint32_t u32IT);
uint32_t SPI_IsEnableIT(SPI_TypeDef* SPIx, uint32_t u32IT);
uint32_t SPI_IsActiveFlag(SPI_TypeDef* SPIx, uint32_t u32IT);
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint32_t u32IT);
void SPI_ClearFlag_ALL(SPI_TypeDef* SPIx);
void SPI_SetFlag_TXE(SPI_TypeDef* SPIx);
en_result_t Spi_SendData(SPI_TypeDef* SPIx, uint16_t u16Data);
uint16_t Spi_RWByte(SPI_TypeDef* SPIx, uint16_t u16Data);
void Spi_Slave_DummyWriteData(SPI_TypeDef* SPIx, uint16_t u16Data);
en_result_t Spi_Send_Rec_Buf(SPI_TypeDef* SPIx, uint16_t pu16SendBuf[],uint16_t pu16RecBuf[], uint32_t u32Len);
uint16_t Spi_ReceiveData(SPI_TypeDef* SPIx);


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

#endif /* __SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
