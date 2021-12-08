/*
 * uart.c
 *
 *  Created on: Dec 6, 2021
 *      Author: kimli
 */

#ifndef MOCK_UART
#include "uart.h"

uart_rx_status RX_COMPLETE = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
	RX_COMPLETE = 1;
}

/**
 * @brief 	Tries to send data out via UART
 *
 * @param 	uint8_t *data: A pointer to the data to be sent
 * @param 	uint16_t data_size: Size of data buffer in bytes
 *
 * @retval	returns UART_OK if the transmission succeeded, otherwise UART_FAIL
 */
UART_status uart_send_data(uint8_t *data, uint16_t data_size) {
	if (HAL_UART_Transmit(&huart5, data, data_size, TX_TIMEOUT) != HAL_OK) {
		return UART_FAIL;
	} else {
		return UART_OK;
	}
}

/**
 * @brief 	Tries to read buffer_size amount of bytes received via UART. This function will block until
 * 			the whole buffer has been filled with data.
 *
 * @param 	uint8_t *buffer: A pointer to the buffer that should be filled with received data
 * @param 	uint16_t buffer_size: Size of the buffer
 *
 * @retval	returns UART_OK if the buffer was filled. UART_FAIL if an error occured.
 */
UART_status uart_receive_data_block(uint8_t *buffer, uint16_t buffer_size) {
	if (HAL_UART_Receive_IT(&huart5, buffer, buffer_size) != HAL_OK) {
		return UART_FAIL;
	}

	/* Wait until buffer is filled */
	while (!RX_COMPLETE)
		;

	RX_COMPLETE = 0;

	return UART_OK;
}
#endif
