#ifndef SSD1306_H_
#define SSD1306_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/* OLED I2C Address */
#define SSD1306_ADDR 0x3C
/*i2c init bit rate*/
#define BITRATE 400000U
/*Next byte is data or command*/
#define COMMAND 0x00
#define DATA 0x40

/* -------- PUBLIC APIs -------- */

void ssd1306_command(uint8_t cmd);
void ssd1306_data(uint8_t data);
void ssd1306_updateScreen(void); 

void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_fill(void);

#endif /* SSD1306_H_ */
