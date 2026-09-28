#!/usr/bin/env python3
"""
把 XHSC HC32A052 DDL 聚合为自包含的驱动层:

  输入 (temp/, 只读):
    driver/inc/*.h   (30 个模块)            驱动模块声明
    driver/src/*.c   (30 个模块)            驱动模块实现
    mcu/common/base_types.h                 基础类型
    mcu/common/hc32a052.h                   器件寄存器 / 中断号 / 外设基址
    mcu/common/interrupts_hc32a052.{h,c}    中断分发框架
    mcu/common/system_hc32a052.h            系统时钟声明
    example/template/source/ddl_device.h    器件型号宏 (无实际消费者)

  输出 (hal/hc32a052/):
    driver.h        全部声明/类型/宏, 单层 extern "C"
    driver.cpp      全部实现

  刻意不进入 driver 的部分 (与板级/外部强相关, 需人工维护):
    mcu/common/system_hc32a052.c   ->  hal/hc32a052/config.cpp   (时钟初始化实现)
    mcu/common/board_stkhc32a052.h ->  hal/hc32a052/config.h     (板级配置机制/类型/预设)
                                        app/<proj>/inc/board_config.h  (板级策略, app 侧)

处理规则:
  1. CRLF -> LF
  2. 去掉每个文件开头重复的 license / @file 注释块
  3. 去掉 include guard (#ifndef/#define/#endif)
  4. 去掉各文件自己的 #ifdef __cplusplus / extern "C" { ... } 块 (合成一层)
  5. 头文件 include 就地展开, 全局 emitted 集合复刻原 include guard 语义
     (ddl.h 被 29 个头文件 include, 只能真正展开一次)
  6. 系统头 <...> 上提到文件顶部; 但器件头的 <core_cm0plus.h> 必须留在
     IRQn_Type 之后 (CMSIS 依赖器件头先提供 IRQn_Type 与 __NVIC_PRIO_BITS)
  7. 丢弃 #include "board_stk<chip>.h" (板级内容已迁到 config.h)
  8. 去掉结尾 "EOF (not truncated)" 块
  9. 应用 C -> C++ 兼容性补丁 与 原厂遗漏声明补全
 10. 为原厂只有 __WEAK 声明、没有定义的中断回调补空定义

用法: python3 tools/merge_driver.py [--chip hc32a052]
"""
import glob
import os
import re
import sys

# ============================================================================
# ★ 换芯片时主要改这里 (也可命令行 --chip hc32f052)
# ----------------------------------------------------------------------------
# 目录/文件名全部由芯片名推导:
#   temp/HC32<XXX>_DLL_*/      厂商 DDL 包 (自动取排序最大的一个)
#   <chip>.h                   器件寄存器/中断号头 (mcu/common)
#   interrupts_<chip>.{h,c}    中断分发框架
#   system_<chip>.{h,c}        系统时钟 (声明进 driver.h, 实现迁到 config.cpp)
#   board_stk<chip>.h          板级头 (丢弃, 内容迁到 config.h)
# 仍需人工核对 (各芯片不同, 见文件末尾 "★ 逐芯片人工核对项"):
#   MISSING_DECLS / CPP_PATCHES / 器件头拆分锚点 / IRQ 符号提取正则
# ============================================================================
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CHIP = "hc32a052"
if "--chip" in sys.argv:
    CHIP = sys.argv[sys.argv.index("--chip") + 1]

UPPER = "HC32" + CHIP[4:].upper()          # hc32a052 -> HC32A052

_dll_dirs = sorted(glob.glob(os.path.join(ROOT, "temp", UPPER + "_DLL_*")))
if not _dll_dirs:
    raise SystemExit("找不到厂商 DDL 目录: temp/%s_DLL_*" % UPPER)
DLL = _dll_dirs[-1]

