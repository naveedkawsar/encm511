/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: ksbengal 
* Date: Wed 2016/12/07 at 05:42:08 PM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "Lab4_Refactored_uTTCOSg2016_main.h"

volatile unsigned short int idInit_LCD		= 0;

#define EVERY_SEC						14*uTTCOSg_GetTickFrequency( )
#define EVERY_TWO_SECS					14*uTTCOSg_GetTickFrequency( )*2
#define EVERY_FIFTH_SECS				14*uTTCOSg_GetTickFrequency( )/5
#define EVERY_FIVE_SECS					14*uTTCOSg_GetTickFrequency( )*5
#define DELAY_EVERY_SEC					14*uTTCOSg_GetTickFrequency( )
#define DELAY_TWO_SECS					14*uTTCOSg_GetTickFrequency( )*2
#define DELAY_THREE_SECS				14*uTTCOSg_GetTickFrequency( )*3
#define DELAY_THREE_HALVES_SECS			14*uTTCOSg_GetTickFrequency( )*3.5
#define DELAY_FOUR_SECS					14*uTTCOSg_GetTickFrequency( )*4
#define DELAY_FOUR_HALVES_SECS			14*uTTCOSg_GetTickFrequency( )*4.5
#define DELAY_FIVE_SECS					14*uTTCOSg_GetTickFrequency( )*5


void main(void) {
	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 8;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

	uTTCOSg_OS_Init(USE_AUDIO_INTERRUPT, 0, 44000);

	My_InitLED();
	My_InitSwitches();

	uTTCOSg_AddThread(Flash_LED6, NO_DELAY, EVERY_SEC);
	uTTCOSg_AddThread(SPI_controller, NO_DELAY, EVERY_FIFTH_SECS); // Make Faster Later
	uTTCOSg_AddThread(Init_SPI, DELAY_EVERY_SEC, RUN_ONCE);
	idInit_LCD = uTTCOSg_AddThread(Init_LCD, DELAY_EVERY_SEC, EVERY_FIFTH_SECS);
//	uTTCOSg_AddThread(Temp_SPI_controller, DELAY_THREE_SECS, EVERY_FIFTH_SECS); // Make Faster Later
	uTTCOSg_AddThread(MSG0, DELAY_TWO_SECS, EVERY_TWO_SECS/4);
	uTTCOSg_AddThread(MSG1, DELAY_TWO_SECS, EVERY_TWO_SECS/8);
	uTTCOSg_AddThread(LAB3_temp, DELAY_TWO_SECS, EVERY_TWO_SECS/6);

	uTTCOSg_Start_Scheduler(maxNumberThreads);   //  Start the scheduler timer
	while (1) {
		uTTCOSg_GoToSleep( );
		uTTCOSg_DispatchThreads( );
	}
}

