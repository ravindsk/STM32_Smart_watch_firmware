#ifndef __MAX30102_LIB_H__
#define __MAX30102_LIB_H__

#include"pulse_oximetry_lib.h"
#include"max30102.h"
#include<stdbool.h>
#include<stdint.h>

bool get_pa10_state(void);

void max30102_init(void);
void pa10_gpio_init(void);
void max30102_process(void);

#endif
