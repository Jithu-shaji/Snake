#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "sh1106.h"

uint8_t sh1106_buffer[SH1106_WIDTH * SH1106_HEIGHT / 8] = {0};
  
void sh1106_command_buffer(uint8_t* cmd, uint8_t length)
{
    i2cStart();
    /*Slave address + Write*/
    i2cWrite(SLA_RW(SH1106_ADDR,WRITE));
    /*Next byte is command*/
    i2cWrite(COMMAND);
    for(uint8_t i = 0; i < length; i++)
    {
        i2cWrite(cmd[i]);
    }
    I2C_STOP();
}

void sh1106_command(uint8_t cmd)
{
    i2cStart();
    /*Slave address + Write*/
    i2cWrite(SLA_RW(SH1106_ADDR,WRITE));
    /*Next byte is command*/
    i2cWrite(COMMAND);
    i2cWrite(cmd);
    I2C_STOP();
}

void sh1106_data(uint8_t data)
{
    i2cStart();
    /*Slave address + Write*/
    i2cWrite(SLA_RW(SH1106_ADDR,WRITE));
    /*Next byte is data*/
    i2cWrite(DATA);               
    i2cWrite(data);
    I2C_STOP();
}

void sh1106_update_screen(void)
{
    for (uint8_t page = 0; page < 8; page++) 
    {
        /*Setting page address*/
        sh1106_command(0xB0 + page);   // Page start address (B0–B7)
        sh1106_command(0x02);          // Lower column start (low nibble)
        sh1106_command(0x10);          // Upper column start (high nibble)

  
        i2cStart();
        i2cWrite(SLA_RW(SH1106_ADDR, WRITE));  // Device address + Write
        i2cWrite(DATA);                         

        for (uint8_t col = 0; col < SH1106_WIDTH; col++) 
        {
            i2cWrite(sh1106_buffer[(page * SH1106_WIDTH) + col]);
        }

        I2C_STOP();
    }
}


void sh1106_init(void)
{
    _delay_ms(100);  // wait after power-up

    sh1106_command(0xAE); // Display OFF
    sh1106_command(0x40); // Set Display Start Line = 0
    sh1106_command(0xAF); // Display ON

}

void sh1106_clear(void)
{
    for (uint16_t i = 0; i < sizeof(sh1106_buffer); i++) 
    {
        sh1106_buffer[i] = 0x00;
    }
    sh1106_update_screen();
}

void sh1106_fill( ) 
{
    for (uint16_t i = 0; i < sizeof(sh1106_buffer); i++) 
    {
        sh1106_buffer[i] = 0xFF;
    }
    sh1106_update_screen();
}

void sh1106_drawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    if (x >= SH1106_WIDTH || y >= SH1106_HEIGHT) {
        return; // Out of bounds
    }

    uint16_t byteIndex = x + (y / 8) * SH1106_WIDTH;
    uint8_t bitMask = 1 << (y % 8);

    if (color) {
        sh1106_buffer[byteIndex] |= bitMask;   // Set pixel ON
    } else {
        sh1106_buffer[byteIndex] &= ~bitMask;  // Set pixel OFF
    }
}



