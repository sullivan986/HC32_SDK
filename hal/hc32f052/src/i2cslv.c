/**
 *******************************************************************************
 * @file  i2cslv.c
 * @brief This file provides firmware functions to manage the I2CSLV.
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

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "i2cslv.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_I2CSLV I2CSLV模块驱动库
 * @brief I2CSLV Driver Library I2CSLV模块驱动库
 * @{
 */

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/

/*******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/

/*******************************************************************************
* Local function prototypes ('static')
******************************************************************************/

/*******************************************************************************
* Local variable definitions ('static')
******************************************************************************/

/*******************************************************************************
* Function implementation - global ('extern') and local ('static')
******************************************************************************/
/**
 * @defgroup I2CSLV_Global_Functions I2CSLV全局函数定义
 * @{
 */

/**
 * @brief  I2CSLV模块主机初始化
 *
 * @param  [in] pstcInitCfg: I2CSLV 初始化结构体
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 *
 */
en_result_t I2CSLV_Init(stc_i2cslv_init_cfg_t *pstcInitCfg)
{   
    ASSERT(NULL != pstcInitCfg);
	
	if (pstcInitCfg->u32TimeOut > 0) /* 需要配置SCL低电平超时 */
    {
		REG_MODIFY(HC_I2CSLV->CR, 
					 I2CSLV_CR_FSCLC
				   | I2CSLV_CR_TIMEOUT
				   | I2CSLV_CR_GC
				   | I2CSLV_CR_DMATE
				   | I2CSLV_CR_DMARE
				   , 
					 pstcInitCfg->u32HSMODE
				   | I2CSLV_CR_TIMEOUT
				   | pstcInitCfg->u32Broadcast
				   | pstcInitCfg->u32DMAReq);
	    
		HC_I2CSLV->TOR = pstcInitCfg->u32TimeOut;  /* 设定SCL低电平超时长度值 */
    }else   /* SCL低电平可以无限时间拉低 */
	{
		REG_MODIFY(HC_I2CSLV->CR, 
					 I2CSLV_CR_FSCLC
				   | I2CSLV_CR_TIMEOUT
				   | I2CSLV_CR_GC
				   | I2CSLV_CR_DMATE
				   | I2CSLV_CR_DMARE
				   , 
					 pstcInitCfg->u32HSMODE
				   | pstcInitCfg->u32Broadcast
				   | pstcInitCfg->u32DMAReq);
	}
	
    /* SDA由0变1时总线驱动能力配置 */
    HC_I2CSLV->ODDR = pstcInitCfg->u32DriveStrength;
	
	/* 接收采样位置配置 */
    HC_I2CSLV->RSR  = pstcInitCfg->u32RxSampleDot;
	
	/* SDA和SCL输入滤波宽度配置 */
    HC_I2CSLV->FLT  = pstcInitCfg->u32Filter;
	
	/* 从机地址0配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr0)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR0 = (0x7F & (pstcInitCfg->u32SlaveAddr0));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR0 = I2CSLV_SLADR0_AM | (0x3FF & (pstcInitCfg->u32SlaveAddr0));
	}
	/* 从机地址0掩码配置 */
	HC_I2CSLV->ADMR0 = pstcInitCfg->u32SlaveAddr0Mask | pstcInitCfg->u32AddrClkForceStretch;
	
	/* 从机地址1配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr1)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR1 = (0x7F & (pstcInitCfg->u32SlaveAddr1));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR1 = I2CSLV_SLADR1_AM | (0x3FF & (pstcInitCfg->u32SlaveAddr1));
	}
	
	/*  从机地址2配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr2)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR2 = (0x7F & (pstcInitCfg->u32SlaveAddr2));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR2 = I2CSLV_SLADR2_ADDRLEN | (0x3FF & (pstcInitCfg->u32SlaveAddr2));
	}
	
	/* 从机地址3配置 */
	if ((0x380 & (pstcInitCfg->u32SlaveAddr3)) == 0)  /* 7位地址 */
	{
		HC_I2CSLV->SLADR3 = (0x7F & (pstcInitCfg->u32SlaveAddr3));
	}else  /* 10位地址 */
	{
		HC_I2CSLV->SLADR3 = I2CSLV_SLADR3_ADDRLEN | (0x3FF & (pstcInitCfg->u32SlaveAddr3));
	}
     
    return Ok;
}


