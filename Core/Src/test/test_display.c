/*
 * test_display.c
 *
 *  Created on: 16 dec. 2021
 *      Author: kimli
 */

#include "test/test_display.h"
#include "stdio.h"

static int errors = 0;
static int pass = 0;

void test_display() {
	printf("\nDISPLAY TEST START\n\n");
	display_init();

	print_test_result(errors, pass);
	printf("\nDISPLAY TEST END\n");
}
