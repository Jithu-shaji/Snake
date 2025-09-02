#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"


volatile uint8_t keypress = 0;

void SetDir(volatile uint8_t* DDRx, uint8_t Dir)
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

void Int0_int()
{
    SetDir(&DDRD, IN);
    SetPin(&PORTD , 2, LOW);
    /*Enable external interrupt INT0*/
    EIMSK |= (1 << INT0);
    /*Trigger on raising edge*/
    EICRA |= (1 << ISC01) | (1 << ISC00);
    sei();
}

ISR(INT0_vect)
{
    if (GetPin(&DDRC,1))
        keypress = UP;
    else if (GetPin(&DDRC,2))
        keypress = DOWN;
    else if  (GetPin(&DDRC,3))
        keypress = LEFT;
    else if  (GetPin(&DDRC,4))
        keypress = RIGHT;
    else
    {
        /*Do Nothing*/
    }

}