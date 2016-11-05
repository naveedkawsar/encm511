/*
 * My_WaterControlCode_ASM.asm
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */

//#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include <blackfin.h>

	.section L1_data;


#define INPAR1_R4				R4
#define RETURN_R0				R0

#define BASEADDR_P0 			P0
#define TEMP_C_R2				R2
#define WATER_ML_R3				R3
#define WATER_FLOW_REG_OFFSET	7
#define EIGHTY_DEG_C			80
#define FIFTY_ML				50
#define FOURTY_ML				44	//22 if one coffeepot at a time

 	.section program
 	.global _AddWater_ASM
 _AddWater_ASM:								
 	[--SP] = R4;									//	COFFEEPOT_DEVICE *coffeePot_BaseAddress;
 	LINK 20;
 	BASEADDR_P0 = R0;								//		IN_PARAM1 always passed in R0, Leaf function
 	WATER_ML_R3 = FIFTY_ML;
 	B[BASEADDR_P0 + WATER_FLOW_REG_OFFSET] = WATER_ML_R3; // coffeePot_BaseAddress->waterInFlowRegister = FIFTY_ML;	
 _AddWater_ASM.END:
 	[SP++] = R4;
 	UNLINK;
 	RTS;
 
 	.section program
 	.global _ReplaceEvaporatingWater_ASM
_ReplaceEvaporatingWater_ASM:
 	[--SP] = R4;									//	COFFEEPOT_DEVICE *coffeePot_BaseAddress;
 	INPAR1_R4 = R0;									//		IN_PARAM1 always passed in R0
 	LINK 20;

	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
	CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE; 	// unsigned int currentTempC = CurrentTemperature_CPP(coffeePot_BaseAddress);
	BASEADDR_P0 = R4;								//		IN_PARAM1 always passed in R0
	TEMP_C_R2 = EIGHTY_DEG_C;
	WATER_ML_R3 = FOURTY_ML;
	CC = RETURN_R0 < TEMP_C_R2;						//if (currentTempC > EIGHTY_DEG_C)
	IF CC JUMP _ReplaceEvaporatingWater_ASM.END;	// else break
	B[BASEADDR_P0 + WATER_FLOW_REG_OFFSET] = WATER_ML_R3;	// coffeePot_BaseAddress->waterInFlowRegister = FOURTY_ML;
	
	.extern __Z31My_SimulateOneSecondPassing_CPPv;	
	CALL __Z31My_SimulateOneSecondPassing_CPPv;		// My_SimulateOneSecondPassing_CPP();
_ReplaceEvaporatingWater_ASM.END:
 	[SP++] = R4;
 	UNLINK;
 	RTS;
 		