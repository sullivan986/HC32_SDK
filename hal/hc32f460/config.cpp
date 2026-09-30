/**
 *******************************************************************************
 * @file  config.cpp
 * @brief HC32F460 系统时钟初始化 (人工维护)
 *
 * 本文件把 config.h 中声明式 (constexpr) 的板级配置翻译成厂商 LL 库的 CLK_*
 * 调用, 并实现 startup.s 需要的那几个 C 符号:
 *   SystemInit()            —— 复位后由 startup.s 调用, 做一次性时钟初始化
 *   SystemCoreClockUpdate() —— 重新读硬件算出 HCLK 并刷新全局变量
 *   SystemCoreClock          —— 供 driver.cpp 的 DDL_DelayMS/US 使用
 *
 * 内容源自厂商 system_hc32f460.c + examples/clk/clk_switch_sysclk, 并改为由
 * config.h 驱动. 厂商那份只能给出"复位默认档"; 本文件额外支持 XTAL / MPLL.
 *
 * 初始化顺序 (照抄官方例程, 顺序有讲究, 别随意调整):
 *   放开寄存器写保护 -> FPU -> 总线分频 -> SRAM/EFM 等待周期 -> HRC/LRC ->
 *   XTAL -> PLL -> 切高性能模式 -> 切系统时钟源 -> 恢复写保护 -> 刷新频率
 *  其中"等待周期必须在提速之前设足"与"切源前先 PWC_HighSpeedToHighPerformance"
 *  是最容易漏的两步, 漏了会在高频下随机跑飞.
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

/* --------------------------------------------------------------------------
 * 下面这几个原本定义在厂商的 system_hc32f460.c 里 (它已被排除, 实现搬到了本文件),
 * 因此这里的定义也必须一起搬过来 —— 否则 CLK_GetClockFreq / CLK_PLLInit
 * 会引用到未定义的 HRC_VALUE (链接期报 undefined symbol).
 *   HRC_VALUE      : HRC 的实际频率(全局变量). ICG1 的 HRCFREQSEL 位决定
 *                    芯片出厂校的是 16MHz 还是 20MHz, 运行时读出来才知道.
 *   HRC_FREQ_MON() : 读 ICG1 寄存器中的 HRCFREQSEL 位.
 * -------------------------------------------------------------------------- */
#define HRC_16MHz_VALUE (16000000UL)
#define HRC_20MHz_VALUE (20000000UL)
#define HRC_FREQ_MON() (*((volatile uint32_t *)(0x40010684UL)))

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
    return static_cast<T>(static_cast<std::underlying_type_t<E>>(e));
}

/// 分频比 -> CLK_SetClockDiv 用的掩码 (直接取厂商宏, 不手写移位)
constexpr std::uint32_t hclk_mask(Div d) noexcept
{
    constexpr std::uint32_t t[] = {CLK_HCLK_DIV1,  CLK_HCLK_DIV2,  CLK_HCLK_DIV4, CLK_HCLK_DIV8,
                                   CLK_HCLK_DIV16, CLK_HCLK_DIV32, CLK_HCLK_DIV64};
    return t[static_cast<std::uint8_t>(d)];
}

constexpr std::uint32_t exclk_mask(Div d) noexcept
{
    constexpr std::uint32_t t[] = {CLK_EXCLK_DIV1,  CLK_EXCLK_DIV2,  CLK_EXCLK_DIV4, CLK_EXCLK_DIV8,
                                   CLK_EXCLK_DIV16, CLK_EXCLK_DIV32, CLK_EXCLK_DIV64};
    return t[static_cast<std::uint8_t>(d)];
}

template <std::size_t N> constexpr std::uint32_t pclk_mask(Div d, const std::uint32_t (&t)[N]) noexcept
{
    return t[static_cast<std::uint8_t>(d)];
}

/// 一次算出全部分频掩码
constexpr std::uint32_t bus_div_mask() noexcept
{
    return hclk_mask(config.div.hclk) | exclk_mask(config.div.exclk) |
           pclk_mask(config.div.pclk0, {CLK_PCLK0_DIV1, CLK_PCLK0_DIV2, CLK_PCLK0_DIV4, CLK_PCLK0_DIV8, CLK_PCLK0_DIV16,
                                        CLK_PCLK0_DIV32, CLK_PCLK0_DIV64}) |
           pclk_mask(config.div.pclk1, {CLK_PCLK1_DIV1, CLK_PCLK1_DIV2, CLK_PCLK1_DIV4, CLK_PCLK1_DIV8, CLK_PCLK1_DIV16,
                                        CLK_PCLK1_DIV32, CLK_PCLK1_DIV64}) |
           pclk_mask(config.div.pclk2, {CLK_PCLK2_DIV1, CLK_PCLK2_DIV2, CLK_PCLK2_DIV4, CLK_PCLK2_DIV8, CLK_PCLK2_DIV16,
                                        CLK_PCLK2_DIV32, CLK_PCLK2_DIV64}) |
           pclk_mask(config.div.pclk3, {CLK_PCLK3_DIV1, CLK_PCLK3_DIV2, CLK_PCLK3_DIV4, CLK_PCLK3_DIV8, CLK_PCLK3_DIV16,
                                        CLK_PCLK3_DIV32, CLK_PCLK3_DIV64}) |
           pclk_mask(config.div.pclk4, {CLK_PCLK4_DIV1, CLK_PCLK4_DIV2, CLK_PCLK4_DIV4, CLK_PCLK4_DIV8, CLK_PCLK4_DIV16,
                                        CLK_PCLK4_DIV32, CLK_PCLK4_DIV64});
}

