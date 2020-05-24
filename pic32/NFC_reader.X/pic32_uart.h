/* 
 * File:   uart.h
 * Author: user
 *
 * Created on May 31, 2017, 12:01 PM
 */

#ifndef _PIC32_UART_H
#define	_PIC32_UART_H

#ifndef SYS_FREQ
#define SYS_FREQ			(96000000UL)
#endif 
#ifndef PBCLK_FREQUENCY
#define PBCLK_FREQUENCY		(96 * 1000 * 1000)
#endif


#define U1RxBufSize 64
#define U1TxBufSize 64

extern unsigned char U1TxBuf[U1TxBufSize];
extern unsigned char U1RxBuf[U1RxBufSize];
extern unsigned char U1Unread;

#define U2RxBufSize 256
#define U2TxBufSize 256

extern unsigned char U2TxBuf[U2TxBufSize];
extern unsigned char U2RxBuf[U2RxBufSize];
extern unsigned char U2Unread;
void f_init_UARTS();
void UART1_init(unsigned long int UART_Baud);
void UART1_write_string(const char *string);
void UART1_write_char(const char ch);

void UART2_write_string_1(const char *string,int length);
void UART1_write_string_1(const char *string,int length);


void UART1_reset_rx_buffer(void);
unsigned char UART1_is_unread(void);
void UART1_clear_unread(void);


unsigned char U1DataAvailable();
unsigned char U2DataAvailable();
unsigned char U1ClearDataAvailable();
unsigned char U2ClearDataAvailable();

void UART2_init(UINT32  UART_Baud);
void UART2_write_string(const char *string);
void UART2_write_char(const char ch);

void UART2_reset_rx_buffer(void);
unsigned char UART2_is_unread(void);
void UART2_clear_unread(void);

#endif	/* UART_H */