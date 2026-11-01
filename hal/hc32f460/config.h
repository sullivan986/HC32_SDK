/**
 *******************************************************************************
 * @file  config.h
 * @brief HC32F460 板级配置: 类型 / 预设 / 校验 / C 接口
 *
 * 三层分工:
 *   driver.h/driver.cpp    寄存器与外设驱动 (merge_driver.py 生成, 勿手改)
 *   config.h/config.cpp    机制层: 配置类型、预设、校验、时钟初始化
 *   board_config.h         策略层 (app 侧): 生效配置、晶振、板载引脚
 *
 * 包含方向不可反过来 (否则循环包含):
 *   driver.h -> config.h -> board_config.h
 *   config.cpp -> driver.h
 *
 * 本芯片 (M4F) 与 M0+ 系列的差异:
 *   - 时钟源含 MRC/LRC/XTAL32, 以及 MPLL; 分频是 HCLK/EXCLK/PCLK0..4 各自一份
 *   - PLL 参数为 M/N/P/Q/R: Fvco = Fin/M*N, Fout = Fvco/P (寄存器存"值-1")
 *   - 初始化需先放开写保护, 并设 SRAM/EFM 等待周期
 *   - 厂商不引用晶振频率宏, 故不强制 board_config.h 定义任何宏
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
 */

#ifndef __HC32F460_CONFIG_H__
#define __HC32F460_CONFIG_H__

#ifdef __cplusplus
#include <cstdint>
#include <utility>
#else
#include <stdint.h> /* config.h 在 driver.h 的系统头之前被包含, C 下需自带 */
#endif

/* ==========================================================================
 * 1. 配置类型 / 预设 / 校验
 *    enum 数值与 driver.h 的 CLK_* 宏一致; config.cpp 用 static_assert 逐项校验.
 * ========================================================================== */
#ifdef __cplusplus

