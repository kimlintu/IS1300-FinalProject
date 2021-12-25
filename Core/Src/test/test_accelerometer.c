/*
 * test_accerelometer.c
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#include <test/test_accelerometer.h>
#include "stdio.h"
#include "stdint.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

void test_accelerometer() {
	printf("\nACCERELOMETER TEST START\n\n");

	if(accelerometer_start(ACCELEROMETER_AXIS_X | ACCELEROMETER_AXIS_Y) != ACCELEROMETER_OK) {
		printf("\tfail: Could not start accelerometer\n");
		errors++;
	} else {
		pass++;
	}

	print_test_result(errors, pass);
	printf("\nACCERELOMETER TEST END\n\n");
}