DRV_INC = os.path.join(DLL, "driver/inc")
DRV_C = os.path.join(DLL, "driver/src")
MCU = os.path.join(DLL, "mcu/common")
TPL = os.path.join(DLL, "example/template/source")
HAL = os.path.join(ROOT, "hal", CHIP)
OUT_H = os.path.join(HAL, "driver.h")
OUT_C = os.path.join(HAL, "driver.cpp")
SELF = "tools/merge_driver.py"

# 由芯片名推导的文件名
DEVICE_H = CHIP + ".h"                      # hc32a052.h
IRQ_H = "interrupts_" + CHIP + ".h"
IRQ_C = "interrupts_" + CHIP + ".c"
SYS_H = "system_" + CHIP + ".h"
SYS_C = "system_" + CHIP + ".c"

# ---- 参与合并的头文件注册表: 文件名 -> 所在目录 -----------------------------
HDR_SRC = {}
for _f in os.listdir(DRV_INC):
    if _f.endswith(".h"):
        HDR_SRC[_f] = DRV_INC
for _f in os.listdir(MCU):
    if _f.endswith(".h"):
        HDR_SRC[_f] = MCU
HDR_SRC["ddl_device.h"] = TPL

# 板级头: 内容已迁到 config.h, 此处丢弃其引用 (按前缀匹配, 兼容各芯片命名)
DROPPED_INCLUDE_PREFIXES = ("board_stk",)

MERGED_SRCS = sorted(f for f in os.listdir(DRV_C) if f.endswith(".c"))
MCU_SRCS = [IRQ_C]                          # 进 driver.cpp
EXCLUDED_SRCS = [SYS_C]                     # 不进 driver.cpp, 见 config.cpp

SYSINC_RE = re.compile(r"^\s*#\s*include\s+<([^>]+)>")
INKINC_RE = re.compile(r'^\s*#\s*include\s+"([^"]+)"')

MERGED_HDRS = sorted(f for f in os.listdir(DRV_INC) if f.endswith(".h"))

# ---- 原厂遗漏声明补全 --------------------------------- ★ 逐芯片人工核对 ---------
# 这些符号在 src 中有定义, 但原厂头文件从未声明它们.
# 原始 C 工程下它们天然是 C 链接; 聚合到单个 .cpp 后用 C++ 编译会得到 _Z... 修饰名,
# 与其它 TU (C 或 extern "C" 声明) 的引用不匹配, 故必须补声明.
# 校验方式: clang++ -c driver.cpp && llvm-nm driver.o | grep -w _Z   (应为空)
MISSING_DECLS = [
    "void     SPI_SetDMAReq(SPI_TypeDef *SPIx, uint32_t u32DMAReq);",
    "uint32_t SPI_GetDMAReq(SPI_TypeDef *SPIx);",
    "void     Sysctrl_GetChipInfo(stc_sysctrl_chip_info_t *pstcChipInfo);",
    # SystemHCLK / SystemPCLK 定义于 system_hc32a052.c 却从未声明, 同属原厂遗漏.
    # 实现已移到 config.cpp, 此处补声明.
    "extern uint32_t SystemHCLK;",
    "extern uint32_t SystemPCLK;",
]

# ---- C -> C++ 兼容性补丁 --------------------------------- ★ 逐芯片人工核对 ----
# 原代码是 C 编译的; C 允许 "枚举变量 &= 整数掩码" (隐式转换), C++ 不允许.
# 显式加一次强制转换, 行为与 C 版完全一致 (仅清掉掩码位).
CPP_PATCHES = [
    (
        "        enPeripheral &= ~_PERICLK_REG1_MSK;",
        "        /* C++: 枚举不可直接复合赋值位掩码, 显式转换, 语义与 C 一致 */\n"
        "        enPeripheral = (en_sysctrl_peripheral_gate_t)((uint32_t)enPeripheral & ~(uint32_t)_PERICLK_REG1_MSK);",
        2,
    ),
    (
        "        enPeripheral &= (~_PERICLK_REG1_MSK);",
        "        enPeripheral = (en_sysctrl_peripheral_gate_t)((uint32_t)enPeripheral & ~(uint32_t)_PERICLK_REG1_MSK);",
        1,
    ),
    (
        "        enFunc &= ~_SYSCTRL_FUNC_MSK;",
        "        enFunc = (en_sysctrl_func_t)((uint32_t)enFunc & ~(uint32_t)_SYSCTRL_FUNC_MSK);",
        1,
    ),
    # USART_SC_Init(): switch 的 default 分支未给 u32Cr3Val 赋值, 随后直接写 USARTx->CR3,
    # 属原厂代码的 UB (-Wsometimes-uninitialized). 初始化为 0 (SCEN 关闭) 以消除.
    (
        "    uint32_t u32CalBaudRate = 0U;\n    uint32_t u32Parity;\n    uint32_t u32Cr3Val;",
        "    uint32_t u32CalBaudRate = 0U;\n    uint32_t u32Parity;\n"
        "    uint32_t u32Cr3Val = 0U;   /* 原厂 default 分支未赋值, 消除 UB */",
        1,
    ),
]

