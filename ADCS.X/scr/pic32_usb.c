#include "pic32_usb.h"
#include <xc.h>

#define USB_DATA_PLUS_PIN  1
#define USB_DATA_MINUS_PIN  1


void pic32_usb_init(void){
	U1CONbits.JSTATE = 0; //Live Differential Receiver JSTATE flag bit
	U1CONbits.SE0 = 0;
	U1CONbits.PKTDIS = 0;
//	U1CONbits.USBRST =1; 
	U1CONbits.HOSTEN = 0;
	U1CONbits.RESUME = 0;
	U1CONbits.USBEN = 1;

	U1ADDRbits.LSPDEN = 1; //<7>
//	U1CONbits.DEVADDR = 0X7F;  <6:0> 7 bits addr
//	VID MICROCHIP 4D8
//	SEE DEVICE MANAGER
//PID PRODUCT ID
}
