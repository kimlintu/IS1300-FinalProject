/**
 ******************************************************************************
 @brief 	Driver for the external backlight.
 @file 		backlight.c
 @author	Kim Lintu
 ******************************************************************************
 */

#include "backlight.h"
#include "pwm.h"
#include "potentiometer.h"

/**
 * @brief	Turns on the backlight. The brightness of the backlight
 * 			will be set to the current potentiometer value.
 *
 * @retval	None.
 */
void backlight_on() {
	backlight_update_brightness();
	pwm_start();
}

/**
 * @brief	Turns off the backlight.
 *
 * @retval	None.
 */
void backlight_off() {
	pwm_stop();
}

/**
 * @brief	Updates the brightness of the backlight to a value proportional to the
 * 			current value of the potentiometer.
 *
 * @retval	None.
 */
void backlight_update_brightness() {
	uint32_t p_value = potentiometer_read();

	/* ADC resolution is 12 bit so max value should be 2^12 -1. */
	uint32_t duty_cycle = ((float) p_value / 4095) * 100;

	pwm_set_duty_cycle(duty_cycle);
}
