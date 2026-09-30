/**
 *******************************************************************************
 * @file  config.h
 * @brief HC32F005 板级配置「机制」: 类型 / 预设 / 校验 / 接口 (HAL 提供)
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
 *   因此策略被移到 app 侧: app 只需在自己的 inc 目录放一个 board_config.h,
 *   本文件会自动包含它 (见第 2 节).
 *   => 正常使用**不需要改本文件**; 改板级参数请改 app 的 board_config.h.
 *
 * ## 包含方向 (请勿反过来)
 *   driver.h   ->  #include "config.h"        (驱动内部用 SYSTEM_XTH 做频率换算)
 *   config.h   ->  #include "board_config.h"  (app 侧, 若存在)
 *   config.cpp ->  #include "driver.h"
 * 所以本文件 **不得** include "driver.h", 否则形成循环包含.
 *
 * ## HC32F005 与 HC32A052 的时钟差异 (写配置时注意)
 *   - **无 PLL**: 时钟源只有 RCH / XTH / RCL / XTL 四种, 主频靠 RCH 自身分档
 *     (最高 24MHz) 或外部晶振 (最高 32MHz) 直接决定.
 *   - RCH 分档是"直接选频率"而非 A052 那种"12MHz 再分频":
 *       24MHz=0, 22.12MHz=1, 16MHz=2, 8MHz=3, 4MHz=4 (枚举值即档位索引)
 *   - Flash 读等待周期只有 0/1 两档 (HCLK > 24MHz 时必须为 1).
 *   - 无 XTL 振幅配置 (en_sysctrl_xtl_amp_t 不存在), 也无需 SYSTEM_XTL 宏.
 *   - 无外部晶振失效检测 API, 故没有 auto_switch_rch_on_fail 选项.
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
 */

#ifndef __HC32F005_CONFIG_H__
#define __HC32F005_CONFIG_H__

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

/** @brief 系统时钟源 (对应 en_sysctrl_clk_source_t; F005 无 PLL) */
enum class ClockSource : std::uint8_t
{
    Rch = 0u, ///< 内部高速 RC (复位默认, 不依赖外部晶振)
    Xth = 1u, ///< 外部高速晶振
    Rcl = 2u, ///< 内部低速 RC
    Xtl = 3u, ///< 外部低速晶振 (32.768 kHz)
};

/** @brief RCH 输出频率 (对应 en_sysctrl_rch_freq_t; 枚举值即档位索引) */
enum class RchFreq : std::uint8_t
{
    Mhz24 = 0u,
    Mhz22_12 = 1u,
    Mhz16 = 2u,
    Mhz8 = 3u,
    Mhz4 = 4u,
};

/** @brief RCL 校准频率 (对应 en_sysctrl_rcl_freq_t) */
enum class RclFreq : std::uint8_t
{
    Hz38400 = 0x10u,
    Hz32768 = 0x11u,
};

/** @brief XTH 频率范围 (对应 en_sysctrl_xth_freq_t) */
enum class XthRange : std::uint8_t
{
    Mhz4_6 = 0u,
    Mhz6_12 = 1u,
    Mhz12_20 = 2u,
    Mhz20_32 = 3u,
};

/** @brief 晶振驱动能力 (对应 en_sysctrl_xtal_driver_t): 0 最弱 .. 3 最强 */
enum class Drive : std::uint8_t
{
    Drive0 = 0u,
    Drive1 = 1u,
    Drive2 = 2u,
    Drive3 = 3u,
};

