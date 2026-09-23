/**
 *******************************************************************************
 * @file  rtc.c
 * @brief This file provides firmware functions to manage the RTC.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-07-15       MADS             First version
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
#include "rtc.h"


/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_RTC RTC模块驱动库
 * @brief RTC Driver Library RTC模块驱动库
 * @{
 */

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
/**
 * @defgroup RTC_Local_Macros RTC局部宏定义
 * @{
 */
/**
 * @defgroup RTC_WPR_Value RTC WPR Value definition RTC WPR保护序列
 * @{
 */
#define RTC_UNLOCK_VALUE1       (0xCAU) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_UNLOCK_VALUE2       (0x53U) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_LOCK_VALUE          (0xFFU) /*!< 写入其他序列锁定寄存器写，除了WPR与ICR */
/**
 * @}
 */

/**
 * @}
 */


/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
/**
 * @addtogroup RTC_Local_Functions RTC局部函数定义
 * @{
 */
static en_result_t RTC_CheckBCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max);
static boolean_t RTC_IsLeapYear(uint8_t u8year);
/**
 * @}
 */

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/
/**
 * @defgroup RTC_Local_Variables RTC局部变量定义
 * @{
 */
/**
 * @brief  平年每个月最后一天日期表 BCD格式.
 */
const static uint8_t Cnst_Month_Tbl[12]={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
/**
 * @}
 */
/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup RTC_Local_Functions RTC局部函数定义
 * @{
 */
/**
 * @brief  BCD格式检查.
 * @param  [in] u8data: BCD带检查数
 * @param  [in] u8limit_min: BCD最小值
 * @param  [in] u8limit_min: BCD最大值
 * @retval en_result_t:
 *           - Ok: BCD格式正确
 *           - Error: BCD格式错误
 */
static en_result_t RTC_CheckBCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max)
{
    if (((u8data & 0x0FU) > 0x09U) || ((u8data & 0xF0U) > 0x90U)
    ||(u8data > u8limit_max) || (u8data < u8limit_min))
    {
        return Error;
    }
    return Ok;
}


/**
 * @brief  闰年判断.
 * @param  [in] u8year: 2000年后的年份的十位和个位0~99 
 * @retval boolean_t:
 *           - TRUE: 是闰年
 *           - FALSE: 不是闰年
 */
static boolean_t RTC_IsLeapYear(uint8_t u8year)
{
    uint16_t u16year;
    u16year = 2000U + u8year;
    if(((u16year%4U == 0U) && (u16year%100U != 0U)) || (u16year%400U == 0U))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
* @}
*/

/**
 * @defgroup RTC_Global_Functions RTC全局函数定义
 * @{
 */
/**
 * @brief  RTC写保护寄存器解锁.
 * @retval None.
 */
void RTC_Unlock(void)
{
    HC_RTC->WPR = RTC_UNLOCK_VALUE1;
    HC_RTC->WPR = RTC_UNLOCK_VALUE2;
}

/**
 * @brief  RTC写保护寄存器锁定.
 * @retval None.
 */
void RTC_Lock(void)
{
    HC_RTC->WPR = RTC_UNLOCK_VALUE1;
    HC_RTC->WPR = RTC_LOCK_VALUE;
}


/**
 * @brief  RTC计数器的使能或停止.
 * @param  [in] NewState: TRUE:使能RTC计数  FALSE:停止RTC计数
 * @retval None.
 */
void RTC_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(HC_RTC->CR0)), RTC_CR0_START_Pos, NewState);
}


/**
 * @brief  RTC计数器启动等待函数，如启动RTC计数器后立即进入低功耗模式，
 *         进入低功耗模式之前需执行此函数，以确保RTC已启动完成.
 * @retval None.
 */
void RTC_StartWait(void)
{
    HC_RTC->CR1_f.WAIT = 1U;
    while (HC_RTC->CR1_f.WAITF != 1U)  /* 等待直到WAITF=1 */
    {
        ;
    }
    HC_RTC->CR1_f.WAIT = 0U;
    while (HC_RTC->CR1_f.WAITF != 0U)  /* 等待直到WAITF=0 */
    {
        ;
    }
}
 
