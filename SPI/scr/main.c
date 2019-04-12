
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
	core_timer_trigger(1);
	servo_set_timeout(15);
	while (1){
		/*TODO :fix the issue,SPI is blocking the timeout, check flags!! */
  		cli_execute_debug_command();
		core_timer_polling_routine();

		if(millis_timeout_reached()){
			millis_set_timeout(1000);
			LED_YELLOW_TOGGLE();
		}



		if ( servo_trigger()){
			SERVO_ON();
			if (servo_timeout_reached()){
				SERVO_OFF();
				
			}
		}
	}
}