warnings = []


def read(path):
    with open(path, "rb") as fp:
        raw = fp.read()
    return raw.replace(b"\r\n", b"\n").replace(b"\r", b"\n").decode("utf-8")


def strip_leading_banner(text, path):
    """去掉文件开头的 /** ... */ 大注释块 (license/@file/@brief/change log)."""
    m = re.match(r"[ \t]*/\*\*.*?\*/[ \t]*\n", text, re.S)
    if m:
        return text[m.end():]
    warnings.append("no leading banner: %s" % path)
    return text


def strip_trailing(text):
    """从尾部剥掉空白行 / #endif / 结尾注释块."""
    lines = text.split("\n")
    while lines:
        s = lines[-1].strip()
        if s == "":
            lines.pop()
            continue
        if re.match(r"^#endif\b", s):
            lines.pop()
            continue
        if s.endswith("*/"):
            depth = 0
            i = len(lines) - 1
            while i >= 0:
                depth += lines[i].count("*/") - lines[i].count("/*")
                if depth <= 0:
                    break
                i -= 1
            if i >= 0 and "/*" in "".join(lines[i:]):
                del lines[i:]
                continue
        break
    return "\n".join(lines)


def drop_cxx_blocks(text, path):
    """删掉 #ifdef __cplusplus / extern "C" { ... } 成对块 (只含 extern "C" 与花括号的)."""
    lines = text.split("\n")
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if re.match(r"^\s*#\s*if\s+(defined\s*\(\s*__cplusplus\s*\)|defined\s+__cplusplus|__cplusplus)\s*$", line) \
           or re.match(r"^\s*#\s*ifdef\s+__cplusplus\s*$", line):
            depth = 1
            j = i + 1
            body = []
            while j < len(lines) and depth > 0:
                t = lines[j].strip()
                if re.match(r"^#\s*if", t):
                    depth += 1
                elif re.match(r"^#\s*endif", t):
                    depth -= 1
                    if depth == 0:
                        break
                if depth > 0:
                    body.append(t)
                j += 1
            body_txt = " ".join(body).strip()
            if re.fullmatch(r'(extern\s+"C"\s*\{?)?\s*(\}\s*)?\s*', body_txt):
                i = j + 1
                continue
            warnings.append("unexpected __cplusplus body in %s: %r" % (path, body_txt[:120]))
            out.append(line)
            i += 1
            continue
        out.append(line)
        i += 1
    return "\n".join(out)


def drop_guard(text):
    lines = text.split("\n")
    out = []
    i = 0
    while i < len(lines):
        if re.match(r"^\s*#\s*ifndef\s+__\w+_H__\s*$", lines[i]) \
           and i + 1 < len(lines) and re.match(r"^\s*#\s*define\s+__\w+_H__\s*$", lines[i + 1]):
            i += 2
            continue
        out.append(lines[i])
        i += 1
    return "\n".join(out)


def tidy(text):
    lines = [ln.rstrip() for ln in text.split("\n")]
    return "\n".join(lines).strip("\n")


# ---------------------------------------------------------------- include 展开

