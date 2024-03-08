/*
 * commonStrings.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_COMMONSTRINGS_H_
#define INC_COMMONSTRINGS_H_

#include "main.h"

/* Firmware information */
const int versionCode = 0;
const char versionName[] = "1.x";

/* OLED */
char headerBootingUp[] = "Booting up...";			// Enum 1
char headerDisconnected[] = "Disconnected";			// Enum 2
char headerConnected[] = "Connected";				// Enum 3

char bodyVersion[] = "Version ";					// Enum 1
char bodyLogotype[] = "S(car)lett";					// Enum 2

#endif /* INC_COMMONSTRINGS_H_ */