/**
 * @brief  使能 I2CSLV 模块
 *
 * @retval None
 */
void I2CSLV_Enable(void)
{
	REG_SETBITS(HC_I2CSLV->CR, I2CSLV_CR_EN);
}

/**
 * @brief  禁止 I2CSLV 模块
 *
 * @retval None
 */
void I2CSLV_Disable(void)
{
	REG_CLEARBITS(HC_I2CSLV->CR, I2CSLV_CR_EN);	
}

/**
 * @brief  检查I2CSLV 模块 是否已开启
 *
 * @retval uint32_t:
 *               - 0：未开启； 
 *               -非0：已开启
 */
uint32_t I2CSLV_IsEnable(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_EN) == I2CSLV_CR_EN);	
}

/**
 * @brief  I2CSLV 从机响应主机配置
 * @param  [in] u32Ack: 从机响应配置 @ref I2CSLV_ACK_SELECTION
 *              - I2CSLV_ACK    从机响应主机，主机收到ACK
 *              - I2CSLV_NACK   从机不响应主机，主机收到NACK
 *
 * @retval None       
 */
void I2CSLV_SetAck(uint32_t u32Ack)
{
	REG_MODIFY(HC_I2CSLV->CR, I2CSLV_CR_BUSY, u32Ack);
}
 
/**
 * @brief  获取 I2CSLV 从机响应主机配置
 *
 * @retval uint32_t: 从机响应配置 @ref I2CSLV_ACK_SELECTION
 *               - I2CSLV_ACK    从机响应主机，主机收到ACK
 *               - I2CSLV_NACK   从机不响应主机，主机收到NACK
 *       
 */
uint32_t I2CSLV_GetAck(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_BUSY));	
}
 
/**
 * @brief  I2CSLV 配置高速模式下，地址匹配后，如果I2CSLV_DOUTR没有数据，是否强制延迟SCL低电平
 * @param  [in] u32ClkForceStretch: 高速模式控制 @ref I2CSLV_HIGH_SPEED_MODE_SELECTION
 *              - I2CSLV_HIGH_SPEED_MODE_DISABLE  I2CSLV_DOUTR没有数据时强制SCL电平延长
 *              - I2CSLV_HIGH_SPEED_MODE_ENABLE   I2CSLV_DOUTR没有数据时不强制SCL电平延长，回复NACK
 *
 * @retval None
 *        
 */
void I2CSLV_SetHsmodeForceStretch(uint32_t u32ClkForceStretch)
{
	REG_MODIFY(HC_I2CSLV->CR, I2CSLV_CR_FSCLC, u32ClkForceStretch);
}
 
/**
 * @brief  获取 I2CSLV 配置高速模式下，地址匹配后，如果I2CSLV_DOUTR没有数据，是否强制延迟SCL低电平
 *
 * @retval uint32_t: 高速模式控制 @ref I2CSLV_HIGH_SPEED_MODE_SELECTION
 *              - I2CSLV_HIGH_SPEED_MODE_DISABLE  I2CSLV_DOUTR没有数据时强制SCL电平延长
 *              - I2CSLV_HIGH_SPEED_MODE_ENABLE   I2CSLV_DOUTR没有数据时不强制SCL电平延长，回复NACK
 *        
 */
uint32_t I2CSLV_GetHsmodeForceStretch(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_FSCLC));	
}

/**
 * @brief  使能 I2CSLV 广播地址
 *
 * @retval None
 */
void I2CSLV_EnableBroadcast(void)
{
	REG_SETBITS(HC_I2CSLV->CR, I2CSLV_CR_GC);
}

/**
 * @brief  禁止 I2CSLV 广播地址
 *
 * @retval None
 */
