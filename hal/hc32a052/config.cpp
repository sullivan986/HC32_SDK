/**
 *******************************************************************************
 * @file  config.cpp
 * @brief HC32A052 系统时钟初始化 (人工维护)
 *
 * 本文件把 config.h 中声明式 (constexpr) 的板级配置翻译成厂商 DDL 的
 * Sysctrl_* 调用, 并实现 startup.s 需要的那几个 C 符号:
 *   SystemInit()            —— 复位后由 startup.s 调用, 做一次性时钟初始化
 *   SystemCoreClockUpdate() —— 重新读硬件算出 HCLK/PCLK 并刷新全局变量
 *   SystemCoreClock / SystemHCLK / SystemPCLK —— 供 driver.cpp 的延时函数使用
 *
 * 内容源自厂商 mcu/common/system_hc32a052.c, 已去掉 MDK/IAR 专用的
 * $Sub$$main / __low_level_init (ATfE/picolibc 下不命中), 改为由 config.h 驱动.
 *
 * 校验: 本文件与 driver.h 中的 en_sysctrl_* 数值必须一一对应, 下方 static_assert
 *       会在编译期强制检查; 改板级配置只需改 config.h, 一般无需改动本文件.
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
static_assert(static_cast<int>(ClockSource::Pll) == static_cast<int>(SysctrlClkPLL));

static_assert(static_cast<int>(RchFreq::Mhz12) == static_cast<int>(SysctrlRchFreq12MHz));
static_assert(static_cast<int>(RchFreq::Mhz6) == static_cast<int>(SysctrlRchFreq6MHz));
static_assert(static_cast<int>(RchFreq::Mhz4) == static_cast<int>(SysctrlRchFreq4MHz));
static_assert(static_cast<int>(RchFreq::Mhz3) == static_cast<int>(SysctrlRchFreq3MHz));

static_assert(static_cast<int>(RclFreq::Hz38400) == static_cast<int>(SysctrlRclFreq38400));
static_assert(static_cast<int>(RclFreq::Hz32768) == static_cast<int>(SysctrlRclFreq32768));

static_assert(static_cast<int>(XthRange::Mhz8_12) == static_cast<int>(SysctrlXthFreq8_12MHz));
static_assert(static_cast<int>(XthRange::Mhz8_16) == static_cast<int>(SysctrlXthFreq8_16MHz));
static_assert(static_cast<int>(XthRange::Mhz16_24) == static_cast<int>(SysctrlXthFreq16_24MHz));
static_assert(static_cast<int>(XthRange::Mhz20_24) == static_cast<int>(SysctrlXthFreq20_24MHz));

static_assert(static_cast<int>(Drive::Drive0) == static_cast<int>(SysctrlXtalDriver0));
static_assert(static_cast<int>(Drive::Drive3) == static_cast<int>(SysctrlXtalDriver3));
static_assert(static_cast<int>(XtlAmp::Amp0) == static_cast<int>(SysctrlXtlAmp0));
static_assert(static_cast<int>(XtlAmp::Amp3) == static_cast<int>(SysctrlXtlAmp3));

static_assert(static_cast<int>(PllSource::Rch) == static_cast<int>(SysctrlPllRch));
static_assert(static_cast<int>(PllSource::Xth) == static_cast<int>(SysctrlPllXthXtal));

static_assert(static_cast<int>(HclkDiv::Div1) == static_cast<int>(SysctrlHclkDiv1));
static_assert(static_cast<int>(HclkDiv::Div128) == static_cast<int>(SysctrlHclkDiv128));
static_assert(static_cast<int>(PclkDiv::Div1) == static_cast<int>(SysctrlPclkDiv1));
static_assert(static_cast<int>(PclkDiv::Div8) == static_cast<int>(SysctrlPclkDiv8));

/* ==========================================================================
 * 板级配置合法性校验 (编译期)
 * ========================================================================== */
static_assert(config.pll.in_div >= 1u && config.pll.in_div <= 2u, "PLL 输入分频须为 1..2");
static_assert(config.pll.mul_n >= 2u && config.pll.mul_n <= 128u, "PLL 整数倍频须为 2..128");
static_assert(config.pll.mul_f <= 7u, "PLL 小数倍频须为 0..7");
static_assert(config.pll.out_div >= 4u && config.pll.out_div <= 34u && (config.pll.out_div % 2u) == 0u,
              "PLL 输出分频须为 4..34 的偶数");
