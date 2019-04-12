#include <xc.h>
#include <plib.h>
#include "pic32_timers.h"
#include "hw_profile.h"

uint32_t u32_millis_counter;
uint32_t u32_timeout_counter;


typedef struct {
	uint32_t counter;
	uint8_t triggered;
	uint8_t done;
}timeout_t;

timeout_t micros;
timeout_t millis;
timeout_t seconds;
#pragma interrupt OC1Interrupt ipl2 vector 6
void OC1Interrupt(void){
	IFS0bits.OC1IF = 0;
}
void pic32_set_pwm(unsigned  long int pwm_period, unsigned long int pwm_duty_cycle){

	unsigned long int calculated_pr;
	unsigned long int calculated_duty_cycle;

	CloseOC3();

 	calculated_pr = (pwm_period*SYS_FREQ)-1; 
	calculated_duty_cycle = calculated_pr * (pwm_duty_cycle/100);
	OpenOC3( OC_ON |
 		OC_TIMER2_SRC |
 		OC_PWM_FAULT_PIN_DISABLE,
 		0,
 		0);
  	OpenTimer2( T2_ON |
  		T1_PS_1_1 |
  		T2_SOURCE_INT,
  		calculated_pr);

 	SetDCOC3PWM(calculated_duty_cycle/2); 

}

/*Timeout using the CORETIMER*/
void core_timer_trigger(uint16_t timeout_seconds){ 
	OpenCoreTimer(CORE_TICK_RATE);
	mCTClearIntFlag();
	UpdateCoreTimer(CORE_TICK_RATE);		
}
void timers_coretimer_setup(void){	
	OpenCoreTimer(CORE_TICK_RATE);
	mConfigIntCoreTimer((CT_INT_OFF | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));
}



char servo_timeout_reached(){
 	return micros.done;
}
void servo_set_timeout(uint32_t micros_period){
	micros.done = 0 ;
	micros.counter = micros_period;
}

char servo_trigger(){
	return micros.triggered;
}


char millis_timeout_reached(){
 	return millis.done;
}
void millis_set_timeout(uint32_t millis_period){
	millis.done = 0 ;
	millis.counter = millis_period*10;
}

char millis_trigger(){
	return millis.triggered;
}

char core_timer_polling_routine(void){
	if (!mCTGetIntFlag() ){
		return 0;
	}
	UpdateCoreTimer(CORE_TICK_RATE);
	mCTClearIntFlag();

	if(micros.counter) micros.counter--;
	if (micros.counter==0) {
		micros.done = 1;
		micros.triggered = 0;
	}

	if(millis.counter) millis.counter--;
	if (millis.counter==0) {
		millis.done = 1;
		millis.triggered = 0;
	}

//	CloseCoreTimer();
	
	return 1;
}


