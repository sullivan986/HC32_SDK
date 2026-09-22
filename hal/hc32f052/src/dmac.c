/**
 *******************************************************************************
 * @file  dmac.c
 * @brief This file provides firmware functions to manage the DMAC.
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

/*******************************************************************************
* Include files
******************************************************************************/
#include "dmac.h"

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DMAC DMAC模块驱动库
 * @brief DMAC Driver Library DMAC模块驱动库
 * @{
 */

/*******************************************************************************
* Local type definitions ('typedef')
******************************************************************************/

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/
/**
 * @defgroup DMAC_Local_Macros DMAC局部宏定义
 * @{
 */

/**
 * @defgroup DMAC_PARA_CHECK 参数合法性检查
 * @{
 */
/**
 * @brief  DMA 通道参数有效性检查 @ref en_dma_channel_t
 */
#define IS_VALID_CH(x)                 \
(   (DmaCh0 == (x))                 || \
    (DmaCh1 == (x))                 || \
    (DmaCh2 == (x))                 || \
    (DmaCh3 == (x))                 || \
    (DmaCh4 == (x)))

/**
 * @brief  DMA 传输数据宽度，参数有效性检查 @ref en_dma_transfer_width_t
 */
#define IS_VALID_TRN_WIDTH(x)                  \
(   (DmaMsk8Bit == (x))                     || \
    (DmaMsk16Bit == (x))                    || \
    (DmaMsk32Bit == (x)))

/**
 * @brief  DMA源地址控制模式，参数有效性检查 @ref en_src_address_mode_t
 */
#define IS_VALID_SRC_ADDR_MODE(x)              \
(   (DmaMskSrcAddrFix == (x))               || \
    (DmaMskSrcAddrInc == (x)))

/**
 * @brief  DMA目的地址控制模式，参数有效性检查 @ref en_dst_address_mode_t
 */
#define IS_VALID_DST_ADDR_MODE(x)              \
(   (DmaMskDstAddrFix == (x))               || \
    (DmaMskDstAddrInc == (x)))

/**
 * @brief  DMA 优先级, 参数有效性检查 @ref en_dma_priority_t
 */
#define IS_VALID_PRIO_MODE(x)                  \
(   (DmaMskPriorityFix == (x))              || \
    (DmaMskPriorityLoop == (x)))

/**
 * @brief  DMA 传输模式，参数有效性检查 @ref en_dma_msk_t
 */
#define IS_VALID_TRANSFER_MODE(x)              \
(   (DmaMskOneTransfer == (x))              || \
    (DmaMskContinuousTransfer == (x)))

/**
 * @brief  DMA 块传输大小，参数有效性检查
 */
#define IS_VALID_BLKSIZE(x)                 ((!((x) & ~(DMAC_CONFA0_BC_Msk >> DMAC_CONFA0_BC_Pos)))&&((x)>0))

/**
 * @brief  DMA 块传输次数，参数有效性检查
 */
#define IS_VALID_TRNCNT(x)                  (!((x) & ~(DMAC_CONFA0_TC_Msk >> DMAC_CONFA0_TC_Pos)))


/**
 * @}
 */

/**
 * @}
 */
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
 * @defgroup DMAC_Global_Functions DMAC全局函数定义
 * @{
 */

/**
 * @brief  初始化DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] pstcCfg: DMA通道初始化配置结构体指针 @ref stc_dma_cfg_t
 * @retval en_result_t:
 *           - Ok: 初始化成功
 *           - ErrorInvalidParameter: pstcCfg是空指针
 */
en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg)
{
    volatile uint32_t u32reg;

    ASSERT(IS_VALID_CH(enCh));/* 检查通道值有效性 */
    ASSERT(NULL != pstcCfg);
    ASSERT(IS_VALID_BLKSIZE(pstcCfg->u16BlockSize));
    ASSERT(IS_VALID_TRNCNT(pstcCfg->u16TransferCnt));
    ASSERT(IS_VALID_TRN_WIDTH(pstcCfg->enTransferWidth));
    ASSERT(IS_VALID_SRC_ADDR_MODE(pstcCfg->enSrcAddrMode));
    ASSERT(IS_VALID_DST_ADDR_MODE(pstcCfg->enDstAddrMode));
    ASSERT(IS_VALID_PRIO_MODE(pstcCfg->enPriority));
    ASSERT(IS_VALID_TRANSFER_MODE(pstcCfg->enTransferMode));
      
    /* 检查通道值有效性和pstcCfg是否空指针 */
    if (NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }
  
    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = 0U;
    *((uint32_t*)u32reg) = (uint32_t)pstcCfg->enMode             |
                                  (uint32_t)pstcCfg->enTransferWidth    |
                                  (uint32_t)pstcCfg->enSrcAddrMode      |
                                  (uint32_t)pstcCfg->enDstAddrMode      |
                                  (uint32_t)pstcCfg->enSrcAddrReloadCtl |
                                  (uint32_t)pstcCfg->enDestAddrReloadCtl|
                                  (uint32_t)pstcCfg->enSrcBcTcReloadCtl |
                                  (uint32_t)pstcCfg->enTransferMode;

    /* 首先把TRI_SEL[6:0]     BC[3:0] TC[15:0]这些位清零，然后再赋值 */
    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= ((uint32_t)~(DMAC_CONFA0_TRISEL_Msk | DMAC_CONFA0_BC_Msk \
                                                | DMAC_CONFA0_TC_Msk));
    *((uint32_t*)u32reg)    |= ((uint32_t)pstcCfg->u16TransferCnt - 1U)    | \
                                   (((uint32_t)pstcCfg->u16BlockSize - 1U) << DMAC_CONFA0_BC_Pos)| \
                                   ((uint32_t)pstcCfg->enRequestNum << DMAC_CONFA0_TRISEL_Pos);        

    HC_DMAC->CONF |= (uint32_t)(pstcCfg->enPriority);                           
    
    u32reg = (uint32_t)&HC_DMAC->SRCADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = (uint32_t)(pstcCfg->u32SrcAddress);
    u32reg = (uint32_t)&HC_DMAC->DSTADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = (uint32_t)(pstcCfg->u32DstAddress);
    
  return Ok;
}

/**
 * @brief  DMA模块使能函数，使能所有通道的操作，每个通道按照各自设置工作
 * @retval None
 */
void Dma_Enable(void)
{
    HC_DMAC->CONF |= DMAC_CONF_EN_Msk;
}

/**
 * @brief  DMA模块功能禁止函数，所有通道禁止工作
 * @retval None
 */
void Dma_Disable(void)
{
    HC_DMAC->CONF &= (~DMAC_CONF_EN_Msk);
}

/**
 * @brief  触发指定DMA通道软件传输功能
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_SwStart(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFA0_ST_Msk;
}

/**
 * @brief  停止指定DMA通道软件传输功能
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_SwStop(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFA0_ST_Msk);
}

/**
 * @brief  使能指定DMA通道的（传输完成）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableChannelIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFB0_FISIE_Msk; 
}

/**
 * @brief  禁用指定DMA通道的（传输完成）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableChannelIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_FISIE_Msk);
}

/**
 * @brief  使能指定DMA通道的（传输错误）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableChannelErrIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFB0_ERRIE_Msk;
}

/**
 * @brief  禁用指定DMA通道的（传输错误）中断
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableChannelErrIrq(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_ERRIE_Msk);
}

/**
 * @brief  使能指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableChannel(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) |= DMAC_CONFA0_ENS_Msk;
}

/**
 * @brief  禁用指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableChannel(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) &= (~DMAC_CONFA0_ENS_Msk);
}

/**
 * @brief  设定指定通道的块(Block)尺寸
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u16BlkSize: 块(Block)尺寸
 * @retval None
 */
void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize)
{
    volatile uint32_t u32reg;
    uint32_t u32val;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;  
    u32val = *((uint32_t*)u32reg) & ((uint32_t)~DMAC_CONFA0_BC_Msk);
    *((uint32_t*)u32reg) = u32val | ((((uint32_t)u16BlkSize-1U)&0x0fU)<<DMAC_CONFA0_BC_Pos);
}

