/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "display.h"
#include "timestring.h"
#include "backlight.h"
#include "stdio.h"
#include "math.h"
#define RUN_TEST

#ifdef RUN_TEST
#include "test/test_uart.h"
#include "test/test_spi.h"
#include "test/test_rtc.h"
#include "test/test_pwm.h"
#include "test/test_display.h"
#include "test/test_timestring.h"
#include "test/test_adc.h"
#include "test/test_potentiometer.h"
#include "test/test_backlight.h"
#include "test/test_accelerometer.h"

#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}

uint32_t last_tick = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	static uint8_t x_n = 0;
	static uint8_t x_p = 0;
	static uint8_t y_n = 0;
	static uint8_t y_p = 0;

	switch (GPIO_Pin) {
	case Acc_INT2_Pin: {
		uint8_t bfr;
		while (i2c_read(&bfr, 1, 0x1e, 0x5f) != I2C_OK)
			;

		if (x_p && x_n) {
			if (bfr & 0x80) {
				printf("shake X!\n");
			}
			x_p = 0;
			x_n = 0;
		} else if (y_p && y_n) {
			if (bfr & 0x20) {
				printf("shake Y!\n");
			}
			y_p = 0;
			y_n = 0;
		} else {
			if (x_p) {
				if (bfr & 0x40) {
					x_n = 1;
				} else {
					x_p = 0;
				}
			} else if (x_n) {
				if (bfr & 0x80) {
					x_p = 1;
				} else {
					x_n = 0;
				}
			} else if (y_p) {
				if (bfr & 0x10) {
					y_n = 1;
				} else {
					y_p = 0;
				}
			} else if (y_n) {
				if (bfr & 0x20) {
					y_p = 1;
				} else {
					y_n = 0;
				}
			} else {
				if (bfr & 0x80) {
					x_p = 1;
				} else if (bfr & 0x40) {
					x_n = 1;
				} else if (bfr & 0x20) {
					y_n = 1;
				} else if (bfr & 0x10) {
					y_p = 1;
				}
			}
		}

		printf("sm 1 axis : %u\n", bfr);
	}
		break;
	}
	/* read to clear interrupt flag */

}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	printf("\n");
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_UART5_Init();
	MX_RTC_Init();
	MX_SPI2_Init();
	MX_TIM3_Init();
	MX_ADC1_Init();
	/* USER CODE BEGIN 2 */
#ifdef RUN_TEST
	//test_uart();
	test_spi();
	//test_timestring();
	test_rtc();
	//test_pwm();
	//test_display();
  	//test_adc();
  //test_potentiometer();
  test_backlight();
#endif
  backlight_on();
  display_init();
  /* Function set RE = 1 (enable extended function registers), R/W=0 RS=0*/
  uint8_t cmd1[3] = { 0x1f, 0x0A, 0x03 };

  /* ROM select */
  uint8_t cmd2[2] = { 0x02, 0x07 };

  /* Select ROM A (0x00) R/W=0 RS=1 */
  uint8_t cmd3[3] = { 0x5f, 0x0, 0x0 };

  /* Function set RE = 0*/
  uint8_t cmd4[3] = { 0x1f, 0x08, 0x03 };

  spi_send(cmd1, 3);
  spi_send(cmd2, 2);
  spi_send(cmd3, 3);
  spi_send(cmd4, 3);

  display_clear();
  uint8_t block = 0x1F;
  display_write(&block, 1, 1, 1);
  display_write(&block, 1, 3, 1);
while(1);

	/* Startup procedure */

	display_init();
	display_clear();

	backlight_on();

	uint8_t *str = "Send";
	uint8_t *str3 = "timestring";
	display_write(str, strlen(str), 1, 1);
	display_write(str3, strlen(str3), 2, 1);

	/* Get user initial timestring */
	timestring user_timestring;
	while(get_user_timestring(&user_timestring) != TIMESTRING_OK) {
		uint8_t *str2 = "TRY AGAIN";
		display_write(str2, strlen(str2), 1, 1);
	}
	display_clear();
	rtc_set_time_from_timestring(&user_timestring);
#endif


	/* USER CODE END 2 */

	/* Init scheduler */
	osKernelInitialize(); /* Call init function for freertos objects (in freertos.c) */
	MX_FREERTOS_Init();
	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	/* Start program */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM1) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
