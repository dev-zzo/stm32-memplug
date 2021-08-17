#include "mem_handler.h"
#include <stm32f1xx.h>
#include "debug.h"
#include "usb_device.h"
#include "nor_driver.h"

void LED_Activity(char state);

static NOR_Handle_t Handle;

HAL_StatusTypeDef NOR_Setup(void)
{
    HAL_StatusTypeDef status;
    FSMC_NORSRAM_InitTypeDef Init;
    FSMC_NORSRAM_TimingTypeDef Timing;

    Handle.Device = FSMC_NORSRAM_DEVICE;
    Handle.ExtDevice = FSMC_NORSRAM_EXTENDED_DEVICE;

    /* Use the slowest timing */
	Timing.AddressSetupTime = 7;
	Timing.AddressHoldTime = 1;
	Timing.DataSetupTime = 6;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 0;
	Timing.DataLatency = 0;
	Timing.AccessMode = FSMC_ACCESS_MODE_B;

    Init.NSBank               = FSMC_NORSRAM_BANK1;
    Init.DataAddressMux       = FSMC_DATA_ADDRESS_MUX_DISABLE;
    Init.MemoryType           = FSMC_MEMORY_TYPE_NOR;
    Init.MemoryDataWidth      = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    Init.BurstAccessMode      = FSMC_BURST_ACCESS_MODE_DISABLE;
    Init.WaitSignal           = FSMC_WAIT_SIGNAL_DISABLE;
    Init.WaitSignalPolarity   = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    Init.WaitSignalActive     = FSMC_WAIT_TIMING_BEFORE_WS;
    Init.WrapMode             = FSMC_WRAP_MODE_DISABLE;
    Init.WriteOperation       = FSMC_WRITE_OPERATION_ENABLE; /* MUST BE ENABLED */
    Init.ExtendedMode         = FSMC_EXTENDED_MODE_DISABLE; /* CHECK */
    Init.AsynchronousWait     = FSMC_ASYNCHRONOUS_WAIT_ENABLE;
    Init.WriteBurst           = FSMC_WRITE_BURST_DISABLE;
    Init.PageSize             = FSMC_PAGE_SIZE_NONE; /* CHECK */

    status = NOR_Init(&Handle, &Init, &Timing, &Timing);
    if (status != HAL_OK) {
        DEBUG_PrintString("NOR init failed\n");
    }
    return status;
}


static uint8_t NOR_ReadID_Handler(void)
{
    HAL_StatusTypeDef status;
    status = NOR_ReadID(&Handle, (NOR_IDTypeDef *)&PageBuffer[0]);
    if (status != HAL_OK) {
        DEBUG_PrintString("NOR read id failed\n");
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], 8, NULL);
    return MEM_OK;
}


static uint8_t NOR_ReadCFI_Handler(void)
{
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = NOR_ReadCFI(&Handle, 0, (uint16_t *)&PageBuffer[0], 128);
    for (int i = 0; i < 128; ++i) {
        PageBuffer[i] = PageBuffer[2*i];
    }
    LED_Activity(0);
    if (status != HAL_OK) {
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], 128, NULL);
    return MEM_OK;
}


typedef struct NOR_ReadAutoSelect_Params {
    uint32_t Address;
    uint32_t Count;
} NOR_ReadAutoSelect_Params;

