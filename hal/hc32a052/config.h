/**
 *******************************************************************************
 * @file  config.h
 * @brief HC32A052 板级配置「机制」: 类型 / 预设 / 校验 / 接口 (HAL 提供)
 *
 * ## 三层分工
 *   driver.h / driver.cpp  器件寄存器与外设驱动 (tools/merge_driver.py 生成, 勿手改)
 *   config.h / config.cpp  本层「机制」: 配置类型、预设、校验、时钟初始化实现
 *   board_config.h         app 层「策略」: 晶振频率、生效配置、板载引脚
 *
 * ## 为什么要分层
 *   "Config 类型有哪些字段""时钟怎么切""参数范围是多少" 是**每块板子都一样**
 *   的机制; 而"这块板焊了几 MHz 晶振""开机跑哪个档""LED 接哪个脚" 是**每个
 *   应用各不相同**的策略. 策略写死在 HAL 里会导致每换一个 app 就得改 HAL.
 *   因此策略被移到 app 侧: app 只需在自己的 inc 目录放一个 board_config.h,
 *   本文件会自动包含它 (见第 2 节).
 *   => 正常使用**不需要改本文件**; 改板级参数请改 app 的 board_config.h.
 *
 * ## 包含方向 (请勿反过来)
 *   driver.h   ->  #include "config.h"        (驱动内部用 SYSTEM_XTH/XTL 做频率换算)
 *   config.h   ->  #include "board_config.h"  (app 侧, 若存在)
 *   config.cpp ->  #include "driver.h"
 * 所以本文件 **不得** include "driver.h", 否则形成循环包含.
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
 */

#ifndef __HC32A052_CONFIG_H__
#define __HC32A052_CONFIG_H__

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h> /* config.h 在 driver.h 的系统头之前被包含, C 下需自带 */
#endif

/* ==========================================================================
 * 1. 板级配置「机制」——类型 / 预设 / 校验 (HAL 提供, 通常无需修改)
 * --------------------------------------------------------------------------
 * 下面这些 enum / struct 的数值都与 driver.h 中对应的 en_sysctrl_* 一致,
 * config.cpp 里有 static_assert 逐项校验, 改坏了会在编译期报错.
 *
 * 注意: 本节点只定义"有哪些配置项"; 实际生效的选择在第 4 节, 由 app 决定.
 * ========================================================================== */
#ifdef __cplusplus

