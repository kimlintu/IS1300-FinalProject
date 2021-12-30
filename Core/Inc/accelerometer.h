/*
 * accerelometer.h
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_

#include "stdint.h"

typedef enum {
	ACCELEROMETER_OK,
	ACCELEROMETER_FAIL
} ACCELEROMETER_STATUS;

#define ACCELEROMETER_AXIS_X 0x1
#define ACCELEROMETER_AXIS_Y 0x2
#define ACCELEROMETER_AXIS_Z 0x4

#define ACCELEROMETER_ADDRESS 0x1E // 001 1110 if SEL is LOW

ACCELEROMETER_STATUS accelerometer_start(uint8_t axis);

void accelerometer_init_sm();
ACCELEROMETER_STATUS accelerometer_setup_sm1(int8_t threshold, uint16_t time_between_shake);
ACCELEROMETER_STATUS accelerometer_setup_sm2(int8_t threshold, uint16_t time_between_shake);

#endif /* INC_ACCELEROMETER_H_ */
