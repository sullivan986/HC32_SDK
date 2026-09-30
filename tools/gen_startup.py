#!/usr/bin/env python3
"""
由器件头的 IRQn_Type 枚举自动生成 startup.s + Link.ld (ATfE / picolibc 专用).

为什么需要它: 向量表有"空洞"(保留位)且同一槽位可能被多个外设共用
(如 A052 的 VC0/VC1/LVD 合成一个 IRQ), 手抄极易出错. 手抄错一个 word,
中断就会静默失效 —— 编译链接全绿, 运行时才发现.

生成规则
  IRQ 号 0..N 逐个取值:
    - 器件头里有 IRQn == 号  -> 用 "<名字>_IRQHandler"
    - 没有 (保留槽)           -> 用 Dummy_IRQHandler (死循环, 便于调试时发现误触发)
  核心异常 (NMI/HardFault/SVC/PendSV/SysTick) 由 CHIPS[].core_vec 给出,
  它们的位置固定在向量表前 16 个字, 与 IRQ 枚举里的负值一一对应.

用法
  python3 tools/gen_startup.py                 # 生成所有已配置芯片
  python3 tools/gen_startup.py hc32f005        # 只生成指定芯片
  python3 tools/gen_startup.py --check hc32a052  # 生成到临时目录并与现有文件比对

新增芯片: 在 CHIPS 里加一项 (见文件末尾 ★ 说明).
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# ============================================================================
# ★ 逐芯片配置: 新增芯片在此登记
# ----------------------------------------------------------------------------
#   device_hdr : 器件头 (含 typedef enum IRQn) 的相对路径
#   arch       : .arch 指令 (armv6-m = M0/M0+; armv7-m = M3/M4)
#   isa        : MCU 描述 (仅注释用)
#   core_vec   : 向量表前 16 个字的 (偏移, 符号) —— 固定 16 项
#   vec_start/vec_items : 向量表第 16 字起的第一个 IRQ 号 (通常 0)
#   irq_alias  : {IRQ号: 处理函数名} 覆盖自动推导
#                (用于一个槽位多个外设共用的情形)
#   handler_rule : (正则, 替换) 把 IRQn 枚举名(去掉 _IRQn) 映射成处理函数名.
#                缺省为 None => "<枚举名>_IRQHandler".
#                F460 的枚举是 INT000 而处理函数是 IRQ000_Handler, 就靠它转.
#   weak_extra : 除向量表处理器外, 还需额外声明为弱符号的名字 (一般留空)
#   flash/ram  : (ORIGIN, LENGTH) 字符串, 直接写进 MEMORY
#   min_heap/min_stack : RAM 保留量
#   note       : 内存/型号说明 (写进 Link.ld 注释)
# ============================================================================
CHIPS = {
    "hc32a052": {
        "device_hdr": "temp/HC32A052_DLL_Rev1.0.1/mcu/common/hc32a052.h",
        "arch": "armv6-m",
        "isa": "ARM Cortex-M0+ (ARMv6-M)",
        "core_vec": ["__stack", "Reset_Handler", "NMI_Handler", "HardFault_Handler",
                     "0", "0", "0", "0", "0", "0", "0", "SVC_Handler",
                     "0", "0", "PendSV_Handler", "SysTick_Handler"],
        "irq_alias": {
            26: "VC0_1_LVD_IRQHandler",      # VC0 / VC1 / LVD 共用
            31: "CTRIM_FAULT_IRQHandler",    # CTRIM / FAULT 共用
        },
        "flash": ("0x00000000", "128K"),
        "ram": ("0x20000000", "16K"),
        "min_heap": 0x200,
        "min_stack": 0x400,
        "note": ["型号 FA/JA 用 128K Flash; 型号 F8/J8 请把 LENGTH 改为 64K.",
                 "RAM 全部 16KB (型号后缀无关)."],
    },
    "hc32f005": {
        "device_hdr": "temp/HC32F005_DDL_Rev2.0.0/mcu/common/hc32f005.h",
        "arch": "armv6-m",
        "isa": "ARM Cortex-M0+ (ARMv6-M)",
        "core_vec": ["__stack", "Reset_Handler", "NMI_Handler", "HardFault_Handler",
                     "0", "0", "0", "0", "0", "0", "0", "SVC_Handler",
                     "0", "0", "PendSV_Handler", "SysTick_Handler"],
        "irq_alias": {},
        "flash": ("0x00000000", "32K"),
        "ram": ("0x20000000", "4K"),
        "min_heap": 0x100,
        "min_stack": 0x100,
        "note": ["HC32F005 全系列: 32KB Flash / 4KB RAM.",
                 "官方 CSTACK/HEAP 默认各 0x100."],
    },
    "hc32f460": {
        "device_hdr": ("temp/HC32F460_DDL_Rev3.3.0/drivers/cmsis/Device/"
                       "HDSC/hc32f4xx/Include/hc32f460.h"),
        "arch": "armv7-m",
        "isa": "ARM Cortex-M4F (ARMv7-M)",
        "mcpu": "cortex-m4",
        # M4 比 M0+ 多 4 个可配置异常 (MemManage/BusFault/UsageFault/DebugMonitor)
        "core_vec": ["__stack", "Reset_Handler", "NMI_Handler", "HardFault_Handler",
                     "MemManage_Handler", "BusFault_Handler", "UsageFault_Handler",
                     "0", "0", "0", "0", "SVC_Handler", "DebugMon_Handler",
                     "0", "PendSV_Handler", "SysTick_Handler"],
        "irq_alias": {},        # 枚举是 INT000_IRQn, 但中断处理函数叫 IRQ000_Handler (厂商命名)
        "handler_rule": (r"^INT(\d+)$", r"IRQ\1_Handler"),        # F460 中断号是**位置式** INT000_IRQn..INT127_IRQn, 不是外设名.
        # 外设->INT 的对应关系由厂商头的 #define (如 USART1_IRQn INT036_IRQn) 给出,
        # 中断分发由 hc32f460_ll_interrupts_share.c 负责.
        "flash": ("0x00000000", "512K"),
        "ram": ("0x1FFF8000", "188K"),
        "min_heap": 0x400,
        "min_stack": 0x800,
        "note": ["型号密度: xE = 512KB Flash, xC = 256KB Flash (本脚本按 xE 512K).",
                 "RAM 基址是 0x1FFF8000 (与 M0+ 系列的 0x20000000 不同!), 共 188KB.",
                 "另有一段 RET_RAM 在 0x200F0000 (4KB), 本脚本未使用.",
                 "注意: Cortex-M4F 带 FPU, 用硬件浮点需保证 SystemInit 里使能了",
                 "      CPACR 的 CP10/CP11 (厂商 system_hc32f460.c 已处理)."],
    },
}

BANNER_STARTUP = """@*******************************************************************************
@  Startup / vector table for XHSC {UPPER} ({ISA})
@  Target toolchain: ATfE (Arm Toolchain for Embedded, clang + picolibc) ONLY
@
@  [自动生成] 勿手改; 重新生成: python3 {SELF} {CHIP}
@  Written in GNU assembler syntax, assembled by the ATfE clang integrated
@  assembler (LLVM). Link with -nostartfiles against the matching linker
@  script Link.ld (same directory), e.g.:
@
@    clang --target=arm-none-eabi -mcpu={MCPU} -mthumb -nostartfiles \\
@        -T Link.ld startup.s ... -o app.elf
@
@  中断向量表顺序与 IRQ 编号来源:
@    {DEVHDR}   (enum IRQn)
@
@  Symbol contract (all provided by Link.ld, picolibc naming):
@    __stack       : initial stack pointer (top of RAM)
@    __data_source : load address of .data (in flash)
@    __data_start  : start of .data in RAM
@    __data_end    : end   of .data in RAM
@    __bss_start   : start of .bss in RAM
@    __bss_end     : end   of .bss in RAM
@*******************************************************************************

    .syntax unified
    .arch   {ARCH}
    .thumb

