#include "nand_driver.h"
#include "debug.h"

extern void MEM_ControlRST(int state);

#define DEBUG_ME 0

#define USE_DMA 1

#if USE_DMA
DMA_HandleTypeDef DmaHandle;
#endif

/* Helper function implementations ---------------------------------------- */

static void NAND_WriteCommand(NAND_Handle_t *Handle, uint8_t Value)
{
    *(__IO uint8_t *)(Handle->BankBase + CMD_AREA) = Value;
    __DSB();
}

static void NAND_WriteAddress(NAND_Handle_t *Handle, uint8_t Value)
{
    *(__IO uint8_t *)(Handle->BankBase + ADDR_AREA) = Value;
    __DSB();
}

static uint8_t NAND_ReadByteData(NAND_Handle_t *Handle)
{
    return *(__IO uint8_t *)Handle->BankBase;
}

static void NAND_WriteByteData(NAND_Handle_t *Handle, uint8_t Value)
{
    *(__IO uint8_t *)Handle->BankBase = Value;
}

static uint16_t NAND_ReadWordData(NAND_Handle_t *Handle)
{
    return *(__IO uint16_t *)Handle->BankBase;
}

static void NAND_WriteWordData(NAND_Handle_t *Handle, uint16_t Value)
{
    *(__IO uint16_t *)Handle->BankBase = Value;
}

static void NAND_ReadBytes(NAND_Handle_t *Handle, uint8_t *Data, uint32_t Count)
{
    for (uint8_t *Limit = &Data[Count]; Data < Limit; Data++) {
        if (Handle->BusWidth == FSMC_NAND_PCC_MEM_BUS_WIDTH_8) {
            *Data = NAND_ReadByteData(Handle);
        } else {
            /* Data is output on the lower byte only */
            *Data = NAND_ReadWordData(Handle);
        }
    }
}

static void NAND_ReadData(NAND_Handle_t *Handle, void *Data, uint32_t Count)
{
    if (Handle->BusWidth == FSMC_NAND_PCC_MEM_BUS_WIDTH_8) {
#if USE_DMA
        HAL_DMA_Start(&DmaHandle, Handle->BankBase, (uint32_t)Data, Count);
        HAL_DMA_PollForTransfer(&DmaHandle, HAL_DMA_FULL_TRANSFER, 60000);
#else
        uint8_t *Ptr = (uint8_t *)Data;
        for (uint8_t *Limit = &Ptr[Count]; Ptr < Limit; Ptr++) {
            *Ptr = NAND_ReadByteData(Handle);
        }
#endif
    } else {
        uint16_t *Ptr = (uint16_t *)Data;
        for (uint16_t *Limit = &Ptr[(Count+1) >> 1]; Ptr < Limit; Ptr++) {
            *Ptr = NAND_ReadWordData(Handle);
        }
    }
}

static void NAND_WriteData(NAND_Handle_t *Handle, const void *Data, uint32_t Count)
{
    if (Handle->BusWidth == FSMC_NAND_PCC_MEM_BUS_WIDTH_8) {
        const uint8_t *Ptr = (const uint8_t *)Data;
        for (const uint8_t *Limit = &Ptr[Count]; Ptr < Limit; Ptr++) {
            NAND_WriteByteData(Handle, *Ptr);
        }
    } else {
        const uint16_t *Ptr = (const uint16_t *)Data;
        for (const uint16_t *Limit = &Ptr[(Count+1) >> 1]; Ptr < Limit; Ptr++) {
            NAND_WriteWordData(Handle, *Ptr);
        }
    }
}

static HAL_StatusTypeDef NAND_WriteRowAddress(NAND_Handle_t *Handle, uint32_t Address)
{
    switch (Handle->RowAddressSize) {
        case 3:
            NAND_WriteAddress(Handle, (uint8_t)Address);
            Address >>= 8;
        case 2:
            NAND_WriteAddress(Handle, (uint8_t)Address);
            Address >>= 8;
        case 1:
            NAND_WriteAddress(Handle, (uint8_t)Address);
            return HAL_OK;
        default:
            return HAL_ERROR;
    }
}

static HAL_StatusTypeDef NAND_WritePageAddress(NAND_Handle_t *Handle, uint32_t Address)
{
    switch (Handle->ColAddressSize) {
        case 2:
            NAND_WriteAddress(Handle, 0x00);
        case 1:
            NAND_WriteAddress(Handle, 0x00);
            break;
        default:
            return HAL_ERROR;
    }
    return NAND_WriteRowAddress(Handle, Address);
}

/* NAND API implementations ------------------------------------------------ */

