/*
 * display.c
 *
 *  Created on: 16 dec. 2021
 *      Author: kimli
 */

#include "display.h"

void display_init() {
	uint8_t start_command = { DISP_START_INSTR_W, BYTE_TO_DISPLAY_BYTE((DISP_FS | DISP_FS_RE_BIT)) };
	uint8_t commands[10][2] = {
			{ BYTE_TO_DISPLAY_BYTE(DISP_EXT_FS_4LINE) },
			{ BYTE_TO_DISPLAY_BYTE((DISP_ENTRY | DISP_ENTRY_CRSR_R_BIT)) },
			{ BYTE_TO_DISPLAY_BYTE(DISP_BIAS) },
			{ BYTE_TO_DISPLAY_BYTE((DISP_FS | DISP_FS_IS_BIT)) },
			{ BYTE_TO_DISPLAY_BYTE(DISP_OSC) },
			{ BYTE_TO_DISPLAY_BYTE(DISP_FOLLOWER_CTRL) },
			{ BYTE_TO_DISPLAY_BYTE(DISP_POWER_CTRL) },
			{ BYTE_TO_DISPLAY_BYTE(DISP_CONTRAST_SET) },
			{ BYTE_TO_DISPLAY_BYTE(DISP_FS) },
			{ BYTE_TO_DISPLAY_BYTE((DISP_CTRL | DISP_CTRL_ON_BIT | DISP_CTRL_CURSOR_BIT | DISP_CTRL_CURSOR_BLINK_BIT)) }
	};

	spi_send(&start_command, 3);
	for(int i = 0; i < 10; i++) {
		spi_send(commands[i], 2);
	}
}
