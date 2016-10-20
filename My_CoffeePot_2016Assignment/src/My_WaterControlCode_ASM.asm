/*
 * My_WaterControlCode_ASM.asm
 *
 *  Created on: Oct 10, 2016
 *      Author: aspireE15
 */

//#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include "MyCoffeePotFunctions_forCPP.h"

#define INPAR1_R01		R0
#define INPAR2_R01 		R1
#define INPAR1_R4		R4
#define INPAR2_R5		R5
#define returnValue_R0	R0

#define baseAddress_P0 	P0
#define waterLevel_R1	R1
#define temp_R2			R2
#define FIFTY_ML		50
 
 	.section program
 	.global _My_WaterControlCode_ASM 				//ASM way of saying the function is not private
 _My_WaterControlCode_ASM:							//extern "C" void My_WaterControlCode_ASM() {
 	[--SP] = R4;									//	COFFEEPOT_DEVICE *coffeePot_BaseAddress;
 	INPAR1_R4 = R0;									//		IN_PARAM1 always passed in R0
 	[--SP] = R5;									//	unsigned short int waterLevelRequired;
 	INPAR2_R5 = R1;									//		IN_PARAM2 always passed in R1 	
 	LINK 20;
 	
 	extern __CurrentWaterLevel_CPP_NM;				//Name mangling occurs
 	CALL __CurrentWaterLevel_CPP_NM;				//unsigned int waterLevel = CurrentWaterLevel();
 	waterLevel_R1 = returnValue_R0;					//Functions always return value in R0;
 	
 WHILE_WCC: 										// while (1)
 	CC waterLevel_R1 < INPAR2_R5;					//	(waterLevel < waterLevelRequired)
 	IF !CC JUMP END_WHILE_CC;						// EXIT WHILE if condition is NOT TRUE
 		baseAddress_P0 = INPAR1_R4;					//	coffeePot_BaseAddress->waterInFlowRegister
 		temp_R2 = FIFTY_ML;							//
 		B[P0 + waterFlowOffset] = temp_R2;
 		.extern __Z23 My_SimulateOneSecondPassing_CPPv;
 		Call __Z23 My_SimulateOneSecondPassing_CPPv();	// 	My_SimulateOneSecondPassing();
 		extern __CurrentWaterLevel_CPP_NM;			//	Update
 		CALL __CurrentWaterLevel_CPP_NM;			//	unsigned int waterLevel = CurrentWaterLevel();
 		waterLevel_R1 = returnValue_R0;				//	Functions always return value in R0;
 	JUMP WHILE_CC;
 	
 END_WHILE_CC:										//} /*END WHILE*/
 _My_WaterControlCode_ASM_END:	
 	UNKLINK;										// LINK and UNLINK always paired
 	R4 = [SP++];									//
 	R5 = [SP++];									// RECOVER AFTER LINK
 	RTS;