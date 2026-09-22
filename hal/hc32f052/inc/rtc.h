/**
 *******************************************************************************
 * @file  rtc.h
 * @brief This file contains all the functions prototypes of the RTC driver
 *        library.
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
#ifndef __RTC_H__
#define __RTC_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_RTC RTC模块驱动库
 * @{
 */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup RTC_Global_Macros RTC全局宏定义
 * @{
 */
/**
 * @defgroup RTC_AlarmDayOfWeek_Sel  RTC闹钟周内选择
 * @{
 */
#define RTC_ALMWEEK_SUNDAY          (0x01U) /*!< 周日 */
#define RTC_ALMWEEK_MONDAY          (0x02U) /*!< 周一 */
#define RTC_ALMWEEK_TUESDAY         (0x04U) /*!< 周二 */
#define RTC_ALMWEEK_WEDNESDAY       (0x08U) /*!< 周三 */
#define RTC_ALMWEEK_THURSDAY        (0x10U) /*!< 周四 */
#define RTC_ALMWEEK_FRIDAY          (0x20U) /*!< 周无 */
#define RTC_ALMWEEK_SATURDAY        (0x40U) /*!< 周六 */
#define RTC_ALMWEEK_ALL             (0x7FU) /*!< 一周全选 */
/**
 * @}
 */

/**
 * @defgroup RTC_IRQ_Flag  RTC中断标志
 * @{
 */
#define RTC_IRQ_ALMA        RTC_IER_ALMA    /*!< 闹钟A */
#define RTC_IRQ_ALMB        RTC_IER_ALMB    /*!< 闹钟B */
#define RTC_IRQ_WU          RTC_IER_WU      /*!< 定时唤醒中断 */
#define RTC_IRQ_TS          RTC_IER_TS      /*!< 时间戳中断 */
#define RTC_IRQ_TSOV        RTC_IER_TSOV    /*!< 时间戳溢出中断 */
#define RTC_IRQ_PRD         RTC_IER_PRD     /*!< 周期中断 */
#define RTC_IRQ_ALL         (RTC_IER_ALMA | \
                            RTC_IER_ALMB | \
                            RTC_IER_WU | \
                            RTC_IER_TS | \
                            RTC_IER_TSOV | \
                            RTC_IER_PRD)    /*!< 所有中断 */
/**
 * @}
 */


/**
 * @}
 */
