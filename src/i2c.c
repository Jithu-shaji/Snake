#include <stdint.h>
#include <avr/io.h>
#include "i2c.h"

uint8_t i2cStart()
{
    uint8_t retVal =0 ;

    /*Setting register values for transmitting I2C START condition*/
    TWCR = (1 << TWINT) | (1<<TWSTA) | (1<<TWEN);
    /*Starting watchdog to prevent infinite looping*/
    wdt_enable(WDTO_60MS);
    /*TWINT will be updated as 0 after START condition is transmitted*/
    while (!(TWCR & (1<<TWINT))); 
    /*Disable watchdog on loop exit*/
    wdt_disable();
    /*Checking TWSR register with masking last two prescaler and unused bits*/
    if(0x08 == (TWSR & 0xF8))
    {
        retVal = 1;
    }
    
    return retVal;

}
void i2cStop()
{
    /*Setting register values for transmitting I2C STOP condition*/
    TWCR = (1 << TWINT) | (1<<TWSTO) | (1<<TWEN);    

}

uint8_t i2cWrite(uint8_t data)
{
    uint8_t Status;
    uint8_t retVal = 0;
    /*Loading Data to be transmitted to TWDR register*/
    TWDR = data;
    /*Setting register values for initiating transmission*/
    TWCR = (1<<TWINT) | (1<<TWEN);
    /*Wait till the TWINT bit gets set after transmission completed*/
    while (!(TWCR & (1<<TWINT)));
    /*Masking TWSR register Prescalar to get status data*/
    Status = TWSR & 0xF8;
    if((0x18 == Status) || (0x28 == Status))
    {
        // 0x18: SLA+W transmitted, ACK received
        // 0x28: Data transmitted, ACK received
        retVal = 1;
    }         
    else if((0x20 == Status) || (0x30 == Status))
    {
        // 0x20: SLA+W transmitted, NACK received
        // 0x30: Data transmitted, NACK received
        retVal = 2;
    }
    else
    {
        /*Do Nothing*/ 
    }
    
    return retVal;

}

void i2cRead(uint8_t data)
{
    

}
