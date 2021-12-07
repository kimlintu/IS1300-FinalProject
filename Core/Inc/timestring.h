/*
 * timestring.h
 *
 *  Created on: 7 dec. 2021
 *      Author: kimli
 */

#ifndef INC_TIMESTRING_H_
#define INC_TIMESTRING_H_

#include "stdint.h"

typedef struct Timestring {
	uint8_t hour[2];
	uint8_t minute[2];
	uint8_t second[2];
} timestring;

void get_user_timestring(timestring *time);

#endif /* INC_TIMESTRING_H_ */
