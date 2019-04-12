// -*- C++ -*-
/* 
 * File:   Modules.h
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:48
 */

#ifndef MODULES_H
#define	MODULES_H
#define IRC4Mhz 0x60  
#define InternalOscillator 0x02 
#define LedsOnBoardOn  0xFF  //leds on portD

void ClockSetting(void);
void DigitalIO(void);
void InitConf(void);
void delay_ms(volatile int);

void ClockSetup(void)
{
    OSCCON=IRC4Mhz|InternalOscillator;
    OSCTUNE = 0x00;
}
void delay_ms(volatile int TMR2Millis)
{
  volatile int iTMR2Millis;
  for(iTMR2Millis=0;iTMR2Millis<TMR2Millis;iTMR2Millis++)
  {
    PR2=49;
    T2CON=(0X04<<3)|BIT0;
    TMR2=0;
    T2CON|=BIT2;
    PIE1|=BIT1;
    while((PIR1&BIT1)==0);
    PIR1&=~BIT1;
    T2CON&=~BIT2;
    PIE1&=~BIT1;
  }
}


void DigitalIO(void)
{
    LATD=0;
    PORTD=0;
    TRISD=0;
    TRISD& =~(LedsOnBoardOn);

}

void InitConf(void)
{
    ClockSetup();
    DigitalIO();
}







#endif	/* MODULES_H */

