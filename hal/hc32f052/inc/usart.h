/**
 *******************************************************************************
 * @file  usart.h
 * @brief This file contains all the functions prototypes of the USART driver
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
#ifndef __USART_H__
#define __USART_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
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
 * @addtogroup DDL_USART USART子模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Types USART全局类型定义
 * @{
 */

/**
 * @brief  USART 高级功能初始化配置
 */
typedef struct
{
    uint32_t u32TxRxCombine;        /*!< 收发端口复合使能位  @ref USART_Tx_Rx_Comb            */
    uint32_t u32StartBitDetectMode; /*!< 接收起始位检测模式  @ref USART_Start_Bit_Detect      */
    uint32_t u32MSBFirst;           /*!< MSB/LSB方式选择     @ref USART_MSB_First             */
    uint32_t u32ClockCtrl;          /*!< 时钟控制位          @ref USART_Clk_Control           */
    uint32_t u32TxRxSwap;           /*!< TX/RX引脚互换控制位 @ref USART_Tx_Rx_Swap            */
    uint32_t u32TxRxPinLevelInvert; /*!< 输出信号反向控制位  @ref USART_Tx_Rx_Inv             */
    uint32_t u32HWFlowCtrl;         /*!< 硬件流控            @ref USART_Hardware_Flow_Control */
    uint32_t u32DMATxRxTransfer;    /*!< DMA传输控制         @ref USART_DMA_Tx_Rx             */
} stc_usart_adv_feature_init_t;

/**
 * @brief  USART 多处理机初始化配置
 */
typedef struct
{
    /* Multi Processor Enable Type */
    uint32_t u32MultiProEn; /*!< UART多处理器功能使能控制 @ref USART_UART_Multi_Pro_En          */
    /* Master Type */
    uint32_t u32MultiProID; /*!< UART多处理器ID位         @ref USART_UART_Multi_Pro_ID          */
    /* Slaver Type */
    uint32_t u32MultiProSilentMode; /*!< UART多处理静默模式 @ref USART_UART_Multi_Pro_Silent_Mode */
    uint8_t  u8SlaveAddr;           /*!< 从机地址      取值范围0 ~ 127                            */
    uint8_t  u8SlaveAddrMsk;        /*!< 从机地址掩码  取值范围0 ~ 127                            */
} stc_usart_multi_pro_init_t;

/**
 * @brief  USART UART初始化
 */
