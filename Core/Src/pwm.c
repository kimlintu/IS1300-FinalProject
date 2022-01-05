/**
 ******************************************************************************
 @brief 	Driver for the PWM module.
 @file 		pwm.c
 @author	Kim Lintu
 ******************************************************************************
 */

#include "pwm.h"
#include "error_handler.h"

#define TIM3_PERIOD 1041

/**
 * @brief	Starts the PWM output on Timer 3.
 *
 * @retval	PWM_OK if started successfully, otherwise PWM_FAIL
 */
PWM_STATUS pwm_start() {
	HAL_StatusTypeDef status;
	if ((status = HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)) != HAL_OK) {
#ifdef LOG_ERRORS
		HAL_error_handler("PWM", status);
#endif
		return PWM_FAIL;
	} else {
		return PWM_OK;
	}
}

/**
 * @brief	Stops the PWM output on Timer 3.
 *
 * @retval	PWM_OK if stopped successfully, otherwise PWM_FAIL
 */
PWM_STATUS pwm_stop() {
	HAL_StatusTypeDef status;
	if ((status = HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2)) != HAL_OK) {
#ifdef LOG_ERRORS
		HAL_error_handler("PWM", status);
#endif
		return PWM_FAIL;
	} else {
		return PWM_OK;
	}
}

/**
 * @brief	Sets the duty cycle of PWM to 'p' percent.
 *
 * @param	uint8_t p: The desired duty cycle. Should be a value between 0 and 100 percent.
 *
 * @retval 	PWM_DC_CHANGE_FAIL if the p value was out of bounds. Otherwise
 * 			PWM_DC_CHANGE_OK is returned.
 */
PWM_STATUS pwm_set_duty_cycle(uint8_t p) {
	if((p < 0) || (p > 100)) {
		return PWM_FAIL;
	}
	uint32_t dc = (uint32_t)(((float)p / 100) * TIM3_PERIOD);

	TIM3->CCR2 = dc;

	return PWM_OK;
}
