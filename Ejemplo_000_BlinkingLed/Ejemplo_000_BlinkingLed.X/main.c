/*
 * File:   main.c
 * Author: mauro r.
 *
 * Created on Jan-4-2017
 *
This  example shows how to enable ouputs


|->RD0..
| .
| .
| .
|->..RD7

*/

#include <xc.h>
#include "PicConf.h"
#include "Modules.h"
#include "Ejemplo.h"
void main(void)
{
	pheriperals_init();
	/*lcd relates routines are optinal*/
	lcd_start_message();
	LATD=0X0F;

	while(1)
	{
		LATD^=0XFF;
		delay_ms(500);//delay_ms	usando el tmr2
		LATD^=0XFF;
		delay_ms(500);
	}
	return;
}
