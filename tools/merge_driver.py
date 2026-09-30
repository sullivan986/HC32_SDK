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
# ★ 换芯片时主要改这里: 在 PROFILE 里加一项 (也可命令行 --chip hc32f005)
# ----------------------------------------------------------------------------
# 目录/文件名全部由芯片名推导:
#   temp/HC32<XXX>_D?L_*/      厂商 DDL 包 (DLL 或 DDL 均可, 取排序最大的)
#   <chip>.h                   器件寄存器/中断号头 (mcu/common)
#   interrupts_<chip>.{h,c}    中断分发框架
#   system_<chip>.{h,c}        系统时钟 (声明进 driver.h, 实现迁到 config.cpp)
#   board_stk<chip>.h          板级头 (丢弃, 内容迁到 config.h)
# 仍需逐芯片人工核对的项 (grep ★): PROFILE 里的 missing_decls / cpp_patches,
#   器件头拆分锚点, IRQ 符号提取正则
# ============================================================================
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CHIP = "hc32a052"
if "--chip" in sys.argv:
    CHIP = sys.argv[sys.argv.index("--chip") + 1]

UPPER = "HC32" + CHIP[4:].upper()          # hc32a052 -> HC32A052

_dll_dirs = sorted(glob.glob(os.path.join(ROOT, "temp", UPPER + "_D?L_*")))
if not _dll_dirs:
    raise SystemExit("找不到厂商 DDL 目录: temp/%s_D?L_*" % UPPER)
DLL = _dll_dirs[-1]

HAL = os.path.join(ROOT, "hal", CHIP)
OUT_H = os.path.join(HAL, "driver.h")
OUT_C = os.path.join(HAL, "driver.cpp")
SELF = "tools/merge_driver.py"

SYSINC_RE = re.compile(r"^\s*#\s*include\s+<([^>]+)>")
INKINC_RE = re.compile(r'^\s*#\s*include\s+"([^"]+)"')

# 板级头: 内容已迁到 config.h, 此处丢弃其引用 (按前缀匹配, 兼容各芯片命名)
DROPPED_INCLUDE_PREFIXES = ("board_stk",)

# ---- 以下所有路径/文件清单都由 PROFILE 推导 (见下) --------------------------

