/*
 * test_rtc.c
 *
 *  Created on: Dec 9, 2021
 *      Author: kimli
 */

#include "test/test_rtc.h"
#include "timestring.h"
#include "stdio.h"
#include "stdbool.h"

static uint32_t errors = 0;
static uint32_t pass = 0;

static bool time_set = false;

/**
 * @brief	Tests that the initialization of the RTC module works.
 */
void test_rtc_initialization() {
	if (rtc_init() != RTC_OK) {
		printf("\tfail: rtc was not initialized correctly\n");
		errors++;
	} else {
		pass++;
	}
}

/**
 * @brief	Tries to set the time of the RTC module.
 *
 * @retval	the timestring that RTC was initialized with.
 */
timestring test_rtc_settime() {
	timestring time;
	time.hour = 1;
	time.minute = 1;
	time.second = 1;
	if (rtc_set_time(&time) != RTC_OK) {
		printf("\tfail: could not set rtc time\n");
		errors++;
	} else {
		time_set = true;
		pass++;

		return time;
	}

	timestring null_timestring = { 0, 0, 0 };
	return null_timestring;
}

/**
 * @brief	Tries to retrieve time of the RTC module.
 *
 * @retval	a timestring that contains the time that was retrieved from RTC.
 */
timestring test_rtc_gettime() {
	timestring retrieved_time = { 0, 0, 0 };
	if (rtc_get_time(&retrieved_time) != RTC_OK) {
		printf("\tfail: could not get RTC time\n");
		/* print retrieved time */
		errors++;
	} else {
		pass++;

		return retrieved_time;
	}

	timestring null_timestring = { 0, 0, 0 };
	return null_timestring;
}

/**
 * @brief	Compares timestrings retrieved from previous tests (set time, and get time).
 * 			The retrieved timestring should be retrieved immediately after the time was set.
 */
void test_correct_settime(timestring set_time, timestring retrieved_time) {
	uint8_t fail = 0;

	if (retrieved_time.hour != set_time.hour) {
		printf(
				"\tfail: retrieved time after set does not have correct 'hour'\n");
		printf("\t->expected %u but got %u\n", set_time.hour,
				retrieved_time.hour);
		errors++;
		fail = 1;
	}

	if (retrieved_time.minute != set_time.minute) {
		printf(
				"\tfail: retrieved time after set does not have correct 'minute'\n");
		printf("\t->expected %u but got %u\n", set_time.minute,
				retrieved_time.minute);
		errors++;
		fail = 1;
	}

	if (retrieved_time.second != set_time.second) {
		printf(
				"\tfail: retrieved time after set does not have correct 'second'\n");
		printf("\t->expected %u but got %u\n", set_time.second,
				retrieved_time.second);
		errors++;
		fail = 1;
	}

	if(!fail) {
		pass++;
	}
}

/**
 * @brief	Retrieves time from RTC in 1 second interval and verify that RTC counter has increased.
 */
void test_rtc_updatetime() {
	int c = 5;
	uint8_t seconds[c];

	timestring retrieved_time = { 0, 0, 0 };
	for (int i = 0; i < c; i++) {
		rtc_get_time(&retrieved_time);
		seconds[i] = retrieved_time.second;
		HAL_Delay(1000);
	}

	uint8_t fail = 0;
	for (int i = 1; i < c; i++) {
		if (seconds[i] == seconds[i - 1]) {
			if (!fail) {
				printf("\tfail: time did not update after 1s\n");
				fail = 1;
			}
			printf("\t-> seconds[%d]=%u is same as [%d]=%u\n", i, seconds[i],
					i - 1, seconds[i - 1]);
		}
	}

	if (fail) {
		errors++;
	} else {
		pass++;
	}
}

void test_rtc() {
	/* Initialization test */
	printf("\nRTC TEST START\n\n");
	test_rtc_initialization();
	timestring set_time = test_rtc_settime();
	timestring set_time_retrieve = test_rtc_gettime(); /* try retrieving time just after setting it */

	HAL_Delay(2000); // Need some delay to wait for RTC counter to start?
	if (time_set) {
		test_correct_settime(set_time, set_time_retrieve);
		test_rtc_updatetime();
	} else {
		printf("\terror: could not run remaining test since time was not set\n");
	}

	print_test_result(errors, pass);
	printf("\nRTC TEST END\n");
}
