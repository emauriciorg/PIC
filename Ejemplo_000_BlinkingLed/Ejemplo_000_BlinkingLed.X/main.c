/*
 * File:   main.c
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:30
 *
This  example shows how to enable ouputs


|->RD0..
| .
| .
| .
|->..RD7

*/

#include <xc.h>
#include "PicConf.h"
#include "Modules.h"
#include "Ejemplo.h"
void main(void)
{
  InitConf();
  ejemplo();
  LATD=0X0F;
  

  while(1)
  {
    
    LATD^=0XFF;  
    
    delay_ms(500);//delay_ms  usando el tmr2
    LATD^=0XFF;    
  
    delay_ms(500); 
  }
  return;
}

