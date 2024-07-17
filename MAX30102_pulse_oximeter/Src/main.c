#include "stm32f4xx.h"
#include  "fpu.h"
#include "uart.h"
#include<stdio.h>
#include "timebase.h"
#include "max30102_lib.h"
#include "i2c.h"
#include "main.h"
#include "rtc.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "LCD_Test.h"
#include "spi.h"
#include "timebase.h"
#include "uart.h"
#include "display_driver.h"
#include <pulse_ox_display.h>



#define GPIOAEN (1U<<0)
#define PIN5     (1U<<5)
#define LED_PIN   PIN5

/*Module
 * FPU
 * UART
 * GPIO
 * TIMEBASE
 */


int main()
{
	//Enable FPU
	fpu_enable();

	//Initialize UART
	debug_uart_init();

	rtc_init();
	//Initialize Timebase
	timebase_init();

	gc9a01_display_init();

	i2c1_init();

	max30102_init();

	pa10_gpio_init();


	gc9a01_start();

	while(1)
	{
		max30102_process();
		show_time();
	}
}

