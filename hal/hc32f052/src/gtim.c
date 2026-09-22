/**
 *******************************************************************************
 * @file  gtim.c
 * @brief This file provides firmware functions to manage the GTIM.
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

/******************************************************************************
 * Include files
 ******************************************************************************/

#include "gtim.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_GTIM GTIM模块驱动库
 * @brief GTIM Driver Library GTIM模块驱动库
 * @{
 */
   
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
   
/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
   
/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
   
/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
   
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup GTIM_Global_Functions GTIM全局函数定义
 * @{
 */
   
/**
 * @brief  定时器GTIM的初始化配置
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] pstcInitCfg :                初始化GTIMx的结构体
 * @        pstcInitCfg->u32TaskMode:        定时器计数模式选择  @ref Gtim_Task_Count_Mode
 * @        pstcInitCfg->u32WorkMode:        工作模式            @ref Gtim_Work_Mode
 * @        pstcInitCfg->u32Prescaler:       计数时钟信号分频    @ref Gtim_Clock_Divide
 * @        pstcInitCfg->u32ToggleEn:        Toggle_N和Toggle_P输出使能 @ref Gtim_Tog_Ouput_define
 * @        pstcInitCfg->u32TriggerSource:   触发源选择:                @ref Gtim_Trigger_Source_Sel
 * @        pstcInitCfg->u32ExInputPolarity: 外部输入极性选择           @ref Gtim_ETR_Input_Polarity
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Gtim_Init(GTIM_TypeDef* GTIMx, stc_gtim_init_t* pstcInitCfg)
{
    if (NULL == pstcInitCfg)
    {
        return ErrorInvalidParameter;
    }

    REG_MODIFY( GTIMx->CR0,\
                     GTIM_CR0_MD\
                            | GTIM_CR0_TOGEN\
                            | GTIM_CR0_PRS\
                            | GTIM_CR0_OST\
                            | GTIM_CR0_TRS\
                            | GTIM_CR0_ETP\
                            , \
                             pstcInitCfg->u32TaskMode
                            | pstcInitCfg->u32WorkMode\
                            | pstcInitCfg->u32Prescaler\
                            | pstcInitCfg->u32ToggleEn\
                            | pstcInitCfg->u32TriggerSource\
                            | pstcInitCfg->u32ExInputPolarity);
	
    REG_MODIFY( GTIMx->ARR, GTIM_ARR_ARR, (uint16_t)pstcInitCfg->u32AutoReloadVal);

    return Ok;
}

/**
 * @brief  获取GTIM计数器计数值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIMx计数器计数值        
 */
uint32_t Gtim_GetCounter(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CNT, GTIM_CNT_CNT));	
}
   
/**
 * @brief  设置GTIM计数器计数值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u16CntValue: 计数值
 *
 * @retval None      
 */
void Gtim_SetCounter(GTIM_TypeDef* GTIMx, uint16_t u16CntValue)
{
    REG_WRITE( GTIMx->CNT, (uint32_t)u16CntValue);
}
 
/**
 * @brief  设定GTIM 重载寄存器的值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u16AutoReload: 重载值
 *
 * @retval None       
 */
void Gtim_SetAutoReload(GTIM_TypeDef* GTIMx, uint16_t u16AutoReload)
{
    REG_WRITE(GTIMx->ARR, (uint32_t)u16AutoReload);
}
 
/**
 * @brief  获取GTIM 重载寄存器的值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIMx重载寄存器的值    
 */
uint32_t Gtim_GetAutoReload(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->ARR, GTIM_ARR_ARR));	
}

/**
 * @brief  开启定时器GTIM模块
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_Enable(GTIM_TypeDef* GTIMx)
{
    REG_SETBITS( GTIMx->CR0, GTIM_CR0_CEN);
}

/**
 * @brief  禁止定时器GTIM模块
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_Disable(GTIM_TypeDef* GTIMx)
{
    REG_CLEARBITS( GTIMx->CR0, GTIM_CR0_CEN);	
}

/**
 * @brief  检查定时器GTIM模块是否已开启
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval boolean_t:
 *           - FALSE: 未开启
 *           - TRUE: 已开启
 */
boolean_t Gtim_IsEnable(GTIM_TypeDef* GTIMx)
{
    return REG_READBITS( GTIMx->CR0, GTIM_CR0_CEN) ? TRUE : FALSE;	
}


/**
 * @brief  设定定时器GTIM 工作模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32WorkMode: 选择GTIM工作模式  @ref Gtim_Work_Mode
 *
 * @retval None
 */
void Gtim_SetWorkMode(GTIM_TypeDef* GTIMx, uint32_t u32WorkMode)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_MD, u32WorkMode);	
}
 
