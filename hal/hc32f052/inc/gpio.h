/**
 *******************************************************************************
 * @file  gpio.h
 * @brief This file contains all the functions prototypes of the GPIO driver
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

#ifndef __GPIO_H__
#define __GPIO_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
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
 * @addtogroup DDL_GPIO GPIO模块驱动库
 * @{
 */


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Types GPIO全局类型定义
 * @{
 */
 
/**
 * @brief  GPIO PIN类型定义
 */
typedef enum
{
    GpioPin0  = 0u,                 /*!< GPIO PIN0 */
    GpioPin1  = 1u,                 /*!< GPIO PIN1 */ 
    GpioPin2  = 2u,                 /*!< GPIO PIN2 */ 
    GpioPin3  = 3u,                 /*!< GPIO PIN3 */ 
    GpioPin4  = 4u,                 /*!< GPIO PIN4 */ 
    GpioPin5  = 5u,                 /*!< GPIO PIN5 */ 
    GpioPin6  = 6u,                 /*!< GPIO PIN6 */ 
    GpioPin7  = 7u,                 /*!< GPIO PIN7 */ 
    GpioPin8  = 8u,                 /*!< GPIO PIN8 */ 
    GpioPin9  = 9u,                 /*!< GPIO PIN9 */ 
    GpioPin10 = 10u,                /*!< GPIO PIN10 */ 
    GpioPin11 = 11u,                /*!< GPIO PIN11 */ 
    GpioPin12 = 12u,                /*!< GPIO PIN12 */ 
    GpioPin13 = 13u,                /*!< GPIO PIN13 */ 
    GpioPin14 = 14u,                /*!< GPIO PIN14 */ 
    GpioPin15 = 15u,                /*!< GPIO PIN15 */ 
}en_gpio_pin_t;

/**
 * @brief  GPIO 端口复用功能(AF-Alternate function)类型定义
 * @note  具体功能及含义请参考用户手册GPIO复用表或下表(如果用户手册或数据手册有更新，以手册为准)
 */
typedef enum
{
    GpioAf0  = 0u,      /*!< GPIO功能 */ 
    GpioAf1  = 1u,      /*!< GPIO AF1:复用功能1 */ 
    GpioAf2  = 2u,      /*!< GPIO AF2:复用功能2 */ 
    GpioAf3  = 3u,      /*!< GPIO AF3:复用功能3 */ 
    GpioAf4  = 4u,      /*!< GPIO AF4:复用功能4 */ 
    GpioAf5  = 5u,      /*!< GPIO AF5:复用功能5 */ 
    GpioAf6  = 6u,      /*!< GPIO AF6:复用功能6 */ 
    GpioAf7  = 7u,      /*!< GPIO AF7:复用功能7 */ 
}en_gpio_af_t;

/*!<||======||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||PSEL  ||   GpioAf1   ||   GpioAf2   ||   GpioAf3   ||   GpioAf4   ||   GpioAf5   ||   GpioAf6   ||   GpioAf7   ||*/
/*!<||======||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||PA00  ||UART1_CTS    ||LPUART1_TXD  ||ATIM0_ETR    ||VC0_OUT      ||ATIM1_CHA    ||ATIM3_ETR    ||ATIM0_CHA    ||*/
/*!<||PA01  ||USART1_RTS   ||LPUART1_RXD  ||ATIM0_CHB    ||ATIM1_ETR    ||ATIM1_CHB    ||HCLK_OUT     ||SPI1_MOSI    ||*/
/*!<||PA02  ||USART1_TXD   ||ATIM0_CHA    ||VC1_OUT      ||ATIM1_CHA    ||ATIM2_CHA    ||ATIM3_CH0A   ||SPI1_MISO    ||*/
/*!<||PA03  ||USART1_RXD   ||ATIM0_GATE   ||ATIM1_CHB    ||ATIM2_CHB    ||SPI1_CS      ||ATIM3_CH0B   ||PCLK_OUT     ||*/
/*!<||PA04  ||SPI0_CS      ||UART1_SCK    ||CTIM1_CH0    ||ATIM2_ETR    ||ATIM3_CH1A   ||USART1_TXD   ||I2CSLV_SCL   ||*/
/*!<||PA05  ||SPI0_SCK     ||ATIM0_ETR    ||CTIM0_ETR    ||ATIM0_CHA    ||ATIM3_CH1B   ||XTL_OUT      ||XTH_OUT      ||*/
/*!<||PA06  ||SPI0_MISO    ||CTIM0_CH0    ||ATIM3_BK     ||ATIM1_CHA    ||VC0_OUT      ||ATIM3_GATE   ||LPUART0_CTS  ||*/
/*!<||PA07  ||SPI0_MOSI    ||CTIM0_CH1    ||HCLK_OUT     ||ATIM3_CH2A   ||ATIM2_CHA    ||VC1_OUT      ||CTIM1_TOG    ||*/
/*!<||PA08  ||USART0_SCK   ||ATIM3_CH0A   ||USART0_TXD   ||CAN_STBY     ||ATIM1_GATE   ||CTIM0_TOGN   ||ATIM3_BK     ||*/
/*!<||PA09  ||USART0_TXD   ||STIM3_CH1A   ||STIM0_BK     ||I2C0_SCL     ||MCO_OUT      ||HCLK_OUT     ||I2CSLV_SCL   ||*/
/*!<||PA10  ||USART0_RXD   ||ATIM3_CH2A   ||ATIM2_BK     ||I2C0_SDA     ||ATIM2_GATE   ||PCLK_OUT     ||I2CSLV_SDA   ||*/
/*!<||PA11  ||USART0_CTS   ||ATIM3_GATE   ||I2C1_SCL     ||CAN_TX       ||VC0_OUT      ||SPI0_MISO    ||ATIM3_CH1B   ||*/
/*!<||PA12  ||USART0_RTS   ||ATIM3_ETR    ||I2C1_SDA     ||CAN_RX       ||VC1_OUT      ||SPI0_MOSI    ||CTIM1_ETR    ||*/
/*!<||PA13  ||USART1_SCK   ||USART0_RXD   ||LVD_OUT      ||ATIM3_ETR    ||RTC_1HZ      ||CTIM1_CH1    ||CTRIM_ETRTOG ||*/
/*!<||PA14  ||USART1_TXD   ||USART0_TXD   ||ATIM3_CH2A   ||LVD_OUT      ||RCH_OUT      ||RCL_OUT      ||PLL_OUT      ||*/
/*!<||PA15  ||SPI0_CS      ||USART1_RXD   ||LPUART1_RTS  ||ATIM0_ETR    ||ATIM0_CHA    ||ATIM3_CH1A   ||CAN_STBY     ||*/
/*!<||PB00  ||CTIM0_CH2    ||CTIM1_TOGN   ||LPUART0_TXD  ||ATIM3_CH2B   ||RCH_OUT      ||RCL_OUT      ||PLL_OUT      ||*/
/*!<||PB01  ||CTIM0_CH3    ||PCLK_OUT     ||I2CSLV_SDA   ||ATIM3_CH1B   ||LPUART0_RTS  ||LPTIM_TOGN   ||USART0_SCK   ||*/
/*!<||PB02  ||LPTIM_TOG    ||CTIM0_ETR    ||LPUART1_TXD  ||ATIM3_CH0B   ||ATIM1_BK     ||ATIM0_BK     ||ATIM2_BK     ||*/
/*!<||PB03  ||SPI0_SCK     ||ATIM0_CHB    ||ATIM1_GATE   ||ATIM3_CH0A   ||LPTIM_GATE   ||XTL_OUT      ||XTH_OUT      ||*/
/*!<||PB04  ||SPI0_MISO    ||CTIM0_CH0    ||ATIM2_BK     ||USART0_CTS   ||ATIM2_GATE   ||ATIM3_CH0B   ||LPTIM_ETR    ||*/
/*!<||PB05  ||SPI0_MOSI    ||ATIM3_BK     ||ATIM1_BK     ||CTIM0_CH1    ||LPTIM_GATE   ||CTRIM_ETRTOG ||USART0_RTS   ||*/
/*!<||PB06  ||I2C0_SCL     ||USART0_TXD   ||ATIM1_CHB    ||ATIM0_CHA    ||LPTIM_ETR    ||ATIM3_CH0A   ||LPTIM_TOG    ||*/
/*!<||PB07  ||I2C0_SDA     ||USART0_RXD   ||ATIM2_CHB    ||LPUART1_CTS  ||ATIM0_CHB    ||LPTIM_TOGN   ||ATIM3_ETR    ||*/
/*!<||PB08  ||I2C0_SCL     ||ATIM1_CHA    ||CAN_RX       ||ATIM2_CHA    ||ATIM0_GATE   ||ATIM3_CH2A   ||USART0_TXD   ||*/
/*!<||PB09  ||I2C0_SDA     ||USART0_SCK   ||SPI1_CS      ||ATIM2_CHA    ||CAN_TX       ||ATIM2_CHB    ||USART0_RXD   ||*/
/*!<||PB10  ||I2C1_SCL     ||SPI1_SCK     ||ATIM1_CHA    ||LPUART0_TXD  ||ATIM3_CH1A   ||LPUART1_RTS  ||USART1_RTS   ||*/
/*!<||PB11  ||I2C1_SDA     ||ATIM1_CHB    ||LPUART0_RXD  ||ATIM2_GATE   ||ATIM3_CH1A   ||LPUART1_CTS  ||USART1_CTS   ||*/
/*!<||PB12  ||SPI1_CS      ||ATIM3_BK     ||LPUART0_TXD  ||ATIM0_BK     ||             ||LPUART0_RTS  ||ATIM3_CH0A   ||*/
/*!<||PB13  ||SPI1_SCK     ||I2C1_SCL     ||ATIM3_CH0B   ||LPUART0_CTS  ||ATIM1_CHA    ||ATIM1_GATE   ||             ||*/
/*!<||PB14  ||SPI1_MISO    ||I2C1_SDA     ||ATIM3_CH1B   ||ATIM0_CHA    ||ATIM3_CH2A   ||LPUART0_RTS  ||ATIM1_BK     ||*/
/*!<||PB15  ||SPI1_MOSI    ||ATIM3_CH2B   ||ATIM0_CHB    ||ATIM0_GATE   ||RTC_1HZ      ||CTIM0_TOG    ||LPUART1_RXD  ||*/
/*!<||PC13  ||CTIM1_ETR    ||RTC_1HZ      ||ATIM3_CH1B   ||CTIM0_TOG    ||             ||             ||             ||*/
/*!<||PC14  ||CTIM1_CH0    ||CTIM0_TOGN   ||LVD_OUT      ||             ||             ||             ||             ||*/
/*!<||PC15  ||CTIM1_CH0    ||             ||             ||             ||             ||             ||             ||*/
/*!<||PD00  ||I2C0_SDA     ||CTRIM_ETRTOG ||USART1_TXD   ||CTIM1_CH2    ||I2CSLV_SCL   ||             ||             ||*/
/*!<||PD01  ||I2C0_SCL     ||ATIM3_CH0B   ||USART1_RXD   ||CTIM1_CH3    ||I2CSLV_SDA   ||             ||             ||*/
/*!<||PD02  ||PCA_ECI      ||LPUART0_RTS  ||TIM1_ETR     ||             ||             ||             ||             ||*/
/*!<||PD03  ||             ||             ||             ||             ||             ||             ||             ||*/
/*!<||PD06  ||I2C1_SCL     ||LPUART1_CTS  ||USART0_CTS   ||RTC_OUT      ||ATIM3_BK     ||CTIM1_CH2    ||             ||*/
/*!<||PD07  ||I2C1_SDA     ||LPUART1_RTS  ||USART0_RTS   ||RTC_TS       ||ATIM3_ETR    ||CTIM1_CH3    ||             ||*/
/*!<||======||=============||=============||=============||=============||=============||=============||=============||*/

/**
 * @brief  GPIO 输入输出配置数据类型定义
 */
typedef enum
{
    GpioDirOut = 0u,                /*!< GPIO 输出 */ 
    GpioDirIn  = 1u,                /*!< GPIO 输入 */ 
}en_gpio_dir_t;

/**
 * @brief GPIO端口上拉配置数据类型定义
 */
typedef enum
{
    GpioPuDisable = 0u,                /*!< GPIO无上拉 */ 
    GpioPuEnable  = 1u,                /*!< GPIO上拉 */ 
}en_gpio_pu_t;

/**
 * @brief GPIO端口下拉配置数据类型定义
 */
typedef enum
{
    GpioPdDisable = 0u,                /*!< GPIO无下拉 */ 
    GpioPdEnable  = 1u,                /*!< GPIO下拉 */ 
}en_gpio_pd_t;
/**
 * @brief GPIO端口输出驱动能力配置数据类型定义
 */
typedef enum
{
    GpioDrvH = 0u,                  /*!< GPIO高驱动能力 */ 
    GpioDrvL = 1u,                  /*!< GPIO低驱动能力 */ 
}en_gpio_drv_t;

/**
 * @brief GPIO端口开漏输出控制数据类型定义
 */
typedef enum
{
    GpioOdDisable = 0u,             /*!< GPIO开漏输出关闭 */ 
    GpioOdEnable  = 1u,             /*!< GPIO开漏输出使能 */ 
}en_gpio_od_t;

/**
 * @brief GPIO中断触发方式类型定义
 */
typedef enum
{
    GpioIrqHigh     = 0u,           /*!< GPIO高电平触发 */ 
    GpioIrqLow      = 4u,           /*!< GPIO低电平触发 */ 
    GpioIrqRising   = 8u,           /*!< GPIO上升沿触发 */ 
    GpioIrqFalling  = 12u,          /*!< GPIO下降沿触发 */ 
}en_gpio_irqtype_t;


/**
 * @brief GPIO 辅助功能（SF-Secondary Function）MCO输出时钟选择类型定义
 */
typedef enum
{
    GpioSfMcoSrcRCH    = 0u,      /*!< MCO output RCH */ 
    GpioSfMcoSrcXTH    = 1u,      /*!< MCO output XTH */ 
    GpioSfMcoSrcRCL    = 2u,      /*!< MCO output RCL */ 
    GpioSfMcoSrcPLL    = 4u,      /*!< MCO output PLL */ 
    GpioSfMcoSrcRC150K = 5u,      /*!< MCO output RC150K */ 
    GpioSfMcoSrcRC96M  = 7u,      /*!< MCO output RC96M */ 
}en_gpio_sf_mco_src_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）MCO输出分频选择类型定义
 */
typedef enum
{
    GpioSfMcoOutDisable = 0u,      /*!< MCO output disable */ 
    GpioSfMcoOutDiv1    = 1u,      /*!< MCO */ 
    GpioSfMcoOutDiv8    = 2u,      /*!< MCO/2 */ 
    GpioSfMcoOutDiv64   = 3u,      /*!< MCO/64 */ 
    GpioSfMcoOutDiv256  = 4u,      /*!< MCO/256 */
}en_gpio_sf_mcoout_div_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）PCLK输出分频选择类型定义
 */
typedef enum
{
    GpioSfPclkOutDisable = 0u,      /*!< PCLK output disable */ 
    GpioSfPclkOutDiv1    = 1u,      /*!< PCLK */ 
    GpioSfPclkOutDiv2    = 2u,      /*!< PCLK/2 */ 
    GpioSfPclkOutDiv4    = 3u,      /*!< PCLK/4 */ 
    GpioSfPclkOutDiv8    = 4u,      /*!< PCLK/8 */ 
}en_gpio_sf_pclkout_div_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器ETR类型选择数据类型定义
 */
typedef enum
{
    GpioSfAtim0Etr   = 0u,                   /*!< Atim0定时器ETR输入选择 */
    GpioSfCtim0Etr   = 4u,                   /*!< Ctim0定时器ETR输入选择 */
    GpioSfCtim1Etr   = 8u,                   /*!< Ctim1定时器ETR输入选择 */
    GpioSfAtim3Etr   = 12u,                  /*!< Atim3定时器ETR输入选择 */
}en_gpio_sf_tim_e_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器捕获输入类型选择数据类型定义
 */
typedef enum
{
    GpioSfAtim0Cap0 = 0u,                   /*!< Atim0定时器CH0A输入选择 */
    GpioSfCtim0Cap3 = 4u,                   /*!< Ctim0定时器CH3输入选择 */
    GpioSfCtim1Cap3 = 8u,                   /*!< Ctim1定时器CH3输入选择 */
    GpioSfAtim3Cap2 = 12u,                  /*!< Atim3定时器CH2B输入选择 */
}en_gpio_sf_tim_c_t;


/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器互联功能选择类型定义
 * @note  具体功能及含义请参考用户手册GPIO辅助寄存器描述
 */
typedef enum
{
    GpioSf0 = 0u,       /*!<  SF0:AFRH/AFRL的配置功能 */
    GpioSf1 = 1u,       /*!<  SF1:辅助功能1 */
    GpioSf2 = 2u,       /*!<  SF2:辅助功能2 */
    GpioSf3 = 3u,       /*!<  SF3:辅助功能3 */
    GpioSf4 = 4u,       /*!<  SF4:辅助功能4 */
    GpioSf5 = 5u,       /*!<  SF5:辅助功能5 */
    GpioSf6 = 6u,       /*!<  SF6:辅助功能6 */
    GpioSf7 = 7u,       /*!<  SF7:辅助功能7 */
}en_gpio_sf_t;
/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||   ETR      ||     sf0     ||     sf1     ||     sf2     ||     sf3     ||     sf4     ||     sf5     ||     sf6     ||     sf7     ||*/
/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||CTIM0ETR    ||GTIM0_ETR    ||USART1_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA05         ||PA13         ||PB05         ||*/
/*!<||CTIM1ETR    ||GTIM1_ETR    ||LPUART0_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA06         ||PA14         ||PB06         ||*/
/*!<||ATIM0ETR    ||ATIM0_ETR    ||USART0_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA04         ||PA12         ||PB04         ||*/
/*!<||ATIM3ETR    ||ATIM3_ETR    ||LPUART1_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA07         ||PA15         ||PB07         ||*/


/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||    CAP     ||     sf0     ||     sf1     ||     sf2     ||     sf3     ||     sf4     ||     sf5     ||     sf6     ||     sf7     ||*/
/*!<||============||=============||=============||=============||=============||=============||=============||=============||=============||*/
/*!<||CTIM0CAP3   ||GTIM0_CH3    ||USART1_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA01         ||PA09         ||PB01         ||*/
/*!<||CTIM1CAP3   ||GTIM1_CH3    ||LPUART0_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA02         ||PA10         ||PB02         ||*/
/*!<||ATIM0CAP0   ||ATIM0_CH0A   ||USART0_RXD   ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA00         ||PA08         ||PB00         ||*/
/*!<||ATIM3CAP2   ||ATIM3_CH2B   ||LPUART1_RXD  ||VC0_OUT      ||LVD_OUT      ||VC1_OUT      ||PA03         ||PA11         ||PB03         ||*/

/**
 * @brief GPIO 端口配置结构体定义
 */
typedef struct
{
    boolean_t           bOutputVal;      /*!< 默认端口输出电平 */ 
    en_gpio_dir_t       enDir;           /*!< 端口方向配置 */ 
    en_gpio_drv_t       enDrv;           /*!< 端口驱动能力配置 */ 
    en_gpio_pu_t        enPu;            /*!< 端口上拉配置 */ 
    en_gpio_pd_t        enPd;            /*!< 端口下拉配置 */ 
    en_gpio_od_t        enOD;            /*!< 端口开漏输出配置 */ 
}stc_gpio_cfg_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Macros GPIO全局宏定义
 * @{
 */

  
/**
 * @brief GPIO PORT类型定义 GPIO_PORTs_define
 */
#define  GpioPortA   HC_GPIOA             /*!< GPIO PORT A */ 
#define  GpioPortB   HC_GPIOB             /*!< GPIO PORT B */ 
#define  GpioPortC   HC_GPIOC             /*!< GPIO PORT C */ 
#define  GpioPortD   HC_GPIOD             /*!< GPIO PORT D */ 


/**
 * @defgroup GPIO 复用功能定义
 * @{
 */

/**
 * @defgroup GPIO_AF1 复用功能1
 * @{
 */
#define PA00_USART1_CTS       GpioAf1
#define PA01_USART1_RTS       GpioAf1
#define PA02_USART1_TXD       GpioAf1
#define PA03_USART1_RXD       GpioAf1
#define PA04_SPI0_CS          GpioAf1
#define PA05_SPI0_SCK         GpioAf1
#define PA06_SPI0_MISO        GpioAf1
#define PA07_SPI0_MOSI        GpioAf1
#define PA08_USART0_SCK       GpioAf1
#define PA09_USART0_TXD       GpioAf1
#define PA10_USART0_RXD       GpioAf1
#define PA11_USART0_CTS       GpioAf1
#define PA12_USART0_RTS       GpioAf1
#define PA13_USART1_SCK       GpioAf1
#define PA14_USART1_TXD       GpioAf1
#define PA15_SPI0_CS          GpioAf1
#define PB00_CTIM0_CH2        GpioAf1
#define PB01_CTIM0_CH3        GpioAf1
#define PB02_LPTIM_TOG        GpioAf1
#define PB03_SPI0_SCK         GpioAf1
#define PB04_SPI0_MISO        GpioAf1
#define PB05_SPI0_MOSI        GpioAf1
#define PB06_I2C0_SCL         GpioAf1
#define PB07_I2C0_SDA         GpioAf1
#define PB08_I2C0_SCL         GpioAf1
#define PB09_I2C0_SDA         GpioAf1
#define PB10_I2C1_SCL         GpioAf1
#define PB11_I2C1_SDA         GpioAf1
#define PB12_SPI1_CS          GpioAf1
#define PB13_SPI1_SCK         GpioAf1
#define PB14_SPI1_MISO        GpioAf1
#define PB15_SPI1_MOSI        GpioAf1
#define PC13_CTIM1_ETR        GpioAf1
#define PC14_CTIM1_CH0        GpioAf1
#define PC15_CTIM1_CH0        GpioAf1
#define PD00_I2C0_SDA         GpioAf1
#define PD01_I2C0_SCL         GpioAf1
#define PD03_1x               GpioAf1
#define PD06_I2C1_SCL         GpioAf1
#define PD07_I2C1_SDA         GpioAf1                            
/**
 * @}
 */
/**
 * @defgroup GPIO_AF2 复用功能2
 * @{
 */
#define PA00_LPUART1_TXD      GpioAf2
#define PA01_LPUART1_RXD      GpioAf2
#define PA02_ATIM0_CHA        GpioAf2
#define PA03_ATIM0_GATE       GpioAf2
#define PA04_USART1_SCK       GpioAf2
#define PA05_ATIM0_ETR        GpioAf2
#define PA06_CTIM0_CH0        GpioAf2
#define PA07_CTIM0_CH1        GpioAf2
#define PA08_ATIM3_CH0A       GpioAf2
#define PA09_ATIM3_CH1A       GpioAf2
#define PA10_ATIM3_CH2A       GpioAf2
#define PA11_ATIM3_GATE       GpioAf2
#define PA12_ATIM3_ETR        GpioAf2
#define PA13_USART0_RXD       GpioAf2
#define PA14_USART0_TXD       GpioAf2
#define PA15_USART1_RXD       GpioAf2
#define PB00_CTIM1_TOGN       GpioAf2
#define PB01_PCLK_OUT         GpioAf2
#define PB02_CTIM0_ETR        GpioAf2
#define PB03_ATIM0_CHB        GpioAf2
#define PB04_CTIM0_CH0        GpioAf2
#define PB05_ATIM3_BK         GpioAf2
#define PB06_USART0_TXD       GpioAf2
#define PB07_USART0_RXD       GpioAf2
#define PB08_ATIM1_CHA        GpioAf2
#define PB09_USART0_SCK       GpioAf2
#define PB10_SPI1_SCK         GpioAf2
#define PB11_ATIM1_CHB        GpioAf2
#define PB12_ATIM3_BK         GpioAf2
#define PB13_I2C1_SCL         GpioAf2
#define PB14_I2C1_SDA         GpioAf2
#define PB15_ATIM3_CH2B       GpioAf2
#define PC13_RTC_1HZ          GpioAf2
#define PC14_CTIM0_TOGN       GpioAf2
#define PC15_2x               GpioAf2
#define PD00_CTRIM_ETRTOG     GpioAf2
#define PD01_ATIM3_CH0B       GpioAf2
#define PD03_2x               GpioAf2
#define PD06_LPUART1_CTS      GpioAf2
#define PD07_LPUART1_RTS      GpioAf2
/**
 * @}
 */
/**
 * @defgroup GPIO_AF3 复用功能3
 * @{
 */             
#define PA00_ATIM0_ETR        GpioAf3
#define PA01_ATIM0_CHB        GpioAf3
#define PA02_VC1_OUT          GpioAf3
#define PA03_ATIM1_CHB        GpioAf3
#define PA04_CTIM1_CH0        GpioAf3
#define PA05_CTIM0_ETR        GpioAf3
#define PA06_ATIM3_BK         GpioAf3
#define PA07_HCLK_OUT         GpioAf3
#define PA08_USART0_TXD       GpioAf3
#define PA09_ATIM0_BK         GpioAf3
#define PA10_ATIM2_BK         GpioAf3
#define PA11_I2C1_SCL         GpioAf3
#define PA12_I2C1_SDA         GpioAf3
#define PA13_LVD_OUT          GpioAf3
#define PA14_ATIM3_CH2A       GpioAf3
#define PA15_LPUART1_RTS      GpioAf3
#define PB00_LPUART0_TXD      GpioAf3
#define PB01_I2CSLV_SDA       GpioAf3
#define PB02_LPUART1_TXD      GpioAf3
#define PB03_ATIM1_GATE       GpioAf3
#define PB04_ATIM2_BK         GpioAf3
#define PB05_ATIM1_BK         GpioAf3
#define PB06_ATIM1_CHB        GpioAf3
#define PB07_ATIM2_CHB        GpioAf3
#define PB08_CAN_RX           GpioAf3
#define PB09_SPI1_CS          GpioAf3
#define PB10_ATIM1_CHA        GpioAf3
#define PB11_LPUART0_RXD      GpioAf3
#define PB12_LPUART0_TXD      GpioAf3
#define PB13_ATIM3_CH0B       GpioAf3
#define PB14_ATIM3_CH1B       GpioAf3
#define PB15_ATIM0_CHB        GpioAf3
#define PC13_ATIM3_CH1B       GpioAf3
#define PC14_LVD_OUT          GpioAf3
#define PC15_3x               GpioAf3
#define PD00_USART1_TXD       GpioAf3
#define PD01_USART1_RXD       GpioAf3
#define PD03_3x               GpioAf3
#define PD06_USART0_CTS       GpioAf3
#define PD07_USART0_RTS       GpioAf3
/**
 * @}
 */                       
/**
 * @defgroup GPIO_AF4 复用功能4
 * @{
 */
#define PA00_VC0_OUT          GpioAf4
#define PA01_ATIM1_ETR        GpioAf4
#define PA02_ATIM1_CHA        GpioAf4
#define PA03_ATIM2_CHB        GpioAf4
#define PA04_ATIM2_ETR        GpioAf4
#define PA05_ATIM0_CHA        GpioAf4
#define PA06_ATIM1_CHA        GpioAf4
#define PA07_ATIM3_CH2A       GpioAf4
#define PA08_CAN_STBY         GpioAf4
#define PA09_I2C0_SCL         GpioAf4
#define PA10_I2C0_SDA         GpioAf4
#define PA11_CAN_TX           GpioAf4
#define PA12_CAN_RX           GpioAf4
#define PA13_ATIM3_ETR        GpioAf4
#define PA14_LVD_OUT          GpioAf4
#define PA15_ATIM0_ETR        GpioAf4
#define PB00_ATIM3_CH2B       GpioAf4
#define PB01_ATIM3_CH1B       GpioAf4
#define PB02_ATIM3_CH0B       GpioAf4
#define PB03_ATIM3_CH0A       GpioAf4
#define PB04_USART0_CTS       GpioAf4
#define PB05_CTIM0_CH1        GpioAf4
#define PB06_ATIM0_CHA        GpioAf4
#define PB07_LPUART1_CTS      GpioAf4
#define PB08_ATIM2_CHA        GpioAf4
#define PB09_ATIM2_CHA        GpioAf4
#define PB10_LPUART0_TXD      GpioAf4
#define PB11_ATIM2_GATE       GpioAf4
#define PB12_ATIM0_BK         GpioAf4
#define PB13_LPUART0_CTS      GpioAf4
#define PB14_ATIM0_CHA        GpioAf4
#define PB15_ATIM0_GATE       GpioAf4
#define PC13_CTIM0_TOG        GpioAf4
#define PC14_4x               GpioAf4
#define PC15_4x               GpioAf4
#define PD00_CTIM1_CH2        GpioAf4
#define PD01_CTIM1_CH3        GpioAf4
#define PD03_4x               GpioAf4
#define PD06_RTC_OUT          GpioAf4
#define PD07_RTC_TS           GpioAf4
/**
 * @}
 */
/**
 * @defgroup GPIO_AF5 复用功能5
 * @{
 */
#define PA00_ATIM1_CHA        GpioAf5
#define PA01_ATIM1_CHB        GpioAf5
#define PA02_ATIM2_CHA        GpioAf5
#define PA03_SPI1_CS          GpioAf5
#define PA04_ATIM3_CH1A       GpioAf5
#define PA05_ATIM3_CH1B       GpioAf5
#define PA06_VC0_OUT          GpioAf5
#define PA07_ATIM2_CHA        GpioAf5
#define PA08_ATIM1_GATE       GpioAf5
#define PA09_MCO_OUT          GpioAf5
#define PA10_ATIM2_GATE       GpioAf5
#define PA11_VC0_OUT          GpioAf5
#define PA12_VC1_OUT          GpioAf5
#define PA13_RTC_1HZ          GpioAf5
#define PA14_RCH_OUT          GpioAf5
#define PA15_ATIM0_CHA        GpioAf5
#define PB00_RCH_OUT          GpioAf5
#define PB01_LPUART0_RTS      GpioAf5
#define PB02_ATIM1_BK         GpioAf5
#define PB03_LPTIM_GATE       GpioAf5
#define PB04_ATIM2_GATE       GpioAf5
#define PB05_LPTIM_GATE       GpioAf5
#define PB06_LPTIM_ETR        GpioAf5
#define PB07_ATIM0_CHB        GpioAf5
#define PB08_ATIM0_GATE       GpioAf5
#define PB09_CAN_TX           GpioAf5
#define PB10_ATIM3_CH2A       GpioAf5
#define PB11_ATIM3_CH1A       GpioAf5
#define PB12_5x               GpioAf5
#define PB13_ATIM1_CHA        GpioAf5
#define PB14_ATIM3_CH2A       GpioAf5
#define PB15_RTC_1HZ          GpioAf5
#define PC13_5x               GpioAf5
#define PC14_5x               GpioAf5
#define PC15_5x               GpioAf5
#define PD00_I2CSLV_SCL       GpioAf5
#define PD01_I2CSLV_SDA       GpioAf5
#define PD03_5x               GpioAf5
#define PD06_ATIM3_BK         GpioAf5
#define PD07_ATIM3_ETR        GpioAf5
/**
 * @}
 */
/**
 * @defgroup GPIO_AF6 复用功能6
 * @{
 */
#define PA00_ATIM3_ETR        GpioAf6
#define PA01_HCLK_OUT         GpioAf6
#define PA02_ATIM3_CH0A       GpioAf6
#define PA03_ATIM3_CH0B       GpioAf6
#define PA04_USART1_TXD       GpioAf6
#define PA05_XTL_OUT          GpioAf6
#define PA06_ATIM3_GATE       GpioAf6
#define PA07_VC1_OUT          GpioAf6
#define PA08_CTIM0_TOGN       GpioAf6
#define PA09_HCLK_OUT         GpioAf6
#define PA10_PCLK_OUT         GpioAf6
#define PA11_SPI0_MISO        GpioAf6
#define PA12_SPI0_MOSI        GpioAf6
#define PA13_CTIM1_CH1        GpioAf6
#define PA14_RCL_OUT          GpioAf6
#define PA15_ATIM3_CH1A       GpioAf6
#define PB00_RCL_OUT          GpioAf6
#define PB01_LPTIM_TOGN       GpioAf6
#define PB02_ATIM0_BK         GpioAf6
#define PB03_XTL_OUT          GpioAf6
#define PB04_ATIM3_CH0B       GpioAf6
#define PB05_CTRIM_ETRTOG     GpioAf6
#define PB06_ATIM3_CH0A       GpioAf6
#define PB07_LPTIM_TOGN       GpioAf6
#define PB08_ATIM3_CH2A       GpioAf6
#define PB09_ATIM2_CHB        GpioAf6
#define PB10_LPUART1_RTS      GpioAf6
#define PB11_LPUART1_CTS      GpioAf6
#define PB12_LPUART0_RTS      GpioAf6
#define PB13_ATIM1_GATE       GpioAf6
#define PB14_LPUART0_RTS      GpioAf6
#define PB15_CTIM0_TOG        GpioAf6
#define PC13_6x               GpioAf6
#define PC14_6x               GpioAf6
#define PC15_6x               GpioAf6
#define PD00_6x               GpioAf6
#define PD01_6x               GpioAf6
#define PD03_6x               GpioAf6
#define PD06_CTIM1_CH2        GpioAf6
#define PD07_CTIM1_CH3        GpioAf6
/**
 * @}
 */                         
/**
 * @defgroup GPIO_AF7 复用功能7
 * @{
 */
#define PA00_ATIM0_CHA        GpioAf7
#define PA01_SPI1_MOSI        GpioAf7
#define PA02_SPI1_MISO        GpioAf7
#define PA03_PCLK_OUT         GpioAf7
#define PA04_I2CSLV_SCL       GpioAf7
#define PA05_XTH_OUT          GpioAf7
#define PA06_LPUART0_CTS      GpioAf7
#define PA07_CTIM1_TOG        GpioAf7
#define PA08_ATIM3_BK         GpioAf7
#define PA09_I2CSLV_SCL       GpioAf7
#define PA10_I2CSLV_SDA       GpioAf7
#define PA11_ATIM3_CH1B       GpioAf7
#define PA12_CTIM1_ETR        GpioAf7
#define PA13_CTRIM_ETRTOG     GpioAf7
#define PA14_PLL_OUT          GpioAf7
#define PA15_CAN_STBY         GpioAf7
#define PB00_PLL_OUT          GpioAf7
#define PB01_USART0_SCK       GpioAf7
#define PB02_ATIM2_BK         GpioAf7
#define PB03_XTH_OUT          GpioAf7
#define PB04_LPTIM_ETR        GpioAf7
#define PB05_USART0_RTS       GpioAf7
#define PB06_LPTIM_TOG        GpioAf7
#define PB07_ATIM3_ETR        GpioAf7
#define PB08_USART0_TXD       GpioAf7
#define PB09_USART0_RXD       GpioAf7
#define PB10_USART1_RTS       GpioAf7
#define PB11_USART1_CTS       GpioAf7
#define PB12_ATIM3_CH0A       GpioAf7
#define PB13_7x               GpioAf7
#define PB14_ATIM1_BK         GpioAf7
#define PB15_LPUART1_RXD      GpioAf7
#define PC13_7x               GpioAf7
#define PC14_7x               GpioAf7
#define PC15_7x               GpioAf7
#define PD00_7x               GpioAf7
#define PD01_7x               GpioAf7
#define PD03_7x               GpioAf7
#define PD06_7x               GpioAf7
#define PD07_7x               GpioAf7
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
 * Local type definitions ('typedef')
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/


/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup GPIO_Global_Functions GPIO全局函数定义
 * @{
 */
en_result_t Gpio_Init(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, stc_gpio_cfg_t *pstcGpioCfg);
boolean_t   Gpio_GetInputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
uint16_t    Gpio_GetInputData(GPIO_TypeDef *GPIOx);
en_result_t Gpio_WriteOutputPort(GPIO_TypeDef *GPIOx, uint16_t u16Val);
boolean_t   Gpio_ReadOutputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SetPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk);
en_result_t Gpio_SetIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_ClrPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk);
en_result_t Gpio_ClrIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SetClrPort(GPIO_TypeDef *GPIOx, uint32_t u32ValMsk);
en_result_t Gpio_SetAnalogMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SetAfMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_af_t enAf);
en_result_t Gpio_EnableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
en_result_t Gpio_DisableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
boolean_t   Gpio_GetIrqStatus(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_ClearIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin);
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_div_t enDiv);
en_result_t Gpio_SfMcoOutputCfg(en_gpio_sf_mco_src_t ensrc,en_gpio_sf_mcoout_div_t endiv);
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
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

#endif /* __GPIO_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
