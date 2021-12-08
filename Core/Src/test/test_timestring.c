/*
 * test_timestring.h
 *
 *  Created on: Dec 7, 2021
 *      Author: kimli
 */

#include "test/test_timestring.h"
#include "test/test_utils.h"
#include "stdio.h"
#include "string.h"

static uint32_t errors;
static uint32_t pass;

void test_timestring_validation() {
	uint8_t *valid_timestring = (uint8_t*) "02:31:40\n";
	if (!valid_timestring_format(valid_timestring)) {
		printf("\tfail: valid timestring %s is not deemed valid\n",
				valid_timestring);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring1 = (uint8_t*) "02:AB:40\n";
	if (valid_timestring_format(invalid_timestring1)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring1);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring2 = (uint8_t*) "02332:40\n";
	if (valid_timestring_format(invalid_timestring2)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring2);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring3 = (uint8_t*) "02:AB:403";
	if (valid_timestring_format(invalid_timestring3)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring3);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring4 = (uint8_t*) "AB:CD:EF\n";
	if (valid_timestring_format(invalid_timestring4)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring4);
		errors++;
	} else {
		pass++;
	}
}

void test_timestring_extraction() {
	uint8_t *valid_timestring = (uint8_t*) "02:32:43\n";
	uint8_t numbers[3];
	extract_timestring_numbers(valid_timestring, numbers);
	if ((numbers[0] == 2) && (numbers[1] == 32) && (numbers[2] == 43)) {
		pass++;
	} else {
		printf("\tfail: incorrect timestring extraction\n");
		printf("\t-> expected 2, 32, 43 from %s but got %u, %u, %u\n",
				valid_timestring, numbers[0], numbers[1], numbers[2]);
		errors++;
	}
}

void test_timestring() {

	printf("\nTIMESTRING TEST START\n\n");
	test_timestring_validation();
	test_timestring_extraction();

	print_test_result(errors, pass);
	printf("\nTIMESTRING TEST END\n");
}
