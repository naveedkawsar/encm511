/*
 * MyCoffeePotFunctions_CPP.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */

//#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include "MyCoffeePotFunctions_forCPP.h"
#include <blackfin.h>

#define FALSE 											0
#define INDIVIDUAL_ASSIGNMENT_MANUAL_UPDATE          	1
#define INDIVIDUAL_ASSIGNMENT_TIMER_INTERRUPT_UPDATE 	0
#define TEST_FOR_OVERFLOW								0
#define DEVICE_READY_BIT_MASK		DEVICE_READY_BIT_RO


void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
		unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired) {
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress, uniqueCoffeePotName);

	//Set water level flow rate
	//coffeePot_BaseAddress->waterInFlowRegister = 200;
	My_SimulateOneSecondPassing_CPP();

	//Simulate water flowing for 10 seconds
	//NOTE SAFETY FEATURED: Auto max flow rate control, water flow rate slowly return to OFF
/*	for (int time = 0; time < 15; time++) {
		coffeePot_BaseAddress->waterInFlowRegister = waterLevelRequired;
		My_SimulateOneSecondPassing_CPP();
	}*/

#if TEST_FOR_OVERFLOW
#else
//	"Your water control code here"
	My_WaterControlCode_CPP(coffeePot_BaseAddress, waterLevelRequired);
//	My_WaterControlCode_ASM(coffeePot_BaseAddress, waterLevelRequired);
	My_HeaterControlCode_CPP(coffeePot_BaseAddress, waterTemperatureRequired);
#endif
}

void My_DemonstrateCoffeePotsAction(bool hardwareControl,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress1,
		char uniqueCoffeePotName1[], unsigned short int waterLevelRequired1, unsigned short int waterTemperatureRequired1,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress2,
		char uniqueCoffeePotName2[], unsigned short int waterLevelRequired2, unsigned short int waterTemperatureRequired2) {
#warning "INCOMPLETE"

	//Set control register bits INITandSTAYPOWEREDON BIT on device 1
	coffeePot_BaseAddress1->controlRegister |= INITandSTAYPOWEREDON_BIT;

	//Wait till Read-only Control Register bit DEVICE_READY_RO becomes 1 (after 10 simulated seconds)
	if (hardwareControl == FALSE) {

		/*Fill with water about half way - heat to required temperature*/
		/*Set control register bits INITandSTAYPOWEREDON bit on Device 2*/
		coffeePot_BaseAddress2->controlRegister |= INITandSTAYPOWEREDON_BIT;
		//My_SimulateOneSecondPassing_ASM();
		/*Wait till Read-only Control Register bit DEVICE_READY_RO becomes 1 (after 10 simulated seconds)*/
		/*Fill with water about half way - heat to required temperature - do not turn off*/
		/* Note that Device 2 keeps working - in fact it will cool down*/
		/* *SIMULTANEOUSLY fill the two coffeepots to required level and temperature*/
		/* *Automatically control for "considerable time"*/
	}
	else {
		/*In assignment 2 we will connect up the MOCKED coffeepot up to real LEDS and switches*/
		//printf("Coffeepot was initiated %s.\n", uniqueCoffeePotName1); //TODO: printf for CoffeePot2?
	}
}

void My_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[]) {
	//unsigned short int controlRegisterValue = 0;
	//Smith_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress, uniqueCoffeePotName);

	//Set control register bits INITandSTAYPOWEREDON BIT on device 1
	coffeePot_BaseAddress->controlRegister |= INITandSTAYPOWEREDON_BIT;
//	My_SimulateOneSecondPassing_CPP();

	//Enable LED operation -- Using BIT-WISE OR
	coffeePot_BaseAddress->controlRegister |= LED_DISPLAY_ENABLE_BIT;
//	My_SimulateOneSecondPassing_CPP();

	//Use LEDs to show system powered up and LEDs enabled
	coffeePot_BaseAddress->controlRegister |= (USE_LED1_TO_SHOW_SYSTEM_POWEREDUP | USE_LED4_TO_SHOW_LED_DISPLAY_ENABLED);
//	My_SimulateOneSecondPassing_CPP();

	//Wait till Read-only Control Register bit DEVICE_READY_RO becomes 1 (after 10 simulated seconds)*
	/*for (int time = 0; time < 10; time++) {
		My_SimulateOneSecondPassing_CPP();
	}*/
	coffeePot_BaseAddress->controlRegister |= DEVICE_READY_BIT_MASK;

}

void Smith_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[]) {
	// Why is this code unable to cause coffeepot initialization?
	coffeePot_BaseAddress->controlRegister = INITandSTAYPOWEREDON_BIT | LED4_BIT;
}

void My_SimulateOneSecondPassing_CPP(void) {
#if INDIVIDUAL_ASSIGNMENT_MANUAL_UPDATE
	UpdateSimulationDisplay();
#elif INDIVIDUAL_ASSIGNMENT_TIMER_INTERRUPT_UPDATE
	/*Do via interrupt control*/
#else
#error "No assignment type specified"
#endif
}