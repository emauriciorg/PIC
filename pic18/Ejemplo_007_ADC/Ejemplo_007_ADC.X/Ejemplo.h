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
  LCDPutStr("Ejemplo_007 ADC");
  mCURSOR_LINE2;
  LCDPutStr("ADC");

}

#endif	/* EJEMPLO_H */

