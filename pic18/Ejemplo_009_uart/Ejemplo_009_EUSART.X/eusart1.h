
#ifndef _EUSART1_H
#define _EUSART1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
 
#define EUSART1_DataReady  (PIR1bits.RC1IF)


void EUSART1_Initialize(void)
{
    RCSTA = 0x80;
    TXSTA = 0x26;
    SPBRG = 64;
    SPBRGH = 0x00;
    TXREG = 0x00;
    RCREG = 0x00;

}


void EUSART1_Write(uint8_t txData)
{
    while(0 == PIR1bits.TX1IF)
    {
    }

    TXREG = txData;    // Write the data byte to the USART.
}



void putch(char txData)
{
    EUSART1_Write(txData);
}


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _EUSART1_H
/**
 End of File
*/