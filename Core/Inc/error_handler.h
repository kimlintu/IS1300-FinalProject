/*
 * error_handler.h
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#ifndef INC_ERROR_HANDLER_H_
#define INC_ERROR_HANDLER_H_

#include "stdint.h"
#include "main.h"

void HAL_error_handler(char *source, HAL_StatusTypeDef status);

#endif /* INC_ERROR_HANDLER_H_ */
