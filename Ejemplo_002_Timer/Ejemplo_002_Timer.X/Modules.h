// -*- C++ -*-
/*
 * File:   Modules.h
 * Author: Mauricio
 *
 * Created on 4 de enero de 2017, 2:48
 */

#ifndef MODULES_H
#define	MODULES_H

#include"Macros.h"
#include<xc.h>

#define IRC4Mhz 0x60
#define InternalOscillator 0x02
#define PrimaryOscillator 0x00
#define LedsOnBoardOn  0xFF  //leds on portD
#define ButtonOnBoardRA5  BIT5  //leds on portD
#define ButtonOnBoardRB0  BIT0  //leds on portD


void ClockSetting(void);
void DigitalIO(void);
void InitConf(void);
void Timer2(volatile int);



#endif	/* MODULES_H */
