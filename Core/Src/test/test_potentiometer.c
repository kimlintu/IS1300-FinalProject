/*
 * test_potentiometer.c
 *
 *  Created on: 22 dec. 2021
 *      Author: kimli
 */

#include "test/test_potentiometer.h"
#include "stdio.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

void test_potentiometer() {
	printf("\nPOTENTIOMETER TEST START\n\n");

	printf("Reading values from potentiometer every 0.5s for 10 seconds\n");
	printf("Adjust potentiometer and verify that the value changes\n");
	int c = 20;
	while(c > 0) {
		uint32_t p_value = potentiometer_read();
		printf("value: %lu\n", p_value);
		HAL_Delay(500);
		c--;
	}
	pass++;

	print_test_result(errors, pass);
	printf("\nPOTENTIOMETER TEST END\n\n");
}
