
#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#define GetSystemClock()	(96000000ul)
#define GetInstructionClock()	(GetSystemClock()/1)	// 
#define GetPeripheralClock()	(GetSystemClock()/1)	// Divisor is dependent on the value of FPBDIV set(configuration bits).

#define SYS_FREQ            (96000000UL)
#define PBCLK_FREQUENCY        (96 * 1000 * 1000)

#define cnsPbDivide		1
#define cnsPrescaler		256

#define TOGGLES_PER_SECOND 10000
#define CORE_TICK_RATE	(SYS_FREQ/2/TOGGLES_PER_SECOND)		


#define Timer1Tick		(SYS_FREQ/cnsPbDivide/cnsPrescaler/cnsTogglesPerSec)// timer 1, 1ms period

#endif  //HARDWARE_PROFILE_H
