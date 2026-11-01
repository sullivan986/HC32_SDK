/**
 *******************************************************************************
 * @file  config.cpp
 * @brief HC32F460 系统时钟初始化
 *
 * 把 config.h 的 constexpr 配置翻译成厂商 CLK_* 调用, 并提供 startup.s 需要的
 * C 符号: SystemInit / SystemCoreClockUpdate / SystemCoreClock.
 *
 * 顺序不可调换: 写保护 -> FPU -> 分频 -> SRAM/EFM 等待周期 -> HRC/LRC ->
 * XTAL -> PLL -> 高性能模式 -> 切源 -> 恢复写保护 -> 刷新频率.
 * 等待周期必须早于提速; 切源必须晚于 PWC_HighSpeedToHighPerformance.
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
#include "mmio.h"

#include <cstdint>
#include <type_traits>
#include <utility>

/* ICG1.HRCFREQSEL: 芯片出厂校的是 16MHz 还是 20MHz, 运行时读出来才知道 */
constexpr std::uintptr_t kIcg1Addr = 0x40010684UL;

namespace
{

using namespace hc32::board;

/* ==========================================================================
 * 枚举数值一致性校验
 * --------------------------------------------------------------------------
 * board::* 与厂商 CLK_* 宏的数值必须一致, 才能用一次 static_cast 互转.
 * 预移位的宏 (如 CLK_HCLK_DIVn) 先右移回字段值再比.
 * ========================================================================== */
static_assert(static_cast<int>(ClockSource::Hrc) == static_cast<int>(CLK_SYSCLK_SRC_HRC));
static_assert(static_cast<int>(ClockSource::Mrc) == static_cast<int>(CLK_SYSCLK_SRC_MRC));
static_assert(static_cast<int>(ClockSource::Lrc) == static_cast<int>(CLK_SYSCLK_SRC_LRC));
static_assert(static_cast<int>(ClockSource::Xtal) == static_cast<int>(CLK_SYSCLK_SRC_XTAL));
static_assert(static_cast<int>(ClockSource::Xtal32) == static_cast<int>(CLK_SYSCLK_SRC_XTAL32));
static_assert(static_cast<int>(ClockSource::Pll) == static_cast<int>(CLK_SYSCLK_SRC_PLL));

static_assert(static_cast<int>(PllSource::Xtal) == static_cast<int>(CLK_PLL_SRC_XTAL));
static_assert(static_cast<int>(PllSource::Hrc) == static_cast<int>(CLK_PLL_SRC_HRC));

static_assert(static_cast<int>(XtalDrive::High) == static_cast<int>(CLK_XTAL_DRV_HIGH >> CMU_XTALCFGR_XTALDRV_POS));
static_assert(static_cast<int>(XtalDrive::ULow) == static_cast<int>(CLK_XTAL_DRV_ULOW >> CMU_XTALCFGR_XTALDRV_POS));
static_assert(static_cast<int>(XtalStable::Ms2) == static_cast<int>(CLK_XTAL_STB_2MS));
static_assert(static_cast<int>(XtalStable::Ms31) == static_cast<int>(CLK_XTAL_STB_31MS));

/* Div 的数值 == "分频指数": 0->1, 1->2, 2->4 ... (即 1 << n) */
static_assert(static_cast<int>(Div::Div1) == static_cast<int>(CLK_HCLK_DIV1 >> CMU_SCFGR_HCLKS_POS));
static_assert(static_cast<int>(Div::Div2) == static_cast<int>(CLK_HCLK_DIV2 >> CMU_SCFGR_HCLKS_POS));
static_assert(static_cast<int>(Div::Div64) == static_cast<int>(CLK_HCLK_DIV64 >> CMU_SCFGR_HCLKS_POS));

/* ==========================================================================
 * 工具函数
 * ========================================================================== */

/// enum class -> 厂商枚举/宏值
template <typename T, typename E> constexpr T to_vendor(E e) noexcept
{
    return static_cast<T>(std::to_underlying(e));
}

/// Div -> 厂商分频掩码表里的一项
template <std::size_t N> constexpr std::uint32_t pick_div(Div d, const std::uint32_t (&tbl)[N]) noexcept
{
    return tbl[std::to_underlying(d)];
}

#define HC32_DIV_TABLE(prefix)                                                                                         \
    {prefix##_DIV1, prefix##_DIV2, prefix##_DIV4, prefix##_DIV8, prefix##_DIV16, prefix##_DIV32, prefix##_DIV64}

/// 一次算出全部分频掩码 (交给 CLK_SetClockDiv)
constexpr std::uint32_t bus_div_mask() noexcept
{
    return pick_div(config.div.hclk, HC32_DIV_TABLE(CLK_HCLK)) | pick_div(config.div.exclk, HC32_DIV_TABLE(CLK_EXCLK)) |
           pick_div(config.div.pclk0, HC32_DIV_TABLE(CLK_PCLK0)) |
           pick_div(config.div.pclk1, HC32_DIV_TABLE(CLK_PCLK1)) |
           pick_div(config.div.pclk2, HC32_DIV_TABLE(CLK_PCLK2)) |
           pick_div(config.div.pclk3, HC32_DIV_TABLE(CLK_PCLK3)) |
           pick_div(config.div.pclk4, HC32_DIV_TABLE(CLK_PCLK4));
}

/// 读 ICG1.HRCFREQSEL 刷新 HRC 实际频率 (CLK_* 内部依赖它)
void refresh_hrc_value() noexcept
{
    HRC_VALUE = hc32::mmio::reg32{kIcg1Addr}.test(1u) ? 16000000u : 20000000u;
}

/// HCLK -> Flash (EFM) 读等待周期. 手册台阶: 33/66/100/133/166/200 MHz.
constexpr std::uint8_t efm_wait_for(std::uint32_t hz) noexcept
{
    return (hz > 166000000u)   ? EFM_WAIT_CYCLE5
           : (hz > 133000000u) ? EFM_WAIT_CYCLE4
           : (hz > 100000000u) ? EFM_WAIT_CYCLE3
           : (hz > 66000000u)  ? EFM_WAIT_CYCLE2
           : (hz > 33000000u)  ? EFM_WAIT_CYCLE1
                               : EFM_WAIT_CYCLE0;
}

/// 使能外部高速晶振 (含可选的引脚模拟输入配置)
void enable_xtal() noexcept
{
#if defined(HC32_XTAL_PORT) && defined(HC32_XTAL_PIN)
    /* 晶振引脚必须配成模拟功能, 否则数字输入会成为振荡器的额外负载 */
    (void)GPIO_AnalogCmd(HC32_XTAL_PORT, HC32_XTAL_PIN, ENABLE);
#endif
    stc_clock_xtal_init_t x{};
    (void)CLK_XtalStructInit(&x);
    x.u8State = CLK_XTAL_ON;
    x.u8Mode = config.xtal.external_clock ? CLK_XTAL_MD_EXCLK : CLK_XTAL_MD_OSC;
    x.u8Drv = to_vendor<std::uint8_t>(config.xtal.drive);
    x.u8SuperDrv = config.xtal.super_drive ? CLK_XTAL_SUPDRV_ON : CLK_XTAL_SUPDRV_OFF;
    x.u8StableTime = to_vendor<std::uint8_t>(config.xtal.stable);
    (void)CLK_XtalInit(&x);
}

/// 配置并使能 MPLL
void enable_pll() noexcept
{
    stc_clock_pll_init_t p{};
    (void)CLK_PLLStructInit(&p);
    p.PLLCFGR = 0UL;
    /* 寄存器里存的是"实际值 - 1" (官方例程同样写法) */
    p.PLLCFGR_f.PLLM = static_cast<std::uint32_t>(config.pll.m - 1u);
    p.PLLCFGR_f.PLLN = static_cast<std::uint32_t>(config.pll.n - 1u);
    p.PLLCFGR_f.PLLP = static_cast<std::uint32_t>(config.pll.p - 1u);
    p.PLLCFGR_f.PLLQ = static_cast<std::uint32_t>(config.pll.q - 1u);
    p.PLLCFGR_f.PLLR = static_cast<std::uint32_t>(config.pll.r - 1u);
    p.PLLCFGR_f.PLLSRC = to_vendor<std::uint32_t>(config.pll.source);
    p.u8PLLState = CLK_PLL_ON;
    (void)CLK_PLLInit(&p);
}

} // namespace

/* ==========================================================================
 * C 链接接口 (供 startup.s / driver.cpp / 应用代码)
 * ========================================================================== */
extern "C"
{

    /* 复位默认 HRC. DDL_DelayMS 通过 HCLK_VALUE 读它算循环次数, 早期延时也要有效 */
    uint32_t SystemCoreClock = 16000000u;

    /* CLK_GetClockFreq / CLK_PLLInit 直接引用, 初始化期间不能为 0 */
    uint32_t HRC_VALUE = 16000000u;

    void SystemCoreClockUpdate(void)
    {
        refresh_hrc_value();

        stc_clock_freq_t f{};
        if (LL_OK == CLK_GetClockFreq(&f))
        {
            SystemCoreClock = f.u32HclkFreq;
        }
    }

    void SystemInit(void)
    {
        refresh_hrc_value();

        LL_PERIPH_WE(LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_GPIO | LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM);

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
        SCB->CPACR |= ((3UL << 20) | (3UL << 22)); /* CP10/CP11 全访问 */
#endif

        CLK_SetClockDiv(CLK_BUS_CLK_ALL, bus_div_mask());

        if (config.sram_high_speed)
        {
            (void)SRAM_SetWaitCycle(SRAM_SRAM_ALL, SRAM_WAIT_CYCLE1, SRAM_WAIT_CYCLE1);
            (void)SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE0, SRAM_WAIT_CYCLE0);
        }

        (void)EFM_SetWaitCycle(efm_wait_for(target_hclk_hz()));

        CLK_HrcTrim(config.hrc_trim);
        (void)CLK_HrcCmd(ENABLE);
        (void)CLK_LrcCmd(ENABLE);

        const bool need_xtal =
            config.xtal.enable || (config.source == ClockSource::Pll && config.pll.source == PllSource::Xtal);
        if (need_xtal)
        {
            enable_xtal();
        }

        if (config.source == ClockSource::Pll)
        {
            enable_pll();
        }

        PWC_HighSpeedToHighPerformance();

        CLK_SetSysClockSrc(to_vendor<std::uint8_t>(config.source));

        LL_PERIPH_WP(LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_GPIO | LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM);

        SystemCoreClockUpdate();
    }

} // extern "C"
