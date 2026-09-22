/**
 *******************************************************************************
 * @file  can.c
 * @brief This file provides firmware functions to manage the CAN.
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
#include "can.h"


/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CAN CAN模块驱动库
 * @brief CAN Driver Library CAN模块驱动库
 * @{
 */


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CAN_Local_Macros CAN局部宏定义
 * @{
 */
/**
 * @defgroup CAN_Reset_definition CAN复位请求
 * @{
 */
#define CAN_RESET_ENABLE()                  do{HC_CAN->CFG_STAT_f.RESET = 1U;}while(0U)/*!< 请求局部复位 */
#define CAN_RESET_DISABLE()                 do{HC_CAN->CFG_STAT_f.RESET = 0U;\
                                            while(HC_CAN->CFG_STAT_f.RESET){}\
                                            }while(0U)/*!< 不请求局部复位 */
/**
 * @}
 */
/**
 * @defgroup ACF_SELMASK_definition 选择筛选器的屏蔽寄存器
 * @{
 */
#define CAN_ACF_ID_REG_SEL                  ((uint8_t)0x00U)/*!< ACF指向筛选器ID寄存器 */
#define CAN_ACF_MASK_REG_SEL                ((uint8_t)0x01U)/*!< ACF指向筛选器MASK寄存器 */
/**
 * @}
 */
/**
 * @defgroup CAN_FLAG_CLEAR_MASK CAN标志位清除屏蔽值
 * @{
 */
#define CAN_IE_CLEAR_MASK                   ((uint32_t)0xFF2A00FFU)/*!< CAN中断标志清除屏蔽值 */
/**
 * @}
 */

/**
 * @defgroup CAN_PARA_CHECK 参数合法性检查
 * @{
 */

/**
 * @brief Parameter validity check for CAN Mode @ref en_can_mode_t
 */
#define IS_CAN_MODE_VALID(CanMode)                                             \
(       (CanExternalLoopBackMode  == (CanMode)) ||                               \
        (CanInternalLoopBackMode  == (CanMode)) ||                               \
        (CanTxSignalPrimaryMode   == (CanMode)) ||                               \
        (CanTxSignalSecondaryMode == (CanMode)) ||                               \
        (CanListenOnlyMode        == (CanMode))                                  \
)

/**
 * @brief Parameter validity check for CAN Tx Cmd @ref en_can_tx_cmd_t
 */
#define IS_TX_CMD_VALID(TxCmd)                                                 \
(       (CanPTBTxCmd      == (TxCmd)) ||                                         \
        (CanPTBTxAbortCmd == (TxCmd)) ||                                         \
        (CanSTBTxOneCmd   == (TxCmd)) ||                                         \
        (CanSTBTxAllCmd   == (TxCmd)) ||                                         \
        (CanSTBTxAbortCmd == (TxCmd))                                            \
)

/**
 * @brief Parameter validity check for CAN status @ref en_can_status_t
 */
#define IS_CAN_STATUS_VALID(enCanStatus)                                       \
(       (CanRxActive == (enCanStatus)) ||                                        \
        (CanTxActive == (enCanStatus)) ||                                        \
        (CanBusoff   == (enCanStatus))                                           \
)

/**
 * @brief Parameter validity check for CAN Irq type @ref en_can_irq_type_t
 */
#define IS_CAN_IRQ_TYPE_VALID(enCanIrqType)                                    \
(       (CanRxIrqEn              == (enCanIrqType)) ||                           \
        (CanRxOverIrqEn          == (enCanIrqType)) ||                           \
        (CanRxBufFullIrqEn       == (enCanIrqType)) ||                           \
        (CanRxBufAlmostFullIrqEn == (enCanIrqType)) ||                           \
        (CanTxPrimaryIrqEn       == (enCanIrqType)) ||                           \
        (CanTxSecondaryIrqEn     == (enCanIrqType)) ||                           \
        (CanErrorIrqEn           == (enCanIrqType)) ||                           \
        (CanErrorPassiveIrqEn    == (enCanIrqType)) ||                           \
        (CanArbiLostIrqEn        == (enCanIrqType)) ||                           \
        (CanBusErrorIrqEn        == (enCanIrqType))                              \
)

