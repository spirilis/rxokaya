/* Okaya ST7579 LCD display
 * Test pattern writer
 */

#include "iodefine.h"
#include "st7579.h"
#include "okaya.h"
#include <stdint.h>
#include <string.h>

//const char *teststr = "The quick brown fox quickly jumps\nover the\thill.\n";
//const char *teststr = "The quick brown fox quickly jumps";
const char *teststr = "The quick brown fox quickly jumps\nover the\thill.\nTell him that you love him\nShow him that you\b care\nA whole lo\bt.";

int main()
{
	//uint16_t i;

	SYSTEM.SCKCR.BIT.ICK = 0x00;  // ICLK = 96MHz
	SYSTEM.SCKCR.BIT.PCK = 0x02;  // PCLK = 24MHz
	SYSTEM.SCKCR.BIT.PSTOP1 = 1;
	SYSTEM.SCKCR.BIT.PSTOP0 = 1;

	PORTD.DDR.BIT.B2=1;
	PORTD.DR.BIT.B2=1;

	st7579_init();  // Releases RSTOUT# and initializes the LCD, initializes backlight LED (turns it off by default)
	st7579_backlight(0);
	okaya_init();

	okaya_puts(teststr);

	while(1) ;

	return 0;
}
