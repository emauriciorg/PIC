/* ************************************************************************** */
/** Descriptive File Name

 
  @File Name
    uart.h

  @Summary
    low level uart driver.

  @Description
    Handle all pic32 uart.
 */
/* ************************************************************************** */

#ifndef _PIC32_UART_H_    /* Guard against multiple inclusion */
#define _PIC32_UART_H_


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <xc.h>
#include "plib.h"
#include "hw_profile.h"
#include <proc/p32mx440f256h.h>



#define RX_BUFFER_SIZE 1088
#define PACKET_SIZE 32
#define SERIAL_SIZE 9

typedef struct {
    char packet_init_sequence;
    char command;
    char packet_data[RX_BUFFER_SIZE];
    char packet_end_sequence;
    char packet_complete;
    char available;
}uart_protocol;


typedef struct {
	char     unread;
	char     RxBuf[RX_BUFFER_SIZE];
	uint16_t	RxHead;
	uint16_t    RxTail;        
	uart_protocol packet;
}st_uart_set;



#define __DEBUG_

#ifdef __DEBUG_
	#define __debug_port_ UART1
	void _mon_putc(char c);
	char uart_get_command(void);
	void send_debug_chr(char character);
	#ifdef PRINT_STDIO
		#define DEBUG_MSG(...) printf(__VA_ARGS__)
	#else
		void DEBUG_MSG(char *str);
	#endif
#else
	#define DEBUG_MSG(...) 
	#define printf(...)
#endif /* __DEBUG_ */


#define __USE_UART1_ 
//#define __USE_UART2_
//#define __USE_UART3_
//#define __USE_UART4_
//#define __USE_UART5_
//#define __USE_UART6_


#ifdef __USE_UART1_
	st_uart_set UART1_INST;
#endif /* __USE_UART1_ */

#ifdef __USE_UART2_
	st_uart_set UART2_INST;
#endif 

#ifdef __USE_UART3_
	st_uart_set UART3_INST; 
#endif 

#ifdef __USE_UART4_
	st_uart_set UART4_INST;
#endif 

#ifdef __USE_UART5_
	st_uart_set UART5_INST;
#endif 

#ifdef __USE_UART6_
	st_uart_set UART6_INST;
#endif 
    
   
#define UART_FUNCTION_DEC(X)    void WriteChar_U##X(char character);      \
				void WriteString_UART_##X (char *string); \
				char  U##X##sget( char *rd );             \
				char U##X##BufGet(void);                  \
				void U##X##_clear_variables(void);        \
				char U##X##_get_rx_length(void);          \
				void uart##X##_serial_reciever(void);     \
				void uart##X##_store_packet(void);        \
				char UART##X##_is_package_available(void);\


