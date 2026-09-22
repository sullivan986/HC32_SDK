/**
 *******************************************************************************
 * @file  i2cslv.h
 * @brief This file contains all the functions prototypes of the I2CSLV driver
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

#ifndef __I2CSLV_H__
#define __I2CSLV_H__

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
 * @addtogroup DDL_I2CSLV I2CSLV模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup I2CSLV_Global_Types I2CSLV全局类型定义
 * @{
 */
/**
 * @brief I2C从机初始化配置结构
 */
typedef struct
{
    uint32_t        u32Filter;              /*!<  滤波配置  @ref I2CSLV_FILTER_SELECTION */ 
    uint32_t        u32RxSampleDot;         /*!<  接收采样位置配置  @ref I2CSLV_RX_SAMPLE_DOT_SELECTION */ 
    uint32_t        u32DriveStrength;       /*!<  SDA由0变1时驱动能力配置  @ref I2CSLV_HIGH_DRIVE_SELECTION */ 
    uint32_t        u32AddrClkForceStretch; /*!<  地址时钟强制延长配置  @ref I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION */ 
    uint32_t        u32TimeOut;             /*!<  SCL低电平超时配置  超时长度=(u32TimeOut+1)*64*(1/PCLK),详见文档 */ 
    uint32_t        u32Broadcast;           /*!<  广播地址配置  @ref I2CSLV_BROADCAST_SELECTION */ 
    uint32_t        u32DMAReq;              /*!<  DMA请求使能配置  @ref I2CSLV_DMA_REQUEST_SELECTION */ 
    uint32_t        u32HSMODE;              /*!<  高速模式配置  @ref I2CSLV_HIGH_SPEED_MODE_SELECTION */ 
    uint32_t        u32SlaveAddr0;          /*!<  从机地址0  最长有效地址10bit */ 
    uint32_t        u32SlaveAddr0Mask;      /*!<  从机地址0掩码  最长有效地址10bit */ 
    uint32_t        u32SlaveAddr1;          /*!<  从机地址1 最长有效地址10bit */ 
    uint32_t        u32SlaveAddr2;          /*!<  从机地址2  最长有效地址10bit */ 
    uint32_t        u32SlaveAddr3;          /*!<  从机地址3  最长有效地址10bit */ 
}stc_i2cslv_init_cfg_t;
/**
 * @}
 */

/******************************************************************************
 * Global pre-processor symbols/macros ('#define')                            *
 ******************************************************************************/
/**
 * @defgroup I2CSLV_Global_Macros I2CSLV全局宏定义
 * @{
 */

/** @defgroup Bit definition
  * @{
  */
#define  I2CSLV_RSR_NS_0                       (0x1<<I2CSLV_RSR_NS_Pos)
#define  I2CSLV_RSR_NS_1                       (0x2<<I2CSLV_RSR_NS_Pos)

#define  I2CSLV_ODDR_ODPU_0                    (0x1<<I2CSLV_ODDR_ODPU_Pos)
#define  I2CSLV_ODDR_ODPU_1                    (0x2<<I2CSLV_ODDR_ODPU_Pos)

#define  I2CSLV_FLT_FW_0                       (0x1<<I2CSLV_FLT_FW_Pos)
#define  I2CSLV_FLT_FW_1                       (0x2<<I2CSLV_FLT_FW_Pos)
#define  I2CSLV_FLT_FW_2                       (0x4<<I2CSLV_FLT_FW_Pos)
/**
  * @}
  */

/** @defgroup I2CSLV_ACK_SELECTION  从机响应配置
  * @{
  */
#define I2CSLV_ACK                              (0x00000000UL)         /*!<  从机响应主机，主机收到ACK  */
#define I2CSLV_NACK                             (I2CSLV_CR_BUSY)       /*!<  从机不响应主机，主机收到NACK  */
/**
  * @}
  */

/** @defgroup I2CSLV_HIGH_SPEED_MODE_SELECTION  高速模式控制
  * @{
  */
