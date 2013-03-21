/* RSPI utility for Okaya ST7579 display driver
 *
 * Board-specific functions for initializing & detaching requisite I/O ports
 * Note that RSPI Slave Select pin ID is defined in rspi_util.h as RSPI_ST7579_SLAVESELECT
 *
 */

#include "iodefine.h"
#include "rspi_util.h"
#include <stdint.h>

/* USER-CONFIGURABLE FUNCTIONS
 * Tweak these as needed to set the correct port parameters.
 * e.g. if you choose to use the RSPI[0|1] A or B pins...
 */
void rspi_ports_enable()
{
	// RSPI0 pin choice "A"
	IOPORT.PFGSPI.BIT.RSPIS = 0;

	IOPORT.PFGSPI.BYTE |= 0x8E;  // MISO, MOSI, RSPCK, SSLA3-A enabled & connected to physical pins
	PORTC.DDR.BIT.B7 = 0;  // MISO = input
	PORTC.ICR.BIT.B7 = 1;

	PORTC.DDR.BIT.B6 = 1;  // MOSI output
	PORTC.DDR.BIT.B5 = 1;  // RSPCK output

	// SSLA3-A used for SPI Chip Select
	PORTC.DDR.BIT.B2 = 1;
	PORTC.DR.BIT.B2 = 1;
}

void rspi_ports_disable()
{
	// Disconnects RSPI peripheral function only
	IOPORT.PFGSPI.BYTE &= ~0x8E;  // Disconnect MISO, MOSI, RSPCK, SSLA3-A
	PORTC.DDR.BIT.B2 = 0;  // Disconnect SSLA3-A chip select
}
