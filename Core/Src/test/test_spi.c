/*
 * test_spi.c
 *
 *  Created on: Dec 10, 2021
 *      Author: kimli
 */

#include "test/test_spi.h"
#include "stdint.h"
#include "stdio.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

void test_spi_send() {
	uint16_t data_size = 4;
	uint8_t data[data_size];
	for (int i = 0; i < data_size; i++) {
		data[i] = i;
	}

	if (spi_send(data, data_size) != SPI_OK) {
		printf("\tfail: send data via SPI failed\n");
		errors++;
	} else {
		pass++;
	}
}

void test_spi_receive() {
	uint16_t data_size = 4;
	uint8_t data[data_size];
	if (spi_receive(data, data_size) != SPI_OK) {
		printf("\tfail: recieve data via SPI failed\n");
		errors++;
	} else {
		pass++;
	}
}

void test_spi() {
	printf("\nSPI TEST START\n\n");
	test_spi_send();
	test_spi_receive();

	print_test_result(errors, pass);
	printf("\nSPI TEST END\n");
}
