/*
 * led_array.c
 *
 *  Created on: Jan 9, 2024
 *      Author: phatl
 */

#include "global.h"

struct Led_Flag led_flag[12] = {0};

void sk9822_send_data(uint32_t data)
{
	for(uint32_t mask = 0x80000000; mask > 0; mask >>= 1)
	{
	    HAL_GPIO_WritePin(LED_CK_GPIO_Port, LED_CK_Pin, GPIO_PIN_RESET);
	    asm("nop");
	    asm("nop");
	    if (data & mask) {
	      HAL_GPIO_WritePin(LED_DA_GPIO_Port, LED_DA_Pin, GPIO_PIN_SET);
	    } else {
	      HAL_GPIO_WritePin(LED_DA_GPIO_Port, LED_DA_Pin, GPIO_PIN_RESET);
	    }
	    HAL_GPIO_WritePin(LED_CK_GPIO_Port, LED_CK_Pin, GPIO_PIN_SET);
	    asm("nop");
	    asm("nop");
	}
}

void sk9822_start_frame(void) {
  sk9822_send_data(0);
}

void sk9822_stop_frame(void) {
  sk9822_send_data(0xffffffff);
}

void sk9822_data_one_led(uint8_t gray, uint8_t r, uint8_t g, uint8_t b) {
  uint32_t tosend;
  gray &= 0x1f;
  tosend = ((0xe0 | gray) << 24) | (b << 16) | (g << 8) | r;
  sk9822_send_data(tosend);
}

uint32_t sk9822_gen_data_one_led(uint8_t gray, uint8_t r, uint8_t g, uint8_t b) {
  uint32_t tosend;
  gray &= 0x1f;
  tosend = ((0xe0 | gray) << 24) | (b << 16) | (g << 8) | r;
  return tosend;
}

void sk9822_data_one_led_at_position(uint32_t color, int position)
{
	led_flag[position].flag = 1;
	led_flag[position].color = color;
	sk9822_start_frame();
	for(int i = 0; i < position;i++)
	{
		if(led_flag[i].flag == 1)
		{
			sk9822_send_data(led_flag[i].color);
		}
		else
		{
			sk9822_send_data(gray[0]);
		}
	}
	sk9822_send_data(color);
	for(int i = position + 1; i < LED_NUM;i++)
	{
		if(led_flag[i].flag == 1)
		{
			sk9822_send_data(led_flag[i].color);
		}
		else
		{
			sk9822_send_data(gray[0]);
		}
	}
	sk9822_stop_frame();

}

void sk9822_data_all_led(uint32_t color)
{
	sk9822_start_frame();
	for(int i = 0; i < LED_NUM; i++)
	{
		sk9822_send_data(color);
	}
	sk9822_stop_frame();
}

void sk9822_flash(uint32_t color1, uint32_t color2, uint32_t interval) {
  uint8_t index;
  color1 |= 0xe0000000;
  color2 |= 0xe0000000;
  sk9822_start_frame();
  for (index = 0; index < LED_NUM; index++) {
    sk9822_send_data(color1);
  }
  sk9822_stop_frame();
  HAL_Delay(interval);
  sk9822_start_frame();
  for (index = 0; index < LED_NUM; index++) {
    sk9822_send_data(color2);
  }
  sk9822_stop_frame();
  HAL_Delay(interval);
}
