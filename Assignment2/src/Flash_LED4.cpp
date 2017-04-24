/*
 * Flash_LED4.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: nkawsar
 */

#include "Lab0Lib.h"

#define LED4_ON_MASK	0x08
#define LED4_OFF_MASK	~(0x08)

enum bitwise_LED4_State {JUST_STARTED, IS_OFF, IS_ON};
static bitwise_LED4_State currentState = JUST_STARTED;

void Flash_LED4(void) {
	bitwise_LED4_State nextStateToDo = currentState;

	switch (currentState) {
	case JUST_STARTED:
		Write_LED_GPIOInterface(LED4_OFF_MASK & Read_LED_GPIOInterface());// << (3 - 1)); // Turn off LED 3
		nextStateToDo = IS_OFF;
		break;
	case IS_OFF:
		Write_LED_GPIOInterface(LED4_ON_MASK | Read_LED_GPIOInterface());// << (3 - 1));  // Was off turn it on
		nextStateToDo = IS_ON;
		break;
	case IS_ON:
		Write_LED_GPIOInterface(LED4_OFF_MASK & Read_LED_GPIOInterface());// << (3 - 1)); // Turn off LED 3
		nextStateToDo = IS_OFF;
	break;
	}

	currentState = nextStateToDo;
}


