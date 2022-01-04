/*
 * test_adc.c
 *
 *  Created on: 22 dec. 2021
 *      Author: kimli
 */

#include "test/test_adc.h"
#include "stdio.h"
#include "string.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

void test_adc_start() {
	if (adc_start() != ADC_OK) {
		printf("\tfail: Could not start ADC conversion\n");
		errors++;
	} else {
		pass++;
	}
}

void test_adc_read() {
	printf("Reading some values from adc for five seconds.\n");

	adc_start();
	for (int i = 0; i < 5; i++) {
		uint32_t adc_value = adc_read();
		printf("value[%d]: %u\n", i, adc_value);
		HAL_Delay(1000);
	}
}

void test_adc() {
	printf("\nADC TEST START\n\n");
	test_adc_start();
	test_adc_read();

	print_test_result(errors, pass);
	printf("\nADC TEST END\n\n");
}