def flatten_header(name, emitted, sys_inc, keep_sysinc=False):
    """就地展开已注册的头文件 include, 返回内容行.

    emitted    : 全局已展开集合, 等价于原 include guard 去重语义
                 (ddl.h 被 29 个头文件 include, 只能真正展开一次)
    sys_inc    : 收集到的系统头 <...>, 稍后统一上提到文件顶部
    keep_sysinc: True 时系统头保留原位 —— hc32a052.h 的 <core_cm0plus.h>
                 必须留在 IRQn_Type 之后, CMSIS 依赖设备头先提供该类型
    """
    if name in emitted:
        return []
    emitted.add(name)
    path = os.path.join(HDR_SRC[name], name)
    text = read(path)
    text = strip_leading_banner(text, path)
    text = strip_trailing(text)
    text = drop_cxx_blocks(text, path)
    text = drop_guard(text)

    body = []
    for line in text.split("\n"):
        m = SYSINC_RE.match(line)
        if m:
            if keep_sysinc:
                body.append(line)
            elif m.group(1) not in sys_inc:
                sys_inc.append(m.group(1))
            continue
        m = INKINC_RE.match(line)
        if m:
            inc = os.path.basename(m.group(1))
            if any(inc.startswith(p) for p in DROPPED_INCLUDE_PREFIXES):
                continue
            if inc in HDR_SRC:
                sub = flatten_header(inc, emitted, sys_inc)
                if sub:
                    body.append("/* >>> inlined from %s */" % inc)
                    body += sub
                    body.append("/* <<< end of %s */" % inc)
            else:
                body.append(line)       # 未注册的头, 原样保留
            continue
        body.append(line)
    return body


def flatten_source(name, src_dir):
    """读取 .c 实现, 丢弃其中的 #include (driver.h 已全部包含)."""
    path = os.path.join(src_dir, name)
    text = read(path)
    text = strip_leading_banner(text, path)
    text = strip_trailing(text)
    text = drop_cxx_blocks(text, path)
    return [ln for ln in text.split("\n") if not re.match(r'^\s*#\s*include\b', ln)]


def split_device_head(body):               # ★ 逐芯片人工核对: 拆分锚点
    """把器件头拆成 (CMSIS 前置段, 器件定义段).

    前置段 = CMSIS 配置宏 + IRQn_Type + <core_cm0plus.h> + <stdint.h>,
    必须整体位于其余器件定义之前, 且必须放在 driver.h 的 extern "C" 之外
    (CMSIS 核心头自带 C++ 处理, 不宜卷进 C 链接块).
    """
    for i, ln in enumerate(body):
        m = SYSINC_RE.match(ln)
        if m and m.group(1) == "stdint.h":
            return body[:i + 1], body[i + 1:]
    raise SystemExit("%s: 找不到 <stdint.h> 拆分点" % DEVICE_H)


def extract_irq_symbols():                 # ★ 逐芯片人工核对: 提取正则
    """从 interrupts_<chip>.c 提取需要在 driver.h 补 extern "C" 声明的符号.

    原厂 interrupts_<chip>.h 只声明了 EnableNvic(), 这些中断入口/回调全部
    没有声明. 单独编译成 .o 时它们是 C 符号, 但合并进 driver.cpp 后用 C++
    编译, 就会变成 _Z... 修饰名, 向量表里引用的 C 符号名便再也找不到 ->
    实测后果: 向量表全部指向 startup.s 的 Default_Handler, 中断彻底失效.

    返回 (弱回调名列表, 中断入口名列表).
    """
    path = os.path.join(MCU, IRQ_C)
    lines = read(path).split("\n")
    weak_cbs, handlers = [], []
    for i, ln in enumerate(lines):
        t = ln.strip()
        m = re.match(r"^__WEAK\s+void\s+(\w+)\s*\(\s*void\s*\)\s*;$", t)
        if m:
            weak_cbs.append(m.group(1))
            continue
        m = re.match(r"^void\s+(\w+)\s*\(\s*void\s*\)\s*$", t)
        if m:
            j = i + 1
            while j < len(lines) and not lines[j].strip():
                j += 1
            if j < len(lines) and lines[j].strip().startswith("{"):
                handlers.append(m.group(1))
    if not weak_cbs or not handlers:
        raise SystemExit("%s: 中断符号提取失败 "
                         "(回调 %d 个, 入口 %d 个)" % (IRQ_C, len(weak_cbs), len(handlers)))
    return weak_cbs, handlers


