/*
 * commonVariables.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_COMMONVARIABLES_H_
#define INC_COMMONVARIABLES_H_

/* For LED stripes */
#define PACKING WS2812B_PACKING_SINGLE
#define PREFIX_LEN 1
#define SUFFIX_LEN 4
#define LED_COUNT 7

#include "main.h"

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

/* LED stripes */
enum StripesEffect {
	NONE = 1,
	DEFAULT = 2,
	STOP = 3,
	PARK_SEARCHING = 4,
	PARK_FOUND = 5,
	PARK_NOT_FOUND = 6
};

struct DesiredStripesColor {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

void setStripesEffect(enum StripesEffect, struct DesiredStripesColor *);

/* BLDC motor */
int sliderAccelerateDeceleratePreviousValue = 0;
int sliderAccelerateDecelerateCurrentValue = 0;

/* Stepper motor */
int sliderLeftRightPreviousValue = 0;
int sliderLeftRightCurrentValue = 0;

/* UART */
uint8_t RxBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};

#endif /* INC_COMMONVARIABLES_H_ */
