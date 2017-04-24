/*
 * Lab1LibraryASM.asm
 *
 *  Created on: Oct 25, 2016
 *      Author: nkawsar
 */

#include <blackfin.h>

	.section program
	.global _My_ReadSwitchesASM
	
_My_ReadSwitchesASM:
	LINK 16;
	.extern _Read_Input_GPIOInterface;
	CALL _Read_Input_GPIOInterface;
#define SHIFT_MASK 8
	R1 = SHIFT_MASK;
	R0 >>= R1;
_My_ReadSwitchesASM.END:
	UNLINK;
	RTS;
	
	.section program
	.global _My_InitSwitchesASM;
	
_My_InitSwitchesASM:
	LINK 16;
	.extern _Init_Input_GPIOInterface;
	CALL _Init_Input_GPIOInterface;
_My_InitSwitchesASM.END:
	UNLINK;
	RTS;