static_assert(!(config.pll.source == PllSource::Xth) || (config.source == ClockSource::Pll),
              "PLL 以 XTH 为源时 system source 必须是 Pll");

/* ==========================================================================
 * 工具函数
 * ========================================================================== */

/// enum class -> 厂商枚举 (先转底层整型, 保证合法)
template <typename VendorEnum, typename E> constexpr VendorEnum to_vendor(E e) noexcept
{
    return static_cast<VendorEnum>(static_cast<std::underlying_type_t<E>>(e));
}

constexpr std::uint32_t kRchBaseHz = 12000000u; ///< RCH 基频

/// RCHCR.DIV 档位 -> 实际输出频率
constexpr std::uint32_t rch_hz(RchFreq f) noexcept
{
    constexpr std::uint32_t div[] = {1u, 2u, 3u, 4u}; // 与 au32RCHFreqTable 一致
    return kRchBaseHz / div[static_cast<std::uint8_t>(f)];
}

/// 按当前配置推算切换完成后的 HCLK (Hz), 用于选 Flash 读等待周期
constexpr std::uint32_t target_hclk_hz() noexcept
{
    std::uint32_t src = 0u;
    switch (config.source)
    {
    case ClockSource::Rch:
        src = rch_hz(config.rch_freq);
        break;
    case ClockSource::Rcl:
        src = (config.rcl_freq == RclFreq::Hz32768) ? 32768u : 38400u;
        break;
    case ClockSource::Xth:
        src = xth_hz;
        break;
    case ClockSource::Xtl:
        src = xtl_hz;
        break;
    case ClockSource::Pll: {
        const std::uint32_t fin = (config.pll.source == PllSource::Rch ? kRchBaseHz : xth_hz) / config.pll.in_div;
        const std::uint32_t fvco = fin * config.pll.mul_n + (fin * config.pll.mul_f) / 8u;
        src = fvco / config.pll.out_div;
        break;
    }
    }
    constexpr std::uint32_t hclk_div[] = {1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u};
    return src / hclk_div[static_cast<std::uint8_t>(config.hclk_div)];
}

/// HCLK -> Flash 读等待周期: >24 MHz 至少 1, >48 MHz 至少 2
constexpr en_flash_waitcycle_t flash_wait_for(std::uint32_t hz) noexcept
{
    return (hz > 48000000u) ? FlashWaitCycle2 : (hz > 24000000u) ? FlashWaitCycle1 : FlashWaitCycle0;
}

/// 配置并使能 XTH (外部高速晶振)
void enable_xth() noexcept
{
    (void)Sysctrl_SetXTHFreq(to_vendor<en_sysctrl_xth_freq_t>(config.xth_range));
    (void)Sysctrl_XTHDriverCfg(to_vendor<en_sysctrl_xtal_driver_t>(config.xth_drive));
    (void)Sysctrl_SetXTHStableTime(SysctrlXthStableCycle16384);
    (void)Sysctrl_ClkSourceEnable(SysctrlClkXTH, TRUE); /* 无晶振时此调用会在此死等 */

    if (config.auto_switch_rch_on_fail)
    {
        /* 先使能"晶振失效自动切回 RCH", 再配置失效监测 (与原厂示例顺序一致) */
        (void)Sysctrl_SetFunc(SysctrlAutoSwitchRchEn, TRUE);
        stc_sysctrl_fail_det_cfg_t det{};
        det.u32DetectIntEn = SYSCTRL_EXTOSC_FAIL_DET_INT_DIS;
        det.u32DetectTime = SYSCTRL_EXTOSC_FAIL_DET_TIME_8MS_128;
        det.u32DetectEn = SYSCTRL_EXTOSC_FAIL_DET_EN;
        (void)Sysctrl_ExtOscFailDetCfg(SYSCTRL_EXTOSC_FAIL_XTH, &det);
    }
}

