/*
 * -----------------------------------------------------------------------------
 *  GNU LD linker script for XHSC HC32A052 (ARM Cortex-M0+)
 * -----------------------------------------------------------------------------
 *  本脚本根据官方 IAR (.icf) / MDK (.uvprojx) 配置转换而来，
 *  仅面向 ATfE (Arm Toolchain for Embedded) 工具链:
 *    - 编译器: clang --target=arm-none-eabi (LLVM integrated assembler)
 *    - C 库:   picolibc
 *    - 链接器: ld.lld / GNU ld
 *
 *  配套启动文件: startup.s (与本脚本位于同一目录, 仅用于 ATfE)
 *  链接时请使用 -nostartfiles, 由该启动文件负责 .data 拷贝与 .bss 清零。
 *
 *  内存映射 (数据来源: temp/HC32A052_Template_Rev1.0.0/example/EWARM/<variant>/config
 *                     下的 .icf 文件, 与 mcu/common/hc32a052.h):
 *    Flash: 0x00000000
 *    RAM  : 0x20000000
 *
 *  各型号 Flash / RAM 容量:
 *    +---------------------+---------+--------+
 *    | Device              | Flash   | RAM    |
 *    +---------------------+---------+--------+
 *    | HC32A052J8xA / F8xA |  64 KB  |  16 KB |
 *    | HC32A052JAxA / FAxA | 128 KB  |  16 KB |
 *    +---------------------+---------+--------+
 *  即型号第 3 个字母为 "8" => 64KB Flash, "A" => 128KB Flash。
 *  RAM 全部为 16KB (0x20000000 ~ 0x20003FFF)。
 *
 *  默认配置: 128KB Flash / 16KB RAM (FA / JA 型号)。
 *  若使用 64KB 型号, 请把下面 FLASH 的 LENGTH 改为 64K。
 * -----------------------------------------------------------------------------
 */

/* 入口: 复位处理函数 (由启动文件导出) */
ENTRY(Reset_Handler)

/* ---------------------------------------------------------------------------
 * 用户可调参数
 * ------------------------------------------------------------------------- */

/* 链接期堆/栈最小保留量, 用于在 RAM 不足时通过链接错误提前暴露问题 */
_Min_Heap_Size  = 0x00000200;   /* 512 Byte (官方 HEAP 默认值) */
_Min_Stack_Size = 0x00000400;   /* 1 KB  (官方 CSTACK 默认 0x200, 此处略放大更安全) */

/* picolibc 的 crt0 / malloc 使用 __stack_size 与 __stack */
__stack_size = _Min_Stack_Size;

/* ---------------------------------------------------------------------------
 * 内存区域定义
 * ------------------------------------------------------------------------- */
MEMORY
{
  /* 型号 FA/JA 用 128K; 型号 F8/J8 请改为 64K */
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 128K
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 16K
}

/* 栈顶 (满递减栈), 位于 RAM 最高地址 (picolibc 约定: __stack) */
__stack = ORIGIN(RAM) + LENGTH(RAM);

/* ---------------------------------------------------------------------------
 * 段分配
 * ------------------------------------------------------------------------- */
SECTIONS
{
  /* ---- 中断向量表: 必须位于 Flash 起始地址 0x00000000 ---- */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  /* ---- 代码 ---- */
  .text :
  {
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
  } >FLASH

  /* ---- 只读数据 ---- */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* ---- ARM 异常处理表 (Cortex-M0+ 用于展开/回溯) ---- */
  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  /* ---- C 运行时初始化数组 ---- */
  .preinit_array :
  {
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array*))
    PROVIDE_HIDDEN(__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN(__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    PROVIDE_HIDDEN(__fini_array_end = .);
  } >FLASH

  /* ---- 已初始化数据 ----
   * 运行地址(VMA)在 RAM, 加载地址(LMA)紧跟只读数据之后, 位于 Flash。
   * 启动代码从 __data_source(= Flash LMA) 拷贝到 __data_start .. __data_end。 */
  .data :
  {
    . = ALIGN(4);
    __data_start = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
  } >RAM AT> FLASH

  /* ---- TLS 已初始化数据 (.tdata) ----------------------------------------
   * C++ 的 thread_local、以及 libc 的 errno 都存放在 TLS 区。
   * picolibc 的 __aeabi_read_tp() 实现为 "返回 *(void**)&__tls",
   * 而 __tls 由 _set_tls(__tls_base) 在启动时写入; 若从不调用 _set_tls,
   * __tls 恒为 0, 于是 errno 会被写到地址 0 (Flash) => HardFault。
   *
   * 关键布局约束: .tdata 必须紧接 .data, 且在 RAM 与 Flash 中都连续,
   * 这样启动代码一次拷贝(__data_size 字节)即可同时完成 .data 和 .tdata。 */
  .tdata : ALIGN(__tls_align)
  {
    __tdata_start = .;
    *(.tdata .tdata.* .gnu.linkonce.td.*)
    . = ALIGN(4);
    __tdata_end = .;
  } >RAM AT> FLASH

  __data_end = .;                     /* .data + .tdata 的 RAM 结束地址 */
  __tdata_source = LOADADDR(.tdata);  /* .tdata 的 Flash 加载地址 */

  /* picolibc 约定: .data(含 .tdata) 的加载地址与大小 */
  __data_source = LOADADDR(.data);
  __data_size   = __data_end - __data_start;
  __tdata_size  = __tdata_end - __tdata_start;

  /* ---- TLS 未初始化数据 (.tbss) -----------------------------------------
   * 必须紧接在 .bss 之前, 并把 __bss_start 指向 .tbss 起址,
   * 这样启动代码的清零循环会一次性清掉 .tbss + .bss。 */
  .tbss (NOLOAD) :
  {
    . = ALIGN(__tls_align);
    __tbss_start = .;
    *(.tbss .tbss.* .gnu.linkonce.tb.*)
    *(.tcommon)
    . = ALIGN(4);
    __tbss_end = .;
  } >RAM

  /* ---- 未初始化数据 (上电清零, 范围含 .tbss) ---- */
  .bss :
  {
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } >RAM

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
  {
    . = ALIGN(4);
    __noinit_start = .;
    *(.noinit)
    *(.noinit*)
    . = ALIGN(4);
    __noinit_end = .;
  } >RAM

  /* ---- 堆栈保留区 --------------------------------------------------------
   * 该段不占用 Flash, 仅推进 RAM 定位计数器; 一旦 RAM 容不下
   * (bss + _Min_Heap_Size + _Min_Stack_Size) 就会触发链接错误。
   * 同时在此导出 picolibc 的堆起始符号。 */
  ._user_heap_stack (NOLOAD) :
  {
    . = ALIGN(8);
    __heap_start = .;
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* picolibc malloc 使用的堆边界: 堆自 bss 末尾向上生长, 到栈底为止 */
  __heap_end  = __stack - __stack_size;
  __heap_size = __heap_end - __heap_start;

  /* ---- ARM 属性段 ---- */
  .ARM.attributes 0 : { *(.ARM.attributes) }
}