void I2CSLV_DisableBroadcast(void)
{
	REG_CLEARBITS(HC_I2CSLV->CR, I2CSLV_CR_GC);	
}

/**
 * @brief  检查I2CSLV 广播地址 是否已开启
 *
 * @retval uint32_t:  
 *         - 0: 未开启
 *         - 非0: 已开启
 */
uint32_t I2CSLV_IsEnableBroadcast(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, I2CSLV_CR_GC) == I2CSLV_CR_GC);	
}

/**
 * @brief  I2CSLV 从机DMA请求配置
 * @param  [in] u32DmaReq: 从机DMA请求配置 @ref I2CSLV_DMA_REQUEST_SELECTION
 *              - I2CSLV_DMA_REQUEST_RX_TX_DISABLE 从机TX RX DMA请求禁止
 *              - I2CSLV_DMA_REQUEST_RX_ENABLE     从机RX DMA请求使能
 *              - I2CSLV_DMA_REQUEST_TX_ENABLE     从机TX DMA请求使能
 *              - I2CSLV_DMA_REQUEST_RX_TX_ENABLE  从机TX RX DMA请求使能

 * @retval None
 *      
 */
void I2CSLV_SetDMAReq(uint32_t u32DmaReq)
{
	REG_MODIFY(HC_I2CSLV->CR, (I2CSLV_CR_DMARE | I2CSLV_CR_DMATE), u32DmaReq);
}
 
/**
 * @brief  获取 I2CSLV 从机DMA请求配置
 *
 * @retval uint32_t:从机DMA请求配置 @ref I2CSLV_DMA_REQUEST_SELECTION
 *         - I2CSLV_DMA_REQUEST_RX_TX_DISABLE 从机TX RX DMA请求禁止
 *         - I2CSLV_DMA_REQUEST_RX_ENABLE     从机RX DMA请求使能
 *         - I2CSLV_DMA_REQUEST_TX_ENABLE     从机TX DMA请求使能
 *         - I2CSLV_DMA_REQUEST_RX_TX_ENABLE  从机TX RX DMA请求使能
 *         
 */
uint32_t I2CSLV_GetDMAReq(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->CR, (I2CSLV_CR_DMARE | I2CSLV_CR_DMATE)));	
}

/**
 * @brief  使能 I2CSLV模块 某一个特定的中断
 * @param  [in] u32IrqCfg: 中断配置 @ref I2CSLV_IT_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_IT_RD
 *         - I2CSLV_IT_WR
 *         - I2CSLV_IT_STOP
 *         - I2CSLV_IT_START
 *         - I2CSLV_IT_NACK
 *         - I2CSLV_IT_I2CINT
 *         - I2CSLV_IT_ACTIVE
 *         - I2CSLV_IT_HSMODE
 *         - I2CSLV_IT_TIMEOUT
 *         - I2CSLV_IT_ACK
 *         - I2CSLV_IT_SLADDR0
 *         - I2CSLV_IT_SLADDR1
 *         - I2CSLV_IT_SLADDR2
 *         - I2CSLV_IT_SLADDR3
 *         - I2CSLV_IT_TXE
 *         - I2CSLV_IT_RXNE
 *         - I2CSLV_IT_GC
 *
 * @retval None
 */
void I2CSLV_EnableIT(uint32_t u32IrqCfg)
{
	REG_SETBITS(HC_I2CSLV->IER, u32IrqCfg);
}

/**
 * @brief  禁止 I2CSLV模块 某一个特定的中断
 * @param  [in] u32IrqCfg: 中断配置 @ref I2CSLV_IT_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_IT_RD
 *         - I2CSLV_IT_WR
 *         - I2CSLV_IT_STOP
 *         - I2CSLV_IT_START
 *         - I2CSLV_IT_NACK
 *         - I2CSLV_IT_I2CINT
 *         - I2CSLV_IT_ACTIVE
 *         - I2CSLV_IT_HSMODE
 *         - I2CSLV_IT_TIMEOUT
 *         - I2CSLV_IT_ACK
 *         - I2CSLV_IT_SLADDR0
 *         - I2CSLV_IT_SLADDR1
 *         - I2CSLV_IT_SLADDR2
 *         - I2CSLV_IT_SLADDR3
 *         - I2CSLV_IT_TXE
 *         - I2CSLV_IT_RXNE
 *         - I2CSLV_IT_GC
 *
 * @retval None
 */
