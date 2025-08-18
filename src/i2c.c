#include <stdint.h>
#include <avr/io.h>
#include "i2c.h"

uint8_t i2cStart()
{
    uint8_t retVal =0 ;

    /*Setting register values for transmitting I2C START condition*/
    TWCR = (1 << TWINT) | (1<<TWSTA) | (1<<TWEN);
    /* TWINT will be updated as 0 after START condition is transmitted */
    while (!(TWCR & (1<<TWINT))); 
    /*Checking TWSR register with masking last two prescaler and unused bits*/
    if(0x08 == (TWSR & 0xF8))
      retVal = 1;
    
    return retVal;

}
void i2cStop()
{
    

}

void i2cWrite(uint8_t data)
{
    

}

void i2cRead(uint8_t data)
{
    

}
