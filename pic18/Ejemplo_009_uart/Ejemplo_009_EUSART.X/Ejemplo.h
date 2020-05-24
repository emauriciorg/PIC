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



void ejemplo(void)
{
     mOPEN_LCD;
    mCURSOR_LINE1;
    LCDPutStr("Ejemplo_009");
    mCURSOR_LINE2;
    LCDPutStr("Eusart");

}



#endif	/* EJEMPLO_H */

