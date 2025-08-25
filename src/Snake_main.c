#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Std_types.h"
#include "game_types.h"
#include "i2c.h"  
#include "sh1106.h"

extern uint8_t sh1106_buffer[SH1106_WIDTH * (SH1106_HEIGHT / 8)];
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
            /*Clearing tail pixel after checking if its border pixels*/
            if((0 != snake_tailX) || (SH1106_WIDTH == snake_tailX))
                sh1106_Pixel(snake_tailX,snake_tailY,CLR);
            snake_tailX++;
            /*reset tail to one when tail reaches boarder pixel*/
            if(SH1106_WIDTH-1 == snake_tailX)
                snake_tailX = 1;
            sh1106_update_screen();
            /*Adding head pixel*/
            snake_headX++; 
            /*Setting head pixel after checking if its border pixels*/
            if((0 != snake_headX) || (SH1106_WIDTH == snake_headX))
                sh1106_Pixel(snake_headX,snake_headY,SET);
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
