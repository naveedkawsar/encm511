/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: ksbengal 
* Date: Wed 2016/12/07 at 05:42:08 PM 
* File Type: TTCOS Main Header File
*************************************************************************************/

#ifndef LAB4_REFACTORED_UTTCOSG2016_H
#define LAB4_REFACTORED_UTTCOSG2016_H

#include <uTTCOSg2016/uTTCOSg.h>

#include "Lab4_Refactored_uTTCOSg2016_main.h"
#include "superloop.h"
#include "Lab0Lib.h"
#include "string.h"

#include <stdio.h>

/* Global variables*/
extern volatile bool isInitialized;
extern volatile unsigned short int LCDCmdIndex;
extern volatile bool commandStringBeingSent;
extern volatile bool commandStringToSend;
extern volatile bool commandStringIsInstruction;
extern char SPI_MessageBuffer[256];
extern unsigned char commandsToSend;
extern unsigned char commandsSent;

/*Thread IDs*/
extern volatile unsigned short int idInit_LCD;
extern volatile unsigned int id_SendSPICommandString;

/* Smith's functions*/
void MSG0(void);
void MSG1(void);
void MSG2(void);
void DisplayLAB3Temp(void);
void LAB3_temp (void);
void SPI_controller(void);
void Init_SPI(void);
void SPI_controller(void);
void SendSPICommandString(void);

/* Our functions*/
void Init_LCD(void);
void toggleEnableLine(unsigned short int value);
bool isSPIReady(void);
void SPI_Send(bool commandStringIsInstruction, unsigned short int commandToSend);
void clearScreen(void);

#endif
