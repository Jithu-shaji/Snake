#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "i2c.h"
#include "Std_types.h"

uint8_t data = 0;

void i2cInit(uint32_t freq, uint8_t prescl)
{
    switch (prescl)
    {
        case 1:
            TWSR = (TWSR & STAT_MASK) | PRE_SCL_ONE;
            break;
        case 4:
            TWSR = (TWSR & STAT_MASK) | PRE_SCL_FOUR;
            break;
        case 16:
            TWSR = (TWSR & STAT_MASK) | PRE_SCL_SIXTEEN;
            break;
        case 64:
            TWSR = (TWSR & STAT_MASK) | PRE_SCL_SIXTYFOUR;
            break;
        default: 
            TWSR = (TWSR & STAT_MASK) | PRE_SCL_ONE;
            break;              
    }
    /*Calculating i2c bit rate*/
    TWBR = (uint8_t) (((F_CPU / freq) - 16) / (2 * prescl));      
}


uint8_t i2cStart(void)
{
    uint8_t retVal = E_NOT_OK;
    uint16_t timeout = 10000;

    /*Setting register values for transmitting I2C START condition*/
    TWCR = (1 << TWINT) | (1<<TWSTA) | (1<<TWEN);
    /*TWINT will be updated as 0 after START condition is transmitted*/
    while (!(TWCR & (1 << TWINT)))
    {
        if (--timeout == 0)
        {
            /*release bus*/
            I2C_STOP();    
            return E_TIMEOUT;
        }
    }
    /*Checking TWSR register with masking last two prescaler and unused bits*/
    if(START_OK == (TWSR & STAT_MASK))
    {
        retVal = E_OK;
    }
    else
    {
        /*Initiate stop condition*/
        I2C_STOP();
    }
    
    return retVal;

}

uint8_t i2cWrite(uint8_t data)
{
    uint8_t Status = 0;
    uint8_t retVal = E_NOT_OK;
    uint8_t retry = RETRY_CNT;
     /*Check if retry count exceeded*/
    while(retry > 0)
    {
        /*Loading Data to be transmitted to TWDR register*/
        TWDR = data;
        /*Setting register values for initiating transmission*/
        TWCR = (1<<TWINT) | (1<<TWEN);
        /*Wait till the TWINT bit gets set after transmission completed*/
        while (!(TWCR & (1<<TWINT)));        
        /*Masking TWSR register Prescalar to get status data*/
        Status = TWSR & STAT_MASK;
        /*Check Arbitration lost*/
        if (ARBT_FAIL == Status) 
        {   
            retry--;
            _delay_us(10); 
            retVal = E_ARBLOST;
            continue;           
        }     
        /*Check status register value for write Acknowledgment state*/
        else if((ADDR_ACK_W == Status) || (DATA_ACK_W == Status))
        {                         
            retVal = E_OK;
            /*stopping further re-transmission*/ 
            break;
        }  
        else if((ADDR_NACK_W == Status) || (DATA_NACK_W == Status))
        {          
            retry--;
            retVal = E_NACK;
            continue;
        } 
        else
        {
            I2C_STOP(); 
            break;
        }
        
    }
   
    return retVal;
}

uint8_t i2cRead(uint8_t SlaveAddr)
{
    uint8_t Status = 0;
    uint8_t retVal = E_NOT_OK;
    uint8_t retry = RETRY_CNT;
    
    /*Check if retry count exceeded*/
    while(retry > 0)
    {
        /*Loading slave adder from which to be received to TWDR register*/
        TWDR = SlaveAddr;
        /*Setting register values for initiating transmission*/
        TWCR = (1<<TWINT) | (1<<TWEN);
        /*Wait till the TWINT bit gets set after transmission completed*/
        while (!(TWCR & (1<<TWINT)));
        
        /*Masking TWSR register Prescalar to get status data*/
        Status = TWSR & STAT_MASK;
        /*Check Arbitration lost*/
        if (ARBT_FAIL == Status) 
        {   
            retry--;
            _delay_us(10);  
            retVal = E_ARBLOST;
            continue;           
        }
        /*Check status register value for read Acknowledgment state*/
        else if(ADDR_ACK_R == Status)
        {
            /* Send NACK since we are reading only 1 byte */
            TWCR = (1<<TWINT) | (1<<TWEN);
            while (!(TWCR & (1<<TWINT)));

            Status = TWSR & STAT_MASK;
            /* Send NACK since we are reading only 1 byte */
            if (DATA_ACK_R == Status || DATA_NACK_R == Status)
            {
                data = TWDR; /*TO DO : Multiple byte receive logic*/               
                /*Initiate stop condition*/
                retVal = E_OK;
                /*stopping further re-transmission*/
                break;
            }
        }       
        else if(ADDR_NACK_R == Status)
        {
            retry--;
            retVal = E_NACK;
            continue;
        }
        else
        {
            I2C_STOP();
            break;
        }
    }                      
    return retVal;   
}