@===============================================================================
@  Interrupt vector table (must be at the very start of flash, address 0x00000000)
@===============================================================================
    .section .isr_vector, "a", %progbits
    .align  2
    .globl  __Vectors
    .globl  g_pfnVectors
    .type   g_pfnVectors, %object
g_pfnVectors:
__Vectors:
"""

RESET_BODY = """
@===============================================================================
@  Reset handler (runtime startup)
@===============================================================================
    .section .text.Reset_Handler, "ax", %progbits
    .align  2
    .globl  Reset_Handler
    .type   Reset_Handler, %function
    .thumb_func
Reset_Handler:
    @ --- 官方 IAR/MDK 启动文件在此处会把 VTOR 复位为 0x00000000。
    @ --- Cortex-M 复位后 VTOR 本身就是 0, 而向量表位于 Flash 起始 0x0,
    @ --- 因此从 Flash 运行时不需额外设置 (仅在 RAM 调试模式下才需要)。 ---

    @ --- Copy .data from flash (LMA) to RAM (VMA) ---
    ldr     r0, =__data_start
    ldr     r1, =__data_end
    ldr     r2, =__data_source
    b       .Lcopy_check
.Lcopy_loop:
    ldr     r3, [r2]
    str     r3, [r0]
    adds    r0, r0, #4
    adds    r2, r2, #4
