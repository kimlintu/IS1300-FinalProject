/*
 * test_utils.c
 *
 *  Created on: 8 dec. 2021
 *      Author: kimli
 */

#include "test/test_utils.h"

void print_test_result(uint32_t errors, uint32_t pass) {
	printf("%d tests, %d passed, %d failed\n", (errors + pass), pass, errors);
}
