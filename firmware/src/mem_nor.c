#include "mem_driver.h"
#include <stm32f1xx.h>
#include "debug.h"
#include "usb_device.h"

#define NOR_BANK_ADDR NOR_MEMORY_ADRESS1

void LED_Activity(char state);

static NOR_HandleTypeDef Handle;

HAL_StatusTypeDef NOR_Setup(void)
{
    HAL_StatusTypeDef status;
    FSMC_NORSRAM_TimingTypeDef Timing;

    Handle.Instance = FSMC_NORSRAM_DEVICE;
    Handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

    /* Use the slowest timing */
	Timing.AddressSetupTime = 7;
	Timing.AddressHoldTime = 1;
	Timing.DataSetupTime = 6;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 0;
	Timing.DataLatency = 0;
	Timing.AccessMode = FSMC_ACCESS_MODE_B;

    Handle.Init.NSBank               = FSMC_NORSRAM_BANK1;
    Handle.Init.DataAddressMux       = FSMC_DATA_ADDRESS_MUX_DISABLE;
    Handle.Init.MemoryType           = FSMC_MEMORY_TYPE_NOR;
    Handle.Init.MemoryDataWidth      = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    Handle.Init.BurstAccessMode      = FSMC_BURST_ACCESS_MODE_DISABLE;
    Handle.Init.WaitSignal           = FSMC_WAIT_SIGNAL_DISABLE;
    Handle.Init.WaitSignalPolarity   = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    Handle.Init.WaitSignalActive     = FSMC_WAIT_TIMING_BEFORE_WS;
    Handle.Init.WrapMode             = FSMC_WRAP_MODE_DISABLE;
    Handle.Init.WriteOperation       = FSMC_WRITE_OPERATION_ENABLE; /* MUST BE ENABLED */
    Handle.Init.ExtendedMode         = FSMC_EXTENDED_MODE_DISABLE; /* CHECK */
    Handle.Init.AsynchronousWait     = FSMC_ASYNCHRONOUS_WAIT_ENABLE;
    Handle.Init.WriteBurst           = FSMC_WRITE_BURST_DISABLE;
    Handle.Init.PageSize             = FSMC_PAGE_SIZE_NONE; /* CHECK */

    status = HAL_NOR_Init(&Handle, &Timing, &Timing);
    if (status != HAL_OK) {
        DEBUG_PrintString("NOR init failed\n");
    }
    return status;
}


static uint8_t NOR_ReadID(void)
{
    HAL_StatusTypeDef status;
    status = HAL_NOR_Read_ID(&Handle, (NOR_IDTypeDef *)&PageBuffer[0]);
    HAL_NOR_ReturnToReadMode(&Handle);
    if (status != HAL_OK) {
        DEBUG_PrintString("NOR read id failed\n");
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], 8, NULL);
    return MEM_OK;
}


static uint8_t NOR_ReadCFI(void)
{
    HAL_StatusTypeDef status;
    LED_Activity(1);
    /* Honestly, reading CFI data with HAL is bonkers */
    status = HAL_NOR_Read_CFI(&Handle, (NOR_CFITypeDef *)&PageBuffer[0]);
    uint16_t *mmio = (uint16_t *)NOR_BANK_ADDR;
    for (int i = 0; i < 128; ++i) {
        PageBuffer[i] = mmio[i];
    }
    HAL_NOR_ReturnToReadMode(&Handle);
    LED_Activity(0);
    if (status != HAL_OK) {
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], 128, NULL);
    return MEM_OK;
}


typedef struct NOR_ReadStreamed_Params {
    uint32_t Address;
    uint32_t Count;
} NOR_ReadStreamed_Params;

static uint8_t NOR_ReadStreamed(void)
{
    const NOR_ReadStreamed_Params *_params = (const NOR_ReadStreamed_Params *)&ParamsStatusBuffer[0];
    HAL_NOR_ReturnToReadMode(&Handle);
    uint8_t *mmio = (uint8_t *)NOR_BANK_ADDR;
    USBD_SetupReading(&mmio[_params->Address], _params->Count, NULL);
    return MEM_OK;
}


typedef struct NOR_EraseBlock_Params {
    uint32_t Address;
    uint32_t TimeoutMs;
} NOR_EraseBlock_Params;

