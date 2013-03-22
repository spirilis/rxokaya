/* Okaya ST7579 LCD graphics and terminal library
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
