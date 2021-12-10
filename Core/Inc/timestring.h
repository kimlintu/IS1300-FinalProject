/*
 * timestring.h
 *
 *  Created on: 7 dec. 2021
 *      Author: kimli
 */

#ifndef INC_TIMESTRING_H_
#define INC_TIMESTRING_H_

#include "stdint.h"
#include "stdbool.h"

#ifdef MOCK_UART
#include "test/mock/mock_uart.h"
#else
#include "uart.h"
#endif

typedef enum {
	TIMESTRING_OK,
	TIMESTRING_INVALID_FORMAT,
	TIMESTRING_INVALID_TIME_RANGE
} TIMESTRING_STATUS;

typedef struct Timestring {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint32_t subsecond;
} timestring;

bool valid_time_range(uint8_t time, uint8_t min, uint8_t max);
bool valid_timestring_format(uint8_t *buffer);
void extract_timestring_numbers(uint8_t *buffer, uint8_t *numbers);
TIMESTRING_STATUS get_user_timestring(timestring *time);

#endif /* INC_TIMESTRING_H_ */
