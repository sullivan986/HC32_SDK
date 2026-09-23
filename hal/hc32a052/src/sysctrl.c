/**
 *******************************************************************************
 * @file  sysctrl.c
 * @brief This file provides firmware functions to manage the SYSCTRL.
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
#include "sysctrl.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @brief SYSCTRL Driver Library SYSCTRL模块驱动库
 * @{
 */


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Macros SYSCTRL局部宏定义
 * @{
 */

/**
 * @defgroup SYSCTRL_CLK_TIMEOUT 超时定义值
 * @{
 */
#define CLK_TIMEOUT                 (1000000u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_IN_DIV PLL输入时钟源分频倍数范围定义
 * @{
 */
#define SYSCTRL_PLL_IN_DIV_MIN      (1u)
#define SYSCTRL_PLL_IN_DIV_MAX      (2u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_MULLN PLL 整数倍频范围定义
 * @{
 */
#define SYSCTRL_PLL_MULLN_MIN       (2u)
#define SYSCTRL_PLL_MULLN_MAX       (128u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_MULLF PLL 小数倍频范围定义
 * @{
 */
#define SYSCTRL_PLL_MULLF_MIN       (0u)
#define SYSCTRL_PLL_MULLF_MAX       (7u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_OUT_DIV PLL 输出分频定义
 * @{
 */
#define SYSCTRL_PLL_OUT_DIV_MIN     (4u)
#define SYSCTRL_PLL_OUT_DIV_MAX     (34u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_FVCO PLL Fvco范围定义
 * @{
 */
#define SYSCTRL_PLL_FVCO_MIN        (384000000u)
#define SYSCTRL_PLL_FVCO_MAX        (512000000u)
/**
 * @}
 */
/**
 * @defgroup SYSCTRL_PLL_OUT PLL 输出频率范围定义
 * @{
 */
#define SYSCTRL_PLL_OUT_MIN         (15000000u)
#define SYSCTRL_PLL_OUT_MAX         (64000000u)
/**
 * @}
 */
/**
 * @defgroup RCL_CR_TRIM RCL trim值地址定义
 * @{
 */
#define RCL_CR_TRIM_38400_VAL       (0x00101BE8u)
#define RCL_CR_TRIM_32768_VAL       (0x00101BEAu)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Variables SYSCTRL全局变量定义
 * @{
 */
extern uint32_t SystemCoreClock;
/**
 * @}
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Variables SYSCTRL局部变量定义
 * @{
 */

static const uint32_t au32RCHFreqTable[4] = {
                                              1u,
                                              2u,
                                              3u,
                                              4u
                                            };
/**
 * @}
 */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Functions SYSCTRL局部函数定义
 * @{
 */
static void _SysctrlUnlock(void);
/**
* @}
*/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Functions SYSCTRL局部函数定义
 * @{
 */
/**
 * @brief SYSCTRL0\SYSCTRL1寄存器操作解锁
 *
 * @retval None
 */
static void _SysctrlUnlock(void)
{
    HC_SYSCTRL->CR3 = 0x5A5Au;
    HC_SYSCTRL->CR3 = 0xA5A5u;
}
/**
* @}
*/

/**
 * @defgroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */

/**
 * @brief 系统时钟源使能
 * @param [in]  enSource   目标时钟源 @ref en_sysctrl_clk_source_t
 * @param [in]  bFlag      TRUE:开/FALSE:关
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 * - 注意:使能RCH/RCL，优先设置RCH/RCL相关参数!!!
 * - 注意:使能XTH/XTL，必须先设置XTH和XTL频率、驱动能力、稳定时间等参数!!!
 * - 注意:使能PLL之前，需确保PLL配置成功!!!
 */
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;
    
    bFlag = bFlag  ? TRUE : FALSE;

    u32Temp = HC_SYSCTRL->PERICLKEN1;
    switch (enSource)
    {
        case SysctrlClkRCH:
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.RCH = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.RCH) && bFlag)
            {
                ;
            }
            break;

        case SysctrlClkXTH:
            HC_SYSCTRL->PERICLKEN1_f.GPIOD = 1u;
            HC_GPIOD->ADS |= 3u;
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.XTH = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.XTH) && bFlag)
            {
                ;
            }
			delay1ms(10);
            break;

        case SysctrlClkRCL:
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.RCL = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.RCL) && bFlag)
            {
                ;
            }
            break;

        case SysctrlClkXTL:
            HC_SYSCTRL->PERICLKEN1_f.GPIOC = TRUE;
            HC_GPIOC->ADS |= 0xC000u;
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.XTL = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.XTL) && bFlag)
            {
                ;
            }
            break;

        case SysctrlClkPLL:
            HC_SYSCTRL->PERICLKEN0_f.ADC = TRUE;
            HC_ADC->BGR_f.BGREN = TRUE;
            delay100us(2u);
            _SysctrlUnlock();
            HC_SYSCTRL->CR2_f.PLL = bFlag;
            while((1u != HC_SYSCTRL->STATE_f.PLL) && bFlag)
            {
                ;
            }
            break;

        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    HC_SYSCTRL->PERICLKEN1 = u32Temp;
    
    return enRet;
}


/**
 * @brief 内部高速时钟RCH目标频率设置
 *
 * @param [in]  enRCHFreq  设定的RCH目标频率值 @ref en_sysctrl_rch_freq_t
 *
 * @retval  en_result_t:
 *            - Ok:  设定成功
 *            - 其他: 设定失败或时钟未稳定
 */
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq)
{
    /* 加载RCH 分频值 */
    HC_SYSCTRL->RCHCR_f.DIV = enRCHFreq;

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();
    
    return Ok;
}


