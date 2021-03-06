# stm32-memplug

The `stm32-memplug` project aims to be a universal toy for playing with
various memory ICs. As is obvious from the name, it is based on the STM32
SoC series, more specifically the ever-popular STM32F103 chips.

The software bit sits on top of the code kindly provided by the
manufacturer, the "STM32CubeF1 MCU Firmware Package". At least some part
of it will have to be rewritten later to support the flexibility I want it
to have.

# Why would you even?

> Science is not about why! It's about why not?

This toy is meant for learning and experimenting, not for any kind of
"professional work". Hack it and have fun while learning about the F103
and different memory types.

# How to do anything useful with this?

## eMMC devices

Connect your eMMC chip to the STM32F103 board:

eMMC pin | F103 pin
-------|---------
CLK | PC12
CMD | PD2
D0 | PC8

D1 through D7 are not used anyway at this point (see Performance).
Remember to connect 3.3V and GND too! Note that some eMMC chips will require
connecting most or all power pads.

Both standard and high capacity devices should be supported.

If everything works fine, the device will appear as a simple USB mass storage
when connected to the host system. When the chip is accessed, the PC13 LED
will light up for visual confirmation.

## NAND devices

That is yet to come. :-)

## NOR devices

That is yet to come. :-)

# Building firmware

A Makefile is provided which should do that for you. Just run `make` from the
root dir. The script relies on the `CROSS_COMPILE` environment variable to
find the right compiler; it should be set to the path and prefix of your ARM
compiler; for example, it's `~/x-tools/arm-none-eabi/bin/arm-none-eabi-` on my system.

# Building hardware

That is yet to come. :-)

# Performance

The design is limited mostly by the USB unit of the F103 at the moment.
The theoretical speed is no greater than 1MB/s, so don't expect blazing
rates here. Dumping a 8GB MMC will take about 5-6 hours.
