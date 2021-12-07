/*
 * timestring.c
 *
 *  Created on: 7 dec. 2021
 *      Author: kimli
 */

#include "timestring.h"
#include "uart.h"
#include "stdbool.h"
#include "stdlib.h"

void get_user_timestring(timestring *time) {
	uint16_t buffer_size = sizeof(timestring) + 3;
	uint8_t buffer[buffer_size]; // space for HH:MM:SS\n (9 bytes)

	uart_receive_data_block(buffer, buffer_size);

	/* Check correct format 'HH:MM:SS'\n */

	// Check numbers
	for(uint8_t i = 0; i < buffer_size; i += 3) {
		uint8_t c = buffer[i];
		bool is_number = ((c >= 0x30) && (c <= 0x39)) ? true : false; // between ASCII value for 0 and 9
		strtol(c, NULL, 10);
	}
}
