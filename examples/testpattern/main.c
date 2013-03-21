/* Okaya ST7579 LCD display
 * Test pattern writer
 */

#include "iodefine.h"
#include "st7579.h"
#include <stdint.h>

int main()
{
	SYSTEM.SCKCR.BIT.ICK = 0x00;  // ICLK = 96MHz
	SYSTEM.SCKCR.BIT.PCK = 0x02;  // PCLK = 24MHz
	SYSTEM.SCKCR.BIT.PSTOP1 = 1;
	SYSTEM.SCKCR.BIT.PSTOP0 = 1;

	st7579_init();  // Releases RSTOUT# and initializes the LCD, initializes backlight LED (turns it off by default)
	st7579_testpattern(); // Diagonal parallel lines drawn on the display
	st7579_backlight(0);

	while(1) ;

	return 0;
}