/**
 * @brief  RTC的1Hz输出的使能或停止.
 * @param  [in] pricision: RtcHz1selGeneralPricision 或 RtcHz1selHighPricision @ref en_rtc_hz1sel_t
 * @param  [in] NewState: FALSE: Hz1o_Disable  TRUE: HZ1o_Enable
 * @retval None.
 */
void RTC_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState)
{
    SetBit((uint32_t)(&(HC_RTC->CR0)), RTC_CR0_HZ1SEL_Pos, pricision);  /* 设置普通精度或者高精度1Hz输出 */
    SetBit((uint32_t)(&(HC_RTC->CR0)), RTC_CR0_HZ1OE_Pos, NewState);   /* 设置1Hz输出使能或禁止 */
}    


/**
 * @brief  设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX).
 * @param  [in] pstcPrd: 根据结构体的定义设置PRDSEL、PRDS与PRDX @ref stc_rtc_prdcfg_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_PrdCfg(stc_rtc_prdcfg_t* pstcPrd)
{
    en_result_t enRet = Ok;
    HC_RTC->CR0_f.PRDSEL = pstcPrd->enPrdsel;
    if(pstcPrd->enPrdsel == RtcPrds)
    {
        HC_RTC->CR0_f.PRDS = pstcPrd->enPrds; 
    }
    else if(pstcPrd->enPrdsel == RtcPrdx)
    {
        if(pstcPrd->u8Prdx>=64U)
        {
            enRet = ErrorInvalidParameter;
            return enRet;
        }
        HC_RTC->CR0_f.PRDX = pstcPrd->u8Prdx;
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }
    return enRet;
}    

/**
 * @brief  闹钟使能.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @retval None.
 */
void RTC_AlarmEnalbe(en_rtc_alarmch_t enAlarmX)
{
    if(RtcAlarmA == enAlarmX)
    {
        HC_RTC->CR2 |= RTC_CR2_ALMAE;
    }
    else if(RtcAlarmB == enAlarmX)
    {
        HC_RTC->CR2 |= RTC_CR2_ALMBE;
    }
    else
    {
        ;
    }
}

/**
 * @brief  闹钟失能.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @retval None.
 */
void RTC_AlarmDisalbe(en_rtc_alarmch_t enAlarmX)
{
    if(RtcAlarmA == enAlarmX)
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMAE);
    }
    else if(RtcAlarmB == enAlarmX)
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMBE);
    }
    else
    {
        ;
    }
}


/**
 * @brief  RTC闹钟中断时间获取.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @param  [in] pstcAlarmTime: 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval None.
 */
void RTC_GetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime)
{
    uint32_t u32RegAddr;
    uint8_t u8Hour;

    if(RtcAlarmA == enAlarmX)
    {
        u32RegAddr = (uint32_t)&HC_RTC->ALMA;
    }
    else
    {
        u32RegAddr = (uint32_t)&HC_RTC->ALMB;
    }

    pstcAlarmTime->u8AlarmSec    = (uint8_t)(((*(uint32_t*)u32RegAddr) & (RTC_ALMA_SECL | RTC_ALMA_SECH)) >> RTC_ALMA_SECL_Pos);
    pstcAlarmTime->u8AlarmMinute = (uint8_t)(((*(uint32_t*)u32RegAddr) & (RTC_ALMA_MINL | RTC_ALMA_MINH)) >> RTC_ALMA_MINL_Pos);
    u8Hour   = (uint8_t)(((*(uint32_t*)u32RegAddr) & (RTC_ALMA_HOURL | RTC_ALMA_HOURH)) >> RTC_ALMA_HOURL_Pos);
    pstcAlarmTime->u8AlarmDayOfWeek   = (uint8_t)(((*(uint32_t*)u32RegAddr) & RTC_ALMA_WEEK) >> RTC_ALMA_WEEK_Pos);
    pstcAlarmTime->bAlarmMskH = ((*(uint32_t*)u32RegAddr) & RTC_ALMA_MSKH)? TRUE: FALSE;
    pstcAlarmTime->bAlarmMskM = ((*(uint32_t*)u32RegAddr) & RTC_ALMA_MSKM)? TRUE: FALSE;
    pstcAlarmTime->bAlarmMskS = ((*(uint32_t*)u32RegAddr) & RTC_ALMA_MSKS)? TRUE: FALSE;

    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        pstcAlarmTime->u8AlarmHour = u8Hour;
    }
    else
    {
        pstcAlarmTime->u8AlarmHour = u8Hour & 0x1fU;
        pstcAlarmTime->u8AmPm = (u8Hour & 0x20U)? 1U : 0U;
    }
}


