/* ST7579 LCD I/O library for Renesas RX with RSPI
 *
 * Board-specific functions such as LCD-RS, Backlight I/O which may vary
 * among boards/implementations.
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
