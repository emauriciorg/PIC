// -*- C++ -*-
/* 
 * File:   Modules.h
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:48
 */

#ifndef MODULES_H
#define	MODULES_H

#include"Macros.h"
#include<xc.h>

#define IRC4Mhz 0x60  
#define InternalOscillator 0x02 
#define PrimaryOscillator 0x00 
#define LedsOnBoardOn  0xFF  //leds on portD
#define ButtonOnBoardRA5  BIT5  //leds on portD
#define ButtonOnBoardRB0  BIT0  //leds on portD


void ClockSetting(void);
void DigitalIO(void);
void InitConf(void);
void Timer2(volatile int);

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



#endif	/* MODULES_H */

