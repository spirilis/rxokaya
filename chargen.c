/* chargen.c - Framebuffer and character display manager for ST7579 96x64 LCD display
 */

#include "iodefine.h"
#include <string.h>
#include <stdint.h>
#include "font_5x7.h"
#include "okaya.h"

uint8_t okaya_framebuffer[OKAYA_COLUMNS*OKAYA_CHAR_WIDTH*OKAYA_LINES];
uint16_t okaya_dirtybits[ (OKAYA_COLUMNS / 16) * OKAYA_LINES ];

uint8_t okaya_x, okaya_y;

void okaya_init()
{
	memset(okaya_framebuffer, 0, OKAYA_LINES*OKAYA_COLUMNS*OKAYA_CHAR_WIDTH);
	okaya_x = 0;
	okaya_y = 0;
	st7579_clear();
}

void okaya_putc(uint8_t c, uint8_t doflush)
{
	uint8_t i = 0;
	uint16_t j;

	// Process the character as is
	if (c > 0x7F)  // High-bit characters treated as spaces; so are ctrl chars
		c = 0x20;

	if (c >= 0x20) {
		j = okaya_y * OKAYA_X_PIXELS + okaya_x * OKAYA_CHAR_WIDTH;
		memcpy(okaya_framebuffer+j, okaya_5x7_font[c-0x20], OKAYA_CHAR_WIDTH);

		// Flag dirty buffer
		okaya_dirtybits[okaya_y] |= 1 << okaya_x;
		okaya_x++;
	} else {
		// Process control character
		switch (c) {
			case '\n':
#ifdef OKAYA_USE_CURSOR
				// Erase the cursor presently at okaya_x,okaya_y before moving it
				j = okaya_y * OKAYA_X_PIXELS + okaya_x * OKAYA_CHAR_WIDTH;
				memcpy(okaya_framebuffer+j, okaya_5x7_font[0], OKAYA_CHAR_WIDTH);
				okaya_dirtybits[okaya_y] |= 1 << okaya_x;
#endif
				okaya_x = 0;
				okaya_y++;
				break;
			case '\t':
#ifdef OKAYA_USE_CURSOR
				// Erase the cursor presently at okaya_x,okaya_y before moving it
				j = okaya_y * OKAYA_X_PIXELS + okaya_x * OKAYA_CHAR_WIDTH;
				memcpy(okaya_framebuffer+j, okaya_5x7_font[0], OKAYA_CHAR_WIDTH);
				okaya_dirtybits[okaya_y] |= 1 << okaya_x;
#endif
				if (okaya_x % OKAYA_TAB_SPACING == 0) {
					okaya_x += OKAYA_TAB_SPACING;
				} else {
				PORTD.DR.BIT.B2=0;
					okaya_x += okaya_x % OKAYA_TAB_SPACING;
				}
				break;
			case '\b':
				if (okaya_x > 0) {  // Nothing happens if @ beginning of line
					okaya_x--;
					j = okaya_y * OKAYA_X_PIXELS + okaya_x * OKAYA_CHAR_WIDTH;
					// Otherwise, the previous character gets erased.
					memcpy(okaya_framebuffer+j, okaya_5x7_font[0], OKAYA_CHAR_WIDTH);
					okaya_dirtybits[okaya_y] |= 1 << okaya_x;
				}
				break;
			// No default section; any other ctrl char is ignored
		}
	}

	if (okaya_x >= OKAYA_COLUMNS) {
		// Shift down one row
		okaya_y++;
		okaya_x = 0;
	}

	if (okaya_y >= OKAYA_LINES) {
		// Ut oh, we must scroll...
		for (i=1; i < OKAYA_LINES; i++) {
			memcpy(okaya_framebuffer+(i-1)*OKAYA_X_PIXELS,
			       okaya_framebuffer+i*OKAYA_X_PIXELS,
			       OKAYA_X_PIXELS);
			okaya_dirtybits[i] = 0xFFFF;
		}
		okaya_y = OKAYA_LINES-1;
		memset(okaya_framebuffer + okaya_y*OKAYA_X_PIXELS,
		       0x00,
		       OKAYA_X_PIXELS);  // Clear last line
	}

#ifdef OKAYA_USE_CURSOR
	j = okaya_y * OKAYA_X_PIXELS + okaya_x * OKAYA_CHAR_WIDTH;
	memcpy(okaya_framebuffer+j, okaya_cursor, OKAYA_CHAR_WIDTH);
	okaya_dirtybits[okaya_y] |= 1 << okaya_x;
#endif

	if (doflush)
		okaya_flush();
}

void okaya_flush()
{
	uint16_t i, j;

	for (i=0; i < OKAYA_LINES; i++) {
		if (okaya_dirtybits[i]) {
			if (okaya_dirtybits[i] == 0xFFFF) {  // Quick optimization for refreshing a whole line
				st7579_go(0, i);
				st7579_write(okaya_framebuffer + OKAYA_X_PIXELS*i, OKAYA_X_PIXELS);
			} else {
				for (j=0; j < OKAYA_COLUMNS; j++) {
					if (okaya_dirtybits[i] & (1 << j)) {
						st7579_go( j*OKAYA_CHAR_WIDTH, i );
						st7579_write(okaya_framebuffer + OKAYA_X_PIXELS*i + OKAYA_CHAR_WIDTH*j, OKAYA_CHAR_WIDTH);
						okaya_dirtybits[i] &= ~(1 << j);  // Flushed; clear bit
					}
				}
			}
		}
	}
}

void okaya_puts(const char *str)
{
	uint16_t i, j;

	j = strlen(str);
	for (i=0; i < j; i++)
		okaya_putc((uint8_t)str[i], 0);
	okaya_flush();
}
