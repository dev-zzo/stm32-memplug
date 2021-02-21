#include <stm32f1xx.h>
#include "debug.h"
#include "usb_device.h"

MMC_HandleTypeDef uSdHandle; 
extern PCD_HandleTypeDef hpcd_USB_FS;

void led_activity(int state)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void HAL_MMC_MspInit(MMC_HandleTypeDef* hsd)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    __SDIO_CLK_ENABLE();

    /**SDIO GPIO Configuration   
    PB9     ------> SDIO_D5
    PB8     ------> SDIO_D4
    PC12    ------> SDIO_CK
    PC11    ------> SDIO_D3
    PC10    ------> SDIO_D2
    PC9     ------> SDIO_D1
    PC8     ------> SDIO_D0
    PC7     ------> SDIO_D7
    PC6     ------> SDIO_D6
    PD2     ------> SDIO_CMD
    */
    
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

int MMC_Init(void)
{ 
    /* uSD device interface configuration */
    uSdHandle.Instance = SDIO;
    uSdHandle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
    uSdHandle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
    uSdHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
    uSdHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
    uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    uSdHandle.Init.ClockDiv            = SDIO_TRANSFER_CLK_DIV;

    if(HAL_MMC_Init(&uSdHandle) != HAL_OK) {
        DEBUG_PrintString("MMC init failed\n");
        return 0;
    }

#if 0
    if(HAL_MMC_ConfigWideBusOperation(&uSdHandle, SDIO_BUS_WIDE_1B) != HAL_OK) {
        DEBUG_PrintString("MMC bus width setting failed\n");
        return 0;
    }
#endif

    return 1;
} 

static void setup(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_SDIO_CLK_ENABLE();
    
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    led_activity(0);
    
    DEBUG_Init();
    
    if (!MMC_Init()) {
        /* What do we want to report here and how? */
    }
}

void SystemClock_Config(void)
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
    clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
    if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK) {
        /* Initialization Error */
        while(1);
    }
} 

int SDCardWriteSect(uint8_t* bufferOut, uint32_t sector, uint16_t count)
{
    HAL_StatusTypeDef status;
    led_activity(1);
    status = HAL_MMC_WriteBlocks(&uSdHandle, bufferOut, sector, count, 0xFFFF);
    led_activity(0);
    return status == HAL_OK;
}

int SDCardReadSect(uint8_t* bufferOut, uint32_t sector, uint16_t count)
{
    HAL_StatusTypeDef status;
    led_activity(1);
    status = HAL_MMC_ReadBlocks(&uSdHandle, bufferOut, sector, count, 0xFFFF);
    led_activity(0);
    return status == HAL_OK;
}

uint32_t SDCardSectorCount()
{
    HAL_MMC_CardInfoTypeDef info;
    if (HAL_OK == HAL_MMC_GetCardInfo(&uSdHandle, &info)) {
        return info.LogBlockNbr;
    }
    return 0;
}

void *memset(void *dst, int c, size_t n)
{
    uint8_t *p = (uint8_t *)dst;
    while (n--) {
        *p++ = c;
    }
    return dst;
}

static void hexdump(const uint8_t *buffer, unsigned count)
{
    while (count--) {
        DEBUG_PrintU8(*buffer++);
    }
    DEBUG_PrintChar('\n');
}

int main()
{
    HAL_MMC_CardInfoTypeDef info;
    
    HAL_Init();
    SystemClock_Config();
    setup();
    MX_USB_DEVICE_Init();
    
    HAL_MMC_GetCardInfo(&uSdHandle, &info);
    DEBUG_PrintString("Card capacity: "); DEBUG_PrintU32(info.LogBlockNbr); DEBUG_PrintChar('\n');
    
    //DEBUG_PrintString("\n\nThat's all folks!\n\n");
    for (;;) {
    }
}
