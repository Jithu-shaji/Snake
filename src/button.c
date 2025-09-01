#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "../include/button.h"

#include <avr/iom328p.h>

volatile uint8_t keypress = 0;

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

ISR(INT0_vect)
{
    if (GetPin(DDRC,1))
        keypress = UP;
    else if (GetPin(DDRC,2))
        keypress = DOWN;
    else if  (GetPin(DDRC,3))
        keypress = LEFT;
    else if  (GetPin(DDRC,4))
        keypress = RIGHT;
    else
    {
        /*Do Nothing*/
    }

}