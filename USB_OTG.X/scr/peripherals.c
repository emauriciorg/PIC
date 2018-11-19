#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "../inc/hw_profile.h"
#include "../inc/peripherals.h"
#include "../inc/pic32_uart.h"


void pheripherals_init(void){
	SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
}
