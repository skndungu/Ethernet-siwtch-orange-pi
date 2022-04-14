# Ethernet-siwtch-orange-pi
Five Port Managed Ethernet Switch
=================================


This project is a five port managed switch based on a Micrel KSZ8995M and an
Atmel ATMega168 microcontroller.


Contents
--------

    COPYING     text version of the GPL
    README      this file
    firmware/   source directory for firmware files
    hardware/   source directory for the hardware design files

Firmware
--------

Building requires an avr-gcc toolchain, in the firmware/ directory, to build
run:

    make

Flashing the firmware on the device requires avrdude and a compatible hardware
programmer. Default configuration is stored at the beginning of the Makefile.
To program with the default configuration, run:

    make load

Fuses can be configured running:

    make fuse 

Hardware
--------

All hardware files (schematic, layout and libraries) are in CadSoft Eagle
format.

The switch can be configured in unmanaged mode by not shorting any jumper.

To configure the switch in SPI slave mode, PS[1:0] have to be set to 10, so
just short the pins 1 and 2 of SJ2.



License
-------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