/**
 * @brief  RTC闹钟设置.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @param  [in] pstcAlarmTime: 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval en_result_t:
 *         - Ok: 设置完成.
 *         - ErrorInvalidParameter: 设置失败，时间BCD格式不符合.
 */
en_result_t RTC_SetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime)
{
    en_result_t enRet = Ok;
    uint32_t u32RegValue;
    uint32_t u32Hour;
  
    if(Ok != RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmSec, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmMinute, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }

    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        enRet = RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmHour, 0x00U, 0x23U); /* 24H */
        u32Hour = pstcAlarmTime->u8AlarmHour;
    }
    else
    {
        enRet = RTC_CheckBCD_Format(pstcAlarmTime->u8AlarmHour&(~0x20U), 0x01U, 0x12U); /* 12H */
        u32Hour = pstcAlarmTime->u8AmPm? (pstcAlarmTime->u8AlarmHour | 0x20U): pstcAlarmTime->u8AlarmHour;
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }


    u32RegValue = (((uint32_t)pstcAlarmTime->u8AlarmSec << RTC_ALMA_SECL_Pos) | \
                    ((uint32_t)pstcAlarmTime->u8AlarmMinute << RTC_ALMA_MINL_Pos) | \
                    ((uint32_t)u32Hour << RTC_ALMA_HOURL_Pos) | \
                    ((uint32_t)pstcAlarmTime->u8AlarmDayOfWeek << RTC_ALMA_WEEK_Pos) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskS << RTC_ALMA_MSKS_Pos) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskM << RTC_ALMA_MSKM_Pos) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskH << RTC_ALMA_MSKH_Pos));

    if(RtcAlarmA == enAlarmX)
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMAE);      /* 闹钟禁止以后再设置闹钟时间 */
        HC_RTC->ALMA = u32RegValue;
        HC_RTC->CR2 |= RTC_CR2_ALMAE;
    }
    else
    {
        HC_RTC->CR2 &= (~RTC_CR2_ALMBE);      /* 闹钟禁止以后再设置闹钟时间 */
        HC_RTC->ALMB = u32RegValue;
        HC_RTC->CR2 |= RTC_CR2_ALMBE;
    }

    return Ok;
}



/**
 * @brief  RTC唤醒定时器使能.
 * @retval None.
 */
void RTC_WakeupTimerEnable(void)
{
    HC_RTC->CR2 |= RTC_CR2_WUTE;
}

/**
 * @brief  RTC唤醒定时器失能.
 * @retval None.
 */
void RTC_WakeupTimerDisable(void)
{
    HC_RTC->CR2 &= (~RTC_CR2_WUTE);
}

/**
 * @brief  RTC唤醒定时器时钟选择.
 * @retval None.
 */
void RTC_WakeupTimerClkSel(en_rtc_wucksel_t enWucksel)
{
    uint32_t u32RegValue;

    u32RegValue = HC_RTC->CR2 & (~RTC_CR2_WUCKSEL);
    HC_RTC->CR2 = u32RegValue | (uint32_t)enWucksel;
}


/**
 * @brief  RTC唤醒定时器设置周期值.
 * @param  [in] u16Arr: RTC唤醒定时器周期值
 * @retval None.
 */
