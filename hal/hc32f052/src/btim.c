/**
 *******************************************************************************
 * @file  btim.c
 * @brief This file provides firmware functions to manage the BTIM.
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

#include "btim.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_BTIM BTIM模块驱动库
 * @brief BTIM Driver Library BTIM模块驱动库
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
 * @defgroup BTIM_Global_Functions BTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器BTIMx的初始化配置
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] pstcInitCfg : 初始化BTIMx的结构体
 *              - pstcInitCfg->u32TaskMode:  单次/连续计数模式控制  @ref Btim_Count_Task_Mode
 *              - pstcInitCfg->u32WorkMode:  工作模式控制     @ref Btim_Work_Mode
 *              - pstcInitCfg->u32Prescaler: 预分频时钟选择   @ref Btim_Clock_devide        
 *              - pstcInitCfg->u32ToggleEn:  TOG管脚输出使能控制  @ref Btim_Toggle_ourput_control
 *              - pstcInitCfg->u32TriggerSource: 触发源选择  @ref Btim_Trigger_Source_Selection
 *              - pstcInitCfg->u32ExInputPolarity: 外部管脚输入的ETR信号极性选择 @ref  Btim_ETR_Input_Polarity
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
*/
en_result_t Btim_Init(BTIM_TypeDef* BTIMx, stc_btim_init_t* pstcInitCfg)
{
    if (NULL == pstcInitCfg)
    {
        return ErrorInvalidParameter;
    }
	
    REG_MODIFY(BTIMx->CR, 
                           BTIM_CR_OST\
                            | BTIM_CR_MD\
                            | BTIM_CR_PRS\
                            | BTIM_CR_TOGEN\
                            | BTIM_CR_TRS\
                            | BTIM_CR_ETP\
                            , \
                            pstcInitCfg->u32TaskMode\
                            | pstcInitCfg->u32WorkMode\
                            | pstcInitCfg->u32Prescaler\
                            | pstcInitCfg->u32ToggleEn\
                            | pstcInitCfg->u32TriggerSource\
                            | pstcInitCfg->u32ExInputPolarity);
	
    REG_MODIFY(BTIMx->ARR, BTIM_ARR_ARR, (uint16_t)pstcInitCfg->u32AutoReloadVal);
	        
    return Ok;
}
                   
/**
 * @brief  设定BTIMx计数器计数值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u16CntValue  16bit 计数值
 *
 * @retval None
 */
void Btim_SetCounter(BTIM_TypeDef* BTIMx, uint16_t u16CntValue)
{
    REG_WRITE(BTIMx->CNT, (uint32_t)u16CntValue);
}

/**
 * @brief  获取BTIMx计数器计数值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t: BTIMx计数器计数值   
 */
uint32_t Btim_GetCounter(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CNT, BTIM_CNT_CNT));	
}
 
/**
 * @brief  设定BTIMx 重载寄存器的值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u16AutoReload: 重载值
 *
 * @retval None
 */       
void Btim_SetAutoReload(BTIM_TypeDef* BTIMx, uint16_t u16AutoReload)
{
    REG_WRITE(BTIMx->ARR, (uint32_t)u16AutoReload);
}
 
/**
 * @brief  获取BTIMx 重载寄存器的值
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t: BTIMx重载寄存器的值   
 */
uint32_t Btim_GetAutoReload(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->ARR, BTIM_ARR_ARR));	
}

/**
 * @brief  开启定时器BTIMx模块
 *
 * @param  [in] BTIMx: BTIM结构体变量
 *
 * @retval None
 */
 void Btim_Enable(BTIM_TypeDef *BTIMx)
{
    REG_SETBITS(BTIMx->CR, BTIM_CR_CEN);
}

/**
 * @brief  禁止定时器BTIMx模块
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval NULL
 */
 void Btim_Disable(BTIM_TypeDef *BTIMx)
{
    REG_CLEARBITS(BTIMx->CR, BTIM_CR_CEN);	
}

/**
 * @brief  检查定时器BTIMx模块是否已开启
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval  FALSE:未开启;  TRUE:已开启
 */
 boolean_t Btim_IsEnable(BTIM_TypeDef *BTIMx)
{
    return REG_READBITS(BTIMx->CR, BTIM_CR_CEN) ? TRUE : FALSE;	
}
 
/**
 * @brief  设定定时器BTIMx 工作模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32WorkMode: 选择BTIM工作模式  @ref Btim_Work_Mode  
 *
 * @retval None
 */
void Btim_SetWorkMode(BTIM_TypeDef* BTIMx, uint32_t u32WorkMode)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_MD, u32WorkMode);	
}
 
/**
 * @brief  获取定时器BTIMx 工作模式
 *  
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t:BTIM工作模式  @ref Btim_Work_Mode            
 * 
 */
 uint32_t Btim_GetWorkMode(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_MD));	
}



/**
 * @brief  定时器BTIMx TOG输出使能，TOGP和TOGN输出相位相反的信号
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval None
 */
 void Btim_EnableToggle(BTIM_TypeDef *BTIMx)
{
    REG_SETBITS(BTIMx->CR, BTIM_CR_TOGEN);
}

/**
 * @brief  定时器BTIMx TOG输出禁止，TOGP和TOGN同时输出0
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval None
 */
 void Btim_DisableToggle(BTIM_TypeDef *BTIMx)
{
    REG_CLEARBITS(BTIMx->CR, BTIM_CR_TOGEN);	
}

/**
 * @brief  检查定时器BTIMx模块 TOG输出 是否已开启
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval boolean_t:
 *           - FALSE: 未开启
 *           - TRUE: 已开启
 */
 boolean_t Btim_IsEnableToggle(BTIM_TypeDef *BTIMx)
{
    return REG_READBITS(BTIMx->CR, BTIM_CR_TOGEN) ? TRUE : FALSE;	
}


