/*
 * File:   main.c
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:30
 
 Este codigo permite contar los segundos que pasan despues de un reset usando interrupciones por timer2
 *     ________________
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
#include"timer.h"
#include"Ejemplo.h"

unsigned char sec=0,min=0,hour=0;
unsigned char CountIFG=0;
volatile char Counter=0;
bit mostrar=0;
void Clock(void);
void main(void)
{
  InitConf(); //incia configuracion de reloj y puertos digitales
  
  ejemplo();
 
  InitTimer2Interrupts();
  while(1)
  {
      Clock();
      
    
      
  }
  return;
}


void  Clock(void)
{
    if(mostrar==1){
        mostrar=0;
    mCURSOR_LINE2;
    LCDPutStr("TimerIn ");
    LCDPutChar(hour/10+'0');
    LCDPutChar(hour%10+'0');
    LCDPutChar(':');
    LCDPutChar(min/10+'0');
    LCDPutChar(min%10+'0');
    LCDPutChar(':');
    LCDPutChar(sec/10+'0');
    LCDPutChar(sec%10+'0');
    LCDPutStr("        ");
    }
}
void interrupt Timer0_interrupt()
{
 INTCON&=~(BIT7|BIT6); //Disabled the global interrupts 
 //timer2 interrupt  0,010S
 if(PIR1&TimerIFG)  
 {
   PIR1&=~TimerIFG;
 if(Counter==100){Counter=0;CountIFG=1;mostrar=1;}else{Counter++;}
 if(CountIFG){   
     sec++;CountIFG=0;LATD=sec;
     if(sec>59){sec=0;min++;}
     if(min>59){min=0;hour++;}
     if(hour>24){hour=0;}
 }
 }
 
 INTCON|=(BIT7|BIT6); //global interrupt enable
}

