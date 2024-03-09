/*
 * commonVariables.c
 *
 *  Created on: Mar 9, 2024
 *      Author: Piotr Grala
 */

#include "commonVariables.h"

/* OLED */
bool isConnected = true;

/* LED stripes */
enum StripesEffect stripesEffect = NONE;

/* BLDC motor */
int sliderAccelerateDeceleratePreviousValue = 0;
int sliderAccelerateDecelerateCurrentValue = 0;

/* Stepper motor */
int sliderLeftRightPreviousValue = 0;
int sliderLeftRightCurrentValue = 0;

/* UART */
uint8_t RxBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};