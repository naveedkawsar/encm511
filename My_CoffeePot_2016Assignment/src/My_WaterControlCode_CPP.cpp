/*
 * My_WaterControlCode_CPP.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */

#include "MyCoffeePotFunctions_forCPP.h"
#define FIFTY_ML	50


void My_WaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired) {
	/*	WATER_INFLOW�peripheral�device�register�� 8�bits�� RESET�VALUE�0x00
	� Controls�amount�of�water�following�into�coffeepot
	� Value�=�number of�mL�of�water�flowing�into�coffeepot�/�second
	� Real�time�� fills�in�about�2�minutes
	� Fast�time�simulation�� allow�to�fill�in�30�seconds
	� Final�design�� only�operates�if�water�power�turned�on�and�device�is�ready
	User�friendly�feature�note.�Turn�on�one�of�the�coffeepot�LEDs�to�signify�that�the�
	WATER�power�has�been�turned�on.*/

	//Enable water power -- show with LED
	coffeePot_BaseAddress->controlRegister |= WATER_ENABLE_BIT;
	coffeePot_BaseAddress->controlRegister |= (USE_LED3_TO_SHOW_WATER_ENABLED);
	My_SimulateOneSecondPassing_CPP();

	unsigned int waterLevelmL = CurrentWaterLevel_CPP(coffeePot_BaseAddress);

	while (waterLevelmL < waterLevelRequired) {
		coffeePot_BaseAddress->waterInFlowRegister = FIFTY_ML;		//Set water level flow rate
		My_SimulateOneSecondPassing_CPP();
		waterLevelmL = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	}
}

// Given default code
void Smith_WaterContolCode(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired) {
	unsigned int waterLevel = CurrentWaterLevel_CPP(coffeePot_BaseAddress);

	while (waterLevel < waterLevelRequired) {
		coffeePot_BaseAddress->waterInFlowRegister = 200;
		My_SimulateOneSecondPassing_CPP();
		waterLevel = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	}
}