/**
 * @brief  获取定时器GTIM 工作模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIM工作模式  @ref Gtim_Work_Mode         
 */
uint32_t Gtim_GetWorkMode(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS(GTIMx->CR0, GTIM_CR0_MD));	
}

/**
 * @brief  定时器GTIM TOG输出使能，TOGP和TOGN输出相位相反的信号
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_EnableToggle(GTIM_TypeDef* GTIMx)
{
    REG_SETBITS( GTIMx->CR0, GTIM_CR0_TOGEN);
}

/**
 * @brief  定时器GTIM TOG输出禁止，TOGP和TOGN同时输出0
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_DisableToggle(GTIM_TypeDef* GTIMx)
{
    REG_CLEARBITS( GTIMx->CR0, GTIM_CR0_TOGEN);	
}

/**
 * @brief  检查定时器GTIM模块 TOG输出 是否已开启
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval boolean_t:
 *           - FALSE: 未开启
 *           - TRUE: 已开启
 */
boolean_t Gtim_IsEnableToggle(GTIM_TypeDef* GTIMx)
{
    return REG_READBITS( GTIMx->CR0, GTIM_CR0_TOGEN) ? TRUE : FALSE;	
}

/**
 * @brief  定时器GTIM模块 计数时钟预除频
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32CounterClkDiv: 计数时钟预分频选择  @ref Gtim_Clock_Divide
 *
 * @retval None      
 */
void Gtim_SetCounterClkDiv(GTIM_TypeDef* GTIMx, uint32_t u32CounterClkDiv)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_PRS, u32CounterClkDiv);	
}
 
/**
 * @brief  获取定时器GTIM 时钟，此时钟是定时器模块工作时钟，非计数时钟源
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: 计数时钟预分频   @ref Gtim_Clock_Divide
 */
uint32_t Gtim_GetCounterClkDiv(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_PRS));	
}


 /**
 * @brief  设定GTIM 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Mode: 计数模式 @ref Gtim_Task_Count_Mode   
 *
 * @retval None    
 */
void Gtim_SetTaskMode(GTIM_TypeDef* GTIMx, uint32_t u32Mode)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_OST, u32Mode);	
}
 
/**
 * @brief  获取GTIM 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIM计数模式 @ref Gtim_Task_Count_Mode       
 */
uint32_t Gtim_GetTaskMode(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_OST));	
}

/**
 * @brief  设定定时器GTIM 触发源
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32TriggerSource: 选择GTIM触发源  @ref Gtim_Trigger_Source_Sel
 *
 * @retval None     
 */
void Gtim_SetTriggerSource(GTIM_TypeDef* GTIMx, uint32_t u32TriggerSource)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_TRS, u32TriggerSource);	
}
 
/**
 * @brief  获取定时器GTIM 触发源
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: GTIM 触发源  @ref Gtim_Trigger_Source_Sel      
 */
uint32_t Gtim_GetTriggerSource(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_TRS));	
}


 
/**
 * @brief  设定定时器GTIM 外部输入ETR极性设定
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32ExInputPolarity: 外部输入ETR极性 @ref Gtim_ETR_Input_Polarity  
 *
 * @retval None       
 */
void Gtim_SetExInputPolarity(GTIM_TypeDef* GTIMx, uint32_t u32ExInputPolarity)
{
    REG_MODIFY( GTIMx->CR0, GTIM_CR0_ETP, u32ExInputPolarity);	
}
 
/**
 * @brief  获取定时器GTIM 外部输入ETR极性配置
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: 外部输入ETR极性  @ref Gtim_ETR_Input_Polarity         
 */
uint32_t Gtim_GetExInputPolarity(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR0, GTIM_CR0_ETP));	
}

/**
 * @brief  设定定时器GTIM 外部输入ETR滤波时间
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32ExInputFilter: 外部输入ETR滤波时间  @ref Gtim_ETP_External_Input_Filter
 * 
 * @retval None
 */
void Gtim_SetExInputFilter(GTIM_TypeDef* GTIMx, uint32_t u32ExInputFilter)
{
    REG_MODIFY( GTIMx->CR1, GTIM_CR1_ETRFLT, u32ExInputFilter);	
}

/**
 * @brief  获取定时器GTIM 外部输入ETR滤波时间
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval uint32_t: 外部输入ETR滤波时间  @ref Gtim_ETP_External_Input_Filter      
 */
uint32_t Gtim_GetExInputFilter(GTIM_TypeDef* GTIMx)
{
    return (uint32_t)(REG_READBITS( GTIMx->CR1, GTIM_CR1_ETRFLT));	
}

/**
 * @brief  定时器GTIM 捕获比较模式选择
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 * @param  [in] u32CaptureMode: 捕获比较模式选择 @ref Gtim_Capture_Compare_Mode_Config     
 *
 * @retval None
 */
