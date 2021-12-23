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
 * @brief	Tries to set the time of the RTC module.
 *
 * @retval	the timestring that RTC was initialized with.
 */
RTC_TimeTypeDef test_rtc_settime() {
	RTC_TimeTypeDef time;
	time.Hours = 1;
	time.Minutes = 1;
	time.Seconds = 1;
	time.SubSeconds = 0;
	time.TimeFormat = RTC_HOURFORMAT_24;
	if (rtc_set_time(&time) != RTC_OK) {
		printf("\tfail: could not set rtc time\n");
		errors++;
	} else {
		time_set = true;
		pass++;

		return time;
	}

	RTC_TimeTypeDef null_timestring = { 0 };
	return null_timestring;
}

/**
 * @brief	Tries to retrieve time of the RTC module.
 *
 * @retval	a timestring that contains the time that was retrieved from RTC.
 */
RTC_TimeTypeDef test_rtc_gettime() {
	RTC_TimeTypeDef retrieved_time = { 0 };
	if (rtc_get_time(&retrieved_time) != RTC_OK) {
		printf("\tfail: could not get RTC time\n");
		/* print retrieved time */
		errors++;
	} else {
		pass++;

		return retrieved_time;
	}

	RTC_TimeTypeDef null_timestring = { 0 };
	return null_timestring;
}

/**
 * @brief	Compares timestrings retrieved from previous tests (set time, and get time).
 * 			The retrieved timestring should be retrieved immediately after the time was set.
 */
void test_correct_settime(RTC_TimeTypeDef set_time, RTC_TimeTypeDef retrieved_time) {
	uint8_t fail = 0;

	if (retrieved_time.Hours != set_time.Hours) {
		printf(
				"\tfail: retrieved time after set does not have correct 'hour'\n");
		printf("\t->expected %u but got %u\n", set_time.Hours,
				retrieved_time.Hours);
		errors++;
		fail = 1;
	}

	if (retrieved_time.Minutes != set_time.Minutes) {
		printf(
				"\tfail: retrieved time after set does not have correct 'minute'\n");
		printf("\t->expected %u but got %u\n", set_time.Minutes,
				retrieved_time.Minutes);
		errors++;
		fail = 1;
	}

	if (retrieved_time.Seconds != set_time.Seconds) {
		printf(
				"\tfail: retrieved time after set does not have correct 'second'\n");
		printf("\t->expected %u but got %u\n", set_time.Seconds,
				retrieved_time.Seconds);
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
	RTC_TimeTypeDef seconds[c];

	RTC_TimeTypeDef retrieved_time = { 0 };
	for (int i = 0; i < c; i++) {
		rtc_get_time(&retrieved_time);
		seconds[i] = retrieved_time;
		HAL_Delay(1000);
	}

	uint8_t fail = 0;
	for (int i = 1; i < c; i++) {
		if (seconds[i].Seconds == seconds[i - 1].Seconds) {
			if (!fail) {
				printf("\tfail: time did not update after 1s\n");
				fail = 1;
			}
			printf("\t-> seconds[%d]=%u is same as [%d]=%u\n", i, seconds[i].Seconds,
					i - 1, seconds[i - 1].Seconds);
		}
	}

	if (fail) {
		errors++;
	} else {
		pass++;
	}
}

void test_rtc() {
	printf("\nRTC TEST START\n\n");
	RTC_TimeTypeDef set_time = test_rtc_settime();
	RTC_TimeTypeDef set_time_retrieve = test_rtc_gettime(); /* try retrieving time just after setting it */

	if (time_set) {
		test_correct_settime(set_time, set_time_retrieve);

#ifndef MOCK_RTC
		test_rtc_updatetime();
#endif
	} else {
		printf("\terror: could not run remaining test since time was not set\n");
	}

	uint8_t str[] = "12:03:12\n";
	timestring time;
	for(int i = 0; i < sizeof(timestring); i++) {
		time[i] = str[i];
	}

	rtc_set_time_from_timestring(&time);

	print_test_result(errors, pass);
	printf("\nRTC TEST END\n");
}
