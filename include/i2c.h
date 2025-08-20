#ifndef I2C_H
#define I2C_H   

/*Setting register values for transmitting I2C STOP condition*/
#define I2C_STOP()   (TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN))
        
/*0x18: SLA+W transmitted, ACK received*/        
#define ADDR_ACK 0x18
/*0x28: Data transmitted, ACK received*/
#define DATA_ACK 0x28
/*0x20: SLA+W transmitted, NACK received*/
#define ADDR_NACK 0x20
/*0x30: Data transmitted, NACK receive*/
#define DATA_NACK 0x30

uint8_t i2cStart();
uint8_t i2cWrite(uint8_t data);
void i2cRead(uint8_t data);

#endif