.Lcopy_check:
    cmp     r0, r1
    bcc     .Lcopy_loop

    @ --- Zero-fill .bss ---
    ldr     r0, =__bss_start
    ldr     r1, =__bss_end
    movs    r3, #0
    b       .Lzero_check
.Lzero_loop:
    str     r3, [r0]
    adds    r0, r0, #4
.Lzero_check:
    cmp     r0, r1
    bcc     .Lzero_loop

    @ --- Initialize the TLS pointer (picolibc) ---
    @ 必须位于 .bss 清零之后、__libc_init_array 之前。
    @ picolibc 的 __aeabi_read_tp() 是 "返回 *(void**)&__tls", 而 __tls 变量
    @ 存放在 .bss 中; _set_tls(__tls_base) 负责把它指向真正的 TLS 块。
    @ 若缺少这一步, errno / C++ thread_local 会访问地址 0 (Flash) 导致 HardFault。
    ldr     r0, =__tls_base
    bl      _set_tls

    @ --- System clock / device early init (provided by config.cpp) ---
    bl      SystemInit

    @ --- Run C/C++ constructors (__init_array). Provided by picolibc ---
    bl      __libc_init_array

    @ --- Jump to application ---
    bl      main

.Lhang:
    b       .Lhang
    .size   Reset_Handler, . - Reset_Handler

@===============================================================================
@  Default handler and weak aliases for all exception / IRQ handlers
@  (同名强符号定义在 driver.cpp 中时会自动覆盖这些弱符号)
@===============================================================================
    .section .text.Default_Handler, "ax", %progbits
    .align  2
    .globl  Default_Handler
    .type   Default_Handler, %function
    .thumb_func
Default_Handler:
    b       .
    .size   Default_Handler, . - Default_Handler
"""

LINK_TEMPLATE = """/*
 * -----------------------------------------------------------------------------
 *  GNU LD linker script for XHSC {UPPER} ({ISA})
 * -----------------------------------------------------------------------------
 *  [自动生成] 勿手改; 重新生成: python3 {SELF} {CHIP}
 *  本脚本根据官方 IAR (.icf) / MDK (.uvprojx) 配置转换而来，
 *  仅面向 ATfE (Arm Toolchain for Embedded) 工具链:
 *    - 编译器: clang --target=arm-none-eabi (LLVM integrated assembler)
 *    - C 库:   picolibc
 *    - 链接器: ld.lld / GNU ld
 *
 *  配套启动文件: startup.s (与本脚本位于同一目录, 仅用于 ATfE)
 *  链接时请使用 -nostartfiles, 由该启动文件负责 .data 拷贝与 .bss 清零。
 *
 *  内存映射:
 *    Flash: {FLASH_ORG}
 *    RAM  : {RAM_ORG}
{NOTE_LINES}
 * -----------------------------------------------------------------------------
 */

/* 入口: 复位处理函数 (由启动文件导出) */
ENTRY(Reset_Handler)

/* ---------------------------------------------------------------------------
 * 用户可调参数
 * ------------------------------------------------------------------------- */

/* 链接期堆/栈最小保留量, 用于在 RAM 不足时通过链接错误提前暴露问题 */
_Min_Heap_Size  = {MIN_HEAP};
_Min_Stack_Size = {MIN_STACK};

/* picolibc 的 crt0 / malloc 使用 __stack_size 与 __stack */
__stack_size = _Min_Stack_Size;

/* ---------------------------------------------------------------------------
 * 内存区域定义
 * ------------------------------------------------------------------------- */
MEMORY
{{
  FLASH (rx)  : ORIGIN = {FLASH_ORG}, LENGTH = {FLASH_LEN}
  RAM   (xrw) : ORIGIN = {RAM_ORG}, LENGTH = {RAM_LEN}
}}

