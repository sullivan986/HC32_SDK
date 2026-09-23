/**
 *******************************************************************************
 * @file  eau.h
 * @brief This file contains all the functions prototypes of the eau driver
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
#ifndef __EAU_H__
#define __EAU_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32A052_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_EAU EAU模块驱动库
 * @{
 */


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EAU_Global_Types EAU全局类型定义
 * @{
 */
/**
 * @brief  EAU 运算状态定义
 */
typedef enum
{
    EauOk           = 0U, /*!< EAU计算正常 */
    EauErrTimeout   = 1U, /*!< EAU计算超时错误 */
    EauErrZero      = 2U, /*!< EAU除法运算除数为0错误 */
    EauErrOverflow  = 3U, /*!< EAU有符号除法运算溢出错误，商超出32位有符号数编码范围 */
    EauErrPara      = 4U, /*!< EAU参数错误 指针为空*/
}en_eau_status_t;



/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EAU_Global_Macros EAU全局宏定义
 * @{
 */


/**
 * @defgroup EAU_Mode EAU 运算模式
 * @{
 */
#define EAU_MODE_UNSIGN_DIV     (0x0U)  /*!< 无符号除法运算 */
#define EAU_MODE_SIGN_DIV       (0x1U)  /*!< 有符号除法运算 */
#define EAU_MODE_SQRT           (0x2U)  /*!< 开方运算 */
/**
 * @}
 */



/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EAU_Global_Functions EAU全局函数定义
 * @{
 */

en_eau_status_t EAU_Sqrt(uint32_t u32A, uint32_t *pu32X, uint32_t *pu32Y);
en_eau_status_t EAU_UnsignDiv(uint32_t u32A, uint32_t u32B, uint32_t *pu32X, uint32_t *pu32Y);
en_eau_status_t EAU_SignDiv(int32_t s32A, int32_t s32B, int32_t *ps32X, int32_t *ps32Y);

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

#endif /* __EAU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