/**
 * @brief 内部低速时钟频率TRIM值加载
 *
 * @param [in]  enRCLFreq  设定的RCL目标频率值 @ref en_sysctrl_rcl_freq_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq)
{
    uint16_t u16Val;
    u16Val = ((SysctrlRclFreq38400 == enRCLFreq) ? (*(volatile uint16_t*)(RCL_CR_TRIM_38400_VAL )) :\
                                                   (*(volatile uint16_t*)(RCL_CR_TRIM_32768_VAL )));
    HC_SYSCTRL->RCLTRIM_f.TRIM  = u16Val;

    return Ok;
}

/**
 * @brief 内部低速时钟稳定周期配置
 *
 * @param [in]  enCycle     内部低速时钟稳定周期设置 @ref en_sysctrl_rcl_cycle_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    HC_SYSCTRL->RCLCR_f.STARTUP = enCycle;
    return enRet;
}


/**
 * @brief 外部高速时钟频率范围设定
 * 
 * @param [in]  enXTHFreq  设定的频率值 @ref en_sysctrl_xth_freq_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败或时钟未稳定
 */
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq)
{
    en_result_t enRet = Ok;

    HC_SYSCTRL->XTHCR_f.RANGE = enXTHFreq;

    return enRet;
}


/**
 * @brief 外部高速晶振驱动配置
 * 
 * @param [in]  enDriver   外部高速晶振驱动能力选择 @ref en_sysctrl_xtal_driver_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    HC_SYSCTRL->XTHCR_f.DRIVER   = enDriver;

    return enRet;
}

/**
 * @brief 外部高速时钟稳定周期配置
 * 
 * @param [in]  enCycle     外部高速时钟稳定周期设置 @ref en_sysctrl_xth_cycle_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    HC_SYSCTRL->XTHCR_f.STARTUP = enCycle;
    return enRet;
}

/**
 * @brief 外部低速晶振驱动配置
 * 
 * @param [in]  enAmp:      外部低速晶振频率范围选择 @ref en_sysctrl_xtl_amp_t
 * @param [in]  enDriver:   外部低速晶振驱动能力选择 @ref en_sysctrl_xtal_driver_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_XTLDriverCfg(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    HC_SYSCTRL->XTLCR_f.AMP_SEL = enAmp;
    HC_SYSCTRL->XTLCR_f.DRIVER  = enDriver;

    return enRet;
}

/**
 * @brief 外部低速时钟稳定周期配置
 *
 * @param [in]  enCycle     外部低速时钟稳定周期设置 @ref en_sysctrl_xtl_cycle_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    HC_SYSCTRL->XTLCR_f.STARTUP = enCycle;
    return enRet;
}


/**
 * @brief 设置XTH/XTL 失效检测功能
 * 
 * @param [in]  u32OscSel      XTH/XTL选择  @ref XTH_XTL_Fail_Det_Sel
 * @param [in]  pstcCfg        失效检测结构体 @ref stc_sysctrl_fail_det_cfg_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_ExtOscFailDetCfg(uint32_t u32OscSel, stc_sysctrl_fail_det_cfg_t* pstcCfg)
{
    uint32_t u32BaseAddress;
    
    u32BaseAddress = (uint32_t)(&HC_SYSCTRL->XTHCR) + u32OscSel;
    
    REG_MODIFY(*(volatile uint32_t *)u32BaseAddress, \
               SYSCTRL_XTHCR_DETEN | SYSCTRL_XTHCR_DETTIME | SYSCTRL_XTHCR_DETIE,\
               pstcCfg->u32DetectEn | pstcCfg->u32DetectTime | pstcCfg->u32DetectIntEn);

    return Ok;
}

/**
 * @brief PLL时钟配置
 *
 * @param [in]  pstcPLLCfg PLL配置结构体指针  @ref stc_sysctrl_pll_cfg_t
 *              - 注意:调用PLL配置函数需要判断返回值，确保参数配置成功!!!
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败或参数值不匹配
 */
