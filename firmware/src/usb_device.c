/**
  ******************************************************************************
  * @file           : USB_DEVICE
  * @brief          : This file implements the USB Device
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "debug.h"
#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage_if.h"
#include "mem_handler.h"

#define BULK_EPIN_ADDR 0x81
#define BULK_EPOUT_ADDR 0x01

#define BULK_PACKET_SIZE 64

typedef struct USBD_ClassContext {
    uint8_t BufferPointer;
    uint16_t BufferCount;
    const MD_CmdHanderEntry_t *Commands;
    MD_CmdHandler_t Handler;
    USBD_TransferCompletion_t ReadingCallback;
    USBD_TransferCompletion_t WritingCallback;
} USBD_ClassContext_t;

/* USB Device Core handle declaration */
USBD_HandleTypeDef hUsbDeviceFS;
USBD_ClassContext_t Context;
uint32_t ParamsStatusBuffer[16];

uint8_t USBD_ClassInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
    /* Configure endpoints */
    USBD_LL_OpenEP(pdev, BULK_EPOUT_ADDR, USBD_EP_TYPE_BULK, BULK_PACKET_SIZE);
    USBD_LL_OpenEP(pdev, BULK_EPIN_ADDR,  USBD_EP_TYPE_BULK, BULK_PACKET_SIZE);
    /* Setup our context */
    pdev->pClassData = &Context;
    return 0;
}

void USBD_RegisterCommands(const MD_CmdHanderEntry_t *cmds)
{
    Context.Commands = cmds;
}

uint8_t USBD_ClassDeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
    USBD_LL_CloseEP(pdev, BULK_EPOUT_ADDR);
    USBD_LL_CloseEP(pdev, BULK_EPIN_ADDR);
    return 0;
}

static uint8_t USBD_HandleRequest(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
    USBD_ClassContext_t *ctx = (USBD_ClassContext_t *)pdev->pClassData;
    const MD_CmdHanderEntry_t *Entry = ctx->Commands;
    if (Entry) {
        /* Walk the table; an all-zero entry is the sentinel */
        for (; Entry->Handler; Entry++) {
            if (Entry->CommandID != req->bRequest || Entry->ParamsLength != req->wLength)
                continue;

            if (Entry->ParamsLength) {
                /* Set up the params reception */
                ctx->Handler = Entry->Handler;
                USBD_CtlPrepareRx(pdev, (uint8_t *)&ParamsStatusBuffer[0], Entry->ParamsLength);

            } else {
                /* Fire the handler as is */
                if (Entry->Handler() != MEM_OK) {
                    USBD_CtlError(pdev, req);
                    return USBD_FAIL;
                }
            }
            return USBD_OK;
        }
        DEBUG_PrintString("No handler for CMD"); DEBUG_PrintU8(req->bRequest); DEBUG_PrintChar('\n');
    } else {
        DEBUG_PrintString("No command handlers reg'd!\n");
    }
    /* All class requests should be handled, so fail if unknown one */
    USBD_CtlError(pdev, req);
    return USBD_FAIL;
}

uint8_t USBD_ClassSetup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
    if ((req->bmRequest & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_CLASS) {
        switch (req->bRequest) {
        case 0:
            /* Read back the operation status */
            USBD_CtlSendData(pdev, (uint8_t *)&ParamsStatusBuffer[0], MIN(req->wLength, sizeof(ParamsStatusBuffer)));
            return USBD_OK;

        case 1:
            /* Clear error condition */
            USBD_LL_ClearStallEP(pdev, BULK_EPOUT_ADDR);
            USBD_LL_ClearStallEP(pdev, BULK_EPIN_ADDR);
            return USBD_OK;

        default:
            /* Hand over to the specific driver */
            return USBD_HandleRequest(pdev, req);
        }
    }
    USBD_CtlError(pdev, req);
    return USBD_FAIL;
}

/**
  * @brief  Handle device-to-host control transfer completion
  * @param  pdev: device instance
  * @retval status
  */
uint8_t USBD_ClassCtlTxSent(USBD_HandleTypeDef *pdev)
{
    /* Currently unused */
    return 0;
}

/**
  * @brief  Handle host-to-device control transfer completion
  * @param  pdev: device instance
  * @retval status
  */
uint8_t USBD_ClassCtlRxReady(USBD_HandleTypeDef *pdev)
{
    USBD_ClassContext_t *ctx = (USBD_ClassContext_t *)pdev->pClassData;
    if (ctx->Handler() != MEM_OK) {
        USBD_CtlError(pdev, NULL);
        return USBD_FAIL;
    }
    return USBD_OK;
}