void I2CSLV_DisableIT(uint32_t u32IrqCfg)
{
	REG_CLEARBITS(HC_I2CSLV->IER, u32IrqCfg);	
}

/**
 * @brief  检查I2CSLVx模块 某一个特定的中断 是否已开启
 * @param  [in] u32IrqCfg: 中断配置 @ref I2CSLV_IT_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_IT_RD
 *         - I2CSLV_IT_WR
 *         - I2CSLV_IT_STOP
 *         - I2CSLV_IT_START
 *         - I2CSLV_IT_NACK
 *         - I2CSLV_IT_I2CINT
 *         - I2CSLV_IT_ACTIVE
 *         - I2CSLV_IT_HSMODE
 *         - I2CSLV_IT_TIMEOUT
 *         - I2CSLV_IT_ACK
 *         - I2CSLV_IT_SLADDR0
 *         - I2CSLV_IT_SLADDR1
 *         - I2CSLV_IT_SLADDR2
 *         - I2CSLV_IT_SLADDR3
 *         - I2CSLV_IT_TXE
 *         - I2CSLV_IT_RXNE
 *         - I2CSLV_IT_GC
 *
 * @retval uint32_t:
 *         - 0：未开启;
 *         - 非0：已开启
 */
uint32_t I2CSLV_IsEnableIT(uint32_t u32IrqCfg)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->IER, u32IrqCfg) == u32IrqCfg);	
}

/**
 * @brief  获取 I2CSLVx 中断标志
 * @param  [in] u32IrqFlag: 中断标记 @ref I2CSLV_FLAG_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_FLAG_RD
 *         - I2CSLV_FLAG_WR
 *         - I2CSLV_FLAG_STOP
 *         - I2CSLV_FLAG_START
 *         - I2CSLV_FLAG_NACK
 *         - I2CSLV_FLAG_I2CINT
 *         - I2CSLV_FLAG_ACTIVE
 *         - I2CSLV_FLAG_HSMODE
 *         - I2CSLV_FLAG_TIMEOUT
 *         - I2CSLV_FLAG_ACK
 *         - I2CSLV_FLAG_SLADDR0
 *         - I2CSLV_FLAG_SLADDR1
 *         - I2CSLV_FLAG_SLADDR2
 *         - I2CSLV_FLAG_SLADDR3
 *         - I2CSLV_FLAG_TXE
 *         - I2CSLV_FLAG_RXNE
 *         - I2CSLV_FLAG_GC
 *
 * @retval uint32_t: 
 *         - 0: 未检测到所查询的中断标志
 *         - 1: 已检测到所查询的中断标志
 */
uint32_t I2CSLV_IsActiveFlag(uint32_t u32IrqFlag)
{
	return (REG_READBITS(HC_I2CSLV->SR, u32IrqFlag) == u32IrqFlag);	
}
 
/**
 * @brief  获取 I2CSLV 状态寄存器
 *
 * @retval uint32_t: I2CSLV所有状态标志位       
 */
uint32_t I2CSLV_GetState(void)
{
	return (uint32_t)(0xFFFF & (HC_I2CSLV->SR));	
}

