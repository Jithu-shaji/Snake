#ifndef SSD1306_H_
#define SSD1306_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/* OLED I2C Address */
#define SH1106_ADDR 0x3C
#define SH1106_WIDTH   128
#define SH1106_HEIGHT  64
/*i2c init bit rate*/
#define BITRATE 400000U
/*Next byte is data or command*/
#define COMMAND 0x00
#define DATA 0x40

/* -------- PUBLIC APIs -------- */

void sh1106_command(uint8_t cmd);
void sh1106_command_buffer(uint8_t* cmd, uint8_t length);
void sh1106_data(uint8_t data);
void sh1106_update_screen(void);

void sh1106_init(void);
void sh1106_clear(void);
void sh1106_fill(void);

#endif /* SSD1306_H_ */