# ---- 逐芯片 profile ------------------------------- ★ 逐芯片人工核对 ---------
# missing_decls: 在 src 中有定义、但原厂头文件从未声明的符号.
#   原始 C 工程下它们天然是 C 链接; 聚合到单个 .cpp 后用 C++ 编译会得到 _Z... 修饰名,
#   与其它 TU (C 或 extern "C" 声明) 的引用不匹配, 故必须补声明.
#   校验方式: clang++ -c driver.cpp && llvm-nm driver.o | grep -w _Z   (应为空)
# cpp_patches: C -> C++ 兼容性补丁, 每项 (原文, 替换, 命中次数).
#   命中次数不符会直接报错退出 (防止补丁失效却静默跳过).
# required_macros: config.h 必须提供的宏 (driver.h 顶部会 #error 检查).
#   每项为 (宏名, 说明) —— 说明写进 #error 文本, 便于使用者定位.
# sysinc_split: 器件头里区分 "CMSIS 前置段 / 器件定义段" 的锚点行.
PROFILE = {
    "hc32a052": {
        "required_macros": [("SYSTEM_XTH", "外部高速晶振频率(Hz)"),
                            ("SYSTEM_XTL", "外部低速晶振频率(Hz)")],
        "sysinc_split": "stdint.h",
        "missing_decls": [
            "void     SPI_SetDMAReq(SPI_TypeDef *SPIx, uint32_t u32DMAReq);",
            "uint32_t SPI_GetDMAReq(SPI_TypeDef *SPIx);",
            "void     Sysctrl_GetChipInfo(stc_sysctrl_chip_info_t *pstcChipInfo);",
            # SystemHCLK / SystemPCLK 定义于 system_<chip>.c 却从未声明,
            # 同属原厂遗漏. 实现已移到 config.cpp, 此处补声明.
            "extern uint32_t SystemHCLK;",
            "extern uint32_t SystemPCLK;",
        ],
        "cpp_patches": [
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
            # USART_SC_Init(): switch 的 default 分支未给 u32Cr3Val 赋值, 随后直接
            # 写 USARTx->CR3, 属原厂 UB. 初始化为 0 (SCEN 关闭) 以消除.
            (
                "    uint32_t u32CalBaudRate = 0U;\n    uint32_t u32Parity;\n    uint32_t u32Cr3Val;",
                "    uint32_t u32CalBaudRate = 0U;\n    uint32_t u32Parity;\n"
                "    uint32_t u32Cr3Val = 0U;   /* 原厂 default 分支未赋值, 消除 UB */",
                1,
            ),
        ],
    },
    "hc32f005": {
        # F005 的 board_stkhc32f005.h 只给了 SYSTEM_XTH, 未给 SYSTEM_XTL
        # (sysctrl.c 也未引用 XTL 频率宏), 故只强制要求 XTH.
        "required_macros": [("SYSTEM_XTH", "外部高速晶振频率(Hz)")],
        "sysinc_split": "stdint.h",
        "missing_decls": [
            # Uart_SetSaddr 在 uart.c 有定义, uart.h 却未声明
            "en_result_t Uart_SetSaddr(M0P_UART_TypeDef *UARTx, uint8_t u8Addr);",
            # Debug_Output 在 ddl.c 有定义, ddl.h 只声明了 Debug_UartInit
            "void Debug_Output(uint8_t u8Data);",
            # ddl.c 里两个 Keil/ARMCC 遗留的重定向钩子, 无任何头文件声明.
            # picolibc 下不会被调用, 但保留原样 (不删原厂代码) 就必须给出 C 链接
            # 声明, 否则它们会变成 _Z... 修饰名.
            "void _ttywrch(int c);",
            "int  __backspace(void);",
        ],
        "cpp_patches": [
            # ddl.c 无条件打开 __DEBUG, 从而编译出 MDK 风格的 fputc 重定向.
            # 该重定向在 picolibc 下**无效**(printf 走 FILE 回调而非 fputc), 而且
            # 一个强定义 fputc 可能与 libc 归档成员冲突; 其调用的 Debug_Output
            # 本身也已被原厂整段注释掉(空操作). 故显式保持 __DEBUG 未定义.
            (
                "#ifndef __DEBUG\n#define __DEBUG\n//#define __CC_ARM\n#endif",
                "/* C++/picolibc: 原厂借 __DEBUG 打开 MDK 风格 fputc 重定向.\n"
                " * picolibc 的 printf 走 FILE 回调而非 fputc, 该重定向无效,\n"
                " * 且强定义 fputc 有与 libc 归档成员冲突的风险; 其依赖的\n"
                " * Debug_Output 也已被原厂注释成空操作. 故保持 __DEBUG 未定义. */\n"
                "#undef __DEBUG",
                1,
            ),
        ],
    },
    "hc32f460": {
        # ---- 包布局: 与 A052/F005 完全不同 (LL 驱动, 不是 DDL) ----
        "module_hdr_dir": "drivers/hc32_ll_driver/inc",
        "module_src_dir": "drivers/hc32_ll_driver/src",
        "hdr_dirs": ["drivers/hc32_ll_driver/inc",
                     "drivers/cmsis/Device/HDSC/hc32f4xx/Include"],
        "src_dirs": ["drivers/hc32_ll_driver/src"],
        "base_hdr": "hc32_ll_def.h",          # DDL_ON/DDL_OFF/en_result_t 等
        "device_h": "hc32f460.h",
        "umbrella_hdr": "hc32_ll.h",
        "irq_hdrs": ["hc32_ll_interrupts.h", "hc32f460_ll_interrupts_share.h"],
        "irq_srcs": ["hc32_ll_interrupts.c", "hc32f460_ll_interrupts_share.c"],
        "sys_h": "system_hc32f460.h",
        "sys_c": "system_hc32f460.c",
        # hc32_ll_usb.c 需要 midware 的 usb_bsp.h, 聚合层不带中间件; 与之配套的
        # 头也必须排除, 否则 hc32_ll.h 打开 LL_USB 时会去 include usb_app_conf.h.
        "exclude_srcs": ["hc32_ll_usb.c"],
        "module_hdr_skip": ["hc32_ll.h", "hc32_ll_usb.h"],
        # hc32f4xx.h 靠这个宏选型: 不定义就 #error. 厂商工程里由 IDE 的
        # 预定义宏传入 (如 Keil 的 HC32F460), 这里写进 driver.h 开头最省事.
        # USE_DDL_DRIVER: hc32_ll.h 把"包含各模块头"的那段放在
        #   #if defined(USE_DDL_DRIVER) 里, 而它默认是注释掉的. 不定义的话
        #   模块声明会被整段编译掉, 只剩 .c 里的定义 -> 大面积 "undeclared".
        "device_defines": ["HC32F460", "USE_DDL_DRIVER"],
        # hc32f4xx_conf.h 在每个例程里都不同(多数模块 DDL_OFF), 聚合方案要
        # driver.h 自包含, 故用生成的"全部打开"版本替代它.
        "synthetic": {"hc32f4xx_conf.h": "ll_conf"},
        # F460 的时钟初始化直接读寄存器算频率, 厂商代码不引用晶振频率宏.
        "required_macros": [],
        "sysinc_split": "stdint.h",
        # LL 风格: 中断入口 (IRQ000_Handler..IRQ143_Handler) 已在厂商头里声明,
        # 聚合后不会变 _Z 名, 无需补声明; 也没有 __WEAK 回调节奏.
        "irq_style": "ll",
        "missing_decls": [],
        "cpp_patches": [],
    },
}
if CHIP not in PROFILE:
    raise SystemExit("芯片 %s 尚未在 PROFILE 中登记 (已有: %s)"
                     % (CHIP, ", ".join(sorted(PROFILE))))

