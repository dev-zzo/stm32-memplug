#include "mem_handler.h"
#include <stm32f1xx.h>
#include "debug.h"
#include "usb_device.h"

void LED_Activity(char state);

MMC_HandleTypeDef Handle;

HAL_StatusTypeDef MMC_Setup(void)
{
    HAL_StatusTypeDef Status;

    /* uSD device interface configuration */
    Handle.Instance = SDIO;

    Handle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
    Handle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
    Handle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
    Handle.Init.BusWide             = SDIO_BUS_WIDE_1B;
    Handle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    Handle.Init.ClockDiv            = SDIO_TRANSFER_CLK_DIV;

    Status = HAL_MMC_Init(&Handle);
    if (Status != HAL_OK) {
        DEBUG_PrintString("MMC init failed: "); DEBUG_PrintU32(Status); DEBUG_PrintChar('\n');
        return Status;
    }
    DEBUG_PrintString("MMC init OK\n");

#if 0
    Status = HAL_MMC_ConfigWideBusOperation(&Handle, SDIO_BUS_WIDE_1B);
    if (Status != HAL_OK) {
        DEBUG_PrintString("MMC bus width setting failed\n");
        return Status;
    }
#endif

    DEBUG_PrintString("CID: ");
    DEBUG_PrintU32(Handle.CID[0]);
    DEBUG_PrintChar(' ');
    DEBUG_PrintU32(Handle.CID[1]);
    DEBUG_PrintChar(' ');
    DEBUG_PrintU32(Handle.CID[2]);
    DEBUG_PrintChar(' ');
    DEBUG_PrintU32(Handle.CID[3]);
    DEBUG_PrintChar('\n');

    DEBUG_PrintString("CSD: ");
    DEBUG_PrintU32(Handle.CSD[0]);
    DEBUG_PrintChar(' ');
    DEBUG_PrintU32(Handle.CSD[1]);
    DEBUG_PrintChar(' ');
    DEBUG_PrintU32(Handle.CSD[2]);
    DEBUG_PrintChar(' ');
    DEBUG_PrintU32(Handle.CSD[3]);
    DEBUG_PrintChar('\n');

    return HAL_OK;
}

int SDCardWriteSect(uint8_t* bufferOut, uint32_t sector, uint16_t count)
{
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = HAL_MMC_WriteBlocks(&Handle, bufferOut, sector, count, 0xFFFF);
    LED_Activity(0);
    return status == HAL_OK;
}

int SDCardReadSect(uint8_t* bufferOut, uint32_t sector, uint16_t count)
{
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = HAL_MMC_ReadBlocks(&Handle, bufferOut, sector, count, 0xFFFF);
    LED_Activity(0);
    return status == HAL_OK;
}

uint32_t SDCardSectorCount()
{
    HAL_MMC_CardInfoTypeDef info;
    if (HAL_OK == HAL_MMC_GetCardInfo(&Handle, &info)) {
        DEBUG_PrintString("Card size from GetCardInfo: ");
        DEBUG_PrintU32(info.LogBlockNbr);
        DEBUG_PrintChar('\n');
        return info.LogBlockNbr;
    }
    return 0;
}

