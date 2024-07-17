#include "pulse_oximetry_lib.h"
#include<math.h>
#include<stdio.h>
#include"timebase.h"

/*This function helps you understand how a process variable changes over time*/
float calculate_linear_regression_beta(float *data_points,float mean_index, float sum_of_squares);

//This calculates the RMS
float get_rms(float *data_points, int length, float *sumsq);

/*
 *  PPG signal analysis, this function might be used to:
 *  	1.Compare the red and IR signals to detect synchronization.
 * 		2.Identify periods where the signals are highly similar
 *  	3.Provide a quick measure of the overall similarity between the two signals
 *
 *  	We need to see if the IR and RED values are good enough to process SpO2
 *  	(We need both of them to be good to process SpO2.This function finds correlation between them)

*/
float get_correlation_prod(float*x_data,float*y_data,int length);

//Calculate lag(offset) between signals
float calculate_autocorrelation(float *data_points,int length, int lag);

void periodicity_search_init(float *data_points, int length, int32_t *last_periodicity, int max_distance,float min_auto_ratio,float auto_lag0);

void sig_periodicity(float *data_points, int length,
		             int32_t *last_periodicity, int min_distance, int max_distance
		              ,float min_auto_ratio, float auto_lag0, float *ratio);

static int32_t n_last_peak_interval=LOWEST_PK_PK_INTERVAL;

void compute_HR_SPO2(uint32_t *pun_ir_buffer,uint32_t n_buffer_length,
		             uint32_t *pun_red_buffer,
		             float *pn_spo2,int8_t *pch_spo2_valid,int32_t *pn_heart_rate,
					 int8_t *pch_hr_valid,float *ratio,float *correl)
{
	//Declare local variables
		int k;
		float f_ir_mean,f_red_mean, f_ir_sumsq,f_red_sumsq;//Holds mean values for red,IR,sum of squares
		float y_ac,x_ac,xy_ratio; // AC components
		float beta_ir,beta_red,x;//correlation
		float an_x[BUFFER_SIZE];
		float an_y[BUFFER_SIZE];
		float *ptr_x,*ptr_y;


		f_ir_mean = 0.0;
		f_red_mean = 0.0;

		for(k= 0; k < n_buffer_length; k++)
		{
			f_ir_mean +=pun_ir_buffer[k];
			f_red_mean +=pun_red_buffer[k];

		}

		f_ir_mean =  f_ir_mean/n_buffer_length;
		f_red_mean =  f_red_mean/n_buffer_length;

		//Subtract  mean from signal to remove DC
		for(k = 0, ptr_x = an_x, ptr_y = an_y; k < n_buffer_length;++k,++ptr_x,++ptr_y)
		{
			*ptr_x = pun_ir_buffer[k] - f_ir_mean;
			*ptr_y = pun_red_buffer[k] - f_red_mean;

		}
		//TO DO DEBUG:  Plot signal
	    for(int i = 0; i < n_buffer_length;i++)
	    {
	    	printf("%d,",(int)an_x[i]);
	    	printf("%d\r\n",(int)an_y[i]);
	    	delay(10);

	    }

		//Remove linear trend SUM_OF_SQS

		beta_ir=calculate_linear_regression_beta(an_x,MEAN_IDX,SUM_OF_SQS);
		beta_red=calculate_linear_regression_beta(an_y,MEAN_IDX,SUM_OF_SQS);

		for(k=0,x= -MEAN_IDX,ptr_x=an_x,ptr_y=an_y;k<n_buffer_length;++k,++x,++ptr_x,++ptr_y)
		{
			*ptr_x -= beta_ir * x;
			*ptr_y -= beta_red * x;
		}

		//Calculate RMS of signals
		x_ac=get_rms(an_x,n_buffer_length,&f_ir_sumsq);
		y_ac=get_rms(an_y,n_buffer_length,&f_red_sumsq);

		//Calculate Pearson Correlation between signals (checks for good red and IR values, if its good enough it will continue SpO2 calculation)

		*correl=get_correlation_prod(an_x,an_y,n_buffer_length) /sqrt(f_ir_sumsq*f_red_sumsq);

		//Find signal periodicity (allows to detect heartbeat)

		if(*correl>=min_pearson_correlation)
		{
			if(n_last_peak_interval==LOWEST_PK_PK_INTERVAL)
			{
			   periodicity_search_init(an_x,n_buffer_length,&n_last_peak_interval,HIGHEST_PK_PK_INTERVAL, min_autocorrelation_ratio, f_ir_sumsq);

		    }
			if(n_last_peak_interval!=0)
			{
				sig_periodicity(an_x,n_buffer_length,&n_last_peak_interval,LOWEST_PK_PK_INTERVAL, HIGHEST_PK_PK_INTERVAL, min_autocorrelation_ratio, f_ir_sumsq,ratio );

		    }
			else
			{
				n_last_peak_interval=0;
			}

		}
		//Calculate the heart rate
		if(n_last_peak_interval !=0)
		{
			*pn_heart_rate = (int32_t)(FS60/n_last_peak_interval);
			*pch_hr_valid=1;
		}
		else
		{
			*pn_heart_rate=-999;
			*pch_hr_valid=0;
			*pn_spo2 = -999;
			*pch_spo2_valid=0;
			return;
		}
		//Calculate SpO2
		xy_ratio = (y_ac * f_ir_mean)/(x_ac*f_red_mean);
		if(xy_ratio > 0.02 && xy_ratio <1.84)
		{
			*pn_spo2 = (-45.06 * xy_ratio + 30.354)*xy_ratio + 94.845;
			*pch_spo2_valid=1;
		}
		else
		{
			*pn_spo2 = -999;
			*pch_spo2_valid=0;
		}

}
//Calculate lag(offset) between signals
float calculate_autocorrelation(float *data_points,int length, int lag)
{
	if(lag<0 || lag>=length)
	{
		return 0;
	}

	float sum =0.0;
	for (int i=0;i<(length-lag);i++)
	{
		sum += data_points[i] * data_points[i+lag];

	}
	return sum/(length-lag);
}


