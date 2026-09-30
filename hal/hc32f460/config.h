/**
 *******************************************************************************
 * @file  config.h
 * @brief HC32F460 板级配置「机制」: 类型 / 预设 / 校验 / 接口 (HAL 提供)
 *
 * ## 三层分工
 *   driver.h / driver.cpp  器件寄存器与外设驱动 (tools/merge_driver.py 生成, 勿手改)
 *   config.h / config.cpp  本层「机制」: 配置类型、预设、校验、时钟初始化实现
 *   board_config.h         app 层「策略」: 晶振频率、生效配置、板载引脚
 *
 * ## 为什么要分层
 *   "Config 类型有哪些字段""时钟怎么切""参数范围是多少" 是每块板子都一样
 *   的机制; 而"这块板焊了几 MHz 晶振""开机跑哪个档""LED 接哪个脚" 是每个
 *   应用各不相同的策略. 策略写死在 HAL 里会导致每换一个 app 就得改 HAL.
 *   => 正常使用**不需要改本文件**; 改板级参数请改 app 的 board_config.h.
 *
 * ## 包含方向 (请勿反过来)
 *   driver.h   ->  #include "config.h"
 *   config.h   ->  #include "board_config.h"  (app 侧, 若存在)
 *   config.cpp ->  #include "driver.h"
 * 所以本文件 **不得** include "driver.h", 否则形成循环包含.
 *
 * ## 与 HC32A052 / HC32F005 的差异 (写配置时注意)
 *   - 内核是 **Cortex-M4F** (带 FPU), 不是 M0+.
 *   - 时钟树复杂得多: HRC / MRC / LRC / XTAL / XTAL32 / **MPLL / UPLL**,
 *     且分频是"每个总线各自一份"(HCLK / EXCLK / PCLK0..PCLK4).
 *   - **PLL 参数是 M/N/P/Q/R 五个**, 不是 A052 那种 in_div/mul_n/out_div:
 *         Fvco = Fin / M * N ,  Fout = Fvco / P
 *     (PLLM/PLLN/PLLP/PLLQ/PLLR 寄存器里存的都是"实际值 - 1")
 *   - 时钟初始化前需要放开寄存器写保护 (LL_PERIPH_WE) 并设置
 *     SRAM / EFM 等待周期, 高频切换前还要 PWC_HighSpeedToHighPerformance().
 *   - 厂商不引用晶振频率宏 (system_hc32f460.c 直接读寄存器算频率), 故本芯片
 *     **不强制** board_config.h 提供任何宏; 但晶振频率会影响 PLL 实际频率,
 *     请按板上实际晶振在 board_config.h 里说明并选对预设.
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
#else
#include <stdint.h> /* config.h 在 driver.h 的系统头之前被包含, C 下需自带 */
#endif

/* ==========================================================================
 * 1. 板级配置「机制」——类型 / 预设 / 校验 (HAL 提供, 通常无需修改)
 * --------------------------------------------------------------------------
 * 下面这些 enum / struct 的数值都与 driver.h 中对应的 CLK_* 宏一致,
 * config.cpp 里有 static_assert 逐项校验, 改坏了会在编译期报错.
 *
 * 注意: 本节点只定义"有哪些配置项"; 实际生效的选择在第 4 节, 由 app 决定.
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
constexpr std::uint32_t div_ratio(Div d) noexcept
{
    return 1u << static_cast<std::uint8_t>(d);
}

/// 编译期校验: 各字段取值是否都在厂商允许范围内
constexpr bool is_valid(const Config &c) noexcept
{
    if (c.hrc_trim < -32 || c.hrc_trim > 31)
        return false;
    /* PLL 各分频/倍频范围 (与手册的 PLLM/PLLN/PLLP/PLLQ/PLLR 位宽一致) */
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

/// [默认] 保持复位默认档: HRC, 总线不分频 (不需要任何外部器件)
inline constexpr Config preset_hrc_default{
    .source = ClockSource::Hrc,
};

/// 外部 8MHz 晶振直出, 总线全不分频
inline constexpr Config preset_xtal_8mhz{
    .source = ClockSource::Xtal,
    .xtal = {.enable = true, .drive = XtalDrive::ULow, .stable = XtalStable::Ms2},
};

/// 外部 8MHz 晶振 + MPLL => 200MHz (8/1*50/2)
/// 高位主频, 必须放开 SRAM/EFM 等待周期并切高性能模式 (config.cpp 会自动做)
inline constexpr Config preset_pll_200mhz_from_xtal{
    .source = ClockSource::Pll,
    .xtal = {.enable = true, .drive = XtalDrive::ULow, .stable = XtalStable::Ms2},
    .pll = {.source = PllSource::Xtal, .m = 1u, .n = 50u, .p = 2u, .q = 2u, .r = 2u},
};

/// 内部 HRC + MPLL (HRC 约 16MHz, 精度差, 仅适合无需精确时钟的场合)
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
 * 2. 板级配置「策略」——由 app 提供 (HAL 不替任何板子做选择)
 * --------------------------------------------------------------------------
 * app 可在它的 inc 目录放一个 board_config.h (本文件会自动包含), 里面定义:
 *   HC32_BOARD_CONFIG   实际生效的 hc32::board::Config 表达式
 *   (可选) 板载资源宏   LED / 按键等引脚
 *
 * 也可改用编译选项传入:
 *   -DHC32_BOARD_CONFIG=::hc32::board::preset_hrc_default
 *
 * 注意: F460 厂商代码不引用晶振频率宏, 故这里**不强制**定义 SYSTEM_XTH;
 *       但用 XTAL / PLL 时, 请确认预设的 PLL 参数与板上晶振匹配
 *       (厂商默认 XTAL_VALUE = 8MHz, 见 system_hc32f460.h).
 * ========================================================================== */
#if defined(__has_include)
#if __has_include("board_config.h")
#include "board_config.h"
#endif
#endif

#ifdef __cplusplus

/* ==========================================================================
 * 3. 生效配置 (把 app 的选择接进 C++ 命名空间)
 * ========================================================================== */
namespace hc32::board
{

/// 实际生效的板级配置 —— 取自 app 的 board_config.h; 未提供时用安全默认档
#if defined(HC32_BOARD_CONFIG)
inline constexpr Config config = HC32_BOARD_CONFIG;
#else
inline constexpr Config config = preset_hrc_default;
#endif

static_assert(is_valid(config), "板级配置非法: 请检查 app 的 board_config.h (PLL 分频/倍频范围)");

/// 本配置是否会真正用到外部晶振
inline constexpr bool uses_external_crystal =
    (config.source == ClockSource::Xtal) || (config.source == ClockSource::Xtal32) ||
    (config.source == ClockSource::Pll && config.pll.source == PllSource::Xtal);

/// 切换完成后的 HCLK (Hz) —— 需要知道晶振实际频率才能算准, 这里按厂商默认
/// XTAL_VALUE / HRC 标称值估算, 仅用于"选等待周期"这种粗粒度场合;
/// 运行时精确值请读 SystemCoreClock (config.cpp 里由 CLK_GetClockFreq 刷新).
constexpr std::uint32_t target_hclk_hz() noexcept
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
 * 4. C 链接接口 (startup.s 与 driver.cpp 的消费者)
 * --------------------------------------------------------------------------
 * startup.s 的 Reset_Handler 会 `bl SystemInit`; driver.cpp 里的
 * DDL_DelayMS/DDL_DelayUS 会读 SystemCoreClock (通过 HCLK_VALUE 宏).
 * 这两个都必须是 C 符号, 故显式 extern "C".
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