static uint8_t NOR_EraseBlock(void)
{
    const NOR_EraseBlock_Params *_params = (const NOR_EraseBlock_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    LED_Activity(1);
    op_status = HAL_NOR_Erase_Block(&Handle, _params->Address, NOR_BANK_ADDR);
    if (op_status != HAL_OK) {
        LED_Activity(0);
        return MEM_FAIL;
    }
    HAL_NOR_StatusTypeDef status = HAL_NOR_GetStatus(&Handle, NOR_BANK_ADDR + _params->Address, _params->TimeoutMs);
    LED_Activity(0);
    if (status != HAL_NOR_STATUS_SUCCESS) {
        DEBUG_PrintString("NOR_EraseBlock: timed out\n");
        return MEM_TIMEOUT;
    }
    return MEM_OK;
}


typedef struct NOR_EraseChip_Params {
    uint32_t TimeoutMs;
} NOR_EraseChip_Params;

static uint8_t NOR_EraseChip(void)
{
    const NOR_EraseChip_Params *_params = (const NOR_EraseChip_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    LED_Activity(1);
    op_status = HAL_NOR_Erase_Chip(&Handle, NOR_BANK_ADDR);
    if (op_status != HAL_OK) {
        LED_Activity(0);
        return MEM_FAIL;
    }
    HAL_NOR_StatusTypeDef status = HAL_NOR_GetStatus(&Handle, NOR_BANK_ADDR, _params->TimeoutMs);
    LED_Activity(0);
    if (status != HAL_NOR_STATUS_SUCCESS) {
        DEBUG_PrintString("NOR_EraseChip: timed out\n");
        return MEM_TIMEOUT;
    }
    return MEM_OK;
}


typedef struct NOR_ProgramStreamed_Params {
    uint32_t Address;
    uint32_t Count;
    uint32_t BufferSize;
} NOR_ProgramStreamed_Params;

typedef struct NOR_ProgramStreamed_Status {
    uint32_t Address;
    uint32_t Error;
} NOR_ProgramStreamed_Status;

#define NOR_PROGRAM_TIMEOUT 10

static void NOR_ProgramStreamedCallback(void)
{
    NOR_ProgramStreamed_Params *params = (NOR_ProgramStreamed_Params *)&ParamsStatusBuffer[0];
    NOR_ProgramStreamed_Status *status = (NOR_ProgramStreamed_Status *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    HAL_NOR_StatusTypeDef wait_status;
    LED_Activity(1);
    unsigned count = MIN(params->Count, PAGE_BUFFER_SIZE);
    if (params->BufferSize) {
        /* Buffered programming is available; make use of it */
        for (unsigned i = 0; i < count; i += params->BufferSize) {
            uint32_t address = params->Address + i;
            uint32_t bytes = MIN(params->BufferSize, count - i);
            op_status = HAL_NOR_ProgramBuffer(&Handle,
                address,
                (uint16_t *)&PageBuffer[i],
                bytes / 2);
            if (op_status != HAL_OK) {
                status->Address = address;
                status->Error = MEM_FAIL;
                DEBUG_PrintString("ProgramBuffer failed\n");
                break;
            }
            wait_status = HAL_NOR_GetStatus(&Handle, NOR_BANK_ADDR + params->Address, NOR_PROGRAM_TIMEOUT);
            if (wait_status != HAL_NOR_STATUS_SUCCESS) {
                status->Address = address;
                status->Error = MEM_TIMEOUT;
                DEBUG_PrintString("ProgramBuffer timed out\n");
                break;
            }
        }
    } else {
        /* Program each word separately */
        for (unsigned i = 0; i < count; i += 2) {
            uint32_t address = NOR_BANK_ADDR + params->Address + i;
            op_status = HAL_NOR_Program(&Handle,
                (uint32_t *)address,
                (uint16_t *)&PageBuffer[i]);
            if (op_status != HAL_OK) {
                status->Address = address;
                status->Error = MEM_FAIL;
                DEBUG_PrintString("Program failed\n");
                break;
            }
            wait_status = HAL_NOR_GetStatus(&Handle, address, NOR_PROGRAM_TIMEOUT);
            if (wait_status != HAL_NOR_STATUS_SUCCESS) {
                status->Address = address;
                status->Error = MEM_TIMEOUT;
                DEBUG_PrintString("Program timed out\n");
                break;
            }
        }
    }
    LED_Activity(0);

    if (op_status == HAL_OK && wait_status == HAL_NOR_STATUS_SUCCESS) {
        /* Set up the next transfer */
        params->Address += count;
        if (params->Count > PAGE_BUFFER_SIZE) {
            params->Count -= PAGE_BUFFER_SIZE;
            USBD_SetupWriting(&PageBuffer[0], MIN(params->Count, PAGE_BUFFER_SIZE), NOR_ProgramStreamedCallback);
        }
    } else {
        /* Stall and report back */
        USBD_StallOperation();
    }
}

static uint8_t NOR_ProgramStreamed(void)
{
    const NOR_ProgramStreamed_Params *params = (const NOR_ProgramStreamed_Params *)&ParamsStatusBuffer[0];
    USBD_SetupWriting(&PageBuffer[0], MIN(params->Count, PAGE_BUFFER_SIZE), NOR_ProgramStreamedCallback);
    return MEM_OK;
}


const MD_CmdHanderEntry_t NOR_Handlers[] = {
    { 0x10, 0, NOR_ReadID },
    { 0x11, 0, NOR_ReadCFI },
    { 0x20, sizeof(NOR_ReadStreamed_Params), NOR_ReadStreamed },
    { 0x30, sizeof(NOR_EraseBlock_Params), NOR_EraseBlock },
    { 0x31, sizeof(NOR_EraseChip_Params), NOR_EraseChip },
    { 0x40, sizeof(NOR_ProgramStreamed_Params), NOR_ProgramStreamed },
    {0}, /* Sentinel */
};
