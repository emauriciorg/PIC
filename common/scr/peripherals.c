#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "hw_profile.h"
#include "peripherals.h"
#include "pic32_uart.h"
#include "pic32_usb.h"
#include "pic32_timers.h"
#include "pic32_adc.h"

void pheripherals_leds_init(void ){
	mPORTDSetPinsDigitalOut(BIT_1);
}

void pheripherals_init(void){
	SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
	//SYSTEMConfigPerformance(SYS_FREQ);
	timers_coretimer_setup();  
 	pic32_uart_initialize(UART2,115200);
	pheripherals_leds_init();
	pic32_adc_initialize(ENABLE_AN1_ANA);
	pic32_set_pwm(10000, 50);
}




