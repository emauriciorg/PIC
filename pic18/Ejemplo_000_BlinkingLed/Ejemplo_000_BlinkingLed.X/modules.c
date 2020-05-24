#include "modules.h"

#define IRC_4MHZ        0x60
#define INTERNAL_OSC    0x02
#define AVAILABLE_LEDS  0xFF  //leds on portD


void ClockSetup(void)
{
	OSCCON  = IRC_4MHZ | INTERNAL_OSC;
	OSCTUNE = 0x00;
}


void delay_ms(volatile unsigned int TMR2Millis)
{
	volatile unsigned int ticks;
	for(ticks=0; ticks < TMR2Millis; ticks++)
	{
		PR2               = 49;
		T2CON             = (0X04<<3)|BIT0;
		TMR2              = 0;
		T2CON            |= BIT2;
		PIE1             |= BIT1;

		while((PIR1&BIT1) ==0);

		PIR1              &= ~BIT1;
		T2CON             &= ~BIT2;
		PIE1              &= ~BIT1;
	}
}


void DigitalIO(void)
{
	LATD   = 0;
	PORTD  = 0;
	TRISD  = 0;
	TRISD &=~(AVAILABLE_LEDS);

}

void pheriperals_init(void)
{
	ClockSetup();
	DigitalIO();
}
