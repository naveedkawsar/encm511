/*****************************************************************************
 * Assignment2.cpp
 *****************************************************************************/

#include <sys/platform.h>
#include "adi_initialize.h"
#include "Assignment2.h"

#define WAIT_TIME 0x926252

volatile int timerSignal  = 0;
volatile int SWIsignal = 0;

void main(void) {
	My_InitSwitchesASM();
	My_ReadSwitchesASM( );
	Init_LED_GPIOInterface( );

	while (1) {
		Wait_Time_USeconds(WAIT_TIME);
		if (isSW4Pressed())
			Flash_LED1( );
		InitCoreTimer( );
		Set(IMASK);       // Set(SIC_MASK) – Not needed for core timer
		/*Set(EVT, CoreTimer_ISR_CPP);   Start_CoreTimer( );
		while (1) {
			Waste1Sec( );
			if (SW4 is on)  { Flash_LED1( ) }; */
			//  COMMENTED OUT  if (SW3 is on) {  asm(“raise 6; “); }
			// Cause CoreTimersoftware interrupt( )

	}
}
#define SW4_Pressed 	0x08
bool isSW4Pressed(void){
	unsigned char switchBitValue = My_ReadSwitchesASM( );
	if((switchBitValue & SW4_Pressed) == SW4_Pressed)
		return true;
	else
		return false;
}
