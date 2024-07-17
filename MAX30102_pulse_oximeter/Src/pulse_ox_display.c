#include <pulse_ox_display.h>
#include "image.h"
#include "LCD_1in28.h"
#include "DEV_Config.h"


#define BUFF_LEN 	20


uint8_t time_buff[BUFF_LEN] = {0};


void gc9a01_start(void)
{
	DEV_Module_Init();
  
	LCD_1IN28_SetBackLight(1000);
	LCD_1IN28_Init(VERTICAL);
 	LCD_1IN28_Clear(BLACK);
	
	Paint_NewImage(LCD_1IN28_WIDTH,LCD_1IN28_HEIGHT, 0, BLACK);
	
	Paint_SetClearFuntion(LCD_1IN28_Clear);
	Paint_SetDisplayFuntion(LCD_1IN28_DrawPaint);

	
  Paint_DrawCircle(120,120, 120, BLUE ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawLine  (120, 0, 120, 12,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);
  Paint_DrawLine  (120, 228, 120, 240,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);
  Paint_DrawLine  (0, 120, 12, 120,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);
  Paint_DrawLine  (228, 120, 240, 120,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);

  Paint_DrawString_EN(65, 40, "Heart Rate ",&Font16,  BLACK, GREEN);
  Paint_DrawString_EN(100, 70, "-- ",&Font24,  BLACK, RED);
  Paint_DrawString_EN(130, 70, "BPM ",&Font16,  BLACK, BLUE);

  Paint_DrawString_EN(65, 110, "Blood Oxygen",&Font16,  BLACK, GREEN);
  Paint_DrawString_EN(100, 140, "-- ",&Font24,  BLACK, RED);
  Paint_DrawString_EN(130, 140, "% ",&Font16,  BLACK, BLUE);


  
}

void update_pulse_ox_heart_rate(int32_t hr_val)
{
	char screen_buff[3];

	snprintf(screen_buff,sizeof(screen_buff),"%d ",(int)hr_val);
	Paint_DrawString_EN(100, 70, screen_buff,&Font24,  BLACK, RED);
}

void update_pulse_ox_spo2(int32_t spo2)
{
	char screen_buff[3];

	snprintf(screen_buff,sizeof(screen_buff),"%d ",(int)spo2);
	Paint_DrawString_EN(100, 140, screen_buff,&Font24,  BLACK, RED);

}

void show_time(void)
{
	/*Display format :  hh : mm : ss*/
	sprintf((char *)time_buff,"%.2d :%.2d :%.2d",rtc_convert_bcd2bin(rtc_time_get_hour()),
			rtc_convert_bcd2bin(rtc_time_get_minute()),
			rtc_convert_bcd2bin(rtc_time_get_second()));

	Paint_DrawString_EN(70, 180, time_buff,&Font16,  BLACK, GBLUE);

}
