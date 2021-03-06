/*
 * MyCoffeePotFunctions_forCPP.h
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */

#ifndef MYCOFFEEPOTFUNCTIONS_FORCPP_H_
#define MYCOFFEEPOTFUNCTIONS_FORCPP_H_

#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>

//void My_SimulateOneSecondPassing(void);
void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress,
		char uniqueCoffeePotName[],
		unsigned short int waterLevelRequired,
		unsigned short int waterTemperatureRequired);

void My_DemonstrateCoffeePotsAction(bool hardwareControl,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress1,
		char uniqueCoffeePotName1[],
		unsigned short int waterLevelRequired1,
		unsigned short int waterTemperatureRequired1,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress2,
		char uniqueCoffeePotName2[],
		unsigned short int waterLevelRequired2,
		unsigned short int waterTemperatureRequired2);

void My_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[]);
void Smith_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[]);

extern "C" void My_WaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
extern "C" void My_HeaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress , unsigned short int watertemperatureRequired);

void Smith_WaterContolCode(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
void My_WaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
extern "C" void My_WaterControlCode_CallASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
extern "C" void AddWater_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress);
extern "C" void ReplaceEvaporatingWater_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress);

void My_SimulateOneSecondPassing_CPP(void);
//extern "C" void My_SimulateOneSecondPassing_ASM(void);

void My_HeaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired);
extern "C" void My_HeaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired);

#endif /* MYCOFFEEPOTFUNCTIONS_FORCPP_H_ */
