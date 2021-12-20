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

void test_display() {
	printf("\nDISPLAY TEST START\n\n");
	display_init();
	pass++;

	uint8_t *data = (uint8_t *) "Hello World!";
	if(display_write(data, strlen((char *)data), 2, 3) != DISPLAY_OK) {
		printf("\tfail: Could not write to display\n");
		errors++;
	} else {
		pass++;
	}

	HAL_Delay(3000);

	display_clear();
	pass++;

	print_test_result(errors, pass);
	printf("\nDISPLAY TEST END\n");
}