/**
 * @brief  清除 I2CSLVx 逻辑单元 中断标志
 * @param  [in] u32IrqFlag: 中断标记 @ref I2CSLV_FLAG_SELECTION
 *         - 下列值或下列值相或的组合
 *         - I2CSLV_FLAG_RD
 *         - I2CSLV_FLAG_WR
 *         - I2CSLV_FLAG_STOP
 *         - I2CSLV_FLAG_START
 *         - I2CSLV_FLAG_NACK
 *         - I2CSLV_FLAG_I2CINT
 *         - I2CSLV_FLAG_ACTIVE
 *         - I2CSLV_FLAG_HSMODE
 *         - I2CSLV_FLAG_TIMEOUT
 *         - I2CSLV_FLAG_ACK
 *         - I2CSLV_FLAG_SLADDR0
 *         - I2CSLV_FLAG_SLADDR1
 *         - I2CSLV_FLAG_SLADDR2
 *         - I2CSLV_FLAG_SLADDR3
 *         - I2CSLV_FLAG_TXE
 *         - I2CSLV_FLAG_RXNE
 *         - I2CSLV_FLAG_GC
 *         
 * @retval None
 */
void I2CSLV_ClearFlag(uint32_t u32IrqFlag)
{
	REG_CLEARBITS(HC_I2CSLV->ICR, u32IrqFlag);	
}

/**
 * @brief  清除 I2CSLVx 所有 中断标志
 *
 * @retval None
 */
void I2CSLV_ClearFlag_ALL(void)
{
	HC_I2CSLV->ICR = I2CSLV_SR_TXE;	/* ICR.TXE不能写零，否则TXE标记会置一 */
}

/**
 * @brief  设置 I2CSLVx TXE标记为1
 *
 * @retval None
 */
void I2CSLV_SetFlag_TXE(void)
{
	REG_CLEARBITS(HC_I2CSLV->ICR, I2CSLV_SR_TXE);
}
 
 /**
 * @brief  设置 I2CSLV device ID
 * @param  [in] u32RID: 修订标识
 * @param  [in] u32PID: 零件标识
 * @param  [in] u32MID: 制造商标识
 *
 * @retval None       
 */
void I2CSLV_SetDeviceID(uint32_t u32RID, uint32_t u32PID, uint32_t u32MID)
{
	HC_I2CSLV->DIDR = ((u32MID<<12) | (u32PID<<3) | u32RID);
}
 
/**
 * @brief  获取 I2CSLV device ID
 *
 * @retval uint32_t:device ID: bit[2:0]RID, bit[11:3]PID, bit[23:12]RID
 *         
 */
uint32_t I2CSLV_GetDeviceID(void)
{
	return (uint32_t)((HC_I2CSLV->DIDR)&0xFFFFFF);	
}
 
/**
 * @brief  设置 I2CSLV 接收采样位置
 * @param  [in] u32SampleDot: 接收采样位置 @ref I2CSLV_RX_SAMPLE_DOT_SELECTION
 *              - I2CSLV_RX_SAMPLE_DOT_0CYCLE   SCL下降沿时采样
 *              - I2CSLV_RX_SAMPLE_DOT_1CYCLE   从SCL下降沿往回计时，第1个PCLK采样
 *              - I2CSLV_RX_SAMPLE_DOT_2CYCLE   从SCL下降沿往回计时，第2个PCLK采样
 *              - I2CSLV_RX_SAMPLE_DOT_3CYCLE   从SCL下降沿往回计时，第3个PCLK采样
 *
 * @retval None        
 */
void I2CSLV_SetRxSampleDot(uint32_t u32SampleDot)
{
	REG_MODIFY(HC_I2CSLV->RSR, I2CSLV_RSR_NS, u32SampleDot);
}
 
/**
 * @brief  获取 I2CSLV 接收采样位置
 *
 * @retval uint32_t: 接收采样位置 @ref I2CSLV_RX_SAMPLE_DOT_SELECTION
 *         - I2CSLV_RX_SAMPLE_DOT_0CYCLE   SCL下降沿时采样
 *         - I2CSLV_RX_SAMPLE_DOT_1CYCLE   从SCL下降沿往回计时，第1个PCLK采样
 *         - I2CSLV_RX_SAMPLE_DOT_2CYCLE   从SCL下降沿往回计时，第2个PCLK采样
 *         - I2CSLV_RX_SAMPLE_DOT_3CYCLE   从SCL下降沿往回计时，第3个PCLK采样
 *         
 */
uint32_t I2CSLV_GetRxSampleDot(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->RSR, I2CSLV_RSR_NS));	
}
 
