/**
 *******************************************************************************
 * @file  dmac.h
 * @brief This file contains all the functions prototypes of the dmac driver
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
#ifndef __DMAC_H__
#define __DMAC_H__

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
 * @addtogroup DDL_DMAC DMAC模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DMAC_Global_Types DMAC全局类型定义
 * @{
 */
/**
 * @brief  DMA 通道
 */
typedef enum
{
    DmaCh0      = 0x00U, /*!< DMA 通道0 */
    DmaCh1      = 0x10U, /*!< DMA 通道1 */
    DmaCh2      = 0x20U, /*!< DMA 通道2 */
    DmaCh3      = 0x30U, /*!< DMA 通道3 */
    DmaCh4      = 0x40U, /*!< DMA 通道4 */
} en_dma_channel_t;

/**
 * @brief  DMA 优先级
 */
typedef enum
{
    DmaMskPriorityFix   = 0x00000000U, /*!< DMA 各通道优先级固定 (CH0>CH1) */
    DmaMskPriorityLoop  = 0x10000000U, /*!< DMA 各通道优先级采用轮询方式 */
} en_dma_priority_t;

/**
 * @brief  DMA 传输数据宽度
 */
typedef enum
{
    DmaMsk8Bit      = 0x00000000U, /*!< 8 bit  字节传输 */
    DmaMsk16Bit     = 0x04000000U, /*!< 16 bit 半字传输 */
    DmaMsk32Bit     = 0x08000000U, /*!< 32 bit 字传输 */
} en_dma_transfer_width_t;

/**
 * @brief  DMA 传输模式：块(Block)传输或者突发(Burst)传输
 */
typedef enum
{
    DmaMskBlock     = 0x00000000U, /*!< 块(Block)传输 */
    DmaMskBurst     = 0x10000000U, /*!< 突发(Burst)传输 */
} en_dma_transfer_mode_t;

/**
 * @brief  DMA 传输当前状态
 */ 
typedef enum
{
    DmaDefault          = 0U, /*!< 初始值 */
    DmaAddOverflow      = 1U, /*!< 传输错误引起中止（地址溢出） */
    DmaHALT             = 2U, /*!< 传输停止请求引起中止（外设停止请求引起的停止或者EB/DE位引起的禁止传输） */
    DmaAccSCRErr        = 3U, /*!< 传输错误引起中止（传输源地址访问错误） */
    DmaAccDestErr       = 4U, /*!< 传输错误引起中止（传输目的地址访问错误） */
    DmaTransferComplete = 5U, /*!< 成功传输完成 */
    DmaTransferPause    = 7U, /*!< 传输暂停 */
} en_dma_stat_t;

/**
 * @brief  DMA 源地址控制模式：自增或固定
 */ 
typedef enum
{    
    DmaMskSrcAddrInc    = 0x00000000U, /*!< 地址自增 */
    DmaMskSrcAddrFix    = 0x02000000U, /*!< 地址固定 */
} en_src_address_mode_t;

/**
 * @brief  DMA 目的地址控制模式：自增或固定
 */ 
typedef enum
{    
    DmaMskDstAddrInc    = 0x00000000U, /*!< 地址自增 */
    DmaMskDstAddrFix    = 0x01000000U, /*!< 地址固定 */
} en_dst_address_mode_t;

/**
 * @brief  DMA CONFA:BC[3:0]和CONFA:TC[15:0]的重载功能
 */
typedef enum
{    
    DmaMskBcTcReloadDisable = 0x00000000U, /*!< 禁止重载 */
    DmaMskBcTcReloadEnable  = 0x00800000U, /*!< 使能重载 */
} en_bc_tc_reload_mode_t;

/**
 * @brief  DMA 源地址重载功能：使能或禁止
 */
typedef enum
{    
    DmaMskSrcAddrReloadDisable  = 0x00000000U, /*!< 禁止DMA源地址重载 */
    DmaMskSrcAddrReloadEnable   = 0x00400000U, /*!< 使能DMA源地址重载 */
} en_src_address_reload_mode_t;

/**
 * @brief  DMA 目的地址重载功能：使能或禁止
 */
typedef enum
{    
    DmaMskDstAddrReloadDisable  = 0x00000000U, /*!< 禁止DMA目的地址重载 */
    DmaMskDstAddrReloadEnable   = 0x00200000U, /*!< 使能DMA目的地址重载 */
} en_dst_address_reload_mode_t;

/**
 * @brief  DMA 连续传输设置
 */
typedef enum
{
    DmaMskOneTransfer           = 0x00000000U, /*!< 传输一次，DMA传输完成时清除CONFA:ENS位 */
    DmaMskContinuousTransfer    = 0x00000001U, /*!< 连续传输，DMA传输完成时不清除CONFA:ENS位 */
} en_dma_msk_t;

/**
 * @brief  DMA 触发源选择
 */
