/*
 * My_HeaterControlCode_CPP.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include "MyCoffeePotFunctions_forCPP.h"

#define TWO_HUNDRED_WATTS	200
#define EIGHTY_DEG_C		80
#define BOOST_FACTOR_TWO	2
#define BOOST_FACTOR_FIVE	5

void My_HeaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired) {
	/*HEATER peripheral device register – 8 bits – RESET 0x00
	– Value = number of J (Joules) of heat flowing into coffeepot / second (W)
	– SAFETY FEATURE (or BUG?) : You can burn out the coffeepot if you forget to turn off the 
	heater.  The computer control automatically turns down the heater to zero over a period of  
	time to avoid this problem. 
	HEATER BOOST device register – 4 bits – RESET 0x0
	– Allows you to boost the amount of heat flowing into water so that you can heat the water 
	faster for a quick coffee fix in the morning
	– NOTE: ‐‐ Heat applied = HEATER VALUE  * HEATER BOOST VALUE*/

	unsigned int currentTempC = CurrentTemperature_CPP(coffeePot_BaseAddress);
	unsigned char boostValue = 0;

	if (currentTempC > EIGHTY_DEG_C)
		boostValue = BOOST_FACTOR_TWO;
	else
		boostValue = BOOST_FACTOR_FIVE;

	if (currentTempC < waterTemperatureRequired) {
		coffeePot_BaseAddress->heaterRegister = TWO_HUNDRED_WATTS;
		coffeePot_BaseAddress->heaterBoostRegister = boostValue;
		My_SimulateOneSecondPassing_CPP();
//		currentTempC = CurrentTemperature_CPP(coffeePot_BaseAddress);
	}

//	coffeePot_BaseAddress->heaterRegister = 0x00;
//	coffeePot_BaseAddress->heaterBoostRegister = 0x0;
}


