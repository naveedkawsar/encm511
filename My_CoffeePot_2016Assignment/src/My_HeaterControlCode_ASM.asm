/*
 * My_HeaterControlCode_ASM.asm
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */
#include <blackfin.h>

	.section L1_data
	
#define INPAR1_R4 				R4
#define INPAR2_R5				R5
#define TEMP_C_R6				R6	
#define RETURN_R0 				R0
 
#define BASEADDR_P0 			P0
#define BOOST_R2 				R2
#define HEATER_REG_OFFSET		6
#define BOOST_REG_OFFSET		8
#define EIGHTY_DEG_C			80
#define TWO_HUNDRED_WATTS		200
#define BOOST_FACTOR_FIFTEEN	15
#define BOOST_FACTOR_FIVE		5
#define HEATER_WATTS_R3			R3	

	.section program
	.global _My_HeaterControlCode_ASM

_My_HeaterControlCode_ASM:
	[--SP] = R4;									//	COFFEEPOT_DEVICE *coffeePot_BaseAddress;
 	INPAR1_R4 = R0;									//		IN_PARAM1 always passed in R0
 	[--SP] = R5;									//	unsigned short int waterLevelRequired;
 	INPAR2_R5 = R1;									//		IN_PARAM2 always passed in R1
 	[--SP] = R6;
	LINK 20;

	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
	CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;	// unsigned int currentTempC = CurrentTemperature_CPP(coffeePot_BaseAddress);
	
	TEMP_C_R6 = EIGHTY_DEG_C;								
	CC = RETURN_R0 < TEMP_C_R6;								// if (currentTempC > EIGHTY_DEG_C)
	IF CC JUMP HIGH_BOOST;									// JUMP HIGH_BOOST
	BOOST_R2 = BOOST_FACTOR_FIVE;							// else boostValue = BOOST_FACTOR_FIVE;
	JUMP ADD_HEAT;
HIGH_BOOST:
	BOOST_R2 = BOOST_FACTOR_FIFTEEN;						// boostValue = BOOST_FACTOR_FIFTEEN;
ADD_HEAT:
	BASEADDR_P0 = R4;
	HEATER_WATTS_R3 = TWO_HUNDRED_WATTS;	
	CC = RETURN_R0 < INPAR2_R5;								// if (currentTempC < waterTemperatureRequired)
	IF !CC JUMP _My_HeaterControlCode_ASM.END;				// else break
	B[BASEADDR_P0 + HEATER_REG_OFFSET] = HEATER_WATTS_R3; 	// coffeePot_BaseAddress->heaterRegister = TWO_HUNDRED_WATTS;
	B[BASEADDR_P0 + BOOST_REG_OFFSET] = BOOST_R2;			// coffeePot_BaseAddress->heaterBoostRegister = boostValue;
	
	.extern __Z31My_SimulateOneSecondPassing_CPPv;
	CALL __Z31My_SimulateOneSecondPassing_CPPv; 	// My_SimulateOneSecondPassing_CPP();
_My_HeaterControlCode_ASM.END:
	[SP++] = R6;
	[SP++] = R5;
 	[SP++] = R4;
	UNLINK;
	RTS;