/**
 * @brief  I2CSLV SDA由0变1时总线驱动能力配置
 * @param  [in] u32HighDrive: 驱动能力配置 @ref I2CSLV_HIGH_DRIVE_SELECTION
 *              - I2CSLV_HIGH_DRIVE_NONE    由外部上拉电阻拉高，无强驱
 *              - I2CSLV_HIGH_DRIVE_1PCLK   输出1个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *              - I2CSLV_HIGH_DRIVE_2PCLK   输出2个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *              - I2CSLV_HIGH_DRIVE_4PCLK   输出4个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *
 * @retval None    
 */
void I2CSLV_SetDriveStrength(uint32_t u32HighDrive)
{
	REG_MODIFY(HC_I2CSLV->ODDR, I2CSLV_ODDR_ODPU, u32HighDrive);
}
 
/**
 * @brief  获取 I2CSLV SDA由0变1时总线驱动能力配置
 *
 * @retval uint32_t: 驱动能力配置 @ref I2CSLV_HIGH_DRIVE_SELECTION
 *         - I2CSLV_HIGH_DRIVE_NONE    由外部上拉电阻拉高，无强驱
 *         - I2CSLV_HIGH_DRIVE_1PCLK   输出1个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *         - I2CSLV_HIGH_DRIVE_2PCLK   输出2个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *         - I2CSLV_HIGH_DRIVE_4PCLK   输出4个PCLK宽度的强驱高电平，后续由上拉电阻维持
 *         
 */
uint32_t I2CSLV_GetDriveStrength(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->ODDR, I2CSLV_ODDR_ODPU));	
}
 
/**
 * @brief  I2CSLV SCL低电平超时配置，只有CR.EN=0时可配置
 * @param  [in] u32TimeOver: 超时长度设置，超时时间=(u32TimeOver+1)*64*(1/pclk)
 *
 * @retval None       
 */
void I2CSLV_SetTimeOut(uint32_t u32TimeOver)
{
	if (u32TimeOver == 0) /*  关闭超时功能 */
	{
		REG_CLEARBITS(HC_I2CSLV->CR, I2CSLV_CR_TIMEOUT);         /*   禁止SCL低电平超时功能 */
	}else
	{
		REG_SETBITS(HC_I2CSLV->CR, I2CSLV_CR_TIMEOUT);           /*  使能SCL低电平超时功能 */
	    REG_MODIFY(HC_I2CSLV->TOR, I2CSLV_TOR_TOR, u32TimeOver); /*  配置超时时长 */
	}
}
 
/**
 * @brief  获取 I2CSLV SCL低电平超时配置
 *
 * @retval uint32_t: 超时长度,长度与时间关系：时间=(TOR+1)*64*(1/pclk)
 *         
 */
uint32_t I2CSLV_GetTimeOut(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->TOR, I2CSLV_TOR_TOR));	
}
 
/**
 * @brief  I2CSLV SDA和SCL输入滤波宽度设置
 * @param  [in] u32Filter: 滤波宽度 @ref I2CSLV_FILTER_SELECTION
 *              - I2CSLV_FILTER_NONE    无滤波
 *              - I2CSLV_FILTER_1PCLK   1个PCLK宽度的滤波
 *              - I2CSLV_FILTER_2PCLK   2个PCLK宽度的滤波
 *              - I2CSLV_FILTER_3PCLK   3个PCLK宽度的滤波
 *              - I2CSLV_FILTER_4PCLK   4个PCLK宽度的滤波
 *              - I2CSLV_FILTER_8PCLK   8个PCLK宽度的滤波
 *              - I2CSLV_FILTER_12PCLK  12个PCLK宽度的滤波
 *              - I2CSLV_FILTER_16PCLK  16个PCLK宽度的滤波
 * @retval None        
 */
void I2CSLV_SetFilter(uint32_t u32Filter)
{
	REG_MODIFY(HC_I2CSLV->FLT, I2CSLV_FLT_FW, u32Filter);
}
 
