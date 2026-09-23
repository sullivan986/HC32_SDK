/**
 *******************************************************************************
 * @file  board_stkhc32a052.h
 * @brief stk board common define.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-28       MADS Team       First version
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

#ifndef __BOARD_STKHC32A052_H__
#define __BOARD_STKHC32A052_H__


/**
 * @defgroup STK_GPIO_DEFINE_Define STK板相关参数和功能IO定义
 * @{
 */

/**
 * @defgroup USER_KEY_Define 用户按键引脚
 * @{
 */
#define STK_USER_PORT       HC_GPIOB
#define STK_USER_PIN        GpioPin1

#define STK_USER_READ()     (HC_GPIOB->IN_f.PIN1)
/**
  * @}
  */

/**
 * @defgroup LED_Define LED灯引脚定义
 * @{
 */
#define STK_LED_PORT        HC_GPIOA
#define STK_LED_PIN         GpioPin15

#define STK_LED_ON()        (HC_GPIOA->BSRR_f.BSPIN15 = 1)
#define STK_LED_OFF()       (HC_GPIOA->BRR_f.PIN15 = 1)
/**
  * @}
  */

/**
 * @defgroup XTH_Define XTH频率和引脚定义
 * @{
 */
#define SYSTEM_XTH          (8u*1000u*1000u)    /* 8MHz */

#define STK_XTHI_PORT       GpioPortD
#define STK_XTHI_PIN        GpioPin0
#define STK_XTHO_PORT       GpioPortD
#define STK_XTHO_PIN        GpioPin1
/**
  * @}
  */

/**
 * @defgroup XTL_Define XTL频率和引脚定义
 * @{
 */
#define SYSTEM_XTL          (32768u)            /* 32768Hz */

#define STK_XTLI_PORT       GpioPortC
#define STK_XTLI_PIN        GpioPin14
#define STK_XTLO_PORT       GpioPortC
#define STK_XTLO_PIN        GpioPin15
/**
  * @}
  */


/**
 * @defgroup I2C_EEPROM_Define I2C EEPROM引脚定义
 * @{
 */
#define EVB_I2C0_EEPROM_SCL_PORT    GpioPortB
#define EVB_I2C0_EEPROM_SCL_PIN     GpioPin6
#define EVB_I2C0_EEPROM_SDA_PORT    GpioPortB
#define EVB_I2C0_EEPROM_SDA_PIN     GpioPin7
/**
  * @}
  */

/**
 * @defgroup SPI_Define SPI引脚定义
 * @{
 */
#define STK_SPI0_CS_PORT      GpioPortB
#define STK_SPI0_CS_PIN       GpioPin12
#define STK_SPI0_SCK_PORT     GpioPortB
#define STK_SPI0_SCK_PIN      GpioPin13
#define STK_SPI0_MISO_PORT    GpioPortB
#define STK_SPI0_MISO_PIN     GpioPin14
#define STK_SPI0_MOSI_PORT    GpioPortB
#define STK_SPI0_MOSI_PIN     GpioPin15
/**
  * @}
  */

/**
  * @}
  */

#endif
