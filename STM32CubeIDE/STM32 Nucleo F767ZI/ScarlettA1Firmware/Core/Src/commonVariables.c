/*
 * commonVariables.c
 *
 *  Created on: Mar 8, 2024
 *      Author: Piotr Grala
 */

#include "commonVariables.h"

/* LED stripes */
void setStripesEffect(enum StripesEffect stripesEffect, struct DesiredStripesColor *desiredStripesColor) {
	switch (stripesEffect) {
	case 1:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x00;
		break;
	case 2:
		desiredStripesColor->red = 0x40;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x40;
		break;
	case 3:
		desiredStripesColor->red = 0x40;
		desiredStripesColor->green = 0x40;
		desiredStripesColor->blue = 0x40;
		break;
	case 4:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x40;
		break;
	case 5:
		desiredStripesColor->red = 0x00;
		desiredStripesColor->green = 0x40;
		desiredStripesColor->blue = 0x00;
		break;
	case 6:
		desiredStripesColor->red = 0x40;
		desiredStripesColor->green = 0x00;
		desiredStripesColor->blue = 0x00;
		break;
	}
}