/**
  * @brief  Prepare data to be sent over the bulk IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
void USBD_SetupReading(void *buffer, unsigned count, USBD_TransferCompletion_t callback)
{
    USBD_ClassContext_t *ctx = (USBD_ClassContext_t *)hUsbDeviceFS.pClassData;
    ctx->ReadingCallback = callback;
    USBD_LL_Transmit(&hUsbDeviceFS, BULK_EPIN_ADDR, buffer, count);
}

/**
  * @brief  Handle transfer completion via a non-control IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t USBD_ClassDataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
    USBD_ClassContext_t *ctx = (USBD_ClassContext_t *)pdev->pClassData;
    USBD_TransferCompletion_t callback = ctx->ReadingCallback;
    ctx->ReadingCallback = NULL;
    if (callback) {
        callback();
    }
    return 0;
}

/**
  * @brief  Prepare data to be sent over the bulk IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
void USBD_SetupWriting(void *buffer, unsigned count, USBD_TransferCompletion_t callback)
{
    USBD_ClassContext_t *ctx = (USBD_ClassContext_t *)hUsbDeviceFS.pClassData;
    ctx->WritingCallback = callback;
    USBD_LL_PrepareReceive(&hUsbDeviceFS, BULK_EPOUT_ADDR, buffer, count);
}

/**
  * @brief  Handle transfer completion via a non-control OUT endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t USBD_ClassDataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
    USBD_ClassContext_t *ctx = (USBD_ClassContext_t *)pdev->pClassData;
    USBD_TransferCompletion_t callback = ctx->WritingCallback;
    ctx->WritingCallback = NULL;
    if (callback) {
        callback();
    }
    return 0;
}

void USBD_StallOperation(void)
{
    USBD_LL_StallEP(&hUsbDeviceFS, BULK_EPIN_ADDR);
    USBD_LL_StallEP(&hUsbDeviceFS, BULK_EPOUT_ADDR);
}

/* USB Mass storage device Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
uint8_t USBD_ClassCfgFSDesc[32]  __ALIGN_END =
{
    0x09,   /* bLength: Configuation Descriptor size */
    USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
    32,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    0x04,   /* iConfiguration: */
    0xC0,   /* bmAttributes: */
    0x32,   /* MaxPower 100 mA */

    /******************** Interface ********************/
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0xFF,   /* bInterfaceClass: Vendor-specific */
    0xFF,   /* bInterfaceSubClass: Vendor-specific */
    0x00,   /* nInterfaceProtocol */
    0x05,   /* iInterface */
    /********************  Endpoints ********************/
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    BULK_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    BULK_PACKET_SIZE,   /*Max packet*/
    0x00,
    0x00,   /*Polling interval in milliseconds */

    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    BULK_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
    0x02,   /*Bulk endpoint type */
    BULK_PACKET_SIZE,   /*Max packet*/
    0x00,
    0x00     /*Polling interval in milliseconds*/
};

__ALIGN_BEGIN uint8_t USBD_ClassOtherSpeedCfgDesc[32]   __ALIGN_END  =
{
    0x09,   /* bLength: Configuation Descriptor size */
    USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,
    32,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    0x04,   /* iConfiguration: */
    0xC0,   /* bmAttributes: */
    0x32,   /* MaxPower 100 mA */

    /******************** Interface ********************/
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x00,   /* bNumEndpoints*/
    0xFF,   /* bInterfaceClass: Vendor-specific */
    0xFF,   /* bInterfaceSubClass: Vendor-specific */
    0x00,   /* nInterfaceProtocol */
    0x05,   /* iInterface */
    /********************  Endpoints ********************/
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    BULK_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    BULK_PACKET_SIZE,   /*Max packet*/
    0x00,
    0x00,   /*Polling interval in milliseconds */

    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    BULK_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
    0x02,   /*Bulk endpoint type */
    BULK_PACKET_SIZE,   /*Max packet*/
    0x00,
    0x00     /*Polling interval in milliseconds*/
};

uint8_t *USBD_ClassGetHSCfgDesc(uint16_t *length)
{
    *length = sizeof (USBD_ClassCfgFSDesc);
    return USBD_ClassCfgFSDesc;
}

uint8_t *USBD_ClassGetFSCfgDesc(uint16_t *length)
{
    *length = sizeof (USBD_ClassCfgFSDesc);
    return USBD_ClassCfgFSDesc;
}

uint8_t *USBD_ClassGetOtherSpeedCfgDesc(uint16_t *length)
{
    *length = sizeof (USBD_ClassOtherSpeedCfgDesc);
    return USBD_ClassOtherSpeedCfgDesc;
}

USBD_ClassTypeDef USBD_CustomClass = {
    USBD_ClassInit,
    USBD_ClassDeInit,
    USBD_ClassSetup,
    USBD_ClassCtlTxSent,
    USBD_ClassCtlRxReady,
    USBD_ClassDataIn, /*DataIn*/
    USBD_ClassDataOut, /*DataOut*/
    NULL, /*SOF */
    NULL,
    NULL,
    USBD_ClassGetHSCfgDesc,
    USBD_ClassGetFSCfgDesc,
    USBD_ClassGetOtherSpeedCfgDesc,
    NULL,
};

/* init function */
void MX_USB_DEVICE_Init(int do_msc)
{
    /* Init Device Library */
    USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);

    /* The following depends on the mode we're initializing in */
    if (do_msc) {
        USBD_RegisterClass(&hUsbDeviceFS, &USBD_MSC);
        USBD_MSC_RegisterStorage(&hUsbDeviceFS, &USBD_Storage_Interface_fops_FS);
    } else {
        USBD_RegisterClass(&hUsbDeviceFS, &USBD_CustomClass);
    }

    USBD_Start(&hUsbDeviceFS);
}
