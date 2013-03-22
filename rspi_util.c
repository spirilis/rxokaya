/* RSPI utility for Okaya ST7579 display driver
 *
 * Board-specific functions including:
 *         rspi_enable_ports()
 *         rspi_disable_ports()
 * are implemented in rspi_boardspecific.c
 *
 * Slave Select ID# is specified in rspi_util.h as ST7579_RSPI_SLAVESELECT
 * RSPI peripheral# is specified in rspi_util.h as ST7579_RSPI
 *
    Copyright (c) 2013 Eric Brundick <spirilis [at] linux dot com>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
 */

#include "iodefine.h"
#include "rspi_util.h"
#include <stdint.h>

void rspi_init()
{
	ST7579_RSPI_MSTP = 0;
	ST7579_RSPI.SPCR.BYTE = 0;
	ST7579_RSPI.SPPCR.BYTE = 0;
	ST7579_RSPI.SPBR = 0;  // 24MHz SPI, assuming PCLK=48MHz
	ST7579_RSPI.SPDCR.BYTE = 0;
	ST7579_RSPI.SPCKD.BYTE = 0;
	ST7579_RSPI.SSLND.BYTE = 0;
	ST7579_RSPI.SPND.BYTE = 0;
	ST7579_RSPI.SPCR2.BYTE = 0;
	ST7579_RSPI.SPCMD0.WORD = 0;
	ST7579_RSPI.SSLP.BYTE = 0;
	ST7579_RSPI.SPCR.BIT.MSTR = 1;
	ST7579_RSPI.SPCR.BIT.SPE = 1;
	ST7579_RSPI.SPCR.BIT.SPMS = 0;  // 4-wire SPI with RSPI controlling Chip Select

	rspi_ports_enable();
}

uint8_t rspi_transfer(uint8_t data)
{
	ST7579_RSPI.SPSCR.BIT.SPSLN = 0;
	ST7579_RSPI.SPCMD0.BIT.SPB = 7;
	ST7579_RSPI.SPCMD0.BIT.CPHA = ST7579_RSPI_CPHA;
	ST7579_RSPI.SPCMD0.BIT.CPOL = ST7579_RSPI_CPOL;
	ST7579_RSPI.SPCMD0.BIT.SSLA = ST7579_RSPI_SLAVESELECT;
	ST7579_RSPI.SPCMD0.BIT.SSLKP = 0;
	ST7579_RSPI.SPDR.WORD.H = data;
	while (!ST7579_RSPI.SPSR.BIT.SPRF)
		;
	return (ST7579_RSPI.SPDR.WORD.H & 0xFF);
}