# ---------------------------------------------------------------- 文本块

def banner(kind, title):
    return """/**
 *******************************************************************************
 * @file  %s
 * @brief %s
 *
 * 本文件由 XHSC %s DDL 自动聚合生成, 请勿逐模块手工修改.
 * 重新生成: python3 %s            (会覆盖本文件的修改)
 *
 * 聚合来源: temp/ 下的厂商 DDL 包 (%s_DLL_xxx)
 *   driver/{inc,src}   驱动模块
 *   mcu/common/        base_types.h / 器件头 / 中断框架
 *
 * 未纳入本文件的部分 (与板级/外部强相关, 按「机制/策略」分层):
 *   hal/%s/config.h          板级配置「机制」: 类型 / 预设 / 校验
 *   hal/%s/config.cpp        时钟初始化实现 (SystemInit)
 *   app/<proj>/inc/board_config.h  板级「策略」: 晶振频率 + 生效配置 + 板载引脚
 *                                  (由 config.h 自动包含, app 侧文件)
 *
 * 所有函数声明统一包裹在一层 extern "C" 内, 保持 C 链接以保证底层寄存器操作
 * 不受 C++ 名称修饰影响; 亦因此本头文件可被 C 与 C++ 同时包含.
 *
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
""" % (kind, title, UPPER, SELF, UPPER, CHIP, CHIP)


CONFIG_BLOCK = """/******************************************************************************/
/* 板级配置 (外部相关, 按「机制/策略」分层)
 *
 * 驱动中的时钟计算 (sysctrl.c 的 PLL 与 Sysctrl_GetHClkFreq) 必须知道板上实际
 * 焊接的晶振频率 (SYSTEM_XTH / SYSTEM_XTL), 故自动包含同目录下的 config.h.
 *
 *   config.h       板级配置「机制」: Config 类型 / 预设 / 校验 (HAL 提供)
 *   board_config.h 板级配置「策略」: 晶振频率 + 生效配置 (app 提供)
 *                  config.h 会自动 #include 它 (若在 include path 上)
 *
 * 若确实不用 board_config.h, 也可用编译选项传入:
 *   -DSYSTEM_XTH=8000000 -DSYSTEM_XTL=32768
 *   -DHC32_BOARD_CONFIG=::hc32::board::preset_rch_4mhz
 */
/******************************************************************************/
#if defined(__has_include)
#  if __has_include("config.h")
#    include "config.h"
#  endif
#endif

#if !defined(SYSTEM_XTH)
#  error "SYSTEM_XTH 未定义: 请在 app 的 inc 目录创建 board_config.h, 给出外部高速晶振频率(Hz)"
#endif
#if !defined(SYSTEM_XTL)
#  error "SYSTEM_XTL 未定义: 请在 app 的 inc 目录创建 board_config.h, 给出外部低速晶振频率(Hz)"
#endif"""


def section(title):
    return [
        "",
        "/* ========================================================================== */",
        "/*  %-72s  */" % title,
        "/* ========================================================================== */",
        "",
    ]


# ---------------------------------------------------------------- 组装

