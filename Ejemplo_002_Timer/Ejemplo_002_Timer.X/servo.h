// -*- C++ -*-
/* 
 * File:   servo.h
 * Author: Mauricio
 *
 * Created on 15 de enero de 2017, 20:38
 */

#ifndef SERVO_H
#define	SERVO_H
#include"timer.h"
#include<xc.h>
//La funcion servo opera bajo un oscilador de 10Mhz, si se cambia el oscilador se deben cambia los valores de las variables
// PR2, Postcaler y prescaler
#define Servo0Pin  TRISDbits.TRISD0 
#define Servo0State  LATDbits.LATD0

#define LimSup  110
#define LimIn   35

//#define ServoxPin  TRISYbits.TRISY0  
//#define ServoxState  LATYbits.LATY0

//para agraegar mas servos  cambiar  x por el numero del pin y (Y) por el puerto para el puertoD en RD1 seria 
//#define Servo1Pin  TRISDbits.TRISD1  
//#define Servo1State  LATDbits.LATD1

unsigned char Position=50;
void TestServo(void);
void MoveServo(void);
void InitServo(void);
void SendServo(unsigned char);
void ChangePosition(void);

void InitServo(void){

  Servo0Pin =0; //Servo como salida
  
  PR2=24;
  T2CON=(Pos2>>1)|(Pres1);
  PIE1|=EnableTimer;
  PIR1&=~TimerIFG;   
  T2CON|=StartTimer;

}

void TestServo(void)
{
    SendServo(100);
    ChangePosition();
}

void SendServo( unsigned char TimeP )
{
  volatile int Count=0, PostIFG=0;
  while(PostIFG<TimeP)
  {  
  while(!TMR2IF);
  TMR2IF=0;
  if(Count<Position){Servo0State=1;}else{Servo0State=0;}
  //if(Count<PositionServox){ServoxState=1;}else{ServoxState=0;}
  
  if(Count==1000){Count=0;PostIFG++;}else{Count++;}
  }  
}

void ChangePosition(void)
{
if(Position==LimSup){Position=LimIn;}else{Position=LimSup;}
}
void MoveServo(void)
{
 SendServo(2);
 if((PORTA&BIT5)==0){if(Position<LimSup){Position+=2;}}
 if((PORTB&BIT0)==0){if(Position>LimIn){Position-=2;}}
}

#endif	/* SERVO_H */