en_result_t Sysctrl_SetPLLFreq(stc_sysctrl_pll_cfg_t *pstcPLLCfg)
{
    en_result_t enRet = Ok;
    uint32_t u32Fin;
    volatile uint32_t u32Fvco, u32PllOut;
    
    /* PLL最高时钟不能超过64MHz */
    if((pstcPLLCfg->u8SourceDiv < SYSCTRL_PLL_IN_DIV_MIN) || (pstcPLLCfg->u8SourceDiv > SYSCTRL_PLL_IN_DIV_MAX))
    {
        return ErrorInvalidParameter;
    }
    if((pstcPLLCfg->u8MullN < SYSCTRL_PLL_MULLN_MIN) || (pstcPLLCfg->u8MullN > SYSCTRL_PLL_MULLN_MAX))
    {
        return ErrorInvalidParameter;
    }
    if(pstcPLLCfg->u8MullF > SYSCTRL_PLL_MULLF_MAX)
    {
        return ErrorInvalidParameter;
    }
    if((pstcPLLCfg->u8OutputDiv < SYSCTRL_PLL_OUT_DIV_MIN) || (pstcPLLCfg->u8OutputDiv > SYSCTRL_PLL_OUT_DIV_MAX))
    {
        return ErrorInvalidParameter;
    }
    
    if(0x01u == (pstcPLLCfg->u8OutputDiv & 0x01u))
    {
        return ErrorInvalidParameter;
    }
        
    if(SysctrlPllRch == pstcPLLCfg->enPllSource)
    {
        u32Fin = 12000000u;
    }
    else
    {
        u32Fin = SYSTEM_XTH;
    }
    u32Fin = u32Fin  / pstcPLLCfg->u8SourceDiv;
    u32Fvco = u32Fin * pstcPLLCfg->u8MullN + ((u32Fin * pstcPLLCfg->u8MullF)>>3u);
    if(u32Fvco < SYSCTRL_PLL_FVCO_MIN)
    {
        return ErrorInvalidParameter;
    }
    if(u32Fvco > SYSCTRL_PLL_FVCO_MAX)
    {
        return ErrorInvalidParameter;
    }
    u32PllOut = u32Fvco / pstcPLLCfg->u8OutputDiv;
    if(u32PllOut < SYSCTRL_PLL_OUT_MIN)
    {
        return ErrorInvalidParameter;
    }
    if(u32PllOut > SYSCTRL_PLL_OUT_MAX)
    {
        return ErrorInvalidParameter;
    }
    
    REG_WRITE(HC_SYSCTRL->PLLCR, pstcPLLCfg->enPllSource | \
                                  (((uint32_t)pstcPLLCfg->u8SourceDiv-1u)<<SYSCTRL_PLLCR_DIVR_Pos) |\
                                  (((uint32_t)pstcPLLCfg->u8MullN-2u)<<SYSCTRL_PLLCR_DIVN_Pos) | \
                                  (uint32_t)pstcPLLCfg->u8MullF<<SYSCTRL_PLLCR_DIVF_Pos |\
                                  ((((uint32_t)pstcPLLCfg->u8OutputDiv>>1u) -2u)<<SYSCTRL_PLLCR_POSTDIV_Pos));
    
    REG_MODIFY(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_WAITCYCLE, (uint32_t)pstcPLLCfg->enStableWaitCycle);

    return enRet;
}




