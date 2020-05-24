#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "hw_profile.h"
#include "peripherals.h"
#include "pic32_uart.h"
#include "pic32_usb.h"

void pheripherals_init(void){
	SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
}

void pheripherals_leds_init(void ){
	mPORTBSetPinsDigitalOut(BIT_0);
}