typedef struct
{
    /* UART Base Type */
    uint32_t u32BaudRate;    /*!< UART 通信波特率配置(bps) */
    uint32_t u32SampleMode;  /*!< UART 采样模式设定16倍/8倍采样 @ref USART_Over_Sampling */
    uint32_t u32FrameLength; /*!< 数据帧长度8/9bits             @ref USART_Frame_Length  */
    uint32_t u32Parity;      /*!< 奇偶校验选择                  @ref USART_Parity        */
    uint32_t u32StopBits;    /*!< 停止位长度                    @ref USART_Stop_Bits     */
    uint32_t u32TransMode;   /*!< 数据传输方式                  @ref USART_Mode          */

    /* UART Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_uart_init_t;

/**
 * @brief  USART 同步串口初始化
 */
typedef struct
{
    /* Clock Sync Base Type */
    uint32_t u32BaudRate;  /*!< UART 通信波特率配置(bps)                               */
    uint32_t u32TransMode; /*!< 数据传输方式                  @ref USART_Mode          */

    /* Clock Sync Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_clksync_init_t;

/**
 * @brief  USART 红外模式初始化配置
 */
typedef struct
{
    /* IR Base Type */
    uint32_t u32BaudRate;         /*!< UART 通信波特率配置(bps)                              */
    uint32_t u32FrameLength;      /*!< 数据帧长度8/9bits @ref USART_Frame_Length             */
    uint32_t u32Parity;           /*!< 奇偶校验选择      @ref USART_Parity                   */
    uint32_t u32TransMode;        /*!< 数据传输方式      @ref USART_Mode                     */
    uint32_t u32IRMode;           /*!< 红外模式          @ref USART_IR_Mode_Select           */
    uint32_t u32IRMod38K;         /*!< 38K调制方式       @ref USART_IR_38K_Modulation_Select */
    uint32_t u32HighLevelTime38K; /*!< 38K载波高电平维持时间(μs)                             */
    uint32_t u32LowLevelTime38K;  /*!< 38K载波低电平维持时间(μs)                             */

    /* IR Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_ir_init_t;

/**
 * @brief  LIN LIN模式初始化配置
 */
typedef struct
{
    /* LIN Base Type */
    uint32_t u32BaudRate;   /*!< UART 通信波特率配置(bps) */
    uint32_t u32SampleMode; /*!< UART 采样模式设定16倍/8倍采样 @ref USART_Over_Sampling */

    /* UART Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_lin_init_t;

/**
 * @brief  SC 智能卡模式初始化配置
 */
typedef struct
{
    /* SC Base Type */
    uint32_t u32DataBaudRate; /*!< IO上的数据传输波特率配置(bps) */
    uint32_t u32Parity;       /*!< 奇偶校验选择，标准智能卡均采用偶校验      @ref USART_Parity */
    uint32_t u32FiBCN;        /*!< 一位数据传输时的基本时钟数                @ref USART_SC_BCN_SET*/
    uint32_t u32IOPUTime;     /*!< 开漏时强输出CMOS高电平时间，单位:1/pclk   @ref USART_SC_SMCPU_SET*/

    /* SC Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 @ref stc_usart_adv_feature_init_t */
} stc_usart_smart_card_init_t;

/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Macros USART全局宏定义
 * @{
 */

/**
 * @defgroup USART_Mode_Select USART UART和时钟同步模式选择
 * @{
 */
#define USART_UART_MODE    0x00000000U    /*!< UART模式     */
#define USART_CLKSYNC_MODE USART_CR2_SYNC /*!< 时钟同步模式 */
/**
 * @}
 */

/**
 * @defgroup USART_Over_Sampling UART Over Sampling
 * @{
 */
#define USART_OVERSAMPLING_16 0x00000000U     /*!< Oversampling by 16 */
#define USART_OVERSAMPLING_8  USART_CR1_OVER8 /*!< Oversampling by 8  */
/**
 * @}
 */

/**
 * @defgroup USART_Frame_Length  UART Frame Length
 * @{
 */
#define USART_FRAME_LEN_8BITS 0x00000000U     /*!< UART 帧长度 8Bits  */
#define USART_FRAME_LEN_9BITS USART_CR1_CHLEN /*!< UART 帧长度 9Bits  */
/**
 * @}
 */

/**
 * @defgroup USART_Parity  UART Parity
 * @{
 */
#define USART_PARITY_NONE 0x00000000U                    /*!< No parity   */
#define USART_PARITY_EVEN USART_CR1_PCE                  /*!< Even parity */
#define USART_PARITY_ODD  (USART_CR1_PCE | USART_CR1_PS) /*!< Odd parity  */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Bits UART STOP位长选择
 * @{
 */
#define USART_STOP_1BIT  0x00000000U    /*!< USART frame with 1 stop bit  */
#define USART_STOP_2BITS USART_CR1_STOP /*!< USART frame with 2 stop bits */
/**
 * @}
 */

/**
 * @defgroup USART_Mode UART Transfer Mode
 * @{
 */
#define USART_MODE_RX    USART_CR1_RE                  /*!< RX mode        */
#define USART_MODE_TX    USART_CR1_TE                  /*!< TX mode        */
#define USART_MODE_TX_RX (USART_CR1_TE | USART_CR1_RE) /*!< RX and TX mode */
/**
 * @}
 */

/**
 * @defgroup USART_Tx_Rx_COMB UART 收发端口复合使能位
 * @{
 */
#define USART_RX_TX_SEPARATE 0x00000000U    /*!< USART TXD和RXD分开使用                    */
#define USART_RX_TX_COMBINE  USART_CR1_COMB /*!< USART UART单总线模式，TXD和RXD合用TXD端口 */
/**
 * @}
 */

/**
 * @defgroup USART_Start_Bit_Detect UART Start位检测
 * @{
 */
#define USART_START_BIT_RX_EDGE  0x00000000U   /*!< USART Start位检测 接收数据RXD管脚边沿作为起始位 */
#define USART_START_BIT_RX_LEVEL USART_CR1_SBS /*!< USART Start位检测 接收数据RXD管脚电平作为起始位 */
/**
 * @}
 */

/**
 * @defgroup USART_MSB_First   UART Advanced Feature MSB First
 * @{
 */
#define USART_ADV_MSBFIRST_DISABLE 0x00000000U   /*!< Most significant bit sent/received first disable */
#define USART_ADV_MSBFIRST_ENABLE  USART_CR1_MSB /*!< Most significant bit sent/received first enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Clk_Control USART 时钟控制位
 * @{
 */
#define USART_UART_INT_CLK_OUTPUT_DIS   0x00000000U                   /*!< UART: 内部生成的时钟，不输出到CK管脚     */
#define USART_UART_INT_CLK_OUTPUT_EN    (0x1UL << USART_CR2_CLKC_Pos) /*!< UART: 内部生成的时钟，输出到CK管脚       */
#define USART_CLKSYNC_INT_CLK_OUTPUT_EN 0x00000000U                   /*!< 时钟同步：内部生成的时钟，输出到CK管脚   */
#define USART_CLKSYNC_EXT_CLK           (0x2UL << USART_CR2_CLKC_Pos) /*!< 时钟同步：外部输入时钟，频率和波特率相同 */
#define USART_SC7816_INT_CLK_OUTPUT_DIS 0x00000000U                   /*!< 智能卡：内部生成的时钟，不输出到CK管脚   */
#define USART_SC7816_INT_CLK_OUTPUT_EN  (0x1UL << USART_CR2_CLKC_Pos) /*!< 智能卡：内部生成的时钟，输出到CK管脚     */
/**
 * @}
 */

/**
 * @defgroup USART_Tx_Rx_Swap UART Advanced Feature RX TX Pins Swap
 * @{
 */
#define USART_ADV_SWAP_DISABLE 0x00000000U    /*!< TX/RX pins swap disable */
#define USART_ADV_SWAP_ENABLE  USART_CR2_SWAP /*!< TX/RX pins swap enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Tx_Rx_Inv UART Advanced Feature RX Pin Active Level Inversion
 * @{
 */
#define USART_ADV_TX_RX_INV_DISABLE 0x00000000U                         /*!< TX/RX pin active level inversion disable */
#define USART_ADV_TX_INV_ENABLE     USART_CR2_TXINV                     /*!< TX pin active level inversion enable     */
#define USART_ADV_RX_INV_ENABLE     USART_CR2_RXINV                     /*!< RX pin active level inversion enable     */
#define USART_ADV_TX_RX_INV_ENABLE  (USART_CR2_TXINV | USART_CR2_RXINV) /*!< TX/RX pin active level inversion enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Hardware_Flow_Control USART Hardware Flow Control
 * @{
 */
#define USART_HWCONTROL_NONE    0x00000000U                         /*!< No hardware control       */
#define USART_HWCONTROL_RTS     USART_CR2_RTSEN                     /*!< Request To Send           */
#define USART_HWCONTROL_CTS     USART_CR2_CTSEN                     /*!< Clear To Send             */
#define USART_HWCONTROL_RTS_CTS (USART_CR2_RTSEN | USART_CR2_CTSEN) /*!< Request and Clear To Send */
/**
 * @}
 */

/**
 * @defgroup USART_DMA_Tx_Rx    UART DMA Tx
 * @{
 */
#define USART_DMA_TX_RX_DISABLE 0x00000000U                             /*!< UART DMA TX/RX disabled */
#define USART_DMA_TX_ENABLE     USART_CR2_TXDMAEN                       /*!< UART DMA TX enabled     */
#define USART_DMA_RX_ENABLE     USART_CR2_RXDMAEN                       /*!< UART DMA RX enabled     */
#define USART_DMA_TX_RX_ENABLE  (USART_CR2_TXDMAEN | USART_CR2_RXDMAEN) /*!< UART DMA TX/RX enabled  */
/**
 * @}
 */

/**
 * @defgroup USART_Baud_Rate_Pre_Clock_Div USART 波特率生成预分频
 * @{
 */
#define USART_Baud_Rate_Pre_Clock_Div1  0x00000000U                  /*!< 内部时钟源时，预分频器选择 PCLK    */
#define USART_Baud_Rate_Pre_Clock_Div4  (0x1UL << USART_BRR_PSC_Pos) /*!< 内部时钟源时，预分频器选择 PCLK/4  */
#define USART_Baud_Rate_Pre_Clock_Div16 (0x2UL << USART_BRR_PSC_Pos) /*!< 内部时钟源时，预分频器选择 PCLK/16 */
#define USART_Baud_Rate_Pre_Clock_Div64 (0x3UL << USART_BRR_PSC_Pos) /*!< 内部时钟源时，预分频器选择 PCLK/64 */
/**
 * @}
 */

/**
 * @defgroup UART_AutoBaud_Rate_Mode    UART Advanced Feature Auto BaudRate Detection
 * @{
 */
#define USART_ADV_AUTO_BAUDRATE_DISABLE 0x00000000U    /*!< Auto Baud rate detection disable */
#define USART_ADV_AUTO_BAUDRATE_ENABLE  USART_CR3_ABRE /*!< Auto Baud rate detection enable  */
/**
 * @}
 */

/**
 * @defgroup USART_Timer    USART 多功能定时器工作模式配置
 * @{
 */
#define USART_TIMER_STOP              0x00000000U                  /*!< 停止定时计数器                          */
#define USART_GENERAL_TIMER_START     (0x1UL << USART_CR1_TOE_Pos) /*!< 通用定时功能启动                        */
#define USART_RECEIVE_TIMER_START     (0x2UL << USART_CR1_TOE_Pos) /*!< 接收定时功能启动                        */
#define USART_DATA_FRAME_TIMER_START  (0x3UL << USART_CR1_TOE_Pos) /*!< 数据帧间定时功能启动                    */
#define USART_LIN_BREAK_TIMER_START   (0x4UL << USART_CR1_TOE_Pos) /*!< LIN模式下，间隔段计数使能               */
#define USART_AUTO_BAUDRATE_DETECT_EN (0x5UL << USART_CR1_TOE_Pos) /*!< LIN模式或UART模式下，波特率自动检测使能 */
/**
 * @}
 */

/**
 * @defgroup USART_Status_Flags     UART Status Flags
 * @{
 */
#define USART_FLAG_TXE  USART_SR_TXE  /*!< 发送缓存空           */
#define USART_FLAG_TC   USART_SR_TC   /*!< 发送完成             */
#define USART_FLAG_RC   USART_SR_RC   /*!< 接收完成             */
#define USART_FLAG_PE   USART_SR_PE   /*!< 接收数据校验错误     */
#define USART_FLAG_FE   USART_SR_FE   /*!< 接收帧错误           */
#define USART_FLAG_OR   USART_SR_OR   /*!< 接收数据上溢         */
#define USART_FLAG_TO   USART_SR_TO   /*!< 定时器溢出           */
#define USART_FLAG_MPB  USART_SR_MPB  /*!< 多机模式数据、ID标志 */
#define USART_FLAG_AM   USART_SR_AM   /*!< 多机模式地址匹配标志 */
#define USART_FLAG_CTSV USART_SR_CTSV /*!< CTS信号电平值        */
#define USART_FLAG_CTS  USART_SR_CTS  /*!< CTS中断标志          */
#define USART_FLAG_ABR  USART_SR_ABR  /*!< 自动波特率检测标志   */
#define USART_FLAG_LBD  USART_SR_LBD  /*!< LIN模式间隔断检测标志*/
#define USART_FLAG_DWK  USART_SR_DWK  /*!< RXD线唤醒标志        */
#define USART_FLAG_ALL  (0xFFFFU)     /*!< 所有标志             */
/**
 * @}
 */

/**
 * @defgroup USART_UART_Multi_Pro_Silent_Mode USART UART多处理操作静默模式
 * @{
 */
#define USART_UART_NORMAL_MODE 0x00000000U    /*!< 多处理器操作时，正常模式 */
#define USART_UART_SILENT_MODE USART_CR1_SLME /*!< 多处理器操作时，静默模式 */
/**
 * @}
 */

/**
 * @defgroup USART_UART_Multi_Pro_ID USART UART多处理器ID位
 * @{
 */
#define USART_UART_SEND_DATA 0x00000000U    /*!< 多处理器操作时，发送数据 */
#define USART_UART_SEND_ID   USART_TDR_MPID /*!< 多处理器操作时，发送ID   */
/**
 * @}
 */

/**
 * @defgroup USART_UART_Multi_Pro_En USART UART多处理器功能使能控制
 * @{
 */
#define USART_UART_MULTI_PRO_DISABLE 0x00000000U   /*!< 多处理器功能禁止 */
#define USART_UART_MULTI_PRO_ENABLE  USART_CR1_MPE /*!< 多处理器功能使能 */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_ENABLE    USART Local Interconnection Network mode
 * @{
 */
#define USART_LIN_DISABLE 0x00000000U     /*!< Local Interconnect Network disable */
#define USART_LIN_ENABLE  USART_CR3_LINEN /*!< Local Interconnect Network enable  */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Break_Detection  USART LIN Break Detection
 * @{
 */
#define USART_LIN_BREAK_DETECT_DISABLE 0x00000000U    /*!< LIN break detection disable */
#define USART_LIN_BREAK_DETECT_ENABLE  USART_CR3_LBDE /*!< LIN break detection enable  */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Bps_Auto_Detection  USART LIN Auto Bps Detection
 * @{
 */
#define USART_LIN_AUTO_BPS_DETECT_DISABLE 0x00000000U    /*!< LIN auto Bps detection disable */
#define USART_LIN_AUTO_BPS_DETECT_ENABLE  USART_CR3_ABRE /*!< LIN auto Bps detection enable  */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Break_Send  USART LIN Send Break
 * @{
 */
#define USART_LIN_BREAK_SEND_DISABLE 0x00000000U     /*!< LIN break send disable */
#define USART_LIN_BREAK_SEND_ENABLE  USART_CR3_BREAK /*!< LIN break send enable  */
/**
 * @}
 */

/**
 * @defgroup USART_IR_Mode_Select USART IR模式选择
 * @{
 */
#define USART_IR_MODE_3_16 0x00000000U    /*!< 3/16模式    */
#define USART_IR_MODE_38K  USART_CR3_IRCW /*!< 38K载波模式 */
/**
 * @}
 */

/**
 * @defgroup USART_IR_38K_Modulation_Select USART IR 38K调制模式选择
 * @{
 */
#define USART_IR_38K_Mod_0 0x00000000U     /*!< 38K调制模式，数据0输出38K载波 */
#define USART_IR_38K_Mod_1 USART_CR3_IRMOD /*!< 38K载波模式，数据1输出38K载波 */
/**
 * @}
 */

/**
 * @defgroup USART_SC_ENABLE    USART Local Interconnection Network mode
 * @{
 */
#define USART_SC_DISABLE 0x00000000U    /*!< SmartCard mode disable */
#define USART_SC_ENABLE  USART_CR3_SCEN /*!< SmartCard mode enable  */
/**
 * @}
 */
/**
 * @defgroup USART_UART_Error_Code  UART Error Codes
 * @{
 */
#define USART_UART_NoError       0x00000000U /*!< 无错误           */
#define USART_UART_TimeoutError  0xFFFFFFFFU /*!< 超时错误         */
#define USART_UART_ParityError   USART_SR_PE /*!< 接收数据校验错误 */
#define USART_UART_FrameError    USART_SR_FE /*!< 接收帧错误       */
#define USART_UART_OverflowError USART_SR_OR /*!< 接收数据上溢     */
/**
 * @}
 */

/**
 * @defgroup USART_BAUD_RATE_SET_MODE  波特率设置模式选择
 * @{
 */
#define USART_BAUD_RATE_UART    0x00U /*!< UART模式         */
#define USART_BAUD_RATE_CLKSYNC 0x01U /*!< 时钟同步模式     */
#define USART_BAUD_RATE_SC      0x02U /*!< 智能卡接口模式   */
#define USART_BAUD_RATE_IR      0x03U /*!< 红外通信模式     */
#define USART_BAUD_RATE_LIN     0x04U /*!< LIN模式          */
/**
 * @}
 */

/**
 * @defgroup USART_SAMPLE_BITS_SET  采样次数选择
 * @{
 */
#define USART_SAMPLE_BITS_CLKSYNC 0x04U /*!< 时钟同步模式 采样次数 */
#define USART_SAMPLE_BITS_IR      0x10U /*!< 红外通信模式 采样次数 */
/**
 * @}
 */

/**
 * @defgroup USART_SC_SMCPU_SET  智能卡模式输出边沿整型选择
 * @{
 */
#define USART_SC_SMCPU_00 0U /*!< 智能卡模式 输出边沿整形，开漏时强输出无边沿整形             */
#define USART_SC_SMCPU_01 1U /*!< 智能卡模式 输出边沿整形，开漏时强输出1个PCLK周期CMOS高电平  */
#define USART_SC_SMCPU_02 2U /*!< 智能卡模式 输出边沿整形，开漏时强输出2个PCLK周期CMOS高电平  */
#define USART_SC_SMCPU_04 3U /*!< 智能卡模式 输出边沿整形，开漏时强输出4个PCLK周期CMOS高电平  */

/**
 * @defgroup USART_SC_BCN_SET  智能卡模式一位数据传输期间的基本时钟数选择
 * @{
 */
#define USART_SC_BCN_16  16U  /*!< 智能卡模式 BCN=16  */
#define USART_SC_BCN_32  32U  /*!< 智能卡模式 BCN=32  */
#define USART_SC_BCN_64  64U  /*!< 智能卡模式 BCN=64  */
#define USART_SC_BCN_128 128U /*!< 智能卡模式 BCN=128 */
#define USART_SC_BCN_186 186U /*!< 智能卡模式 BCN=186 */
#define USART_SC_BCN_256 256U /*!< 智能卡模式 BCN=256 */
#define USART_SC_BCN_372 372U /*!< 智能卡模式 BCN=372 */
#define USART_SC_BCN_512 512U /*!< 智能卡模式 BCN=512 */

/**
 * @}
 */

/**
 * @defgroup USART_TOE_Type  多功能定时器工作模式配置
 * @{
 */
#define USART_TOE_Stop          0x00000000U                  /*!< 停止定时计数器                          */
#define USART_TOE_General       (0x1UL << USART_CR1_TOE_Pos) /*!< 通用定时功能                            */
#define USART_TOE_Receive       (0x2UL << USART_CR1_TOE_Pos) /*!< 接收定时功能                            */
#define USART_TOE_Data_Frame    (0x3UL << USART_CR1_TOE_Pos) /*!< 数据帧间定时功能                        */
#define USART_TOE_Break         (0x4UL << USART_CR1_TOE_Pos) /*!< LIN模式下，间隔段计数使能               */
#define USART_TOE_Auto_BaudRate (0x5UL << USART_CR1_TOE_Pos) /*!< LIN模式或UART模式下，波特率自动检测使能 */
/**
 * @}
 */

/**
 * @}
 */
/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup USART_Global_Functions USART全局函数定义
 * @{
 */

uint32_t    USART_BaudRateCal(USART_TypeDef* USARTx, uint32_t u32BaudRateSetMode, uint32_t u32BaudRate, uint32_t u32PCLK, uint32_t u32SampMode);
uint32_t    USART_UART_Init(USART_TypeDef* USARTx, stc_usart_uart_init_t* pstcUARTInit);
uint32_t    USART_LIN_Init(USART_TypeDef* USARTx, stc_usart_lin_init_t* pstcLinInit);
uint32_t    USART_IR_Init(USART_TypeDef* USARTx, stc_usart_ir_init_t* pstcIRInit);
uint32_t    USART_SC_Init(USART_TypeDef* USARTx, stc_usart_smart_card_init_t* pstcSmartCardInit);
uint32_t    USART_ClkSync_Init(USART_TypeDef* USARTx, stc_usart_clksync_init_t* pstcClkSyncInit);
en_result_t USART_UART_Transmit(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout);
void        USART_UART_TransmitINT(USART_TypeDef* USARTx, uint8_t* pu8Data);
void        USART_SC_TransmitINT(USART_TypeDef* USARTx, uint8_t *pu8Data);
void        USART_SC_ReceiveINT(USART_TypeDef* USARTx);
uint32_t    USART_UART_Receive(USART_TypeDef* USARTx, uint8_t* pu8Data, uint32_t u32Size, uint32_t u32Timeout);
void        USART_UART_ReceiveINT(USART_TypeDef* USARTx, uint8_t* pu8Data);
void        USART_UART_ABR_Detect(USART_TypeDef* USARTx, uint32_t u32PSC);
void        USART_UART_Detect_ABR_Set(USART_TypeDef* USARTx);
void        USART_SC_CLK_Enable(USART_TypeDef* USARTx, boolean_t bEn);
uint32_t    USART_GetFlag(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_ClearFlag(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_EnableIrq(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_DisableIrq(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_ClearIrq(USART_TypeDef* USARTx, uint32_t u32State);
uint32_t    USART_GetIrqEn(USART_TypeDef* USARTx, uint32_t u32State);
void        USART_IR_EnableIR(USART_TypeDef* USARTx);
void        USART_IR_DisableIR(USART_TypeDef* USARTx);

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

#endif /* __USART_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
