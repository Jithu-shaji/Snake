#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H


#define IN  0
#define OUT  1
#define LOW     0
#define HIGH    1

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define SELECT 5

void SetDir(volatile uint8_t* DDRx, uint8_t Dir);
void SetPin(volatile uint8_t *port, uint8_t pin, uint8_t value);
uint8_t GetPin(volatile uint8_t* port, uint8_t pin);
void Int0_int();

#endif //SNAKE_BUTTON_H