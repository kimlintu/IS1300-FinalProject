/*
 * test_uart.c
 *
 *  Created on: Dec 6, 2021
 *      Author: kimli
 */

#include "test/test_uart.h"
#include "string.h"
#include "stdlib.h"

void test_uart() {
	/********* TEST SETUP *********/
	uint8_t *data_string_tx = (uint8_t *)"Hello \n";

	uint16_t data_size = (uint16_t) strlen((char *)data_string_tx);
	uint8_t fail = 0;
	/* Send our Hello World string */
	if(uart_send_data(data_string_tx, data_size + 1) != UART_OK) {
		/* Fail UART transmit test */
		fail = 1;
	}

	/* Receive same string */
	uint8_t data_string_rx[data_size + 1]; // + 1 for null character
	if(uart_receive_data_block(data_string_rx, data_size) != UART_OK) {
		/* Fail UART receive test */
		fail = 1;
	}
	data_string_rx[data_size] = '\0';

	/* Test: same data in transmitted and receive string */
	uint8_t *tx = data_string_tx;
	uint8_t *rx = data_string_rx;
	while((*tx != '\0') && (*rx != '\0')) {
		if(*tx != *rx) {
			/* Fail test : Not same character */
			fail = 1;
		}
		tx++;
		rx++;
	}
	/* Test end */

	/* Test: same length of transmitted and received string */
	if(*tx != '\0') {
		/* Fail test : data_string_tx shorter than data_string_rx */
		fail = 1;
	}

	if(*rx != '\0') {
		/* Fail test : data_string_tx shorter than data_string_rx */
		fail = 1;
	}
	/* Test end */
}
