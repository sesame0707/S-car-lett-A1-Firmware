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

/* OLED */
enum Header {
	BOOTING_UP = 1,
	DISCONNECTED = 2,
	CONNECTED = 3
};

enum Body {
	VERSION = 1,
	LOGOTYPE = 2
};

extern volatile bool isConnected;

/* LED stripes */
enum StripesEffect {
	NONE = 1,
	DEFAULT = 2,
	STOP = 3,
	PARK_SEARCHING = 4,
	PARK_FOUND = 5,
	PARK_NOT_FOUND = 6
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

/* UART */
extern volatile uint8_t RxBuffer[];

#endif /* INC_COMMONVARIABLES_H_ */
