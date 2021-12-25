/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "error_handler.h"
/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c3;

/* USER CODE BEGIN Private defines */
typedef enum {
	I2C_OK,
	I2C_FAIL
} I2C_STATUS;
/* USER CODE END Private defines */

void MX_I2C3_Init(void);

/* USER CODE BEGIN Prototypes */
I2C_STATUS i2c_write(uint8_t *data, uint16_t data_size, uint8_t device_address, uint8_t mem_address);
I2C_STATUS i2c_read(uint8_t *buffer, uint16_t buffer_size, uint8_t device_address, uint8_t mem_address);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
