/*
 * mock_uart.h
 *
 *  Created on: 8 dec. 2021
 *      Author: kimli
 */

#ifndef INC_TEST_MOCK_MOCK_UART_H_
#define INC_TEST_MOCK_MOCK_UART_H_

#include "stdint.h"

typedef enum {
	UART_OK,
	UART_FAIL
} UART_status;

void mock_uart_set_receive_retval(uint8_t *retval, uint16_t size);

UART_status uart_send_data(uint8_t *data, uint16_t data_size);

UART_status uart_receive_data_block(uint8_t *buffer, uint16_t buffer_size);

#endif /* INC_TEST_MOCK_MOCK_UART_H_ */
