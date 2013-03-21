/* st7579.h
 * Driver support header for ST7579-based LCD controller
 * Includes command definitions
 */

#ifndef ST7579_H
#define ST7579_H

#include <stdint.h>

#define ST7579_X_PIXELS 102
#define ST7579_Y_ROWS 9

/* Instructions */
#define ST7579_NOP 0x00
#define ST7579_NOP_MASK 0x00
#define ST7579_NOP_RS 0
#define ST7579_NOP_H 255
// Note: H=255 means ignore (don't bother setting 'H' in function set)

#define ST7579_FUNCSET 0x20
#define ST7579_FUNCSET_MASK 0x1F
#define ST7579_FUNCSET_RS 0
#define ST7579_FUNCSET_H 255

#define		ST7579_FUNCSET_PARAM_MX 0x10
#define		ST7579_FUNCSET_PARAM_MY 0x08
#define		ST7579_FUNCSET_PARAM_PD 0x04

#define ST7579_WRITE 0x00
#define ST7579_WRITE_MASK 0xFF
#define ST7579_WRITE_RS 1
#define ST7579_WRITE_H 255

#define ST7579_SETVLCD 0x04
#define ST7579_SETVLCD_MASK 0x01
#define ST7579_SETVLCD_RS 0
#define ST7579_SETVLCD_H 0

#define		ST7579_SETVLCD_PARAM_PRS 0x01

#define ST7579_END 0x06
#define ST7579_END_MASK 0x00
#define ST7579_END_RS 0
#define ST7579_END_H 0

#define ST7579_READMODIFYWRITE 0x07
#define ST7579_READMODIFYWRITE_MASK 0x00
#define ST7579_READMODIFYWRITE_RS 0
#define ST7579_READMODIFYWRITE_H 0

#define ST7579_DISPLAYCTRL 0x08
#define ST7579_DISPLAYCTRL_MASK 0x05
#define ST7579_DISPLAYCTRL_RS 0
#define ST7579_DISPLAYCTRL_H 0

#define		ST7579_DISPLAYCTRL_PARAM_OFF 0x00
#define		ST7579_DISPLAYCTRL_PARAM_NORMAL 0x04
#define		ST7579_DISPLAYCTRL_PARAM_ALLON 0x01
#define		ST7579_DISPLAYCTRL_PARAM_INVERSE 0x05

#define ST7579_SETY 0x40
#define ST7579_SETY_MASK 0x0F
#define ST7579_SETY_RS 0
#define ST7579_SETY_H 0

#define ST7579_SETX 0x80
#define ST7579_SETX_MASK 0x7F
#define ST7579_SETX_RS 0
#define ST7579_SETX_H 0

#define ST7579_ROWDATAORDER 0x08
#define ST7579_ROWDATAORDER_MASK 0x04
#define ST7579_ROWDATAORDER_RS 0
#define ST7579_ROWDATAORDER_H 1

#define		ST7579_ROWDATAORDER_PARAM_DO 0x04

#define ST7579_SETBIAS 0x10
#define ST7579_SETBIAS_MASK 0x07
#define ST7579_SETBIAS_RS 0
#define ST7579_SETBIAS_H 1

#define ST7579_SETSTARTS6 0x04
#define ST7579_SETSTARTS6_MASK 0x01
#define ST7579_SETSTARTS6_RS 0
#define ST7579_SETSTARTS6_H 1

#define ST7579_SETSTART 0x40
#define ST7579_SETSTART_MASK 0x3F
#define ST7579_SETSTART_RS 0
#define ST7579_SETSTART_H 1

#define ST7579_SETVOP 0x80
#define ST7579_SETVOP_MASK 0x7F
#define ST7579_SETVOP_RS 0
#define ST7579_SETVOP_H 1

#define ST7579_PARTIALSCREEN_MODE 0x04
#define ST7579_PARTIALSCREEN_MODE_MASK 0x01
#define ST7579_PARTIALSCREEN_MODE_RS 0
#define ST7579_PARTIALSCREEN_MODE_H 2

#define		ST7579_PARTIALSCREEN_MODE_PARAM_PS 0x01

#define ST7579_PARTIALSCREEN_SIZE 0x08
#define ST7579_PARTIALSCREEN_SIZE_MASK 0x01
#define ST7579_PARTIALSCREEN_SIZE_RS 0
#define ST7579_PARTIALSCREEN_SIZE_H 2

#define		ST7579_PARTIALSCREEN_SIZE_PARAM_WS 0x01

#define ST7579_DISPLAYPART 0x10
#define ST7579_DISPLAYPART_MASK 0x07
#define ST7579_DISPLAYPART_RS 0
#define ST7579_DISPLAYPART_H 2

#define ST7579_TESTMODE 0x00
#define ST7579_TESTMODE_MASK 0x01
#define ST7579_TESTMODE_RS 0
#define ST7579_TESTMODE_H 3

#define ST7579_RESET 0x03
#define ST7579_RESET_MASK 0x00
#define ST7579_RESET_RS 0
#define ST7579_RESET_H 3

#define ST7579_FRAMERATE 0x08
#define ST7579_FRAMERATE_MASK 0x07
#define ST7579_FRAMERATE_RS 0
#define ST7579_FRAMERATE_H 3

#define ST7579_NLINE_INVERT 0x40
#define ST7579_NLINE_INVERT_MASK 0x1F
#define ST7579_NLINE_INVERT_RS 0
#define ST7579_NLINE_INVERT_H 3

#define ST7579_BOOSTER_EFFICIENCY 0x90
#define ST7579_BOOSTER_EFFICIENCY_MASK 0x0F
#define ST7579_BOOSTER_EFFICIENCY_RS 0
#define ST7579_BOOSTER_EFFICIENCY_H 3




/* st7579 library functions */
void st7579_init();
void st7579_go(uint8_t x, uint8_t y);
void st7579_write(uint8_t *buf, uint16_t len);

void st7579_command(uint8_t reg, uint8_t mask, uint8_t data, uint8_t h);
void st7579_reset();
void st7579_backlight_init();
void st7579_backlight(uint8_t onoff);
void st7579_rs_init();
void st7579_rs(uint8_t onoff);
void st7579_clear();
void st7579_testpattern();

void st7579_poweron();
void st7579_poweroff();
void st7579_display_normal();
void st7579_display_off();
void st7579_display_invert();
void st7579_display_allon();

void st7579_config_booster(uint8_t be, uint8_t pc);
void st7579_config_vlcd(uint8_t vop);
void st7579_config_bias(uint8_t bias);
void st7579_config_framerate(uint8_t framerate);
void st7579_config_startline(uint8_t st);



#endif /* ST7579_H */
