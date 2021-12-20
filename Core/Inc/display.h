/*
 * display.h
 *
 *  Created on: 16 dec. 2021
 *      Author: kimli
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "spi.h"

/* Display command definitions */
#define BYTE_TO_DISPLAY_BYTE(byte) (0x0f & byte), ((0xf0 & byte) >> 4)
#define COORD_TO_DISPLAY_ADDR(x, y) (((y) * 0x20) + (x))

/* Start byte */
#define DISP_START_INSTR_W 0x1f

/* Command */
/* Function set */
#define DISP_FS 0x30 // 8-bit data selected
#define DISP_FS_RE_BIT (0x1 << 1)
#define DISP_FS_IS_BIT (0x1)

/* Extended function set */
#define DISP_EXT_FS_4LINE 0x09

/* Entry mode */
#define DISP_ENTRY 0x4
#define DISP_ENTRY_CURSOR_R_BIT (0x1 << 1) // Move cursor right after write

/* Bias */
#define DISP_BIAS 0x1E

/* Oscillator */
#define DISP_OSC 0x1B

/* Follower */
#define DISP_FOLLOWER_CTRL 0x6E

/* Power control */
#define DISP_POWER_CTRL 0x56

/* Contrast set */
#define DISP_CONTRAST_SET 0x7A

/* Display */
#define DISP_CTRL 0x08
#define DISP_CTRL_ON_BIT (0x1 << 2)			// Turn on display
#define DISP_CTRL_CURSOR_BIT (0x1 << 1)		// Enable cursor
#define DISP_CTRL_CURSOR_BLINK_BIT (0x1)	// Enable cursor blink
#define DISP_CLEAR 0x01

/* Display address counter */
#define DISP_DDRAM_SET_ADDR 0x80

/******************************/

typedef enum {
	DISPLAY_OK,
	DISPLAY_WRITE_ERROR
} DISPLAY_STATUS;

void display_init(void);

DISPLAY_STATUS display_write(uint8_t *data, uint16_t data_size, uint8_t row, uint8_t col);

void display_clear(void);

#endif /* INC_DISPLAY_H_ */
