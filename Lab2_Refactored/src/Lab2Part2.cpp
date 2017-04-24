/*
 * Lab2Part2.cpp
 *
 *  Created on: Dec 6, 2016
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


volatile unsigned char StoredSwitchCommandsArray[60];
volatile unsigned int idStoreSwitchCommands 	= 0;
volatile unsigned int Arraycounter 				= 0;

extern volatile unsigned int idLab2Part3 		= 0;

void Lab2Part2_Launch(void){
	ResetSwitchCommandsArray();
	idStoreSwitchCommands 	= uTTCOSg_AddThread(StoreSwitchCommands,NO_DELAY,EXECUTE_QUARTER_SECOND);
	idDisplayLED 			= uTTCOSg_AddThread(DisplayLED, NO_DELAY, EXECUTE_QUARTER_SECOND);
}
enum DriveKey_State {INIT_SW4, PRESSED_SW4, RELEASED_SW4, CHECK_COAST, THREAD_IS_KILL};
static DriveKey_State current_State = INIT_SW4;
void StoreSwitchCommands(void){
	LEDvalues1to4ToDisplay = currentSwitchValues;
	DriveKey_State next_state = current_State;
	switch(current_State){
	case INIT_SW4:
		next_state = PRESSED_SW4;
		break;
	case PRESSED_SW4:
		if(isSW4Pressed(currentSwitchValues)){
			next_state = RELEASED_SW4;
		}
		break;
	case RELEASED_SW4:
		if(!isSW4Pressed(currentSwitchValues)){
			next_state = CHECK_COAST;
			if(idChristine != 0){
				Kill_and_Launch_Christine();
			}
			StoredSwitchCommandsArray[Arraycounter] = (LEDvalues1to4ToDisplay & 0x7);
			Arraycounter++;
		}
		break;
	case CHECK_COAST:
		 if((Arraycounter >= 3) &&
				 (StoredSwitchCommandsArray[Arraycounter-1] == 0x00 &&
					 StoredSwitchCommandsArray[Arraycounter-2] == 0x00 &&
					 StoredSwitchCommandsArray[Arraycounter-3] == 0x00)){
				 next_state = THREAD_IS_KILL;
		 }
		 else if(Arraycounter >= 59){
			 next_state = THREAD_IS_KILL;
		}
		 else
			 next_state = PRESSED_SW4;
		 break;
	case THREAD_IS_KILL:
		 Stop_Lab2Part2_Launch_Lab2Part3();
		 next_state = INIT_SW4;
		 break;
	}
	current_State = next_state;
}
void ResetSwitchCommandsArray(void){
	for (int i =0; i <60; i++){
		StoredSwitchCommandsArray[i] = 0;
	}
}
//idStoreSwitchCommands 	= uTTCOSg_AddThread(StoreSwitchCommands,NO_DELAY,EXECUTE_QUARTER_SECOND);
void Kill_StoreSwitchCommands(void){
	uTTCOSg_DeleteThread(idStoreSwitchCommands);
}
//idReadSwitches 			= uTTCOSg_AddThread(ReadSwitches, NO_DELAY, EXECUTE_EIGHTH_SECOND);
void Kill_ReadSwitches(void){
	uTTCOSg_DeleteThread(idReadSwitches);
}
//idChristine 	= uTTCOSg_AddThread(Flash_LED5, DELAY_TEN_SECONDS, EXECUTE_EIGHTH_SECOND);
void Kill_Christine_Forever(void){
	uTTCOSg_DeleteThread(idChristine);
	Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~LED5_ON));
}
void Stop_Lab2Part2_Launch_Lab2Part3(void){
	Kill_DisplayLED();
//	Kill_ReadSwitches();
	Kill_Christine_Forever();
	Kill_StoreSwitchCommands();

	idLab2Part3 = uTTCOSg_AddThread(Lab2Part3_Launch, DELAY_FIVE_SECONDS, RUN_ONCE);
}