#define  I2CSLV_HIGH_SPEED_MODE_DISABLE         (0x00000000UL)         /*!<  标准和快速模式，I2CSLV_DOUTR没有数据时强制SCL电平延长  */
#define  I2CSLV_HIGH_SPEED_MODE_ENABLE          (I2CSLV_CR_FSCLC)      /*!<  高速模式，I2CSLV_DOUTR没有数据时不强制SCL电平延长，回复NACK  */
/**
  * @}
  */

/** @defgroup I2CSLV_BROADCAST_SELECTION  广播地址是否使能配置
  * @{
  */
#define  I2CSLV_BROADCAST_DISABLE               (0x00000000UL)   /*!<  使能I2CSLV 广播地址  */
#define  I2CSLV_BROADCAST_ENABLE                (I2CSLV_CR_GC)   /*!<  禁止I2CSLV 广播地址  */
/**
  * @}
  */

/** @defgroup I2CSLV_DMA_REQUEST_SELECTION  DMA请求选择
  * @{
  */
#define I2CSLV_DMA_REQUEST_RX_TX_DISABLE        (0x00000000UL)                       /*!<  使能I2CSLV 从机TX RX DMA请求禁止  */
#define I2CSLV_DMA_REQUEST_RX_ENABLE            (I2CSLV_CR_DMARE)                    /*!<  从机RX DMA请求使能  */
#define I2CSLV_DMA_REQUEST_TX_ENABLE            (I2CSLV_CR_DMATE)                    /*!<  从机TX DMA请求使能  */
#define I2CSLV_DMA_REQUEST_RX_TX_ENABLE         (I2CSLV_CR_DMARE | I2CSLV_CR_DMATE)  /*!<  从机TX RX DMA请求使能  */
/**
  * @}
  */

/** @defgroup I2CSLV_IT_SELECTION  中断选择
  * @{
  */
#define I2CSLV_IT_RD                    (I2CSLV_IER_RD)        
#define I2CSLV_IT_WR                    (I2CSLV_IER_WR)
#define I2CSLV_IT_STOP                  (I2CSLV_IER_STOP)
#define I2CSLV_IT_START                 (I2CSLV_IER_START)
#define I2CSLV_IT_NACK                  (I2CSLV_IER_NACK)
#define I2CSLV_IT_I2CINT                (I2CSLV_IER_I2CINT)
#define I2CSLV_IT_ACTIVE                (I2CSLV_IER_ACTIVE)
#define I2CSLV_IT_HSMODE                (I2CSLV_IER_HSMODE)
#define I2CSLV_IT_TIMEOUT               (I2CSLV_IER_TIMEOUT)
#define I2CSLV_IT_ACK                   (I2CSLV_IER_ACK)
#define I2CSLV_IT_SLADDR0               (I2CSLV_IER_SLADDR0)
#define I2CSLV_IT_SLADDR1               (I2CSLV_IER_SLADDR1)
#define I2CSLV_IT_SLADDR2               (I2CSLV_IER_SLADDR2)
#define I2CSLV_IT_SLADDR3               (I2CSLV_IER_SLADDR3)
#define I2CSLV_IT_TXE                   (I2CSLV_IER_TXE)
#define I2CSLV_IT_RXNE                  (I2CSLV_IER_RXNE)
#define I2CSLV_IT_GC                    (I2CSLV_IER_GC)
/**
  * @}
  */

/** @defgroup I2CSLV_FLAG_SELECTION  中断标志位选择
  * @{
  */
#define I2CSLV_FLAG_RD                  (I2CSLV_SR_RD)
#define I2CSLV_FLAG_WR                  (I2CSLV_SR_WR)
#define I2CSLV_FLAG_STOP                (I2CSLV_SR_STOP)
#define I2CSLV_FLAG_START               (I2CSLV_SR_START)
#define I2CSLV_FLAG_NACK                (I2CSLV_SR_NACK)
#define I2CSLV_FLAG_I2CINT              (I2CSLV_SR_I2CINT)
#define I2CSLV_FLAG_ACTIVE              (I2CSLV_SR_ACTIVE)
#define I2CSLV_FLAG_HSMODE              (I2CSLV_SR_HSMODE)
#define I2CSLV_FLAG_TIMEOUT             (I2CSLV_SR_TIMEOUT)
#define I2CSLV_FLAG_ACK                 (I2CSLV_SR_ACK)
#define I2CSLV_FLAG_SLADDR0             (I2CSLV_SR_SLADDR0)
#define I2CSLV_FLAG_SLADDR1             (I2CSLV_SR_SLADDR1)
#define I2CSLV_FLAG_SLADDR2             (I2CSLV_SR_SLADDR2)
#define I2CSLV_FLAG_SLADDR3             (I2CSLV_SR_SLADDR3)
#define I2CSLV_FLAG_TXE                 (I2CSLV_SR_TXE)
#define I2CSLV_FLAG_RXNE                (I2CSLV_SR_RXNE)
#define I2CSLV_FLAG_GC                  (I2CSLV_SR_GC)
/**
  * @}
  */

