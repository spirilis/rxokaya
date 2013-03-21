/* Renesas RX RSPI utility library
 * Designed for driving the Okaya ST7579 LCD display on the YRDKRX62N board
 */

#ifndef RSPI_UTIL_H
#define RSPI_UTIL_H

#include "iodefine.h"
#include <stdint.h>

// SPI mode 0
#define ST7579_RSPI_CPHA 0
#define ST7579_RSPI_CPOL 0

// SPI Slave Select pin
#define ST7579_RSPI_SLAVESELECT 3

// RSPI peripheral number
#define ST7579_RSPI RSPI0

// RSPI MSTP command
#define ST7579_RSPI_MSTP MSTP(RSPI0)

// SPI initialization and I/O
void rspi_init();
void rspi_ports_enable();  // User-tweaked function to flip on RSPI functionality on pins
void rspi_ports_disable(); // User-tweaked function to suspend RSPI functionality on pins
uint8_t rspi_transfer(uint8_t);     // SPI transfer

#endif /* RSPI_UTIL.H */
