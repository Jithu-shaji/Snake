#ifndef I2C_H
#define I2C_H

uint8_t i2cStart();
void i2cStop();
uint8_t i2cWrite(uint8_t data);
void i2cRead(uint8_t data);

#endif
