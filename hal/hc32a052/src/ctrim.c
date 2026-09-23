/**
 *******************************************************************************
 * @file  ctrim.c
 * @brief This file provides firmware functions to manage the CTRIM.
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
#include "ctrim.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CTRIM CTRIM模块驱动库
 * @brief CTRIM Driver Library CTRIM模块驱动库
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */

/**
 * @brief  CTRIM 时钟校准初始化配置
 * @param  [in] CTRIMx:      TRIM类型定义           @ref CTRIM_TypeDef
 * @param  [in] pstcInitCfg: Trim时钟校准结构体     @ref stc_ctrim_cali_init_t
 * @retval en_result_t
 *         - Ok:                    OK
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CTRIM_CaliInit(CTRIM_TypeDef* CTRIMx, stc_ctrim_cali_init_t* pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    if (((pstcInitCfg->u32Mode & CTRIM_CR1_MD_B1) != 0u) || (pstcInitCfg->u32RefClockDiv == 0u))
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_STEP | CTRIM_CR0_ETRFLT | CTRIM_CR0_SRC,
        pstcInitCfg->u32InitialStep | pstcInitCfg->u32EtrFilter | pstcInitCfg->u32AccurateClock);

    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_MD | CTRIM_CR1_AUTO | CTRIM_CR1_PRS | CTRIM_CR1_OST | CTRIM_CR1_MDRCH,
        pstcInitCfg->u32Mode | pstcInitCfg->u32RefClockDiv | pstcInitCfg->u32OneShot | pstcInitCfg->u32RCHTrimBits);

    CTRIMx->ARR = pstcInitCfg->u16ReloadVal;

    CTRIMx->FLIM = pstcInitCfg->u16CountErrorLimit;

    return Ok;
}

/**
 * @brief  CTRIM 时钟功能初始化配置
 * @param  [in] CTRIMx:      TRIM类型定义             @ref CTRIM_TypeDef
 * @param  [in] pstcInitCfg: Trim时钟初始化结构体     @ref stc_ctrim_timer_init_t
 * @retval en_result_t
 *         - Ok:                    OK
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CTRIM_TimerInit(CTRIM_TypeDef* CTRIMx, stc_ctrim_timer_init_t* pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    if (pstcInitCfg->u32ClockDiv == 0u)
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_ETRFLT | CTRIM_CR0_SRC, pstcInitCfg->u32EtrFilter | pstcInitCfg->u32Clock);

    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_MD | CTRIM_CR1_AUTO | CTRIM_CR1_PRS, CTRIM_CR1_MD_B1 | pstcInitCfg->u32ClockDiv);

    CTRIMx->ARR = pstcInitCfg->u16ReloadVal;

    return Ok;
}

/**
 * @brief  CTRIM 获取误差计数器计数值
 * @param  [in] CTRIMx:      TRIM类型定义             @ref CTRIM_TypeDef
 * @retval uint32_t：        计数器计数值
 */
uint32_t CTRIM_GetCounter(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CNT, CTRIM_CNT_CNT));
}

/**
 * @brief  CTRIM 设定自动装载寄存器的值
 * @param  [in] CTRIMx:        TRIM类型定义             @ref CTRIM_TypeDef
 * @param  [in] u32AutoReload: 重载值 取值范围 0x0 ~ 0xFFFF 
 * @retval None
 */
void CTRIM_SetAutoReload(CTRIM_TypeDef* CTRIMx, uint32_t u32AutoReload)
{
    REG_MODIFY(CTRIMx->ARR, CTRIM_ARR_ARR, u32AutoReload);
}

/**
 * @brief  CTRIM 获取自动装载寄存器的值
 * @param  [in] CTRIMx:        TRIM类型定义             @ref CTRIM_TypeDef
 * @retval uint32_t：          自动装载寄存器的值
 */
uint32_t CTRIM_GetAutoReload(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->ARR, CTRIM_ARR_ARR));
}

/**
 * @brief  CTRIM RCH/RCL TRIM初始步进量配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] CTRIMx:        TRIM类型定义      @ref CTRIM_TypeDef
 * @param  [in] u32TrimStep:   初始步进量        @ref CTRIM_INITIAL_STEP_SELECTION
 * @retval None
 */
void CTRIM_SetInitialStep(CTRIM_TypeDef* CTRIMx, uint32_t u32TrimStep)
{
    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_STEP, u32TrimStep);
}

