/*
 * firmwareConfig.h
 *
 *  Created on: Mar 9, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_FIRMWARECONFIG_H_
#define INC_FIRMWARECONFIG_H_

/* General */
#define ACKNOWLEDGE_PACKETS_FREQUENCY	5000
#define TIME_MARGIN						500

/* OLED */
#define STARTUP_DURATION	3000

/* LED stripes */
#define PACKING		WS2812B_PACKING_SINGLE
#define PREFIX_LEN	1
#define SUFFIX_LEN	4
#define LED_COUNT	7

/* Lights */
#define BLINKERS_DURATION		400
#define BRAKE_LIGHTS_DURATION	500

#endif /* INC_FIRMWARECONFIG_H_ */