typedef enum
{
    DmaSWTrig           = 0x00U, /*!< 软件触发 */

    DmaUart0TxTrig      = 0x40U, /*!< USART0发送Buf空 */
    DmaUart0RxTrig      = 0x41U, /*!< USART0接收Buf非空 */
    DmaUart1TxTrig      = 0x42U, /*!< USART1发送Buf空 */
    DmaUart1RxTrig      = 0x43U, /*!< USART1接收Buf非空 */
    DmaLpUart0TxTrig    = 0x44U, /*!< LPUART0发送Buf空 */
    DmaLpUart0RxTrig    = 0x45U, /*!< LPUART0接收Buf非空 */
    DmaLpUart1TxTrig    = 0x46U, /*!< LPUART1发送Buf空 */
    DmaLpUart1RxTrig    = 0x47U, /*!< LPUART1接收Buf非空 */
    DmaGtim0Trig        = 0x48U, /*!< GTIM0发生捕获事件或比较事件 */
    DmaGtim1Trig        = 0x49U, /*!< GTIM1发生捕获事件或比较事件 */

    DmaADCJQRTrig       = 0x4CU, /*!< ADC插队转换完成 */
    DmaADCEOCTrig       = 0x4DU, /*!< ADC顺序单次转换完成 */

    DmaSPI0TXTrig       = 0x50U, /*!< SPI0发送Buf空 */
    DmaSPI0RXTrig       = 0x51U, /*!< SPI0接收Buf非空 */
    DmaSPI1TXTrig       = 0x52U, /*!< SPI1发送Buf空 */
    DmaSPI1RXTrig       = 0x53U, /*!< SPI1接收Buf非空 */
    DmaI2CSLVRXTrig     = 0x54U, /*!< I2CSLV接收Buf非空 */
    DmaI2CSLVTXTrig     = 0x55U, /*!< I2CSLV发送Buf空 */

    DmaATIM0ATrig       = 0x58U, /*!< ATIM0 通道A，发生捕获事件或比较事件 */
    DmaATIM0BTrig       = 0x59U, /*!< ATIM0 通道B，发生捕获事件或比较事件 */
    DmaATIM1ATrig       = 0x5AU, /*!< ATIM1 通道A，发生捕获事件或比较事件 */
    DmaATIM1BTrig       = 0x5BU, /*!< ATIM1 通道B，发生捕获事件或比较事件 */
    DmaATIM2ATrig       = 0x5CU, /*!< ATIM2 通道A，发生捕获事件或比较事件 */
    DmaATIM2BTrig       = 0x5DU, /*!< ATIM2 通道B，发生捕获事件或比较事件 */
    DmaATIM3ATrig       = 0x5EU, /*!< ATIM3 通道A，发生捕获事件或比较事件 */
    DmaATIM3BTrig       = 0x5FU, /*!< ATIM3 通道B，发生捕获事件或比较事件 */
}en_dma_trig_sel_t;  

/**
 * @brief  DMA 通道初始化配置结构体
 */
typedef struct
{
    en_dma_transfer_mode_t         enMode;              /*!< DMA 传输模式 @ref en_dma_transfer_mode_t */

    uint16_t                       u16BlockSize;        /*!< 块传输个数 */
    uint16_t                       u16TransferCnt;      /*!< 传输块次数 */
    en_dma_transfer_width_t        enTransferWidth;     /*!< 传输数据字节宽度 @ref en_dma_transfer_width_t */

    en_src_address_mode_t          enSrcAddrMode;       /*!< DMA源地址控制模式：自增或固定 @ref en_src_address_mode_t */
    en_dst_address_mode_t          enDstAddrMode;       /*!< DMA目的地址控制模式：自增或固定 @ref en_dst_address_mode_t */

    en_src_address_reload_mode_t   enSrcAddrReloadCtl;  /*!< 源地址重载 @ref en_src_address_reload_mode_t */
    en_dst_address_reload_mode_t   enDestAddrReloadCtl; /*!< 目的地址重载 @ref en_dst_address_reload_mode_t */
    en_bc_tc_reload_mode_t         enSrcBcTcReloadCtl;  /*!< Bc/Tc值重载功能 @ref en_bc_tc_reload_mode_t */

    uint32_t                       u32SrcAddress;       /*!< 源地址 */
    uint32_t                       u32DstAddress;       /*!< 目的地址 */

    en_dma_msk_t                   enTransferMode;      /*!< DMA 连续传输设置 @ref en_dma_msk_t */
    en_dma_priority_t              enPriority;          /*!< DMA 优先级设定 @ref en_dma_priority_t */
    en_dma_trig_sel_t              enRequestNum;        /*!< DMA 触发源选择 @ref en_dma_trig_sel_t */
} stc_dma_cfg_t;


/**
 * @}
 */

  /*******************************************************************************
  * Global pre-processor symbols/macros ('#define')
  ******************************************************************************/
  
  /*******************************************************************************
  * Global variable definitions ('extern')
  ******************************************************************************/
  
  /*******************************************************************************
  * Global function prototypes (definition in C source)
  ******************************************************************************/
 /**
 * @addtogroup DMAC_Global_Functions DMAC全局函数定义
 * @{
 */

en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg);  

void Dma_Enable(void);   
void Dma_Disable(void);  

void Dma_SwStart(en_dma_channel_t enCh);  
void Dma_SwStop(en_dma_channel_t enCh);

void Dma_EnableChannelIrq(en_dma_channel_t enCh);
void Dma_DisableChannelIrq(en_dma_channel_t enCh);
void Dma_EnableChannelErrIrq(en_dma_channel_t enCh);
void Dma_DisableChannelErrIrq(en_dma_channel_t enCh);

void Dma_EnableChannel(en_dma_channel_t enCh);
void Dma_DisableChannel(en_dma_channel_t enCh);

void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize);
void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt);

void Dma_EnableContinusTranfer(en_dma_channel_t enCh);
void Dma_DisableContinusTranfer(en_dma_channel_t enCh);

void Dma_HaltTranfer(void);
void Dma_RecoverTranfer(void);
void Dma_PauseChannelTranfer(en_dma_channel_t enCh);
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh);

void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth);  
void Dma_SetChPriority(en_dma_priority_t enPrio);

en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh);  
void Dma_ClrStat(en_dma_channel_t enCh);

void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address);
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address);


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

#endif /* __DMAC_H__ */

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
