/*
 * pwm.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kimli
 */

#include "pwm.h"

#define TIM3_PERIOD 1041

PWM_STATUS pwm_start() {
	if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2) != HAL_OK) {
		return PWM_START_FAIL;
	} else {
		return PWM_OK;
	}
}

PWM_STATUS pwm_stop() {
	if (HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2) != HAL_OK) {
		return PWM_STOP_FAIL;
	} else {
		return PWM_OK;
	}
}

/**
 * @brief	Sets the duty cycle of PWM to 'p'.
 *
 * @param	uint8_t p: The desired duty cycle. Should be between 0 and 100.
 *
 * @retval 	PWM_DC_CHANGE_FAIL if the p value was out of bounds. Otherwise
 * 			PWM_DC_CHANGE_OK is returned.
 */
PWM_STATUS pwm_set_duty_cycle(uint8_t p) {
	if((p < 0) || (p > 100)) {
		return PWM_DC_CHANGE_FAIL;
	}
	uint32_t dc = (uint32_t)(((float)p / 100) * TIM3_PERIOD);

	TIM3->CCR2 = dc;

	return PWM_DC_CHANGE_OK;
}
