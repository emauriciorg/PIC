
#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "peripherals.h"
#include "main.h"
#define LED_YELLOW_TOGGLE() mPORTDToggleBits(BIT_1)
#define LED_YELLOW_ON() mPORTDSetBits(BIT_1)
#define LED_YELLOW_OFF() mPORTDClearBits(BIT_1)


unsigned char  U1TxBuf[30];
unsigned char	U1RxBuf[30];


int main(){

	pheripherals_init();
	DEBUG_MSG("Program start! %s\n",__DATE__);

 	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTDisableInterrupts();

	while (1){

		if(timers_timeout_reached()){
			timers_trigger_timeout(1);			
			LED_YELLOW_TOGGLE();
			DEBUG_MSG ("ADC1 is %d\n",  pic32_adc_read_channel(0));

		}

	}
}
