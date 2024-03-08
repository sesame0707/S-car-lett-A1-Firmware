/*
 * commonVariables.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_COMMONVARIABLES_H_
#define INC_COMMONVARIABLES_H_

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
	DEFAULT = 1,
	STOP = 2,
	PARK_SEARCHING = 3,
	PARK_FOUND = 4,
	PARK_NOT_FOUND = 5
};

/* BLDC motor */
int sliderAccelerateDeceleratePreviousValue = 0;
int sliderAccelerateDecelerateCurrentValue = 0;

/* Stepper motor */
int sliderLeftRightPreviousValue = 0;
int sliderLeftRightCurrentValue = 0;

/* UART */
uint8_t RxBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};

#endif /* INC_COMMONVARIABLES_H_ */
