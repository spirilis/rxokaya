/* Device Operations Table for Newlib device I/O */

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
