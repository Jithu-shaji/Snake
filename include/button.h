#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H


#define IN  0
#define OUT  1
#define LOW     0
#define HIGH    1

void SetPort(volatile uint8_t* DDRx, uint8_t Dir);
void SetPin(volatile uint8_t *port, uint8_t pin, uint8_t value);
uint8_t GetPin(volatile uint8_t* port, uint8_t pin);

#endif //SNAKE_BUTTON_H