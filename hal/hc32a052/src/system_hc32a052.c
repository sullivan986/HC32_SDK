/**
 *******************************************************************************
 * @file  system_hc32a052.c
 * @brief System clock initialization
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
#include "base_types.h"
#include "hc32a052.h"
#include "system_hc32a052.h"
#include "sysctrl.h"

/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
uint32_t SystemCoreClock = 4000000u;
uint32_t SystemHCLK      = 4000000u;
uint32_t SystemPCLK      = 4000000u;

/*!< Update SystemCoreClock variable */
void SystemCoreClockUpdate (void)
{
//    SystemCoreClock = Sysctrl_GetHClkFreq();
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

/**
 * @brief  Setup the microcontroller system. Initialize the System and update
 * - the SystemCoreClock variable.
 *
 * @retval None
 */
void SystemInit(void)
{
    //*(volatile uint32_t *)0x40002380  = 0x07u;
    HC_SYSCTRL->RCLTRIM_f.TRIM  = SYSCTRL_RCL_TRIM_32p8KHz; 
    HC_SYSCTRL->RCHTRIM         = SYSCTRL_RCH_TRIM_12MHz;
    HC_SYSCTRL->RCHCR_f.DIV  = 2u;
    SystemCoreClockUpdate();
}


#if defined (__CC_ARM)
extern int32_t $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    SystemInit();
    $Super$$main();
    return 0;
}
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
extern int32_t $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    SystemInit();
    $Super$$main();
    return 0;
}
#elif defined(__ICCARM__)
extern int32_t main(void);
/* __low_level_init will auto called by IAR cstartup */
extern void __iar_data_init3(void);
int __low_level_init(void)
{
    /*!< call IAR table copy function */
    __iar_data_init3();
    SystemInit();
    main();
    return 0;
}
#endif