#define UART_FUNCTIONS_INIT(X,P,SP)	UARTConfigure(UART##X, UART_ENABLE_PINS_TX_RX_ONLY);                                     \
					UARTSetFifoMode(UART##X, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_TX_DONE);    \
					UARTSetLineControl(UART##X, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);\
					UARTSetDataRate(UART##X, GetPeripheralClock(), UART_Baud);                               \
					UARTEnable(UART##X, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));             \
					U##X##_clear_variables();                                                                \
					INTEnable(INT_SOURCE_UART_RX(UART##X), INT_ENABLED);                                     \
					INTSetVectorPriority(INT_VECTOR_UART(UART##X), INT_PRIORITY_LEVEL_##P);                  \
					INTSetVectorSubPriority(INT_VECTOR_UART(UART##X), INT_SUB_PRIORITY_LEVEL_##SP);          \



#define UART_FUNCTION_ISR(X,S)	void __ISR(_UART_##X##_VECTOR, IPL##S##AUTO) IntUart##X##Handler(void){                  \
				if (INTGetFlag(INT_SOURCE_UART_RX(UART##X)))        {                                    \
					UART##X##_INST.RxBuf[UART##X##_INST.RxTail++] = UARTGetDataByte(UART##X);        \
					if (UART##X##_INST.RxTail>=RX_BUFFER_SIZE) UART##X##_INST.RxTail=0;              \
						INTClearFlag(INT_SOURCE_UART_RX(UART##X));     }                         \
				if ( INTGetFlag(INT_SOURCE_UART_TX(UART##X)) )     {                                     \
					INTClearFlag(INT_SOURCE_UART_TX(UART##X));    }}                                 \



#define UART_FUNCTION_WRITE_CHAR(X) void WriteChar_U##X(char character){               \
						while(!UARTTransmitterIsReady(UART##X));      \
						UARTSendDataByte(UART##X, character);         \
						while(!UARTTransmissionHasCompleted(UART##X));\
					    }                                                 \

#define UART_FUNCTION_WRITE_STRING(X)       void WriteString_UART_##X(char *string){\
						while(*string != '\0'){             \
						    WriteChar_U##X(*string);        \
						    string++;                       \
						}                                   \
					    }                                       \

#define UART_FUNCTION_GET(X)	char  U##X##sget( char *rd ){                                                      \
					if (UART##X##_INST.RxHead != UART##X##_INST.RxTail ){                      \
						*rd = (char)UART##X##_INST.RxBuf[UART##X##_INST.RxHead];           \
						UART##X##_INST.RxHead ++;                                          \
						if (UART##X##_INST.RxHead>=RX_BUFFER_SIZE) UART##X##_INST.RxHead=0;\
						return 1;                                                          \
					}                                                                          \
					return 0;                                                                  \
				}                                                                                  \

#define UART_FUNCTION_CLEAR_VARIABLES(X)        void U##X##_clear_variables(void){                         \
						    memset(UART##X##_INST.RxBuf, 0, UART##X##_INST.RxTail);\
						    UART##X##_INST.RxHead=0,UART##X##_INST.RxTail=0;       \
						}                                                          \


#define UART_FUNCTION_GET_RX_LENGTH(X)       char U##X##_get_rx_length(void){                                                  \
						if (UART##X##_INST.RxHead < UART##X##_INST.RxTail){                           \
						    return (UART##X##_INST.RxTail - UART##X##_INST.RxHead);                   \
						}                                                                             \
						else if (UART##X##_INST.RxHead > UART##X##_INST.RxTail){                      \
						    return ((RX_BUFFER_SIZE - UART##X##_INST.RxHead) + UART##X##_INST.RxTail);\
						}                                                                             \
						else{                                                                         \
						    return 0;                                                                 \
						}                                                                             \
					    }                                                                                 \


					    
#define UART_FUNCTION_RECIEVE_DATA_NOT_ISR(X)  void uart##X##_serial_reciever(void)\
						{\
						   if (INTGetFlag(INT_SOURCE_UART_RX(UART##X)))\
						   {\
						       UART##X##_INST.RxBuf[UART##X##_INST.RxTail] = UARTGetDataByte(UART##X);\
							U##X##STAbits.OERR=false;\
							INTClearFlag(INT_SOURCE_UART_RX(UART##X));\
							if ( UART##X##_INST.RxBuf[UART##X##_INST.RxTail]=='#')\
						       {\
							   UART##X##_INST.packet.packet_complete=1;\
						       }\
						       if ( UART##X##_INST.RxBuf[UART##X##_INST.RxTail]=='>')\
						       {\
							   UART##X##_INST.RxTail =0;\
							   UART##X##_INST.packet.packet_complete=0;\
						       }else\
						       {   \
							   UART##X##_INST.RxTail++;\
						       }\
						       if (UART##X##_INST.RxTail>=RX_BUFFER_SIZE)\
						       {\
							   UART##X##_INST.RxTail=0;\
						       }\
						   }\
						  }

#define UART_STORE_RECIEVED_PACKAGE(X)      void uart##X##_store_packet(void)\
					    {\
					       if (UART##X##_INST.packet.packet_complete)\
					       {\
						   UART##X##_INST.RxTail=0;\
						   UART##X##_INST.packet.command=0;\
						   memset(UART##X##_INST.packet.packet_data,0,RX_BUFFER_SIZE);\
						   UART##X##_INST.packet.packet_complete =0;\
						   UART##X##_INST.packet.command= UART##X##_INST.RxBuf[0];\
						   memcpy(UART##X##_INST.packet.packet_data,  UART##X##_INST.RxBuf , strlen(UART##X##_INST.RxBuf ));\
						   /*memset(UART##X##_INST.RxBuf ,0,RX_BUFFER_SIZE);\*/\
						   UART##X##_INST.packet.available=1;\
					       }\
					   }\
						  

#define IS_PACKAGE_AVAILABLE(X)     char UART##X##_is_package_available(void)\
				    {\
					    return UART##X##_INST.packet.available;\
				    }\

/****************************************************************************************************************
*                                       DECLARARION                                                              *
*                                       DECLARARION                                                              *
*                                       DECLARARION                                                              *
 ****************************************************************************************************************/


UART_FUNCTION_DEC(1)
UART_FUNCTION_DEC(2)
UART_FUNCTION_DEC(3)
UART_FUNCTION_DEC(4)
UART_FUNCTION_DEC(5) 
//UART Functions:
void                initialize_UART_x(char UART_NUM,long int UART_Baud);

     


#endif /* __END_OF_FILE__ */
