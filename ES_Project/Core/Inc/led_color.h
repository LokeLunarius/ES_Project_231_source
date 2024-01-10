/*
 * led_color.h
 *
 *  Created on: Jan 10, 2024
 *      Author: phatl
 */

#ifndef INC_LED_COLOR_H_
#define INC_LED_COLOR_H_

#include "global.h"

#define BIT_8 	256
#define BIT_5	32

extern uint32_t white;
extern uint32_t black;
extern uint32_t red[BIT_8];
extern uint32_t green[BIT_8];
extern uint32_t blue[BIT_8];
extern uint32_t gray[BIT_8];
extern uint32_t gray_5[BIT_8];

void color_init();

#endif /* INC_LED_COLOR_H_ */
