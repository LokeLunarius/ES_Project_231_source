/*
 * random_value.c
 *
 *  Created on: Jan 10, 2024
 *      Author: phatl
 */


#include "global.h"

int radom_angle_generator()
{
	int angle = 0;
	srand(time(0));

	angle = rand() % 360;
	return angle;
}
