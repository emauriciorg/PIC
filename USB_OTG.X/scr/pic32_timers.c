#include <xc.h>
#include <plib.h>
#include "pic32_timers.h"
#include "hw_profile.h"

uint32_t u32_millis_counter;
uint32_t u32_timeout_counter;

void timers_trigger_timeout(unsigned int timeout_seconds) //maximum of 255 seconds
{	
	OpenCoreTimer(CORE_TICK_RATE);
	u32_timeout_counter  = timeout_seconds*1000;
	mCTClearIntFlag();
	UpdateCoreTimer(CORE_TICK_RATE);		
}
void timers_coretimer_setup(void)
{	
	OpenCoreTimer(CORE_TICK_RATE);
	mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));
}

char timers_timeout_reached(void)
{
	if (!mCTGetIntFlag() ){
		return 0;
	}
	mCTClearIntFlag();

	if (u32_millis_counter)u32_millis_counter--;
		
	if (u32_timeout_counter){
		u32_timeout_counter--;
		UpdateCoreTimer(CORE_TICK_RATE);
		return 0;
	}
	CloseCoreTimer();
	
	return 1;
}
