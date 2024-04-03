/*
 * commonVariables.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_COMMONVARIABLES_H_
#define INC_COMMONVARIABLES_H_

#include <stdint.h>
#include <stdbool.h>

/* General */
enum Direction {
	LEFT = 0,
	RIGHT = 1
};

extern volatile bool internalFunctionCall;

/* OLED */
enum Header {
	BOOTING_UP = 0,
	DISCONNECTED = 1,
	CONNECTED = 2
};

enum Body {
	VERSION = 0,
	LOGOTYPE = 1
};

extern volatile bool isConnected;

/* LED stripes */
enum StripesEffect {
	NONE = 0,
	DEFAULT = 1,
	STOP = 2,
	PARKING = 3
};

extern volatile enum StripesEffect stripesEffect;
extern volatile bool isOn;
extern volatile bool ommitToggle;
extern volatile bool isStopped;

struct DesiredStripesColor {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

/* BLDC motor */
extern volatile int sliderAccelerateDeceleratePreviousValue;
extern volatile int sliderAccelerateDecelerateCurrentValue;
extern volatile bool isWithdrawing;
extern volatile float BLDCMotorSpeedVoltage;
extern volatile uint32_t BLDCMotorSpeedValue;

/* Stepper motor */
extern volatile int sliderLeftRightPreviousValue;
extern volatile int sliderLeftRightCurrentValue;

/* LiDAR sphere */
extern volatile bool isParking;

/* UART */
extern volatile uint8_t RxBuffer[];

#endif /* INC_COMMONVARIABLES_H_ */
