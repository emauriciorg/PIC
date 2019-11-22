#include "Modules.h"

void ClockSetup(void)
{
    OSCCON=IRC4Mhz|PrimaryOscillator;
    OSCTUNE = 0x00;
}



void DigitalIO(void)
{
    LATA=0;
    PORTA=0;
    TRISA=ButtonOnBoardRA5;
    ADCON1=0X0F; //A/D control Port , configuracion adicional para habilatar deshabilitar las entradas analogas

    LATB=0;
    PORTB=0;
    TRISB=ButtonOnBoardRB0;

    LATD=0;
    PORTD=0;
    TRISD=0;
    TRISD&=~(LedsOnBoardOn);//equivalente a TRISD=0x00, todo el puerto como salida
    PSPCON=0;
}

void InitConf(void)
{
    ClockSetup();
    DigitalIO();
}
