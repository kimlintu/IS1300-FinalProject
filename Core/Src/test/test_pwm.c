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

void test_pwm() {
	printf("\nPWM TEST START\n\n");
	test_pwm_start();
	HAL_Delay(2000);
	test_pwm_stop();

	print_test_result(errors, pass);
	printf("\nPWM TEST END\n\n");
}