void RTC_WakeupTimerSetArr(uint16_t u16Arr)
{
    HC_RTC->WUTARR = (uint32_t)u16Arr;
}

/**
 * @brief  RTC唤醒定时器获取周期值.
 * @retval uint16_t: RTC唤醒定时器周期值
 */
uint16_t RTC_WakeupTimerGetArr(void)
{
    return (uint16_t)HC_RTC->WUTARR;
}


/**
 * @brief  RTC时间戳使能.
 * @retval None.
 */
void RTC_TimestampEnable(void)
{
    HC_RTC->CR2 |= RTC_CR2_TSE;
}

/**
 * @brief  RTC时间戳失能.
 * @retval None.
 */
void RTC_TimestampDisable(void)
{
    HC_RTC->CR2 &= (~RTC_CR2_TSE);
}


/**
 * @brief  RTC时间戳边沿选择.
 * @param  [in] enEdge: RTC时间戳边沿选择 @ref en_rtc_tsedge_t
 * @retval None.
 */
void RTC_TimestampEdgeSel(en_rtc_tsedge_t enEdge)
{
    if(RtcTSFalling == enEdge)
    {
        HC_RTC->CR2 |= RTC_CR2_TSEDG;
    }
    else
    {
        HC_RTC->CR2 &= (~RTC_CR2_TSEDG);
    }  
}


/**
 * @brief  RTC时间戳时间读取.
 * @param  [in] pstcTs: RTC时间戳读取指针 @ref stc_rtc_ts_t
 * @retval None.
 */
void RTC_TimestampGet(stc_rtc_ts_t *pstcTs)
{
    uint8_t u8Hour;

    pstcTs->u8Second = (uint8_t)((HC_RTC->TSTR & (RTC_TSTR_SECL | RTC_TSTR_SECH)) >> RTC_TSTR_SECL_Pos);
    pstcTs->u8Minute = (uint8_t)((HC_RTC->TSTR & (RTC_TSTR_MINL | RTC_TSTR_MINH)) >> RTC_TSTR_MINL_Pos);
    u8Hour = (uint8_t)((HC_RTC->TSTR & (RTC_TSTR_HOURL | RTC_TSTR_HOURH)) >> RTC_TSTR_HOURL_Pos);
    pstcTs->u8DayOfWeek = (uint8_t)((HC_RTC->TSDR & RTC_TSDR_WEEK) >> RTC_TSDR_WEEK_Pos);
    pstcTs->u8Day = (uint8_t)((HC_RTC->TSDR & (RTC_TSDR_DAYL | RTC_TSDR_DAYH)) >> RTC_TSDR_DAYL_Pos);
    pstcTs->u8Month = (uint8_t)((HC_RTC->TSDR & RTC_TSDR_MON) >> RTC_TSDR_MON_Pos);

    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        pstcTs->u8Hour = u8Hour;
    }
    else
    {
        pstcTs->u8Hour = u8Hour & 0x1fU;
        pstcTs->u8AmPm = (u8Hour & 0x20U)? 1U : 0U;
    }
}


/**
 * @brief  RTC读取中断标志.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t RTC_GetIrqFlag(uint32_t u32IqrFlag)
{
    return (HC_RTC->IFR & u32IqrFlag)? TRUE: FALSE;
}


/**
 * @brief  RTC清除中断标志.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void RTC_ClearIrqFlag(uint32_t u32IqrFlag)
{
    HC_RTC->ICR = (~u32IqrFlag);
}

/**
 * @brief  RTC读取中断使能状态.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval boolean_t:
 *           - TRUE: 中断使能
 *           - FALSE: 中断未使能
 */
boolean_t RTC_GetIrqEn(uint32_t u32IqrFlag)
{
    return (HC_RTC->IER & u32IqrFlag)? TRUE: FALSE;
}