/// 配置并使能 XTL (外部低速晶振)
void enable_xtl() noexcept
{
    (void)Sysctrl_XTLDriverCfg(to_vendor<en_sysctrl_xtl_amp_t>(config.xtl_amp),
                               to_vendor<en_sysctrl_xtal_driver_t>(config.xtl_drive));
    (void)Sysctrl_SetXTLStableTime(SysctrlXtlStableCycle16384);
    (void)Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE); /* 无晶振时此调用会在此死等 */
}

/// 配置并使能 PLL (必要时先起振 XTH)
void enable_pll() noexcept
{
    if (config.pll.source == PllSource::Xth)
    {
        enable_xth(); /* PLL 以晶振为源时必须先让 XTH 稳定 */
    }

    stc_sysctrl_pll_cfg_t cfg{};
    cfg.enPllSource = to_vendor<en_sysctrl_pll_clksource_t>(config.pll.source);
    cfg.u8SourceDiv = config.pll.in_div;
    cfg.enStableWaitCycle = SysctrlPllStableCycle16384;
    cfg.u8MullN = config.pll.mul_n;
    cfg.u8MullF = config.pll.mul_f;
    cfg.u8OutputDiv = config.pll.out_div;
    /* 参数已由 static_assert 保证合法, 此处最多一轮即成功 (与原厂示例同构) */
    while (Ok != Sysctrl_SetPLLFreq(&cfg))
    {
    }

    (void)Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
}

} // namespace

/* ==========================================================================
 * C 链接接口 (供 startup.s / driver.cpp / 应用代码)
 * ========================================================================== */
extern "C"
{

    /* 复位默认值: RCH 12 MHz / 3 = 4 MHz, 与厂商 system_hc32a052.c 初值一致.
     * 必须在 SystemInit 早期就有效, 因为 Sysctrl_ClkSourceEnable(XTH/PLL) 内部会用
     * delay1ms/delay100us, 而那两个延时函数读的正是 SystemCoreClock. */
    uint32_t SystemCoreClock = 4000000u;
    uint32_t SystemHCLK = 4000000u;
    uint32_t SystemPCLK = 4000000u;

    void SystemCoreClockUpdate(void)
    {
        SystemCoreClock = Sysctrl_GetHClkFreq();
        SystemHCLK = SystemCoreClock;
        SystemPCLK = Sysctrl_GetPClkFreq();

        /* 启动 SysTick 作为自由计数器 (driver 的 delay 函数依赖它; 不开中断) */
        SysTick->LOAD = 0xFFFFFFu;
        SysTick->VAL = 0u;
        SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    }

    void SystemInit(void)
    {
        /* 1) RC 时钟校准; RCH 常开 —— 它既是 PLL 的可选源, 也是晶振失效时的兜底 */
        (void)Sysctrl_SetRCHTrim(to_vendor<en_sysctrl_rch_freq_t>(config.rch_freq));
        (void)Sysctrl_SetRCLTrim(to_vendor<en_sysctrl_rcl_freq_t>(config.rcl_freq));
        (void)Sysctrl_SetRCLStableTime(SysctrlRclStableCycle256);
        (void)Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);

        /* 2) HCLK/PCLK 分频: 先设好, 使切换后的 HCLK 立即符合预期 */
        (void)Sysctrl_SetHCLKDiv(to_vendor<en_sysctrl_hclk_div_t>(config.hclk_div));
        (void)Sysctrl_SetPCLKDiv(to_vendor<en_sysctrl_pclk_div_t>(config.pclk_div));

        /* 3) Flash 读等待周期: 必须在提速切源之前设足, 否则高频下取指可能出错 */
        (void)Flash_WaitCycle(flash_wait_for(target_hclk_hz()));

        /* 4) 使能并切换到目标时钟源 (RCH 已是当前源, 无需处理) */
        switch (config.source)
        {
        case ClockSource::Rch:
            break;
        case ClockSource::Rcl:
            break;
        case ClockSource::Xth:
            enable_xth();
            break;
        case ClockSource::Xtl:
            enable_xtl();
            break;
        case ClockSource::Pll:
            enable_pll();
            break;
        }
        (void)Sysctrl_SysClkSwitch(to_vendor<en_sysctrl_clk_source_t>(config.source));

        /* 5) 按实际寄存器刷新 SystemCoreClock / SystemHCLK / SystemPCLK 并启动 SysTick */
        SystemCoreClockUpdate();
    }

} // extern "C"
