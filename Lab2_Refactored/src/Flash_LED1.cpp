/*
 * Flash_LED1.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: nkawsar
 */

#include "Lab0Lib.h"

#define LED1_ON_MASK	0x01
#define LED1_OFF_MASK	~(0x01)

enum bitwise_LED1_State {JUST_STARTED, IS_OFF, IS_ON};
static bitwise_LED1_State currentState = JUST_STARTED;

void Flash_LED1(void) {
	bitwise_LED1_State nextStateToDo = currentState;

	switch (currentState) {
	case JUST_STARTED:
		Write_LED_GPIOInterface(LED1_OFF_MASK & Read_LED_GPIOInterface());// << (3 - 1)); // Turn off LED 3
		nextStateToDo = IS_OFF;
		break;
	case IS_OFF:
		Write_LED_GPIOInterface(LED1_ON_MASK | Read_LED_GPIOInterface());// << (3 - 1));  // Was off turn it on
		nextStateToDo = IS_ON;
		break;
	case IS_ON:
		Write_LED_GPIOInterface(LED1_OFF_MASK & Read_LED_GPIOInterface());// << (3 - 1)); // Turn off LED 3
		nextStateToDo = IS_OFF;
	break;
	}

	currentState = nextStateToDo;
}