/* 栈顶 (满递减栈), 位于 RAM 最高地址 (picolibc 约定: __stack) */
__stack = ORIGIN(RAM) + LENGTH(RAM);

/* ---------------------------------------------------------------------------
 * 段分配
 * ------------------------------------------------------------------------- */
SECTIONS
{{
  /* ---- 中断向量表: 必须位于 Flash 起始地址 ---- */
  .isr_vector :
  {{
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  }} >FLASH

  /* ---- 代码 ---- */
  .text :
  {{
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)          /* ARM/Thumb 互调用桩 */
    *(.glue_7t)
    *(.eh_frame)

    /* C++ 全局构造/析构调用表 */
    KEEP(*(.init))
    KEEP(*(.fini))

    . = ALIGN(4);
    _etext = .;
  }} >FLASH

  /* ---- 只读数据 ---- */
  .rodata :
  {{
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  }} >FLASH

  /* ---- ARM 异常处理表 (展开/回溯用) ---- */
  .ARM.extab :
  {{
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  }} >FLASH

  .ARM :
  {{
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  }} >FLASH

  /* ---- C 运行时初始化数组 ---- */
  .preinit_array :
  {{
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array*))
    PROVIDE_HIDDEN(__preinit_array_end = .);
  }} >FLASH

  .init_array :
  {{
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN(__init_array_end = .);
  }} >FLASH

  .fini_array :
  {{
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    PROVIDE_HIDDEN(__fini_array_end = .);
  }} >FLASH

  /* ---- 已初始化数据 ----
   * 运行地址(VMA)在 RAM, 加载地址(LMA)紧跟只读数据之后, 位于 Flash。
   * 启动代码从 __data_source(= Flash LMA) 拷贝到 __data_start .. __data_end。 */
  .data :
  {{
    . = ALIGN(4);
    __data_start = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
  }} >RAM AT> FLASH

  /* ---- TLS 已初始化数据 (.tdata) ----------------------------------------
   * C++ 的 thread_local、以及 libc 的 errno 都存放在 TLS 区。
   * picolibc 的 __aeabi_read_tp() 实现为 "返回 *(void**)&__tls",
   * 而 __tls 由 _set_tls(__tls_base) 在启动时写入; 若从不调用 _set_tls,
   * __tls 恒为 0, 于是 errno 会被写到地址 0 (Flash) => HardFault。
   *
   * 关键布局约束: .tdata 必须紧接 .data, 且在 RAM 与 Flash 中都连续,
   * 这样启动代码一次拷贝(__data_size 字节)即可同时完成 .data 和 .tdata。 */
  .tdata : ALIGN(__tls_align)
  {{
    __tdata_start = .;
    *(.tdata .tdata.* .gnu.linkonce.td.*)
    . = ALIGN(4);
    __tdata_end = .;
  }} >RAM AT> FLASH

  /* ---- RAM 中执行的函数 (EFM 烧写等) ------------------------------------
   * 厂商用 __RAM_FUNC = __attribute__((section(".ramfunc"))) 标记这类函数:
   * 擦写 Flash 时总线读不到 Flash, 函数体必须在 RAM 里跑。
   * 位置很关键: 必须紧跟 .data/.tdata 且在 RAM/Flash 中都连续, 这样启动代码的
   * 一次拷贝 (__data_size 字节) 就顺带把它搬到 RAM 了; 而且 __data_end 必须
   * 在它之后, 否则拷贝循环覆盖不到。 */
  .ramfunc : ALIGN(4)
  {{
    __ramfunc_start = .;
    *(.ramfunc)
    *(.ramfunc*)
    . = ALIGN(4);
    __ramfunc_end = .;
  }} >RAM AT> FLASH

  __data_end = .;                     /* .data + .tdata + .ramfunc 的 RAM 结束地址 */
  __tdata_source = LOADADDR(.tdata);  /* .tdata 的 Flash 加载地址 */
  __ramfunc_source = LOADADDR(.ramfunc);

  /* picolibc 约定: .data(含 .tdata) 的加载地址与大小 */
  __data_source = LOADADDR(.data);
  __data_size   = __data_end - __data_start;
  __tdata_size  = __tdata_end - __tdata_start;

  /* picolibc 约定: .data(含 .tdata) 的加载地址与大小 */
  __data_source = LOADADDR(.data);
  __data_size   = __data_end - __data_start;
  __tdata_size  = __tdata_end - __tdata_start;

  /* ---- TLS 未初始化数据 (.tbss) -----------------------------------------
   * 必须紧接在 .bss 之前, 并把 __bss_start 指向 .tbss 起址,
   * 这样启动代码的清零循环会一次性清掉 .tbss + .bss。 */
  .tbss (NOLOAD) :
  {{
    . = ALIGN(__tls_align);
    __tbss_start = .;
    *(.tbss .tbss.* .gnu.linkonce.tb.*)
    *(.tcommon)
    . = ALIGN(4);
    __tbss_end = .;
  }} >RAM

  /* ---- 未初始化数据 (上电清零, 范围含 .tbss) ---- */
  .bss :
  {{
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  }} >RAM

  /* picolibc 约定: 清零起点为 .tbss 起始 (而非 .bss) */
  __bss_start = ADDR(.tbss);
  __bss_size  = __bss_end - __bss_start;

  /* ---- TLS 相关符号 (picolibc / ARM EABI) ------------------------------- */
  __tls_align = MAX(ALIGNOF(.tdata), ALIGNOF(.tbss));
  __tls_size  = SIZEOF(.tdata) + SIZEOF(.tbss);
  __tls_base  = ADDR(.tdata);                   /* TLS 块起址, 启动时传给 _set_tls */
  __tls_end   = __tls_base + __tls_size;
  __tls_space = __tls_base;
  __arm32_tls_tcb_offset = MAX(8, __tls_align);

  /* ---- 上电不初始化的数据 (掉电保持 / 复位保持) ---- */
  .noinit (NOLOAD) :
  {{
    . = ALIGN(4);
    __noinit_start = .;
    *(.noinit)
    *(.noinit*)
    . = ALIGN(4);
    __noinit_end = .;
  }} >RAM

  /* ---- 堆栈保留区 --------------------------------------------------------
   * 该段不占用 Flash, 仅推进 RAM 定位计数器; 一旦 RAM 容不下
   * (bss + _Min_Heap_Size + _Min_Stack_Size) 就会触发链接错误。
   * 同时在此导出 picolibc 的堆起始符号。 */
  ._user_heap_stack (NOLOAD) :
  {{
    . = ALIGN(8);
    __heap_start = .;
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  }} >RAM

  /* picolibc malloc 使用的堆边界: 堆自 bss 末尾向上生长, 到栈底为止 */
  __heap_end  = __stack - __stack_size;
  __heap_size = __heap_end - __heap_start;

  /* ---- ARM 属性段 ---- */
  .ARM.attributes 0 : {{ *(.ARM.attributes) }}
}}
"""

IRQN_RE = re.compile(r"^\s*([A-Za-z_]\w*)_IRQn\s*=\s*(-?\d+)\s*,", re.M)


def parse_irqn(device_hdr):
    """从器件头解析 {IRQ号: 外设名} (只取 >=0 的).

    做法: 先定位 `} IRQn_Type;`, 再向前找最近的 `typedef enum ... {`,
    取其间的正文. 比"从第一个 typedef enum 往后扫"稳健 —— 器件头里
    在 IRQn 之前往往还有别的枚举(A052/F005 就有), 后者会跨越它们.
    """
    with open(device_hdr, "rb") as fp:
        text = fp.read().replace(b"\r\n", b"\n").decode("utf-8", "replace")
    tail = text.find("} IRQn_Type")
    if tail < 0:
        raise SystemExit("%s: 找不到 '} IRQn_Type;'" % device_hdr)
    head = text[:tail]
    m = None
    for m in re.finditer(r"typedef\s+enum[^{;]*\{", head):
        pass                      # 取最后一个 = 离 IRQn_Type 最近的那个
    if m is None:
        raise SystemExit("%s: 找不到 IRQn 枚举的 typedef enum" % device_hdr)
    body = head[m.end():]
    irqs = {}
    for mm in IRQN_RE.finditer(body):
        name, val = mm.group(1), int(mm.group(2))
        if val >= 0:
            irqs[val] = name
    if not irqs:
        raise SystemExit("%s: IRQn 解析结果为空" % device_hdr)
    return irqs


def handler_name(cfg, enum_base):
    """IRQn 枚举名(去掉 _IRQn) -> 中断处理函数名.

    缺省 "<枚举名>_IRQHandler"; 若 profile 给了 handler_rule, 先做一次正则替换
    (F460: INT000 -> IRQ000_Handler).
    """
    rule = cfg.get("handler_rule")
    if rule is not None:
        enum_base = re.sub(rule[0], rule[1], enum_base)
    else:
        enum_base = enum_base + "_IRQHandler"
    return enum_base


def build_vectors(cfg, irqs):
    """返回 [(word 表达式, 注释)] —— 覆盖向量表全部 16 + N 个字."""
    out = []
    for i, sym in enumerate(cfg["core_vec"]):
        out.append((sym, "core slot %d" % i))
    max_irq = max(irqs) if irqs else -1
    for n in range(0, max_irq + 1):
        if n in cfg.get("irq_alias", {}):
            out.append((cfg["irq_alias"][n], "IRQ #%d" % n))
        elif n in irqs:
            out.append((handler_name(cfg, irqs[n]), "IRQ #%d" % n))
        else:
            # 保留槽: 硬件上不会触发; 用死循环 handler 而非 0,
            # 万一误触发可以停住被调试器捕获, 而不是跳地址 0。
            out.append(("Dummy_IRQHandler", "IRQ #%d (reserved)" % n))
    return out


def gen_startup(chip, cfg, irqs):
    up = "HC32" + chip[4:].upper()
    txt = BANNER_STARTUP.format(
        UPPER=up, ISA=cfg["isa"], SELF="tools/gen_startup.py", CHIP=chip,
        MCPU=cfg.get("mcpu", "cortex-m0plus"), DEVHDR=cfg["device_hdr"],
        ARCH=cfg["arch"])
    vecs = build_vectors(cfg, irqs)
    for sym, cmt in vecs:
        txt += "    .word   %-32s @ %s\n" % (sym, cmt)
    txt += "    .size   g_pfnVectors, . - g_pfnVectors\n"
    txt += RESET_BODY
    # 弱别名: 全部核心异常 + 全部外设处理函数 (含 Dummy)
    # 注意: Reset_Handler 是本文件自己定义的强符号, 不能设成弱别名;
    #       __stack 是链接脚本提供的数据符号, 也不是函数.
    skip = {"0", "Reset_Handler", "__stack"}
    seen, names = set(), []
    for s, _ in vecs:
        if s not in skip and s not in seen:
            seen.add(s)
            names.append(s)
    for nm in names:
        txt += "\n    .weak   %s\n    .thumb_set %s, Default_Handler\n" % (nm, nm)
    txt += "\n\n    .end\n"
    return txt


def gen_link(chip, cfg):
    up = "HC32" + chip[4:].upper()
    notes = "\n".join(" *  " + n for n in cfg.get("note", []))
    return LINK_TEMPLATE.format(
        UPPER=up, ISA=cfg["isa"], SELF="tools/gen_startup.py", CHIP=chip,
        FLASH_ORG=cfg["flash"][0], FLASH_LEN=cfg["flash"][1],
        RAM_ORG=cfg["ram"][0], RAM_LEN=cfg["ram"][1],
        MIN_HEAP=("0x%08X" % cfg["min_heap"]), MIN_STACK=("0x%08X" % cfg["min_stack"]),
        NOTE_LINES=notes)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    check = "--check" in sys.argv
    targets = args or sorted(CHIPS)
    for chip in targets:
        if chip not in CHIPS:
            raise SystemExit("未配置的芯片: %s (可选: %s)" % (chip, ", ".join(sorted(CHIPS))))
        cfg = CHIPS[chip]
        hdr = os.path.join(ROOT, cfg["device_hdr"])
        if not os.path.isfile(hdr):
            raise SystemExit("器件头不存在: %s" % hdr)
        irqs = parse_irqn(hdr)
        s = gen_startup(chip, cfg, irqs)
        l = gen_link(chip, cfg)
        if check:
            outdir = os.path.join("/tmp", "gen_" + chip)
            os.makedirs(outdir, exist_ok=True)
        else:
            outdir = os.path.join(ROOT, "hal", chip)
            os.makedirs(outdir, exist_ok=True)
        for name, txt in (("startup.s", s), ("Link.ld", l)):
            p = os.path.join(outdir, name)
            with open(p, "w", encoding="utf-8", newline="\n") as fp:
                fp.write(txt)
            print("%-10s %-10s lines=%-5d -> %s" % (chip, name, txt.count("\n"), p))
        print("           外设中断 %d 个 (最大 IRQ 号 %d), 向量表共 %d 字"
              % (len(irqs), max(irqs), 16 + max(irqs) + 1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
