@*******************************************************************************
@  Startup / vector table for XHSC HC32A052 (ARM Cortex-M0+, ARMv6-M)
@  Target toolchain: ATfE (Arm Toolchain for Embedded, clang + picolibc) ONLY
@
@  Written in GNU assembler syntax, assembled by the ATfE clang integrated
@  assembler (LLVM). Link with -nostartfiles against the matching linker
@  script Link.ld (same directory), e.g.:
@
@    clang --target=arm-none-eabi -mcpu=cortex-m0plus -mthumb -nostartfiles \
@        -T Link.ld startup.s ... -o app.elf
@
@  中断向量表顺序与 IRQ 编号来源:
@    temp/HC32A052_Template_Rev1.0.0/example/MDK/startup_hc32a052.s
@    temp/HC32A052_Template_Rev1.0.0/example/EWARM/*/startup_hc32a052.s
@    temp/HC32A052_DLL_Rev1.0.1/mcu/common/hc32a052.h  (enum IRQn)
@  与 HC32F052 的向量表布局完全一致 (32 个外设中断)。
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
    .arch   armv6-m
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
    .word   __stack                     @ 0x00  Top of Stack
    .word   Reset_Handler               @ 0x04  Reset
    .word   NMI_Handler                 @ 0x08  NMI
    .word   HardFault_Handler           @ 0x0C  Hard Fault
    .word   0                           @ 0x10  Reserved
    .word   0                           @ 0x14  Reserved
    .word   0                           @ 0x18  Reserved
    .word   0                           @ 0x1C  Reserved
    .word   0                           @ 0x20  Reserved
    .word   0                           @ 0x24  Reserved
    .word   0                           @ 0x28  Reserved
    .word   SVC_Handler                 @ 0x2C  SVCall
    .word   0                           @ 0x30  Reserved
    .word   0                           @ 0x34  Reserved
    .word   PendSV_Handler              @ 0x38  PendSV
    .word   SysTick_Handler             @ 0x3C  SysTick

    .word   PORTA_IRQHandler            @ IRQ #0
    .word   PORTB_IRQHandler            @ IRQ #1
    .word   PORTC_IRQHandler            @ IRQ #2
    .word   PORTD_IRQHandler            @ IRQ #3
    .word   DMAC_IRQHandler             @ IRQ #4
    .word   ATIM3_IRQHandler            @ IRQ #5
    .word   USART0_IRQHandler           @ IRQ #6
    .word   USART1_IRQHandler           @ IRQ #7
    .word   LPUART0_IRQHandler          @ IRQ #8
    .word   LPUART1_IRQHandler          @ IRQ #9
    .word   SPI0_IRQHandler             @ IRQ #10
    .word   SPI1_IRQHandler             @ IRQ #11
    .word   I2C0_IRQHandler             @ IRQ #12
    .word   I2C1_IRQHandler             @ IRQ #13
    .word   ATIM0_IRQHandler            @ IRQ #14
    .word   ATIM1_IRQHandler            @ IRQ #15
    .word   ATIM2_IRQHandler            @ IRQ #16
    .word   LPTIM_IRQHandler            @ IRQ #17
    .word   GTIM0_BTIM0_1_2_IRQHandler  @ IRQ #18
    .word   GTIM1_BTIM3_4_5_IRQHandler  @ IRQ #19
    .word   I2CSLV_IRQHandler           @ IRQ #20
    .word   WWDT_IRQHandler             @ IRQ #21
    .word   IWDT_IRQHandler             @ IRQ #22
    .word   RTC_IRQHandler              @ IRQ #23
    .word   ADC_IRQHandler              @ IRQ #24
    .word   Dummy_IRQHandler            @ IRQ #25
    .word   VC0_1_LVD_IRQHandler        @ IRQ #26  (VC0 / VC1 / LVD 共用)
    .word   Dummy_IRQHandler            @ IRQ #27
    .word   CAN_IRQHandler              @ IRQ #28
    .word   ATIM_BK_IRQHandler          @ IRQ #29
    .word   FLASH_RAM_IRQHandler        @ IRQ #30  (FLASH / RAM 共用)
    .word   CTRIM_FAULT_IRQHandler      @ IRQ #31  (CTRIM / FAULT 共用)
    .size   g_pfnVectors, . - g_pfnVectors

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
    @ --- Cortex-M0+ 复位后 VTOR 本身就是 0, 而向量表位于 Flash 起始 0x0,
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

    @ --- System clock / device early init (provided by system_hc32a052.c) ---
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
@  (同名强符号定义在 mcu/common/interrupts_hc32a052.c 中时会自动覆盖这些弱符号)
@===============================================================================
    .section .text.Default_Handler, "ax", %progbits
    .align  2
    .globl  Default_Handler
    .type   Default_Handler, %function
    .thumb_func
Default_Handler:
    b       .
    .size   Default_Handler, . - Default_Handler

@ --- Cortex-M system exceptions (weak) ---
    .weak   NMI_Handler
    .thumb_set NMI_Handler, Default_Handler

    .weak   HardFault_Handler
    .thumb_set HardFault_Handler, Default_Handler

    .weak   SVC_Handler
    .thumb_set SVC_Handler, Default_Handler

    .weak   PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler

    .weak   SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler

@ --- Device interrupt handlers (weak) ---
    .weak   PORTA_IRQHandler
    .thumb_set PORTA_IRQHandler, Default_Handler

    .weak   PORTB_IRQHandler
    .thumb_set PORTB_IRQHandler, Default_Handler

    .weak   PORTC_IRQHandler
    .thumb_set PORTC_IRQHandler, Default_Handler

    .weak   PORTD_IRQHandler
    .thumb_set PORTD_IRQHandler, Default_Handler

    .weak   DMAC_IRQHandler
    .thumb_set DMAC_IRQHandler, Default_Handler

    .weak   ATIM3_IRQHandler
    .thumb_set ATIM3_IRQHandler, Default_Handler

    .weak   USART0_IRQHandler
    .thumb_set USART0_IRQHandler, Default_Handler

    .weak   USART1_IRQHandler
    .thumb_set USART1_IRQHandler, Default_Handler

    .weak   LPUART0_IRQHandler
    .thumb_set LPUART0_IRQHandler, Default_Handler

    .weak   LPUART1_IRQHandler
    .thumb_set LPUART1_IRQHandler, Default_Handler

    .weak   SPI0_IRQHandler
    .thumb_set SPI0_IRQHandler, Default_Handler

    .weak   SPI1_IRQHandler
    .thumb_set SPI1_IRQHandler, Default_Handler

    .weak   I2C0_IRQHandler
    .thumb_set I2C0_IRQHandler, Default_Handler

    .weak   I2C1_IRQHandler
    .thumb_set I2C1_IRQHandler, Default_Handler

    .weak   ATIM0_IRQHandler
    .thumb_set ATIM0_IRQHandler, Default_Handler

    .weak   ATIM1_IRQHandler
    .thumb_set ATIM1_IRQHandler, Default_Handler

    .weak   ATIM2_IRQHandler
    .thumb_set ATIM2_IRQHandler, Default_Handler

    .weak   LPTIM_IRQHandler
    .thumb_set LPTIM_IRQHandler, Default_Handler

    .weak   GTIM0_BTIM0_1_2_IRQHandler
    .thumb_set GTIM0_BTIM0_1_2_IRQHandler, Default_Handler

    .weak   GTIM1_BTIM3_4_5_IRQHandler
    .thumb_set GTIM1_BTIM3_4_5_IRQHandler, Default_Handler

    .weak   I2CSLV_IRQHandler
    .thumb_set I2CSLV_IRQHandler, Default_Handler

    .weak   WWDT_IRQHandler
    .thumb_set WWDT_IRQHandler, Default_Handler

    .weak   IWDT_IRQHandler
    .thumb_set IWDT_IRQHandler, Default_Handler

    .weak   RTC_IRQHandler
    .thumb_set RTC_IRQHandler, Default_Handler

    .weak   ADC_IRQHandler
    .thumb_set ADC_IRQHandler, Default_Handler

    .weak   Dummy_IRQHandler
    .thumb_set Dummy_IRQHandler, Default_Handler

    .weak   VC0_1_LVD_IRQHandler
    .thumb_set VC0_1_LVD_IRQHandler, Default_Handler

    .weak   CAN_IRQHandler
    .thumb_set CAN_IRQHandler, Default_Handler

    .weak   ATIM_BK_IRQHandler
    .thumb_set ATIM_BK_IRQHandler, Default_Handler

    .weak   FLASH_RAM_IRQHandler
    .thumb_set FLASH_RAM_IRQHandler, Default_Handler

    .weak   CTRIM_FAULT_IRQHandler
    .thumb_set CTRIM_FAULT_IRQHandler, Default_Handler

    .end
