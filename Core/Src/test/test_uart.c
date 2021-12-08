/*
 * test_uart.c
 *
 *  Created on: Dec 6, 2021
 *      Author: kimli
 */

#include "test/test_uart.h"
#include "test/test_utils.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

void test_received_correct_data(uint8_t *expected_data, bool should_fail) {
	uint16_t data_size = strlen(expected_data);

	uint8_t data_rx[data_size + 1]; // + 1 for null character
	if (uart_receive_data_block(data_rx, data_size) != UART_OK) {
		/* Fail UART receive test */
		printf("\tfail: Failed UART receive\n");
	}
	data_rx[data_size] = '\0';

	/* Test: same data in transmitted and receive string */
	uint8_t *expect = expected_data;
	uint8_t *rx = data_rx;
	bool same_string = true;
	while ((*expect != '\0') && (*rx != '\0')) {
		if (*expect != *rx) {
			/* Fail test : Not same character */
			same_string = false;
		}
		expect++;
		rx++;
	}

	if (!same_string && !should_fail) {
		printf("\tfail: Received string was not as expected.");
		printf("\t->expected %s but got %s\n", expected_data, data_rx);
		errors++;
	} else {
		pass++;
	}
}

void test_uart_send() {
	uint8_t *data_string_tx = (uint8_t*) "Hello \n";
	uint16_t data_size = (uint16_t) strlen((char*) data_string_tx);
	/* Send our Hello string */
	if (uart_send_data(data_string_tx, data_size + 1) != UART_OK) {
		/* Fail UART transmit test */
		printf("\tfail: Failed UART transmit");
		errors++;
	}
}

void test_uart() {
	printf("\nUART TEST START\n\n");

	/* Receive same string */
	uint8_t *expected_data = (uint8_t*) "Hello World\n";

#ifdef MOCK_UART
	uint8_t *correct_data = expected_data;
	uint16_t c_data_size = strlen(correct_data);
	mock_uart_set_receive_retval(expected_data, c_data_size);
#else
	uint8_t *prompt1 = (uint8_t *) "Type: \"Hello World\\n\"";
	uint16_t data_size = (uint16_t) strlen((char*) prompt1);
	uart_send_data(prompt1, data_size + 1);
#endif
	test_received_correct_data(expected_data, false);

#ifdef MOCK_UART
	uint8_t *wrong_data = (uint8_t *)"Not the same\t";
	uint16_t w_data_size = strlen(wrong_data);
	mock_uart_set_receive_retval(wrong_data, w_data_size);
#else
	uint8_t *prompt2 = (uint8_t *) "Type something EXCEPT: \"Hello World\\n\"";
	data_size = (uint16_t) strlen((char*) prompt2);
	uart_send_data(prompt2, data_size + 1);
#endif
	test_received_correct_data(expected_data, true);
	/* Test end */

	print_test_result(errors, pass);
	printf("\nUART TEST END\n");
}
