/*
 * test.c
 *
 *  Created on: Jan 9, 2024
 *      Author: phatl
 */

#include "global.h"

int index_0 = 0;
int index_1 = 0;
int first_time = 1;
int second = 15;
int minute = 15;
int hour = 0;

void test_init()
{
	Set_timer(1000, 0);
	Set_timer(1000, 1);
	Set_timer(1000, 2);
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, 0);
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, 0);
	HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, 0);
	sk9822_data_all_led(gray[0]);
}

void test_i2s()
{

}
void led_clock_display()
{
	int h = hour/12;
	int m = minute/5;
	int s = second/5;
	led_flag[hour/12].flag = 1;
	led_flag[minute/5].flag = 1;
	led_flag[second/5].flag = 1;

	uint32_t mix_color_hm = sk9822_gen_data_one_led(gray_5[18], 30, 30, 0);
	uint32_t mix_color_hs = sk9822_gen_data_one_led(gray_5[18], 30, 0, 30);
	uint32_t mix_color_ms = sk9822_gen_data_one_led(gray_5[18], 0, 30, 30);
	uint32_t mix_color_hms = sk9822_gen_data_one_led(gray_5[18], 30, 30, 30);

	if(hour/12 == minute/5 && hour/12 == second/5)
	{
		sk9822_data_one_led_at_position(mix_color_hms, hour/12);
	}
	else if(hour/12 == minute/5)
	{
		sk9822_data_one_led_at_position(mix_color_hm, hour/12);
		sk9822_data_one_led_at_position(blue[30], second/5);
	}
	else if(hour/12 == second/5)
	{
		sk9822_data_one_led_at_position(mix_color_hs, hour/12);
		sk9822_data_one_led_at_position(green[30], minute/5);
	}
	else if(minute/5 == second/5)
	{
		sk9822_data_one_led_at_position(red[30], hour/12);
		sk9822_data_one_led_at_position(mix_color_ms, minute/5);
	}
	else
	{
		sk9822_data_one_led_at_position(red[30], hour/12);
		sk9822_data_one_led_at_position(green[30], minute/5);
		sk9822_data_one_led_at_position(blue[30], second/5);
	}
	led_flag[hour/12].flag = 0;
	led_flag[minute/5].flag = 0;
	led_flag[second/5].flag = 0;
}

void clock_led()
{
	if(timer_flag[2] == 1)
	{
		if(second >= 60)
		{
			second = 0;
			minute++;
		}
		if(minute >= 60)
		{
			minute = 0;
			hour++;
		}
		if(hour >= 24)
		{
			hour = 0;
		}
		led_clock_display();
		second++;
		Set_timer(1000, 2);
	}
}

void test_led_array()
{
	if(index_1 >= 4)
	{
		index_1 = 1;
	}
	if(timer_flag[1] == 1)
	{
		switch (index_1) {
			case 1:
//				sk9822_start_frame();
//				for(int i = 0; i < LED_NUM; i++)
//				{
//					sk9822_send_data(gray[0]);
//				}
//				sk9822_stop_frame();
				//sk9822_data_all_led(red[30]);
				sk9822_data_one_led_at_position(red[30], 3);
				break;
			case 2:
//				sk9822_start_frame();
//				for(int i = 0; i < LED_NUM; i++)
//				{
//					sk9822_send_data(gray[30]);
//				}
//				sk9822_stop_frame();
				//sk9822_data_all_led(green[30]);
				sk9822_data_one_led_at_position(blue[30], 6);
				break;
			case 3:
//				sk9822_start_frame();
//				for(int i = 0; i < LED_NUM; i++)
//				{
//					sk9822_send_data(gray[60]);
//				}
//				sk9822_stop_frame();
				//sk9822_data_all_led(blue[30]);
				sk9822_data_one_led_at_position(green[30], 9);
				break;
			default:
				break;
		}
		index_1++;
		Set_timer(1000, 1);
	}
}

void test_RGB()
{
	if(index_0 >= 4)
	{
		index_0 = 1;
	}
	if(timer_flag[0] == 1)
	{
		switch (index_0) {
			case 1:
				HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, 1);
				HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, 0);
				HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, 0);
				break;
			case 2:
				HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, 0);
				HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, 1);
				HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, 0);
				break;
			case 3:
				HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, 0);
				HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, 0);
				HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, 1);
				break;
			default:
				break;
		}
		index_0++;
		Set_timer(1000, 0);
	}
}