/**
 * @brief 时钟源切换，该函数执行后会开启新时钟源
 * 
 * @note  选择时钟源之前，需根据需要配置目标时钟源的频率/驱动参数/使能时钟源等!!!
 * 
 * @param [in]  enSource   新时钟源  @ref en_sysctrl_clk_source_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 * - 注意1：调用此函数前，必须确保新的系统时钟源的相关参数已经初始化，并且新时钟源已经使能且稳定运行
 * - 注意2: 时钟切换前，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2
 * - 注意3: 当HCLK大于24MHz小于48MH在时，FLASH等待周期插入必须至少为1,否则程序运行可能产生未知错误
 * - 注意4: 当HCLK大于48MHz时，FLASH等待周期插入必须至少为2,否则程序运行可能产生未知错误
 */
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource)
{
    en_result_t enRet = Ok;

    en_sysctrl_clk_source_t ClkNew = enSource;

    _SysctrlUnlock();
    HC_SYSCTRL->CR0_f.CLKSRC = ClkNew;

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();

    return enRet;
}

/**
 * @brief 系统时钟 HCLK 频率获取
 * 
 * @retval uint32_t：HCLK频率值(Hz)
 */
uint32_t Sysctrl_GetHClkFreq(void)
{
    uint16_t u16RCL32p8;
    uint32_t u32ValHclk, u32Fin,  u32Fdivn, u32Fdivf;
    
    u16RCL32p8  = SYSCTRL_RCL_TRIM_32p8KHz;


    /* Update [SystemCoreClock]*/
    if(SYSCTRL_SYSCLK_SOURCE_XTH == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        u32ValHclk = SYSTEM_XTH;
    }

    if(SYSCTRL_SYSCLK_SOURCE_RCL == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        if(u16RCL32p8 == (REG_READBITS(HC_SYSCTRL->RCLTRIM, SYSCTRL_RCLTRIM_TRIM)))
        {
            u32ValHclk = 32768u;
        }
        else
        {
            u32ValHclk = 38400u;
        }
    }

    if(SYSCTRL_SYSCLK_SOURCE_XTL == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        u32ValHclk = SYSTEM_XTL;
    }

    if(SYSCTRL_SYSCLK_SOURCE_PLL == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        if(SysctrlPllRch == REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_SRC))
        {
            u32ValHclk = 12000000u;
        }
        else
        {
            u32ValHclk = SYSTEM_XTH;
        }

        u32Fin = u32ValHclk /((REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_DIVR) >> SYSCTRL_PLLCR_DIVR_Pos) + 1u);
        u32Fdivn = u32Fin * ((REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_DIVN) >> SYSCTRL_PLLCR_DIVN_Pos) + 2u);
        u32Fdivf = (u32Fin * (REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_DIVF) >> SYSCTRL_PLLCR_DIVF_Pos)) >> 3;
        u32ValHclk = ((u32Fdivn + u32Fdivf) / ((REG_READBITS(HC_SYSCTRL->PLLCR, SYSCTRL_PLLCR_POSTDIV) >> SYSCTRL_PLLCR_POSTDIV_Pos) + 2u)) >> 1;
    }

    if(SYSCTRL_SYSCLK_SOURCE_RCH == REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_CLKSRC))
    {
        u32ValHclk = 12000000u;

        u32ValHclk = u32ValHclk / au32RCHFreqTable[REG_READBITS(HC_SYSCTRL->RCHCR, SYSCTRL_RCHCR_DIV) >> SYSCTRL_RCHCR_DIV_Pos];

    }

    u32ValHclk = u32ValHclk >> (REG_READBITS(HC_SYSCTRL->CR0, SYSCTRL_CR0_HCLKPRS) >> SYSCTRL_CR0_HCLKPRS_Pos);

    return u32ValHclk;
}

/**
 * @brief 获得外设时钟（PCLK）频率值
 *
 * @retval uint32_t：PCLK频率值(Hz)
 */
uint32_t Sysctrl_GetPClkFreq(void)
{
    uint32_t u32Val = 0u;

    u32Val = Sysctrl_GetHClkFreq();
    u32Val = (u32Val >> (HC_SYSCTRL->CR0_f.PCLKPRS));

    return u32Val;
}

