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
#define ChannelAN0 0x00
#define VddAndVss  0x00
#define ConfAN0    0x0E;
#define ACQT20TAD  0x38
#define AdcClock   0x05
#define ADCWait    10
#define ACQ_US_DELAY   500 //10*TAD
volatile unsigned int voltage=0,volts;
volatile unsigned int milN, cenN, decN, unitN;

volatile unsigned int volti=0;
void ClockSetting(void);
void DigitalIO(void);
void InitConf(void);
void InitAdc10(void);
unsigned int  SampleADC(void);
void TestADC(void);
void ClockSetup(void)
{
    OSCCON=IRC4Mhz|PrimaryOscillator;
    OSCTUNE = 0x00;
}

void InitAdc10(void)
{
    TRISAbits.RA0=1;
   ADCON0bits.GODONE=0;
   
    ADCON1=VddAndVss|ConfAN0;
    ADCON0=ChannelAN0;
    ADCON2=ACQT20TAD|AdcClock;  
    ADCON2bits.ADFM=1; //Justificado a la derecha
    
   
}
unsigned int SampleAN0(void)
{   
   ADCON0bits.GODONE=0;
    ADCON0bits.ADON=1;
    __delay_us(ACQ_US_DELAY);
   ADCON0bits.GODONE=1;
   __delay_us(ACQ_US_DELAY);
   while(ADCON0&0x02);
   volti=(((ADRESH<<8))|ADRESL);
   ADCON0bits.GODONE=0;
   ADCON0bits.ADON=0;

   return (volti);
}
void TestADC(void)
{
 __delay_ms(100);
    //voltage=(soyMSB<<8)|soyLSB;
    voltage=SampleAN0()&0x03ff;
    milN=(voltage/1000)+'0';
    cenN=((voltage%1000)/100)+'0';
    decN=((voltage%100)/10)+'0';
    unitN=((voltage%10))+'0';
    mCURSOR_LINE2;
    LCDPutChar(milN);
    LCDPutChar(cenN);
    LCDPutChar(decN);
    LCDPutChar(unitN);
    volts=voltage*0.5;
    LCDPutChar(' ');
    LCDPutChar((volts/100)+'0');
    LCDPutChar('.');
    LCDPutChar(((volts%100)/10)+'0');
    LCDPutChar((volts%10)+'0');
    LATD=voltage;
    
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