/** @defgroup I2CSLV_RX_SAMPLE_DOT_SELECTION  接收采样位置选择
  * @{
  */
#define  I2CSLV_RX_SAMPLE_DOT_0CYCLE    (0x00000000UL)                      /*!<  SCL下降沿时采样  */
#define  I2CSLV_RX_SAMPLE_DOT_1CYCLE    (I2CSLV_RSR_NS_0)                   /*!<  从SCL下降沿往回计时，第1个PCLK采样  */
#define  I2CSLV_RX_SAMPLE_DOT_2CYCLE    (I2CSLV_RSR_NS_1)                   /*!<  从SCL下降沿往回计时，第2个PCLK采样  */
#define  I2CSLV_RX_SAMPLE_DOT_3CYCLE    (I2CSLV_RSR_NS_0 | I2CSLV_RSR_NS_1) /*!<  从SCL下降沿往回计时，第3个PCLK采样  */
/**
  * @}
  */

/** @defgroup I2CSLV_HIGH_DRIVE_SELECTION  强驱高电平宽度选择
  * @{
  */
#define  I2CSLV_HIGH_DRIVE_NONE         (0x00000000UL)                           /*!<  由外部上拉电阻拉高，无强驱  */
#define  I2CSLV_HIGH_DRIVE_1PCLK        (I2CSLV_ODDR_ODPU_0)                     /*!<  输出1个PCLK宽度的强驱高电平，后续由上拉电阻维持  */
#define  I2CSLV_HIGH_DRIVE_2PCLK        (I2CSLV_ODDR_ODPU_1)                     /*!<  输出2个PCLK宽度的强驱高电平，后续由上拉电阻维持  */
#define  I2CSLV_HIGH_DRIVE_4PCLK        (I2CSLV_ODDR_ODPU_0 | I2CSLV_ODDR_ODPU_1)/*!<  输出4个PCLK宽度的强驱高电平，后续由上拉电阻维持  */
/**
  * @}
  */

/** @defgroup I2CSLV_FILTER_SELECTION  滤波宽度选择
  * @{
  */
#define  I2CSLV_FILTER_NONE             (0x00000000UL)                                          /*!<  无滤波  */
#define  I2CSLV_FILTER_1PCLK            (I2CSLV_FLT_FW_0)                                       /*!<  1个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_2PCLK            (I2CSLV_FLT_FW_1)                                       /*!<  2个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_3PCLK            (I2CSLV_FLT_FW_0 | I2CSLV_FLT_FW_1)                     /*!<  3个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_4PCLK            (I2CSLV_FLT_FW_2)                                       /*!<  4个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_8PCLK            (I2CSLV_FLT_FW_0 | I2CSLV_FLT_FW_2)                     /*!<  8个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_12PCLK           (I2CSLV_FLT_FW_1 | I2CSLV_FLT_FW_2)                     /*!<  12个PCLK宽度的滤波  */
#define  I2CSLV_FILTER_16PCLK           (I2CSLV_FLT_FW_0 | I2CSLV_FLT_FW_1 | I2CSLV_FLT_FW_2)   /*!<  16个PCLK宽度的滤波  */
/**
  * @}
  */

/** @defgroup I2CSLV_ADDR_SELECTION  从机地址号选择
  * @{
  */
#define  I2CSLV_ADDR0   0     /*!<  从机地址0  */
#define  I2CSLV_ADDR1   1     /*!<  从机地址1  */
#define  I2CSLV_ADDR2   2     /*!<  从机地址2  */
#define  I2CSLV_ADDR3   3     /*!<  从机地址3  */
/**
  * @}
  */

