/*
 * File:   main.c
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:30
 
 Para usar el codigo usar solo una de las funciones comentadas en el main,
1- TestSpeaker ,Enviar una onda cuadrada de ~500hz en RF0
2- Reproduce unas notas musicales en RF0
 
 Debe usarse un amplificador de audio o un driver para un speaker de lo contrario el
 pin sufrira daño irreversible por exceso de carga 
     ________________
    |                |
    |             RA5|<---external Pull-up 15k and buttom to ground
    |                |
    |                |       
    |             RB0|<---external Pull-up 15k and buttom to ground                    
    |                |       
    |           PORTD|-->LEDS
    |            RF0 |-->driver speaker
    |            MCLR|<---external Pull-up 4.7k and buttom to ground 
    |________________|
 */

#include <xc.h>
#include "PicConf.h"
#include "Modules.h"
#include"speaker.h"
#include"Ejemplo.h"
#include"Notes.h"

void main(void)
{
  InitConf(); //incia configuracion de reloj y puertos digitales
  
  ejemplo();
  InitSpeaker();
  
  while(1)
  {
  
  //TestSpeaker();   
  TheImperialMarch();
  
  }
  return;
}


