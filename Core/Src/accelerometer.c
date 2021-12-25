/*
 * accerelometer.c
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#include "accelerometer.h"
#include "i2c.h"
#include "stdio.h"

ACCELEROMETER_STATUS accelerometer_start(uint8_t axis) {
	uint8_t cmd1 = 0x60 | axis;

	if (i2c_write(&cmd1, 1, ACCELEROMETER_ADDRESS, 0x20) == I2C_FAIL) {
		return ACCELEROMETER_FAIL;
	}

	uint8_t status_buffer;

	int c = 1000;
	while (1) {
		i2c_read(&status_buffer, 1, ACCELEROMETER_ADDRESS, 0x27);
		while (!(status_buffer & 0x8)) {
			i2c_read(&status_buffer, 1, ACCELEROMETER_ADDRESS, 0x27);
		}

		int8_t x_data_buffer_l;
		int8_t x_data_buffer_h;
		i2c_read(&x_data_buffer_l, 1, ACCELEROMETER_ADDRESS, 0x28);
		i2c_read(&x_data_buffer_h, 1, ACCELEROMETER_ADDRESS, 0x29);
		int16_t x_data = ((x_data_buffer_h << 4) | x_data_buffer_l);

		int8_t y_data_buffer_l;
		int8_t y_data_buffer_h;
		i2c_read(&y_data_buffer_l, 1, ACCELEROMETER_ADDRESS, 0x2A);
		i2c_read(&y_data_buffer_h, 1, ACCELEROMETER_ADDRESS, 0x2B);
		int16_t y_data = ((y_data_buffer_h << 4) | y_data_buffer_l);

		int8_t z_data_buffer_l;
		int8_t z_data_buffer_h;
		i2c_read(&z_data_buffer_l, 1, ACCELEROMETER_ADDRESS, 0x2C);
		i2c_read(&z_data_buffer_h, 1, ACCELEROMETER_ADDRESS, 0x2D);
		int16_t z_data = ((z_data_buffer_h << 4) | z_data_buffer_l);

		printf("\nx: %d\ny: %d\nz: %d\n", x_data, y_data, z_data);

		c--;
		HAL_Delay(1);
	}

	return ACCELEROMETER_OK;
}
