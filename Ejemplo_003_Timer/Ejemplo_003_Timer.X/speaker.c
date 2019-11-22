#include "speaker.h"

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