# ---- DDL 风格 (A052/F005) 的缺省值: 只需在 profile 里写差异部分 -------------
_DDL_DEFAULTS = {
    "module_hdr_dir": "driver/inc",
    "module_src_dir": "driver/src",
    "hdr_dirs": ["driver/inc", "mcu/common"],
    "src_dirs": ["driver/src", "mcu/common"],
    "base_hdr": "base_types.h",
    "device_h": CHIP + ".h",
    "umbrella_hdr": "ddl.h",
    "irq_hdrs": ["interrupts_" + CHIP + ".h"],
    "irq_srcs": ["interrupts_" + CHIP + ".c"],
    "sys_h": "system_" + CHIP + ".h",
    "sys_c": "system_" + CHIP + ".c",
    "exclude_srcs": [],
    "module_hdr_skip": [],
    "synthetic": {},
    "irq_style": "ddl",
    "need_ddl_device": True,
}
PROF = dict(_DDL_DEFAULTS) if CHIP != "hc32f460" else {}
PROF.update(PROFILE[CHIP])

MISSING_DECLS = PROF["missing_decls"]
CPP_PATCHES = PROF["cpp_patches"]
REQUIRED_MACROS = PROF["required_macros"]
SYSINC_SPLIT = PROF["sysinc_split"]
IRQ_STYLE = PROF.get("irq_style", "ddl")

# ---------------------------------------------------------------------------
# 由 profile 解析出实际路径与文件清单
# ---------------------------------------------------------------------------
def _rel(p):
    return os.path.join(DLL, p) if p else None


DRV_INC = _rel(PROF["module_hdr_dir"])
DRV_C = _rel(PROF["module_src_dir"])
HDR_DIRS = [_rel(d) for d in PROF["hdr_dirs"]]
SRC_DIRS = [_rel(d) for d in PROF["src_dirs"]]

# 头/源注册表: 文件名 -> 所在目录 (同名以先注册的为准)
HDR_SRC = {}
for _d in HDR_DIRS:
    for _f in sorted(os.listdir(_d)):
        if _f.endswith(".h") and _f not in HDR_SRC:
            HDR_SRC[_f] = _d
SRC_SRC = {}
for _d in SRC_DIRS:
    for _f in sorted(os.listdir(_d)):
        if _f.endswith(".c") and _f not in SRC_SRC:
            SRC_SRC[_f] = _d

# ddl_device.h (器件系列/封装宏): A052 在 example/template/source/ 有,
# F005 则每个 example 各带一份 (经比对 md5 全同), 就近取第一份.
if PROF.get("need_ddl_device"):
    _tpl = _rel("example/template/source")
    _tpl_dev = os.path.join(_tpl, "ddl_device.h") if _tpl else None
    if _tpl_dev and os.path.isfile(_tpl_dev):
        HDR_SRC["ddl_device.h"] = _tpl
    else:
        _found = sorted(glob.glob(os.path.join(DLL, "example", "**", "ddl_device.h"),
                                  recursive=True))
        if not _found:
            raise SystemExit("找不到 ddl_device.h (器件系列/封装宏头)")
        HDR_SRC["ddl_device.h"] = os.path.dirname(_found[0])

