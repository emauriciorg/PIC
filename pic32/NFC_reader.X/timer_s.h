
#ifndef _TIMERS_H    /* Guard against multiple inclusion */
#define _TIMERS_H
#include <stdint.h>

#ifndef SYS_FREQ
#define SYS_FREQ			(96000000ul)
#endif 
#ifndef PBCLK_FREQUENCY
#define PBCLK_FREQUENCY		(96 * 1000 * 1000)
#endif

#define CORE_TICK_RATE (SYS_FREQ / 2 / 1000)

uint32_t u32_timeout_counter;

void pr_trigger_timeout(unsigned int timeout_seconds);
void pr_configure_timeout(void);
char  pr_timeout_reached(void);
  uint32_t u32_millis_counter;



#endif