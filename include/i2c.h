#ifndef I2C_H
#define I2C_H   


/*Setting register values for transmitting I2C STOP condition*/
#define I2C_STOP()   (TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN))
/*Setting slave address + read or write value to transmit with START condition*/
#define SLA_RW(addr,rw) (((addr) << (1)) | rw)

#define READ  1
#define WRITE 0
/*Number of times to retry*/
#define RETRY_CNT 3

/*Status Codes for Master Transmitter Mode*/

/*0x08: START condition transmitted*/
#define START_OK 0x08
/*0x18: SLA+W transmitted, ACK received*/        
#define ADDR_ACK_W  0x18
/*0x20: SLA+W transmitted, NACK received*/
#define ADDR_NACK_W 0x20
/*0x28: Data transmitted, ACK received*/
#define DATA_ACK_W  0x28
/*0x30: Data transmitted, NACK receive*/
#define DATA_NACK_W 0x30
/*0x38: Arbitration lost*/
#define ARBT_FAIL 0x38

/*Status Codes for Master Receiver Mode*/

/*0x48: SLA+R transmitted, ACK received*/        
#define ADDR_ACK_R  0x40
/*0x40: SLA+R transmitted, NACK received*/
#define ADDR_NACK_R 0x48
/*0x50: Data received, ACK returned*/
#define DATA_ACK_R  0x50
/*0x58: Data received, NACK returned*/
#define DATA_NACK_R 0x58


/*masking last two prescaler and unused bits*/
#define STAT_MASK 0xF8
/*Possible prescalar values*/
#define PRE_SCL_ONE 0x00
#define PRE_SCL_FOUR 0x01
#define PRE_SCL_SIXTEEN 0x02
#define PRE_SCL_SIXTYFOUR 0x03


void i2cInit(uint32_t freq, uint8_t prescl);
uint8_t i2cStart(void);
uint8_t i2cWrite(uint8_t data);
uint8_t i2cRead(uint8_t SlaveAddr);

#endif //I2C_H