/**
 * @brief  RTC使能中断.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void RTC_EnableIrq(uint32_t u32IqrFlag)
{
    HC_RTC->IER |= u32IqrFlag;
}


/**
 * @brief  RTC禁用中断.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void RTC_DisableIrq(uint32_t u32IqrFlag)
{
    HC_RTC->IER &= (~u32IqrFlag);
}


/**
 * @brief  计算RTC误差补偿寄存器的值.
 * @param  [in] s16CompUnit: 补偿单位，取值范围 -275 ~ +213，1个单位为(1/32768)*10^6 /32 = 0.96ppm
 * @param  [out] pu16CompValue: 计算结果
 * @retval en_result_t:
 *           - Ok: 计算成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_CalcCompValue(int16_t s16CompUnit, uint16_t *pu16CompValue)
{
    uint16_t u16Res;
    int32_t s32Temp = s16CompUnit;

    if((s16CompUnit < -275) || (s16CompUnit > 213))
    {
        return ErrorInvalidParameter;
    }
    s32Temp = (s32Temp * 32768 * 32 / 1000000) + 32;
    u16Res = (uint16_t)s32Temp;
    u16Res &= 0x1ffU;
    *pu16CompValue = u16Res;

    return Ok;
}


/**
 * @brief  配置RTC的误差补偿寄存器.
 * @param  [in] u16CompValue: 数值的范围为：0-511
 * @param  [in] NewStatus: RtcCompenDisable 或 RtcAmCompenEnable @ref en_rtc_compen_t
 * @retval en_result_t:
 *           - Ok: 设置成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t RTC_CompCfg(uint16_t u16CompValue, en_rtc_compen_t NewStatus)
{
    if(u16CompValue > 0x1ffU)
    {
        return ErrorInvalidParameter;
    }
    else
    {
        HC_RTC->COMPEN_f.EN = NewStatus;
        HC_RTC->COMPEN_f.CR = u16CompValue;
    }

    return Ok;
}


/**
 * @brief  RTC获取时间函数.
 * @param  [in] pstcDateTime: 用于存放读取日期时间的指针 @ref stc_rtc_time_t
 * @retval int32_t:
 *           - Ok: 获取正常
 *           - ErrorTimeout: 超时错误
 */
