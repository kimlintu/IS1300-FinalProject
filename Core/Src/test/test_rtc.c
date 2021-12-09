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

void test_rtc_initialization() {
	if (rtc_init() != RTC_OK) {
		printf("\tfail: rtc was not initialized correctly\n");
		errors++;
	} else {
		pass++;
	}
}

void test_rtc_settime() {
	timestring time;
	time.hour = 12;
	time.minute = 3;
	time.second = 40;
	if (rtc_set_time(&time) != RTC_OK) {
		printf("\tfail: could not set rtc time\n");
		errors++;
	} else {
		time_set = true;
		pass++;
	}
}

void test_rtc_gettime() {
	timestring retrieved_time = { 0, 0, 0 };
	if (rtc_get_time(&retrieved_time) != RTC_OK) {
		printf("\tfail: could not get RTC time\n");
		/* print retrieved time */
		errors++;
	} else {
		pass++;
	}
}

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
	test_rtc_settime();
	HAL_Delay(2000);

	if (!time_set) {
		printf("\tfail: did not run tests since time was not set\n");
	} else {
		test_rtc_gettime();
		test_rtc_updatetime();
	}

	print_test_result(errors, pass);
	printf("\nRTC TEST END\n");
}
