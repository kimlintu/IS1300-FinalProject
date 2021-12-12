/*
 * pwm.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kimli
 */

#include "pwm.h"

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
