/*
 * potentiometer.c
 *
 *  Created on: 22 dec. 2021
 *      Author: kimli
 */

#include "potentiometer.h"
#include "adc.h"

/**
 * @brief 	Reads the current value of the potentiometer.
 *
 * @retval	the current value of the potentiometer.
 */
uint32_t potentiometer_read() {
	adc_start();

	return adc_read();
}
