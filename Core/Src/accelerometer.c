/*
 * accerelometer.c
 *
 *  Created on: Dec 25, 2021
 *      Author: kimli
 */

#include "accelerometer.h"
#include "i2c.h"
#include "stdio.h"

/**
 * @brief	Brings the accerelometer out of 'power down' mode into 'normal mode' and
 * 			enables data gathering on the specified axis.
 *
 * @param	uint8_t axis: The enabled axis. Can be either of the values:
 * 							- ACCELEROMETER_AXIS_X
 * 							- ACCELEROMETER_AXIS_Y
 * 							- ACCELEROMETER_AXIS_Z
 * 						  The values can be ORed together to enable multiple axis.
 *
 * @retval	ACCELEROMETER_STATUS
 */
ACCELEROMETER_STATUS accelerometer_start(uint8_t axis) {
	uint8_t cmd1 = 0x20 | axis;

	if (i2c_write(&cmd1, 1, ACCELEROMETER_ADDRESS, 0x20) == I2C_FAIL) {
		return ACCELEROMETER_FAIL;
	}

	return ACCELEROMETER_OK;
}

#define ACCLR_INT_ACTIVE_HIGH (0x1 << 6)
#define ACCLR_INT2_ENABLE (0x1 << 4)

#define ACCLR_SM1_THRS2 0xFE
#define ACCLR_SM1_MASK 0xA0
#define ACCLR_SM1_ABS (0x1 << 5)
#define ACCLR_SM1_SITR 0x1
#define ACCLR_SM1_ROUTE_INT2 (0x1 << 3)
#define ACCLR_SM1_ENABLE (0x1)

#define ACCLR_SM2_THRS2 0x02
#define ACCLR_SM2_MASK 0xA0
#define ACCLR_SM2_ABS (0x1 << 5)
#define ACCLR_SM2_SITR 0x1
#define ACCLR_SM2_ROUTE_INT2 (0x1 << 3)
#define ACCLR_SM2_ENABLE (0x1)

#define ACCLR_REG_CTRL3 0x23
#define ACCLR_REG_CTRL5 0x24

#define ACCLR_REG_SM1_CTRL 0x21
#define ACCLR_REG_SM1_TIM1L 0x54
#define ACCLR_REG_SM1_TIM1H 0x55
#define ACCLR_REG_SM1_THRS2 0x56
#define ACCLR_REG_SM1_THRS1 0x57
#define ACCLR_REG_SM1_MASK_A 0x5A
#define ACCLR_REG_SM1_MASK_B 0x59
#define ACCLR_REG_SM1_SETT1 0x5B
#define ACCLR_REG_SM1_INSTR0 0x40 // First instruction register for SM1

#define ACCLR_REG_SM2_CTRL 0x22
#define ACCLR_REG_SM2_TIM1L 0x74
#define ACCLR_REG_SM2_TIM1H 0x75
#define ACCLR_REG_SM2_THRS2 0x76
#define ACCLR_REG_SM2_THRS1 0x77
#define ACCLR_REG_SM2_MASK_A 0x7A
#define ACCLR_REG_SM2_MASK_B 0x79
#define ACCLR_REG_SM2_SETT1 0x7B
#define ACCLR_REG_SM2_INSTR0 0x60 // First instruction register for SM1

#define ACCLR_SM_SHIFT_RESET 0x4
#define ACCLR_SM_GREATER_THRS1 0x05
#define ACCLR_SM_GREATER_THRS2 0x06
#define ACCLR_SM_LESS_THRS1 0x07
#define ACCLR_SM_LESS_THRS2 0x08
#define ACCLR_SM_GREATER_RTHRSH1 0x0B
#define ACCLR_SM_GREATER_RTHRSH2 0x0D
#define ACCLR_SM_LESS_RTHRSH1 0x0C
#define ACCLR_SM_LESS_RTHRSH2 0x0E
#define ACCLR_SM_TIM1 0x01
#define ACCLR_SM_TIM2 0x02
#define ACCLR_SM_CMD_CONT 0x11

void accelerometer_init_sm() {
	// Set interrupt to active high and enable interrupts on INT2 pin
	uint8_t data = ACCLR_INT_ACTIVE_HIGH | ACCLR_INT2_ENABLE;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_CTRL3) != I2C_OK)
		;

	// Full scale selection, we go with 16g
	data = 0x20; // 16g
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_CTRL5) != I2C_OK)
		;
}

