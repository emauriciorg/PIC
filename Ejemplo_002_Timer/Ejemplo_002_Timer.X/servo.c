#include "servo.h"

void InitServo(void){

	Servo0Pin =0; //Servo como salida

	PR2=24;
	T2CON  = (Pos2>>1)|(Pres1);
	PIE1  |= EnableTimer;
	PIR1  &= ~TimerIFG;
	T2CON |= StartTimer;

}

void TestServo(void)
{
	SendServo(100);
	ChangePosition();
}

void SendServo( unsigned char TimeP )
{
	volatile int Count=0, PostIFG=0;
	while(PostIFG<TimeP)
	{
		while(!TMR2IF);
		TMR2IF=0;
		if(Count<Position){
			Servo0State = 1;
		}else
		{
			Servo0State = 0;
		}
		//if(Count<PositionServox){ServoxState=1;}else{ServoxState=0;}

		if(Count==1000){
			Count=0;
			PostIFG++;
		}else{
			Count++;
		}
	}
}

void ChangePosition(void)
{
	if(Position==LimSup){
		Position=LimIn;
	}
	else{
		Position=LimSup;
	}
}
void MoveServo(void)
{
	SendServo(2);
	if((PORTA&BIT5)==0){
		if(Position<LimSup){
			Position+=2;
		}
	}
	if((PORTB&BIT0)==0){
		if(Position>LimIn){
			Position-=2;
		}
	}
}
