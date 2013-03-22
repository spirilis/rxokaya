/* ST7579 LCD I/O library for Renesas RX with RSPI
 *
 * Board-specific functions such as LCD-RS, Backlight I/O which may vary
 * among boards/implementations.
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
#include "st7579.h"
#include <stdint.h>
#include <string.h>

void st7579_reset()
{
	PORTC.DDR.BIT.B3 = 1;
	PORTC.DR.BIT.B3 = 0;  // Pull RSTOUT# inverting buffer low so RSTOUT# goes high, releasing reset state.
}

void st7579_backlight_init()
{
	PORT2.DDR.BIT.B1 = 1;
	PORT2.DR.BIT.B1 = 0;  // Off by default
}

void st7579_backlight(uint8_t onoff)
{
	PORT2.DR.BIT.B1 = onoff;
}

void st7579_rs_init()
{
	PORT5.DDR.BIT.B1 = 1;
	PORT5.DR.BIT.B1 = 0;
}

void st7579_rs(uint8_t onoff)
{
	PORT5.DR.BIT.B1 = onoff;
}
