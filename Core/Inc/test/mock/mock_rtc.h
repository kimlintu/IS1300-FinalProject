/*
 * mock_rtc.h
 *
 *  Created on: Dec 22, 2021
 *      Author: kimli
 */

#ifndef INC_TEST_MOCK_MOCK_RTC_H_
#define INC_TEST_MOCK_MOCK_RTC_H_

#include "main.h"

typedef struct ReturnValues {
	RTC_TimeTypeDef time;
} rtc_mock_retvals;

rtc_mock_retvals rtc_mock;

typedef enum {
	RTC_OK,
	RTC_INIT_FAIL,
	RTC_SETTIME_FAIL,
	RTC_GETTIME_FAIL
} RTC_STATUS;

void rtc_mock_init();
RTC_STATUS rtc_set_time(RTC_TimeTypeDef *time);
RTC_STATUS rtc_get_time(RTC_TimeTypeDef *time);

#endif /* INC_TEST_MOCK_MOCK_RTC_H_ */
