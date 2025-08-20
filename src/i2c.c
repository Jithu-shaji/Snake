#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
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

uint8_t i2cWrite(uint8_t data)
{
    uint8_t Status = 0;
    uint8_t retVal = 0;
    /*Loading Data to be transmitted to TWDR register*/
    TWDR = data;
    /*Setting register values for initiating transmission*/
    TWCR = (1<<TWINT) | (1<<TWEN);
    /*Wait till the TWINT bit gets set after transmission completed*/
    while (!(TWCR & (1<<TWINT)));
    /*Masking TWSR register Prescalar to get status data*/
    Status = TWSR & 0xF8;
    if((ADDR_ACK == Status) || (DATA_ACK == Status))
    {
        retVal = 1;
    }         
    else if((ADDR_NACK == Status) || (DATA_NACK == Status))
    {
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
