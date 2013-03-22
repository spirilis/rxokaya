/* ST7579 LCD I/O library for Renesas RX with RSPI
 * Relies on "rspi_util.c" functions for RSPI I/O
 *
 * Board-specific functions including:
 *         st7579_rs_init()
 *         st7579_rs()
 *         st7579_reset()
 *         st7579_backlight_init()
 *         st7579_backlight()
 * are provided in "st7579_boardspecific.c"
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

uint8_t st7579_funcset;  // Keep track of the current state of our function bits

void st7579_init()
{
	rspi_init();  // Enable RSPI ports
	st7579_rs_init();
	st7579_backlight_init();
	st7579_backlight(0);

	st7579_reset();
	st7579_funcset = ST7579_FUNCSET_PARAM_MY | 0x01;  // MX=0, MY=1, PD=0, H=0,1
	// Init H=0,1
	st7579_command(ST7579_FUNCSET, ST7579_FUNCSET_MASK, st7579_funcset, 255);

	// YRDKRX62N Okaya LCD parameters
	st7579_config_bias(6);
	st7579_config_booster(2, 3);
	st7579_config_vlcd(0x68);

	st7579_config_framerate(0x07);
	st7579_go(0, 0);
	st7579_display_normal();
	st7579_config_startline(0);

	st7579_clear();
}

// RS is always 0 for commands; for writes, a separate function is used.
void st7579_command(uint8_t reg, uint8_t mask, uint8_t data, uint8_t h)
{
	if (h < 255) {
		// Set H mode (instruction mode) if we're not already there.
		if ( (st7579_funcset & 0x03) != h ) {
			st7579_funcset = (st7579_funcset & 0xFC) | h;
			st7579_command(ST7579_FUNCSET, ST7579_FUNCSET_MASK, st7579_funcset, 255);
		}
	}
	rspi_transfer(reg | (data & mask));  // Chip Select driven automatically by RSPI
}

void st7579_write(uint8_t *buf, uint16_t len)
{
	uint16_t i=0;

	st7579_rs(1);
	for (i=0; i < len; i++) {
		rspi_transfer(buf[i]);
	}
	st7579_rs(0);
}

void st7579_clear()
{
	uint8_t y, dpydata[102];

	memset(dpydata, 0, 102);  // Newlib uses ASM string-manipulation instructions for this!
	for (y=0; y < 10; y++) {
		st7579_command(ST7579_SETY, ST7579_SETY_MASK, y, ST7579_SETY_H);  // Set row
		st7579_command(ST7579_SETX, ST7579_SETX_MASK, 0, ST7579_SETX_H);  // Set column
		st7579_write(dpydata, 102);
	}
	st7579_command(ST7579_SETY, ST7579_SETY_MASK, 0, ST7579_SETY_H);  // Reset current position to origin
	st7579_command(ST7579_SETX, ST7579_SETX_MASK, 0, ST7579_SETX_H);
}

void st7579_testpattern()
{
	uint8_t y, x, c=0x80, dpydata[102];

	for (x=0; x < 102; x++) {  // Set a pattern with a single bit getting shifted down
		dpydata[x] = c;
		c >>= 1;
		if (!c) c = 0x80;
	}

	st7579_go(0, 0);
	for (y=0; y < 9; y++) {
		//st7579_go(0, y);
		st7579_write(dpydata, 102);
	}
	st7579_go(0, 0);
}

void st7579_go(uint8_t x, uint8_t y)
{
	st7579_command(ST7579_SETY, ST7579_SETY_MASK, y, ST7579_SETY_H);
	st7579_command(ST7579_SETX, ST7579_SETX_MASK, x, ST7579_SETX_H);
}

void st7579_poweron()
{
	st7579_funcset &= ~ST7579_FUNCSET_PARAM_PD;
	st7579_command(ST7579_FUNCSET, ST7579_FUNCSET_MASK, st7579_funcset, ST7579_FUNCSET_H);
}

void st7579_poweroff()
{
	st7579_funcset |= ST7579_FUNCSET_PARAM_PD;
	st7579_command(ST7579_FUNCSET, ST7579_FUNCSET_MASK, st7579_funcset, ST7579_FUNCSET_H);
}

void st7579_display_normal()
{
	st7579_command(ST7579_DISPLAYCTRL, ST7579_DISPLAYCTRL_MASK, ST7579_DISPLAYCTRL_PARAM_NORMAL, ST7579_DISPLAYCTRL_H);
}

void st7579_display_off()
{
	st7579_command(ST7579_DISPLAYCTRL, ST7579_DISPLAYCTRL_MASK, ST7579_DISPLAYCTRL_PARAM_OFF, ST7579_DISPLAYCTRL_H);
}

void st7579_display_invert()
{
	st7579_command(ST7579_DISPLAYCTRL, ST7579_DISPLAYCTRL_MASK, ST7579_DISPLAYCTRL_PARAM_INVERSE, ST7579_DISPLAYCTRL_H);
}

void st7579_display_allon()
{
	st7579_command(ST7579_DISPLAYCTRL, ST7579_DISPLAYCTRL_MASK, ST7579_DISPLAYCTRL_PARAM_ALLON, ST7579_DISPLAYCTRL_H);
}

void st7579_config_booster(uint8_t be, uint8_t pc)
{
	st7579_command(ST7579_BOOSTER_EFFICIENCY, ST7579_BOOSTER_EFFICIENCY_MASK, ((be & 0x03) << 2) | (pc & 0x03),
		       ST7579_BOOSTER_EFFICIENCY_H);
}

void st7579_config_vlcd(uint8_t vop)
{
	st7579_command(ST7579_SETVLCD, ST7579_SETVLCD_MASK, (vop & 0x80) >> 7, ST7579_SETVLCD_H);
	st7579_command(ST7579_SETVOP, ST7579_SETVOP_MASK, vop & 0x7F, ST7579_SETVOP_H);
}

void st7579_config_bias(uint8_t bias)
{
	st7579_command(ST7579_SETBIAS, ST7579_SETBIAS_MASK, bias & 0x07, ST7579_SETBIAS_H);
}

void st7579_config_framerate(uint8_t framerate)
{
	st7579_command(ST7579_FRAMERATE, ST7579_FRAMERATE_MASK, framerate & 0x07, ST7579_FRAMERATE_H);
}

void st7579_config_startline(uint8_t st)
{
	st7579_command(ST7579_SETSTART, ST7579_SETSTART_MASK, st & 0x3F, ST7579_SETSTART_H);
	st7579_command(ST7579_SETSTARTS6, ST7579_SETSTARTS6_MASK, (st & 0x40) >> 6, ST7579_SETSTARTS6_H);
}