namespace hc32::board
{

/** @brief 系统时钟源 (对应 CLK_SYSCLK_SRC_*, 数值即寄存器编码) */
enum class ClockSource : std::uint8_t
{
    Hrc = 0u,    ///< 内部高速 RC (复位默认)
    Mrc = 1u,    ///< 内部中速 RC
    Lrc = 2u,    ///< 内部低速 RC
    Xtal = 3u,   ///< 外部高速晶振
    Xtal32 = 4u, ///< 外部低速晶振 (32.768 kHz)
    Pll = 5u,    ///< MPLL
};

/** @brief 晶振驱动能力 (对应 CLK_XTAL_DRV_*): 0 最强 .. 3 最弱 */
enum class XtalDrive : std::uint8_t
{
    High = 0u, ///< CLK_XTAL_DRV_HIGH
    Mid = 1u,  ///< CLK_XTAL_DRV_MID
    Low = 2u,  ///< CLK_XTAL_DRV_LOW
    ULow = 3u, ///< CLK_XTAL_DRV_ULOW (最弱)
};

/** @brief 晶振起振稳定等待 (对应 CLK_XTAL_STB_*, 数值即寄存器编码) */
enum class XtalStable : std::uint8_t
{
    Us133 = 1u,
    Us255 = 2u,
    Us499 = 3u,
    Us988 = 4u,
    Ms2 = 5u,
    Ms4 = 6u,
    Ms8 = 7u,
    Ms16 = 8u,
    Ms31 = 9u,
};

/** @brief 总线分频比 (DIV1..DIV64; 数值为"分频指数": 0=DIV1, 1=DIV2, ...) */
enum class Div : std::uint8_t
{
    Div1 = 0u,
    Div2 = 1u,
    Div4 = 2u,
    Div8 = 3u,
    Div16 = 4u,
    Div32 = 5u,
    Div64 = 6u,
};

/** @brief MPLL 输入源 (对应 CLK_PLL_SRC_*) */
enum class PllSource : std::uint8_t
{
    Xtal = 0u, ///< CLK_PLL_SRC_XTAL
    Hrc = 1u,  ///< CLK_PLL_SRC_HRC
};

/** @brief 外部高速晶振配置 */
struct Xtal
{
    bool enable = false;                 ///< 是否使能 XTAL
    bool external_clock = false;         ///< true = 从引脚直接输入时钟(不走振荡器)
    bool super_drive = false;            ///< 超强驱动 (通常低频晶振才需要)
    XtalDrive drive = XtalDrive::ULow;   ///< 驱动能力
    XtalStable stable = XtalStable::Ms2; ///< 起振稳定等待
};

/** @brief MPLL 倍频参数
 *  Fvco = Fin / m * n ,  Fout = Fvco / p
 *  下面存的是**实际值**(不是寄存器里的"值-1"), config.cpp 会做换算. */
struct Pll
{
    PllSource source = PllSource::Xtal;
    std::uint8_t m = 1u;   ///< 输入分频, 取值 1..32
    std::uint16_t n = 50u; ///< 倍频, 取值 1..512 (9 位, 放不下 uint8_t)
    std::uint8_t p = 2u;   ///< 系统输出分频 (也是 SYSCLK), 取值 1..16
    std::uint8_t q = 2u;   ///< 另一路输出分频, 取值 1..16
    std::uint8_t r = 2u;   ///< 另一路输出分频, 取值 1..16
};

/** @brief 各总线分频 (对应 CLK_SetClockDiv 的第二参数) */
struct BusDiv
{
    Div hclk = Div::Div1;  ///< AHB / 内核
    Div exclk = Div::Div1; ///< 外部总线
    Div pclk0 = Div::Div1; ///< APB0 (含部分定时器)
    Div pclk1 = Div::Div1; ///< APB1
    Div pclk2 = Div::Div1; ///< APB2
    Div pclk3 = Div::Div1; ///< APB3
    Div pclk4 = Div::Div1; ///< APB4
};

/** @brief 整块板子的启动配置 (只影响 SystemInit 里的一次性时钟初始化) */
struct Config
{
    ClockSource source = ClockSource::Hrc; ///< 复位后切换到哪个时钟源
    std::int8_t hrc_trim = 0;              ///< HRC 微调, -32..31 (0 = 出厂值)
    Xtal xtal{};                           ///< source == Xtal / Pll 时需要
    Pll pll{};                             ///< source == Pll 时生效
    BusDiv div{};                          ///< 总线分频
    bool sram_high_speed = true;           ///< 使能 SRAM 高速读写等待(高频必需)
};

/// 分频指数 -> 实际分频比
[[nodiscard]] constexpr std::uint32_t div_ratio(Div d) noexcept
{
    return 1u << std::to_underlying(d);
}

/// 编译期校验: 各字段是否在厂商允许范围内
[[nodiscard]] constexpr bool is_valid(const Config &c) noexcept
{
    if (c.hrc_trim < -32 || c.hrc_trim > 31)
        return false;
    /* PLL 各分频/倍频范围 (与 PLLM/PLLN/PLLP/PLLQ/PLLR 位宽一致) */
    if (c.pll.m < 1u || c.pll.m > 32u)
        return false;
    if (c.pll.n < 1u || c.pll.n > 512u)
        return false;
    if (c.pll.p < 1u || c.pll.p > 16u)
        return false;
    if (c.pll.q < 1u || c.pll.q > 16u)
        return false;
    if (c.pll.r < 1u || c.pll.r > 16u)
        return false;
    /* 选了 PLL 却没给出输入源晶振, 等于跑不起来 */
    if (c.source == ClockSource::Pll && c.pll.source == PllSource::Xtal && !c.xtal.enable)
        return false;
    return true;
}

/* ---- 预设: app 在 board_config.h 里挑一个赋给 HC32_BOARD_CONFIG ---- */

/// [默认] 复位默认档: HRC, 不分频, 不需外部器件
inline constexpr Config preset_hrc_default{
    .source = ClockSource::Hrc,
};

/// 外部 8MHz 晶振直出, 不分频
inline constexpr Config preset_xtal_8mhz{
    .source = ClockSource::Xtal,
    .xtal = {.enable = true, .drive = XtalDrive::ULow, .stable = XtalStable::Ms2},
};

/// 外部 8MHz + MPLL => 200MHz (8/1*50/2)
inline constexpr Config preset_pll_200mhz_from_xtal{
    .source = ClockSource::Pll,
    .xtal = {.enable = true, .drive = XtalDrive::ULow, .stable = XtalStable::Ms2},
    .pll = {.source = PllSource::Xtal, .m = 1u, .n = 50u, .p = 2u, .q = 2u, .r = 2u},
};

/// 内部 HRC + MPLL (HRC 精度差, 仅适合不要求精确时钟的场合)
inline constexpr Config preset_pll_from_hrc{
    .source = ClockSource::Pll,
    .pll = {.source = PllSource::Hrc, .m = 2u, .n = 50u, .p = 2u, .q = 2u, .r = 2u},
};

/* HAL 自带的预设本身也必须合法 (改了预设却没同步约束时在这里报错) */
static_assert(is_valid(preset_hrc_default), "HAL 预设 preset_hrc_default 非法");
static_assert(is_valid(preset_xtal_8mhz), "HAL 预设 preset_xtal_8mhz 非法");
static_assert(is_valid(preset_pll_200mhz_from_xtal), "HAL 预设 preset_pll_200mhz_from_xtal 非法");
static_assert(is_valid(preset_pll_from_hrc), "HAL 预设 preset_pll_from_hrc 非法");

} // namespace hc32::board