void Gtim_SetCompareCaptureMode(GTIM_TypeDef* GTIMx, uint32_t u32Channel, uint32_t u32CaptureMode)
{
    REG_MODIFY(GTIMx->CMMR, GTIM_CMMR_CC0M << u32Channel, u32CaptureMode << u32Channel);	
}
 
/**
 * @brief  获取定时器GTIMx 捕获比较模式
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 *
 * @retval uint32_t: 捕获比较模式 @ref Gtim_Capture_Compare_Mode_Config     
 */
uint32_t Gtim_GetCompareCaptureMode(GTIM_TypeDef* GTIMx, uint32_t u32Channel)
{
    return (uint32_t)((REG_READBITS(GTIMx->CMMR, GTIM_CMMR_CC0M << u32Channel)) >> u32Channel);	
}

/**
 * @brief  设定GTIM 比较捕获（寄存器）值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 * @param  [in] u32Capture: 16位比较捕获寄存器值
 *
 * @retval None     
 */
void Gtim_SetCompareCaptureReg(GTIM_TypeDef* GTIMx, uint32_t u32Channel, uint32_t u32Capture)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress =(uint32_t)(&GTIMx->CCR0) + (uint32_t)u32Channel;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAdress, GTIM_CCR0_CCR, u32Capture);	
}
 
/**
 * @brief  获取GTIM 比较捕获（寄存器）值
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32Channel: 比较捕获通道选择 @ref Gtim_Capture_Compare_Channel_Sel
 *
 * @retval uint32_t: 比较捕获寄存器的值  
 */
uint32_t Gtim_GetCompareCaptureReg(GTIM_TypeDef* GTIMx, uint32_t u32Channel)
{
    uint32_t u32BaseAdress;
    
    u32BaseAdress =(uint32_t)(&GTIMx->CCR0) + u32Channel;
    
    return (uint32_t)(REG_READBITS(*(volatile uint32_t *)u32BaseAdress, GTIM_CCR0_CCR));	
}
        
/**
 * @brief  禁止所有通道比较捕获功能
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 *
 * @retval None
 */
void Gtim_DisableCompareCaptureAll(GTIM_TypeDef* GTIMx)
{
    REG_CLEAR( GTIMx->CMMR);
}

/**
 * @brief  GTIM 中断或触发DMA/ADC使能
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IT: 中断使能控制位  @ref Gtim_Interrupt_TRIG_Enable_Disable
 *
 * @retval None
 */
void Gtim_EnableIT(GTIM_TypeDef* GTIMx, uint32_t u32IT)
{
    REG_SETBITS( GTIMx->IER, u32IT);
}

/**
 * @brief  GTIM 中断禁止
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IT: 中断使能控制位  @ref Gtim_Interrupt_TRIG_Enable_Disable
 *
 * @retval None
 */
void Gtim_DisableIT(GTIM_TypeDef* GTIMx, uint32_t u32IT)
{
    REG_CLEARBITS( GTIMx->IER, u32IT);	
}

/**
 * @brief  检查 GTIM 中断是否已使能
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IntEnableTypes  中断使能类型   @ref Gtim_Interrupt_TRIG_Enable_Disable
 *
 * @retval boolean_t:
 *           - FALSE: 未使能
 *           - TRUE: 已使能
 */
boolean_t Gtim_IsEnableIT(GTIM_TypeDef* GTIMx, uint32_t u32IntEnableTypes)
{
    return (REG_READBITS( GTIMx->IER, u32IntEnableTypes) == u32IntEnableTypes) ? TRUE : FALSE;	
}


/**
 * @brief  获取 GTIM 中断标志
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IntFlagTypes     中断标志类型  @ref Gtim_Interrupt_Flag
 *
 * @retval boolean_t:
 *           - FALSE: 未置起
 *           - TRUE: 已置起
 */
boolean_t Gtim_IsActiveFlag(GTIM_TypeDef* GTIMx, uint32_t u32IntFlagTypes)
{
    return (REG_READBITS(GTIMx->IFR, u32IntFlagTypes) == u32IntFlagTypes) ? TRUE : FALSE;	
}
               
               
/**
 * @brief  清除 GTIM 中断 标志位
 *
 * @param  [in] GTIMx: GTIM单元名宏定义(HC_GTIM0/HC_GTIM1)
 * @param  [in] u32IntClrFlag      中断清除标志定义 @ref Gtim_Interrupt_Clear_Types
 *
 * @retval None
 */
void Gtim_ClearFlag(GTIM_TypeDef* GTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS( GTIMx->ICR, u32IntClrFlag);	
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
 ******************************************************************************/
