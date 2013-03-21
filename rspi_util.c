/* RSPI utility for Okaya ST7579 display driver
 *
 * Board-specific functions including:
 *         rspi_enable_ports()
 *         rspi_disable_ports()
 * are implemented in rspi_boardspecific.c
 *
 * Slave Select ID# is specified in rspi_util.h as ST7579_RSPI_SLAVESELECT
 * RSPI peripheral# is specified in rspi_util.h as ST7579_RSPI
 *
 */

#include "iodefine.h"
#include "rspi_util.h"
#include <stdint.h>

void rspi_init()
{
	ST7579_RSPI_MSTP = 0;
	ST7579_RSPI.SPCR.BYTE = 0;
	ST7579_RSPI.SPPCR.BYTE = 0;
	ST7579_RSPI.SPBR = 0;  // 24MHz SPI, assuming PCLK=48MHz
	ST7579_RSPI.SPDCR.BYTE = 0;
	ST7579_RSPI.SPCKD.BYTE = 0;
	ST7579_RSPI.SSLND.BYTE = 0;
	ST7579_RSPI.SPND.BYTE = 0;
	ST7579_RSPI.SPCR2.BYTE = 0;
	ST7579_RSPI.SPCMD0.WORD = 0;
	ST7579_RSPI.SSLP.BYTE = 0;
	ST7579_RSPI.SPCR.BIT.MSTR = 1;
	ST7579_RSPI.SPCR.BIT.SPE = 1;
	ST7579_RSPI.SPCR.BIT.SPMS = 0;  // 4-wire SPI with RSPI controlling Chip Select

	rspi_ports_enable();
}

uint8_t rspi_transfer(uint8_t data)
{
	ST7579_RSPI.SPSCR.BIT.SPSLN = 0;
	ST7579_RSPI.SPCMD0.BIT.SPB = 7;
	ST7579_RSPI.SPCMD0.BIT.CPHA = ST7579_RSPI_CPHA;
	ST7579_RSPI.SPCMD0.BIT.CPOL = ST7579_RSPI_CPOL;
	ST7579_RSPI.SPCMD0.BIT.SSLA = ST7579_RSPI_SLAVESELECT;
	ST7579_RSPI.SPCMD0.BIT.SSLKP = 0;
	ST7579_RSPI.SPDR.WORD.H = data;
	while (!ST7579_RSPI.SPSR.BIT.SPRF)
		;
	return (ST7579_RSPI.SPDR.WORD.H & 0xFF);
}