/**
 * @brief Parameter validity check for CAN Irq flag type @ref en_can_irq_flag_type_t
 */
#define IS_CAN_IRQ_FLAG_VALID(enCanIrqFLg)                                     \
(       (CanTxBufFullIrqFlg        == (enCanIrqFLg)) ||                          \
        (CanRxIrqFlg               == (enCanIrqFLg)) ||                          \
        (CanRxOverIrqFlg           == (enCanIrqFLg)) ||                          \
        (CanRxBufFullIrqFlg        == (enCanIrqFLg)) ||                          \
        (CanRxBufAlmostFullIrqFlg  == (enCanIrqFLg)) ||                          \
        (CanTxPrimaryIrqFlg        == (enCanIrqFLg)) ||                          \
        (CanTxSecondaryIrqFlg      == (enCanIrqFLg)) ||                          \
        (CanErrorIrqFlg            == (enCanIrqFLg)) ||                          \
        (CanAbortIrqFlg            == (enCanIrqFLg)) ||                          \
        (CanErrorWarningIrqFlg     == (enCanIrqFLg)) ||                          \
        (CanErrorPassivenodeIrqFlg == (enCanIrqFLg)) ||                          \
        (CanErrorPassiveIrqFlg     == (enCanIrqFLg)) ||                          \
        (CanArbiLostIrqFlg         == (enCanIrqFLg)) ||                          \
        (CanBusErrorIrqFlg         == (enCanIrqFLg))                             \
)
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
 * @defgroup CAN_Global_Functions CAN全局函数定义
 * @{
 */

/**
 * @brief  CAN 初始化
 * @param  [in] pstcCanInitCfg: @ref stc_can_init_config_t.
 * @retval None.
 */
void CAN_Init(stc_can_init_config_t *pstcCanInitCfg)
{
    ASSERT(NULL != pstcCanInitCfg);

    CAN_RESET_ENABLE();

    HC_CAN->BT_f.PRESC = pstcCanInitCfg->stcCanBt.PRESC;
    HC_CAN->BT_f.SEG_1 = pstcCanInitCfg->stcCanBt.SEG_1;
    HC_CAN->BT_f.SEG_2 = pstcCanInitCfg->stcCanBt.SEG_2;
    HC_CAN->BT_f.SJW   = pstcCanInitCfg->stcCanBt.SJW;

    CAN_RESET_DISABLE();

    
    
    HC_CAN->LIMIT_f.AFWL = pstcCanInitCfg->stcWarningLimit.CanWarningLimitVal;
    HC_CAN->LIMIT_f.EWL  = pstcCanInitCfg->stcWarningLimit.CanErrorWarningLimitVal;
    
    HC_CAN->TCTRL_f.TSMODE = pstcCanInitCfg->enCanSTBMode;
    
    HC_CAN->RCTRL_f.RBALL  = pstcCanInitCfg->enCanRxBufAll;
    HC_CAN->RCTRL_f.ROM    = pstcCanInitCfg->enCanRxBufMode;
    HC_CAN->RTIE = 0x00U;
}


/**
 * @brief  CAN 去初始化 (RESET CAN register)
 * @retval None.
 */
void CAN_DeInit(void)
{
    CAN_RESET_ENABLE();
}


/**
 * @brief  CAN 模式配置
 * @param  [in] enMode: 模式. @ref en_can_mode_t
 * @param  [in] enCanSAck: 模式. 自应答 @ref en_can_self_ack_en_t
 * @param  [in] enNewState: TRUE:使能；FLASE:禁止.
 * @retval None.
 */
void CAN_ModeConfig(en_can_mode_t enMode, en_can_self_ack_en_t enCanSAck, boolean_t enNewState)
{
    ASSERT(IS_CAN_MODE_VALID(enMode));
    ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(CanListenOnlyMode == enMode)
    {
        HC_CAN->TCMD_f.LOM = enNewState;
    }else
    {
        if(TRUE == enNewState)
        {
            HC_CAN->CFG_STAT |= enMode;
        }else
        {
            HC_CAN->CFG_STAT &= (uint8_t)(~enMode);
        }
    }
    
    HC_CAN->RCTRL_f.SACK = enCanSAck;

}


/**
 * @brief  CAN 筛选器配置
 * @param  [in] pstcFilter: 筛选器配置指针 @ref stc_can_filter_t.
 * @param  [in] enNewState: TRUE:使能；FLASE:禁止.
 * @retval None.
 */
void CAN_FilterConfig(stc_can_filter_t *pstcFilter, boolean_t enNewState)
{
    ASSERT(NULL != pstcFilter);
    ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CAN_RESET_ENABLE();

    /* Acceptance filter address */
    HC_CAN->ACFCTRL_f.ACFADR  = pstcFilter->enFilterSel;

    /* ID config */
    HC_CAN->ACFCTRL_f.SELMASK = CAN_ACF_ID_REG_SEL;
    HC_CAN->ACF               = pstcFilter->u32CODE;

    /* MASK config */
    HC_CAN->ACFCTRL_f.SELMASK = CAN_ACF_MASK_REG_SEL;
    HC_CAN->ACF               = pstcFilter->u32MASK;

    /* Frame format config */
    HC_CAN->ACF_f.AIDEE = (((uint32_t)pstcFilter->enAcfFormat >> 1) & 0x01U);
    HC_CAN->ACF_f.AIDE  = ((uint32_t)pstcFilter->enAcfFormat & 0x01U);

    if(TRUE == enNewState)
    {
        HC_CAN->ACFEN |= 1u << pstcFilter->enFilterSel;
    }else
    {
        HC_CAN->ACFEN &= ~(1u << pstcFilter->enFilterSel);
    }

    CAN_RESET_DISABLE();
}


/**
 * @brief  CAN 发送数据帧设置
 * @param  [in] pstcTxFrame: 发送数据帧指针 @ref stc_can_txframe_t.
 * @retval None.
 */
void CAN_SetFrame(stc_can_txframe_t *pstcTxFrame)
{
    ASSERT(NULL != pstcTxFrame);

    HC_CAN->TCMD_f.TBSEL = pstcTxFrame->enBufferSel;
    HC_CAN->TBUF0 = pstcTxFrame->TBUF32_0;
    HC_CAN->TBUF1 = pstcTxFrame->TBUF32_1;
    HC_CAN->TBUF2 = pstcTxFrame->TBUF32_2[0];
    HC_CAN->TBUF3 = pstcTxFrame->TBUF32_2[1];

    if(CanSTBSel == pstcTxFrame->enBufferSel)
    {
        HC_CAN->TCTRL_f.TSNEXT = TRUE;
    }

}


/**
 * @brief  CAN 数据帧发送命令
 * @param  [in] enTxCmd: 数据帧发送命令 @ref en_can_tx_cmd_t.
 * @retval None.
 */
void CAN_TransmitCmd(en_can_tx_cmd_t enTxCmd)
{
    ASSERT(IS_TX_CMD_VALID(enTxCmd));

    HC_CAN->TCMD |= enTxCmd;

}


/**
 * @brief  CAN 发送数据缓冲器状态获取
 * @retval en_can_tx_buf_status_t: CAN 发送数据缓冲器状态 @ref en_can_tx_buf_status_t
 */
en_can_tx_buf_status_t CAN_TxBufStatusGet(void)
{
    return (en_can_tx_buf_status_t)HC_CAN->TCTRL_f.TSSTAT;
}


/**
 * @brief  CAN 数据帧接收
 * @param  [out] pstcRxFrame: 数据帧接收指针 @ref stc_can_rxframe_t.
 * @retval None.
 */
void CAN_Receive(stc_can_rxframe_t *pstcRxFrame)
{
    ASSERT(NULL != pstcRxFrame);

    pstcRxFrame->RBUF32_0    = HC_CAN->RBUF0;
    pstcRxFrame->RBUF32_1    = HC_CAN->RBUF1;
    pstcRxFrame->RBUF32_2[0] = HC_CAN->RBUF2;
    pstcRxFrame->RBUF32_2[1] = HC_CAN->RBUF3;

    HC_CAN->RCTRL_f.RREL = 1U;

}


/**
 * @brief  CAN 接收数据缓冲器状态获取
 * @retval en_can_rx_buf_status_t: Can 接收数据缓冲器状态 @ref en_can_rx_buf_status_t
 */
en_can_rx_buf_status_t CAN_RxBufStatusGet(void)
{
    return (en_can_rx_buf_status_t)HC_CAN->RCTRL_f.RSSTAT;
}


/**
 * @brief  CAN 错误状态获取
 * @retval en_can_error_t: 错误状态 @ref en_can_error_t
 */
en_can_error_t CAN_ErrorStatusGet(void)
{
    if(6U > HC_CAN->EALCAP_f.KOER)
    {
        return (en_can_error_t)HC_CAN->EALCAP_f.KOER;
    }else
    {
        return UNKOWN_ERROR;
    }

}


/**
 * @brief  CAN 通信状态获取
 * @param  [in] enCanStatus: CAN 通信状态 @ref en_can_status_t 
 * @retval boolean_t: 
 *              - TRUE:对应状态位已置位
 *              - FLASE:对应状态位未置位
 */
boolean_t CAN_StatusGet(en_can_status_t enCanStatus)
{
    ASSERT(IS_CAN_STATUS_VALID(enCanStatus));

    if(HC_CAN->CFG_STAT & enCanStatus)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }
}