/// HCLK -> Flash (EFM) 读等待周期. 手册给的台阶: 33/66/100/133/166/200 MHz.
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

    /* 复位默认值: HRC. vendor 的 system_hc32f460.c 用 __NO_INIT 修饰, 但这里
     * 需要它一开始就有合法值 —— DDL_DelayMS 通过 HCLK_VALUE 宏读它算循环次数,
     * 而 SystemInit 早期(放写保护/配置等待周期)就可能用到延时. */
    uint32_t SystemCoreClock = 16000000u;

    /* HRC 实际频率. CLK_GetClockFreq / CLK_PLLInit 都直接引用它, 必须在它们
     * 之前就是有效值 (初始化期间也不能为 0, 否则算出的频率是 0). */
    uint32_t HRC_VALUE = 16000000u;

    void SystemCoreClockUpdate(void)
    {
        /* HRC 到底是 16MHz 还是 20MHz 由芯片内部的 ICG1.HRCFREQSEL 决定,
         * 必须先刷新它, CLK_GetClockFreq 才能算准 HRC/PLL 档的频率. */
        HRC_VALUE = (1UL == (HRC_FREQ_MON() & 1UL)) ? HRC_16MHz_VALUE : HRC_20MHz_VALUE;

        stc_clock_freq_t f{};
        if (LL_OK == CLK_GetClockFreq(&f))
        {
            SystemCoreClock = f.u32HclkFreq;
        }
    }

    void SystemInit(void)
    {
        /* 0) 先刷 HRC 实际频率: CLK_PLLInit/CLK_SetClockDiv 内部要引用它,
         *    此时 SystemCoreClock 还不能读 (寄存器还没配), 所以只取 HRC. */
        HRC_VALUE = (1UL == (HRC_FREQ_MON() & 1UL)) ? HRC_16MHz_VALUE : HRC_20MHz_VALUE;

        /* 1) 放开寄存器写保护 (时钟/电源相关寄存器受保护, 不解锁写不进去) */
        LL_PERIPH_WE(LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_GPIO | LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM);

        /* 2) FPU: 使能 CP10/CP11 全访问, 否则硬件浮点指令会触发 UsageFault */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
        SCB->CPACR |= ((3UL << 20) | (3UL << 22));
#endif

        /* 3) 总线分频: 先设好, 后面切源时 HCLK 直接就是目标值 */
        CLK_SetClockDiv(CLK_BUS_CLK_ALL, bus_div_mask());

        /* 4) SRAM 等待周期 (高频必需, 官方在 200MHz 下用 1/0) */
        if (config.sram_high_speed)
        {
            (void)SRAM_SetWaitCycle(SRAM_SRAM_ALL, SRAM_WAIT_CYCLE1, SRAM_WAIT_CYCLE1);
            (void)SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE0, SRAM_WAIT_CYCLE0);
        }

        /* 5) Flash 等待周期: 必须在提速之前设足, 否则高频下取指出错 */
        (void)EFM_SetWaitCycle(efm_wait_for(target_hclk_hz()));

        /* 6) 内部 RC: HRC 是复位默认源, LRC 供 RTC/WDT 等低速场合 */
        CLK_HrcTrim(config.hrc_trim);
        (void)CLK_HrcCmd(ENABLE);
        (void)CLK_LrcCmd(ENABLE);

        /* 7) 需要外部晶振时先让它起振 (PLL 以 XTAL 为源时同理) */
        const bool need_xtal =
            config.xtal.enable || (config.source == ClockSource::Pll && config.pll.source == PllSource::Xtal);
        if (need_xtal)
        {
            enable_xtal();
        }

        /* 8) 需要 PLL 时配置并使能 */
        if (config.source == ClockSource::Pll)
        {
            enable_pll();
        }

        /* 9) 切高频模式: 官方也是在切源前调它, 漏了会在高频下不稳定 */
        PWC_HighSpeedToHighPerformance();

        /* 10) 切到目标时钟源 (HRC 已是当前源, 调一次保证状态明确) */
        CLK_SetSysClockSrc(to_vendor<std::uint8_t>(config.source));

        /* 11) 恢复寄存器写保护 */
        LL_PERIPH_WP(LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_GPIO | LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM);

        /* 12) 按实际寄存器刷新 SystemCoreClock */
        SystemCoreClockUpdate();
    }

} // extern "C"
