/* Okaya ST7579 LCD display
 * Test pattern writer
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
	fprintf(stdout, "For realz.");
	printf("\nCheck out that fine cursor too.");
	fflush(stdout);

	while(1) ;

	return 0;
}