/** @defgroup I2CSLV_ADDR_LENGTH_SELECTION  从机地址长度选择
  * @{
  */
#define  I2CSLV_ADDR_LENGTH_7BIT        (0x00000000UL)       /*!<  7位地址长度  */
#define  I2CSLV_ADDR_LENGTH_10BIT       (I2CSLV_SLADR0_AM)   /*!<  10位地址长度  */
/**
  * @}
  */

/** @defgroup I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION  地址匹配后时钟是否强制延长设置
  * @{
  */
#define  I2CSLV_ADDR_CLOCK_FORCE_STRETCH_DISABLE    (0x00000000UL)        /*!<  地址匹配后时钟不强制SCL电平延长  */
#define  I2CSLV_ADDR_CLOCK_FORCE_STRETCH_ENABLE     (I2CSLV_ADMR0_FACS)   /*!<  地址匹配后时钟强制SCL电平延长  */
/**
  * @}
  */

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
 * @addtogroup I2CSLV_Global_Functions I2CSLV全局函数定义
 * @{
 */
 
en_result_t I2CSLV_Init(stc_i2cslv_init_cfg_t *pstcInitCfg);
void I2CSLV_Enable(void);
void I2CSLV_Disable(void);
uint32_t I2CSLV_IsEnable(void);
void I2CSLV_SetAck(uint32_t u32Ack);
uint32_t I2CSLV_GetAck(void);
void I2CSLV_SetHsmodeForceStretch(uint32_t u32ClkForceStretch);
uint32_t I2CSLV_GetHsmodeForceStretch(void);
void I2CSLV_EnableBroadcast(void);
void I2CSLV_DisableBroadcast(void);
uint32_t I2CSLV_IsEnableBroadcast(void);
void I2CSLV_SetDMAReq(uint32_t u32DmaReq);
uint32_t I2CSLV_GetDMAReq(void);
void I2CSLV_EnableIT(uint32_t u32IrqCfg);
void I2CSLV_DisableIT(uint32_t u32IrqCfg);
uint32_t I2CSLV_IsEnableIT(uint32_t u32IrqCfg);
uint32_t I2CSLV_IsActiveFlag(uint32_t u32IrqFlag);
uint32_t I2CSLV_GetState(void);
void I2CSLV_ClearFlag(uint32_t u32IrqFlag);
void I2CSLV_ClearFlag_ALL(void);
void I2CSLV_SetFlag_TXE(void);
void I2CSLV_SetDeviceID(uint32_t u32RID, uint32_t u32PID, uint32_t u32MID);
uint32_t I2CSLV_GetDeviceID(void);
void I2CSLV_SetRxSampleDot(uint32_t u32SampleDot);
uint32_t I2CSLV_GetRxSampleDot(void);
void I2CSLV_SetDriveStrength(uint32_t u32HighDrive);
uint32_t I2CSLV_GetDriveStrength(void);
void I2CSLV_SetTimeOut(uint32_t u32TimeOver);
uint32_t I2CSLV_GetTimeOut(void);
void I2CSLV_SetFilter(uint32_t u32Filter);
uint32_t I2CSLV_GetFilter(void);
void I2CSLV_SetAddress(uint32_t u32AddrNum, uint32_t u32AddrLength, uint32_t u32Addr);
uint32_t I2CSLV_GetAddress(uint32_t u32AddrNum);
uint32_t I2CSLV_GetAddressLength(uint32_t u32AddrNum);
void I2CSLV_SetAddress0Mask(uint32_t u32Address0Mask);
uint32_t I2CSLV_GetAddress0Mask(void);
uint32_t I2CSLV_GetReceivedAddr(void);
uint32_t I2CSLV_GetReceivedAddrLength(void);
void I2CSLV_SetAddrClockForceStretch(uint32_t u32ClkForceStretch);
uint32_t I2CSLV_GetAddrClockForceStretch(void);
void I2CSLV_WriteByte(uint8_t u8Data);
uint8_t I2CSLV_ReadByte(void);
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

#endif /* __I2CSLV_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


