
#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "peripherals.h"
#include "main.h"


int main(){

	pheripherals_init();
	DEBUG_MSG("S314E : Program start! %s\n",__DATE__);

 	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableInterrupts();

	while (1){
  		cli_execute_debug_command();
		if(timers_timeout_reached()){
			timers_trigger_timeout(1);			
//			LED_YELLOW_TOGGLE();
		}
	}
}
