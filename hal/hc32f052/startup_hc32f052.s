;/******************************************************************************
;*  
;* Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
;* 
;* This software component is licensed by XHSC under BSD 3-Clause license
;* (the "License"); You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                    opensource.org/licenses/BSD-3-Clause
;* 
;*/
;/*****************************************************************************/

;/*****************************************************************************/
;/*  Startup for ARM                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2022-08-08                                                   */
;/*  Target-mcu  {MCU_PN_H}                                                   */
;/*****************************************************************************/

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors                       
                DCD     __initial_sp                ; Top of Stack
                DCD     Reset_Handler               ; Reset        
                DCD     NMI_Handler                 ; NMI
                DCD     HardFault_Handler           ; Hard Fault
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVC_Handler                 ; SVCall
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     PendSV_Handler              ; PendSV
                DCD     SysTick_Handler             ; SysTick

                DCD     PORTA_IRQHandler            ; IRQ #0 
                DCD     PORTB_IRQHandler            ; IRQ #1 
                DCD     PORTC_IRQHandler            ; IRQ #2 
                DCD     PORTD_IRQHandler            ; IRQ #3 
                DCD     DMAC_IRQHandler             ; IRQ #4 
                DCD     ATIM3_IRQHandler            ; IRQ #5 
                DCD     USART0_IRQHandler           ; IRQ #6 
                DCD     USART1_IRQHandler           ; IRQ #7 
                DCD     LPUART0_IRQHandler          ; IRQ #8 
                DCD     LPUART1_IRQHandler          ; IRQ #9 
                DCD     SPI0_IRQHandler             ; IRQ #10
                DCD     SPI1_IRQHandler             ; IRQ #11
                DCD     I2C0_IRQHandler             ; IRQ #12
                DCD     I2C1_IRQHandler             ; IRQ #13
                DCD     ATIM0_IRQHandler            ; IRQ #14
                DCD     ATIM1_IRQHandler            ; IRQ #15
                DCD     ATIM2_IRQHandler            ; IRQ #16
                DCD     LPTIM_IRQHandler            ; IRQ #17
                DCD     GTIM0_BTIM0_1_2_IRQHandler  ; IRQ #18
                DCD     GTIM1_BTIM3_4_5_IRQHandler  ; IRQ #19
                DCD     I2CSLV_IRQHandler           ; IRQ #20
                DCD     WWDT_IRQHandler             ; IRQ #21
                DCD     IWDT_IRQHandler             ; IRQ #22
                DCD     RTC_IRQHandler              ; IRQ #23
                DCD     ADC_IRQHandler              ; IRQ #24
                DCD     Dummy_IRQHandler            ; IRQ #25
                DCD     VC0_1_LVD_IRQHandler        ; IRQ #26
                DCD     Dummy_IRQHandler            ; IRQ #27
                DCD     CAN_IRQHandler              ; IRQ #28
                DCD     ATIM_BK_IRQHandler          ; IRQ #29
                DCD     FLASH_RAM_IRQHandler        ; IRQ #30
                DCD     CTRIM_FAULT_IRQHandler      ; IRQ #31
__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler               [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

               ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0
                MOVS    R1, #0                 ; for warning, 
                ADD     R1, PC,#0              ; for A1609W, 
                CMP     R1, R0
                BLS     RAMCODE

              ; ram code base address. 
                ADD     R2, R0,R2
RAMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08 
                STR     R2, [R0]

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                 [WEAK]
                B       .
                ENDP
                
                
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler           [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                 [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler              [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler             [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  PORTA_IRQHandler              [WEAK]
                EXPORT  PORTB_IRQHandler              [WEAK]
                EXPORT  PORTC_IRQHandler              [WEAK]
                EXPORT  PORTD_IRQHandler              [WEAK]
                EXPORT  DMAC_IRQHandler               [WEAK]
                EXPORT  ATIM3_IRQHandler              [WEAK]
                EXPORT  USART0_IRQHandler             [WEAK]
				EXPORT  USART1_IRQHandler             [WEAK]
                EXPORT  LPUART0_IRQHandler            [WEAK]
                EXPORT  LPUART1_IRQHandler            [WEAK]
                EXPORT  SPI0_IRQHandler               [WEAK]
                EXPORT  SPI1_IRQHandler               [WEAK]
                EXPORT  I2C0_IRQHandler               [WEAK]
				EXPORT  I2C1_IRQHandler               [WEAK]
                EXPORT  ATIM0_IRQHandler              [WEAK]
				EXPORT  ATIM1_IRQHandler              [WEAK]
				EXPORT  ATIM2_IRQHandler              [WEAK]
				EXPORT  LPTIM_IRQHandler              [WEAK]
				EXPORT  GTIM0_BTIM0_1_2_IRQHandler    [WEAK]
                EXPORT  GTIM1_BTIM3_4_5_IRQHandler    [WEAK]
                EXPORT  I2CSLV_IRQHandler             [WEAK]
                EXPORT  WWDT_IRQHandler               [WEAK]
                EXPORT  IWDT_IRQHandler               [WEAK]
                EXPORT  RTC_IRQHandler                [WEAK]
                EXPORT  ADC_IRQHandler                [WEAK]
				EXPORT  Dummy_IRQHandler              [WEAK]
                EXPORT  VC0_1_LVD_IRQHandler          [WEAK]
                EXPORT  CAN_IRQHandler                [WEAK]
				EXPORT  ATIM_BK_IRQHandler            [WEAK]
                EXPORT  FLASH_RAM_IRQHandler          [WEAK]
                EXPORT  CTRIM_FAULT_IRQHandler        [WEAK]

PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
DMAC_IRQHandler
ATIM3_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
LPUART0_IRQHandler
LPUART1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
ATIM0_IRQHandler
ATIM1_IRQHandler
ATIM2_IRQHandler
LPTIM_IRQHandler
GTIM0_BTIM0_1_2_IRQHandler
GTIM1_BTIM3_4_5_IRQHandler
I2CSLV_IRQHandler
WWDT_IRQHandler
IWDT_IRQHandler
RTC_IRQHandler
ADC_IRQHandler
Dummy_IRQHandler
VC0_1_LVD_IRQHandler
CAN_IRQHandler
ATIM_BK_IRQHandler
FLASH_RAM_IRQHandler
CTRIM_FAULT_IRQHandler
                        
                              
                        
                        








                
               B .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
