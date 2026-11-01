/**
 *******************************************************************************
 * @file  config.cpp
 * @brief HC32F005 系统时钟初始化
 *
 * 把 config.h 的 constexpr 配置翻译成厂商 Sysctrl_* 调用, 并提供 C 符号:
 *   SystemInit / SystemCoreClockUpdate / SystemCoreClock
 *
 * F005 无 PLL, 主频由 RCH 档位或外部晶振直接决定.
 * 下方 static_assert 强制校验 board::* 与 en_sysctrl_* 数值一致.
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
 */

#include "driver.h"

#include <cstdint>
#include <type_traits>
#include <utility>

namespace
{

using namespace hc32::board;

/* board::* 与厂商 en_sysctrl_* 数值必须相同, 才能一次 static_cast 互转 */
static_assert(static_cast<int>(ClockSource::Rch) == static_cast<int>(SysctrlClkRCH));
static_assert(static_cast<int>(ClockSource::Xth) == static_cast<int>(SysctrlClkXTH));
static_assert(static_cast<int>(ClockSource::Rcl) == static_cast<int>(SysctrlClkRCL));
static_assert(static_cast<int>(ClockSource::Xtl) == static_cast<int>(SysctrlClkXTL));

/* RCH 枚举值就是档位索引 (Sysctrl_SetRCHTrim 用它索引 TRIM 表), 不可改动 */
static_assert(static_cast<int>(RchFreq::Mhz24) == static_cast<int>(SysctrlRchFreq24MHz));
static_assert(static_cast<int>(RchFreq::Mhz22_12) == static_cast<int>(SysctrlRchFreq22_12MHz));
static_assert(static_cast<int>(RchFreq::Mhz16) == static_cast<int>(SysctrlRchFreq16MHz));
static_assert(static_cast<int>(RchFreq::Mhz8) == static_cast<int>(SysctrlRchFreq8MHz));
static_assert(static_cast<int>(RchFreq::Mhz4) == static_cast<int>(SysctrlRchFreq4MHz));

static_assert(static_cast<int>(RclFreq::Hz38400) == static_cast<int>(SysctrlRclFreq38400));
static_assert(static_cast<int>(RclFreq::Hz32768) == static_cast<int>(SysctrlRclFreq32768));

static_assert(static_cast<int>(XthRange::Mhz4_6) == static_cast<int>(SysctrlXthFreq4_6MHz));
static_assert(static_cast<int>(XthRange::Mhz6_12) == static_cast<int>(SysctrlXthFreq6_12MHz));
static_assert(static_cast<int>(XthRange::Mhz12_20) == static_cast<int>(SysctrlXthFreq12_20MHz));
static_assert(static_cast<int>(XthRange::Mhz20_32) == static_cast<int>(SysctrlXthFreq20_32MHz));

static_assert(static_cast<int>(Drive::Drive0) == static_cast<int>(SysctrlXtalDriver0));
static_assert(static_cast<int>(Drive::Drive3) == static_cast<int>(SysctrlXtalDriver3));

static_assert(static_cast<int>(XthCycle::Cycle256) == static_cast<int>(SysctrlXthStableCycle256));
static_assert(static_cast<int>(XthCycle::Cycle16384) == static_cast<int>(SysctrlXthStableCycle16384));

static_assert(static_cast<int>(HclkDiv::Div1) == static_cast<int>(SysctrlHclkDiv1));
static_assert(static_cast<int>(HclkDiv::Div128) == static_cast<int>(SysctrlHclkDiv128));
static_assert(static_cast<int>(PclkDiv::Div1) == static_cast<int>(SysctrlPclkDiv1));
static_assert(static_cast<int>(PclkDiv::Div8) == static_cast<int>(SysctrlPclkDiv8));

/* ==========================================================================
 * 工具函数
 * ========================================================================== */

/// enum class -> 厂商枚举
template <typename VendorEnum, typename E> constexpr VendorEnum to_vendor(E e) noexcept
{
    return static_cast<VendorEnum>(std::to_underlying(e));
}

/// HCLK -> Flash 读等待周期 (F005 只有 0/1 两档; >24 MHz 必须为 1)
[[nodiscard]] constexpr en_flash_waitcycle_t flash_wait_for(std::uint32_t hz) noexcept
{
    return (hz > 24000000u) ? FlashWaitCycle1 : FlashWaitCycle0;
}

} // namespace

/* ==========================================================================
 * C 链接接口 (startup.s / driver.cpp / 应用代码)
 * ========================================================================== */
extern "C"
{

    /* 复位默认 RCH 4MHz. 必须早于 SystemInit 就有效:
     * Sysctrl_ClkSourceEnable 内部的 delay1ms 读的就是 SystemCoreClock */
    uint32_t SystemCoreClock = 4000000u;

    void SystemCoreClockUpdate(void)
    {
        SystemCoreClock = Sysctrl_GetHClkFreq();

        /* SysTick 作自由计数器 (delay 依赖它, 不开中断) */
        SysTick->LOAD = 0xFFFFFFu;
        SysTick->VAL = 0u;
        SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    }

    void SystemInit(void)
    {
        (void)Sysctrl_SetRCHTrim(to_vendor<en_sysctrl_rch_freq_t>(config.rch_freq));
        (void)Sysctrl_SetRCLTrim(to_vendor<en_sysctrl_rcl_freq_t>(config.rcl_freq));
        (void)Sysctrl_SetRCLStableTime(SysctrlRclStableCycle256);

        /* 目标时钟源的前置配置必须在使能之前 */
        if (config.source == ClockSource::Xth)
        {
            (void)Sysctrl_SetXTHFreq(to_vendor<en_sysctrl_xth_freq_t>(config.xth_range));
            (void)Sysctrl_XTHDriverCfg(to_vendor<en_sysctrl_xtal_driver_t>(config.xth_drive));
            (void)Sysctrl_SetXTHStableTime(to_vendor<en_sysctrl_xth_cycle_t>(config.xth_stable));
        }

        (void)Sysctrl_SetHCLKDiv(to_vendor<en_sysctrl_hclk_div_t>(config.hclk_div));
        (void)Sysctrl_SetPCLKDiv(to_vendor<en_sysctrl_pclk_div_t>(config.pclk_div));

        /* Flash 等待周期必须早于提速 */
        (void)Flash_WaitCycle(flash_wait_for(target_hclk_hz()));

        (void)Sysctrl_ClkSourceEnable(to_vendor<en_sysctrl_clk_source_t>(config.source), TRUE);
        (void)Sysctrl_SysClkSwitch(to_vendor<en_sysctrl_clk_source_t>(config.source));

        SystemCoreClockUpdate();
    }

} // extern "C"
