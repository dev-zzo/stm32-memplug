#include "mem_handler.h"
#include <stm32f1xx.h>
#include "debug.h"
#include "usb_device.h"

void LED_Activity(char state);

MMC_HandleTypeDef uSdHandle;

HAL_StatusTypeDef MMC_Setup(void)
{
    HAL_StatusTypeDef Status;

    /* uSD device interface configuration */
    uSdHandle.Instance = SDIO;

    uSdHandle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
    uSdHandle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
    uSdHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
    uSdHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
    uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    uSdHandle.Init.ClockDiv            = SDIO_TRANSFER_CLK_DIV;

    Status = HAL_MMC_Init(&uSdHandle);
    if (Status != HAL_OK) {
        DEBUG_PrintString("MMC init failed: "); DEBUG_PrintU32(Status); DEBUG_PrintChar('\n');
        return Status;
    }

#if 0
    Status = HAL_MMC_ConfigWideBusOperation(&uSdHandle, SDIO_BUS_WIDE_1B);
    if (Status != HAL_OK) {
        DEBUG_PrintString("MMC bus width setting failed\n");
        return Status;
    }
#endif

    return HAL_OK;
}

int SDCardWriteSect(uint8_t* bufferOut, uint32_t sector, uint16_t count)
{
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = HAL_MMC_WriteBlocks(&uSdHandle, bufferOut, sector, count, 0xFFFF);
    LED_Activity(0);
    return status == HAL_OK;
}

int SDCardReadSect(uint8_t* bufferOut, uint32_t sector, uint16_t count)
{
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = HAL_MMC_ReadBlocks(&uSdHandle, bufferOut, sector, count, 0xFFFF);
    LED_Activity(0);
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

