/*
 * test_rtc.h
 *
 *  Created on: Dec 9, 2021
 *      Author: kimli
 */

#ifndef INC_TEST_TEST_RTC_H_
#define INC_TEST_TEST_RTC_H_

#include "test/test_utils.h"

#ifdef MOCK_RTC
#include "test/mock/mock_rtc.h"
#else
#include "rtc.h"
#endif

void test_rtc(void);

#endif /* INC_TEST_TEST_RTC_H_ */
