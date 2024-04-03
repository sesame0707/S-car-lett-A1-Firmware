/*
 * commonVariables.c
 *
 *  Created on: Mar 9, 2024
 *      Author: Piotr Grala
 */

#include "commonVariables.h"

/* General */
volatile bool internalFunctionCall = false;

/* OLED */
volatile bool isConnected = false;

/* LED stripes */
volatile enum StripesEffect stripesEffect = NONE;
volatile bool isOn = false;
volatile bool ommitToggle = false;
volatile bool isStopped = false;

/* BLDC motor */
volatile int sliderAccelerateDeceleratePreviousValue = 0;
volatile int sliderAccelerateDecelerateCurrentValue = 0;
volatile bool isWithdrawing = false;
volatile float BLDCMotorSpeedVoltage = 0.0;
volatile uint32_t BLDCMotorSpeedValue = 0.0;

/* Stepper motor */
volatile int sliderLeftRightPreviousValue = 0;
volatile int sliderLeftRightCurrentValue = 0;

/* LiDAR sphere */
volatile bool isParking = false;

/* UART */
volatile uint8_t RxBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
