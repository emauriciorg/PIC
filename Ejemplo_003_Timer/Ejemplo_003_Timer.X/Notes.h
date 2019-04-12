// -*- C++ -*-
/* 
 * File:   Notes.h
 * Author: Mauricio
 *
 * Created on 15 de enero de 2017, 22:12
 */

#ifndef NOTES_H
#define	NOTES_H

#include"speaker.h"
#include"timer.h"
//speaker connected to one of the PWM ports
#define speaker Speaker
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880


unsigned int DelayAmount = 0;

long LoopTime = 0;


void delay_mio(unsigned int TMR2Millis)
{
volatile unsigned int iTMR2Millis;
  for(iTMR2Millis=0;iTMR2Millis<TMR2Millis;iTMR2Millis++)
  {
    PR2=1;
    T2CON=Pos1|Pres1;
    TMR2=0;
    T2CON|=StartTimer;
    PIE1|=TimerIFG;
    while((PIR1&0x02)==0);
    PIR1&=~TimerIFG;
    T2CON&=~StartTimer;
    PIE1&=~TimerIFG;
  }
}




void beep(int FrequencyInHertz, long TimeInMilliseconds)
{
    volatile int x=0;
    Speaker=1;
    LATD=FrequencyInHertz;
    DelayAmount =  (80000/FrequencyInHertz);
    LoopTime = (long)((TimeInMilliseconds*100)/(DelayAmount*2));

    for (x=0;x<LoopTime;x++)
    {
        Speaker=1;
       delay_mio(DelayAmount);
        Speaker=0; 
       delay_mio(DelayAmount);
    }
    LATD=0;
    __delay_ms(100);
}

void TheImperialMarch()
{
    beep(a, 500);
    beep( a, 500);
    beep( a, 500);
    beep( f, 350);
    beep( cH, 150);

    beep( a, 500);
    beep( f, 350);
    beep( cH, 150);
    beep( a, 1000);
   
    beep( eH, 500);
    beep( eH, 500);
    beep(eH, 500);
    beep( fH, 350);
    beep( cH, 150);

    beep( gS, 500);
    beep( f, 350);
    beep( cH, 150);
    beep( a, 1000);
    
    beep( aH, 500);
    beep( a, 350);
    beep( a, 150);
    beep( aH, 500);
    beep( gSH, 250);
    beep( gH, 250);

    beep( fSH, 125);
    beep( fH, 125);
    beep( fSH, 250);
    __delay_ms(150);
    beep( aS, 250);
    beep( dSH, 500);
    beep( dH, 250);
    beep( cSH, 250);
  

    beep( cH, 125);
    beep( b, 125);
    beep( cH, 250);
    __delay_ms(150);
    beep( f, 125);
    beep( gS, 500);
    beep( f, 375);
    beep( a, 125);

    beep( cH, 500);
    beep( a, 375);
    beep( cH, 125);
    beep( eH, 1000);
   
    beep( aH, 500);
    beep( a, 350);
    beep( a, 150);
    beep( aH, 500);
    beep( gSH, 250);
    beep( gH, 250);

    beep( fSH, 125);
    beep( fH, 125);
    beep( fSH, 250);
    __delay_ms(150);
    beep(aS, 250);
    beep(dSH, 500);
    beep(dH, 250);
    beep(cSH, 250);
    

    beep( cH, 125);
    beep( b, 125);
    beep( cH, 250);
    __delay_ms(150);
    beep( f, 250);
    beep( gS, 500);
    beep( f, 375);
    beep( cH, 125);

    beep( a, 500);
    beep( f, 375);
    beep( c, 125);
    beep( a, 1000);
  
}



#endif	/* NOTES_H */

