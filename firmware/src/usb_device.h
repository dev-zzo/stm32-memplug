/**
  ******************************************************************************
  * @file           : USB_DEVICE
  * @version        : v2.0_Cube
  * @brief          : Header for usb_device file.
  ******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usb_device_H
#define __usb_device_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "usbd_def.h"
#include "mem_handler.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
extern uint32_t ParamsStatusBuffer[16];

/* USB_Device init function */	
void MX_USB_DEVICE_Init(void);

void USBD_SetProduct(uint16_t pid, const char *product);

void USBD_RegisterCommands(const MD_CmdHanderEntry_t *cmds);

typedef void (*USBD_TransferCompletion_t)(void);

void USBD_SetupReading(void *buffer, unsigned count, USBD_TransferCompletion_t callback);
void USBD_SetupWriting(void *buffer, unsigned count, USBD_TransferCompletion_t callback);
void USBD_StallOperation(void);

#ifdef __cplusplus
}
#endif
#endif /*__usb_device_H */
