/*
 * test_pwm.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kimli
 */

#include "test/test_pwm.h"
#include "stdint.h"
#include "stdio.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

void test_pwm_start() {
	if (pwm_start() != PWM_OK) {
		printf("\tfail: PWM did not start\n");
		errors++;
	} else {
		pass++;
	}
}

void test_pwm_stop() {
	if (pwm_stop() != PWM_OK) {
		printf("\tfail: PWM did not stop\n");
		errors++;
	} else {
		pass++;
	}
}

void test_pwm_change_dc() {
	int c = 10;
	printf("Changing duty cycle of PWM to values 100, 90, 80, .., 0\n");

	int8_t dc = 100;
	while (dc >= 0) {
		printf("Setting duty cycle to %u\n", dc);
		if (pwm_change_duty_cycle((uint8_t)dc) != PWM_DC_CHANGE_OK) {
			printf(
					"\tfail: Could not set PWM duty cycle to valid value of %u\n",
					dc);
			errors++;
			continue;
		}
		dc -= 10;
		c--;
		pass++;
		HAL_Delay(1000);
	}

	/* Test some invalid duty cycle values */
	uint8_t invalid_dc = 123;
	if (pwm_change_duty_cycle(invalid_dc) == PWM_DC_CHANGE_OK) {
		printf("\tfail: Could set PWM duty cycle to invalid value of %u\n",
				invalid_dc);
		errors++;
	} else {
		pass++;
	}
}

void test_pwm() {
	printf("\nPWM TEST START\n\n");
	test_pwm_start();
	HAL_Delay(2000);
	test_pwm_change_dc();

	HAL_Delay(2000);
	test_pwm_stop();

	print_test_result(errors, pass);
	printf("\nPWM TEST END\n\n");
}
