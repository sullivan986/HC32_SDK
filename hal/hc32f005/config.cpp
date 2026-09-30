/**
 *******************************************************************************
 * @file  config.cpp
 * @brief HC32F005 系统时钟初始化 (人工维护)
 *
 * 本文件把 config.h 中声明式 (constexpr) 的板级配置翻译成厂商 DDL 的
 * Sysctrl_* 调用, 并实现 startup.s 需要的那几个 C 符号:
 *   SystemInit()            —— 复位后由 startup.s 调用, 做一次性时钟初始化
 *   SystemCoreClockUpdate() —— 重新读硬件算出 HCLK 并刷新全局变量
 *   SystemCoreClock          —— 供 driver.cpp 的延时函数使用
 *
 * 内容源自厂商 mcu/common/system_hc32f005.c, 并补齐其未做的时钟源切换;
 * 已去掉 MDK/IAR 专用的 $Sub$$main / __low_level_init, 改为由 config.h 驱动.
 *
 * 与 A052 的差异: F005 **无 PLL**, 主频由 RCH 档位或外部晶振直接决定.
 *
 * 校验: 本文件与 driver.h 中的 en_sysctrl_* 数值必须一一对应, 下方 static_assert
 *       会在编译期强制检查; 改板级配置只需改 app 的 board_config.h.
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
 */

#include "driver.h" /* 同时带出 config.h (driver.h 顶部会 #include "config.h") */

#include <cstdint>
#include <type_traits>

namespace
{

using namespace hc32::board;

/* ==========================================================================
 * 枚举数值一致性校验
 * --------------------------------------------------------------------------
 * board::* 与厂商 en_sysctrl_* 的数值必须相同, 才能用一次 static_cast 互转.
 * 若哪天换成别的芯片 / 别的 DDL 版本, 这里的断言会立刻把问题暴露出来.
 * ========================================================================== */
static_assert(static_cast<int>(ClockSource::Rch) == static_cast<int>(SysctrlClkRCH));
static_assert(static_cast<int>(ClockSource::Xth) == static_cast<int>(SysctrlClkXTH));
static_assert(static_cast<int>(ClockSource::Rcl) == static_cast<int>(SysctrlClkRCL));
static_assert(static_cast<int>(ClockSource::Xtl) == static_cast<int>(SysctrlClkXTL));

/* RCH 的枚举值就是档位索引 (Sysctrl_SetRCHTrim 用 value 索引 TRIM 表),
 * 因此绝不能随意改动这些数值. */
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

/// enum class -> 厂商枚举 (先转底层整型, 保证合法)
template <typename VendorEnum, typename E> constexpr VendorEnum to_vendor(E e) noexcept
{
    return static_cast<VendorEnum>(static_cast<std::underlying_type_t<E>>(e));
}

/// HCLK -> Flash 读等待周期 (F005 只有 0/1 两档; >24 MHz 必须为 1)
constexpr en_flash_waitcycle_t flash_wait_for(std::uint32_t hz) noexcept
{
    return (hz > 24000000u) ? FlashWaitCycle1 : FlashWaitCycle0;
}

} // namespace

/* ==========================================================================
 * C 链接接口 (供 startup.s / driver.cpp / 应用代码)
 * ========================================================================== */
extern "C"
{

    /* 复位默认值: RCH 4 MHz, 与厂商 system_hc32f005.c 初值一致.
     * 必须在 SystemInit 早期就有效, 因为 Sysctrl_ClkSourceEnable(XTH) 内部会用
     * delay1ms, 而延时函数读的正是 SystemCoreClock. */
    uint32_t SystemCoreClock = 4000000u;

    void SystemCoreClockUpdate(void)
    {
        SystemCoreClock = Sysctrl_GetHClkFreq();

        /* 启动 SysTick 作为自由计数器 (driver 的 delay 函数依赖它; 不开中断) */
        SysTick->LOAD = 0xFFFFFFu;
        SysTick->VAL = 0u;
        SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    }

    void SystemInit(void)
    {
        /* 1) RC 时钟校准; RCH 常开 —— 它是复位默认源, 也是兜底 */
        (void)Sysctrl_SetRCHTrim(to_vendor<en_sysctrl_rch_freq_t>(config.rch_freq));
        (void)Sysctrl_SetRCLTrim(to_vendor<en_sysctrl_rcl_freq_t>(config.rcl_freq));
        (void)Sysctrl_SetRCLStableTime(SysctrlRclStableCycle256);

        /* 2) 目标时钟源的前置配置 (必须在使能之前) */
        if (config.source == ClockSource::Xth)
        {
            (void)Sysctrl_SetXTHFreq(to_vendor<en_sysctrl_xth_freq_t>(config.xth_range));
            (void)Sysctrl_XTHDriverCfg(to_vendor<en_sysctrl_xtal_driver_t>(config.xth_drive));
            (void)Sysctrl_SetXTHStableTime(to_vendor<en_sysctrl_xth_cycle_t>(config.xth_stable));
        }

        /* 3) HCLK/PCLK 分频: 先设好, 使切换后的 HCLK 立即符合预期 */
        (void)Sysctrl_SetHCLKDiv(to_vendor<en_sysctrl_hclk_div_t>(config.hclk_div));
        (void)Sysctrl_SetPCLKDiv(to_vendor<en_sysctrl_pclk_div_t>(config.pclk_div));

        /* 4) Flash 读等待周期: 必须在提速切源之前设足, 否则高频下取指可能出错 */
        (void)Flash_WaitCycle(flash_wait_for(target_hclk_hz()));

        /* 5) 使能并切换到目标时钟源 (RCH 是当前源, 使能一下保证状态明确) */
        (void)Sysctrl_ClkSourceEnable(to_vendor<en_sysctrl_clk_source_t>(config.source), TRUE);
        (void)Sysctrl_SysClkSwitch(to_vendor<en_sysctrl_clk_source_t>(config.source));

        /* 6) 按实际寄存器刷新 SystemCoreClock 并启动 SysTick
         * (Sysctrl_SysClkSwitch 内部已调过一次, 这里再调是幂等的, 但更明确) */
        SystemCoreClockUpdate();
    }

} // extern "C"
