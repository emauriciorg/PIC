
#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#define GetSystemClock()	(80000000ul)
#define GetInstructionClock()	(GetSystemClock()/1)	// 
#define GetPeripheralClock()	(GetSystemClock()/1)	// Divisor is dependent on the value of FPBDIV set(configuration bits).

#ifndef SYS_FREQ 
    #define SYS_FREQ                (80000000ul)
#endif

#endif  //HARDWARE_PROFILE_H