en_result_t RTC_ReadDateTime(stc_rtc_time_t* pstcDateTime)
{
    uint32_t u32TimeOut;

    ASSERT(NULL != pstcDateTime);  
    
    if(1U == HC_RTC->CR0_f.START)
    {
        HC_RTC->CR1_f.WAIT = 1U;
        u32TimeOut = 1000U;
        while(FALSE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
		}
    }
    pstcDateTime->u8Second  = (uint8_t)HC_RTC->SEC;
    pstcDateTime->u8Minute  = (uint8_t)HC_RTC->MIN;
    if(1U == HC_RTC->CR0_f.AMPM)
    {
        pstcDateTime->u8Hour   = (uint8_t)HC_RTC->HOUR;
    }
    else
    {
        pstcDateTime->u8Hour   = (uint8_t)HC_RTC->HOUR & 0x1fU;
        pstcDateTime->u8AmPm = ((HC_RTC->HOUR & 0x20U)? 1U : 0U);
    }
    pstcDateTime->u8Day       = (uint8_t)HC_RTC->DAY;
    pstcDateTime->u8DayOfWeek = (uint8_t)HC_RTC->WEEK;
    pstcDateTime->u8Month     = (uint8_t)HC_RTC->MON;
    pstcDateTime->u8Year      = (uint8_t)HC_RTC->YEAR;

    HC_RTC->CR1_f.WAIT = 0U;
    if(1U == HC_RTC->CR0_f.START)
    {
        u32TimeOut = 1000U;
        while(TRUE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
    }
    
    return Ok;
}


/**
 * @brief  向RTC时间寄存器写入时间.
 * @param  [in] pstcDateTime: 用于存放读取日期时间的指针 @ref stc_rtc_time_t
 * @retval en_result_t:
 *           - Ok: 写入正常
 *           - ErrorInvalidParameter: 参数错误
 *           - ErrorTimeout: 时间溢出错误
 */
en_result_t RTC_SetDateTime(stc_rtc_time_t* pstcDateTime)
{
    en_result_t enRet = Ok;
    uint32_t u32TimeOut;
    uint8_t u8MonthIndex;
    
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Second, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Minute, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Month, 0x01U, 0x12U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8Year, 0x00U, 0x99U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != RTC_CheckBCD_Format(pstcDateTime->u8DayOfWeek, 0x00U, 0x06U))
    {
        return ErrorInvalidParameter;
    }
    u8MonthIndex = ((pstcDateTime->u8Month & 0x10U)? 10U: 0U) + (pstcDateTime->u8Month & 0x0fU) - 1U;
    if(pstcDateTime->u8Month == 0x02U)
    {
        if(RTC_IsLeapYear(pstcDateTime->u8Year))
        {
            enRet = RTC_CheckBCD_Format(pstcDateTime->u8Day, 0x01U, 0x29U); /*!< 闰年2月 */
        }
        else
        {
            enRet = RTC_CheckBCD_Format(pstcDateTime->u8Day, 0x01U, 0x28U); /*!< 平年2月 */
        }
    }
    else
    {
        enRet = RTC_CheckBCD_Format(pstcDateTime->u8Day, 0x01U, Cnst_Month_Tbl[u8MonthIndex]);
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }
    if(RtcAmpm24H == HC_RTC->CR0_f.AMPM)
    {
        enRet = RTC_CheckBCD_Format(pstcDateTime->u8Hour, 0x00U, 0x23U); /*!< 24H */
    }
    else
    {
        enRet = RTC_CheckBCD_Format(pstcDateTime->u8Hour&(~0x20U), 0x01U, 0x12U); /*!< 12H */
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }


    if(HC_RTC->CR0_f.START == 1U)
    {
        HC_RTC->CR1_f.WAIT = 1U;
        u32TimeOut = 1000U;
        while(FALSE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
		}
    }
    HC_RTC->SEC   = pstcDateTime->u8Second;
    HC_RTC->MIN   = pstcDateTime->u8Minute;
    if(1U == HC_RTC->CR0_f.AMPM)
    {
        HC_RTC->HOUR  = pstcDateTime->u8Hour;
    }
    else
    {
        HC_RTC->HOUR  = (uint32_t)pstcDateTime->u8Hour | ((uint32_t)pstcDateTime->u8AmPm<<5U);
    }
    HC_RTC->DAY   = pstcDateTime->u8Day;
    HC_RTC->MON   = pstcDateTime->u8Month;
    HC_RTC->YEAR  = pstcDateTime->u8Year;
    HC_RTC->WEEK  = pstcDateTime->u8DayOfWeek;

    HC_RTC->CR1_f.WAIT = 0U;
    if(HC_RTC->CR0_f.START == 1U)
    {
        u32TimeOut = 1000U;
        while(TRUE == HC_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
    }
    enRet = Ok;
    return enRet;
}


/**
 * @brief  读取RTC当前的时间格式 12小时制或者24小时制.
 * @retval en_rtc_ampm_t：  @ref en_rtc_ampm_t
 *           - RtcAmpm12H: 12小时制
 *           - RtcAmpm24H: 24小时制
 */
en_rtc_ampm_t RTC_GetAmpmFormat(void)
{
    return (HC_RTC->CR0 & RTC_CR0_AMPM)? RtcAmpm24H : RtcAmpm12H;
}


/**
 * @brief  初始化RTC.
 * @param  [in] pstcRtcInit: 初始化结构体指针 @ref stc_rtc_initstruct_t
 * @retval None.
 */
void RTC_Init(stc_rtc_initstruct_t* pstcRtcInit)
{
    HC_RTC->CR0 &= (~RTC_CR0_START);                /* 计数停止 */
    HC_RTC->CR0_f.AMPM = pstcRtcInit->enAmpm;        /* 实时时钟小时的时制 */
    HC_RTC->CR1_f.CKSEL = pstcRtcInit->enClksrc;      /* 实时时钟RTC的时钟源 */
    HC_RTC->CR0 |= RTC_CR0_START;                /* 计数开始 */
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
