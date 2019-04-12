/*
 * File:   main.c
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:30
 
 Para usar el codigo usar solo una de las funciones comentadas en el main,
1- TestServo , mueve el servo automaticamente
2-Mueve el servo con los botones en la board RB0 y RA5
     ________________
    |                |
    |             RA5|<---external Pull-up 15k and buttom to ground
    |                |
    |                |       
    |             RB0|<---external Pull-up 15k and buttom to ground                    
    |                |       
    |          PORTD0|-->Servo
    |                |
    |            MCLR|<---external Pull-up 4.7k and buttom to ground 
    |________________|
 */

#include <xc.h>
#include "PicConf.h"
#include "Modules.h"
#include"servo.h"
#include"Ejemplo.h"


void main(void)
{
  InitConf(); //incia configuracion de reloj y puertos digitales
  ejemplo();
  
  InitServo();
  
  while(1)
  {
  
  TestServo();   
  //MoveServo();
   }
  return;
}
