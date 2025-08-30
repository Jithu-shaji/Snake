#include <avr/io.h>
#include "button.h"


void SetPort(volatile uint8_t* DDRx, uint8_t Dir)
{
    if (OUT == Dir)
    {
        /*Setting bit*/
        *DDRx |= (1 << Dir);
    }
    else
    {
        /*Clearing bit*/
        *DDRx &= ~(1 << Dir);
    }

}


void SetPin(volatile uint8_t *port, uint8_t pin, uint8_t value)
{
    if (value == HIGH) {
        /*set bit -> HIGH*/
        *port |= (1 << pin);
    }
    else
    {
        /*clear bit -> LOW*/
        *port &= ~(1 << pin);
    }
}

uint8_t GetPin(volatile uint8_t* port, uint8_t pin)
{
    uint8_t retVal = 0;
    if (*port & (1 << pin))
    {
        retVal = 1 ;
    }
    else
    {
        /*Do Nothing*/
    }
    return retVal;
}