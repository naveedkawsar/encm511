/*
 * My_WaterControlCode_CPP.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */

#include "MyCoffeePotFunctions_forCPP.h"
#define FIFTY_ML			50
#define FOURTY_ML			44 //22 if one coffeepot at a time
#define EIGHTY_DEG_C		80
#define PERCENT_NINETY		0.9

void My_WaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired) {
	/*	WATER_INFLOW peripheral device register – 8 bits – RESET VALUE 0x00
	– Controls amount of water following into coffeepot
	– Value = number of mL of water flowing into coffeepot / second*/
	unsigned int waterLevelmL = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	if (waterLevelmL < waterLevelRequired*PERCENT_NINETY) {
		coffeePot_BaseAddress->waterInFlowRegister = FIFTY_ML;		//Set water level flow rate
		AddWater_ASM(coffeePot_BaseAddress);
		waterLevelmL = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	}
	unsigned int currentTempC = CurrentTemperature_CPP(coffeePot_BaseAddress);
		if (currentTempC > EIGHTY_DEG_C) {
			coffeePot_BaseAddress->waterInFlowRegister = FOURTY_ML;
		}
		My_SimulateOneSecondPassing_CPP();

}

void My_WaterControlCode_CallASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired) {
	/*	WATER_INFLOW peripheral device register – 8 bits – RESET VALUE 0x00
	– Controls amount of water following into coffeepot
	– Value = number of mL of water flowing into coffeepot / second*/

	unsigned int waterLevelmL = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	if (waterLevelmL < waterLevelRequired*PERCENT_NINETY) {
		AddWater_ASM(coffeePot_BaseAddress);
		waterLevelmL = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	}
	ReplaceEvaporatingWater_ASM(coffeePot_BaseAddress);
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
