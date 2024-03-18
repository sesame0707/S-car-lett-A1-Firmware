/*
 * commonFunctions.h
 *
 *  Created on: Mar 9, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_COMMONFUNCTIONS_H_
#define INC_COMMONFUNCTIONS_H_

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "dac.h"

#include "commonVariables.h"
#include "firmwareConfig.h"

extern osThreadId_t LEDStripesTaskHandle;
extern osThreadId_t LeftBlinkersTasHandle;
extern osThreadId_t RightBlinkersTaHandle;
extern osThreadId_t DecelerateTaskHandle;
extern osThreadId_t AccelerateTaskHandle;

/* LED stripes */
void setLEDStripesEffect(enum StripesEffect stripesEffect, struct DesiredStripesColor *desiredStripesColor);

/* BLDC motor */
void setBLDCMotorSpeed(void);

/* Stepper motor */
void moveStepperMotor(enum Direction direction);
void moveStepperMotorUntil(int targetLeftRightPosition);

/* LiDAR sphere */
void park(enum Direction direction);

#endif /* INC_COMMONFUNCTIONS_H_ */