/**
 * @brief  CTRIM 获取TRIM初始步进量
 * @param  [in] CTRIMx:     TRIM类型定义      @ref CTRIM_TypeDef
 * @retval uint32_t:        TRIM初始步进量
 *         - CTRIM_INITIAL_STEP_1
 *         - CTRIM_INITIAL_STEP_2
 *         - CTRIM_INITIAL_STEP_4
 *         - CTRIM_INITIAL_STEP_8
 *         - CTRIM_INITIAL_STEP_16
 *         - CTRIM_INITIAL_STEP_32
 *         - CTRIM_INITIAL_STEP_64
 *         - CTRIM_INITIAL_STEP_128
 */
uint32_t CTRIM_GetInitialStep(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR0, CTRIM_CR0_STEP));
}

/**
 * @brief  CTRIM 外部管脚输入时钟滤波配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] CTRIMx:            TRIM类型定义         @ref CTRIM_TypeDef
 * @param  [in] u32ExClockFilter:  外部输入时钟滤波配置  @ref CTRIM_ETR_CLOCK_FILTER_SELECTION
 * @retval None
 */
void CTRIM_SetEtrClockFilter(CTRIM_TypeDef* CTRIMx, uint32_t u32ExClockFilter)
{
    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_ETRFLT, u32ExClockFilter);
}

/**
 * @brief  CTRIM 获取外部管脚输入时钟滤波配置
 * @param  [in] CTRIMx:            TRIM类型定义         @ref CTRIM_TypeDef
 * @retval uint32_t： 外部输入时钟滤波配置
 *         - CTRIM_ETR_CLOCK_FILTER_NONE:               外部输入时钟无滤波
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV1_CYCLE2:   采样时钟频率为PCLK，滤波宽度小于2个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV1_CYCLE4:   采样时钟频率为PCLK，滤波宽度小于4个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV1_CYCLE6:   采样时钟频率为PCLK，滤波宽度小于6个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV4_CYCLE4:   采样时钟频率为PCLK/4，滤波宽度小于4个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV4_CYCLE6:   采样时钟频率为PCLK/4，滤波宽度小于6个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV8_CYCLE4:   采样时钟频率为PCLK/8，滤波宽度小于4个采样周期
 *         - CTRIM_ETR_CLOCK_FILTER_PCLK_DIV8_CYCLE6:   采样时钟频率为PCLK/8，滤波宽度小于6个采样周期
 */
uint32_t CTRIM_GetEtrClockFilter(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR0, CTRIM_CR0_ETRFLT));
}

/**
 * @brief  CTRIM 精确时钟源选择，必须在CTRIM模块未使能时才可以配置
 * @param  [in] CTRIMx:            TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32ClockSource:    时钟源选择      @ref CTRIM_ACCURATE_CLOCK_SELECTION
 * @retval None
 */
void CTRIM_SetAccurateClock(CTRIM_TypeDef* CTRIMx, uint32_t u32ClockSource)
{
    REG_MODIFY(CTRIMx->CR0, CTRIM_CR0_SRC, u32ClockSource);
}

/**
 * @brief  CTRIM 获取精确时钟源选择
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t:           时钟源选择
 *         - CTRIM_ACCURATE_CLOCK_ETR:         精准时钟源选择外部输入时钟
 *         - CTRIM_ACCURATE_CLOCK_XTH:         精准时钟源选择XTH
 *         - CTRIM_ACCURATE_CLOCK_XTL:         精准时钟源选择XTL
 *         - CTRIM_ACCURATE_CLOCK_PCLK:        精准时钟源选择PCLK
 *         - CTRIM_ACCURATE_CLOCK_RCL:         精准时钟源选择RCL
 *         - CTRIM_ACCURATE_CLOCK_RCH:         精准时钟源选择RCH
 *         - CTRIM_ACCURATE_CLOCK_LPTIM_TOG:   精准时钟源选择LPTIM_TOG
 */
uint32_t CTRIM_GetAccurateClock(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR0, CTRIM_CR0_SRC));
}

/**
 * @brief  CTRIM 工作模式配置
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32Mode:       工作模式选择    @ref CTRIM_MODE_SELECTION
 * @retval None
 */
void CTRIM_SetMode(CTRIM_TypeDef* CTRIMx, uint32_t u32Mode)
{
    REG_MODIFY(CTRIMx->CR1, (CTRIM_CR1_AUTO | CTRIM_CR1_MD), u32Mode);
}

/**
 * @brief  CTRIM 获取工作模式配置
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t：          工作模式选择
 *         - CTRIM_MODE_RCH_AUTO_TRIM:    RCH自动校准模式
 *         - CTRIM_MODE_RCL_AUTO_TRIM:    RCL自动校准模式
 *         - CTRIM_MODE_TIMER:            定时器模式
 */
