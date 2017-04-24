/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: ksbengal 
* Date: Mon 2016/12/05 at 06:08:09 PM 
* File Type: TTCOS Main Header File
*************************************************************************************/

#ifndef LAB2_REFACTORED_UTTCOSG2016_H
#define LAB2_REFACTORED_UTTCOSG2016_H

//#include <uTTCOSg2016/uTTCOSg.h>
#include <uTTCOSg2016/uTTCOSg.h>
#include <stdio.h>

#include "Lab2_Refactored_uTTCOSg2016_main.h"
#include "Lab0Lib.h"
#include "superloop.h"

extern volatile unsigned int idLab2Part1;

extern volatile unsigned int idGoldilocks;
extern volatile unsigned int idNarrator;
extern volatile unsigned int idChristine;
extern volatile unsigned int idWoodElf;

extern volatile unsigned int idDisplayLED;
extern volatile unsigned int idLED1;
extern volatile unsigned int idLED2;
extern volatile unsigned int idLED3;

extern volatile unsigned int idReadSwitches;
extern volatile unsigned char currentSwitchValues;
extern volatile char LEDvalues1to4ToDisplay;

extern volatile unsigned int idLab2Part2;

extern volatile unsigned char StoredSwitchCommandsArray[60];
extern volatile unsigned int idStoreSwitchCommands;
extern volatile unsigned int Arraycounter;

extern volatile unsigned int idLab2Part3;

void Lab2Part1_Launch (void);

void Kill_and_Launch_Narrator(void);
void Launch_Narrator_with_Delay(void);

void Launch_Christine_with_Delay(void);
void Kill_and_Launch_Christine(void);

void ReadSwitches(void);
void Kill_ReadSwitches(void);

void DisplayLED(void);
void Kill_DisplayLED(void);

void HandleSwitchCommands(void);
void Kill_HandleSwitchCommands(void);

void WoodElf_TwinkleLights (void);
void Kill_WoodElf_TwinkleLights(void);

void Kill_Goldilocks(void);

void Check_KeyPress(void);
void Kill_Check_KeyPress(void);

void Stop_Lab2Part1_Launch_Lab2Part2(void);

/*--------------------------------------------------END OF LAB2 PART 1-------------------------------------------*/
void Lab2Part2_Launch(void);
void StoreSwitchCommands(void);
void ResetSwitchCommandsArray(void);
void Kill_StoreSwitchCommands(void);
void Kill_Christine_Forever(void);

void Stop_Lab2Part2_Launch_Lab2Part3(void);

/*--------------------------------------------------END OF LAB2 PART 2-------------------------------------------*/
void Lab2Part3_Launch (void);
void Kill_Narrator(void);

void ReadSwitchCommandsArray(void);
void Kill_ReadSwitchCommandsArray(void);

void Troll_Function(void);
void Kill_Troll_Function(void);

void Stop_Lab2Part3_Launch_Lab2Part1(void);

#endif
