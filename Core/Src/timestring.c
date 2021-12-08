/*
 * timestring.c
 *
 *  Created on: 7 dec. 2021
 *      Author: kimli
 */

#include "timestring.h"
#include "ctype.h"
#include "string.h"

bool valid_time_range(uint8_t time, uint8_t min, uint8_t max) {
	if ((time < min) || (time > max)) {
		return false;
	} else {
		return true;
	}
}

bool valid_timestring_format(uint8_t *buffer) {
	/* Check valid format */
	if ((buffer[2] != ':') || (buffer[5]) != ':') {
		return false;
	}

	if (buffer[8] != '\n') {
		return false;
	}

	/* Get time unit numbers */
	for (int i = 0; i < 9; i += 3) {
		uint8_t ten_digit = buffer[i];
		uint8_t digit = buffer[i + 1];
		if (!isdigit(ten_digit) && !isdigit(digit)) {
			return false;
		}
	}

	return true;
}

void extract_timestring_numbers(uint8_t *buffer, uint8_t *numbers) {
	uint16_t len = strlen((char*) buffer);
	for (int i = 0; i < len; i += 3) {
		uint8_t ten_digit = buffer[i] - 0x30;
		uint8_t digit = buffer[i + 1] - 0x30;
		numbers[i / 3] = ten_digit * 10 + digit;
	}
}

TIMESTRING_STATUS get_user_timestring(timestring *time) {
	uint16_t buffer_size = sizeof(timestring) + 3; // space for HH:MM:SS\n (9 bytes)
	uint8_t buffer[buffer_size];

	/* Get the timestring from user : format HH:MM:SS */
	uart_receive_data_block(buffer, buffer_size);

	uint8_t numbers[3];
	if (valid_timestring_format(buffer)) {
		extract_timestring_numbers(buffer, numbers);
	} else {
		return TIMESTRING_INVALID_FORMAT;
	}

	/* Check that all time units are in a valid range */
	if (!valid_time_range(numbers[0], 0, 23)
			|| !valid_time_range(numbers[1], 0, 59)
			|| !valid_time_range(numbers[2], 0, 59)) {
		return TIMESTRING_INVALID_TIME_RANGE;
	}

	time->hour = numbers[0];
	time->minute = numbers[1];
	time->second = numbers[2];

	return TIMESTRING_OK;
}
