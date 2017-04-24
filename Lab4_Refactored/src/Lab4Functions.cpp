/*
 * Lab4Functions.CPP
 *
 *  Created on: Dec 7, 2016
 *      Author: ksbengal
 */
#include "Lab4_Refactored_uTTCOSg2016_main.h"

#define EN_HIGH			0x0100
#define RS_HIGH			0x0400
#define CLEAR			0x0001
#define SPIF_COMPLETE	0x0001

#define EVERY_SEC						14*uTTCOSg_GetTickFrequency( )
#define EVERY_TWO_SECS					14*uTTCOSg_GetTickFrequency( )*2
#define EVERY_FIFTH_SECS				14*uTTCOSg_GetTickFrequency( )/5
#define EVERY_FIVE_SECS					14*uTTCOSg_GetTickFrequency( )*5
#define DELAY_EVERY_SEC					14*uTTCOSg_GetTickFrequency( )
#define DELAY_TWO_SECS					14*uTTCOSg_GetTickFrequency( )*2
#define DELAY_THREE_SECS				14*uTTCOSg_GetTickFrequency( )*3
#define DELAY_THREE_HALVES_SECS			14*uTTCOSg_GetTickFrequency( )*3.5
#define DELAY_FOUR_SECS					14*uTTCOSg_GetTickFrequency( )*4
#define DELAY_FOUR_HALVES_SECS			14*uTTCOSg_GetTickFrequency( )*4.5
#define DELAY_FIVE_SECS					14*uTTCOSg_GetTickFrequency( )*5

#define WAITTIME		0x11111

/* index */
volatile unsigned short int LCDCmdIndex = 0;
volatile bool isInitialized				= false;

/* thread ids */
volatile unsigned int id_SendSPICommandString;

volatile bool commandStringBeingSent;
volatile bool commandStringToSend;
volatile bool commandStringIsInstruction;
char SPI_MessageBuffer[256];
unsigned char commandsToSend;
unsigned char commandsSent;

bool newMessage = true;
void MSG0(void) {
	Flash_LED2();
	if (commandStringBeingSent == true) return;
	if (commandStringToSend == true) return;
	commandStringToSend = 1; // uTTCOSg guarentees NO DATA RACE
	commandStringIsInstruction = false;
//	clearScreen();
	strcpy(SPI_MessageBuffer, "ENCM 511 RULS ");
}
void MSG1(void) {
	if (commandStringBeingSent == true) return;
	if (commandStringToSend == true) return;
	commandStringToSend = 1; // uTTCOSg guarentees NO DATA RACE
	commandStringIsInstruction = false;
//	clearScreen();
	strcpy(SPI_MessageBuffer, "Merry Christmas ");
}

static float ChinookTemp[10] = { 24.0, 26.0, 28.0, 29.0, 33.0, -35.0, -34.0, -20.0};
float currentTemp = 0;
float GetTemperature_TMP03(void) {
	static int mockTempIndex = -1;
	mockTempIndex++;
	if (mockTempIndex >= 10) mockTempIndex = 0;
	return ChinookTemp[mockTempIndex];
}

void LAB3_temp (void) {
		Flash_LED4();
		if (commandStringBeingSent == true) return;
		if (commandStringToSend == true) return;
		commandStringToSend = 1; // uTTCOSg guarentees NO DATA RACE
		commandStringIsInstruction = false;
		float currentTemp = GetTemperature_TMP03( );
		sprintf(SPI_MessageBuffer, "Temp : %5.2f", currentTemp);
}

void SPI_controller(void) {
	Flash_LED5( );
	if (commandStringToSend == false) return; 	// No message
	if (commandStringBeingSent == true) return; // SPI bus in use
	clearScreen();
	commandStringBeingSent = true;
	commandsToSend = strlen(SPI_MessageBuffer);
	commandsSent = 0;
	id_SendSPICommandString = uTTCOSg_AddThread(SendSPICommandString, NO_DELAY, EVERY_FIFTH_SECS);
}
void SendSPICommandString(void) {
	if (commandsToSend == 0) return;
	if (isSPIReady( ) == false) return;
	SPI_Send(commandStringIsInstruction, (unsigned short int) SPI_MessageBuffer[commandsSent++]);
	commandsToSend--;
	if (commandsToSend == 0) {
		commandsSent = 0;
		SPI_MessageBuffer[commandsSent++];
		commandStringBeingSent = false;
		commandStringToSend = false;
		if(id_SendSPICommandString != 0)
			uTTCOSg_DeleteThread(id_SendSPICommandString);
	}
}

void SPI_Send(bool commandStringIsInstruction, unsigned short int commandToSend) {
	if (newMessage) {
		newMessage = false;
	}
	if(isSPIReady())
		toggleEnableLine(commandToSend);

}
void Init_SPI(void) {
	*pSPI_BAUD	= 0x8000;
	*pSPI_FLG	= 0x20;
	*pSPI_CTL	= 0x5101;
}

static char initLCDcmd[5] = {0x30, 0x30, 0x3C, 0x0F, 0x01};

void Init_LCD(void) {
	toggleEnableLine((unsigned short int) initLCDcmd[LCDCmdIndex++]);
	if (LCDCmdIndex == strlen(initLCDcmd)) {
		isInitialized = true;
		if (idInit_LCD != 0)
			uTTCOSg_DeleteThread(idInit_LCD);
	}
}

void toggleEnableLine(unsigned short int value) {
	if(!isInitialized) {
		*pSPI_TDBR	= value | EN_HIGH;
		Wait_Time_USeconds(WAITTIME);

		*pSPI_TDBR	= value & ~EN_HIGH;
		Wait_Time_USeconds(WAITTIME);

		*pSPI_TDBR	= value | EN_HIGH;
		Wait_Time_USeconds(WAITTIME);
	}
	else {
		*pSPI_TDBR	= RS_HIGH | (value | EN_HIGH);
		Wait_Time_USeconds(WAITTIME);

		*pSPI_TDBR	= RS_HIGH | (value & ~EN_HIGH);
		Wait_Time_USeconds(WAITTIME);

		*pSPI_TDBR	= RS_HIGH | (value | EN_HIGH);
		Wait_Time_USeconds(WAITTIME);
	}
}

void clearScreen(void) {
	*pSPI_TDBR	= (~RS_HIGH) & (0x0001 | EN_HIGH);
	Wait_Time_USeconds(WAITTIME);

	*pSPI_TDBR	= (~RS_HIGH) & (0x0001 & ~EN_HIGH);
	Wait_Time_USeconds(WAITTIME);

	*pSPI_TDBR	= (~RS_HIGH) & (0x0001 | EN_HIGH);
	Wait_Time_USeconds(WAITTIME);
/*
	*pSPI_TDBR	= 0x0001 | EN_HIGH;
	Wait_Time_USeconds(WAITTIME);

	*pSPI_TDBR	= 0x0001 & ~EN_HIGH;
	Wait_Time_USeconds(WAITTIME);

	*pSPI_TDBR	= 0x0001 | EN_HIGH;
	Wait_Time_USeconds(WAITTIME);
*/
}

bool isSPIReady(void) {
	unsigned short int SPIF_done = *pSPI_STAT & SPIF_COMPLETE;
	if (SPIF_done == SPIF_COMPLETE)
		return true;
	else return false;
}