/**
 * @brief  CAN 中断使能
 * @param  [in] enCanIrqType: 中断类型 @ref en_can_irq_type_t.
 * @param  [in] enNewState: TRUE:使能；FLASE:禁止.
 * @retval None.
 */
void CAN_IrqCmd(en_can_irq_type_t enCanIrqType, boolean_t enNewState)
{
    volatile uint32_t *u32pIE;

    ASSERT(IS_CAN_IRQ_TYPE_VALID(enCanIrqType));
    ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32pIE = (volatile uint32_t*)(&HC_CAN->RTIE);

    if(TRUE == enNewState)
    {
        *u32pIE |= (uint32_t)enCanIrqType;
    }else
    {
        *u32pIE &= ~(uint32_t)enCanIrqType;
    }

}


/**
 * @brief  CAN 中断标志获取
 * @param  [in] enCanIrqFlgType: 中断标志类型 @ref en_can_irq_flag_type_t.
 * @retval boolean_t: 
 *             - TRUE: 发生此中断
 *             - FLASE: 未发生此中断
 */
boolean_t CAN_IrqFlgGet(en_can_irq_flag_type_t enCanIrqFlgType)
{
    volatile uint32_t *u32pIE = NULL;

    ASSERT(IS_CAN_IRQ_FLAG_VALID(enCanIrqFlgType));

    u32pIE = (volatile uint32_t*)(&HC_CAN->RTIE);

    if( *u32pIE & (uint32_t)enCanIrqFlgType)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }

}


