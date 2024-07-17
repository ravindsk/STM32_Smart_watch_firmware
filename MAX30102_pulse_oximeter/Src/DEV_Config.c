/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"
#include "timebase.h"
extern SPI_HandleTypeDef hspi1;

/********************************************************************************
function:	Delay function
note:
	Driver_Delay_ms(xms) : Delay x ms
********************************************************************************/

void DEV_Digital_Write(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Value) {
    if (Value == 0) {
        GPIOx->BSRR = (uint32_t)Pin << 16; // Reset the pin (BSRR register, reset part)
    } else {
        GPIOx->BSRR = Pin; // Set the pin (BSRR register, set part)
    }
}

uint8_t DEV_Digital_Read(GPIO_TypeDef* GPIOx, uint16_t Pin) {
    if ((GPIOx->IDR & Pin) != 0) {
        return 1;
    } else {
        return 0;
    }
}
void DEV_delay_ms(uint16_t xms )
{
	delay(xms);
}


void DEV_SPI_WRite(UBYTE _dat)
{
	spi_transmit(&hspi1, (uint8_t *)&_dat, 1, 500);
}

int DEV_Module_Init(void)
{
    DEV_Digital_Write(DEV_DC_PIN, 1);
    DEV_Digital_Write(DEV_CS_PIN, 1);
    DEV_Digital_Write(DEV_RST_PIN, 1);
		return 0;
}

void DEV_Module_Exit(void)
{
    DEV_Digital_Write(DEV_DC_PIN, 0);
    DEV_Digital_Write(DEV_CS_PIN, 0);
    //close 
    DEV_Digital_Write(DEV_RST_PIN, 0);
}