uint32_t CTRIM_GetMode(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, (CTRIM_CR1_AUTO | CTRIM_CR1_MD)));
}

/**
 * @brief  CTRIM RCH Trim Bits配置
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32RchTrimBits: TRIM Bits选择   @ref CTRIM_RCH_TRIM_BITS_SELECTION
 * @retval None
 */
void CTRIM_SetRCHTrimBits(CTRIM_TypeDef* CTRIMx, uint32_t u32RchTrimBits)
{
    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_MDRCH, u32RchTrimBits);
}

/**
 * @brief  CTRIM 获取RCH Trim Bits配置
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t：          工作模式选择
 *         - CTRIM_RCH_TRIM_11bit:   RCH 单次校准 11bit
 *         - CTRIM_RCH_TRIM_5bit:    RCH 粗调校准 5bit
 *         - CTRIM_RCH_TRIM_6bit:    RCH 细调校准 6bit
 */
uint32_t CTRIM_GetRCHTrimBits(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, CTRIM_CR1_MDRCH));
}

/**
 * @brief  CTRIM 参考时钟预分频配置,CTRIMx->CR1.PRS不能配置为0值，否则CTRIM不能正常工作
 * @param  [in] CTRIMx:         TRIM类型定义         @ref CTRIM_TypeDef
 * @param  [in] u32RefClockDiv: 参考时钟预分频配置    @ref CTRIM_REF_CLOCK_DIV_SELECTION
 * @retval None
 */
void CTRIM_SetRefClockDiv(CTRIM_TypeDef* CTRIMx, uint32_t u32RefClockDiv)
{
    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_PRS, u32RefClockDiv);
}

/**
 * @brief  CTRIM 获取参考时钟预分频配置
 * @param  [in] CTRIMx:         TRIM类型定义         @ref CTRIM_TypeDef
 * @retval uint32_t: 参考时钟预分频配置
 *         - CTRIM_REF_CLOCK_DIV2
 *         - CTRIM_REF_CLOCK_DIV4
 *         - CTRIM_REF_CLOCK_DIV8
 *         - CTRIM_REF_CLOCK_DIV16
 *         - CTRIM_REF_CLOCK_DIV32
 *         - CTRIM_REF_CLOCK_DIV64
 *         - CTRIM_REF_CLOCK_DIV128
 *         - CTRIM_REF_CLOCK_DIV512
 *         - CTRIM_REF_CLOCK_DIV1024
 *         - CTRIM_REF_CLOCK_DIV2048
 *         - CTRIM_REF_CLOCK_DIV4096
 *         - CTRIM_REF_CLOCK_DIV8192
 *         - CTRIM_REF_CLOCK_DIV16384
 *         - CTRIM_REF_CLOCK_DIV32768
 */
uint32_t CTRIM_GetRefClockDiv(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, CTRIM_CR1_PRS));
}

/**
 * @brief  CTRIM 校准模式配置
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32OneShotMode: 校准模式配置    @ref CTRIM_ONE_SHOT_SELECTION
 * @retval None
 */
void CTRIM_SetOneShot(CTRIM_TypeDef* CTRIMx, uint32_t u32OneShotMode)
{
    REG_MODIFY(CTRIMx->CR1, CTRIM_CR1_OST, u32OneShotMode);
}

/**
 * @brief  CTRIM 获取校准模式配置
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 校准模式配置
 *         - CTRIM_ONE_SHOT_REPETITIVE:    实时校准模式
 *         - CTRIM_ONE_SHOT_SINGLE:        单次校准模式
 */
uint32_t CTRIM_GetOneShot(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->CR1, CTRIM_CR1_OST));
}

/**
 * @brief  CTRIM 获取误差计数器计数方向
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 误差计数器计数方向
 *         - CTRIM_ARR_COUNT_DIR_INCREASE:  递增计数，RCH输出频率高于目标频率，或RCL输出频率低于目标频率
 *         - CTRIM_ARR_COUNT_DIR_DECREASE:  递减计数，RCH输出频率低于目标频率，或RCL输出频率高于目标频率
 */
uint32_t CTRIM_GetARRCoutDir(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->ISR, CTRIM_ISR_DIR));
}

/**
 * @brief  CTRIM 获取TrimCode值，及trim结束后的trim校准值
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: TrimCode值 
 */
uint32_t CTRIM_GetTrimCode(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->TVAL, CTRIM_TVAL_TVAL));
}

/**
 * @brief  CTRIM 获取计数误差捕获值，校准结束时，ARR寄存器里面的值
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 计数误差捕获值
 */
uint32_t CTRIM_GetCountErrorCapture(CTRIM_TypeDef* CTRIMx)
{
    return (uint32_t)(REG_READBITS(CTRIMx->FCAP, CTRIM_FCAP_FCAP));
}