HAL_StatusTypeDef NAND_Init(
    NAND_Handle_t *Handle,
    FSMC_NAND_InitTypeDef *Init,
    FSMC_NAND_PCC_TimingTypeDef *ComSpace_Timing,
    FSMC_NAND_PCC_TimingTypeDef *AttSpace_Timing)
{
    /* Call MCU-dependent init routine */
    NAND_MspInit(Handle);

    /* Initialize the NAND control interface */
    (void)FSMC_NAND_Init(Handle->Device, Init);
    (void)FSMC_NAND_CommonSpace_Timing_Init(Handle->Device, ComSpace_Timing, Init->NandBank);
    (void)FSMC_NAND_AttributeSpace_Timing_Init(Handle->Device, AttSpace_Timing, Init->NandBank);
    __FSMC_NAND_ENABLE(Handle->Device, Init->NandBank);

    /* Stash some parameters */
    switch (Init->NandBank) {
        case FSMC_NAND_BANK2: Handle->BankBase = NAND_DEVICE1; break;
        case FSMC_NAND_BANK3: Handle->BankBase = NAND_DEVICE2; break;
        default: return HAL_ERROR;
    }
    Handle->BusWidth = Init->MemoryDataWidth;

    MEM_ControlRST(0);

#if USE_DMA
    __HAL_RCC_DMA1_CLK_ENABLE();
    DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;
    DmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
    DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
    DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    DmaHandle.Init.Mode = DMA_NORMAL;
    DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;
    DmaHandle.Instance = DMA1_Channel1;
    if (HAL_DMA_Init(&DmaHandle) != HAL_OK) {
        DEBUG_PrintString("DMA init failed\n");
        return HAL_ERROR;
    }
#endif

    /* SIDE NOTE:
    Funnily enough, CLE and ALE are simply controlled via address lines?
    I wonder if this could be abused for other things.
    */

    /* TODO: Detect if this is x8 or x16 */

    return HAL_OK;
}

HAL_StatusTypeDef NAND_Reset(NAND_Handle_t *Handle)
{
    NAND_WriteCommand(Handle, 0xFF);
    NAND_ReadStatus(Handle);
    return HAL_OK;
}

HAL_StatusTypeDef NAND_ReadID(NAND_Handle_t *Handle, uint8_t *Data, uint16_t Size)
{
    NAND_WriteCommand(Handle, 0x90);
    NAND_WriteAddress(Handle, 0x00);
    NAND_ReadBytes(Handle, (uint8_t *)Data, Size);
    return HAL_OK;
}

HAL_StatusTypeDef NAND_ReadONFIMark(NAND_Handle_t *Handle, uint8_t *Data)
{
    NAND_WriteCommand(Handle, 0x90);
    NAND_WriteAddress(Handle, 0x20);
    NAND_ReadBytes(Handle, Data, 4);
    return HAL_OK;
}

HAL_StatusTypeDef NAND_ReadONFI(NAND_Handle_t *Handle, uint8_t *Data)
{
    NAND_WriteCommand(Handle, 0xEC);
    NAND_WriteAddress(Handle, 0x00);
    NAND_ReadBytes(Handle, Data, 256);
    return HAL_OK;
}

HAL_StatusTypeDef NAND_ReadPage(NAND_Handle_t *Handle, uint32_t RowAddress, uint8_t *Data, uint16_t PageSize)
{
    NAND_WriteCommand(Handle, 0x00);
    if (NAND_WritePageAddress(Handle, RowAddress) != HAL_OK) {
        return HAL_ERROR;
    }
    NAND_WriteCommand(Handle, 0x30);
    NAND_ReadData(Handle, Data, PageSize);
    return HAL_OK;
}

HAL_StatusTypeDef NAND_ProgramPage(NAND_Handle_t *Handle, uint32_t RowAddress, const uint8_t *Data, uint16_t PageSize)
{
    NAND_WriteCommand(Handle, 0x80);
    if (NAND_WritePageAddress(Handle, RowAddress) != HAL_OK) {
        return HAL_ERROR;
    }
    NAND_WriteData(Handle, Data, PageSize);
    NAND_WriteCommand(Handle, 0x10);
    return HAL_OK;
}

HAL_StatusTypeDef NAND_EraseBlock(NAND_Handle_t *Handle, uint32_t RowAddress)
{
    NAND_WriteCommand(Handle, 0x60);
    if (NAND_WriteRowAddress(Handle, RowAddress) != HAL_OK) {
        return HAL_ERROR;
    }
    NAND_WriteCommand(Handle, 0xD0);
    return HAL_OK;
}

unsigned NAND_ReadStatus(NAND_Handle_t *Handle)
{
    NAND_WriteCommand(Handle, 0x70);
    uint8_t Data = NAND_ReadByteData(Handle);
    if (Data & 0x03) {
        return NAND_ERROR;
    }
    if (Data & 0x40) {
        return NAND_READY;
    }
    return NAND_BUSY;
}

unsigned NAND_GetStatus(NAND_Handle_t *Handle, uint32_t TimeoutMs)
{
    unsigned Status;
    uint32_t Start = HAL_GetTick();

    do {
        Status = NAND_ReadStatus(Handle);
        if (TimeoutMs != HAL_MAX_DELAY && Status != NAND_BUSY) {
            if ((HAL_GetTick() - Start) > TimeoutMs) {
                Status = NAND_TIMEOUT_ERROR;
            }
        }
    } while (Status == NAND_BUSY);

    return Status;
}
