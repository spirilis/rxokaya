/* Renesas RX RSPI utility library
 * Designed for driving the Okaya ST7579 LCD display on the YRDKRX62N board
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

#ifndef RSPI_UTIL_H
#define RSPI_UTIL_H

#include "iodefine.h"
#include <stdint.h>

// SPI mode 0
#define ST7579_RSPI_CPHA 0
#define ST7579_RSPI_CPOL 0

// SPI Slave Select pin
#define ST7579_RSPI_SLAVESELECT 3

// RSPI peripheral number
#define ST7579_RSPI RSPI0

// RSPI MSTP command
#define ST7579_RSPI_MSTP MSTP(RSPI0)

// SPI initialization and I/O
void rspi_init();
void rspi_ports_enable();  // User-tweaked function to flip on RSPI functionality on pins
void rspi_ports_disable(); // User-tweaked function to suspend RSPI functionality on pins
uint8_t rspi_transfer(uint8_t);     // SPI transfer

#endif /* RSPI_UTIL.H */