/**
 * @brief 时钟去初始化函数
 * @恢复为上电默认状态->PCLK=HCLK=SystemClk=RCH4MHz
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_ClkDeInit(void)
{
    en_result_t enRet = Ok;

    /* 配置RCH为内部4Hz */
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);

    /* 时钟源使能 */
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);

    /* 时钟源切换 */
    Sysctrl_SysClkSwitch(SysctrlClkRCH);

    /* 其它时钟源使能关闭 */
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, FALSE);

    /* 时钟分频设置 */
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();
    
    return enRet;
}



/**
 * @brief 系统时钟（HCLK）分频设定
 * 
 * @param [in]  enHCLKDiv  分频设定值 @ref en_sysctrl_hclk_div_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv)
{
    _SysctrlUnlock();
    HC_SYSCTRL->CR0_f.HCLKPRS = enHCLKDiv;

    /* 更新Core时钟(HCLK) */
    SystemCoreClockUpdate();
    
    return Ok;
}

/**
 * @brief 外设时钟（PCLK）分频设定
 * 
 * @param [in]  enPCLKDiv  分频设定值  @ref en_sysctrl_pclk_div_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv)
{
    _SysctrlUnlock();
    HC_SYSCTRL->CR0_f.PCLKPRS = enPCLKDiv;

    return Ok;
}


/**
 * @brief 设置外设时钟门控开关
 * @设置外设时钟门控开关:用于控制外设模块的使能,使用该模块的功能之前,必须使能该模块的门控时钟
 * @param [in]  enPeripheral   目标外设  @ref en_sysctrl_peripheral_gate_t
 * @param [in]  bFlag          TRUE:开/FALSE:关
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag)
{
    if(enPeripheral & _PERICLK_REG1_MSK)
    {
        enPeripheral &= ~_PERICLK_REG1_MSK;
        
        REG_MODIFY(HC_SYSCTRL->PERICLKEN1, 1u<<((uint32_t)enPeripheral), ((uint32_t)bFlag)<<((uint32_t)enPeripheral));

    }
    else
    {
        REG_MODIFY(HC_SYSCTRL->PERICLKEN0, 1u<<((uint32_t)enPeripheral), ((uint32_t)bFlag)<<((uint32_t)enPeripheral));
    }

    return Ok;
}

/**
 * @brief 获得外设时钟门控开关状态 @ref en_sysctrl_peripheral_gate_t
 * 
 * @param [in]  enPeripheral   目标外设
 * 
 * @retval boolean_t:
 *                - TRUE: 开
 *                - FALSE: 关
 */
boolean_t Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral)
{
    if(enPeripheral&_PERICLK_REG1_MSK)
    {
        enPeripheral &= ~_PERICLK_REG1_MSK;
        
        return REG_READBITS(HC_SYSCTRL->PERICLKEN1, 1u<<((uint32_t)enPeripheral)) ? TRUE : FALSE;
    }
    else
    {
        return REG_READBITS(HC_SYSCTRL->PERICLKEN0, 1u<<((uint32_t)enPeripheral)) ? TRUE : FALSE;
    }
}

/**
 * @brief 系统功能设定
 * 
 * @param [in]  enFunc     系统功能枚举类型  @ref en_sysctrl_func_t
 * @param [in]  bFlag      TRUE:开/FALSE:关
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag)
{
    if(enFunc & _SYSCTRL_FUNC_MSK)
    {
        enFunc &= ~_SYSCTRL_FUNC_MSK;
        _SysctrlUnlock();
        REG_MODIFY(HC_SYSCTRL->CR2, 1u<<((uint32_t)enFunc), ((uint32_t)bFlag)<<((uint32_t)enFunc));

    }
    else
    {
        _SysctrlUnlock();
        REG_MODIFY(HC_SYSCTRL->CR1, 1u<<((uint32_t)enFunc), ((uint32_t)bFlag)<<((uint32_t)enFunc));
    }
    return Ok;
}


/**
 * @brief 获取外部时钟起振标志
 * 
 * @param [in]  u32ExtOscFlag  外部时钟起振标志类型  @ref XTH_XTL_Flag_Type
 * 
 * @retval boolean_t:
 *                - TRUE: 失败 
 *                - FALSE: 成功
 */
boolean_t Sysctrl_GetExtOscFlag(uint32_t u32ExtOscFlag)
{
    return REG_READBITS(HC_SYSCTRL->STATE, u32ExtOscFlag) ? TRUE : FALSE;
}


