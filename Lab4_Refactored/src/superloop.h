/*****************************************************************************
 * superloop.h
 *****************************************************************************/

#ifndef __SUPERLOOP_H__
#define __SUPERLOOP_H__

/* Add your custom header content here */

 void My_InitLED(void);
 void My_InitSwitches(void);
 extern "C" void My_InitSwitchesASM(void);
 void Wait_Time_USeconds(unsigned long int delayMicroSeconds);
 void Flash_LED5(void );
 void Flash_LED6(void );
 unsigned short int My_ReadSwitches(void);
 extern "C" short int My_ReadSwitchesASM(void);
 void My_WriteLED(unsigned char LEDBitPattern);
 unsigned char My_ReadLED(void);
 void Reset_Flash_LED5_StateMachine(void);
 void Reset_Flash_LED6_StateMachine(void);
 void My_WriteLEDs(unsigned char switchBitValue);
 unsigned int My_StopWhenImReady(void);

 bool isSW4Pressed(unsigned char switchBitValue);
 bool isSW124Pressed(unsigned char switchBitValue);
#endif /* __SUPERLOOP_H__ */
