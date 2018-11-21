
#include <xc.h>
#include <plib.h>
#include <proc/p32mx440f256h.h>
#include "peripherals.h"
#include "main.h"


int main(){
	pheripherals_init();
	initialize_UART_x(1,115200);
}
