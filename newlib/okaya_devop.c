/* Device driver for stdio - Okaya LCD
 * Implements requisite open, close, write, read
 * Read not actually implemented
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
		st7579_init();
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
