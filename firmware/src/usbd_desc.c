/**
  ******************************************************************************
  * @file           : usbd_desc.c
  * @brief          : This file implements the USB Device descriptors
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"

#define USBD_VID                        0x0483
#define USBD_LANGID_STRING              1033
#define USBD_MANUFACTURER_STRING        "@InfoSecDJ"

#define USBD_PID_FS                     0x5720
#define USBD_PRODUCT_STRING_FS          "STM32-MemPlug"
#define USBD_CONFIGURATION_STRING_FS    "MSC Config"
#define USBD_INTERFACE_STRING_FS        "MSC Interface"

uint8_t *     USBD_FS_DeviceDescriptor( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_LangIDStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_ManufacturerStrDescriptor ( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_ProductStrDescriptor ( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_SerialStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_ConfigStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_InterfaceStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length);

#ifdef USB_SUPPORT_USER_STRING_DESC
uint8_t *     USBD_FS_USRStringDesc (USBD_SpeedTypeDef speed, uint8_t idx , uint16_t *length);
#endif /* USB_SUPPORT_USER_STRING_DESC */

USBD_DescriptorsTypeDef FS_Desc =
{
    USBD_FS_DeviceDescriptor,
    USBD_FS_LangIDStrDescriptor,
    USBD_FS_ManufacturerStrDescriptor,
    USBD_FS_ProductStrDescriptor,
    USBD_FS_SerialStrDescriptor,
    USBD_FS_ConfigStrDescriptor,
    USBD_FS_InterfaceStrDescriptor,
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
  {
    0x12,                       /*bLength*/
    USB_DESC_TYPE_DEVICE,       /*bDescriptorType*/
    0x00, 0x02,                 /*bcdUSB*/
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    USB_MAX_EP0_SIZE,           /*bMaxPacketSize*/
    LOBYTE(USBD_VID),           /*idVendor*/
    HIBYTE(USBD_VID),           /*idVendor*/
    LOBYTE(USBD_PID_FS),        /*idProduct*/
    HIBYTE(USBD_PID_FS),        /*idProduct*/
    0x00, 0x02,                 /*bcdDevice rel. 2.00*/
    USBD_IDX_MFC_STR,           /*Index of manufacturer string*/
    USBD_IDX_PRODUCT_STR,       /*Index of product string*/
    USBD_IDX_SERIAL_STR,        /*Index of serial number string*/
    USBD_MAX_NUM_CONFIGURATION  /*bNumConfigurations*/
  } ;
/* USB_DeviceDescriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif

/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END =
{
    USB_LEN_LANGID_STR_DESC,
    USB_DESC_TYPE_STRING,
    LOBYTE(USBD_LANGID_STRING),
    HIBYTE(USBD_LANGID_STRING),
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

static const char *USBD_ProductDesc;

void USBD_SetProduct(uint16_t pid, const char *product)
{
    USBD_FS_DeviceDesc[10] = LOBYTE(pid);
    USBD_FS_DeviceDesc[11] = HIBYTE(pid);
    USBD_ProductDesc = product;
}

/**
* @brief  USBD_FS_DeviceDescriptor
*         return the device descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_DeviceDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
  *length = sizeof(USBD_FS_DeviceDesc);
  return USBD_FS_DeviceDesc;
}

/**
* @brief  USBD_FS_LangIDStrDescriptor
*         return the LangID string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_LangIDStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
  *length =  sizeof(USBD_LangIDDesc);
  return USBD_LangIDDesc;
}

/**
* @brief  USBD_FS_ProductStrDescriptor
*         return the product string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_ProductStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
  if(speed == 0)
  {
    USBD_GetString ((const uint8_t *)USBD_ProductDesc, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString ((const uint8_t *)USBD_ProductDesc, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
* @brief  USBD_FS_ManufacturerStrDescriptor
*         return the manufacturer string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_ManufacturerStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
    USBD_GetString ((const uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
    return USBD_StrDesc;
}


static void u32_to_hex(uint32_t value, char *buf)
{
    static const char map[16] = "0123456789ABCDEF";
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    value >>= 4;
    *buf++ = map[value & 0xF];
    *buf = '\0';
}

/**
* @brief  USBD_FS_SerialStrDescriptor
*         return the serial number string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_SerialStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
    char buffer[34];
    u32_to_hex(HAL_GetUIDw0(), &buffer[0*8]);
    u32_to_hex(HAL_GetUIDw1(), &buffer[1*8]);
    u32_to_hex(HAL_GetUIDw2(), &buffer[2*8]);
    USBD_GetString ((uint8_t *)buffer, USBD_StrDesc, length);
    return USBD_StrDesc;
}

/**
* @brief  USBD_FS_ConfigStrDescriptor
*         return the configuration string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_ConfigStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
  if(speed  == USBD_SPEED_HIGH)
  {
    USBD_GetString ((const uint8_t *)USBD_CONFIGURATION_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString ((const uint8_t *)USBD_CONFIGURATION_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
* @brief  USBD_HS_InterfaceStrDescriptor
*         return the interface string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *  USBD_FS_InterfaceStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
  if(speed == 0)
  {
    USBD_GetString ((const uint8_t *)USBD_INTERFACE_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString ((const uint8_t *)USBD_INTERFACE_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}
