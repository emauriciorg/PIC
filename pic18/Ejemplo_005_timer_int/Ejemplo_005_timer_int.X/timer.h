// -*- C++ -*-
/* 
 * File:   timer.h
 * Author: Mauricio
 *
 * Created on 14 de enero de 2017, 10:19
 */

#ifndef timer_H
#define	timer_H



#define EnableTimer2 0x02
#define StartTimer2  0x04
#define Timer2IFG    0x02

#define PwmMode  0x0C
unsigned int PwmDuty=0x00;
volatile unsigned int tiempo=0;

void InitTimer2(void);
void TestCCP4(void);
void InitCCP4(void);
void SetPwmCCP4(unsigned int);
void AutoTestCCP4(void);
void EnableInterrupts(void);

#define Pos1  0x00
#define Pos2  0x10
#define Pos3  0x20
#define Pos4  0x30
#define Pos5  0x40
#define Pos6  0x50
#define Pos7  0x60
#define Pos8  0x70
#define Pos9  0x80
#define Pos10 0x90
#define Pos11 0xA0
#define Pos12 0xB0
#define Pos13 0xC0
#define Pos14 0xD0
#define Pos15 0xE0
#define Pos16 0xF0
#define Pres1 0x00
#define Pres4 0x01
#define Pres16 0x02 
#define EnableTimer 0x02
#define StartTimer  0x04
#define TimerIFG    0x02
void Timer2(void);
void InitTimer2Interrupts(void);

void InitTimer2Interrupts(void)
{
  
    Timer2();
    EnableInterrupts();
  
}
  
void Timer2(void)
{
   PR2=96;
   T2CON=(Pos16>>1)|(Pres16);
   TMR2=0;   
   PIE1|=EnableTimer;
   T2CON|=StartTimer;
  //while((PIR1&TimerIFG)==0);
   PIR1&=~TimerIFG;
}


void EnableInterrupts(void)
{
   INTCONbits.GIE=1;
   INTCONbits.PEIE_GIEL=1; //global interrupt enable

}



#endif	/* TIMER_H */