/**
 * @brief  获取 I2CSLV SDA和SCL输入滤波宽度
 * @retval uint32_t: 滤波宽度 @ref I2CSLV_FILTER_SELECTION
 *         - I2CSLV_FILTER_NONE    无滤波
 *         - I2CSLV_FILTER_1PCLK   1个PCLK宽度的滤波
 *         - I2CSLV_FILTER_2PCLK   2个PCLK宽度的滤波
 *         - I2CSLV_FILTER_3PCLK   3个PCLK宽度的滤波
 *         - I2CSLV_FILTER_4PCLK   4个PCLK宽度的滤波
 *         - I2CSLV_FILTER_8PCLK   8个PCLK宽度的滤波
 *         - I2CSLV_FILTER_12PCLK  12个PCLK宽度的滤波
 *         - I2CSLV_FILTER_16PCLK  16个PCLK宽度的滤波
 *         
 */
uint32_t I2CSLV_GetFilter(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->FLT, I2CSLV_FLT_FW));	
}
 
/**
 * @brief  I2CSLV 从机地址设置
 * @param  [in] u32AddrNum: 从机地址号 @ref I2CSLV_ADDR_SELECTION
 *         - I2CSLV_ADDR0   从机地址0
 *         - I2CSLV_ADDR1   从机地址1
 *         - I2CSLV_ADDR2   从机地址2
 *         - I2CSLV_ADDR3   从机地址3
 * @param  [in] u32AddrLength: 地址长度
 *         - I2CSLV_ADDR_LENGTH_7BIT    7位地址长度
 *         - I2CSLV_ADDR_LENGTH_10BIT   10位地址长度
 * @param  [in] u32Addr: 从机地址0
 *
 * @retval None        
 */
void I2CSLV_SetAddress(uint32_t u32AddrNum, uint32_t u32AddrLength, uint32_t u32Addr)
{
	REG_MODIFY(*(&HC_I2CSLV->SLADR0 + u32AddrNum), (I2CSLV_SLADR0_AM | I2CSLV_SLADR0_ADDR), (u32AddrLength | (0x3FF&u32Addr)));
}
 
/**
 * @brief  获取 I2CSLV 从机地址
 * @param  [in] u32AddrNum: 从机地址号 @ref I2CSLV_ADDR_SELECTION
 *         - I2CSLV_ADDR0   从机地址0
 *         - I2CSLV_ADDR1   从机地址1
 *         - I2CSLV_ADDR2   从机地址2
 *         - I2CSLV_ADDR3   从机地址3
 *
 * @retval uint32_t: 从机地址        
 */
uint32_t I2CSLV_GetAddress(uint32_t u32AddrNum)
{
	if ((*(&HC_I2CSLV->SLADR0 + u32AddrNum) & I2CSLV_SLADR0_AM) != 0)  /*  10位地址长度 */
	{
		return (uint32_t)(0x3FF & (REG_READBITS(*(&HC_I2CSLV->SLADR0 + u32AddrNum), I2CSLV_SLADR0_ADDR)));
	}else
	{
		return (uint32_t)(0x7F & (REG_READBITS(*(&HC_I2CSLV->SLADR0 + u32AddrNum), I2CSLV_SLADR0_ADDR)));
	}		
}
 
/**
 * @brief  获取 I2CSLV 从机地址0长度
 * @param  [in] u32AddrNum: 从机地址号 @ref I2CSLV_ADDR_SELECTION
 *         - I2CSLV_ADDR0   从机地址0
 *         - I2CSLV_ADDR1   从机地址1
 *         - I2CSLV_ADDR2   从机地址2
 *         - I2CSLV_ADDR3   从机地址3
 *
 * @retval uint32_t: 从机地址长度      
 */
uint32_t I2CSLV_GetAddressLength(uint32_t u32AddrNum)
{
	return (uint32_t)(0x3FF & (REG_READBITS(*(&HC_I2CSLV->SLADR0 + u32AddrNum), I2CSLV_SLADR0_AM)));		
}
 
