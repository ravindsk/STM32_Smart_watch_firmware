#include"max30102_lib.h"
#include"stm32f4xx.h"
#include<stdbool.h>
#include"pulse_ox_display.h"
#include"pulse_oximetry_lib.h"

static uint32_t aun_ir_buffer[BUFFER_SIZE];
static uint32_t aun_red_buffer[BUFFER_SIZE];

#define INT_PIN (1U<<10)

int8_t ch_spo2_valid;
int8_t ch_hr_valid;
int32_t n_heart_rate;
float n_spo2;

float ratio_val;
float correl_val;
bool get_pa10_state(void);


void max30102_init(void)
{
	uint8_t dummy;
	max30102_reset();
	max30102_read_reg(REG_INTR_STATUS_1,&dummy);
	max30102_params_init();

}

void max30102_process(void)
{
	int i;
	for(i=0;i<BUFFER_SIZE;i++)
	{
		/*Wait until interrupt pin is set*/
		while(get_pa10_state()==1){}

		//Read MAX FIFO
		max30102_read_fifo((aun_red_buffer+i),(aun_ir_buffer+i));
	}
	//Then compute HR and SPO2
	compute_HR_SPO2(aun_ir_buffer,BUFFER_SIZE,
			         aun_red_buffer,
			          &n_spo2, &ch_spo2_valid,&n_heart_rate,
						 &ch_hr_valid,&ratio_val,&correl_val);

	if((n_heart_rate >MIN_HR) && (n_heart_rate <MAX_HR))
	{
		update_pulse_ox_heart_rate(n_heart_rate);
	}

	if((n_spo2 > MIN_SPO2) && (n_spo2 < MAX_SPO2))
		{
		update_pulse_ox_spo2(n_spo2);
		}
}
//PA10 will be interrupt pin for max30102
void pa10_gpio_init(void)
{
	RCC->AHB1ENR |=(1U<<0);

	GPIOA->MODER &=~(1U<<20);
	GPIOA->MODER &=~(1U<<21);

}

bool get_pa10_state(void)
{
	if(GPIOA->IDR &(INT_PIN))
	{
		return true;
	}
	else
	{
		return false;
	}
}