DEVICE_H = PROF["device_h"]
BASE_HDR = PROF.get("base_hdr")
UMBRELLA_HDR = PROF.get("umbrella_hdr")
IRQ_HDRS = list(PROF.get("irq_hdrs", []))
IRQ_SRCS = list(PROF.get("irq_srcs", []))
SYS_H = PROF.get("sys_h")
SYS_C = PROF.get("sys_c")
EXCLUDED_SRCS = list(PROF.get("exclude_srcs", []))
MODULE_HDR_SKIP = set(PROF.get("module_hdr_skip", []))

MERGED_HDRS = sorted(f for f in os.listdir(DRV_INC)
                     if f.endswith(".h") and f not in MODULE_HDR_SKIP)
# 注意: 中断源必须从模块列表里排除 —— F460 的 hc32_ll_interrupts.c 就在
# hc32_ll_driver/src 下, 与模块同目录; 不排除会重复编进 driver.cpp (redefinition).
MERGED_SRCS = sorted(f for f in os.listdir(DRV_C)
                     if f.endswith(".c") and f not in EXCLUDED_SRCS
                     and f not in IRQ_SRCS)
MCU_SRCS = [s for s in IRQ_SRCS if s not in EXCLUDED_SRCS]


def build_synthetic_headers():
    """把 profile 里的 synthetic 声明展开成 {头文件名: 内容}.

    "ll_conf" 指按 module_hdr_dir 下现存的 hc32_ll_*.h 自动生成一份
    "全部打开"的 hc32f4xx_conf.h, 让聚合后的 driver.h 自包含、不依赖
    某个具体例程的 conf (原厂的 conf 每个例程都不同, 多数模块是 DDL_OFF).
    """
    out = {}
    for name, spec in PROF.get("synthetic", {}).items():
        if spec != "ll_conf":
            out[name] = spec
            continue
        mods = set()
        for f in os.listdir(DRV_INC):
            if f.startswith("hc32_ll_") and f.endswith(".h"):
                mods.add(f[len("hc32_ll_"):-2].upper())
        mods.discard("DEF")                      # 无 LL_DEF_ENABLE 消费者
        mods.add("INTERRUPTS_SHARE")             # hc32f460_ll_interrupts_share.h
        lines = [
            "/* 本块由 %s 生成, 替代原厂的 hc32f4xx_conf.h." % SELF,
            " * 原厂那份在每个例程里都不同(多数模块 DDL_OFF); 聚合方案要 driver.h",
            " * 自包含, 故统一打开全部模块.",
            " * LL_PRINT_ENABLE 保持 OFF: 打开会引入 IAR 专有的",
            " * <LowLevelIOInterface.h>. printf 重定向属应用层职责.",
            " * LL_USB_ENABLE 保持 OFF: 依赖 midware 的 usb_bsp.h, 聚合层不带中间件.",
            " */",
        ]
        off = {"PRINT", "USB"}
        for m in sorted(mods):
            lines.append("#define LL_%s_ENABLE%s(DDL_%s)"
                         % (m, " " * max(1, 34 - len(m)), "OFF" if m in off else "ON"))
        out[name] = "\n".join(lines)
    return out


SYNTHETIC_HEADERS = build_synthetic_headers()

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


