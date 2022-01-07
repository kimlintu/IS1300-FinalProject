/*
 * test_backlight.c
 *
 *  Created on: 22 dec. 2021
 *      Author: kimli
 */


#include "test/test_backlight.h"
#include "stdio.h"
#include "stdint.h"

static uint32_t pass = 0;

void test_backlight() {
	printf("\nBACKLIGHT TEST START\n\n");

	printf("Turning on backlight. Brightness is set to current potentiometer value at startup\n");
	backlight_on();
	pass++;

	printf("Changing brightness based on potentiometer for 15s\n");
	printf("Adjust the potentiometer and verify that the brightness changes\n");
	uint32_t start = HAL_GetTick();
	while((HAL_GetTick() - start) < 15000) {
		backlight_update_brightness();
	}
	pass++;

	printf("Turning off backlight.\n");
	backlight_off();
	pass++;

	printf("\nBACKLIGHT TEST END\n\n");
}
