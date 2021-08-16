#ifndef __NOR_DRIVER_H
#define __NOR_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

struct NOR_CommandSet_t;

typedef struct NOR_Handle_t {
    FSMC_NORSRAM_TypeDef *Device;
    FSMC_NORSRAM_EXTENDED_TypeDef *ExtDevice;
    uintptr_t BankBase;
    uint8_t BusWidth;
    const struct NOR_CommandSet_t *CommandSet;
} NOR_Handle_t;

typedef struct NOR_CommandSet_t {
    void (*Reset)(NOR_Handle_t *Handle);
    void (*AutoSelect)(NOR_Handle_t *Handle);
    void (*Program)(NOR_Handle_t *Handle, uint32_t Address, uint16_t Data);
    void (*ProgramBuffer)(NOR_Handle_t *Handle, uint32_t Address, const uint16_t *Data, uint32_t WordCount);
    void (*EraseBlock)(NOR_Handle_t *Handle, uint32_t Address);
    void (*EraseChip)(NOR_Handle_t *Handle);
    HAL_NOR_StatusTypeDef (*GetStatus)(NOR_Handle_t *Handle, uint32_t Address);
} NOR_CommandSet_t;

void NOR_MspInit(NOR_Handle_t *Handle);

HAL_StatusTypeDef NOR_Init(
    NOR_Handle_t *Handle,
    FSMC_NORSRAM_InitTypeDef *Init,
    FSMC_NORSRAM_TimingTypeDef *Timing,
    FSMC_NORSRAM_TimingTypeDef *ExtTiming);

/**
  * @brief  Read ID words from NOR memory
  * @param  Handle Initialized module handle
  * @param  Data Buffer address
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ReadID(NOR_Handle_t *Handle, NOR_IDTypeDef *Data);

/**
  * @brief  Read CFI data from NOR memory
  * @param  Handle Initialized module handle
  * @param  Offset Byte offset in CFI address space, 0-based
  * @param  Data Buffer address
  * @param  WordCount How many data words (not bytes) to read
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ReadCFI(NOR_Handle_t *Handle, uint32_t Offset, uint16_t *Data, uint32_t WordCount);

/**
  * @brief  Read auto-select data from NOR memory
  * @param  Handle Initialized module handle
  * @param  Offset Byte offset in auto-select address space, 0-based
  * @param  Data Buffer address
  * @param  WordCount How many data words (not bytes) to read
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ReadAutoSelect(NOR_Handle_t *Handle, uint32_t Offset, uint16_t *Data, uint32_t WordCount);

/**
  * @brief  Read array data from NOR memory, single word version
  * @param  Handle Initialized module handle
  * @param  Address Byte address, 0-based
  * @param  Data Memory to store data read
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ReadData(NOR_Handle_t *Handle, uint32_t Address, uint16_t *Data);

/**
  * @brief  Program word data to NOR memory, single word version
  * @param  Handle Initialized module handle
  * @param  Address Byte address, 0-based
  * @param  Data Word data to write
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ProgramData(NOR_Handle_t *Handle, uint32_t Address, uint16_t Data);

/**
  * @brief  Read array data from NOR memory, buffer version
  * @param  Handle Initialized module handle
  * @param  Address Byte address, 0-based
  * @param  Data Buffer address
  * @param  WordCount How many data words (not bytes) to read
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ReadBuffer(NOR_Handle_t *Handle, uint32_t Address, uint16_t *Data, uint32_t WordCount);

/**
  * @brief  Program array data to NOR memory, buffer version
  * @param  Handle Initialized module handle
  * @param  Address Byte address, 0-based
  * @param  Data Buffer address
  * @param  WordCount How many data words (not bytes) to program
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_ProgramBuffer(NOR_Handle_t *Handle, uint32_t Address, const uint16_t *Data, uint32_t WordCount);

/**
  * @brief  Erase the given block/sector
  * @param  Handle Initialized module handle
  * @param  Address Byte address, 0-based, pointing to the desired block/sector
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_EraseBlock(NOR_Handle_t *Handle, uint32_t Address);

/**
  * @brief  Erase the whole chip
  * @param  Handle Initialized module handle
  * @retval HAL status
  */
HAL_StatusTypeDef NOR_EraseChip(NOR_Handle_t *Handle);

/**
  * @brief  Check the chip status
  * @param  Handle Initialized module handle
  * @param  Address Byte address, 0-based, pointing to the desired block/sector
  * @param  TimeoutMs Timeout for in-progress operations, in milliseconds
  * @retval HAL NOR status
  */
HAL_NOR_StatusTypeDef NOR_GetStatus(NOR_Handle_t *Handle, uint32_t Address, uint32_t TimeoutMs);

#ifdef __cplusplus
}
#endif
#endif /* __NOR_DRIVER_H */
