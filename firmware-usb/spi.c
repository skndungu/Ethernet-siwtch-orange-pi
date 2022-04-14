/*
 * Copyright 2011 Fabio Baltieri (fabio.baltieri@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "board.h"

void spi_init(void)
{
	spi_cs_h();

	SPI_DDR = _BV(SPI_SCK) | _BV(SPI_MOSI) | _BV(SPI_CS);
	
	SPCR = ( (0 << SPIE) |
		 (1 << SPE)  |
		 (0 << DORD) |
		 (1 << MSTR) |
		 (0 << CPOL) | (0 << CPHA) |
		 (0 << SPR1) | (0 << SPR0) );
	
	SPSR = ( (0 << SPI2X) );
}

uint8_t spi_io(uint8_t data)
{
	uint8_t ret;

	SPDR = data;
	ret = 0xff;

	while (!(SPSR & _BV(SPIF)))
		ret = SPDR;

	return ret;
}

void spi_write_block(uint8_t addr, uint8_t *buf, uint8_t count)
{
	uint8_t i;

	spi_cs_l();

	spi_io(0x02); /* WRITE DATA */

	spi_io(addr);

	for (i = 0; i < count; i++)
		spi_io(buf[i]);

	spi_cs_h();
}

void spi_read_block(uint8_t addr, uint8_t *buf, uint8_t count)
{
	uint8_t i;

	spi_cs_l();

	spi_io(0x03); /* READ DATA */

	spi_io(addr);

	for (i = 0; i < count; i++)
		buf[i] = spi_io(0xff);

	spi_cs_h();
}

void spi_write(uint8_t value, uint8_t addr)
{
	spi_cs_l();

	spi_io(0x02); /* WRITE DATA */

	spi_io(addr);

	spi_io(value);

	spi_cs_h();
}

uint8_t spi_read(uint8_t addr)
{
	uint8_t ret;

	spi_cs_l();

	spi_io(0x03); /* READ DATA */

	spi_io(addr);

	ret = spi_io(0xff);

	spi_cs_h();

	return ret;
}
