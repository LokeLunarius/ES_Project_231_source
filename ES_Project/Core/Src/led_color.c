/*
 * led_color.c
 *
 *  Created on: Jan 10, 2024
 *      Author: phatl
 */


#include "global.h"

uint32_t red[BIT_8] = {0};
uint32_t green[BIT_8] = {0};
uint32_t blue[BIT_8] = {0};
uint32_t gray[BIT_8] = {0};
uint32_t gray_5[BIT_8] = {0};

void color_init()
{
	for(int i = 0; i < BIT_8; i++)
	{
		gray_5[i] = i;
	}
	for(int i = 0;i < BIT_8; i++)
	{
		red[i] = sk9822_gen_data_one_led(gray_5[18], i, 0, 0);
		green[i] = sk9822_gen_data_one_led(gray_5[18], 0, i, 0);
		blue[i] = sk9822_gen_data_one_led(gray_5[18], 0, 0, i);
		gray[i] = sk9822_gen_data_one_led(i, i, i, i);
	}
}
