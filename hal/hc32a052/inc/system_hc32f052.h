/**
 *******************************************************************************
 * @file  system_hc32a052.h
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

#ifndef __SYSTEM_HC32A052_H__
#define __SYSTEM_HC32A052_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
#define HWWD_DISABLE        (1)


#if defined(__ICCARM__)
  
    #include "HC32A052_CONFIG.h"  
    #if !defined(HC32A052JAxA) && !defined(HC32A052FAxA) && !defined(HC32A052J8xA) && !defined(HC32A052F8xA)
        #error "Unknown devices"
    #endif  
#endif 

/**
 ******************************************************************************
 ** \brief Clock Setup macro definition
 **
 ** - 0: CLOCK_SETTING_NONE  - User provides own clock setting in application
 ** - 1: CLOCK_SETTING_CMSIS - 
 ******************************************************************************/
#define CLOCK_SETTING_NONE  0u
#define CLOCK_SETTING_CMSIS 1u


/******************************************************************************/
/*                                                                            */
/*                      START OF USER SETTINGS HERE                           */
/*                      ===========================                           */
/*                                                                            */
/*                 All lines with '<<<' can be set by user.                   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/


extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)
extern void SystemInit (void);            // Initialize the system
extern void SystemCoreClockUpdate (void); // Update SystemCoreClock variable

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_HC32F420 _H__ */







