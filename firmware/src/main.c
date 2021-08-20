#include <stm32f1xx.h>
#include <stm32f1xx_ll_utils.h>
#include "debug.h"
#include "usb_device.h"

HAL_StatusTypeDef MMC_Setup(void);
HAL_StatusTypeDef NOR_Setup(void);
HAL_StatusTypeDef NAND_Setup(void);

extern const MD_CmdHanderEntry_t NOR_Handlers[];
extern const MD_CmdHanderEntry_t NAND_Handlers[];

uint8_t PageBuffer[8192];

void LED_Activity(char state)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState        = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
    oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK) {
        /* Initialization Error */
        while(1);
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    clkinitstruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK) {
        /* Initialization Error */
        while(1);
    }
}

void *memset(void *dst, int c, size_t n)
{
    uint8_t *p = (uint8_t *)dst;
    while (n--) {
        *p++ = c;
    }
    return dst;
}

int main()
{
    /* Setup clocks */
    SystemClock_Config();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    /* Run through HAL init stuff */
    HAL_Init();
    __enable_irq();

    __HAL_RCC_AFIO_CLK_ENABLE();
    //__HAL_AFIO_REMAP_SWJ_NOJTAG();

    /* Init the debug prints */
#ifdef _DEBUG
    DEBUG_Init();
    DEBUG_PrintString("I'm alive\n");
#endif

    GPIO_InitTypeDef gpio;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /* Setup activity LED on PC13 */
    gpio.Pin = GPIO_PIN_13;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOC, &gpio);
    LED_Activity(0);

    /* Setup PA3..0 as inputs with pull-ups */
    gpio.Pin = GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &gpio);

    HAL_StatusTypeDef Status;
    int top_id =
          (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) << 3)
        | (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) << 2)
        | (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) << 1)
        | (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) << 0);
    DEBUG_PrintString("Top board ID: ");
    switch (top_id) {
    case 0x0:
        DEBUG_PrintString("eMMC rev A\n");
        USBD_SetProduct(0x5720, "STM32-MemPlug: eMMC");
        Status = MMC_Setup();
        break;
    case 0x1:
        DEBUG_PrintString("NAND rev A\n");
        USBD_SetProduct(0x5721, "STM32-MemPlug: NAND");
        Status = NAND_Setup();
        USBD_RegisterCommands(NAND_Handlers);
        break;
    case 0x3:
        DEBUG_PrintString("NOR rev A\n");
        USBD_SetProduct(0x5723, "STM32-MemPlug: NOR");
        Status = NOR_Setup();
        USBD_RegisterCommands(NOR_Handlers);
        break;
    default:
        DEBUG_PrintString("UNKNOWN: ");
        DEBUG_PrintChar('A' + top_id);
        DEBUG_PrintChar('\n');
        USBD_SetProduct(0x572F, "STM32-MemPlug: Unknown TOP");
        break;
    }

    MX_USB_DEVICE_Init(top_id == 0x0);

    for (;;) {
        __WFE();
    }
}

void __libc_init_array(void)
{
    /* Unused as we don't use libc */
}
