/**
 *******************************************************************************
 * @file  HC32A052.h
 * @brief Headerfile for HC32A052 series MCU.
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

#ifndef __HC32A052_H__
#define __HC32A052_H__

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Configuration of the Cortex-M0+ Processor and Core Peripherals
 ******************************************************************************/
#define __MPU_PRESENT 0          /* No MPU                                       */
#define __NVIC_PRIO_BITS 2       /* M0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig 0 /* Set to 1 if different SysTick Config is used */
    /** @} */                    /* End of group Configuration_of_CMSIS */

    /******************************************************************************
     * Interrupt Number Definition
     ******************************************************************************/
    typedef enum IRQn
    {
        NMI_IRQn = -14,       /*  2 Non Maskable                            */
        HardFault_IRQn = -13, /*  3 Hard Fault                              */
        SVC_IRQn = -5,        /* 11 SV Call                                 */
        PendSV_IRQn = -2,     /* 14 Pend SV                                 */
        SysTick_IRQn = -1,    /* 15 System Tick                             */

        PORTA_IRQn = 0,
        PORTB_IRQn = 1,
        PORTC_IRQn = 2,
        PORTD_IRQn = 3,
        DMAC_IRQn = 4,
        ATIM3_IRQn = 5,
        USART0_IRQn = 6,
        USART1_IRQn = 7,
        LPUART0_IRQn = 8,
        LPUART1_IRQn = 9,
        SPI0_IRQn = 10,
        SPI1_IRQn = 11,
        I2C0_IRQn = 12,
        I2C1_IRQn = 13,
        ATIM0_IRQn = 14,
        ATIM1_IRQn = 15,
        ATIM2_IRQn = 16,
        LPTIM_IRQn = 17,
        GTIM0_BTIM0_1_2_IRQn = 18,
        GTIM1_BTIM3_4_5_IRQn = 19,
        I2CSLV_IRQn = 20,
        WWDT_IRQn = 21,
        IWDT_IRQn = 22,
        RTC_IRQn = 23,
        ADC_IRQn = 24,
        VC0_VC1_LVD_IRQn = 26,
        CAN_IRQn = 28,
        ATIM_BK_IRQn = 29,
        FLASH_RAM_IRQn = 30,
        CTRIM_IRQn = 31,

    } IRQn_Type;

#include <core_cm0plus.h>
#include <stdint.h>

#define SUCCESS (0)
#define ERROR (-1)

#ifndef NULL
#define NULL (0)
#endif

    /******************************************************************************/
    /*                Device Specific Peripheral Registers structures             */
    /******************************************************************************/

#if defined(__CC_ARM)
#pragma anon_unions
#endif

    typedef struct
    {
        __IO uint32_t BGREN : 1;
        __IO uint32_t TSEN : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_adc_bgr_field_t;

    typedef struct
    {
        __IO uint32_t EN : 1;
        __IO uint32_t CKDIV : 3;
        __IO uint32_t SGLMUX : 5;
        __IO uint32_t REF : 2;
        __IO uint32_t BUF : 1;
        __IO uint32_t SAM : 2;
        uint32_t RESERVED14 : 17;
        __IO uint32_t RSV : 1;
    } stc_adc_cr0_field_t;

    typedef struct
    {
        __IO uint32_t MODE : 2;
        __IO uint32_t ALIGN : 1;
        __IO uint32_t THCH : 5;
        uint32_t RESERVED8 : 2;
        __IO uint32_t OVMD : 1;
        __IO uint32_t RACCEN : 1;
        __IO uint32_t LTCMP : 1;
        __IO uint32_t HTCMP : 1;
        __IO uint32_t REGCMP : 1;
        __IO uint32_t RACCCLR : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_cr1_field_t;

    typedef struct
    {
        __IO uint32_t ESG : 1;
        __IO uint32_t LTI : 1;
        __IO uint32_t HTI : 1;
        __IO uint32_t RGI : 1;
        __IO uint32_t EOS : 1;
        __IO uint32_t EOJ : 1;
        __IO uint32_t EOC : 1;
        __IO uint32_t DEOC : 1;
        __IO uint32_t DEOJ : 1;
        __IO uint32_t OV : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_adc_ier_field_t;

    typedef struct
    {
        __IO uint32_t CH0MUX : 5;
        __IO uint32_t CH1MUX : 5;
        __IO uint32_t CH2MUX : 5;
        __IO uint32_t CH3MUX : 5;
        __IO uint32_t CH4MUX : 5;
        __IO uint32_t CH5MUX : 5;
        uint32_t RESERVED30 : 1;
        __IO uint32_t RSV : 1;
    } stc_adc_sqr0_field_t;

    typedef struct
    {
        __IO uint32_t CH6MUX : 5;
        __IO uint32_t CH7MUX : 5;
        __IO uint32_t CH8MUX : 5;
        __IO uint32_t CH9MUX : 5;
        __IO uint32_t CH10MUX : 5;
        __IO uint32_t CH11MUX : 5;
        uint32_t RESERVED30 : 1;
        __IO uint32_t RSV : 1;
    } stc_adc_sqr1_field_t;

    typedef struct
    {
        __IO uint32_t CH12MUX : 5;
        __IO uint32_t CH13MUX : 5;
        __IO uint32_t CH14MUX : 5;
        __IO uint32_t CH15MUX : 5;
        __IO uint32_t CNT : 4;
        uint32_t RESERVED24 : 7;
        __IO uint32_t RSV : 1;
    } stc_adc_sqr2_field_t;

    typedef struct
    {
        __IO uint32_t CH0MUX : 5;
        __IO uint32_t CH1MUX : 5;
        __IO uint32_t CH2MUX : 5;
        __IO uint32_t CH3MUX : 5;
        __IO uint32_t CNT : 2;
        uint32_t RESERVED22 : 9;
        __IO uint32_t RSV : 1;
    } stc_adc_jqr_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_sqrresult0_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_sqrresult1_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_sqrresult2_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_sqrresult3_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_jqrresult0_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_jqrresult1_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_jqrresult2_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_jqrresult3_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_adc_result_field_t;

    typedef struct
    {
        __IO uint32_t RESULTACC : 20;
        uint32_t RESERVED20 : 11;
        __IO uint32_t RSV : 1;
    } stc_adc_resultacc_field_t;

    typedef struct
    {
        __IO uint32_t HT : 12;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_adc_ht_field_t;

    typedef struct
    {
        __IO uint32_t LT : 12;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_adc_lt_field_t;

    typedef struct
    {
        __IO uint32_t ESG : 1;
        __IO uint32_t LTI : 1;
        __IO uint32_t HTI : 1;
        __IO uint32_t RGI : 1;
        __IO uint32_t EOS : 1;
        __IO uint32_t EOJ : 1;
        __IO uint32_t EOC : 1;
        uint32_t RESERVED7 : 2;
        __IO uint32_t OV : 1;
        __IO uint32_t RDY : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_adc_ifr_field_t;

    typedef struct
    {
        __IO uint32_t ESG : 1;
        __IO uint32_t LTI : 1;
        __IO uint32_t HTI : 1;
        __IO uint32_t RGI : 1;
        __IO uint32_t EOS : 1;
        __IO uint32_t EOJ : 1;
        __IO uint32_t EOC : 1;
        uint32_t RESERVED7 : 2;
        __IO uint32_t OV : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_adc_icr_field_t;

    typedef struct
    {
        __IO uint32_t TRIG : 5;
        __IO uint32_t DELAY : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_adc_exttrig0_field_t;

    typedef struct
    {
        __IO uint32_t TRIG : 5;
        __IO uint32_t DELAY : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_adc_exttrig1_field_t;

    typedef struct
    {
        __IO uint32_t START : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_adc_sglstart_field_t;

    typedef struct
    {
        __IO uint32_t START : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_adc_sqrstart_field_t;

    typedef struct
    {
        __IO uint32_t START : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_adc_jqrstart_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_arr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_cnt_field_t;

    typedef struct
    {
        __IO uint32_t CTEN : 1;
        __IO uint32_t COMP : 1;
        __IO uint32_t CT : 1;
        __IO uint32_t PWM2S : 1;
        __IO uint32_t PRS : 3;
        __IO uint32_t BUFPEN : 1;
        __IO uint32_t CRG : 1;
        __IO uint32_t CFG : 1;
        __IO uint32_t UIE : 1;
        __IO uint32_t UDE : 1;
        __IO uint32_t MODE : 2;
        __IO uint32_t ONESHOT : 1;
        __IO uint32_t CSG : 1;
        __IO uint32_t OCCS : 1;
        __IO uint32_t URS : 1;
        __IO uint32_t TDE : 1;
        __IO uint32_t TIE : 1;
        __IO uint32_t BIE : 1;
        __IO uint32_t CIS : 2;
        __IO uint32_t OCCE : 1;
        __IO uint32_t TG : 1;
        __IO uint32_t UG : 1;
        __IO uint32_t BG : 1;
        __IO uint32_t DIR : 1;
        __IO uint32_t OVE : 1;
        __IO uint32_t UNDE : 1;
        uint32_t RESERVED30 : 1;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_m23cr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t CA0 : 1;
        __IO uint32_t CA1 : 1;
        __IO uint32_t CA2 : 1;
        __IO uint32_t CB0 : 1;
        __IO uint32_t CB1 : 1;
        __IO uint32_t CB2 : 1;
        __IO uint32_t CA0E : 1;
        __IO uint32_t CA1E : 1;
        __IO uint32_t CA2E : 1;
        __IO uint32_t CB0E : 1;
        __IO uint32_t CB1E : 1;
        __IO uint32_t CB2E : 1;
        __IO uint32_t BI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t UND : 1;
        __IO uint32_t CA3A : 1;
        __IO uint32_t CA3B : 1;
        uint32_t RESERVED20 : 11;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ifr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t CA0 : 1;
        __IO uint32_t CA1 : 1;
        __IO uint32_t CA2 : 1;
        __IO uint32_t CB0 : 1;
        __IO uint32_t CB1 : 1;
        __IO uint32_t CB2 : 1;
        __IO uint32_t CA0E : 1;
        __IO uint32_t CA1E : 1;
        __IO uint32_t CA2E : 1;
        __IO uint32_t CB0E : 1;
        __IO uint32_t CB1E : 1;
        __IO uint32_t CB2E : 1;
        __IO uint32_t BI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t UND : 1;
        __IO uint32_t CA3A : 1;
        __IO uint32_t CA3B : 1;
        uint32_t RESERVED20 : 11;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_iclr_field_t;

    typedef struct
    {
        __IO uint32_t MMS : 3;
        __IO uint32_t CCDS : 1;
        __IO uint32_t MSM : 1;
        __IO uint32_t TS : 3;
        __IO uint32_t SMS : 3;
        __IO uint32_t IA0S : 1;
        __IO uint32_t IB0S : 1;
        uint32_t RESERVED13 : 18;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_mscr_field_t;

    typedef struct
    {
        __IO uint32_t OCMA0FLTA0 : 3;
        __IO uint32_t CCPA0 : 1;
        __IO uint32_t OCMB0FLTB0 : 3;
        __IO uint32_t CCPB0 : 1;
        __IO uint32_t OCMA1FLTA1 : 3;
        __IO uint32_t CCPA1 : 1;
        __IO uint32_t OCMB1FLTB1 : 3;
        __IO uint32_t CCPB1 : 1;
        __IO uint32_t OCMA2FLTA2 : 3;
        __IO uint32_t CCPA2 : 1;
        __IO uint32_t OCMB2FLTB2 : 3;
        __IO uint32_t CCPB2 : 1;
        __IO uint32_t FLTBK : 3;
        __IO uint32_t BKP : 1;
        __IO uint32_t FLTET : 3;
        __IO uint32_t ETP : 1;
    } stc_atim3mode23_fltr_field_t;

    typedef struct
    {
        __IO uint32_t UEVE : 1;
        __IO uint32_t CMA0E : 1;
        __IO uint32_t CMA1E : 1;
        __IO uint32_t CMA2E : 1;
        __IO uint32_t CMB0E : 1;
        __IO uint32_t CMB1E : 1;
        __IO uint32_t CMB2E : 1;
        __IO uint32_t ADTE : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_adtr_field_t;

    typedef struct
    {
        __IO uint32_t CFACRABKSA : 2;
        __IO uint32_t CFBCRBBKSB : 2;
        __IO uint32_t CSA : 1;
        __IO uint32_t CSB : 1;
        __IO uint32_t BUFEA : 1;
        __IO uint32_t BUFEB : 1;
        __IO uint32_t CIEA : 1;
        __IO uint32_t CIEB : 1;
        __IO uint32_t CDEA : 1;
        __IO uint32_t CDEB : 1;
        __IO uint32_t CISB : 2;
        __IO uint32_t CCGA : 1;
        __IO uint32_t CCGB : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_crch0_field_t;

    typedef struct
    {
        __IO uint32_t CFACRABKSA : 2;
        __IO uint32_t CFBCRBBKSB : 2;
        __IO uint32_t CSA : 1;
        __IO uint32_t CSB : 1;
        __IO uint32_t BUFEA : 1;
        __IO uint32_t BUFEB : 1;
        __IO uint32_t CIEA : 1;
        __IO uint32_t CIEB : 1;
        __IO uint32_t CDEA : 1;
        __IO uint32_t CDEB : 1;
        __IO uint32_t CISB : 2;
        __IO uint32_t CCGA : 1;
        __IO uint32_t CCGB : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_crch1_field_t;

    typedef struct
    {
        __IO uint32_t CFACRABKSA : 2;
        __IO uint32_t CFBCRBBKSB : 2;
        __IO uint32_t CSA : 1;
        __IO uint32_t CSB : 1;
        __IO uint32_t BUFEA : 1;
        __IO uint32_t BUFEB : 1;
        __IO uint32_t CIEA : 1;
        __IO uint32_t CIEB : 1;
        __IO uint32_t CDEA : 1;
        __IO uint32_t CDEB : 1;
        __IO uint32_t CISB : 2;
        __IO uint32_t CCGA : 1;
        __IO uint32_t CCGB : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_crch2_field_t;

    typedef struct
    {
        __IO uint32_t DTR : 8;
        __IO uint32_t BKSEL : 1;
        __IO uint32_t DTEN : 1;
        __IO uint32_t BKE : 1;
        __IO uint32_t AOE : 1;
        __IO uint32_t MOE : 1;
        __IO uint32_t SAFEEN : 1;
        __IO uint32_t VCE : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_dtr_field_t;

    typedef struct
    {
        __IO uint32_t RCR : 8;
        __IO uint32_t OV : 1;
        __IO uint32_t UD : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_rcr_field_t;

    typedef struct
    {
        __IO uint32_t CCR0A : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr0a_field_t;

    typedef struct
    {
        __IO uint32_t CCR0B : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr0b_field_t;

    typedef struct
    {
        __IO uint32_t CCR1A : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr1a_field_t;

    typedef struct
    {
        __IO uint32_t CCR1B : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr1b_field_t;

    typedef struct
    {
        __IO uint32_t CCR2A : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr2a_field_t;

    typedef struct
    {
        __IO uint32_t CCR2B : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr2b_field_t;

    typedef struct
    {
        __IO uint32_t CCR3A : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr3a_field_t;

    typedef struct
    {
        __IO uint32_t BUF : 1;
        __IO uint32_t CI : 1;
        __IO uint32_t CD : 1;
        __IO uint32_t CIS : 2;
        __IO uint32_t C3AEN : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_crch3a_field_t;

    typedef struct
    {
        __IO uint32_t CCR3B : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_ccr3b_field_t;

    typedef struct
    {
        __IO uint32_t BUF : 1;
        __IO uint32_t CI : 1;
        __IO uint32_t CD : 1;
        __IO uint32_t CIS : 2;
        __IO uint32_t C3BEN : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_atim3mode23_crch3b_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode0_arr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode0_cnt_field_t;

    typedef struct
    {
        __IO uint32_t CNT32 : 32;
    } stc_atimmode0_cnt32_field_t;

    typedef struct
    {
        __IO uint32_t CTEN : 1;
        __IO uint32_t MD : 1;
        __IO uint32_t CT : 1;
        __IO uint32_t TOGEN : 1;
        __IO uint32_t PRS : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t GATE : 1;
        __IO uint32_t GATEP : 1;
        __IO uint32_t UIE : 1;
        uint32_t RESERVED11 : 1;
        __IO uint32_t MODE : 2;
        uint32_t RESERVED14 : 17;
        __IO uint32_t RSV : 1;
    } stc_atimmode0_m0cr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_atimmode0_ifr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_atimmode0_iclr_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 12;
        __IO uint32_t MOE : 1;
        uint32_t RESERVED13 : 18;
        __IO uint32_t RSV : 1;
    } stc_atimmode0_dtr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_cnt_field_t;

    typedef struct
    {
        __IO uint32_t CTEN : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t CT : 1;
        uint32_t RESERVED3 : 1;
        __IO uint32_t PRS : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t EDG1ST : 1;
        __IO uint32_t EDG2ND : 1;
        __IO uint32_t UIE : 1;
        uint32_t RESERVED11 : 1;
        __IO uint32_t MODE : 2;
        __IO uint32_t ONESHOT : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_m1cr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t PWC : 1;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_ifr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t PWC : 1;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_iclr_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 5;
        __IO uint32_t TS : 3;
        uint32_t RESERVED8 : 3;
        __IO uint32_t IA0S : 1;
        __IO uint32_t IB0S : 1;
        uint32_t RESERVED13 : 18;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_mscr_field_t;

    typedef struct
    {
        __IO uint32_t FLTA0 : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t FLTB0 : 3;
        uint32_t RESERVED7 : 21;
        __IO uint32_t FLTET : 3;
        __IO uint32_t ETP : 1;
    } stc_atimmode1_fltr_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 4;
        __IO uint32_t CSA : 1;
        __IO uint32_t CSB : 1;
        uint32_t RESERVED6 : 2;
        __IO uint32_t CIEA : 1;
        uint32_t RESERVED9 : 22;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_cr0_field_t;

    typedef struct
    {
        __IO uint32_t CCR0A : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode1_ccr0a_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_arr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_cnt_field_t;

    typedef struct
    {
        __IO uint32_t CTEN : 1;
        __IO uint32_t COMP : 1;
        __IO uint32_t CT : 1;
        __IO uint32_t PWM2S : 1;
        __IO uint32_t PRS : 3;
        __IO uint32_t BUFPEN : 1;
        __IO uint32_t CRG : 1;
        __IO uint32_t CFG : 1;
        __IO uint32_t UIE : 1;
        __IO uint32_t UDE : 1;
        __IO uint32_t MODE : 2;
        __IO uint32_t ONESHOT : 1;
        __IO uint32_t CSG : 1;
        __IO uint32_t OCCS : 1;
        __IO uint32_t URS : 1;
        __IO uint32_t TDE : 1;
        __IO uint32_t TIE : 1;
        __IO uint32_t BIE : 1;
        __IO uint32_t CIS : 2;
        __IO uint32_t OCCE : 1;
        __IO uint32_t TG : 1;
        __IO uint32_t UG : 1;
        __IO uint32_t BG : 1;
        __IO uint32_t DIR : 1;
        __IO uint32_t OVE : 1;
        __IO uint32_t UNDE : 1;
        uint32_t RESERVED30 : 1;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_m23cr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t CA0 : 1;
        uint32_t RESERVED3 : 2;
        __IO uint32_t CB0 : 1;
        uint32_t RESERVED6 : 2;
        __IO uint32_t CA0E : 1;
        uint32_t RESERVED9 : 2;
        __IO uint32_t CB0E : 1;
        uint32_t RESERVED12 : 2;
        __IO uint32_t BI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t UND : 1;
        uint32_t RESERVED18 : 13;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_ifr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t CA0 : 1;
        uint32_t RESERVED3 : 2;
        __IO uint32_t CB0 : 1;
        uint32_t RESERVED6 : 2;
        __IO uint32_t CA0E : 1;
        uint32_t RESERVED9 : 2;
        __IO uint32_t CB0E : 1;
        uint32_t RESERVED12 : 2;
        __IO uint32_t BI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t UND : 1;
        uint32_t RESERVED18 : 13;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_iclr_field_t;

    typedef struct
    {
        __IO uint32_t MMS : 3;
        __IO uint32_t CCDS : 1;
        __IO uint32_t MSM : 1;
        __IO uint32_t TS : 3;
        __IO uint32_t SMS : 3;
        __IO uint32_t IA0S : 1;
        __IO uint32_t IB0S : 1;
        uint32_t RESERVED13 : 18;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_mscr_field_t;

    typedef struct
    {
        __IO uint32_t OCMA0FLTA0 : 3;
        __IO uint32_t CCPA0 : 1;
        __IO uint32_t OCMB0FLTB0 : 3;
        __IO uint32_t CCPB0 : 1;
        uint32_t RESERVED8 : 16;
        __IO uint32_t FLTBK : 3;
        __IO uint32_t BKP : 1;
        __IO uint32_t FLTET : 3;
        __IO uint32_t ETP : 1;
    } stc_atimmode23_fltr_field_t;

    typedef struct
    {
        __IO uint32_t UEVE : 1;
        __IO uint32_t CMA0E : 1;
        uint32_t RESERVED2 : 2;
        __IO uint32_t CMB0E : 1;
        uint32_t RESERVED5 : 2;
        __IO uint32_t ADTE : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_adtr_field_t;

    typedef struct
    {
        __IO uint32_t CFACRABKSA : 2;
        __IO uint32_t CFBCRBBKSB : 2;
        __IO uint32_t CSA : 1;
        __IO uint32_t CSB : 1;
        __IO uint32_t BUFEA : 1;
        __IO uint32_t BUFEB : 1;
        __IO uint32_t CIEA : 1;
        __IO uint32_t CIEB : 1;
        __IO uint32_t CDEA : 1;
        __IO uint32_t CDEB : 1;
        __IO uint32_t CISB : 2;
        __IO uint32_t CCGA : 1;
        __IO uint32_t CCGB : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_crch0_field_t;

    typedef struct
    {
        __IO uint32_t DTR : 8;
        __IO uint32_t BKSEL : 1;
        __IO uint32_t DTEN : 1;
        __IO uint32_t BKE : 1;
        __IO uint32_t AOE : 1;
        __IO uint32_t MOE : 1;
        __IO uint32_t SAFEEN : 1;
        __IO uint32_t VCE : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_dtr_field_t;

    typedef struct
    {
        __IO uint32_t RCR : 8;
        __IO uint32_t OV : 1;
        __IO uint32_t UD : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_rcr_field_t;

    typedef struct
    {
        __IO uint32_t CCR0A : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_ccr0a_field_t;

    typedef struct
    {
        __IO uint32_t CCR0B : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_atimmode23_ccr0b_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_btim_arr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_btim_cnt_field_t;

    typedef struct
    {
        __IO uint32_t CEN : 1;
        __IO uint32_t MD : 2;
        __IO uint32_t TOGEN : 1;
        __IO uint32_t PRS : 4;
        __IO uint32_t OST : 1;
        __IO uint32_t TRS : 2;
        __IO uint32_t ETP : 1;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_btim_cr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        __IO uint32_t TI : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_btim_ier_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        __IO uint32_t TI : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_btim_ifr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        __IO uint32_t TI : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_btim_icr_field_t;

    typedef struct
    {
        __IO uint32_t UI03 : 1;
        __IO uint32_t TI03 : 1;
        __IO uint32_t UI14 : 1;
        __IO uint32_t TI14 : 1;
        __IO uint32_t UI25 : 1;
        __IO uint32_t TI25 : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_btim_aifr_field_t;

    typedef struct
    {
        __IO uint32_t UI03 : 1;
        __IO uint32_t TI03 : 1;
        __IO uint32_t UI14 : 1;
        __IO uint32_t TI14 : 1;
        __IO uint32_t UI25 : 1;
        __IO uint32_t TI25 : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_btim_aicr_field_t;

    typedef struct
    {
        __IO uint8_t BUSOFF : 1;
        __IO uint8_t TACTIVE : 1;
        __IO uint8_t RACTIVE : 1;
        __IO uint8_t TSSS : 1;
        __IO uint8_t TPSS : 1;
        __IO uint8_t LBMI : 1;
        __IO uint8_t LBME : 1;
        __IO uint8_t RESET : 1;
    } stc_can_cfg_stat_field_t;

    typedef struct
    {
        __IO uint8_t TSA : 1;
        __IO uint8_t TSALL : 1;
        __IO uint8_t TSONE : 1;
        __IO uint8_t TPA : 1;
        __IO uint8_t TPE : 1;
        __IO uint8_t STBY : 1;
        __IO uint8_t LOM : 1;
        __IO uint8_t TBSEL : 1;
    } stc_can_tcmd_field_t;

    typedef struct
    {
        __IO uint8_t TSSTAT : 2;
        uint8_t RESERVED2 : 2;
        __IO uint8_t TTTBM : 1;
        __IO uint8_t TSMODE : 1;
        __IO uint8_t TSNEXT : 1;
    } stc_can_tctrl_field_t;

    typedef struct
    {
        __IO uint8_t RSSTAT : 2;
        uint8_t RESERVED2 : 1;
        __IO uint8_t RBALL : 1;
        __IO uint8_t RREL : 1;
        __IO uint8_t ROV : 1;
        __IO uint8_t ROM : 1;
        __IO uint8_t SACK : 1;
    } stc_can_rctrl_field_t;

    typedef struct
    {
        __IO uint8_t TSFF : 1;
        __IO uint8_t EIE : 1;
        __IO uint8_t TSIE : 1;
        __IO uint8_t TPIE : 1;
        __IO uint8_t RAFIE : 1;
        __IO uint8_t RFIE : 1;
        __IO uint8_t ROIE : 1;
        __IO uint8_t RIE : 1;
    } stc_can_rtie_field_t;

    typedef struct
    {
        __IO uint8_t AIF : 1;
        __IO uint8_t EIF : 1;
        __IO uint8_t TSIF : 1;
        __IO uint8_t TPIF : 1;
        __IO uint8_t RAFIF : 1;
        __IO uint8_t RFIF : 1;
        __IO uint8_t ROIF : 1;
        __IO uint8_t RIF : 1;
    } stc_can_rtif_field_t;

    typedef struct
    {
        __IO uint8_t BEIF : 1;
        __IO uint8_t BEIE : 1;
        __IO uint8_t ALIF : 1;
        __IO uint8_t ALIE : 1;
        __IO uint8_t EPIF : 1;
        __IO uint8_t EPIE : 1;
        __IO uint8_t EPASS : 1;
        __IO uint8_t EWARN : 1;
    } stc_can_errint_field_t;

    typedef struct
    {
        __IO uint8_t EWL : 4;
        __IO uint8_t AFWL : 4;
    } stc_can_limit_field_t;

    typedef struct
    {
        __IO uint32_t SEG_1 : 8;
        __IO uint32_t SEG_2 : 7;
        uint32_t RESERVED15 : 1;
        __IO uint32_t SJW : 7;
        uint32_t RESERVED23 : 1;
        __IO uint32_t PRESC : 8;
    } stc_can_bt_field_t;

    typedef struct
    {
        __IO uint8_t ALC : 5;
        __IO uint8_t KOER : 3;
    } stc_can_ealcap_field_t;

    typedef struct
    {
        __IO uint8_t ACFADR : 4;
        uint8_t RESERVED4 : 1;
        __IO uint8_t SELMASK : 1;
    } stc_can_acfctrl_field_t;

    typedef struct
    {
        __IO uint8_t AE_1 : 1;
        __IO uint8_t AE_2 : 1;
        __IO uint8_t AE_3 : 1;
        __IO uint8_t AE_4 : 1;
        __IO uint8_t AE_5 : 1;
        __IO uint8_t AE_6 : 1;
        __IO uint8_t AE_7 : 1;
        __IO uint8_t AE_8 : 1;
    } stc_can_acfen_field_t;

    typedef struct
    {
        __IO uint32_t ACODE_AMASK : 29;
        __IO uint32_t AIDE : 1;
        __IO uint32_t AIDEE : 1;
    } stc_can_acf_field_t;

    typedef struct
    {
        __IO uint8_t TBPTR : 3;
        uint8_t RESERVED3 : 3;
        __IO uint8_t TBF : 1;
        __IO uint8_t TBE : 1;
    } stc_can_tbslot_field_t;

    typedef struct
    {
        __IO uint8_t TTEN : 1;
        __IO uint8_t T_PRESC : 2;
        __IO uint8_t TTIF : 1;
        __IO uint8_t TTIE : 1;
        __IO uint8_t TEIF : 1;
        __IO uint8_t WTIF : 1;
        __IO uint8_t WTIE : 1;
    } stc_can_ttcfg_field_t;

    typedef struct
    {
        __IO uint32_t REF_ID : 29;
        uint32_t RESERVED29 : 2;
        __IO uint32_t REF_IDE : 1;
    } stc_can_ref_msg_field_t;

    typedef struct
    {
        __IO uint16_t TTPTR : 3;
        uint16_t RESERVED3 : 5;
        __IO uint16_t TTYPE : 3;
        uint16_t RESERVED11 : 1;
        __IO uint16_t TEW : 4;
    } stc_can_trg_cfg_field_t;

    typedef struct
    {
        __IO uint32_t CODE : 1;
        __IO uint32_t FLAG : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_crc_csr_field_t;

    typedef struct
    {
        __IO uint32_t RESULT : 32;
    } stc_crc_result_field_t;

    typedef struct
    {
        __IO uint32_t DATA : 32;
    } stc_crc_data_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_ctrim_arr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_ctrim_cnt_field_t;

    typedef struct
    {
        __IO uint32_t STEP : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t ETRFLT : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t SRC : 3;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_ctrim_cr0_field_t;

    typedef struct
    {
        __IO uint32_t EN : 1;
        __IO uint32_t MD : 2;
        __IO uint32_t AUTO : 1;
        __IO uint32_t PRS : 4;
        __IO uint32_t OST : 1;
        __IO uint32_t MDRCH : 2;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_ctrim_cr1_field_t;

    typedef struct
    {
        __IO uint32_t UD : 1;
        __IO uint32_t END : 1;
        __IO uint32_t PS : 1;
        __IO uint32_t MISS : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t OK : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_ctrim_ier_field_t;

    typedef struct
    {
        __IO uint32_t UD : 1;
        __IO uint32_t END : 1;
        __IO uint32_t PS : 1;
        __IO uint32_t MISS : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t OK : 1;
        __IO uint32_t DIR : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_ctrim_isr_field_t;

    typedef struct
    {
        __IO uint32_t UD : 1;
        __IO uint32_t END : 1;
        __IO uint32_t PS : 1;
        __IO uint32_t MISS : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t OK : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_ctrim_icr_field_t;

    typedef struct
    {
        __IO uint32_t FCAP : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_ctrim_fcap_field_t;

    typedef struct
    {
        __IO uint32_t TVAL : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_ctrim_tval_field_t;

    typedef struct
    {
        __IO uint32_t FLIM : 12;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_ctrim_flim_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 24;
        __IO uint32_t HALT : 4;
        __IO uint32_t PRIO : 1;
        uint32_t RESERVED29 : 2;
        __IO uint32_t EN : 1;
    } stc_dmac_conf_field_t;

    typedef struct
    {
        __IO uint32_t TC : 16;
        __IO uint32_t BC : 4;
        uint32_t RESERVED20 : 2;
        __IO uint32_t TRISEL : 7;
        __IO uint32_t ST : 1;
        __IO uint32_t PAS : 1;
        __IO uint32_t ENS : 1;
    } stc_dmac_confa0_field_t;

    typedef struct
    {
        __IO uint32_t MSK : 1;
        uint32_t RESERVED1 : 15;
        __IO uint32_t STAT : 3;
        __IO uint32_t FISIE : 1;
        __IO uint32_t ERRIE : 1;
        __IO uint32_t RD : 1;
        __IO uint32_t RS : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t FD : 1;
        __IO uint32_t FS : 1;
        __IO uint32_t WIDTH : 2;
        __IO uint32_t MODE : 2;
    } stc_dmac_confb0_field_t;

    typedef struct
    {
        __IO uint32_t SRCADR : 32;
    } stc_dmac_srcadr0_field_t;

    typedef struct
    {
        __IO uint32_t DSTADR : 32;
    } stc_dmac_dstadr0_field_t;

    typedef struct
    {
        __IO uint32_t TC : 16;
        __IO uint32_t BC : 4;
        uint32_t RESERVED20 : 2;
        __IO uint32_t TRISEL : 7;
        __IO uint32_t ST : 1;
        __IO uint32_t PAS : 1;
        __IO uint32_t ENS : 1;
    } stc_dmac_confa1_field_t;

    typedef struct
    {
        __IO uint32_t MSK : 1;
        uint32_t RESERVED1 : 15;
        __IO uint32_t STAT : 3;
        __IO uint32_t FISIE : 1;
        __IO uint32_t ERRIE : 1;
        __IO uint32_t RD : 1;
        __IO uint32_t RS : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t FD : 1;
        __IO uint32_t FS : 1;
        __IO uint32_t WIDTH : 2;
        __IO uint32_t MODE : 2;
    } stc_dmac_confb1_field_t;

    typedef struct
    {
        __IO uint32_t SRCADR : 32;
    } stc_dmac_srcadr1_field_t;

    typedef struct
    {
        __IO uint32_t DSTADR : 32;
    } stc_dmac_dstadr1_field_t;

    typedef struct
    {
        __IO uint32_t TC : 16;
        __IO uint32_t BC : 4;
        uint32_t RESERVED20 : 2;
        __IO uint32_t TRISEL : 7;
        __IO uint32_t ST : 1;
        __IO uint32_t PAS : 1;
        __IO uint32_t ENS : 1;
    } stc_dmac_confa2_field_t;

    typedef struct
    {
        __IO uint32_t MSK : 1;
        uint32_t RESERVED1 : 15;
        __IO uint32_t STAT : 3;
        __IO uint32_t FISIE : 1;
        __IO uint32_t ERRIE : 1;
        __IO uint32_t RD : 1;
        __IO uint32_t RS : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t FD : 1;
        __IO uint32_t FS : 1;
        __IO uint32_t WIDTH : 2;
        __IO uint32_t MODE : 2;
    } stc_dmac_confb2_field_t;

    typedef struct
    {
        __IO uint32_t SRCADR : 32;
    } stc_dmac_srcadr2_field_t;

    typedef struct
    {
        __IO uint32_t DSTADR : 32;
    } stc_dmac_dstadr2_field_t;

    typedef struct
    {
        __IO uint32_t TC : 16;
        __IO uint32_t BC : 4;
        uint32_t RESERVED20 : 2;
        __IO uint32_t TRISEL : 7;
        __IO uint32_t ST : 1;
        __IO uint32_t PAS : 1;
        __IO uint32_t ENS : 1;
    } stc_dmac_confa3_field_t;

    typedef struct
    {
        __IO uint32_t MSK : 1;
        uint32_t RESERVED1 : 15;
        __IO uint32_t STAT : 3;
        __IO uint32_t FISIE : 1;
        __IO uint32_t ERRIE : 1;
        __IO uint32_t RD : 1;
        __IO uint32_t RS : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t FD : 1;
        __IO uint32_t FS : 1;
        __IO uint32_t WIDTH : 2;
        __IO uint32_t MODE : 2;
    } stc_dmac_confb3_field_t;

    typedef struct
    {
        __IO uint32_t SRCADR : 32;
    } stc_dmac_srcadr3_field_t;

    typedef struct
    {
        __IO uint32_t DSTADR : 32;
    } stc_dmac_dstadr3_field_t;

    typedef struct
    {
        __IO uint32_t TC : 16;
        __IO uint32_t BC : 4;
        uint32_t RESERVED20 : 2;
        __IO uint32_t TRISEL : 7;
        __IO uint32_t ST : 1;
        __IO uint32_t PAS : 1;
        __IO uint32_t ENS : 1;
    } stc_dmac_confa4_field_t;

    typedef struct
    {
        __IO uint32_t MSK : 1;
        uint32_t RESERVED1 : 15;
        __IO uint32_t STAT : 3;
        __IO uint32_t FISIE : 1;
        __IO uint32_t ERRIE : 1;
        __IO uint32_t RD : 1;
        __IO uint32_t RS : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t FD : 1;
        __IO uint32_t FS : 1;
        __IO uint32_t WIDTH : 2;
        __IO uint32_t MODE : 2;
    } stc_dmac_confb4_field_t;

    typedef struct
    {
        __IO uint32_t SRCADR : 32;
    } stc_dmac_srcadr4_field_t;

    typedef struct
    {
        __IO uint32_t DSTADR : 32;
    } stc_dmac_dstadr4_field_t;

    typedef struct
    {
        __IO uint32_t TC : 16;
        __IO uint32_t BC : 4;
        uint32_t RESERVED20 : 2;
        __IO uint32_t TRISEL : 7;
        __IO uint32_t ST : 1;
        __IO uint32_t PAS : 1;
        __IO uint32_t ENS : 1;
    } stc_dmac_confa5_field_t;

    typedef struct
    {
        __IO uint32_t MSK : 1;
        uint32_t RESERVED1 : 15;
        __IO uint32_t STAT : 3;
        __IO uint32_t FISIE : 1;
        __IO uint32_t ERRIE : 1;
        __IO uint32_t RD : 1;
        __IO uint32_t RS : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t FD : 1;
        __IO uint32_t FS : 1;
        __IO uint32_t WIDTH : 2;
        __IO uint32_t MODE : 2;
    } stc_dmac_confb5_field_t;

    typedef struct
    {
        __IO uint32_t SRCADR : 32;
    } stc_dmac_srcadr5_field_t;

    typedef struct
    {
        __IO uint32_t DSTADR : 32;
    } stc_dmac_dstadr5_field_t;

    typedef struct
    {
        __IO uint32_t MODE : 2;
        __IO uint32_t OVR : 1;
        __IO uint32_t ZERO : 1;
        __IO uint32_t BUSY : 1;
        uint32_t RESERVED5 : 26;
        __IO uint32_t RSV : 1;
    } stc_eau_csr_field_t;

    typedef struct
    {
        __IO uint32_t DIVIDEND : 32;
    } stc_eau_dividend_field_t;

    typedef struct
    {
        __IO uint32_t DIVISOR : 32;
    } stc_eau_divisor_field_t;

    typedef struct
    {
        __IO uint32_t QUOTIENT : 32;
    } stc_eau_quotient_field_t;

    typedef struct
    {
        __IO uint32_t REMAINDER : 32;
    } stc_eau_remainder_field_t;

    typedef struct
    {
        __IO uint32_t OP : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t FWUP : 1;
        __IO uint32_t ROMD : 1;
        uint32_t RESERVED6 : 1;
        __IO uint32_t DPSTBEN : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_flash_cr_field_t;

    typedef struct
    {
        __IO uint32_t WAIT : 3;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_flash_wait_field_t;

    typedef struct
    {
        __IO uint32_t STATE : 2;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_flash_lockst_field_t;

    typedef struct
    {
        __IO uint32_t PC : 1;
        __IO uint32_t PROT : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_flash_ier_field_t;

    typedef struct
    {
        __IO uint32_t PC : 1;
        __IO uint32_t PROT : 1;
        uint32_t RESERVED2 : 2;
        __IO uint32_t BUSY : 1;
        __IO uint32_t CFDONE : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_flash_ifr_field_t;

    typedef struct
    {
        __IO uint32_t PC : 1;
        __IO uint32_t PROT : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_flash_icr_field_t;

    typedef struct
    {
        __IO uint32_t BYSEQ : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_flash_bypass_field_t;

    typedef struct
    {
        __IO uint32_t SLOCK : 32;
    } stc_flash_slock0_field_t;

    typedef struct
    {
        __IO uint32_t SLOCK : 32;
    } stc_flash_slock1_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_ads_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_dir_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_opendrain_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_driver_field_t;

    typedef struct
    {
        __IO uint32_t PUPIN0 : 1;
        __IO uint32_t PUPIN1 : 1;
        __IO uint32_t PUPIN2 : 1;
        __IO uint32_t PUPIN3 : 1;
        __IO uint32_t PUPIN4 : 1;
        __IO uint32_t PUPIN5 : 1;
        __IO uint32_t PUPIN6 : 1;
        __IO uint32_t PUPIN7 : 1;
        __IO uint32_t PUPIN8 : 1;
        __IO uint32_t PUPIN9 : 1;
        __IO uint32_t PUPIN10 : 1;
        __IO uint32_t PUPIN11 : 1;
        __IO uint32_t PUPIN12 : 1;
        __IO uint32_t PUPIN13 : 1;
        __IO uint32_t PUPIN14 : 1;
        __IO uint32_t PUPIN15 : 1;
        __IO uint32_t PDPIN0 : 1;
        __IO uint32_t PDPIN1 : 1;
        __IO uint32_t PDPIN2 : 1;
        __IO uint32_t PDPIN3 : 1;
        __IO uint32_t PDPIN4 : 1;
        __IO uint32_t PDPIN5 : 1;
        __IO uint32_t PDPIN6 : 1;
        __IO uint32_t PDPIN7 : 1;
        __IO uint32_t PDPIN8 : 1;
        __IO uint32_t PDPIN9 : 1;
        __IO uint32_t PDPIN10 : 1;
        __IO uint32_t PDPIN11 : 1;
        __IO uint32_t PDPIN12 : 1;
        __IO uint32_t PDPIN13 : 1;
        __IO uint32_t PDPIN14 : 1;
        __IO uint32_t PDPIN15 : 1;
    } stc_gpio_pupd_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_in_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_out_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_brr_field_t;

    typedef struct
    {
        __IO uint32_t BSPIN0 : 1;
        __IO uint32_t BSPIN1 : 1;
        __IO uint32_t BSPIN2 : 1;
        __IO uint32_t BSPIN3 : 1;
        __IO uint32_t BSPIN4 : 1;
        __IO uint32_t BSPIN5 : 1;
        __IO uint32_t BSPIN6 : 1;
        __IO uint32_t BSPIN7 : 1;
        __IO uint32_t BSPIN8 : 1;
        __IO uint32_t BSPIN9 : 1;
        __IO uint32_t BSPIN10 : 1;
        __IO uint32_t BSPIN11 : 1;
        __IO uint32_t BSPIN12 : 1;
        __IO uint32_t BSPIN13 : 1;
        __IO uint32_t BSPIN14 : 1;
        __IO uint32_t BSPIN15 : 1;
        __IO uint32_t BRPIN0 : 1;
        __IO uint32_t BRPIN1 : 1;
        __IO uint32_t BRPIN2 : 1;
        __IO uint32_t BRPIN3 : 1;
        __IO uint32_t BRPIN4 : 1;
        __IO uint32_t BRPIN5 : 1;
        __IO uint32_t BRPIN6 : 1;
        __IO uint32_t BRPIN7 : 1;
        __IO uint32_t BRPIN8 : 1;
        __IO uint32_t BRPIN9 : 1;
        __IO uint32_t BRPIN10 : 1;
        __IO uint32_t BRPIN11 : 1;
        __IO uint32_t BRPIN12 : 1;
        __IO uint32_t BRPIN13 : 1;
        __IO uint32_t BRPIN14 : 1;
        __IO uint32_t BRPIN15 : 1;
    } stc_gpio_bsrr_field_t;

    typedef struct
    {
        __IO uint32_t AFSEL0 : 4;
        __IO uint32_t AFSEL1 : 4;
        __IO uint32_t AFSEL2 : 4;
        __IO uint32_t AFSEL3 : 4;
        __IO uint32_t AFSEL4 : 4;
        __IO uint32_t AFSEL5 : 4;
        __IO uint32_t AFSEL6 : 4;
        __IO uint32_t AFSEL7 : 4;
    } stc_gpio_afrl_field_t;

    typedef struct
    {
        __IO uint32_t AFSEL8 : 4;
        __IO uint32_t AFSEL9 : 4;
        __IO uint32_t AFSEL10 : 4;
        __IO uint32_t AFSEL11 : 4;
        __IO uint32_t AFSEL12 : 4;
        __IO uint32_t AFSEL13 : 4;
        __IO uint32_t AFSEL14 : 4;
        __IO uint32_t AFSEL15 : 4;
    } stc_gpio_afrh_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_highie_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_lowie_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_riseie_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_fallie_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_ifr_field_t;

    typedef struct
    {
        __IO uint32_t PIN0 : 1;
        __IO uint32_t PIN1 : 1;
        __IO uint32_t PIN2 : 1;
        __IO uint32_t PIN3 : 1;
        __IO uint32_t PIN4 : 1;
        __IO uint32_t PIN5 : 1;
        __IO uint32_t PIN6 : 1;
        __IO uint32_t PIN7 : 1;
        __IO uint32_t PIN8 : 1;
        __IO uint32_t PIN9 : 1;
        __IO uint32_t PIN10 : 1;
        __IO uint32_t PIN11 : 1;
        __IO uint32_t PIN12 : 1;
        __IO uint32_t PIN13 : 1;
        __IO uint32_t PIN14 : 1;
        __IO uint32_t PIN15 : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gpio_icr_field_t;

    typedef struct
    {
        __IO uint32_t PCLKDIV : 3;
        uint32_t RESERVED3 : 5;
        __IO uint32_t MCODIV : 3;
        uint32_t RESERVED11 : 1;
        __IO uint32_t MCOSEL : 3;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_gpioaux_cr0_field_t;

    typedef struct
    {
        __IO uint32_t ATIM0ETR : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t CTIM0ETR : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t CTIM1ETR : 3;
        uint32_t RESERVED11 : 1;
        __IO uint32_t ATIM3ETR : 3;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_gpioaux_cr1_field_t;

    typedef struct
    {
        __IO uint32_t ATIM0CAP0 : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t CTIM0CAP3 : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t CTIM1CAP3 : 3;
        uint32_t RESERVED11 : 1;
        __IO uint32_t ATIM3CAP3 : 3;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_gpioaux_cr2_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gtim_arr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gtim_cnt_field_t;

    typedef struct
    {
        __IO uint32_t CC0M : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t CC1M : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t CC2M : 3;
        uint32_t RESERVED11 : 1;
        __IO uint32_t CC3M : 3;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_gtim_cmmr_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 4;
        __IO uint32_t ETRFLT : 3;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_gtim_cr1_field_t;

    typedef struct
    {
        __IO uint32_t CEN : 1;
        __IO uint32_t MD : 2;
        __IO uint32_t TOGEN : 1;
        __IO uint32_t PRS : 4;
        __IO uint32_t OST : 1;
        __IO uint32_t TRS : 2;
        __IO uint32_t ETP : 1;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_gtim_cr0_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t CC0 : 1;
        __IO uint32_t CC1 : 1;
        __IO uint32_t CC2 : 1;
        __IO uint32_t CC3 : 1;
        __IO uint32_t DCC0 : 1;
        __IO uint32_t DCC1 : 1;
        __IO uint32_t DCC2 : 1;
        __IO uint32_t DCC3 : 1;
        __IO uint32_t OVTRAD : 1;
        __IO uint32_t C0TRAD : 1;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_gtim_ier_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t CC0 : 1;
        __IO uint32_t CC1 : 1;
        __IO uint32_t CC2 : 1;
        __IO uint32_t CC3 : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_gtim_ifr_field_t;

    typedef struct
    {
        __IO uint32_t UI : 1;
        __IO uint32_t TI : 1;
        __IO uint32_t CC0 : 1;
        __IO uint32_t CC1 : 1;
        __IO uint32_t CC2 : 1;
        __IO uint32_t CC3 : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_gtim_icr_field_t;

    typedef struct
    {
        __IO uint32_t CCR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gtim_ccr0_field_t;

    typedef struct
    {
        __IO uint32_t CCR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gtim_ccr1_field_t;

    typedef struct
    {
        __IO uint32_t CCR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gtim_ccr2_field_t;

    typedef struct
    {
        __IO uint32_t CCR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_gtim_ccr3_field_t;

    typedef struct
    {
        __IO uint32_t TME : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_i2c_tmrun_field_t;

    typedef struct
    {
        __IO uint32_t TM : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2c_tm_field_t;

    typedef struct
    {
        __IO uint32_t H1M : 1;
        uint32_t RESERVED1 : 1;
        __IO uint32_t AA : 1;
        __IO uint32_t SI : 1;
        __IO uint32_t STO : 1;
        __IO uint32_t STA : 1;
        __IO uint32_t ENS : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_i2c_cr_field_t;

    typedef struct
    {
        __IO uint32_t DAT : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2c_data_field_t;

    typedef struct
    {
        __IO uint32_t GC : 1;
        __IO uint32_t ADDR0 : 7;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2c_addr0_field_t;

    typedef struct
    {
        __IO uint32_t STAT : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2c_stat_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 1;
        __IO uint32_t ADDR : 7;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2c_addr1_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 1;
        __IO uint32_t ADDR : 7;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2c_addr2_field_t;

    typedef struct
    {
        __IO uint32_t AD0F : 1;
        __IO uint32_t AD1F : 1;
        __IO uint32_t AD2F : 1;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_i2c_match_field_t;

    typedef struct
    {
        __IO uint32_t RD : 1;
        __IO uint32_t WR : 1;
        __IO uint32_t STOP : 1;
        __IO uint32_t START : 1;
        __IO uint32_t NACK : 1;
        __IO uint32_t I2CINT : 1;
        __IO uint32_t ACTIVE : 1;
        __IO uint32_t HSMODE : 1;
        __IO uint32_t TIMEOUT : 1;
        __IO uint32_t ACK : 1;
        __IO uint32_t SLADDR0 : 1;
        __IO uint32_t SLADDR1 : 1;
        __IO uint32_t SLADDR2 : 1;
        __IO uint32_t SLADDR3 : 1;
        __IO uint32_t TXE : 1;
        __IO uint32_t RXNE : 1;
        __IO uint32_t GC : 1;
        uint32_t RESERVED17 : 14;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_sr_field_t;

    typedef struct
    {
        __IO uint32_t DOUT : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_doutr_field_t;

    typedef struct
    {
        __IO uint32_t ADIR : 10;
        __IO uint32_t ADRLEN : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_adir_field_t;

    typedef struct
    {
        __IO uint32_t ADDR : 10;
        __IO uint32_t AM : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_sladr0_field_t;

    typedef struct
    {
        __IO uint32_t ADDR : 10;
        __IO uint32_t AM : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_sladr1_field_t;

    typedef struct
    {
        __IO uint32_t ADDR : 10;
        __IO uint32_t ADDRLEN : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_sladr2_field_t;

    typedef struct
    {
        __IO uint32_t ADDR : 10;
        __IO uint32_t ADDRLEN : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_sladr3_field_t;

    typedef struct
    {
        __IO uint32_t DIN : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_dinr_field_t;

    typedef struct
    {
        __IO uint32_t EN : 1;
        __IO uint32_t BUSY : 1;
        __IO uint32_t FSCLC : 1;
        __IO uint32_t TIMEOUT : 1;
        uint32_t RESERVED4 : 3;
        __IO uint32_t GC : 1;
        __IO uint32_t DMATE : 1;
        __IO uint32_t DMARE : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_cr_field_t;

    typedef struct
    {
        __IO uint32_t ADDRMASK : 10;
        __IO uint32_t FACS : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_admr0_field_t;

    typedef struct
    {
        __IO uint32_t FW : 3;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_flt_field_t;

    typedef struct
    {
        __IO uint32_t TOR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_tor_field_t;

    typedef struct
    {
        __IO uint32_t ODPU : 2;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_oddr_field_t;

    typedef struct
    {
        __IO uint32_t NS : 2;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_rsr_field_t;

    typedef struct
    {
        __IO uint32_t RD : 1;
        __IO uint32_t WR : 1;
        __IO uint32_t STOP : 1;
        __IO uint32_t START : 1;
        __IO uint32_t NACK : 1;
        __IO uint32_t I2CINT : 1;
        __IO uint32_t ACTIVE : 1;
        __IO uint32_t HSMODE : 1;
        __IO uint32_t TIMEOUT : 1;
        __IO uint32_t ACK : 1;
        __IO uint32_t SLADDR0 : 1;
        __IO uint32_t SLADDR1 : 1;
        __IO uint32_t SLADDR2 : 1;
        __IO uint32_t SLADDR3 : 1;
        __IO uint32_t TXE : 1;
        __IO uint32_t RXNE : 1;
        __IO uint32_t GC : 1;
        uint32_t RESERVED17 : 14;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_ier_field_t;

    typedef struct
    {
        __IO uint32_t RD : 1;
        __IO uint32_t WR : 1;
        __IO uint32_t STOP : 1;
        __IO uint32_t START : 1;
        __IO uint32_t NACK : 1;
        __IO uint32_t I2CINT : 1;
        __IO uint32_t ACTIVE : 1;
        __IO uint32_t HSMODE : 1;
        __IO uint32_t TIMEOUT : 1;
        __IO uint32_t ACK : 1;
        __IO uint32_t SLADDR0 : 1;
        __IO uint32_t SLADDR1 : 1;
        __IO uint32_t SLADDR2 : 1;
        __IO uint32_t SLADDR3 : 1;
        __IO uint32_t TXE : 1;
        __IO uint32_t RXNE : 1;
        __IO uint32_t GC : 1;
        uint32_t RESERVED17 : 14;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_icr_field_t;

    typedef struct
    {
        __IO uint32_t RID : 3;
        __IO uint32_t PID : 9;
        __IO uint32_t MID : 12;
        uint32_t RESERVED24 : 7;
        __IO uint32_t RSV : 1;
    } stc_i2cslv_didr_field_t;

    typedef struct
    {
        __IO uint32_t KR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_iwdt_kr_field_t;

    typedef struct
    {
        __IO uint32_t PRS : 3;
        uint32_t RESERVED3 : 1;
        __IO uint32_t IE : 1;
        __IO uint32_t ACTION : 1;
        __IO uint32_t PAUSE : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_iwdt_cr_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 12;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_iwdt_arr_field_t;

    typedef struct
    {
        __IO uint32_t PRSF : 1;
        __IO uint32_t ARRF : 1;
        __IO uint32_t WINRF : 1;
        __IO uint32_t OV : 1;
        __IO uint32_t RUN : 1;
        uint32_t RESERVED5 : 26;
        __IO uint32_t RSV : 1;
    } stc_iwdt_sr_field_t;

    typedef struct
    {
        __IO uint32_t WINR : 12;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_iwdt_winr_field_t;

    typedef struct
    {
        __IO uint32_t CNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_lptim_cnt_field_t;

    typedef struct
    {
        __IO uint32_t ARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_lptim_arr_field_t;

    typedef struct
    {
        __IO uint32_t CEN : 1;
        __IO uint32_t MD : 1;
        __IO uint32_t CT : 1;
        __IO uint32_t TOG_EN : 1;
        __IO uint32_t TCK_SEL : 2;
        uint32_t RESERVED6 : 1;
        __IO uint32_t WT_FLAG : 1;
        __IO uint32_t GATE : 1;
        __IO uint32_t GATE_P : 1;
        __IO uint32_t IE : 1;
        __IO uint32_t PRS : 4;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_lptim_cr_field_t;

    typedef struct
    {
        __IO uint32_t OV : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_lptim_ifr_field_t;

    typedef struct
    {
        __IO uint32_t OV : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_lptim_iclr_field_t;

    typedef struct
    {
        __IO uint32_t DATA : 8;
        __IO uint32_t DR8 : 1;
        uint32_t RESERVED9 : 22;
        __IO uint32_t RSV : 1;
    } stc_lpuart_sbuf_field_t;

    typedef struct
    {
        __IO uint32_t RCIE : 1;
        __IO uint32_t TCIE : 1;
        __IO uint32_t DR8CFG : 2;
        __IO uint32_t RXEN : 1;
        __IO uint32_t ADRDET : 1;
        __IO uint32_t MODE : 2;
        __IO uint32_t TXEIE : 1;
        __IO uint32_t OVER : 2;
        __IO uint32_t CLKSRC : 2;
        __IO uint32_t PEIE : 1;
        __IO uint32_t STOP : 2;
        __IO uint32_t DMARXEN : 1;
        __IO uint32_t DMATXEN : 1;
        __IO uint32_t RTSEN : 1;
        __IO uint32_t CTSEN : 1;
        __IO uint32_t CTSIE : 1;
        __IO uint32_t FEIE : 1;
        __IO uint32_t HDSEL : 1;
        uint32_t RESERVED23 : 8;
        __IO uint32_t RSV : 1;
    } stc_lpuart_scon_field_t;

    typedef struct
    {
        __IO uint32_t ADDR : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_lpuart_saddr_field_t;

    typedef struct
    {
        __IO uint32_t SADEN : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_lpuart_saden_field_t;

    typedef struct
    {
        __IO uint32_t RC : 1;
        __IO uint32_t TC : 1;
        __IO uint32_t FE : 1;
        __IO uint32_t TXE : 1;
        __IO uint32_t PE : 1;
        __IO uint32_t CTSIF : 1;
        __IO uint32_t CTS : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_lpuart_isr_field_t;

    typedef struct
    {
        __IO uint32_t RC : 1;
        __IO uint32_t TC : 1;
        __IO uint32_t FE : 1;
        uint32_t RESERVED3 : 1;
        __IO uint32_t PE : 1;
        __IO uint32_t CTSIF : 1;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_lpuart_icr_field_t;

    typedef struct
    {
        __IO uint32_t SCNT : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_lpuart_scnt_field_t;

    typedef struct
    {
        __IO uint32_t LVDEN : 1;
        __IO uint32_t ACT : 1;
        __IO uint32_t SOURCE : 2;
        __IO uint32_t VTDS : 4;
        __IO uint32_t FLTEN : 1;
        __IO uint32_t DEBOUNCETIME : 3;
        __IO uint32_t FTEN : 1;
        __IO uint32_t RTEN : 1;
        __IO uint32_t HTEN : 1;
        __IO uint32_t IE : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_lvd_cr_field_t;

    typedef struct
    {
        __IO uint32_t INTF : 1;
        __IO uint32_t FILTER : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_lvd_sr_field_t;

    typedef struct
    {
        __IO uint32_t OPAEN : 1;
        __IO uint32_t AZEN : 1;
        uint32_t RESERVED2 : 5;
        __IO uint32_t BIASSEL : 3;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_opa_cr0_field_t;

    typedef struct
    {
        __IO uint32_t OPAEN : 1;
        __IO uint32_t AZEN : 1;
        uint32_t RESERVED2 : 5;
        __IO uint32_t BIASSEL : 3;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_opa_cr1_field_t;

    typedef struct
    {
        __IO uint32_t ADCTREN : 1;
        __IO uint32_t TRIGGER : 1;
        __IO uint32_t AZPULSE : 1;
        __IO uint32_t CLKSWSET : 1;
        __IO uint32_t CLKSEL : 4;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_opa_az_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 1;
        __IO uint32_t IE : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_ram_cr_field_t;

    typedef struct
    {
        __IO uint32_t ERRADDR : 14;
        uint32_t RESERVED14 : 17;
        __IO uint32_t RSV : 1;
    } stc_ram_erraddr_field_t;

    typedef struct
    {
        __IO uint32_t ERR : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_ram_ifr_field_t;

    typedef struct
    {
        __IO uint32_t ERRCLR : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_ram_iclr_field_t;

    typedef struct
    {
        __IO uint32_t PRDS : 3;
        __IO uint32_t AMPM : 1;
        uint32_t RESERVED4 : 1;
        __IO uint32_t HZ1OE : 1;
        __IO uint32_t HZ1SEL : 1;
        __IO uint32_t START : 1;
        __IO uint32_t PRDX : 6;
        __IO uint32_t PRDSEL : 1;
        __IO uint32_t TEST : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_rtc_cr0_field_t;

    typedef struct
    {
        __IO uint32_t WAIT : 1;
        __IO uint32_t WAITF : 1;
        uint32_t RESERVED2 : 6;
        __IO uint32_t CKSEL : 3;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_rtc_cr1_field_t;

    typedef struct
    {
        __IO uint32_t SECL : 4;
        __IO uint32_t SECH : 3;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_rtc_sec_field_t;

    typedef struct
    {
        __IO uint32_t MINL : 4;
        __IO uint32_t MINH : 3;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_rtc_min_field_t;

    typedef struct
    {
        __IO uint32_t HOURL : 4;
        __IO uint32_t HOURH : 2;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_rtc_hour_field_t;

    typedef struct
    {
        __IO uint32_t WEEK : 3;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_rtc_week_field_t;

    typedef struct
    {
        __IO uint32_t DAYL : 4;
        __IO uint32_t DAYH : 2;
        uint32_t RESERVED6 : 25;
        __IO uint32_t RSV : 1;
    } stc_rtc_day_field_t;

    typedef struct
    {
        __IO uint32_t MON : 5;
        uint32_t RESERVED5 : 26;
        __IO uint32_t RSV : 1;
    } stc_rtc_mon_field_t;

    typedef struct
    {
        __IO uint32_t YEARL : 4;
        __IO uint32_t YEARH : 4;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_rtc_year_field_t;

    typedef struct
    {
        __IO uint32_t CR : 9;
        uint32_t RESERVED9 : 6;
        __IO uint32_t EN : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_rtc_compen_field_t;

    typedef struct
    {
        __IO uint32_t WUCKSEL : 3;
        __IO uint32_t TSEDG : 1;
        __IO uint32_t O2SEL : 2;
        __IO uint32_t TSE : 1;
        __IO uint32_t WUTE : 1;
        uint32_t RESERVED8 : 1;
        __IO uint32_t ALMAE : 1;
        __IO uint32_t ALMBE : 1;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_rtc_cr2_field_t;

    typedef struct
    {
        __IO uint32_t SECL : 4;
        __IO uint32_t SECH : 3;
        __IO uint32_t MSKS : 1;
        __IO uint32_t MINL : 4;
        __IO uint32_t MINH : 3;
        __IO uint32_t MSKM : 1;
        __IO uint32_t HOURL : 4;
        __IO uint32_t HOURH : 2;
        uint32_t RESERVED22 : 1;
        __IO uint32_t MSKH : 1;
        __IO uint32_t WEEK : 7;
        __IO uint32_t RSV : 1;
    } stc_rtc_alma_field_t;

    typedef struct
    {
        __IO uint32_t SECL : 4;
        __IO uint32_t SECH : 3;
        __IO uint32_t MSKS : 1;
        __IO uint32_t MINL : 4;
        __IO uint32_t MINH : 3;
        __IO uint32_t MSKM : 1;
        __IO uint32_t HOURL : 4;
        __IO uint32_t HOURH : 2;
        uint32_t RESERVED22 : 1;
        __IO uint32_t MSKH : 1;
        __IO uint32_t WEEK : 7;
        __IO uint32_t RSV : 1;
    } stc_rtc_almb_field_t;

    typedef struct
    {
        __IO uint32_t SECL : 4;
        __IO uint32_t SECH : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t MINL : 4;
        __IO uint32_t MINH : 3;
        uint32_t RESERVED15 : 1;
        __IO uint32_t HOURL : 4;
        __IO uint32_t HOURH : 2;
        uint32_t RESERVED22 : 9;
        __IO uint32_t RSV : 1;
    } stc_rtc_tstr_field_t;

    typedef struct
    {
        __IO uint32_t DAYL : 4;
        __IO uint32_t DAYH : 2;
        uint32_t RESERVED6 : 2;
        __IO uint32_t MON : 5;
        __IO uint32_t WEEK : 3;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_rtc_tsdr_field_t;

    typedef struct
    {
        __IO uint32_t WUTARR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_rtc_wutarr_field_t;

    typedef struct
    {
        __IO uint32_t ALMA : 1;
        __IO uint32_t ALMB : 1;
        __IO uint32_t WU : 1;
        __IO uint32_t TS : 1;
        __IO uint32_t TSOV : 1;
        uint32_t RESERVED5 : 1;
        __IO uint32_t PRD : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_rtc_ier_field_t;

    typedef struct
    {
        __IO uint32_t ALMA : 1;
        __IO uint32_t ALMB : 1;
        __IO uint32_t WU : 1;
        __IO uint32_t TS : 1;
        __IO uint32_t TSOV : 1;
        uint32_t RESERVED5 : 1;
        __IO uint32_t PRD : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_rtc_ifr_field_t;

    typedef struct
    {
        __IO uint32_t ALMA : 1;
        __IO uint32_t ALMB : 1;
        __IO uint32_t WU : 1;
        __IO uint32_t TS : 1;
        __IO uint32_t TSOV : 1;
        uint32_t RESERVED5 : 1;
        __IO uint32_t PRD : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_rtc_icr_field_t;

    typedef struct
    {
        __IO uint32_t WPR : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_rtc_wpr_field_t;

    typedef struct
    {
        __IO uint32_t EN : 1;
        __IO uint32_t BRR : 3;
        __IO uint32_t CPHA : 1;
        __IO uint32_t CPOL : 1;
        __IO uint32_t MSTR : 1;
        __IO uint32_t LSBF : 1;
        __IO uint32_t WIDTH : 4;
        __IO uint32_t SSM : 1;
        __IO uint32_t CM : 2;
        __IO uint32_t SMP : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_spi_cr0_field_t;

    typedef struct
    {
        __IO uint32_t TXEIE : 1;
        __IO uint32_t RXNEIE : 1;
        __IO uint32_t SSFIE : 1;
        __IO uint32_t SSRIE : 1;
        __IO uint32_t UDFIE : 1;
        __IO uint32_t OVFIE : 1;
        __IO uint32_t SSERRIE : 1;
        __IO uint32_t MODFIE : 1;
        __IO uint32_t DMARXEN : 1;
        __IO uint32_t DMATXEN : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_spi_cr1_field_t;

    typedef struct
    {
        __IO uint32_t HDOE : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_spi_hdoe_field_t;

    typedef struct
    {
        __IO uint32_t SSI : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_spi_ssi_field_t;

    typedef struct
    {
        __IO uint32_t TXE : 1;
        __IO uint32_t RXNE : 1;
        __IO uint32_t SSF : 1;
        __IO uint32_t SSR : 1;
        __IO uint32_t UDF : 1;
        __IO uint32_t OVF : 1;
        __IO uint32_t SSERR : 1;
        __IO uint32_t MODF : 1;
        __IO uint32_t BUSY : 1;
        __IO uint32_t SSLVL : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_spi_sr_field_t;

    typedef struct
    {
        __IO uint32_t TXE : 1;
        __IO uint32_t RXNE : 1;
        __IO uint32_t SSF : 1;
        __IO uint32_t SSR : 1;
        __IO uint32_t UDF : 1;
        __IO uint32_t OVF : 1;
        __IO uint32_t SSERR : 1;
        __IO uint32_t MODF : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_spi_icr_field_t;

    typedef struct
    {
        __IO uint32_t DR : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_spi_dr_field_t;

    typedef struct
    {
        __IO uint32_t CLKSRC : 3;
        __IO uint32_t HCLKPRS : 3;
        __IO uint32_t PCLKPRS : 2;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_cr0_field_t;

    typedef struct
    {
        __IO uint32_t SWDUSEIO : 1;
        __IO uint32_t LOCKUP_EN : 1;
        __IO uint32_t WAKEUPBYRCH : 1;
        __IO uint32_t RTCLPW : 1;
        __IO uint32_t RTCADJ : 3;
        __IO uint32_t AUTOSWITCH : 1;
        __IO uint32_t SPIPCTRL : 1;
        __IO uint32_t XTHFLT : 1;
        __IO uint32_t GTIM0CFG : 1;
        __IO uint32_t GTIM1CFG : 1;
        __IO uint32_t FASTIOENB : 1;
        uint32_t RESERVED13 : 18;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_cr1_field_t;

    typedef struct
    {
        __IO uint32_t RCH : 1;
        __IO uint32_t XTH : 1;
        __IO uint32_t RCL : 1;
        __IO uint32_t XTL : 1;
        __IO uint32_t PLL : 1;
        __IO uint32_t EXXTH : 1;
        __IO uint32_t EXXTL : 1;
        __IO uint32_t XTLLOCK : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_cr2_field_t;

    typedef struct
    {
        __IO uint32_t CR3 : 16;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_cr3_field_t;

    typedef struct
    {
        __IO uint32_t DIV : 3;
        uint32_t RESERVED3 : 28;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_rchcr_field_t;

    typedef struct
    {
        __IO uint32_t DRIVER : 2;
        __IO uint32_t RANGE : 2;
        __IO uint32_t STARTUP : 2;
        __IO uint32_t DETEN : 1;
        __IO uint32_t DETTIME : 1;
        __IO uint32_t DETIE : 1;
        uint32_t RESERVED9 : 22;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_xthcr_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 10;
        __IO uint32_t STARTUP : 2;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_rclcr_field_t;

    typedef struct
    {
        __IO uint32_t DRIVER : 2;
        __IO uint32_t AMP_SEL : 2;
        __IO uint32_t STARTUP : 2;
        __IO uint32_t DETEN : 1;
        __IO uint32_t DETTIME : 1;
        __IO uint32_t DETIE : 1;
        uint32_t RESERVED9 : 22;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_xtlcr_field_t;

    typedef struct
    {
        __IO uint32_t SRC : 2;
        __IO uint32_t DIVR : 1;
        uint32_t RESERVED3 : 1;
        __IO uint32_t WAITCYCLE : 3;
        uint32_t RESERVED7 : 1;
        __IO uint32_t DIVN : 7;
        uint32_t RESERVED15 : 1;
        __IO uint32_t DIVF : 3;
        uint32_t RESERVED19 : 1;
        __IO uint32_t POSTDIV : 4;
        uint32_t RESERVED24 : 7;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_pllcr_field_t;

    typedef struct
    {
        __IO uint32_t TRIML : 6;
        __IO uint32_t TRIMH : 5;
        uint32_t RESERVED11 : 20;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_rchtrim_field_t;

    typedef struct
    {
        __IO uint32_t TRIM : 10;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_rcltrim_field_t;

    typedef struct
    {
        __IO uint32_t RCH : 1;
        __IO uint32_t XTH : 1;
        __IO uint32_t RCL : 1;
        __IO uint32_t XTL : 1;
        __IO uint32_t PLL : 1;
        __IO uint32_t PLLLOCK : 1;
        uint32_t RESERVED6 : 2;
        __IO uint32_t XTHFAIL : 1;
        __IO uint32_t XTHFAULT : 1;
        __IO uint32_t XTLFAIL : 1;
        __IO uint32_t XTLFAULT : 1;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_state_field_t;

    typedef struct
    {
        __IO uint32_t USART0 : 1;
        __IO uint32_t USART1 : 1;
        __IO uint32_t LPUART0 : 1;
        __IO uint32_t LPUART1 : 1;
        __IO uint32_t I2C0 : 1;
        __IO uint32_t I2C1 : 1;
        __IO uint32_t SPI0 : 1;
        __IO uint32_t SPI1 : 1;
        __IO uint32_t ATIM0 : 1;
        __IO uint32_t LPTIM : 1;
        __IO uint32_t ATIM1 : 1;
        __IO uint32_t ATIM3 : 1;
        __IO uint32_t ATIM2 : 1;
        __IO uint32_t OPA : 1;
        __IO uint32_t WWDT : 1;
        __IO uint32_t IWDT : 1;
        __IO uint32_t ADC : 1;
        __IO uint32_t VCLVD : 1;
        __IO uint32_t I2CSLV : 1;
        uint32_t RESERVED19 : 1;
        __IO uint32_t RTC : 1;
        __IO uint32_t CTRIM : 1;
        uint32_t RESERVED22 : 2;
        __IO uint32_t TICK : 1;
        __IO uint32_t SWD : 1;
        __IO uint32_t CRC : 1;
        uint32_t RESERVED27 : 2;
        __IO uint32_t DMA : 1;
        __IO uint32_t EAU : 1;
        __IO uint32_t FLASH : 1;
    } stc_sysctrl_periclken0_field_t;

    typedef struct
    {
        __IO uint32_t GPIOA : 1;
        __IO uint32_t GPIOB : 1;
        __IO uint32_t GPIOC : 1;
        __IO uint32_t GPIOD : 1;
        uint32_t RESERVED4 : 3;
        __IO uint32_t CAN : 1;
        __IO uint32_t GTIM0 : 1;
        __IO uint32_t GTIM1 : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_periclken1_field_t;

    typedef struct
    {
        __IO uint32_t USART0 : 1;
        __IO uint32_t USART1 : 1;
        __IO uint32_t LPUART0 : 1;
        __IO uint32_t LPUART1 : 1;
        __IO uint32_t I2C0 : 1;
        __IO uint32_t I2C1 : 1;
        __IO uint32_t SPI0 : 1;
        __IO uint32_t SPI1 : 1;
        __IO uint32_t ATIM0 : 1;
        __IO uint32_t LPTIM : 1;
        __IO uint32_t ATIM1 : 1;
        __IO uint32_t ATIM3 : 1;
        __IO uint32_t ATIM2 : 1;
        __IO uint32_t OPA : 1;
        __IO uint32_t WWDT : 1;
        __IO uint32_t IWDT : 1;
        __IO uint32_t ADC : 1;
        __IO uint32_t VCLVD : 1;
        __IO uint32_t I2CSLV : 1;
        uint32_t RESERVED19 : 1;
        __IO uint32_t RTC : 1;
        __IO uint32_t CTRIM : 1;
        uint32_t RESERVED22 : 2;
        __IO uint32_t TICK : 1;
        __IO uint32_t SWD : 1;
        __IO uint32_t CRC : 1;
        uint32_t RESERVED27 : 2;
        __IO uint32_t DMA : 1;
        __IO uint32_t EAU : 1;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_perireset0_field_t;

    typedef struct
    {
        __IO uint32_t GPIOA : 1;
        __IO uint32_t GPIOB : 1;
        __IO uint32_t GPIOC : 1;
        __IO uint32_t GPIOD : 1;
        uint32_t RESERVED4 : 3;
        __IO uint32_t CAN : 1;
        __IO uint32_t GTIM0 : 1;
        __IO uint32_t GTIM1 : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_perireset1_field_t;

    typedef struct
    {
        __IO uint32_t POR5V : 1;
        __IO uint32_t POR12V : 1;
        __IO uint32_t LVD : 1;
        __IO uint32_t IWDT : 1;
        __IO uint32_t WWDT : 1;
        __IO uint32_t LOCKUP : 1;
        __IO uint32_t SYSREQ : 1;
        __IO uint32_t RSTB : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_rstflag_field_t;

    typedef struct
    {
        __IO uint32_t ATIM0 : 1;
        __IO uint32_t ATIM1 : 1;
        __IO uint32_t ATIM2 : 1;
        __IO uint32_t LPTIM : 1;
        __IO uint32_t GTIM0 : 1;
        __IO uint32_t GTIM1 : 1;
        uint32_t RESERVED6 : 1;
        __IO uint32_t CTRIM : 1;
        __IO uint32_t IWDT : 1;
        __IO uint32_t RTC : 1;
        __IO uint32_t TICK : 1;
        __IO uint32_t ATIM3 : 1;
        __IO uint32_t WWDT : 1;
        uint32_t RESERVED13 : 18;
        __IO uint32_t RSV : 1;
    } stc_sysctrl_dbgstop_field_t;

    typedef struct
    {
        __IO uint32_t RE : 1;
        __IO uint32_t TE : 1;
        __IO uint32_t PS : 1;
        __IO uint32_t PCE : 1;
        __IO uint32_t CHLEN : 1;
        __IO uint32_t STOP : 1;
        __IO uint32_t MSB : 1;
        __IO uint32_t OVER8 : 1;
        __IO uint32_t TOE : 3;
        __IO uint32_t SBS : 1;
        __IO uint32_t COMB : 1;
        __IO uint32_t MPE : 1;
        __IO uint32_t SLME : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_usart_cr1_field_t;

    typedef struct
    {
        __IO uint32_t RXDMAEN : 1;
        __IO uint32_t TXDMAEN : 1;
        __IO uint32_t RTSEN : 1;
        __IO uint32_t CTSEN : 1;
        __IO uint32_t RXINV : 1;
        __IO uint32_t TXINV : 1;
        __IO uint32_t SYNC : 1;
        __IO uint32_t SWAP : 1;
        __IO uint32_t CLKC : 2;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_usart_cr2_field_t;

    typedef struct
    {
        __IO uint32_t LINEN : 1;
        __IO uint32_t LBDE : 1;
        __IO uint32_t ABRE : 1;
        __IO uint32_t BREAK : 1;
        __IO uint32_t SCEN : 1;
        __IO uint32_t BCN : 3;
        __IO uint32_t SMCPU : 2;
        uint32_t RESERVED10 : 3;
        __IO uint32_t IREN : 1;
        __IO uint32_t IRCW : 1;
        __IO uint32_t IRMOD : 1;
        uint32_t RESERVED16 : 15;
        __IO uint32_t RSV : 1;
    } stc_usart_cr3_field_t;

    typedef struct
    {
        __IO uint32_t DIVF : 7;
        __IO uint32_t FBME : 1;
        __IO uint32_t DIVI : 8;
        __IO uint32_t PSC : 2;
        uint32_t RESERVED18 : 13;
        __IO uint32_t RSV : 1;
    } stc_usart_brr_field_t;

    typedef struct
    {
        __IO uint32_t TOR : 20;
        uint32_t RESERVED20 : 11;
        __IO uint32_t RSV : 1;
    } stc_usart_tor_field_t;

    typedef struct
    {
        __IO uint32_t TXE : 1;
        __IO uint32_t TC : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t PE : 1;
        __IO uint32_t FE : 1;
        __IO uint32_t OR : 1;
        __IO uint32_t TO : 1;
        uint32_t RESERVED7 : 1;
        __IO uint32_t MPB : 1;
        __IO uint32_t AM : 1;
        __IO uint32_t CTSV : 1;
        __IO uint32_t CTS : 1;
        __IO uint32_t ABR : 1;
        __IO uint32_t LBD : 1;
        __IO uint32_t DWK : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_usart_sr_field_t;

    typedef struct
    {
        __IO uint32_t TDR : 9;
        __IO uint32_t MPID : 1;
        uint32_t RESERVED10 : 21;
        __IO uint32_t RSV : 1;
    } stc_usart_tdr_field_t;

    typedef struct
    {
        __IO uint32_t TXE : 1;
        __IO uint32_t TC : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t PE : 1;
        __IO uint32_t FE : 1;
        __IO uint32_t OR : 1;
        __IO uint32_t TO : 1;
        uint32_t RESERVED7 : 2;
        __IO uint32_t AM : 1;
        uint32_t RESERVED10 : 1;
        __IO uint32_t CTS : 1;
        __IO uint32_t ABR : 1;
        __IO uint32_t LBD : 1;
        __IO uint32_t DWK : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_usart_ier_field_t;

    typedef struct
    {
        uint32_t RESERVED0 : 1;
        __IO uint32_t TC : 1;
        __IO uint32_t RC : 1;
        __IO uint32_t PE : 1;
        __IO uint32_t FE : 1;
        __IO uint32_t OR : 1;
        __IO uint32_t TO : 1;
        uint32_t RESERVED7 : 2;
        __IO uint32_t AM : 1;
        uint32_t RESERVED10 : 1;
        __IO uint32_t CTS : 1;
        __IO uint32_t ABR : 1;
        __IO uint32_t LBD : 1;
        __IO uint32_t DWK : 1;
        uint32_t RESERVED15 : 16;
        __IO uint32_t RSV : 1;
    } stc_usart_icr_field_t;

    typedef struct
    {
        __IO uint32_t RDR : 9;
        uint32_t RESERVED9 : 22;
        __IO uint32_t RSV : 1;
    } stc_usart_rdr_field_t;

    typedef struct
    {
        __IO uint32_t ADDR : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_usart_addr_field_t;

    typedef struct
    {
        __IO uint32_t ADDM : 8;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_usart_addmr_field_t;

    typedef struct
    {
        __IO uint32_t BDR : 12;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_usart_bdr_field_t;

    typedef struct
    {
        __IO uint32_t DCNTL : 11;
        uint32_t RESERVED11 : 5;
        __IO uint32_t DCNTH : 11;
        uint32_t RESERVED27 : 4;
        __IO uint32_t RSV : 1;
    } stc_usart_ir_field_t;

    typedef struct
    {
        __IO uint32_t DIV : 6;
        __IO uint32_t DIVEN : 1;
        __IO uint32_t REF : 1;
        __IO uint32_t BIAS : 2;
        __IO uint32_t HYS : 2;
        uint32_t RESERVED12 : 19;
        __IO uint32_t RSV : 1;
    } stc_vc_cr0_field_t;

    typedef struct
    {
        __IO uint32_t PSEL : 4;
        __IO uint32_t NSEL : 4;
        __IO uint32_t FLTEN : 1;
        __IO uint32_t FLTTIME : 3;
        __IO uint32_t FALLING : 1;
        __IO uint32_t RISING : 1;
        __IO uint32_t LEVEL : 1;
        __IO uint32_t IE : 1;
        __IO uint32_t EN : 1;
        __IO uint32_t FLTCLK : 1;
        uint32_t RESERVED18 : 13;
        __IO uint32_t RSV : 1;
    } stc_vc_cr1_field_t;

    typedef struct
    {
        __IO uint32_t POL : 1;
        __IO uint32_t ATIM0CLR : 1;
        __IO uint32_t ATIM1CLR : 1;
        __IO uint32_t ATIM2CLR : 1;
        __IO uint32_t ATIM3CLR : 1;
        __IO uint32_t ATIMBK : 1;
        __IO uint32_t WINDOW : 1;
        uint32_t RESERVED7 : 24;
        __IO uint32_t RSV : 1;
    } stc_vc_cr2_field_t;

    typedef struct
    {
        __IO uint32_t INTF : 1;
        __IO uint32_t FLTV : 1;
        uint32_t RESERVED2 : 29;
        __IO uint32_t RSV : 1;
    } stc_vc_sr_field_t;

    typedef struct
    {
        __IO uint32_t WCNT : 7;
        __IO uint32_t EN : 1;
        uint32_t RESERVED8 : 23;
        __IO uint32_t RSV : 1;
    } stc_wwdt_cr0_field_t;

    typedef struct
    {
        __IO uint32_t WINR : 7;
        uint32_t RESERVED7 : 2;
        __IO uint32_t IE : 1;
        uint32_t RESERVED10 : 1;
        __IO uint32_t PRS : 3;
        uint32_t RESERVED14 : 17;
        __IO uint32_t RSV : 1;
    } stc_wwdt_cr1_field_t;

    typedef struct
    {
        __IO uint32_t POV : 1;
        uint32_t RESERVED1 : 30;
        __IO uint32_t RSV : 1;
    } stc_wwdt_sr_field_t;

    typedef struct
    {
        union {
            __IO uint32_t BGR;
            stc_adc_bgr_field_t BGR_f;
        };
        union {
            __IO uint32_t CR0;
            stc_adc_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_adc_cr1_field_t CR1_f;
        };
        uint8_t RESERVED3[36];
        union {
            __IO uint32_t IER;
            stc_adc_ier_field_t IER_f;
        };
        uint8_t RESERVED4[12];
        union {
            __IO uint32_t SQR0;
            stc_adc_sqr0_field_t SQR0_f;
        };
        union {
            __IO uint32_t SQR1;
            stc_adc_sqr1_field_t SQR1_f;
        };
        union {
            __IO uint32_t SQR2;
            stc_adc_sqr2_field_t SQR2_f;
        };
        union {
            __IO uint32_t JQR;
            stc_adc_jqr_field_t JQR_f;
        };
        union {
            __IO uint32_t SQRRESULT0;
            stc_adc_sqrresult0_field_t SQRRESULT0_f;
        };
        union {
            __IO uint32_t SQRRESULT1;
            stc_adc_sqrresult1_field_t SQRRESULT1_f;
        };
        union {
            __IO uint32_t SQRRESULT2;
            stc_adc_sqrresult2_field_t SQRRESULT2_f;
        };
        union {
            __IO uint32_t SQRRESULT3;
            stc_adc_sqrresult3_field_t SQRRESULT3_f;
        };
        uint8_t RESERVED12[48];
        union {
            __IO uint32_t JQRRESULT0;
            stc_adc_jqrresult0_field_t JQRRESULT0_f;
        };
        union {
            __IO uint32_t JQRRESULT1;
            stc_adc_jqrresult1_field_t JQRRESULT1_f;
        };
        union {
            __IO uint32_t JQRRESULT2;
            stc_adc_jqrresult2_field_t JQRRESULT2_f;
        };
        union {
            __IO uint32_t JQRRESULT3;
            stc_adc_jqrresult3_field_t JQRRESULT3_f;
        };
        union {
            __IO uint32_t RESULT;
            stc_adc_result_field_t RESULT_f;
        };
        union {
            __IO uint32_t RESULTACC;
            stc_adc_resultacc_field_t RESULTACC_f;
        };
        union {
            __IO uint32_t HT;
            stc_adc_ht_field_t HT_f;
        };
        union {
            __IO uint32_t LT;
            stc_adc_lt_field_t LT_f;
        };
        union {
            __IO uint32_t IFR;
            stc_adc_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_adc_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t EXTTRIG0;
            stc_adc_exttrig0_field_t EXTTRIG0_f;
        };
        union {
            __IO uint32_t EXTTRIG1;
            stc_adc_exttrig1_field_t EXTTRIG1_f;
        };
        union {
            __IO uint32_t SGLSTART;
            stc_adc_sglstart_field_t SGLSTART_f;
        };
        union {
            __IO uint32_t SQRSTART;
            stc_adc_sqrstart_field_t SQRSTART_f;
        };
        union {
            __IO uint32_t JQRSTART;
            stc_adc_jqrstart_field_t JQRSTART_f;
        };
    } ADC_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t ARR;
            stc_atim3mode23_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t CNT;
            stc_atim3mode23_cnt_field_t CNT_f;
        };
        uint8_t RESERVED2[4];
        union {
            __IO uint32_t M23CR;
            stc_atim3mode23_m23cr_field_t M23CR_f;
        };
        union {
            __IO uint32_t IFR;
            stc_atim3mode23_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICLR;
            stc_atim3mode23_iclr_field_t ICLR_f;
        };
        union {
            __IO uint32_t MSCR;
            stc_atim3mode23_mscr_field_t MSCR_f;
        };
        union {
            __IO uint32_t FLTR;
            stc_atim3mode23_fltr_field_t FLTR_f;
        };
        union {
            __IO uint32_t ADTR;
            stc_atim3mode23_adtr_field_t ADTR_f;
        };
        union {
            __IO uint32_t CRCH0;
            stc_atim3mode23_crch0_field_t CRCH0_f;
        };
        union {
            __IO uint32_t CRCH1;
            stc_atim3mode23_crch1_field_t CRCH1_f;
        };
        union {
            __IO uint32_t CRCH2;
            stc_atim3mode23_crch2_field_t CRCH2_f;
        };
        union {
            __IO uint32_t DTR;
            stc_atim3mode23_dtr_field_t DTR_f;
        };
        union {
            __IO uint32_t RCR;
            stc_atim3mode23_rcr_field_t RCR_f;
        };
        uint8_t RESERVED13[4];
        union {
            __IO uint32_t CCR0A;
            stc_atim3mode23_ccr0a_field_t CCR0A_f;
        };
        union {
            __IO uint32_t CCR0B;
            stc_atim3mode23_ccr0b_field_t CCR0B_f;
        };
        union {
            __IO uint32_t CCR1A;
            stc_atim3mode23_ccr1a_field_t CCR1A_f;
        };
        union {
            __IO uint32_t CCR1B;
            stc_atim3mode23_ccr1b_field_t CCR1B_f;
        };
        union {
            __IO uint32_t CCR2A;
            stc_atim3mode23_ccr2a_field_t CCR2A_f;
        };
        union {
            __IO uint32_t CCR2B;
            stc_atim3mode23_ccr2b_field_t CCR2B_f;
        };
        union {
            __IO uint32_t CCR3A;
            stc_atim3mode23_ccr3a_field_t CCR3A_f;
        };
        union {
            __IO uint32_t CRCH3A;
            stc_atim3mode23_crch3a_field_t CRCH3A_f;
        };
        union {
            __IO uint32_t CCR3B;
            stc_atim3mode23_ccr3b_field_t CCR3B_f;
        };
        union {
            __IO uint32_t CRCH3B;
            stc_atim3mode23_crch3b_field_t CRCH3B_f;
        };
    } ATIM3MODE23_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t ARR;
            stc_atimmode0_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t CNT;
            stc_atimmode0_cnt_field_t CNT_f;
        };
        union {
            __IO uint32_t CNT32;
            stc_atimmode0_cnt32_field_t CNT32_f;
        };
        union {
            __IO uint32_t M0CR;
            stc_atimmode0_m0cr_field_t M0CR_f;
        };
        union {
            __IO uint32_t IFR;
            stc_atimmode0_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICLR;
            stc_atimmode0_iclr_field_t ICLR_f;
        };
        uint8_t RESERVED6[24];
        union {
            __IO uint32_t DTR;
            stc_atimmode0_dtr_field_t DTR_f;
        };
    } ATIMMODE0_TypeDef;

    typedef struct
    {
        uint8_t RESERVED0[4];
        union {
            __IO uint32_t CNT;
            stc_atimmode1_cnt_field_t CNT_f;
        };
        uint8_t RESERVED1[4];
        union {
            __IO uint32_t M1CR;
            stc_atimmode1_m1cr_field_t M1CR_f;
        };
        union {
            __IO uint32_t IFR;
            stc_atimmode1_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICLR;
            stc_atimmode1_iclr_field_t ICLR_f;
        };
        union {
            __IO uint32_t MSCR;
            stc_atimmode1_mscr_field_t MSCR_f;
        };
        union {
            __IO uint32_t FLTR;
            stc_atimmode1_fltr_field_t FLTR_f;
        };
        uint8_t RESERVED6[4];
        union {
            __IO uint32_t CR0;
            stc_atimmode1_cr0_field_t CR0_f;
        };
        uint8_t RESERVED7[20];
        union {
            __IO uint32_t CCR0A;
            stc_atimmode1_ccr0a_field_t CCR0A_f;
        };
    } ATIMMODE1_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t ARR;
            stc_atimmode23_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t CNT;
            stc_atimmode23_cnt_field_t CNT_f;
        };
        uint8_t RESERVED2[4];
        union {
            __IO uint32_t M23CR;
            stc_atimmode23_m23cr_field_t M23CR_f;
        };
        union {
            __IO uint32_t IFR;
            stc_atimmode23_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICLR;
            stc_atimmode23_iclr_field_t ICLR_f;
        };
        union {
            __IO uint32_t MSCR;
            stc_atimmode23_mscr_field_t MSCR_f;
        };
        union {
            __IO uint32_t FLTR;
            stc_atimmode23_fltr_field_t FLTR_f;
        };
        union {
            __IO uint32_t ADTR;
            stc_atimmode23_adtr_field_t ADTR_f;
        };
        union {
            __IO uint32_t CRCH0;
            stc_atimmode23_crch0_field_t CRCH0_f;
        };
        uint8_t RESERVED9[8];
        union {
            __IO uint32_t DTR;
            stc_atimmode23_dtr_field_t DTR_f;
        };
        union {
            __IO uint32_t RCR;
            stc_atimmode23_rcr_field_t RCR_f;
        };
        uint8_t RESERVED11[4];
        union {
            __IO uint32_t CCR0A;
            stc_atimmode23_ccr0a_field_t CCR0A_f;
        };
        union {
            __IO uint32_t CCR0B;
            stc_atimmode23_ccr0b_field_t CCR0B_f;
        };
    } ATIMMODE23_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t ARR;
            stc_btim_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t CNT;
            stc_btim_cnt_field_t CNT_f;
        };
        uint8_t RESERVED2[8];
        union {
            __IO uint32_t CR;
            stc_btim_cr_field_t CR_f;
        };
        union {
            __IO uint32_t IER;
            stc_btim_ier_field_t IER_f;
        };
        union {
            __IO uint32_t IFR;
            stc_btim_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_btim_icr_field_t ICR_f;
        };
        uint8_t RESERVED6[40];
        union {
            __IO uint32_t AIFR;
            stc_btim_aifr_field_t AIFR_f;
        };
        union {
            __IO uint32_t AICR;
            stc_btim_aicr_field_t AICR_f;
        };
    } BTIM_TypeDef;

    typedef struct
    {
        __IO uint32_t RBUF0;
        __IO uint32_t RBUF1;
        __IO uint32_t RBUF2;
        __IO uint32_t RBUF3;
        uint8_t RESERVED4[64];
        __IO uint32_t TBUF0;
        __IO uint32_t TBUF1;
        __IO uint32_t TBUF2;
        __IO uint32_t TBUF3;
        uint8_t RESERVED8[64];
        union {
            __IO uint8_t CFG_STAT;
            stc_can_cfg_stat_field_t CFG_STAT_f;
        };
        union {
            __IO uint8_t TCMD;
            stc_can_tcmd_field_t TCMD_f;
        };
        union {
            __IO uint8_t TCTRL;
            stc_can_tctrl_field_t TCTRL_f;
        };
        union {
            __IO uint8_t RCTRL;
            stc_can_rctrl_field_t RCTRL_f;
        };
        union {
            __IO uint8_t RTIE;
            stc_can_rtie_field_t RTIE_f;
        };
        union {
            __IO uint8_t RTIF;
            stc_can_rtif_field_t RTIF_f;
        };
        union {
            __IO uint8_t ERRINT;
            stc_can_errint_field_t ERRINT_f;
        };
        union {
            __IO uint8_t LIMIT;
            stc_can_limit_field_t LIMIT_f;
        };
        union {
            __IO uint32_t BT;
            stc_can_bt_field_t BT_f;
        };
        uint8_t RESERVED17[4];
        union {
            __IO uint8_t EALCAP;
            stc_can_ealcap_field_t EALCAP_f;
        };
        uint8_t RESERVED18[1];
        __IO uint8_t RECNT;
        __IO uint8_t TECNT;
        union {
            __IO uint8_t ACFCTRL;
            stc_can_acfctrl_field_t ACFCTRL_f;
        };
        uint8_t RESERVED21[1];
        union {
            __IO uint8_t ACFEN;
            stc_can_acfen_field_t ACFEN_f;
        };
        uint8_t RESERVED22[1];
        union {
            __IO uint32_t ACF;
            stc_can_acf_field_t ACF_f;
        };
        uint8_t RESERVED23[2];
        union {
            __IO uint8_t TBSLOT;
            stc_can_tbslot_field_t TBSLOT_f;
        };
        union {
            __IO uint8_t TTCFG;
            stc_can_ttcfg_field_t TTCFG_f;
        };
        union {
            __IO uint32_t REF_MSG;
            stc_can_ref_msg_field_t REF_MSG_f;
        };
        union {
            __IO uint16_t TRG_CFG;
            stc_can_trg_cfg_field_t TRG_CFG_f;
        };
        __IO uint16_t TT_TRIG;
        __IO uint16_t TT_WTRIG;
    } CAN_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CSR;
            stc_crc_csr_field_t CSR_f;
        };
        union {
            __IO uint32_t RESULT;
            stc_crc_result_field_t RESULT_f;
        };
        uint8_t RESERVED2[120];
        union {
            __IO uint32_t DATA;
            stc_crc_data_field_t DATA_f;
        };
    } CRC_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t ARR;
            stc_ctrim_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t CNT;
            stc_ctrim_cnt_field_t CNT_f;
        };
        uint8_t RESERVED2[4];
        union {
            __IO uint32_t CR0;
            stc_ctrim_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_ctrim_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t IER;
            stc_ctrim_ier_field_t IER_f;
        };
        union {
            __IO uint32_t ISR;
            stc_ctrim_isr_field_t ISR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_ctrim_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t FCAP;
            stc_ctrim_fcap_field_t FCAP_f;
        };
        union {
            __IO uint32_t TVAL;
            stc_ctrim_tval_field_t TVAL_f;
        };
        union {
            __IO uint32_t FLIM;
            stc_ctrim_flim_field_t FLIM_f;
        };
    } CTRIM_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CONF;
            stc_dmac_conf_field_t CONF_f;
        };
        uint8_t RESERVED1[12];
        union {
            __IO uint32_t CONFA0;
            stc_dmac_confa0_field_t CONFA0_f;
        };
        union {
            __IO uint32_t CONFB0;
            stc_dmac_confb0_field_t CONFB0_f;
        };
        union {
            __IO uint32_t SRCADR0;
            stc_dmac_srcadr0_field_t SRCADR0_f;
        };
        union {
            __IO uint32_t DSTADR0;
            stc_dmac_dstadr0_field_t DSTADR0_f;
        };
        union {
            __IO uint32_t CONFA1;
            stc_dmac_confa1_field_t CONFA1_f;
        };
        union {
            __IO uint32_t CONFB1;
            stc_dmac_confb1_field_t CONFB1_f;
        };
        union {
            __IO uint32_t SRCADR1;
            stc_dmac_srcadr1_field_t SRCADR1_f;
        };
        union {
            __IO uint32_t DSTADR1;
            stc_dmac_dstadr1_field_t DSTADR1_f;
        };
        union {
            __IO uint32_t CONFA2;
            stc_dmac_confa2_field_t CONFA2_f;
        };
        union {
            __IO uint32_t CONFB2;
            stc_dmac_confb2_field_t CONFB2_f;
        };
        union {
            __IO uint32_t SRCADR2;
            stc_dmac_srcadr2_field_t SRCADR2_f;
        };
        union {
            __IO uint32_t DSTADR2;
            stc_dmac_dstadr2_field_t DSTADR2_f;
        };
        union {
            __IO uint32_t CONFA3;
            stc_dmac_confa3_field_t CONFA3_f;
        };
        union {
            __IO uint32_t CONFB3;
            stc_dmac_confb3_field_t CONFB3_f;
        };
        union {
            __IO uint32_t SRCADR3;
            stc_dmac_srcadr3_field_t SRCADR3_f;
        };
        union {
            __IO uint32_t DSTADR3;
            stc_dmac_dstadr3_field_t DSTADR3_f;
        };
        union {
            __IO uint32_t CONFA4;
            stc_dmac_confa4_field_t CONFA4_f;
        };
        union {
            __IO uint32_t CONFB4;
            stc_dmac_confb4_field_t CONFB4_f;
        };
        union {
            __IO uint32_t SRCADR4;
            stc_dmac_srcadr4_field_t SRCADR4_f;
        };
        union {
            __IO uint32_t DSTADR4;
            stc_dmac_dstadr4_field_t DSTADR4_f;
        };
        union {
            __IO uint32_t CONFA5;
            stc_dmac_confa5_field_t CONFA5_f;
        };
        union {
            __IO uint32_t CONFB5;
            stc_dmac_confb5_field_t CONFB5_f;
        };
        union {
            __IO uint32_t SRCADR5;
            stc_dmac_srcadr5_field_t SRCADR5_f;
        };
        union {
            __IO uint32_t DSTADR5;
            stc_dmac_dstadr5_field_t DSTADR5_f;
        };
    } DMAC_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CSR;
            stc_eau_csr_field_t CSR_f;
        };
        union {
            __IO uint32_t DIVIDEND;
            stc_eau_dividend_field_t DIVIDEND_f;
        };
        union {
            __IO uint32_t DIVISOR;
            stc_eau_divisor_field_t DIVISOR_f;
        };
        union {
            __IO uint32_t QUOTIENT;
            stc_eau_quotient_field_t QUOTIENT_f;
        };
        union {
            __IO uint32_t REMAINDER;
            stc_eau_remainder_field_t REMAINDER_f;
        };
    } EAU_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR;
            stc_flash_cr_field_t CR_f;
        };
        union {
            __IO uint32_t WAIT;
            stc_flash_wait_field_t WAIT_f;
        };
        union {
            __IO uint32_t LOCKST;
            stc_flash_lockst_field_t LOCKST_f;
        };
        union {
            __IO uint32_t IER;
            stc_flash_ier_field_t IER_f;
        };
        union {
            __IO uint32_t IFR;
            stc_flash_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_flash_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t BYPASS;
            stc_flash_bypass_field_t BYPASS_f;
        };
        uint8_t RESERVED7[20];
        union {
            __IO uint32_t SLOCK0;
            stc_flash_slock0_field_t SLOCK0_f;
        };
        union {
            __IO uint32_t SLOCK1;
            stc_flash_slock1_field_t SLOCK1_f;
        };
    } FLASH_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t ADS;
            stc_gpio_ads_field_t ADS_f;
        };
        union {
            __IO uint32_t DIR;
            stc_gpio_dir_field_t DIR_f;
        };
        union {
            __IO uint32_t OPENDRAIN;
            stc_gpio_opendrain_field_t OPENDRAIN_f;
        };
        uint8_t RESERVED3[4];
        union {
            __IO uint32_t DRIVER;
            stc_gpio_driver_field_t DRIVER_f;
        };
        uint8_t RESERVED4[4];
        union {
            __IO uint32_t PUPD;
            stc_gpio_pupd_field_t PUPD_f;
        };
        union {
            __IO uint32_t IN;
            stc_gpio_in_field_t IN_f;
        };
        union {
            __IO uint32_t OUT;
            stc_gpio_out_field_t OUT_f;
        };
        union {
            __IO uint32_t BRR;
            stc_gpio_brr_field_t BRR_f;
        };
        union {
            __IO uint32_t BSRR;
            stc_gpio_bsrr_field_t BSRR_f;
        };
        uint8_t RESERVED9[4];
        union {
            __IO uint32_t AFRL;
            stc_gpio_afrl_field_t AFRL_f;
        };
        union {
            __IO uint32_t AFRH;
            stc_gpio_afrh_field_t AFRH_f;
        };
        union {
            __IO uint32_t HIGHIE;
            stc_gpio_highie_field_t HIGHIE_f;
        };
        union {
            __IO uint32_t LOWIE;
            stc_gpio_lowie_field_t LOWIE_f;
        };
        union {
            __IO uint32_t RISEIE;
            stc_gpio_riseie_field_t RISEIE_f;
        };
        union {
            __IO uint32_t FALLIE;
            stc_gpio_fallie_field_t FALLIE_f;
        };
        union {
            __IO uint32_t IFR;
            stc_gpio_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_gpio_icr_field_t ICR_f;
        };
    } GPIO_TypeDef;

    typedef struct
    {
        uint8_t RESERVED0[112];
        union {
            __IO uint32_t CR0;
            stc_gpioaux_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_gpioaux_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t CR2;
            stc_gpioaux_cr2_field_t CR2_f;
        };
    } GPIOAUX_TypeDef;

    typedef struct
    {
        uint8_t RESERVED0[768];
        union {
            __IO uint32_t ARR;
            stc_gtim_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t CNT;
            stc_gtim_cnt_field_t CNT_f;
        };
        union {
            __IO uint32_t CMMR;
            stc_gtim_cmmr_field_t CMMR_f;
        };
        union {
            __IO uint32_t CR1;
            stc_gtim_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t CR0;
            stc_gtim_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t IER;
            stc_gtim_ier_field_t IER_f;
        };
        union {
            __IO uint32_t IFR;
            stc_gtim_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_gtim_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t CCR0;
            stc_gtim_ccr0_field_t CCR0_f;
        };
        union {
            __IO uint32_t CCR1;
            stc_gtim_ccr1_field_t CCR1_f;
        };
        union {
            __IO uint32_t CCR2;
            stc_gtim_ccr2_field_t CCR2_f;
        };
        union {
            __IO uint32_t CCR3;
            stc_gtim_ccr3_field_t CCR3_f;
        };
    } GTIM_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t TMRUN;
            stc_i2c_tmrun_field_t TMRUN_f;
        };
        union {
            __IO uint32_t TM;
            stc_i2c_tm_field_t TM_f;
        };
        union {
            __IO uint32_t CR;
            stc_i2c_cr_field_t CR_f;
        };
        union {
            __IO uint32_t DATA;
            stc_i2c_data_field_t DATA_f;
        };
        union {
            __IO uint32_t ADDR0;
            stc_i2c_addr0_field_t ADDR0_f;
        };
        union {
            __IO uint32_t STAT;
            stc_i2c_stat_field_t STAT_f;
        };
        uint8_t RESERVED6[8];
        union {
            __IO uint32_t ADDR1;
            stc_i2c_addr1_field_t ADDR1_f;
        };
        union {
            __IO uint32_t ADDR2;
            stc_i2c_addr2_field_t ADDR2_f;
        };
        union {
            __IO uint32_t MATCH;
            stc_i2c_match_field_t MATCH_f;
        };
    } I2C_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t SR;
            stc_i2cslv_sr_field_t SR_f;
        };
        union {
            __IO uint32_t DOUTR;
            stc_i2cslv_doutr_field_t DOUTR_f;
        };
        union {
            __IO uint32_t ADIR;
            stc_i2cslv_adir_field_t ADIR_f;
        };
        union {
            __IO uint32_t SLADR0;
            stc_i2cslv_sladr0_field_t SLADR0_f;
        };
        union {
            __IO uint32_t SLADR1;
            stc_i2cslv_sladr1_field_t SLADR1_f;
        };
        union {
            __IO uint32_t SLADR2;
            stc_i2cslv_sladr2_field_t SLADR2_f;
        };
        union {
            __IO uint32_t SLADR3;
            stc_i2cslv_sladr3_field_t SLADR3_f;
        };
        union {
            __IO uint32_t DINR;
            stc_i2cslv_dinr_field_t DINR_f;
        };
        union {
            __IO uint32_t CR;
            stc_i2cslv_cr_field_t CR_f;
        };
        uint8_t RESERVED9[12];
        union {
            __IO uint32_t ADMR0;
            stc_i2cslv_admr0_field_t ADMR0_f;
        };
        uint8_t RESERVED10[12];
        union {
            __IO uint32_t FLT;
            stc_i2cslv_flt_field_t FLT_f;
        };
        union {
            __IO uint32_t TOR;
            stc_i2cslv_tor_field_t TOR_f;
        };
        union {
            __IO uint32_t ODDR;
            stc_i2cslv_oddr_field_t ODDR_f;
        };
        union {
            __IO uint32_t RSR;
            stc_i2cslv_rsr_field_t RSR_f;
        };
        union {
            __IO uint32_t IER;
            stc_i2cslv_ier_field_t IER_f;
        };
        union {
            __IO uint32_t ICR;
            stc_i2cslv_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t DIDR;
            stc_i2cslv_didr_field_t DIDR_f;
        };
    } I2CSLV_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t KR;
            stc_iwdt_kr_field_t KR_f;
        };
        union {
            __IO uint32_t CR;
            stc_iwdt_cr_field_t CR_f;
        };
        union {
            __IO uint32_t ARR;
            stc_iwdt_arr_field_t ARR_f;
        };
        union {
            __IO uint32_t SR;
            stc_iwdt_sr_field_t SR_f;
        };
        union {
            __IO uint32_t WINR;
            stc_iwdt_winr_field_t WINR_f;
        };
    } IWDT_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CNT;
            stc_lptim_cnt_field_t CNT_f;
        };
        union {
            __IO uint32_t ARR;
            stc_lptim_arr_field_t ARR_f;
        };
        uint8_t RESERVED2[4];
        union {
            __IO uint32_t CR;
            stc_lptim_cr_field_t CR_f;
        };
        union {
            __IO uint32_t IFR;
            stc_lptim_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICLR;
            stc_lptim_iclr_field_t ICLR_f;
        };
    } LPTIM_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t SBUF;
            stc_lpuart_sbuf_field_t SBUF_f;
        };
        union {
            __IO uint32_t SCON;
            stc_lpuart_scon_field_t SCON_f;
        };
        union {
            __IO uint32_t SADDR;
            stc_lpuart_saddr_field_t SADDR_f;
        };
        union {
            __IO uint32_t SADEN;
            stc_lpuart_saden_field_t SADEN_f;
        };
        union {
            __IO uint32_t ISR;
            stc_lpuart_isr_field_t ISR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_lpuart_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t SCNT;
            stc_lpuart_scnt_field_t SCNT_f;
        };
    } LPUART_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR;
            stc_lvd_cr_field_t CR_f;
        };
        union {
            __IO uint32_t SR;
            stc_lvd_sr_field_t SR_f;
        };
    } LVD_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR0;
            stc_opa_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_opa_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t AZ;
            stc_opa_az_field_t AZ_f;
        };
    } OPA_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR;
            stc_ram_cr_field_t CR_f;
        };
        union {
            __IO uint32_t ERRADDR;
            stc_ram_erraddr_field_t ERRADDR_f;
        };
        union {
            __IO uint32_t IFR;
            stc_ram_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICLR;
            stc_ram_iclr_field_t ICLR_f;
        };
    } RAM_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR0;
            stc_rtc_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_rtc_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t SEC;
            stc_rtc_sec_field_t SEC_f;
        };
        union {
            __IO uint32_t MIN;
            stc_rtc_min_field_t MIN_f;
        };
        union {
            __IO uint32_t HOUR;
            stc_rtc_hour_field_t HOUR_f;
        };
        union {
            __IO uint32_t WEEK;
            stc_rtc_week_field_t WEEK_f;
        };
        union {
            __IO uint32_t DAY;
            stc_rtc_day_field_t DAY_f;
        };
        union {
            __IO uint32_t MON;
            stc_rtc_mon_field_t MON_f;
        };
        union {
            __IO uint32_t YEAR;
            stc_rtc_year_field_t YEAR_f;
        };
        uint8_t RESERVED9[12];
        union {
            __IO uint32_t COMPEN;
            stc_rtc_compen_field_t COMPEN_f;
        };
        uint8_t RESERVED10[8];
        union {
            __IO uint32_t CR2;
            stc_rtc_cr2_field_t CR2_f;
        };
        union {
            __IO uint32_t ALMA;
            stc_rtc_alma_field_t ALMA_f;
        };
        union {
            __IO uint32_t ALMB;
            stc_rtc_almb_field_t ALMB_f;
        };
        union {
            __IO uint32_t TSTR;
            stc_rtc_tstr_field_t TSTR_f;
        };
        union {
            __IO uint32_t TSDR;
            stc_rtc_tsdr_field_t TSDR_f;
        };
        union {
            __IO uint32_t WUTARR;
            stc_rtc_wutarr_field_t WUTARR_f;
        };
        union {
            __IO uint32_t IER;
            stc_rtc_ier_field_t IER_f;
        };
        union {
            __IO uint32_t IFR;
            stc_rtc_ifr_field_t IFR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_rtc_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t WPR;
            stc_rtc_wpr_field_t WPR_f;
        };
    } RTC_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR0;
            stc_spi_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_spi_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t HDOE;
            stc_spi_hdoe_field_t HDOE_f;
        };
        union {
            __IO uint32_t SSI;
            stc_spi_ssi_field_t SSI_f;
        };
        union {
            __IO uint32_t SR;
            stc_spi_sr_field_t SR_f;
        };
        union {
            __IO uint32_t ICR;
            stc_spi_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t DR;
            stc_spi_dr_field_t DR_f;
        };
    } SPI_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR0;
            stc_sysctrl_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_sysctrl_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t CR2;
            stc_sysctrl_cr2_field_t CR2_f;
        };
        union {
            __IO uint32_t CR3;
            stc_sysctrl_cr3_field_t CR3_f;
        };
        union {
            __IO uint32_t RCHCR;
            stc_sysctrl_rchcr_field_t RCHCR_f;
        };
        union {
            __IO uint32_t XTHCR;
            stc_sysctrl_xthcr_field_t XTHCR_f;
        };
        union {
            __IO uint32_t RCLCR;
            stc_sysctrl_rclcr_field_t RCLCR_f;
        };
        union {
            __IO uint32_t XTLCR;
            stc_sysctrl_xtlcr_field_t XTLCR_f;
        };
        union {
            __IO uint32_t PLLCR;
            stc_sysctrl_pllcr_field_t PLLCR_f;
        };
        union {
            __IO uint32_t RCHTRIM;
            stc_sysctrl_rchtrim_field_t RCHTRIM_f;
        };
        union {
            __IO uint32_t RCLTRIM;
            stc_sysctrl_rcltrim_field_t RCLTRIM_f;
        };
        union {
            __IO uint32_t STATE;
            stc_sysctrl_state_field_t STATE_f;
        };
        union {
            __IO uint32_t PERICLKEN0;
            stc_sysctrl_periclken0_field_t PERICLKEN0_f;
        };
        union {
            __IO uint32_t PERICLKEN1;
            stc_sysctrl_periclken1_field_t PERICLKEN1_f;
        };
        union {
            __IO uint32_t PERIRESET0;
            stc_sysctrl_perireset0_field_t PERIRESET0_f;
        };
        union {
            __IO uint32_t PERIRESET1;
            stc_sysctrl_perireset1_field_t PERIRESET1_f;
        };
        union {
            __IO uint32_t RSTFLAG;
            stc_sysctrl_rstflag_field_t RSTFLAG_f;
        };
        union {
            __IO uint32_t DBGSTOP;
            stc_sysctrl_dbgstop_field_t DBGSTOP_f;
        };
    } SYSCTRL_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR1;
            stc_usart_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t CR2;
            stc_usart_cr2_field_t CR2_f;
        };
        union {
            __IO uint32_t CR3;
            stc_usart_cr3_field_t CR3_f;
        };
        union {
            __IO uint32_t BRR;
            stc_usart_brr_field_t BRR_f;
        };
        union {
            __IO uint32_t TOR;
            stc_usart_tor_field_t TOR_f;
        };
        union {
            __IO uint32_t SR;
            stc_usart_sr_field_t SR_f;
        };
        union {
            __IO uint32_t TDR;
            stc_usart_tdr_field_t TDR_f;
        };
        union {
            __IO uint32_t IER;
            stc_usart_ier_field_t IER_f;
        };
        union {
            __IO uint32_t ICR;
            stc_usart_icr_field_t ICR_f;
        };
        union {
            __IO uint32_t RDR;
            stc_usart_rdr_field_t RDR_f;
        };
        union {
            __IO uint32_t ADDR;
            stc_usart_addr_field_t ADDR_f;
        };
        union {
            __IO uint32_t ADDMR;
            stc_usart_addmr_field_t ADDMR_f;
        };
        union {
            __IO uint32_t BDR;
            stc_usart_bdr_field_t BDR_f;
        };
        uint8_t RESERVED13[188];
        union {
            __IO uint32_t IR;
            stc_usart_ir_field_t IR_f;
        };
    } USART_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR0;
            stc_vc_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_vc_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t CR2;
            stc_vc_cr2_field_t CR2_f;
        };
        union {
            __IO uint32_t SR;
            stc_vc_sr_field_t SR_f;
        };
    } VC_TypeDef;

    typedef struct
    {
        union {
            __IO uint32_t CR0;
            stc_wwdt_cr0_field_t CR0_f;
        };
        union {
            __IO uint32_t CR1;
            stc_wwdt_cr1_field_t CR1_f;
        };
        union {
            __IO uint32_t SR;
            stc_wwdt_sr_field_t SR_f;
        };
    } WWDT_TypeDef;

#define PERIPH_BASE (0x40000000UL)
#define ADC_BASE (PERIPH_BASE + 0x00002500UL)
#define ATIM0MODE0_BASE (PERIPH_BASE + 0x00003000UL)
#define ATIM0MODE1_BASE (PERIPH_BASE + 0x00003000UL)
#define ATIM0MODE23_BASE (PERIPH_BASE + 0x00003000UL)
#define ATIM1MODE0_BASE (PERIPH_BASE + 0x00003400UL)
#define ATIM1MODE1_BASE (PERIPH_BASE + 0x00003400UL)
#define ATIM1MODE23_BASE (PERIPH_BASE + 0x00003400UL)
#define ATIM2MODE0_BASE (PERIPH_BASE + 0x00003800UL)
#define ATIM2MODE1_BASE (PERIPH_BASE + 0x00003800UL)
#define ATIM2MODE23_BASE (PERIPH_BASE + 0x00003800UL)
#define ATIM3MODE0_BASE (PERIPH_BASE + 0x00005800UL)
#define ATIM3MODE1_BASE (PERIPH_BASE + 0x00005800UL)
#define ATIM3MODE23_BASE (PERIPH_BASE + 0x00005800UL)
#define BTIM0_BASE (PERIPH_BASE + 0x00001800UL)
#define BTIM1_BASE (PERIPH_BASE + 0x00001900UL)
#define BTIM2_BASE (PERIPH_BASE + 0x00001A00UL)
#define BTIM3_BASE (PERIPH_BASE + 0x00001C00UL)
#define BTIM4_BASE (PERIPH_BASE + 0x00001D00UL)
#define BTIM5_BASE (PERIPH_BASE + 0x00001E00UL)
#define CAN_BASE (PERIPH_BASE + 0x00030000UL)
#define CRC_BASE (PERIPH_BASE + 0x00020800UL)
#define CTRIM_BASE (PERIPH_BASE + 0x00005000UL)
#define DMAC_BASE (PERIPH_BASE + 0x00021000UL)
#define EAU_BASE (PERIPH_BASE + 0x00021800UL)
#define FLASH_BASE (PERIPH_BASE + 0x00020000UL)
#define GPIOA_BASE (PERIPH_BASE + 0x00020C00UL)
#define GPIOAUX_BASE (PERIPH_BASE + 0x00002000UL)
#define GPIOB_BASE (PERIPH_BASE + 0x00021C00UL)
#define GPIOC_BASE (PERIPH_BASE + 0x00022000UL)
#define GPIOD_BASE (PERIPH_BASE + 0x00022400UL)
#define GTIM0_BASE (PERIPH_BASE + 0x00001800UL)
#define GTIM1_BASE (PERIPH_BASE + 0x00001C00UL)
#define I2C0_BASE (PERIPH_BASE + 0x00000400UL)
#define I2C1_BASE (PERIPH_BASE + 0x00004400UL)
#define I2CSLV_BASE (PERIPH_BASE + 0x00004C00UL)
#define IWDT_BASE (PERIPH_BASE + 0x00001080UL)
#define LPTIM_BASE (PERIPH_BASE + 0x00000C00UL)
#define LPUART0_BASE (PERIPH_BASE + 0x00000000UL)
#define LPUART1_BASE (PERIPH_BASE + 0x00004000UL)
#define LVD_BASE (PERIPH_BASE + 0x00002480UL)
#define OPA_BASE (PERIPH_BASE + 0x00002600UL)
#define RAM_BASE (PERIPH_BASE + 0x00020400UL)
#define RTC_BASE (PERIPH_BASE + 0x00001400UL)
#define SPI0_BASE (PERIPH_BASE + 0x00000800UL)
#define SPI1_BASE (PERIPH_BASE + 0x00004800UL)
#define SYSCTRL_BASE (PERIPH_BASE + 0x00002000UL)
#define USART0_BASE (PERIPH_BASE + 0x00006000UL)
#define USART1_BASE (PERIPH_BASE + 0x00006400UL)
#define VC0_BASE (PERIPH_BASE + 0x00002400UL)
#define VC1_BASE (PERIPH_BASE + 0x00002410UL)
#define WWDT_BASE (PERIPH_BASE + 0x00006800UL)

#define HC_ADC ((ADC_TypeDef *)0x40002500UL)
#define HC_ATIM0MODE0 ((ATIMMODE0_TypeDef *)0x40003000UL)
#define HC_ATIM0MODE1 ((ATIMMODE1_TypeDef *)0x40003000UL)
#define HC_ATIM0MODE23 ((ATIMMODE23_TypeDef *)0x40003000UL)
#define HC_ATIM1MODE0 ((ATIMMODE0_TypeDef *)0x40003400UL)
#define HC_ATIM1MODE1 ((ATIMMODE1_TypeDef *)0x40003400UL)
#define HC_ATIM1MODE23 ((ATIMMODE23_TypeDef *)0x40003400UL)
#define HC_ATIM2MODE0 ((ATIMMODE0_TypeDef *)0x40003800UL)
#define HC_ATIM2MODE1 ((ATIMMODE1_TypeDef *)0x40003800UL)
#define HC_ATIM2MODE23 ((ATIMMODE23_TypeDef *)0x40003800UL)
#define HC_ATIM3MODE0 ((ATIMMODE0_TypeDef *)0x40005800UL)
#define HC_ATIM3MODE1 ((ATIMMODE1_TypeDef *)0x40005800UL)
#define HC_ATIM3MODE23 ((ATIM3MODE23_TypeDef *)0x40005800UL)
#define HC_BTIM0 ((BTIM_TypeDef *)0x40001800UL)
#define HC_BTIM1 ((BTIM_TypeDef *)0x40001900UL)
#define HC_BTIM2 ((BTIM_TypeDef *)0x40001A00UL)
#define HC_BTIM3 ((BTIM_TypeDef *)0x40001C00UL)
#define HC_BTIM4 ((BTIM_TypeDef *)0x40001D00UL)
#define HC_BTIM5 ((BTIM_TypeDef *)0x40001E00UL)
#define HC_CAN ((CAN_TypeDef *)0x40030000UL)
#define HC_CRC ((CRC_TypeDef *)0x40020800UL)
#define HC_CTRIM ((CTRIM_TypeDef *)0x40005000UL)
#define HC_DMAC ((DMAC_TypeDef *)0x40021000UL)
#define HC_EAU ((EAU_TypeDef *)0x40021800UL)
#define HC_FLASH ((FLASH_TypeDef *)0x40020000UL)
#define HC_GPIOA ((GPIO_TypeDef *)0x40020C00UL)
#define HC_GPIOAUX ((GPIOAUX_TypeDef *)0x40002000UL)
#define HC_GPIOB ((GPIO_TypeDef *)0x40021C00UL)
#define HC_GPIOC ((GPIO_TypeDef *)0x40022000UL)
#define HC_GPIOD ((GPIO_TypeDef *)0x40022400UL)
#define HC_GTIM0 ((GTIM_TypeDef *)0x40001800UL)
#define HC_GTIM1 ((GTIM_TypeDef *)0x40001C00UL)
#define HC_I2C0 ((I2C_TypeDef *)0x40000400UL)
#define HC_I2C1 ((I2C_TypeDef *)0x40004400UL)
#define HC_I2CSLV ((I2CSLV_TypeDef *)0x40004C00UL)
#define HC_IWDT ((IWDT_TypeDef *)0x40001080UL)
#define HC_LPTIM ((LPTIM_TypeDef *)0x40000C00UL)
#define HC_LPUART0 ((LPUART_TypeDef *)0x40000000UL)
#define HC_LPUART1 ((LPUART_TypeDef *)0x40004000UL)
#define HC_LVD ((LVD_TypeDef *)0x40002480UL)
#define HC_OPA ((OPA_TypeDef *)0x40002600UL)
#define HC_RAM ((RAM_TypeDef *)0x40020400UL)
#define HC_RTC ((RTC_TypeDef *)0x40001400UL)
#define HC_SPI0 ((SPI_TypeDef *)0x40000800UL)
#define HC_SPI1 ((SPI_TypeDef *)0x40004800UL)
#define HC_SYSCTRL ((SYSCTRL_TypeDef *)0x40002000UL)
#define HC_USART0 ((USART_TypeDef *)0x40006000UL)
#define HC_USART1 ((USART_TypeDef *)0x40006400UL)
#define HC_VC0 ((VC_TypeDef *)0x40002400UL)
#define HC_VC1 ((VC_TypeDef *)0x40002410UL)
#define HC_WWDT ((WWDT_TypeDef *)0x40006800UL)

//********************    Bits Define For Peripheral ADC    ********************//
// ADC_BGR
#define ADC_BGR_BGREN_Pos (0U)
#define ADC_BGR_BGREN_Msk (0x1UL << ADC_BGR_BGREN_Pos)
#define ADC_BGR_BGREN ADC_BGR_BGREN_Msk
#define ADC_BGR_TSEN_Pos (1U)
#define ADC_BGR_TSEN_Msk (0x1UL << ADC_BGR_TSEN_Pos)
#define ADC_BGR_TSEN ADC_BGR_TSEN_Msk

// ADC_CR0
#define ADC_CR0_EN_Pos (0U)
#define ADC_CR0_EN_Msk (0x1UL << ADC_CR0_EN_Pos)
#define ADC_CR0_EN ADC_CR0_EN_Msk
#define ADC_CR0_CKDIV_Pos (1U)
#define ADC_CR0_CKDIV_Msk (0x7UL << ADC_CR0_CKDIV_Pos)
#define ADC_CR0_CKDIV ADC_CR0_CKDIV_Msk
#define ADC_CR0_SGLMUX_Pos (4U)
#define ADC_CR0_SGLMUX_Msk (0x1FUL << ADC_CR0_SGLMUX_Pos)
#define ADC_CR0_SGLMUX ADC_CR0_SGLMUX_Msk
#define ADC_CR0_REF_Pos (9U)
#define ADC_CR0_REF_Msk (0x3UL << ADC_CR0_REF_Pos)
#define ADC_CR0_REF ADC_CR0_REF_Msk
#define ADC_CR0_BUF_Pos (11U)
#define ADC_CR0_BUF_Msk (0x1UL << ADC_CR0_BUF_Pos)
#define ADC_CR0_BUF ADC_CR0_BUF_Msk
#define ADC_CR0_SAM_Pos (12U)
#define ADC_CR0_SAM_Msk (0x3UL << ADC_CR0_SAM_Pos)
#define ADC_CR0_SAM ADC_CR0_SAM_Msk

// ADC_CR1
#define ADC_CR1_MODE_Pos (0U)
#define ADC_CR1_MODE_Msk (0x3UL << ADC_CR1_MODE_Pos)
#define ADC_CR1_MODE ADC_CR1_MODE_Msk
#define ADC_CR1_ALIGN_Pos (2U)
#define ADC_CR1_ALIGN_Msk (0x1UL << ADC_CR1_ALIGN_Pos)
#define ADC_CR1_ALIGN ADC_CR1_ALIGN_Msk
#define ADC_CR1_THCH_Pos (3U)
#define ADC_CR1_THCH_Msk (0x1FUL << ADC_CR1_THCH_Pos)
#define ADC_CR1_THCH ADC_CR1_THCH_Msk
#define ADC_CR1_OVMD_Pos (10U)
#define ADC_CR1_OVMD_Msk (0x1UL << ADC_CR1_OVMD_Pos)
#define ADC_CR1_OVMD ADC_CR1_OVMD_Msk
#define ADC_CR1_RACCEN_Pos (11U)
#define ADC_CR1_RACCEN_Msk (0x1UL << ADC_CR1_RACCEN_Pos)
#define ADC_CR1_RACCEN ADC_CR1_RACCEN_Msk
#define ADC_CR1_LTCMP_Pos (12U)
#define ADC_CR1_LTCMP_Msk (0x1UL << ADC_CR1_LTCMP_Pos)
#define ADC_CR1_LTCMP ADC_CR1_LTCMP_Msk
#define ADC_CR1_HTCMP_Pos (13U)
#define ADC_CR1_HTCMP_Msk (0x1UL << ADC_CR1_HTCMP_Pos)
#define ADC_CR1_HTCMP ADC_CR1_HTCMP_Msk
#define ADC_CR1_REGCMP_Pos (14U)
#define ADC_CR1_REGCMP_Msk (0x1UL << ADC_CR1_REGCMP_Pos)
#define ADC_CR1_REGCMP ADC_CR1_REGCMP_Msk
#define ADC_CR1_RACCCLR_Pos (15U)
#define ADC_CR1_RACCCLR_Msk (0x1UL << ADC_CR1_RACCCLR_Pos)
#define ADC_CR1_RACCCLR ADC_CR1_RACCCLR_Msk

// ADC_IER
#define ADC_IER_ESG_Pos (0U)
#define ADC_IER_ESG_Msk (0x1UL << ADC_IER_ESG_Pos)
#define ADC_IER_ESG ADC_IER_ESG_Msk
#define ADC_IER_LTI_Pos (1U)
#define ADC_IER_LTI_Msk (0x1UL << ADC_IER_LTI_Pos)
#define ADC_IER_LTI ADC_IER_LTI_Msk
#define ADC_IER_HTI_Pos (2U)
#define ADC_IER_HTI_Msk (0x1UL << ADC_IER_HTI_Pos)
#define ADC_IER_HTI ADC_IER_HTI_Msk
#define ADC_IER_RGI_Pos (3U)
#define ADC_IER_RGI_Msk (0x1UL << ADC_IER_RGI_Pos)
#define ADC_IER_RGI ADC_IER_RGI_Msk
#define ADC_IER_EOS_Pos (4U)
#define ADC_IER_EOS_Msk (0x1UL << ADC_IER_EOS_Pos)
#define ADC_IER_EOS ADC_IER_EOS_Msk
#define ADC_IER_EOJ_Pos (5U)
#define ADC_IER_EOJ_Msk (0x1UL << ADC_IER_EOJ_Pos)
#define ADC_IER_EOJ ADC_IER_EOJ_Msk
#define ADC_IER_EOC_Pos (6U)
#define ADC_IER_EOC_Msk (0x1UL << ADC_IER_EOC_Pos)
#define ADC_IER_EOC ADC_IER_EOC_Msk
#define ADC_IER_DEOC_Pos (7U)
#define ADC_IER_DEOC_Msk (0x1UL << ADC_IER_DEOC_Pos)
#define ADC_IER_DEOC ADC_IER_DEOC_Msk
#define ADC_IER_DEOJ_Pos (8U)
#define ADC_IER_DEOJ_Msk (0x1UL << ADC_IER_DEOJ_Pos)
#define ADC_IER_DEOJ ADC_IER_DEOJ_Msk
#define ADC_IER_OV_Pos (9U)
#define ADC_IER_OV_Msk (0x1UL << ADC_IER_OV_Pos)
#define ADC_IER_OV ADC_IER_OV_Msk

// ADC_SQR0
#define ADC_SQR0_CH0MUX_Pos (0U)
#define ADC_SQR0_CH0MUX_Msk (0x1FUL << ADC_SQR0_CH0MUX_Pos)
#define ADC_SQR0_CH0MUX ADC_SQR0_CH0MUX_Msk
#define ADC_SQR0_CH1MUX_Pos (5U)
#define ADC_SQR0_CH1MUX_Msk (0x1FUL << ADC_SQR0_CH1MUX_Pos)
#define ADC_SQR0_CH1MUX ADC_SQR0_CH1MUX_Msk
#define ADC_SQR0_CH2MUX_Pos (10U)
#define ADC_SQR0_CH2MUX_Msk (0x1FUL << ADC_SQR0_CH2MUX_Pos)
#define ADC_SQR0_CH2MUX ADC_SQR0_CH2MUX_Msk
#define ADC_SQR0_CH3MUX_Pos (15U)
#define ADC_SQR0_CH3MUX_Msk (0x1FUL << ADC_SQR0_CH3MUX_Pos)
#define ADC_SQR0_CH3MUX ADC_SQR0_CH3MUX_Msk
#define ADC_SQR0_CH4MUX_Pos (20U)
#define ADC_SQR0_CH4MUX_Msk (0x1FUL << ADC_SQR0_CH4MUX_Pos)
#define ADC_SQR0_CH4MUX ADC_SQR0_CH4MUX_Msk
#define ADC_SQR0_CH5MUX_Pos (25U)
#define ADC_SQR0_CH5MUX_Msk (0x1FUL << ADC_SQR0_CH5MUX_Pos)
#define ADC_SQR0_CH5MUX ADC_SQR0_CH5MUX_Msk

// ADC_SQR1
#define ADC_SQR1_CH6MUX_Pos (0U)
#define ADC_SQR1_CH6MUX_Msk (0x1FUL << ADC_SQR1_CH6MUX_Pos)
#define ADC_SQR1_CH6MUX ADC_SQR1_CH6MUX_Msk
#define ADC_SQR1_CH7MUX_Pos (5U)
#define ADC_SQR1_CH7MUX_Msk (0x1FUL << ADC_SQR1_CH7MUX_Pos)
#define ADC_SQR1_CH7MUX ADC_SQR1_CH7MUX_Msk
#define ADC_SQR1_CH8MUX_Pos (10U)
#define ADC_SQR1_CH8MUX_Msk (0x1FUL << ADC_SQR1_CH8MUX_Pos)
#define ADC_SQR1_CH8MUX ADC_SQR1_CH8MUX_Msk
#define ADC_SQR1_CH9MUX_Pos (15U)
#define ADC_SQR1_CH9MUX_Msk (0x1FUL << ADC_SQR1_CH9MUX_Pos)
#define ADC_SQR1_CH9MUX ADC_SQR1_CH9MUX_Msk
#define ADC_SQR1_CH10MUX_Pos (20U)
#define ADC_SQR1_CH10MUX_Msk (0x1FUL << ADC_SQR1_CH10MUX_Pos)
#define ADC_SQR1_CH10MUX ADC_SQR1_CH10MUX_Msk
#define ADC_SQR1_CH11MUX_Pos (25U)
#define ADC_SQR1_CH11MUX_Msk (0x1FUL << ADC_SQR1_CH11MUX_Pos)
#define ADC_SQR1_CH11MUX ADC_SQR1_CH11MUX_Msk

// ADC_SQR2
#define ADC_SQR2_CH12MUX_Pos (0U)
#define ADC_SQR2_CH12MUX_Msk (0x1FUL << ADC_SQR2_CH12MUX_Pos)
#define ADC_SQR2_CH12MUX ADC_SQR2_CH12MUX_Msk
#define ADC_SQR2_CH13MUX_Pos (5U)
#define ADC_SQR2_CH13MUX_Msk (0x1FUL << ADC_SQR2_CH13MUX_Pos)
#define ADC_SQR2_CH13MUX ADC_SQR2_CH13MUX_Msk
#define ADC_SQR2_CH14MUX_Pos (10U)
#define ADC_SQR2_CH14MUX_Msk (0x1FUL << ADC_SQR2_CH14MUX_Pos)
#define ADC_SQR2_CH14MUX ADC_SQR2_CH14MUX_Msk
#define ADC_SQR2_CH15MUX_Pos (15U)
#define ADC_SQR2_CH15MUX_Msk (0x1FUL << ADC_SQR2_CH15MUX_Pos)
#define ADC_SQR2_CH15MUX ADC_SQR2_CH15MUX_Msk
#define ADC_SQR2_CNT_Pos (20U)
#define ADC_SQR2_CNT_Msk (0xFUL << ADC_SQR2_CNT_Pos)
#define ADC_SQR2_CNT ADC_SQR2_CNT_Msk

// ADC_JQR
#define ADC_JQR_CH0MUX_Pos (0U)
#define ADC_JQR_CH0MUX_Msk (0x1FUL << ADC_JQR_CH0MUX_Pos)
#define ADC_JQR_CH0MUX ADC_JQR_CH0MUX_Msk
#define ADC_JQR_CH1MUX_Pos (5U)
#define ADC_JQR_CH1MUX_Msk (0x1FUL << ADC_JQR_CH1MUX_Pos)
#define ADC_JQR_CH1MUX ADC_JQR_CH1MUX_Msk
#define ADC_JQR_CH2MUX_Pos (10U)
#define ADC_JQR_CH2MUX_Msk (0x1FUL << ADC_JQR_CH2MUX_Pos)
#define ADC_JQR_CH2MUX ADC_JQR_CH2MUX_Msk
#define ADC_JQR_CH3MUX_Pos (15U)
#define ADC_JQR_CH3MUX_Msk (0x1FUL << ADC_JQR_CH3MUX_Pos)
#define ADC_JQR_CH3MUX ADC_JQR_CH3MUX_Msk
#define ADC_JQR_CNT_Pos (20U)
#define ADC_JQR_CNT_Msk (0x3UL << ADC_JQR_CNT_Pos)
#define ADC_JQR_CNT ADC_JQR_CNT_Msk

// ADC_SQRRESULT0
#define ADC_SQRRESULT0_RESULT_Pos (0U)
#define ADC_SQRRESULT0_RESULT_Msk (0xFFFFUL << ADC_SQRRESULT0_RESULT_Pos)
#define ADC_SQRRESULT0_RESULT ADC_SQRRESULT0_RESULT_Msk

// ADC_SQRRESULT1
#define ADC_SQRRESULT1_RESULT_Pos (0U)
#define ADC_SQRRESULT1_RESULT_Msk (0xFFFFUL << ADC_SQRRESULT1_RESULT_Pos)
#define ADC_SQRRESULT1_RESULT ADC_SQRRESULT1_RESULT_Msk

// ADC_SQRRESULT2
#define ADC_SQRRESULT2_RESULT_Pos (0U)
#define ADC_SQRRESULT2_RESULT_Msk (0xFFFFUL << ADC_SQRRESULT2_RESULT_Pos)
#define ADC_SQRRESULT2_RESULT ADC_SQRRESULT2_RESULT_Msk

// ADC_SQRRESULT3
#define ADC_SQRRESULT3_RESULT_Pos (0U)
#define ADC_SQRRESULT3_RESULT_Msk (0xFFFFUL << ADC_SQRRESULT3_RESULT_Pos)
#define ADC_SQRRESULT3_RESULT ADC_SQRRESULT3_RESULT_Msk

// ADC_JQRRESULT0
#define ADC_JQRRESULT0_RESULT_Pos (0U)
#define ADC_JQRRESULT0_RESULT_Msk (0xFFFFUL << ADC_JQRRESULT0_RESULT_Pos)
#define ADC_JQRRESULT0_RESULT ADC_JQRRESULT0_RESULT_Msk

// ADC_JQRRESULT1
#define ADC_JQRRESULT1_RESULT_Pos (0U)
#define ADC_JQRRESULT1_RESULT_Msk (0xFFFFUL << ADC_JQRRESULT1_RESULT_Pos)
#define ADC_JQRRESULT1_RESULT ADC_JQRRESULT1_RESULT_Msk

// ADC_JQRRESULT2
#define ADC_JQRRESULT2_RESULT_Pos (0U)
#define ADC_JQRRESULT2_RESULT_Msk (0xFFFFUL << ADC_JQRRESULT2_RESULT_Pos)
#define ADC_JQRRESULT2_RESULT ADC_JQRRESULT2_RESULT_Msk

// ADC_JQRRESULT3
#define ADC_JQRRESULT3_RESULT_Pos (0U)
#define ADC_JQRRESULT3_RESULT_Msk (0xFFFFUL << ADC_JQRRESULT3_RESULT_Pos)
#define ADC_JQRRESULT3_RESULT ADC_JQRRESULT3_RESULT_Msk

// ADC_RESULT
#define ADC_RESULT_RESULT_Pos (0U)
#define ADC_RESULT_RESULT_Msk (0xFFFFUL << ADC_RESULT_RESULT_Pos)
#define ADC_RESULT_RESULT ADC_RESULT_RESULT_Msk

// ADC_RESULTACC
#define ADC_RESULTACC_RESULTACC_Pos (0U)
#define ADC_RESULTACC_RESULTACC_Msk (0xFFFFFUL << ADC_RESULTACC_RESULTACC_Pos)
#define ADC_RESULTACC_RESULTACC ADC_RESULTACC_RESULTACC_Msk

// ADC_HT
#define ADC_HT_HT_Pos (0U)
#define ADC_HT_HT_Msk (0xFFFUL << ADC_HT_HT_Pos)
#define ADC_HT_HT ADC_HT_HT_Msk

// ADC_LT
#define ADC_LT_LT_Pos (0U)
#define ADC_LT_LT_Msk (0xFFFUL << ADC_LT_LT_Pos)
#define ADC_LT_LT ADC_LT_LT_Msk

// ADC_IFR
#define ADC_IFR_ESG_Pos (0U)
#define ADC_IFR_ESG_Msk (0x1UL << ADC_IFR_ESG_Pos)
#define ADC_IFR_ESG ADC_IFR_ESG_Msk
#define ADC_IFR_LTI_Pos (1U)
#define ADC_IFR_LTI_Msk (0x1UL << ADC_IFR_LTI_Pos)
#define ADC_IFR_LTI ADC_IFR_LTI_Msk
#define ADC_IFR_HTI_Pos (2U)
#define ADC_IFR_HTI_Msk (0x1UL << ADC_IFR_HTI_Pos)
#define ADC_IFR_HTI ADC_IFR_HTI_Msk
#define ADC_IFR_RGI_Pos (3U)
#define ADC_IFR_RGI_Msk (0x1UL << ADC_IFR_RGI_Pos)
#define ADC_IFR_RGI ADC_IFR_RGI_Msk
#define ADC_IFR_EOS_Pos (4U)
#define ADC_IFR_EOS_Msk (0x1UL << ADC_IFR_EOS_Pos)
#define ADC_IFR_EOS ADC_IFR_EOS_Msk
#define ADC_IFR_EOJ_Pos (5U)
#define ADC_IFR_EOJ_Msk (0x1UL << ADC_IFR_EOJ_Pos)
#define ADC_IFR_EOJ ADC_IFR_EOJ_Msk
#define ADC_IFR_EOC_Pos (6U)
#define ADC_IFR_EOC_Msk (0x1UL << ADC_IFR_EOC_Pos)
#define ADC_IFR_EOC ADC_IFR_EOC_Msk
#define ADC_IFR_OV_Pos (9U)
#define ADC_IFR_OV_Msk (0x1UL << ADC_IFR_OV_Pos)
#define ADC_IFR_OV ADC_IFR_OV_Msk
#define ADC_IFR_RDY_Pos (10U)
#define ADC_IFR_RDY_Msk (0x1UL << ADC_IFR_RDY_Pos)
#define ADC_IFR_RDY ADC_IFR_RDY_Msk

// ADC_ICR
#define ADC_ICR_ESG_Pos (0U)
#define ADC_ICR_ESG_Msk (0x1UL << ADC_ICR_ESG_Pos)
#define ADC_ICR_ESG ADC_ICR_ESG_Msk
#define ADC_ICR_LTI_Pos (1U)
#define ADC_ICR_LTI_Msk (0x1UL << ADC_ICR_LTI_Pos)
#define ADC_ICR_LTI ADC_ICR_LTI_Msk
#define ADC_ICR_HTI_Pos (2U)
#define ADC_ICR_HTI_Msk (0x1UL << ADC_ICR_HTI_Pos)
#define ADC_ICR_HTI ADC_ICR_HTI_Msk
#define ADC_ICR_RGI_Pos (3U)
#define ADC_ICR_RGI_Msk (0x1UL << ADC_ICR_RGI_Pos)
#define ADC_ICR_RGI ADC_ICR_RGI_Msk
#define ADC_ICR_EOS_Pos (4U)
#define ADC_ICR_EOS_Msk (0x1UL << ADC_ICR_EOS_Pos)
#define ADC_ICR_EOS ADC_ICR_EOS_Msk
#define ADC_ICR_EOJ_Pos (5U)
#define ADC_ICR_EOJ_Msk (0x1UL << ADC_ICR_EOJ_Pos)
#define ADC_ICR_EOJ ADC_ICR_EOJ_Msk
#define ADC_ICR_EOC_Pos (6U)
#define ADC_ICR_EOC_Msk (0x1UL << ADC_ICR_EOC_Pos)
#define ADC_ICR_EOC ADC_ICR_EOC_Msk
#define ADC_ICR_OV_Pos (9U)
#define ADC_ICR_OV_Msk (0x1UL << ADC_ICR_OV_Pos)
#define ADC_ICR_OV ADC_ICR_OV_Msk

// ADC_EXTTRIG0
#define ADC_EXTTRIG0_TRIG_Pos (0U)
#define ADC_EXTTRIG0_TRIG_Msk (0x1FUL << ADC_EXTTRIG0_TRIG_Pos)
#define ADC_EXTTRIG0_TRIG ADC_EXTTRIG0_TRIG_Msk
#define ADC_EXTTRIG0_DELAY_Pos (5U)
#define ADC_EXTTRIG0_DELAY_Msk (0x1UL << ADC_EXTTRIG0_DELAY_Pos)
#define ADC_EXTTRIG0_DELAY ADC_EXTTRIG0_DELAY_Msk

// ADC_EXTTRIG1
#define ADC_EXTTRIG1_TRIG_Pos (0U)
#define ADC_EXTTRIG1_TRIG_Msk (0x1FUL << ADC_EXTTRIG1_TRIG_Pos)
#define ADC_EXTTRIG1_TRIG ADC_EXTTRIG1_TRIG_Msk
#define ADC_EXTTRIG1_DELAY_Pos (5U)
#define ADC_EXTTRIG1_DELAY_Msk (0x1UL << ADC_EXTTRIG1_DELAY_Pos)
#define ADC_EXTTRIG1_DELAY ADC_EXTTRIG1_DELAY_Msk

// ADC_SGLSTART
#define ADC_SGLSTART_START_Pos (0U)
#define ADC_SGLSTART_START_Msk (0x1UL << ADC_SGLSTART_START_Pos)
#define ADC_SGLSTART_START ADC_SGLSTART_START_Msk

// ADC_SQRSTART
#define ADC_SQRSTART_START_Pos (0U)
#define ADC_SQRSTART_START_Msk (0x1UL << ADC_SQRSTART_START_Pos)
#define ADC_SQRSTART_START ADC_SQRSTART_START_Msk

// ADC_JQRSTART
#define ADC_JQRSTART_START_Pos (0U)
#define ADC_JQRSTART_START_Msk (0x1UL << ADC_JQRSTART_START_Pos)
#define ADC_JQRSTART_START ADC_JQRSTART_START_Msk

//********************    Bits Define For Peripheral ATIM3MODE23    ********************//
// ATIM3MODE23_ARR
#define ATIM3MODE23_ARR_ARR_Pos (0U)
#define ATIM3MODE23_ARR_ARR_Msk (0xFFFFUL << ATIM3MODE23_ARR_ARR_Pos)
#define ATIM3MODE23_ARR_ARR ATIM3MODE23_ARR_ARR_Msk

// ATIM3MODE23_CNT
#define ATIM3MODE23_CNT_CNT_Pos (0U)
#define ATIM3MODE23_CNT_CNT_Msk (0xFFFFUL << ATIM3MODE23_CNT_CNT_Pos)
#define ATIM3MODE23_CNT_CNT ATIM3MODE23_CNT_CNT_Msk

// ATIM3MODE23_M23CR
#define ATIM3MODE23_M23CR_CTEN_Pos (0U)
#define ATIM3MODE23_M23CR_CTEN_Msk (0x1UL << ATIM3MODE23_M23CR_CTEN_Pos)
#define ATIM3MODE23_M23CR_CTEN ATIM3MODE23_M23CR_CTEN_Msk
#define ATIM3MODE23_M23CR_COMP_Pos (1U)
#define ATIM3MODE23_M23CR_COMP_Msk (0x1UL << ATIM3MODE23_M23CR_COMP_Pos)
#define ATIM3MODE23_M23CR_COMP ATIM3MODE23_M23CR_COMP_Msk
#define ATIM3MODE23_M23CR_CT_Pos (2U)
#define ATIM3MODE23_M23CR_CT_Msk (0x1UL << ATIM3MODE23_M23CR_CT_Pos)
#define ATIM3MODE23_M23CR_CT ATIM3MODE23_M23CR_CT_Msk
#define ATIM3MODE23_M23CR_PWM2S_Pos (3U)
#define ATIM3MODE23_M23CR_PWM2S_Msk (0x1UL << ATIM3MODE23_M23CR_PWM2S_Pos)
#define ATIM3MODE23_M23CR_PWM2S ATIM3MODE23_M23CR_PWM2S_Msk
#define ATIM3MODE23_M23CR_PRS_Pos (4U)
#define ATIM3MODE23_M23CR_PRS_Msk (0x7UL << ATIM3MODE23_M23CR_PRS_Pos)
#define ATIM3MODE23_M23CR_PRS ATIM3MODE23_M23CR_PRS_Msk
#define ATIM3MODE23_M23CR_BUFPEN_Pos (7U)
#define ATIM3MODE23_M23CR_BUFPEN_Msk (0x1UL << ATIM3MODE23_M23CR_BUFPEN_Pos)
#define ATIM3MODE23_M23CR_BUFPEN ATIM3MODE23_M23CR_BUFPEN_Msk
#define ATIM3MODE23_M23CR_CRG_Pos (8U)
#define ATIM3MODE23_M23CR_CRG_Msk (0x1UL << ATIM3MODE23_M23CR_CRG_Pos)
#define ATIM3MODE23_M23CR_CRG ATIM3MODE23_M23CR_CRG_Msk
#define ATIM3MODE23_M23CR_CFG_Pos (9U)
#define ATIM3MODE23_M23CR_CFG_Msk (0x1UL << ATIM3MODE23_M23CR_CFG_Pos)
#define ATIM3MODE23_M23CR_CFG ATIM3MODE23_M23CR_CFG_Msk
#define ATIM3MODE23_M23CR_UIE_Pos (10U)
#define ATIM3MODE23_M23CR_UIE_Msk (0x1UL << ATIM3MODE23_M23CR_UIE_Pos)
#define ATIM3MODE23_M23CR_UIE ATIM3MODE23_M23CR_UIE_Msk
#define ATIM3MODE23_M23CR_UDE_Pos (11U)
#define ATIM3MODE23_M23CR_UDE_Msk (0x1UL << ATIM3MODE23_M23CR_UDE_Pos)
#define ATIM3MODE23_M23CR_UDE ATIM3MODE23_M23CR_UDE_Msk
#define ATIM3MODE23_M23CR_MODE_Pos (12U)
#define ATIM3MODE23_M23CR_MODE_Msk (0x3UL << ATIM3MODE23_M23CR_MODE_Pos)
#define ATIM3MODE23_M23CR_MODE ATIM3MODE23_M23CR_MODE_Msk
#define ATIM3MODE23_M23CR_ONESHOT_Pos (14U)
#define ATIM3MODE23_M23CR_ONESHOT_Msk (0x1UL << ATIM3MODE23_M23CR_ONESHOT_Pos)
#define ATIM3MODE23_M23CR_ONESHOT ATIM3MODE23_M23CR_ONESHOT_Msk
#define ATIM3MODE23_M23CR_CSG_Pos (15U)
#define ATIM3MODE23_M23CR_CSG_Msk (0x1UL << ATIM3MODE23_M23CR_CSG_Pos)
#define ATIM3MODE23_M23CR_CSG ATIM3MODE23_M23CR_CSG_Msk
#define ATIM3MODE23_M23CR_OCCS_Pos (16U)
#define ATIM3MODE23_M23CR_OCCS_Msk (0x1UL << ATIM3MODE23_M23CR_OCCS_Pos)
#define ATIM3MODE23_M23CR_OCCS ATIM3MODE23_M23CR_OCCS_Msk
#define ATIM3MODE23_M23CR_URS_Pos (17U)
#define ATIM3MODE23_M23CR_URS_Msk (0x1UL << ATIM3MODE23_M23CR_URS_Pos)
#define ATIM3MODE23_M23CR_URS ATIM3MODE23_M23CR_URS_Msk
#define ATIM3MODE23_M23CR_TDE_Pos (18U)
#define ATIM3MODE23_M23CR_TDE_Msk (0x1UL << ATIM3MODE23_M23CR_TDE_Pos)
#define ATIM3MODE23_M23CR_TDE ATIM3MODE23_M23CR_TDE_Msk
#define ATIM3MODE23_M23CR_TIE_Pos (19U)
#define ATIM3MODE23_M23CR_TIE_Msk (0x1UL << ATIM3MODE23_M23CR_TIE_Pos)
#define ATIM3MODE23_M23CR_TIE ATIM3MODE23_M23CR_TIE_Msk
#define ATIM3MODE23_M23CR_BIE_Pos (20U)
#define ATIM3MODE23_M23CR_BIE_Msk (0x1UL << ATIM3MODE23_M23CR_BIE_Pos)
#define ATIM3MODE23_M23CR_BIE ATIM3MODE23_M23CR_BIE_Msk
#define ATIM3MODE23_M23CR_CIS_Pos (21U)
#define ATIM3MODE23_M23CR_CIS_Msk (0x3UL << ATIM3MODE23_M23CR_CIS_Pos)
#define ATIM3MODE23_M23CR_CIS ATIM3MODE23_M23CR_CIS_Msk
#define ATIM3MODE23_M23CR_OCCE_Pos (23U)
#define ATIM3MODE23_M23CR_OCCE_Msk (0x1UL << ATIM3MODE23_M23CR_OCCE_Pos)
#define ATIM3MODE23_M23CR_OCCE ATIM3MODE23_M23CR_OCCE_Msk
#define ATIM3MODE23_M23CR_TG_Pos (24U)
#define ATIM3MODE23_M23CR_TG_Msk (0x1UL << ATIM3MODE23_M23CR_TG_Pos)
#define ATIM3MODE23_M23CR_TG ATIM3MODE23_M23CR_TG_Msk
#define ATIM3MODE23_M23CR_UG_Pos (25U)
#define ATIM3MODE23_M23CR_UG_Msk (0x1UL << ATIM3MODE23_M23CR_UG_Pos)
#define ATIM3MODE23_M23CR_UG ATIM3MODE23_M23CR_UG_Msk
#define ATIM3MODE23_M23CR_BG_Pos (26U)
#define ATIM3MODE23_M23CR_BG_Msk (0x1UL << ATIM3MODE23_M23CR_BG_Pos)
#define ATIM3MODE23_M23CR_BG ATIM3MODE23_M23CR_BG_Msk
#define ATIM3MODE23_M23CR_DIR_Pos (27U)
#define ATIM3MODE23_M23CR_DIR_Msk (0x1UL << ATIM3MODE23_M23CR_DIR_Pos)
#define ATIM3MODE23_M23CR_DIR ATIM3MODE23_M23CR_DIR_Msk
#define ATIM3MODE23_M23CR_OVE_Pos (28U)
#define ATIM3MODE23_M23CR_OVE_Msk (0x1UL << ATIM3MODE23_M23CR_OVE_Pos)
#define ATIM3MODE23_M23CR_OVE ATIM3MODE23_M23CR_OVE_Msk
#define ATIM3MODE23_M23CR_UNDE_Pos (29U)
#define ATIM3MODE23_M23CR_UNDE_Msk (0x1UL << ATIM3MODE23_M23CR_UNDE_Pos)
#define ATIM3MODE23_M23CR_UNDE ATIM3MODE23_M23CR_UNDE_Msk

// ATIM3MODE23_IFR
#define ATIM3MODE23_IFR_UI_Pos (0U)
#define ATIM3MODE23_IFR_UI_Msk (0x1UL << ATIM3MODE23_IFR_UI_Pos)
#define ATIM3MODE23_IFR_UI ATIM3MODE23_IFR_UI_Msk
#define ATIM3MODE23_IFR_CA0_Pos (2U)
#define ATIM3MODE23_IFR_CA0_Msk (0x1UL << ATIM3MODE23_IFR_CA0_Pos)
#define ATIM3MODE23_IFR_CA0 ATIM3MODE23_IFR_CA0_Msk
#define ATIM3MODE23_IFR_CA1_Pos (3U)
#define ATIM3MODE23_IFR_CA1_Msk (0x1UL << ATIM3MODE23_IFR_CA1_Pos)
#define ATIM3MODE23_IFR_CA1 ATIM3MODE23_IFR_CA1_Msk
#define ATIM3MODE23_IFR_CA2_Pos (4U)
#define ATIM3MODE23_IFR_CA2_Msk (0x1UL << ATIM3MODE23_IFR_CA2_Pos)
#define ATIM3MODE23_IFR_CA2 ATIM3MODE23_IFR_CA2_Msk
#define ATIM3MODE23_IFR_CB0_Pos (5U)
#define ATIM3MODE23_IFR_CB0_Msk (0x1UL << ATIM3MODE23_IFR_CB0_Pos)
#define ATIM3MODE23_IFR_CB0 ATIM3MODE23_IFR_CB0_Msk
#define ATIM3MODE23_IFR_CB1_Pos (6U)
#define ATIM3MODE23_IFR_CB1_Msk (0x1UL << ATIM3MODE23_IFR_CB1_Pos)
#define ATIM3MODE23_IFR_CB1 ATIM3MODE23_IFR_CB1_Msk
#define ATIM3MODE23_IFR_CB2_Pos (7U)
#define ATIM3MODE23_IFR_CB2_Msk (0x1UL << ATIM3MODE23_IFR_CB2_Pos)
#define ATIM3MODE23_IFR_CB2 ATIM3MODE23_IFR_CB2_Msk
#define ATIM3MODE23_IFR_CA0E_Pos (8U)
#define ATIM3MODE23_IFR_CA0E_Msk (0x1UL << ATIM3MODE23_IFR_CA0E_Pos)
#define ATIM3MODE23_IFR_CA0E ATIM3MODE23_IFR_CA0E_Msk
#define ATIM3MODE23_IFR_CA1E_Pos (9U)
#define ATIM3MODE23_IFR_CA1E_Msk (0x1UL << ATIM3MODE23_IFR_CA1E_Pos)
#define ATIM3MODE23_IFR_CA1E ATIM3MODE23_IFR_CA1E_Msk
#define ATIM3MODE23_IFR_CA2E_Pos (10U)
#define ATIM3MODE23_IFR_CA2E_Msk (0x1UL << ATIM3MODE23_IFR_CA2E_Pos)
#define ATIM3MODE23_IFR_CA2E ATIM3MODE23_IFR_CA2E_Msk
#define ATIM3MODE23_IFR_CB0E_Pos (11U)
#define ATIM3MODE23_IFR_CB0E_Msk (0x1UL << ATIM3MODE23_IFR_CB0E_Pos)
#define ATIM3MODE23_IFR_CB0E ATIM3MODE23_IFR_CB0E_Msk
#define ATIM3MODE23_IFR_CB1E_Pos (12U)
#define ATIM3MODE23_IFR_CB1E_Msk (0x1UL << ATIM3MODE23_IFR_CB1E_Pos)
#define ATIM3MODE23_IFR_CB1E ATIM3MODE23_IFR_CB1E_Msk
#define ATIM3MODE23_IFR_CB2E_Pos (13U)
#define ATIM3MODE23_IFR_CB2E_Msk (0x1UL << ATIM3MODE23_IFR_CB2E_Pos)
#define ATIM3MODE23_IFR_CB2E ATIM3MODE23_IFR_CB2E_Msk
#define ATIM3MODE23_IFR_BI_Pos (14U)
#define ATIM3MODE23_IFR_BI_Msk (0x1UL << ATIM3MODE23_IFR_BI_Pos)
#define ATIM3MODE23_IFR_BI ATIM3MODE23_IFR_BI_Msk
#define ATIM3MODE23_IFR_TI_Pos (15U)
#define ATIM3MODE23_IFR_TI_Msk (0x1UL << ATIM3MODE23_IFR_TI_Pos)
#define ATIM3MODE23_IFR_TI ATIM3MODE23_IFR_TI_Msk
#define ATIM3MODE23_IFR_OV_Pos (16U)
#define ATIM3MODE23_IFR_OV_Msk (0x1UL << ATIM3MODE23_IFR_OV_Pos)
#define ATIM3MODE23_IFR_OV ATIM3MODE23_IFR_OV_Msk
#define ATIM3MODE23_IFR_UND_Pos (17U)
#define ATIM3MODE23_IFR_UND_Msk (0x1UL << ATIM3MODE23_IFR_UND_Pos)
#define ATIM3MODE23_IFR_UND ATIM3MODE23_IFR_UND_Msk
#define ATIM3MODE23_IFR_CA3A_Pos (18U)
#define ATIM3MODE23_IFR_CA3A_Msk (0x1UL << ATIM3MODE23_IFR_CA3A_Pos)
#define ATIM3MODE23_IFR_CA3A ATIM3MODE23_IFR_CA3A_Msk
#define ATIM3MODE23_IFR_CA3B_Pos (19U)
#define ATIM3MODE23_IFR_CA3B_Msk (0x1UL << ATIM3MODE23_IFR_CA3B_Pos)
#define ATIM3MODE23_IFR_CA3B ATIM3MODE23_IFR_CA3B_Msk

// ATIM3MODE23_ICLR
#define ATIM3MODE23_ICLR_UI_Pos (0U)
#define ATIM3MODE23_ICLR_UI_Msk (0x1UL << ATIM3MODE23_ICLR_UI_Pos)
#define ATIM3MODE23_ICLR_UI ATIM3MODE23_ICLR_UI_Msk
#define ATIM3MODE23_ICLR_CA0_Pos (2U)
#define ATIM3MODE23_ICLR_CA0_Msk (0x1UL << ATIM3MODE23_ICLR_CA0_Pos)
#define ATIM3MODE23_ICLR_CA0 ATIM3MODE23_ICLR_CA0_Msk
#define ATIM3MODE23_ICLR_CA1_Pos (3U)
#define ATIM3MODE23_ICLR_CA1_Msk (0x1UL << ATIM3MODE23_ICLR_CA1_Pos)
#define ATIM3MODE23_ICLR_CA1 ATIM3MODE23_ICLR_CA1_Msk
#define ATIM3MODE23_ICLR_CA2_Pos (4U)
#define ATIM3MODE23_ICLR_CA2_Msk (0x1UL << ATIM3MODE23_ICLR_CA2_Pos)
#define ATIM3MODE23_ICLR_CA2 ATIM3MODE23_ICLR_CA2_Msk
#define ATIM3MODE23_ICLR_CB0_Pos (5U)
#define ATIM3MODE23_ICLR_CB0_Msk (0x1UL << ATIM3MODE23_ICLR_CB0_Pos)
#define ATIM3MODE23_ICLR_CB0 ATIM3MODE23_ICLR_CB0_Msk
#define ATIM3MODE23_ICLR_CB1_Pos (6U)
#define ATIM3MODE23_ICLR_CB1_Msk (0x1UL << ATIM3MODE23_ICLR_CB1_Pos)
#define ATIM3MODE23_ICLR_CB1 ATIM3MODE23_ICLR_CB1_Msk
#define ATIM3MODE23_ICLR_CB2_Pos (7U)
#define ATIM3MODE23_ICLR_CB2_Msk (0x1UL << ATIM3MODE23_ICLR_CB2_Pos)
#define ATIM3MODE23_ICLR_CB2 ATIM3MODE23_ICLR_CB2_Msk
#define ATIM3MODE23_ICLR_CA0E_Pos (8U)
#define ATIM3MODE23_ICLR_CA0E_Msk (0x1UL << ATIM3MODE23_ICLR_CA0E_Pos)
#define ATIM3MODE23_ICLR_CA0E ATIM3MODE23_ICLR_CA0E_Msk
#define ATIM3MODE23_ICLR_CA1E_Pos (9U)
#define ATIM3MODE23_ICLR_CA1E_Msk (0x1UL << ATIM3MODE23_ICLR_CA1E_Pos)
#define ATIM3MODE23_ICLR_CA1E ATIM3MODE23_ICLR_CA1E_Msk
#define ATIM3MODE23_ICLR_CA2E_Pos (10U)
#define ATIM3MODE23_ICLR_CA2E_Msk (0x1UL << ATIM3MODE23_ICLR_CA2E_Pos)
#define ATIM3MODE23_ICLR_CA2E ATIM3MODE23_ICLR_CA2E_Msk
#define ATIM3MODE23_ICLR_CB0E_Pos (11U)
#define ATIM3MODE23_ICLR_CB0E_Msk (0x1UL << ATIM3MODE23_ICLR_CB0E_Pos)
#define ATIM3MODE23_ICLR_CB0E ATIM3MODE23_ICLR_CB0E_Msk
#define ATIM3MODE23_ICLR_CB1E_Pos (12U)
#define ATIM3MODE23_ICLR_CB1E_Msk (0x1UL << ATIM3MODE23_ICLR_CB1E_Pos)
#define ATIM3MODE23_ICLR_CB1E ATIM3MODE23_ICLR_CB1E_Msk
#define ATIM3MODE23_ICLR_CB2E_Pos (13U)
#define ATIM3MODE23_ICLR_CB2E_Msk (0x1UL << ATIM3MODE23_ICLR_CB2E_Pos)
#define ATIM3MODE23_ICLR_CB2E ATIM3MODE23_ICLR_CB2E_Msk
#define ATIM3MODE23_ICLR_BI_Pos (14U)
#define ATIM3MODE23_ICLR_BI_Msk (0x1UL << ATIM3MODE23_ICLR_BI_Pos)
#define ATIM3MODE23_ICLR_BI ATIM3MODE23_ICLR_BI_Msk
#define ATIM3MODE23_ICLR_TI_Pos (15U)
#define ATIM3MODE23_ICLR_TI_Msk (0x1UL << ATIM3MODE23_ICLR_TI_Pos)
#define ATIM3MODE23_ICLR_TI ATIM3MODE23_ICLR_TI_Msk
#define ATIM3MODE23_ICLR_OV_Pos (16U)
#define ATIM3MODE23_ICLR_OV_Msk (0x1UL << ATIM3MODE23_ICLR_OV_Pos)
#define ATIM3MODE23_ICLR_OV ATIM3MODE23_ICLR_OV_Msk
#define ATIM3MODE23_ICLR_UND_Pos (17U)
#define ATIM3MODE23_ICLR_UND_Msk (0x1UL << ATIM3MODE23_ICLR_UND_Pos)
#define ATIM3MODE23_ICLR_UND ATIM3MODE23_ICLR_UND_Msk
#define ATIM3MODE23_ICLR_CA3A_Pos (18U)
#define ATIM3MODE23_ICLR_CA3A_Msk (0x1UL << ATIM3MODE23_ICLR_CA3A_Pos)
#define ATIM3MODE23_ICLR_CA3A ATIM3MODE23_ICLR_CA3A_Msk
#define ATIM3MODE23_ICLR_CA3B_Pos (19U)
#define ATIM3MODE23_ICLR_CA3B_Msk (0x1UL << ATIM3MODE23_ICLR_CA3B_Pos)
#define ATIM3MODE23_ICLR_CA3B ATIM3MODE23_ICLR_CA3B_Msk

// ATIM3MODE23_MSCR
#define ATIM3MODE23_MSCR_MMS_Pos (0U)
#define ATIM3MODE23_MSCR_MMS_Msk (0x7UL << ATIM3MODE23_MSCR_MMS_Pos)
#define ATIM3MODE23_MSCR_MMS ATIM3MODE23_MSCR_MMS_Msk
#define ATIM3MODE23_MSCR_CCDS_Pos (3U)
#define ATIM3MODE23_MSCR_CCDS_Msk (0x1UL << ATIM3MODE23_MSCR_CCDS_Pos)
#define ATIM3MODE23_MSCR_CCDS ATIM3MODE23_MSCR_CCDS_Msk
#define ATIM3MODE23_MSCR_MSM_Pos (4U)
#define ATIM3MODE23_MSCR_MSM_Msk (0x1UL << ATIM3MODE23_MSCR_MSM_Pos)
#define ATIM3MODE23_MSCR_MSM ATIM3MODE23_MSCR_MSM_Msk
#define ATIM3MODE23_MSCR_TS_Pos (5U)
#define ATIM3MODE23_MSCR_TS_Msk (0x7UL << ATIM3MODE23_MSCR_TS_Pos)
#define ATIM3MODE23_MSCR_TS ATIM3MODE23_MSCR_TS_Msk
#define ATIM3MODE23_MSCR_SMS_Pos (8U)
#define ATIM3MODE23_MSCR_SMS_Msk (0x7UL << ATIM3MODE23_MSCR_SMS_Pos)
#define ATIM3MODE23_MSCR_SMS ATIM3MODE23_MSCR_SMS_Msk
#define ATIM3MODE23_MSCR_IA0S_Pos (11U)
#define ATIM3MODE23_MSCR_IA0S_Msk (0x1UL << ATIM3MODE23_MSCR_IA0S_Pos)
#define ATIM3MODE23_MSCR_IA0S ATIM3MODE23_MSCR_IA0S_Msk
#define ATIM3MODE23_MSCR_IB0S_Pos (12U)
#define ATIM3MODE23_MSCR_IB0S_Msk (0x1UL << ATIM3MODE23_MSCR_IB0S_Pos)
#define ATIM3MODE23_MSCR_IB0S ATIM3MODE23_MSCR_IB0S_Msk

// ATIM3MODE23_FLTR
#define ATIM3MODE23_FLTR_OCMA0FLTA0_Pos (0U)
#define ATIM3MODE23_FLTR_OCMA0FLTA0_Msk (0x7UL << ATIM3MODE23_FLTR_OCMA0FLTA0_Pos)
#define ATIM3MODE23_FLTR_OCMA0FLTA0 ATIM3MODE23_FLTR_OCMA0FLTA0_Msk
#define ATIM3MODE23_FLTR_CCPA0_Pos (3U)
#define ATIM3MODE23_FLTR_CCPA0_Msk (0x1UL << ATIM3MODE23_FLTR_CCPA0_Pos)
#define ATIM3MODE23_FLTR_CCPA0 ATIM3MODE23_FLTR_CCPA0_Msk
#define ATIM3MODE23_FLTR_OCMB0FLTB0_Pos (4U)
#define ATIM3MODE23_FLTR_OCMB0FLTB0_Msk (0x7UL << ATIM3MODE23_FLTR_OCMB0FLTB0_Pos)
#define ATIM3MODE23_FLTR_OCMB0FLTB0 ATIM3MODE23_FLTR_OCMB0FLTB0_Msk
#define ATIM3MODE23_FLTR_CCPB0_Pos (7U)
#define ATIM3MODE23_FLTR_CCPB0_Msk (0x1UL << ATIM3MODE23_FLTR_CCPB0_Pos)
#define ATIM3MODE23_FLTR_CCPB0 ATIM3MODE23_FLTR_CCPB0_Msk
#define ATIM3MODE23_FLTR_OCMA1FLTA1_Pos (8U)
#define ATIM3MODE23_FLTR_OCMA1FLTA1_Msk (0x7UL << ATIM3MODE23_FLTR_OCMA1FLTA1_Pos)
#define ATIM3MODE23_FLTR_OCMA1FLTA1 ATIM3MODE23_FLTR_OCMA1FLTA1_Msk
#define ATIM3MODE23_FLTR_CCPA1_Pos (11U)
#define ATIM3MODE23_FLTR_CCPA1_Msk (0x1UL << ATIM3MODE23_FLTR_CCPA1_Pos)
#define ATIM3MODE23_FLTR_CCPA1 ATIM3MODE23_FLTR_CCPA1_Msk
#define ATIM3MODE23_FLTR_OCMB1FLTB1_Pos (12U)
#define ATIM3MODE23_FLTR_OCMB1FLTB1_Msk (0x7UL << ATIM3MODE23_FLTR_OCMB1FLTB1_Pos)
#define ATIM3MODE23_FLTR_OCMB1FLTB1 ATIM3MODE23_FLTR_OCMB1FLTB1_Msk
#define ATIM3MODE23_FLTR_CCPB1_Pos (15U)
#define ATIM3MODE23_FLTR_CCPB1_Msk (0x1UL << ATIM3MODE23_FLTR_CCPB1_Pos)
#define ATIM3MODE23_FLTR_CCPB1 ATIM3MODE23_FLTR_CCPB1_Msk
#define ATIM3MODE23_FLTR_OCMA2FLTA2_Pos (16U)
#define ATIM3MODE23_FLTR_OCMA2FLTA2_Msk (0x7UL << ATIM3MODE23_FLTR_OCMA2FLTA2_Pos)
#define ATIM3MODE23_FLTR_OCMA2FLTA2 ATIM3MODE23_FLTR_OCMA2FLTA2_Msk
#define ATIM3MODE23_FLTR_CCPA2_Pos (19U)
#define ATIM3MODE23_FLTR_CCPA2_Msk (0x1UL << ATIM3MODE23_FLTR_CCPA2_Pos)
#define ATIM3MODE23_FLTR_CCPA2 ATIM3MODE23_FLTR_CCPA2_Msk
#define ATIM3MODE23_FLTR_OCMB2FLTB2_Pos (20U)
#define ATIM3MODE23_FLTR_OCMB2FLTB2_Msk (0x7UL << ATIM3MODE23_FLTR_OCMB2FLTB2_Pos)
#define ATIM3MODE23_FLTR_OCMB2FLTB2 ATIM3MODE23_FLTR_OCMB2FLTB2_Msk
#define ATIM3MODE23_FLTR_CCPB2_Pos (23U)
#define ATIM3MODE23_FLTR_CCPB2_Msk (0x1UL << ATIM3MODE23_FLTR_CCPB2_Pos)
#define ATIM3MODE23_FLTR_CCPB2 ATIM3MODE23_FLTR_CCPB2_Msk
#define ATIM3MODE23_FLTR_FLTBK_Pos (24U)
#define ATIM3MODE23_FLTR_FLTBK_Msk (0x7UL << ATIM3MODE23_FLTR_FLTBK_Pos)
#define ATIM3MODE23_FLTR_FLTBK ATIM3MODE23_FLTR_FLTBK_Msk
#define ATIM3MODE23_FLTR_BKP_Pos (27U)
#define ATIM3MODE23_FLTR_BKP_Msk (0x1UL << ATIM3MODE23_FLTR_BKP_Pos)
#define ATIM3MODE23_FLTR_BKP ATIM3MODE23_FLTR_BKP_Msk
#define ATIM3MODE23_FLTR_FLTET_Pos (28U)
#define ATIM3MODE23_FLTR_FLTET_Msk (0x7UL << ATIM3MODE23_FLTR_FLTET_Pos)
#define ATIM3MODE23_FLTR_FLTET ATIM3MODE23_FLTR_FLTET_Msk
#define ATIM3MODE23_FLTR_ETP_Pos (31U)
#define ATIM3MODE23_FLTR_ETP_Msk (0x1UL << ATIM3MODE23_FLTR_ETP_Pos)
#define ATIM3MODE23_FLTR_ETP ATIM3MODE23_FLTR_ETP_Msk

// ATIM3MODE23_ADTR
#define ATIM3MODE23_ADTR_UEVE_Pos (0U)
#define ATIM3MODE23_ADTR_UEVE_Msk (0x1UL << ATIM3MODE23_ADTR_UEVE_Pos)
#define ATIM3MODE23_ADTR_UEVE ATIM3MODE23_ADTR_UEVE_Msk
#define ATIM3MODE23_ADTR_CMA0E_Pos (1U)
#define ATIM3MODE23_ADTR_CMA0E_Msk (0x1UL << ATIM3MODE23_ADTR_CMA0E_Pos)
#define ATIM3MODE23_ADTR_CMA0E ATIM3MODE23_ADTR_CMA0E_Msk
#define ATIM3MODE23_ADTR_CMA1E_Pos (2U)
#define ATIM3MODE23_ADTR_CMA1E_Msk (0x1UL << ATIM3MODE23_ADTR_CMA1E_Pos)
#define ATIM3MODE23_ADTR_CMA1E ATIM3MODE23_ADTR_CMA1E_Msk
#define ATIM3MODE23_ADTR_CMA2E_Pos (3U)
#define ATIM3MODE23_ADTR_CMA2E_Msk (0x1UL << ATIM3MODE23_ADTR_CMA2E_Pos)
#define ATIM3MODE23_ADTR_CMA2E ATIM3MODE23_ADTR_CMA2E_Msk
#define ATIM3MODE23_ADTR_CMB0E_Pos (4U)
#define ATIM3MODE23_ADTR_CMB0E_Msk (0x1UL << ATIM3MODE23_ADTR_CMB0E_Pos)
#define ATIM3MODE23_ADTR_CMB0E ATIM3MODE23_ADTR_CMB0E_Msk
#define ATIM3MODE23_ADTR_CMB1E_Pos (5U)
#define ATIM3MODE23_ADTR_CMB1E_Msk (0x1UL << ATIM3MODE23_ADTR_CMB1E_Pos)
#define ATIM3MODE23_ADTR_CMB1E ATIM3MODE23_ADTR_CMB1E_Msk
#define ATIM3MODE23_ADTR_CMB2E_Pos (6U)
#define ATIM3MODE23_ADTR_CMB2E_Msk (0x1UL << ATIM3MODE23_ADTR_CMB2E_Pos)
#define ATIM3MODE23_ADTR_CMB2E ATIM3MODE23_ADTR_CMB2E_Msk
#define ATIM3MODE23_ADTR_ADTE_Pos (7U)
#define ATIM3MODE23_ADTR_ADTE_Msk (0x1UL << ATIM3MODE23_ADTR_ADTE_Pos)
#define ATIM3MODE23_ADTR_ADTE ATIM3MODE23_ADTR_ADTE_Msk

// ATIM3MODE23_CRCH0
#define ATIM3MODE23_CRCH0_CFACRABKSA_Pos (0U)
#define ATIM3MODE23_CRCH0_CFACRABKSA_Msk (0x3UL << ATIM3MODE23_CRCH0_CFACRABKSA_Pos)
#define ATIM3MODE23_CRCH0_CFACRABKSA ATIM3MODE23_CRCH0_CFACRABKSA_Msk
#define ATIM3MODE23_CRCH0_CFBCRBBKSB_Pos (2U)
#define ATIM3MODE23_CRCH0_CFBCRBBKSB_Msk (0x3UL << ATIM3MODE23_CRCH0_CFBCRBBKSB_Pos)
#define ATIM3MODE23_CRCH0_CFBCRBBKSB ATIM3MODE23_CRCH0_CFBCRBBKSB_Msk
#define ATIM3MODE23_CRCH0_CSA_Pos (4U)
#define ATIM3MODE23_CRCH0_CSA_Msk (0x1UL << ATIM3MODE23_CRCH0_CSA_Pos)
#define ATIM3MODE23_CRCH0_CSA ATIM3MODE23_CRCH0_CSA_Msk
#define ATIM3MODE23_CRCH0_CSB_Pos (5U)
#define ATIM3MODE23_CRCH0_CSB_Msk (0x1UL << ATIM3MODE23_CRCH0_CSB_Pos)
#define ATIM3MODE23_CRCH0_CSB ATIM3MODE23_CRCH0_CSB_Msk
#define ATIM3MODE23_CRCH0_BUFEA_Pos (6U)
#define ATIM3MODE23_CRCH0_BUFEA_Msk (0x1UL << ATIM3MODE23_CRCH0_BUFEA_Pos)
#define ATIM3MODE23_CRCH0_BUFEA ATIM3MODE23_CRCH0_BUFEA_Msk
#define ATIM3MODE23_CRCH0_BUFEB_Pos (7U)
#define ATIM3MODE23_CRCH0_BUFEB_Msk (0x1UL << ATIM3MODE23_CRCH0_BUFEB_Pos)
#define ATIM3MODE23_CRCH0_BUFEB ATIM3MODE23_CRCH0_BUFEB_Msk
#define ATIM3MODE23_CRCH0_CIEA_Pos (8U)
#define ATIM3MODE23_CRCH0_CIEA_Msk (0x1UL << ATIM3MODE23_CRCH0_CIEA_Pos)
#define ATIM3MODE23_CRCH0_CIEA ATIM3MODE23_CRCH0_CIEA_Msk
#define ATIM3MODE23_CRCH0_CIEB_Pos (9U)
#define ATIM3MODE23_CRCH0_CIEB_Msk (0x1UL << ATIM3MODE23_CRCH0_CIEB_Pos)
#define ATIM3MODE23_CRCH0_CIEB ATIM3MODE23_CRCH0_CIEB_Msk
#define ATIM3MODE23_CRCH0_CDEA_Pos (10U)
#define ATIM3MODE23_CRCH0_CDEA_Msk (0x1UL << ATIM3MODE23_CRCH0_CDEA_Pos)
#define ATIM3MODE23_CRCH0_CDEA ATIM3MODE23_CRCH0_CDEA_Msk
#define ATIM3MODE23_CRCH0_CDEB_Pos (11U)
#define ATIM3MODE23_CRCH0_CDEB_Msk (0x1UL << ATIM3MODE23_CRCH0_CDEB_Pos)
#define ATIM3MODE23_CRCH0_CDEB ATIM3MODE23_CRCH0_CDEB_Msk
#define ATIM3MODE23_CRCH0_CISB_Pos (12U)
#define ATIM3MODE23_CRCH0_CISB_Msk (0x3UL << ATIM3MODE23_CRCH0_CISB_Pos)
#define ATIM3MODE23_CRCH0_CISB ATIM3MODE23_CRCH0_CISB_Msk
#define ATIM3MODE23_CRCH0_CCGA_Pos (14U)
#define ATIM3MODE23_CRCH0_CCGA_Msk (0x1UL << ATIM3MODE23_CRCH0_CCGA_Pos)
#define ATIM3MODE23_CRCH0_CCGA ATIM3MODE23_CRCH0_CCGA_Msk
#define ATIM3MODE23_CRCH0_CCGB_Pos (15U)
#define ATIM3MODE23_CRCH0_CCGB_Msk (0x1UL << ATIM3MODE23_CRCH0_CCGB_Pos)
#define ATIM3MODE23_CRCH0_CCGB ATIM3MODE23_CRCH0_CCGB_Msk

// ATIM3MODE23_CRCH1
#define ATIM3MODE23_CRCH1_CFACRABKSA_Pos (0U)
#define ATIM3MODE23_CRCH1_CFACRABKSA_Msk (0x3UL << ATIM3MODE23_CRCH1_CFACRABKSA_Pos)
#define ATIM3MODE23_CRCH1_CFACRABKSA ATIM3MODE23_CRCH1_CFACRABKSA_Msk
#define ATIM3MODE23_CRCH1_CFBCRBBKSB_Pos (2U)
#define ATIM3MODE23_CRCH1_CFBCRBBKSB_Msk (0x3UL << ATIM3MODE23_CRCH1_CFBCRBBKSB_Pos)
#define ATIM3MODE23_CRCH1_CFBCRBBKSB ATIM3MODE23_CRCH1_CFBCRBBKSB_Msk
#define ATIM3MODE23_CRCH1_CSA_Pos (4U)
#define ATIM3MODE23_CRCH1_CSA_Msk (0x1UL << ATIM3MODE23_CRCH1_CSA_Pos)
#define ATIM3MODE23_CRCH1_CSA ATIM3MODE23_CRCH1_CSA_Msk
#define ATIM3MODE23_CRCH1_CSB_Pos (5U)
#define ATIM3MODE23_CRCH1_CSB_Msk (0x1UL << ATIM3MODE23_CRCH1_CSB_Pos)
#define ATIM3MODE23_CRCH1_CSB ATIM3MODE23_CRCH1_CSB_Msk
#define ATIM3MODE23_CRCH1_BUFEA_Pos (6U)
#define ATIM3MODE23_CRCH1_BUFEA_Msk (0x1UL << ATIM3MODE23_CRCH1_BUFEA_Pos)
#define ATIM3MODE23_CRCH1_BUFEA ATIM3MODE23_CRCH1_BUFEA_Msk
#define ATIM3MODE23_CRCH1_BUFEB_Pos (7U)
#define ATIM3MODE23_CRCH1_BUFEB_Msk (0x1UL << ATIM3MODE23_CRCH1_BUFEB_Pos)
#define ATIM3MODE23_CRCH1_BUFEB ATIM3MODE23_CRCH1_BUFEB_Msk
#define ATIM3MODE23_CRCH1_CIEA_Pos (8U)
#define ATIM3MODE23_CRCH1_CIEA_Msk (0x1UL << ATIM3MODE23_CRCH1_CIEA_Pos)
#define ATIM3MODE23_CRCH1_CIEA ATIM3MODE23_CRCH1_CIEA_Msk
#define ATIM3MODE23_CRCH1_CIEB_Pos (9U)
#define ATIM3MODE23_CRCH1_CIEB_Msk (0x1UL << ATIM3MODE23_CRCH1_CIEB_Pos)
#define ATIM3MODE23_CRCH1_CIEB ATIM3MODE23_CRCH1_CIEB_Msk
#define ATIM3MODE23_CRCH1_CDEA_Pos (10U)
#define ATIM3MODE23_CRCH1_CDEA_Msk (0x1UL << ATIM3MODE23_CRCH1_CDEA_Pos)
#define ATIM3MODE23_CRCH1_CDEA ATIM3MODE23_CRCH1_CDEA_Msk
#define ATIM3MODE23_CRCH1_CDEB_Pos (11U)
#define ATIM3MODE23_CRCH1_CDEB_Msk (0x1UL << ATIM3MODE23_CRCH1_CDEB_Pos)
#define ATIM3MODE23_CRCH1_CDEB ATIM3MODE23_CRCH1_CDEB_Msk
#define ATIM3MODE23_CRCH1_CISB_Pos (12U)
#define ATIM3MODE23_CRCH1_CISB_Msk (0x3UL << ATIM3MODE23_CRCH1_CISB_Pos)
#define ATIM3MODE23_CRCH1_CISB ATIM3MODE23_CRCH1_CISB_Msk
#define ATIM3MODE23_CRCH1_CCGA_Pos (14U)
#define ATIM3MODE23_CRCH1_CCGA_Msk (0x1UL << ATIM3MODE23_CRCH1_CCGA_Pos)
#define ATIM3MODE23_CRCH1_CCGA ATIM3MODE23_CRCH1_CCGA_Msk
#define ATIM3MODE23_CRCH1_CCGB_Pos (15U)
#define ATIM3MODE23_CRCH1_CCGB_Msk (0x1UL << ATIM3MODE23_CRCH1_CCGB_Pos)
#define ATIM3MODE23_CRCH1_CCGB ATIM3MODE23_CRCH1_CCGB_Msk

// ATIM3MODE23_CRCH2
#define ATIM3MODE23_CRCH2_CFACRABKSA_Pos (0U)
#define ATIM3MODE23_CRCH2_CFACRABKSA_Msk (0x3UL << ATIM3MODE23_CRCH2_CFACRABKSA_Pos)
#define ATIM3MODE23_CRCH2_CFACRABKSA ATIM3MODE23_CRCH2_CFACRABKSA_Msk
#define ATIM3MODE23_CRCH2_CFBCRBBKSB_Pos (2U)
#define ATIM3MODE23_CRCH2_CFBCRBBKSB_Msk (0x3UL << ATIM3MODE23_CRCH2_CFBCRBBKSB_Pos)
#define ATIM3MODE23_CRCH2_CFBCRBBKSB ATIM3MODE23_CRCH2_CFBCRBBKSB_Msk
#define ATIM3MODE23_CRCH2_CSA_Pos (4U)
#define ATIM3MODE23_CRCH2_CSA_Msk (0x1UL << ATIM3MODE23_CRCH2_CSA_Pos)
#define ATIM3MODE23_CRCH2_CSA ATIM3MODE23_CRCH2_CSA_Msk
#define ATIM3MODE23_CRCH2_CSB_Pos (5U)
#define ATIM3MODE23_CRCH2_CSB_Msk (0x1UL << ATIM3MODE23_CRCH2_CSB_Pos)
#define ATIM3MODE23_CRCH2_CSB ATIM3MODE23_CRCH2_CSB_Msk
#define ATIM3MODE23_CRCH2_BUFEA_Pos (6U)
#define ATIM3MODE23_CRCH2_BUFEA_Msk (0x1UL << ATIM3MODE23_CRCH2_BUFEA_Pos)
#define ATIM3MODE23_CRCH2_BUFEA ATIM3MODE23_CRCH2_BUFEA_Msk
#define ATIM3MODE23_CRCH2_BUFEB_Pos (7U)
#define ATIM3MODE23_CRCH2_BUFEB_Msk (0x1UL << ATIM3MODE23_CRCH2_BUFEB_Pos)
#define ATIM3MODE23_CRCH2_BUFEB ATIM3MODE23_CRCH2_BUFEB_Msk
#define ATIM3MODE23_CRCH2_CIEA_Pos (8U)
#define ATIM3MODE23_CRCH2_CIEA_Msk (0x1UL << ATIM3MODE23_CRCH2_CIEA_Pos)
#define ATIM3MODE23_CRCH2_CIEA ATIM3MODE23_CRCH2_CIEA_Msk
#define ATIM3MODE23_CRCH2_CIEB_Pos (9U)
#define ATIM3MODE23_CRCH2_CIEB_Msk (0x1UL << ATIM3MODE23_CRCH2_CIEB_Pos)
#define ATIM3MODE23_CRCH2_CIEB ATIM3MODE23_CRCH2_CIEB_Msk
#define ATIM3MODE23_CRCH2_CDEA_Pos (10U)
#define ATIM3MODE23_CRCH2_CDEA_Msk (0x1UL << ATIM3MODE23_CRCH2_CDEA_Pos)
#define ATIM3MODE23_CRCH2_CDEA ATIM3MODE23_CRCH2_CDEA_Msk
#define ATIM3MODE23_CRCH2_CDEB_Pos (11U)
#define ATIM3MODE23_CRCH2_CDEB_Msk (0x1UL << ATIM3MODE23_CRCH2_CDEB_Pos)
#define ATIM3MODE23_CRCH2_CDEB ATIM3MODE23_CRCH2_CDEB_Msk
#define ATIM3MODE23_CRCH2_CISB_Pos (12U)
#define ATIM3MODE23_CRCH2_CISB_Msk (0x3UL << ATIM3MODE23_CRCH2_CISB_Pos)
#define ATIM3MODE23_CRCH2_CISB ATIM3MODE23_CRCH2_CISB_Msk
#define ATIM3MODE23_CRCH2_CCGA_Pos (14U)
#define ATIM3MODE23_CRCH2_CCGA_Msk (0x1UL << ATIM3MODE23_CRCH2_CCGA_Pos)
#define ATIM3MODE23_CRCH2_CCGA ATIM3MODE23_CRCH2_CCGA_Msk
#define ATIM3MODE23_CRCH2_CCGB_Pos (15U)
#define ATIM3MODE23_CRCH2_CCGB_Msk (0x1UL << ATIM3MODE23_CRCH2_CCGB_Pos)
#define ATIM3MODE23_CRCH2_CCGB ATIM3MODE23_CRCH2_CCGB_Msk

// ATIM3MODE23_DTR
#define ATIM3MODE23_DTR_DTR_Pos (0U)
#define ATIM3MODE23_DTR_DTR_Msk (0xFFUL << ATIM3MODE23_DTR_DTR_Pos)
#define ATIM3MODE23_DTR_DTR ATIM3MODE23_DTR_DTR_Msk
#define ATIM3MODE23_DTR_BKSEL_Pos (8U)
#define ATIM3MODE23_DTR_BKSEL_Msk (0x1UL << ATIM3MODE23_DTR_BKSEL_Pos)
#define ATIM3MODE23_DTR_BKSEL ATIM3MODE23_DTR_BKSEL_Msk
#define ATIM3MODE23_DTR_DTEN_Pos (9U)
#define ATIM3MODE23_DTR_DTEN_Msk (0x1UL << ATIM3MODE23_DTR_DTEN_Pos)
#define ATIM3MODE23_DTR_DTEN ATIM3MODE23_DTR_DTEN_Msk
#define ATIM3MODE23_DTR_BKE_Pos (10U)
#define ATIM3MODE23_DTR_BKE_Msk (0x1UL << ATIM3MODE23_DTR_BKE_Pos)
#define ATIM3MODE23_DTR_BKE ATIM3MODE23_DTR_BKE_Msk
#define ATIM3MODE23_DTR_AOE_Pos (11U)
#define ATIM3MODE23_DTR_AOE_Msk (0x1UL << ATIM3MODE23_DTR_AOE_Pos)
#define ATIM3MODE23_DTR_AOE ATIM3MODE23_DTR_AOE_Msk
#define ATIM3MODE23_DTR_MOE_Pos (12U)
#define ATIM3MODE23_DTR_MOE_Msk (0x1UL << ATIM3MODE23_DTR_MOE_Pos)
#define ATIM3MODE23_DTR_MOE ATIM3MODE23_DTR_MOE_Msk
#define ATIM3MODE23_DTR_SAFEEN_Pos (13U)
#define ATIM3MODE23_DTR_SAFEEN_Msk (0x1UL << ATIM3MODE23_DTR_SAFEEN_Pos)
#define ATIM3MODE23_DTR_SAFEEN ATIM3MODE23_DTR_SAFEEN_Msk
#define ATIM3MODE23_DTR_VCE_Pos (14U)
#define ATIM3MODE23_DTR_VCE_Msk (0x1UL << ATIM3MODE23_DTR_VCE_Pos)
#define ATIM3MODE23_DTR_VCE ATIM3MODE23_DTR_VCE_Msk

// ATIM3MODE23_RCR
#define ATIM3MODE23_RCR_RCR_Pos (0U)
#define ATIM3MODE23_RCR_RCR_Msk (0xFFUL << ATIM3MODE23_RCR_RCR_Pos)
#define ATIM3MODE23_RCR_RCR ATIM3MODE23_RCR_RCR_Msk
#define ATIM3MODE23_RCR_OV_Pos (8U)
#define ATIM3MODE23_RCR_OV_Msk (0x1UL << ATIM3MODE23_RCR_OV_Pos)
#define ATIM3MODE23_RCR_OV ATIM3MODE23_RCR_OV_Msk
#define ATIM3MODE23_RCR_UD_Pos (9U)
#define ATIM3MODE23_RCR_UD_Msk (0x1UL << ATIM3MODE23_RCR_UD_Pos)
#define ATIM3MODE23_RCR_UD ATIM3MODE23_RCR_UD_Msk

// ATIM3MODE23_CCR0A
#define ATIM3MODE23_CCR0A_CCR0A_Pos (0U)
#define ATIM3MODE23_CCR0A_CCR0A_Msk (0xFFFFUL << ATIM3MODE23_CCR0A_CCR0A_Pos)
#define ATIM3MODE23_CCR0A_CCR0A ATIM3MODE23_CCR0A_CCR0A_Msk

// ATIM3MODE23_CCR0B
#define ATIM3MODE23_CCR0B_CCR0B_Pos (0U)
#define ATIM3MODE23_CCR0B_CCR0B_Msk (0xFFFFUL << ATIM3MODE23_CCR0B_CCR0B_Pos)
#define ATIM3MODE23_CCR0B_CCR0B ATIM3MODE23_CCR0B_CCR0B_Msk

// ATIM3MODE23_CCR1A
#define ATIM3MODE23_CCR1A_CCR1A_Pos (0U)
#define ATIM3MODE23_CCR1A_CCR1A_Msk (0xFFFFUL << ATIM3MODE23_CCR1A_CCR1A_Pos)
#define ATIM3MODE23_CCR1A_CCR1A ATIM3MODE23_CCR1A_CCR1A_Msk

// ATIM3MODE23_CCR1B
#define ATIM3MODE23_CCR1B_CCR1B_Pos (0U)
#define ATIM3MODE23_CCR1B_CCR1B_Msk (0xFFFFUL << ATIM3MODE23_CCR1B_CCR1B_Pos)
#define ATIM3MODE23_CCR1B_CCR1B ATIM3MODE23_CCR1B_CCR1B_Msk

// ATIM3MODE23_CCR2A
#define ATIM3MODE23_CCR2A_CCR2A_Pos (0U)
#define ATIM3MODE23_CCR2A_CCR2A_Msk (0xFFFFUL << ATIM3MODE23_CCR2A_CCR2A_Pos)
#define ATIM3MODE23_CCR2A_CCR2A ATIM3MODE23_CCR2A_CCR2A_Msk

// ATIM3MODE23_CCR2B
#define ATIM3MODE23_CCR2B_CCR2B_Pos (0U)
#define ATIM3MODE23_CCR2B_CCR2B_Msk (0xFFFFUL << ATIM3MODE23_CCR2B_CCR2B_Pos)
#define ATIM3MODE23_CCR2B_CCR2B ATIM3MODE23_CCR2B_CCR2B_Msk

// ATIM3MODE23_CCR3A
#define ATIM3MODE23_CCR3A_CCR3A_Pos (0U)
#define ATIM3MODE23_CCR3A_CCR3A_Msk (0xFFFFUL << ATIM3MODE23_CCR3A_CCR3A_Pos)
#define ATIM3MODE23_CCR3A_CCR3A ATIM3MODE23_CCR3A_CCR3A_Msk

// ATIM3MODE23_CRCH3A
#define ATIM3MODE23_CRCH3A_BUF_Pos (0U)
#define ATIM3MODE23_CRCH3A_BUF_Msk (0x1UL << ATIM3MODE23_CRCH3A_BUF_Pos)
#define ATIM3MODE23_CRCH3A_BUF ATIM3MODE23_CRCH3A_BUF_Msk
#define ATIM3MODE23_CRCH3A_CI_Pos (1U)
#define ATIM3MODE23_CRCH3A_CI_Msk (0x1UL << ATIM3MODE23_CRCH3A_CI_Pos)
#define ATIM3MODE23_CRCH3A_CI ATIM3MODE23_CRCH3A_CI_Msk
#define ATIM3MODE23_CRCH3A_CD_Pos (2U)
#define ATIM3MODE23_CRCH3A_CD_Msk (0x1UL << ATIM3MODE23_CRCH3A_CD_Pos)
#define ATIM3MODE23_CRCH3A_CD ATIM3MODE23_CRCH3A_CD_Msk
#define ATIM3MODE23_CRCH3A_CIS_Pos (3U)
#define ATIM3MODE23_CRCH3A_CIS_Msk (0x3UL << ATIM3MODE23_CRCH3A_CIS_Pos)
#define ATIM3MODE23_CRCH3A_CIS ATIM3MODE23_CRCH3A_CIS_Msk
#define ATIM3MODE23_CRCH3A_C3AEN_Pos (5U)
#define ATIM3MODE23_CRCH3A_C3AEN_Msk (0x1UL << ATIM3MODE23_CRCH3A_C3AEN_Pos)
#define ATIM3MODE23_CRCH3A_C3AEN ATIM3MODE23_CRCH3A_C3AEN_Msk

// ATIM3MODE23_CCR3B
#define ATIM3MODE23_CCR3B_CCR3B_Pos (0U)
#define ATIM3MODE23_CCR3B_CCR3B_Msk (0xFFFFUL << ATIM3MODE23_CCR3B_CCR3B_Pos)
#define ATIM3MODE23_CCR3B_CCR3B ATIM3MODE23_CCR3B_CCR3B_Msk

// ATIM3MODE23_CRCH3B
#define ATIM3MODE23_CRCH3B_BUF_Pos (0U)
#define ATIM3MODE23_CRCH3B_BUF_Msk (0x1UL << ATIM3MODE23_CRCH3B_BUF_Pos)
#define ATIM3MODE23_CRCH3B_BUF ATIM3MODE23_CRCH3B_BUF_Msk
#define ATIM3MODE23_CRCH3B_CI_Pos (1U)
#define ATIM3MODE23_CRCH3B_CI_Msk (0x1UL << ATIM3MODE23_CRCH3B_CI_Pos)
#define ATIM3MODE23_CRCH3B_CI ATIM3MODE23_CRCH3B_CI_Msk
#define ATIM3MODE23_CRCH3B_CD_Pos (2U)
#define ATIM3MODE23_CRCH3B_CD_Msk (0x1UL << ATIM3MODE23_CRCH3B_CD_Pos)
#define ATIM3MODE23_CRCH3B_CD ATIM3MODE23_CRCH3B_CD_Msk
#define ATIM3MODE23_CRCH3B_CIS_Pos (3U)
#define ATIM3MODE23_CRCH3B_CIS_Msk (0x3UL << ATIM3MODE23_CRCH3B_CIS_Pos)
#define ATIM3MODE23_CRCH3B_CIS ATIM3MODE23_CRCH3B_CIS_Msk
#define ATIM3MODE23_CRCH3B_C3BEN_Pos (5U)
#define ATIM3MODE23_CRCH3B_C3BEN_Msk (0x1UL << ATIM3MODE23_CRCH3B_C3BEN_Pos)
#define ATIM3MODE23_CRCH3B_C3BEN ATIM3MODE23_CRCH3B_C3BEN_Msk

//********************    Bits Define For Peripheral ATIMMODE0    ********************//
// ATIMMODE0_ARR
#define ATIMMODE0_ARR_ARR_Pos (0U)
#define ATIMMODE0_ARR_ARR_Msk (0xFFFFUL << ATIMMODE0_ARR_ARR_Pos)
#define ATIMMODE0_ARR_ARR ATIMMODE0_ARR_ARR_Msk

// ATIMMODE0_CNT
#define ATIMMODE0_CNT_CNT_Pos (0U)
#define ATIMMODE0_CNT_CNT_Msk (0xFFFFUL << ATIMMODE0_CNT_CNT_Pos)
#define ATIMMODE0_CNT_CNT ATIMMODE0_CNT_CNT_Msk

// ATIMMODE0_CNT32
#define ATIMMODE0_CNT32_CNT32_Pos (0U)
#define ATIMMODE0_CNT32_CNT32_Msk (0xFFFFFFFFUL << ATIMMODE0_CNT32_CNT32_Pos)
#define ATIMMODE0_CNT32_CNT32 ATIMMODE0_CNT32_CNT32_Msk

// ATIMMODE0_M0CR
#define ATIMMODE0_M0CR_CTEN_Pos (0U)
#define ATIMMODE0_M0CR_CTEN_Msk (0x1UL << ATIMMODE0_M0CR_CTEN_Pos)
#define ATIMMODE0_M0CR_CTEN ATIMMODE0_M0CR_CTEN_Msk
#define ATIMMODE0_M0CR_MD_Pos (1U)
#define ATIMMODE0_M0CR_MD_Msk (0x1UL << ATIMMODE0_M0CR_MD_Pos)
#define ATIMMODE0_M0CR_MD ATIMMODE0_M0CR_MD_Msk
#define ATIMMODE0_M0CR_CT_Pos (2U)
#define ATIMMODE0_M0CR_CT_Msk (0x1UL << ATIMMODE0_M0CR_CT_Pos)
#define ATIMMODE0_M0CR_CT ATIMMODE0_M0CR_CT_Msk
#define ATIMMODE0_M0CR_TOGEN_Pos (3U)
#define ATIMMODE0_M0CR_TOGEN_Msk (0x1UL << ATIMMODE0_M0CR_TOGEN_Pos)
#define ATIMMODE0_M0CR_TOGEN ATIMMODE0_M0CR_TOGEN_Msk
#define ATIMMODE0_M0CR_PRS_Pos (4U)
#define ATIMMODE0_M0CR_PRS_Msk (0x7UL << ATIMMODE0_M0CR_PRS_Pos)
#define ATIMMODE0_M0CR_PRS ATIMMODE0_M0CR_PRS_Msk
#define ATIMMODE0_M0CR_GATE_Pos (8U)
#define ATIMMODE0_M0CR_GATE_Msk (0x1UL << ATIMMODE0_M0CR_GATE_Pos)
#define ATIMMODE0_M0CR_GATE ATIMMODE0_M0CR_GATE_Msk
#define ATIMMODE0_M0CR_GATEP_Pos (9U)
#define ATIMMODE0_M0CR_GATEP_Msk (0x1UL << ATIMMODE0_M0CR_GATEP_Pos)
#define ATIMMODE0_M0CR_GATEP ATIMMODE0_M0CR_GATEP_Msk
#define ATIMMODE0_M0CR_UIE_Pos (10U)
#define ATIMMODE0_M0CR_UIE_Msk (0x1UL << ATIMMODE0_M0CR_UIE_Pos)
#define ATIMMODE0_M0CR_UIE ATIMMODE0_M0CR_UIE_Msk
#define ATIMMODE0_M0CR_MODE_Pos (12U)
#define ATIMMODE0_M0CR_MODE_Msk (0x3UL << ATIMMODE0_M0CR_MODE_Pos)
#define ATIMMODE0_M0CR_MODE ATIMMODE0_M0CR_MODE_Msk

// ATIMMODE0_IFR
#define ATIMMODE0_IFR_UI_Pos (0U)
#define ATIMMODE0_IFR_UI_Msk (0x1UL << ATIMMODE0_IFR_UI_Pos)
#define ATIMMODE0_IFR_UI ATIMMODE0_IFR_UI_Msk

// ATIMMODE0_ICLR
#define ATIMMODE0_ICLR_UI_Pos (0U)
#define ATIMMODE0_ICLR_UI_Msk (0x1UL << ATIMMODE0_ICLR_UI_Pos)
#define ATIMMODE0_ICLR_UI ATIMMODE0_ICLR_UI_Msk

// ATIMMODE0_DTR
#define ATIMMODE0_DTR_MOE_Pos (12U)
#define ATIMMODE0_DTR_MOE_Msk (0x1UL << ATIMMODE0_DTR_MOE_Pos)
#define ATIMMODE0_DTR_MOE ATIMMODE0_DTR_MOE_Msk

//********************    Bits Define For Peripheral ATIMMODE1    ********************//
// ATIMMODE1_CNT
#define ATIMMODE1_CNT_CNT_Pos (0U)
#define ATIMMODE1_CNT_CNT_Msk (0xFFFFUL << ATIMMODE1_CNT_CNT_Pos)
#define ATIMMODE1_CNT_CNT ATIMMODE1_CNT_CNT_Msk

// ATIMMODE1_M1CR
#define ATIMMODE1_M1CR_CTEN_Pos (0U)
#define ATIMMODE1_M1CR_CTEN_Msk (0x1UL << ATIMMODE1_M1CR_CTEN_Pos)
#define ATIMMODE1_M1CR_CTEN ATIMMODE1_M1CR_CTEN_Msk
#define ATIMMODE1_M1CR_CT_Pos (2U)
#define ATIMMODE1_M1CR_CT_Msk (0x1UL << ATIMMODE1_M1CR_CT_Pos)
#define ATIMMODE1_M1CR_CT ATIMMODE1_M1CR_CT_Msk
#define ATIMMODE1_M1CR_PRS_Pos (4U)
#define ATIMMODE1_M1CR_PRS_Msk (0x7UL << ATIMMODE1_M1CR_PRS_Pos)
#define ATIMMODE1_M1CR_PRS ATIMMODE1_M1CR_PRS_Msk
#define ATIMMODE1_M1CR_EDG1ST_Pos (8U)
#define ATIMMODE1_M1CR_EDG1ST_Msk (0x1UL << ATIMMODE1_M1CR_EDG1ST_Pos)
#define ATIMMODE1_M1CR_EDG1ST ATIMMODE1_M1CR_EDG1ST_Msk
#define ATIMMODE1_M1CR_EDG2ND_Pos (9U)
#define ATIMMODE1_M1CR_EDG2ND_Msk (0x1UL << ATIMMODE1_M1CR_EDG2ND_Pos)
#define ATIMMODE1_M1CR_EDG2ND ATIMMODE1_M1CR_EDG2ND_Msk
#define ATIMMODE1_M1CR_UIE_Pos (10U)
#define ATIMMODE1_M1CR_UIE_Msk (0x1UL << ATIMMODE1_M1CR_UIE_Pos)
#define ATIMMODE1_M1CR_UIE ATIMMODE1_M1CR_UIE_Msk
#define ATIMMODE1_M1CR_MODE_Pos (12U)
#define ATIMMODE1_M1CR_MODE_Msk (0x3UL << ATIMMODE1_M1CR_MODE_Pos)
#define ATIMMODE1_M1CR_MODE ATIMMODE1_M1CR_MODE_Msk
#define ATIMMODE1_M1CR_ONESHOT_Pos (14U)
#define ATIMMODE1_M1CR_ONESHOT_Msk (0x1UL << ATIMMODE1_M1CR_ONESHOT_Pos)
#define ATIMMODE1_M1CR_ONESHOT ATIMMODE1_M1CR_ONESHOT_Msk

// ATIMMODE1_IFR
#define ATIMMODE1_IFR_UI_Pos (0U)
#define ATIMMODE1_IFR_UI_Msk (0x1UL << ATIMMODE1_IFR_UI_Pos)
#define ATIMMODE1_IFR_UI ATIMMODE1_IFR_UI_Msk
#define ATIMMODE1_IFR_PWC_Pos (2U)
#define ATIMMODE1_IFR_PWC_Msk (0x1UL << ATIMMODE1_IFR_PWC_Pos)
#define ATIMMODE1_IFR_PWC ATIMMODE1_IFR_PWC_Msk

// ATIMMODE1_ICLR
#define ATIMMODE1_ICLR_UI_Pos (0U)
#define ATIMMODE1_ICLR_UI_Msk (0x1UL << ATIMMODE1_ICLR_UI_Pos)
#define ATIMMODE1_ICLR_UI ATIMMODE1_ICLR_UI_Msk
#define ATIMMODE1_ICLR_PWC_Pos (2U)
#define ATIMMODE1_ICLR_PWC_Msk (0x1UL << ATIMMODE1_ICLR_PWC_Pos)
#define ATIMMODE1_ICLR_PWC ATIMMODE1_ICLR_PWC_Msk

// ATIMMODE1_MSCR
#define ATIMMODE1_MSCR_TS_Pos (5U)
#define ATIMMODE1_MSCR_TS_Msk (0x7UL << ATIMMODE1_MSCR_TS_Pos)
#define ATIMMODE1_MSCR_TS ATIMMODE1_MSCR_TS_Msk
#define ATIMMODE1_MSCR_IA0S_Pos (11U)
#define ATIMMODE1_MSCR_IA0S_Msk (0x1UL << ATIMMODE1_MSCR_IA0S_Pos)
#define ATIMMODE1_MSCR_IA0S ATIMMODE1_MSCR_IA0S_Msk
#define ATIMMODE1_MSCR_IB0S_Pos (12U)
#define ATIMMODE1_MSCR_IB0S_Msk (0x1UL << ATIMMODE1_MSCR_IB0S_Pos)
#define ATIMMODE1_MSCR_IB0S ATIMMODE1_MSCR_IB0S_Msk

// ATIMMODE1_FLTR
#define ATIMMODE1_FLTR_FLTA0_Pos (0U)
#define ATIMMODE1_FLTR_FLTA0_Msk (0x7UL << ATIMMODE1_FLTR_FLTA0_Pos)
#define ATIMMODE1_FLTR_FLTA0 ATIMMODE1_FLTR_FLTA0_Msk
#define ATIMMODE1_FLTR_FLTB0_Pos (4U)
#define ATIMMODE1_FLTR_FLTB0_Msk (0x7UL << ATIMMODE1_FLTR_FLTB0_Pos)
#define ATIMMODE1_FLTR_FLTB0 ATIMMODE1_FLTR_FLTB0_Msk
#define ATIMMODE1_FLTR_FLTET_Pos (28U)
#define ATIMMODE1_FLTR_FLTET_Msk (0x7UL << ATIMMODE1_FLTR_FLTET_Pos)
#define ATIMMODE1_FLTR_FLTET ATIMMODE1_FLTR_FLTET_Msk
#define ATIMMODE1_FLTR_ETP_Pos (31U)
#define ATIMMODE1_FLTR_ETP_Msk (0x1UL << ATIMMODE1_FLTR_ETP_Pos)
#define ATIMMODE1_FLTR_ETP ATIMMODE1_FLTR_ETP_Msk

// ATIMMODE1_CR0
#define ATIMMODE1_CR0_CSA_Pos (4U)
#define ATIMMODE1_CR0_CSA_Msk (0x1UL << ATIMMODE1_CR0_CSA_Pos)
#define ATIMMODE1_CR0_CSA ATIMMODE1_CR0_CSA_Msk
#define ATIMMODE1_CR0_CSB_Pos (5U)
#define ATIMMODE1_CR0_CSB_Msk (0x1UL << ATIMMODE1_CR0_CSB_Pos)
#define ATIMMODE1_CR0_CSB ATIMMODE1_CR0_CSB_Msk
#define ATIMMODE1_CR0_CIEA_Pos (8U)
#define ATIMMODE1_CR0_CIEA_Msk (0x1UL << ATIMMODE1_CR0_CIEA_Pos)
#define ATIMMODE1_CR0_CIEA ATIMMODE1_CR0_CIEA_Msk

// ATIMMODE1_CCR0A
#define ATIMMODE1_CCR0A_CCR0A_Pos (0U)
#define ATIMMODE1_CCR0A_CCR0A_Msk (0xFFFFUL << ATIMMODE1_CCR0A_CCR0A_Pos)
#define ATIMMODE1_CCR0A_CCR0A ATIMMODE1_CCR0A_CCR0A_Msk

//********************    Bits Define For Peripheral ATIMMODE23    ********************//
// ATIMMODE23_ARR
#define ATIMMODE23_ARR_ARR_Pos (0U)
#define ATIMMODE23_ARR_ARR_Msk (0xFFFFUL << ATIMMODE23_ARR_ARR_Pos)
#define ATIMMODE23_ARR_ARR ATIMMODE23_ARR_ARR_Msk

// ATIMMODE23_CNT
#define ATIMMODE23_CNT_CNT_Pos (0U)
#define ATIMMODE23_CNT_CNT_Msk (0xFFFFUL << ATIMMODE23_CNT_CNT_Pos)
#define ATIMMODE23_CNT_CNT ATIMMODE23_CNT_CNT_Msk

// ATIMMODE23_M23CR
#define ATIMMODE23_M23CR_CTEN_Pos (0U)
#define ATIMMODE23_M23CR_CTEN_Msk (0x1UL << ATIMMODE23_M23CR_CTEN_Pos)
#define ATIMMODE23_M23CR_CTEN ATIMMODE23_M23CR_CTEN_Msk
#define ATIMMODE23_M23CR_COMP_Pos (1U)
#define ATIMMODE23_M23CR_COMP_Msk (0x1UL << ATIMMODE23_M23CR_COMP_Pos)
#define ATIMMODE23_M23CR_COMP ATIMMODE23_M23CR_COMP_Msk
#define ATIMMODE23_M23CR_CT_Pos (2U)
#define ATIMMODE23_M23CR_CT_Msk (0x1UL << ATIMMODE23_M23CR_CT_Pos)
#define ATIMMODE23_M23CR_CT ATIMMODE23_M23CR_CT_Msk
#define ATIMMODE23_M23CR_PWM2S_Pos (3U)
#define ATIMMODE23_M23CR_PWM2S_Msk (0x1UL << ATIMMODE23_M23CR_PWM2S_Pos)
#define ATIMMODE23_M23CR_PWM2S ATIMMODE23_M23CR_PWM2S_Msk
#define ATIMMODE23_M23CR_PRS_Pos (4U)
#define ATIMMODE23_M23CR_PRS_Msk (0x7UL << ATIMMODE23_M23CR_PRS_Pos)
#define ATIMMODE23_M23CR_PRS ATIMMODE23_M23CR_PRS_Msk
#define ATIMMODE23_M23CR_BUFPEN_Pos (7U)
#define ATIMMODE23_M23CR_BUFPEN_Msk (0x1UL << ATIMMODE23_M23CR_BUFPEN_Pos)
#define ATIMMODE23_M23CR_BUFPEN ATIMMODE23_M23CR_BUFPEN_Msk
#define ATIMMODE23_M23CR_CRG_Pos (8U)
#define ATIMMODE23_M23CR_CRG_Msk (0x1UL << ATIMMODE23_M23CR_CRG_Pos)
#define ATIMMODE23_M23CR_CRG ATIMMODE23_M23CR_CRG_Msk
#define ATIMMODE23_M23CR_CFG_Pos (9U)
#define ATIMMODE23_M23CR_CFG_Msk (0x1UL << ATIMMODE23_M23CR_CFG_Pos)
#define ATIMMODE23_M23CR_CFG ATIMMODE23_M23CR_CFG_Msk
#define ATIMMODE23_M23CR_UIE_Pos (10U)
#define ATIMMODE23_M23CR_UIE_Msk (0x1UL << ATIMMODE23_M23CR_UIE_Pos)
#define ATIMMODE23_M23CR_UIE ATIMMODE23_M23CR_UIE_Msk
#define ATIMMODE23_M23CR_UDE_Pos (11U)
#define ATIMMODE23_M23CR_UDE_Msk (0x1UL << ATIMMODE23_M23CR_UDE_Pos)
#define ATIMMODE23_M23CR_UDE ATIMMODE23_M23CR_UDE_Msk
#define ATIMMODE23_M23CR_MODE_Pos (12U)
#define ATIMMODE23_M23CR_MODE_Msk (0x3UL << ATIMMODE23_M23CR_MODE_Pos)
#define ATIMMODE23_M23CR_MODE ATIMMODE23_M23CR_MODE_Msk
#define ATIMMODE23_M23CR_ONESHOT_Pos (14U)
#define ATIMMODE23_M23CR_ONESHOT_Msk (0x1UL << ATIMMODE23_M23CR_ONESHOT_Pos)
#define ATIMMODE23_M23CR_ONESHOT ATIMMODE23_M23CR_ONESHOT_Msk
#define ATIMMODE23_M23CR_CSG_Pos (15U)
#define ATIMMODE23_M23CR_CSG_Msk (0x1UL << ATIMMODE23_M23CR_CSG_Pos)
#define ATIMMODE23_M23CR_CSG ATIMMODE23_M23CR_CSG_Msk
#define ATIMMODE23_M23CR_OCCS_Pos (16U)
#define ATIMMODE23_M23CR_OCCS_Msk (0x1UL << ATIMMODE23_M23CR_OCCS_Pos)
#define ATIMMODE23_M23CR_OCCS ATIMMODE23_M23CR_OCCS_Msk
#define ATIMMODE23_M23CR_URS_Pos (17U)
#define ATIMMODE23_M23CR_URS_Msk (0x1UL << ATIMMODE23_M23CR_URS_Pos)
#define ATIMMODE23_M23CR_URS ATIMMODE23_M23CR_URS_Msk
#define ATIMMODE23_M23CR_TDE_Pos (18U)
#define ATIMMODE23_M23CR_TDE_Msk (0x1UL << ATIMMODE23_M23CR_TDE_Pos)
#define ATIMMODE23_M23CR_TDE ATIMMODE23_M23CR_TDE_Msk
#define ATIMMODE23_M23CR_TIE_Pos (19U)
#define ATIMMODE23_M23CR_TIE_Msk (0x1UL << ATIMMODE23_M23CR_TIE_Pos)
#define ATIMMODE23_M23CR_TIE ATIMMODE23_M23CR_TIE_Msk
#define ATIMMODE23_M23CR_BIE_Pos (20U)
#define ATIMMODE23_M23CR_BIE_Msk (0x1UL << ATIMMODE23_M23CR_BIE_Pos)
#define ATIMMODE23_M23CR_BIE ATIMMODE23_M23CR_BIE_Msk
#define ATIMMODE23_M23CR_CIS_Pos (21U)
#define ATIMMODE23_M23CR_CIS_Msk (0x3UL << ATIMMODE23_M23CR_CIS_Pos)
#define ATIMMODE23_M23CR_CIS ATIMMODE23_M23CR_CIS_Msk
#define ATIMMODE23_M23CR_OCCE_Pos (23U)
#define ATIMMODE23_M23CR_OCCE_Msk (0x1UL << ATIMMODE23_M23CR_OCCE_Pos)
#define ATIMMODE23_M23CR_OCCE ATIMMODE23_M23CR_OCCE_Msk
#define ATIMMODE23_M23CR_TG_Pos (24U)
#define ATIMMODE23_M23CR_TG_Msk (0x1UL << ATIMMODE23_M23CR_TG_Pos)
#define ATIMMODE23_M23CR_TG ATIMMODE23_M23CR_TG_Msk
#define ATIMMODE23_M23CR_UG_Pos (25U)
#define ATIMMODE23_M23CR_UG_Msk (0x1UL << ATIMMODE23_M23CR_UG_Pos)
#define ATIMMODE23_M23CR_UG ATIMMODE23_M23CR_UG_Msk
#define ATIMMODE23_M23CR_BG_Pos (26U)
#define ATIMMODE23_M23CR_BG_Msk (0x1UL << ATIMMODE23_M23CR_BG_Pos)
#define ATIMMODE23_M23CR_BG ATIMMODE23_M23CR_BG_Msk
#define ATIMMODE23_M23CR_DIR_Pos (27U)
#define ATIMMODE23_M23CR_DIR_Msk (0x1UL << ATIMMODE23_M23CR_DIR_Pos)
#define ATIMMODE23_M23CR_DIR ATIMMODE23_M23CR_DIR_Msk
#define ATIMMODE23_M23CR_OVE_Pos (28U)
#define ATIMMODE23_M23CR_OVE_Msk (0x1UL << ATIMMODE23_M23CR_OVE_Pos)
#define ATIMMODE23_M23CR_OVE ATIMMODE23_M23CR_OVE_Msk
#define ATIMMODE23_M23CR_UNDE_Pos (29U)
#define ATIMMODE23_M23CR_UNDE_Msk (0x1UL << ATIMMODE23_M23CR_UNDE_Pos)
#define ATIMMODE23_M23CR_UNDE ATIMMODE23_M23CR_UNDE_Msk

// ATIMMODE23_IFR
#define ATIMMODE23_IFR_UI_Pos (0U)
#define ATIMMODE23_IFR_UI_Msk (0x1UL << ATIMMODE23_IFR_UI_Pos)
#define ATIMMODE23_IFR_UI ATIMMODE23_IFR_UI_Msk
#define ATIMMODE23_IFR_CA0_Pos (2U)
#define ATIMMODE23_IFR_CA0_Msk (0x1UL << ATIMMODE23_IFR_CA0_Pos)
#define ATIMMODE23_IFR_CA0 ATIMMODE23_IFR_CA0_Msk
#define ATIMMODE23_IFR_CB0_Pos (5U)
#define ATIMMODE23_IFR_CB0_Msk (0x1UL << ATIMMODE23_IFR_CB0_Pos)
#define ATIMMODE23_IFR_CB0 ATIMMODE23_IFR_CB0_Msk
#define ATIMMODE23_IFR_CA0E_Pos (8U)
#define ATIMMODE23_IFR_CA0E_Msk (0x1UL << ATIMMODE23_IFR_CA0E_Pos)
#define ATIMMODE23_IFR_CA0E ATIMMODE23_IFR_CA0E_Msk
#define ATIMMODE23_IFR_CB0E_Pos (11U)
#define ATIMMODE23_IFR_CB0E_Msk (0x1UL << ATIMMODE23_IFR_CB0E_Pos)
#define ATIMMODE23_IFR_CB0E ATIMMODE23_IFR_CB0E_Msk
#define ATIMMODE23_IFR_BI_Pos (14U)
#define ATIMMODE23_IFR_BI_Msk (0x1UL << ATIMMODE23_IFR_BI_Pos)
#define ATIMMODE23_IFR_BI ATIMMODE23_IFR_BI_Msk
#define ATIMMODE23_IFR_TI_Pos (15U)
#define ATIMMODE23_IFR_TI_Msk (0x1UL << ATIMMODE23_IFR_TI_Pos)
#define ATIMMODE23_IFR_TI ATIMMODE23_IFR_TI_Msk
#define ATIMMODE23_IFR_OV_Pos (16U)
#define ATIMMODE23_IFR_OV_Msk (0x1UL << ATIMMODE23_IFR_OV_Pos)
#define ATIMMODE23_IFR_OV ATIMMODE23_IFR_OV_Msk
#define ATIMMODE23_IFR_UND_Pos (17U)
#define ATIMMODE23_IFR_UND_Msk (0x1UL << ATIMMODE23_IFR_UND_Pos)
#define ATIMMODE23_IFR_UND ATIMMODE23_IFR_UND_Msk

// ATIMMODE23_ICLR
#define ATIMMODE23_ICLR_UI_Pos (0U)
#define ATIMMODE23_ICLR_UI_Msk (0x1UL << ATIMMODE23_ICLR_UI_Pos)
#define ATIMMODE23_ICLR_UI ATIMMODE23_ICLR_UI_Msk
#define ATIMMODE23_ICLR_CA0_Pos (2U)
#define ATIMMODE23_ICLR_CA0_Msk (0x1UL << ATIMMODE23_ICLR_CA0_Pos)
#define ATIMMODE23_ICLR_CA0 ATIMMODE23_ICLR_CA0_Msk
#define ATIMMODE23_ICLR_CB0_Pos (5U)
#define ATIMMODE23_ICLR_CB0_Msk (0x1UL << ATIMMODE23_ICLR_CB0_Pos)
#define ATIMMODE23_ICLR_CB0 ATIMMODE23_ICLR_CB0_Msk
#define ATIMMODE23_ICLR_CA0E_Pos (8U)
#define ATIMMODE23_ICLR_CA0E_Msk (0x1UL << ATIMMODE23_ICLR_CA0E_Pos)
#define ATIMMODE23_ICLR_CA0E ATIMMODE23_ICLR_CA0E_Msk
#define ATIMMODE23_ICLR_CB0E_Pos (11U)
#define ATIMMODE23_ICLR_CB0E_Msk (0x1UL << ATIMMODE23_ICLR_CB0E_Pos)
#define ATIMMODE23_ICLR_CB0E ATIMMODE23_ICLR_CB0E_Msk
#define ATIMMODE23_ICLR_BI_Pos (14U)
#define ATIMMODE23_ICLR_BI_Msk (0x1UL << ATIMMODE23_ICLR_BI_Pos)
#define ATIMMODE23_ICLR_BI ATIMMODE23_ICLR_BI_Msk
#define ATIMMODE23_ICLR_TI_Pos (15U)
#define ATIMMODE23_ICLR_TI_Msk (0x1UL << ATIMMODE23_ICLR_TI_Pos)
#define ATIMMODE23_ICLR_TI ATIMMODE23_ICLR_TI_Msk
#define ATIMMODE23_ICLR_OV_Pos (16U)
#define ATIMMODE23_ICLR_OV_Msk (0x1UL << ATIMMODE23_ICLR_OV_Pos)
#define ATIMMODE23_ICLR_OV ATIMMODE23_ICLR_OV_Msk
#define ATIMMODE23_ICLR_UND_Pos (17U)
#define ATIMMODE23_ICLR_UND_Msk (0x1UL << ATIMMODE23_ICLR_UND_Pos)
#define ATIMMODE23_ICLR_UND ATIMMODE23_ICLR_UND_Msk

// ATIMMODE23_MSCR
#define ATIMMODE23_MSCR_MMS_Pos (0U)
#define ATIMMODE23_MSCR_MMS_Msk (0x7UL << ATIMMODE23_MSCR_MMS_Pos)
#define ATIMMODE23_MSCR_MMS ATIMMODE23_MSCR_MMS_Msk
#define ATIMMODE23_MSCR_CCDS_Pos (3U)
#define ATIMMODE23_MSCR_CCDS_Msk (0x1UL << ATIMMODE23_MSCR_CCDS_Pos)
#define ATIMMODE23_MSCR_CCDS ATIMMODE23_MSCR_CCDS_Msk
#define ATIMMODE23_MSCR_MSM_Pos (4U)
#define ATIMMODE23_MSCR_MSM_Msk (0x1UL << ATIMMODE23_MSCR_MSM_Pos)
#define ATIMMODE23_MSCR_MSM ATIMMODE23_MSCR_MSM_Msk
#define ATIMMODE23_MSCR_TS_Pos (5U)
#define ATIMMODE23_MSCR_TS_Msk (0x7UL << ATIMMODE23_MSCR_TS_Pos)
#define ATIMMODE23_MSCR_TS ATIMMODE23_MSCR_TS_Msk
#define ATIMMODE23_MSCR_SMS_Pos (8U)
#define ATIMMODE23_MSCR_SMS_Msk (0x7UL << ATIMMODE23_MSCR_SMS_Pos)
#define ATIMMODE23_MSCR_SMS ATIMMODE23_MSCR_SMS_Msk
#define ATIMMODE23_MSCR_IA0S_Pos (11U)
#define ATIMMODE23_MSCR_IA0S_Msk (0x1UL << ATIMMODE23_MSCR_IA0S_Pos)
#define ATIMMODE23_MSCR_IA0S ATIMMODE23_MSCR_IA0S_Msk
#define ATIMMODE23_MSCR_IB0S_Pos (12U)
#define ATIMMODE23_MSCR_IB0S_Msk (0x1UL << ATIMMODE23_MSCR_IB0S_Pos)
#define ATIMMODE23_MSCR_IB0S ATIMMODE23_MSCR_IB0S_Msk

// ATIMMODE23_FLTR
#define ATIMMODE23_FLTR_OCMA0FLTA0_Pos (0U)
#define ATIMMODE23_FLTR_OCMA0FLTA0_Msk (0x7UL << ATIMMODE23_FLTR_OCMA0FLTA0_Pos)
#define ATIMMODE23_FLTR_OCMA0FLTA0 ATIMMODE23_FLTR_OCMA0FLTA0_Msk
#define ATIMMODE23_FLTR_CCPA0_Pos (3U)
#define ATIMMODE23_FLTR_CCPA0_Msk (0x1UL << ATIMMODE23_FLTR_CCPA0_Pos)
#define ATIMMODE23_FLTR_CCPA0 ATIMMODE23_FLTR_CCPA0_Msk
#define ATIMMODE23_FLTR_OCMB0FLTB0_Pos (4U)
#define ATIMMODE23_FLTR_OCMB0FLTB0_Msk (0x7UL << ATIMMODE23_FLTR_OCMB0FLTB0_Pos)
#define ATIMMODE23_FLTR_OCMB0FLTB0 ATIMMODE23_FLTR_OCMB0FLTB0_Msk
#define ATIMMODE23_FLTR_CCPB0_Pos (7U)
#define ATIMMODE23_FLTR_CCPB0_Msk (0x1UL << ATIMMODE23_FLTR_CCPB0_Pos)
#define ATIMMODE23_FLTR_CCPB0 ATIMMODE23_FLTR_CCPB0_Msk
#define ATIMMODE23_FLTR_FLTBK_Pos (24U)
#define ATIMMODE23_FLTR_FLTBK_Msk (0x7UL << ATIMMODE23_FLTR_FLTBK_Pos)
#define ATIMMODE23_FLTR_FLTBK ATIMMODE23_FLTR_FLTBK_Msk
#define ATIMMODE23_FLTR_BKP_Pos (27U)
#define ATIMMODE23_FLTR_BKP_Msk (0x1UL << ATIMMODE23_FLTR_BKP_Pos)
#define ATIMMODE23_FLTR_BKP ATIMMODE23_FLTR_BKP_Msk
#define ATIMMODE23_FLTR_FLTET_Pos (28U)
#define ATIMMODE23_FLTR_FLTET_Msk (0x7UL << ATIMMODE23_FLTR_FLTET_Pos)
#define ATIMMODE23_FLTR_FLTET ATIMMODE23_FLTR_FLTET_Msk
#define ATIMMODE23_FLTR_ETP_Pos (31U)
#define ATIMMODE23_FLTR_ETP_Msk (0x1UL << ATIMMODE23_FLTR_ETP_Pos)
#define ATIMMODE23_FLTR_ETP ATIMMODE23_FLTR_ETP_Msk

// ATIMMODE23_ADTR
#define ATIMMODE23_ADTR_UEVE_Pos (0U)
#define ATIMMODE23_ADTR_UEVE_Msk (0x1UL << ATIMMODE23_ADTR_UEVE_Pos)
#define ATIMMODE23_ADTR_UEVE ATIMMODE23_ADTR_UEVE_Msk
#define ATIMMODE23_ADTR_CMA0E_Pos (1U)
#define ATIMMODE23_ADTR_CMA0E_Msk (0x1UL << ATIMMODE23_ADTR_CMA0E_Pos)
#define ATIMMODE23_ADTR_CMA0E ATIMMODE23_ADTR_CMA0E_Msk
#define ATIMMODE23_ADTR_CMB0E_Pos (4U)
#define ATIMMODE23_ADTR_CMB0E_Msk (0x1UL << ATIMMODE23_ADTR_CMB0E_Pos)
#define ATIMMODE23_ADTR_CMB0E ATIMMODE23_ADTR_CMB0E_Msk
#define ATIMMODE23_ADTR_ADTE_Pos (7U)
#define ATIMMODE23_ADTR_ADTE_Msk (0x1UL << ATIMMODE23_ADTR_ADTE_Pos)
#define ATIMMODE23_ADTR_ADTE ATIMMODE23_ADTR_ADTE_Msk

// ATIMMODE23_CRCH0
#define ATIMMODE23_CRCH0_CFACRABKSA_Pos (0U)
#define ATIMMODE23_CRCH0_CFACRABKSA_Msk (0x3UL << ATIMMODE23_CRCH0_CFACRABKSA_Pos)
#define ATIMMODE23_CRCH0_CFACRABKSA ATIMMODE23_CRCH0_CFACRABKSA_Msk
#define ATIMMODE23_CRCH0_CFBCRBBKSB_Pos (2U)
#define ATIMMODE23_CRCH0_CFBCRBBKSB_Msk (0x3UL << ATIMMODE23_CRCH0_CFBCRBBKSB_Pos)
#define ATIMMODE23_CRCH0_CFBCRBBKSB ATIMMODE23_CRCH0_CFBCRBBKSB_Msk
#define ATIMMODE23_CRCH0_CSA_Pos (4U)
#define ATIMMODE23_CRCH0_CSA_Msk (0x1UL << ATIMMODE23_CRCH0_CSA_Pos)
#define ATIMMODE23_CRCH0_CSA ATIMMODE23_CRCH0_CSA_Msk
#define ATIMMODE23_CRCH0_CSB_Pos (5U)
#define ATIMMODE23_CRCH0_CSB_Msk (0x1UL << ATIMMODE23_CRCH0_CSB_Pos)
#define ATIMMODE23_CRCH0_CSB ATIMMODE23_CRCH0_CSB_Msk
#define ATIMMODE23_CRCH0_BUFEA_Pos (6U)
#define ATIMMODE23_CRCH0_BUFEA_Msk (0x1UL << ATIMMODE23_CRCH0_BUFEA_Pos)
#define ATIMMODE23_CRCH0_BUFEA ATIMMODE23_CRCH0_BUFEA_Msk
#define ATIMMODE23_CRCH0_BUFEB_Pos (7U)
#define ATIMMODE23_CRCH0_BUFEB_Msk (0x1UL << ATIMMODE23_CRCH0_BUFEB_Pos)
#define ATIMMODE23_CRCH0_BUFEB ATIMMODE23_CRCH0_BUFEB_Msk
#define ATIMMODE23_CRCH0_CIEA_Pos (8U)
#define ATIMMODE23_CRCH0_CIEA_Msk (0x1UL << ATIMMODE23_CRCH0_CIEA_Pos)
#define ATIMMODE23_CRCH0_CIEA ATIMMODE23_CRCH0_CIEA_Msk
#define ATIMMODE23_CRCH0_CIEB_Pos (9U)
#define ATIMMODE23_CRCH0_CIEB_Msk (0x1UL << ATIMMODE23_CRCH0_CIEB_Pos)
#define ATIMMODE23_CRCH0_CIEB ATIMMODE23_CRCH0_CIEB_Msk
#define ATIMMODE23_CRCH0_CDEA_Pos (10U)
#define ATIMMODE23_CRCH0_CDEA_Msk (0x1UL << ATIMMODE23_CRCH0_CDEA_Pos)
#define ATIMMODE23_CRCH0_CDEA ATIMMODE23_CRCH0_CDEA_Msk
#define ATIMMODE23_CRCH0_CDEB_Pos (11U)
#define ATIMMODE23_CRCH0_CDEB_Msk (0x1UL << ATIMMODE23_CRCH0_CDEB_Pos)
#define ATIMMODE23_CRCH0_CDEB ATIMMODE23_CRCH0_CDEB_Msk
#define ATIMMODE23_CRCH0_CISB_Pos (12U)
#define ATIMMODE23_CRCH0_CISB_Msk (0x3UL << ATIMMODE23_CRCH0_CISB_Pos)
#define ATIMMODE23_CRCH0_CISB ATIMMODE23_CRCH0_CISB_Msk
#define ATIMMODE23_CRCH0_CCGA_Pos (14U)
#define ATIMMODE23_CRCH0_CCGA_Msk (0x1UL << ATIMMODE23_CRCH0_CCGA_Pos)
#define ATIMMODE23_CRCH0_CCGA ATIMMODE23_CRCH0_CCGA_Msk
#define ATIMMODE23_CRCH0_CCGB_Pos (15U)
#define ATIMMODE23_CRCH0_CCGB_Msk (0x1UL << ATIMMODE23_CRCH0_CCGB_Pos)
#define ATIMMODE23_CRCH0_CCGB ATIMMODE23_CRCH0_CCGB_Msk

// ATIMMODE23_DTR
#define ATIMMODE23_DTR_DTR_Pos (0U)
#define ATIMMODE23_DTR_DTR_Msk (0xFFUL << ATIMMODE23_DTR_DTR_Pos)
#define ATIMMODE23_DTR_DTR ATIMMODE23_DTR_DTR_Msk
#define ATIMMODE23_DTR_BKSEL_Pos (8U)
#define ATIMMODE23_DTR_BKSEL_Msk (0x1UL << ATIMMODE23_DTR_BKSEL_Pos)
#define ATIMMODE23_DTR_BKSEL ATIMMODE23_DTR_BKSEL_Msk
#define ATIMMODE23_DTR_DTEN_Pos (9U)
#define ATIMMODE23_DTR_DTEN_Msk (0x1UL << ATIMMODE23_DTR_DTEN_Pos)
#define ATIMMODE23_DTR_DTEN ATIMMODE23_DTR_DTEN_Msk
#define ATIMMODE23_DTR_BKE_Pos (10U)
#define ATIMMODE23_DTR_BKE_Msk (0x1UL << ATIMMODE23_DTR_BKE_Pos)
#define ATIMMODE23_DTR_BKE ATIMMODE23_DTR_BKE_Msk
#define ATIMMODE23_DTR_AOE_Pos (11U)
#define ATIMMODE23_DTR_AOE_Msk (0x1UL << ATIMMODE23_DTR_AOE_Pos)
#define ATIMMODE23_DTR_AOE ATIMMODE23_DTR_AOE_Msk
#define ATIMMODE23_DTR_MOE_Pos (12U)
#define ATIMMODE23_DTR_MOE_Msk (0x1UL << ATIMMODE23_DTR_MOE_Pos)
#define ATIMMODE23_DTR_MOE ATIMMODE23_DTR_MOE_Msk
#define ATIMMODE23_DTR_SAFEEN_Pos (13U)
#define ATIMMODE23_DTR_SAFEEN_Msk (0x1UL << ATIMMODE23_DTR_SAFEEN_Pos)
#define ATIMMODE23_DTR_SAFEEN ATIMMODE23_DTR_SAFEEN_Msk
#define ATIMMODE23_DTR_VCE_Pos (14U)
#define ATIMMODE23_DTR_VCE_Msk (0x1UL << ATIMMODE23_DTR_VCE_Pos)
#define ATIMMODE23_DTR_VCE ATIMMODE23_DTR_VCE_Msk

// ATIMMODE23_RCR
#define ATIMMODE23_RCR_RCR_Pos (0U)
#define ATIMMODE23_RCR_RCR_Msk (0xFFUL << ATIMMODE23_RCR_RCR_Pos)
#define ATIMMODE23_RCR_RCR ATIMMODE23_RCR_RCR_Msk
#define ATIMMODE23_RCR_OV_Pos (8U)
#define ATIMMODE23_RCR_OV_Msk (0x1UL << ATIMMODE23_RCR_OV_Pos)
#define ATIMMODE23_RCR_OV ATIMMODE23_RCR_OV_Msk
#define ATIMMODE23_RCR_UD_Pos (9U)
#define ATIMMODE23_RCR_UD_Msk (0x1UL << ATIMMODE23_RCR_UD_Pos)
#define ATIMMODE23_RCR_UD ATIMMODE23_RCR_UD_Msk

// ATIMMODE23_CCR0A
#define ATIMMODE23_CCR0A_CCR0A_Pos (0U)
#define ATIMMODE23_CCR0A_CCR0A_Msk (0xFFFFUL << ATIMMODE23_CCR0A_CCR0A_Pos)
#define ATIMMODE23_CCR0A_CCR0A ATIMMODE23_CCR0A_CCR0A_Msk

// ATIMMODE23_CCR0B
#define ATIMMODE23_CCR0B_CCR0B_Pos (0U)
#define ATIMMODE23_CCR0B_CCR0B_Msk (0xFFFFUL << ATIMMODE23_CCR0B_CCR0B_Pos)
#define ATIMMODE23_CCR0B_CCR0B ATIMMODE23_CCR0B_CCR0B_Msk

//********************    Bits Define For Peripheral BTIM    ********************//
// BTIM_ARR
#define BTIM_ARR_ARR_Pos (0U)
#define BTIM_ARR_ARR_Msk (0xFFFFUL << BTIM_ARR_ARR_Pos)
#define BTIM_ARR_ARR BTIM_ARR_ARR_Msk

// BTIM_CNT
#define BTIM_CNT_CNT_Pos (0U)
#define BTIM_CNT_CNT_Msk (0xFFFFUL << BTIM_CNT_CNT_Pos)
#define BTIM_CNT_CNT BTIM_CNT_CNT_Msk

// BTIM_CR
#define BTIM_CR_CEN_Pos (0U)
#define BTIM_CR_CEN_Msk (0x1UL << BTIM_CR_CEN_Pos)
#define BTIM_CR_CEN BTIM_CR_CEN_Msk
#define BTIM_CR_MD_Pos (1U)
#define BTIM_CR_MD_Msk (0x3UL << BTIM_CR_MD_Pos)
#define BTIM_CR_MD BTIM_CR_MD_Msk
#define BTIM_CR_TOGEN_Pos (3U)
#define BTIM_CR_TOGEN_Msk (0x1UL << BTIM_CR_TOGEN_Pos)
#define BTIM_CR_TOGEN BTIM_CR_TOGEN_Msk
#define BTIM_CR_PRS_Pos (4U)
#define BTIM_CR_PRS_Msk (0xFUL << BTIM_CR_PRS_Pos)
#define BTIM_CR_PRS BTIM_CR_PRS_Msk
#define BTIM_CR_OST_Pos (8U)
#define BTIM_CR_OST_Msk (0x1UL << BTIM_CR_OST_Pos)
#define BTIM_CR_OST BTIM_CR_OST_Msk
#define BTIM_CR_TRS_Pos (9U)
#define BTIM_CR_TRS_Msk (0x3UL << BTIM_CR_TRS_Pos)
#define BTIM_CR_TRS BTIM_CR_TRS_Msk
#define BTIM_CR_ETP_Pos (11U)
#define BTIM_CR_ETP_Msk (0x1UL << BTIM_CR_ETP_Pos)
#define BTIM_CR_ETP BTIM_CR_ETP_Msk

// BTIM_IER
#define BTIM_IER_UI_Pos (0U)
#define BTIM_IER_UI_Msk (0x1UL << BTIM_IER_UI_Pos)
#define BTIM_IER_UI BTIM_IER_UI_Msk
#define BTIM_IER_TI_Pos (1U)
#define BTIM_IER_TI_Msk (0x1UL << BTIM_IER_TI_Pos)
#define BTIM_IER_TI BTIM_IER_TI_Msk

// BTIM_IFR
#define BTIM_IFR_UI_Pos (0U)
#define BTIM_IFR_UI_Msk (0x1UL << BTIM_IFR_UI_Pos)
#define BTIM_IFR_UI BTIM_IFR_UI_Msk
#define BTIM_IFR_TI_Pos (1U)
#define BTIM_IFR_TI_Msk (0x1UL << BTIM_IFR_TI_Pos)
#define BTIM_IFR_TI BTIM_IFR_TI_Msk

// BTIM_ICR
#define BTIM_ICR_UI_Pos (0U)
#define BTIM_ICR_UI_Msk (0x1UL << BTIM_ICR_UI_Pos)
#define BTIM_ICR_UI BTIM_ICR_UI_Msk
#define BTIM_ICR_TI_Pos (1U)
#define BTIM_ICR_TI_Msk (0x1UL << BTIM_ICR_TI_Pos)
#define BTIM_ICR_TI BTIM_ICR_TI_Msk

// BTIM_AIFR
#define BTIM_AIFR_UI03_Pos (0U)
#define BTIM_AIFR_UI03_Msk (0x1UL << BTIM_AIFR_UI03_Pos)
#define BTIM_AIFR_UI03 BTIM_AIFR_UI03_Msk
#define BTIM_AIFR_TI03_Pos (1U)
#define BTIM_AIFR_TI03_Msk (0x1UL << BTIM_AIFR_TI03_Pos)
#define BTIM_AIFR_TI03 BTIM_AIFR_TI03_Msk
#define BTIM_AIFR_UI14_Pos (2U)
#define BTIM_AIFR_UI14_Msk (0x1UL << BTIM_AIFR_UI14_Pos)
#define BTIM_AIFR_UI14 BTIM_AIFR_UI14_Msk
#define BTIM_AIFR_TI14_Pos (3U)
#define BTIM_AIFR_TI14_Msk (0x1UL << BTIM_AIFR_TI14_Pos)
#define BTIM_AIFR_TI14 BTIM_AIFR_TI14_Msk
#define BTIM_AIFR_UI25_Pos (4U)
#define BTIM_AIFR_UI25_Msk (0x1UL << BTIM_AIFR_UI25_Pos)
#define BTIM_AIFR_UI25 BTIM_AIFR_UI25_Msk
#define BTIM_AIFR_TI25_Pos (5U)
#define BTIM_AIFR_TI25_Msk (0x1UL << BTIM_AIFR_TI25_Pos)
#define BTIM_AIFR_TI25 BTIM_AIFR_TI25_Msk

// BTIM_AICR
#define BTIM_AICR_UI03_Pos (0U)
#define BTIM_AICR_UI03_Msk (0x1UL << BTIM_AICR_UI03_Pos)
#define BTIM_AICR_UI03 BTIM_AICR_UI03_Msk
#define BTIM_AICR_TI03_Pos (1U)
#define BTIM_AICR_TI03_Msk (0x1UL << BTIM_AICR_TI03_Pos)
#define BTIM_AICR_TI03 BTIM_AICR_TI03_Msk
#define BTIM_AICR_UI14_Pos (2U)
#define BTIM_AICR_UI14_Msk (0x1UL << BTIM_AICR_UI14_Pos)
#define BTIM_AICR_UI14 BTIM_AICR_UI14_Msk
#define BTIM_AICR_TI14_Pos (3U)
#define BTIM_AICR_TI14_Msk (0x1UL << BTIM_AICR_TI14_Pos)
#define BTIM_AICR_TI14 BTIM_AICR_TI14_Msk
#define BTIM_AICR_UI25_Pos (4U)
#define BTIM_AICR_UI25_Msk (0x1UL << BTIM_AICR_UI25_Pos)
#define BTIM_AICR_UI25 BTIM_AICR_UI25_Msk
#define BTIM_AICR_TI25_Pos (5U)
#define BTIM_AICR_TI25_Msk (0x1UL << BTIM_AICR_TI25_Pos)
#define BTIM_AICR_TI25 BTIM_AICR_TI25_Msk

//********************    Bits Define For Peripheral CAN    ********************//
// CAN_CFG_STAT
#define CAN_CFG_STAT_BUSOFF_Pos (0U)
#define CAN_CFG_STAT_BUSOFF_Msk (0x1UL << CAN_CFG_STAT_BUSOFF_Pos)
#define CAN_CFG_STAT_BUSOFF CAN_CFG_STAT_BUSOFF_Msk
#define CAN_CFG_STAT_TACTIVE_Pos (1U)
#define CAN_CFG_STAT_TACTIVE_Msk (0x1UL << CAN_CFG_STAT_TACTIVE_Pos)
#define CAN_CFG_STAT_TACTIVE CAN_CFG_STAT_TACTIVE_Msk
#define CAN_CFG_STAT_RACTIVE_Pos (2U)
#define CAN_CFG_STAT_RACTIVE_Msk (0x1UL << CAN_CFG_STAT_RACTIVE_Pos)
#define CAN_CFG_STAT_RACTIVE CAN_CFG_STAT_RACTIVE_Msk
#define CAN_CFG_STAT_TSSS_Pos (3U)
#define CAN_CFG_STAT_TSSS_Msk (0x1UL << CAN_CFG_STAT_TSSS_Pos)
#define CAN_CFG_STAT_TSSS CAN_CFG_STAT_TSSS_Msk
#define CAN_CFG_STAT_TPSS_Pos (4U)
#define CAN_CFG_STAT_TPSS_Msk (0x1UL << CAN_CFG_STAT_TPSS_Pos)
#define CAN_CFG_STAT_TPSS CAN_CFG_STAT_TPSS_Msk
#define CAN_CFG_STAT_LBMI_Pos (5U)
#define CAN_CFG_STAT_LBMI_Msk (0x1UL << CAN_CFG_STAT_LBMI_Pos)
#define CAN_CFG_STAT_LBMI CAN_CFG_STAT_LBMI_Msk
#define CAN_CFG_STAT_LBME_Pos (6U)
#define CAN_CFG_STAT_LBME_Msk (0x1UL << CAN_CFG_STAT_LBME_Pos)
#define CAN_CFG_STAT_LBME CAN_CFG_STAT_LBME_Msk
#define CAN_CFG_STAT_RESET_Pos (7U)
#define CAN_CFG_STAT_RESET_Msk (0x1UL << CAN_CFG_STAT_RESET_Pos)
#define CAN_CFG_STAT_RESET CAN_CFG_STAT_RESET_Msk

// CAN_TCMD
#define CAN_TCMD_TSA_Pos (0U)
#define CAN_TCMD_TSA_Msk (0x1UL << CAN_TCMD_TSA_Pos)
#define CAN_TCMD_TSA CAN_TCMD_TSA_Msk
#define CAN_TCMD_TSALL_Pos (1U)
#define CAN_TCMD_TSALL_Msk (0x1UL << CAN_TCMD_TSALL_Pos)
#define CAN_TCMD_TSALL CAN_TCMD_TSALL_Msk
#define CAN_TCMD_TSONE_Pos (2U)
#define CAN_TCMD_TSONE_Msk (0x1UL << CAN_TCMD_TSONE_Pos)
#define CAN_TCMD_TSONE CAN_TCMD_TSONE_Msk
#define CAN_TCMD_TPA_Pos (3U)
#define CAN_TCMD_TPA_Msk (0x1UL << CAN_TCMD_TPA_Pos)
#define CAN_TCMD_TPA CAN_TCMD_TPA_Msk
#define CAN_TCMD_TPE_Pos (4U)
#define CAN_TCMD_TPE_Msk (0x1UL << CAN_TCMD_TPE_Pos)
#define CAN_TCMD_TPE CAN_TCMD_TPE_Msk
#define CAN_TCMD_STBY_Pos (5U)
#define CAN_TCMD_STBY_Msk (0x1UL << CAN_TCMD_STBY_Pos)
#define CAN_TCMD_STBY CAN_TCMD_STBY_Msk
#define CAN_TCMD_LOM_Pos (6U)
#define CAN_TCMD_LOM_Msk (0x1UL << CAN_TCMD_LOM_Pos)
#define CAN_TCMD_LOM CAN_TCMD_LOM_Msk
#define CAN_TCMD_TBSEL_Pos (7U)
#define CAN_TCMD_TBSEL_Msk (0x1UL << CAN_TCMD_TBSEL_Pos)
#define CAN_TCMD_TBSEL CAN_TCMD_TBSEL_Msk

// CAN_TCTRL
#define CAN_TCTRL_TSSTAT_Pos (0U)
#define CAN_TCTRL_TSSTAT_Msk (0x3UL << CAN_TCTRL_TSSTAT_Pos)
#define CAN_TCTRL_TSSTAT CAN_TCTRL_TSSTAT_Msk
#define CAN_TCTRL_TTTBM_Pos (4U)
#define CAN_TCTRL_TTTBM_Msk (0x1UL << CAN_TCTRL_TTTBM_Pos)
#define CAN_TCTRL_TTTBM CAN_TCTRL_TTTBM_Msk
#define CAN_TCTRL_TSMODE_Pos (5U)
#define CAN_TCTRL_TSMODE_Msk (0x1UL << CAN_TCTRL_TSMODE_Pos)
#define CAN_TCTRL_TSMODE CAN_TCTRL_TSMODE_Msk
#define CAN_TCTRL_TSNEXT_Pos (6U)
#define CAN_TCTRL_TSNEXT_Msk (0x1UL << CAN_TCTRL_TSNEXT_Pos)
#define CAN_TCTRL_TSNEXT CAN_TCTRL_TSNEXT_Msk

// CAN_RCTRL
#define CAN_RCTRL_RSSTAT_Pos (0U)
#define CAN_RCTRL_RSSTAT_Msk (0x3UL << CAN_RCTRL_RSSTAT_Pos)
#define CAN_RCTRL_RSSTAT CAN_RCTRL_RSSTAT_Msk
#define CAN_RCTRL_RBALL_Pos (3U)
#define CAN_RCTRL_RBALL_Msk (0x1UL << CAN_RCTRL_RBALL_Pos)
#define CAN_RCTRL_RBALL CAN_RCTRL_RBALL_Msk
#define CAN_RCTRL_RREL_Pos (4U)
#define CAN_RCTRL_RREL_Msk (0x1UL << CAN_RCTRL_RREL_Pos)
#define CAN_RCTRL_RREL CAN_RCTRL_RREL_Msk
#define CAN_RCTRL_ROV_Pos (5U)
#define CAN_RCTRL_ROV_Msk (0x1UL << CAN_RCTRL_ROV_Pos)
#define CAN_RCTRL_ROV CAN_RCTRL_ROV_Msk
#define CAN_RCTRL_ROM_Pos (6U)
#define CAN_RCTRL_ROM_Msk (0x1UL << CAN_RCTRL_ROM_Pos)
#define CAN_RCTRL_ROM CAN_RCTRL_ROM_Msk
#define CAN_RCTRL_SACK_Pos (7U)
#define CAN_RCTRL_SACK_Msk (0x1UL << CAN_RCTRL_SACK_Pos)
#define CAN_RCTRL_SACK CAN_RCTRL_SACK_Msk

// CAN_RTIE
#define CAN_RTIE_TSFF_Pos (0U)
#define CAN_RTIE_TSFF_Msk (0x1UL << CAN_RTIE_TSFF_Pos)
#define CAN_RTIE_TSFF CAN_RTIE_TSFF_Msk
#define CAN_RTIE_EIE_Pos (1U)
#define CAN_RTIE_EIE_Msk (0x1UL << CAN_RTIE_EIE_Pos)
#define CAN_RTIE_EIE CAN_RTIE_EIE_Msk
#define CAN_RTIE_TSIE_Pos (2U)
#define CAN_RTIE_TSIE_Msk (0x1UL << CAN_RTIE_TSIE_Pos)
#define CAN_RTIE_TSIE CAN_RTIE_TSIE_Msk
#define CAN_RTIE_TPIE_Pos (3U)
#define CAN_RTIE_TPIE_Msk (0x1UL << CAN_RTIE_TPIE_Pos)
#define CAN_RTIE_TPIE CAN_RTIE_TPIE_Msk
#define CAN_RTIE_RAFIE_Pos (4U)
#define CAN_RTIE_RAFIE_Msk (0x1UL << CAN_RTIE_RAFIE_Pos)
#define CAN_RTIE_RAFIE CAN_RTIE_RAFIE_Msk
#define CAN_RTIE_RFIE_Pos (5U)
#define CAN_RTIE_RFIE_Msk (0x1UL << CAN_RTIE_RFIE_Pos)
#define CAN_RTIE_RFIE CAN_RTIE_RFIE_Msk
#define CAN_RTIE_ROIE_Pos (6U)
#define CAN_RTIE_ROIE_Msk (0x1UL << CAN_RTIE_ROIE_Pos)
#define CAN_RTIE_ROIE CAN_RTIE_ROIE_Msk
#define CAN_RTIE_RIE_Pos (7U)
#define CAN_RTIE_RIE_Msk (0x1UL << CAN_RTIE_RIE_Pos)
#define CAN_RTIE_RIE CAN_RTIE_RIE_Msk

// CAN_RTIF
#define CAN_RTIF_AIF_Pos (0U)
#define CAN_RTIF_AIF_Msk (0x1UL << CAN_RTIF_AIF_Pos)
#define CAN_RTIF_AIF CAN_RTIF_AIF_Msk
#define CAN_RTIF_EIF_Pos (1U)
#define CAN_RTIF_EIF_Msk (0x1UL << CAN_RTIF_EIF_Pos)
#define CAN_RTIF_EIF CAN_RTIF_EIF_Msk
#define CAN_RTIF_TSIF_Pos (2U)
#define CAN_RTIF_TSIF_Msk (0x1UL << CAN_RTIF_TSIF_Pos)
#define CAN_RTIF_TSIF CAN_RTIF_TSIF_Msk
#define CAN_RTIF_TPIF_Pos (3U)
#define CAN_RTIF_TPIF_Msk (0x1UL << CAN_RTIF_TPIF_Pos)
#define CAN_RTIF_TPIF CAN_RTIF_TPIF_Msk
#define CAN_RTIF_RAFIF_Pos (4U)
#define CAN_RTIF_RAFIF_Msk (0x1UL << CAN_RTIF_RAFIF_Pos)
#define CAN_RTIF_RAFIF CAN_RTIF_RAFIF_Msk
#define CAN_RTIF_RFIF_Pos (5U)
#define CAN_RTIF_RFIF_Msk (0x1UL << CAN_RTIF_RFIF_Pos)
#define CAN_RTIF_RFIF CAN_RTIF_RFIF_Msk
#define CAN_RTIF_ROIF_Pos (6U)
#define CAN_RTIF_ROIF_Msk (0x1UL << CAN_RTIF_ROIF_Pos)
#define CAN_RTIF_ROIF CAN_RTIF_ROIF_Msk
#define CAN_RTIF_RIF_Pos (7U)
#define CAN_RTIF_RIF_Msk (0x1UL << CAN_RTIF_RIF_Pos)
#define CAN_RTIF_RIF CAN_RTIF_RIF_Msk

// CAN_ERRINT
#define CAN_ERRINT_BEIF_Pos (0U)
#define CAN_ERRINT_BEIF_Msk (0x1UL << CAN_ERRINT_BEIF_Pos)
#define CAN_ERRINT_BEIF CAN_ERRINT_BEIF_Msk
#define CAN_ERRINT_BEIE_Pos (1U)
#define CAN_ERRINT_BEIE_Msk (0x1UL << CAN_ERRINT_BEIE_Pos)
#define CAN_ERRINT_BEIE CAN_ERRINT_BEIE_Msk
#define CAN_ERRINT_ALIF_Pos (2U)
#define CAN_ERRINT_ALIF_Msk (0x1UL << CAN_ERRINT_ALIF_Pos)
#define CAN_ERRINT_ALIF CAN_ERRINT_ALIF_Msk
#define CAN_ERRINT_ALIE_Pos (3U)
#define CAN_ERRINT_ALIE_Msk (0x1UL << CAN_ERRINT_ALIE_Pos)
#define CAN_ERRINT_ALIE CAN_ERRINT_ALIE_Msk
#define CAN_ERRINT_EPIF_Pos (4U)
#define CAN_ERRINT_EPIF_Msk (0x1UL << CAN_ERRINT_EPIF_Pos)
#define CAN_ERRINT_EPIF CAN_ERRINT_EPIF_Msk
#define CAN_ERRINT_EPIE_Pos (5U)
#define CAN_ERRINT_EPIE_Msk (0x1UL << CAN_ERRINT_EPIE_Pos)
#define CAN_ERRINT_EPIE CAN_ERRINT_EPIE_Msk
#define CAN_ERRINT_EPASS_Pos (6U)
#define CAN_ERRINT_EPASS_Msk (0x1UL << CAN_ERRINT_EPASS_Pos)
#define CAN_ERRINT_EPASS CAN_ERRINT_EPASS_Msk
#define CAN_ERRINT_EWARN_Pos (7U)
#define CAN_ERRINT_EWARN_Msk (0x1UL << CAN_ERRINT_EWARN_Pos)
#define CAN_ERRINT_EWARN CAN_ERRINT_EWARN_Msk

// CAN_LIMIT
#define CAN_LIMIT_EWL_Pos (0U)
#define CAN_LIMIT_EWL_Msk (0xFUL << CAN_LIMIT_EWL_Pos)
#define CAN_LIMIT_EWL CAN_LIMIT_EWL_Msk
#define CAN_LIMIT_AFWL_Pos (4U)
#define CAN_LIMIT_AFWL_Msk (0xFUL << CAN_LIMIT_AFWL_Pos)
#define CAN_LIMIT_AFWL CAN_LIMIT_AFWL_Msk

// CAN_BT
#define CAN_BT_SEG_1_Pos (0U)
#define CAN_BT_SEG_1_Msk (0xFFUL << CAN_BT_SEG_1_Pos)
#define CAN_BT_SEG_1 CAN_BT_SEG_1_Msk
#define CAN_BT_SEG_2_Pos (8U)
#define CAN_BT_SEG_2_Msk (0x7FUL << CAN_BT_SEG_2_Pos)
#define CAN_BT_SEG_2 CAN_BT_SEG_2_Msk
#define CAN_BT_SJW_Pos (16U)
#define CAN_BT_SJW_Msk (0x7FUL << CAN_BT_SJW_Pos)
#define CAN_BT_SJW CAN_BT_SJW_Msk
#define CAN_BT_PRESC_Pos (24U)
#define CAN_BT_PRESC_Msk (0xFFUL << CAN_BT_PRESC_Pos)
#define CAN_BT_PRESC CAN_BT_PRESC_Msk

// CAN_EALCAP
#define CAN_EALCAP_ALC_Pos (0U)
#define CAN_EALCAP_ALC_Msk (0x1FUL << CAN_EALCAP_ALC_Pos)
#define CAN_EALCAP_ALC CAN_EALCAP_ALC_Msk
#define CAN_EALCAP_KOER_Pos (5U)
#define CAN_EALCAP_KOER_Msk (0x7UL << CAN_EALCAP_KOER_Pos)
#define CAN_EALCAP_KOER CAN_EALCAP_KOER_Msk

// CAN_ACFCTRL
#define CAN_ACFCTRL_ACFADR_Pos (0U)
#define CAN_ACFCTRL_ACFADR_Msk (0xFUL << CAN_ACFCTRL_ACFADR_Pos)
#define CAN_ACFCTRL_ACFADR CAN_ACFCTRL_ACFADR_Msk
#define CAN_ACFCTRL_SELMASK_Pos (5U)
#define CAN_ACFCTRL_SELMASK_Msk (0x1UL << CAN_ACFCTRL_SELMASK_Pos)
#define CAN_ACFCTRL_SELMASK CAN_ACFCTRL_SELMASK_Msk

// CAN_ACFEN
#define CAN_ACFEN_AE_1_Pos (0U)
#define CAN_ACFEN_AE_1_Msk (0x1UL << CAN_ACFEN_AE_1_Pos)
#define CAN_ACFEN_AE_1 CAN_ACFEN_AE_1_Msk
#define CAN_ACFEN_AE_2_Pos (1U)
#define CAN_ACFEN_AE_2_Msk (0x1UL << CAN_ACFEN_AE_2_Pos)
#define CAN_ACFEN_AE_2 CAN_ACFEN_AE_2_Msk
#define CAN_ACFEN_AE_3_Pos (2U)
#define CAN_ACFEN_AE_3_Msk (0x1UL << CAN_ACFEN_AE_3_Pos)
#define CAN_ACFEN_AE_3 CAN_ACFEN_AE_3_Msk
#define CAN_ACFEN_AE_4_Pos (3U)
#define CAN_ACFEN_AE_4_Msk (0x1UL << CAN_ACFEN_AE_4_Pos)
#define CAN_ACFEN_AE_4 CAN_ACFEN_AE_4_Msk
#define CAN_ACFEN_AE_5_Pos (4U)
#define CAN_ACFEN_AE_5_Msk (0x1UL << CAN_ACFEN_AE_5_Pos)
#define CAN_ACFEN_AE_5 CAN_ACFEN_AE_5_Msk
#define CAN_ACFEN_AE_6_Pos (5U)
#define CAN_ACFEN_AE_6_Msk (0x1UL << CAN_ACFEN_AE_6_Pos)
#define CAN_ACFEN_AE_6 CAN_ACFEN_AE_6_Msk
#define CAN_ACFEN_AE_7_Pos (6U)
#define CAN_ACFEN_AE_7_Msk (0x1UL << CAN_ACFEN_AE_7_Pos)
#define CAN_ACFEN_AE_7 CAN_ACFEN_AE_7_Msk
#define CAN_ACFEN_AE_8_Pos (7U)
#define CAN_ACFEN_AE_8_Msk (0x1UL << CAN_ACFEN_AE_8_Pos)
#define CAN_ACFEN_AE_8 CAN_ACFEN_AE_8_Msk

// CAN_ACF
#define CAN_ACF_ACODE_AMASK_Pos (0U)
#define CAN_ACF_ACODE_AMASK_Msk (0x1FFFFFFFUL << CAN_ACF_ACODE_AMASK_Pos)
#define CAN_ACF_ACODE_AMASK CAN_ACF_ACODE_AMASK_Msk
#define CAN_ACF_AIDE_Pos (29U)
#define CAN_ACF_AIDE_Msk (0x1UL << CAN_ACF_AIDE_Pos)
#define CAN_ACF_AIDE CAN_ACF_AIDE_Msk
#define CAN_ACF_AIDEE_Pos (30U)
#define CAN_ACF_AIDEE_Msk (0x1UL << CAN_ACF_AIDEE_Pos)
#define CAN_ACF_AIDEE CAN_ACF_AIDEE_Msk

// CAN_TBSLOT
#define CAN_TBSLOT_TBPTR_Pos (0U)
#define CAN_TBSLOT_TBPTR_Msk (0x7UL << CAN_TBSLOT_TBPTR_Pos)
#define CAN_TBSLOT_TBPTR CAN_TBSLOT_TBPTR_Msk
#define CAN_TBSLOT_TBF_Pos (6U)
#define CAN_TBSLOT_TBF_Msk (0x1UL << CAN_TBSLOT_TBF_Pos)
#define CAN_TBSLOT_TBF CAN_TBSLOT_TBF_Msk
#define CAN_TBSLOT_TBE_Pos (7U)
#define CAN_TBSLOT_TBE_Msk (0x1UL << CAN_TBSLOT_TBE_Pos)
#define CAN_TBSLOT_TBE CAN_TBSLOT_TBE_Msk

// CAN_TTCFG
#define CAN_TTCFG_TTEN_Pos (0U)
#define CAN_TTCFG_TTEN_Msk (0x1UL << CAN_TTCFG_TTEN_Pos)
#define CAN_TTCFG_TTEN CAN_TTCFG_TTEN_Msk
#define CAN_TTCFG_T_PRESC_Pos (1U)
#define CAN_TTCFG_T_PRESC_Msk (0x3UL << CAN_TTCFG_T_PRESC_Pos)
#define CAN_TTCFG_T_PRESC CAN_TTCFG_T_PRESC_Msk
#define CAN_TTCFG_TTIF_Pos (3U)
#define CAN_TTCFG_TTIF_Msk (0x1UL << CAN_TTCFG_TTIF_Pos)
#define CAN_TTCFG_TTIF CAN_TTCFG_TTIF_Msk
#define CAN_TTCFG_TTIE_Pos (4U)
#define CAN_TTCFG_TTIE_Msk (0x1UL << CAN_TTCFG_TTIE_Pos)
#define CAN_TTCFG_TTIE CAN_TTCFG_TTIE_Msk
#define CAN_TTCFG_TEIF_Pos (5U)
#define CAN_TTCFG_TEIF_Msk (0x1UL << CAN_TTCFG_TEIF_Pos)
#define CAN_TTCFG_TEIF CAN_TTCFG_TEIF_Msk
#define CAN_TTCFG_WTIF_Pos (6U)
#define CAN_TTCFG_WTIF_Msk (0x1UL << CAN_TTCFG_WTIF_Pos)
#define CAN_TTCFG_WTIF CAN_TTCFG_WTIF_Msk
#define CAN_TTCFG_WTIE_Pos (7U)
#define CAN_TTCFG_WTIE_Msk (0x1UL << CAN_TTCFG_WTIE_Pos)
#define CAN_TTCFG_WTIE CAN_TTCFG_WTIE_Msk

// CAN_REF_MSG
#define CAN_REF_MSG_REF_ID_Pos (0U)
#define CAN_REF_MSG_REF_ID_Msk (0x1FFFFFFFUL << CAN_REF_MSG_REF_ID_Pos)
#define CAN_REF_MSG_REF_ID CAN_REF_MSG_REF_ID_Msk
#define CAN_REF_MSG_REF_IDE_Pos (31U)
#define CAN_REF_MSG_REF_IDE_Msk (0x1UL << CAN_REF_MSG_REF_IDE_Pos)
#define CAN_REF_MSG_REF_IDE CAN_REF_MSG_REF_IDE_Msk

// CAN_TRG_CFG
#define CAN_TRG_CFG_TTPTR_Pos (0U)
#define CAN_TRG_CFG_TTPTR_Msk (0x7UL << CAN_TRG_CFG_TTPTR_Pos)
#define CAN_TRG_CFG_TTPTR CAN_TRG_CFG_TTPTR_Msk
#define CAN_TRG_CFG_TTYPE_Pos (8U)
#define CAN_TRG_CFG_TTYPE_Msk (0x7UL << CAN_TRG_CFG_TTYPE_Pos)
#define CAN_TRG_CFG_TTYPE CAN_TRG_CFG_TTYPE_Msk
#define CAN_TRG_CFG_TEW_Pos (12U)
#define CAN_TRG_CFG_TEW_Msk (0xFUL << CAN_TRG_CFG_TEW_Pos)
#define CAN_TRG_CFG_TEW CAN_TRG_CFG_TEW_Msk

//********************    Bits Define For Peripheral CRC    ********************//
// CRC_CSR
#define CRC_CSR_CODE_Pos (0U)
#define CRC_CSR_CODE_Msk (0x1UL << CRC_CSR_CODE_Pos)
#define CRC_CSR_CODE CRC_CSR_CODE_Msk
#define CRC_CSR_FLAG_Pos (1U)
#define CRC_CSR_FLAG_Msk (0x1UL << CRC_CSR_FLAG_Pos)
#define CRC_CSR_FLAG CRC_CSR_FLAG_Msk

// CRC_RESULT
#define CRC_RESULT_RESULT_Pos (0U)
#define CRC_RESULT_RESULT_Msk (0xFFFFFFFFUL << CRC_RESULT_RESULT_Pos)
#define CRC_RESULT_RESULT CRC_RESULT_RESULT_Msk

// CRC_DATA
#define CRC_DATA_DATA_Pos (0U)
#define CRC_DATA_DATA_Msk (0xFFFFFFFFUL << CRC_DATA_DATA_Pos)
#define CRC_DATA_DATA CRC_DATA_DATA_Msk

//********************    Bits Define For Peripheral CTRIM    ********************//
// CTRIM_ARR
#define CTRIM_ARR_ARR_Pos (0U)
#define CTRIM_ARR_ARR_Msk (0xFFFFUL << CTRIM_ARR_ARR_Pos)
#define CTRIM_ARR_ARR CTRIM_ARR_ARR_Msk

// CTRIM_CNT
#define CTRIM_CNT_CNT_Pos (0U)
#define CTRIM_CNT_CNT_Msk (0xFFFFUL << CTRIM_CNT_CNT_Pos)
#define CTRIM_CNT_CNT CTRIM_CNT_CNT_Msk

// CTRIM_CR0
#define CTRIM_CR0_STEP_Pos (0U)
#define CTRIM_CR0_STEP_Msk (0x7UL << CTRIM_CR0_STEP_Pos)
#define CTRIM_CR0_STEP CTRIM_CR0_STEP_Msk
#define CTRIM_CR0_ETRFLT_Pos (4U)
#define CTRIM_CR0_ETRFLT_Msk (0x7UL << CTRIM_CR0_ETRFLT_Pos)
#define CTRIM_CR0_ETRFLT CTRIM_CR0_ETRFLT_Msk
#define CTRIM_CR0_SRC_Pos (8U)
#define CTRIM_CR0_SRC_Msk (0x7UL << CTRIM_CR0_SRC_Pos)
#define CTRIM_CR0_SRC CTRIM_CR0_SRC_Msk

// CTRIM_CR1
#define CTRIM_CR1_EN_Pos (0U)
#define CTRIM_CR1_EN_Msk (0x1UL << CTRIM_CR1_EN_Pos)
#define CTRIM_CR1_EN CTRIM_CR1_EN_Msk
#define CTRIM_CR1_MD_Pos (1U)
#define CTRIM_CR1_MD_Msk (0x3UL << CTRIM_CR1_MD_Pos)
#define CTRIM_CR1_MD CTRIM_CR1_MD_Msk
#define CTRIM_CR1_AUTO_Pos (3U)
#define CTRIM_CR1_AUTO_Msk (0x1UL << CTRIM_CR1_AUTO_Pos)
#define CTRIM_CR1_AUTO CTRIM_CR1_AUTO_Msk
#define CTRIM_CR1_PRS_Pos (4U)
#define CTRIM_CR1_PRS_Msk (0xFUL << CTRIM_CR1_PRS_Pos)
#define CTRIM_CR1_PRS CTRIM_CR1_PRS_Msk
#define CTRIM_CR1_OST_Pos (8U)
#define CTRIM_CR1_OST_Msk (0x1UL << CTRIM_CR1_OST_Pos)
#define CTRIM_CR1_OST CTRIM_CR1_OST_Msk
#define CTRIM_CR1_MDRCH_Pos (9U)
#define CTRIM_CR1_MDRCH_Msk (0x3UL << CTRIM_CR1_MDRCH_Pos)
#define CTRIM_CR1_MDRCH CTRIM_CR1_MDRCH_Msk

// CTRIM_IER
#define CTRIM_IER_UD_Pos (0U)
#define CTRIM_IER_UD_Msk (0x1UL << CTRIM_IER_UD_Pos)
#define CTRIM_IER_UD CTRIM_IER_UD_Msk
#define CTRIM_IER_END_Pos (1U)
#define CTRIM_IER_END_Msk (0x1UL << CTRIM_IER_END_Pos)
#define CTRIM_IER_END CTRIM_IER_END_Msk
#define CTRIM_IER_PS_Pos (2U)
#define CTRIM_IER_PS_Msk (0x1UL << CTRIM_IER_PS_Pos)
#define CTRIM_IER_PS CTRIM_IER_PS_Msk
#define CTRIM_IER_MISS_Pos (3U)
#define CTRIM_IER_MISS_Msk (0x1UL << CTRIM_IER_MISS_Pos)
#define CTRIM_IER_MISS CTRIM_IER_MISS_Msk
#define CTRIM_IER_OV_Pos (4U)
#define CTRIM_IER_OV_Msk (0x1UL << CTRIM_IER_OV_Pos)
#define CTRIM_IER_OV CTRIM_IER_OV_Msk
#define CTRIM_IER_OK_Pos (5U)
#define CTRIM_IER_OK_Msk (0x1UL << CTRIM_IER_OK_Pos)
#define CTRIM_IER_OK CTRIM_IER_OK_Msk

// CTRIM_ISR
#define CTRIM_ISR_UD_Pos (0U)
#define CTRIM_ISR_UD_Msk (0x1UL << CTRIM_ISR_UD_Pos)
#define CTRIM_ISR_UD CTRIM_ISR_UD_Msk
#define CTRIM_ISR_END_Pos (1U)
#define CTRIM_ISR_END_Msk (0x1UL << CTRIM_ISR_END_Pos)
#define CTRIM_ISR_END CTRIM_ISR_END_Msk
#define CTRIM_ISR_PS_Pos (2U)
#define CTRIM_ISR_PS_Msk (0x1UL << CTRIM_ISR_PS_Pos)
#define CTRIM_ISR_PS CTRIM_ISR_PS_Msk
#define CTRIM_ISR_MISS_Pos (3U)
#define CTRIM_ISR_MISS_Msk (0x1UL << CTRIM_ISR_MISS_Pos)
#define CTRIM_ISR_MISS CTRIM_ISR_MISS_Msk
#define CTRIM_ISR_OV_Pos (4U)
#define CTRIM_ISR_OV_Msk (0x1UL << CTRIM_ISR_OV_Pos)
#define CTRIM_ISR_OV CTRIM_ISR_OV_Msk
#define CTRIM_ISR_OK_Pos (5U)
#define CTRIM_ISR_OK_Msk (0x1UL << CTRIM_ISR_OK_Pos)
#define CTRIM_ISR_OK CTRIM_ISR_OK_Msk
#define CTRIM_ISR_DIR_Pos (6U)
#define CTRIM_ISR_DIR_Msk (0x1UL << CTRIM_ISR_DIR_Pos)
#define CTRIM_ISR_DIR CTRIM_ISR_DIR_Msk

// CTRIM_ICR
#define CTRIM_ICR_UD_Pos (0U)
#define CTRIM_ICR_UD_Msk (0x1UL << CTRIM_ICR_UD_Pos)
#define CTRIM_ICR_UD CTRIM_ICR_UD_Msk
#define CTRIM_ICR_END_Pos (1U)
#define CTRIM_ICR_END_Msk (0x1UL << CTRIM_ICR_END_Pos)
#define CTRIM_ICR_END CTRIM_ICR_END_Msk
#define CTRIM_ICR_PS_Pos (2U)
#define CTRIM_ICR_PS_Msk (0x1UL << CTRIM_ICR_PS_Pos)
#define CTRIM_ICR_PS CTRIM_ICR_PS_Msk
#define CTRIM_ICR_MISS_Pos (3U)
#define CTRIM_ICR_MISS_Msk (0x1UL << CTRIM_ICR_MISS_Pos)
#define CTRIM_ICR_MISS CTRIM_ICR_MISS_Msk
#define CTRIM_ICR_OV_Pos (4U)
#define CTRIM_ICR_OV_Msk (0x1UL << CTRIM_ICR_OV_Pos)
#define CTRIM_ICR_OV CTRIM_ICR_OV_Msk
#define CTRIM_ICR_OK_Pos (5U)
#define CTRIM_ICR_OK_Msk (0x1UL << CTRIM_ICR_OK_Pos)
#define CTRIM_ICR_OK CTRIM_ICR_OK_Msk

// CTRIM_FCAP
#define CTRIM_FCAP_FCAP_Pos (0U)
#define CTRIM_FCAP_FCAP_Msk (0xFFFFUL << CTRIM_FCAP_FCAP_Pos)
#define CTRIM_FCAP_FCAP CTRIM_FCAP_FCAP_Msk

// CTRIM_TVAL
#define CTRIM_TVAL_TVAL_Pos (0U)
#define CTRIM_TVAL_TVAL_Msk (0xFFFFUL << CTRIM_TVAL_TVAL_Pos)
#define CTRIM_TVAL_TVAL CTRIM_TVAL_TVAL_Msk

// CTRIM_FLIM
#define CTRIM_FLIM_FLIM_Pos (0U)
#define CTRIM_FLIM_FLIM_Msk (0xFFFUL << CTRIM_FLIM_FLIM_Pos)
#define CTRIM_FLIM_FLIM CTRIM_FLIM_FLIM_Msk

//********************    Bits Define For Peripheral DMAC    ********************//
// DMAC_CONF
#define DMAC_CONF_HALT_Pos (24U)
#define DMAC_CONF_HALT_Msk (0xFUL << DMAC_CONF_HALT_Pos)
#define DMAC_CONF_HALT DMAC_CONF_HALT_Msk
#define DMAC_CONF_PRIO_Pos (28U)
#define DMAC_CONF_PRIO_Msk (0x1UL << DMAC_CONF_PRIO_Pos)
#define DMAC_CONF_PRIO DMAC_CONF_PRIO_Msk
#define DMAC_CONF_EN_Pos (31U)
#define DMAC_CONF_EN_Msk (0x1UL << DMAC_CONF_EN_Pos)
#define DMAC_CONF_EN DMAC_CONF_EN_Msk

// DMAC_CONFA0
#define DMAC_CONFA0_TC_Pos (0U)
#define DMAC_CONFA0_TC_Msk (0xFFFFUL << DMAC_CONFA0_TC_Pos)
#define DMAC_CONFA0_TC DMAC_CONFA0_TC_Msk
#define DMAC_CONFA0_BC_Pos (16U)
#define DMAC_CONFA0_BC_Msk (0xFUL << DMAC_CONFA0_BC_Pos)
#define DMAC_CONFA0_BC DMAC_CONFA0_BC_Msk
#define DMAC_CONFA0_TRISEL_Pos (22U)
#define DMAC_CONFA0_TRISEL_Msk (0x7FUL << DMAC_CONFA0_TRISEL_Pos)
#define DMAC_CONFA0_TRISEL DMAC_CONFA0_TRISEL_Msk
#define DMAC_CONFA0_ST_Pos (29U)
#define DMAC_CONFA0_ST_Msk (0x1UL << DMAC_CONFA0_ST_Pos)
#define DMAC_CONFA0_ST DMAC_CONFA0_ST_Msk
#define DMAC_CONFA0_PAS_Pos (30U)
#define DMAC_CONFA0_PAS_Msk (0x1UL << DMAC_CONFA0_PAS_Pos)
#define DMAC_CONFA0_PAS DMAC_CONFA0_PAS_Msk
#define DMAC_CONFA0_ENS_Pos (31U)
#define DMAC_CONFA0_ENS_Msk (0x1UL << DMAC_CONFA0_ENS_Pos)
#define DMAC_CONFA0_ENS DMAC_CONFA0_ENS_Msk

// DMAC_CONFB0
#define DMAC_CONFB0_MSK_Pos (0U)
#define DMAC_CONFB0_MSK_Msk (0x1UL << DMAC_CONFB0_MSK_Pos)
#define DMAC_CONFB0_MSK DMAC_CONFB0_MSK_Msk
#define DMAC_CONFB0_STAT_Pos (16U)
#define DMAC_CONFB0_STAT_Msk (0x7UL << DMAC_CONFB0_STAT_Pos)
#define DMAC_CONFB0_STAT DMAC_CONFB0_STAT_Msk
#define DMAC_CONFB0_FISIE_Pos (19U)
#define DMAC_CONFB0_FISIE_Msk (0x1UL << DMAC_CONFB0_FISIE_Pos)
#define DMAC_CONFB0_FISIE DMAC_CONFB0_FISIE_Msk
#define DMAC_CONFB0_ERRIE_Pos (20U)
#define DMAC_CONFB0_ERRIE_Msk (0x1UL << DMAC_CONFB0_ERRIE_Pos)
#define DMAC_CONFB0_ERRIE DMAC_CONFB0_ERRIE_Msk
#define DMAC_CONFB0_RD_Pos (21U)
#define DMAC_CONFB0_RD_Msk (0x1UL << DMAC_CONFB0_RD_Pos)
#define DMAC_CONFB0_RD DMAC_CONFB0_RD_Msk
#define DMAC_CONFB0_RS_Pos (22U)
#define DMAC_CONFB0_RS_Msk (0x1UL << DMAC_CONFB0_RS_Pos)
#define DMAC_CONFB0_RS DMAC_CONFB0_RS_Msk
#define DMAC_CONFB0_RC_Pos (23U)
#define DMAC_CONFB0_RC_Msk (0x1UL << DMAC_CONFB0_RC_Pos)
#define DMAC_CONFB0_RC DMAC_CONFB0_RC_Msk
#define DMAC_CONFB0_FD_Pos (24U)
#define DMAC_CONFB0_FD_Msk (0x1UL << DMAC_CONFB0_FD_Pos)
#define DMAC_CONFB0_FD DMAC_CONFB0_FD_Msk
#define DMAC_CONFB0_FS_Pos (25U)
#define DMAC_CONFB0_FS_Msk (0x1UL << DMAC_CONFB0_FS_Pos)
#define DMAC_CONFB0_FS DMAC_CONFB0_FS_Msk
#define DMAC_CONFB0_WIDTH_Pos (26U)
#define DMAC_CONFB0_WIDTH_Msk (0x3UL << DMAC_CONFB0_WIDTH_Pos)
#define DMAC_CONFB0_WIDTH DMAC_CONFB0_WIDTH_Msk
#define DMAC_CONFB0_MODE_Pos (28U)
#define DMAC_CONFB0_MODE_Msk (0x3UL << DMAC_CONFB0_MODE_Pos)
#define DMAC_CONFB0_MODE DMAC_CONFB0_MODE_Msk

// DMAC_SRCADR0
#define DMAC_SRCADR0_SRCADR_Pos (0U)
#define DMAC_SRCADR0_SRCADR_Msk (0xFFFFFFFFUL << DMAC_SRCADR0_SRCADR_Pos)
#define DMAC_SRCADR0_SRCADR DMAC_SRCADR0_SRCADR_Msk

// DMAC_DSTADR0
#define DMAC_DSTADR0_DSTADR_Pos (0U)
#define DMAC_DSTADR0_DSTADR_Msk (0xFFFFFFFFUL << DMAC_DSTADR0_DSTADR_Pos)
#define DMAC_DSTADR0_DSTADR DMAC_DSTADR0_DSTADR_Msk

// DMAC_CONFA1
#define DMAC_CONFA1_TC_Pos (0U)
#define DMAC_CONFA1_TC_Msk (0xFFFFUL << DMAC_CONFA1_TC_Pos)
#define DMAC_CONFA1_TC DMAC_CONFA1_TC_Msk
#define DMAC_CONFA1_BC_Pos (16U)
#define DMAC_CONFA1_BC_Msk (0xFUL << DMAC_CONFA1_BC_Pos)
#define DMAC_CONFA1_BC DMAC_CONFA1_BC_Msk
#define DMAC_CONFA1_TRISEL_Pos (22U)
#define DMAC_CONFA1_TRISEL_Msk (0x7FUL << DMAC_CONFA1_TRISEL_Pos)
#define DMAC_CONFA1_TRISEL DMAC_CONFA1_TRISEL_Msk
#define DMAC_CONFA1_ST_Pos (29U)
#define DMAC_CONFA1_ST_Msk (0x1UL << DMAC_CONFA1_ST_Pos)
#define DMAC_CONFA1_ST DMAC_CONFA1_ST_Msk
#define DMAC_CONFA1_PAS_Pos (30U)
#define DMAC_CONFA1_PAS_Msk (0x1UL << DMAC_CONFA1_PAS_Pos)
#define DMAC_CONFA1_PAS DMAC_CONFA1_PAS_Msk
#define DMAC_CONFA1_ENS_Pos (31U)
#define DMAC_CONFA1_ENS_Msk (0x1UL << DMAC_CONFA1_ENS_Pos)
#define DMAC_CONFA1_ENS DMAC_CONFA1_ENS_Msk

// DMAC_CONFB1
#define DMAC_CONFB1_MSK_Pos (0U)
#define DMAC_CONFB1_MSK_Msk (0x1UL << DMAC_CONFB1_MSK_Pos)
#define DMAC_CONFB1_MSK DMAC_CONFB1_MSK_Msk
#define DMAC_CONFB1_STAT_Pos (16U)
#define DMAC_CONFB1_STAT_Msk (0x7UL << DMAC_CONFB1_STAT_Pos)
#define DMAC_CONFB1_STAT DMAC_CONFB1_STAT_Msk
#define DMAC_CONFB1_FISIE_Pos (19U)
#define DMAC_CONFB1_FISIE_Msk (0x1UL << DMAC_CONFB1_FISIE_Pos)
#define DMAC_CONFB1_FISIE DMAC_CONFB1_FISIE_Msk
#define DMAC_CONFB1_ERRIE_Pos (20U)
#define DMAC_CONFB1_ERRIE_Msk (0x1UL << DMAC_CONFB1_ERRIE_Pos)
#define DMAC_CONFB1_ERRIE DMAC_CONFB1_ERRIE_Msk
#define DMAC_CONFB1_RD_Pos (21U)
#define DMAC_CONFB1_RD_Msk (0x1UL << DMAC_CONFB1_RD_Pos)
#define DMAC_CONFB1_RD DMAC_CONFB1_RD_Msk
#define DMAC_CONFB1_RS_Pos (22U)
#define DMAC_CONFB1_RS_Msk (0x1UL << DMAC_CONFB1_RS_Pos)
#define DMAC_CONFB1_RS DMAC_CONFB1_RS_Msk
#define DMAC_CONFB1_RC_Pos (23U)
#define DMAC_CONFB1_RC_Msk (0x1UL << DMAC_CONFB1_RC_Pos)
#define DMAC_CONFB1_RC DMAC_CONFB1_RC_Msk
#define DMAC_CONFB1_FD_Pos (24U)
#define DMAC_CONFB1_FD_Msk (0x1UL << DMAC_CONFB1_FD_Pos)
#define DMAC_CONFB1_FD DMAC_CONFB1_FD_Msk
#define DMAC_CONFB1_FS_Pos (25U)
#define DMAC_CONFB1_FS_Msk (0x1UL << DMAC_CONFB1_FS_Pos)
#define DMAC_CONFB1_FS DMAC_CONFB1_FS_Msk
#define DMAC_CONFB1_WIDTH_Pos (26U)
#define DMAC_CONFB1_WIDTH_Msk (0x3UL << DMAC_CONFB1_WIDTH_Pos)
#define DMAC_CONFB1_WIDTH DMAC_CONFB1_WIDTH_Msk
#define DMAC_CONFB1_MODE_Pos (28U)
#define DMAC_CONFB1_MODE_Msk (0x3UL << DMAC_CONFB1_MODE_Pos)
#define DMAC_CONFB1_MODE DMAC_CONFB1_MODE_Msk

// DMAC_SRCADR1
#define DMAC_SRCADR1_SRCADR_Pos (0U)
#define DMAC_SRCADR1_SRCADR_Msk (0xFFFFFFFFUL << DMAC_SRCADR1_SRCADR_Pos)
#define DMAC_SRCADR1_SRCADR DMAC_SRCADR1_SRCADR_Msk

// DMAC_DSTADR1
#define DMAC_DSTADR1_DSTADR_Pos (0U)
#define DMAC_DSTADR1_DSTADR_Msk (0xFFFFFFFFUL << DMAC_DSTADR1_DSTADR_Pos)
#define DMAC_DSTADR1_DSTADR DMAC_DSTADR1_DSTADR_Msk

// DMAC_CONFA2
#define DMAC_CONFA2_TC_Pos (0U)
#define DMAC_CONFA2_TC_Msk (0xFFFFUL << DMAC_CONFA2_TC_Pos)
#define DMAC_CONFA2_TC DMAC_CONFA2_TC_Msk
#define DMAC_CONFA2_BC_Pos (16U)
#define DMAC_CONFA2_BC_Msk (0xFUL << DMAC_CONFA2_BC_Pos)
#define DMAC_CONFA2_BC DMAC_CONFA2_BC_Msk
#define DMAC_CONFA2_TRISEL_Pos (22U)
#define DMAC_CONFA2_TRISEL_Msk (0x7FUL << DMAC_CONFA2_TRISEL_Pos)
#define DMAC_CONFA2_TRISEL DMAC_CONFA2_TRISEL_Msk
#define DMAC_CONFA2_ST_Pos (29U)
#define DMAC_CONFA2_ST_Msk (0x1UL << DMAC_CONFA2_ST_Pos)
#define DMAC_CONFA2_ST DMAC_CONFA2_ST_Msk
#define DMAC_CONFA2_PAS_Pos (30U)
#define DMAC_CONFA2_PAS_Msk (0x1UL << DMAC_CONFA2_PAS_Pos)
#define DMAC_CONFA2_PAS DMAC_CONFA2_PAS_Msk
#define DMAC_CONFA2_ENS_Pos (31U)
#define DMAC_CONFA2_ENS_Msk (0x1UL << DMAC_CONFA2_ENS_Pos)
#define DMAC_CONFA2_ENS DMAC_CONFA2_ENS_Msk

// DMAC_CONFB2
#define DMAC_CONFB2_MSK_Pos (0U)
#define DMAC_CONFB2_MSK_Msk (0x1UL << DMAC_CONFB2_MSK_Pos)
#define DMAC_CONFB2_MSK DMAC_CONFB2_MSK_Msk
#define DMAC_CONFB2_STAT_Pos (16U)
#define DMAC_CONFB2_STAT_Msk (0x7UL << DMAC_CONFB2_STAT_Pos)
#define DMAC_CONFB2_STAT DMAC_CONFB2_STAT_Msk
#define DMAC_CONFB2_FISIE_Pos (19U)
#define DMAC_CONFB2_FISIE_Msk (0x1UL << DMAC_CONFB2_FISIE_Pos)
#define DMAC_CONFB2_FISIE DMAC_CONFB2_FISIE_Msk
#define DMAC_CONFB2_ERRIE_Pos (20U)
#define DMAC_CONFB2_ERRIE_Msk (0x1UL << DMAC_CONFB2_ERRIE_Pos)
#define DMAC_CONFB2_ERRIE DMAC_CONFB2_ERRIE_Msk
#define DMAC_CONFB2_RD_Pos (21U)
#define DMAC_CONFB2_RD_Msk (0x1UL << DMAC_CONFB2_RD_Pos)
#define DMAC_CONFB2_RD DMAC_CONFB2_RD_Msk
#define DMAC_CONFB2_RS_Pos (22U)
#define DMAC_CONFB2_RS_Msk (0x1UL << DMAC_CONFB2_RS_Pos)
#define DMAC_CONFB2_RS DMAC_CONFB2_RS_Msk
#define DMAC_CONFB2_RC_Pos (23U)
#define DMAC_CONFB2_RC_Msk (0x1UL << DMAC_CONFB2_RC_Pos)
#define DMAC_CONFB2_RC DMAC_CONFB2_RC_Msk
#define DMAC_CONFB2_FD_Pos (24U)
#define DMAC_CONFB2_FD_Msk (0x1UL << DMAC_CONFB2_FD_Pos)
#define DMAC_CONFB2_FD DMAC_CONFB2_FD_Msk
#define DMAC_CONFB2_FS_Pos (25U)
#define DMAC_CONFB2_FS_Msk (0x1UL << DMAC_CONFB2_FS_Pos)
#define DMAC_CONFB2_FS DMAC_CONFB2_FS_Msk
#define DMAC_CONFB2_WIDTH_Pos (26U)
#define DMAC_CONFB2_WIDTH_Msk (0x3UL << DMAC_CONFB2_WIDTH_Pos)
#define DMAC_CONFB2_WIDTH DMAC_CONFB2_WIDTH_Msk
#define DMAC_CONFB2_MODE_Pos (28U)
#define DMAC_CONFB2_MODE_Msk (0x3UL << DMAC_CONFB2_MODE_Pos)
#define DMAC_CONFB2_MODE DMAC_CONFB2_MODE_Msk

// DMAC_SRCADR2
#define DMAC_SRCADR2_SRCADR_Pos (0U)
#define DMAC_SRCADR2_SRCADR_Msk (0xFFFFFFFFUL << DMAC_SRCADR2_SRCADR_Pos)
#define DMAC_SRCADR2_SRCADR DMAC_SRCADR2_SRCADR_Msk

// DMAC_DSTADR2
#define DMAC_DSTADR2_DSTADR_Pos (0U)
#define DMAC_DSTADR2_DSTADR_Msk (0xFFFFFFFFUL << DMAC_DSTADR2_DSTADR_Pos)
#define DMAC_DSTADR2_DSTADR DMAC_DSTADR2_DSTADR_Msk

// DMAC_CONFA3
#define DMAC_CONFA3_TC_Pos (0U)
#define DMAC_CONFA3_TC_Msk (0xFFFFUL << DMAC_CONFA3_TC_Pos)
#define DMAC_CONFA3_TC DMAC_CONFA3_TC_Msk
#define DMAC_CONFA3_BC_Pos (16U)
#define DMAC_CONFA3_BC_Msk (0xFUL << DMAC_CONFA3_BC_Pos)
#define DMAC_CONFA3_BC DMAC_CONFA3_BC_Msk
#define DMAC_CONFA3_TRISEL_Pos (22U)
#define DMAC_CONFA3_TRISEL_Msk (0x7FUL << DMAC_CONFA3_TRISEL_Pos)
#define DMAC_CONFA3_TRISEL DMAC_CONFA3_TRISEL_Msk
#define DMAC_CONFA3_ST_Pos (29U)
#define DMAC_CONFA3_ST_Msk (0x1UL << DMAC_CONFA3_ST_Pos)
#define DMAC_CONFA3_ST DMAC_CONFA3_ST_Msk
#define DMAC_CONFA3_PAS_Pos (30U)
#define DMAC_CONFA3_PAS_Msk (0x1UL << DMAC_CONFA3_PAS_Pos)
#define DMAC_CONFA3_PAS DMAC_CONFA3_PAS_Msk
#define DMAC_CONFA3_ENS_Pos (31U)
#define DMAC_CONFA3_ENS_Msk (0x1UL << DMAC_CONFA3_ENS_Pos)
#define DMAC_CONFA3_ENS DMAC_CONFA3_ENS_Msk

// DMAC_CONFB3
#define DMAC_CONFB3_MSK_Pos (0U)
#define DMAC_CONFB3_MSK_Msk (0x1UL << DMAC_CONFB3_MSK_Pos)
#define DMAC_CONFB3_MSK DMAC_CONFB3_MSK_Msk
#define DMAC_CONFB3_STAT_Pos (16U)
#define DMAC_CONFB3_STAT_Msk (0x7UL << DMAC_CONFB3_STAT_Pos)
#define DMAC_CONFB3_STAT DMAC_CONFB3_STAT_Msk
#define DMAC_CONFB3_FISIE_Pos (19U)
#define DMAC_CONFB3_FISIE_Msk (0x1UL << DMAC_CONFB3_FISIE_Pos)
#define DMAC_CONFB3_FISIE DMAC_CONFB3_FISIE_Msk
#define DMAC_CONFB3_ERRIE_Pos (20U)
#define DMAC_CONFB3_ERRIE_Msk (0x1UL << DMAC_CONFB3_ERRIE_Pos)
#define DMAC_CONFB3_ERRIE DMAC_CONFB3_ERRIE_Msk
#define DMAC_CONFB3_RD_Pos (21U)
#define DMAC_CONFB3_RD_Msk (0x1UL << DMAC_CONFB3_RD_Pos)
#define DMAC_CONFB3_RD DMAC_CONFB3_RD_Msk
#define DMAC_CONFB3_RS_Pos (22U)
#define DMAC_CONFB3_RS_Msk (0x1UL << DMAC_CONFB3_RS_Pos)
#define DMAC_CONFB3_RS DMAC_CONFB3_RS_Msk
#define DMAC_CONFB3_RC_Pos (23U)
#define DMAC_CONFB3_RC_Msk (0x1UL << DMAC_CONFB3_RC_Pos)
#define DMAC_CONFB3_RC DMAC_CONFB3_RC_Msk
#define DMAC_CONFB3_FD_Pos (24U)
#define DMAC_CONFB3_FD_Msk (0x1UL << DMAC_CONFB3_FD_Pos)
#define DMAC_CONFB3_FD DMAC_CONFB3_FD_Msk
#define DMAC_CONFB3_FS_Pos (25U)
#define DMAC_CONFB3_FS_Msk (0x1UL << DMAC_CONFB3_FS_Pos)
#define DMAC_CONFB3_FS DMAC_CONFB3_FS_Msk
#define DMAC_CONFB3_WIDTH_Pos (26U)
#define DMAC_CONFB3_WIDTH_Msk (0x3UL << DMAC_CONFB3_WIDTH_Pos)
#define DMAC_CONFB3_WIDTH DMAC_CONFB3_WIDTH_Msk
#define DMAC_CONFB3_MODE_Pos (28U)
#define DMAC_CONFB3_MODE_Msk (0x3UL << DMAC_CONFB3_MODE_Pos)
#define DMAC_CONFB3_MODE DMAC_CONFB3_MODE_Msk

// DMAC_SRCADR3
#define DMAC_SRCADR3_SRCADR_Pos (0U)
#define DMAC_SRCADR3_SRCADR_Msk (0xFFFFFFFFUL << DMAC_SRCADR3_SRCADR_Pos)
#define DMAC_SRCADR3_SRCADR DMAC_SRCADR3_SRCADR_Msk

// DMAC_DSTADR3
#define DMAC_DSTADR3_DSTADR_Pos (0U)
#define DMAC_DSTADR3_DSTADR_Msk (0xFFFFFFFFUL << DMAC_DSTADR3_DSTADR_Pos)
#define DMAC_DSTADR3_DSTADR DMAC_DSTADR3_DSTADR_Msk

// DMAC_CONFA4
#define DMAC_CONFA4_TC_Pos (0U)
#define DMAC_CONFA4_TC_Msk (0xFFFFUL << DMAC_CONFA4_TC_Pos)
#define DMAC_CONFA4_TC DMAC_CONFA4_TC_Msk
#define DMAC_CONFA4_BC_Pos (16U)
#define DMAC_CONFA4_BC_Msk (0xFUL << DMAC_CONFA4_BC_Pos)
#define DMAC_CONFA4_BC DMAC_CONFA4_BC_Msk
#define DMAC_CONFA4_TRISEL_Pos (22U)
#define DMAC_CONFA4_TRISEL_Msk (0x7FUL << DMAC_CONFA4_TRISEL_Pos)
#define DMAC_CONFA4_TRISEL DMAC_CONFA4_TRISEL_Msk
#define DMAC_CONFA4_ST_Pos (29U)
#define DMAC_CONFA4_ST_Msk (0x1UL << DMAC_CONFA4_ST_Pos)
#define DMAC_CONFA4_ST DMAC_CONFA4_ST_Msk
#define DMAC_CONFA4_PAS_Pos (30U)
#define DMAC_CONFA4_PAS_Msk (0x1UL << DMAC_CONFA4_PAS_Pos)
#define DMAC_CONFA4_PAS DMAC_CONFA4_PAS_Msk
#define DMAC_CONFA4_ENS_Pos (31U)
#define DMAC_CONFA4_ENS_Msk (0x1UL << DMAC_CONFA4_ENS_Pos)
#define DMAC_CONFA4_ENS DMAC_CONFA4_ENS_Msk

// DMAC_CONFB4
#define DMAC_CONFB4_MSK_Pos (0U)
#define DMAC_CONFB4_MSK_Msk (0x1UL << DMAC_CONFB4_MSK_Pos)
#define DMAC_CONFB4_MSK DMAC_CONFB4_MSK_Msk
#define DMAC_CONFB4_STAT_Pos (16U)
#define DMAC_CONFB4_STAT_Msk (0x7UL << DMAC_CONFB4_STAT_Pos)
#define DMAC_CONFB4_STAT DMAC_CONFB4_STAT_Msk
#define DMAC_CONFB4_FISIE_Pos (19U)
#define DMAC_CONFB4_FISIE_Msk (0x1UL << DMAC_CONFB4_FISIE_Pos)
#define DMAC_CONFB4_FISIE DMAC_CONFB4_FISIE_Msk
#define DMAC_CONFB4_ERRIE_Pos (20U)
#define DMAC_CONFB4_ERRIE_Msk (0x1UL << DMAC_CONFB4_ERRIE_Pos)
#define DMAC_CONFB4_ERRIE DMAC_CONFB4_ERRIE_Msk
#define DMAC_CONFB4_RD_Pos (21U)
#define DMAC_CONFB4_RD_Msk (0x1UL << DMAC_CONFB4_RD_Pos)
#define DMAC_CONFB4_RD DMAC_CONFB4_RD_Msk
#define DMAC_CONFB4_RS_Pos (22U)
#define DMAC_CONFB4_RS_Msk (0x1UL << DMAC_CONFB4_RS_Pos)
#define DMAC_CONFB4_RS DMAC_CONFB4_RS_Msk
#define DMAC_CONFB4_RC_Pos (23U)
#define DMAC_CONFB4_RC_Msk (0x1UL << DMAC_CONFB4_RC_Pos)
#define DMAC_CONFB4_RC DMAC_CONFB4_RC_Msk
#define DMAC_CONFB4_FD_Pos (24U)
#define DMAC_CONFB4_FD_Msk (0x1UL << DMAC_CONFB4_FD_Pos)
#define DMAC_CONFB4_FD DMAC_CONFB4_FD_Msk
#define DMAC_CONFB4_FS_Pos (25U)
#define DMAC_CONFB4_FS_Msk (0x1UL << DMAC_CONFB4_FS_Pos)
#define DMAC_CONFB4_FS DMAC_CONFB4_FS_Msk
#define DMAC_CONFB4_WIDTH_Pos (26U)
#define DMAC_CONFB4_WIDTH_Msk (0x3UL << DMAC_CONFB4_WIDTH_Pos)
#define DMAC_CONFB4_WIDTH DMAC_CONFB4_WIDTH_Msk
#define DMAC_CONFB4_MODE_Pos (28U)
#define DMAC_CONFB4_MODE_Msk (0x3UL << DMAC_CONFB4_MODE_Pos)
#define DMAC_CONFB4_MODE DMAC_CONFB4_MODE_Msk

// DMAC_SRCADR4
#define DMAC_SRCADR4_SRCADR_Pos (0U)
#define DMAC_SRCADR4_SRCADR_Msk (0xFFFFFFFFUL << DMAC_SRCADR4_SRCADR_Pos)
#define DMAC_SRCADR4_SRCADR DMAC_SRCADR4_SRCADR_Msk

// DMAC_DSTADR4
#define DMAC_DSTADR4_DSTADR_Pos (0U)
#define DMAC_DSTADR4_DSTADR_Msk (0xFFFFFFFFUL << DMAC_DSTADR4_DSTADR_Pos)
#define DMAC_DSTADR4_DSTADR DMAC_DSTADR4_DSTADR_Msk

// DMAC_CONFA5
#define DMAC_CONFA5_TC_Pos (0U)
#define DMAC_CONFA5_TC_Msk (0xFFFFUL << DMAC_CONFA5_TC_Pos)
#define DMAC_CONFA5_TC DMAC_CONFA5_TC_Msk
#define DMAC_CONFA5_BC_Pos (16U)
#define DMAC_CONFA5_BC_Msk (0xFUL << DMAC_CONFA5_BC_Pos)
#define DMAC_CONFA5_BC DMAC_CONFA5_BC_Msk
#define DMAC_CONFA5_TRISEL_Pos (22U)
#define DMAC_CONFA5_TRISEL_Msk (0x7FUL << DMAC_CONFA5_TRISEL_Pos)
#define DMAC_CONFA5_TRISEL DMAC_CONFA5_TRISEL_Msk
#define DMAC_CONFA5_ST_Pos (29U)
#define DMAC_CONFA5_ST_Msk (0x1UL << DMAC_CONFA5_ST_Pos)
#define DMAC_CONFA5_ST DMAC_CONFA5_ST_Msk
#define DMAC_CONFA5_PAS_Pos (30U)
#define DMAC_CONFA5_PAS_Msk (0x1UL << DMAC_CONFA5_PAS_Pos)
#define DMAC_CONFA5_PAS DMAC_CONFA5_PAS_Msk
#define DMAC_CONFA5_ENS_Pos (31U)
#define DMAC_CONFA5_ENS_Msk (0x1UL << DMAC_CONFA5_ENS_Pos)
#define DMAC_CONFA5_ENS DMAC_CONFA5_ENS_Msk

// DMAC_CONFB5
#define DMAC_CONFB5_MSK_Pos (0U)
#define DMAC_CONFB5_MSK_Msk (0x1UL << DMAC_CONFB5_MSK_Pos)
#define DMAC_CONFB5_MSK DMAC_CONFB5_MSK_Msk
#define DMAC_CONFB5_STAT_Pos (16U)
#define DMAC_CONFB5_STAT_Msk (0x7UL << DMAC_CONFB5_STAT_Pos)
#define DMAC_CONFB5_STAT DMAC_CONFB5_STAT_Msk
#define DMAC_CONFB5_FISIE_Pos (19U)
#define DMAC_CONFB5_FISIE_Msk (0x1UL << DMAC_CONFB5_FISIE_Pos)
#define DMAC_CONFB5_FISIE DMAC_CONFB5_FISIE_Msk
#define DMAC_CONFB5_ERRIE_Pos (20U)
#define DMAC_CONFB5_ERRIE_Msk (0x1UL << DMAC_CONFB5_ERRIE_Pos)
#define DMAC_CONFB5_ERRIE DMAC_CONFB5_ERRIE_Msk
#define DMAC_CONFB5_RD_Pos (21U)
#define DMAC_CONFB5_RD_Msk (0x1UL << DMAC_CONFB5_RD_Pos)
#define DMAC_CONFB5_RD DMAC_CONFB5_RD_Msk
#define DMAC_CONFB5_RS_Pos (22U)
#define DMAC_CONFB5_RS_Msk (0x1UL << DMAC_CONFB5_RS_Pos)
#define DMAC_CONFB5_RS DMAC_CONFB5_RS_Msk
#define DMAC_CONFB5_RC_Pos (23U)
#define DMAC_CONFB5_RC_Msk (0x1UL << DMAC_CONFB5_RC_Pos)
#define DMAC_CONFB5_RC DMAC_CONFB5_RC_Msk
#define DMAC_CONFB5_FD_Pos (24U)
#define DMAC_CONFB5_FD_Msk (0x1UL << DMAC_CONFB5_FD_Pos)
#define DMAC_CONFB5_FD DMAC_CONFB5_FD_Msk
#define DMAC_CONFB5_FS_Pos (25U)
#define DMAC_CONFB5_FS_Msk (0x1UL << DMAC_CONFB5_FS_Pos)
#define DMAC_CONFB5_FS DMAC_CONFB5_FS_Msk
#define DMAC_CONFB5_WIDTH_Pos (26U)
#define DMAC_CONFB5_WIDTH_Msk (0x3UL << DMAC_CONFB5_WIDTH_Pos)
#define DMAC_CONFB5_WIDTH DMAC_CONFB5_WIDTH_Msk
#define DMAC_CONFB5_MODE_Pos (28U)
#define DMAC_CONFB5_MODE_Msk (0x3UL << DMAC_CONFB5_MODE_Pos)
#define DMAC_CONFB5_MODE DMAC_CONFB5_MODE_Msk

// DMAC_SRCADR5
#define DMAC_SRCADR5_SRCADR_Pos (0U)
#define DMAC_SRCADR5_SRCADR_Msk (0xFFFFFFFFUL << DMAC_SRCADR5_SRCADR_Pos)
#define DMAC_SRCADR5_SRCADR DMAC_SRCADR5_SRCADR_Msk

// DMAC_DSTADR5
#define DMAC_DSTADR5_DSTADR_Pos (0U)
#define DMAC_DSTADR5_DSTADR_Msk (0xFFFFFFFFUL << DMAC_DSTADR5_DSTADR_Pos)
#define DMAC_DSTADR5_DSTADR DMAC_DSTADR5_DSTADR_Msk

//********************    Bits Define For Peripheral EAU    ********************//
// EAU_CSR
#define EAU_CSR_MODE_Pos (0U)
#define EAU_CSR_MODE_Msk (0x3UL << EAU_CSR_MODE_Pos)
#define EAU_CSR_MODE EAU_CSR_MODE_Msk
#define EAU_CSR_OVR_Pos (2U)
#define EAU_CSR_OVR_Msk (0x1UL << EAU_CSR_OVR_Pos)
#define EAU_CSR_OVR EAU_CSR_OVR_Msk
#define EAU_CSR_ZERO_Pos (3U)
#define EAU_CSR_ZERO_Msk (0x1UL << EAU_CSR_ZERO_Pos)
#define EAU_CSR_ZERO EAU_CSR_ZERO_Msk
#define EAU_CSR_BUSY_Pos (4U)
#define EAU_CSR_BUSY_Msk (0x1UL << EAU_CSR_BUSY_Pos)
#define EAU_CSR_BUSY EAU_CSR_BUSY_Msk

// EAU_DIVIDEND
#define EAU_DIVIDEND_DIVIDEND_Pos (0U)
#define EAU_DIVIDEND_DIVIDEND_Msk (0xFFFFFFFFUL << EAU_DIVIDEND_DIVIDEND_Pos)
#define EAU_DIVIDEND_DIVIDEND EAU_DIVIDEND_DIVIDEND_Msk

// EAU_DIVISOR
#define EAU_DIVISOR_DIVISOR_Pos (0U)
#define EAU_DIVISOR_DIVISOR_Msk (0xFFFFFFFFUL << EAU_DIVISOR_DIVISOR_Pos)
#define EAU_DIVISOR_DIVISOR EAU_DIVISOR_DIVISOR_Msk

// EAU_QUOTIENT
#define EAU_QUOTIENT_QUOTIENT_Pos (0U)
#define EAU_QUOTIENT_QUOTIENT_Msk (0xFFFFFFFFUL << EAU_QUOTIENT_QUOTIENT_Pos)
#define EAU_QUOTIENT_QUOTIENT EAU_QUOTIENT_QUOTIENT_Msk

// EAU_REMAINDER
#define EAU_REMAINDER_REMAINDER_Pos (0U)
#define EAU_REMAINDER_REMAINDER_Msk (0xFFFFFFFFUL << EAU_REMAINDER_REMAINDER_Pos)
#define EAU_REMAINDER_REMAINDER EAU_REMAINDER_REMAINDER_Msk

//********************    Bits Define For Peripheral FLASH    ********************//
// FLASH_CR
#define FLASH_CR_OP_Pos (0U)
#define FLASH_CR_OP_Msk (0x7UL << FLASH_CR_OP_Pos)
#define FLASH_CR_OP FLASH_CR_OP_Msk
#define FLASH_CR_FWUP_Pos (4U)
#define FLASH_CR_FWUP_Msk (0x1UL << FLASH_CR_FWUP_Pos)
#define FLASH_CR_FWUP FLASH_CR_FWUP_Msk
#define FLASH_CR_ROMD_Pos (5U)
#define FLASH_CR_ROMD_Msk (0x1UL << FLASH_CR_ROMD_Pos)
#define FLASH_CR_ROMD FLASH_CR_ROMD_Msk
#define FLASH_CR_DPSTBEN_Pos (7U)
#define FLASH_CR_DPSTBEN_Msk (0x1UL << FLASH_CR_DPSTBEN_Pos)
#define FLASH_CR_DPSTBEN FLASH_CR_DPSTBEN_Msk

// FLASH_WAIT
#define FLASH_WAIT_WAIT_Pos (0U)
#define FLASH_WAIT_WAIT_Msk (0x7UL << FLASH_WAIT_WAIT_Pos)
#define FLASH_WAIT_WAIT FLASH_WAIT_WAIT_Msk

// FLASH_LOCKST
#define FLASH_LOCKST_STATE_Pos (0U)
#define FLASH_LOCKST_STATE_Msk (0x3UL << FLASH_LOCKST_STATE_Pos)
#define FLASH_LOCKST_STATE FLASH_LOCKST_STATE_Msk

// FLASH_IER
#define FLASH_IER_PC_Pos (0U)
#define FLASH_IER_PC_Msk (0x1UL << FLASH_IER_PC_Pos)
#define FLASH_IER_PC FLASH_IER_PC_Msk
#define FLASH_IER_PROT_Pos (1U)
#define FLASH_IER_PROT_Msk (0x1UL << FLASH_IER_PROT_Pos)
#define FLASH_IER_PROT FLASH_IER_PROT_Msk

// FLASH_IFR
#define FLASH_IFR_PC_Pos (0U)
#define FLASH_IFR_PC_Msk (0x1UL << FLASH_IFR_PC_Pos)
#define FLASH_IFR_PC FLASH_IFR_PC_Msk
#define FLASH_IFR_PROT_Pos (1U)
#define FLASH_IFR_PROT_Msk (0x1UL << FLASH_IFR_PROT_Pos)
#define FLASH_IFR_PROT FLASH_IFR_PROT_Msk
#define FLASH_IFR_BUSY_Pos (4U)
#define FLASH_IFR_BUSY_Msk (0x1UL << FLASH_IFR_BUSY_Pos)
#define FLASH_IFR_BUSY FLASH_IFR_BUSY_Msk
#define FLASH_IFR_CFDONE_Pos (5U)
#define FLASH_IFR_CFDONE_Msk (0x1UL << FLASH_IFR_CFDONE_Pos)
#define FLASH_IFR_CFDONE FLASH_IFR_CFDONE_Msk

// FLASH_ICR
#define FLASH_ICR_PC_Pos (0U)
#define FLASH_ICR_PC_Msk (0x1UL << FLASH_ICR_PC_Pos)
#define FLASH_ICR_PC FLASH_ICR_PC_Msk
#define FLASH_ICR_PROT_Pos (1U)
#define FLASH_ICR_PROT_Msk (0x1UL << FLASH_ICR_PROT_Pos)
#define FLASH_ICR_PROT FLASH_ICR_PROT_Msk

// FLASH_BYPASS
#define FLASH_BYPASS_BYSEQ_Pos (0U)
#define FLASH_BYPASS_BYSEQ_Msk (0xFFFFUL << FLASH_BYPASS_BYSEQ_Pos)
#define FLASH_BYPASS_BYSEQ FLASH_BYPASS_BYSEQ_Msk

// FLASH_SLOCK0
#define FLASH_SLOCK0_SLOCK_Pos (0U)
#define FLASH_SLOCK0_SLOCK_Msk (0xFFFFFFFFUL << FLASH_SLOCK0_SLOCK_Pos)
#define FLASH_SLOCK0_SLOCK FLASH_SLOCK0_SLOCK_Msk

// FLASH_SLOCK1
#define FLASH_SLOCK1_SLOCK_Pos (0U)
#define FLASH_SLOCK1_SLOCK_Msk (0xFFFFFFFFUL << FLASH_SLOCK1_SLOCK_Pos)
#define FLASH_SLOCK1_SLOCK FLASH_SLOCK1_SLOCK_Msk

//********************    Bits Define For Peripheral GPIO    ********************//
// GPIO_ADS
#define GPIO_ADS_PIN0_Pos (0U)
#define GPIO_ADS_PIN0_Msk (0x1UL << GPIO_ADS_PIN0_Pos)
#define GPIO_ADS_PIN0 GPIO_ADS_PIN0_Msk
#define GPIO_ADS_PIN1_Pos (1U)
#define GPIO_ADS_PIN1_Msk (0x1UL << GPIO_ADS_PIN1_Pos)
#define GPIO_ADS_PIN1 GPIO_ADS_PIN1_Msk
#define GPIO_ADS_PIN2_Pos (2U)
#define GPIO_ADS_PIN2_Msk (0x1UL << GPIO_ADS_PIN2_Pos)
#define GPIO_ADS_PIN2 GPIO_ADS_PIN2_Msk
#define GPIO_ADS_PIN3_Pos (3U)
#define GPIO_ADS_PIN3_Msk (0x1UL << GPIO_ADS_PIN3_Pos)
#define GPIO_ADS_PIN3 GPIO_ADS_PIN3_Msk
#define GPIO_ADS_PIN4_Pos (4U)
#define GPIO_ADS_PIN4_Msk (0x1UL << GPIO_ADS_PIN4_Pos)
#define GPIO_ADS_PIN4 GPIO_ADS_PIN4_Msk
#define GPIO_ADS_PIN5_Pos (5U)
#define GPIO_ADS_PIN5_Msk (0x1UL << GPIO_ADS_PIN5_Pos)
#define GPIO_ADS_PIN5 GPIO_ADS_PIN5_Msk
#define GPIO_ADS_PIN6_Pos (6U)
#define GPIO_ADS_PIN6_Msk (0x1UL << GPIO_ADS_PIN6_Pos)
#define GPIO_ADS_PIN6 GPIO_ADS_PIN6_Msk
#define GPIO_ADS_PIN7_Pos (7U)
#define GPIO_ADS_PIN7_Msk (0x1UL << GPIO_ADS_PIN7_Pos)
#define GPIO_ADS_PIN7 GPIO_ADS_PIN7_Msk
#define GPIO_ADS_PIN8_Pos (8U)
#define GPIO_ADS_PIN8_Msk (0x1UL << GPIO_ADS_PIN8_Pos)
#define GPIO_ADS_PIN8 GPIO_ADS_PIN8_Msk
#define GPIO_ADS_PIN9_Pos (9U)
#define GPIO_ADS_PIN9_Msk (0x1UL << GPIO_ADS_PIN9_Pos)
#define GPIO_ADS_PIN9 GPIO_ADS_PIN9_Msk
#define GPIO_ADS_PIN10_Pos (10U)
#define GPIO_ADS_PIN10_Msk (0x1UL << GPIO_ADS_PIN10_Pos)
#define GPIO_ADS_PIN10 GPIO_ADS_PIN10_Msk
#define GPIO_ADS_PIN11_Pos (11U)
#define GPIO_ADS_PIN11_Msk (0x1UL << GPIO_ADS_PIN11_Pos)
#define GPIO_ADS_PIN11 GPIO_ADS_PIN11_Msk
#define GPIO_ADS_PIN12_Pos (12U)
#define GPIO_ADS_PIN12_Msk (0x1UL << GPIO_ADS_PIN12_Pos)
#define GPIO_ADS_PIN12 GPIO_ADS_PIN12_Msk
#define GPIO_ADS_PIN13_Pos (13U)
#define GPIO_ADS_PIN13_Msk (0x1UL << GPIO_ADS_PIN13_Pos)
#define GPIO_ADS_PIN13 GPIO_ADS_PIN13_Msk
#define GPIO_ADS_PIN14_Pos (14U)
#define GPIO_ADS_PIN14_Msk (0x1UL << GPIO_ADS_PIN14_Pos)
#define GPIO_ADS_PIN14 GPIO_ADS_PIN14_Msk
#define GPIO_ADS_PIN15_Pos (15U)
#define GPIO_ADS_PIN15_Msk (0x1UL << GPIO_ADS_PIN15_Pos)
#define GPIO_ADS_PIN15 GPIO_ADS_PIN15_Msk

// GPIO_DIR
#define GPIO_DIR_PIN0_Pos (0U)
#define GPIO_DIR_PIN0_Msk (0x1UL << GPIO_DIR_PIN0_Pos)
#define GPIO_DIR_PIN0 GPIO_DIR_PIN0_Msk
#define GPIO_DIR_PIN1_Pos (1U)
#define GPIO_DIR_PIN1_Msk (0x1UL << GPIO_DIR_PIN1_Pos)
#define GPIO_DIR_PIN1 GPIO_DIR_PIN1_Msk
#define GPIO_DIR_PIN2_Pos (2U)
#define GPIO_DIR_PIN2_Msk (0x1UL << GPIO_DIR_PIN2_Pos)
#define GPIO_DIR_PIN2 GPIO_DIR_PIN2_Msk
#define GPIO_DIR_PIN3_Pos (3U)
#define GPIO_DIR_PIN3_Msk (0x1UL << GPIO_DIR_PIN3_Pos)
#define GPIO_DIR_PIN3 GPIO_DIR_PIN3_Msk
#define GPIO_DIR_PIN4_Pos (4U)
#define GPIO_DIR_PIN4_Msk (0x1UL << GPIO_DIR_PIN4_Pos)
#define GPIO_DIR_PIN4 GPIO_DIR_PIN4_Msk
#define GPIO_DIR_PIN5_Pos (5U)
#define GPIO_DIR_PIN5_Msk (0x1UL << GPIO_DIR_PIN5_Pos)
#define GPIO_DIR_PIN5 GPIO_DIR_PIN5_Msk
#define GPIO_DIR_PIN6_Pos (6U)
#define GPIO_DIR_PIN6_Msk (0x1UL << GPIO_DIR_PIN6_Pos)
#define GPIO_DIR_PIN6 GPIO_DIR_PIN6_Msk
#define GPIO_DIR_PIN7_Pos (7U)
#define GPIO_DIR_PIN7_Msk (0x1UL << GPIO_DIR_PIN7_Pos)
#define GPIO_DIR_PIN7 GPIO_DIR_PIN7_Msk
#define GPIO_DIR_PIN8_Pos (8U)
#define GPIO_DIR_PIN8_Msk (0x1UL << GPIO_DIR_PIN8_Pos)
#define GPIO_DIR_PIN8 GPIO_DIR_PIN8_Msk
#define GPIO_DIR_PIN9_Pos (9U)
#define GPIO_DIR_PIN9_Msk (0x1UL << GPIO_DIR_PIN9_Pos)
#define GPIO_DIR_PIN9 GPIO_DIR_PIN9_Msk
#define GPIO_DIR_PIN10_Pos (10U)
#define GPIO_DIR_PIN10_Msk (0x1UL << GPIO_DIR_PIN10_Pos)
#define GPIO_DIR_PIN10 GPIO_DIR_PIN10_Msk
#define GPIO_DIR_PIN11_Pos (11U)
#define GPIO_DIR_PIN11_Msk (0x1UL << GPIO_DIR_PIN11_Pos)
#define GPIO_DIR_PIN11 GPIO_DIR_PIN11_Msk
#define GPIO_DIR_PIN12_Pos (12U)
#define GPIO_DIR_PIN12_Msk (0x1UL << GPIO_DIR_PIN12_Pos)
#define GPIO_DIR_PIN12 GPIO_DIR_PIN12_Msk
#define GPIO_DIR_PIN13_Pos (13U)
#define GPIO_DIR_PIN13_Msk (0x1UL << GPIO_DIR_PIN13_Pos)
#define GPIO_DIR_PIN13 GPIO_DIR_PIN13_Msk
#define GPIO_DIR_PIN14_Pos (14U)
#define GPIO_DIR_PIN14_Msk (0x1UL << GPIO_DIR_PIN14_Pos)
#define GPIO_DIR_PIN14 GPIO_DIR_PIN14_Msk
#define GPIO_DIR_PIN15_Pos (15U)
#define GPIO_DIR_PIN15_Msk (0x1UL << GPIO_DIR_PIN15_Pos)
#define GPIO_DIR_PIN15 GPIO_DIR_PIN15_Msk

// GPIO_OPENDRAIN
#define GPIO_OPENDRAIN_PIN0_Pos (0U)
#define GPIO_OPENDRAIN_PIN0_Msk (0x1UL << GPIO_OPENDRAIN_PIN0_Pos)
#define GPIO_OPENDRAIN_PIN0 GPIO_OPENDRAIN_PIN0_Msk
#define GPIO_OPENDRAIN_PIN1_Pos (1U)
#define GPIO_OPENDRAIN_PIN1_Msk (0x1UL << GPIO_OPENDRAIN_PIN1_Pos)
#define GPIO_OPENDRAIN_PIN1 GPIO_OPENDRAIN_PIN1_Msk
#define GPIO_OPENDRAIN_PIN2_Pos (2U)
#define GPIO_OPENDRAIN_PIN2_Msk (0x1UL << GPIO_OPENDRAIN_PIN2_Pos)
#define GPIO_OPENDRAIN_PIN2 GPIO_OPENDRAIN_PIN2_Msk
#define GPIO_OPENDRAIN_PIN3_Pos (3U)
#define GPIO_OPENDRAIN_PIN3_Msk (0x1UL << GPIO_OPENDRAIN_PIN3_Pos)
#define GPIO_OPENDRAIN_PIN3 GPIO_OPENDRAIN_PIN3_Msk
#define GPIO_OPENDRAIN_PIN4_Pos (4U)
#define GPIO_OPENDRAIN_PIN4_Msk (0x1UL << GPIO_OPENDRAIN_PIN4_Pos)
#define GPIO_OPENDRAIN_PIN4 GPIO_OPENDRAIN_PIN4_Msk
#define GPIO_OPENDRAIN_PIN5_Pos (5U)
#define GPIO_OPENDRAIN_PIN5_Msk (0x1UL << GPIO_OPENDRAIN_PIN5_Pos)
#define GPIO_OPENDRAIN_PIN5 GPIO_OPENDRAIN_PIN5_Msk
#define GPIO_OPENDRAIN_PIN6_Pos (6U)
#define GPIO_OPENDRAIN_PIN6_Msk (0x1UL << GPIO_OPENDRAIN_PIN6_Pos)
#define GPIO_OPENDRAIN_PIN6 GPIO_OPENDRAIN_PIN6_Msk
#define GPIO_OPENDRAIN_PIN7_Pos (7U)
#define GPIO_OPENDRAIN_PIN7_Msk (0x1UL << GPIO_OPENDRAIN_PIN7_Pos)
#define GPIO_OPENDRAIN_PIN7 GPIO_OPENDRAIN_PIN7_Msk
#define GPIO_OPENDRAIN_PIN8_Pos (8U)
#define GPIO_OPENDRAIN_PIN8_Msk (0x1UL << GPIO_OPENDRAIN_PIN8_Pos)
#define GPIO_OPENDRAIN_PIN8 GPIO_OPENDRAIN_PIN8_Msk
#define GPIO_OPENDRAIN_PIN9_Pos (9U)
#define GPIO_OPENDRAIN_PIN9_Msk (0x1UL << GPIO_OPENDRAIN_PIN9_Pos)
#define GPIO_OPENDRAIN_PIN9 GPIO_OPENDRAIN_PIN9_Msk
#define GPIO_OPENDRAIN_PIN10_Pos (10U)
#define GPIO_OPENDRAIN_PIN10_Msk (0x1UL << GPIO_OPENDRAIN_PIN10_Pos)
#define GPIO_OPENDRAIN_PIN10 GPIO_OPENDRAIN_PIN10_Msk
#define GPIO_OPENDRAIN_PIN11_Pos (11U)
#define GPIO_OPENDRAIN_PIN11_Msk (0x1UL << GPIO_OPENDRAIN_PIN11_Pos)
#define GPIO_OPENDRAIN_PIN11 GPIO_OPENDRAIN_PIN11_Msk
#define GPIO_OPENDRAIN_PIN12_Pos (12U)
#define GPIO_OPENDRAIN_PIN12_Msk (0x1UL << GPIO_OPENDRAIN_PIN12_Pos)
#define GPIO_OPENDRAIN_PIN12 GPIO_OPENDRAIN_PIN12_Msk
#define GPIO_OPENDRAIN_PIN13_Pos (13U)
#define GPIO_OPENDRAIN_PIN13_Msk (0x1UL << GPIO_OPENDRAIN_PIN13_Pos)
#define GPIO_OPENDRAIN_PIN13 GPIO_OPENDRAIN_PIN13_Msk
#define GPIO_OPENDRAIN_PIN14_Pos (14U)
#define GPIO_OPENDRAIN_PIN14_Msk (0x1UL << GPIO_OPENDRAIN_PIN14_Pos)
#define GPIO_OPENDRAIN_PIN14 GPIO_OPENDRAIN_PIN14_Msk
#define GPIO_OPENDRAIN_PIN15_Pos (15U)
#define GPIO_OPENDRAIN_PIN15_Msk (0x1UL << GPIO_OPENDRAIN_PIN15_Pos)
#define GPIO_OPENDRAIN_PIN15 GPIO_OPENDRAIN_PIN15_Msk

// GPIO_DRIVER
#define GPIO_DRIVER_PIN0_Pos (0U)
#define GPIO_DRIVER_PIN0_Msk (0x1UL << GPIO_DRIVER_PIN0_Pos)
#define GPIO_DRIVER_PIN0 GPIO_DRIVER_PIN0_Msk
#define GPIO_DRIVER_PIN1_Pos (1U)
#define GPIO_DRIVER_PIN1_Msk (0x1UL << GPIO_DRIVER_PIN1_Pos)
#define GPIO_DRIVER_PIN1 GPIO_DRIVER_PIN1_Msk
#define GPIO_DRIVER_PIN2_Pos (2U)
#define GPIO_DRIVER_PIN2_Msk (0x1UL << GPIO_DRIVER_PIN2_Pos)
#define GPIO_DRIVER_PIN2 GPIO_DRIVER_PIN2_Msk
#define GPIO_DRIVER_PIN3_Pos (3U)
#define GPIO_DRIVER_PIN3_Msk (0x1UL << GPIO_DRIVER_PIN3_Pos)
#define GPIO_DRIVER_PIN3 GPIO_DRIVER_PIN3_Msk
#define GPIO_DRIVER_PIN4_Pos (4U)
#define GPIO_DRIVER_PIN4_Msk (0x1UL << GPIO_DRIVER_PIN4_Pos)
#define GPIO_DRIVER_PIN4 GPIO_DRIVER_PIN4_Msk
#define GPIO_DRIVER_PIN5_Pos (5U)
#define GPIO_DRIVER_PIN5_Msk (0x1UL << GPIO_DRIVER_PIN5_Pos)
#define GPIO_DRIVER_PIN5 GPIO_DRIVER_PIN5_Msk
#define GPIO_DRIVER_PIN6_Pos (6U)
#define GPIO_DRIVER_PIN6_Msk (0x1UL << GPIO_DRIVER_PIN6_Pos)
#define GPIO_DRIVER_PIN6 GPIO_DRIVER_PIN6_Msk
#define GPIO_DRIVER_PIN7_Pos (7U)
#define GPIO_DRIVER_PIN7_Msk (0x1UL << GPIO_DRIVER_PIN7_Pos)
#define GPIO_DRIVER_PIN7 GPIO_DRIVER_PIN7_Msk
#define GPIO_DRIVER_PIN8_Pos (8U)
#define GPIO_DRIVER_PIN8_Msk (0x1UL << GPIO_DRIVER_PIN8_Pos)
#define GPIO_DRIVER_PIN8 GPIO_DRIVER_PIN8_Msk
#define GPIO_DRIVER_PIN9_Pos (9U)
#define GPIO_DRIVER_PIN9_Msk (0x1UL << GPIO_DRIVER_PIN9_Pos)
#define GPIO_DRIVER_PIN9 GPIO_DRIVER_PIN9_Msk
#define GPIO_DRIVER_PIN10_Pos (10U)
#define GPIO_DRIVER_PIN10_Msk (0x1UL << GPIO_DRIVER_PIN10_Pos)
#define GPIO_DRIVER_PIN10 GPIO_DRIVER_PIN10_Msk
#define GPIO_DRIVER_PIN11_Pos (11U)
#define GPIO_DRIVER_PIN11_Msk (0x1UL << GPIO_DRIVER_PIN11_Pos)
#define GPIO_DRIVER_PIN11 GPIO_DRIVER_PIN11_Msk
#define GPIO_DRIVER_PIN12_Pos (12U)
#define GPIO_DRIVER_PIN12_Msk (0x1UL << GPIO_DRIVER_PIN12_Pos)
#define GPIO_DRIVER_PIN12 GPIO_DRIVER_PIN12_Msk
#define GPIO_DRIVER_PIN13_Pos (13U)
#define GPIO_DRIVER_PIN13_Msk (0x1UL << GPIO_DRIVER_PIN13_Pos)
#define GPIO_DRIVER_PIN13 GPIO_DRIVER_PIN13_Msk
#define GPIO_DRIVER_PIN14_Pos (14U)
#define GPIO_DRIVER_PIN14_Msk (0x1UL << GPIO_DRIVER_PIN14_Pos)
#define GPIO_DRIVER_PIN14 GPIO_DRIVER_PIN14_Msk
#define GPIO_DRIVER_PIN15_Pos (15U)
#define GPIO_DRIVER_PIN15_Msk (0x1UL << GPIO_DRIVER_PIN15_Pos)
#define GPIO_DRIVER_PIN15 GPIO_DRIVER_PIN15_Msk

// GPIO_PUPD
#define GPIO_PUPD_PUPIN0_Pos (0U)
#define GPIO_PUPD_PUPIN0_Msk (0x1UL << GPIO_PUPD_PUPIN0_Pos)
#define GPIO_PUPD_PUPIN0 GPIO_PUPD_PUPIN0_Msk
#define GPIO_PUPD_PUPIN1_Pos (1U)
#define GPIO_PUPD_PUPIN1_Msk (0x1UL << GPIO_PUPD_PUPIN1_Pos)
#define GPIO_PUPD_PUPIN1 GPIO_PUPD_PUPIN1_Msk
#define GPIO_PUPD_PUPIN2_Pos (2U)
#define GPIO_PUPD_PUPIN2_Msk (0x1UL << GPIO_PUPD_PUPIN2_Pos)
#define GPIO_PUPD_PUPIN2 GPIO_PUPD_PUPIN2_Msk
#define GPIO_PUPD_PUPIN3_Pos (3U)
#define GPIO_PUPD_PUPIN3_Msk (0x1UL << GPIO_PUPD_PUPIN3_Pos)
#define GPIO_PUPD_PUPIN3 GPIO_PUPD_PUPIN3_Msk
#define GPIO_PUPD_PUPIN4_Pos (4U)
#define GPIO_PUPD_PUPIN4_Msk (0x1UL << GPIO_PUPD_PUPIN4_Pos)
#define GPIO_PUPD_PUPIN4 GPIO_PUPD_PUPIN4_Msk
#define GPIO_PUPD_PUPIN5_Pos (5U)
#define GPIO_PUPD_PUPIN5_Msk (0x1UL << GPIO_PUPD_PUPIN5_Pos)
#define GPIO_PUPD_PUPIN5 GPIO_PUPD_PUPIN5_Msk
#define GPIO_PUPD_PUPIN6_Pos (6U)
#define GPIO_PUPD_PUPIN6_Msk (0x1UL << GPIO_PUPD_PUPIN6_Pos)
#define GPIO_PUPD_PUPIN6 GPIO_PUPD_PUPIN6_Msk
#define GPIO_PUPD_PUPIN7_Pos (7U)
#define GPIO_PUPD_PUPIN7_Msk (0x1UL << GPIO_PUPD_PUPIN7_Pos)
#define GPIO_PUPD_PUPIN7 GPIO_PUPD_PUPIN7_Msk
#define GPIO_PUPD_PUPIN8_Pos (8U)
#define GPIO_PUPD_PUPIN8_Msk (0x1UL << GPIO_PUPD_PUPIN8_Pos)
#define GPIO_PUPD_PUPIN8 GPIO_PUPD_PUPIN8_Msk
#define GPIO_PUPD_PUPIN9_Pos (9U)
#define GPIO_PUPD_PUPIN9_Msk (0x1UL << GPIO_PUPD_PUPIN9_Pos)
#define GPIO_PUPD_PUPIN9 GPIO_PUPD_PUPIN9_Msk
#define GPIO_PUPD_PUPIN10_Pos (10U)
#define GPIO_PUPD_PUPIN10_Msk (0x1UL << GPIO_PUPD_PUPIN10_Pos)
#define GPIO_PUPD_PUPIN10 GPIO_PUPD_PUPIN10_Msk
#define GPIO_PUPD_PUPIN11_Pos (11U)
#define GPIO_PUPD_PUPIN11_Msk (0x1UL << GPIO_PUPD_PUPIN11_Pos)
#define GPIO_PUPD_PUPIN11 GPIO_PUPD_PUPIN11_Msk
#define GPIO_PUPD_PUPIN12_Pos (12U)
#define GPIO_PUPD_PUPIN12_Msk (0x1UL << GPIO_PUPD_PUPIN12_Pos)
#define GPIO_PUPD_PUPIN12 GPIO_PUPD_PUPIN12_Msk
#define GPIO_PUPD_PUPIN13_Pos (13U)
#define GPIO_PUPD_PUPIN13_Msk (0x1UL << GPIO_PUPD_PUPIN13_Pos)
#define GPIO_PUPD_PUPIN13 GPIO_PUPD_PUPIN13_Msk
#define GPIO_PUPD_PUPIN14_Pos (14U)
#define GPIO_PUPD_PUPIN14_Msk (0x1UL << GPIO_PUPD_PUPIN14_Pos)
#define GPIO_PUPD_PUPIN14 GPIO_PUPD_PUPIN14_Msk
#define GPIO_PUPD_PUPIN15_Pos (15U)
#define GPIO_PUPD_PUPIN15_Msk (0x1UL << GPIO_PUPD_PUPIN15_Pos)
#define GPIO_PUPD_PUPIN15 GPIO_PUPD_PUPIN15_Msk
#define GPIO_PUPD_PDPIN0_Pos (16U)
#define GPIO_PUPD_PDPIN0_Msk (0x1UL << GPIO_PUPD_PDPIN0_Pos)
#define GPIO_PUPD_PDPIN0 GPIO_PUPD_PDPIN0_Msk
#define GPIO_PUPD_PDPIN1_Pos (17U)
#define GPIO_PUPD_PDPIN1_Msk (0x1UL << GPIO_PUPD_PDPIN1_Pos)
#define GPIO_PUPD_PDPIN1 GPIO_PUPD_PDPIN1_Msk
#define GPIO_PUPD_PDPIN2_Pos (18U)
#define GPIO_PUPD_PDPIN2_Msk (0x1UL << GPIO_PUPD_PDPIN2_Pos)
#define GPIO_PUPD_PDPIN2 GPIO_PUPD_PDPIN2_Msk
#define GPIO_PUPD_PDPIN3_Pos (19U)
#define GPIO_PUPD_PDPIN3_Msk (0x1UL << GPIO_PUPD_PDPIN3_Pos)
#define GPIO_PUPD_PDPIN3 GPIO_PUPD_PDPIN3_Msk
#define GPIO_PUPD_PDPIN4_Pos (20U)
#define GPIO_PUPD_PDPIN4_Msk (0x1UL << GPIO_PUPD_PDPIN4_Pos)
#define GPIO_PUPD_PDPIN4 GPIO_PUPD_PDPIN4_Msk
#define GPIO_PUPD_PDPIN5_Pos (21U)
#define GPIO_PUPD_PDPIN5_Msk (0x1UL << GPIO_PUPD_PDPIN5_Pos)
#define GPIO_PUPD_PDPIN5 GPIO_PUPD_PDPIN5_Msk
#define GPIO_PUPD_PDPIN6_Pos (22U)
#define GPIO_PUPD_PDPIN6_Msk (0x1UL << GPIO_PUPD_PDPIN6_Pos)
#define GPIO_PUPD_PDPIN6 GPIO_PUPD_PDPIN6_Msk
#define GPIO_PUPD_PDPIN7_Pos (23U)
#define GPIO_PUPD_PDPIN7_Msk (0x1UL << GPIO_PUPD_PDPIN7_Pos)
#define GPIO_PUPD_PDPIN7 GPIO_PUPD_PDPIN7_Msk
#define GPIO_PUPD_PDPIN8_Pos (24U)
#define GPIO_PUPD_PDPIN8_Msk (0x1UL << GPIO_PUPD_PDPIN8_Pos)
#define GPIO_PUPD_PDPIN8 GPIO_PUPD_PDPIN8_Msk
#define GPIO_PUPD_PDPIN9_Pos (25U)
#define GPIO_PUPD_PDPIN9_Msk (0x1UL << GPIO_PUPD_PDPIN9_Pos)
#define GPIO_PUPD_PDPIN9 GPIO_PUPD_PDPIN9_Msk
#define GPIO_PUPD_PDPIN10_Pos (26U)
#define GPIO_PUPD_PDPIN10_Msk (0x1UL << GPIO_PUPD_PDPIN10_Pos)
#define GPIO_PUPD_PDPIN10 GPIO_PUPD_PDPIN10_Msk
#define GPIO_PUPD_PDPIN11_Pos (27U)
#define GPIO_PUPD_PDPIN11_Msk (0x1UL << GPIO_PUPD_PDPIN11_Pos)
#define GPIO_PUPD_PDPIN11 GPIO_PUPD_PDPIN11_Msk
#define GPIO_PUPD_PDPIN12_Pos (28U)
#define GPIO_PUPD_PDPIN12_Msk (0x1UL << GPIO_PUPD_PDPIN12_Pos)
#define GPIO_PUPD_PDPIN12 GPIO_PUPD_PDPIN12_Msk
#define GPIO_PUPD_PDPIN13_Pos (29U)
#define GPIO_PUPD_PDPIN13_Msk (0x1UL << GPIO_PUPD_PDPIN13_Pos)
#define GPIO_PUPD_PDPIN13 GPIO_PUPD_PDPIN13_Msk
#define GPIO_PUPD_PDPIN14_Pos (30U)
#define GPIO_PUPD_PDPIN14_Msk (0x1UL << GPIO_PUPD_PDPIN14_Pos)
#define GPIO_PUPD_PDPIN14 GPIO_PUPD_PDPIN14_Msk
#define GPIO_PUPD_PDPIN15_Pos (31U)
#define GPIO_PUPD_PDPIN15_Msk (0x1UL << GPIO_PUPD_PDPIN15_Pos)
#define GPIO_PUPD_PDPIN15 GPIO_PUPD_PDPIN15_Msk

// GPIO_IN
#define GPIO_IN_PIN0_Pos (0U)
#define GPIO_IN_PIN0_Msk (0x1UL << GPIO_IN_PIN0_Pos)
#define GPIO_IN_PIN0 GPIO_IN_PIN0_Msk
#define GPIO_IN_PIN1_Pos (1U)
#define GPIO_IN_PIN1_Msk (0x1UL << GPIO_IN_PIN1_Pos)
#define GPIO_IN_PIN1 GPIO_IN_PIN1_Msk
#define GPIO_IN_PIN2_Pos (2U)
#define GPIO_IN_PIN2_Msk (0x1UL << GPIO_IN_PIN2_Pos)
#define GPIO_IN_PIN2 GPIO_IN_PIN2_Msk
#define GPIO_IN_PIN3_Pos (3U)
#define GPIO_IN_PIN3_Msk (0x1UL << GPIO_IN_PIN3_Pos)
#define GPIO_IN_PIN3 GPIO_IN_PIN3_Msk
#define GPIO_IN_PIN4_Pos (4U)
#define GPIO_IN_PIN4_Msk (0x1UL << GPIO_IN_PIN4_Pos)
#define GPIO_IN_PIN4 GPIO_IN_PIN4_Msk
#define GPIO_IN_PIN5_Pos (5U)
#define GPIO_IN_PIN5_Msk (0x1UL << GPIO_IN_PIN5_Pos)
#define GPIO_IN_PIN5 GPIO_IN_PIN5_Msk
#define GPIO_IN_PIN6_Pos (6U)
#define GPIO_IN_PIN6_Msk (0x1UL << GPIO_IN_PIN6_Pos)
#define GPIO_IN_PIN6 GPIO_IN_PIN6_Msk
#define GPIO_IN_PIN7_Pos (7U)
#define GPIO_IN_PIN7_Msk (0x1UL << GPIO_IN_PIN7_Pos)
#define GPIO_IN_PIN7 GPIO_IN_PIN7_Msk
#define GPIO_IN_PIN8_Pos (8U)
#define GPIO_IN_PIN8_Msk (0x1UL << GPIO_IN_PIN8_Pos)
#define GPIO_IN_PIN8 GPIO_IN_PIN8_Msk
#define GPIO_IN_PIN9_Pos (9U)
#define GPIO_IN_PIN9_Msk (0x1UL << GPIO_IN_PIN9_Pos)
#define GPIO_IN_PIN9 GPIO_IN_PIN9_Msk
#define GPIO_IN_PIN10_Pos (10U)
#define GPIO_IN_PIN10_Msk (0x1UL << GPIO_IN_PIN10_Pos)
#define GPIO_IN_PIN10 GPIO_IN_PIN10_Msk
#define GPIO_IN_PIN11_Pos (11U)
#define GPIO_IN_PIN11_Msk (0x1UL << GPIO_IN_PIN11_Pos)
#define GPIO_IN_PIN11 GPIO_IN_PIN11_Msk
#define GPIO_IN_PIN12_Pos (12U)
#define GPIO_IN_PIN12_Msk (0x1UL << GPIO_IN_PIN12_Pos)
#define GPIO_IN_PIN12 GPIO_IN_PIN12_Msk
#define GPIO_IN_PIN13_Pos (13U)
#define GPIO_IN_PIN13_Msk (0x1UL << GPIO_IN_PIN13_Pos)
#define GPIO_IN_PIN13 GPIO_IN_PIN13_Msk
#define GPIO_IN_PIN14_Pos (14U)
#define GPIO_IN_PIN14_Msk (0x1UL << GPIO_IN_PIN14_Pos)
#define GPIO_IN_PIN14 GPIO_IN_PIN14_Msk
#define GPIO_IN_PIN15_Pos (15U)
#define GPIO_IN_PIN15_Msk (0x1UL << GPIO_IN_PIN15_Pos)
#define GPIO_IN_PIN15 GPIO_IN_PIN15_Msk

// GPIO_OUT
#define GPIO_OUT_PIN0_Pos (0U)
#define GPIO_OUT_PIN0_Msk (0x1UL << GPIO_OUT_PIN0_Pos)
#define GPIO_OUT_PIN0 GPIO_OUT_PIN0_Msk
#define GPIO_OUT_PIN1_Pos (1U)
#define GPIO_OUT_PIN1_Msk (0x1UL << GPIO_OUT_PIN1_Pos)
#define GPIO_OUT_PIN1 GPIO_OUT_PIN1_Msk
#define GPIO_OUT_PIN2_Pos (2U)
#define GPIO_OUT_PIN2_Msk (0x1UL << GPIO_OUT_PIN2_Pos)
#define GPIO_OUT_PIN2 GPIO_OUT_PIN2_Msk
#define GPIO_OUT_PIN3_Pos (3U)
#define GPIO_OUT_PIN3_Msk (0x1UL << GPIO_OUT_PIN3_Pos)
#define GPIO_OUT_PIN3 GPIO_OUT_PIN3_Msk
#define GPIO_OUT_PIN4_Pos (4U)
#define GPIO_OUT_PIN4_Msk (0x1UL << GPIO_OUT_PIN4_Pos)
#define GPIO_OUT_PIN4 GPIO_OUT_PIN4_Msk
#define GPIO_OUT_PIN5_Pos (5U)
#define GPIO_OUT_PIN5_Msk (0x1UL << GPIO_OUT_PIN5_Pos)
#define GPIO_OUT_PIN5 GPIO_OUT_PIN5_Msk
#define GPIO_OUT_PIN6_Pos (6U)
#define GPIO_OUT_PIN6_Msk (0x1UL << GPIO_OUT_PIN6_Pos)
#define GPIO_OUT_PIN6 GPIO_OUT_PIN6_Msk
#define GPIO_OUT_PIN7_Pos (7U)
#define GPIO_OUT_PIN7_Msk (0x1UL << GPIO_OUT_PIN7_Pos)
#define GPIO_OUT_PIN7 GPIO_OUT_PIN7_Msk
#define GPIO_OUT_PIN8_Pos (8U)
#define GPIO_OUT_PIN8_Msk (0x1UL << GPIO_OUT_PIN8_Pos)
#define GPIO_OUT_PIN8 GPIO_OUT_PIN8_Msk
#define GPIO_OUT_PIN9_Pos (9U)
#define GPIO_OUT_PIN9_Msk (0x1UL << GPIO_OUT_PIN9_Pos)
#define GPIO_OUT_PIN9 GPIO_OUT_PIN9_Msk
#define GPIO_OUT_PIN10_Pos (10U)
#define GPIO_OUT_PIN10_Msk (0x1UL << GPIO_OUT_PIN10_Pos)
#define GPIO_OUT_PIN10 GPIO_OUT_PIN10_Msk
#define GPIO_OUT_PIN11_Pos (11U)
#define GPIO_OUT_PIN11_Msk (0x1UL << GPIO_OUT_PIN11_Pos)
#define GPIO_OUT_PIN11 GPIO_OUT_PIN11_Msk
#define GPIO_OUT_PIN12_Pos (12U)
#define GPIO_OUT_PIN12_Msk (0x1UL << GPIO_OUT_PIN12_Pos)
#define GPIO_OUT_PIN12 GPIO_OUT_PIN12_Msk
#define GPIO_OUT_PIN13_Pos (13U)
#define GPIO_OUT_PIN13_Msk (0x1UL << GPIO_OUT_PIN13_Pos)
#define GPIO_OUT_PIN13 GPIO_OUT_PIN13_Msk
#define GPIO_OUT_PIN14_Pos (14U)
#define GPIO_OUT_PIN14_Msk (0x1UL << GPIO_OUT_PIN14_Pos)
#define GPIO_OUT_PIN14 GPIO_OUT_PIN14_Msk
#define GPIO_OUT_PIN15_Pos (15U)
#define GPIO_OUT_PIN15_Msk (0x1UL << GPIO_OUT_PIN15_Pos)
#define GPIO_OUT_PIN15 GPIO_OUT_PIN15_Msk

// GPIO_BRR
#define GPIO_BRR_PIN0_Pos (0U)
#define GPIO_BRR_PIN0_Msk (0x1UL << GPIO_BRR_PIN0_Pos)
#define GPIO_BRR_PIN0 GPIO_BRR_PIN0_Msk
#define GPIO_BRR_PIN1_Pos (1U)
#define GPIO_BRR_PIN1_Msk (0x1UL << GPIO_BRR_PIN1_Pos)
#define GPIO_BRR_PIN1 GPIO_BRR_PIN1_Msk
#define GPIO_BRR_PIN2_Pos (2U)
#define GPIO_BRR_PIN2_Msk (0x1UL << GPIO_BRR_PIN2_Pos)
#define GPIO_BRR_PIN2 GPIO_BRR_PIN2_Msk
#define GPIO_BRR_PIN3_Pos (3U)
#define GPIO_BRR_PIN3_Msk (0x1UL << GPIO_BRR_PIN3_Pos)
#define GPIO_BRR_PIN3 GPIO_BRR_PIN3_Msk
#define GPIO_BRR_PIN4_Pos (4U)
#define GPIO_BRR_PIN4_Msk (0x1UL << GPIO_BRR_PIN4_Pos)
#define GPIO_BRR_PIN4 GPIO_BRR_PIN4_Msk
#define GPIO_BRR_PIN5_Pos (5U)
#define GPIO_BRR_PIN5_Msk (0x1UL << GPIO_BRR_PIN5_Pos)
#define GPIO_BRR_PIN5 GPIO_BRR_PIN5_Msk
#define GPIO_BRR_PIN6_Pos (6U)
#define GPIO_BRR_PIN6_Msk (0x1UL << GPIO_BRR_PIN6_Pos)
#define GPIO_BRR_PIN6 GPIO_BRR_PIN6_Msk
#define GPIO_BRR_PIN7_Pos (7U)
#define GPIO_BRR_PIN7_Msk (0x1UL << GPIO_BRR_PIN7_Pos)
#define GPIO_BRR_PIN7 GPIO_BRR_PIN7_Msk
#define GPIO_BRR_PIN8_Pos (8U)
#define GPIO_BRR_PIN8_Msk (0x1UL << GPIO_BRR_PIN8_Pos)
#define GPIO_BRR_PIN8 GPIO_BRR_PIN8_Msk
#define GPIO_BRR_PIN9_Pos (9U)
#define GPIO_BRR_PIN9_Msk (0x1UL << GPIO_BRR_PIN9_Pos)
#define GPIO_BRR_PIN9 GPIO_BRR_PIN9_Msk
#define GPIO_BRR_PIN10_Pos (10U)
#define GPIO_BRR_PIN10_Msk (0x1UL << GPIO_BRR_PIN10_Pos)
#define GPIO_BRR_PIN10 GPIO_BRR_PIN10_Msk
#define GPIO_BRR_PIN11_Pos (11U)
#define GPIO_BRR_PIN11_Msk (0x1UL << GPIO_BRR_PIN11_Pos)
#define GPIO_BRR_PIN11 GPIO_BRR_PIN11_Msk
#define GPIO_BRR_PIN12_Pos (12U)
#define GPIO_BRR_PIN12_Msk (0x1UL << GPIO_BRR_PIN12_Pos)
#define GPIO_BRR_PIN12 GPIO_BRR_PIN12_Msk
#define GPIO_BRR_PIN13_Pos (13U)
#define GPIO_BRR_PIN13_Msk (0x1UL << GPIO_BRR_PIN13_Pos)
#define GPIO_BRR_PIN13 GPIO_BRR_PIN13_Msk
#define GPIO_BRR_PIN14_Pos (14U)
#define GPIO_BRR_PIN14_Msk (0x1UL << GPIO_BRR_PIN14_Pos)
#define GPIO_BRR_PIN14 GPIO_BRR_PIN14_Msk
#define GPIO_BRR_PIN15_Pos (15U)
#define GPIO_BRR_PIN15_Msk (0x1UL << GPIO_BRR_PIN15_Pos)
#define GPIO_BRR_PIN15 GPIO_BRR_PIN15_Msk

// GPIO_BSRR
#define GPIO_BSRR_BSPIN0_Pos (0U)
#define GPIO_BSRR_BSPIN0_Msk (0x1UL << GPIO_BSRR_BSPIN0_Pos)
#define GPIO_BSRR_BSPIN0 GPIO_BSRR_BSPIN0_Msk
#define GPIO_BSRR_BSPIN1_Pos (1U)
#define GPIO_BSRR_BSPIN1_Msk (0x1UL << GPIO_BSRR_BSPIN1_Pos)
#define GPIO_BSRR_BSPIN1 GPIO_BSRR_BSPIN1_Msk
#define GPIO_BSRR_BSPIN2_Pos (2U)
#define GPIO_BSRR_BSPIN2_Msk (0x1UL << GPIO_BSRR_BSPIN2_Pos)
#define GPIO_BSRR_BSPIN2 GPIO_BSRR_BSPIN2_Msk
#define GPIO_BSRR_BSPIN3_Pos (3U)
#define GPIO_BSRR_BSPIN3_Msk (0x1UL << GPIO_BSRR_BSPIN3_Pos)
#define GPIO_BSRR_BSPIN3 GPIO_BSRR_BSPIN3_Msk
#define GPIO_BSRR_BSPIN4_Pos (4U)
#define GPIO_BSRR_BSPIN4_Msk (0x1UL << GPIO_BSRR_BSPIN4_Pos)
#define GPIO_BSRR_BSPIN4 GPIO_BSRR_BSPIN4_Msk
#define GPIO_BSRR_BSPIN5_Pos (5U)
#define GPIO_BSRR_BSPIN5_Msk (0x1UL << GPIO_BSRR_BSPIN5_Pos)
#define GPIO_BSRR_BSPIN5 GPIO_BSRR_BSPIN5_Msk
#define GPIO_BSRR_BSPIN6_Pos (6U)
#define GPIO_BSRR_BSPIN6_Msk (0x1UL << GPIO_BSRR_BSPIN6_Pos)
#define GPIO_BSRR_BSPIN6 GPIO_BSRR_BSPIN6_Msk
#define GPIO_BSRR_BSPIN7_Pos (7U)
#define GPIO_BSRR_BSPIN7_Msk (0x1UL << GPIO_BSRR_BSPIN7_Pos)
#define GPIO_BSRR_BSPIN7 GPIO_BSRR_BSPIN7_Msk
#define GPIO_BSRR_BSPIN8_Pos (8U)
#define GPIO_BSRR_BSPIN8_Msk (0x1UL << GPIO_BSRR_BSPIN8_Pos)
#define GPIO_BSRR_BSPIN8 GPIO_BSRR_BSPIN8_Msk
#define GPIO_BSRR_BSPIN9_Pos (9U)
#define GPIO_BSRR_BSPIN9_Msk (0x1UL << GPIO_BSRR_BSPIN9_Pos)
#define GPIO_BSRR_BSPIN9 GPIO_BSRR_BSPIN9_Msk
#define GPIO_BSRR_BSPIN10_Pos (10U)
#define GPIO_BSRR_BSPIN10_Msk (0x1UL << GPIO_BSRR_BSPIN10_Pos)
#define GPIO_BSRR_BSPIN10 GPIO_BSRR_BSPIN10_Msk
#define GPIO_BSRR_BSPIN11_Pos (11U)
#define GPIO_BSRR_BSPIN11_Msk (0x1UL << GPIO_BSRR_BSPIN11_Pos)
#define GPIO_BSRR_BSPIN11 GPIO_BSRR_BSPIN11_Msk
#define GPIO_BSRR_BSPIN12_Pos (12U)
#define GPIO_BSRR_BSPIN12_Msk (0x1UL << GPIO_BSRR_BSPIN12_Pos)
#define GPIO_BSRR_BSPIN12 GPIO_BSRR_BSPIN12_Msk
#define GPIO_BSRR_BSPIN13_Pos (13U)
#define GPIO_BSRR_BSPIN13_Msk (0x1UL << GPIO_BSRR_BSPIN13_Pos)
#define GPIO_BSRR_BSPIN13 GPIO_BSRR_BSPIN13_Msk
#define GPIO_BSRR_BSPIN14_Pos (14U)
#define GPIO_BSRR_BSPIN14_Msk (0x1UL << GPIO_BSRR_BSPIN14_Pos)
#define GPIO_BSRR_BSPIN14 GPIO_BSRR_BSPIN14_Msk
#define GPIO_BSRR_BSPIN15_Pos (15U)
#define GPIO_BSRR_BSPIN15_Msk (0x1UL << GPIO_BSRR_BSPIN15_Pos)
#define GPIO_BSRR_BSPIN15 GPIO_BSRR_BSPIN15_Msk
#define GPIO_BSRR_BRPIN0_Pos (16U)
#define GPIO_BSRR_BRPIN0_Msk (0x1UL << GPIO_BSRR_BRPIN0_Pos)
#define GPIO_BSRR_BRPIN0 GPIO_BSRR_BRPIN0_Msk
#define GPIO_BSRR_BRPIN1_Pos (17U)
#define GPIO_BSRR_BRPIN1_Msk (0x1UL << GPIO_BSRR_BRPIN1_Pos)
#define GPIO_BSRR_BRPIN1 GPIO_BSRR_BRPIN1_Msk
#define GPIO_BSRR_BRPIN2_Pos (18U)
#define GPIO_BSRR_BRPIN2_Msk (0x1UL << GPIO_BSRR_BRPIN2_Pos)
#define GPIO_BSRR_BRPIN2 GPIO_BSRR_BRPIN2_Msk
#define GPIO_BSRR_BRPIN3_Pos (19U)
#define GPIO_BSRR_BRPIN3_Msk (0x1UL << GPIO_BSRR_BRPIN3_Pos)
#define GPIO_BSRR_BRPIN3 GPIO_BSRR_BRPIN3_Msk
#define GPIO_BSRR_BRPIN4_Pos (20U)
#define GPIO_BSRR_BRPIN4_Msk (0x1UL << GPIO_BSRR_BRPIN4_Pos)
#define GPIO_BSRR_BRPIN4 GPIO_BSRR_BRPIN4_Msk
#define GPIO_BSRR_BRPIN5_Pos (21U)
#define GPIO_BSRR_BRPIN5_Msk (0x1UL << GPIO_BSRR_BRPIN5_Pos)
#define GPIO_BSRR_BRPIN5 GPIO_BSRR_BRPIN5_Msk
#define GPIO_BSRR_BRPIN6_Pos (22U)
#define GPIO_BSRR_BRPIN6_Msk (0x1UL << GPIO_BSRR_BRPIN6_Pos)
#define GPIO_BSRR_BRPIN6 GPIO_BSRR_BRPIN6_Msk
#define GPIO_BSRR_BRPIN7_Pos (23U)
#define GPIO_BSRR_BRPIN7_Msk (0x1UL << GPIO_BSRR_BRPIN7_Pos)
#define GPIO_BSRR_BRPIN7 GPIO_BSRR_BRPIN7_Msk
#define GPIO_BSRR_BRPIN8_Pos (24U)
#define GPIO_BSRR_BRPIN8_Msk (0x1UL << GPIO_BSRR_BRPIN8_Pos)
#define GPIO_BSRR_BRPIN8 GPIO_BSRR_BRPIN8_Msk
#define GPIO_BSRR_BRPIN9_Pos (25U)
#define GPIO_BSRR_BRPIN9_Msk (0x1UL << GPIO_BSRR_BRPIN9_Pos)
#define GPIO_BSRR_BRPIN9 GPIO_BSRR_BRPIN9_Msk
#define GPIO_BSRR_BRPIN10_Pos (26U)
#define GPIO_BSRR_BRPIN10_Msk (0x1UL << GPIO_BSRR_BRPIN10_Pos)
#define GPIO_BSRR_BRPIN10 GPIO_BSRR_BRPIN10_Msk
#define GPIO_BSRR_BRPIN11_Pos (27U)
#define GPIO_BSRR_BRPIN11_Msk (0x1UL << GPIO_BSRR_BRPIN11_Pos)
#define GPIO_BSRR_BRPIN11 GPIO_BSRR_BRPIN11_Msk
#define GPIO_BSRR_BRPIN12_Pos (28U)
#define GPIO_BSRR_BRPIN12_Msk (0x1UL << GPIO_BSRR_BRPIN12_Pos)
#define GPIO_BSRR_BRPIN12 GPIO_BSRR_BRPIN12_Msk
#define GPIO_BSRR_BRPIN13_Pos (29U)
#define GPIO_BSRR_BRPIN13_Msk (0x1UL << GPIO_BSRR_BRPIN13_Pos)
#define GPIO_BSRR_BRPIN13 GPIO_BSRR_BRPIN13_Msk
#define GPIO_BSRR_BRPIN14_Pos (30U)
#define GPIO_BSRR_BRPIN14_Msk (0x1UL << GPIO_BSRR_BRPIN14_Pos)
#define GPIO_BSRR_BRPIN14 GPIO_BSRR_BRPIN14_Msk
#define GPIO_BSRR_BRPIN15_Pos (31U)
#define GPIO_BSRR_BRPIN15_Msk (0x1UL << GPIO_BSRR_BRPIN15_Pos)
#define GPIO_BSRR_BRPIN15 GPIO_BSRR_BRPIN15_Msk

// GPIO_AFRL
#define GPIO_AFRL_AFSEL0_Pos (0U)
#define GPIO_AFRL_AFSEL0_Msk (0xFUL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL0 GPIO_AFRL_AFSEL0_Msk
#define GPIO_AFRL_AFSEL1_Pos (4U)
#define GPIO_AFRL_AFSEL1_Msk (0xFUL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL1 GPIO_AFRL_AFSEL1_Msk
#define GPIO_AFRL_AFSEL2_Pos (8U)
#define GPIO_AFRL_AFSEL2_Msk (0xFUL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2 GPIO_AFRL_AFSEL2_Msk
#define GPIO_AFRL_AFSEL3_Pos (12U)
#define GPIO_AFRL_AFSEL3_Msk (0xFUL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL3 GPIO_AFRL_AFSEL3_Msk
#define GPIO_AFRL_AFSEL4_Pos (16U)
#define GPIO_AFRL_AFSEL4_Msk (0xFUL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL4 GPIO_AFRL_AFSEL4_Msk
#define GPIO_AFRL_AFSEL5_Pos (20U)
#define GPIO_AFRL_AFSEL5_Msk (0xFUL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL5 GPIO_AFRL_AFSEL5_Msk
#define GPIO_AFRL_AFSEL6_Pos (24U)
#define GPIO_AFRL_AFSEL6_Msk (0xFUL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL6 GPIO_AFRL_AFSEL6_Msk
#define GPIO_AFRL_AFSEL7_Pos (28U)
#define GPIO_AFRL_AFSEL7_Msk (0xFUL << GPIO_AFRL_AFSEL7_Pos)
#define GPIO_AFRL_AFSEL7 GPIO_AFRL_AFSEL7_Msk

// GPIO_AFRH
#define GPIO_AFRH_AFSEL8_Pos (0U)
#define GPIO_AFRH_AFSEL8_Msk (0xFUL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL8 GPIO_AFRH_AFSEL8_Msk
#define GPIO_AFRH_AFSEL9_Pos (4U)
#define GPIO_AFRH_AFSEL9_Msk (0xFUL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL9 GPIO_AFRH_AFSEL9_Msk
#define GPIO_AFRH_AFSEL10_Pos (8U)
#define GPIO_AFRH_AFSEL10_Msk (0xFUL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL10 GPIO_AFRH_AFSEL10_Msk
#define GPIO_AFRH_AFSEL11_Pos (12U)
#define GPIO_AFRH_AFSEL11_Msk (0xFUL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL11 GPIO_AFRH_AFSEL11_Msk
#define GPIO_AFRH_AFSEL12_Pos (16U)
#define GPIO_AFRH_AFSEL12_Msk (0xFUL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL12 GPIO_AFRH_AFSEL12_Msk
#define GPIO_AFRH_AFSEL13_Pos (20U)
#define GPIO_AFRH_AFSEL13_Msk (0xFUL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL13 GPIO_AFRH_AFSEL13_Msk
#define GPIO_AFRH_AFSEL14_Pos (24U)
#define GPIO_AFRH_AFSEL14_Msk (0xFUL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL14 GPIO_AFRH_AFSEL14_Msk
#define GPIO_AFRH_AFSEL15_Pos (28U)
#define GPIO_AFRH_AFSEL15_Msk (0xFUL << GPIO_AFRH_AFSEL15_Pos)
#define GPIO_AFRH_AFSEL15 GPIO_AFRH_AFSEL15_Msk

// GPIO_HIGHIE
#define GPIO_HIGHIE_PIN0_Pos (0U)
#define GPIO_HIGHIE_PIN0_Msk (0x1UL << GPIO_HIGHIE_PIN0_Pos)
#define GPIO_HIGHIE_PIN0 GPIO_HIGHIE_PIN0_Msk
#define GPIO_HIGHIE_PIN1_Pos (1U)
#define GPIO_HIGHIE_PIN1_Msk (0x1UL << GPIO_HIGHIE_PIN1_Pos)
#define GPIO_HIGHIE_PIN1 GPIO_HIGHIE_PIN1_Msk
#define GPIO_HIGHIE_PIN2_Pos (2U)
#define GPIO_HIGHIE_PIN2_Msk (0x1UL << GPIO_HIGHIE_PIN2_Pos)
#define GPIO_HIGHIE_PIN2 GPIO_HIGHIE_PIN2_Msk
#define GPIO_HIGHIE_PIN3_Pos (3U)
#define GPIO_HIGHIE_PIN3_Msk (0x1UL << GPIO_HIGHIE_PIN3_Pos)
#define GPIO_HIGHIE_PIN3 GPIO_HIGHIE_PIN3_Msk
#define GPIO_HIGHIE_PIN4_Pos (4U)
#define GPIO_HIGHIE_PIN4_Msk (0x1UL << GPIO_HIGHIE_PIN4_Pos)
#define GPIO_HIGHIE_PIN4 GPIO_HIGHIE_PIN4_Msk
#define GPIO_HIGHIE_PIN5_Pos (5U)
#define GPIO_HIGHIE_PIN5_Msk (0x1UL << GPIO_HIGHIE_PIN5_Pos)
#define GPIO_HIGHIE_PIN5 GPIO_HIGHIE_PIN5_Msk
#define GPIO_HIGHIE_PIN6_Pos (6U)
#define GPIO_HIGHIE_PIN6_Msk (0x1UL << GPIO_HIGHIE_PIN6_Pos)
#define GPIO_HIGHIE_PIN6 GPIO_HIGHIE_PIN6_Msk
#define GPIO_HIGHIE_PIN7_Pos (7U)
#define GPIO_HIGHIE_PIN7_Msk (0x1UL << GPIO_HIGHIE_PIN7_Pos)
#define GPIO_HIGHIE_PIN7 GPIO_HIGHIE_PIN7_Msk
#define GPIO_HIGHIE_PIN8_Pos (8U)
#define GPIO_HIGHIE_PIN8_Msk (0x1UL << GPIO_HIGHIE_PIN8_Pos)
#define GPIO_HIGHIE_PIN8 GPIO_HIGHIE_PIN8_Msk
#define GPIO_HIGHIE_PIN9_Pos (9U)
#define GPIO_HIGHIE_PIN9_Msk (0x1UL << GPIO_HIGHIE_PIN9_Pos)
#define GPIO_HIGHIE_PIN9 GPIO_HIGHIE_PIN9_Msk
#define GPIO_HIGHIE_PIN10_Pos (10U)
#define GPIO_HIGHIE_PIN10_Msk (0x1UL << GPIO_HIGHIE_PIN10_Pos)
#define GPIO_HIGHIE_PIN10 GPIO_HIGHIE_PIN10_Msk
#define GPIO_HIGHIE_PIN11_Pos (11U)
#define GPIO_HIGHIE_PIN11_Msk (0x1UL << GPIO_HIGHIE_PIN11_Pos)
#define GPIO_HIGHIE_PIN11 GPIO_HIGHIE_PIN11_Msk
#define GPIO_HIGHIE_PIN12_Pos (12U)
#define GPIO_HIGHIE_PIN12_Msk (0x1UL << GPIO_HIGHIE_PIN12_Pos)
#define GPIO_HIGHIE_PIN12 GPIO_HIGHIE_PIN12_Msk
#define GPIO_HIGHIE_PIN13_Pos (13U)
#define GPIO_HIGHIE_PIN13_Msk (0x1UL << GPIO_HIGHIE_PIN13_Pos)
#define GPIO_HIGHIE_PIN13 GPIO_HIGHIE_PIN13_Msk
#define GPIO_HIGHIE_PIN14_Pos (14U)
#define GPIO_HIGHIE_PIN14_Msk (0x1UL << GPIO_HIGHIE_PIN14_Pos)
#define GPIO_HIGHIE_PIN14 GPIO_HIGHIE_PIN14_Msk
#define GPIO_HIGHIE_PIN15_Pos (15U)
#define GPIO_HIGHIE_PIN15_Msk (0x1UL << GPIO_HIGHIE_PIN15_Pos)
#define GPIO_HIGHIE_PIN15 GPIO_HIGHIE_PIN15_Msk

// GPIO_LOWIE
#define GPIO_LOWIE_PIN0_Pos (0U)
#define GPIO_LOWIE_PIN0_Msk (0x1UL << GPIO_LOWIE_PIN0_Pos)
#define GPIO_LOWIE_PIN0 GPIO_LOWIE_PIN0_Msk
#define GPIO_LOWIE_PIN1_Pos (1U)
#define GPIO_LOWIE_PIN1_Msk (0x1UL << GPIO_LOWIE_PIN1_Pos)
#define GPIO_LOWIE_PIN1 GPIO_LOWIE_PIN1_Msk
#define GPIO_LOWIE_PIN2_Pos (2U)
#define GPIO_LOWIE_PIN2_Msk (0x1UL << GPIO_LOWIE_PIN2_Pos)
#define GPIO_LOWIE_PIN2 GPIO_LOWIE_PIN2_Msk
#define GPIO_LOWIE_PIN3_Pos (3U)
#define GPIO_LOWIE_PIN3_Msk (0x1UL << GPIO_LOWIE_PIN3_Pos)
#define GPIO_LOWIE_PIN3 GPIO_LOWIE_PIN3_Msk
#define GPIO_LOWIE_PIN4_Pos (4U)
#define GPIO_LOWIE_PIN4_Msk (0x1UL << GPIO_LOWIE_PIN4_Pos)
#define GPIO_LOWIE_PIN4 GPIO_LOWIE_PIN4_Msk
#define GPIO_LOWIE_PIN5_Pos (5U)
#define GPIO_LOWIE_PIN5_Msk (0x1UL << GPIO_LOWIE_PIN5_Pos)
#define GPIO_LOWIE_PIN5 GPIO_LOWIE_PIN5_Msk
#define GPIO_LOWIE_PIN6_Pos (6U)
#define GPIO_LOWIE_PIN6_Msk (0x1UL << GPIO_LOWIE_PIN6_Pos)
#define GPIO_LOWIE_PIN6 GPIO_LOWIE_PIN6_Msk
#define GPIO_LOWIE_PIN7_Pos (7U)
#define GPIO_LOWIE_PIN7_Msk (0x1UL << GPIO_LOWIE_PIN7_Pos)
#define GPIO_LOWIE_PIN7 GPIO_LOWIE_PIN7_Msk
#define GPIO_LOWIE_PIN8_Pos (8U)
#define GPIO_LOWIE_PIN8_Msk (0x1UL << GPIO_LOWIE_PIN8_Pos)
#define GPIO_LOWIE_PIN8 GPIO_LOWIE_PIN8_Msk
#define GPIO_LOWIE_PIN9_Pos (9U)
#define GPIO_LOWIE_PIN9_Msk (0x1UL << GPIO_LOWIE_PIN9_Pos)
#define GPIO_LOWIE_PIN9 GPIO_LOWIE_PIN9_Msk
#define GPIO_LOWIE_PIN10_Pos (10U)
#define GPIO_LOWIE_PIN10_Msk (0x1UL << GPIO_LOWIE_PIN10_Pos)
#define GPIO_LOWIE_PIN10 GPIO_LOWIE_PIN10_Msk
#define GPIO_LOWIE_PIN11_Pos (11U)
#define GPIO_LOWIE_PIN11_Msk (0x1UL << GPIO_LOWIE_PIN11_Pos)
#define GPIO_LOWIE_PIN11 GPIO_LOWIE_PIN11_Msk
#define GPIO_LOWIE_PIN12_Pos (12U)
#define GPIO_LOWIE_PIN12_Msk (0x1UL << GPIO_LOWIE_PIN12_Pos)
#define GPIO_LOWIE_PIN12 GPIO_LOWIE_PIN12_Msk
#define GPIO_LOWIE_PIN13_Pos (13U)
#define GPIO_LOWIE_PIN13_Msk (0x1UL << GPIO_LOWIE_PIN13_Pos)
#define GPIO_LOWIE_PIN13 GPIO_LOWIE_PIN13_Msk
#define GPIO_LOWIE_PIN14_Pos (14U)
#define GPIO_LOWIE_PIN14_Msk (0x1UL << GPIO_LOWIE_PIN14_Pos)
#define GPIO_LOWIE_PIN14 GPIO_LOWIE_PIN14_Msk
#define GPIO_LOWIE_PIN15_Pos (15U)
#define GPIO_LOWIE_PIN15_Msk (0x1UL << GPIO_LOWIE_PIN15_Pos)
#define GPIO_LOWIE_PIN15 GPIO_LOWIE_PIN15_Msk

// GPIO_RISEIE
#define GPIO_RISEIE_PIN0_Pos (0U)
#define GPIO_RISEIE_PIN0_Msk (0x1UL << GPIO_RISEIE_PIN0_Pos)
#define GPIO_RISEIE_PIN0 GPIO_RISEIE_PIN0_Msk
#define GPIO_RISEIE_PIN1_Pos (1U)
#define GPIO_RISEIE_PIN1_Msk (0x1UL << GPIO_RISEIE_PIN1_Pos)
#define GPIO_RISEIE_PIN1 GPIO_RISEIE_PIN1_Msk
#define GPIO_RISEIE_PIN2_Pos (2U)
#define GPIO_RISEIE_PIN2_Msk (0x1UL << GPIO_RISEIE_PIN2_Pos)
#define GPIO_RISEIE_PIN2 GPIO_RISEIE_PIN2_Msk
#define GPIO_RISEIE_PIN3_Pos (3U)
#define GPIO_RISEIE_PIN3_Msk (0x1UL << GPIO_RISEIE_PIN3_Pos)
#define GPIO_RISEIE_PIN3 GPIO_RISEIE_PIN3_Msk
#define GPIO_RISEIE_PIN4_Pos (4U)
#define GPIO_RISEIE_PIN4_Msk (0x1UL << GPIO_RISEIE_PIN4_Pos)
#define GPIO_RISEIE_PIN4 GPIO_RISEIE_PIN4_Msk
#define GPIO_RISEIE_PIN5_Pos (5U)
#define GPIO_RISEIE_PIN5_Msk (0x1UL << GPIO_RISEIE_PIN5_Pos)
#define GPIO_RISEIE_PIN5 GPIO_RISEIE_PIN5_Msk
#define GPIO_RISEIE_PIN6_Pos (6U)
#define GPIO_RISEIE_PIN6_Msk (0x1UL << GPIO_RISEIE_PIN6_Pos)
#define GPIO_RISEIE_PIN6 GPIO_RISEIE_PIN6_Msk
#define GPIO_RISEIE_PIN7_Pos (7U)
#define GPIO_RISEIE_PIN7_Msk (0x1UL << GPIO_RISEIE_PIN7_Pos)
#define GPIO_RISEIE_PIN7 GPIO_RISEIE_PIN7_Msk
#define GPIO_RISEIE_PIN8_Pos (8U)
#define GPIO_RISEIE_PIN8_Msk (0x1UL << GPIO_RISEIE_PIN8_Pos)
#define GPIO_RISEIE_PIN8 GPIO_RISEIE_PIN8_Msk
#define GPIO_RISEIE_PIN9_Pos (9U)
#define GPIO_RISEIE_PIN9_Msk (0x1UL << GPIO_RISEIE_PIN9_Pos)
#define GPIO_RISEIE_PIN9 GPIO_RISEIE_PIN9_Msk
#define GPIO_RISEIE_PIN10_Pos (10U)
#define GPIO_RISEIE_PIN10_Msk (0x1UL << GPIO_RISEIE_PIN10_Pos)
#define GPIO_RISEIE_PIN10 GPIO_RISEIE_PIN10_Msk
#define GPIO_RISEIE_PIN11_Pos (11U)
#define GPIO_RISEIE_PIN11_Msk (0x1UL << GPIO_RISEIE_PIN11_Pos)
#define GPIO_RISEIE_PIN11 GPIO_RISEIE_PIN11_Msk
#define GPIO_RISEIE_PIN12_Pos (12U)
#define GPIO_RISEIE_PIN12_Msk (0x1UL << GPIO_RISEIE_PIN12_Pos)
#define GPIO_RISEIE_PIN12 GPIO_RISEIE_PIN12_Msk
#define GPIO_RISEIE_PIN13_Pos (13U)
#define GPIO_RISEIE_PIN13_Msk (0x1UL << GPIO_RISEIE_PIN13_Pos)
#define GPIO_RISEIE_PIN13 GPIO_RISEIE_PIN13_Msk
#define GPIO_RISEIE_PIN14_Pos (14U)
#define GPIO_RISEIE_PIN14_Msk (0x1UL << GPIO_RISEIE_PIN14_Pos)
#define GPIO_RISEIE_PIN14 GPIO_RISEIE_PIN14_Msk
#define GPIO_RISEIE_PIN15_Pos (15U)
#define GPIO_RISEIE_PIN15_Msk (0x1UL << GPIO_RISEIE_PIN15_Pos)
#define GPIO_RISEIE_PIN15 GPIO_RISEIE_PIN15_Msk

// GPIO_FALLIE
#define GPIO_FALLIE_PIN0_Pos (0U)
#define GPIO_FALLIE_PIN0_Msk (0x1UL << GPIO_FALLIE_PIN0_Pos)
#define GPIO_FALLIE_PIN0 GPIO_FALLIE_PIN0_Msk
#define GPIO_FALLIE_PIN1_Pos (1U)
#define GPIO_FALLIE_PIN1_Msk (0x1UL << GPIO_FALLIE_PIN1_Pos)
#define GPIO_FALLIE_PIN1 GPIO_FALLIE_PIN1_Msk
#define GPIO_FALLIE_PIN2_Pos (2U)
#define GPIO_FALLIE_PIN2_Msk (0x1UL << GPIO_FALLIE_PIN2_Pos)
#define GPIO_FALLIE_PIN2 GPIO_FALLIE_PIN2_Msk
#define GPIO_FALLIE_PIN3_Pos (3U)
#define GPIO_FALLIE_PIN3_Msk (0x1UL << GPIO_FALLIE_PIN3_Pos)
#define GPIO_FALLIE_PIN3 GPIO_FALLIE_PIN3_Msk
#define GPIO_FALLIE_PIN4_Pos (4U)
#define GPIO_FALLIE_PIN4_Msk (0x1UL << GPIO_FALLIE_PIN4_Pos)
#define GPIO_FALLIE_PIN4 GPIO_FALLIE_PIN4_Msk
#define GPIO_FALLIE_PIN5_Pos (5U)
#define GPIO_FALLIE_PIN5_Msk (0x1UL << GPIO_FALLIE_PIN5_Pos)
#define GPIO_FALLIE_PIN5 GPIO_FALLIE_PIN5_Msk
#define GPIO_FALLIE_PIN6_Pos (6U)
#define GPIO_FALLIE_PIN6_Msk (0x1UL << GPIO_FALLIE_PIN6_Pos)
#define GPIO_FALLIE_PIN6 GPIO_FALLIE_PIN6_Msk
#define GPIO_FALLIE_PIN7_Pos (7U)
#define GPIO_FALLIE_PIN7_Msk (0x1UL << GPIO_FALLIE_PIN7_Pos)
#define GPIO_FALLIE_PIN7 GPIO_FALLIE_PIN7_Msk
#define GPIO_FALLIE_PIN8_Pos (8U)
#define GPIO_FALLIE_PIN8_Msk (0x1UL << GPIO_FALLIE_PIN8_Pos)
#define GPIO_FALLIE_PIN8 GPIO_FALLIE_PIN8_Msk
#define GPIO_FALLIE_PIN9_Pos (9U)
#define GPIO_FALLIE_PIN9_Msk (0x1UL << GPIO_FALLIE_PIN9_Pos)
#define GPIO_FALLIE_PIN9 GPIO_FALLIE_PIN9_Msk
#define GPIO_FALLIE_PIN10_Pos (10U)
#define GPIO_FALLIE_PIN10_Msk (0x1UL << GPIO_FALLIE_PIN10_Pos)
#define GPIO_FALLIE_PIN10 GPIO_FALLIE_PIN10_Msk
#define GPIO_FALLIE_PIN11_Pos (11U)
#define GPIO_FALLIE_PIN11_Msk (0x1UL << GPIO_FALLIE_PIN11_Pos)
#define GPIO_FALLIE_PIN11 GPIO_FALLIE_PIN11_Msk
#define GPIO_FALLIE_PIN12_Pos (12U)
#define GPIO_FALLIE_PIN12_Msk (0x1UL << GPIO_FALLIE_PIN12_Pos)
#define GPIO_FALLIE_PIN12 GPIO_FALLIE_PIN12_Msk
#define GPIO_FALLIE_PIN13_Pos (13U)
#define GPIO_FALLIE_PIN13_Msk (0x1UL << GPIO_FALLIE_PIN13_Pos)
#define GPIO_FALLIE_PIN13 GPIO_FALLIE_PIN13_Msk
#define GPIO_FALLIE_PIN14_Pos (14U)
#define GPIO_FALLIE_PIN14_Msk (0x1UL << GPIO_FALLIE_PIN14_Pos)
#define GPIO_FALLIE_PIN14 GPIO_FALLIE_PIN14_Msk
#define GPIO_FALLIE_PIN15_Pos (15U)
#define GPIO_FALLIE_PIN15_Msk (0x1UL << GPIO_FALLIE_PIN15_Pos)
#define GPIO_FALLIE_PIN15 GPIO_FALLIE_PIN15_Msk

// GPIO_IFR
#define GPIO_IFR_PIN0_Pos (0U)
#define GPIO_IFR_PIN0_Msk (0x1UL << GPIO_IFR_PIN0_Pos)
#define GPIO_IFR_PIN0 GPIO_IFR_PIN0_Msk
#define GPIO_IFR_PIN1_Pos (1U)
#define GPIO_IFR_PIN1_Msk (0x1UL << GPIO_IFR_PIN1_Pos)
#define GPIO_IFR_PIN1 GPIO_IFR_PIN1_Msk
#define GPIO_IFR_PIN2_Pos (2U)
#define GPIO_IFR_PIN2_Msk (0x1UL << GPIO_IFR_PIN2_Pos)
#define GPIO_IFR_PIN2 GPIO_IFR_PIN2_Msk
#define GPIO_IFR_PIN3_Pos (3U)
#define GPIO_IFR_PIN3_Msk (0x1UL << GPIO_IFR_PIN3_Pos)
#define GPIO_IFR_PIN3 GPIO_IFR_PIN3_Msk
#define GPIO_IFR_PIN4_Pos (4U)
#define GPIO_IFR_PIN4_Msk (0x1UL << GPIO_IFR_PIN4_Pos)
#define GPIO_IFR_PIN4 GPIO_IFR_PIN4_Msk
#define GPIO_IFR_PIN5_Pos (5U)
#define GPIO_IFR_PIN5_Msk (0x1UL << GPIO_IFR_PIN5_Pos)
#define GPIO_IFR_PIN5 GPIO_IFR_PIN5_Msk
#define GPIO_IFR_PIN6_Pos (6U)
#define GPIO_IFR_PIN6_Msk (0x1UL << GPIO_IFR_PIN6_Pos)
#define GPIO_IFR_PIN6 GPIO_IFR_PIN6_Msk
#define GPIO_IFR_PIN7_Pos (7U)
#define GPIO_IFR_PIN7_Msk (0x1UL << GPIO_IFR_PIN7_Pos)
#define GPIO_IFR_PIN7 GPIO_IFR_PIN7_Msk
#define GPIO_IFR_PIN8_Pos (8U)
#define GPIO_IFR_PIN8_Msk (0x1UL << GPIO_IFR_PIN8_Pos)
#define GPIO_IFR_PIN8 GPIO_IFR_PIN8_Msk
#define GPIO_IFR_PIN9_Pos (9U)
#define GPIO_IFR_PIN9_Msk (0x1UL << GPIO_IFR_PIN9_Pos)
#define GPIO_IFR_PIN9 GPIO_IFR_PIN9_Msk
#define GPIO_IFR_PIN10_Pos (10U)
#define GPIO_IFR_PIN10_Msk (0x1UL << GPIO_IFR_PIN10_Pos)
#define GPIO_IFR_PIN10 GPIO_IFR_PIN10_Msk
#define GPIO_IFR_PIN11_Pos (11U)
#define GPIO_IFR_PIN11_Msk (0x1UL << GPIO_IFR_PIN11_Pos)
#define GPIO_IFR_PIN11 GPIO_IFR_PIN11_Msk
#define GPIO_IFR_PIN12_Pos (12U)
#define GPIO_IFR_PIN12_Msk (0x1UL << GPIO_IFR_PIN12_Pos)
#define GPIO_IFR_PIN12 GPIO_IFR_PIN12_Msk
#define GPIO_IFR_PIN13_Pos (13U)
#define GPIO_IFR_PIN13_Msk (0x1UL << GPIO_IFR_PIN13_Pos)
#define GPIO_IFR_PIN13 GPIO_IFR_PIN13_Msk
#define GPIO_IFR_PIN14_Pos (14U)
#define GPIO_IFR_PIN14_Msk (0x1UL << GPIO_IFR_PIN14_Pos)
#define GPIO_IFR_PIN14 GPIO_IFR_PIN14_Msk
#define GPIO_IFR_PIN15_Pos (15U)
#define GPIO_IFR_PIN15_Msk (0x1UL << GPIO_IFR_PIN15_Pos)
#define GPIO_IFR_PIN15 GPIO_IFR_PIN15_Msk

// GPIO_ICR
#define GPIO_ICR_PIN0_Pos (0U)
#define GPIO_ICR_PIN0_Msk (0x1UL << GPIO_ICR_PIN0_Pos)
#define GPIO_ICR_PIN0 GPIO_ICR_PIN0_Msk
#define GPIO_ICR_PIN1_Pos (1U)
#define GPIO_ICR_PIN1_Msk (0x1UL << GPIO_ICR_PIN1_Pos)
#define GPIO_ICR_PIN1 GPIO_ICR_PIN1_Msk
#define GPIO_ICR_PIN2_Pos (2U)
#define GPIO_ICR_PIN2_Msk (0x1UL << GPIO_ICR_PIN2_Pos)
#define GPIO_ICR_PIN2 GPIO_ICR_PIN2_Msk
#define GPIO_ICR_PIN3_Pos (3U)
#define GPIO_ICR_PIN3_Msk (0x1UL << GPIO_ICR_PIN3_Pos)
#define GPIO_ICR_PIN3 GPIO_ICR_PIN3_Msk
#define GPIO_ICR_PIN4_Pos (4U)
#define GPIO_ICR_PIN4_Msk (0x1UL << GPIO_ICR_PIN4_Pos)
#define GPIO_ICR_PIN4 GPIO_ICR_PIN4_Msk
#define GPIO_ICR_PIN5_Pos (5U)
#define GPIO_ICR_PIN5_Msk (0x1UL << GPIO_ICR_PIN5_Pos)
#define GPIO_ICR_PIN5 GPIO_ICR_PIN5_Msk
#define GPIO_ICR_PIN6_Pos (6U)
#define GPIO_ICR_PIN6_Msk (0x1UL << GPIO_ICR_PIN6_Pos)
#define GPIO_ICR_PIN6 GPIO_ICR_PIN6_Msk
#define GPIO_ICR_PIN7_Pos (7U)
#define GPIO_ICR_PIN7_Msk (0x1UL << GPIO_ICR_PIN7_Pos)
#define GPIO_ICR_PIN7 GPIO_ICR_PIN7_Msk
#define GPIO_ICR_PIN8_Pos (8U)
#define GPIO_ICR_PIN8_Msk (0x1UL << GPIO_ICR_PIN8_Pos)
#define GPIO_ICR_PIN8 GPIO_ICR_PIN8_Msk
#define GPIO_ICR_PIN9_Pos (9U)
#define GPIO_ICR_PIN9_Msk (0x1UL << GPIO_ICR_PIN9_Pos)
#define GPIO_ICR_PIN9 GPIO_ICR_PIN9_Msk
#define GPIO_ICR_PIN10_Pos (10U)
#define GPIO_ICR_PIN10_Msk (0x1UL << GPIO_ICR_PIN10_Pos)
#define GPIO_ICR_PIN10 GPIO_ICR_PIN10_Msk
#define GPIO_ICR_PIN11_Pos (11U)
#define GPIO_ICR_PIN11_Msk (0x1UL << GPIO_ICR_PIN11_Pos)
#define GPIO_ICR_PIN11 GPIO_ICR_PIN11_Msk
#define GPIO_ICR_PIN12_Pos (12U)
#define GPIO_ICR_PIN12_Msk (0x1UL << GPIO_ICR_PIN12_Pos)
#define GPIO_ICR_PIN12 GPIO_ICR_PIN12_Msk
#define GPIO_ICR_PIN13_Pos (13U)
#define GPIO_ICR_PIN13_Msk (0x1UL << GPIO_ICR_PIN13_Pos)
#define GPIO_ICR_PIN13 GPIO_ICR_PIN13_Msk
#define GPIO_ICR_PIN14_Pos (14U)
#define GPIO_ICR_PIN14_Msk (0x1UL << GPIO_ICR_PIN14_Pos)
#define GPIO_ICR_PIN14 GPIO_ICR_PIN14_Msk
#define GPIO_ICR_PIN15_Pos (15U)
#define GPIO_ICR_PIN15_Msk (0x1UL << GPIO_ICR_PIN15_Pos)
#define GPIO_ICR_PIN15 GPIO_ICR_PIN15_Msk

//********************    Bits Define For Peripheral GPIOAUX    ********************//
// GPIOAUX_CR0
#define GPIOAUX_CR0_PCLKDIV_Pos (0U)
#define GPIOAUX_CR0_PCLKDIV_Msk (0x7UL << GPIOAUX_CR0_PCLKDIV_Pos)
#define GPIOAUX_CR0_PCLKDIV GPIOAUX_CR0_PCLKDIV_Msk
#define GPIOAUX_CR0_MCODIV_Pos (8U)
#define GPIOAUX_CR0_MCODIV_Msk (0x7UL << GPIOAUX_CR0_MCODIV_Pos)
#define GPIOAUX_CR0_MCODIV GPIOAUX_CR0_MCODIV_Msk
#define GPIOAUX_CR0_MCOSEL_Pos (12U)
#define GPIOAUX_CR0_MCOSEL_Msk (0x7UL << GPIOAUX_CR0_MCOSEL_Pos)
#define GPIOAUX_CR0_MCOSEL GPIOAUX_CR0_MCOSEL_Msk

// GPIOAUX_CR1
#define GPIOAUX_CR1_ATIM0ETR_Pos (0U)
#define GPIOAUX_CR1_ATIM0ETR_Msk (0x7UL << GPIOAUX_CR1_ATIM0ETR_Pos)
#define GPIOAUX_CR1_ATIM0ETR GPIOAUX_CR1_ATIM0ETR_Msk
#define GPIOAUX_CR1_CTIM0ETR_Pos (4U)
#define GPIOAUX_CR1_CTIM0ETR_Msk (0x7UL << GPIOAUX_CR1_CTIM0ETR_Pos)
#define GPIOAUX_CR1_CTIM0ETR GPIOAUX_CR1_CTIM0ETR_Msk
#define GPIOAUX_CR1_CTIM1ETR_Pos (8U)
#define GPIOAUX_CR1_CTIM1ETR_Msk (0x7UL << GPIOAUX_CR1_CTIM1ETR_Pos)
#define GPIOAUX_CR1_CTIM1ETR GPIOAUX_CR1_CTIM1ETR_Msk
#define GPIOAUX_CR1_ATIM3ETR_Pos (12U)
#define GPIOAUX_CR1_ATIM3ETR_Msk (0x7UL << GPIOAUX_CR1_ATIM3ETR_Pos)
#define GPIOAUX_CR1_ATIM3ETR GPIOAUX_CR1_ATIM3ETR_Msk

// GPIOAUX_CR2
#define GPIOAUX_CR2_ATIM0CAP0_Pos (0U)
#define GPIOAUX_CR2_ATIM0CAP0_Msk (0x7UL << GPIOAUX_CR2_ATIM0CAP0_Pos)
#define GPIOAUX_CR2_ATIM0CAP0 GPIOAUX_CR2_ATIM0CAP0_Msk
#define GPIOAUX_CR2_CTIM0CAP3_Pos (4U)
#define GPIOAUX_CR2_CTIM0CAP3_Msk (0x7UL << GPIOAUX_CR2_CTIM0CAP3_Pos)
#define GPIOAUX_CR2_CTIM0CAP3 GPIOAUX_CR2_CTIM0CAP3_Msk
#define GPIOAUX_CR2_CTIM1CAP3_Pos (8U)
#define GPIOAUX_CR2_CTIM1CAP3_Msk (0x7UL << GPIOAUX_CR2_CTIM1CAP3_Pos)
#define GPIOAUX_CR2_CTIM1CAP3 GPIOAUX_CR2_CTIM1CAP3_Msk
#define GPIOAUX_CR2_ATIM3CAP3_Pos (12U)
#define GPIOAUX_CR2_ATIM3CAP3_Msk (0x7UL << GPIOAUX_CR2_ATIM3CAP3_Pos)
#define GPIOAUX_CR2_ATIM3CAP3 GPIOAUX_CR2_ATIM3CAP3_Msk

//********************    Bits Define For Peripheral GTIM    ********************//
// GTIM_ARR
#define GTIM_ARR_ARR_Pos (0U)
#define GTIM_ARR_ARR_Msk (0xFFFFUL << GTIM_ARR_ARR_Pos)
#define GTIM_ARR_ARR GTIM_ARR_ARR_Msk

// GTIM_CNT
#define GTIM_CNT_CNT_Pos (0U)
#define GTIM_CNT_CNT_Msk (0xFFFFUL << GTIM_CNT_CNT_Pos)
#define GTIM_CNT_CNT GTIM_CNT_CNT_Msk

// GTIM_CMMR
#define GTIM_CMMR_CC0M_Pos (0U)
#define GTIM_CMMR_CC0M_Msk (0x7UL << GTIM_CMMR_CC0M_Pos)
#define GTIM_CMMR_CC0M GTIM_CMMR_CC0M_Msk
#define GTIM_CMMR_CC1M_Pos (4U)
#define GTIM_CMMR_CC1M_Msk (0x7UL << GTIM_CMMR_CC1M_Pos)
#define GTIM_CMMR_CC1M GTIM_CMMR_CC1M_Msk
#define GTIM_CMMR_CC2M_Pos (8U)
#define GTIM_CMMR_CC2M_Msk (0x7UL << GTIM_CMMR_CC2M_Pos)
#define GTIM_CMMR_CC2M GTIM_CMMR_CC2M_Msk
#define GTIM_CMMR_CC3M_Pos (12U)
#define GTIM_CMMR_CC3M_Msk (0x7UL << GTIM_CMMR_CC3M_Pos)
#define GTIM_CMMR_CC3M GTIM_CMMR_CC3M_Msk

// GTIM_CR1
#define GTIM_CR1_ETRFLT_Pos (4U)
#define GTIM_CR1_ETRFLT_Msk (0x7UL << GTIM_CR1_ETRFLT_Pos)
#define GTIM_CR1_ETRFLT GTIM_CR1_ETRFLT_Msk

// GTIM_CR0
#define GTIM_CR0_CEN_Pos (0U)
#define GTIM_CR0_CEN_Msk (0x1UL << GTIM_CR0_CEN_Pos)
#define GTIM_CR0_CEN GTIM_CR0_CEN_Msk
#define GTIM_CR0_MD_Pos (1U)
#define GTIM_CR0_MD_Msk (0x3UL << GTIM_CR0_MD_Pos)
#define GTIM_CR0_MD GTIM_CR0_MD_Msk
#define GTIM_CR0_TOGEN_Pos (3U)
#define GTIM_CR0_TOGEN_Msk (0x1UL << GTIM_CR0_TOGEN_Pos)
#define GTIM_CR0_TOGEN GTIM_CR0_TOGEN_Msk
#define GTIM_CR0_PRS_Pos (4U)
#define GTIM_CR0_PRS_Msk (0xFUL << GTIM_CR0_PRS_Pos)
#define GTIM_CR0_PRS GTIM_CR0_PRS_Msk
#define GTIM_CR0_OST_Pos (8U)
#define GTIM_CR0_OST_Msk (0x1UL << GTIM_CR0_OST_Pos)
#define GTIM_CR0_OST GTIM_CR0_OST_Msk
#define GTIM_CR0_TRS_Pos (9U)
#define GTIM_CR0_TRS_Msk (0x3UL << GTIM_CR0_TRS_Pos)
#define GTIM_CR0_TRS GTIM_CR0_TRS_Msk
#define GTIM_CR0_ETP_Pos (11U)
#define GTIM_CR0_ETP_Msk (0x1UL << GTIM_CR0_ETP_Pos)
#define GTIM_CR0_ETP GTIM_CR0_ETP_Msk

// GTIM_IER
#define GTIM_IER_UI_Pos (0U)
#define GTIM_IER_UI_Msk (0x1UL << GTIM_IER_UI_Pos)
#define GTIM_IER_UI GTIM_IER_UI_Msk
#define GTIM_IER_TI_Pos (1U)
#define GTIM_IER_TI_Msk (0x1UL << GTIM_IER_TI_Pos)
#define GTIM_IER_TI GTIM_IER_TI_Msk
#define GTIM_IER_CC0_Pos (2U)
#define GTIM_IER_CC0_Msk (0x1UL << GTIM_IER_CC0_Pos)
#define GTIM_IER_CC0 GTIM_IER_CC0_Msk
#define GTIM_IER_CC1_Pos (3U)
#define GTIM_IER_CC1_Msk (0x1UL << GTIM_IER_CC1_Pos)
#define GTIM_IER_CC1 GTIM_IER_CC1_Msk
#define GTIM_IER_CC2_Pos (4U)
#define GTIM_IER_CC2_Msk (0x1UL << GTIM_IER_CC2_Pos)
#define GTIM_IER_CC2 GTIM_IER_CC2_Msk
#define GTIM_IER_CC3_Pos (5U)
#define GTIM_IER_CC3_Msk (0x1UL << GTIM_IER_CC3_Pos)
#define GTIM_IER_CC3 GTIM_IER_CC3_Msk
#define GTIM_IER_DCC0_Pos (6U)
#define GTIM_IER_DCC0_Msk (0x1UL << GTIM_IER_DCC0_Pos)
#define GTIM_IER_DCC0 GTIM_IER_DCC0_Msk
#define GTIM_IER_DCC1_Pos (7U)
#define GTIM_IER_DCC1_Msk (0x1UL << GTIM_IER_DCC1_Pos)
#define GTIM_IER_DCC1 GTIM_IER_DCC1_Msk
#define GTIM_IER_DCC2_Pos (8U)
#define GTIM_IER_DCC2_Msk (0x1UL << GTIM_IER_DCC2_Pos)
#define GTIM_IER_DCC2 GTIM_IER_DCC2_Msk
#define GTIM_IER_DCC3_Pos (9U)
#define GTIM_IER_DCC3_Msk (0x1UL << GTIM_IER_DCC3_Pos)
#define GTIM_IER_DCC3 GTIM_IER_DCC3_Msk
#define GTIM_IER_OVTRAD_Pos (10U)
#define GTIM_IER_OVTRAD_Msk (0x1UL << GTIM_IER_OVTRAD_Pos)
#define GTIM_IER_OVTRAD GTIM_IER_OVTRAD_Msk
#define GTIM_IER_C0TRAD_Pos (11U)
#define GTIM_IER_C0TRAD_Msk (0x1UL << GTIM_IER_C0TRAD_Pos)
#define GTIM_IER_C0TRAD GTIM_IER_C0TRAD_Msk

// GTIM_IFR
#define GTIM_IFR_UI_Pos (0U)
#define GTIM_IFR_UI_Msk (0x1UL << GTIM_IFR_UI_Pos)
#define GTIM_IFR_UI GTIM_IFR_UI_Msk
#define GTIM_IFR_TI_Pos (1U)
#define GTIM_IFR_TI_Msk (0x1UL << GTIM_IFR_TI_Pos)
#define GTIM_IFR_TI GTIM_IFR_TI_Msk
#define GTIM_IFR_CC0_Pos (2U)
#define GTIM_IFR_CC0_Msk (0x1UL << GTIM_IFR_CC0_Pos)
#define GTIM_IFR_CC0 GTIM_IFR_CC0_Msk
#define GTIM_IFR_CC1_Pos (3U)
#define GTIM_IFR_CC1_Msk (0x1UL << GTIM_IFR_CC1_Pos)
#define GTIM_IFR_CC1 GTIM_IFR_CC1_Msk
#define GTIM_IFR_CC2_Pos (4U)
#define GTIM_IFR_CC2_Msk (0x1UL << GTIM_IFR_CC2_Pos)
#define GTIM_IFR_CC2 GTIM_IFR_CC2_Msk
#define GTIM_IFR_CC3_Pos (5U)
#define GTIM_IFR_CC3_Msk (0x1UL << GTIM_IFR_CC3_Pos)
#define GTIM_IFR_CC3 GTIM_IFR_CC3_Msk

// GTIM_ICR
#define GTIM_ICR_UI_Pos (0U)
#define GTIM_ICR_UI_Msk (0x1UL << GTIM_ICR_UI_Pos)
#define GTIM_ICR_UI GTIM_ICR_UI_Msk
#define GTIM_ICR_TI_Pos (1U)
#define GTIM_ICR_TI_Msk (0x1UL << GTIM_ICR_TI_Pos)
#define GTIM_ICR_TI GTIM_ICR_TI_Msk
#define GTIM_ICR_CC0_Pos (2U)
#define GTIM_ICR_CC0_Msk (0x1UL << GTIM_ICR_CC0_Pos)
#define GTIM_ICR_CC0 GTIM_ICR_CC0_Msk
#define GTIM_ICR_CC1_Pos (3U)
#define GTIM_ICR_CC1_Msk (0x1UL << GTIM_ICR_CC1_Pos)
#define GTIM_ICR_CC1 GTIM_ICR_CC1_Msk
#define GTIM_ICR_CC2_Pos (4U)
#define GTIM_ICR_CC2_Msk (0x1UL << GTIM_ICR_CC2_Pos)
#define GTIM_ICR_CC2 GTIM_ICR_CC2_Msk
#define GTIM_ICR_CC3_Pos (5U)
#define GTIM_ICR_CC3_Msk (0x1UL << GTIM_ICR_CC3_Pos)
#define GTIM_ICR_CC3 GTIM_ICR_CC3_Msk

// GTIM_CCR0
#define GTIM_CCR0_CCR_Pos (0U)
#define GTIM_CCR0_CCR_Msk (0xFFFFUL << GTIM_CCR0_CCR_Pos)
#define GTIM_CCR0_CCR GTIM_CCR0_CCR_Msk

// GTIM_CCR1
#define GTIM_CCR1_CCR_Pos (0U)
#define GTIM_CCR1_CCR_Msk (0xFFFFUL << GTIM_CCR1_CCR_Pos)
#define GTIM_CCR1_CCR GTIM_CCR1_CCR_Msk

// GTIM_CCR2
#define GTIM_CCR2_CCR_Pos (0U)
#define GTIM_CCR2_CCR_Msk (0xFFFFUL << GTIM_CCR2_CCR_Pos)
#define GTIM_CCR2_CCR GTIM_CCR2_CCR_Msk

// GTIM_CCR3
#define GTIM_CCR3_CCR_Pos (0U)
#define GTIM_CCR3_CCR_Msk (0xFFFFUL << GTIM_CCR3_CCR_Pos)
#define GTIM_CCR3_CCR GTIM_CCR3_CCR_Msk

//********************    Bits Define For Peripheral I2C    ********************//
// I2C_TMRUN
#define I2C_TMRUN_TME_Pos (0U)
#define I2C_TMRUN_TME_Msk (0x1UL << I2C_TMRUN_TME_Pos)
#define I2C_TMRUN_TME I2C_TMRUN_TME_Msk

// I2C_TM
#define I2C_TM_TM_Pos (0U)
#define I2C_TM_TM_Msk (0xFFUL << I2C_TM_TM_Pos)
#define I2C_TM_TM I2C_TM_TM_Msk

// I2C_CR
#define I2C_CR_H1M_Pos (0U)
#define I2C_CR_H1M_Msk (0x1UL << I2C_CR_H1M_Pos)
#define I2C_CR_H1M I2C_CR_H1M_Msk
#define I2C_CR_AA_Pos (2U)
#define I2C_CR_AA_Msk (0x1UL << I2C_CR_AA_Pos)
#define I2C_CR_AA I2C_CR_AA_Msk
#define I2C_CR_SI_Pos (3U)
#define I2C_CR_SI_Msk (0x1UL << I2C_CR_SI_Pos)
#define I2C_CR_SI I2C_CR_SI_Msk
#define I2C_CR_STO_Pos (4U)
#define I2C_CR_STO_Msk (0x1UL << I2C_CR_STO_Pos)
#define I2C_CR_STO I2C_CR_STO_Msk
#define I2C_CR_STA_Pos (5U)
#define I2C_CR_STA_Msk (0x1UL << I2C_CR_STA_Pos)
#define I2C_CR_STA I2C_CR_STA_Msk
#define I2C_CR_ENS_Pos (6U)
#define I2C_CR_ENS_Msk (0x1UL << I2C_CR_ENS_Pos)
#define I2C_CR_ENS I2C_CR_ENS_Msk

// I2C_DATA
#define I2C_DATA_DAT_Pos (0U)
#define I2C_DATA_DAT_Msk (0xFFUL << I2C_DATA_DAT_Pos)
#define I2C_DATA_DAT I2C_DATA_DAT_Msk

// I2C_ADDR0
#define I2C_ADDR0_GC_Pos (0U)
#define I2C_ADDR0_GC_Msk (0x1UL << I2C_ADDR0_GC_Pos)
#define I2C_ADDR0_GC I2C_ADDR0_GC_Msk
#define I2C_ADDR0_ADDR0_Pos (1U)
#define I2C_ADDR0_ADDR0_Msk (0x7FUL << I2C_ADDR0_ADDR0_Pos)
#define I2C_ADDR0_ADDR0 I2C_ADDR0_ADDR0_Msk

// I2C_STAT
#define I2C_STAT_STAT_Pos (0U)
#define I2C_STAT_STAT_Msk (0xFFUL << I2C_STAT_STAT_Pos)
#define I2C_STAT_STAT I2C_STAT_STAT_Msk

// I2C_ADDR1
#define I2C_ADDR1_ADDR_Pos (1U)
#define I2C_ADDR1_ADDR_Msk (0x7FUL << I2C_ADDR1_ADDR_Pos)
#define I2C_ADDR1_ADDR I2C_ADDR1_ADDR_Msk

// I2C_ADDR2
#define I2C_ADDR2_ADDR_Pos (1U)
#define I2C_ADDR2_ADDR_Msk (0x7FUL << I2C_ADDR2_ADDR_Pos)
#define I2C_ADDR2_ADDR I2C_ADDR2_ADDR_Msk

// I2C_MATCH
#define I2C_MATCH_AD0F_Pos (0U)
#define I2C_MATCH_AD0F_Msk (0x1UL << I2C_MATCH_AD0F_Pos)
#define I2C_MATCH_AD0F I2C_MATCH_AD0F_Msk
#define I2C_MATCH_AD1F_Pos (1U)
#define I2C_MATCH_AD1F_Msk (0x1UL << I2C_MATCH_AD1F_Pos)
#define I2C_MATCH_AD1F I2C_MATCH_AD1F_Msk
#define I2C_MATCH_AD2F_Pos (2U)
#define I2C_MATCH_AD2F_Msk (0x1UL << I2C_MATCH_AD2F_Pos)
#define I2C_MATCH_AD2F I2C_MATCH_AD2F_Msk

//********************    Bits Define For Peripheral I2CSLV    ********************//
// I2CSLV_SR
#define I2CSLV_SR_RD_Pos (0U)
#define I2CSLV_SR_RD_Msk (0x1UL << I2CSLV_SR_RD_Pos)
#define I2CSLV_SR_RD I2CSLV_SR_RD_Msk
#define I2CSLV_SR_WR_Pos (1U)
#define I2CSLV_SR_WR_Msk (0x1UL << I2CSLV_SR_WR_Pos)
#define I2CSLV_SR_WR I2CSLV_SR_WR_Msk
#define I2CSLV_SR_STOP_Pos (2U)
#define I2CSLV_SR_STOP_Msk (0x1UL << I2CSLV_SR_STOP_Pos)
#define I2CSLV_SR_STOP I2CSLV_SR_STOP_Msk
#define I2CSLV_SR_START_Pos (3U)
#define I2CSLV_SR_START_Msk (0x1UL << I2CSLV_SR_START_Pos)
#define I2CSLV_SR_START I2CSLV_SR_START_Msk
#define I2CSLV_SR_NACK_Pos (4U)
#define I2CSLV_SR_NACK_Msk (0x1UL << I2CSLV_SR_NACK_Pos)
#define I2CSLV_SR_NACK I2CSLV_SR_NACK_Msk
#define I2CSLV_SR_I2CINT_Pos (5U)
#define I2CSLV_SR_I2CINT_Msk (0x1UL << I2CSLV_SR_I2CINT_Pos)
#define I2CSLV_SR_I2CINT I2CSLV_SR_I2CINT_Msk
#define I2CSLV_SR_ACTIVE_Pos (6U)
#define I2CSLV_SR_ACTIVE_Msk (0x1UL << I2CSLV_SR_ACTIVE_Pos)
#define I2CSLV_SR_ACTIVE I2CSLV_SR_ACTIVE_Msk
#define I2CSLV_SR_HSMODE_Pos (7U)
#define I2CSLV_SR_HSMODE_Msk (0x1UL << I2CSLV_SR_HSMODE_Pos)
#define I2CSLV_SR_HSMODE I2CSLV_SR_HSMODE_Msk
#define I2CSLV_SR_TIMEOUT_Pos (8U)
#define I2CSLV_SR_TIMEOUT_Msk (0x1UL << I2CSLV_SR_TIMEOUT_Pos)
#define I2CSLV_SR_TIMEOUT I2CSLV_SR_TIMEOUT_Msk
#define I2CSLV_SR_ACK_Pos (9U)
#define I2CSLV_SR_ACK_Msk (0x1UL << I2CSLV_SR_ACK_Pos)
#define I2CSLV_SR_ACK I2CSLV_SR_ACK_Msk
#define I2CSLV_SR_SLADDR0_Pos (10U)
#define I2CSLV_SR_SLADDR0_Msk (0x1UL << I2CSLV_SR_SLADDR0_Pos)
#define I2CSLV_SR_SLADDR0 I2CSLV_SR_SLADDR0_Msk
#define I2CSLV_SR_SLADDR1_Pos (11U)
#define I2CSLV_SR_SLADDR1_Msk (0x1UL << I2CSLV_SR_SLADDR1_Pos)
#define I2CSLV_SR_SLADDR1 I2CSLV_SR_SLADDR1_Msk
#define I2CSLV_SR_SLADDR2_Pos (12U)
#define I2CSLV_SR_SLADDR2_Msk (0x1UL << I2CSLV_SR_SLADDR2_Pos)
#define I2CSLV_SR_SLADDR2 I2CSLV_SR_SLADDR2_Msk
#define I2CSLV_SR_SLADDR3_Pos (13U)
#define I2CSLV_SR_SLADDR3_Msk (0x1UL << I2CSLV_SR_SLADDR3_Pos)
#define I2CSLV_SR_SLADDR3 I2CSLV_SR_SLADDR3_Msk
#define I2CSLV_SR_TXE_Pos (14U)
#define I2CSLV_SR_TXE_Msk (0x1UL << I2CSLV_SR_TXE_Pos)
#define I2CSLV_SR_TXE I2CSLV_SR_TXE_Msk
#define I2CSLV_SR_RXNE_Pos (15U)
#define I2CSLV_SR_RXNE_Msk (0x1UL << I2CSLV_SR_RXNE_Pos)
#define I2CSLV_SR_RXNE I2CSLV_SR_RXNE_Msk
#define I2CSLV_SR_GC_Pos (16U)
#define I2CSLV_SR_GC_Msk (0x1UL << I2CSLV_SR_GC_Pos)
#define I2CSLV_SR_GC I2CSLV_SR_GC_Msk

// I2CSLV_DOUTR
#define I2CSLV_DOUTR_DOUT_Pos (0U)
#define I2CSLV_DOUTR_DOUT_Msk (0xFFUL << I2CSLV_DOUTR_DOUT_Pos)
#define I2CSLV_DOUTR_DOUT I2CSLV_DOUTR_DOUT_Msk

// I2CSLV_ADIR
#define I2CSLV_ADIR_ADIR_Pos (0U)
#define I2CSLV_ADIR_ADIR_Msk (0x3FFUL << I2CSLV_ADIR_ADIR_Pos)
#define I2CSLV_ADIR_ADIR I2CSLV_ADIR_ADIR_Msk
#define I2CSLV_ADIR_ADRLEN_Pos (10U)
#define I2CSLV_ADIR_ADRLEN_Msk (0x1UL << I2CSLV_ADIR_ADRLEN_Pos)
#define I2CSLV_ADIR_ADRLEN I2CSLV_ADIR_ADRLEN_Msk

// I2CSLV_SLADR0
#define I2CSLV_SLADR0_ADDR_Pos (0U)
#define I2CSLV_SLADR0_ADDR_Msk (0x3FFUL << I2CSLV_SLADR0_ADDR_Pos)
#define I2CSLV_SLADR0_ADDR I2CSLV_SLADR0_ADDR_Msk
#define I2CSLV_SLADR0_AM_Pos (10U)
#define I2CSLV_SLADR0_AM_Msk (0x1UL << I2CSLV_SLADR0_AM_Pos)
#define I2CSLV_SLADR0_AM I2CSLV_SLADR0_AM_Msk

// I2CSLV_SLADR1
#define I2CSLV_SLADR1_ADDR_Pos (0U)
#define I2CSLV_SLADR1_ADDR_Msk (0x3FFUL << I2CSLV_SLADR1_ADDR_Pos)
#define I2CSLV_SLADR1_ADDR I2CSLV_SLADR1_ADDR_Msk
#define I2CSLV_SLADR1_AM_Pos (10U)
#define I2CSLV_SLADR1_AM_Msk (0x1UL << I2CSLV_SLADR1_AM_Pos)
#define I2CSLV_SLADR1_AM I2CSLV_SLADR1_AM_Msk

// I2CSLV_SLADR2
#define I2CSLV_SLADR2_ADDR_Pos (0U)
#define I2CSLV_SLADR2_ADDR_Msk (0x3FFUL << I2CSLV_SLADR2_ADDR_Pos)
#define I2CSLV_SLADR2_ADDR I2CSLV_SLADR2_ADDR_Msk
#define I2CSLV_SLADR2_ADDRLEN_Pos (10U)
#define I2CSLV_SLADR2_ADDRLEN_Msk (0x1UL << I2CSLV_SLADR2_ADDRLEN_Pos)
#define I2CSLV_SLADR2_ADDRLEN I2CSLV_SLADR2_ADDRLEN_Msk

// I2CSLV_SLADR3
#define I2CSLV_SLADR3_ADDR_Pos (0U)
#define I2CSLV_SLADR3_ADDR_Msk (0x3FFUL << I2CSLV_SLADR3_ADDR_Pos)
#define I2CSLV_SLADR3_ADDR I2CSLV_SLADR3_ADDR_Msk
#define I2CSLV_SLADR3_ADDRLEN_Pos (10U)
#define I2CSLV_SLADR3_ADDRLEN_Msk (0x1UL << I2CSLV_SLADR3_ADDRLEN_Pos)
#define I2CSLV_SLADR3_ADDRLEN I2CSLV_SLADR3_ADDRLEN_Msk

// I2CSLV_DINR
#define I2CSLV_DINR_DIN_Pos (0U)
#define I2CSLV_DINR_DIN_Msk (0xFFUL << I2CSLV_DINR_DIN_Pos)
#define I2CSLV_DINR_DIN I2CSLV_DINR_DIN_Msk

// I2CSLV_CR
#define I2CSLV_CR_EN_Pos (0U)
#define I2CSLV_CR_EN_Msk (0x1UL << I2CSLV_CR_EN_Pos)
#define I2CSLV_CR_EN I2CSLV_CR_EN_Msk
#define I2CSLV_CR_BUSY_Pos (1U)
#define I2CSLV_CR_BUSY_Msk (0x1UL << I2CSLV_CR_BUSY_Pos)
#define I2CSLV_CR_BUSY I2CSLV_CR_BUSY_Msk
#define I2CSLV_CR_FSCLC_Pos (2U)
#define I2CSLV_CR_FSCLC_Msk (0x1UL << I2CSLV_CR_FSCLC_Pos)
#define I2CSLV_CR_FSCLC I2CSLV_CR_FSCLC_Msk
#define I2CSLV_CR_TIMEOUT_Pos (3U)
#define I2CSLV_CR_TIMEOUT_Msk (0x1UL << I2CSLV_CR_TIMEOUT_Pos)
#define I2CSLV_CR_TIMEOUT I2CSLV_CR_TIMEOUT_Msk
#define I2CSLV_CR_GC_Pos (7U)
#define I2CSLV_CR_GC_Msk (0x1UL << I2CSLV_CR_GC_Pos)
#define I2CSLV_CR_GC I2CSLV_CR_GC_Msk
#define I2CSLV_CR_DMATE_Pos (8U)
#define I2CSLV_CR_DMATE_Msk (0x1UL << I2CSLV_CR_DMATE_Pos)
#define I2CSLV_CR_DMATE I2CSLV_CR_DMATE_Msk
#define I2CSLV_CR_DMARE_Pos (9U)
#define I2CSLV_CR_DMARE_Msk (0x1UL << I2CSLV_CR_DMARE_Pos)
#define I2CSLV_CR_DMARE I2CSLV_CR_DMARE_Msk

// I2CSLV_ADMR0
#define I2CSLV_ADMR0_ADDRMASK_Pos (0U)
#define I2CSLV_ADMR0_ADDRMASK_Msk (0x3FFUL << I2CSLV_ADMR0_ADDRMASK_Pos)
#define I2CSLV_ADMR0_ADDRMASK I2CSLV_ADMR0_ADDRMASK_Msk
#define I2CSLV_ADMR0_FACS_Pos (10U)
#define I2CSLV_ADMR0_FACS_Msk (0x1UL << I2CSLV_ADMR0_FACS_Pos)
#define I2CSLV_ADMR0_FACS I2CSLV_ADMR0_FACS_Msk

// I2CSLV_FLT
#define I2CSLV_FLT_FW_Pos (0U)
#define I2CSLV_FLT_FW_Msk (0x7UL << I2CSLV_FLT_FW_Pos)
#define I2CSLV_FLT_FW I2CSLV_FLT_FW_Msk

// I2CSLV_TOR
#define I2CSLV_TOR_TOR_Pos (0U)
#define I2CSLV_TOR_TOR_Msk (0xFFFFUL << I2CSLV_TOR_TOR_Pos)
#define I2CSLV_TOR_TOR I2CSLV_TOR_TOR_Msk

// I2CSLV_ODDR
#define I2CSLV_ODDR_ODPU_Pos (0U)
#define I2CSLV_ODDR_ODPU_Msk (0x3UL << I2CSLV_ODDR_ODPU_Pos)
#define I2CSLV_ODDR_ODPU I2CSLV_ODDR_ODPU_Msk

// I2CSLV_RSR
#define I2CSLV_RSR_NS_Pos (0U)
#define I2CSLV_RSR_NS_Msk (0x3UL << I2CSLV_RSR_NS_Pos)
#define I2CSLV_RSR_NS I2CSLV_RSR_NS_Msk

// I2CSLV_IER
#define I2CSLV_IER_RD_Pos (0U)
#define I2CSLV_IER_RD_Msk (0x1UL << I2CSLV_IER_RD_Pos)
#define I2CSLV_IER_RD I2CSLV_IER_RD_Msk
#define I2CSLV_IER_WR_Pos (1U)
#define I2CSLV_IER_WR_Msk (0x1UL << I2CSLV_IER_WR_Pos)
#define I2CSLV_IER_WR I2CSLV_IER_WR_Msk
#define I2CSLV_IER_STOP_Pos (2U)
#define I2CSLV_IER_STOP_Msk (0x1UL << I2CSLV_IER_STOP_Pos)
#define I2CSLV_IER_STOP I2CSLV_IER_STOP_Msk
#define I2CSLV_IER_START_Pos (3U)
#define I2CSLV_IER_START_Msk (0x1UL << I2CSLV_IER_START_Pos)
#define I2CSLV_IER_START I2CSLV_IER_START_Msk
#define I2CSLV_IER_NACK_Pos (4U)
#define I2CSLV_IER_NACK_Msk (0x1UL << I2CSLV_IER_NACK_Pos)
#define I2CSLV_IER_NACK I2CSLV_IER_NACK_Msk
#define I2CSLV_IER_I2CINT_Pos (5U)
#define I2CSLV_IER_I2CINT_Msk (0x1UL << I2CSLV_IER_I2CINT_Pos)
#define I2CSLV_IER_I2CINT I2CSLV_IER_I2CINT_Msk
#define I2CSLV_IER_ACTIVE_Pos (6U)
#define I2CSLV_IER_ACTIVE_Msk (0x1UL << I2CSLV_IER_ACTIVE_Pos)
#define I2CSLV_IER_ACTIVE I2CSLV_IER_ACTIVE_Msk
#define I2CSLV_IER_HSMODE_Pos (7U)
#define I2CSLV_IER_HSMODE_Msk (0x1UL << I2CSLV_IER_HSMODE_Pos)
#define I2CSLV_IER_HSMODE I2CSLV_IER_HSMODE_Msk
#define I2CSLV_IER_TIMEOUT_Pos (8U)
#define I2CSLV_IER_TIMEOUT_Msk (0x1UL << I2CSLV_IER_TIMEOUT_Pos)
#define I2CSLV_IER_TIMEOUT I2CSLV_IER_TIMEOUT_Msk
#define I2CSLV_IER_ACK_Pos (9U)
#define I2CSLV_IER_ACK_Msk (0x1UL << I2CSLV_IER_ACK_Pos)
#define I2CSLV_IER_ACK I2CSLV_IER_ACK_Msk
#define I2CSLV_IER_SLADDR0_Pos (10U)
#define I2CSLV_IER_SLADDR0_Msk (0x1UL << I2CSLV_IER_SLADDR0_Pos)
#define I2CSLV_IER_SLADDR0 I2CSLV_IER_SLADDR0_Msk
#define I2CSLV_IER_SLADDR1_Pos (11U)
#define I2CSLV_IER_SLADDR1_Msk (0x1UL << I2CSLV_IER_SLADDR1_Pos)
#define I2CSLV_IER_SLADDR1 I2CSLV_IER_SLADDR1_Msk
#define I2CSLV_IER_SLADDR2_Pos (12U)
#define I2CSLV_IER_SLADDR2_Msk (0x1UL << I2CSLV_IER_SLADDR2_Pos)
#define I2CSLV_IER_SLADDR2 I2CSLV_IER_SLADDR2_Msk
#define I2CSLV_IER_SLADDR3_Pos (13U)
#define I2CSLV_IER_SLADDR3_Msk (0x1UL << I2CSLV_IER_SLADDR3_Pos)
#define I2CSLV_IER_SLADDR3 I2CSLV_IER_SLADDR3_Msk
#define I2CSLV_IER_TXE_Pos (14U)
#define I2CSLV_IER_TXE_Msk (0x1UL << I2CSLV_IER_TXE_Pos)
#define I2CSLV_IER_TXE I2CSLV_IER_TXE_Msk
#define I2CSLV_IER_RXNE_Pos (15U)
#define I2CSLV_IER_RXNE_Msk (0x1UL << I2CSLV_IER_RXNE_Pos)
#define I2CSLV_IER_RXNE I2CSLV_IER_RXNE_Msk
#define I2CSLV_IER_GC_Pos (16U)
#define I2CSLV_IER_GC_Msk (0x1UL << I2CSLV_IER_GC_Pos)
#define I2CSLV_IER_GC I2CSLV_IER_GC_Msk

// I2CSLV_ICR
#define I2CSLV_ICR_RD_Pos (0U)
#define I2CSLV_ICR_RD_Msk (0x1UL << I2CSLV_ICR_RD_Pos)
#define I2CSLV_ICR_RD I2CSLV_ICR_RD_Msk
#define I2CSLV_ICR_WR_Pos (1U)
#define I2CSLV_ICR_WR_Msk (0x1UL << I2CSLV_ICR_WR_Pos)
#define I2CSLV_ICR_WR I2CSLV_ICR_WR_Msk
#define I2CSLV_ICR_STOP_Pos (2U)
#define I2CSLV_ICR_STOP_Msk (0x1UL << I2CSLV_ICR_STOP_Pos)
#define I2CSLV_ICR_STOP I2CSLV_ICR_STOP_Msk
#define I2CSLV_ICR_START_Pos (3U)
#define I2CSLV_ICR_START_Msk (0x1UL << I2CSLV_ICR_START_Pos)
#define I2CSLV_ICR_START I2CSLV_ICR_START_Msk
#define I2CSLV_ICR_NACK_Pos (4U)
#define I2CSLV_ICR_NACK_Msk (0x1UL << I2CSLV_ICR_NACK_Pos)
#define I2CSLV_ICR_NACK I2CSLV_ICR_NACK_Msk
#define I2CSLV_ICR_I2CINT_Pos (5U)
#define I2CSLV_ICR_I2CINT_Msk (0x1UL << I2CSLV_ICR_I2CINT_Pos)
#define I2CSLV_ICR_I2CINT I2CSLV_ICR_I2CINT_Msk
#define I2CSLV_ICR_ACTIVE_Pos (6U)
#define I2CSLV_ICR_ACTIVE_Msk (0x1UL << I2CSLV_ICR_ACTIVE_Pos)
#define I2CSLV_ICR_ACTIVE I2CSLV_ICR_ACTIVE_Msk
#define I2CSLV_ICR_HSMODE_Pos (7U)
#define I2CSLV_ICR_HSMODE_Msk (0x1UL << I2CSLV_ICR_HSMODE_Pos)
#define I2CSLV_ICR_HSMODE I2CSLV_ICR_HSMODE_Msk
#define I2CSLV_ICR_TIMEOUT_Pos (8U)
#define I2CSLV_ICR_TIMEOUT_Msk (0x1UL << I2CSLV_ICR_TIMEOUT_Pos)
#define I2CSLV_ICR_TIMEOUT I2CSLV_ICR_TIMEOUT_Msk
#define I2CSLV_ICR_ACK_Pos (9U)
#define I2CSLV_ICR_ACK_Msk (0x1UL << I2CSLV_ICR_ACK_Pos)
#define I2CSLV_ICR_ACK I2CSLV_ICR_ACK_Msk
#define I2CSLV_ICR_SLADDR0_Pos (10U)
#define I2CSLV_ICR_SLADDR0_Msk (0x1UL << I2CSLV_ICR_SLADDR0_Pos)
#define I2CSLV_ICR_SLADDR0 I2CSLV_ICR_SLADDR0_Msk
#define I2CSLV_ICR_SLADDR1_Pos (11U)
#define I2CSLV_ICR_SLADDR1_Msk (0x1UL << I2CSLV_ICR_SLADDR1_Pos)
#define I2CSLV_ICR_SLADDR1 I2CSLV_ICR_SLADDR1_Msk
#define I2CSLV_ICR_SLADDR2_Pos (12U)
#define I2CSLV_ICR_SLADDR2_Msk (0x1UL << I2CSLV_ICR_SLADDR2_Pos)
#define I2CSLV_ICR_SLADDR2 I2CSLV_ICR_SLADDR2_Msk
#define I2CSLV_ICR_SLADDR3_Pos (13U)
#define I2CSLV_ICR_SLADDR3_Msk (0x1UL << I2CSLV_ICR_SLADDR3_Pos)
#define I2CSLV_ICR_SLADDR3 I2CSLV_ICR_SLADDR3_Msk
#define I2CSLV_ICR_TXE_Pos (14U)
#define I2CSLV_ICR_TXE_Msk (0x1UL << I2CSLV_ICR_TXE_Pos)
#define I2CSLV_ICR_TXE I2CSLV_ICR_TXE_Msk
#define I2CSLV_ICR_RXNE_Pos (15U)
#define I2CSLV_ICR_RXNE_Msk (0x1UL << I2CSLV_ICR_RXNE_Pos)
#define I2CSLV_ICR_RXNE I2CSLV_ICR_RXNE_Msk
#define I2CSLV_ICR_GC_Pos (16U)
#define I2CSLV_ICR_GC_Msk (0x1UL << I2CSLV_ICR_GC_Pos)
#define I2CSLV_ICR_GC I2CSLV_ICR_GC_Msk

// I2CSLV_DIDR
#define I2CSLV_DIDR_RID_Pos (0U)
#define I2CSLV_DIDR_RID_Msk (0x7UL << I2CSLV_DIDR_RID_Pos)
#define I2CSLV_DIDR_RID I2CSLV_DIDR_RID_Msk
#define I2CSLV_DIDR_PID_Pos (3U)
#define I2CSLV_DIDR_PID_Msk (0x1FFUL << I2CSLV_DIDR_PID_Pos)
#define I2CSLV_DIDR_PID I2CSLV_DIDR_PID_Msk
#define I2CSLV_DIDR_MID_Pos (12U)
#define I2CSLV_DIDR_MID_Msk (0xFFFUL << I2CSLV_DIDR_MID_Pos)
#define I2CSLV_DIDR_MID I2CSLV_DIDR_MID_Msk

//********************    Bits Define For Peripheral IWDT    ********************//
// IWDT_KR
#define IWDT_KR_KR_Pos (0U)
#define IWDT_KR_KR_Msk (0xFFFFUL << IWDT_KR_KR_Pos)
#define IWDT_KR_KR IWDT_KR_KR_Msk

// IWDT_CR
#define IWDT_CR_PRS_Pos (0U)
#define IWDT_CR_PRS_Msk (0x7UL << IWDT_CR_PRS_Pos)
#define IWDT_CR_PRS IWDT_CR_PRS_Msk
#define IWDT_CR_IE_Pos (4U)
#define IWDT_CR_IE_Msk (0x1UL << IWDT_CR_IE_Pos)
#define IWDT_CR_IE IWDT_CR_IE_Msk
#define IWDT_CR_ACTION_Pos (5U)
#define IWDT_CR_ACTION_Msk (0x1UL << IWDT_CR_ACTION_Pos)
#define IWDT_CR_ACTION IWDT_CR_ACTION_Msk
#define IWDT_CR_PAUSE_Pos (6U)
#define IWDT_CR_PAUSE_Msk (0x1UL << IWDT_CR_PAUSE_Pos)
#define IWDT_CR_PAUSE IWDT_CR_PAUSE_Msk

// IWDT_ARR
#define IWDT_ARR_ARR_Pos (0U)
#define IWDT_ARR_ARR_Msk (0xFFFUL << IWDT_ARR_ARR_Pos)
#define IWDT_ARR_ARR IWDT_ARR_ARR_Msk

// IWDT_SR
#define IWDT_SR_PRSF_Pos (0U)
#define IWDT_SR_PRSF_Msk (0x1UL << IWDT_SR_PRSF_Pos)
#define IWDT_SR_PRSF IWDT_SR_PRSF_Msk
#define IWDT_SR_ARRF_Pos (1U)
#define IWDT_SR_ARRF_Msk (0x1UL << IWDT_SR_ARRF_Pos)
#define IWDT_SR_ARRF IWDT_SR_ARRF_Msk
#define IWDT_SR_WINRF_Pos (2U)
#define IWDT_SR_WINRF_Msk (0x1UL << IWDT_SR_WINRF_Pos)
#define IWDT_SR_WINRF IWDT_SR_WINRF_Msk
#define IWDT_SR_OV_Pos (3U)
#define IWDT_SR_OV_Msk (0x1UL << IWDT_SR_OV_Pos)
#define IWDT_SR_OV IWDT_SR_OV_Msk
#define IWDT_SR_RUN_Pos (4U)
#define IWDT_SR_RUN_Msk (0x1UL << IWDT_SR_RUN_Pos)
#define IWDT_SR_RUN IWDT_SR_RUN_Msk

// IWDT_WINR
#define IWDT_WINR_WINR_Pos (0U)
#define IWDT_WINR_WINR_Msk (0xFFFUL << IWDT_WINR_WINR_Pos)
#define IWDT_WINR_WINR IWDT_WINR_WINR_Msk

//********************    Bits Define For Peripheral LPTIM    ********************//
// LPTIM_CNT
#define LPTIM_CNT_CNT_Pos (0U)
#define LPTIM_CNT_CNT_Msk (0xFFFFUL << LPTIM_CNT_CNT_Pos)
#define LPTIM_CNT_CNT LPTIM_CNT_CNT_Msk

// LPTIM_ARR
#define LPTIM_ARR_ARR_Pos (0U)
#define LPTIM_ARR_ARR_Msk (0xFFFFUL << LPTIM_ARR_ARR_Pos)
#define LPTIM_ARR_ARR LPTIM_ARR_ARR_Msk

// LPTIM_CR
#define LPTIM_CR_CEN_Pos (0U)
#define LPTIM_CR_CEN_Msk (0x1UL << LPTIM_CR_CEN_Pos)
#define LPTIM_CR_CEN LPTIM_CR_CEN_Msk
#define LPTIM_CR_MD_Pos (1U)
#define LPTIM_CR_MD_Msk (0x1UL << LPTIM_CR_MD_Pos)
#define LPTIM_CR_MD LPTIM_CR_MD_Msk
#define LPTIM_CR_CT_Pos (2U)
#define LPTIM_CR_CT_Msk (0x1UL << LPTIM_CR_CT_Pos)
#define LPTIM_CR_CT LPTIM_CR_CT_Msk
#define LPTIM_CR_TOG_EN_Pos (3U)
#define LPTIM_CR_TOG_EN_Msk (0x1UL << LPTIM_CR_TOG_EN_Pos)
#define LPTIM_CR_TOG_EN LPTIM_CR_TOG_EN_Msk
#define LPTIM_CR_TCK_SEL_Pos (4U)
#define LPTIM_CR_TCK_SEL_Msk (0x3UL << LPTIM_CR_TCK_SEL_Pos)
#define LPTIM_CR_TCK_SEL LPTIM_CR_TCK_SEL_Msk
#define LPTIM_CR_WT_FLAG_Pos (7U)
#define LPTIM_CR_WT_FLAG_Msk (0x1UL << LPTIM_CR_WT_FLAG_Pos)
#define LPTIM_CR_WT_FLAG LPTIM_CR_WT_FLAG_Msk
#define LPTIM_CR_GATE_Pos (8U)
#define LPTIM_CR_GATE_Msk (0x1UL << LPTIM_CR_GATE_Pos)
#define LPTIM_CR_GATE LPTIM_CR_GATE_Msk
#define LPTIM_CR_GATE_P_Pos (9U)
#define LPTIM_CR_GATE_P_Msk (0x1UL << LPTIM_CR_GATE_P_Pos)
#define LPTIM_CR_GATE_P LPTIM_CR_GATE_P_Msk
#define LPTIM_CR_IE_Pos (10U)
#define LPTIM_CR_IE_Msk (0x1UL << LPTIM_CR_IE_Pos)
#define LPTIM_CR_IE LPTIM_CR_IE_Msk
#define LPTIM_CR_PRS_Pos (11U)
#define LPTIM_CR_PRS_Msk (0xFUL << LPTIM_CR_PRS_Pos)
#define LPTIM_CR_PRS LPTIM_CR_PRS_Msk

// LPTIM_IFR
#define LPTIM_IFR_OV_Pos (0U)
#define LPTIM_IFR_OV_Msk (0x1UL << LPTIM_IFR_OV_Pos)
#define LPTIM_IFR_OV LPTIM_IFR_OV_Msk

// LPTIM_ICLR
#define LPTIM_ICLR_OV_Pos (0U)
#define LPTIM_ICLR_OV_Msk (0x1UL << LPTIM_ICLR_OV_Pos)
#define LPTIM_ICLR_OV LPTIM_ICLR_OV_Msk

//********************    Bits Define For Peripheral LPUART    ********************//
// LPUART_SBUF
#define LPUART_SBUF_DATA_Pos (0U)
#define LPUART_SBUF_DATA_Msk (0xFFUL << LPUART_SBUF_DATA_Pos)
#define LPUART_SBUF_DATA LPUART_SBUF_DATA_Msk
#define LPUART_SBUF_DR8_Pos (8U)
#define LPUART_SBUF_DR8_Msk (0x1UL << LPUART_SBUF_DR8_Pos)
#define LPUART_SBUF_DR8 LPUART_SBUF_DR8_Msk

// LPUART_SCON
#define LPUART_SCON_RCIE_Pos (0U)
#define LPUART_SCON_RCIE_Msk (0x1UL << LPUART_SCON_RCIE_Pos)
#define LPUART_SCON_RCIE LPUART_SCON_RCIE_Msk
#define LPUART_SCON_TCIE_Pos (1U)
#define LPUART_SCON_TCIE_Msk (0x1UL << LPUART_SCON_TCIE_Pos)
#define LPUART_SCON_TCIE LPUART_SCON_TCIE_Msk
#define LPUART_SCON_DR8CFG_Pos (2U)
#define LPUART_SCON_DR8CFG_Msk (0x3UL << LPUART_SCON_DR8CFG_Pos)
#define LPUART_SCON_DR8CFG LPUART_SCON_DR8CFG_Msk
#define LPUART_SCON_RXEN_Pos (4U)
#define LPUART_SCON_RXEN_Msk (0x1UL << LPUART_SCON_RXEN_Pos)
#define LPUART_SCON_RXEN LPUART_SCON_RXEN_Msk
#define LPUART_SCON_ADRDET_Pos (5U)
#define LPUART_SCON_ADRDET_Msk (0x1UL << LPUART_SCON_ADRDET_Pos)
#define LPUART_SCON_ADRDET LPUART_SCON_ADRDET_Msk
#define LPUART_SCON_MODE_Pos (6U)
#define LPUART_SCON_MODE_Msk (0x3UL << LPUART_SCON_MODE_Pos)
#define LPUART_SCON_MODE LPUART_SCON_MODE_Msk
#define LPUART_SCON_TXEIE_Pos (8U)
#define LPUART_SCON_TXEIE_Msk (0x1UL << LPUART_SCON_TXEIE_Pos)
#define LPUART_SCON_TXEIE LPUART_SCON_TXEIE_Msk
#define LPUART_SCON_OVER_Pos (9U)
#define LPUART_SCON_OVER_Msk (0x3UL << LPUART_SCON_OVER_Pos)
#define LPUART_SCON_OVER LPUART_SCON_OVER_Msk
#define LPUART_SCON_CLKSRC_Pos (11U)
#define LPUART_SCON_CLKSRC_Msk (0x3UL << LPUART_SCON_CLKSRC_Pos)
#define LPUART_SCON_CLKSRC LPUART_SCON_CLKSRC_Msk
#define LPUART_SCON_PEIE_Pos (13U)
#define LPUART_SCON_PEIE_Msk (0x1UL << LPUART_SCON_PEIE_Pos)
#define LPUART_SCON_PEIE LPUART_SCON_PEIE_Msk
#define LPUART_SCON_STOP_Pos (14U)
#define LPUART_SCON_STOP_Msk (0x3UL << LPUART_SCON_STOP_Pos)
#define LPUART_SCON_STOP LPUART_SCON_STOP_Msk
#define LPUART_SCON_DMARXEN_Pos (16U)
#define LPUART_SCON_DMARXEN_Msk (0x1UL << LPUART_SCON_DMARXEN_Pos)
#define LPUART_SCON_DMARXEN LPUART_SCON_DMARXEN_Msk
#define LPUART_SCON_DMATXEN_Pos (17U)
#define LPUART_SCON_DMATXEN_Msk (0x1UL << LPUART_SCON_DMATXEN_Pos)
#define LPUART_SCON_DMATXEN LPUART_SCON_DMATXEN_Msk
#define LPUART_SCON_RTSEN_Pos (18U)
#define LPUART_SCON_RTSEN_Msk (0x1UL << LPUART_SCON_RTSEN_Pos)
#define LPUART_SCON_RTSEN LPUART_SCON_RTSEN_Msk
#define LPUART_SCON_CTSEN_Pos (19U)
#define LPUART_SCON_CTSEN_Msk (0x1UL << LPUART_SCON_CTSEN_Pos)
#define LPUART_SCON_CTSEN LPUART_SCON_CTSEN_Msk
#define LPUART_SCON_CTSIE_Pos (20U)
#define LPUART_SCON_CTSIE_Msk (0x1UL << LPUART_SCON_CTSIE_Pos)
#define LPUART_SCON_CTSIE LPUART_SCON_CTSIE_Msk
#define LPUART_SCON_FEIE_Pos (21U)
#define LPUART_SCON_FEIE_Msk (0x1UL << LPUART_SCON_FEIE_Pos)
#define LPUART_SCON_FEIE LPUART_SCON_FEIE_Msk
#define LPUART_SCON_HDSEL_Pos (22U)
#define LPUART_SCON_HDSEL_Msk (0x1UL << LPUART_SCON_HDSEL_Pos)
#define LPUART_SCON_HDSEL LPUART_SCON_HDSEL_Msk

// LPUART_SADDR
#define LPUART_SADDR_ADDR_Pos (0U)
#define LPUART_SADDR_ADDR_Msk (0xFFUL << LPUART_SADDR_ADDR_Pos)
#define LPUART_SADDR_ADDR LPUART_SADDR_ADDR_Msk

// LPUART_SADEN
#define LPUART_SADEN_SADEN_Pos (0U)
#define LPUART_SADEN_SADEN_Msk (0xFFUL << LPUART_SADEN_SADEN_Pos)
#define LPUART_SADEN_SADEN LPUART_SADEN_SADEN_Msk

// LPUART_ISR
#define LPUART_ISR_RC_Pos (0U)
#define LPUART_ISR_RC_Msk (0x1UL << LPUART_ISR_RC_Pos)
#define LPUART_ISR_RC LPUART_ISR_RC_Msk
#define LPUART_ISR_TC_Pos (1U)
#define LPUART_ISR_TC_Msk (0x1UL << LPUART_ISR_TC_Pos)
#define LPUART_ISR_TC LPUART_ISR_TC_Msk
#define LPUART_ISR_FE_Pos (2U)
#define LPUART_ISR_FE_Msk (0x1UL << LPUART_ISR_FE_Pos)
#define LPUART_ISR_FE LPUART_ISR_FE_Msk
#define LPUART_ISR_TXE_Pos (3U)
#define LPUART_ISR_TXE_Msk (0x1UL << LPUART_ISR_TXE_Pos)
#define LPUART_ISR_TXE LPUART_ISR_TXE_Msk
#define LPUART_ISR_PE_Pos (4U)
#define LPUART_ISR_PE_Msk (0x1UL << LPUART_ISR_PE_Pos)
#define LPUART_ISR_PE LPUART_ISR_PE_Msk
#define LPUART_ISR_CTSIF_Pos (5U)
#define LPUART_ISR_CTSIF_Msk (0x1UL << LPUART_ISR_CTSIF_Pos)
#define LPUART_ISR_CTSIF LPUART_ISR_CTSIF_Msk
#define LPUART_ISR_CTS_Pos (6U)
#define LPUART_ISR_CTS_Msk (0x1UL << LPUART_ISR_CTS_Pos)
#define LPUART_ISR_CTS LPUART_ISR_CTS_Msk

// LPUART_ICR
#define LPUART_ICR_RC_Pos (0U)
#define LPUART_ICR_RC_Msk (0x1UL << LPUART_ICR_RC_Pos)
#define LPUART_ICR_RC LPUART_ICR_RC_Msk
#define LPUART_ICR_TC_Pos (1U)
#define LPUART_ICR_TC_Msk (0x1UL << LPUART_ICR_TC_Pos)
#define LPUART_ICR_TC LPUART_ICR_TC_Msk
#define LPUART_ICR_FE_Pos (2U)
#define LPUART_ICR_FE_Msk (0x1UL << LPUART_ICR_FE_Pos)
#define LPUART_ICR_FE LPUART_ICR_FE_Msk
#define LPUART_ICR_PE_Pos (4U)
#define LPUART_ICR_PE_Msk (0x1UL << LPUART_ICR_PE_Pos)
#define LPUART_ICR_PE LPUART_ICR_PE_Msk
#define LPUART_ICR_CTSIF_Pos (5U)
#define LPUART_ICR_CTSIF_Msk (0x1UL << LPUART_ICR_CTSIF_Pos)
#define LPUART_ICR_CTSIF LPUART_ICR_CTSIF_Msk

// LPUART_SCNT
#define LPUART_SCNT_SCNT_Pos (0U)
#define LPUART_SCNT_SCNT_Msk (0xFFFFUL << LPUART_SCNT_SCNT_Pos)
#define LPUART_SCNT_SCNT LPUART_SCNT_SCNT_Msk

//********************    Bits Define For Peripheral LVD    ********************//
// LVD_CR
#define LVD_CR_LVDEN_Pos (0U)
#define LVD_CR_LVDEN_Msk (0x1UL << LVD_CR_LVDEN_Pos)
#define LVD_CR_LVDEN LVD_CR_LVDEN_Msk
#define LVD_CR_ACT_Pos (1U)
#define LVD_CR_ACT_Msk (0x1UL << LVD_CR_ACT_Pos)
#define LVD_CR_ACT LVD_CR_ACT_Msk
#define LVD_CR_SOURCE_Pos (2U)
#define LVD_CR_SOURCE_Msk (0x3UL << LVD_CR_SOURCE_Pos)
#define LVD_CR_SOURCE LVD_CR_SOURCE_Msk
#define LVD_CR_VTDS_Pos (4U)
#define LVD_CR_VTDS_Msk (0xFUL << LVD_CR_VTDS_Pos)
#define LVD_CR_VTDS LVD_CR_VTDS_Msk
#define LVD_CR_FLTEN_Pos (8U)
#define LVD_CR_FLTEN_Msk (0x1UL << LVD_CR_FLTEN_Pos)
#define LVD_CR_FLTEN LVD_CR_FLTEN_Msk
#define LVD_CR_DEBOUNCETIME_Pos (9U)
#define LVD_CR_DEBOUNCETIME_Msk (0x7UL << LVD_CR_DEBOUNCETIME_Pos)
#define LVD_CR_DEBOUNCETIME LVD_CR_DEBOUNCETIME_Msk
#define LVD_CR_FTEN_Pos (12U)
#define LVD_CR_FTEN_Msk (0x1UL << LVD_CR_FTEN_Pos)
#define LVD_CR_FTEN LVD_CR_FTEN_Msk
#define LVD_CR_RTEN_Pos (13U)
#define LVD_CR_RTEN_Msk (0x1UL << LVD_CR_RTEN_Pos)
#define LVD_CR_RTEN LVD_CR_RTEN_Msk
#define LVD_CR_HTEN_Pos (14U)
#define LVD_CR_HTEN_Msk (0x1UL << LVD_CR_HTEN_Pos)
#define LVD_CR_HTEN LVD_CR_HTEN_Msk
#define LVD_CR_IE_Pos (15U)
#define LVD_CR_IE_Msk (0x1UL << LVD_CR_IE_Pos)
#define LVD_CR_IE LVD_CR_IE_Msk

// LVD_SR
#define LVD_SR_INTF_Pos (0U)
#define LVD_SR_INTF_Msk (0x1UL << LVD_SR_INTF_Pos)
#define LVD_SR_INTF LVD_SR_INTF_Msk
#define LVD_SR_FILTER_Pos (1U)
#define LVD_SR_FILTER_Msk (0x1UL << LVD_SR_FILTER_Pos)
#define LVD_SR_FILTER LVD_SR_FILTER_Msk

//********************    Bits Define For Peripheral OPA    ********************//
// OPA_CR0
#define OPA_CR0_OPAEN_Pos (0U)
#define OPA_CR0_OPAEN_Msk (0x1UL << OPA_CR0_OPAEN_Pos)
#define OPA_CR0_OPAEN OPA_CR0_OPAEN_Msk
#define OPA_CR0_AZEN_Pos (1U)
#define OPA_CR0_AZEN_Msk (0x1UL << OPA_CR0_AZEN_Pos)
#define OPA_CR0_AZEN OPA_CR0_AZEN_Msk
#define OPA_CR0_BIASSEL_Pos (7U)
#define OPA_CR0_BIASSEL_Msk (0x7UL << OPA_CR0_BIASSEL_Pos)
#define OPA_CR0_BIASSEL OPA_CR0_BIASSEL_Msk

// OPA_CR1
#define OPA_CR1_OPAEN_Pos (0U)
#define OPA_CR1_OPAEN_Msk (0x1UL << OPA_CR1_OPAEN_Pos)
#define OPA_CR1_OPAEN OPA_CR1_OPAEN_Msk
#define OPA_CR1_AZEN_Pos (1U)
#define OPA_CR1_AZEN_Msk (0x1UL << OPA_CR1_AZEN_Pos)
#define OPA_CR1_AZEN OPA_CR1_AZEN_Msk
#define OPA_CR1_BIASSEL_Pos (7U)
#define OPA_CR1_BIASSEL_Msk (0x7UL << OPA_CR1_BIASSEL_Pos)
#define OPA_CR1_BIASSEL OPA_CR1_BIASSEL_Msk

// OPA_AZ
#define OPA_AZ_ADCTREN_Pos (0U)
#define OPA_AZ_ADCTREN_Msk (0x1UL << OPA_AZ_ADCTREN_Pos)
#define OPA_AZ_ADCTREN OPA_AZ_ADCTREN_Msk
#define OPA_AZ_TRIGGER_Pos (1U)
#define OPA_AZ_TRIGGER_Msk (0x1UL << OPA_AZ_TRIGGER_Pos)
#define OPA_AZ_TRIGGER OPA_AZ_TRIGGER_Msk
#define OPA_AZ_AZPULSE_Pos (2U)
#define OPA_AZ_AZPULSE_Msk (0x1UL << OPA_AZ_AZPULSE_Pos)
#define OPA_AZ_AZPULSE OPA_AZ_AZPULSE_Msk
#define OPA_AZ_CLKSWSET_Pos (3U)
#define OPA_AZ_CLKSWSET_Msk (0x1UL << OPA_AZ_CLKSWSET_Pos)
#define OPA_AZ_CLKSWSET OPA_AZ_CLKSWSET_Msk
#define OPA_AZ_CLKSEL_Pos (4U)
#define OPA_AZ_CLKSEL_Msk (0xFUL << OPA_AZ_CLKSEL_Pos)
#define OPA_AZ_CLKSEL OPA_AZ_CLKSEL_Msk

//********************    Bits Define For Peripheral RAM    ********************//
// RAM_CR
#define RAM_CR_IE_Pos (1U)
#define RAM_CR_IE_Msk (0x1UL << RAM_CR_IE_Pos)
#define RAM_CR_IE RAM_CR_IE_Msk

// RAM_ERRADDR
#define RAM_ERRADDR_ERRADDR_Pos (0U)
#define RAM_ERRADDR_ERRADDR_Msk (0x3FFFUL << RAM_ERRADDR_ERRADDR_Pos)
#define RAM_ERRADDR_ERRADDR RAM_ERRADDR_ERRADDR_Msk

// RAM_IFR
#define RAM_IFR_ERR_Pos (0U)
#define RAM_IFR_ERR_Msk (0x1UL << RAM_IFR_ERR_Pos)
#define RAM_IFR_ERR RAM_IFR_ERR_Msk

// RAM_ICLR
#define RAM_ICLR_ERRCLR_Pos (0U)
#define RAM_ICLR_ERRCLR_Msk (0x1UL << RAM_ICLR_ERRCLR_Pos)
#define RAM_ICLR_ERRCLR RAM_ICLR_ERRCLR_Msk

//********************    Bits Define For Peripheral RTC    ********************//
// RTC_CR0
#define RTC_CR0_PRDS_Pos (0U)
#define RTC_CR0_PRDS_Msk (0x7UL << RTC_CR0_PRDS_Pos)
#define RTC_CR0_PRDS RTC_CR0_PRDS_Msk
#define RTC_CR0_AMPM_Pos (3U)
#define RTC_CR0_AMPM_Msk (0x1UL << RTC_CR0_AMPM_Pos)
#define RTC_CR0_AMPM RTC_CR0_AMPM_Msk
#define RTC_CR0_HZ1OE_Pos (5U)
#define RTC_CR0_HZ1OE_Msk (0x1UL << RTC_CR0_HZ1OE_Pos)
#define RTC_CR0_HZ1OE RTC_CR0_HZ1OE_Msk
#define RTC_CR0_HZ1SEL_Pos (6U)
#define RTC_CR0_HZ1SEL_Msk (0x1UL << RTC_CR0_HZ1SEL_Pos)
#define RTC_CR0_HZ1SEL RTC_CR0_HZ1SEL_Msk
#define RTC_CR0_START_Pos (7U)
#define RTC_CR0_START_Msk (0x1UL << RTC_CR0_START_Pos)
#define RTC_CR0_START RTC_CR0_START_Msk
#define RTC_CR0_PRDX_Pos (8U)
#define RTC_CR0_PRDX_Msk (0x3FUL << RTC_CR0_PRDX_Pos)
#define RTC_CR0_PRDX RTC_CR0_PRDX_Msk
#define RTC_CR0_PRDSEL_Pos (14U)
#define RTC_CR0_PRDSEL_Msk (0x1UL << RTC_CR0_PRDSEL_Pos)
#define RTC_CR0_PRDSEL RTC_CR0_PRDSEL_Msk
#define RTC_CR0_TEST_Pos (15U)
#define RTC_CR0_TEST_Msk (0x1UL << RTC_CR0_TEST_Pos)
#define RTC_CR0_TEST RTC_CR0_TEST_Msk

// RTC_CR1
#define RTC_CR1_WAIT_Pos (0U)
#define RTC_CR1_WAIT_Msk (0x1UL << RTC_CR1_WAIT_Pos)
#define RTC_CR1_WAIT RTC_CR1_WAIT_Msk
#define RTC_CR1_WAITF_Pos (1U)
#define RTC_CR1_WAITF_Msk (0x1UL << RTC_CR1_WAITF_Pos)
#define RTC_CR1_WAITF RTC_CR1_WAITF_Msk
#define RTC_CR1_CKSEL_Pos (8U)
#define RTC_CR1_CKSEL_Msk (0x7UL << RTC_CR1_CKSEL_Pos)
#define RTC_CR1_CKSEL RTC_CR1_CKSEL_Msk

// RTC_SEC
#define RTC_SEC_SECL_Pos (0U)
#define RTC_SEC_SECL_Msk (0xFUL << RTC_SEC_SECL_Pos)
#define RTC_SEC_SECL RTC_SEC_SECL_Msk
#define RTC_SEC_SECH_Pos (4U)
#define RTC_SEC_SECH_Msk (0x7UL << RTC_SEC_SECH_Pos)
#define RTC_SEC_SECH RTC_SEC_SECH_Msk

// RTC_MIN
#define RTC_MIN_MINL_Pos (0U)
#define RTC_MIN_MINL_Msk (0xFUL << RTC_MIN_MINL_Pos)
#define RTC_MIN_MINL RTC_MIN_MINL_Msk
#define RTC_MIN_MINH_Pos (4U)
#define RTC_MIN_MINH_Msk (0x7UL << RTC_MIN_MINH_Pos)
#define RTC_MIN_MINH RTC_MIN_MINH_Msk

// RTC_HOUR
#define RTC_HOUR_HOURL_Pos (0U)
#define RTC_HOUR_HOURL_Msk (0xFUL << RTC_HOUR_HOURL_Pos)
#define RTC_HOUR_HOURL RTC_HOUR_HOURL_Msk
#define RTC_HOUR_HOURH_Pos (4U)
#define RTC_HOUR_HOURH_Msk (0x3UL << RTC_HOUR_HOURH_Pos)
#define RTC_HOUR_HOURH RTC_HOUR_HOURH_Msk

// RTC_WEEK
#define RTC_WEEK_WEEK_Pos (0U)
#define RTC_WEEK_WEEK_Msk (0x7UL << RTC_WEEK_WEEK_Pos)
#define RTC_WEEK_WEEK RTC_WEEK_WEEK_Msk

// RTC_DAY
#define RTC_DAY_DAYL_Pos (0U)
#define RTC_DAY_DAYL_Msk (0xFUL << RTC_DAY_DAYL_Pos)
#define RTC_DAY_DAYL RTC_DAY_DAYL_Msk
#define RTC_DAY_DAYH_Pos (4U)
#define RTC_DAY_DAYH_Msk (0x3UL << RTC_DAY_DAYH_Pos)
#define RTC_DAY_DAYH RTC_DAY_DAYH_Msk

// RTC_MON
#define RTC_MON_MON_Pos (0U)
#define RTC_MON_MON_Msk (0x1FUL << RTC_MON_MON_Pos)
#define RTC_MON_MON RTC_MON_MON_Msk

// RTC_YEAR
#define RTC_YEAR_YEARL_Pos (0U)
#define RTC_YEAR_YEARL_Msk (0xFUL << RTC_YEAR_YEARL_Pos)
#define RTC_YEAR_YEARL RTC_YEAR_YEARL_Msk
#define RTC_YEAR_YEARH_Pos (4U)
#define RTC_YEAR_YEARH_Msk (0xFUL << RTC_YEAR_YEARH_Pos)
#define RTC_YEAR_YEARH RTC_YEAR_YEARH_Msk

// RTC_COMPEN
#define RTC_COMPEN_CR_Pos (0U)
#define RTC_COMPEN_CR_Msk (0x1FFUL << RTC_COMPEN_CR_Pos)
#define RTC_COMPEN_CR RTC_COMPEN_CR_Msk
#define RTC_COMPEN_EN_Pos (15U)
#define RTC_COMPEN_EN_Msk (0x1UL << RTC_COMPEN_EN_Pos)
#define RTC_COMPEN_EN RTC_COMPEN_EN_Msk

// RTC_CR2
#define RTC_CR2_WUCKSEL_Pos (0U)
#define RTC_CR2_WUCKSEL_Msk (0x7UL << RTC_CR2_WUCKSEL_Pos)
#define RTC_CR2_WUCKSEL RTC_CR2_WUCKSEL_Msk
#define RTC_CR2_TSEDG_Pos (3U)
#define RTC_CR2_TSEDG_Msk (0x1UL << RTC_CR2_TSEDG_Pos)
#define RTC_CR2_TSEDG RTC_CR2_TSEDG_Msk
#define RTC_CR2_O2SEL_Pos (4U)
#define RTC_CR2_O2SEL_Msk (0x3UL << RTC_CR2_O2SEL_Pos)
#define RTC_CR2_O2SEL RTC_CR2_O2SEL_Msk
#define RTC_CR2_TSE_Pos (6U)
#define RTC_CR2_TSE_Msk (0x1UL << RTC_CR2_TSE_Pos)
#define RTC_CR2_TSE RTC_CR2_TSE_Msk
#define RTC_CR2_WUTE_Pos (7U)
#define RTC_CR2_WUTE_Msk (0x1UL << RTC_CR2_WUTE_Pos)
#define RTC_CR2_WUTE RTC_CR2_WUTE_Msk
#define RTC_CR2_ALMAE_Pos (9U)
#define RTC_CR2_ALMAE_Msk (0x1UL << RTC_CR2_ALMAE_Pos)
#define RTC_CR2_ALMAE RTC_CR2_ALMAE_Msk
#define RTC_CR2_ALMBE_Pos (10U)
#define RTC_CR2_ALMBE_Msk (0x1UL << RTC_CR2_ALMBE_Pos)
#define RTC_CR2_ALMBE RTC_CR2_ALMBE_Msk

// RTC_ALMA
#define RTC_ALMA_SECL_Pos (0U)
#define RTC_ALMA_SECL_Msk (0xFUL << RTC_ALMA_SECL_Pos)
#define RTC_ALMA_SECL RTC_ALMA_SECL_Msk
#define RTC_ALMA_SECH_Pos (4U)
#define RTC_ALMA_SECH_Msk (0x7UL << RTC_ALMA_SECH_Pos)
#define RTC_ALMA_SECH RTC_ALMA_SECH_Msk
#define RTC_ALMA_MSKS_Pos (7U)
#define RTC_ALMA_MSKS_Msk (0x1UL << RTC_ALMA_MSKS_Pos)
#define RTC_ALMA_MSKS RTC_ALMA_MSKS_Msk
#define RTC_ALMA_MINL_Pos (8U)
#define RTC_ALMA_MINL_Msk (0xFUL << RTC_ALMA_MINL_Pos)
#define RTC_ALMA_MINL RTC_ALMA_MINL_Msk
#define RTC_ALMA_MINH_Pos (12U)
#define RTC_ALMA_MINH_Msk (0x7UL << RTC_ALMA_MINH_Pos)
#define RTC_ALMA_MINH RTC_ALMA_MINH_Msk
#define RTC_ALMA_MSKM_Pos (15U)
#define RTC_ALMA_MSKM_Msk (0x1UL << RTC_ALMA_MSKM_Pos)
#define RTC_ALMA_MSKM RTC_ALMA_MSKM_Msk
#define RTC_ALMA_HOURL_Pos (16U)
#define RTC_ALMA_HOURL_Msk (0xFUL << RTC_ALMA_HOURL_Pos)
#define RTC_ALMA_HOURL RTC_ALMA_HOURL_Msk
#define RTC_ALMA_HOURH_Pos (20U)
#define RTC_ALMA_HOURH_Msk (0x3UL << RTC_ALMA_HOURH_Pos)
#define RTC_ALMA_HOURH RTC_ALMA_HOURH_Msk
#define RTC_ALMA_MSKH_Pos (23U)
#define RTC_ALMA_MSKH_Msk (0x1UL << RTC_ALMA_MSKH_Pos)
#define RTC_ALMA_MSKH RTC_ALMA_MSKH_Msk
#define RTC_ALMA_WEEK_Pos (24U)
#define RTC_ALMA_WEEK_Msk (0x7FUL << RTC_ALMA_WEEK_Pos)
#define RTC_ALMA_WEEK RTC_ALMA_WEEK_Msk

// RTC_ALMB
#define RTC_ALMB_SECL_Pos (0U)
#define RTC_ALMB_SECL_Msk (0xFUL << RTC_ALMB_SECL_Pos)
#define RTC_ALMB_SECL RTC_ALMB_SECL_Msk
#define RTC_ALMB_SECH_Pos (4U)
#define RTC_ALMB_SECH_Msk (0x7UL << RTC_ALMB_SECH_Pos)
#define RTC_ALMB_SECH RTC_ALMB_SECH_Msk
#define RTC_ALMB_MSKS_Pos (7U)
#define RTC_ALMB_MSKS_Msk (0x1UL << RTC_ALMB_MSKS_Pos)
#define RTC_ALMB_MSKS RTC_ALMB_MSKS_Msk
#define RTC_ALMB_MINL_Pos (8U)
#define RTC_ALMB_MINL_Msk (0xFUL << RTC_ALMB_MINL_Pos)
#define RTC_ALMB_MINL RTC_ALMB_MINL_Msk
#define RTC_ALMB_MINH_Pos (12U)
#define RTC_ALMB_MINH_Msk (0x7UL << RTC_ALMB_MINH_Pos)
#define RTC_ALMB_MINH RTC_ALMB_MINH_Msk
#define RTC_ALMB_MSKM_Pos (15U)
#define RTC_ALMB_MSKM_Msk (0x1UL << RTC_ALMB_MSKM_Pos)
#define RTC_ALMB_MSKM RTC_ALMB_MSKM_Msk
#define RTC_ALMB_HOURL_Pos (16U)
#define RTC_ALMB_HOURL_Msk (0xFUL << RTC_ALMB_HOURL_Pos)
#define RTC_ALMB_HOURL RTC_ALMB_HOURL_Msk
#define RTC_ALMB_HOURH_Pos (20U)
#define RTC_ALMB_HOURH_Msk (0x3UL << RTC_ALMB_HOURH_Pos)
#define RTC_ALMB_HOURH RTC_ALMB_HOURH_Msk
#define RTC_ALMB_MSKH_Pos (23U)
#define RTC_ALMB_MSKH_Msk (0x1UL << RTC_ALMB_MSKH_Pos)
#define RTC_ALMB_MSKH RTC_ALMB_MSKH_Msk
#define RTC_ALMB_WEEK_Pos (24U)
#define RTC_ALMB_WEEK_Msk (0x7FUL << RTC_ALMB_WEEK_Pos)
#define RTC_ALMB_WEEK RTC_ALMB_WEEK_Msk

// RTC_TSTR
#define RTC_TSTR_SECL_Pos (0U)
#define RTC_TSTR_SECL_Msk (0xFUL << RTC_TSTR_SECL_Pos)
#define RTC_TSTR_SECL RTC_TSTR_SECL_Msk
#define RTC_TSTR_SECH_Pos (4U)
#define RTC_TSTR_SECH_Msk (0x7UL << RTC_TSTR_SECH_Pos)
#define RTC_TSTR_SECH RTC_TSTR_SECH_Msk
#define RTC_TSTR_MINL_Pos (8U)
#define RTC_TSTR_MINL_Msk (0xFUL << RTC_TSTR_MINL_Pos)
#define RTC_TSTR_MINL RTC_TSTR_MINL_Msk
#define RTC_TSTR_MINH_Pos (12U)
#define RTC_TSTR_MINH_Msk (0x7UL << RTC_TSTR_MINH_Pos)
#define RTC_TSTR_MINH RTC_TSTR_MINH_Msk
#define RTC_TSTR_HOURL_Pos (16U)
#define RTC_TSTR_HOURL_Msk (0xFUL << RTC_TSTR_HOURL_Pos)
#define RTC_TSTR_HOURL RTC_TSTR_HOURL_Msk
#define RTC_TSTR_HOURH_Pos (20U)
#define RTC_TSTR_HOURH_Msk (0x3UL << RTC_TSTR_HOURH_Pos)
#define RTC_TSTR_HOURH RTC_TSTR_HOURH_Msk

// RTC_TSDR
#define RTC_TSDR_DAYL_Pos (0U)
#define RTC_TSDR_DAYL_Msk (0xFUL << RTC_TSDR_DAYL_Pos)
#define RTC_TSDR_DAYL RTC_TSDR_DAYL_Msk
#define RTC_TSDR_DAYH_Pos (4U)
#define RTC_TSDR_DAYH_Msk (0x3UL << RTC_TSDR_DAYH_Pos)
#define RTC_TSDR_DAYH RTC_TSDR_DAYH_Msk
#define RTC_TSDR_MON_Pos (8U)
#define RTC_TSDR_MON_Msk (0x1FUL << RTC_TSDR_MON_Pos)
#define RTC_TSDR_MON RTC_TSDR_MON_Msk
#define RTC_TSDR_WEEK_Pos (13U)
#define RTC_TSDR_WEEK_Msk (0x7UL << RTC_TSDR_WEEK_Pos)
#define RTC_TSDR_WEEK RTC_TSDR_WEEK_Msk

// RTC_WUTARR
#define RTC_WUTARR_WUTARR_Pos (0U)
#define RTC_WUTARR_WUTARR_Msk (0xFFFFUL << RTC_WUTARR_WUTARR_Pos)
#define RTC_WUTARR_WUTARR RTC_WUTARR_WUTARR_Msk

// RTC_IER
#define RTC_IER_ALMA_Pos (0U)
#define RTC_IER_ALMA_Msk (0x1UL << RTC_IER_ALMA_Pos)
#define RTC_IER_ALMA RTC_IER_ALMA_Msk
#define RTC_IER_ALMB_Pos (1U)
#define RTC_IER_ALMB_Msk (0x1UL << RTC_IER_ALMB_Pos)
#define RTC_IER_ALMB RTC_IER_ALMB_Msk
#define RTC_IER_WU_Pos (2U)
#define RTC_IER_WU_Msk (0x1UL << RTC_IER_WU_Pos)
#define RTC_IER_WU RTC_IER_WU_Msk
#define RTC_IER_TS_Pos (3U)
#define RTC_IER_TS_Msk (0x1UL << RTC_IER_TS_Pos)
#define RTC_IER_TS RTC_IER_TS_Msk
#define RTC_IER_TSOV_Pos (4U)
#define RTC_IER_TSOV_Msk (0x1UL << RTC_IER_TSOV_Pos)
#define RTC_IER_TSOV RTC_IER_TSOV_Msk
#define RTC_IER_PRD_Pos (6U)
#define RTC_IER_PRD_Msk (0x1UL << RTC_IER_PRD_Pos)
#define RTC_IER_PRD RTC_IER_PRD_Msk

// RTC_IFR
#define RTC_IFR_ALMA_Pos (0U)
#define RTC_IFR_ALMA_Msk (0x1UL << RTC_IFR_ALMA_Pos)
#define RTC_IFR_ALMA RTC_IFR_ALMA_Msk
#define RTC_IFR_ALMB_Pos (1U)
#define RTC_IFR_ALMB_Msk (0x1UL << RTC_IFR_ALMB_Pos)
#define RTC_IFR_ALMB RTC_IFR_ALMB_Msk
#define RTC_IFR_WU_Pos (2U)
#define RTC_IFR_WU_Msk (0x1UL << RTC_IFR_WU_Pos)
#define RTC_IFR_WU RTC_IFR_WU_Msk
#define RTC_IFR_TS_Pos (3U)
#define RTC_IFR_TS_Msk (0x1UL << RTC_IFR_TS_Pos)
#define RTC_IFR_TS RTC_IFR_TS_Msk
#define RTC_IFR_TSOV_Pos (4U)
#define RTC_IFR_TSOV_Msk (0x1UL << RTC_IFR_TSOV_Pos)
#define RTC_IFR_TSOV RTC_IFR_TSOV_Msk
#define RTC_IFR_PRD_Pos (6U)
#define RTC_IFR_PRD_Msk (0x1UL << RTC_IFR_PRD_Pos)
#define RTC_IFR_PRD RTC_IFR_PRD_Msk

// RTC_ICR
#define RTC_ICR_ALMA_Pos (0U)
#define RTC_ICR_ALMA_Msk (0x1UL << RTC_ICR_ALMA_Pos)
#define RTC_ICR_ALMA RTC_ICR_ALMA_Msk
#define RTC_ICR_ALMB_Pos (1U)
#define RTC_ICR_ALMB_Msk (0x1UL << RTC_ICR_ALMB_Pos)
#define RTC_ICR_ALMB RTC_ICR_ALMB_Msk
#define RTC_ICR_WU_Pos (2U)
#define RTC_ICR_WU_Msk (0x1UL << RTC_ICR_WU_Pos)
#define RTC_ICR_WU RTC_ICR_WU_Msk
#define RTC_ICR_TS_Pos (3U)
#define RTC_ICR_TS_Msk (0x1UL << RTC_ICR_TS_Pos)
#define RTC_ICR_TS RTC_ICR_TS_Msk
#define RTC_ICR_TSOV_Pos (4U)
#define RTC_ICR_TSOV_Msk (0x1UL << RTC_ICR_TSOV_Pos)
#define RTC_ICR_TSOV RTC_ICR_TSOV_Msk
#define RTC_ICR_PRD_Pos (6U)
#define RTC_ICR_PRD_Msk (0x1UL << RTC_ICR_PRD_Pos)
#define RTC_ICR_PRD RTC_ICR_PRD_Msk

// RTC_WPR
#define RTC_WPR_WPR_Pos (0U)
#define RTC_WPR_WPR_Msk (0xFFUL << RTC_WPR_WPR_Pos)
#define RTC_WPR_WPR RTC_WPR_WPR_Msk

//********************    Bits Define For Peripheral SPI    ********************//
// SPI_CR0
#define SPI_CR0_EN_Pos (0U)
#define SPI_CR0_EN_Msk (0x1UL << SPI_CR0_EN_Pos)
#define SPI_CR0_EN SPI_CR0_EN_Msk
#define SPI_CR0_BRR_Pos (1U)
#define SPI_CR0_BRR_Msk (0x7UL << SPI_CR0_BRR_Pos)
#define SPI_CR0_BRR SPI_CR0_BRR_Msk
#define SPI_CR0_CPHA_Pos (4U)
#define SPI_CR0_CPHA_Msk (0x1UL << SPI_CR0_CPHA_Pos)
#define SPI_CR0_CPHA SPI_CR0_CPHA_Msk
#define SPI_CR0_CPOL_Pos (5U)
#define SPI_CR0_CPOL_Msk (0x1UL << SPI_CR0_CPOL_Pos)
#define SPI_CR0_CPOL SPI_CR0_CPOL_Msk
#define SPI_CR0_MSTR_Pos (6U)
#define SPI_CR0_MSTR_Msk (0x1UL << SPI_CR0_MSTR_Pos)
#define SPI_CR0_MSTR SPI_CR0_MSTR_Msk
#define SPI_CR0_LSBF_Pos (7U)
#define SPI_CR0_LSBF_Msk (0x1UL << SPI_CR0_LSBF_Pos)
#define SPI_CR0_LSBF SPI_CR0_LSBF_Msk
#define SPI_CR0_WIDTH_Pos (8U)
#define SPI_CR0_WIDTH_Msk (0xFUL << SPI_CR0_WIDTH_Pos)
#define SPI_CR0_WIDTH SPI_CR0_WIDTH_Msk
#define SPI_CR0_SSM_Pos (12U)
#define SPI_CR0_SSM_Msk (0x1UL << SPI_CR0_SSM_Pos)
#define SPI_CR0_SSM SPI_CR0_SSM_Msk
#define SPI_CR0_CM_Pos (13U)
#define SPI_CR0_CM_Msk (0x3UL << SPI_CR0_CM_Pos)
#define SPI_CR0_CM SPI_CR0_CM_Msk
#define SPI_CR0_SMP_Pos (15U)
#define SPI_CR0_SMP_Msk (0x1UL << SPI_CR0_SMP_Pos)
#define SPI_CR0_SMP SPI_CR0_SMP_Msk

// SPI_CR1
#define SPI_CR1_TXEIE_Pos (0U)
#define SPI_CR1_TXEIE_Msk (0x1UL << SPI_CR1_TXEIE_Pos)
#define SPI_CR1_TXEIE SPI_CR1_TXEIE_Msk
#define SPI_CR1_RXNEIE_Pos (1U)
#define SPI_CR1_RXNEIE_Msk (0x1UL << SPI_CR1_RXNEIE_Pos)
#define SPI_CR1_RXNEIE SPI_CR1_RXNEIE_Msk
#define SPI_CR1_SSFIE_Pos (2U)
#define SPI_CR1_SSFIE_Msk (0x1UL << SPI_CR1_SSFIE_Pos)
#define SPI_CR1_SSFIE SPI_CR1_SSFIE_Msk
#define SPI_CR1_SSRIE_Pos (3U)
#define SPI_CR1_SSRIE_Msk (0x1UL << SPI_CR1_SSRIE_Pos)
#define SPI_CR1_SSRIE SPI_CR1_SSRIE_Msk
#define SPI_CR1_UDFIE_Pos (4U)
#define SPI_CR1_UDFIE_Msk (0x1UL << SPI_CR1_UDFIE_Pos)
#define SPI_CR1_UDFIE SPI_CR1_UDFIE_Msk
#define SPI_CR1_OVFIE_Pos (5U)
#define SPI_CR1_OVFIE_Msk (0x1UL << SPI_CR1_OVFIE_Pos)
#define SPI_CR1_OVFIE SPI_CR1_OVFIE_Msk
#define SPI_CR1_SSERRIE_Pos (6U)
#define SPI_CR1_SSERRIE_Msk (0x1UL << SPI_CR1_SSERRIE_Pos)
#define SPI_CR1_SSERRIE SPI_CR1_SSERRIE_Msk
#define SPI_CR1_MODFIE_Pos (7U)
#define SPI_CR1_MODFIE_Msk (0x1UL << SPI_CR1_MODFIE_Pos)
#define SPI_CR1_MODFIE SPI_CR1_MODFIE_Msk
#define SPI_CR1_DMARXEN_Pos (8U)
#define SPI_CR1_DMARXEN_Msk (0x1UL << SPI_CR1_DMARXEN_Pos)
#define SPI_CR1_DMARXEN SPI_CR1_DMARXEN_Msk
#define SPI_CR1_DMATXEN_Pos (9U)
#define SPI_CR1_DMATXEN_Msk (0x1UL << SPI_CR1_DMATXEN_Pos)
#define SPI_CR1_DMATXEN SPI_CR1_DMATXEN_Msk

// SPI_HDOE
#define SPI_HDOE_HDOE_Pos (0U)
#define SPI_HDOE_HDOE_Msk (0x1UL << SPI_HDOE_HDOE_Pos)
#define SPI_HDOE_HDOE SPI_HDOE_HDOE_Msk

// SPI_SSI
#define SPI_SSI_SSI_Pos (0U)
#define SPI_SSI_SSI_Msk (0x1UL << SPI_SSI_SSI_Pos)
#define SPI_SSI_SSI SPI_SSI_SSI_Msk

// SPI_SR
#define SPI_SR_TXE_Pos (0U)
#define SPI_SR_TXE_Msk (0x1UL << SPI_SR_TXE_Pos)
#define SPI_SR_TXE SPI_SR_TXE_Msk
#define SPI_SR_RXNE_Pos (1U)
#define SPI_SR_RXNE_Msk (0x1UL << SPI_SR_RXNE_Pos)
#define SPI_SR_RXNE SPI_SR_RXNE_Msk
#define SPI_SR_SSF_Pos (2U)
#define SPI_SR_SSF_Msk (0x1UL << SPI_SR_SSF_Pos)
#define SPI_SR_SSF SPI_SR_SSF_Msk
#define SPI_SR_SSR_Pos (3U)
#define SPI_SR_SSR_Msk (0x1UL << SPI_SR_SSR_Pos)
#define SPI_SR_SSR SPI_SR_SSR_Msk
#define SPI_SR_UDF_Pos (4U)
#define SPI_SR_UDF_Msk (0x1UL << SPI_SR_UDF_Pos)
#define SPI_SR_UDF SPI_SR_UDF_Msk
#define SPI_SR_OVF_Pos (5U)
#define SPI_SR_OVF_Msk (0x1UL << SPI_SR_OVF_Pos)
#define SPI_SR_OVF SPI_SR_OVF_Msk
#define SPI_SR_SSERR_Pos (6U)
#define SPI_SR_SSERR_Msk (0x1UL << SPI_SR_SSERR_Pos)
#define SPI_SR_SSERR SPI_SR_SSERR_Msk
#define SPI_SR_MODF_Pos (7U)
#define SPI_SR_MODF_Msk (0x1UL << SPI_SR_MODF_Pos)
#define SPI_SR_MODF SPI_SR_MODF_Msk
#define SPI_SR_BUSY_Pos (8U)
#define SPI_SR_BUSY_Msk (0x1UL << SPI_SR_BUSY_Pos)
#define SPI_SR_BUSY SPI_SR_BUSY_Msk
#define SPI_SR_SSLVL_Pos (9U)
#define SPI_SR_SSLVL_Msk (0x1UL << SPI_SR_SSLVL_Pos)
#define SPI_SR_SSLVL SPI_SR_SSLVL_Msk

// SPI_ICR
#define SPI_ICR_TXE_Pos (0U)
#define SPI_ICR_TXE_Msk (0x1UL << SPI_ICR_TXE_Pos)
#define SPI_ICR_TXE SPI_ICR_TXE_Msk
#define SPI_ICR_RXNE_Pos (1U)
#define SPI_ICR_RXNE_Msk (0x1UL << SPI_ICR_RXNE_Pos)
#define SPI_ICR_RXNE SPI_ICR_RXNE_Msk
#define SPI_ICR_SSF_Pos (2U)
#define SPI_ICR_SSF_Msk (0x1UL << SPI_ICR_SSF_Pos)
#define SPI_ICR_SSF SPI_ICR_SSF_Msk
#define SPI_ICR_SSR_Pos (3U)
#define SPI_ICR_SSR_Msk (0x1UL << SPI_ICR_SSR_Pos)
#define SPI_ICR_SSR SPI_ICR_SSR_Msk
#define SPI_ICR_UDF_Pos (4U)
#define SPI_ICR_UDF_Msk (0x1UL << SPI_ICR_UDF_Pos)
#define SPI_ICR_UDF SPI_ICR_UDF_Msk
#define SPI_ICR_OVF_Pos (5U)
#define SPI_ICR_OVF_Msk (0x1UL << SPI_ICR_OVF_Pos)
#define SPI_ICR_OVF SPI_ICR_OVF_Msk
#define SPI_ICR_SSERR_Pos (6U)
#define SPI_ICR_SSERR_Msk (0x1UL << SPI_ICR_SSERR_Pos)
#define SPI_ICR_SSERR SPI_ICR_SSERR_Msk
#define SPI_ICR_MODF_Pos (7U)
#define SPI_ICR_MODF_Msk (0x1UL << SPI_ICR_MODF_Pos)
#define SPI_ICR_MODF SPI_ICR_MODF_Msk

// SPI_DR
#define SPI_DR_DR_Pos (0U)
#define SPI_DR_DR_Msk (0xFFFFUL << SPI_DR_DR_Pos)
#define SPI_DR_DR SPI_DR_DR_Msk

//********************    Bits Define For Peripheral SYSCTRL    ********************//
// SYSCTRL_CR0
#define SYSCTRL_CR0_CLKSRC_Pos (0U)
#define SYSCTRL_CR0_CLKSRC_Msk (0x7UL << SYSCTRL_CR0_CLKSRC_Pos)
#define SYSCTRL_CR0_CLKSRC SYSCTRL_CR0_CLKSRC_Msk
#define SYSCTRL_CR0_HCLKPRS_Pos (3U)
#define SYSCTRL_CR0_HCLKPRS_Msk (0x7UL << SYSCTRL_CR0_HCLKPRS_Pos)
#define SYSCTRL_CR0_HCLKPRS SYSCTRL_CR0_HCLKPRS_Msk
#define SYSCTRL_CR0_PCLKPRS_Pos (6U)
#define SYSCTRL_CR0_PCLKPRS_Msk (0x3UL << SYSCTRL_CR0_PCLKPRS_Pos)
#define SYSCTRL_CR0_PCLKPRS SYSCTRL_CR0_PCLKPRS_Msk

// SYSCTRL_CR1
#define SYSCTRL_CR1_SWDUSEIO_Pos (0U)
#define SYSCTRL_CR1_SWDUSEIO_Msk (0x1UL << SYSCTRL_CR1_SWDUSEIO_Pos)
#define SYSCTRL_CR1_SWDUSEIO SYSCTRL_CR1_SWDUSEIO_Msk
#define SYSCTRL_CR1_LOCKUP_EN_Pos (1U)
#define SYSCTRL_CR1_LOCKUP_EN_Msk (0x1UL << SYSCTRL_CR1_LOCKUP_EN_Pos)
#define SYSCTRL_CR1_LOCKUP_EN SYSCTRL_CR1_LOCKUP_EN_Msk
#define SYSCTRL_CR1_WAKEUPBYRCH_Pos (2U)
#define SYSCTRL_CR1_WAKEUPBYRCH_Msk (0x1UL << SYSCTRL_CR1_WAKEUPBYRCH_Pos)
#define SYSCTRL_CR1_WAKEUPBYRCH SYSCTRL_CR1_WAKEUPBYRCH_Msk
#define SYSCTRL_CR1_RTCLPW_Pos (3U)
#define SYSCTRL_CR1_RTCLPW_Msk (0x1UL << SYSCTRL_CR1_RTCLPW_Pos)
#define SYSCTRL_CR1_RTCLPW SYSCTRL_CR1_RTCLPW_Msk
#define SYSCTRL_CR1_RTCADJ_Pos (4U)
#define SYSCTRL_CR1_RTCADJ_Msk (0x7UL << SYSCTRL_CR1_RTCADJ_Pos)
#define SYSCTRL_CR1_RTCADJ SYSCTRL_CR1_RTCADJ_Msk
#define SYSCTRL_CR1_AUTOSWITCH_Pos (7U)
#define SYSCTRL_CR1_AUTOSWITCH_Msk (0x1UL << SYSCTRL_CR1_AUTOSWITCH_Pos)
#define SYSCTRL_CR1_AUTOSWITCH SYSCTRL_CR1_AUTOSWITCH_Msk
#define SYSCTRL_CR1_SPIPCTRL_Pos (8U)
#define SYSCTRL_CR1_SPIPCTRL_Msk (0x1UL << SYSCTRL_CR1_SPIPCTRL_Pos)
#define SYSCTRL_CR1_SPIPCTRL SYSCTRL_CR1_SPIPCTRL_Msk
#define SYSCTRL_CR1_XTHFLT_Pos (9U)
#define SYSCTRL_CR1_XTHFLT_Msk (0x1UL << SYSCTRL_CR1_XTHFLT_Pos)
#define SYSCTRL_CR1_XTHFLT SYSCTRL_CR1_XTHFLT_Msk
#define SYSCTRL_CR1_GTIM0CFG_Pos (10U)
#define SYSCTRL_CR1_GTIM0CFG_Msk (0x1UL << SYSCTRL_CR1_GTIM0CFG_Pos)
#define SYSCTRL_CR1_GTIM0CFG SYSCTRL_CR1_GTIM0CFG_Msk
#define SYSCTRL_CR1_GTIM1CFG_Pos (11U)
#define SYSCTRL_CR1_GTIM1CFG_Msk (0x1UL << SYSCTRL_CR1_GTIM1CFG_Pos)
#define SYSCTRL_CR1_GTIM1CFG SYSCTRL_CR1_GTIM1CFG_Msk
#define SYSCTRL_CR1_FASTIOENB_Pos (12U)
#define SYSCTRL_CR1_FASTIOENB_Msk (0x1UL << SYSCTRL_CR1_FASTIOENB_Pos)
#define SYSCTRL_CR1_FASTIOENB SYSCTRL_CR1_FASTIOENB_Msk

// SYSCTRL_CR2
#define SYSCTRL_CR2_RCH_Pos (0U)
#define SYSCTRL_CR2_RCH_Msk (0x1UL << SYSCTRL_CR2_RCH_Pos)
#define SYSCTRL_CR2_RCH SYSCTRL_CR2_RCH_Msk
#define SYSCTRL_CR2_XTH_Pos (1U)
#define SYSCTRL_CR2_XTH_Msk (0x1UL << SYSCTRL_CR2_XTH_Pos)
#define SYSCTRL_CR2_XTH SYSCTRL_CR2_XTH_Msk
#define SYSCTRL_CR2_RCL_Pos (2U)
#define SYSCTRL_CR2_RCL_Msk (0x1UL << SYSCTRL_CR2_RCL_Pos)
#define SYSCTRL_CR2_RCL SYSCTRL_CR2_RCL_Msk
#define SYSCTRL_CR2_XTL_Pos (3U)
#define SYSCTRL_CR2_XTL_Msk (0x1UL << SYSCTRL_CR2_XTL_Pos)
#define SYSCTRL_CR2_XTL SYSCTRL_CR2_XTL_Msk
#define SYSCTRL_CR2_PLL_Pos (4U)
#define SYSCTRL_CR2_PLL_Msk (0x1UL << SYSCTRL_CR2_PLL_Pos)
#define SYSCTRL_CR2_PLL SYSCTRL_CR2_PLL_Msk
#define SYSCTRL_CR2_EXXTH_Pos (5U)
#define SYSCTRL_CR2_EXXTH_Msk (0x1UL << SYSCTRL_CR2_EXXTH_Pos)
#define SYSCTRL_CR2_EXXTH SYSCTRL_CR2_EXXTH_Msk
#define SYSCTRL_CR2_EXXTL_Pos (6U)
#define SYSCTRL_CR2_EXXTL_Msk (0x1UL << SYSCTRL_CR2_EXXTL_Pos)
#define SYSCTRL_CR2_EXXTL SYSCTRL_CR2_EXXTL_Msk
#define SYSCTRL_CR2_XTLLOCK_Pos (7U)
#define SYSCTRL_CR2_XTLLOCK_Msk (0x1UL << SYSCTRL_CR2_XTLLOCK_Pos)
#define SYSCTRL_CR2_XTLLOCK SYSCTRL_CR2_XTLLOCK_Msk

// SYSCTRL_CR3
#define SYSCTRL_CR3_CR3_Pos (0U)
#define SYSCTRL_CR3_CR3_Msk (0xFFFFUL << SYSCTRL_CR3_CR3_Pos)
#define SYSCTRL_CR3_CR3 SYSCTRL_CR3_CR3_Msk

// SYSCTRL_RCHCR
#define SYSCTRL_RCHCR_DIV_Pos (0U)
#define SYSCTRL_RCHCR_DIV_Msk (0x7UL << SYSCTRL_RCHCR_DIV_Pos)
#define SYSCTRL_RCHCR_DIV SYSCTRL_RCHCR_DIV_Msk

// SYSCTRL_XTHCR
#define SYSCTRL_XTHCR_DRIVER_Pos (0U)
#define SYSCTRL_XTHCR_DRIVER_Msk (0x3UL << SYSCTRL_XTHCR_DRIVER_Pos)
#define SYSCTRL_XTHCR_DRIVER SYSCTRL_XTHCR_DRIVER_Msk
#define SYSCTRL_XTHCR_RANGE_Pos (2U)
#define SYSCTRL_XTHCR_RANGE_Msk (0x3UL << SYSCTRL_XTHCR_RANGE_Pos)
#define SYSCTRL_XTHCR_RANGE SYSCTRL_XTHCR_RANGE_Msk
#define SYSCTRL_XTHCR_STARTUP_Pos (4U)
#define SYSCTRL_XTHCR_STARTUP_Msk (0x3UL << SYSCTRL_XTHCR_STARTUP_Pos)
#define SYSCTRL_XTHCR_STARTUP SYSCTRL_XTHCR_STARTUP_Msk
#define SYSCTRL_XTHCR_DETEN_Pos (6U)
#define SYSCTRL_XTHCR_DETEN_Msk (0x1UL << SYSCTRL_XTHCR_DETEN_Pos)
#define SYSCTRL_XTHCR_DETEN SYSCTRL_XTHCR_DETEN_Msk
#define SYSCTRL_XTHCR_DETTIME_Pos (7U)
#define SYSCTRL_XTHCR_DETTIME_Msk (0x1UL << SYSCTRL_XTHCR_DETTIME_Pos)
#define SYSCTRL_XTHCR_DETTIME SYSCTRL_XTHCR_DETTIME_Msk
#define SYSCTRL_XTHCR_DETIE_Pos (8U)
#define SYSCTRL_XTHCR_DETIE_Msk (0x1UL << SYSCTRL_XTHCR_DETIE_Pos)
#define SYSCTRL_XTHCR_DETIE SYSCTRL_XTHCR_DETIE_Msk

// SYSCTRL_RCLCR
#define SYSCTRL_RCLCR_STARTUP_Pos (10U)
#define SYSCTRL_RCLCR_STARTUP_Msk (0x3UL << SYSCTRL_RCLCR_STARTUP_Pos)
#define SYSCTRL_RCLCR_STARTUP SYSCTRL_RCLCR_STARTUP_Msk

// SYSCTRL_XTLCR
#define SYSCTRL_XTLCR_DRIVER_Pos (0U)
#define SYSCTRL_XTLCR_DRIVER_Msk (0x3UL << SYSCTRL_XTLCR_DRIVER_Pos)
#define SYSCTRL_XTLCR_DRIVER SYSCTRL_XTLCR_DRIVER_Msk
#define SYSCTRL_XTLCR_AMP_SEL_Pos (2U)
#define SYSCTRL_XTLCR_AMP_SEL_Msk (0x3UL << SYSCTRL_XTLCR_AMP_SEL_Pos)
#define SYSCTRL_XTLCR_AMP_SEL SYSCTRL_XTLCR_AMP_SEL_Msk
#define SYSCTRL_XTLCR_STARTUP_Pos (4U)
#define SYSCTRL_XTLCR_STARTUP_Msk (0x3UL << SYSCTRL_XTLCR_STARTUP_Pos)
#define SYSCTRL_XTLCR_STARTUP SYSCTRL_XTLCR_STARTUP_Msk
#define SYSCTRL_XTLCR_DETEN_Pos (6U)
#define SYSCTRL_XTLCR_DETEN_Msk (0x1UL << SYSCTRL_XTLCR_DETEN_Pos)
#define SYSCTRL_XTLCR_DETEN SYSCTRL_XTLCR_DETEN_Msk
#define SYSCTRL_XTLCR_DETTIME_Pos (7U)
#define SYSCTRL_XTLCR_DETTIME_Msk (0x1UL << SYSCTRL_XTLCR_DETTIME_Pos)
#define SYSCTRL_XTLCR_DETTIME SYSCTRL_XTLCR_DETTIME_Msk
#define SYSCTRL_XTLCR_DETIE_Pos (8U)
#define SYSCTRL_XTLCR_DETIE_Msk (0x1UL << SYSCTRL_XTLCR_DETIE_Pos)
#define SYSCTRL_XTLCR_DETIE SYSCTRL_XTLCR_DETIE_Msk

// SYSCTRL_PLLCR
#define SYSCTRL_PLLCR_SRC_Pos (0U)
#define SYSCTRL_PLLCR_SRC_Msk (0x3UL << SYSCTRL_PLLCR_SRC_Pos)
#define SYSCTRL_PLLCR_SRC SYSCTRL_PLLCR_SRC_Msk
#define SYSCTRL_PLLCR_DIVR_Pos (2U)
#define SYSCTRL_PLLCR_DIVR_Msk (0x1UL << SYSCTRL_PLLCR_DIVR_Pos)
#define SYSCTRL_PLLCR_DIVR SYSCTRL_PLLCR_DIVR_Msk
#define SYSCTRL_PLLCR_WAITCYCLE_Pos (4U)
#define SYSCTRL_PLLCR_WAITCYCLE_Msk (0x7UL << SYSCTRL_PLLCR_WAITCYCLE_Pos)
#define SYSCTRL_PLLCR_WAITCYCLE SYSCTRL_PLLCR_WAITCYCLE_Msk
#define SYSCTRL_PLLCR_DIVN_Pos (8U)
#define SYSCTRL_PLLCR_DIVN_Msk (0x7FUL << SYSCTRL_PLLCR_DIVN_Pos)
#define SYSCTRL_PLLCR_DIVN SYSCTRL_PLLCR_DIVN_Msk
#define SYSCTRL_PLLCR_DIVF_Pos (16U)
#define SYSCTRL_PLLCR_DIVF_Msk (0x7UL << SYSCTRL_PLLCR_DIVF_Pos)
#define SYSCTRL_PLLCR_DIVF SYSCTRL_PLLCR_DIVF_Msk
#define SYSCTRL_PLLCR_POSTDIV_Pos (20U)
#define SYSCTRL_PLLCR_POSTDIV_Msk (0xFUL << SYSCTRL_PLLCR_POSTDIV_Pos)
#define SYSCTRL_PLLCR_POSTDIV SYSCTRL_PLLCR_POSTDIV_Msk

// SYSCTRL_RCHTRIM
#define SYSCTRL_RCHTRIM_TRIML_Pos (0U)
#define SYSCTRL_RCHTRIM_TRIML_Msk (0x3FUL << SYSCTRL_RCHTRIM_TRIML_Pos)
#define SYSCTRL_RCHTRIM_TRIML SYSCTRL_RCHTRIM_TRIML_Msk
#define SYSCTRL_RCHTRIM_TRIMH_Pos (6U)
#define SYSCTRL_RCHTRIM_TRIMH_Msk (0x1FUL << SYSCTRL_RCHTRIM_TRIMH_Pos)
#define SYSCTRL_RCHTRIM_TRIMH SYSCTRL_RCHTRIM_TRIMH_Msk

// SYSCTRL_RCLTRIM
#define SYSCTRL_RCLTRIM_TRIM_Pos (0U)
#define SYSCTRL_RCLTRIM_TRIM_Msk (0x3FFUL << SYSCTRL_RCLTRIM_TRIM_Pos)
#define SYSCTRL_RCLTRIM_TRIM SYSCTRL_RCLTRIM_TRIM_Msk

// SYSCTRL_STATE
#define SYSCTRL_STATE_RCH_Pos (0U)
#define SYSCTRL_STATE_RCH_Msk (0x1UL << SYSCTRL_STATE_RCH_Pos)
#define SYSCTRL_STATE_RCH SYSCTRL_STATE_RCH_Msk
#define SYSCTRL_STATE_XTH_Pos (1U)
#define SYSCTRL_STATE_XTH_Msk (0x1UL << SYSCTRL_STATE_XTH_Pos)
#define SYSCTRL_STATE_XTH SYSCTRL_STATE_XTH_Msk
#define SYSCTRL_STATE_RCL_Pos (2U)
#define SYSCTRL_STATE_RCL_Msk (0x1UL << SYSCTRL_STATE_RCL_Pos)
#define SYSCTRL_STATE_RCL SYSCTRL_STATE_RCL_Msk
#define SYSCTRL_STATE_XTL_Pos (3U)
#define SYSCTRL_STATE_XTL_Msk (0x1UL << SYSCTRL_STATE_XTL_Pos)
#define SYSCTRL_STATE_XTL SYSCTRL_STATE_XTL_Msk
#define SYSCTRL_STATE_PLL_Pos (4U)
#define SYSCTRL_STATE_PLL_Msk (0x1UL << SYSCTRL_STATE_PLL_Pos)
#define SYSCTRL_STATE_PLL SYSCTRL_STATE_PLL_Msk
#define SYSCTRL_STATE_PLLLOCK_Pos (5U)
#define SYSCTRL_STATE_PLLLOCK_Msk (0x1UL << SYSCTRL_STATE_PLLLOCK_Pos)
#define SYSCTRL_STATE_PLLLOCK SYSCTRL_STATE_PLLLOCK_Msk
#define SYSCTRL_STATE_XTHFAIL_Pos (8U)
#define SYSCTRL_STATE_XTHFAIL_Msk (0x1UL << SYSCTRL_STATE_XTHFAIL_Pos)
#define SYSCTRL_STATE_XTHFAIL SYSCTRL_STATE_XTHFAIL_Msk
#define SYSCTRL_STATE_XTHFAULT_Pos (9U)
#define SYSCTRL_STATE_XTHFAULT_Msk (0x1UL << SYSCTRL_STATE_XTHFAULT_Pos)
#define SYSCTRL_STATE_XTHFAULT SYSCTRL_STATE_XTHFAULT_Msk
#define SYSCTRL_STATE_XTLFAIL_Pos (10U)
#define SYSCTRL_STATE_XTLFAIL_Msk (0x1UL << SYSCTRL_STATE_XTLFAIL_Pos)
#define SYSCTRL_STATE_XTLFAIL SYSCTRL_STATE_XTLFAIL_Msk
#define SYSCTRL_STATE_XTLFAULT_Pos (11U)
#define SYSCTRL_STATE_XTLFAULT_Msk (0x1UL << SYSCTRL_STATE_XTLFAULT_Pos)
#define SYSCTRL_STATE_XTLFAULT SYSCTRL_STATE_XTLFAULT_Msk

// SYSCTRL_PERICLKEN0
#define SYSCTRL_PERICLKEN0_USART0_Pos (0U)
#define SYSCTRL_PERICLKEN0_USART0_Msk (0x1UL << SYSCTRL_PERICLKEN0_USART0_Pos)
#define SYSCTRL_PERICLKEN0_USART0 SYSCTRL_PERICLKEN0_USART0_Msk
#define SYSCTRL_PERICLKEN0_USART1_Pos (1U)
#define SYSCTRL_PERICLKEN0_USART1_Msk (0x1UL << SYSCTRL_PERICLKEN0_USART1_Pos)
#define SYSCTRL_PERICLKEN0_USART1 SYSCTRL_PERICLKEN0_USART1_Msk
#define SYSCTRL_PERICLKEN0_LPUART0_Pos (2U)
#define SYSCTRL_PERICLKEN0_LPUART0_Msk (0x1UL << SYSCTRL_PERICLKEN0_LPUART0_Pos)
#define SYSCTRL_PERICLKEN0_LPUART0 SYSCTRL_PERICLKEN0_LPUART0_Msk
#define SYSCTRL_PERICLKEN0_LPUART1_Pos (3U)
#define SYSCTRL_PERICLKEN0_LPUART1_Msk (0x1UL << SYSCTRL_PERICLKEN0_LPUART1_Pos)
#define SYSCTRL_PERICLKEN0_LPUART1 SYSCTRL_PERICLKEN0_LPUART1_Msk
#define SYSCTRL_PERICLKEN0_I2C0_Pos (4U)
#define SYSCTRL_PERICLKEN0_I2C0_Msk (0x1UL << SYSCTRL_PERICLKEN0_I2C0_Pos)
#define SYSCTRL_PERICLKEN0_I2C0 SYSCTRL_PERICLKEN0_I2C0_Msk
#define SYSCTRL_PERICLKEN0_I2C1_Pos (5U)
#define SYSCTRL_PERICLKEN0_I2C1_Msk (0x1UL << SYSCTRL_PERICLKEN0_I2C1_Pos)
#define SYSCTRL_PERICLKEN0_I2C1 SYSCTRL_PERICLKEN0_I2C1_Msk
#define SYSCTRL_PERICLKEN0_SPI0_Pos (6U)
#define SYSCTRL_PERICLKEN0_SPI0_Msk (0x1UL << SYSCTRL_PERICLKEN0_SPI0_Pos)
#define SYSCTRL_PERICLKEN0_SPI0 SYSCTRL_PERICLKEN0_SPI0_Msk
#define SYSCTRL_PERICLKEN0_SPI1_Pos (7U)
#define SYSCTRL_PERICLKEN0_SPI1_Msk (0x1UL << SYSCTRL_PERICLKEN0_SPI1_Pos)
#define SYSCTRL_PERICLKEN0_SPI1 SYSCTRL_PERICLKEN0_SPI1_Msk
#define SYSCTRL_PERICLKEN0_ATIM0_Pos (8U)
#define SYSCTRL_PERICLKEN0_ATIM0_Msk (0x1UL << SYSCTRL_PERICLKEN0_ATIM0_Pos)
#define SYSCTRL_PERICLKEN0_ATIM0 SYSCTRL_PERICLKEN0_ATIM0_Msk
#define SYSCTRL_PERICLKEN0_LPTIM_Pos (9U)
#define SYSCTRL_PERICLKEN0_LPTIM_Msk (0x1UL << SYSCTRL_PERICLKEN0_LPTIM_Pos)
#define SYSCTRL_PERICLKEN0_LPTIM SYSCTRL_PERICLKEN0_LPTIM_Msk
#define SYSCTRL_PERICLKEN0_ATIM1_Pos (10U)
#define SYSCTRL_PERICLKEN0_ATIM1_Msk (0x1UL << SYSCTRL_PERICLKEN0_ATIM1_Pos)
#define SYSCTRL_PERICLKEN0_ATIM1 SYSCTRL_PERICLKEN0_ATIM1_Msk
#define SYSCTRL_PERICLKEN0_ATIM3_Pos (11U)
#define SYSCTRL_PERICLKEN0_ATIM3_Msk (0x1UL << SYSCTRL_PERICLKEN0_ATIM3_Pos)
#define SYSCTRL_PERICLKEN0_ATIM3 SYSCTRL_PERICLKEN0_ATIM3_Msk
#define SYSCTRL_PERICLKEN0_ATIM2_Pos (12U)
#define SYSCTRL_PERICLKEN0_ATIM2_Msk (0x1UL << SYSCTRL_PERICLKEN0_ATIM2_Pos)
#define SYSCTRL_PERICLKEN0_ATIM2 SYSCTRL_PERICLKEN0_ATIM2_Msk
#define SYSCTRL_PERICLKEN0_OPA_Pos (13U)
#define SYSCTRL_PERICLKEN0_OPA_Msk (0x1UL << SYSCTRL_PERICLKEN0_OPA_Pos)
#define SYSCTRL_PERICLKEN0_OPA SYSCTRL_PERICLKEN0_OPA_Msk
#define SYSCTRL_PERICLKEN0_WWDT_Pos (14U)
#define SYSCTRL_PERICLKEN0_WWDT_Msk (0x1UL << SYSCTRL_PERICLKEN0_WWDT_Pos)
#define SYSCTRL_PERICLKEN0_WWDT SYSCTRL_PERICLKEN0_WWDT_Msk
#define SYSCTRL_PERICLKEN0_IWDT_Pos (15U)
#define SYSCTRL_PERICLKEN0_IWDT_Msk (0x1UL << SYSCTRL_PERICLKEN0_IWDT_Pos)
#define SYSCTRL_PERICLKEN0_IWDT SYSCTRL_PERICLKEN0_IWDT_Msk
#define SYSCTRL_PERICLKEN0_ADC_Pos (16U)
#define SYSCTRL_PERICLKEN0_ADC_Msk (0x1UL << SYSCTRL_PERICLKEN0_ADC_Pos)
#define SYSCTRL_PERICLKEN0_ADC SYSCTRL_PERICLKEN0_ADC_Msk
#define SYSCTRL_PERICLKEN0_VCLVD_Pos (17U)
#define SYSCTRL_PERICLKEN0_VCLVD_Msk (0x1UL << SYSCTRL_PERICLKEN0_VCLVD_Pos)
#define SYSCTRL_PERICLKEN0_VCLVD SYSCTRL_PERICLKEN0_VCLVD_Msk
#define SYSCTRL_PERICLKEN0_I2CSLV_Pos (18U)
#define SYSCTRL_PERICLKEN0_I2CSLV_Msk (0x1UL << SYSCTRL_PERICLKEN0_I2CSLV_Pos)
#define SYSCTRL_PERICLKEN0_I2CSLV SYSCTRL_PERICLKEN0_I2CSLV_Msk
#define SYSCTRL_PERICLKEN0_RTC_Pos (20U)
#define SYSCTRL_PERICLKEN0_RTC_Msk (0x1UL << SYSCTRL_PERICLKEN0_RTC_Pos)
#define SYSCTRL_PERICLKEN0_RTC SYSCTRL_PERICLKEN0_RTC_Msk
#define SYSCTRL_PERICLKEN0_CTRIM_Pos (21U)
#define SYSCTRL_PERICLKEN0_CTRIM_Msk (0x1UL << SYSCTRL_PERICLKEN0_CTRIM_Pos)
#define SYSCTRL_PERICLKEN0_CTRIM SYSCTRL_PERICLKEN0_CTRIM_Msk
#define SYSCTRL_PERICLKEN0_TICK_Pos (24U)
#define SYSCTRL_PERICLKEN0_TICK_Msk (0x1UL << SYSCTRL_PERICLKEN0_TICK_Pos)
#define SYSCTRL_PERICLKEN0_TICK SYSCTRL_PERICLKEN0_TICK_Msk
#define SYSCTRL_PERICLKEN0_SWD_Pos (25U)
#define SYSCTRL_PERICLKEN0_SWD_Msk (0x1UL << SYSCTRL_PERICLKEN0_SWD_Pos)
#define SYSCTRL_PERICLKEN0_SWD SYSCTRL_PERICLKEN0_SWD_Msk
#define SYSCTRL_PERICLKEN0_CRC_Pos (26U)
#define SYSCTRL_PERICLKEN0_CRC_Msk (0x1UL << SYSCTRL_PERICLKEN0_CRC_Pos)
#define SYSCTRL_PERICLKEN0_CRC SYSCTRL_PERICLKEN0_CRC_Msk
#define SYSCTRL_PERICLKEN0_DMA_Pos (29U)
#define SYSCTRL_PERICLKEN0_DMA_Msk (0x1UL << SYSCTRL_PERICLKEN0_DMA_Pos)
#define SYSCTRL_PERICLKEN0_DMA SYSCTRL_PERICLKEN0_DMA_Msk
#define SYSCTRL_PERICLKEN0_EAU_Pos (30U)
#define SYSCTRL_PERICLKEN0_EAU_Msk (0x1UL << SYSCTRL_PERICLKEN0_EAU_Pos)
#define SYSCTRL_PERICLKEN0_EAU SYSCTRL_PERICLKEN0_EAU_Msk
#define SYSCTRL_PERICLKEN0_FLASH_Pos (31U)
#define SYSCTRL_PERICLKEN0_FLASH_Msk (0x1UL << SYSCTRL_PERICLKEN0_FLASH_Pos)
#define SYSCTRL_PERICLKEN0_FLASH SYSCTRL_PERICLKEN0_FLASH_Msk

// SYSCTRL_PERICLKEN1
#define SYSCTRL_PERICLKEN1_GPIOA_Pos (0U)
#define SYSCTRL_PERICLKEN1_GPIOA_Msk (0x1UL << SYSCTRL_PERICLKEN1_GPIOA_Pos)
#define SYSCTRL_PERICLKEN1_GPIOA SYSCTRL_PERICLKEN1_GPIOA_Msk
#define SYSCTRL_PERICLKEN1_GPIOB_Pos (1U)
#define SYSCTRL_PERICLKEN1_GPIOB_Msk (0x1UL << SYSCTRL_PERICLKEN1_GPIOB_Pos)
#define SYSCTRL_PERICLKEN1_GPIOB SYSCTRL_PERICLKEN1_GPIOB_Msk
#define SYSCTRL_PERICLKEN1_GPIOC_Pos (2U)
#define SYSCTRL_PERICLKEN1_GPIOC_Msk (0x1UL << SYSCTRL_PERICLKEN1_GPIOC_Pos)
#define SYSCTRL_PERICLKEN1_GPIOC SYSCTRL_PERICLKEN1_GPIOC_Msk
#define SYSCTRL_PERICLKEN1_GPIOD_Pos (3U)
#define SYSCTRL_PERICLKEN1_GPIOD_Msk (0x1UL << SYSCTRL_PERICLKEN1_GPIOD_Pos)
#define SYSCTRL_PERICLKEN1_GPIOD SYSCTRL_PERICLKEN1_GPIOD_Msk
#define SYSCTRL_PERICLKEN1_CAN_Pos (7U)
#define SYSCTRL_PERICLKEN1_CAN_Msk (0x1UL << SYSCTRL_PERICLKEN1_CAN_Pos)
#define SYSCTRL_PERICLKEN1_CAN SYSCTRL_PERICLKEN1_CAN_Msk
#define SYSCTRL_PERICLKEN1_GTIM0_Pos (8U)
#define SYSCTRL_PERICLKEN1_GTIM0_Msk (0x1UL << SYSCTRL_PERICLKEN1_GTIM0_Pos)
#define SYSCTRL_PERICLKEN1_GTIM0 SYSCTRL_PERICLKEN1_GTIM0_Msk
#define SYSCTRL_PERICLKEN1_GTIM1_Pos (9U)
#define SYSCTRL_PERICLKEN1_GTIM1_Msk (0x1UL << SYSCTRL_PERICLKEN1_GTIM1_Pos)
#define SYSCTRL_PERICLKEN1_GTIM1 SYSCTRL_PERICLKEN1_GTIM1_Msk

// SYSCTRL_PERIRESET0
#define SYSCTRL_PERIRESET0_USART0_Pos (0U)
#define SYSCTRL_PERIRESET0_USART0_Msk (0x1UL << SYSCTRL_PERIRESET0_USART0_Pos)
#define SYSCTRL_PERIRESET0_USART0 SYSCTRL_PERIRESET0_USART0_Msk
#define SYSCTRL_PERIRESET0_USART1_Pos (1U)
#define SYSCTRL_PERIRESET0_USART1_Msk (0x1UL << SYSCTRL_PERIRESET0_USART1_Pos)
#define SYSCTRL_PERIRESET0_USART1 SYSCTRL_PERIRESET0_USART1_Msk
#define SYSCTRL_PERIRESET0_LPUART0_Pos (2U)
#define SYSCTRL_PERIRESET0_LPUART0_Msk (0x1UL << SYSCTRL_PERIRESET0_LPUART0_Pos)
#define SYSCTRL_PERIRESET0_LPUART0 SYSCTRL_PERIRESET0_LPUART0_Msk
#define SYSCTRL_PERIRESET0_LPUART1_Pos (3U)
#define SYSCTRL_PERIRESET0_LPUART1_Msk (0x1UL << SYSCTRL_PERIRESET0_LPUART1_Pos)
#define SYSCTRL_PERIRESET0_LPUART1 SYSCTRL_PERIRESET0_LPUART1_Msk
#define SYSCTRL_PERIRESET0_I2C0_Pos (4U)
#define SYSCTRL_PERIRESET0_I2C0_Msk (0x1UL << SYSCTRL_PERIRESET0_I2C0_Pos)
#define SYSCTRL_PERIRESET0_I2C0 SYSCTRL_PERIRESET0_I2C0_Msk
#define SYSCTRL_PERIRESET0_I2C1_Pos (5U)
#define SYSCTRL_PERIRESET0_I2C1_Msk (0x1UL << SYSCTRL_PERIRESET0_I2C1_Pos)
#define SYSCTRL_PERIRESET0_I2C1 SYSCTRL_PERIRESET0_I2C1_Msk
#define SYSCTRL_PERIRESET0_SPI0_Pos (6U)
#define SYSCTRL_PERIRESET0_SPI0_Msk (0x1UL << SYSCTRL_PERIRESET0_SPI0_Pos)
#define SYSCTRL_PERIRESET0_SPI0 SYSCTRL_PERIRESET0_SPI0_Msk
#define SYSCTRL_PERIRESET0_SPI1_Pos (7U)
#define SYSCTRL_PERIRESET0_SPI1_Msk (0x1UL << SYSCTRL_PERIRESET0_SPI1_Pos)
#define SYSCTRL_PERIRESET0_SPI1 SYSCTRL_PERIRESET0_SPI1_Msk
#define SYSCTRL_PERIRESET0_ATIM0_Pos (8U)
#define SYSCTRL_PERIRESET0_ATIM0_Msk (0x1UL << SYSCTRL_PERIRESET0_ATIM0_Pos)
#define SYSCTRL_PERIRESET0_ATIM0 SYSCTRL_PERIRESET0_ATIM0_Msk
#define SYSCTRL_PERIRESET0_LPTIM_Pos (9U)
#define SYSCTRL_PERIRESET0_LPTIM_Msk (0x1UL << SYSCTRL_PERIRESET0_LPTIM_Pos)
#define SYSCTRL_PERIRESET0_LPTIM SYSCTRL_PERIRESET0_LPTIM_Msk
#define SYSCTRL_PERIRESET0_ATIM1_Pos (10U)
#define SYSCTRL_PERIRESET0_ATIM1_Msk (0x1UL << SYSCTRL_PERIRESET0_ATIM1_Pos)
#define SYSCTRL_PERIRESET0_ATIM1 SYSCTRL_PERIRESET0_ATIM1_Msk
#define SYSCTRL_PERIRESET0_ATIM3_Pos (11U)
#define SYSCTRL_PERIRESET0_ATIM3_Msk (0x1UL << SYSCTRL_PERIRESET0_ATIM3_Pos)
#define SYSCTRL_PERIRESET0_ATIM3 SYSCTRL_PERIRESET0_ATIM3_Msk
#define SYSCTRL_PERIRESET0_ATIM2_Pos (12U)
#define SYSCTRL_PERIRESET0_ATIM2_Msk (0x1UL << SYSCTRL_PERIRESET0_ATIM2_Pos)
#define SYSCTRL_PERIRESET0_ATIM2 SYSCTRL_PERIRESET0_ATIM2_Msk
#define SYSCTRL_PERIRESET0_OPA_Pos (13U)
#define SYSCTRL_PERIRESET0_OPA_Msk (0x1UL << SYSCTRL_PERIRESET0_OPA_Pos)
#define SYSCTRL_PERIRESET0_OPA SYSCTRL_PERIRESET0_OPA_Msk
#define SYSCTRL_PERIRESET0_WWDT_Pos (14U)
#define SYSCTRL_PERIRESET0_WWDT_Msk (0x1UL << SYSCTRL_PERIRESET0_WWDT_Pos)
#define SYSCTRL_PERIRESET0_WWDT SYSCTRL_PERIRESET0_WWDT_Msk
#define SYSCTRL_PERIRESET0_IWDT_Pos (15U)
#define SYSCTRL_PERIRESET0_IWDT_Msk (0x1UL << SYSCTRL_PERIRESET0_IWDT_Pos)
#define SYSCTRL_PERIRESET0_IWDT SYSCTRL_PERIRESET0_IWDT_Msk
#define SYSCTRL_PERIRESET0_ADC_Pos (16U)
#define SYSCTRL_PERIRESET0_ADC_Msk (0x1UL << SYSCTRL_PERIRESET0_ADC_Pos)
#define SYSCTRL_PERIRESET0_ADC SYSCTRL_PERIRESET0_ADC_Msk
#define SYSCTRL_PERIRESET0_VCLVD_Pos (17U)
#define SYSCTRL_PERIRESET0_VCLVD_Msk (0x1UL << SYSCTRL_PERIRESET0_VCLVD_Pos)
#define SYSCTRL_PERIRESET0_VCLVD SYSCTRL_PERIRESET0_VCLVD_Msk
#define SYSCTRL_PERIRESET0_I2CSLV_Pos (18U)
#define SYSCTRL_PERIRESET0_I2CSLV_Msk (0x1UL << SYSCTRL_PERIRESET0_I2CSLV_Pos)
#define SYSCTRL_PERIRESET0_I2CSLV SYSCTRL_PERIRESET0_I2CSLV_Msk
#define SYSCTRL_PERIRESET0_RTC_Pos (20U)
#define SYSCTRL_PERIRESET0_RTC_Msk (0x1UL << SYSCTRL_PERIRESET0_RTC_Pos)
#define SYSCTRL_PERIRESET0_RTC SYSCTRL_PERIRESET0_RTC_Msk
#define SYSCTRL_PERIRESET0_CTRIM_Pos (21U)
#define SYSCTRL_PERIRESET0_CTRIM_Msk (0x1UL << SYSCTRL_PERIRESET0_CTRIM_Pos)
#define SYSCTRL_PERIRESET0_CTRIM SYSCTRL_PERIRESET0_CTRIM_Msk
#define SYSCTRL_PERIRESET0_TICK_Pos (24U)
#define SYSCTRL_PERIRESET0_TICK_Msk (0x1UL << SYSCTRL_PERIRESET0_TICK_Pos)
#define SYSCTRL_PERIRESET0_TICK SYSCTRL_PERIRESET0_TICK_Msk
#define SYSCTRL_PERIRESET0_SWD_Pos (25U)
#define SYSCTRL_PERIRESET0_SWD_Msk (0x1UL << SYSCTRL_PERIRESET0_SWD_Pos)
#define SYSCTRL_PERIRESET0_SWD SYSCTRL_PERIRESET0_SWD_Msk
#define SYSCTRL_PERIRESET0_CRC_Pos (26U)
#define SYSCTRL_PERIRESET0_CRC_Msk (0x1UL << SYSCTRL_PERIRESET0_CRC_Pos)
#define SYSCTRL_PERIRESET0_CRC SYSCTRL_PERIRESET0_CRC_Msk
#define SYSCTRL_PERIRESET0_DMA_Pos (29U)
#define SYSCTRL_PERIRESET0_DMA_Msk (0x1UL << SYSCTRL_PERIRESET0_DMA_Pos)
#define SYSCTRL_PERIRESET0_DMA SYSCTRL_PERIRESET0_DMA_Msk
#define SYSCTRL_PERIRESET0_EAU_Pos (30U)
#define SYSCTRL_PERIRESET0_EAU_Msk (0x1UL << SYSCTRL_PERIRESET0_EAU_Pos)
#define SYSCTRL_PERIRESET0_EAU SYSCTRL_PERIRESET0_EAU_Msk

// SYSCTRL_PERIRESET1
#define SYSCTRL_PERIRESET1_GPIOA_Pos (0U)
#define SYSCTRL_PERIRESET1_GPIOA_Msk (0x1UL << SYSCTRL_PERIRESET1_GPIOA_Pos)
#define SYSCTRL_PERIRESET1_GPIOA SYSCTRL_PERIRESET1_GPIOA_Msk
#define SYSCTRL_PERIRESET1_GPIOB_Pos (1U)
#define SYSCTRL_PERIRESET1_GPIOB_Msk (0x1UL << SYSCTRL_PERIRESET1_GPIOB_Pos)
#define SYSCTRL_PERIRESET1_GPIOB SYSCTRL_PERIRESET1_GPIOB_Msk
#define SYSCTRL_PERIRESET1_GPIOC_Pos (2U)
#define SYSCTRL_PERIRESET1_GPIOC_Msk (0x1UL << SYSCTRL_PERIRESET1_GPIOC_Pos)
#define SYSCTRL_PERIRESET1_GPIOC SYSCTRL_PERIRESET1_GPIOC_Msk
#define SYSCTRL_PERIRESET1_GPIOD_Pos (3U)
#define SYSCTRL_PERIRESET1_GPIOD_Msk (0x1UL << SYSCTRL_PERIRESET1_GPIOD_Pos)
#define SYSCTRL_PERIRESET1_GPIOD SYSCTRL_PERIRESET1_GPIOD_Msk
#define SYSCTRL_PERIRESET1_CAN_Pos (7U)
#define SYSCTRL_PERIRESET1_CAN_Msk (0x1UL << SYSCTRL_PERIRESET1_CAN_Pos)
#define SYSCTRL_PERIRESET1_CAN SYSCTRL_PERIRESET1_CAN_Msk
#define SYSCTRL_PERIRESET1_GTIM0_Pos (8U)
#define SYSCTRL_PERIRESET1_GTIM0_Msk (0x1UL << SYSCTRL_PERIRESET1_GTIM0_Pos)
#define SYSCTRL_PERIRESET1_GTIM0 SYSCTRL_PERIRESET1_GTIM0_Msk
#define SYSCTRL_PERIRESET1_GTIM1_Pos (9U)
#define SYSCTRL_PERIRESET1_GTIM1_Msk (0x1UL << SYSCTRL_PERIRESET1_GTIM1_Pos)
#define SYSCTRL_PERIRESET1_GTIM1 SYSCTRL_PERIRESET1_GTIM1_Msk

// SYSCTRL_RSTFLAG
#define SYSCTRL_RSTFLAG_POR5V_Pos (0U)
#define SYSCTRL_RSTFLAG_POR5V_Msk (0x1UL << SYSCTRL_RSTFLAG_POR5V_Pos)
#define SYSCTRL_RSTFLAG_POR5V SYSCTRL_RSTFLAG_POR5V_Msk
#define SYSCTRL_RSTFLAG_POR12V_Pos (1U)
#define SYSCTRL_RSTFLAG_POR12V_Msk (0x1UL << SYSCTRL_RSTFLAG_POR12V_Pos)
#define SYSCTRL_RSTFLAG_POR12V SYSCTRL_RSTFLAG_POR12V_Msk
#define SYSCTRL_RSTFLAG_LVD_Pos (2U)
#define SYSCTRL_RSTFLAG_LVD_Msk (0x1UL << SYSCTRL_RSTFLAG_LVD_Pos)
#define SYSCTRL_RSTFLAG_LVD SYSCTRL_RSTFLAG_LVD_Msk
#define SYSCTRL_RSTFLAG_IWDT_Pos (3U)
#define SYSCTRL_RSTFLAG_IWDT_Msk (0x1UL << SYSCTRL_RSTFLAG_IWDT_Pos)
#define SYSCTRL_RSTFLAG_IWDT SYSCTRL_RSTFLAG_IWDT_Msk
#define SYSCTRL_RSTFLAG_WWDT_Pos (4U)
#define SYSCTRL_RSTFLAG_WWDT_Msk (0x1UL << SYSCTRL_RSTFLAG_WWDT_Pos)
#define SYSCTRL_RSTFLAG_WWDT SYSCTRL_RSTFLAG_WWDT_Msk
#define SYSCTRL_RSTFLAG_LOCKUP_Pos (5U)
#define SYSCTRL_RSTFLAG_LOCKUP_Msk (0x1UL << SYSCTRL_RSTFLAG_LOCKUP_Pos)
#define SYSCTRL_RSTFLAG_LOCKUP SYSCTRL_RSTFLAG_LOCKUP_Msk
#define SYSCTRL_RSTFLAG_SYSREQ_Pos (6U)
#define SYSCTRL_RSTFLAG_SYSREQ_Msk (0x1UL << SYSCTRL_RSTFLAG_SYSREQ_Pos)
#define SYSCTRL_RSTFLAG_SYSREQ SYSCTRL_RSTFLAG_SYSREQ_Msk
#define SYSCTRL_RSTFLAG_RSTB_Pos (7U)
#define SYSCTRL_RSTFLAG_RSTB_Msk (0x1UL << SYSCTRL_RSTFLAG_RSTB_Pos)
#define SYSCTRL_RSTFLAG_RSTB SYSCTRL_RSTFLAG_RSTB_Msk

// SYSCTRL_DBGSTOP
#define SYSCTRL_DBGSTOP_ATIM0_Pos (0U)
#define SYSCTRL_DBGSTOP_ATIM0_Msk (0x1UL << SYSCTRL_DBGSTOP_ATIM0_Pos)
#define SYSCTRL_DBGSTOP_ATIM0 SYSCTRL_DBGSTOP_ATIM0_Msk
#define SYSCTRL_DBGSTOP_ATIM1_Pos (1U)
#define SYSCTRL_DBGSTOP_ATIM1_Msk (0x1UL << SYSCTRL_DBGSTOP_ATIM1_Pos)
#define SYSCTRL_DBGSTOP_ATIM1 SYSCTRL_DBGSTOP_ATIM1_Msk
#define SYSCTRL_DBGSTOP_ATIM2_Pos (2U)
#define SYSCTRL_DBGSTOP_ATIM2_Msk (0x1UL << SYSCTRL_DBGSTOP_ATIM2_Pos)
#define SYSCTRL_DBGSTOP_ATIM2 SYSCTRL_DBGSTOP_ATIM2_Msk
#define SYSCTRL_DBGSTOP_LPTIM_Pos (3U)
#define SYSCTRL_DBGSTOP_LPTIM_Msk (0x1UL << SYSCTRL_DBGSTOP_LPTIM_Pos)
#define SYSCTRL_DBGSTOP_LPTIM SYSCTRL_DBGSTOP_LPTIM_Msk
#define SYSCTRL_DBGSTOP_GTIM0_Pos (4U)
#define SYSCTRL_DBGSTOP_GTIM0_Msk (0x1UL << SYSCTRL_DBGSTOP_GTIM0_Pos)
#define SYSCTRL_DBGSTOP_GTIM0 SYSCTRL_DBGSTOP_GTIM0_Msk
#define SYSCTRL_DBGSTOP_GTIM1_Pos (5U)
#define SYSCTRL_DBGSTOP_GTIM1_Msk (0x1UL << SYSCTRL_DBGSTOP_GTIM1_Pos)
#define SYSCTRL_DBGSTOP_GTIM1 SYSCTRL_DBGSTOP_GTIM1_Msk
#define SYSCTRL_DBGSTOP_CTRIM_Pos (7U)
#define SYSCTRL_DBGSTOP_CTRIM_Msk (0x1UL << SYSCTRL_DBGSTOP_CTRIM_Pos)
#define SYSCTRL_DBGSTOP_CTRIM SYSCTRL_DBGSTOP_CTRIM_Msk
#define SYSCTRL_DBGSTOP_IWDT_Pos (8U)
#define SYSCTRL_DBGSTOP_IWDT_Msk (0x1UL << SYSCTRL_DBGSTOP_IWDT_Pos)
#define SYSCTRL_DBGSTOP_IWDT SYSCTRL_DBGSTOP_IWDT_Msk
#define SYSCTRL_DBGSTOP_RTC_Pos (9U)
#define SYSCTRL_DBGSTOP_RTC_Msk (0x1UL << SYSCTRL_DBGSTOP_RTC_Pos)
#define SYSCTRL_DBGSTOP_RTC SYSCTRL_DBGSTOP_RTC_Msk
#define SYSCTRL_DBGSTOP_TICK_Pos (10U)
#define SYSCTRL_DBGSTOP_TICK_Msk (0x1UL << SYSCTRL_DBGSTOP_TICK_Pos)
#define SYSCTRL_DBGSTOP_TICK SYSCTRL_DBGSTOP_TICK_Msk
#define SYSCTRL_DBGSTOP_ATIM3_Pos (11U)
#define SYSCTRL_DBGSTOP_ATIM3_Msk (0x1UL << SYSCTRL_DBGSTOP_ATIM3_Pos)
#define SYSCTRL_DBGSTOP_ATIM3 SYSCTRL_DBGSTOP_ATIM3_Msk
#define SYSCTRL_DBGSTOP_WWDT_Pos (12U)
#define SYSCTRL_DBGSTOP_WWDT_Msk (0x1UL << SYSCTRL_DBGSTOP_WWDT_Pos)
#define SYSCTRL_DBGSTOP_WWDT SYSCTRL_DBGSTOP_WWDT_Msk

//********************    Bits Define For Peripheral USART    ********************//
// USART_CR1
#define USART_CR1_RE_Pos (0U)
#define USART_CR1_RE_Msk (0x1UL << USART_CR1_RE_Pos)
#define USART_CR1_RE USART_CR1_RE_Msk
#define USART_CR1_TE_Pos (1U)
#define USART_CR1_TE_Msk (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_TE USART_CR1_TE_Msk
#define USART_CR1_PS_Pos (2U)
#define USART_CR1_PS_Msk (0x1UL << USART_CR1_PS_Pos)
#define USART_CR1_PS USART_CR1_PS_Msk
#define USART_CR1_PCE_Pos (3U)
#define USART_CR1_PCE_Msk (0x1UL << USART_CR1_PCE_Pos)
#define USART_CR1_PCE USART_CR1_PCE_Msk
#define USART_CR1_CHLEN_Pos (4U)
#define USART_CR1_CHLEN_Msk (0x1UL << USART_CR1_CHLEN_Pos)
#define USART_CR1_CHLEN USART_CR1_CHLEN_Msk
#define USART_CR1_STOP_Pos (5U)
#define USART_CR1_STOP_Msk (0x1UL << USART_CR1_STOP_Pos)
#define USART_CR1_STOP USART_CR1_STOP_Msk
#define USART_CR1_MSB_Pos (6U)
#define USART_CR1_MSB_Msk (0x1UL << USART_CR1_MSB_Pos)
#define USART_CR1_MSB USART_CR1_MSB_Msk
#define USART_CR1_OVER8_Pos (7U)
#define USART_CR1_OVER8_Msk (0x1UL << USART_CR1_OVER8_Pos)
#define USART_CR1_OVER8 USART_CR1_OVER8_Msk
#define USART_CR1_TOE_Pos (8U)
#define USART_CR1_TOE_Msk (0x7UL << USART_CR1_TOE_Pos)
#define USART_CR1_TOE USART_CR1_TOE_Msk
#define USART_CR1_SBS_Pos (11U)
#define USART_CR1_SBS_Msk (0x1UL << USART_CR1_SBS_Pos)
#define USART_CR1_SBS USART_CR1_SBS_Msk
#define USART_CR1_COMB_Pos (12U)
#define USART_CR1_COMB_Msk (0x1UL << USART_CR1_COMB_Pos)
#define USART_CR1_COMB USART_CR1_COMB_Msk
#define USART_CR1_MPE_Pos (13U)
#define USART_CR1_MPE_Msk (0x1UL << USART_CR1_MPE_Pos)
#define USART_CR1_MPE USART_CR1_MPE_Msk
#define USART_CR1_SLME_Pos (14U)
#define USART_CR1_SLME_Msk (0x1UL << USART_CR1_SLME_Pos)
#define USART_CR1_SLME USART_CR1_SLME_Msk

// USART_CR2
#define USART_CR2_RXDMAEN_Pos (0U)
#define USART_CR2_RXDMAEN_Msk (0x1UL << USART_CR2_RXDMAEN_Pos)
#define USART_CR2_RXDMAEN USART_CR2_RXDMAEN_Msk
#define USART_CR2_TXDMAEN_Pos (1U)
#define USART_CR2_TXDMAEN_Msk (0x1UL << USART_CR2_TXDMAEN_Pos)
#define USART_CR2_TXDMAEN USART_CR2_TXDMAEN_Msk
#define USART_CR2_RTSEN_Pos (2U)
#define USART_CR2_RTSEN_Msk (0x1UL << USART_CR2_RTSEN_Pos)
#define USART_CR2_RTSEN USART_CR2_RTSEN_Msk
#define USART_CR2_CTSEN_Pos (3U)
#define USART_CR2_CTSEN_Msk (0x1UL << USART_CR2_CTSEN_Pos)
#define USART_CR2_CTSEN USART_CR2_CTSEN_Msk
#define USART_CR2_RXINV_Pos (4U)
#define USART_CR2_RXINV_Msk (0x1UL << USART_CR2_RXINV_Pos)
#define USART_CR2_RXINV USART_CR2_RXINV_Msk
#define USART_CR2_TXINV_Pos (5U)
#define USART_CR2_TXINV_Msk (0x1UL << USART_CR2_TXINV_Pos)
#define USART_CR2_TXINV USART_CR2_TXINV_Msk
#define USART_CR2_SYNC_Pos (6U)
#define USART_CR2_SYNC_Msk (0x1UL << USART_CR2_SYNC_Pos)
#define USART_CR2_SYNC USART_CR2_SYNC_Msk
#define USART_CR2_SWAP_Pos (7U)
#define USART_CR2_SWAP_Msk (0x1UL << USART_CR2_SWAP_Pos)
#define USART_CR2_SWAP USART_CR2_SWAP_Msk
#define USART_CR2_CLKC_Pos (8U)
#define USART_CR2_CLKC_Msk (0x3UL << USART_CR2_CLKC_Pos)
#define USART_CR2_CLKC USART_CR2_CLKC_Msk

// USART_CR3
#define USART_CR3_LINEN_Pos (0U)
#define USART_CR3_LINEN_Msk (0x1UL << USART_CR3_LINEN_Pos)
#define USART_CR3_LINEN USART_CR3_LINEN_Msk
#define USART_CR3_LBDE_Pos (1U)
#define USART_CR3_LBDE_Msk (0x1UL << USART_CR3_LBDE_Pos)
#define USART_CR3_LBDE USART_CR3_LBDE_Msk
#define USART_CR3_ABRE_Pos (2U)
#define USART_CR3_ABRE_Msk (0x1UL << USART_CR3_ABRE_Pos)
#define USART_CR3_ABRE USART_CR3_ABRE_Msk
#define USART_CR3_BREAK_Pos (3U)
#define USART_CR3_BREAK_Msk (0x1UL << USART_CR3_BREAK_Pos)
#define USART_CR3_BREAK USART_CR3_BREAK_Msk
#define USART_CR3_SCEN_Pos (4U)
#define USART_CR3_SCEN_Msk (0x1UL << USART_CR3_SCEN_Pos)
#define USART_CR3_SCEN USART_CR3_SCEN_Msk
#define USART_CR3_BCN_Pos (5U)
#define USART_CR3_BCN_Msk (0x7UL << USART_CR3_BCN_Pos)
#define USART_CR3_BCN USART_CR3_BCN_Msk
#define USART_CR3_SMCPU_Pos (8U)
#define USART_CR3_SMCPU_Msk (0x3UL << USART_CR3_SMCPU_Pos)
#define USART_CR3_SMCPU USART_CR3_SMCPU_Msk
#define USART_CR3_IREN_Pos (13U)
#define USART_CR3_IREN_Msk (0x1UL << USART_CR3_IREN_Pos)
#define USART_CR3_IREN USART_CR3_IREN_Msk
#define USART_CR3_IRCW_Pos (14U)
#define USART_CR3_IRCW_Msk (0x1UL << USART_CR3_IRCW_Pos)
#define USART_CR3_IRCW USART_CR3_IRCW_Msk
#define USART_CR3_IRMOD_Pos (15U)
#define USART_CR3_IRMOD_Msk (0x1UL << USART_CR3_IRMOD_Pos)
#define USART_CR3_IRMOD USART_CR3_IRMOD_Msk

// USART_BRR
#define USART_BRR_DIVF_Pos (0U)
#define USART_BRR_DIVF_Msk (0x7FUL << USART_BRR_DIVF_Pos)
#define USART_BRR_DIVF USART_BRR_DIVF_Msk
#define USART_BRR_FBME_Pos (7U)
#define USART_BRR_FBME_Msk (0x1UL << USART_BRR_FBME_Pos)
#define USART_BRR_FBME USART_BRR_FBME_Msk
#define USART_BRR_DIVI_Pos (8U)
#define USART_BRR_DIVI_Msk (0xFFUL << USART_BRR_DIVI_Pos)
#define USART_BRR_DIVI USART_BRR_DIVI_Msk
#define USART_BRR_PSC_Pos (16U)
#define USART_BRR_PSC_Msk (0x3UL << USART_BRR_PSC_Pos)
#define USART_BRR_PSC USART_BRR_PSC_Msk

// USART_TOR
#define USART_TOR_TOR_Pos (0U)
#define USART_TOR_TOR_Msk (0xFFFFFUL << USART_TOR_TOR_Pos)
#define USART_TOR_TOR USART_TOR_TOR_Msk

// USART_SR
#define USART_SR_TXE_Pos (0U)
#define USART_SR_TXE_Msk (0x1UL << USART_SR_TXE_Pos)
#define USART_SR_TXE USART_SR_TXE_Msk
#define USART_SR_TC_Pos (1U)
#define USART_SR_TC_Msk (0x1UL << USART_SR_TC_Pos)
#define USART_SR_TC USART_SR_TC_Msk
#define USART_SR_RC_Pos (2U)
#define USART_SR_RC_Msk (0x1UL << USART_SR_RC_Pos)
#define USART_SR_RC USART_SR_RC_Msk
#define USART_SR_PE_Pos (3U)
#define USART_SR_PE_Msk (0x1UL << USART_SR_PE_Pos)
#define USART_SR_PE USART_SR_PE_Msk
#define USART_SR_FE_Pos (4U)
#define USART_SR_FE_Msk (0x1UL << USART_SR_FE_Pos)
#define USART_SR_FE USART_SR_FE_Msk
#define USART_SR_OR_Pos (5U)
#define USART_SR_OR_Msk (0x1UL << USART_SR_OR_Pos)
#define USART_SR_OR USART_SR_OR_Msk
#define USART_SR_TO_Pos (6U)
#define USART_SR_TO_Msk (0x1UL << USART_SR_TO_Pos)
#define USART_SR_TO USART_SR_TO_Msk
#define USART_SR_MPB_Pos (8U)
#define USART_SR_MPB_Msk (0x1UL << USART_SR_MPB_Pos)
#define USART_SR_MPB USART_SR_MPB_Msk
#define USART_SR_AM_Pos (9U)
#define USART_SR_AM_Msk (0x1UL << USART_SR_AM_Pos)
#define USART_SR_AM USART_SR_AM_Msk
#define USART_SR_CTSV_Pos (10U)
#define USART_SR_CTSV_Msk (0x1UL << USART_SR_CTSV_Pos)
#define USART_SR_CTSV USART_SR_CTSV_Msk
#define USART_SR_CTS_Pos (11U)
#define USART_SR_CTS_Msk (0x1UL << USART_SR_CTS_Pos)
#define USART_SR_CTS USART_SR_CTS_Msk
#define USART_SR_ABR_Pos (12U)
#define USART_SR_ABR_Msk (0x1UL << USART_SR_ABR_Pos)
#define USART_SR_ABR USART_SR_ABR_Msk
#define USART_SR_LBD_Pos (13U)
#define USART_SR_LBD_Msk (0x1UL << USART_SR_LBD_Pos)
#define USART_SR_LBD USART_SR_LBD_Msk
#define USART_SR_DWK_Pos (14U)
#define USART_SR_DWK_Msk (0x1UL << USART_SR_DWK_Pos)
#define USART_SR_DWK USART_SR_DWK_Msk

// USART_TDR
#define USART_TDR_TDR_Pos (0U)
#define USART_TDR_TDR_Msk (0x1FFUL << USART_TDR_TDR_Pos)
#define USART_TDR_TDR USART_TDR_TDR_Msk
#define USART_TDR_MPID_Pos (9U)
#define USART_TDR_MPID_Msk (0x1UL << USART_TDR_MPID_Pos)
#define USART_TDR_MPID USART_TDR_MPID_Msk

// USART_IER
#define USART_IER_TXE_Pos (0U)
#define USART_IER_TXE_Msk (0x1UL << USART_IER_TXE_Pos)
#define USART_IER_TXE USART_IER_TXE_Msk
#define USART_IER_TC_Pos (1U)
#define USART_IER_TC_Msk (0x1UL << USART_IER_TC_Pos)
#define USART_IER_TC USART_IER_TC_Msk
#define USART_IER_RC_Pos (2U)
#define USART_IER_RC_Msk (0x1UL << USART_IER_RC_Pos)
#define USART_IER_RC USART_IER_RC_Msk
#define USART_IER_PE_Pos (3U)
#define USART_IER_PE_Msk (0x1UL << USART_IER_PE_Pos)
#define USART_IER_PE USART_IER_PE_Msk
#define USART_IER_FE_Pos (4U)
#define USART_IER_FE_Msk (0x1UL << USART_IER_FE_Pos)
#define USART_IER_FE USART_IER_FE_Msk
#define USART_IER_OR_Pos (5U)
#define USART_IER_OR_Msk (0x1UL << USART_IER_OR_Pos)
#define USART_IER_OR USART_IER_OR_Msk
#define USART_IER_TO_Pos (6U)
#define USART_IER_TO_Msk (0x1UL << USART_IER_TO_Pos)
#define USART_IER_TO USART_IER_TO_Msk
#define USART_IER_AM_Pos (9U)
#define USART_IER_AM_Msk (0x1UL << USART_IER_AM_Pos)
#define USART_IER_AM USART_IER_AM_Msk
#define USART_IER_CTS_Pos (11U)
#define USART_IER_CTS_Msk (0x1UL << USART_IER_CTS_Pos)
#define USART_IER_CTS USART_IER_CTS_Msk
#define USART_IER_ABR_Pos (12U)
#define USART_IER_ABR_Msk (0x1UL << USART_IER_ABR_Pos)
#define USART_IER_ABR USART_IER_ABR_Msk
#define USART_IER_LBD_Pos (13U)
#define USART_IER_LBD_Msk (0x1UL << USART_IER_LBD_Pos)
#define USART_IER_LBD USART_IER_LBD_Msk
#define USART_IER_DWK_Pos (14U)
#define USART_IER_DWK_Msk (0x1UL << USART_IER_DWK_Pos)
#define USART_IER_DWK USART_IER_DWK_Msk

// USART_ICR
#define USART_ICR_TC_Pos (1U)
#define USART_ICR_TC_Msk (0x1UL << USART_ICR_TC_Pos)
#define USART_ICR_TC USART_ICR_TC_Msk
#define USART_ICR_RC_Pos (2U)
#define USART_ICR_RC_Msk (0x1UL << USART_ICR_RC_Pos)
#define USART_ICR_RC USART_ICR_RC_Msk
#define USART_ICR_PE_Pos (3U)
#define USART_ICR_PE_Msk (0x1UL << USART_ICR_PE_Pos)
#define USART_ICR_PE USART_ICR_PE_Msk
#define USART_ICR_FE_Pos (4U)
#define USART_ICR_FE_Msk (0x1UL << USART_ICR_FE_Pos)
#define USART_ICR_FE USART_ICR_FE_Msk
#define USART_ICR_OR_Pos (5U)
#define USART_ICR_OR_Msk (0x1UL << USART_ICR_OR_Pos)
#define USART_ICR_OR USART_ICR_OR_Msk
#define USART_ICR_TO_Pos (6U)
#define USART_ICR_TO_Msk (0x1UL << USART_ICR_TO_Pos)
#define USART_ICR_TO USART_ICR_TO_Msk
#define USART_ICR_AM_Pos (9U)
#define USART_ICR_AM_Msk (0x1UL << USART_ICR_AM_Pos)
#define USART_ICR_AM USART_ICR_AM_Msk
#define USART_ICR_CTS_Pos (11U)
#define USART_ICR_CTS_Msk (0x1UL << USART_ICR_CTS_Pos)
#define USART_ICR_CTS USART_ICR_CTS_Msk
#define USART_ICR_ABR_Pos (12U)
#define USART_ICR_ABR_Msk (0x1UL << USART_ICR_ABR_Pos)
#define USART_ICR_ABR USART_ICR_ABR_Msk
#define USART_ICR_LBD_Pos (13U)
#define USART_ICR_LBD_Msk (0x1UL << USART_ICR_LBD_Pos)
#define USART_ICR_LBD USART_ICR_LBD_Msk
#define USART_ICR_DWK_Pos (14U)
#define USART_ICR_DWK_Msk (0x1UL << USART_ICR_DWK_Pos)
#define USART_ICR_DWK USART_ICR_DWK_Msk

// USART_RDR
#define USART_RDR_RDR_Pos (0U)
#define USART_RDR_RDR_Msk (0x1FFUL << USART_RDR_RDR_Pos)
#define USART_RDR_RDR USART_RDR_RDR_Msk

// USART_ADDR
#define USART_ADDR_ADDR_Pos (0U)
#define USART_ADDR_ADDR_Msk (0xFFUL << USART_ADDR_ADDR_Pos)
#define USART_ADDR_ADDR USART_ADDR_ADDR_Msk

// USART_ADDMR
#define USART_ADDMR_ADDM_Pos (0U)
#define USART_ADDMR_ADDM_Msk (0xFFUL << USART_ADDMR_ADDM_Pos)
#define USART_ADDMR_ADDM USART_ADDMR_ADDM_Msk

// USART_BDR
#define USART_BDR_BDR_Pos (0U)
#define USART_BDR_BDR_Msk (0xFFFUL << USART_BDR_BDR_Pos)
#define USART_BDR_BDR USART_BDR_BDR_Msk

// USART_IR
#define USART_IR_DCNTL_Pos (0U)
#define USART_IR_DCNTL_Msk (0x7FFUL << USART_IR_DCNTL_Pos)
#define USART_IR_DCNTL USART_IR_DCNTL_Msk
#define USART_IR_DCNTH_Pos (16U)
#define USART_IR_DCNTH_Msk (0x7FFUL << USART_IR_DCNTH_Pos)
#define USART_IR_DCNTH USART_IR_DCNTH_Msk

//********************    Bits Define For Peripheral VC    ********************//
// VC_CR0
#define VC_CR0_DIV_Pos (0U)
#define VC_CR0_DIV_Msk (0x3FUL << VC_CR0_DIV_Pos)
#define VC_CR0_DIV VC_CR0_DIV_Msk
#define VC_CR0_DIVEN_Pos (6U)
#define VC_CR0_DIVEN_Msk (0x1UL << VC_CR0_DIVEN_Pos)
#define VC_CR0_DIVEN VC_CR0_DIVEN_Msk
#define VC_CR0_REF_Pos (7U)
#define VC_CR0_REF_Msk (0x1UL << VC_CR0_REF_Pos)
#define VC_CR0_REF VC_CR0_REF_Msk
#define VC_CR0_BIAS_Pos (8U)
#define VC_CR0_BIAS_Msk (0x3UL << VC_CR0_BIAS_Pos)
#define VC_CR0_BIAS VC_CR0_BIAS_Msk
#define VC_CR0_HYS_Pos (10U)
#define VC_CR0_HYS_Msk (0x3UL << VC_CR0_HYS_Pos)
#define VC_CR0_HYS VC_CR0_HYS_Msk

// VC_CR1
#define VC_CR1_PSEL_Pos (0U)
#define VC_CR1_PSEL_Msk (0xFUL << VC_CR1_PSEL_Pos)
#define VC_CR1_PSEL VC_CR1_PSEL_Msk
#define VC_CR1_NSEL_Pos (4U)
#define VC_CR1_NSEL_Msk (0xFUL << VC_CR1_NSEL_Pos)
#define VC_CR1_NSEL VC_CR1_NSEL_Msk
#define VC_CR1_FLTEN_Pos (8U)
#define VC_CR1_FLTEN_Msk (0x1UL << VC_CR1_FLTEN_Pos)
#define VC_CR1_FLTEN VC_CR1_FLTEN_Msk
#define VC_CR1_FLTTIME_Pos (9U)
#define VC_CR1_FLTTIME_Msk (0x7UL << VC_CR1_FLTTIME_Pos)
#define VC_CR1_FLTTIME VC_CR1_FLTTIME_Msk
#define VC_CR1_FALLING_Pos (12U)
#define VC_CR1_FALLING_Msk (0x1UL << VC_CR1_FALLING_Pos)
#define VC_CR1_FALLING VC_CR1_FALLING_Msk
#define VC_CR1_RISING_Pos (13U)
#define VC_CR1_RISING_Msk (0x1UL << VC_CR1_RISING_Pos)
#define VC_CR1_RISING VC_CR1_RISING_Msk
#define VC_CR1_LEVEL_Pos (14U)
#define VC_CR1_LEVEL_Msk (0x1UL << VC_CR1_LEVEL_Pos)
#define VC_CR1_LEVEL VC_CR1_LEVEL_Msk
#define VC_CR1_IE_Pos (15U)
#define VC_CR1_IE_Msk (0x1UL << VC_CR1_IE_Pos)
#define VC_CR1_IE VC_CR1_IE_Msk
#define VC_CR1_EN_Pos (16U)
#define VC_CR1_EN_Msk (0x1UL << VC_CR1_EN_Pos)
#define VC_CR1_EN VC_CR1_EN_Msk
#define VC_CR1_FLTCLK_Pos (17U)
#define VC_CR1_FLTCLK_Msk (0x1UL << VC_CR1_FLTCLK_Pos)
#define VC_CR1_FLTCLK VC_CR1_FLTCLK_Msk

// VC_CR2
#define VC_CR2_POL_Pos (0U)
#define VC_CR2_POL_Msk (0x1UL << VC_CR2_POL_Pos)
#define VC_CR2_POL VC_CR2_POL_Msk
#define VC_CR2_ATIM0CLR_Pos (1U)
#define VC_CR2_ATIM0CLR_Msk (0x1UL << VC_CR2_ATIM0CLR_Pos)
#define VC_CR2_ATIM0CLR VC_CR2_ATIM0CLR_Msk
#define VC_CR2_ATIM1CLR_Pos (2U)
#define VC_CR2_ATIM1CLR_Msk (0x1UL << VC_CR2_ATIM1CLR_Pos)
#define VC_CR2_ATIM1CLR VC_CR2_ATIM1CLR_Msk
#define VC_CR2_ATIM2CLR_Pos (3U)
#define VC_CR2_ATIM2CLR_Msk (0x1UL << VC_CR2_ATIM2CLR_Pos)
#define VC_CR2_ATIM2CLR VC_CR2_ATIM2CLR_Msk
#define VC_CR2_ATIM3CLR_Pos (4U)
#define VC_CR2_ATIM3CLR_Msk (0x1UL << VC_CR2_ATIM3CLR_Pos)
#define VC_CR2_ATIM3CLR VC_CR2_ATIM3CLR_Msk
#define VC_CR2_ATIMBK_Pos (5U)
#define VC_CR2_ATIMBK_Msk (0x1UL << VC_CR2_ATIMBK_Pos)
#define VC_CR2_ATIMBK VC_CR2_ATIMBK_Msk
#define VC_CR2_WINDOW_Pos (6U)
#define VC_CR2_WINDOW_Msk (0x1UL << VC_CR2_WINDOW_Pos)
#define VC_CR2_WINDOW VC_CR2_WINDOW_Msk

// VC_SR
#define VC_SR_INTF_Pos (0U)
#define VC_SR_INTF_Msk (0x1UL << VC_SR_INTF_Pos)
#define VC_SR_INTF VC_SR_INTF_Msk
#define VC_SR_FLTV_Pos (1U)
#define VC_SR_FLTV_Msk (0x1UL << VC_SR_FLTV_Pos)
#define VC_SR_FLTV VC_SR_FLTV_Msk

//********************    Bits Define For Peripheral WWDT    ********************//
// WWDT_CR0
#define WWDT_CR0_WCNT_Pos (0U)
#define WWDT_CR0_WCNT_Msk (0x7FUL << WWDT_CR0_WCNT_Pos)
#define WWDT_CR0_WCNT WWDT_CR0_WCNT_Msk
#define WWDT_CR0_EN_Pos (7U)
#define WWDT_CR0_EN_Msk (0x1UL << WWDT_CR0_EN_Pos)
#define WWDT_CR0_EN WWDT_CR0_EN_Msk

// WWDT_CR1
#define WWDT_CR1_WINR_Pos (0U)
#define WWDT_CR1_WINR_Msk (0x7FUL << WWDT_CR1_WINR_Pos)
#define WWDT_CR1_WINR WWDT_CR1_WINR_Msk
#define WWDT_CR1_IE_Pos (9U)
#define WWDT_CR1_IE_Msk (0x1UL << WWDT_CR1_IE_Pos)
#define WWDT_CR1_IE WWDT_CR1_IE_Msk
#define WWDT_CR1_PRS_Pos (11U)
#define WWDT_CR1_PRS_Msk (0x7UL << WWDT_CR1_PRS_Pos)
#define WWDT_CR1_PRS WWDT_CR1_PRS_Msk

// WWDT_SR
#define WWDT_SR_POV_Pos (0U)
#define WWDT_SR_POV_Msk (0x1UL << WWDT_SR_POV_Pos)
#define WWDT_SR_POV WWDT_SR_POV_Msk

#ifdef __cplusplus
}
#endif

#endif /* __HC32A052_H__ */
