/*
 * coreTimerISR_ASM.asm
 *
 *  Created on: Nov 23, 2016
 *      Author: nkawsar
 */

#include "blackfin.h"

#define TCNTL				0xFFE03000
#define TCOUNT				0xFFE0300C
#define TPERIOD				0xFFE03004
#define TSCALE				0xFFE03008
#define TIMER_ENABLE		0xFFC00640
#define TIMER_DISABLE		0xFFC00644
#define TIMER_STATUS		0xFFC00648
#define IMASK				0xFFE02104
#define ILAT				0xFFE0210C		
#define SIC_IMASK			0XFFC0010C

_My_AdjustSwitchPolarityASM:
	LINK 16;
	P1.L = lo(FIO_POLAR);
	P1.H = hi(FIO_POLAR);
	R1 = MASK_PF8TO11 ( Z );
	R0 = W[P1](Z);
	R0 = R0 & R1;
__My_AdjustSwitchPolarityASM.END:
	UNLINK;
	RTS;
