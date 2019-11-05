#include "timer.h"

void Timer2M(void)
{
   PR2=4;
   T2CON=(Pos5>>1)|(Pres4);
   TMR2=0;
   //PIE1|=EnableTimer;
   T2CON|=StartTimer;
   while((PIR1&TimerIFG)==0);
   PIR1&=~TimerIFG;
}
