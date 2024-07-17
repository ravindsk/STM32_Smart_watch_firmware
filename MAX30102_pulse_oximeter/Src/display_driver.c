#include "display_driver.h"


SPI_HandleTypeDef hspi1;


/**SPI1 GPIO Configuration
PA5     ------> SPI1_SCK
PA6     ------> SPI1_MISO
PA7     ------> SPI1_MOSI /DIN
PA8		------> DC
PA9		------> RST
PB6		------> CS
3.3v    ------> VCC
*/
void gc9a01_display_init(void)
{
	gc9a01_ctrl_gpio_init();
	gc9a01_spi_init();
}


void gc9a01_ctrl_gpio_init(void)
{
	/*Initialize RST, DC and CS lines as output*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOBEN;

	CS_GPIO_Port->MODER |= (1U<<12);
	CS_GPIO_Port->MODER &= ~(1U<<13);

	RST_GPIO_Port->MODER |= (1U<<18);
	RST_GPIO_Port->MODER &= ~(1U<<19);

	DC_GPIO_Port->MODER |= (1U<<16);
	DC_GPIO_Port->MODER &= ~(1U<<17);

}

void gc9a01_spi_init(void)
{
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction =  SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity =  SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase =  SPI_PHASE_1EDGE;
	hspi1.Init.NSS =  SPI_NSS_SOFT;
	hspi1.Init.BuadRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;


	/*Initialize spi*/
	spi_init(&hspi1);


}
