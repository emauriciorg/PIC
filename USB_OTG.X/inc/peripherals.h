#ifndef __PHERIPHERALS_H__
#define __PHERIPHERALS_H__


#define LED_YELLOW_TOGGLE() mPORTDToggleBits(BIT_1)
#define LED_YELLOW_ON() mPORTDSetBits(BIT_1)
#define LED_YELLOW_OFF() mPORTDClearBits(BIT_1)


void pheriperals_init(void);



#endif
