/*
 * test_uart.h
 *
 *  Created on: Dec 6, 2021
 *      Author: kimli
 */

#ifndef INC_TEST_TEST_UART_H_
#define INC_TEST_TEST_UART_H_

#ifdef MOCK_UART
#include "test/mock/mock_uart.h"
#else
#include "uart.h"
#endif

void test_uart(void);

#endif /* INC_TEST_TEST_UART_H_ */
