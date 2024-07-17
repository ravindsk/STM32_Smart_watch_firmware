#ifndef __MAX30102_H__
#define __MAX30102_H__

#include<stdbool.h>
#include<stdint.h>
#include"i2c.h"


#define I2C_WRITE_ADDR 0xAE
#define I2C_READ_ADDR 0xAF

//MAX30102 register addresses

#define REG_INTR_STATUS_1         0x00//Interrupt status 1
#define REG_INTR_STATUS_2         0x01//Interrupt status 2
#define REG_INTR_ENABLE_1         0x02//Interrupt enable 1
#define REG_INTR_ENABLE_2         0x03//Interrupt enable 2
#define REG_FIFO_WR_PTR           0x04//FIFO writer pointer
#define REG_OVF_COUNTER           0x05//FIFO Overflow counter
#define REG_FIFO_RD_PTR           0x06//FIFO Read pointer
#define REG_FIFO_DATA             0x07//FIFIO Data register
#define REG_FIFO_CONFIG           0x08//FIFO Configuration
#define REG_MODE_CONFIG           0x09//MODE Configuration
#define REG_SPO2_CONFIG           0x0A//SpO2 Configuration
#define REG_LED1_PA         	  0x0C//LED1 Pulse amplitude
#define REG_LED2_PA				  0x0D//LED2 Pulse amplitude
#define REG_PILOT_PA              0x10//Pilot LED Pulse amplitude
#define REG_MULTI_LED_CTRL1       0x11//Multi-LED Mode Control 1
#define REG_MULTI_LED_CTRL2       0x12//Multi-LED Mode Control 2
#define REG_TEMP_INTR             0x1F//Temperature interrupt
#define REG_TEMP_FRAC             0x20//Temperature fraction
#define REG_TEMP_CONGIG           0x21//Temperature configuration
#define REG_PROX_INT_TRESH        0x30//Proximity interrupt threshold
#define REG_REV_ID                0xFE//Revision ID
#define REG_PART_ID               0xFF//Part ID


void max30102_reset(void);
void max30102_read_fifo(uint32_t *pun_red_led,uint32_t *pun_ir_led);
void max30102_params_init(void);
void max30102_read_reg(uint8_t reg_addr,uint8_t *data);
void max30102_write_reg(uint8_t reg_addr,uint8_t data);

#endif

