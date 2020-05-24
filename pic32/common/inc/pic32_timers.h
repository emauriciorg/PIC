#ifndef __PIC32_TIMERS_H__
#define __PIC32_TIMERS_H__

#include <stdint.h>

void core_timer_trigger(uint16_t timeout_seconds);
void timers_coretimer_setup(void);
char core_timer_polling_routine(void);
void pic32_set_pwm(unsigned  long int pwm_period, unsigned long int pwm_duty_cycle);


char servo_timeout_reached();
void servo_set_timeout(uint32_t micros_period);
char servo_trigger(void);


char millis_timeout_reached(void);
void millis_set_timeout(uint32_t millis_period);

char millis_trigger(void);

#endif
