/*
 * test_display.c
 *
 *  Created on: 16 dec. 2021
 *      Author: kimli
 */

#include "test/test_display.h"
#include "stdio.h"
#include "string.h"

static int errors = 0;
static int pass = 0;

void test_display_init() {
	display_init();
	pass++;
}

void test_display_write() {
	printf("Verify that Hello World! Goodbye World is written on display\n");
	uint8_t *data = (uint8_t*) "Hello";
	uint8_t *data2 = (uint8_t*) "World!";
	uint8_t *data3 = (uint8_t*) "Goodbye";
	uint8_t *data4 = (uint8_t*) "World!";
	if ((display_write(data, strlen((char*) data), 1, 1) != DISPLAY_OK)) {
		printf("\tfail: Could not write to display\n");
		errors++;
	} else {
		pass++;
	}

	if ((display_write(data2, strlen((char*) data2), 2, 1) != DISPLAY_OK)) {
		printf("\tfail: Could not write to display\n");
		errors++;
	} else {
		pass++;
	}

	if ((display_write(data3, strlen((char*) data3), 3, 1) != DISPLAY_OK)) {
		printf("\tfail: Could not write to display\n");
		errors++;
	} else {
		pass++;
	}

	if ((display_write(data4, strlen((char*) data4), 4, 1) != DISPLAY_OK)) {
		printf("\tfail: Could not write to display\n");
		errors++;
	} else {
		pass++;
	}
}

void test_display() {
	printf("\nDISPLAY TEST START\n\n");
	test_display_init();
	test_display_write();
	HAL_Delay(5000);

	display_clear();
	pass++;

	print_test_result(errors, pass);
	printf("\nDISPLAY TEST END\n");
}
