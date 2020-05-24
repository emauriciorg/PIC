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

void ejemplo(void);
void ejemplo(void)
{
  mOPEN_LCD;
  mCURSOR_LINE1;
  LCDPutStr("Ejemplo_005");
  mCURSOR_LINE2;
  LCDPutStr("Timer Interrupt");

}

#endif	/* EJEMPLO_H */

