#ifndef __PULSE_OXIMETRY_LIB_H__
#define __PULSE_OXIMETRY_LIB_H__

#include<stdbool.h>
#include<stdint.h>
#include"i2c.h"

//Sampling time in seconds
#define Sampling_time  4

//Sampling frequency in Hz
#define FS             25
#define FS60        (FS * 60) //Samples per min

//Number of samples per processing batch
#define BUFFER_SIZE  (Sampling_time*FS)

#define SUM_OF_SQS    83325.0f
#define MEAN_IDX      ((BUFFER_SIZE-1)/(2.0f))

#define min_pearson_correlation 0.8f
#define min_autocorrelation_ratio 0.5f

#define MAX_HR   180 //BPM
#define MIN_HR    40 //BPM

#define MAX_SPO2   100//%
#define MIN_SPO2   85//%

#define LOWEST_PK_PK_INTERVAL    (FS60 / MAX_HR)
#define HIGHEST_PK_PK_INTERVAL   (FS60 / MIN_HR)

void compute_HR_SPO2(uint32_t *pun_ir_buffer,uint32_t n_buffer_length,
		             uint32_t *pun_red_buffer,
		             float *pn_spo2,int8_t *pch_spo2_valid,int32_t *pn_heart_rate,
					 int8_t *pch_hr_valid,float *ratio,float *correl);
#endif
