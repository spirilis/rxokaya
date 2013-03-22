/* RSPI utility for Okaya ST7579 display driver
 *
 * Board-specific functions for initializing & detaching requisite I/O ports
 * Note that RSPI Slave Select pin ID is defined in rspi_util.h as RSPI_ST7579_SLAVESELECT
 * This is initially configured for the YRDKRX62N demo board.
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

/* USER-CONFIGURABLE FUNCTIONS
 * Tweak these as needed to set the correct port parameters.
 * e.g. if you choose to use the RSPI[0|1] A or B pins...
 */
void rspi_ports_enable()
{
	// RSPI0 pin choice "A"
	IOPORT.PFGSPI.BIT.RSPIS = 0;

	IOPORT.PFGSPI.BYTE |= 0x8E;  // MISO, MOSI, RSPCK, SSLA3-A enabled & connected to physical pins
	PORTC.DDR.BIT.B7 = 0;  // MISO = input
	PORTC.ICR.BIT.B7 = 1;

	PORTC.DDR.BIT.B6 = 1;  // MOSI output
	PORTC.DDR.BIT.B5 = 1;  // RSPCK output

	// SSLA3-A used for SPI Chip Select
	PORTC.DDR.BIT.B2 = 1;
	PORTC.DR.BIT.B2 = 1;
}

void rspi_ports_disable()
{
	// Disconnects RSPI peripheral function only
	IOPORT.PFGSPI.BYTE &= ~0x8E;  // Disconnect MISO, MOSI, RSPCK, SSLA3-A
	PORTC.DDR.BIT.B2 = 0;  // Disconnect SSLA3-A chip select
}
