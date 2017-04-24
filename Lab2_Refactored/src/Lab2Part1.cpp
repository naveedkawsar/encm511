/*
 * Lab2Part1.cpp
 *
 *  Created on: Dec 5, 2016
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

#define SW1_ON		0x01
#define SW2_ON		0x02
#define SW3_ON		0x04
#define SW4_ON		0x08

#define LED4_ON		0x08
#define LED5_ON		0x10
#define LED6_ON		0x20

#define SW1_SW3		0x05
#define SW2_SW3		0x06
#define SW1_SW2		0x03

volatile unsigned int idLED1 = 0;
volatile unsigned int idLED2 = 0;
volatile unsigned int idLED3 = 0;

volatile unsigned int idReadSwitches			= 0;
volatile unsigned int idDisplayLED				= 0;
volatile unsigned int idHandleSwitchCommands	= 0;
volatile unsigned int idCheck_KeyPress			= 0;

volatile unsigned char currentSwitchValues 			= 0;
volatile char LEDvalues1to4ToDisplay 				= 0;
volatile unsigned char init_LEDvalues 				= 0;
volatile unsigned int countSW4pressed				= 0;

volatile unsigned int kill_fairy_count	= 0;
volatile unsigned int idLab2Part2 = 0;

void Lab2Part1_Launch (void){
	// Function stub
	idReadSwitches 			= uTTCOSg_AddThread(ReadSwitches, NO_DELAY, EXECUTE_EIGHTH_SECOND);
	idHandleSwitchCommands 	= uTTCOSg_AddThread(HandleSwitchCommands, NO_DELAY, EXECUTE_EIGHTH_SECOND);
}
void WoodElf_TwinkleLights (void){
	idLED1 = uTTCOSg_AddThread(Flash_LED1,DELAY_ONE_SECONDS, EXECUTE_EVERY_SECOND);
	idLED2 = uTTCOSg_AddThread(Flash_LED2,DELAY_TW0_SECONDS, EXECUTE_EVERY_SECOND);
	idLED3 = uTTCOSg_AddThread(Flash_LED3,DELAY_THREE_SECONDS, EXECUTE_EVERY_SECOND);
}
void ReadSwitches(){
	currentSwitchValues = My_ReadSwitches();
}
void DisplayLED() {
	if((LEDvalues1to4ToDisplay & SW1_ON) == SW1_ON )
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() | SW1_ON );
	else
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~SW1_ON) );

	if((LEDvalues1to4ToDisplay & SW2_ON) == SW2_ON )
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() | SW2_ON );
	else
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~SW2_ON) );

	if((LEDvalues1to4ToDisplay & SW3_ON) == SW3_ON )
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() | SW3_ON );
	else
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~SW3_ON) );

	if((LEDvalues1to4ToDisplay & SW4_ON) == SW4_ON )
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() | SW4_ON );
	else
		Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~SW4_ON) );
}
void HandleSwitchCommands(void) {
	LEDvalues1to4ToDisplay = currentSwitchValues;
	if(LEDvalues1to4ToDisplay != 0x00){
		kill_fairy_count++;
		if(kill_fairy_count == 1){
			Kill_WoodElf_TwinkleLights();
			Kill_and_Launch_Christine();
			idDisplayLED 		= uTTCOSg_AddThread(DisplayLED, NO_DELAY, EXECUTE_EIGHTH_SECOND);
			idCheck_KeyPress 	= uTTCOSg_AddThread(Check_KeyPress, NO_DELAY, EXECUTE_EIGHTH_SECOND);
		}
	}
}
enum CheckKey_State {INIT, SW4_PRESSED, SW4_RELEASED, SW4_TIME, CHECK_SW123, CHECK_SW123_AGAIN, KILL_THREADS};
static CheckKey_State currentState = INIT;
void Check_KeyPress(void){
	CheckKey_State nextState = currentState;
	switch(currentState){
	case INIT:
		nextState = CHECK_SW123;
		break;
	case CHECK_SW123:
		int SW123 = (LEDvalues1to4ToDisplay & 0x07);
		if( SW123 == SW1_SW3 || SW123 == SW2_SW3 || SW123 == SW1_SW2){
			init_LEDvalues 	= currentSwitchValues;
			nextState 		= SW4_RELEASED;
		}
		break;
		// If 12 or 13 or 23
			// Save SW123 values
			//Goto SW4 Released
		// Else stay here
	case SW4_RELEASED:
		countSW4pressed = 0;
		if(isSW4Pressed(currentSwitchValues)){
			nextState = SW4_PRESSED;
		}
		break;
	case SW4_PRESSED:
		countSW4pressed++;
		if(!isSW4Pressed(currentSwitchValues)){
			nextState = SW4_TIME;
		}
		break;
	case SW4_TIME:
		if( countSW4pressed > 25 && countSW4pressed < 80){
			nextState = CHECK_SW123_AGAIN;
		}else{
			nextState 		= CHECK_SW123;
			Kill_Goldilocks();
//			idGoldilocks 	= uTTCOSg_AddThread(Flash_LED4, DELAY_ONE_SECONDS, EXECUTE_QUARTER_SECOND);
		}
		break;
	case CHECK_SW123_AGAIN:
	// If SW123 == Saved SW123 from before
		// goto Kill Threads
	// Else
		// goto Check SW123
		if(init_LEDvalues == currentSwitchValues){
			nextState = KILL_THREADS;
		}else
			nextState = CHECK_SW123;
		break;
	case KILL_THREADS:
		Stop_Lab2Part1_Launch_Lab2Part2();
		break;
	}
	currentState = nextState;
}
void Kill_and_Launch_Narrator(void){
	uTTCOSg_DeleteThread(idNarrator);
	Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~LED6_ON));
	Launch_Narrator_with_Delay();
}
void Launch_Narrator_with_Delay(void){
	idNarrator = uTTCOSg_AddThread(Flash_LED6, DELAY_FIVE_SECONDS, EXECUTE_QUARTER_SECOND);
}
void Kill_WoodElf_TwinkleLights(void){
	uTTCOSg_DeleteThread(idLED1);
	uTTCOSg_DeleteThread(idLED2);
	uTTCOSg_DeleteThread(idLED3);

	Write_LED_GPIOInterface(0xF8);
}
//idChristine = uTTCOSg_AddThread(Flash_LED5, DELAY_TEN_SECONDS, EXECUTE_EIGHTH_SECOND);
void Kill_and_Launch_Christine(void){
	uTTCOSg_DeleteThread(idChristine);
	Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~LED5_ON));
	Launch_Christine_with_Delay();
}
void Launch_Christine_with_Delay(void){
	idChristine = uTTCOSg_AddThread(Flash_LED5, DELAY_TEN_SECONDS, EXECUTE_EIGHTH_SECOND);
}
//idGoldilocks 	= uTTCOSg_AddThread(Flash_LED4, DELAY_ONE_SECONDS, EXECUTE_QUARTER_SECOND);
void Kill_Goldilocks(void){
	uTTCOSg_DeleteThread(idGoldilocks);
	Write_LED_GPIOInterface(Read_LED_GPIOInterface() & (~LED4_ON));
}
//idDisplayLED 		= uTTCOSg_AddThread(DisplayLED, NO_DELAY, EXECUTE_EIGHTH_SECOND);
void Kill_DisplayLED(void){
	uTTCOSg_DeleteThread(idDisplayLED);
	Write_LED_GPIOInterface(Read_LED_GPIOInterface() & 0xF8);
}
//idHandleSwitchCommands 	= uTTCOSg_AddThread(HandleSwitchCommands, NO_DELAY, EXECUTE_EIGHTH_SECOND);
void Kill_HandleSwitchCommands(void){
	uTTCOSg_DeleteThread(idHandleSwitchCommands);
}
//idCheck_KeyPress 	= uTTCOSg_AddThread(Check_KeyPress, NO_DELAY, EXECUTE_EIGHTH_SECOND);
void Kill_Check_KeyPress(void){
	uTTCOSg_DeleteThread(idCheck_KeyPress);
}
void Stop_Lab2Part1_Launch_Lab2Part2(void){
	// Call functions to Kill Threads
	Kill_DisplayLED();
	Kill_Check_KeyPress();
	Kill_HandleSwitchCommands();
	Kill_Goldilocks();
	Kill_and_Launch_Narrator();
	Kill_and_Launch_Christine();

	// Launch Lab2Part2
	idLab2Part2 = uTTCOSg_AddThread(Lab2Part2_Launch, DELAY_FIVE_SECONDS, RUN_ONCE);
}