#endif /* __cplusplus (机制部分结束) */

/* ==========================================================================
 * 2. 策略层: app 在 inc/board_config.h 里定义 (本文件自动包含)
 *    HC32_BOARD_CONFIG   生效的 Config 表达式, 留空则用 preset_hrc_default
 *    也可改用 -DHC32_BOARD_CONFIG=::hc32::board::preset_xxx
 * ========================================================================== */
#if defined(__has_include)
#if __has_include("board_config.h")
#include "board_config.h"
#endif
#endif

#ifdef __cplusplus

/* ==========================================================================
 * 3. 生效配置
 * ========================================================================== */
namespace hc32::board
{

/// 实际生效的板级配置; 未提供时用安全默认档
#if defined(HC32_BOARD_CONFIG)
inline constexpr Config config = HC32_BOARD_CONFIG;
#else
inline constexpr Config config = preset_hrc_default;
#endif

static_assert(is_valid(config), "板级配置非法: 检查 board_config.h 的 PLL 分频/倍频范围");

/// 本配置是否会真正用到外部晶振
inline constexpr bool uses_external_crystal =
    (config.source == ClockSource::Xtal) || (config.source == ClockSource::Xtal32) ||
    (config.source == ClockSource::Pll && config.pll.source == PllSource::Xtal);

/// 估算切换后的 HCLK (Hz). 按标称值算, 只用于选等待周期这类粗粒度场合;
/// 运行时的精确值请读 SystemCoreClock.
[[nodiscard]] constexpr std::uint32_t target_hclk_hz() noexcept
{
    constexpr std::uint32_t kXtalHz = 8000000u; ///< 与 system_hc32f460.h 的 XTAL_VALUE 一致
    constexpr std::uint32_t kHrcHz = 16000000u; ///< HRC 典型值

    std::uint32_t src;
    switch (config.source)
    {
    case ClockSource::Xtal:
        src = kXtalHz;
        break;
    case ClockSource::Pll: {
        const std::uint32_t fin = (config.pll.source == PllSource::Xtal ? kXtalHz : kHrcHz) / config.pll.m;
        src = fin * config.pll.n / config.pll.p;
        break;
    }
    default:
        src = kHrcHz;
        break;
    }
    return src / div_ratio(config.div.hclk);
}

} // namespace hc32::board

#endif /* __cplusplus (生效配置结束) */

/* ==========================================================================
 * 4. C 链接接口 (startup.s 与 driver.cpp 使用)
 * ========================================================================== */
#ifdef __cplusplus
extern "C"
{
#endif

    extern uint32_t SystemCoreClock; /*!< = HCLK, 供 DDL 延时与用户代码使用 */

    void SystemCoreClockUpdate(void); /*!< 重新读取并刷新 SystemCoreClock */
    void SystemInit(void);            /*!< 复位后由 startup.s 调用 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F460_CONFIG_H__ */
