#include <GPIO2016/ADSP_GPIO_Interface.h>     // Check the header file name from Lab. 0
#include "superloop.h"
#include <stdio.h>							//TODO: TAKE OUT AFTER

#define USE_SMITH_GPIO 1    // Those that understand ENUM can use that C++ syntax
#define USE_MY_GPIO 2				// Treat these as "unsigned ints" when prototyping

#define LED5_OFF_MASK	~(0x10)
#define LED5_ON_MASK	0x10
#define LED6_OFF_MASK	~(0x20)//0xDF	//Bit pattern 1101_1111
#define LED6_ON_MASK	0x20	//Bit pattern 0010_0000

#define WAIT_TIME 0x926252

void  My_InitLED(unsigned int whichGPIO) {
     if ( whichGPIO == USE_SMITH_GPIO) {
        Init_LED_GPIOInterface( );
     }
     else {
       printf("My_InitLED with USE_MY_GPIO -- not ready\n");
     }
} 	 // PSP -- REMEMBER CODE REVIEW TIME = 25% OF CODING TIME


void My_InitSwitches(unsigned int whichOS ){
	My_InitSwitchesASM();
}
void Wait_Time_USeconds(unsigned long int waitThisTime) {
//	waitThisTime = 5000;		//adjust this so that wait_Time_USeconds(1 million) is around 1 second

	for (unsigned long int count = 0; count < waitThisTime; count++) {
			//count = count+2;
   }

}

unsigned short int My_ReadSwitches(unsigned int whichGPIO) {
	// Switch register is 16 bits and not 8 bits like LEDs
	     if ( whichGPIO == USE_SMITH_GPIO) {
	    	 //unsigned short int test = Read_Input_GPIOInterface() >> 8;
	    	 //printf("%u",test);
	    	 return Read_Input_GPIOInterface() >> 8;
	     }
	     else {
	#if 1
	       printf("MyReadSwitches with USE_MY_GPIO -- not ready\n");
				  unsigned short int garbage = 0xA0A0;  //Return garbage value -- but make it a "known" garbage value
	       return (garbage);
	#else
	       return (My_ReadSwitchesASM( ));
	#endif
	     }
}

void My_WriteLEDs(unsigned int USE_GPIO, unsigned char switchBitValue){
	if (USE_GPIO == USE_SMITH_GPIO)
		Write_Output_GPIOInterface((switchBitValue | Read_LED_GPIOInterface()));
}

enum bitwise_LED5_State {OFF, ON};
static bitwise_LED5_State currentLED5State = OFF;
void Flash_LED5(void) {
	bitwise_LED5_State nextStateToDo = currentLED5State;

	switch (currentLED5State) {
		case OFF:
			Write_LED_GPIOInterface(LED5_ON_MASK | Read_LED_GPIOInterface());
			nextStateToDo = ON;
			break;
		case ON:
			Write_LED_GPIOInterface(LED5_OFF_MASK & Read_LED_GPIOInterface());
			nextStateToDo = OFF;
			break;
	}
	currentLED5State = nextStateToDo;
}

enum bitwise_LED6_State {IS_OFF, IS_ON};
static bitwise_LED6_State currentState = IS_OFF;
void Flash_LED6(void) {
	bitwise_LED6_State nextStateToDo = currentState;

	switch (currentState) {
		case IS_OFF:
			Write_LED_GPIOInterface(LED6_ON_MASK | Read_LED_GPIOInterface());
			nextStateToDo = IS_ON;
			break;
		case IS_ON:
			Write_LED_GPIOInterface(LED6_OFF_MASK & Read_LED_GPIOInterface());
			nextStateToDo = IS_OFF;
			break;
	}
	currentState = nextStateToDo;
}

void My_WriteLED(unsigned int whichOS, unsigned char LEDvalue) {
      if (whichOS == USE_SMITH_GPIO) {
           Write_LED_GPIOInterface((Read_LED_GPIOInterface() & 0xF0) | LEDvalue );   // Call my existing code
      }
}

void Reset_Flash_LED5_StateMachine(void) {
	currentLED5State = OFF;
}

void Reset_Flash_LED6_StateMachine(void) {
	currentState = IS_OFF;
}

//#define SW3_MASK 0xfffb
//#define SW3_PRESSED 0x0004

#define SW3_PRESSED 	0x4		// Bit pattern 0100
#define LEDsON_MASK 	0x27		// Bit pattern 0010 0011 - should be 0x23?

unsigned int My_StopWhenImReady(void){
	unsigned int ready = 1;
	unsigned int LEDsON = 0;
	unsigned int isSW3_Pressed = 0;

	LEDsON = Read_LED_GPIOInterface();
	isSW3_Pressed = Read_Input_GPIOInterface() >> 8;
	isSW3_Pressed = isSW3_Pressed & SW3_PRESSED;

	if((LEDsON == LEDsON_MASK) && (isSW3_Pressed == SW3_PRESSED)){
		ready = 0;
	}
	else {
		ready = 1;
	}
	return ready;
}

unsigned int counter = 0;
#define SW4_Pressed 	0x08
bool return_value = 0;
enum SW4_state {Waiting_for_press, Pressed, Released};
static SW4_state Current_State = Waiting_for_press;

/*
bool isSW4Pressed(unsigned char switchBitValue){
	SW4_state Next_State = Current_State;

	switch(Current_State){
	case Waiting_for_press:
		if((switchBitValue & SW4_Pressed) == SW4_Pressed){
			Next_State = Pressed;
			return_value = false;
		}
		break;
	case Pressed:
		if((switchBitValue & SW4_Pressed) == 0){
			Next_State = Released;
			return_value = false;
		}
		break;
	case Released:
		Next_State = Waiting_for_press;
		return_value = true;
		break;
	}

	Current_State = Next_State;
	return return_value;
}
*/
/*bool isSW4Pressed(unsigned char switchBitValue){
	if((switchBitValue & SW4_Pressed) == SW4_Pressed)
		return true;
	else
		return false;
}
/*
	}

	if((switchBitValue & SW4_Pressed) == SW4_Pressed)
		return true;
	else
		return false;
}*/

#define SW124_Pressed 	0x0b
bool isSW124Pressed(unsigned char switchBitValue){
	if((switchBitValue & SW124_Pressed) == SW124_Pressed)
		return true;
	else
		return false;
}
