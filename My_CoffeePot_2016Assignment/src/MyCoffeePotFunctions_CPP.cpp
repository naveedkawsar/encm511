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
#define DEVICE_READY_BIT_MASK			DEVICE_READY_BIT_RO
#define PERCENT_FIFTY									0.5


void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
		unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired) {
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress, uniqueCoffeePotName);
	//NOTE SAFETY FEATURED: Auto max flow rate control, water flow rate slowly return to OFF

#if TEST_FOR_OVERFLOW
	while(1) {
		/* Simulate water flowing forever */
		coffeePot_BaseAddress->waterInFlowRegister = waterLevelRequired;
		My_SimulateOneSecondPassing_CPP();
	}
#else
	while(1) {
		/* Water and heater control code here */
	//	My_WaterControlCode_CPP(coffeePot_BaseAddress, waterLevelRequired);
		My_WaterControlCode_CallASM(coffeePot_BaseAddress, waterLevelRequired);
	//	My_HeaterControlCode_CPP(coffeePot_BaseAddress, waterLevelRequired);
		My_HeaterControlCode_ASM(coffeePot_BaseAddress, waterTemperatureRequired);
	}
#endif
}

void My_DemonstrateCoffeePotsAction(bool hardwareControl,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress1,
		char uniqueCoffeePotName1[], unsigned short int waterLevelRequired1, unsigned short int waterTemperatureRequired1,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress2,
		char uniqueCoffeePotName2[], unsigned short int waterLevelRequired2, unsigned short int waterTemperatureRequired2) {

	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress1, uniqueCoffeePotName1);
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress2, uniqueCoffeePotName2);

	if (hardwareControl == FALSE) {
		/* Fill with water about half way - heat to required temperature
		 * No context release required for this assignment.
		 */
		/*unsigned int waterLevelmL1 = CurrentWaterLevel_CPP(coffeePot_BaseAddress1);
		while (CurrentWaterLevel_CPP(coffeePot_BaseAddress1) <= waterLevelRequired1*PERCENT_FIFTY) {
			My_WaterControlCode_CPP(coffeePot_BaseAddress1, (waterLevelRequired1)/2);
		}
		unsigned int currentTempC1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);
		while (CurrentTemperature_CPP(coffeePot_BaseAddress1) < waterTemperatureRequired1*PERCENT_FIFTY) {
			My_HeaterControlCode_CPP(coffeePot_BaseAddress1, (waterTemperatureRequired1)/2);
			//ReplaceEvaporatingWater_ASM(coffeePot_BaseAddress1);
			unsigned int currentTempC = CurrentTemperature_CPP(coffeePot_BaseAddress1);
				if (currentTempC > 80) {
					coffeePot_BaseAddress1->waterInFlowRegister = 20;
				}
		}
		/*Wait till Read-only Control Register bit DEVICE_READY_RO becomes 1 (after 10 simulated seconds)*/

		/*Fill with water about half way - heat to required temperature - do not turn off*/
		/*unsigned int waterLevelmL2 = CurrentWaterLevel_CPP(coffeePot_BaseAddress2);
		while (CurrentWaterLevel_CPP(coffeePot_BaseAddress2) < waterLevelRequired2*PERCENT_FIFTY) {
			//My_WaterControlCode_CallASM(coffeePot_BaseAddress2, (waterLevelRequired2)/2);
			My_WaterControlCode_CPP(coffeePot_BaseAddress1, (waterLevelRequired1)/2);
		}
		unsigned int currentTempC2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);
		while (currentTempC2 < waterTemperatureRequired2) {
			My_HeaterControlCode_ASM(coffeePot_BaseAddress2, waterTemperatureRequired2);
			ReplaceEvaporatingWater_ASM(coffeePot_BaseAddress2);
		}

		/* Note that Device 2 keeps working - in fact it will cool down*/
		/* *SIMULTANEOUSLY fill the two coffeepots to required level and temperature*/
		/* *Automatically control for "considerable time"*/

		while(1) {
			My_WaterControlCode_CPP(coffeePot_BaseAddress1, waterLevelRequired1);
			My_HeaterControlCode_CPP(coffeePot_BaseAddress1, waterTemperatureRequired1);
			My_WaterControlCode_CallASM(coffeePot_BaseAddress2, waterLevelRequired2);
			My_HeaterControlCode_ASM(coffeePot_BaseAddress2, waterTemperatureRequired2);
		}
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

	//Wait till (poll) Read-only Control Register bit DEVICE_READY_RO becomes 1 (after 10 simulated seconds)*
	bool isCoffeePotReady = FALSE;
	while (!isCoffeePotReady) {
		isCoffeePotReady = coffeePot_BaseAddress->controlRegister |= DEVICE_READY_BIT_MASK;
		My_SimulateOneSecondPassing_CPP();
	}
	//Enable LED operation -- Using BIT-WISE OR
	coffeePot_BaseAddress->controlRegister |= LED_DISPLAY_ENABLE_BIT;

	//Use LEDs to show system powered up and LEDs enabled
	coffeePot_BaseAddress->controlRegister |= (USE_LED1_TO_SHOW_SYSTEM_POWEREDUP | USE_LED4_TO_SHOW_LED_DISPLAY_ENABLED);
	My_SimulateOneSecondPassing_CPP();

	//Enable water power -- show with LED
	coffeePot_BaseAddress->controlRegister |= WATER_ENABLE_BIT;
	coffeePot_BaseAddress->controlRegister |= USE_LED3_TO_SHOW_WATER_ENABLED;
	My_SimulateOneSecondPassing_CPP();

	//Enable heater power -- show with LED
	coffeePot_BaseAddress->controlRegister |= HEATER_ENABLE_BIT;
	coffeePot_BaseAddress->controlRegister |= USE_LED2_TO_SHOW_HEATER_ENABLED;
	My_SimulateOneSecondPassing_CPP();
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
