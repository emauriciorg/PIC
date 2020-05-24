#include "xc.h"
#include "plib.h"
#include "pic32_uart.h"
#include "stdio.h"

#ifndef SYS_FREQ
#define SYS_FREQ			(96000000UL)
#endif 

unsigned char  U1TxBuf[U1TxBufSize];
unsigned char	U1RxBuf[U1RxBufSize];
unsigned int	U1RxHead=0,U1RxTail=0;
unsigned int	U1RxCharCount=0;
unsigned char U1Unread = 0 ;

unsigned char  U2TxBuf[U2TxBufSize];
unsigned char	U2RxBuf[U2RxBufSize];
unsigned int	 U2RxHead=0,U2RxTail=0;
unsigned int	U2RxCharCount=0;
unsigned char U2Unread = 0 ;

unsigned char U2ClearDataAvailable()
{
         U2Unread=0;
         U2RxTail=0;
}
unsigned char U1ClearDataAvailable()
{
        U1Unread=0;
        U1RxTail=0;
}
unsigned char U1DataAvailable()
{
        return U1Unread;
}
unsigned char U2DataAvailable()
{
        return U2Unread;
}
//*************************************************************************************************


void f_init_UARTS(){
    
    mPORTDSetPinsDigitalOut(BIT_3); //UART1_TX as an output
    mPORTDSetPinsDigitalIn(BIT_2); //UART1_RX as an input
    mPORTFSetPinsDigitalOut(BIT_5); //UART2_TX as an output
    mPORTFSetPinsDigitalIn(BIT_4); //UART2_RX as an input
   UART1_init(115200);
   UART2_init(115200);
   
}

void UART1_init(unsigned long int UART_Baud)
{
                                              UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);
                                            UARTSetFifoMode(UART1, UART_INTERRUPT_ON_RX_NOT_EMPTY );
//                                            UARTSetFifoMode(UART1, UART_INTERRUPT_ON_RX_NOT_EMPTY|UART_INTERRUPT_ON_TX_DONE  );

                                            UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
                                            UARTSetDataRate(UART1, SYS_FREQ, UART_Baud);
                                            UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
                                            
                                            INTClearFlag(INT_SOURCE_UART_ERROR(UART1));    
                                          INTClearFlag(INT_SOURCE_UART_TX(UART1));    
                                            INTClearFlag(INT_SOURCE_UART_RX(UART1));     
                                            INTClearFlag(INT_SOURCE_UART(UART1));     
                                           
                                            
                                             INTSetVectorPriority(INT_VECTOR_UART(UART1), INT_PRIORITY_LEVEL_3);
                                            INTSetVectorSubPriority(INT_VECTOR_UART(UART1), INT_SUB_PRIORITY_LEVEL_1);

                                           //INTEnable(INT_SOURCE_UART_ERROR(UART1), INT_DISABLED);
                                     //      INTEnable(INT_SOURCE_UART(UART1), INT_DISABLED);
                                            
                                            INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);
                                            //INTEnable(INT_SOURCE_UART_TX(UART1), INT_DISABLED);


}

void UART1_reset_rx_buffer(void)
{
    U1RxTail = 0;
}

unsigned char UART1_is_unread(void)
{
    return (U1Unread);
}

void UART1_clear_unread(void)
{
    U1Unread = 0;
}

void UART1_write_string(const char *string)
{
	while(*string != '\0')
	{
		while(!UARTTransmitterIsReady(UART1))	;
		UARTSendDataByte(UART1, *string);
		string++;
		while(!UARTTransmissionHasCompleted(UART1));
	}
}

void UART1_write_string_1(const char *string,int lengt)
{
    int cntr;
	while(cntr <lengt )
	{
		while(!UARTTransmitterIsReady(UART1))	;
		UARTSendDataByte(UART1, *string);
		string++;
		while(!UARTTransmissionHasCompleted(UART1));
        cntr++;
	}
}

void UART1_write_char(const char ch)
{
		while(!UARTTransmitterIsReady(UART1))	
            continue;
		UARTSendDataByte(UART1, ch);
}

void UART1_get_string(void)
{
    if(UARTReceivedDataIsAvailable(UART1))
    {
        // U1UnRead = 1;
        U1RxBuf[U1RxTail] = UARTGetDataByte(UART1);
        if(U1RxBuf[U1RxTail] == '\r')
        {
            U1Unread = 1;
            U1RxTail = 0;
        }
        else
            U1RxTail++;
        if(U1RxTail >= U1RxBufSize)
            U1RxTail = 0;
    }
}

