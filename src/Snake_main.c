#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Std_types.h"
#include "game_types.h"
#include "i2c.h"  
#include "sh1106.h"
#include "button.h"

extern uint8_t sh1106_buffer[SH1106_WIDTH * (SH1106_HEIGHT / 8)];
extern volatile uint8_t keypress;
uint8_t grow_len = 0;
uint8_t snake_tailX = 20;
uint8_t snake_tailY = 20;

uint8_t snake_headX = 25;
uint8_t snake_headY = 20;

uint8_t delay = 1000;

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

void InitSnake(void)
{     
    for(int i = snake_tailX; i <= (snake_headX); i++)
    {
        sh1106_Pixel(i,snake_headY,SET);    
    }
    
    sh1106_update_screen();
}

void SnakeMove(void)
{
    while(1)
    {
        /*Moving the snake from its current position*/
        if(SH1106_WIDTH - 1 > snake_headX)
        {
            switch (keypress)
            {
                case UP:
                    snake_headY++;
                    break;
                case DOWN:
                    snake_headY--;
                    break;
                case RIGHT:
                    snake_headX++;
                    break;
                case LEFT:
                    snake_headX--;
                    break;
                default:
                    snake_headX++;
                    break;

            }
            /*Adding head pixel*/
            /*Setting head pixel after checking if its border pixels*/
            if((0 != snake_headX) || (SH1106_WIDTH == snake_headX))
                sh1106_Pixel(snake_headX,snake_headY,SET);
            //sh1106_update_screen();
            /*Clearing tail pixel after checking if its border pixels*/
            clearTail();
            sh1106_update_screen();
        }
        else
        {
          /*Start from other end after boarder is reached*/
          snake_headX = 0;
          sh1106_update_screen();
        }
        /*Difficulty increases when delay is decreased*/
        _delay_ms(100);
       
        
    }
}

void clearTail(void)
{
    uint8_t left = INITVAL;
    uint8_t right = INITVAL;
    uint8_t top = INITVAL;
    uint8_t bottom = INITVAL;

    for (int i = 0; i < (SH1106_WIDTH * (SH1106_HEIGHT / 8)); i++)
    {
        int x = i % SH1106_WIDTH;
        int y = (i / SH1106_WIDTH) * 8;

        /* Omit border x */
        if (x > 0 && x < (SH1106_WIDTH - 1))
        {
            /* Check if byte is not set */
            if (sh1106_buffer[i] != 0x00)
            {
                for (int j = y; j < (y + 8) && j < SH1106_HEIGHT; j++)
                {
                    /* Omit border y */
                    if (j > 0 && j < (SH1106_HEIGHT - 1))
                    {
                        if (sh1106_GetPixel(x, j)) // pixel ON
                        {
                            left   = sh1106_GetPixel(x-1, j);
                            right  = sh1106_GetPixel(x+1, j);
                            top    = sh1106_GetPixel(x, j-1);
                            bottom = sh1106_GetPixel(x, j+1);
                            if ((left + right + top + bottom) == 1)
                            {
                                /*Check its not head pixel*/
                                if (!(x == snake_headX && j == snake_headY))
                                {
                                    /* found tail, clear tail */
                                    sh1106_Pixel(x,j,CLR);

                                    return;
                                }
                            }
                        }
                    }
                }
            }
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
    InitSnake();
    SnakeMove();

}