float get_correlation_prod(float*x_data,float*y_data,int length)
{
	if(length<1)
	{
		return NAN;
	}
	float dot_product=0.0f;
	for(int i=0;i<length;i++)
	{
		dot_product += x_data[i]*y_data[i];
	}
	float norm_dot_prod = dot_product /(float) length;
	return norm_dot_prod ;

}


float calculate_linear_regression_beta(float *data_points,float mean_index, float sum_of_squares)
{
	float index, beta=0.0,*data_ptr;

	for(index=-mean_index,data_ptr=data_points;index<=mean_index;++index,++data_ptr)
	{
		beta +=index *(*data_ptr); //Accumulate the weighted sum of data points

	}

	return beta/sum_of_squares;
}

float get_rms(float *data_points, int length, float *sumsq)
{
	int i;
	float *data_ptr;
	float r;
	if(length<1)
		{
			return NAN;
		}
	(*sumsq=0.0);

	for(i=0,data_ptr=data_points;i<length;++i,++data_ptr)
	{
		r=(*data_ptr);
		(*sumsq)=r*r;
	}

	(*sumsq)/=length;
	return sqrt(*sumsq);

}


void periodicity_search_init(float *data_points, int length, int32_t *last_periodicity,
		                    int max_distance,
		                    float min_auto_ratio,float auto_lag0/*baseline for comparison*/)
{
	//Validate input parameters
	if(length<=0 || max_distance>=length|| min_auto_ratio<=0 || auto_lag0 ==0)
	{
		*last_periodicity=0;
		return;
	}

	//Calculate the autocorrelation at the last known periodicity
	float current_autocorrelation = calculate_autocorrelation(data_points,length,*last_periodicity);
	float max_autocorrelation = current_autocorrelation;

	int optimal_lag= *last_periodicity;

	//Iterrate through data_points in steps of 2 from last known periodicity to max distance
	for(int lag = *last_periodicity ;lag<=max_distance ;lag+=2)
	{
		float autocorrelation = calculate_autocorrelation(data_points,length,lag);


			//Check if current lag's autocorrelation is a new maximum
			//and exceeds the min threshold
			if((autocorrelation / auto_lag0)>= min_auto_ratio && autocorrelation >max_autocorrelation)
			{
				max_autocorrelation = autocorrelation;
				optimal_lag =lag;

			}
	}

	if(max_autocorrelation/auto_lag0 >= min_auto_ratio)
	{
		*last_periodicity=optimal_lag; //Set last periodicity to optimal lag found
	}
	else
	{
		*last_periodicity=0;
	}

}


void sig_periodicity(float *data_points, int length,
		             int32_t *last_periodicity, int min_distance, int max_distance
		              ,float min_auto_ratio, float auto_lag0, float *ratio)
{
	//Validate input parameters
		if(length<=0 || max_distance>=length|| min_auto_ratio<=0 || auto_lag0 ==0)
		{
			*last_periodicity=0;
			*ratio=0.0;
			return;
		}

		//Start search from the previous known periodicity
		int current_lag= *last_periodicity;

		//Calculate initialthe autocorrelation
		float current_autocorrelation = calculate_autocorrelation(data_points,length,current_lag);
		//Store current as max
		float max_autocorrelation = current_autocorrelation;

		int optimal_lag= current_lag;


		//Search for autocorrelation to the left of lag
		while(current_lag>=min_distance)
		{
			float left_autocorrelation=calculate_autocorrelation(data_points,length,current_lag-1);

			//Check if we found a local maximum
			if(left_autocorrelation<=current_autocorrelation)
			{
				//Stop the left search because there is no improvement
				break;
			}
			//Update the current autocorrelation to the new one found
			current_autocorrelation=left_autocorrelation;

			//Update the optimal lag
			optimal_lag=current_lag-1;

			//Decrement the current lag for next iteration
			current_lag--;
		}


		//Search for autocorrelation to the right of lag
		 current_lag= *last_periodicity;

		//Calculate initialthe autocorrelation
		 current_autocorrelation = max_autocorrelation;//Rest to max autocorrelation

		//Reset variables
		while(current_lag<=max_distance)
		{
			//Calculate autocorreraltion for right lag
			float right_autocorrelation=calculate_autocorrelation(data_points,length,current_lag+1);

						//Check if we found a local maximum
						if(right_autocorrelation<=current_autocorrelation)
						{
							//Stop the right search because there is no improvement
							break;
						}
						//Update the current autocorrelation to the new one found
						current_autocorrelation=right_autocorrelation;

						//Update the optimal lag
						optimal_lag=current_lag+1;

						//Increment the current lag for next iteration
						current_lag++;

		}

		//Final validation of periodicity found
		float final_ratio =current_autocorrelation /auto_lag0;

		if(final_ratio>=min_auto_ratio)
		{
			*last_periodicity= optimal_lag;//Update last periodicity to the optimal lag found
			*ratio=final_ratio;            //Store the ratio in the output variable
		}
		else
		{
			//Set variables to 0
			*last_periodicity=0.0;
			*ratio=0.0;
		}
}
