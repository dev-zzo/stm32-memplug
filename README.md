# stm32-memplug

The `stm32-memplug` project aims to be a universal toy for playing with
various memory ICs. As is obvious from the name, it is based on the STM32
SoC series, more specifically the ever-popular STM32F103 chips.

The firmware bit sits on top of the code kindly provided by the
manufacturer, the "STM32CubeF1 MCU Firmware Package". At least some part
of it will have to be rewritten later to support the flexibility I want it
to have.

The hardware bit mostly relies on the FSMC unit to handle all the signalling
for NOR, NAND, and eMMC chips.

**CAUTION**: The hardware supports 3v3 chips only. 1v8 chips **will** be destroyed.

# Why would you even?

> Science is not about *why*! It's about *why not*?

This toy is meant for learning and experimenting, not for any kind of
"professional work". Hack it and have fun while learning about the F103
and different memory types.

# How to do anything useful with this?

The toy relies on PA3..0 to detect which memory type it should configure:

PA3..0 | Memory type
-------|------------
0000 | eMMC
0001 | NAND
0011 | NOR
Other | Reserved

If you forget to set those pins to known values, the board will show up as
`STM32-MemPlug: Unknown TOP` in your USB devices.

## eMMC devices

Connect your eMMC chip to the STM32F103 board:

eMMC pin | F103 pin
---------|---------
CLK | PC12
CMD | PD2
D0 | PC8

eMMC D1 through D7 are not used anyway at this point (see Performance).
Remember to connect 3.3V and GND too! Note that some eMMC chips will require
connecting most or all power pads.

Both standard and high capacity devices should be supported.

If everything works fine, the device will appear as a simple USB mass storage
when connected to the host system. When the chip is accessed, the PC13 LED
will light up for visual confirmation.

### Wishlist

* Accessing boot partitions

## NOR devices

The current firmware supports x16 parallel-NOR chips. Wire them up like this:

NOR pin | F103 pin
--------|---------
 A0 | PF0
 A1 | PF1
 A2 | PF2
 A3 | PF3
 A4 | PF4
 A5 | PF5
 A6 | PF12
 A7 | PF13
 A8 | PF14
 A9 | PF15
A10 | PG0
A11 | PG1
A12 | PG2
A13 | PG3
A14 | PG4
A15 | PG5
A16 | PD11
A17 | PD12
A18 | PD13
A19 | PE3
A20 | PE4
A21 | PE5
A22 | PE6
A23 | PE2
A24 | PG13
A15 | PG14
 D0 | PD14
 D1 | PD15
 D2 | PD0
 D3 | PD1
 D4 | PE7
 D5 | PE8
 D6 | PE9
 D7 | PE10
 D8 | PE11
 D9 | PE12
D10 | PE13
D11 | PE14
D12 | PE15
D13 | PD8
D14 | PD9
D15 | PD10
nCE | PD7
nOE | PD4
nWE | PD5
R/B | PD6

Note the `R/B` signal might need a 10k pull-up; the internal pull-up might be
too weak to be fast enough.

## NAND devices

That is yet to come. :-)

# Building firmware

A Makefile is provided which should do that for you. Just run `make` from the
root dir. The script relies on the `CROSS_COMPILE` environment variable to
find the right compiler; it should be set to the path and prefix of your ARM
compiler; for example, it's `~/x-tools/arm-none-eabi/bin/arm-none-eabi-` on my system.

# Building hardware

If you don't want to wire small things all the time, several board designs have been
created as a semi-permanent solution. You can find those designs under `hardware`.

The general approach is, one "top" board is provided for each memory type, this goes
directly on top of the STM32F103ZE "minimal system board" (the cheapest option).
The top board provides wiring and passives as needed and accepts a set of small
footprint-specific boards; you can solder your target to those boards for reliable
and fast connection.

This is especially useful for BGA chips:

* Removing them from the device-under-hack requires hot air / rework station anyway
* Reballing the chip needs to be done anyway, doing it twice doesn't take as long

# Performance

The design is limited mostly by the USB unit of the F103 at the moment.
The theoretical speed is no greater than 1MB/s, so don't expect blazing
rates here. Dumping a 8GB MMC will take about 5-6 hours.

NOR Flash read speeds tend to land somewhere around 700KB/s.

# Debugging

The toy uses Serial Wire Output (SWO) to pring debugging messages in cases when
things go sideways; having a dongle which is able to receive that is advised.
