/* Device driver for stdio - Okaya LCD
 * Implements requisite open, close, write, read
 * Read not actually implemented
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

#include "devoptab.h"
#include "okaya_devop.h"
#include "okaya.h"
#include "rspi_util.h"
#include <stdint.h>
#include <reent.h>
#include <unistd.h>
#include <errno.h>


const devoptab_t devoptab_okaya = {
                "LCD",
                okaya_open,
                okaya_close,
                okaya_write,
                okaya_read };

const devoptab_t devoptab_okaya_backlit = {
                "LCDBACKLIT",
                okaya_open_backlit,
                okaya_close,
                okaya_write,
                okaya_read };

uint8_t okaya_lcd_was_initialized = 0;

int okaya_open(const char *path, int flags, int mode)
{
	if (!okaya_lcd_was_initialized) {
		okaya_init();
		okaya_lcd_was_initialized = 1;
	} else {
		rspi_ports_enable();
	}
	return STDOUT_FILENO;  // STDOUT
}

int okaya_open_backlit(const char *path, int flags, int mode)
{
	int filedes;

	filedes = okaya_open(path, flags, mode);
	st7579_backlight(1);
	return filedes;
}

int okaya_close(int fd)
{
	rspi_ports_disable();
	return 0;
}

int okaya_read(int fd, char *ptr, int len)
{
	errno = EINVAL;
	return -1;
}

int okaya_write(int fd, const char *ptr, int len)
{
	int i;

	for (i=0; i < len; i++) {
		okaya_putc((uint8_t)ptr[i], 0);  // Perform screen refresh after all data's done
	}
	okaya_flush();
	return i;
}