def strip_trailing(text, drop_endif=True):
    """从尾部剥掉空白行 / 结尾注释块 / 最多**一个** include-guard 的 #endif.

    只删一个是有意的: F460 的模块头/源结尾是
        ...
        #endif /* LL_WDT_ENABLE */      <- 功能性收尾, 必须保留
        #endif /* __HC32_LL_WDT_H__ */  <- include guard, 可以删
    早先的实现会连删两个, 导致 driver.cpp 报 "unterminated conditional
    directive" (而且只在 F460 这种带模块开关的包上才暴露).
    源文件不调这里 (drop_endif=False), 因为 .c 结尾的 #endif 全是功能性的.
    """
    lines = text.split("\n")

    def pop_tail_noise():
        while lines:
            s = lines[-1].strip()
            if s == "":
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
                # 只有"整块都是注释"才算尾随注释. 像
                #     #endif /* LL_WDT_ENABLE */
                # 这种"指令 + 尾注释"的行也以 */ 结尾, 但它是指令, 删了就会
                # 让前面的 #if 失去配对 -> "unterminated conditional directive".
                if i >= 0 and lines[i].lstrip().startswith("/*") \
                   and "/*" in "".join(lines[i:]):
                    del lines[i:]
                    continue
            break

    pop_tail_noise()
    if drop_endif and lines and re.match(r"^#\s*endif\b", lines[-1].strip()):
        lines.pop()
        pop_tail_noise()
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
            if inc in SYNTHETIC_HEADERS:
                # 该头由 profile 提供生成内容, 不在这里就地展开 ——
                # build_header 会把它放到文件最前. 必须靠前: 伞形头里有
                #   #if (LL_ADC_ENABLE == DDL_ON) ... #endif
                # 这种"用开关控模块包含"的写法, 若生成内容晚于它,
                # 那些 #if 会因为宏未定义而判假, 模块声明整段消失.
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
    # 源文件结尾的 #endif 是功能性的 (如 LL_XXX_ENABLE 的收尾), 不能删
    text = strip_trailing(text, drop_endif=False)
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
        if m and m.group(1) == SYSINC_SPLIT:
            return body[:i + 1], body[i + 1:]
    raise SystemExit("%s: 找不到 <%s> 拆分点" % (DEVICE_H, SYSINC_SPLIT))


def extract_irq_symbols():                 # ★ 逐芯片人工核对: 提取正则
    """找出需要在 driver.h 补 extern "C" 声明的中断符号.

    DDL 风格 (A052/F005): 原厂 interrupts_<chip>.h 只声明了 EnableNvic(),
    而 interrupts_<chip>.c 里的中断入口/回调全部没有声明. 单独编译成 .o 时
    它们是 C 符号; 但合并进 driver.cpp 后用 C++ 编译, 就会得到 _Z... 修饰名,
    向量表引用的 C 符号名再也匹配不上 -> 向量表全落回 Default_Handler,
    中断彻底失效 (而编译链接全绿!). 故必须补 C 链接声明.

    LL 风格 (F460): hc32_ll_interrupts.h / hc32f460_ll_interrupts_share.h 已经
    声明了全部 IRQxxx_Handler, 合并不产生修饰名, 无需额外补声明.

    返回 (弱回调名列表, 中断入口名列表).
    """
    if IRQ_STYLE == "ll":
        return [], []

    src = IRQ_SRCS[0]
    path = os.path.join(SRC_SRC[src], src)
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
                         "(回调 %d 个, 入口 %d 个)" % (src, len(weak_cbs), len(handlers)))
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
 * 聚合来源: temp/%s/
%s
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
""" % (kind, title, UPPER, SELF, os.path.basename(DLL),
       "\n".join(" *   %-34s %s" % (d + "/", desc) for d, desc in
                 _src_dirs_desc()),
       CHIP, CHIP)


def _src_dirs_desc():
    """聚合来源的两行说明 (目录 + 用途), 给 banner 用."""
    mod = PROF["module_hdr_dir"] + "/"
    rest = [d for d in PROF["hdr_dirs"] if d != PROF["module_hdr_dir"]]
    out = [(mod, "驱动模块 (inc + src 同名目录)")]
    for d in rest:
        out.append((d + "/", "器件头 / 中断框架"))
    return out


CONFIG_BLOCK = """/******************************************************************************/
/* 板级配置 (外部相关, 按「机制/策略」分层)
 *
 * 驱动中的时钟计算 (sysctrl.c) 必须知道板上实际焊接的晶振频率, 故自动包含
 * 同目录下的 config.h.
 *
 *   config.h       板级配置「机制」: Config 类型 / 预设 / 校验 (HAL 提供)
 *   board_config.h 板级配置「策略」: 晶振频率 + 生效配置 (app 提供)
 *                  config.h 会自动 #include 它 (若在 include path 上)
 *
 * 若确实不用 board_config.h, 也可用编译选项传入:
{defs} *   -DHC32_BOARD_CONFIG=::hc32::board::<预设名>
 */
