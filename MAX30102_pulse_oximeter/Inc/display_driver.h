#ifndef __DISPLAY_DRIVER
#define __DISPLAY_DRIVER

#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "spi.h"

#define GPIOAEN		(1U<<0)
#define GPIOBEN		(1U<<1)


#define GPIO_PIN_6		(1U<<6)
#define GPIO_PIN_3		(1U<<8)
#define GPIO_PIN_9		(1U<<9)



//#define DC_Pin GPIO_PIN_3
//#define DC_GPIO_Port GPIOA
//#define RST_Pin GPIO_PIN_9
//#define RST_GPIO_Port GPIOA
//#define CS_Pin GPIO_PIN_6
//#define CS_GPIO_Port GPIOB



void gc9a01_display_init(void);

void gc9a01_ctrl_gpio_init(void);
void gc9a01_spi_init(void);

#endif
