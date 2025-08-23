#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_buffer[1024] = {0};
  
void ssd1306_command(uint8_t cmd)
{
    i2cStart();
    /*Slave address + Write*/
    i2cWrite(SLA_RW(SSD1306_ADDR,WRITE));
    /*Next byte is command*/
    i2cWrite(COMMAND);               
    i2cWrite(cmd);
    I2C_STOP();
}

void ssd1306_data(uint8_t data)
{
    i2cStart();
    /*Slave address + Write*/
    i2cWrite(SLA_RW(SSD1306_ADDR,WRITE));
    /*Next byte is data*/
    i2cWrite(DATA);               
    i2cWrite(data);
    I2C_STOP();
}

void ssd1306_updateScreen(void) 
{
    i2cStart();
    /*Slave address + Write*/
    i2cWrite(SLA_RW(SSD1306_ADDR,WRITE));
    /*Next byte is data*/
    i2cWrite(DATA);
    
    for (uint16_t i = 0; i < sizeof(ssd1306_buffer); i++) 
    {
        i2cWrite(ssd1306_buffer[i]);
    }
    
    I2C_STOP();
}


void ssd1306_init(void)
{
    _delay_ms(100);  // wait after power-up

    ssd1306_command(0xAE); // Display OFF (start init safely)
    ssd1306_command(0x20); // Set Memory Addressing Mode
    ssd1306_command(0x00); // Horizontal addressing mode (usually preferred)
    ssd1306_command(0x21); // Column address range
    ssd1306_command(0x00); 
    ssd1306_command(0x7F);
    ssd1306_command(0x22); // Page address range
    ssd1306_command(0x00); 
    ssd1306_command(0x07);
    ssd1306_command(0xAF); // Display ON

}

void ssd1306_clear(void)
{
    for (uint16_t i = 0; i < sizeof(ssd1306_buffer); i++) 
    {
        ssd1306_buffer[i] = 0x00;
    }
}

void ssd1306_fill(void)
{
    for (uint16_t i = 0; i < sizeof(ssd1306_buffer); i++) 
    {
        ssd1306_buffer[i] = 0xFF;
    }
    ssd1306_updateScreen();
    
}



