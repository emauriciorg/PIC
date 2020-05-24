



#include <xc.h>
#define _XTAL_FREQ 10000000
#include "BBSPI_LCD.h"
#include "eusart1.h"
#include "Modules.h"
#include "PicConf.h"
#include "Ejemplo.h"
/*el siguiente codigo usa el modulo eusart1 a 9600 baudios 8N1 */

void test_uart(void);

void main(void)
{
InitConf();
EUSART1_Initialize();
ejemplo();

    while (1)
    {
     test_uart();   
    }
}


void test_uart(void)
{
    printf("Ejemplo_009 Eusart\n\r");
   
}