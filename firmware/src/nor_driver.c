#include "nor_driver.h"
#include "debug.h"

#define DEBUG_ME 0

#define NOR_BANK_BASE_1 0x60000000U
#define NOR_BANK_BASE_2 0x64000000U
#define NOR_BANK_BASE_3 0x68000000U
#define NOR_BANK_BASE_4 0x6C000000U

/* CFI defines */
#define NOR_CFI_COMMAND_SET_OFFSET  0x0013U

#define NOR_INTEL_SHARP_EXT_COMMAND_SET       (uint16_t)0x0001 /* Supported in this driver */
#define NOR_AMD_FUJITSU_COMMAND_SET           (uint16_t)0x0002 /* Supported in this driver */
#define NOR_INTEL_STANDARD_COMMAND_SET        (uint16_t)0x0003 /* Not Supported in this driver */
#define NOR_AMD_FUJITSU_EXT_COMMAND_SET       (uint16_t)0x0004 /* Not Supported in this driver */
#define NOR_WINDBOND_STANDARD_COMMAND_SET     (uint16_t)0x0006 /* Not Supported in this driver */
#define NOR_MITSUBISHI_STANDARD_COMMAND_SET   (uint16_t)0x0100 /* Not Supported in this driver */
#define NOR_MITSUBISHI_EXT_COMMAND_SET        (uint16_t)0x0101 /* Not Supported in this driver */
#define NOR_PAGE_WRITE_COMMAND_SET            (uint16_t)0x0102 /* Not Supported in this driver */
#define NOR_INTEL_PERFORMANCE_COMMAND_SET     (uint16_t)0x0200 /* Not Supported in this driver */
#define NOR_INTEL_DATA_COMMAND_SET            (uint16_t)0x0210 /* Not Supported in this driver */

/* Auto select defines */
#define NOR_AUTO_SELECT_MANUFACTURER 0x0000U
#define NOR_AUTO_SELECT_DEVICE_1    0x0001U
#define NOR_AUTO_SELECT_DEVICE_2    0x000EU
#define NOR_AUTO_SELECT_DEVICE_3    0x000FU

/* Helper function implementations ---------------------------------------- */

static inline uintptr_t NOR_AdjustAddress(NOR_Handle_t *Handle, uintptr_t Address)
{
    if (Handle->BusWidth == FSMC_NORSRAM_MEM_BUS_WIDTH_16)
        Address <<= 1;
    return Address;
}

static inline void NOR_WriteWord(NOR_Handle_t *Handle, uintptr_t Address, uint16_t Data)
{
    __IO uint16_t *Addr = (__IO uint16_t *)(Handle->BankBase + Address);
    *Addr = Data;
    __DSB();
#if DEBUG_ME
    DEBUG_PrintChar('W');
    DEBUG_PrintU32((uint32_t)Addr);
    DEBUG_PrintChar(':');
    DEBUG_PrintU16(Data);
    DEBUG_PrintChar('\n');
#endif
}

static inline void NOR_WriteWordAdj(NOR_Handle_t *Handle, uintptr_t Address, uint16_t Data)
{
    NOR_WriteWord(Handle, NOR_AdjustAddress(Handle, Address), Data);
}

static inline uint16_t NOR_ReadWordAdj(NOR_Handle_t *Handle, uintptr_t Address)
{
    __IO uint16_t *Addr = (__IO uint16_t *)(Handle->BankBase + NOR_AdjustAddress(Handle, Address));
    return *Addr;
}

/* NOR Command implementations */

static void NOR_Execute_ReadCFI(NOR_Handle_t *Handle)
{
#if DEBUG_ME
    DEBUG_PrintString("ReadCFI\n");
#endif
    NOR_WriteWordAdj(Handle, 0x0055U, 0x98U);
}

static void NOR_Execute_Unlock_0002(NOR_Handle_t *Handle)
{
#if DEBUG_ME
    DEBUG_PrintString("Unlock\n");
#endif
    NOR_WriteWordAdj(Handle, 0x0555U, 0xAAU);
    NOR_WriteWordAdj(Handle, 0x02AAU, 0x55U);
}

static void NOR_Execute_Reset_0002(NOR_Handle_t *Handle)
{
#if DEBUG_ME
    DEBUG_PrintString("Reset\n");
#endif
    NOR_WriteWordAdj(Handle, 0x0000U, 0xF0U);
}

static void NOR_Execute_AutoSelect_0002(NOR_Handle_t *Handle)
{
    NOR_Execute_Unlock_0002(Handle);
#if DEBUG_ME
    DEBUG_PrintString("AutoSelect\n");
#endif
    NOR_WriteWordAdj(Handle, 0x0555U, 0x90U);
}

