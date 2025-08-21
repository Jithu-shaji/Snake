#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include "i2c.h"
#include "Std_types.h"



uint8_t i2cStart()
{
    uint8_t retVal = E_NOT_OK;

    /*Setting register values for transmitting I2C START condition*/
    TWCR = (1 << TWINT) | (1<<TWSTA) | (1<<TWEN);
    /*Starting watchdog to prevent infinite looping*/
    wdt_enable(WDTO_60MS);
    /*TWINT will be updated as 0 after START condition is transmitted*/
    while (!(TWCR & (1<<TWINT))); 
    /*Disable watchdog on loop exit*/
    wdt_disable();
    /*Checking TWSR register with masking last two prescaler and unused bits*/
    if(START_OK == (TWSR & STAT_MASK))
    {
        retVal = E_OK;
    }
    
    return retVal;

}

uint8_t i2cWrite(uint8_t data)
{
    uint8_t Status = 0;
    uint8_t retVal = E_NOT_OK;
    /*Initiate start condition*/
    retVal = i2cStart();
    
    if (E_OK == retVal)
    {
        /*Loading Data to be transmitted to TWDR register*/
        TWDR = data;
        /*Setting register values for initiating transmission*/
        TWCR = (1<<TWINT) | (1<<TWEN);
        /*Wait till the TWINT bit gets set after transmission completed*/
        while (!(TWCR & (1<<TWINT)));
        
        /*Masking TWSR register Prescalar to get status data*/
        Status = TWSR & STAT_MASK;
        /*Check status register value for write Acknowledgment state*/
        if((ADDR_ACK_W == Status) || (DATA_ACK_W == Status))
        {
            retVal = E_OK;
        }  
        else if((ADDR_NACK_W == Status) || (DATA_NACK_W == Status))
        {
            retVal = E_NACK;
        } 
        else
        {
            /*Do Nothing*/ 
        }
    }
    else 
    {
        /*Do Nothing*/ 
    }
    /*Initiate stop condition*/
    I2C_STOP();
    
    return retVal;
}

uint8_t i2cRead(uint8_t SlaveAddr)
{
    uint8_t Status = 0;
    uint8_t retVal = E_NOT_OK;
    uint8_t data = 0;
    /*Initiate start condition*/
    retVal = i2cStart();
    
    if (E_OK == retVal)
    {
        /*Loading slave adder from which to be received to TWDR register*/
        TWDR = SlaveAddr;
        /*Setting register values for initiating transmission*/
        TWCR = (1<<TWINT) | (1<<TWEN);
        /*Wait till the TWINT bit gets set after transmission completed*/
        while (!(TWCR & (1<<TWINT)));
        
        /*Masking TWSR register Prescalar to get status data*/
        Status = TWSR & STAT_MASK;
        /*Check status register value for read Acknowledgment state*/
        if(ADDR_ACK_R == Status)
        {
            /* Send NACK since we are reading only 1 byte */
            TWCR = (1<<TWINT) | (1<<TWEN);
            while (!(TWCR & (1<<TWINT)));

            Status = TWSR & STAT_MASK;
            /* Send NACK since we are reading only 1 byte */
            if (DATA_ACK_R == Status || DATA_NACK_R == Status)
            {
                data = TWDR; /*TO DO : pass data as pointer*/
                retVal = E_OK;
            }
        }       
        else if(ADDR_NACK_R == Status)
        {
            retVal = E_NACK;
        }
        else
        {
            /*Do Nothing*/ 
        }
    }
    
    /*Initiate stop condition*/
    I2C_STOP();
    
    return data;   
}
