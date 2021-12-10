/**
 ******************************************************************************
 * @file    rtc.c
 * @brief   This file provides code for the configuration
 *          of the RTC instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
RTC_HandleTypeDef hrtc;

/* RTC init function */

/**
 * @brief 	Initializes the RTC module
 *
 * @retval 	RTC_OK if initalization succeeded, otherwise RTC_INIT_FAIL
 */
RTC_STATUS rtc_init() {
	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127; // 32k / 128
	hrtc.Init.SynchPrediv = 255;  // 32k / (128 * 256) = 1Hz
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		return RTC_INIT_FAIL;
	}

	return RTC_OK;
}

/**
 * @brief	Sets the time of the RTC module.
 *
 * @param 	timestring *time: A timestring struct containing the time that should be set.
 *
 * @retval	RTC_OK if initalization succeeded, otherwise RTC_SETTIME_FAIL if time could not be set.
 *
 * @note	It's a good idea to put a delay after calling this function so that subsequent calls to
 * 			rtc_get_time() updates accordingly.
 */
RTC_STATUS rtc_set_time(timestring *time) {
	RTC_TimeTypeDef hal_time;
	hal_time.Hours = time->hour;
	hal_time.Minutes = time->minute;
	hal_time.Seconds = time->second;
	hal_time.SubSeconds = 0;
	hal_time.SecondFraction = 0;
	hal_time.TimeFormat = RTC_HOURFORMAT_24;

	if (HAL_RTC_SetTime(&hrtc, &hal_time, RTC_FORMAT_BIN) != HAL_OK) {
		return RTC_SETTIME_FAIL;
	} else {

			return RTC_OK;

	}

}

/**
 * @brief	Retrieves the current time of the RTC module.
 *
 * @param	timestring *time: A pointer to a timestring that should initialized with the retrieved time.
 *
 * @retval	RTC_OK if initalization succeeded, otherwise RTC_GETTIME_FAIL if time could not be retrieved.
 */
RTC_STATUS rtc_get_time(timestring *time) {
	RTC_TimeTypeDef hal_time;
	RTC_DateTypeDef hal_date;
	if (HAL_RTC_GetTime(&hrtc, &hal_time, RTC_FORMAT_BIN) != HAL_OK) {
		return RTC_GETTIME_FAIL;
	} else {
		/* Read date to unlock values in shadow registers */
		HAL_RTC_GetDate(&hrtc, &hal_date, RTC_FORMAT_BIN);

		time->hour = hal_time.Hours;
		time->minute = hal_time.Minutes;
		time->second = hal_time.Seconds;
		time->subsecond = hal_time.SubSeconds;

		return RTC_OK;
	}
}
/* USER CODE END 0 */

void HAL_RTC_MspInit(RTC_HandleTypeDef *rtcHandle) {

	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };
	if (rtcHandle->Instance == RTC) {
		/* USER CODE BEGIN RTC_MspInit 0 */

		/* USER CODE END RTC_MspInit 0 */
		/** Initializes the peripherals clock
		 */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
		PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
			Error_Handler();
		}

		/* RTC clock enable */
		__HAL_RCC_RTC_ENABLE();
		/* USER CODE BEGIN RTC_MspInit 1 */

		/* USER CODE END RTC_MspInit 1 */
	}
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle) {

	if (rtcHandle->Instance == RTC) {
		/* USER CODE BEGIN RTC_MspDeInit 0 */

		/* USER CODE END RTC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();
		/* USER CODE BEGIN RTC_MspDeInit 1 */

		/* USER CODE END RTC_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
