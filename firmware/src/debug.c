#include <stm32f1xx.h>
#include <stdint.h>

#include "debug.h"

/* Debug interface implementation, based on SWO */

void DEBUG_Init(void)
{
    GPIO_InitTypeDef gpio_init;
    gpio_init.Mode = GPIO_MODE_AF_PP;
    gpio_init.Pin = GPIO_PIN_3;
    gpio_init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    gpio_init.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &gpio_init);
    
    SCB->SHCSR |= SCB_SHCSR_USGFAULTENA | SCB_SHCSR_BUSFAULTENA | SCB_SHCSR_MEMFAULTENA;
    SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;
}

void DEBUG_PrintChar_(char x)
{
    ITM_SendChar(x);
}

void DEBUG_PrintString_(const char *s)
{
    while (*s) {
        ITM_SendChar(*s);
        s++;
    }
}

static const char hextab[16] = "0123456789ABCDEF";
static void DEBUG_PrintHexByte(uint8_t value)
{
    ITM_SendChar(hextab[value >> 4]);
    ITM_SendChar(hextab[value & 15]);
}

void DEBUG_PrintHex_(const void *p, unsigned n)
{
    const uint8_t *pp = (const uint8_t *)p;
    while (n--) {
        DEBUG_PrintHexByte(*pp);
        pp++;
        DEBUG_PrintChar_(' ');
    }
}

void DEBUG_PrintU8_(uint8_t value)
{
    DEBUG_PrintHexByte(value);
}

void DEBUG_PrintU16_(uint16_t value)
{
    DEBUG_PrintHexByte((value >> 8) & 0xFF);
    DEBUG_PrintHexByte((value >> 0) & 0xFF);
}

void DEBUG_PrintU32_(uint32_t value)
{
    DEBUG_PrintHexByte((value >> 24) & 0xFF);
    DEBUG_PrintHexByte((value >> 16) & 0xFF);
    DEBUG_PrintHexByte((value >> 8) & 0xFF);
    DEBUG_PrintHexByte((value >> 0) & 0xFF);
}

typedef struct __attribute__((packed)) ContextStateFrame_t {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
} ContextStateFrame_t;

void DEBUG_PrintFault(ContextStateFrame_t *context, unsigned which)
{
    switch (which) {
        case 0: DEBUG_PrintString("\n\n***** HARD FAULT *****\n"); break;
        case 1: DEBUG_PrintString("\n\n***** MM FAULT *****\n"); break;
        case 2: DEBUG_PrintString("\n\n***** BUS FAULT *****\n"); break;
        case 3: DEBUG_PrintString("\n\n***** USAGE FAULT *****\n"); break;
    }
    DEBUG_PrintString("ADDR="); DEBUG_PrintU32(context->pc); DEBUG_PrintChar('\n');
    DEBUG_PrintString("xPSR="); DEBUG_PrintU32(context->xpsr); DEBUG_PrintChar('\n');
    DEBUG_PrintString("R0="); DEBUG_PrintU32(context->r0); DEBUG_PrintChar('\n');
    DEBUG_PrintString("R1="); DEBUG_PrintU32(context->r1); DEBUG_PrintChar('\n');
    DEBUG_PrintString("R2="); DEBUG_PrintU32(context->r2); DEBUG_PrintChar('\n');
    DEBUG_PrintString("R3="); DEBUG_PrintU32(context->r3); DEBUG_PrintChar('\n');
    DEBUG_PrintString("R12="); DEBUG_PrintU32(context->r12); DEBUG_PrintChar('\n');
    DEBUG_PrintString("LR="); DEBUG_PrintU32(context->lr); DEBUG_PrintChar('\n');
    DEBUG_PrintString("CFSR="); DEBUG_PrintU32(SCB->CFSR); DEBUG_PrintChar('\n');
    DEBUG_PrintString("HFSR="); DEBUG_PrintU32(SCB->HFSR); DEBUG_PrintChar('\n');
    DEBUG_PrintString("AFSR="); DEBUG_PrintU32(SCB->AFSR); DEBUG_PrintChar('\n');
    DEBUG_PrintString("BFAR="); DEBUG_PrintU32(SCB->BFAR); DEBUG_PrintChar('\n');
    for(;;);
}
