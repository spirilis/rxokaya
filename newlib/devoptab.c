/* Device Operations Table for Newlib device I/O
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

#include <reent.h>
#include "devoptab.h"
#include "okaya_devop.h"
#include <string.h>
#include <unistd.h>



#define FILE_DESCRIPTOR_LIMIT 3

const devoptab_t *devoptab_list[] = {
	NULL,
	&devoptab_okaya,
	NULL };



/* Newlib primitives for open, close, read, write */
int write (int fd, const void *buf, size_t cnt)
{
	if (fd >= FILE_DESCRIPTOR_LIMIT || devoptab_list[fd] == NULL) {
		errno = ENODEV;
		return -1;
	}

	return devoptab_list[fd]->write(fd, buf, cnt);
}

int read (int fd, void *buf, size_t cnt)
{
	if (fd >= FILE_DESCRIPTOR_LIMIT || devoptab_list[fd] == NULL) {
		errno = ENODEV;
		return -1;
	}

	return devoptab_list[fd]->read(fd, buf, cnt);
}

int open (const char *file, int flags, int mode)
{
	int which_devoptab = 0;
	int fd = -1;

	do {
		if (strcmp(devoptab_list[which_devoptab]->name, file) == 0) {
			fd = which_devoptab;
			break;
		}
	} while (devoptab_list[which_devoptab++]);

	if (fd != -1) {
		return devoptab_list[fd]->open(file, flags, mode);
	} else {
		errno = ENODEV;
		return -1;
	}
}

int close (int fd)
{
	if (fd >= FILE_DESCRIPTOR_LIMIT || devoptab_list[fd] == NULL) {
		errno = ENODEV;
		return -1;
	}

	return devoptab_list[fd]->close(fd);
}

int fstat(int fd, struct stat *buf)
{
	return 0;
}

int isatty(int fd)
{
	if (fd <= STDERR_FILENO)
		return 1;
	errno = ENOTTY;
	return 0;
}

off_t lseek(int fd, off_t offset, int whence)
{
	errno = ENOSYS;
	return -1;
}
