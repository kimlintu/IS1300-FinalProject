/*
 * display.h
 *
 *  Created on: 16 dec. 2021
 *      Author: kimli
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

/* Display command definitions */
#define BYTE_TO_DISPLAY_BYTE(byte) (0x0f & byte), ((0xf0 & byte) >> 4)
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
#define DISP_ENTRY_CRSR_R_BIT (0x1 << 2) // Move cursor right after write

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
#define DISP_CTRL_ON_BIT (0x1 << 2)
#define DISP_CTRL_CURSOR_BIT (0x1 << 1)
#define DISP_CTRL_CURSOR_BLINK_BIT (0x1)

/******************************/

void display_init(void);

#endif /* INC_DISPLAY_H_ */
