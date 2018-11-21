#ifndef __PIC32_TIMERS_H__
#define __PIC32_TIMERS_H__


void timers_trigger_timeout(unsigned int timeout_seconds);
void timers_coretimer_setup(void);
char timers_timeout_reached(void);



#endif
