rxokaya
=======

Renesas RX RSPI library for interfacing with Okaya ST7579-based 96x64 LCD for GNU GCC/GNURX

Core library implementation-
* chargen.c
* okaya.h
* st7579.c
* st7579.h
* st7579_boardspecific.c
* rspi_util.h
* rspi_util.c
* rspi_boardspecific.c
* font_5x7.h

User-configurable functions include the *_boardspecific.c files which expect the user to provide requisite statements for configuring the LCD RS pin, backlight, RSPI port configuration.

_rspi_util.h_ must be configured to set the RSPI Slave Select pin.

Initialization occurs via st7579_init() followed by okaya_init()

All library files expect to find an _iodefine.h_ in the current directory.

Newlib stub support found in-
* newlib/devoptab.c
* newlib/devoptab.h
* newlib/okaya_devop.c
* newlib/okaya_devop.h

This provides open(), close(), read() and write() (only open, close and write do anything meaningful).

The user can utilize Newlib's printf and fprintf on the "stdout" file handle.  Path to the LCD is "LCD".

Example usage in examples/newlib_printf/main.c

Note that an underscore-based cursor is enabled by default.  You may disable this by commenting out _OKAYA_USE_CURSOR_ in okaya.h

A basic manifest of the files required for a simple implementation is found in the _basic/_ subdirectory.