/**
 * @brief  I2CSLV 从机地址0屏蔽码设置
 * @param  [in] u32Address0Mask: 从机地址0屏蔽码 10bit有效位
 *
 * @retval None       
 */
void I2CSLV_SetAddress0Mask(uint32_t u32Address0Mask)
{
	REG_MODIFY(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_ADDRMASK, u32Address0Mask);
}
 
/**
 * @brief  获取 I2CSLV 从机地址0屏蔽码
 *
 * @retval uint32_t: 从机地址0屏蔽码
 *         
 */
uint32_t I2CSLV_GetAddress0Mask(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_ADDRMASK));	
}
 
/**
 * @brief  获取 I2CSLV 已接收地址
 *
 * @retval uint32_t: 已接收地址       
 */
uint32_t I2CSLV_GetReceivedAddr(void)
{
	if ((HC_I2CSLV->ADIR & I2CSLV_ADIR_ADRLEN) != 0)  /*  10位地址长度 */
	{
		return (uint32_t)(0x3FF & (REG_READBITS(HC_I2CSLV->ADIR, I2CSLV_ADIR_ADIR)));
	}else                                           /*  7位地址长度 */
	{
		return (uint32_t)(0x7F & (REG_READBITS(HC_I2CSLV->ADIR, I2CSLV_ADIR_ADIR)));
	}		
}
 
/**
 * @brief  获取 I2CSLV 已接收地址长度
 *
 * @retval uint32_t:已接收地址长度        
 */
uint32_t I2CSLV_GetReceivedAddrLength(void)
{
	return (uint32_t)(0x3FF & (REG_READBITS(HC_I2CSLV->ADIR, I2CSLV_ADIR_ADRLEN)));		
}
 
/**
 * @brief  I2CSLV 地址时钟强制延长，在地址匹配并回复ACK后，控制时钟是否强制延长。如果使能，
 *         在回复地址字节的ACK后时钟拉低延长（并且SR.I2CINT置位），等到手动清零SR.I2CINT才释放。
 * @param  [in] u32ClkForceStretch: 配置是否时钟延长 @ref I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION
 *              - I2CSLV_ADDR_CLOCK_FORCE_STRETCH_DISABLE  地址匹配后时钟不强制SCL电平延长
 *              - I2CSLV_ADDR_CLOCK_FORCE_STRETCH_ENABLE   地址匹配后时钟强制SCL电平延长
 *
 * @retval None       
 */
void I2CSLV_SetAddrClockForceStretch(uint32_t u32ClkForceStretch)
{
	REG_MODIFY(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_FACS, u32ClkForceStretch);
}
 
/**
 * @brief  获取 I2CSLV 收到地址数据后 是否具备对SCL时钟有强制延长功能
 *
 * @retval uint32_t:是否时钟延长 @ref I2CSLV_ADDR_CLOCK_FORCE_STRETCH_SELECTION
 *         - I2CSLV_CLOCK_FORCE_STRETCH_DISABLE  地址时钟不强制SCL电平延长
 *         - I2CSLV_CLOCK_FORCE_STRETCH_ENABLE   地址时钟强制SCL电平延长
 *         
 */
uint32_t I2CSLV_GetAddrClockForceStretch(void)
{
	return (uint32_t)(REG_READBITS(HC_I2CSLV->ADMR0, I2CSLV_ADMR0_FACS));	
}
 
/**
 * @brief  设置 I2CSLV 数据寄存器，写入待发送的数据
 * @param  [in] u8Data: 8bit数据值
 *
 * @retval None
 *         
 */
void I2CSLV_WriteByte(uint8_t u8Data)
{
	REG_MODIFY(HC_I2CSLV->DOUTR, I2CSLV_DOUTR_DOUT, u8Data);
}
 
/**
 * @brief  获取 I2CSLV 数据寄存器，读出接收到的数据
 *
 * @retval uint8_t:I2CSLV 8bit数据值        
 */
uint8_t I2CSLV_ReadByte(void)
{
	return (uint8_t)(REG_READBITS(HC_I2CSLV->DINR, I2CSLV_DINR_DIN));	
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
