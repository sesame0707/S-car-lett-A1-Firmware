/*
 * commonFunctions.h
 *
 *  Created on: Mar 9, 2024
 *      Author: Piotr Grala
 */

#ifndef INC_COMMONFUNCTIONS_H_
#define INC_COMMONFUNCTIONS_H_

#include "commonVariables.h"
#include "dac.h"

/* LED stripes */
void setLEDStripesEffect(enum StripesEffect stripesEffect, struct DesiredStripesColor *desiredStripesColor);

/* BLDC motor */
void setBLDCMotorSpeed(void);

#endif /* INC_COMMONFUNCTIONS_H_ */
