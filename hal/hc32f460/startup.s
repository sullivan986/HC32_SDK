@*******************************************************************************
@  Startup / vector table for XHSC HC32F460 (ARM Cortex-M4F (ARMv7-M))
@  Target toolchain: ATfE (Arm Toolchain for Embedded, clang + picolibc) ONLY
@
@  [自动生成] 勿手改; 重新生成: python3 tools/gen_startup.py hc32f460
@  Written in GNU assembler syntax, assembled by the ATfE clang integrated
@  assembler (LLVM). Link with -nostartfiles against the matching linker
@  script Link.ld (same directory), e.g.:
@
@    clang --target=arm-none-eabi -mcpu=cortex-m4 -mthumb -nostartfiles \
@        -T Link.ld startup.s ... -o app.elf
@
@  中断向量表顺序与 IRQ 编号来源:
@    temp/HC32F460_DDL_Rev3.3.0/drivers/cmsis/Device/HDSC/hc32f4xx/Include/hc32f460.h   (enum IRQn)
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
    .arch   armv7-m
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
    .word   MemManage_Handler                @ core slot 4
    .word   BusFault_Handler                 @ core slot 5
    .word   UsageFault_Handler               @ core slot 6
    .word   0                                @ core slot 7
    .word   0                                @ core slot 8
    .word   0                                @ core slot 9
    .word   0                                @ core slot 10
    .word   SVC_Handler                      @ core slot 11
    .word   DebugMon_Handler                 @ core slot 12
    .word   0                                @ core slot 13
    .word   PendSV_Handler                   @ core slot 14
    .word   SysTick_Handler                  @ core slot 15
    .word   IRQ000_Handler                   @ IRQ #0
    .word   IRQ001_Handler                   @ IRQ #1
    .word   IRQ002_Handler                   @ IRQ #2
    .word   IRQ003_Handler                   @ IRQ #3
    .word   IRQ004_Handler                   @ IRQ #4
    .word   IRQ005_Handler                   @ IRQ #5
    .word   IRQ006_Handler                   @ IRQ #6
    .word   IRQ007_Handler                   @ IRQ #7
    .word   IRQ008_Handler                   @ IRQ #8
    .word   IRQ009_Handler                   @ IRQ #9
    .word   IRQ010_Handler                   @ IRQ #10
    .word   IRQ011_Handler                   @ IRQ #11
    .word   IRQ012_Handler                   @ IRQ #12
    .word   IRQ013_Handler                   @ IRQ #13
    .word   IRQ014_Handler                   @ IRQ #14
    .word   IRQ015_Handler                   @ IRQ #15
    .word   IRQ016_Handler                   @ IRQ #16
    .word   IRQ017_Handler                   @ IRQ #17
    .word   IRQ018_Handler                   @ IRQ #18
    .word   IRQ019_Handler                   @ IRQ #19
    .word   IRQ020_Handler                   @ IRQ #20
    .word   IRQ021_Handler                   @ IRQ #21
    .word   IRQ022_Handler                   @ IRQ #22
    .word   IRQ023_Handler                   @ IRQ #23
    .word   IRQ024_Handler                   @ IRQ #24
    .word   IRQ025_Handler                   @ IRQ #25
    .word   IRQ026_Handler                   @ IRQ #26
    .word   IRQ027_Handler                   @ IRQ #27
    .word   IRQ028_Handler                   @ IRQ #28
    .word   IRQ029_Handler                   @ IRQ #29
    .word   IRQ030_Handler                   @ IRQ #30
    .word   IRQ031_Handler                   @ IRQ #31
    .word   IRQ032_Handler                   @ IRQ #32
    .word   IRQ033_Handler                   @ IRQ #33
    .word   IRQ034_Handler                   @ IRQ #34
    .word   IRQ035_Handler                   @ IRQ #35
    .word   IRQ036_Handler                   @ IRQ #36
    .word   IRQ037_Handler                   @ IRQ #37
    .word   IRQ038_Handler                   @ IRQ #38
    .word   IRQ039_Handler                   @ IRQ #39
    .word   IRQ040_Handler                   @ IRQ #40
    .word   IRQ041_Handler                   @ IRQ #41
    .word   IRQ042_Handler                   @ IRQ #42
    .word   IRQ043_Handler                   @ IRQ #43
    .word   IRQ044_Handler                   @ IRQ #44
    .word   IRQ045_Handler                   @ IRQ #45
    .word   IRQ046_Handler                   @ IRQ #46
    .word   IRQ047_Handler                   @ IRQ #47
    .word   IRQ048_Handler                   @ IRQ #48
    .word   IRQ049_Handler                   @ IRQ #49
    .word   IRQ050_Handler                   @ IRQ #50
    .word   IRQ051_Handler                   @ IRQ #51
    .word   IRQ052_Handler                   @ IRQ #52
    .word   IRQ053_Handler                   @ IRQ #53
    .word   IRQ054_Handler                   @ IRQ #54
    .word   IRQ055_Handler                   @ IRQ #55
    .word   IRQ056_Handler                   @ IRQ #56
    .word   IRQ057_Handler                   @ IRQ #57
    .word   IRQ058_Handler                   @ IRQ #58
    .word   IRQ059_Handler                   @ IRQ #59
    .word   IRQ060_Handler                   @ IRQ #60
    .word   IRQ061_Handler                   @ IRQ #61
    .word   IRQ062_Handler                   @ IRQ #62
    .word   IRQ063_Handler                   @ IRQ #63
    .word   IRQ064_Handler                   @ IRQ #64
    .word   IRQ065_Handler                   @ IRQ #65
    .word   IRQ066_Handler                   @ IRQ #66
    .word   IRQ067_Handler                   @ IRQ #67
    .word   IRQ068_Handler                   @ IRQ #68
    .word   IRQ069_Handler                   @ IRQ #69
    .word   IRQ070_Handler                   @ IRQ #70
    .word   IRQ071_Handler                   @ IRQ #71
    .word   IRQ072_Handler                   @ IRQ #72
    .word   IRQ073_Handler                   @ IRQ #73
    .word   IRQ074_Handler                   @ IRQ #74
    .word   IRQ075_Handler                   @ IRQ #75
    .word   IRQ076_Handler                   @ IRQ #76
    .word   IRQ077_Handler                   @ IRQ #77
    .word   IRQ078_Handler                   @ IRQ #78
    .word   IRQ079_Handler                   @ IRQ #79
    .word   IRQ080_Handler                   @ IRQ #80
    .word   IRQ081_Handler                   @ IRQ #81
    .word   IRQ082_Handler                   @ IRQ #82
    .word   IRQ083_Handler                   @ IRQ #83
    .word   IRQ084_Handler                   @ IRQ #84
    .word   IRQ085_Handler                   @ IRQ #85
    .word   IRQ086_Handler                   @ IRQ #86
    .word   IRQ087_Handler                   @ IRQ #87
    .word   IRQ088_Handler                   @ IRQ #88
    .word   IRQ089_Handler                   @ IRQ #89
    .word   IRQ090_Handler                   @ IRQ #90
    .word   IRQ091_Handler                   @ IRQ #91
    .word   IRQ092_Handler                   @ IRQ #92
    .word   IRQ093_Handler                   @ IRQ #93
    .word   IRQ094_Handler                   @ IRQ #94
    .word   IRQ095_Handler                   @ IRQ #95
    .word   IRQ096_Handler                   @ IRQ #96
    .word   IRQ097_Handler                   @ IRQ #97
    .word   IRQ098_Handler                   @ IRQ #98
    .word   IRQ099_Handler                   @ IRQ #99
    .word   IRQ100_Handler                   @ IRQ #100
    .word   IRQ101_Handler                   @ IRQ #101
    .word   IRQ102_Handler                   @ IRQ #102
    .word   IRQ103_Handler                   @ IRQ #103
    .word   IRQ104_Handler                   @ IRQ #104
    .word   IRQ105_Handler                   @ IRQ #105
    .word   IRQ106_Handler                   @ IRQ #106
    .word   IRQ107_Handler                   @ IRQ #107
    .word   IRQ108_Handler                   @ IRQ #108
    .word   IRQ109_Handler                   @ IRQ #109
    .word   IRQ110_Handler                   @ IRQ #110
    .word   IRQ111_Handler                   @ IRQ #111
    .word   IRQ112_Handler                   @ IRQ #112
    .word   IRQ113_Handler                   @ IRQ #113
    .word   IRQ114_Handler                   @ IRQ #114
    .word   IRQ115_Handler                   @ IRQ #115
    .word   IRQ116_Handler                   @ IRQ #116
    .word   IRQ117_Handler                   @ IRQ #117
    .word   IRQ118_Handler                   @ IRQ #118
    .word   IRQ119_Handler                   @ IRQ #119
    .word   IRQ120_Handler                   @ IRQ #120
    .word   IRQ121_Handler                   @ IRQ #121
    .word   IRQ122_Handler                   @ IRQ #122
    .word   IRQ123_Handler                   @ IRQ #123
    .word   IRQ124_Handler                   @ IRQ #124
    .word   IRQ125_Handler                   @ IRQ #125
    .word   IRQ126_Handler                   @ IRQ #126
    .word   IRQ127_Handler                   @ IRQ #127
    .word   IRQ128_Handler                   @ IRQ #128
    .word   IRQ129_Handler                   @ IRQ #129
    .word   IRQ130_Handler                   @ IRQ #130
    .word   IRQ131_Handler                   @ IRQ #131
    .word   IRQ132_Handler                   @ IRQ #132
    .word   IRQ133_Handler                   @ IRQ #133
    .word   IRQ134_Handler                   @ IRQ #134
    .word   IRQ135_Handler                   @ IRQ #135
    .word   IRQ136_Handler                   @ IRQ #136
    .word   IRQ137_Handler                   @ IRQ #137
    .word   IRQ138_Handler                   @ IRQ #138
    .word   IRQ139_Handler                   @ IRQ #139
    .word   IRQ140_Handler                   @ IRQ #140
    .word   IRQ141_Handler                   @ IRQ #141
    .word   IRQ142_Handler                   @ IRQ #142
    .word   IRQ143_Handler                   @ IRQ #143
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

    .weak   MemManage_Handler
    .thumb_set MemManage_Handler, Default_Handler

    .weak   BusFault_Handler
    .thumb_set BusFault_Handler, Default_Handler

    .weak   UsageFault_Handler
    .thumb_set UsageFault_Handler, Default_Handler

    .weak   SVC_Handler
    .thumb_set SVC_Handler, Default_Handler

    .weak   DebugMon_Handler
    .thumb_set DebugMon_Handler, Default_Handler

    .weak   PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler

    .weak   SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler

    .weak   IRQ000_Handler
    .thumb_set IRQ000_Handler, Default_Handler

    .weak   IRQ001_Handler
    .thumb_set IRQ001_Handler, Default_Handler

    .weak   IRQ002_Handler
    .thumb_set IRQ002_Handler, Default_Handler

    .weak   IRQ003_Handler
    .thumb_set IRQ003_Handler, Default_Handler

    .weak   IRQ004_Handler
    .thumb_set IRQ004_Handler, Default_Handler

    .weak   IRQ005_Handler
    .thumb_set IRQ005_Handler, Default_Handler

    .weak   IRQ006_Handler
    .thumb_set IRQ006_Handler, Default_Handler

    .weak   IRQ007_Handler
    .thumb_set IRQ007_Handler, Default_Handler

    .weak   IRQ008_Handler
    .thumb_set IRQ008_Handler, Default_Handler

    .weak   IRQ009_Handler
    .thumb_set IRQ009_Handler, Default_Handler

    .weak   IRQ010_Handler
    .thumb_set IRQ010_Handler, Default_Handler

    .weak   IRQ011_Handler
    .thumb_set IRQ011_Handler, Default_Handler

    .weak   IRQ012_Handler
    .thumb_set IRQ012_Handler, Default_Handler

    .weak   IRQ013_Handler
    .thumb_set IRQ013_Handler, Default_Handler

    .weak   IRQ014_Handler
    .thumb_set IRQ014_Handler, Default_Handler

    .weak   IRQ015_Handler
    .thumb_set IRQ015_Handler, Default_Handler

    .weak   IRQ016_Handler
    .thumb_set IRQ016_Handler, Default_Handler

    .weak   IRQ017_Handler
    .thumb_set IRQ017_Handler, Default_Handler

    .weak   IRQ018_Handler
    .thumb_set IRQ018_Handler, Default_Handler

    .weak   IRQ019_Handler
    .thumb_set IRQ019_Handler, Default_Handler

    .weak   IRQ020_Handler
    .thumb_set IRQ020_Handler, Default_Handler

    .weak   IRQ021_Handler
    .thumb_set IRQ021_Handler, Default_Handler

    .weak   IRQ022_Handler
    .thumb_set IRQ022_Handler, Default_Handler

    .weak   IRQ023_Handler
    .thumb_set IRQ023_Handler, Default_Handler

    .weak   IRQ024_Handler
    .thumb_set IRQ024_Handler, Default_Handler

    .weak   IRQ025_Handler
    .thumb_set IRQ025_Handler, Default_Handler

    .weak   IRQ026_Handler
    .thumb_set IRQ026_Handler, Default_Handler

    .weak   IRQ027_Handler
    .thumb_set IRQ027_Handler, Default_Handler

    .weak   IRQ028_Handler
    .thumb_set IRQ028_Handler, Default_Handler

    .weak   IRQ029_Handler
    .thumb_set IRQ029_Handler, Default_Handler

    .weak   IRQ030_Handler
    .thumb_set IRQ030_Handler, Default_Handler

    .weak   IRQ031_Handler
    .thumb_set IRQ031_Handler, Default_Handler

    .weak   IRQ032_Handler
    .thumb_set IRQ032_Handler, Default_Handler

    .weak   IRQ033_Handler
    .thumb_set IRQ033_Handler, Default_Handler

    .weak   IRQ034_Handler
    .thumb_set IRQ034_Handler, Default_Handler

    .weak   IRQ035_Handler
    .thumb_set IRQ035_Handler, Default_Handler

    .weak   IRQ036_Handler
    .thumb_set IRQ036_Handler, Default_Handler

    .weak   IRQ037_Handler
    .thumb_set IRQ037_Handler, Default_Handler

    .weak   IRQ038_Handler
    .thumb_set IRQ038_Handler, Default_Handler

    .weak   IRQ039_Handler
    .thumb_set IRQ039_Handler, Default_Handler

    .weak   IRQ040_Handler
    .thumb_set IRQ040_Handler, Default_Handler

    .weak   IRQ041_Handler
    .thumb_set IRQ041_Handler, Default_Handler

    .weak   IRQ042_Handler
    .thumb_set IRQ042_Handler, Default_Handler

    .weak   IRQ043_Handler
    .thumb_set IRQ043_Handler, Default_Handler

    .weak   IRQ044_Handler
    .thumb_set IRQ044_Handler, Default_Handler

    .weak   IRQ045_Handler
    .thumb_set IRQ045_Handler, Default_Handler

    .weak   IRQ046_Handler
    .thumb_set IRQ046_Handler, Default_Handler

    .weak   IRQ047_Handler
    .thumb_set IRQ047_Handler, Default_Handler

    .weak   IRQ048_Handler
    .thumb_set IRQ048_Handler, Default_Handler

    .weak   IRQ049_Handler
    .thumb_set IRQ049_Handler, Default_Handler

    .weak   IRQ050_Handler
    .thumb_set IRQ050_Handler, Default_Handler

    .weak   IRQ051_Handler
    .thumb_set IRQ051_Handler, Default_Handler

    .weak   IRQ052_Handler
    .thumb_set IRQ052_Handler, Default_Handler

    .weak   IRQ053_Handler
    .thumb_set IRQ053_Handler, Default_Handler

    .weak   IRQ054_Handler
    .thumb_set IRQ054_Handler, Default_Handler

    .weak   IRQ055_Handler
    .thumb_set IRQ055_Handler, Default_Handler

    .weak   IRQ056_Handler
    .thumb_set IRQ056_Handler, Default_Handler

    .weak   IRQ057_Handler
    .thumb_set IRQ057_Handler, Default_Handler

    .weak   IRQ058_Handler
    .thumb_set IRQ058_Handler, Default_Handler

    .weak   IRQ059_Handler
    .thumb_set IRQ059_Handler, Default_Handler

    .weak   IRQ060_Handler
    .thumb_set IRQ060_Handler, Default_Handler

    .weak   IRQ061_Handler
    .thumb_set IRQ061_Handler, Default_Handler

    .weak   IRQ062_Handler
    .thumb_set IRQ062_Handler, Default_Handler

    .weak   IRQ063_Handler
    .thumb_set IRQ063_Handler, Default_Handler

    .weak   IRQ064_Handler
    .thumb_set IRQ064_Handler, Default_Handler

    .weak   IRQ065_Handler
    .thumb_set IRQ065_Handler, Default_Handler

    .weak   IRQ066_Handler
    .thumb_set IRQ066_Handler, Default_Handler

    .weak   IRQ067_Handler
    .thumb_set IRQ067_Handler, Default_Handler

    .weak   IRQ068_Handler
    .thumb_set IRQ068_Handler, Default_Handler

    .weak   IRQ069_Handler
    .thumb_set IRQ069_Handler, Default_Handler

    .weak   IRQ070_Handler
    .thumb_set IRQ070_Handler, Default_Handler

    .weak   IRQ071_Handler
    .thumb_set IRQ071_Handler, Default_Handler

    .weak   IRQ072_Handler
    .thumb_set IRQ072_Handler, Default_Handler

    .weak   IRQ073_Handler
    .thumb_set IRQ073_Handler, Default_Handler

    .weak   IRQ074_Handler
    .thumb_set IRQ074_Handler, Default_Handler

    .weak   IRQ075_Handler
    .thumb_set IRQ075_Handler, Default_Handler

    .weak   IRQ076_Handler
    .thumb_set IRQ076_Handler, Default_Handler

    .weak   IRQ077_Handler
    .thumb_set IRQ077_Handler, Default_Handler

    .weak   IRQ078_Handler
    .thumb_set IRQ078_Handler, Default_Handler

    .weak   IRQ079_Handler
    .thumb_set IRQ079_Handler, Default_Handler

    .weak   IRQ080_Handler
    .thumb_set IRQ080_Handler, Default_Handler

    .weak   IRQ081_Handler
    .thumb_set IRQ081_Handler, Default_Handler

    .weak   IRQ082_Handler
    .thumb_set IRQ082_Handler, Default_Handler

    .weak   IRQ083_Handler
    .thumb_set IRQ083_Handler, Default_Handler

    .weak   IRQ084_Handler
    .thumb_set IRQ084_Handler, Default_Handler

    .weak   IRQ085_Handler
    .thumb_set IRQ085_Handler, Default_Handler

    .weak   IRQ086_Handler
    .thumb_set IRQ086_Handler, Default_Handler

    .weak   IRQ087_Handler
    .thumb_set IRQ087_Handler, Default_Handler

    .weak   IRQ088_Handler
    .thumb_set IRQ088_Handler, Default_Handler

    .weak   IRQ089_Handler
    .thumb_set IRQ089_Handler, Default_Handler

    .weak   IRQ090_Handler
    .thumb_set IRQ090_Handler, Default_Handler

    .weak   IRQ091_Handler
    .thumb_set IRQ091_Handler, Default_Handler

    .weak   IRQ092_Handler
    .thumb_set IRQ092_Handler, Default_Handler

    .weak   IRQ093_Handler
    .thumb_set IRQ093_Handler, Default_Handler

    .weak   IRQ094_Handler
    .thumb_set IRQ094_Handler, Default_Handler

    .weak   IRQ095_Handler
    .thumb_set IRQ095_Handler, Default_Handler

    .weak   IRQ096_Handler
    .thumb_set IRQ096_Handler, Default_Handler

    .weak   IRQ097_Handler
    .thumb_set IRQ097_Handler, Default_Handler

    .weak   IRQ098_Handler
    .thumb_set IRQ098_Handler, Default_Handler

    .weak   IRQ099_Handler
    .thumb_set IRQ099_Handler, Default_Handler

    .weak   IRQ100_Handler
    .thumb_set IRQ100_Handler, Default_Handler

    .weak   IRQ101_Handler
    .thumb_set IRQ101_Handler, Default_Handler

    .weak   IRQ102_Handler
    .thumb_set IRQ102_Handler, Default_Handler

    .weak   IRQ103_Handler
    .thumb_set IRQ103_Handler, Default_Handler

    .weak   IRQ104_Handler
    .thumb_set IRQ104_Handler, Default_Handler

    .weak   IRQ105_Handler
    .thumb_set IRQ105_Handler, Default_Handler

    .weak   IRQ106_Handler
    .thumb_set IRQ106_Handler, Default_Handler

    .weak   IRQ107_Handler
    .thumb_set IRQ107_Handler, Default_Handler

    .weak   IRQ108_Handler
    .thumb_set IRQ108_Handler, Default_Handler

    .weak   IRQ109_Handler
    .thumb_set IRQ109_Handler, Default_Handler

    .weak   IRQ110_Handler
    .thumb_set IRQ110_Handler, Default_Handler

    .weak   IRQ111_Handler
    .thumb_set IRQ111_Handler, Default_Handler

    .weak   IRQ112_Handler
    .thumb_set IRQ112_Handler, Default_Handler

    .weak   IRQ113_Handler
    .thumb_set IRQ113_Handler, Default_Handler

    .weak   IRQ114_Handler
    .thumb_set IRQ114_Handler, Default_Handler

    .weak   IRQ115_Handler
    .thumb_set IRQ115_Handler, Default_Handler

    .weak   IRQ116_Handler
    .thumb_set IRQ116_Handler, Default_Handler

    .weak   IRQ117_Handler
    .thumb_set IRQ117_Handler, Default_Handler

    .weak   IRQ118_Handler
    .thumb_set IRQ118_Handler, Default_Handler

    .weak   IRQ119_Handler
    .thumb_set IRQ119_Handler, Default_Handler

    .weak   IRQ120_Handler
    .thumb_set IRQ120_Handler, Default_Handler

    .weak   IRQ121_Handler
    .thumb_set IRQ121_Handler, Default_Handler

    .weak   IRQ122_Handler
    .thumb_set IRQ122_Handler, Default_Handler

    .weak   IRQ123_Handler
    .thumb_set IRQ123_Handler, Default_Handler

    .weak   IRQ124_Handler
    .thumb_set IRQ124_Handler, Default_Handler

    .weak   IRQ125_Handler
    .thumb_set IRQ125_Handler, Default_Handler

    .weak   IRQ126_Handler
    .thumb_set IRQ126_Handler, Default_Handler

    .weak   IRQ127_Handler
    .thumb_set IRQ127_Handler, Default_Handler

    .weak   IRQ128_Handler
    .thumb_set IRQ128_Handler, Default_Handler

    .weak   IRQ129_Handler
    .thumb_set IRQ129_Handler, Default_Handler

    .weak   IRQ130_Handler
    .thumb_set IRQ130_Handler, Default_Handler

    .weak   IRQ131_Handler
    .thumb_set IRQ131_Handler, Default_Handler

    .weak   IRQ132_Handler
    .thumb_set IRQ132_Handler, Default_Handler

    .weak   IRQ133_Handler
    .thumb_set IRQ133_Handler, Default_Handler

    .weak   IRQ134_Handler
    .thumb_set IRQ134_Handler, Default_Handler

    .weak   IRQ135_Handler
    .thumb_set IRQ135_Handler, Default_Handler

    .weak   IRQ136_Handler
    .thumb_set IRQ136_Handler, Default_Handler

    .weak   IRQ137_Handler
    .thumb_set IRQ137_Handler, Default_Handler

    .weak   IRQ138_Handler
    .thumb_set IRQ138_Handler, Default_Handler

    .weak   IRQ139_Handler
    .thumb_set IRQ139_Handler, Default_Handler

    .weak   IRQ140_Handler
    .thumb_set IRQ140_Handler, Default_Handler

    .weak   IRQ141_Handler
    .thumb_set IRQ141_Handler, Default_Handler

    .weak   IRQ142_Handler
    .thumb_set IRQ142_Handler, Default_Handler

    .weak   IRQ143_Handler
    .thumb_set IRQ143_Handler, Default_Handler


    .end