static uint8_t NOR_ReadAutoSelect_Handler(void)
{
    const NOR_ReadAutoSelect_Params *params = (const NOR_ReadAutoSelect_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef status;
    LED_Activity(1);
    status = NOR_ReadAutoSelect(&Handle, params->Address, (uint16_t *)&PageBuffer[0], params->Count / 2);
    LED_Activity(0);
    if (status != HAL_OK) {
        return MEM_FAIL;
    }

    USBD_SetupReading(&PageBuffer[0], params->Count, NULL);
    return MEM_OK;
}


typedef struct NOR_ReadStreamed_Params {
    uint32_t Address;
    uint32_t Count;
} NOR_ReadStreamed_Params;

static uint8_t NOR_ReadStreamed_Handler(void)
{
    const NOR_ReadStreamed_Params *params = (const NOR_ReadStreamed_Params *)&ParamsStatusBuffer[0];
    /* Dummy read operation */
    NOR_ReadData(&Handle, params->Address, (uint16_t *)&PageBuffer[0]);
    /* Since NOR is memory-mapped, provide the buffer pointer directly */
    uint8_t *mmio = (uint8_t *)Handle.BankBase;
    USBD_SetupReading(&mmio[params->Address], params->Count, NULL);
    return MEM_OK;
}


typedef struct NOR_BlankCheck_Params {
    uint32_t Address;
    uint32_t Count;
} NOR_BlankCheck_Params;

typedef struct NOR_BlankCheck_Status {
    uint32_t Status;
    uint32_t Address;
    uint32_t Value;
} NOR_BlankCheck_Status;

static uint8_t NOR_BlankCheck_Handler(void)
{
    const NOR_BlankCheck_Params *params = (const NOR_BlankCheck_Params *)&ParamsStatusBuffer[0];
    NOR_BlankCheck_Status *status = (NOR_BlankCheck_Status *)&ParamsStatusBuffer[0];
    uint16_t Temp;
    uint32_t Limit = params->Address + params->Count;
    for (uint32_t Address = params->Address; Address < Limit; Address += 2) {
        NOR_ReadData(&Handle, params->Address, &Temp);
        if (Temp != 0xFFFFU) {
            status->Status = 1;
            status->Address = Address;
            status->Value = Temp;
            return MEM_FAIL;
        }
    }
    return MEM_OK;
}


typedef struct NOR_EraseBlock_Params {
    uint32_t Address;
    uint32_t TimeoutMs;
} NOR_EraseBlock_Params;

static uint8_t NOR_EraseBlock_Handler(void)
{
    const NOR_EraseBlock_Params *params = (const NOR_EraseBlock_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    LED_Activity(1);
    op_status = NOR_EraseBlock(&Handle, params->Address);
    if (op_status != HAL_OK) {
        LED_Activity(0);
        return MEM_FAIL;
    }
    HAL_NOR_StatusTypeDef status = NOR_GetStatus(&Handle, params->Address, params->TimeoutMs);
    LED_Activity(0);
    switch (status) {
        case HAL_NOR_STATUS_SUCCESS:
            return MEM_OK;
        case HAL_NOR_STATUS_ONGOING: /* should not occur, really */
        case HAL_NOR_STATUS_TIMEOUT:
            DEBUG_PrintString("EraseBlock: timed out\n");
            return MEM_TIMEOUT;
        case HAL_NOR_STATUS_ERROR:
            DEBUG_PrintString("EraseBlock: failed\n");
            return MEM_FAIL;
    }
    return MEM_OK;
}


typedef struct NOR_EraseChip_Params {
    uint32_t TimeoutMs;
} NOR_EraseChip_Params;

static uint8_t NOR_EraseChip_Handler(void)
{
    const NOR_EraseChip_Params *params = (const NOR_EraseChip_Params *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    LED_Activity(1);
    op_status = NOR_EraseChip(&Handle);
    if (op_status != HAL_OK) {
        LED_Activity(0);
        return MEM_FAIL;
    }
    HAL_NOR_StatusTypeDef status = NOR_GetStatus(&Handle, 0, params->TimeoutMs);
    LED_Activity(0);
    switch (status) {
        case HAL_NOR_STATUS_SUCCESS:
            return MEM_OK;
        case HAL_NOR_STATUS_ONGOING: /* should not occur, really */
        case HAL_NOR_STATUS_TIMEOUT:
            DEBUG_PrintString("EraseChip: timed out\n");
            return MEM_TIMEOUT;
        case HAL_NOR_STATUS_ERROR:
            DEBUG_PrintString("EraseChip: failed\n");
            return MEM_FAIL;
    }
    return MEM_OK;
}


typedef struct NOR_ProgramStreamed_Params {
    uint32_t Address;
    uint32_t Count;
    uint32_t BufferSize;
} NOR_ProgramStreamed_Params;

typedef struct NOR_ProgramStreamed_Status {
    uint32_t Status;
    uint32_t Address;
} NOR_ProgramStreamed_Status;

#define NOR_PROGRAM_TIMEOUT 10

static void NOR_ProgramStreamedCallback(void)
{
    NOR_ProgramStreamed_Params *params = (NOR_ProgramStreamed_Params *)&ParamsStatusBuffer[0];
    NOR_ProgramStreamed_Status *status = (NOR_ProgramStreamed_Status *)&ParamsStatusBuffer[0];
    HAL_StatusTypeDef op_status;
    HAL_NOR_StatusTypeDef wait_status;
    DEBUG_PrintString("ProgramStreamedCallback enter\n");
    LED_Activity(1);
    unsigned count = MIN(params->Count, PAGE_BUFFER_SIZE);
    if (params->BufferSize) {
        /* Buffered programming is available; make use of it */
        for (unsigned i = 0; i < count; i += params->BufferSize) {
            uint32_t address = params->Address + i;
            uint32_t bytes = MIN(params->BufferSize, count - i);
            op_status = NOR_ProgramBuffer(&Handle, address, (uint16_t *)&PageBuffer[i], bytes / 2);
            if (op_status != HAL_OK) {
                status->Address = address;
                status->Status = MEM_FAIL;
                DEBUG_PrintString("ProgramBuffer failed\n");
                break;
            }
            wait_status = NOR_GetStatus(&Handle, params->Address, NOR_PROGRAM_TIMEOUT);
            if (wait_status != HAL_NOR_STATUS_SUCCESS) {
                status->Address = address;
                status->Status = MEM_TIMEOUT;
                DEBUG_PrintString("ProgramBuffer timed out\n");
                break;
            }
        }
    } else {
        /* Program each word separately */
        for (unsigned i = 0; i < count; i += 2) {
            uint32_t address = params->Address + i;
            op_status = NOR_ProgramData(&Handle, address, *(uint16_t *)&PageBuffer[i]);
            if (op_status != HAL_OK) {
                status->Address = address;
                status->Status = MEM_FAIL;
                DEBUG_PrintString("Program failed\n");
                break;
            }
            wait_status = NOR_GetStatus(&Handle, address, NOR_PROGRAM_TIMEOUT);
            if (wait_status != HAL_NOR_STATUS_SUCCESS) {
                status->Address = address;
                status->Status = MEM_TIMEOUT;
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
        } else {
            /* For the last block, we can't report the error condition if any */
            status->Status = MEM_OK;
        }
    } else {
        /* Stall and report back */
        USBD_StallOperation();
    }
    DEBUG_PrintString("ProgramStreamedCallback exit\n");
}

static uint8_t NOR_ProgramStreamed_Handler(void)
{
    const NOR_ProgramStreamed_Params *params = (const NOR_ProgramStreamed_Params *)&ParamsStatusBuffer[0];
    USBD_SetupWriting(&PageBuffer[0], MIN(params->Count, PAGE_BUFFER_SIZE), NOR_ProgramStreamedCallback);
    return MEM_OK;
}


const MD_CmdHanderEntry_t NOR_Handlers[] = {
    { 0x10, 0, NOR_ReadID_Handler },
    { 0x11, 0, NOR_ReadCFI_Handler },
    { 0x12, sizeof(NOR_ReadAutoSelect_Params), NOR_ReadAutoSelect_Handler },
    { 0x20, sizeof(NOR_ReadStreamed_Params), NOR_ReadStreamed_Handler },
    { 0x21, sizeof(NOR_BlankCheck_Params), NOR_BlankCheck_Handler },
    { 0x30, sizeof(NOR_EraseBlock_Params), NOR_EraseBlock_Handler },
    { 0x31, sizeof(NOR_EraseChip_Params), NOR_EraseChip_Handler },
    { 0x40, sizeof(NOR_ProgramStreamed_Params), NOR_ProgramStreamed_Handler },
    {0}, /* Sentinel */
};
