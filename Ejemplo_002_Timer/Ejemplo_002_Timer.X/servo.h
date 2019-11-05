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


#endif	/* SERVO_H */
