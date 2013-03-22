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

#include <stdio.h>
#include "iodefine.h"
#include "okaya.h"
#include <stdint.h>
#include <string.h>


int main()
{
	//uint16_t i;

	SYSTEM.SCKCR.BIT.ICK = 0x00;  // ICLK = 96MHz
	SYSTEM.SCKCR.BIT.PCK = 0x02;  // PCLK = 24MHz
	SYSTEM.SCKCR.BIT.PSTOP1 = 1;
	SYSTEM.SCKCR.BIT.PSTOP0 = 1;

	PORTD.DDR.BIT.B2=1;
	PORTD.DR.BIT.B2=1;

	fopen("LCD", "r");  /* fopen calls open with "LCD" as the path; our newlib
			     * stub open() implementation finds devoptab_okaya bears the name
			     * "LCD" and executes its open() call, which returns filedes 1
			     * (STDOUT).  With STDOUT now open, printf() (which uses STDOUT
			     * exclusively by default) will now work.  fprintf(stdout, ...)
			     * also works!
			     */
	printf("Check this out!\n");
	printf("It's awesome.");
	fprintf(stdout, "For realz.\n");
	printf("Check out that fine cursor too.\n");
	fflush(stdout);

	while(1) ;

	return 0;
}