/**
 * @brief  设定指定通道块(Block)传输次数
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u16TrnCnt: 块(Block)传输次数
 * @retval None
 */
void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt)
{
    volatile uint32_t u32reg;
    uint32_t u32val;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh;   
    u32val = *((uint32_t*)u32reg) & ((uint32_t)~DMAC_CONFA0_TC_Msk);   
    *((uint32_t*)u32reg) = u32val | ((((uint32_t)u16TrnCnt-1U)<<DMAC_CONFA0_TC_Pos));
}

/**
 * @brief  允许指定通道可连续传输，即DMA在传输完成时不清除CONFA:ENS位
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_EnableContinusTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh; 
    *((uint32_t*)u32reg) |= DMAC_CONFB0_MSK;
}

/**
 * @brief  禁止指定通道连续传输，即DMA在传输完成时清除CONFA:ENS位
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_DisableContinusTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh; 
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_MSK);
}

/**
 * @brief  暂停所有DMA通道
 * @retval None
 */
void Dma_HaltTranfer(void)
{
    HC_DMAC->CONF_f.HALT = 0x1U;
}

/**
 * @brief  恢复（之前暂停的）所有DMA通道
 * @retval None
 */
void Dma_RecoverTranfer(void)
{
    HC_DMAC->CONF_f.HALT = 0x0U;
}

