
#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#define GetSystemClock()	(80000000ul)
#define GetInstructionClock()	(GetSystemClock()/1)	// 
#define GetPeripheralClock()	(GetSystemClock()/1)	// Divisor is dependent on the value of FPBDIV set(configuration bits).

#define SYS_FREQ            (80000000UL)
#define PBCLK_FREQUENCY        (80 * 1000 * 1000)
#endif  //HARDWARE_PROFILE_H
