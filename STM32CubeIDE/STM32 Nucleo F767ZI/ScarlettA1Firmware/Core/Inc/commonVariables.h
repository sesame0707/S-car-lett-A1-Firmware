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

extern bool isConnected;

/* LED stripes */
enum StripesEffect {
	NONE = 1,
	DEFAULT = 2,
	STOP = 3,
	PARK_SEARCHING = 4,
	PARK_FOUND = 5,
	PARK_NOT_FOUND = 6
};

extern enum StripesEffect stripesEffect;

struct DesiredStripesColor {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

/* BLDC motor */
extern int sliderAccelerateDeceleratePreviousValue;
extern int sliderAccelerateDecelerateCurrentValue;

/* Stepper motor */
extern int sliderLeftRightPreviousValue;
extern int sliderLeftRightCurrentValue;

/* UART */
extern uint8_t RxBuffer[];

#endif /* INC_COMMONVARIABLES_H_ */