/** @brief XTH 起振稳定等待周期 (对应 en_sysctrl_xth_cycle_t) */
enum class XthCycle : std::uint8_t
{
    Cycle256 = 0u,
    Cycle1024 = 1u,
    Cycle4096 = 2u,
    Cycle16384 = 3u,
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

/** @brief 整块板子的启动配置 (只影响 SystemInit 里的一次性时钟初始化) */
struct Config
{
    ClockSource source = ClockSource::Rch;      ///< 复位后切换到哪个时钟源
    RchFreq rch_freq = RchFreq::Mhz4;           ///< RCH 输出频率
    RclFreq rcl_freq = RclFreq::Hz32768;        ///< RCL 校准频率
    XthRange xth_range = XthRange::Mhz6_12;     ///< XTH 频率范围 (须覆盖 SYSTEM_XTH)
    Drive xth_drive = Drive::Drive3;            ///< XTH 驱动能力
    XthCycle xth_stable = XthCycle::Cycle16384; ///< XTH 起振稳定等待
    HclkDiv hclk_div = HclkDiv::Div1;
    PclkDiv pclk_div = PclkDiv::Div1;
};

/// RCH 档位 -> 实际输出频率 (Hz); 与厂商 u32hcr_tbl 一致
constexpr std::uint32_t rch_hz(RchFreq f) noexcept
{
    switch (f)
    {
    case RchFreq::Mhz24:
        return 24000000u;
    case RchFreq::Mhz22_12:
        return 22120000u;
    case RchFreq::Mhz16:
        return 16000000u;
    case RchFreq::Mhz8:
        return 8000000u;
    default:
        return 4000000u;
    }
}

/// 各 XTH 频段覆盖的频率区间 [lo, hi) (Hz)
constexpr bool xth_range_covers(XthRange r, std::uint32_t hz) noexcept
{
    switch (r)
    {
    case XthRange::Mhz4_6:
        return hz > 4000000u && hz <= 6000000u;
    case XthRange::Mhz6_12:
        return hz > 6000000u && hz <= 12000000u;
    case XthRange::Mhz12_20:
        return hz > 12000000u && hz <= 20000000u;
    default:
        return hz > 20000000u && hz <= 32000000u;
    }
}

/// 编译期校验: 各字段取值是否都在厂商允许范围内
constexpr bool is_valid(const Config &c) noexcept
{
    /* F005 无 PLL, 也没有失效检测; 需要校验的只有"晶振档位与目标源是否自洽" */
    (void)c;
    return true;
}

/* ---- 预设: app 在 board_config.h 里挑一个赋给 HC32_BOARD_CONFIG ---- */

/// [默认] 不依赖外部晶振, 复位默认档: RCH 4 MHz
inline constexpr Config preset_rch_4mhz{
    .source = ClockSource::Rch,
    .rch_freq = RchFreq::Mhz4,
};

/// 不依赖外部晶振跑满 RCH: 24 MHz
inline constexpr Config preset_rch_24mhz{
    .source = ClockSource::Rch,
    .rch_freq = RchFreq::Mhz24,
};

/// STK 板 (32 MHz 外部晶振): XTH 直出 32 MHz
inline constexpr Config preset_xth_32mhz{
    .source = ClockSource::Xth,
    .xth_range = XthRange::Mhz20_32,
    .xth_drive = Drive::Drive3,
};

/// 8 MHz 外部晶振: XTH 直出 8 MHz
inline constexpr Config preset_xth_8mhz{
    .source = ClockSource::Xth,
    .xth_range = XthRange::Mhz6_12,
    .xth_drive = Drive::Drive2,
};

/* HAL 自带的预设本身也必须合法 (改了预设却没同步约束时在这里报错) */
static_assert(is_valid(preset_rch_4mhz), "HAL 预设 preset_rch_4mhz 非法");
static_assert(is_valid(preset_rch_24mhz), "HAL 预设 preset_rch_24mhz 非法");
static_assert(is_valid(preset_xth_32mhz), "HAL 预设 preset_xth_32mhz 非法");
static_assert(is_valid(preset_xth_8mhz), "HAL 预设 preset_xth_8mhz 非法");

} // namespace hc32::board

#endif /* __cplusplus (机制部分结束) */

/* ==========================================================================
 * 2. 板级配置「策略」——由 app 提供 (HAL 不替任何板子做选择)
 * --------------------------------------------------------------------------
 * app 需在它的 inc 目录放一个 board_config.h (本文件会自动包含), 里面定义:
 *   SYSTEM_XTH           板上实际焊接的高速晶振频率 (Hz)
 *   HC32_BOARD_CONFIG    实际生效的 hc32::board::Config 表达式
 *   (可选) 板载资源宏    LED / 按键等引脚
 *
 * 也可改用编译选项传入 (二选一或混用均可):
 *   -DSYSTEM_XTH=32000000
 *   -DHC32_BOARD_CONFIG=::hc32::board::preset_rch_4mhz
 *
 * 注意: F005 无 SYSTEM_XTL (厂商 sysctrl.c 不引用 XTL 频率宏, 也无 XTL 振幅配置).
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

/// 实际生效的板级配置 —— 取自 app 的 board_config.h
inline constexpr Config config = HC32_BOARD_CONFIG;

static_assert(is_valid(config), "板级配置非法: 请检查 app 的 board_config.h");
static_assert(config.source != ClockSource::Xth || xth_range_covers(config.xth_range, xth_hz),
              "XTH 档位与 SYSTEM_XTH 不匹配: 请让 board_config.h 里的 "
              "config.xth_range 覆盖 SYSTEM_XTH 的频率");

/// 本配置是否会真正用到外部晶振
inline constexpr bool uses_external_crystal =
    (config.source == ClockSource::Xth) || (config.source == ClockSource::Xtl);

/// 切换完成后的 HCLK (Hz) —— 供 config.cpp 选 Flash 等待周期, 也可被应用读取
constexpr std::uint32_t target_hclk_hz() noexcept
{
    std::uint32_t src;
    switch (config.source)
    {
    case ClockSource::Xth:
        src = xth_hz;
        break;
    case ClockSource::Rcl:
        src = (config.rcl_freq == RclFreq::Hz32768) ? 32768u : 38400u;
        break;
    case ClockSource::Xtl:
        src = 32768u;
        break;
    default:
        src = rch_hz(config.rch_freq);
        break;
    }
    constexpr std::uint32_t div[] = {1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u};
    return src / div[static_cast<std::uint8_t>(config.hclk_div)];
}

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

    void SystemCoreClockUpdate(void); /*!< 重新读取并刷新上面这个变量 */
    void SystemInit(void);            /*!< 复位后由 startup.s 调用 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F005_CONFIG_H__ */
