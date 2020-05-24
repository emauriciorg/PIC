// -*- C++ -*-
/*
 * File:   SPEAKER.h
 * Author: Mauricio
 *
 * Created on 15 de enero de 2017, 20:38
 */

#ifndef SPEAKER_H
#define	SPEAKER_H
#include"timer.h"
#include<xc.h>
#define SpeakerPin  TRISFbits.TRISF0
#define Speaker     LATFbits.LATF0

void SendSpeaker(void);
void InitSpeaker(void);
void TestSpeaker(void);
#endif	/* SERVO_H */
