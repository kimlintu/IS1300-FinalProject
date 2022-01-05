/*
 * mock_uart.c
 *
 *  Created on: 8 dec. 2021
 *      Author: kimli
 */

#ifdef MOCK_UART
#include "test/mock/mock_uart.h"
#include "stdio.h"

#define RECEIVE_BUFFER_SIZE 128

typedef struct ReturnValues {
	uint8_t uart_receive_retval[RECEIVE_BUFFER_SIZE];
} uart_mock_retvals;

uart_mock_retvals uart_mock;

void mock_uart_set_receive_retval(uint8_t *retval, uint16_t size) {
	if(size > RECEIVE_BUFFER_SIZE) {
		printf("Max buffer size is %d\n", RECEIVE_BUFFER_SIZE);
	}

	for(int i = 0; i < size; i++) {
		uart_mock.uart_receive_retval[i] = retval[i];
	}
}

UART_status uart_send_data(uint8_t *data, uint16_t data_size) {
	return UART_OK;
}

UART_status uart_receive_data_block(uint8_t *buffer, uint16_t buffer_size, bool echo) {
	for(int i = 0; i < buffer_size; i++) {
		buffer[i] = uart_mock.uart_receive_retval[i];
	}

	return UART_OK;
}
#endif