/**
 * @brief  定时器BTIMx模块 计数时钟预除频
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32CounterClkDiv: 计数时钟预分频选择   @ref Btim_Clock_devide
 *
 * @retval None
 */
void Btim_SetCounterClkDiv(BTIM_TypeDef* BTIMx, uint32_t u32CounterClkDiv)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_PRS, u32CounterClkDiv);	
}
 
/**
 * @brief  获取定时器BTIMx 时钟，此时钟是定时器模块工作时钟，非计数时钟源
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 *
 * @retval uint32_t:计数时钟预分频   @ref Btim_Clock_devide  
 */
uint32_t Btim_GetCounterClkDiv(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_PRS));	
}


/**
 * @brief  设定BTIMx 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32Mode: 计数模式  @ref Btim_Count_Task_Mode  
 *
 * @retval None
 */
void Btim_SetOneShotMode(BTIM_TypeDef* BTIMx, uint32_t u32Mode)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_OST, u32Mode);	
}
 
/**
 * @brief  获取BTIMx 计数模式：连续计数模式或单次计数模式
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * 
 * @retval uint32_t: BTIMx 计数模式  @ref Btim_Count_Task_Mode       
 */
uint32_t Btim_GetOneShotMode(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_OST));	
}


 
/**
 * @brief  设定定时器BTIMx 触发源
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32TriggerSource: 选择BTIM触发源  @ref Btim_Trigger_Source_Selection
 *
 * @retval None
 */
void Btim_SetTriggerSource(BTIM_TypeDef* BTIMx, uint32_t u32TriggerSource)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_TRS, u32TriggerSource);	
}
 
/**
 * @brief  获取定时器BTIMx 触发源
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * 
 * @retval uint32_t:BTIM 触发源  @ref Btim_Trigger_Source_Selection   
 */
uint32_t Btim_GetTriggerSource(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_TRS));	
}

 
/**
 * @brief  设定定时器BTIMx 外部输入ETR极性设定
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32ExInputPolarity: 外部输入ETR极性 @ref Btim_ETR_Input_Polarity
 *
 * @retval None
 */       

void Btim_SetExInputPolarity(BTIM_TypeDef* BTIMx, uint32_t u32ExInputPolarity)
{
    REG_MODIFY(BTIMx->CR, BTIM_CR_ETP, u32ExInputPolarity);	
}
 
/**
 * @brief  获取定时器BTIMx 外部输入ETR极性设定
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * 
 * @retval uint32_t:外部输入ETR极性  @ref Btim_ETR_Input_Polarity     
 */
uint32_t Btim_GetExInputPolarity(BTIM_TypeDef* BTIMx)
{
    return (uint32_t)(REG_READBITS(BTIMx->CR, BTIM_CR_ETP));	
}

/**
 * @brief  BTIMx 中断使能
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag  中断使能禁止定义 @ref Btim_Interrupt_Enable_Disable
 *
 * @retval None
 */
void Btim_EnableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_SETBITS(BTIMx->IER, u32IntClrFlag);
}

/**
 * @brief  BTIMx 中断禁止
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag  中断使能禁止定义 @ref Btim_Interrupt_Enable_Disable
 *
 * @retval None
 */
void Btim_DisableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS(BTIMx->IER, u32IntClrFlag);	
}

/**
 * @brief  检查 BTIMx 查询中断 是否已使能
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag  中断使能禁止定义 @ref Btim_Interrupt_Enable_Disable
 *
 * @retval boolean_t:
 *           - FALSE: 未使能
 *           - TRUE: 已使能
 */
boolean_t Btim_IsEnableIT(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    return REG_READBITS(BTIMx->IER, u32IntClrFlag) ? TRUE : FALSE;	
}

/**
 * @brief  获取 BTIMx 中断标志
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntFlag    中断置起标志定义  @ref Btim_Interrupt_Flag
 *
 * @retval boolean_t:
 *           - FALSE: 未置起
 *           - TRUE: 已置起
 */
boolean_t Btim_IsActiveFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntFlag)
{
    return REG_READBITS(BTIMx->IFR, u32IntFlag) ? TRUE : FALSE;	
}


/**
 * @brief  清除 BTIMx 中断 标志位
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag   中断清零标志定义 @ref Btim_Interrupt_Clear_Types
 *
 * @retval None
 */
void Btim_ClearFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS(BTIMx->ICR, u32IntClrFlag);	
}


/**
 * @brief  获取 复合 BTIM 中断标志
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntFlag: BTIM0~BTIM5中断标志 @ref Btim_All_Interrupt_Flags
 *
 * @retval boolean_t:
 *           - FALSE: 未置起
 *           - TRUE: 已置起
 */
boolean_t Btim_AIFR_IsActiveFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntFlag)
{
    return REG_READBITS(BTIMx->AIFR, u32IntFlag) ? TRUE : FALSE;	
}


/**
 * @brief  清除 复合 BTIM 中断标志位
 *
 * @param  [in] BTIMx: BTIM单元名宏定义(HC_BTIM0~HC_BTIM5)
 * @param  [in] u32IntClrFlag: BTIM0~BTIM5中断清零标志 @ref Btim_All_Interrupt_Clear_Reg
 *
 * @retval None
 */
void Btim_AICR_ClearFlag(BTIM_TypeDef* BTIMx, uint32_t u32IntClrFlag)
{
    REG_CLEARBITS(BTIMx->AICR, u32IntClrFlag);	
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
