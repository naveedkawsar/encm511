/*
 * Lab2Part3.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: ksbengal
 */
#include "Lab2_Refactored_uTTCOSg2016_main.h"

#undef  EXECUTE_EVERY_SECOND
#define EXECUTE_EVERY_SECOND 		(14 * uTTCOSg_GetTickFrequency( )) // ADJUST ME
#define EXECUTE_HALF_SECOND			(14 * uTTCOSg_GetTickFrequency( ))/2
#define EXECUTE_EIGHTH_SECOND		(14 * uTTCOSg_GetTickFrequency( ))/8
#define EXECUTE_QUARTER_SECOND		(14 * uTTCOSg_GetTickFrequency( ))/4

#define DELAY_THREE_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))*3
#define DELAY_TW0_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))*2
#define DELAY_FIVE_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))*5
#define DELAY_TEN_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))*10
#define DELAY_ONE_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))

#define LED4_ON		0x08
#define LED5_ON		0x10
#define LED6_ON		0x20

volatile unsigned int idReadSwitchCommandsArray = 0;
volatile unsigned int idTroll_Function			= 0;

void Lab2Part3_Launch(void) {
	idDisplayLED = 				uTTCOSg_AddThread(DisplayLED, NO_DELAY, EXECUTE_EVERY_SECOND);
	idReadSwitchCommandsArray = uTTCOSg_AddThread(ReadSwitchCommandsArray, NO_DELAY, EXECUTE_EVERY_SECOND);

}

void ReadSwitchCommandsArray(void) {
	LEDvalues1to4ToDisplay = StoredSwitchCommandsArray[--Arraycounter];

	if (Arraycounter == 0)
	{
		idWoodElf 			= uTTCOSg_AddThread(WoodElf_TwinkleLights, DELAY_ONE_SECOND, RUN_ONCE);
		idTroll_Function 	= uTTCOSg_AddThread(Troll_Function, DELAY_ONE_SECOND, EXECUTE_QUARTER_SECOND);
		Kill_DisplayLED();
		Kill_ReadSwitchCommandsArray();
	}
}

enum Troll_State {INIT, ALL_SW_PRESSED, SW4_RELEASED, KILL_THREADS};
static Troll_State currentState = INIT;
void Troll_Function(void) {
	Troll_State nextState = currentState;
	switch(currentState){
	case INIT:
		nextState = ALL_SW_PRESSED;
		break;
	case ALL_SW_PRESSED:
		unsigned int SW1234 = (currentSwitchValues & 0x0F);
		if (SW1234 == 0x0F) {
			nextState = SW4_RELEASED;
			break;
		}
		break;
	case SW4_RELEASED:
		if(!isSW4Pressed(currentSwitchValues)){
			nextState = KILL_THREADS;
			break;
		}
		break;
	case KILL_THREADS:
		Kill_ReadSwitches();
		Kill_WoodElf_TwinkleLights();
		Kill_Narrator();
		Stop_Lab2Part3_Launch_Lab2Part1();
		Kill_Troll_Function();
		break;
	}
	currentState = nextState;
}

void Kill_Narrator(void){
	uTTCOSg_DeleteThread(idNarrator);
	Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~LED6_ON));
}

void Kill_ReadSwitchCommandsArray(void) {
	uTTCOSg_DeleteThread(idReadSwitchCommandsArray);
}

void Kill_Troll_Function(void){
	uTTCOSg_DeleteThread(idTroll_Function);
}

void Stop_Lab2Part3_Launch_Lab2Part1(void){
	Write_LED_GPIOInterface(0);
	idNarrator 		= uTTCOSg_AddThread(Flash_LED6, NO_DELAY, EXECUTE_EVERY_SECOND);
	idGoldilocks	= uTTCOSg_AddThread(Flash_LED4, DELAY_FIVE_SECONDS, EXECUTE_EVERY_SECOND);
	idLab2Part1 	= uTTCOSg_AddThread(Lab2Part1_Launch, DELAY_FIVE_SECONDS, RUN_ONCE);
	idWoodElf 		= uTTCOSg_AddThread(WoodElf_TwinkleLights, DELAY_ONE_SECOND, RUN_ONCE);
	idChristine 	= uTTCOSg_AddThread(Flash_LED5, DELAY_TEN_SECONDS, EXECUTE_EIGHTH_SECOND);
}