/**
 * @brief 清除外部时钟起振标志
 * 
 * @param [in]  u32ExtOscFlag  外部时钟起振标志类型  @ref XTH_XTL_Flag_Type
 * 
 * @retval boolean_t:
 *                - TRUE: 失败 
 *                - FALSE: 成功
 */
en_result_t Sysctrl_ClrExtOscFlag(uint32_t u32ExtOscFlag)
{
    REG_CLEARBITS(HC_SYSCTRL->STATE, u32ExtOscFlag);
    
    return Ok;
}

/**
 * @brief 设定RTC校准时钟频率
 * 
 * @param [in]  enRtcAdj   校准频率 @ref en_sysctrl_rtc_adjust_t
 * 
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_SetRTCAdjustClkFreq(en_sysctrl_rtc_adjust_t enRtcAdj)
{
    _SysctrlUnlock();
    HC_SYSCTRL->CR1_f.RTCADJ = enRtcAdj;

    return Ok;
}


/**
 * @brief 系统外设复位
 * 
 * @param [in]  enPeripheral 系统外设复位 @ref en_sysctrl_peripheral_gate_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Sysctrl_PeriphReset(en_sysctrl_peripheral_gate_t enPeripheral)
{
    en_result_t enRet = Ok;
    
    if(enPeripheral > SysctrlPeripheralFlash)
    {
        enPeripheral &= (~_PERICLK_REG1_MSK);
        REG_CLEARBITS(HC_SYSCTRL->PERIRESET1, 1u<<((uint32_t)enPeripheral));
        REG_SETBITS(HC_SYSCTRL->PERIRESET1, 1u<<((uint32_t)enPeripheral));
    }
    else if(enPeripheral < SysctrlPeripheralFlash)
    {
        REG_CLEARBITS(HC_SYSCTRL->PERIRESET0, 1u<<((uint32_t)enPeripheral));
        REG_SETBITS(HC_SYSCTRL->PERIRESET0, 1u<<((uint32_t)enPeripheral));
    }
    else
    {
        enRet = Error;
    }
    
    return enRet;
}

/**
 * @brief 系统复位标志清除
 *
 * @param [in]  u32ResetFlag 系统复位标志 @ref Sysctrl_Reset_Flag
 *
 * @retval None
 */
void Sysctrl_ResetFlagClear(uint32_t u32ResetFlag)
{
    REG_CLEARBITS(HC_SYSCTRL->RSTFLAG, u32ResetFlag);
}


/**
 * @brief 系统复位标志获取
 *
 * @param [in]  u32ResetFlag 系统复位标志 @ref Sysctrl_Reset_Flag
 *
 * @retval uint32_t：复位标志
 */
uint32_t Sysctrl_ResetFlagGet(uint32_t u32ResetFlag)
{
    return REG_READBITS(HC_SYSCTRL->RSTFLAG, u32ResetFlag);
}

/**
 * @brief 系统调试功能控制使能,调试状态下暂停模块计数
 *
 * @param [in]  u32DebugModule 系统调试功能定义 @ref Sysctrl_Debug_Module
 *
 * @retval None
 */
void Sysctrl_DebugEnable(uint32_t u32DebugModule)
{
    REG_SETBITS(HC_SYSCTRL->DBGSTOP, u32DebugModule);
}

/**
 * @brief 系统调试功能控制禁止，调试状态下模块计数继续
 *
 * @param [in]  u32DebugModule 系统复位标志 @ref Sysctrl_Debug_Module
 *
 * @retval None
 */
void Sysctrl_DebugDisable(uint32_t u32DebugModule)
{
    REG_CLEARBITS(HC_SYSCTRL->DBGSTOP, u32DebugModule);
}


/**
 * @brief 获取芯片相关信息
 *
 * @param [in]  pstcChipInfo 芯片信息结构体指针 @ref stc_sysctrl_chip_info_t
 *
 * @retval None
 */
void Sysctrl_GetChipInfo(stc_sysctrl_chip_info_t *pstcChipInfo)
{
    //pstcChipInfo->pu8UID          = (uint8_t*)0x0010xxxx;
    pstcChipInfo->pcProductNumber = (char_t*)0x00101B40;
    pstcChipInfo->u32FlashSize    = *((uint32_t*)0x00101B60);
    pstcChipInfo->u32RamSize      = *((uint32_t*)0x00101B64);
    pstcChipInfo->u16PinsCounter  = *((uint16_t*)0x00101B6A);		
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
