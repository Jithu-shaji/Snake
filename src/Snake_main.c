#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"  
#include "sh1106.h"


/* ---------- MAIN ---------- */
int main(void)
{
    i2cInit(400000, 1);
    sh1106_init();
    _delay_ms(10);
    sh1106_clear();
    _delay_ms(10);
    sh1106_fill();

}
