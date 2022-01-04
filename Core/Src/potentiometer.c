/**
 ******************************************************************************
 @brief 	Driver for the external potentiometer.
 @file 		potentiometer.c
 @author	Kim Lintu
 ******************************************************************************
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
