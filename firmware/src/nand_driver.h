#ifndef __NAND_DRIVER_H
#define __NAND_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>

typedef struct NAND_Handle_t {
    FSMC_NAND_TypeDef *Device;
    uintptr_t BankBase;
    uint8_t BusWidth;
    uint8_t RowAddressSize;
    uint8_t ColAddressSize;
} NAND_Handle_t;

void NAND_MspInit(NAND_Handle_t *Handle);

HAL_StatusTypeDef NAND_Init(
    NAND_Handle_t *Handle,
    FSMC_NAND_InitTypeDef *Init,
    FSMC_NAND_PCC_TimingTypeDef *ComSpace_Timing,
    FSMC_NAND_PCC_TimingTypeDef *AttSpace_Timing);
HAL_StatusTypeDef NAND_Reset(NAND_Handle_t *Handle);
HAL_StatusTypeDef NAND_ReadID(NAND_Handle_t *Handle, uint8_t *Data, uint16_t Size);
HAL_StatusTypeDef NAND_ReadONFI(NAND_Handle_t *Handle, uint8_t *Data);
HAL_StatusTypeDef NAND_ReadPage(NAND_Handle_t *Handle, uint32_t RowAddress, uint8_t *Data, uint16_t PageSize);
HAL_StatusTypeDef NAND_ProgramPage(NAND_Handle_t *Handle, uint32_t RowAddress, const uint8_t *Data, uint16_t PageSize);
HAL_StatusTypeDef NAND_EraseBlock(NAND_Handle_t *Handle, uint32_t RowAddress);
unsigned NAND_ReadStatus(NAND_Handle_t *Handle);
unsigned NAND_GetStatus(NAND_Handle_t *Handle, uint32_t TimeoutMs);

#ifdef __cplusplus
}
#endif
#endif /* __NAND_DRIVER_H */