/******************************************************************************/
#if defined(__has_include)
#  if __has_include("config.h")
#    include "config.h"
#  endif
#endif
"""


def config_block():
    """按 profile 的 required_macros 生成板级配置检查块."""
    defs = "".join(" *   -D%s=<值>\n" % m for m, _ in REQUIRED_MACROS)
    txt = CONFIG_BLOCK.format(defs=defs)
    for m, desc in REQUIRED_MACROS:
        txt += ('#if !defined(%s)\n'
                '#  error "%s 未定义: 请在 app 的 inc 目录创建 board_config.h, '
                '给出%s"\n'
                '#endif\n' % (m, m, desc))
    return txt


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

    base = flatten_header(BASE_HDR, emitted, sys_inc) if BASE_HDR else []
    dev_full = flatten_header(DEVICE_H, emitted, sys_inc, keep_sysinc=True)
    dev_head, dev_rest = split_device_head(dev_full)
    # 先取走中断/系统头, 避免它们被伞形头里的 include 拉到中间位置
    irq, sysm, core, mods = [], [], [], []
    for h in IRQ_HDRS:
        irq += flatten_header(h, emitted, sys_inc)
    if SYS_H:
        sysm = flatten_header(SYS_H, emitted, sys_inc)
    if UMBRELLA_HDR:
        core = flatten_header(UMBRELLA_HDR, emitted, sys_inc)
    for h in MERGED_HDRS:
        mods += flatten_header(h, emitted, sys_inc)

    guard = "__%s_DRIVER_H__" % CHIP.upper()
    lines = [banner("driver.h",
                    "%s 驱动库 - 聚合头文件 (声明/类型/宏) [自动生成, 勿手改]" % UPPER)]
    lines.append("#ifndef " + guard)
    lines.append("#define " + guard)
    lines.append("")
    lines += config_block().split("\n")
    if PROF.get("device_defines"):
        lines += section("器件型号宏 (厂商器件头靠它选型, 必须最先定义)")
        for d in PROF["device_defines"]:
            lines.append("#define %s" % d)
        lines.append("")
    lines += section("系统头")
    for s in sys_inc:
        lines.append("#include <%s>" % s)
    if SYNTHETIC_HEADERS:
        lines += section("合成配置头 (替代原包里逐例程不同的那份, 必须最靠前)")
        for nm, txt in SYNTHETIC_HEADERS.items():
            lines.append("/* >>> generated in place of %s */" % nm)
            lines += txt.split("\n")
            lines.append("/* <<< end of %s */" % nm)
    if base:
        lines += section("基础类型 (%s)" % BASE_HDR)
        lines += base
    lines += section("CMSIS 内核配置 + 中断号 "
                     "(%s 前置段, 必须早于内核核心头)" % DEVICE_H)
    lines += dev_head
    lines += section("器件寄存器 / 位定义 / 外设基址 (%s)" % DEVICE_H)
    lines += dev_rest
    lines += section("C 链接区: 以下全部为 C 符号, 供 C / C++ 共用")
    lines.append("#ifdef __cplusplus")
    lines.append('extern "C" {')
    lines.append("#endif")
    if core:
        lines += section("驱动核心 (%s)" % UMBRELLA_HDR)
        lines += core
    lines += section("驱动模块 (%s, %d 个)" % (PROF["module_hdr_dir"], len(MERGED_HDRS)))
    lines += mods
    if irq:
        lines += section("中断分发框架 (%s)" % ", ".join(IRQ_HDRS))
        lines += irq
    if IRQ_STYLE == "ddl":
        lines += section("中断入口与回调声明 (原厂头文件遗漏, 必须补 C 链接声明)")
        lines.append("/*")
        lines.append(" * %s 只声明了 EnableNvic(), 下面这些全部没有声明." % IRQ_SRCS[0])
        lines.append(" * 单独编译成 .o 时它们是 C 符号; 但合并进 driver.cpp 后用 C++ 编译,")
        lines.append(" * 会得到 _Z... 修饰名, 向量表引用的 C 符号名再也匹配不上, 实测后果是")
        lines.append(" * 向量表全部落回 startup.s 的 Default_Handler, 中断彻底失效.")
        lines.append(" *")
        lines.append(" * 另: 回调若未实现, 由 driver.cpp 末尾的弱空定义兜底, 不会跳地址 0.")
        lines.append(" */")
        weak_cbs, handlers = extract_irq_symbols()
        lines.append("/* 中断回调: 应用层实现同名强符号即可覆盖; "
                     "未实现时用 driver.cpp 的弱空定义 (%d 个) */" % len(weak_cbs))
        for n in weak_cbs:
            # 注意: 这里必须发非 __WEAK 声明. 若声明带 weak 属性, 应用层在同一 TU
            # 里的定义会被传染成弱符号, 与 driver.cpp 的弱定义冲突 -> 链接器任选其一,
            # 覆盖失效 (实测中断仍落到空实现).
            lines.append("void %s(void);" % n)
        lines.append("")
        lines.append("/* 向量表中断入口: driver 提供强定义, 覆盖 startup.s 的弱默认 (%d 个) */"
                     % len(handlers))
        for n in handlers:
            lines.append("void %s(void);" % n)
    if sysm:
        lines += section("系统时钟声明 (%s)" % SYS_H)
        lines += sysm
    if MISSING_DECLS:
        lines += section("原厂遗漏声明的补全")
        lines.append("/*")
        lines.append(" * 以下符号在源码中有定义, 但原厂头文件从未声明; 若不补声明,")
        lines.append(" * 聚合到 .cpp 用 C++ 编译后会变成 _Z... 修饰名, 与其它 TU 的")
        lines.append(" * C 符号引用不匹配 (实现见 config.cpp 的另有说明).")
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
                    "%s 驱动库 - 聚合实现 [自动生成, 勿手改]" % UPPER)]
    lines.append('#include "driver.h"')
    lines.append("")
    lines.append("/* 厂商 C 代码惯用 `volatile 变量--` (超时计数), C++20 起被标记 deprecated.")
    lines.append(" * 语义无误, 仅在生成本 TU 内屏蔽该告警, 不影响用户代码. */")
    lines.append("#if defined(__clang__)")
    lines.append('#  pragma clang diagnostic ignored "-Wdeprecated-volatile"')
    lines.append("#endif")
    # 伞形实现 (ddl.c / hc32_ll.c) 放最前, 其余按名字排序
    umbrella_c = (UMBRELLA_HDR or "").replace(".h", ".c")
    order = ([umbrella_c] if umbrella_c in MERGED_SRCS else []) + \
            [s for s in MERGED_SRCS if s != umbrella_c]
    for s in order:
        lines += section(s)
        lines += flatten_source(s, SRC_SRC[s])
    for s in MCU_SRCS:
        lines += section("%s (%s)" % (s, os.path.relpath(SRC_SRC[s], DLL)))
        lines += flatten_source(s, SRC_SRC[s])

    # ---- 中断回调弱定义 (空实现) --------------------------------------------
    # 仅 DDL 风格需要: 原厂只在 interrupts_<chip>.c 里对这批回调做了 __WEAK
    # *声明* (没有定义), 而入口处理函数 (SysTick_Handler / PORTA_IRQHandler ...)
    # 会调用它们. 只声明未定义 => "弱未定义符号": 实测 LLD 会把 bl 退化成相对
    # 偏移 0 (空操作), 但这依赖链接器行为, 换链接器/换优化级别可能变成跳地址 0
    # -> HardFault. 这里补 __WEAK 空定义: 符号有定义, 调用行为确定;
    # 应用层写同名强定义即可覆盖.
    # (LL 风格的中断处理函数在原厂 .c 里就是强定义, 不存在这个问题.)
    if IRQ_STYLE == "ddl":
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
    print("chip       = %s   (包: %s)" % (CHIP, os.path.basename(DLL)))
    print("布局       = %s" % ("LL 驱动" if IRQ_STYLE == "ll" else "DDL 驱动"))
    print("driver.h   lines=%d  -> %s" % (h.count("\n"), OUT_H))
    print("driver.cpp lines=%d  -> %s" % (c.count("\n"), OUT_C))
    print("模块       = %d 头 / %d 源 + 中断 %s"
          % (len(MERGED_HDRS), len(MERGED_SRCS), ", ".join(MCU_SRCS)))
    if EXCLUDED_SRCS:
        print("排除源     = %s" % ", ".join(EXCLUDED_SRCS))
    if SYNTHETIC_HEADERS:
        print("合成头     = %s" % ", ".join(SYNTHETIC_HEADERS))
    print("未纳入 (机制层): hal/%s/config.h, hal/%s/config.cpp" % (CHIP, CHIP))
    print("未纳入 (策略层, app 侧): app/<proj>/inc/board_config.h  <- 改板级参数改这里")
    if SYS_C:
        print("  其中 %s 未进入 driver.cpp (时钟初始化, 见 config.cpp)" % SYS_C)
    if warnings:
        print("\nWARNINGS (%d):" % len(warnings))
        for w in warnings:
            print("  " + w)
    return 0


if __name__ == "__main__":
    sys.exit(main())
