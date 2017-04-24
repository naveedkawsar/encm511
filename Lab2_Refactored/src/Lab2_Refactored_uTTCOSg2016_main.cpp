/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: ksbengal 
* Date: Mon 2016/12/05 at 06:08:09 PM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "Lab2_Refactored_uTTCOSg2016_main.h"

// This timing MACRO may need adjusting	
#undef  EXECUTE_EVERY_SECOND
#define EXECUTE_EVERY_SECOND 		(14 * uTTCOSg_GetTickFrequency( )) // ADJUST ME
#define EXECUTE_EIGHTH_SECOND		(14 * uTTCOSg_GetTickFrequency( ))/8

#define DELAY_FIVE_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))*5
#define DELAY_TEN_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))*10
#define DELAY_ONE_SECONDS			(14 * uTTCOSg_GetTickFrequency( ))

void BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task(void); 

volatile unsigned int idGoldilocks = 0;
volatile unsigned int idLab2Part1 = 0;
volatile unsigned int idChristine = 0;
volatile unsigned int idWoodElf = 0;
volatile unsigned int idNarrator = 0;

void main(void) {
	// Make maxNumberThreads at least 5 larger than the number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 8;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

	uTTCOSg_OS_Init(USE_AUDIO_INTERRUPT, 0, 44000);

	Init_LED_GPIOInterface();
	Write_LED_GPIOInterface(0);

	Init_Input_GPIOInterface();

	idNarrator 		= uTTCOSg_AddThread(Flash_LED6, NO_DELAY, EXECUTE_EVERY_SECOND);
	idGoldilocks	= uTTCOSg_AddThread(Flash_LED4, DELAY_FIVE_SECONDS, EXECUTE_EVERY_SECOND);
	idLab2Part1 	= uTTCOSg_AddThread(Lab2Part1_Launch, DELAY_FIVE_SECONDS, RUN_ONCE);
  	idWoodElf 		= uTTCOSg_AddThread(WoodElf_TwinkleLights, DELAY_ONE_SECOND, RUN_ONCE);
  	idChristine 	= uTTCOSg_AddThread(Flash_LED5, DELAY_TEN_SECONDS, EXECUTE_EIGHTH_SECOND);

	uTTCOSg_Start_Scheduler(maxNumberThreads);   //  Start the scheduler timer
				// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks
	while (1) {

		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		uTTCOSg_GoToSleep( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads( );
	}

}

