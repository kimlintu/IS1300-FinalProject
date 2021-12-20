/*
 * display.c
 *
 *  Created on: 16 dec. 2021
 *      Author: kimli
 */

#include "display.h"

/**
 * @brief	Initializes the display.
 */
void display_init() {
	uint8_t start_command[3] = { DISP_START_INSTR_W, BYTE_TO_DISPLAY_BYTE(
			(DISP_FS | DISP_FS_RE_BIT)) };
	uint8_t commands[10][2] =
			{ { BYTE_TO_DISPLAY_BYTE(DISP_EXT_FS_4LINE) },
					{ BYTE_TO_DISPLAY_BYTE(
							(DISP_ENTRY | DISP_ENTRY_CURSOR_R_BIT)) }, {
							BYTE_TO_DISPLAY_BYTE(DISP_BIAS) }, {
							BYTE_TO_DISPLAY_BYTE((DISP_FS | DISP_FS_IS_BIT)) },
					{ BYTE_TO_DISPLAY_BYTE(DISP_OSC) }, { BYTE_TO_DISPLAY_BYTE(
							DISP_FOLLOWER_CTRL) }, { BYTE_TO_DISPLAY_BYTE(
							DISP_POWER_CTRL) }, { BYTE_TO_DISPLAY_BYTE(
							DISP_CONTRAST_SET) }, { BYTE_TO_DISPLAY_BYTE(
							DISP_FS) },
					{
							BYTE_TO_DISPLAY_BYTE(
									(DISP_CTRL | DISP_CTRL_ON_BIT | DISP_CTRL_CURSOR_BIT | DISP_CTRL_CURSOR_BLINK_BIT)) } };

	spi_send(start_command, 3);
	for (int i = 0; i < 10; i++) {
		spi_send(commands[i], 2);
	}
}

/**
 * @brief	Writes 'data_size' amount of characters from the 'data' buffer
 * 			to the screen.
 *
 * @param	uint8_t *data: A buffer containing characters that should be written to
 * 						   the display. Each character is specified by a code that can
 * 						   be seen in the display datasheet p.6.
 *
 * @param 	uint16_t data_size: The amount of characters that should be written.
 *
 * @param 	uint8_t  row: The row that the data should be written on. Must be between 1 and 4.
 *
 * @param 	uint8_t  col: The column that the data should be written on. Must be between 1 and 20.
 *
 * @retval	DISPLAY_OK if the write was successful. DISPLAY_WRITE_ERROR if an invalid row or column
 * 			value was specified.
 */
DISPLAY_STATUS display_write(uint8_t *data, uint16_t data_size, uint8_t row,
		uint8_t col) {
	/* Check valid values for row and column */
	if ((row < 1) || (row > 20)) {
		return DISPLAY_WRITE_ERROR;
	}

	if ((col < 1) || (col > 4)) {
		return DISPLAY_WRITE_ERROR;
	}

	/* Calculate DDRAM address to match row and column */
	uint8_t display_addr = COORD_TO_DISPLAY_ADDR(col - 1, row - 1);

	/* Set display address counter to correct address */
	uint8_t f_set[3] = { DISP_START_INSTR_W, BYTE_TO_DISPLAY_BYTE((DISP_FS)) }; // RE = 0
	spi_send(f_set, 3);

	uint8_t set_addr_cmd[2] = { BYTE_TO_DISPLAY_BYTE((DISP_DDRAM_SET_ADDR | display_addr)) };
	spi_send(set_addr_cmd, 2);

	/* Write data */
	for(int i = 0; i < data_size; i++) {
		uint8_t cmd[3] = {0x5f, BYTE_TO_DISPLAY_BYTE(*(data + i))};
		spi_send(cmd, 3);
	}

	return DISPLAY_OK;
}

/**
 * @brief	Clears the display and resets the display's address counter to the
 * 			first row and first column.
 *
 * @retval	None
 */
void display_clear() {
	uint8_t clear_cmd[3] = { DISP_START_INSTR_W, BYTE_TO_DISPLAY_BYTE(DISP_CLEAR) };
	spi_send(clear_cmd, 3);
}
