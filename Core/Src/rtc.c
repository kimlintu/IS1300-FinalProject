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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#ifndef MOCK_RTC

RTC_HandleTypeDef hrtc;

/**
 * @brief	Sets the time of the RTC module.
 *
 * @param 	RTC_TimeTypeDef *time: A struct containing the time values that should be set.
 *
 * @retval	RTC_OK if initalization succeeded, otherwise RTC_SETTIME_FAIL if time could not be set.
 */
RTC_STATUS rtc_set_time(RTC_TimeTypeDef *time) {
	time->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	time->StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN) != HAL_OK) {
		return RTC_SETTIME_FAIL;
	} else {
		return RTC_OK;
	}

}

/**
 * @brief 	Sets the time of the RTC clock based on the given timestring.
 *
 * @param	timestring *time: A pointer to a valid 'timestring'. A timestring
 * 							  is a string on the format HH:MM:SS\n
 *
 * @retval	RTC_STATUS
 */
RTC_STATUS rtc_set_time_from_timestring(timestring *time) {
	uint8_t numbers[3];
	extract_timestring_numbers(*time, numbers);

	RTC_TimeTypeDef rtc_time;
	rtc_time.Hours = numbers[0];
	rtc_time.Minutes = numbers[1];
	rtc_time.Seconds = numbers[2];
	rtc_time.SubSeconds = 0;
	rtc_time.TimeFormat = RTC_HOURFORMAT_24;

	return rtc_set_time(&rtc_time);
}

/**
 * @brief	Retrieves the current time of the RTC module.
 *
 * @param	RTC_TimeTypeDef *time: A pointer to a struct that should be filled with the current time values.
 *
 * @retval	RTC_OK if initalization succeeded, otherwise RTC_GETTIME_FAIL if time could not be retrieved.
 */
RTC_STATUS rtc_get_time(RTC_TimeTypeDef *time) {
	RTC_DateTypeDef hal_date;

	if (HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BIN) != HAL_OK) {
		return RTC_GETTIME_FAIL;
	} else {
		/* Read date to unlock values in shadow registers */
		HAL_RTC_GetDate(&hrtc, &hal_date, RTC_FORMAT_BIN);

		return RTC_OK;
	}
}
#endif
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
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
