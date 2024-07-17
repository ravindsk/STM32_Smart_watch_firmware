#include"max30102.h"

void max30102_write_reg(uint8_t reg_addr, uint8_t data)
{
	i2c_mem_write(I2C_WRITE_ADDR, reg_addr, 1, &data,1);
}


void max30102_read_reg(uint8_t reg_addr, uint8_t *data)
{
	i2c_mem_read(I2C_READ_ADDR, reg_addr, 1, &data,1);
}

void max30102_params_init(void)
{
	/*Enable interrupts for FIFO almost full and PPG RDY*/
	max30102_write_reg(REG_INTR_ENABLE_1, 0xC0U);

	max30102_write_reg(REG_INTR_ENABLE_2, 0x00U); // Interrupt Enable 2 Register

	// Initialize all FIFO pointers to zero to reset the FIFO buffer
	max30102_write_reg(REG_FIFO_WR_PTR, 0x00U);  // FIFO Write Pointer Register
	max30102_write_reg(REG_OVF_COUNTER, 0x00U);  // Over Flow Counter Register
	max30102_write_reg(REG_FIFO_RD_PTR, 0x00U);  // FIFO Read Pointer Register

	// Configure FIFO: set sample averaging to 4, and set FIFO almost full threshold to maximum
	max30102_write_reg(REG_FIFO_CONFIG, 0x4FU);

	// Set the operational mode to SpO2 (uses both Red and IR LEDs)
	max30102_write_reg(REG_MODE_CONFIG, 0x03U);  // Mode Configuration Register

	// Configure SpO2 measurement settings: highest LED pulse width, 100 Hz sampling rate,
	// and ADC range to 4096 nA
	max30102_write_reg(REG_SPO2_CONFIG, 0x27U);  // SpO2 Configuration Register

	// Set the current for both LEDs (LED1 and LED2) to approximately 7mA
	max30102_write_reg(REG_LED1_PA, 0x24U);      // LED1 Pulse Amplitude Register
	max30102_write_reg(REG_LED2_PA, 0x24U);      // LED2 Pulse Amplitude Register

	// Set the pilot LED current to approximately 25mA
	max30102_write_reg(REG_PILOT_PA, 0x7FU);     // Pilot LED Pulse Amplitude Register
}




/**
 * Retrieves a set of samples from the MAX30102 FIFO register.
 *
 * This function reads red and infrared (IR) LED data samples from the FIFO data register
 * of the MAX30102 sensor. It is typically used to fetch the latest sensor readings for
 * processing heart rate and oxygen saturation calculations. The function also handles
 * clearing interrupt flags that indicate new data is available.
 *
 * @param[out] pun_red_led Pointer to store the accumulated red LED data.
 * @param[out] pun_ir_led Pointer to store the accumulated IR LED data.
 */
void max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led)
{
    uint32_t un_temp;
    uint8_t uch_temp;
    uint8_t uch_i2c_data[6];

    // Clear any pending interrupts by reading the interrupt status registers
    max30102_read_reg(REG_INTR_STATUS_1, &uch_temp);
    max30102_read_reg(REG_INTR_STATUS_2, &uch_temp);

    // Read 6 bytes from the FIFO data register
    i2c_mem_read(I2C_READ_ADDR, REG_FIFO_DATA, 1, uch_i2c_data, 6U);

    // Initialize the output data
    *pun_ir_led = 0UL;
    *pun_red_led = 0UL;

    // Start assembling the 18-bit red LED data from 3 bytes of I2C data
    un_temp = (uint32_t)uch_i2c_data[0];  // Convert the first byte of red LED data to a 32-bit integer
    un_temp <<= 16;  // Shift the byte left by 16 bits to position it as the most significant byte
    *pun_red_led += un_temp;  // Add this byte to the red LED data accumulator

    un_temp = (uint32_t)uch_i2c_data[1];  // Convert the second byte of red LED data to a 32-bit integer
    un_temp <<= 8;  // Shift the byte left by 8 bits to position it as the middle byte
    *pun_red_led += un_temp;  // Add this byte to the red LED data accumulator

    un_temp = (uint32_t)uch_i2c_data[2];  // Convert the third byte of red LED data to a 32-bit integer
    *pun_red_led += un_temp;  // Add this byte directly to the red LED data accumulator (this byte is the least significant)

    // Start assembling the 18-bit IR LED data from 3 bytes of I2C data
    un_temp = (uint32_t)uch_i2c_data[3];  // Convert the first byte of IR LED data to a 32-bit integer
    un_temp <<= 16;  // Shift the byte left by 16 bits to position it as the most significant byte
    *pun_ir_led += un_temp;  // Add this byte to the IR LED data accumulator

    un_temp = (uint32_t)uch_i2c_data[4];  // Convert the second byte of IR LED data to a 32-bit integer
    un_temp <<= 8;  // Shift the byte left by 8 bits to position it as the middle byte
    *pun_ir_led += un_temp;  // Add this byte to the IR LED data accumulator

    un_temp = (uint32_t)uch_i2c_data[5];  // Convert the third byte of IR LED data to a 32-bit integer
    *pun_ir_led += un_temp;  // Add this byte directly to the IR LED data accumulator (this byte is the least significant)

    // Mask the most significant bits to get the correct data range
    *pun_red_led &= 0x03FFFF;  // Mask the upper 6 bits for 18-bit data
    *pun_ir_led &= 0x03FFFF;   // Mask the upper 6 bits for 18-bit data
}


void max30102_reset(void)
{
	max30102_write_reg(REG_MODE_CONFIG, 0x40U);
}

