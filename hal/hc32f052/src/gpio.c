/**
 *******************************************************************************
 * @file  gpio.c
 * @brief This file provides firmware functions to manage the GPIO.
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
#include "gpio.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_GPIO GPIO模块驱动库
 * @brief GPIO Driver Library GPIO模块驱动库
 * @{
 */


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Variables GPIO局部变量定义
 * @{
 */
/**
 * @brief  引脚位定义.
 */
static const uint32_t au32GpioPinTable[16] = {
                                              0x0001U,  /*!< pin00 */ 
                                              0x0002U,  /*!< pin01 */ 
                                              0x0004U,  /*!< pin02 */ 
                                              0x0008U,  /*!< pin03 */ 
                                              0x0010U,  /*!< pin04 */ 
                                              0x0020U,  /*!< pin05 */ 
                                              0x0040U,  /*!< pin06 */ 
                                              0x0080U,  /*!< pin07 */ 
                                              0x0100U,  /*!< pin08 */ 
                                              0x0200U,  /*!< pin09 */ 
                                              0x0400U,  /*!< pin10 */ 
                                              0x0800U,  /*!< pin11 */ 
                                              0x1000U,  /*!< pin12 */ 
                                              0x2000U,  /*!< pin13 */ 
                                              0x4000U,  /*!< pin14 */ 
                                              0x8000U,  /*!< pin15 */ 
                                            };
/**
 * @}
 */
 
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
   
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Functions GPIO全局函数定义
 * @{
 */

/**
 * @brief  GPIO 初始化
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param [in]  pstcGpioCfg:  IO 配置结构体指针@ref stc_gpio_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_Init(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, stc_gpio_cfg_t  *pstcGpioCfg)
{
    uint32_t val;
    val = au32GpioPinTable[enPin];
    
    /* 模拟功能清零, 配置为GPIO功能 */
    REG_CLEARBITS(GPIOx->ADS, val);
    
    if(enPin <= GpioPin7)
    {
        REG_CLEARBITS(GPIOx->AFRL, 0xFu << ((uint32_t)enPin<<2u));
    }
    else
    {
        REG_CLEARBITS(GPIOx->AFRH, 0xFu << (((uint32_t)enPin-8u)<<2u));
    }

    /* 默认输出值配置 */
    REG_MODIFY(GPIOx->OUT, val, ((uint32_t)(pstcGpioCfg->bOutputVal))<<((uint32_t)enPin));
    
    /* 方向配置 */
    REG_MODIFY(GPIOx->DIR, val, ((uint32_t)(pstcGpioCfg->enDir))<<((uint32_t)enPin));
    /* 驱动能力配置 */
    REG_MODIFY(GPIOx->DRIVER, val, ((uint32_t)(pstcGpioCfg->enDrv))<<((uint32_t)enPin));
    /* 上拉/下拉配置 */
    REG_MODIFY(GPIOx->PUPD, val, ((uint32_t)(pstcGpioCfg->enPu))<<((uint32_t)enPin));
    REG_MODIFY(GPIOx->PUPD, val << 16u, ((uint32_t)pstcGpioCfg->enPd) << ((uint32_t)enPin+16u));
    /* 开漏输出功能 */
    REG_MODIFY(GPIOx->OPENDRAIN, val, ((uint32_t)(pstcGpioCfg->enOD))<<((uint32_t)enPin));

    return Ok;
}

/**
 * @brief  GPIO IO输入值获取
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval boolean_t:
 *           - FALSE: 低电平
 *           - TRUE: 高电平
 */
boolean_t Gpio_GetInputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    return (REG_READBITS(GPIOx->IN, au32GpioPinTable[enPin])) ? TRUE : FALSE;
}

/**
 * @brief  GPIO Port输入数据获取
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * 
 * 
 * @retval uint16_t: PORT电平(每bit对应改组一个IO, 1为高电平, 0为低电平)
 */
uint16_t Gpio_GetInputData(GPIO_TypeDef *GPIOx)
{
    return (uint16_t)REG_READ(GPIOx->IN);
}

/**
 * @brief  GPIO PORT整组IO口输出0(低电平)或1(高电平)
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [out] u16Val:        PORT输出值(每bit对应改组一个IO, 1为高电平, 0为低电平)
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_WriteOutputPort(GPIO_TypeDef *GPIOx, uint16_t u16Val)
{
    REG_WRITE(GPIOx->OUT, u16Val);
    return Ok;
}

/**
 * @brief  GPIO IO输出值获取
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval boolean_t:
 *           - FALSE: 低电平
 *           - TRUE: 高电平
 */
boolean_t   Gpio_ReadOutputIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    return (REG_READBITS(GPIOx->OUT, au32GpioPinTable[enPin])) ? TRUE : FALSE;
}

