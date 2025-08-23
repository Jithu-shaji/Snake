#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"  
#include "ssd1306.h"


/* ---------- MAIN ---------- */
int main(void)
{
    i2cInit(400000, 1);
    ssd1306_init();
    _delay_ms(100);
    ssd1306_fill();

}
