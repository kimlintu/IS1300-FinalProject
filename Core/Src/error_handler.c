/*
 * error_handler.h
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#include "error_handler.h"

#include "stdio.h"

void HAL_error_handler(char *source, HAL_StatusTypeDef status) {

	printf("HAL error:\n");
	if (status == HAL_ERROR) {
		printf("%s, HAL status: HAL_ERROR", source);
	} else if (status == HAL_BUSY) {
		printf("%s, HAL status: HAL_BUSY", source);
	} else if (status == HAL_TIMEOUT) {
		printf("%s, HAL status: HAL_TIMEOUT", source);
	}
	printf("\n");
}

