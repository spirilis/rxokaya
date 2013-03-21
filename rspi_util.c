/* RSPI utility for Okaya ST7579 display driver
 *
 * Board-specific functions including:
 *         rspi_enable_ports()
 *         rspi_disable_ports()
 * are implemented in rspi_boardspecific.c
 *
 * Slave Select ID# is specified in rspi_util.h as ST7579_RSPI_SLAVESELECT
 *
 */

#include "iodefine.h"
#include "rspi_util.h"
#include <stdint.h>

void rspi_init()
{
	MSTP(RSPI0) = 0;
	RSPI0.SPCR.BYTE = 0;
	RSPI0.SPPCR.BYTE = 0;
	RSPI0.SPBR = 0;  // 24MHz SPI, assuming PCLK=48MHz
	RSPI0.SPDCR.BYTE = 0;
	RSPI0.SPCKD.BYTE = 0;
	RSPI0.SSLND.BYTE = 0;
	RSPI0.SPND.BYTE = 0;
	RSPI0.SPCR2.BYTE = 0;
	RSPI0.SPCMD0.WORD = 0;
	RSPI0.SSLP.BYTE = 0;
	RSPI0.SPCR.BIT.MSTR = 1;
	RSPI0.SPCR.BIT.SPE = 1;
	RSPI0.SPCR.BIT.SPMS = 0;  // 4-wire SPI with RSPI controlling Chip Select

	rspi_ports_enable();
}

uint8_t rspi_transfer(uint8_t data)
{
	RSPI0.SPSCR.BIT.SPSLN = 0;
	RSPI0.SPCMD0.BIT.SPB = 7;
	RSPI0.SPCMD0.BIT.CPHA = ST7579_RSPI_CPHA;
	RSPI0.SPCMD0.BIT.CPOL = ST7579_RSPI_CPOL;
	RSPI0.SPCMD0.BIT.SSLA = ST7579_RSPI_SLAVESELECT;
	RSPI0.SPCMD0.BIT.SSLKP = 0;
	RSPI0.SPDR.WORD.H = data;
	while (!RSPI0.SPSR.BIT.SPRF)
		;
	return (RSPI0.SPDR.WORD.H & 0xFF);
}