/**
 * @brief  暂停指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_PauseChannelTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh; 
    *((uint32_t*)u32reg) |= DMAC_CONFA0_PAS_Msk;
}

/**
 * @brief  恢复指定DMA通道
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFA0 + (uint32_t)enCh; 
    *((uint32_t*)u32reg) &= (~DMAC_CONFA0_PAS_Msk);
}

/**
 * @brief  设定指定通道传输数据宽度
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] enWidth: 指定数据宽度 @ref en_dma_transfer_width_t
 * @retval None
 */
void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth)
{
    volatile uint32_t u32reg;
    uint32_t u32val;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;   
    u32val =  *((uint32_t*)u32reg) & ((uint32_t)~DMAC_CONFB0_WIDTH_Msk);
    *((uint32_t*)u32reg) = u32val | ((uint32_t)enWidth);
}

/**
 * @brief  设定DMA通道优先级
 * @param  [in] enPrio: 通道优先级设定参数 @ref en_dma_priority_t
 * @retval None
 */
void Dma_SetChPriority(en_dma_priority_t enPrio)
{
    HC_DMAC->CONF = ((HC_DMAC->CONF)&((uint32_t)~DMAC_CONF_PRIO_Msk))|((uint32_t)enPrio);
}

/**
 * @brief  获取指定DMA通道的状态
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval en_dma_stat_t @ref en_dma_stat_t
 */
en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;  
    return (en_dma_stat_t)((*((uint32_t*)u32reg)&(DMAC_CONFB0_STAT_Msk))>>DMAC_CONFB0_STAT_Pos);
}

/**
 * @brief  清除指定DMA通道的状态值
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @retval None
 */
void Dma_ClrStat(en_dma_channel_t enCh)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->CONFB0 + (uint32_t)enCh;  
    *((uint32_t*)u32reg) &= (~DMAC_CONFB0_STAT_Msk);
}

/**
 * @brief  设定指定通道源地址
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u32Address: 传输源地址
 * @retval None
 */
void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->SRCADR0 + (uint32_t)enCh;  
    *((uint32_t*)u32reg) = u32Address;
}

/**
 * @brief  设定指定通道目标地址
 * @param  [in] enCh: 指定DMA通道 @ref en_dma_channel_t
 * @param  [in] u32Address: 传输源地址
 * @retval None
 */
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
    volatile uint32_t u32reg;

    u32reg = (uint32_t)&HC_DMAC->DSTADR0 + (uint32_t)enCh;
    *((uint32_t*)u32reg) = u32Address;
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
