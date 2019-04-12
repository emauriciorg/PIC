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
#include"BBSPI_LCD.h"

#define IRC4Mhz 0x60  
#define InternalOscillator 0x02 
#define PrimaryOscillator 0x00 
#define LedsOnBoardOn  0xFF  //leds on portD
#define ButtonOnBoardRA5  BIT5  //leds on portD
#define ButtonOnBoardRB0  BIT0  //leds on portD

volatile unsigned int voltage=0,volts;
volatile unsigned int milN, cenN, decN, unitN;

volatile unsigned int volti=0;
void ClockSetting(void);
void DigitalIO(void);
void InitConf(void);
void ClockSetup(void)
{
   OSCCON=PrimaryOscillator ;
   OSCTUNE = 0x00;
 //OSCCON = 0x30;
 //OSCTUNE = 0x40;

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
    PSPCON=0;
  

    LATC = 0x00;
    TRISC = 0xD7;

    
    LATE = 0x00;
    TRISE = 0x07;

    INTCON2bits.nRBPU = 0x01;
    
}

void InitConf(void)
{
    ClockSetup();
    DigitalIO();
}



#endif	/* MODULES_H */

