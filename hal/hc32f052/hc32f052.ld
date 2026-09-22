/*
 * -----------------------------------------------------------------------------
 *  GNU LD linker script for XHSC HC32F052 (ARM Cortex-M0+)
 * -----------------------------------------------------------------------------
 *  本脚本根据官方 IAR (.icf) / MDK (.uvprojx, .pack/pdsc) 配置转换而来，
 *  同时适用于:
 *    - arm-none-eabi-gcc  + newlib   (GNU ld)
 *    - ATfE clang (arm-none-eabi) + picolibc (GNU ld / ld.lld)
 *  脚本同时导出 newlib 与 picolibc 两套运行时符号 (见文件末尾的别名)。
 *
 *  配套启动文件: startup_hc32f052_gcc.s (GNU 汇编, 两个工具链通用)。
 *  链接时请使用 -nostartfiles, 由该启动文件负责 .data 拷贝与 .bss 清零。
 *
 *  内存映射 (数据来源: temp/IAR_IDE/config/linker/XHSC/*.icf 与 MDK pack pdsc):
 *    Flash: 0x00000000
 *    RAM  : 0x20000000
 *
 *  各型号 Flash / RAM 容量:
 *    +---------------------+---------+--------+
 *    | Device              | Flash   | RAM    |
 *    +---------------------+---------+--------+
 *    | HC32F052J8xA / F8xA |  64 KB  |  16 KB |
 *    | HC32F052JAxA / FAxA | 128 KB  |  16 KB |
 *    +---------------------+---------+--------+
 *  即型号第 3 个字母为 "8" => 64KB Flash, "A" => 128KB Flash。
 *  RAM 全部为 16KB。
 *
 *  默认配置: 128KB Flash / 16KB RAM (FA / JA 型号)。
 *  若使用 64KB 型号, 请把下面 FLASH 的 LENGTH 改为 64K。
 * -----------------------------------------------------------------------------
 */

/* 入口: 复位处理函数 (需由启动文件导出) */
ENTRY(Reset_Handler)

/* ---------------------------------------------------------------------------
 * 用户可调参数
 * ------------------------------------------------------------------------- */

/* 链接期堆/栈最小保留量, 用于在 RAM 不足时通过链接错误提前暴露问题 */
_Min_Heap_Size  = 0x00000200;   /* 512 Byte (官方 HEAP 默认值) */
_Min_Stack_Size = 0x00000400;   /* 1 KB  (官方 CSTACK 默认 0x200, 此处略放大更安全) */

/* picolibc(ATfE) 兼容: 其 crt0 / malloc 会使用 __stack_size */
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

/* 栈顶 (满递减栈), 位于 RAM 最高地址 */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* ---------------------------------------------------------------------------
 * 段分配
 * ------------------------------------------------------------------------- */
SECTIONS
{
  /* ---- 中断向量表: 必须位于 Flash 起始地址 0x00000000 ----
   * 注: .isr_vector 为 GCC/CMSIS 约定名, 需与启动文件中的段名一致。 */
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
   * 启动代码需从 _sidata(= Flash LMA) 拷贝到 _sdata .. _edata。 */
  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    __data_start__ = _sdata;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
    __data_end__ = _edata;
  } >RAM AT> FLASH

  /* ---- 未初始化数据 (上电清零) ---- */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  /* ---- 上电不初始化的数据 (掉电保持 / 复位保持) ---- */
  .noinit (NOLOAD) :
  {
    . = ALIGN(4);
    _snoinit = .;
    *(.noinit)
    *(.noinit*)
    . = ALIGN(4);
    _enoinit = .;
  } >RAM

  /* ---- 堆栈保留区: 检查 RAM 是否足够 ---- */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* ---- picolibc / ATfE 兼容别名 -----------------------------------------
   * picolibc 的 crt0 使用 __data_start/__data_source/__data_size 拷贝 .data,
   * 使用 __bss_start/__bss_size 清零 .bss; malloc 使用 __heap_start/__heap_end。
   * 这里以 newlib 符号为基准提供别名, 使同一脚本对 GCC(newlib) 与
   * ATfE(picolibc) 都可用 (使用 PROVIDE, 不会覆盖显式定义)。 */
  PROVIDE(__data_start   = _sdata);
  PROVIDE(__data_source  = _sidata);
  PROVIDE(__data_size    = _edata - _sdata);

  PROVIDE(__bss_start    = _sbss);
  PROVIDE(__bss_end      = _ebss);
  PROVIDE(__bss_size     = _ebss - _sbss);

  PROVIDE(__stack        = _estack);
  PROVIDE(__heap_start   = _end);
  PROVIDE(__heap_end     = _estack - __stack_size);
  PROVIDE(__heap_size    = __heap_end - __heap_start);

  /* ---- ARM 属性段 ---- */
  .ARM.attributes 0 : { *(.ARM.attributes) }
}
