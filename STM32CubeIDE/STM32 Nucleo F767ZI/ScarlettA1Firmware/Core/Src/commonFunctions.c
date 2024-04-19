/*
 * commonFunctions.c
 *
 *  Created on: Mar 9, 2024
 *      Author: Piotr Grala
 */

#include "commonFunctions.h"

/* LED stripes */
void setLEDStripesEffect(enum StripesEffect stripesEffect, struct DesiredStripesColor *desiredStripesColor) {
	switch (stripesEffect) {
	case 0:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x00;
		break;
	case 1:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x2B;
		break;
	case 2:
		desiredStripesColor->red = 0x1B;
		desiredStripesColor->green = 0x1B;
		desiredStripesColor->blue = 0x1B;
		break;
	case 3:
		desiredStripesColor->red = 0x27;
		desiredStripesColor->green = 0x13;
		desiredStripesColor->blue = 0x00;
		break;
	}
}

/* BLDC motor */
void setBLDCMotorSpeed(void) {
	switch(sliderAccelerateDecelerateCurrentValue) {
	case -2:
	  BLDCMotorSpeedVoltage = 0.65;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, RESET);
	  break;
	case -1:
	  BLDCMotorSpeedVoltage = 0.45;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, RESET);
	  break;
	case 0:
	  BLDCMotorSpeedVoltage = 0.0;
	  break;
	case 1:
	  BLDCMotorSpeedVoltage = 0.45;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, SET);
	  break;
	case 2:
	  BLDCMotorSpeedVoltage = 0.65;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, SET);
	  break;
	case 3:
	  BLDCMotorSpeedVoltage = 0.9;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, SET);
	  break;
	case 4:
	  BLDCMotorSpeedVoltage = 1.2;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, SET);
	  break;
	}

	BLDCMotorSpeedValue = BLDCMotorSpeedVoltage * (0xfff + 1) / 3.3;
	HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, BLDCMotorSpeedValue);
}

/* Stepper motor */
void moveStepperMotor(enum Direction direction) {
	if(direction == LEFT) {
		HAL_GPIO_WritePin(StepperMotorDir_GPIO_Port, StepperMotorDir_Pin, RESET);
	} else {
		HAL_GPIO_WritePin(StepperMotorDir_GPIO_Port, StepperMotorDir_Pin, SET);
	}

	TIM4->CCR3 = 500;
	osDelay(70);
	TIM4->CCR3 = 0;
}

void moveStepperMotorUntil(int targetLeftRightPosition) {
	if(sliderLeftRightCurrentValue == targetLeftRightPosition) {
		// Do nothing
	} else if(sliderLeftRightCurrentValue > targetLeftRightPosition) {
		// Turn left until target left/right position is reached
		for(sliderLeftRightCurrentValue; sliderLeftRightCurrentValue != targetLeftRightPosition; sliderLeftRightPreviousValue = sliderLeftRightCurrentValue --) {
			moveStepperMotor(LEFT);
			osDelay(LEFT_RIGHT_DURATION);
		}
	} else {
		// Turn right until target left/right position is reached
		for(sliderLeftRightCurrentValue; sliderLeftRightCurrentValue != targetLeftRightPosition; sliderLeftRightPreviousValue = sliderLeftRightCurrentValue ++) {
			moveStepperMotor(RIGHT);
			osDelay(LEFT_RIGHT_DURATION);
		}
	}
}

/* LiDAR sphere */
void park(enum Direction direction) {
	// Private variables
	int targetLeftRightPosition = 0;

	// Stop BLDC motor
	sliderAccelerateDeceleratePreviousValue = sliderAccelerateDecelerateCurrentValue;
	sliderAccelerateDecelerateCurrentValue = 0;
	setBLDCMotorSpeed();

	// Set LED stripes
	stripesEffect = PARKING;
	ommitToggle = true;
	internalFunctionCall = true;
	vTaskResume(LEDStripesTaskHandle);

	// Toggle left/right blinkers
	if(direction == LEFT) {
		internalFunctionCall = true;
		vTaskResume(LeftBlinkersTasHandle);
	} else {
		internalFunctionCall = true;
		vTaskResume(RightBlinkersTaHandle);
	}

	// Turn left/right to the destination
	if(direction == LEFT) {
		targetLeftRightPosition = -3;
	} else {
		targetLeftRightPosition = 3;
	}
	moveStepperMotorUntil(targetLeftRightPosition);

	// Withdraw a little bit
	internalFunctionCall = true;
	vTaskResume(DecelerateTaskHandle);
	osDelay(ACCELERATE_DECELERATE_DURATION * 0.60);
	internalFunctionCall = true;
	vTaskResume(AccelerateTaskHandle);

	// Turn left/right from the destination
	if(direction == LEFT) {
		targetLeftRightPosition = 3;
	} else {
		targetLeftRightPosition = -3;
	}
	moveStepperMotorUntil(targetLeftRightPosition);

	// Withdraw a little bit
	internalFunctionCall = true;
	vTaskResume(DecelerateTaskHandle);
	osDelay(ACCELERATE_DECELERATE_DURATION * 0.65);
	internalFunctionCall = true;
	vTaskResume(AccelerateTaskHandle);

	// Turn left/right to center position
	targetLeftRightPosition = 0;
	moveStepperMotorUntil(targetLeftRightPosition);

	// Drive forward a little bit
	internalFunctionCall = true;
	vTaskResume(AccelerateTaskHandle);
	osDelay(ACCELERATE_DECELERATE_DURATION * 0.85);
	internalFunctionCall = true;
	vTaskResume(DecelerateTaskHandle);

	// Set LED stripes
	if(isOn) {
		stripesEffect = DEFAULT;
	} else {
		stripesEffect = NONE;
	}
	ommitToggle = true;
	internalFunctionCall = true;
	vTaskResume(LEDStripesTaskHandle);
}
