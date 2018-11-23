#ifndef __PIC32_TIMERS_H__
#define __PIC32_TIMERS_H__


void timers_trigger_timeout(uint16_t timeout_seconds);
void timers_coretimer_setup(void);
char timers_timeout_reached(void);
void pic32_set_pwm(unsigned  long int pwm_period, unsigned long int pwm_duty_cycle);


#endif
