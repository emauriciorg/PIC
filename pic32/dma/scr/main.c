
#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "peripherals.h"
#include "main.h"

#include "spi.h"

int main(){

	pheripherals_init();
	DEBUG_MSG("S314E : Program start! %s\n",__DATE__);

 	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableInterrupts();

	spi_setup();

	while (1){
		/*TODO :fix the issue,SPI is blocking the timeout, check flags!! */
  		cli_execute_debug_command();
		if(timers_timeout_reached()){
			timers_trigger_timeout(1);			
			LED_YELLOW_TOGGLE();
		}
	}
}