def build_header():
    emitted = set()
    sys_inc = []

    base = flatten_header("base_types.h", emitted, sys_inc)
    dev_full = flatten_header(DEVICE_H, emitted, sys_inc, keep_sysinc=True)
    dev_head, dev_rest = split_device_head(dev_full)
    # 先取走中断/系统头, 避免它们被 ddl.h 里的 include 拉到中间位置
    irq = flatten_header(IRQ_H, emitted, sys_inc)
    sysm = flatten_header(SYS_H, emitted, sys_inc)
    core = flatten_header("ddl.h", emitted, sys_inc)          # 内含 sysctrl.h
    mods = []
    for h in MERGED_HDRS:
        mods += flatten_header(h, emitted, sys_inc)

    guard = "__%s_DRIVER_H__" % CHIP.upper()
    lines = [banner("driver.h",
                    "%s DDL 驱动库 - 聚合头文件 (声明/类型/宏) [自动生成, 勿手改]" % UPPER)]
    lines.append("#ifndef " + guard)
    lines.append("#define " + guard)
    lines.append("")
    lines += CONFIG_BLOCK.split("\n")
    lines += section("系统头")
    for s in sys_inc:
        lines.append("#include <%s>" % s)
    lines += section("基础类型 (mcu/common/base_types.h)")
    lines += base
    lines += section("CMSIS 内核配置 + 中断号 "
                     "(%s 前置段, 必须早于 core_cm0plus.h)" % DEVICE_H)
    lines += dev_head
    lines += section("器件寄存器 / 位定义 / 外设基址 (%s)" % DEVICE_H)
    lines += dev_rest
    lines += section("C 链接区: 以下全部为 C 符号, 供 C / C++ 共用")
    lines.append("#ifdef __cplusplus")
    lines.append('extern "C" {')
    lines.append("#endif")
    lines += section("驱动核心: 公共宏 / 类型 / 系统控制 (ddl.h + sysctrl.h)")
    lines += core
    lines += section("驱动模块 (driver/inc 其余 %d 个)" % max(len(MERGED_HDRS) - 2, 0))
    lines += mods
    lines += section("中断分发框架 (mcu/common/%s)" % IRQ_H)
    lines += irq
    lines += section("中断入口与回调声明 (原厂头文件遗漏, 必须补 C 链接声明)")
    lines.append("/*")
    lines.append(" * %s 只声明了 EnableNvic(), 下面这些全部没有声明." % IRQ_H)
    lines.append(" * 单独编译成 .o 时它们是 C 符号; 但合并进 driver.cpp 后用 C++ 编译,")
    lines.append(" * 会得到 _Z... 修饰名, 向量表引用的 C 符号名再也匹配不上, 实测后果是")
    lines.append(" * 向量表全部落回 startup.s 的 Default_Handler, 中断彻底失效.")
    lines.append(" *")
    lines.append(" * 另: 回调若是弱未定义 (用户没实现), 入口会跳到地址 0. 使用时请按需实现.")
    lines.append(" */")
    weak_cbs, handlers = extract_irq_symbols()
    lines.append("/* 中断回调: 弱符号, 应用层实现同名函数即可覆盖 (%d 个) */" % len(weak_cbs))
    for n in weak_cbs:
        lines.append("__WEAK void %s(void);" % n)
    lines.append("")
    lines.append("/* 向量表中断入口: driver 提供强定义, 覆盖 startup.s 的弱默认 (%d 个) */"
                 % len(handlers))
    for n in handlers:
        lines.append("void %s(void);" % n)
    lines += section("系统时钟声明 (mcu/common/%s)" % SYS_H)
    lines += sysm
    lines += section("原厂遗漏声明的补全")
    lines.append("/*")
    lines.append(" * 以下符号在源码中有定义, 但原厂头文件从未声明:")
    lines.append(" *   - SPI_* / Sysctrl_GetChipInfo: 若不补声明, 聚合到 .cpp 用 C++")
    lines.append(" *     编译后会变成 _Z... 修饰名, 与其它 TU 的 C 符号引用不匹配;")
    lines.append(" *   - SystemHCLK / SystemPCLK: 全局变量漏声明, 实现见 config.cpp.")
    lines.append(" * 校验: clang++ -c driver.cpp && llvm-nm driver.o | grep -w _Z")
    lines.append(" */")
    lines += MISSING_DECLS
    lines.append("")
    lines.append("#ifdef __cplusplus")
    lines.append("}")
    lines.append("#endif")
    lines.append("")
    lines.append("#endif /* %s */" % guard)
    return tidy("\n".join(lines)) + "\n"


