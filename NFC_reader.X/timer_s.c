#include "timer_s.h"
#include <xc.h>
#include "plib.h"
void pr_trigger_timeout(unsigned int timeout_seconds) //maximum of 255 seconds
{
    
    OpenCoreTimer(CORE_TICK_RATE);// enable CoreTimer
    u32_timeout_counter  = timeout_seconds*1000;
    mCTClearIntFlag();
    UpdateCoreTimer(CORE_TICK_RATE);
   
      
}
void pr_configure_timeout(void)
{

     OpenCoreTimer(CORE_TICK_RATE);// enable CoreTimer
     mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));

}

char  pr_timeout_reached(void)
{
    char timeout_out= 0;
  if(mCTGetIntFlag() )
  {
      mCTClearIntFlag();
      
      if(u32_millis_counter)u32_millis_counter--;
        
      if( u32_timeout_counter)
      {
          u32_timeout_counter--;
          UpdateCoreTimer(CORE_TICK_RATE);
     
      }
      else
      {
           CloseCoreTimer();
          timeout_out=1;
      }
  }
  
  return timeout_out;
}
