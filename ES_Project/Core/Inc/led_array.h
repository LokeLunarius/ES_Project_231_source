/*
 * led_array.h
 *
 *  Created on: Jan 9, 2024
 *      Author: phatl
 */

#ifndef INC_LED_ARRAY_H_
#define INC_LED_ARRAY_H_

#include "global.h"

#define LED_NUM	12

struct Led_Flag{
	int flag;
	uint32_t color;
};

extern struct Led_Flag led_flag[12];

void sipeed_init_mic_array_led(void);
void sk9822_send_data(uint32_t data);
void sk9822_start_frame(void);
void sk9822_stop_frame(void);
void sk9822_data_one_led(uint8_t gray, uint8_t r, uint8_t g, uint8_t b);
uint32_t sk9822_gen_data_one_led(uint8_t gray, uint8_t r, uint8_t g, uint8_t b);
void sk9822_data_one_led_at_position(uint32_t color, int position);
void sk9822_data_all_led(uint32_t color);
void sk9822_flash(uint32_t color1, uint32_t color2, uint32_t interval);
void sk9822_horse_race(uint8_t r, uint8_t g, uint8_t b, uint32_t interval, uint8_t times);
void sk9822_breath(uint8_t r, uint8_t g, uint8_t b, uint32_t interval);
void sipeed_init_mic_array_led(void);

#endif /* INC_LED_ARRAY_H_ */
