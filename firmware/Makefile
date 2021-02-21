# Easy peasy make file for STM32 boards
# https://www.gnu.org/software/make/manual/make.html

#
# Application related shenanigans
#

# Application objects
APP_OBJS= \
    main.o \
    debug.o \
    stm32f1xx_it.o \
    usb_device.o \
    usbd_conf.o \
    usbd_desc.o \
    usbd_storage_if.o \
    usbd_msc.o \
    usbd_msc_bot.o \
    usbd_msc_data.o \
    usbd_msc_scsi.o \
    usbd_core.o \
    usbd_ctlreq.o \
    usbd_ioreq.o \

# The main dependency name
OUTPUT=project

#
# Build related shenanigans
#

# OS stuff
ifeq ($(OS),Windows_NT)
  RM=del
else
  RM=rm
endif

# Toolchain stuff; export CROSS_COMPILE to state your toolchain location/prefix
AR=$(CROSS_COMPILE)ar
AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
SIZE=$(CROSS_COMPILE)size
OBJCOPY=$(CROSS_COMPILE)objcopy

CFLAGS=-Wall -std=gnu99
CFLAGS+=-mthumb -mcpu=cortex-m3
CFLAGS+=-I./src -I./CMSIS/core -I./CMSIS/device -I./HAL_Driver/Inc -I./STM32_USB_Device_Library/Class/MSC/Inc -I./STM32_USB_Device_Library/Core/Inc
CFLAGS+=-DSTM32 -DSTM32F1 -DSTM32F103xE -DUSE_HAL_DRIVER
CFLAGS+=-Os -ffunction-sections
LDFLAGS+=-Tldscripts/STM32F103XE_FLASH.ld --gc-sections -Map $(OUTPUT).map
LIBGCC:=$(shell $(CC) $(CFLAGS) -print-libgcc-file-name)

# VPATH to support searching for CMSIS files
VPATH=./src:./HAL_Driver/Src:./STM32_USB_Device_Library/Class/MSC/Src:./STM32_USB_Device_Library/Core/Src

# CMSIS objects: startup code, system code, core support functions
PLAT_OBJS=system_stm32f1xx.o startup_stm32f103xe.o

HAL_OBJS= \
    stm32f1xx_hal.o \
    stm32f1xx_hal_adc.o \
    stm32f1xx_hal_adc_ex.o \
    stm32f1xx_hal_can.o \
    stm32f1xx_hal_cec.o \
    stm32f1xx_hal_cortex.o \
    stm32f1xx_hal_crc.o \
    stm32f1xx_hal_dac.o \
    stm32f1xx_hal_dac_ex.o \
    stm32f1xx_hal_dma.o \
    stm32f1xx_hal_eth.o \
    stm32f1xx_hal_exti.o \
    stm32f1xx_hal_flash.o \
    stm32f1xx_hal_flash_ex.o \
    stm32f1xx_hal_gpio.o \
    stm32f1xx_hal_gpio_ex.o \
    stm32f1xx_hal_hcd.o \
    stm32f1xx_hal_i2c.o \
    stm32f1xx_hal_i2s.o \
    stm32f1xx_hal_irda.o \
    stm32f1xx_hal_iwdg.o \
    stm32f1xx_hal_mmc.o \
    stm32f1xx_hal_nand.o \
    stm32f1xx_hal_nor.o \
    stm32f1xx_hal_pccard.o \
    stm32f1xx_hal_pcd.o \
    stm32f1xx_hal_pcd_ex.o \
    stm32f1xx_hal_pwr.o \
    stm32f1xx_hal_rcc.o \
    stm32f1xx_hal_rcc_ex.o \
    stm32f1xx_hal_rtc.o \
    stm32f1xx_hal_rtc_ex.o \
    stm32f1xx_hal_sd.o \
    stm32f1xx_hal_smartcard.o \
    stm32f1xx_hal_spi.o \
    stm32f1xx_hal_sram.o \
    stm32f1xx_hal_tim.o \
    stm32f1xx_hal_tim_ex.o \
    stm32f1xx_hal_uart.o \
    stm32f1xx_hal_usart.o \
    stm32f1xx_hal_wwdg.o \
    stm32f1xx_ll_adc.o \
    stm32f1xx_ll_crc.o \
    stm32f1xx_ll_dac.o \
    stm32f1xx_ll_dma.o \
    stm32f1xx_ll_exti.o \
    stm32f1xx_ll_fsmc.o \
    stm32f1xx_ll_gpio.o \
    stm32f1xx_ll_i2c.o \
    stm32f1xx_ll_pwr.o \
    stm32f1xx_ll_rcc.o \
    stm32f1xx_ll_rtc.o \
    stm32f1xx_ll_sdmmc.o \
    stm32f1xx_ll_spi.o \
    stm32f1xx_ll_tim.o \
    stm32f1xx_ll_usart.o \
    stm32f1xx_ll_usb.o \
    stm32f1xx_ll_utils.o \

OBJS=$(APP_OBJS) $(PLAT_OBJS)

# Recipes

.PHONY: all clean

OUTPUTS=$(OUTPUT).elf $(OUTPUT).hex $(OUTPUT).bin $(OUTPUT).map
all: $(OUTPUTS)

$(OUTPUT).elf: $(OBJS) stm32f1xx_hal.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBGCC)
	$(SIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@
%.bin: %.elf
	$(OBJCOPY) -O binary -j .text -j .data $< $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

stm32f1xx_hal.a: $(HAL_OBJS)
	$(AR) rcs $@ $^

clean:
	$(RM) *.o *.a $(OUTPUTS)
