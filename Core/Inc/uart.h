/*
 * uart.h
 *
 *  Created on: Dec 6, 2021
 *      Author: kimli
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "usart.h"
#include "stdbool.h"

#define TX_TIMEOUT 5000 // How long to wait for a successful transmission

typedef uint8_t uart_rx_status;

typedef enum {
	UART_OK,
	UART_FAIL
} UART_status;

UART_status uart_send_data(uint8_t *data, uint16_t data_size);

UART_status uart_receive_data_block(uint8_t *buffer, uint16_t buffer_size, bool echo);

#endif /* INC_UART_H_ */
