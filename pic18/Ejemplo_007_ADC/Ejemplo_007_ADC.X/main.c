/*
 * File:   main.c
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:30
 
 Este codigo usa el conversor analogo digital  y muestra el resultado de la conversion en la lcd
     ________________
    |                |
    |             RA5|<---external Pull-up 15k and buttom to ground
    |                |
    |                |       
    |             RB0|<---external Pull-up 15k and buttom to ground                    
    |                |       
    |           PORTD|-->LEDS
    |            RA0 |-->Pot
    |            MCLR|<---external Pull-up 4.7k and buttom to ground 
    |________________|
 */

#include <xc.h>
#include "PicConf.h"
#include "Modules.h"
#include"Ejemplo.h"


bit mostrar=0;


void main(void)
{
  InitConf(); //incia configuracion de reloj y puertos digitales
  
  ejemplo();
  InitAdc10();

    while(1)
  {
   
        TestADC();
    
    
  }
  return;
}



