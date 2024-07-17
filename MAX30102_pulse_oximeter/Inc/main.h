
#ifndef MAIN_H_
#define MAIN_H_
#include "stm32f4xx.h"

#define DC_Pin  		(1U<<8)//GPIO_PIN_8
#define DC_GPIO_Port 	GPIOA
#define RST_Pin 		(1U<<9)//GPIO_PIN_9
#define RST_GPIO_Port 	GPIOA
#define CS_Pin 			(1U<<6)//GPIO_PIN_6
#define CS_GPIO_Port 	GPIOB

#endif
