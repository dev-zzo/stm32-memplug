#include "mem_handler.h"
#include "nand_driver.h"
#include "debug.h"
#include "usb_device.h"

void LED_Activity(char state);

static NAND_Handle_t Handle;

HAL_StatusTypeDef NAND_Setup(void)
{
    FSMC_NAND_InitTypeDef Init;
    FSMC_NAND_PCC_TimingTypeDef Timing;

    Handle.Device = FSMC_NAND_DEVICE;

    Timing.SetupTime     = 1;
    Timing.WaitSetupTime = 3;
    Timing.HoldSetupTime = 2;
    Timing.HiZSetupTime  = 1;

    Init.NandBank        = FSMC_NAND_BANK2;
    Init.Waitfeature     = FSMC_NAND_PCC_WAIT_FEATURE_ENABLE;
    Init.MemoryDataWidth = FSMC_NAND_PCC_MEM_BUS_WIDTH_8; /* Should be switchable */
    Init.EccComputation  = FSMC_NAND_ECC_DISABLE;
    Init.ECCPageSize     = FSMC_NAND_ECC_PAGE_SIZE_512BYTE;
    Init.TCLRSetupTime   = 1;
    Init.TARSetupTime    = 1;

    Handle.RowAddressSize = 3;
    Handle.ColAddressSize = 2;

    if (NAND_Init(&Handle, &Init, &Timing, &Timing) != HAL_OK) {
        DEBUG_PrintString("NAND init failed\n");
        return HAL_ERROR;
    }

    NAND_Reset(&Handle);

    uint8_t id[6];
    NAND_ReadID(&Handle, id, 6);
    DEBUG_PrintString("Device ID: ");
    DEBUG_PrintHex(&id, 6);
    DEBUG_PrintChar('\n');

    return HAL_OK;
}


static uint8_t NAND_ReadID_Handler(void)
{
    HAL_StatusTypeDef status;
    status = NAND_ReadID(&Handle, &PageBuffer[0], 6);
    if (status != HAL_OK) {
        DEBUG_PrintString("NAND read id failed\n");
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], 6, NULL);
    return MEM_OK;
}


static uint8_t NAND_ReadONFI_Handler(void)
{
    HAL_StatusTypeDef status;
    status = NAND_ReadONFI(&Handle, &PageBuffer[0]);
    if (status != HAL_OK) {
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], 256, NULL);
    return MEM_OK;
}


typedef struct NAND_ReadPageStreamed_Params {
    uint32_t RowAddress;
    uint16_t PageSize;
    uint16_t Count;
} NAND_ReadPageStreamed_Params;

static void NAND_ReadPageStreamedCallback(void)
{
    NAND_ReadPageStreamed_Params *params = (NAND_ReadPageStreamed_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = NAND_ReadPage(&Handle, params->RowAddress, &PageBuffer[0], params->PageSize);
    LED_Activity(0);
    if (status == HAL_OK) {
        if (params->Count) {
            USBD_SetupReading(&PageBuffer[0], params->PageSize, NAND_ReadPageStreamedCallback);
            params->RowAddress++;
            params->Count--;
        } else {
            USBD_SetupReading(&PageBuffer[0], params->PageSize, NULL);
        }
    } else {
    }
}

static uint8_t NAND_ReadPageStreamed_Handler(void)
{
    NAND_ReadPageStreamedCallback();
    return MEM_OK;
}


typedef struct NAND_EraseBlock_Params {
    uint32_t RowAddress;
    uint32_t TimeoutMs;
} NAND_EraseBlock_Params;

static uint8_t NAND_EraseBlock_Handler(void)
{
    NAND_EraseBlock_Params *params = (NAND_EraseBlock_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = NAND_EraseBlock(&Handle, params->RowAddress);
    if (status != HAL_OK) {
        LED_Activity(0);
        return MEM_FAIL;
    }
    unsigned op_status = NAND_GetStatus(&Handle, params->TimeoutMs);
    LED_Activity(0);
    switch (op_status) {
        case NAND_READY:
            return MEM_OK;
        case NAND_TIMEOUT_ERROR:
            DEBUG_PrintString("EraseBlock: timed out\n");
            return MEM_TIMEOUT;
        case NAND_ERROR:
            DEBUG_PrintString("EraseBlock: failed\n");
            return MEM_FAIL;
    }
    return MEM_OK;
}


typedef struct NAND_ProgramPageStreamed_Params {
    uint32_t RowAddress;
    uint16_t PageSize;
    uint16_t Count;
    uint32_t TimeoutMs;
} NAND_ProgramPageStreamed_Params;

typedef struct NAND_ProgramPageStreamed_Status {
    uint32_t Status;
    uint32_t RowAddress;
} NAND_ProgramPageStreamed_Status;

static void NAND_ProgramPageStreamedCallback(void)
{
    NAND_ProgramPageStreamed_Params *params = (NAND_ProgramPageStreamed_Params *)&ParamsStatusBuffer[0];
    NAND_ProgramPageStreamed_Status *status = (NAND_ProgramPageStreamed_Status *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    LED_Activity(1);
    op_status = NAND_ProgramPage(&Handle, params->RowAddress, &PageBuffer[0], params->PageSize);
    if (op_status != HAL_OK) {
        LED_Activity(0);
        status->RowAddress = params->RowAddress;
        status->Status = MEM_FAIL;
        DEBUG_PrintString("ProgramPage: failed\n");
        return;
    }
    unsigned wait_status = NAND_GetStatus(&Handle, 60000);
    LED_Activity(0);
    switch (wait_status) {
        case NAND_TIMEOUT_ERROR:
            status->RowAddress = params->RowAddress;
            status->Status = MEM_TIMEOUT;
            DEBUG_PrintString("ProgramPage: timed out\n");
            break;
        case NAND_ERROR:
            status->RowAddress = params->RowAddress;
            status->Status = MEM_FAIL;
            DEBUG_PrintString("ProgramPage: failed\n");
            break;
        case NAND_READY:
            params->Count--;
            if (params->Count) {
                USBD_SetupWriting(&PageBuffer[0], params->PageSize, NAND_ProgramPageStreamedCallback);
                params->RowAddress++;
            } else {
                status->Status = MEM_OK;
            }
            break;
    }
}

static uint8_t NAND_ProgramPageStreamed_Handler(void)
{
    NAND_ProgramPageStreamed_Params *params = (NAND_ProgramPageStreamed_Params *)&ParamsStatusBuffer[0];
    USBD_SetupWriting(&PageBuffer[0], params->PageSize, NAND_ProgramPageStreamedCallback);
    return MEM_OK;
}

const MD_CmdHanderEntry_t NAND_Handlers[] = {
    { 0x10, 0, NAND_ReadID_Handler },
    { 0x11, 0, NAND_ReadONFI_Handler },
    { 0x20, sizeof(NAND_ReadPageStreamed_Params), NAND_ReadPageStreamed_Handler },
    { 0x30, sizeof(NAND_EraseBlock_Params), NAND_EraseBlock_Handler },
    { 0x40, sizeof(NAND_ProgramPageStreamed_Params), NAND_ProgramPageStreamed_Handler },
    {0}, /* Sentinel */
};
