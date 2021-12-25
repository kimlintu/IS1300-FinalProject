/*
 * test_timestring.h
 *
 *  Created on: Dec 7, 2021
 *      Author: kimli
 */

#include "test/test_timestring.h"
#include "test/test_utils.h"
#include "stdio.h"
#include "string.h"

static uint32_t errors;
static uint32_t pass;

void test_timestring_validation() {
	uint8_t *valid_timestring = (uint8_t*) "02:31:40\n";
	if (!valid_timestring_format(valid_timestring)) {
		printf("\tfail: valid timestring %s is not deemed valid\n",
				valid_timestring);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring1 = (uint8_t*) "02:AB:40\n";
	if (valid_timestring_format(invalid_timestring1)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring1);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring2 = (uint8_t*) "02332:40\n";
	if (valid_timestring_format(invalid_timestring2)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring2);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring3 = (uint8_t*) "02:AB:403";
	if (valid_timestring_format(invalid_timestring3)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring3);
		errors++;
	} else {
		pass++;
	}

	uint8_t *invalid_timestring4 = (uint8_t*) "AB:CD:EF\n";
	if (valid_timestring_format(invalid_timestring4)) {
		printf("\tfail: invalid timestring %s is deemed valid\n",
				invalid_timestring4);
		errors++;
	} else {
		pass++;
	}
}

void test_timestring_extraction() {
	uint8_t *valid_timestring = (uint8_t*) "02:32:43\n";
	uint8_t numbers[3];
	extract_timestring_numbers(valid_timestring, numbers);
	if ((numbers[0] == 2) && (numbers[1] == 32) && (numbers[2] == 43)) {
		pass++;
	} else {
		printf("\tfail: incorrect timestring extraction\n");
		printf("\t-> expected 2, 32, 43 from %s but got %u, %u, %u\n",
				valid_timestring, numbers[0], numbers[1], numbers[2]);
		errors++;
	}
}

void test_get_user_timestring(bool fail_invalid_format,
bool fail_invalid_range, timestring *time) {
	TIMESTRING_STATUS result;
	result = get_user_timestring(time);

	if ((result == TIMESTRING_OK)) {
		if (!fail_invalid_format && !fail_invalid_range) {
			pass++;
		} else if (fail_invalid_format) {
			printf("\tfail: badly formatted timestring was accepted\n");
		} else {
			printf("\tfail: timestring with invalid time units was accepted\n");
			errors++;
		}
	}

	if (result == TIMESTRING_INVALID_FORMAT) {
		if (fail_invalid_format) {
			pass++;
		} else {
			printf("\tfail: correctly formatted string was NOT accepted\n");
			errors++;
		}
	}

	if (result == TIMESTRING_INVALID_TIME_RANGE) {
		if (fail_invalid_range) {
			pass++;
		} else {
			printf(
					"\tfail: timestring with valid time units was NOT accepted\n");
			errors++;
		}
	}
}

void test_get_clock_timestring() {
	timestring retrieved_time;
	timestring_get_clock_time(&retrieved_time);

	RTC_TimeTypeDef clock;
	rtc_get_time(&clock);

	uint8_t numbers[3];
	extract_timestring_numbers(retrieved_time, numbers);
	if (numbers[0] != clock.Hours) {
		printf("\tfail: Timestring does not contain same hour as clock\n");
		errors++;
	} else {
		pass++;
	}

	if (numbers[1] != clock.Minutes) {
		printf("\tfail: Timestring does not contain same minutes as clock\n");
		errors++;
	} else {
		pass++;
	}

	if (numbers[2] != clock.Seconds) {
		printf("\tfail: Timestring does not contain same seconds as clock\n");
		errors++;
	} else {
		pass++;
	}
}

void test_correct_user_timestring() {
#ifdef MOCK_UART
	uint8_t *correct_timestring = (uint8_t*) "12:03:43\n";
	uint16_t c_data_size = strlen(correct_timestring);
	mock_uart_set_receive_retval(correct_timestring, c_data_size);
#else
	uint8_t *prompt1 = (uint8_t*) "Type: \"12:03:43\\n\"\r\n";
	uint16_t data_size = (uint16_t) strlen((char*) prompt1);
	uart_send_data(prompt1, data_size + 1);
#endif
	timestring user_timestring;
	test_get_user_timestring(false, false, &user_timestring);
	uint8_t numbers[3];
	extract_timestring_numbers(user_timestring, numbers);
	if (numbers[0] != 12) {
		printf("\tfail: invalid value for 'hour' in timestring struct\n");
		printf("\t->expected %d but got %d\n", 12, numbers[0]);
		errors++;
	} else {
		pass++;
	}

	if (numbers[1] != 3) {
		printf("\tfail: invalid value for 'minute' in timestring struct\n");
		printf("\t->expected %d but got %d\n", 3, numbers[1]);
		errors++;
	} else {
		pass++;
	}

	if (numbers[2] != 43) {
		printf("\tfail: invalid value for 'second' in timestring struct\n");
		printf("\t->expected %d but got %d\n", 43, numbers[2]);
		errors++;
	} else {
		pass++;
	}
}

void test_badly_format_user_timestring() {
#ifdef MOCK_UART
	uint8_t *bad_format_timestring = (uint8_t*) "12:AB.43\t";
	uint16_t b_data_size = strlen(bad_format_timestring);
	mock_uart_set_receive_retval(bad_format_timestring, b_data_size);
#else
	uint8_t *prompt2 = (uint8_t*) "Type: \"12:AB.43\\t\"\r\n";
	uint16_t data_size = (uint16_t) strlen((char*) prompt2);
	uart_send_data(prompt2, data_size + 1);
#endif
	timestring user_timestring;
	test_get_user_timestring(true, false, &user_timestring);
}

void test_invalid_range_timestring() {
#ifdef MOCK_UART
	uint8_t *invalid_range_timestring = (uint8_t*) "12:99:43\n";
	uint16_t i_data_size = strlen(invalid_range_timestring);
	mock_uart_set_receive_retval(invalid_range_timestring, i_data_size);
#else
	uint8_t *prompt3 = (uint8_t*) "Type: \"12:99:43\\n\"\r\n";
	uint16_t data_size = (uint16_t) strlen((char*) prompt3);
	uart_send_data(prompt3, data_size + 1);
#endif
	timestring user_timestring;
	test_get_user_timestring(false, true, &user_timestring);
}
void test_timestring() {

	printf("\nTIMESTRING TEST START\n\n");
	test_timestring_validation();
	test_timestring_extraction();
	test_correct_user_timestring();
	test_badly_format_user_timestring();
	test_invalid_range_timestring();

#ifdef MOCK_RTC
	rtc_mock_init();
	test_get_clock_timestring();
#else
#endif

	print_test_result(errors, pass);
	printf("\nTIMESTRING TEST END\n");
}
