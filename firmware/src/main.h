/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stdbool.h"

int SDCardWriteSect(uint8_t* bufferOut, uint32_t sector, uint16_t count);
int SDCardReadSect(uint8_t* bufferOut, uint32_t sector, uint16_t count);
uint32_t SDCardSectorCount();

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