/**
 * @brief  CAN 中断标志清除
 * @param  [in] enCanIrqFlgType: 中断标志类型 @ref en_can_irq_flag_type_t.
 * @retval None.
 */
void CAN_IrqFlgClr(en_can_irq_flag_type_t enCanIrqFlgType)
{
    volatile uint32_t *u32pIE = NULL;
    uint32_t u32IETempMsk = CAN_IE_CLEAR_MASK;
    
    
    ASSERT(IS_CAN_IRQ_FLAG_VALID(enCanIrqFlgType));

    u32pIE = (volatile uint32_t*)(&HC_CAN->RTIE);

    *u32pIE = (((*u32pIE)&u32IETempMsk) | (uint32_t)enCanIrqFlgType);

}


/**
 * @brief  CAN 接收错误计数值获取
 * 
 * @retval uint8_t Error Counter(0~255).
 */
uint8_t CAN_RxErrorCntGet(void)
{
    return HC_CAN->RECNT;
}


/**
 * @brief  CAN 发送错误计数值获取
 * 
 * @retval uint8_t Error Counter(0~255).
 */
uint8_t CAN_TxErrorCntGet(void)
{
    return HC_CAN->TECNT;
}


/**
 * @brief  CAN 仲裁捕获
 * 
 * @retval uint8_t address(0~31).
 */
uint8_t CAN_ArbitrationLostCap(void)
{
    return HC_CAN->EALCAP_f.ALC;
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
 *****************************************************************************/
