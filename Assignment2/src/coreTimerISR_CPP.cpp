/*
 * coreTimerISR_CPP.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: nkawsar
 */

#include "Lab0Lib.h"
#include "Assignment2.h"



#pragma interrupt
void CoreTimer_ISR_CPP(void) {
	// Clear timer interrupt if needed
	Flash_LED3( );
	Flash_LED5( );
//	UpdateSimulationDisplay();
}

void InitCoreTimer(void) {
	*pTIMER_ENABLE |= TIMEN0;
}

void Set(unsigned long int Reg){

}
