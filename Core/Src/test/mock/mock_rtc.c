/*
 * mock_rtc.c
 *
 *  Created on: Dec 22, 2021
 *      Author: kimli
 */

#ifdef MOCK_RTC
#include "test/mock/mock_rtc.h"

void rtc_mock_init() {
	RTC_TimeTypeDef rtc_time;
	rtc_time.Hours = 4;
	rtc_time.Minutes = 4;
	rtc_time.Seconds = 4;
	rtc_time.SubSeconds = 4;
	rtc_time.TimeFormat = RTC_HOURFORMAT_24;
	rtc_set_time(&rtc_time);
}

RTC_STATUS rtc_set_time(RTC_TimeTypeDef *time) {
	rtc_mock.time = *time;

	return RTC_OK;
}

RTC_STATUS rtc_get_time(RTC_TimeTypeDef *time) {
	*time = rtc_mock.time;

	return RTC_OK;
}
#endif
