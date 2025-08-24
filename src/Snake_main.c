#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Std_types.h"
#include "game_types.h"
#include "i2c.h"  
#include "sh1106.h"

extern uint8_t sh1106_buffer[SH1106_WIDTH * (SH1106_HEIGHT / 8)];
uint8_t grow_len = 0;
uint8_t snake_PosX = 20;
uint8_t snake_PosY = 20;

void SetBorder(void)
{
    /*Loop for y*/
    for(int j = 0; j < SH1106_HEIGHT; j++)
    {
        /*Loop for x*/
        for(int i = 0; i < SH1106_WIDTH; i++)
        {
            /*Setting all pixel at top and bottom*/
            if((INITVAL == j) || (SH1106_HEIGHT-1 == j))
            {
                sh1106_Pixel(i,j,SET);
            }
            else
            {
                /*Setting all pixel at left and right end*/
                sh1106_Pixel(INITVAL,j,SET);
                sh1106_Pixel(SH1106_WIDTH-1,j,SET);
            }
        }
    }
    sh1106_update_screen();
}

void SetSnake(void)
{
       
    for(int i = snake_PosX; i <= (snake_PosX + INIT_LEN); i++)
    {
        sh1106_Pixel(i,snake_PosY,SET);    
    }
    sh1106_update_screen();
}

void SnakeMove(void)
{
    while(1)
    {
        if(SH1106_WIDTH - 1 > snake_PosX)
        {
            sh1106_Pixel(snake_PosX,snake_PosY,CLR);
            snake_PosX++;
            SetSnake();
        }
        else
        {
          snake_PosX = INITVAL + 1;
          SetSnake();
        }
    }
}



/* ---------- MAIN ---------- */
int main(void)
{
    i2cInit(400000, 1);
    sh1106_init();
    _delay_ms(10);
    sh1106_clear();
    _delay_ms(10);
    SetBorder();
    SetSnake();
    SnakeMove();

}
