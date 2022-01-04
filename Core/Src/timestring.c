/**
 ******************************************************************************
 @brief 	The timestring module. Allows for retreiving a timestring from the
 	 	 	RTC clock or UART.
 @file 		timestring.c
 @author	Kim Lintu
 ******************************************************************************
 */

#include "timestring.h"
#include "ctype.h"
#include "string.h"

#define VALID_TIME_RANGE(time, min, max) ((time < min) || (time > max)) ? false : true

/**
 * @brief	Verify timestring format.
 *
 * @param	timestring buffer: The timestring that should be verified
 *
 * @retval	true if buffer is a valid timestring, otherwise false.
 */
bool valid_timestring_format(timestring buffer) {
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

/**
 * @brief	Extracts the ascii number values in the timestring and puts in into
 * 			the numbers buffer.
 *
 * @param	timestring buffer: The timestring
 * @param	uint8_t *numbers: The buffer that should be filled with the numbers.
 *
 * @retval	None.
 */
void extract_timestring_numbers(timestring buffer, uint8_t *numbers) {
	uint16_t len = strlen((char*) buffer);
	for (int i = 0; i < len; i += 3) {
		uint8_t ten_digit = buffer[i] - 0x30;
		uint8_t digit = buffer[i + 1] - 0x30;
		numbers[i / 3] = ten_digit * 10 + digit;
	}
}

/**
 * @brief	Waits for the user to enter send a timestring via the serial interface.
 *
 * @param 	timestring *time: A pointer to a timestring that should be set to the
 * 							  received user timestring.
 *
 * @retval	TIMESTRING_OK if the user sent a correctly formatted timestring. Otherwise
 * 			an error is returned. If an error is returned then timestring will not contain
 * 			a valid timestring.
 */
TIMESTRING_STATUS get_user_timestring(timestring *time) {
	/* Get the timestring from user : format HH:MM:SS */
	uart_receive_data_block(*time, sizeof(timestring), true);

	uint8_t numbers[3];
	if (valid_timestring_format(*time)) {
		extract_timestring_numbers(*time, numbers);
	} else {
		return TIMESTRING_INVALID_FORMAT;
	}

	/* Check that all time units are in a valid range */
	if (!VALID_TIME_RANGE(numbers[0], 0, 23)
			|| !VALID_TIME_RANGE(numbers[1], 0, 59)
			|| !VALID_TIME_RANGE(numbers[2], 0, 59)) {
		return TIMESTRING_INVALID_TIME_RANGE;
	}

	return TIMESTRING_OK;
}

/**
 * @brief	Formats a RTC timestamp into a timestring
 *
 * @param	timestring *time: A pointer to the resulting timestring
 * @param	RTC_TimeTypeDef *rtc_time: A pointer to the RTC timestamp
 *
 * @retval	None.
 */
void timestring_rtc_to_timestring(timestring *time, RTC_TimeTypeDef *rtc_time) {
	(*time)[0] = '0' + (rtc_time->Hours / 10);
	(*time)[1] = '0' + (rtc_time->Hours % 10);

	(*time)[2] = ':';

	(*time)[3] = '0' + (rtc_time->Minutes / 10);
	(*time)[4] = '0' + (rtc_time->Minutes % 10);

	(*time)[5] = ':';

	(*time)[6] = '0' + (rtc_time->Seconds / 10);
	(*time)[7] = '0' + (rtc_time->Seconds % 10);

	(*time)[8] = '\n';
}

/**
 * @brief	Sets the provided timestring to the current RTC clock value
 *
 * @param	timestring *time: A pointer to a timestring that should be set
 * 							  to the current clock time.
 * @retval  None.
 */
void timestring_get_clock_time(timestring *time) {
	RTC_TimeTypeDef rtc_time;
	rtc_get_time(&rtc_time);

	/* Convert RTC time to a string */
	timestring_rtc_to_timestring(time, &rtc_time);
}
