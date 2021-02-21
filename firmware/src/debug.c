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
