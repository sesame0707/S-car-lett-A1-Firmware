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
	case 1:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x00;
		break;
	case 2:
		desiredStripesColor->red = 0x40;
		desiredStripesColor->green = 0x20;
		desiredStripesColor->blue = 0x00;
		break;
	case 3:
		desiredStripesColor->red = 0x40;
		desiredStripesColor->green = 0x40;
		desiredStripesColor->blue = 0x40;
		break;
	case 4:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x40;
		break;
	}
}

/* BLDC motor */
void setBLDCMotorSpeed(void) {
	switch(sliderAccelerateDecelerateCurrentValue) {
	case -2:
	  BLDCMotorSpeedVoltage = 0.5;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, SET);
	  break;
	case -1:
	  BLDCMotorSpeedVoltage = 0.4;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, SET);
	  break;
	case 0:
	  BLDCMotorSpeedVoltage = 0.0;
	  break;
	case 1:
	  BLDCMotorSpeedVoltage = 0.4;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, RESET);
	  break;
	case 2:
	  BLDCMotorSpeedVoltage = 0.5;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, RESET);
	  break;
	case 3:
	  BLDCMotorSpeedVoltage = 0.6;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, RESET);
	  break;
	case 4:
	  BLDCMotorSpeedVoltage = 0.7;
	  HAL_GPIO_WritePin(BLDCMotorDir_GPIO_Port, BLDCMotorDir_Pin, RESET);
	  break;
	}

	BLDCMotorSpeedValue = BLDCMotorSpeedVoltage * (0xfff + 1) / 3.3;
	HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, BLDCMotorSpeedValue);
}

/* Stepper motor */
void moveStepperMotor(void) {
	TIM4->CCR3 = 500;
	osDelay(35);
	TIM4->CCR3 = 0;
}