void __ISR(_UART1_VECTOR, IPL6AUTO) IntUART1Handler(void)
{
  if(INTGetFlag(INT_SOURCE_UART_RX(UART1))) //RX?
  {
            U1RxBuf[U1RxTail] = UARTGetDataByte(UART1);
               U1RxHead=U1RxTail;
                U1Unread = 1;
                U1RxTail++;
            
                if(U1RxTail>=U1RxBufSize) 
                U1RxTail=0;
  }

    
    if ( INTGetFlag(INT_SOURCE_UART_TX(UART1)) ){
    }
            INTClearFlag(INT_SOURCE_UART_RX(UART1));
            INTClearFlag(INT_SOURCE_UART_TX(UART1));
            INTClearFlag(INT_SOURCE_UART_ERROR(UART1));
  
}
                                            

//************************************************************************************************
void UART2_init(UINT32 UART_Baud)
{           

                                            UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY);
                                            UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY );
//                                            UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY|UART_INTERRUPT_ON_TX_DONE  );

                                            UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
                                            UARTSetDataRate(UART2, SYS_FREQ, UART_Baud);
                                            UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
                                            
                                            INTClearFlag(INT_SOURCE_UART_ERROR(UART2));    
                                          INTClearFlag(INT_SOURCE_UART_TX(UART2));    
                                            INTClearFlag(INT_SOURCE_UART_RX(UART2));     
                                            INTClearFlag(INT_SOURCE_UART(UART2));     
                                           
                                            
                                             INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_4);
                                            INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_1);

                                           //INTEnable(INT_SOURCE_UART_ERROR(UART2), INT_DISABLED);
                                     //      INTEnable(INT_SOURCE_UART(UART2), INT_DISABLED);
                                            
                                            INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
                                            //INTEnable(INT_SOURCE_UART_TX(UART2), INT_DISABLED);

                                            
}

void UART2_reset_rx_buffer(void)
{
    U2RxTail = 0;
}

unsigned char UART2_is_unread(void)
{
    return (U2Unread);
}

void UART2_clear_unread(void)
{
    U2Unread = 0;
}

void UART2_write_string(const char *string)
{
	while(*string !=0)
	{
		while(!UARTTransmitterIsReady(UART2));
		UARTSendDataByte(UART2, *string);
		string++;
	}
}

void UART2_write_string_1(const char *string,int length)
{
    int cntr=0;
	while(cntr < length)
	{
		while(!UARTTransmitterIsReady(UART2))	;
		UARTSendDataByte(UART2, *string);
		string++;
		while(!UARTTransmissionHasCompleted(UART2));
        cntr++;
    }
}

void UART2_write_char(const char ch)
{
		while(!UARTTransmitterIsReady(UART2))	
            continue;
		UARTSendDataByte(UART2, ch);
}

void UART2_get_string(void)
{
    if(UARTReceivedDataIsAvailable(UART2))
    {
        // U1UnRead = 1;
        U2RxBuf[U2RxTail] = UARTGetDataByte(UART2);
        if(U2RxBuf[U2RxTail] == '\r')
        {
            U2RxHead=U2RxTail;
            U2Unread = 1;
            U2RxTail = 0;
        }
        else
            U2RxTail++;
        if(U2RxTail >= U2RxBufSize)
            U2RxTail = 0;
    }
}


void __ISR(_UART2_VECTOR, IPL5AUTO) IntUart2Handler(void)
{
	if(INTGetFlag(INT_SOURCE_UART_RX(UART2))) //RX?
	{
            U2RxBuf[U2RxTail] = UARTGetDataByte(UART2);
            if(U2RxBuf[U2RxTail] == '\r')
            {
               U2RxHead=U2RxTail;
                U2Unread = 1;
                U2RxTail=0;
            }
            else{
                U2RxTail++;
            }if(U2RxTail>=U2RxBufSize) 
                U2RxTail=0;
	}

    
    if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) ){
    }
            INTClearFlag(INT_SOURCE_UART_RX(UART2));
            INTClearFlag(INT_SOURCE_UART_TX(UART2));
            INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
  
}
