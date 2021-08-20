    .syntax unified
    .cpu cortex-m3
    .thumb

    .section .text,"ax",%progbits

    .global HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    movs r1, #0
    b fault_handler

    .global MemManage_Handler
    .type MemManage_Handler, %function
MemManage_Handler:
    movs r1, #1
    b fault_handler

    .global BusFault_Handler
    .type BusFault_Handler, %function
BusFault_Handler:
    movs r1, #2
    b fault_handler

    .global UsageFault_Handler
    .type UsageFault_Handler, %function
UsageFault_Handler:
    movs r1, #3
    b fault_handler
    nop

fault_handler:
    /* TODO: test bit 4 to determine PSP or MSP */
    mrs r0, msp
    b DEBUG_PrintFault
