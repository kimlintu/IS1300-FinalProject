/*
 * accerelometer.c
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#include "accelerometer.h"
#include "i2c.h"
#include "stdio.h"

/**
 * @brief	Brings the accerelometer out of 'power down' mode into 'normal mode' and
 * 			enables data gathering on the specified axis.
 *
 * @param	uint8_t axis: The enabled axis. Can be either of the values:
 * 							- ACCELEROMETER_AXIS_X
 * 							- ACCELEROMETER_AXIS_Y
 * 							- ACCELEROMETER_AXIS_Z
 * 						  The values can be ORed together to enable multiple axis.
 *
 * @retval	ACCELEROMETER_STATUS
 */
ACCELEROMETER_STATUS accelerometer_start(uint8_t axis) {
	uint8_t cmd1 = 0x60 | axis;

	if (i2c_write(&cmd1, 1, ACCELEROMETER_ADDRESS, 0x20) == I2C_FAIL) {
		return ACCELEROMETER_FAIL;
	}

	return ACCELEROMETER_OK;
}
