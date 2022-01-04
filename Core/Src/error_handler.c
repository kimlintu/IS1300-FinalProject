/**
 ******************************************************************************
 @brief 	Error logging.
 @file 		error_handler.c
 @author	Kim Lintu
 ******************************************************************************
 */

#include "error_handler.h"

#include "stdio.h"

/**
 * @brief	Handles HAL errors. Currently just prints out the source of the
 * 			error (e.g. which peripheral that caused it) and the HAL status
 *
 * @retval 	None.
 */
void HAL_error_handler(char *source, HAL_StatusTypeDef status) {

	printf("HAL error:\n");
	if (status == HAL_ERROR) {
		printf("%s, HAL status: HAL_ERROR", source);
	} else if (status == HAL_BUSY) {
		printf("%s, HAL status: HAL_BUSY", source);
	} else if (status == HAL_TIMEOUT) {
		printf("%s, HAL status: HAL_TIMEOUT", source);
	} else {
		printf("%s, HAL status: UNKNOWN", source);
	}
	printf("\n");
}