namespace hc32::board
{

/** @brief 系统时钟源 (对应 en_sysctrl_clk_source_t) */
enum class ClockSource : std::uint8_t
{
    Rch = 0u, ///< 内部高速 RC (复位默认, 不依赖外部晶振)
    Xth = 1u, ///< 外部高速晶振
    Rcl = 2u, ///< 内部低速 RC
    Xtl = 3u, ///< 外部低速晶振 (32.768 kHz)
    Pll = 4u, ///< PLL (输入源见 Pll::source)
};

/** @brief RCH 输出频率 (对应 en_sysctrl_rch_freq_t; 基频 12 MHz 分频得到) */
enum class RchFreq : std::uint8_t
{
    Mhz12 = 0u,
    Mhz6 = 1u,
    Mhz4 = 2u,
    Mhz3 = 3u,
};

/** @brief RCL 校准频率 (对应 en_sysctrl_rcl_freq_t) */
enum class RclFreq : std::uint8_t
{
    Hz38400 = 0u,
    Hz32768 = 2u,
};

/** @brief XTH 频率范围 (对应 en_sysctrl_xth_freq_t) */
enum class XthRange : std::uint8_t
{
    Mhz8_12 = 0u,
    Mhz8_16 = 1u,
    Mhz16_24 = 2u,
    Mhz20_24 = 3u,
};

/** @brief 晶振驱动能力 (对应 en_sysctrl_xtal_driver_t): 0 最弱 .. 3 最强 */
enum class Drive : std::uint8_t
{
    Drive0 = 0u,
    Drive1 = 1u,
    Drive2 = 2u,
    Drive3 = 3u,
};

/** @brief XTL 振幅 (对应 en_sysctrl_xtl_amp_t): 0 最小 .. 3 最大 */
enum class XtlAmp : std::uint8_t
{
    Amp0 = 0u,
    Amp1 = 1u,
    Amp2 = 2u,
    Amp3 = 3u,
};

/** @brief PLL 输入时钟源 (对应 en_sysctrl_pll_clksource_t) */
enum class PllSource : std::uint8_t
{
    Rch = 0u, ///< 内部 12 MHz RC (与 RchFreq 无关, 厂商按 12 MHz 计算)
    Xth = 1u, ///< 外部高速晶振
};

/** @brief HCLK 分频 (对应 en_sysctrl_hclk_div_t) */
enum class HclkDiv : std::uint8_t
{
    Div1 = 0u,
    Div2 = 1u,
    Div4 = 2u,
    Div8 = 3u,
    Div16 = 4u,
    Div32 = 5u,
    Div64 = 6u,
    Div128 = 7u,
};

/** @brief PCLK 分频 (对应 en_sysctrl_pclk_div_t) */
enum class PclkDiv : std::uint8_t
{
    Div1 = 0u,
    Div2 = 1u,
    Div4 = 2u,
    Div8 = 3u,
};

/** @brief PLL 倍频参数
 *  Fout = (Fin / in_div) * (mul_n + mul_f/8) / out_div */
struct Pll
{
    PllSource source = PllSource::Rch;
    std::uint8_t in_div = 1u;  ///< 输入分频, 取值 1..2
    std::uint8_t mul_n = 40u;  ///< 整数倍频, 取值 2..128
    std::uint8_t mul_f = 0u;   ///< 小数倍频, 取值 0..7 (即 n/8)
    std::uint8_t out_div = 8u; ///< 输出分频, 取值 4..34 且为偶数
};

/** @brief 整块板子的启动配置 (只影响 SystemInit 里的一次性时钟初始化) */
struct Config
{
    ClockSource source = ClockSource::Rch; ///< 复位后切换到哪个时钟源
    RchFreq rch_freq = RchFreq::Mhz4;      ///< RCH 输出频率 (兼作 PLL 源/兜底)
    RclFreq rcl_freq = RclFreq::Hz32768;
    XthRange xth_range = XthRange::Mhz8_12;
    Drive xth_drive = Drive::Drive2;
    XtlAmp xtl_amp = XtlAmp::Amp3;
    Drive xtl_drive = Drive::Drive3;
    Pll pll{}; ///< source == Pll 时生效
    HclkDiv hclk_div = HclkDiv::Div1;
    PclkDiv pclk_div = PclkDiv::Div1;
    bool auto_switch_rch_on_fail = true; ///< 外部晶振失效时自动切回 RCH
};

/// 编译期校验: 各字段取值是否都在厂商允许范围内
constexpr bool is_valid(const Config &c) noexcept
{
    /* PLL 参数范围 (与厂商 Sysctrl_SetPLLFreq 的内部检查一致) */
    if (c.pll.in_div < 1u || c.pll.in_div > 2u)
        return false;
    if (c.pll.mul_n < 2u || c.pll.mul_n > 128u)
        return false;
    if (c.pll.mul_f > 7u)
        return false;
    if (c.pll.out_div < 4u || c.pll.out_div > 34u || (c.pll.out_div % 2u) != 0u)
        return false;
    /* PLL 以 XTH 为源时, 目标时钟源必须是 PLL, 否则配了也不生效 */
    if (c.pll.source == PllSource::Xth && c.source != ClockSource::Pll)
        return false;
    return true;
}

/* ---- 预设: app 在 board_config.h 里挑一个赋给 HC32_BOARD_CONFIG ---- */

/// [默认] 不依赖外部晶振, 复位默认档: RCH 12 MHz / 3 = 4 MHz
inline constexpr Config preset_rch_4mhz{
    .source = ClockSource::Rch,
    .rch_freq = RchFreq::Mhz4,
};

/// 无外部晶振也能跑满速: RCH 12 MHz /2 *64 /6 = 64 MHz
inline constexpr Config preset_pll_64mhz_from_rch{
    .source = ClockSource::Pll,
    .rch_freq = RchFreq::Mhz12,
    .pll = Pll{PllSource::Rch, 2u, 64u, 0u, 6u},
};

/// STK 板 (8 MHz 外部晶振): XTH 8 MHz /1 *64 /8 = 64 MHz
inline constexpr Config preset_pll_64mhz_from_xth{
    .source = ClockSource::Pll,
    .xth_range = XthRange::Mhz8_12,
    .pll = Pll{PllSource::Xth, 1u, 64u, 0u, 8u},
};

/* HAL 自带的预设本身也必须合法 (改了预设却没同步约束时在这里报错) */
static_assert(is_valid(preset_rch_4mhz), "HAL 预设 preset_rch_4mhz 非法");
static_assert(is_valid(preset_pll_64mhz_from_rch), "HAL 预设 preset_pll_64mhz_from_rch 非法");
static_assert(is_valid(preset_pll_64mhz_from_xth), "HAL 预设 preset_pll_64mhz_from_xth 非法");

} // namespace hc32::board