static void NOR_Execute_Program_0002(NOR_Handle_t *Handle, uint32_t Address, uint16_t Data)
{
    NOR_Execute_Unlock_0002(Handle);
#if DEBUG_ME
    DEBUG_PrintString("Program:");
    DEBUG_PrintU32(Address);
    DEBUG_PrintChar(':');
    DEBUG_PrintU16(Data);
    DEBUG_PrintChar('\n');
#endif
    NOR_WriteWordAdj(Handle, 0x0555U, 0xA0U);
    __IO uint16_t *p = (__IO uint16_t *)(Handle->BankBase + Address);
    *p = Data;
    __DSB();
}

static void NOR_Execute_ProgramBuffer_0002(NOR_Handle_t *Handle, uint32_t Address, const uint16_t *Data, uint32_t WordCount)
{
    NOR_Execute_Unlock_0002(Handle);
#if DEBUG_ME
    DEBUG_PrintString("ProgramBuffer:");
    DEBUG_PrintU32(Address);
    DEBUG_PrintChar(':');
    DEBUG_PrintU32((uint32_t)Data);
    DEBUG_PrintChar(':');
    DEBUG_PrintU32(WordCount);
    DEBUG_PrintChar('\n');
#endif
    NOR_WriteWord(Handle, Address, 0x25U);
    NOR_WriteWord(Handle, Address, WordCount-1);
    __IO uint16_t *p = (__IO uint16_t *)(Handle->BankBase + Address);
    while (WordCount--) {
        *p++ = *Data++;
        __DSB();
    }
    NOR_WriteWord(Handle, Address, 0x29U);
}

static void NOR_Execute_EraseBlock_0002(NOR_Handle_t *Handle, uint32_t Address)
{
    NOR_Execute_Unlock_0002(Handle);
#if DEBUG_ME
    DEBUG_PrintString("EraseBlock\n");
#endif
    NOR_WriteWordAdj(Handle, 0x0555U, 0x80U);
    NOR_Execute_Unlock_0002(Handle);
    NOR_WriteWord(Handle, Address, 0x30U);
}

static void NOR_Execute_EraseChip_0002(NOR_Handle_t *Handle)
{
    NOR_Execute_Unlock_0002(Handle);
#if DEBUG_ME
    DEBUG_PrintString("EraseChip\n");
#endif
    NOR_WriteWordAdj(Handle, 0x0555U, 0x80U);
    NOR_Execute_Unlock_0002(Handle);
    NOR_WriteWordAdj(Handle, 0x0555U, 0x10U);
}

static HAL_NOR_StatusTypeDef NOR_Execute_GetStatus_0002(NOR_Handle_t *Handle, uint32_t Address)
{
    __IO uint16_t *p = (__IO uint16_t *)(Handle->BankBase + Address);
    uint16_t status1 = *p;
    uint16_t status2 = *p;
    if (((status1 ^ status2) & (1 << 6)) == 0) {
        return HAL_NOR_STATUS_SUCCESS;
    }
    if (((status2 & (1 << 5)) == 0) && ((status2 & (1 << 1)) == 0)) {
        return HAL_NOR_STATUS_ONGOING;
    }
    uint16_t status3 = *p;
    uint16_t status4 = *p;
    if (((status3 ^ status4) & (1 << 6)) == 0) {
        return HAL_NOR_STATUS_SUCCESS;
    }
    NOR_Execute_Reset_0002(Handle);
    return HAL_NOR_STATUS_ERROR;
}

static const NOR_CommandSet_t NOR_CommandSet_0002 = {
    NOR_Execute_Reset_0002,
    NOR_Execute_AutoSelect_0002,
    NOR_Execute_Program_0002,
    NOR_Execute_ProgramBuffer_0002,
    NOR_Execute_EraseBlock_0002,
    NOR_Execute_EraseChip_0002,
    NOR_Execute_GetStatus_0002
};

/* NOR API implementations ------------------------------------------------ */

