/* Okaya ST7579 LCD graphics and terminal library */

#ifndef OKAYA_H
#define OKAYA_H

#include <stdint.h>
#include "st7579.h"


/* Enable the optional cursor showing current position
 * Comment-out this #define in order to disable it
 */
#define OKAYA_USE_CURSOR 1

/* LCD configuration */
#define OKAYA_LINES 8
#define OKAYA_LINE_HEIGHT 8
#define OKAYA_CHAR_WIDTH 6
#define OKAYA_COLUMNS 16
#define OKAYA_X_PIXELS (OKAYA_COLUMNS * OKAYA_CHAR_WIDTH)
#define OKAYA_Y_PIXELS (OKAYA_LINES * OKAYA_LINE_HEIGHT)
#define OKAYA_TAB_SPACING 4

/* Character handling */
void okaya_init();
void okaya_putc(uint8_t c, uint8_t doflush);
void okaya_puts(const char *str);
void okaya_flush();

extern uint8_t okaya_framebuffer[];
extern uint16_t okaya_dirtybits[];

#endif /* OKAYA_H */
