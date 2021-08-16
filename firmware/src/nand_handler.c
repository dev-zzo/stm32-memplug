#include "mem_handler.h"
#include <stm32f1xx.h>
#include "debug.h"
#include "usb_device.h"

void LED_Activity(char state);

static NAND_HandleTypeDef Handle;

HAL_StatusTypeDef NAND_Setup(void)
{
    /* TODO */
    return HAL_OK;
}

const MD_CmdHanderEntry_t NAND_Handlers[] = {
    {0}, /* Sentinel */
};