HAL_StatusTypeDef NOR_Init(
    NOR_Handle_t *Handle,
    FSMC_NORSRAM_InitTypeDef *Init,
    FSMC_NORSRAM_TimingTypeDef *Timing,
    FSMC_NORSRAM_TimingTypeDef *ExtTiming)
{
    /* Call MCU-dependent init routine */
    NOR_MspInit(Handle);

    /* Initialize the NOR control interface */
    FSMC_NORSRAM_Init(Handle->Device, Init);
    FSMC_NORSRAM_Timing_Init(Handle->Device, Timing, Init->NSBank);
    FSMC_NORSRAM_Extended_Timing_Init(Handle->ExtDevice, ExtTiming, Init->NSBank, Init->ExtendedMode);
    __FSMC_NORSRAM_ENABLE(Handle->Device, Init->NSBank);

    Handle->BusWidth = Init->MemoryDataWidth;

    /* Figure out the bank base address and stash it */
    switch (Init->NSBank) {
        case FSMC_NORSRAM_BANK1: Handle->BankBase = NOR_BANK_BASE_1; break;
        case FSMC_NORSRAM_BANK2: Handle->BankBase = NOR_BANK_BASE_2; break;
        case FSMC_NORSRAM_BANK3: Handle->BankBase = NOR_BANK_BASE_3; break;
        case FSMC_NORSRAM_BANK4: Handle->BankBase = NOR_BANK_BASE_4; break;
        default: return HAL_ERROR;
    }

    /* Figure out which command set it is */
    NOR_Execute_ReadCFI(Handle);
    uint16_t CommandSetID = NOR_ReadWordAdj(Handle, NOR_CFI_COMMAND_SET_OFFSET);
    switch (CommandSetID) {
        case NOR_AMD_FUJITSU_COMMAND_SET:
            Handle->CommandSet = &NOR_CommandSet_0002;
            break;

        default:
            /* Report an error */
            DEBUG_PrintString("Unknown command set: ");
            DEBUG_PrintU16(CommandSetID);
            DEBUG_PrintChar('\n');
            return HAL_ERROR;
    }

    /* Return to array read mode and be done */
    Handle->CommandSet->Reset(Handle);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ReadID(NOR_Handle_t *Handle, NOR_IDTypeDef *Data)
{
    Handle->CommandSet->AutoSelect(Handle);
    Data->Manufacturer_Code = NOR_ReadWordAdj(Handle, NOR_AUTO_SELECT_MANUFACTURER);
    Data->Device_Code1      = NOR_ReadWordAdj(Handle, NOR_AUTO_SELECT_DEVICE_1);
    Data->Device_Code2      = NOR_ReadWordAdj(Handle, NOR_AUTO_SELECT_DEVICE_2);
    Data->Device_Code3      = NOR_ReadWordAdj(Handle, NOR_AUTO_SELECT_DEVICE_3);
    Handle->CommandSet->Reset(Handle);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ReadCFI(NOR_Handle_t *Handle, uint32_t Offset, uint16_t *Data, uint32_t WordCount)
{
    NOR_Execute_ReadCFI(Handle);
    __IO uint16_t *p = (__IO uint16_t *)(Handle->BankBase + Offset);
    while (WordCount--) {
        *Data++ = *p++;
    }
    Handle->CommandSet->Reset(Handle);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ReadAutoSelect(NOR_Handle_t *Handle, uint32_t Offset, uint16_t *Data, uint32_t WordCount)
{
    Handle->CommandSet->AutoSelect(Handle);
    __IO uint16_t *p = (__IO uint16_t *)(Handle->BankBase + Offset);
    while (WordCount--) {
        *Data++ = *p++;
    }
    Handle->CommandSet->Reset(Handle);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ReadData(NOR_Handle_t *Handle, uint32_t Address, uint16_t *Data)
{
    Handle->CommandSet->Reset(Handle);
    *Data = *(__IO uint16_t *)(Handle->BankBase + Address);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ProgramData(NOR_Handle_t *Handle, uint32_t Address, uint16_t Data)
{
    Handle->CommandSet->Program(Handle, Address, Data);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ReadBuffer(NOR_Handle_t *Handle, uint32_t Address, uint16_t *Data, uint32_t WordCount)
{
    Handle->CommandSet->Reset(Handle);
    __IO uint16_t *p = (__IO uint16_t *)(Handle->BankBase + Address);
    while (WordCount--) {
        *Data++ = *p++;
    }
    return HAL_OK;
}

HAL_StatusTypeDef NOR_ProgramBuffer(NOR_Handle_t *Handle, uint32_t Address, const uint16_t *Data, uint32_t WordCount)
{
    Handle->CommandSet->ProgramBuffer(Handle, Address, Data, WordCount);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_EraseBlock(NOR_Handle_t *Handle, uint32_t Address)
{
    Handle->CommandSet->EraseBlock(Handle, Address);
    return HAL_OK;
}

HAL_StatusTypeDef NOR_EraseChip(NOR_Handle_t *Handle)
{
    Handle->CommandSet->EraseChip(Handle);
    return HAL_OK;
}

HAL_NOR_StatusTypeDef NOR_GetStatus(NOR_Handle_t *Handle, uint32_t Address, uint32_t TimeoutMs)
{
    HAL_NOR_StatusTypeDef Status;
    uint32_t Start = HAL_GetTick();

    do {
        Status = Handle->CommandSet->GetStatus(Handle, Address);

        if (TimeoutMs != HAL_MAX_DELAY && Status != HAL_NOR_STATUS_ONGOING) {
            if ((HAL_GetTick() - Start) > TimeoutMs) {
                Status = HAL_NOR_STATUS_TIMEOUT;
            }
        }
    } while (Status == HAL_NOR_STATUS_ONGOING);

    return Status;
}
