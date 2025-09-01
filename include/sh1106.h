#ifndef SSD1306_H
#define SSD1306_H

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
#define SET 1
#define CLR 0


void sh1106_command(uint8_t cmd);
void sh1106_command_buffer(uint8_t* cmd, uint8_t length);
void sh1106_data(uint8_t data);
void sh1106_Pixel(uint8_t x, uint8_t y, uint8_t mode);
void sh1106_update_screen(void);


void sh1106_init(void);
void sh1106_clear(void);
void sh1106_fill(void);

#endif // SSD1306_H
