#ifndef __I2C_H__
#define __I2C_H__
#include<stdint.h>
void i2c1_init();
void I2C_byteRead (char saddr, char maddr, char *data );
void I2C1_burstRead(char saddr, char maddr, char *data, int n);
void I2C1_write_byte( char saddr, char maddr, char data);
void I2C1_burstWrite(char saddr,char maddr, char *data,int n);
void i2c_mem_write(uint16_t saddr, uint16_t maddr,uint16_t mem_addr_sz,uint8_t *p_data,uint16_t size);
void i2c_mem_read(uint16_t saddr, uint16_t maddr,uint16_t mem_addr_sz,uint8_t *p_data,uint16_t size);

#endif
