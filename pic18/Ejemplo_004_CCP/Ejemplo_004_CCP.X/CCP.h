// -*- C++ -*-
/* 
 * File:   timer.h
 * Author: Mauricio
 *
 * Created on 14 de enero de 2017, 10:19
 */

#ifndef CCP_H
#define	CCP_H


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


#define PwmMode  0x0C
unsigned int PwmDuty=0x00;
volatile unsigned int tiempo=0;

char Latch2,Latch;
void Timer2(void);
void TestCCP4(void);
void InitCCP4(void);
void SetPwmCCP4(unsigned int);
void AutoTestCCP4(void);
void Timer2(void)
{
    PR2=155;
   T2CON=(Pos10>>1)|(Pres16);
   TMR2=0;   
   //PIE1|=EnableTimer;
   T2CON|=StartTimer;
   while((PIR1&TimerIFG)==0);
   PIR1&=~TimerIFG;
}

void InitCCP4()
{
    Timer2();
    LATG=0;
    PORTG=0;
    TRISG&=~BIT3;
    CCP4CON=PwmMode;
    CCPR4L=0;
    
    
}
void TestCCP4(void)
{
   SetPwmCCP4(PwmDuty);
   while((PIR1&TimerIFG)==0);
   PIR1&=~TimerIFG;

   
   
  if(((PORTB&BIT0)==0)){if(PwmDuty<1022){PwmDuty+=1;}}
  
  if(((PORTA&BIT5)==0)){if(PwmDuty>0x00){PwmDuty-=1;}}
  

}

void AutoTestCCP4(void)
{
   while((PIR1&TimerIFG)==0);
   PIR1&=~TimerIFG;
 
  if(PwmDuty<900){PwmDuty+=1;}else{PwmDuty=0;}
  SetPwmCCP4(PwmDuty);
 
}
  
  



void SetPwmCCP4(unsigned int PwmValue)
{

CCP4CON&=~0x30;//clear two least significant bits of pwm
CCP4CON|=(PwmValue&0x03)<<4;//clear two upper bits of pwm
CCPR4L=(PwmValue)>>2;

}
#endif	/* CCP_H */

