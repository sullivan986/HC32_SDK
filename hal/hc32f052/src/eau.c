/**
 *******************************************************************************
 * @file  eau.c
 * @brief This file provides firmware functions to manage the EAU.
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
#include "eau.h"


/**
 * @addtogroup HC32F052_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_EAU EAU模块驱动库
 * @brief EAU Driver Library EAU模块驱动库
 * @{
 */


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EAU_Local_Macros EAU局部宏定义
 * @{
 */
/**
 * @defgroup EAU_Timeout EAU 超时时间
 * @{
 */
#define EAU_TIMEOUT_SQRT        (17U)   /*!< 开方运算需要17个HCLK周期 */
#define EAU_TIMEOUT_DIV         (35U)   /*!< 除法运算需要2到35个HCLK周期 */
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
 * @defgroup EAU_Global_Functions EAU全局函数定义
 * @{
 */


/**
 * @brief  开方运算函数
 * @param  [in] u32A: 被开方数
 * @param  [out] pu32X: 平方根结果输出指针
 * @param  [out] pu32Y: 余数结果输出指针
 * @retval en_eau_status_t: 运算状态 @ref en_eau_status_t
 */
en_eau_status_t EAU_Sqrt(uint32_t u32A, uint32_t *pu32X, uint32_t *pu32Y)
{
    uint16_t timeout = 0U;

    if((pu32X == NULL) || (pu32Y ==NULL))
    {
        return EauErrPara;
    }

    HC_EAU->CSR_f.MODE = EAU_MODE_SQRT;
    HC_EAU->DIVIDEND = u32A;
    while(HC_EAU->CSR_f.BUSY)
    {
        timeout ++;
        if(timeout > EAU_TIMEOUT_SQRT)
        {
            return EauErrTimeout;
        }
    }

    *pu32X = HC_EAU->QUOTIENT;
    *pu32Y = HC_EAU->REMAINDER;

    return EauOk;
}


/**
 * @brief  无符号除法运算函数
 * @param  [in] u32A: 被除数
 * @param  [in] u32B: 除数
 * @param  [out] pu32X: 商结果输出指针
 * @param  [out] pu32Y: 余数结果输出指针
 * @retval en_eau_status_t: 运算状态 @ref en_eau_status_t
 */
en_eau_status_t EAU_UnsignDiv(uint32_t u32A, uint32_t u32B, uint32_t *pu32X, uint32_t *pu32Y)
{
    uint16_t timeout = 0U;

    if((pu32X == NULL) || (pu32Y ==NULL))
    {
        return EauErrPara;
    }

    HC_EAU->CSR_f.MODE = EAU_MODE_UNSIGN_DIV;

#if 0 /* CSR_f.ZERO可以判断除数是否为0 */
    if(u32B == 0U)
    {
        return EauErrZero;
    }
#endif
    HC_EAU->DIVIDEND = u32A;
    HC_EAU->DIVISOR = u32B;
    while(HC_EAU->CSR_f.BUSY)
    {
        timeout ++;
        if(timeout > EAU_TIMEOUT_DIV)
        {
            return EauErrTimeout;
        }
    }

    *pu32X = HC_EAU->QUOTIENT;
    *pu32Y = HC_EAU->REMAINDER;

    if(HC_EAU->CSR_f.ZERO)
    {
        return EauErrZero;
    }

    return EauOk;
}


/**
 * @brief  有符号除法运算函数
 * @param  [in] s32A: 被除数
 * @param  [in] s32B: 除数
 * @param  [out] ps32X: 商结果输出指针
 * @param  [out] ps32Y: 余数结果输出指针
 * @retval en_eau_status_t: 运算状态 @ref en_eau_status_t
 */
en_eau_status_t EAU_SignDiv(int32_t s32A, int32_t s32B, int32_t *ps32X, int32_t *ps32Y)
{
    uint16_t timeout = 0U;

    if((ps32X == NULL) || (ps32Y ==NULL))
    {
        return EauErrPara;
    }

    HC_EAU->CSR_f.MODE = EAU_MODE_SIGN_DIV;

#if 0 /* CSR_f.ZERO可以判断除数是否为0 */
    if(s32B == 0U)
    {
        return EauErrZero;
    }
#endif

    HC_EAU->DIVIDEND = (uint32_t)s32A;
    HC_EAU->DIVISOR = (uint32_t)s32B;
    while(HC_EAU->CSR_f.BUSY)
    {
        timeout ++;
        if(timeout > EAU_TIMEOUT_DIV)
        {
            return EauErrTimeout;
        }
    }

    *ps32X = (int32_t)HC_EAU->QUOTIENT;
    *ps32Y = (int32_t)HC_EAU->REMAINDER;

    if(HC_EAU->CSR_f.ZERO)
    {
        return EauErrZero;
    }
    else if(HC_EAU->CSR_f.OVR)
    {
        return EauErrOverflow;
    }
    else
    {
        return EauOk;
    }
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