/**
 * @brief  GPIO IO Port设置输出1(高电平)，可同时设置一组Port中的多个PIN
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] u16ValMsk:    该Port的16个PIN掩码值,将需要设置的PIN对应的bit写1有效
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk)
{
    REG_WRITE(GPIOx->BSRR, u16ValMsk);
    
    return Ok;
}

/**
 * @brief  GPIO 单个IO设置输出1(高电平)
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_WRITE(GPIOx->BSRR, au32GpioPinTable[enPin]);
    
    return Ok;
}

/**
 * @brief  GPIO IO Port清零(低电平)，可同时清零一组Port中的多个PIN
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] u16ValMsk:    该Port的16个PIN掩码值,将需要清零的PIN对应的bit写1有效
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_ClrPort(GPIO_TypeDef *GPIOx, uint16_t u16ValMsk)
{
    REG_WRITE(GPIOx->BRR, u16ValMsk);
    
    return Ok;
}

/**
 * @brief  GPIO 单个IO清零(低电平)
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_ClrIO(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_WRITE(GPIOx->BRR, au32GpioPinTable[enPin]);
    
    return Ok;
}

/**
 * @brief  GPIO IO Port置位/清零，可同时置位/清零一组Port中的多个PIN
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] u32ValMsk:    高16bits表示该Port的16个PIN清零掩码值,
 *                            低16bits表示该Port的16个PIN置位掩码值,
 *                            将需要设置的PIN对应的bit写1,同一个PIN的掩码同时为1,则该PIN清零。
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetClrPort(GPIO_TypeDef *GPIOx, uint32_t u32ValMsk)
{
    REG_WRITE(GPIOx->BSRR, u32ValMsk);
    
    return Ok;
}

/**
 * @brief  GPIO IO配置为模拟功能模式
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetAnalogMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_SETBITS(GPIOx->ADS, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO IO复用功能设置
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param  [in] enAf:         复用功能枚举类型选择 @ref en_gpio_af_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SetAfMode(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_af_t enAf)
{
    uint32_t val;
    
    if(enPin <= GpioPin7)
    {
        val = ((uint32_t)enPin) << 2;
        REG_MODIFY(GPIOx->AFRL, 0x0000000Fu << val, ((uint32_t)enAf) << val);
    }
    else
    {
        val = ((uint32_t)enPin-8u) << 2u;
        REG_MODIFY(GPIOx->AFRH, 0x0000000Fu << val, ((uint32_t)enAf) << val);
    }

    return Ok;
}

/**
 * @brief  GPIO IO中断使能
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param  [in] enType:       中断使能类型 @ref en_gpio_irqtype_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_EnableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = (uint32_t)&GPIOx->HIGHIE + (uint32_t)enType;
    
    REG_SETBITS(*(volatile uint32_t *)u32PieAddr, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO IO中断关闭
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * @param  [in] enType:       中断使能类型 @ref en_gpio_irqtype_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_DisableIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = (uint32_t)(&GPIOx->HIGHIE) + (uint32_t)enType;

    REG_CLEARBITS(*(volatile uint32_t *)u32PieAddr, au32GpioPinTable[enPin]);

    return Ok;
}

/**
 * @brief  GPIO 获得IO中断状态
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval boolean_t:
 *           - FALSE: 中断请求未产生
 *           - TRUE: 中断请求产生
 */
boolean_t Gpio_GetIrqStatus(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    return REG_READBITS(GPIOx->IFR, au32GpioPinTable[enPin]) ? TRUE : FALSE;
}

/**
 * @brief  GPIO 清除IO中断状态
 * @param  [in] GPIOx:        GPIO Port口(HC_GPIOA/HC_GPIOB/HC_GPIOC/HC_GPIOD)
 * @param  [in] enPin:        GPIO Pin脚宏定义 @ref en_gpio_pin_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_ClearIrq(GPIO_TypeDef *GPIOx, en_gpio_pin_t enPin)
{
    REG_CLEARBITS(GPIOx->ICR, au32GpioPinTable[enPin]);
    return Ok;
}

/**
 * @brief  GPIO 端口辅助功能配置——MCO输出配置
 * @param  [in] ensrc:        MCO输出时钟选择类型定义 @ref en_gpio_sf_mco_src_t
 * @param  [in] endiv:        MCO输出分频选择类型定义 @ref en_gpio_sf_mcoout_div_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfMcoOutputCfg(en_gpio_sf_mco_src_t ensrc,en_gpio_sf_mcoout_div_t endiv)
{
    HC_GPIOAUX->CR0_f.MCOSEL  = ensrc;
    HC_GPIOAUX->CR0_f.MCODIV  = endiv;
    
    return Ok;
}

/**
 * @brief  GPIO 端口辅助功能配置——PCLK输出配置
 * @param  [in] enDiv:        PCLK输出分频选择类型定义 @ref en_gpio_sf_pclkout_div_t
 *
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_div_t enDiv)
{
    HC_GPIOAUX->CR0_f.PCLKDIV  = enDiv;
    
    return Ok;
}


/**
 * @brief GPIO 端口辅助功能配置——Timer ETR选择配置
 *
 * @param [in]  enTimE       Timer类型选择枚举
 * @param [in]  enSf         Timer互联功能选择枚举
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf)
{
    REG_MODIFY(HC_GPIOAUX->CR1, GPIOAUX_CR1_ATIM0ETR <<((uint32_t)enTimE), (uint32_t)(((uint32_t)enSf) << ((uint32_t)enTimE)));

    return Ok;
}

/**
 * @brief GPIO 端口辅助功能配置——Timer 捕获输入选择配置
 *
 * @param [in]  enTimC       Timer类型选择枚举
 * @param [in]  enSf         Timer互联功能选择枚举
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf)
{
    REG_MODIFY(HC_GPIOAUX->CR2, GPIOAUX_CR2_ATIM0CAP0 <<((uint32_t)enTimC), (uint32_t)(((uint32_t)enSf) << ((uint32_t)enTimC)));

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

