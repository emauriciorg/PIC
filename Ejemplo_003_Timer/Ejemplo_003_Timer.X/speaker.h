// -*- C++ -*-
/* 
 * File:   SPEAKER.h
 * Author: Mauricio
 *
 * Created on 15 de enero de 2017, 20:38
 */

#ifndef SPEAKER_H
#define	SPEAKER_H
#include"timer.h"
#include<xc.h>
#define SpeakerPin  TRISFbits.TRISF0 
#define Speaker     LATFbits.LATF0

void SendSpeaker(void);
void InitSpeaker(void);
void TestSpeaker(void);
void InitSpeaker(void){
    
  SpeakerPin =0; //Servo como salida
  
  PR2=249;
  T2CON=(Pos5>>1)|(Pres4);
  PIE1|=EnableTimer;
  PIR1&=~TimerIFG;   
  T2CON|=StartTimer;

}

void TestSpeaker(void)
{
SendSpeaker();
}
void SendSpeaker(void)
{
  while(!TMR2IF);
  TMR2IF=0;
  Speaker=0;
  while(!TMR2IF);
  TMR2IF=0;
  Speaker=1;
}


#endif	/* SERVO_H */

