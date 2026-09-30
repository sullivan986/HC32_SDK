@*******************************************************************************
@  Startup / vector table for XHSC HC32F005 (ARM Cortex-M0+ (ARMv6-M))
@  Target toolchain: ATfE (Arm Toolchain for Embedded, clang + picolibc) ONLY
@
@  [自动生成] 勿手改; 重新生成: python3 tools/gen_startup.py hc32f005
@  Written in GNU assembler syntax, assembled by the ATfE clang integrated
@  assembler (LLVM). Link with -nostartfiles against the matching linker
@  script Link.ld (same directory), e.g.:
@
@    clang --target=arm-none-eabi -mcpu=cortex-m0plus -mthumb -nostartfiles \
@        -T Link.ld startup.s ... -o app.elf
@
@  中断向量表顺序与 IRQ 编号来源:
@    temp/HC32F005_DDL_Rev2.0.0/mcu/common/hc32f005.h   (enum IRQn)
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
    .word   __stack                          @ core slot 0
    .word   Reset_Handler                    @ core slot 1
    .word   NMI_Handler                      @ core slot 2
    .word   HardFault_Handler                @ core slot 3
    .word   0                                @ core slot 4
    .word   0                                @ core slot 5
    .word   0                                @ core slot 6
    .word   0                                @ core slot 7
    .word   0                                @ core slot 8
    .word   0                                @ core slot 9
    .word   0                                @ core slot 10
    .word   SVC_Handler                      @ core slot 11
    .word   0                                @ core slot 12
    .word   0                                @ core slot 13
    .word   PendSV_Handler                   @ core slot 14
    .word   SysTick_Handler                  @ core slot 15
    .word   PORT0_IRQHandler                 @ IRQ #0
    .word   PORT1_IRQHandler                 @ IRQ #1
    .word   PORT2_IRQHandler                 @ IRQ #2
    .word   PORT3_IRQHandler                 @ IRQ #3
    .word   Dummy_IRQHandler                 @ IRQ #4 (reserved)
    .word   Dummy_IRQHandler                 @ IRQ #5 (reserved)
    .word   UART0_IRQHandler                 @ IRQ #6
    .word   UART1_IRQHandler                 @ IRQ #7
    .word   Dummy_IRQHandler                 @ IRQ #8 (reserved)
    .word   Dummy_IRQHandler                 @ IRQ #9 (reserved)
    .word   SPI_IRQHandler                   @ IRQ #10
    .word   Dummy_IRQHandler                 @ IRQ #11 (reserved)
    .word   I2C_IRQHandler                   @ IRQ #12
    .word   Dummy_IRQHandler                 @ IRQ #13 (reserved)
    .word   TIM0_IRQHandler                  @ IRQ #14
    .word   TIM1_IRQHandler                  @ IRQ #15
    .word   TIM2_IRQHandler                  @ IRQ #16
    .word   Dummy_IRQHandler                 @ IRQ #17 (reserved)
    .word   ADTIM4_IRQHandler                @ IRQ #18
    .word   ADTIM5_IRQHandler                @ IRQ #19
    .word   ADTIM6_IRQHandler                @ IRQ #20
    .word   PCA_IRQHandler                   @ IRQ #21
    .word   WDT_IRQHandler                   @ IRQ #22
    .word   Dummy_IRQHandler                 @ IRQ #23 (reserved)
    .word   ADC_IRQHandler                   @ IRQ #24
    .word   Dummy_IRQHandler                 @ IRQ #25 (reserved)
    .word   VC0_IRQHandler                   @ IRQ #26
    .word   VC1_IRQHandler                   @ IRQ #27
    .word   LVD_IRQHandler                   @ IRQ #28
    .word   Dummy_IRQHandler                 @ IRQ #29 (reserved)
    .word   FLASH_RAM_IRQHandler             @ IRQ #30
    .word   CLKTRIM_IRQHandler               @ IRQ #31
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

    .weak   PORT0_IRQHandler
    .thumb_set PORT0_IRQHandler, Default_Handler

    .weak   PORT1_IRQHandler
    .thumb_set PORT1_IRQHandler, Default_Handler

    .weak   PORT2_IRQHandler
    .thumb_set PORT2_IRQHandler, Default_Handler

    .weak   PORT3_IRQHandler
    .thumb_set PORT3_IRQHandler, Default_Handler

    .weak   Dummy_IRQHandler
    .thumb_set Dummy_IRQHandler, Default_Handler

    .weak   UART0_IRQHandler
    .thumb_set UART0_IRQHandler, Default_Handler

    .weak   UART1_IRQHandler
    .thumb_set UART1_IRQHandler, Default_Handler

    .weak   SPI_IRQHandler
    .thumb_set SPI_IRQHandler, Default_Handler

    .weak   I2C_IRQHandler
    .thumb_set I2C_IRQHandler, Default_Handler

    .weak   TIM0_IRQHandler
    .thumb_set TIM0_IRQHandler, Default_Handler

    .weak   TIM1_IRQHandler
    .thumb_set TIM1_IRQHandler, Default_Handler

    .weak   TIM2_IRQHandler
    .thumb_set TIM2_IRQHandler, Default_Handler

    .weak   ADTIM4_IRQHandler
    .thumb_set ADTIM4_IRQHandler, Default_Handler

    .weak   ADTIM5_IRQHandler
    .thumb_set ADTIM5_IRQHandler, Default_Handler

    .weak   ADTIM6_IRQHandler
    .thumb_set ADTIM6_IRQHandler, Default_Handler

    .weak   PCA_IRQHandler
    .thumb_set PCA_IRQHandler, Default_Handler

    .weak   WDT_IRQHandler
    .thumb_set WDT_IRQHandler, Default_Handler

    .weak   ADC_IRQHandler
    .thumb_set ADC_IRQHandler, Default_Handler

    .weak   VC0_IRQHandler
    .thumb_set VC0_IRQHandler, Default_Handler

    .weak   VC1_IRQHandler
    .thumb_set VC1_IRQHandler, Default_Handler

    .weak   LVD_IRQHandler
    .thumb_set LVD_IRQHandler, Default_Handler

    .weak   FLASH_RAM_IRQHandler
    .thumb_set FLASH_RAM_IRQHandler, Default_Handler

    .weak   CLKTRIM_IRQHandler
    .thumb_set CLKTRIM_IRQHandler, Default_Handler


    .end
