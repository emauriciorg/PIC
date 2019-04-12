// -*- C++ -*-
/* 
 * File:   Ejemplo.h
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 20:21
 */

#ifndef EJEMPLO_H
#define	EJEMPLO_H
#include"BBSPI_LCD.h"
volatile char asciiLCD;
void  TestChar(void);
void ejemplo(void);

void TestChar(void)
{

mCURSOR_LINE2;
LCDPutChar(asciiLCD++);

}


void ejemplo(void)
{
  mOPEN_LCD;
  mCURSOR_LINE1;
  LCDPutStr("Ejemplo_008 LCD");
  mCURSOR_LINE2;
  LCDPutStr("LCD");

}



#endif	/* EJEMPLO_H */

