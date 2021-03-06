/* Okaya ST7579 LCD display
 * Test pattern writer
 *
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
#include "st7579.h"
#include "okaya.h"
#include <stdint.h>
#include <string.h>

//const char *teststr = "The quick brown fox quickly jumps\nover the\thill.\n";
//const char *teststr = "The quick brown fox quickly jumps";
const char *teststr = "The quick brown fox quickly jumps\nover the\thill.\nTesting back\bspace and\nscrolling is pretty\nfun too.\n";

int main()
{
	//uint16_t i;

	SYSTEM.SCKCR.BIT.ICK = 0x00;  // ICLK = 96MHz
	SYSTEM.SCKCR.BIT.PCK = 0x02;  // PCLK = 24MHz
	SYSTEM.SCKCR.BIT.PSTOP1 = 1;
	SYSTEM.SCKCR.BIT.PSTOP0 = 1;

	PORTD.DDR.BIT.B2=1;
	PORTD.DR.BIT.B2=1;

	okaya_init();  // Runs st7579_init(), releases RSTOUT# and initializes the LCD, initializes backlight LED (turns it off by default)
	st7579_backlight(0);

	okaya_puts(teststr);

	while(1) ;

	return 0;
}
