/*
 * pwm.h
 *
 *  Created on: Dec 12, 2021
 *      Author: kimli
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "tim.h"

typedef enum {
	PWM_OK,
	PWM_START_FAIL,
	PWM_STOP_FAIL,
	PWM_DC_CHANGE_FAIL,
	PWM_DC_CHANGE_OK
} PWM_STATUS;

PWM_STATUS pwm_start();
PWM_STATUS pwm_stop();

PWM_STATUS pwm_change_duty_cycle(uint8_t p);

#endif /* INC_PWM_H_ */