/**
 * @brief  CTRIM 设置误差允许值， 一个周期计数结束，ARR寄存器里的值小于当前设定值，则认为校验成功
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u16ErrLimit:     误差上限值 取值范围 0x0 ~ 0xFFF 
 * @retval None
 */
void CTRIM_SetCountErrorLimit(CTRIM_TypeDef* CTRIMx, uint16_t u16ErrLimit)
{
    REG_MODIFY(CTRIMx->FLIM, CTRIM_FLIM_FLIM, u16ErrLimit);
}

/**
 * @brief  CTRIM 获取误差允许值， 一个周期计数结束，ARR寄存器里的值小于当前设定值，则认为校验成功
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint16_t：  误差上限值
 */
uint16_t CTRIM_GetCountErrorLimit(CTRIM_TypeDef* CTRIMx)
{
    return (uint16_t)(REG_READBITS(CTRIMx->FLIM, CTRIM_FLIM_FLIM));
}

/**
 * @brief  CTRIM 开启模块
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval None
 */
void CTRIM_Enable(CTRIM_TypeDef* CTRIMx)
{
    REG_SETBITS(CTRIMx->CR1, CTRIM_CR1_EN);
}

/**
 * @brief  CTRIM 禁止模块
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval None
 */
void CTRIM_Disable(CTRIM_TypeDef* CTRIMx)
{
    REG_CLEARBITS(CTRIMx->CR1, CTRIM_CR1_EN);
}

/**
 * @brief  CTRIM 检查模块是否已开启
 * @param  [in] CTRIMx:         TRIM类型定义    @ref CTRIM_TypeDef
 * @retval uint32_t: 状态
 *         - 0：  未开启
 *         - 非0：已开启
 */
boolean_t CTRIM_IsEnable(CTRIM_TypeDef* CTRIMx)
{
    return (REG_READBITS(CTRIMx->CR1, CTRIM_CR1_EN) == CTRIM_CR1_EN) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 中断使能
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32IT:         TRIM类型定义    @ref CTRIM_IT_SELECTION
 * @retval None
 */
void CTRIM_EnableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT)
{
    REG_SETBITS(CTRIMx->IER, u32IT);
}

/**
 * @brief  CTRIM 中断禁止
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32IT:         TRIM类型定义    @ref CTRIM_IT_SELECTION
 * @retval None
 */
void CTRIM_DisableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT)
{
    REG_CLEARBITS(CTRIMx->IER, u32IT);
}

/**
 * @brief  CTRIM 检查中断是否开启
 * @param  [in] CTRIMx:        TRIM类型定义    @ref CTRIM_TypeDef
 * @param  [in] u32IT:         TRIM类型定义    @ref CTRIM_IT_SELECTION
 * @retval uint32_t: 状态
 *         - 0：  未开启
 *         - 非0：已开启
 */
boolean_t CTRIM_IsEnableIT(CTRIM_TypeDef* CTRIMx, uint32_t u32IT)
{
    return (REG_READBITS(CTRIMx->IER, u32IT) == u32IT) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 获取中断标志
 * @param  [in] CTRIMx:        TRIM类型定义                               @ref CTRIM_TypeDef
 * @param  [in] u32ITFlag:    中断标记,CTRIM_IT_SELECTION值或值相或的组合 @ref CTRIM_IT_SELECTION
 * @retval uint32_t: 状态
 *         - 0：  对应每位的功能
 *         - 非0：对应每位的功能
 */
boolean_t CTRIM_IsActiveFlag(CTRIM_TypeDef* CTRIMx, uint32_t u32ITFlag)
{
    return (REG_READBITS(CTRIMx->ISR, u32ITFlag) == u32ITFlag) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 清除中断标志
 * @param  [in] CTRIMx:        TRIM类型定义                               @ref CTRIM_TypeDef
 * @param  [in] u32ITFlag:     中断标记,CTRIM_IT_SELECTION值或值相或的组合 @ref CTRIM_IT_SELECTION
 * @retval None
 */
void CTRIM_ClearFlag(CTRIM_TypeDef* CTRIMx, uint32_t u32ITFlag)
{
    REG_CLEARBITS(CTRIMx->ICR, u32ITFlag);
}

/**
 * @brief  CTRIM 清除所有标志
 * @param  [in] CTRIMx:        TRIM类型定义                               @ref CTRIM_TypeDef
 * @retval None
 */
void CTRIM_ClearFlag_ALL(CTRIM_TypeDef* CTRIMx)
{
    CTRIMx->ICR = 0u;
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