/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Types RTC全局类型定义
 * @{
 */
/**
 * @brief  rtc周期中断的时间间隔 RTC_CR0 PRDS
 */
typedef enum
{
    RtcNone   = 0u, /*!< 无周期中断 */
    Rtc05S    = 1u, /*!< 0.5S中断 */
    Rtc1S     = 2u, /*!< 1秒 */
    Rtc1Min   = 3u, /*!< 1分钟 */
    Rtc1H     = 4u, /*!< 1小时 */
    Rtc1Day   = 5u, /*!< 1天 */
    Rtc1Mon   = 6u  /*!< 1月 */
}en_rtc_prds_t;


/**
 * @brief  rtc 12h制或24h制方式选择 RTC_CR0  AMPM
 */
typedef enum
{
    RtcAmpm12H = 0u,     /*!< 12小时制 */
    RtcAmpm24H = 1u      /*!< 24小时制 */
}en_rtc_ampm_t;

/**
 * @brief  普通精度与高精度1Hz输出  RTC_CR0  HZ1SEL
 */
typedef enum
{
    RtcHz1selGeneralPricision = 0u,    /*!< 普通精度1Hz输出 */
    RtcHz1selHighPricision = 1u        /*!< 高精度1Hz输出 */
}en_rtc_hz1sel_t;

/**
 * @brief  周期中断选择   RTC_CR0  PRDSEL
 */
typedef enum
{
    RtcPrds = 0u,   /*!< 使用PRDS所设定的周期中断事件间隔 */
    RtcPrdx = 1u    /*!< 使用PRDX所设定的周期中断事件间隔 */
}en_rtc_prdsel_t;

/**
 * @brief  rtc的时钟选择   RTC_CR1  CKSEL
 */
typedef enum 
{
    RtcClkXtl      = 0u, /*!< 外部低速时钟XTL  32.768k */ 
    RtcClkRcl      = 2u, /*!< 内部低速时钟RCL  32k     */
    RtcClkXth128   = 4u, /*!< 外部晶振4M       XTH/128 */
    RtcClkXth256   = 5u, /*!< 外部晶振8M       XTH/256 */
    RtcClkXth512   = 6u, /*!< 外部晶振16M      XTH/512 */
    RtcClkXth1024  = 7u  /*!< 外部晶振32M      XTH/1024 */
}en_rtc_cksel_t;

/**
 * @brief  时钟误差补偿使能或禁止   RTC_COMPEN  EN
 */
typedef enum
{
    RtcCompenDisable = 0u, /*!< 禁止时钟误差补偿 */
    RtcCompenEnable  = 1u  /*!< 使能时钟误差补偿 */
}en_rtc_compen_t;

/**
 * @brief  配置PRD中断使能及其周期类型
 */
typedef struct
{
    en_rtc_prdsel_t enPrdsel; /*!< 时钟周期选择  @ref en_rtc_prdsel_t */
    uint8_t         u8Prdx;   /*!< 0~63,设置产生周期中断的时间间隔，(rtcPrdx + 1)*0.5s */
    en_rtc_prds_t   enPrds;   /*!< rtc周期中断的时间间隔  @ref en_rtc_prds_t */
}stc_rtc_prdcfg_t;

/**
 * @brief  闹钟时间配置
 */
typedef struct
{
    uint8_t  u8AlarmSec;    /*!< 闹钟秒钟 BCD码 */
    uint8_t  u8AlarmMinute; /*!< 闹钟分钟 BCD码 */
    uint8_t  u8AlarmHour;   /*!< 闹钟小时 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
    uint8_t  u8AlarmDayOfWeek;   /*!< 闹钟星期选择 @ref RTC_AlarmDayOfWeek_Sel */
    boolean_t bAlarmMskH; /*!< 闹钟小时屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与时位无关 */
    boolean_t bAlarmMskM; /*!< 闹钟分屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与分位无关 */
    boolean_t bAlarmMskS; /*!< 闹钟秒屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与秒位无关 */
}stc_rtc_alarmtime_t;

/**
 * @brief  闹钟通道
 */
typedef enum
{
    RtcAlarmA = 0, /*!< 闹钟A */
    RtcAlarmB = 1, /*!< 闹钟B */
}en_rtc_alarmch_t;


/**
 * @brief  唤醒定时器时钟选择
 */
typedef enum
{
    RtcWuckRTC_Div2 = 0,    /*!< RTC/2 */
    RtcWuckRTC_Div4 = 1,    /*!< RTC/4 */
    RtcWuckRTC_Div8 = 2,    /*!< RTC/8 */
    RtcWuckRTC_Div16 = 3,   /*!< RTC/16 */
    RtcWuckRTC_SecDiv1 = 4, /*!< RTC_Sec/1 */
    RtcWuckRTC_SecDiv2 = 5, /*!< RTC_Sec/2 */
    RtcWuckRTC_SecDiv4 = 6, /*!< RTC_Sec/4 */
    RtcWuckRTC_SecDiv8 = 7, /*!< RTC_Sec/8 */
}en_rtc_wucksel_t;

/**
 * @brief  时间戳边沿选择
 */
typedef enum
{
    RtcTSRising = 0,  /*!< 上升沿 */
    RtcTSFalling = 1, /*!< 下降沿 */
}en_rtc_tsedge_t;

/**
 * @brief  rtc时钟时间戳结构
 */
typedef struct
{
    uint8_t  u8Second;      /*!< 时间：秒 BCD码 */
    uint8_t  u8Minute;      /*!< 时间：分 BCD码 */
    uint8_t  u8Hour;        /*!< 时间：时 BCD码 */
    uint8_t  u8DayOfWeek;   /*!< 时间：周 BCD码 */
    uint8_t  u8Day;         /*!< 时间：日 BCD码 */    
    uint8_t  u8Month;       /*!< 时间：月 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
} stc_rtc_ts_t;

/**
 * @brief  rtc时钟年、月、日、时、分、秒读写结构
 */
typedef struct
{
    uint8_t  u8Second;      /*!< 时间：秒 BCD码 */
    uint8_t  u8Minute;      /*!< 时间：分 BCD码 */
    uint8_t  u8Hour;        /*!< 时间：时 BCD码 */
    uint8_t  u8DayOfWeek;   /*!< 时间：周 BCD码 */
    uint8_t  u8Day;         /*!< 时间：日 BCD码 */    
    uint8_t  u8Month;       /*!< 时间：月 BCD码 */
    uint8_t  u8Year;        /*!< 时间：年 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
} stc_rtc_time_t;

/**
 * @brief  初始化RTC的结构体
 */
typedef struct
{
    en_rtc_ampm_t         enAmpm;      /*!< 小时的时制 */
    en_rtc_cksel_t        enClksrc;    /*!< 实时时钟的时钟源 */
}stc_rtc_initstruct_t;


/**
 * @}
 */
/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup RTC_Global_Functions RTC全局函数定义
 * @{
 */
void RTC_Unlock(void);
void RTC_Lock(void);

void RTC_Cmd(boolean_t NewState);
void RTC_StartWait(void);
void RTC_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState);

en_result_t RTC_PrdCfg(stc_rtc_prdcfg_t* pstcPrd);

void RTC_AlarmEnalbe(en_rtc_alarmch_t enAlarmX);
void RTC_AlarmDisalbe(en_rtc_alarmch_t enAlarmX);
void RTC_GetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime);
en_result_t RTC_SetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime);

void RTC_WakeupTimerEnable(void);
void RTC_WakeupTimerDisable(void);
void RTC_WakeupTimerClkSel(en_rtc_wucksel_t enWucksel);
void RTC_WakeupTimerSetArr(uint16_t u16Arr);
uint16_t RTC_WakeupTimerGetArr(void);

void RTC_TimestampEnable(void);
void RTC_TimestampDisable(void);
void RTC_TimestampEdgeSel(en_rtc_tsedge_t enEdge);
void RTC_TimestampGet(stc_rtc_ts_t *pstcTs);

boolean_t RTC_GetIrqFlag(uint32_t u32IqrFlag);
void RTC_ClearIrqFlag(uint32_t u32IqrFlag);
boolean_t RTC_GetIrqEn(uint32_t u32IqrFlag);
void RTC_EnableIrq(uint32_t u32IqrFlag);
void RTC_DisableIrq(uint32_t u32IqrFlag);

en_result_t RTC_CalcCompValue(int16_t s16CompUnit, uint16_t *pu16CompValue);
en_result_t RTC_CompCfg(uint16_t u16CompValue, en_rtc_compen_t NewStatus);
en_result_t RTC_ReadDateTime(stc_rtc_time_t* pstcDateTime);
en_result_t RTC_SetDateTime(stc_rtc_time_t* pstcDateTime);
en_rtc_ampm_t RTC_GetAmpmFormat(void);
void RTC_Init(stc_rtc_initstruct_t* pstcRtcInit);


/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/    


