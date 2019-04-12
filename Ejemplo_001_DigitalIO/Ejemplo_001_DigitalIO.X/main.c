/*
 * File:   main.c
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:30
 
 Para usar el codigo usar solo una de las funciones comentadas en el main,
1- Esta funcion  selleciona que led del puerto D se desea encender usando los botones
2-Esta funcion muestra en los leds el valor de la variable TempValue, los botones sirven para incrementar o decrementar TempValue
     ________________
    |                |
    |             RA5|<---external Pull-up 15k and buttom to ground
    |                |
    |                |       
    |             RB0|<---external Pull-up 15k and buttom to ground                    
    |                |       
    |           PORTD|-->LEDS
    |                |
    |            MCLR|<---external Pull-up 4.7k and buttom to ground 
    |________________|
 */

#include <xc.h>
#include "PicConf.h"
#include "Modules.h"
#include "Ejemplo.h"

volatile unsigned char TempValue=0;

char CheckLimits(void); //revisa que el led encendido no se encuentre en los extremos
void ShiftLeds(void);
void Contador(void);

void main(void)
{
  InitConf(); //inicia configuracion de reloj y puertos    digitales
  ejemplo();
  LATD=0X01; 
  while(1)
  {
   //Este codigo puede ejecutar solo una de la dos funciones al mismo tiempo
    //ShiftLeds();
    Contador();
  }
  return;
}


char CheckLimits(void)
{
    if(LATD&0X01){return 'L';}
    else
    {
     if(LATD&0x80){return 'M';}else{return 0;}
    }
}
void Contador(void)
{
    //Porta&RA5==RA5 ->lectura y comparacion del bit ra5, se puede compara con bit5 o con 0x00
   if(((PORTA&ButtonOnBoardRA5)^ButtonOnBoardRA5) )
    {
      TempValue--;  
     Timer2(200);//Debouncing delay
    }
    if(((PORTB&ButtonOnBoardRB0)^ButtonOnBoardRB0) )
    {
       TempValue++;      
     Timer2(200);//Debouncing delay
    }
   LATD=TempValue;
}


void ShiftLeds(void)
{
//Lectura de cero en RA5 y comparacion de limite
    if(((PORTA&ButtonOnBoardRA5)^ButtonOnBoardRA5) &&(CheckLimits()!='L'))
    {
     LATD>>=1;  //desplazamiento del led
     Timer2(200);//Debouncing delay
    }
    if(((PORTB&ButtonOnBoardRB0)^ButtonOnBoardRB0) &&(CheckLimits()!='M'))
    {
     LATD<<=1;  
     Timer2(200);//Debouncing delay
    }


}