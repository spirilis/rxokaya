TARGETMCU       ?= rx600

CROSS           := rx-elf-
CC              := $(CROSS)gcc
LDSCRIPT	:= rx62n8.ld
FLASHER		:= rxusb -v -v -d
CFLAGS          := -Os -Wall -Werror -g -mcpu=$(TARGETMCU)
CFLAGS += -fdata-sections -ffunction-sections -Wl,--gc-sections

SRCS                    := main.c st7579.c st7579_boardspecific.c rspi_util.c rspi_boardspecific.c chargen.c okaya_devop.c devoptab.c
PROG                    := main

all:                    $(PROG).elf

$(PROG).elf:    $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG).elf $(SRCS) -T $(LDSCRIPT)

clean:
	-rm -f $(PROG).elf

install: $(PROG).elf
	$(FLASHER) $(PROG).elf