def apply_patches(text):
    """应用 C -> C++ 兼容性补丁, 并校验每条的命中次数."""
    for old, new, expect in CPP_PATCHES:
        n = text.count(old)
        if n != expect:
            raise SystemExit("PATCH MISMATCH: expected %d, got %d for %r" % (expect, n, old[:60]))
        text = text.replace(old, new)
    return text


def build_source():
    lines = [banner("driver.cpp",
                    "%s DDL 驱动库 - 聚合实现 [自动生成, 勿手改]" % UPPER)]
    lines.append('#include "driver.h"')
    lines.append("")
    lines.append("/* 厂商 C 代码惯用 `volatile 变量--` (超时计数), C++20 起被标记 deprecated.")
    lines.append(" * 语义无误, 仅在生成本 TU 内屏蔽该告警, 不影响用户代码. */")
    lines.append("#if defined(__clang__)")
    lines.append('#  pragma clang diagnostic ignored "-Wdeprecated-volatile"')
    lines.append("#endif")
    order = ["ddl.c"] + [s for s in MERGED_SRCS if s != "ddl.c"]
    for s in order:
        lines += section(s)
        lines += flatten_source(s, DRV_C)
    for s in MCU_SRCS:
        lines += section("%s (mcu/common)" % s)
        lines += flatten_source(s, MCU)

    # ---- 中断回调弱定义 (空实现) --------------------------------------------
    # 原厂只在 interrupts_hc32a052.c 里对这批回调做了 __WEAK *声明* (没有定义),
    # 而入口处理函数 (SysTick_Handler / PORTA_IRQHandler ...) 会调用它们.
    # 只声明未定义 => "弱未定义符号": 实测 LLD 会把 bl 退化成相对偏移 0 (空操作),
    # 但这依赖链接器行为, 换链接器/换优化级别可能变成跳地址 0 -> HardFault.
    # 这里补 __WEAK 空定义: 符号有定义, 调用行为确定; 应用层写同名强定义即可覆盖.
    weak_cbs, _ = extract_irq_symbols()
    lines += section("中断回调弱定义 (空实现, 应用层可写同名强符号覆盖)")
    lines.append("/*")
    lines.append(" * 下列回调原厂只有 __WEAK 声明而无定义, 入口处理函数却会调用它们.")
    lines.append(" * 补空定义以消除弱未定义符号 (调用行为不再依赖链接器细节).")
    lines.append(" * 应用层若要处理该中断, 直接定义同名函数 (非 __WEAK) 即可自动覆盖.")
    lines.append(" */")
    for n in weak_cbs:
        lines.append("__WEAK void %s(void) {}" % n)

    return apply_patches(tidy("\n".join(lines))) + "\n"


def main():
    h = build_header()
    c = build_source()
    with open(OUT_H, "w", encoding="utf-8", newline="\n") as fp:
        fp.write(h)
    with open(OUT_C, "w", encoding="utf-8", newline="\n") as fp:
        fp.write(c)
    print("chip       = %s   (DDL: %s)" % (CHIP, os.path.basename(DLL)))
    print("driver.h   lines=%d  -> %s" % (h.count("\n"), OUT_H))
    print("driver.cpp lines=%d  -> %s" % (c.count("\n"), OUT_C))
    print("未纳入 (机制层): hal/%s/config.h, hal/%s/config.cpp" % (CHIP, CHIP))
    print("未纳入 (策略层, app 侧): app/<proj>/inc/board_config.h  <- 改板级参数改这里")
    print("  其中 %s 未进入 driver.cpp (时钟初始化, 见 config.cpp)"
          % ", ".join(EXCLUDED_SRCS))
    if warnings:
        print("\nWARNINGS (%d):" % len(warnings))
        for w in warnings:
            print("  " + w)
    return 0


if __name__ == "__main__":
    sys.exit(main())