#endif /* __cplusplus (机制部分结束) */

/* ==========================================================================
 * 2. 板级配置「策略」——由 app 提供 (HAL 不替任何板子做选择)
 * --------------------------------------------------------------------------
 * app 需在它的 inc 目录放一个 board_config.h (本文件会自动包含), 里面定义:
 *   SYSTEM_XTH / SYSTEM_XTL   板上实际焊接的晶振频率 (Hz)
 *   HC32_BOARD_CONFIG         实际生效的 hc32::board::Config 表达式
 *   (可选) 板载资源宏          LED / 按键等引脚
 *
 * 这些是"每块板子 / 每个应用各不相同"的东西, 所以留在 app 侧, HAL 不碰.
 *
 * 也可改用编译选项传入 (二选一或混用均可):
 *   -DSYSTEM_XTH=8000000 -DSYSTEM_XTL=32768
 *   -DHC32_BOARD_CONFIG=::hc32::board::preset_rch_4mhz
 * ========================================================================== */
#if defined(__has_include)
#if __has_include("board_config.h")
#include "board_config.h"
#endif
#endif

/* ==========================================================================
 * 3. 必需项检查 (缺失时给出明确指引, 避免留下难以定位的报错)
 * ========================================================================== */
#if !defined(SYSTEM_XTH)
#error "SYSTEM_XTH 未定义: 请在 app 的 inc 目录创建 board_config.h, 给出外部高速晶振频率(Hz)"
#endif
#if !defined(SYSTEM_XTL)
#error "SYSTEM_XTL 未定义: 请在 app 的 inc 目录创建 board_config.h, 给出外部低速晶振频率(Hz)"
#endif

#ifdef __cplusplus
#if !defined(HC32_BOARD_CONFIG)
#error "HC32_BOARD_CONFIG 未定义: 请在 app 的 inc/board_config.h 指定生效配置 (可从 hc32::board::preset_* 选一个)"
#endif

/* ==========================================================================
 * 4. 生效配置 (把 app 的选择与晶振宏接进 C++ 命名空间)
 * ========================================================================== */
namespace hc32::board
{

/* ---- 晶振频率 (与上面的宏同源, 供 C++ 代码读取) ---- */
inline constexpr std::uint32_t xth_hz = SYSTEM_XTH;
inline constexpr std::uint32_t xtl_hz = SYSTEM_XTL;

/// 实际生效的板级配置 —— 取自 app 的 board_config.h
inline constexpr Config config = HC32_BOARD_CONFIG;

static_assert(is_valid(config), "板级配置非法: 请检查 app 的 board_config.h (PLL 分频/倍频范围)");

/// 本配置是否会真正用到外部晶振 (Xth / Xtl, 或 PLL 以 XTH 为源)
inline constexpr bool uses_external_crystal =
    (config.source == ClockSource::Xth) || (config.source == ClockSource::Xtl) ||
    (config.source == ClockSource::Pll && config.pll.source == PllSource::Xth);

} // namespace hc32::board

#endif /* __cplusplus (生效配置结束) */

/* ==========================================================================
 * 5. C 链接接口 (startup.s 与 driver.cpp 的消费者)
 * --------------------------------------------------------------------------
 * startup.s 的 Reset_Handler 会 `bl SystemInit`; driver.cpp 的延时函数会读
 * SystemCoreClock. 这两个都必须是 C 符号, 故显式 extern "C".
 * ========================================================================== */
#ifdef __cplusplus
extern "C"
{
#endif

    extern uint32_t SystemCoreClock; /*!< = HCLK, 供 driver 延时函数使用 */
    extern uint32_t SystemHCLK;
    extern uint32_t SystemPCLK;

    void SystemCoreClockUpdate(void); /*!< 重新读取并刷新上面三个变量 */
    void SystemInit(void);            /*!< 复位后由 startup.s 调用 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32A052_CONFIG_H__ */