ACCELEROMETER_STATUS accelerometer_setup_sm1(int8_t threshold,
		uint16_t time_between_shake) {
	// Main threshold, decides how hard you have to shake in one direction
	if (threshold == 0x00) {
		threshold = 0x08;
	}
	uint8_t data = threshold;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_THRS1)
			!= I2C_OK)
		;

	// State machine mask, decides which axis to include in conditions
	// For state machine 1, we check +x and +y, meaning the x and y axis with their
	// current signs.
	data = 0xA0;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_MASK_A)
			!= I2C_OK)
		;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_MASK_B)
			!= I2C_OK)
		;

	data = ACCLR_SM1_SITR;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_SETT1)
			!= I2C_OK)
		;

	/* State machine 1 logic */

	// Check if we went in positive x/y direction
	data = ACCLR_SM_GREATER_THRS1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_INSTR0)
			!= I2C_OK)
		;

	data = ACCLR_SM_LESS_RTHRSH1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_INSTR0 + 1)
			!= I2C_OK)
		;

	// CONT instruction, generate interrupt and goto start
	data = ACCLR_SM_CMD_CONT;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_INSTR0 + 2)
			!= I2C_OK)
		;

	// Enable state machine 1, route sm interrupt to INT2
	data = ACCLR_SM1_ROUTE_INT2 | ACCLR_SM1_ENABLE;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM1_CTRL)
			!= I2C_OK)
		;

	return ACCELEROMETER_OK;
}

ACCELEROMETER_STATUS accelerometer_setup_sm2(int8_t threshold,
		uint16_t time_between_shake) {

	// Setup timer 1 (time to wait for a movement in one direction)
	if (time_between_shake == 0x00) {
		time_between_shake = 0x19;
	}
	uint8_t data = time_between_shake & 0xff;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_TIM1L)
			!= I2C_OK)
		;
	data = (time_between_shake & 0xff00) >> 8;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_TIM1H)
			!= I2C_OK)
		;

	// Setup timer 2 (utilized to make sure that initial movement was done in correct direction)
	data = 0x06; //
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, 0x72) != I2C_OK)
		;
	data = 0x00;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, 0x73) != I2C_OK)
		;

	// Threshold 2 (used to wait for stabilization)
	data = ACCLR_SM2_THRS2;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_THRS2)
			!= I2C_OK)
		;

	// Main threshold, decides how hard you have to shake in one direction
	if (threshold == 0x00) {
		threshold = 0xF8;
	}
	data = threshold;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_THRS1)
			!= I2C_OK)
		;

	// State machine mask, decides which axis to include in conditions
	// For state machine 1, we check +x and +y, meaning the x and y axis with their
	// current signs.
	data = 0xA0;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_MASK_A)
			!= I2C_OK)
		;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_MASK_B)
			!= I2C_OK)
		;

	data = ACCLR_SM2_ABS | ACCLR_SM2_SITR;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_SETT1)
			!= I2C_OK)
		;

	/* State machine 2 logic */

	// Check if we went in positive x/y direction
	data = ACCLR_SM_LESS_THRS1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0)
			!= I2C_OK)
		;

	// If we went in the positive x/y direction and stopped, we will generate a force in the
	// opposite (negative) direction. We verify that this happened so we know that the initial movement was in
	// the positive direction.
	data = (ACCLR_SM_TIM2 << ACCLR_SM_SHIFT_RESET) | ACCLR_SM_GREATER_RTHRSH1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 1)
			!= I2C_OK)
		;

	// Wait for accelerometer to stabilize
	data = ACCLR_SM_LESS_RTHRSH1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 2)
			!= I2C_OK)
		;

	// Wait for a shake in opposite (negative) direction, or until timer 1 runs out (reset).
	data = (ACCLR_SM_TIM1 << ACCLR_SM_SHIFT_RESET) | ACCLR_SM_GREATER_RTHRSH1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 3)
			!= I2C_OK)
		;

	// Check for opposite (positive) force again to verify that previous movement was in correct (negative) direction.
	data = (ACCLR_SM_TIM2 << ACCLR_SM_SHIFT_RESET) | ACCLR_SM_LESS_THRS1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 4)
			!= I2C_OK)
		;

	// Wait for accelerometer to stabilize
	data = ACCLR_SM_GREATER_THRS1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 5)
			!= I2C_OK)
		;

	// Next three conditions are the same as the first three
	data = (ACCLR_SM_TIM1 << ACCLR_SM_SHIFT_RESET) | ACCLR_SM_LESS_THRS1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 6)
			!= I2C_OK)
		;

	data = (ACCLR_SM_TIM2 << ACCLR_SM_SHIFT_RESET) | ACCLR_SM_GREATER_RTHRSH1;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 7)
			!= I2C_OK)
		;

	// CONT instruction, generate interrupt and goto start
	data = ACCLR_SM_CMD_CONT;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_INSTR0 + 8)
			!= I2C_OK)
		;

	// Enable state machine 1, route sm interrupt to INT2
	data = ACCLR_SM2_ROUTE_INT2 | ACCLR_SM2_ENABLE;
	while (i2c_write(&data, 1, ACCELEROMETER_ADDRESS, ACCLR_REG_SM2_CTRL)
			!= I2C_OK)
		;

	return ACCELEROMETER_OK;
}
