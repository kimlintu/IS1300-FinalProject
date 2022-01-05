/**
 ******************************************************************************
 @brief 	Driver for the UART interface.
 @file 		uart.c
 @author	Kim Lintu
 ******************************************************************************
 */

#ifndef MOCK_UART // Remove this symbol under Project->Properties->C/C++ Build->Settings->MCU GCC Compiler->Preprocessor to disable this mock
#include "uart.h"
#include "error_handler.h"

/**
 * @brief 	Tries to send data out via UART
 *
 * @param 	uint8_t *data: A pointer to the data to be sent
 * @param 	uint16_t data_size: Size of data buffer in bytes
 *
 * @retval	returns UART_OK if the transmission succeeded, otherwise UART_FAIL
 */
UART_status uart_send_data(uint8_t *data, uint16_t data_size) {
	HAL_StatusTypeDef status;
	if ((status = HAL_UART_Transmit(&huart5, data, data_size, TX_TIMEOUT)) != HAL_OK) {
#ifdef LOG_ERRORS
		HAL_error_handler("UART", status);
#endif
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
 * @param	bool echo: If true, echoes the received character to the transmitter.
 *
 * @retval	returns UART_OK if the buffer was filled. UART_FAIL if an error occured.
 */
UART_status uart_receive_data_block(uint8_t *buffer, uint16_t buffer_size, bool echo) {
	uint16_t received = 0;
	uint8_t data;

	HAL_StatusTypeDef status;
	while(received < buffer_size) {
		if((status = HAL_UART_Receive(&huart5, &data, 1, 5000)) == HAL_OK) {
			*(buffer + received) = data;
			received++;

			if(echo) {
				uart_send_data(&data, 1);
			}
		} else {
#ifdef LOG_ERRORS
		HAL_error_handler("UART", status);
#endif
		}
	}

	return UART_OK;
}
#endif
