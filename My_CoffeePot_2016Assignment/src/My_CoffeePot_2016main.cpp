/*****************************************************************************
 * My_CoffeePot_2016Assignment.cpp
 *****************************************************************************/

#include "My_CoffeePot_2016main.h"

#include <sys/platform.h>
//#include "adi_initialize.h"
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include "MyCoffeePotFunctions_forCPP.h"	//NOTE: LEAVE IN UNLESS MAIN.H INCLUDES

#define DO_SECOND_POT					0
#define CONTROL_TWO_POTS_AT_ONE_TIME	0
#define VOLUME_COFFEEPOT_ONE_ML			484
#define VOLUME_COFFEEPOT_TWO_ML			320
#define PERCENT_NINETY					0.9

void NetworkTimingFudge_USE_CCES_GUI_Delay(void) {/*FUNCTION STUB*/}

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
/*char __argv_string[] = "";*/

int main(int argc, char *argv[])
{
	/* Begin adding your custom code here */

	int numCoffeePots = 2; 									// 4 by end of assignment

	WHICHDISPLAY whichDisplay = USE_TEXT_GUI;				// Use at beginning
//	WHICHDISPLAY whichDisplay = USE_CCES_GUI;
//	WHICHDISPLAY whichDisplay = (WHICHDISPLAY) (USE_TEXT_GUI | USE_TEXT_GUI) ;
//	WHICHDISPLAY whichDisplay = (WHICHDISPLAY) (USE_TEXT_GUI | USE_SPI_GUI);
	Init_CoffeePotSimulation(numCoffeePots, whichDisplay);
	
	char uniqueCoffeePotName1[] = "Naveed";
	char uniqueCoffeePotName2[] = "Kawsar";

	// Simulate plugging in new plug-and-play coffeepot controller devices into USB port
	COFFEEPOT_DEVICE *coffeePot1_BaseAddress  = (COFFEEPOT_DEVICE *) NULL;
	coffeePot1_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT1, uniqueCoffeePotName1);
	// The simulated MOCK device must be told to update
	My_SimulateOneSecondPassing_CPP();

	// Going to call the code to fill a coffeepot to a desired water level but not to any heating
	unsigned short int waterLevelRequired1 = VOLUME_COFFEEPOT_ONE_ML*PERCENT_NINETY;
	unsigned short int waterTemperatureRequired1 = 100;
	My_DemonstrateCoffeePotAction(coffeePot1_BaseAddress, uniqueCoffeePotName1, waterLevelRequired1, waterTemperatureRequired1);

#if DO_SECOND_POT // Leave the second example until we can get the first one to work
	COFFEEPOT_DEVICE *coffeePot2_BaseAddress  = (COFFEEPOT_DEVICE *) NULL;
	coffeePot2_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT2, uniqueCoffeePotName2);
//	My_SimulateOneSecondPassing_ASM();

	unsigned short int waterLevelRequired2 = VOLUME_COFFEEPOT_TWO_ML*PERCENT_NINETY;
	unsigned short int waterTemperatureRequired2 = 80;
	My_DemonstrateCoffeePotAction(coffeePot2_BaseAddress, uniqueCoffeePotName2, waterLevelRequired2, waterTemperatureRequired2);
#endif

#if CONTROL_TWO_POTS_AT_ONE_TIME
	// Example call to control 2 coffeepots at the same time
	//TODO: Question to be answered during Assignment 1
	// How does the overloaded CALL (not the code) get handled when C++ becomes assembly code becomes machine code?
	bool hardwareControl = false;
	My_DemonstrateCoffeePotsAction(hardwareControl,
			coffeePot1_BaseAddress, uniqueCoffeePotName1, waterLevelRequired1, waterTemperatureRequired1,
			coffeePot2_BaseAddress, uniqueCoffeePotName2, waterLevelRequired2, waterTemperatureRequired2);
#endif

	return 0;
}
