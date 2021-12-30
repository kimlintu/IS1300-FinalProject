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

void test_accelerometer_start() {
	if (accelerometer_start(ACCELEROMETER_AXIS_X | ACCELEROMETER_AXIS_Y)
			!= ACCELEROMETER_OK) {
		printf("\tfail: Could not start accelerometer\n");
		errors++;
	} else {
		pass++;
	}
}

void test_accelerometer() {
	printf("\nACCERELOMETER TEST START\n\n");

	test_accelerometer_start();

	accelerometer_init_sm();
	accelerometer_setup_sm1(0x04, 0x00);
	//accelerometer_setup_sm2(0xFF, 0x32);

	print_test_result(errors, pass);
	printf("\nACCERELOMETER TEST END\n\n");
}
