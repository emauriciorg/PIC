/*
 * File:   main.c
 * Author: mauri
 *
 * Created on April 12, 2018, 6:12 PM
 */


#include <string.h>
#include "main.h"
extern unsigned char U1TxBuf[U1TxBufSize];
extern unsigned char U1RxBuf[U1RxBufSize];
extern unsigned char U1Unread;

extern unsigned char U2TxBuf[U2TxBufSize];
extern unsigned char U2RxBuf[U2RxBufSize];
extern unsigned char U2Unread;
extern unsigned int	 U2RxHead,U2RxTail;


#define DELAY_RANDOM 3000000
#define RXbuffLen 24

int tempUART;
char buf[10];
char uartRXbuffer[RXbuffLen];
int tempRX=0;
char received;
unsigned int stopwatch;

unsigned char wake[24]={0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x03,0xfd,0xd4,0x14,0x01,0x17,0x00}; //dummy 0x55 and 0x00 for time wake up = samconfiguration 0x00 0xFF (always present) ;see p.28 AN141520 p532
                                                                                                                                                   // 0x00 0xFF (always present); LEN=0x03; (3 byte da inviare); LCS=256-LEN=256-3=253=0xFD; TFI=0xD4 (SEND COMMAND); 0x14 SAMAConfiguration, 0x01 Mode normal; 0x17 DCS=256-212(d4)-20(0x14)-1=0x17 ignored default; 0x00 End Postable byte
unsigned char WakeIt[]={0x55,0x55,0x00,0x00,0x00};

unsigned char firmware[9]={0x00,0x00,0xFF,0x02,0xFE,0xD4,0x02,0x2A,0x00}; // 00 preamble; 00 ff always present; 02 byte, 256-2=254=fe; d4 command; 02 firmware command page77; 2a PDCS=256-TFi=PD0-..PDn=256-212(d4)-2=42(2A)210; 00 postamble
unsigned char CommandTp[10]={0x00,0x00,0xff,0x00,0xff,0x00};


// PN532 Commands
#define PN532_COMMAND_DIAGNOSE (0x00)
#define PN532_COMMAND_GETFIRMWAREVERSION (0x02)
#define PN532_COMMAND_GETGENERALSTATUS (0x04)
#define PN532_COMMAND_READREGISTER (0x06)
#define PN532_COMMAND_WRITEREGISTER (0x08)
#define PN532_COMMAND_READGPIO (0x0C)
#define PN532_COMMAND_WRITEGPIO (0x0E)
#define PN532_COMMAND_SETSERIALBAUDRATE (0x10)
#define PN532_COMMAND_SETPARAMETERS (0x12)
#define PN532_COMMAND_SAMCONFIGURATION (0x14)
#define PN532_COMMAND_POWERDOWN (0x16)
#define PN532_COMMAND_RFCONFIGURATION (0x32)
#define PN532_COMMAND_RFREGULATIONTEST (0x58)
#define PN532_COMMAND_INJUMPFORDEP (0x56)
#define PN532_COMMAND_INJUMPFORPSL (0x46)
#define PN532_COMMAND_INLISTPASSIVETARGET (0x4A)
#define PN532_COMMAND_INATR (0x50)
#define PN532_COMMAND_INPSL (0x4E)
#define PN532_COMMAND_INDATAEXCHANGE (0x40)
#define PN532_COMMAND_INCOMMUNICATETHRU (0x42)
#define PN532_COMMAND_INDESELECT (0x44)
#define PN532_COMMAND_INRELEASE (0x52)
#define PN532_COMMAND_INSELECT (0x54)
#define PN532_COMMAND_INAUTOPOLL (0x60)
#define PN532_COMMAND_TGINITASTARGET (0x8C)
#define PN532_COMMAND_TGSETGENERALBYTES (0x92)
#define PN532_COMMAND_TGGETDATA (0x86)
#define PN532_COMMAND_TGSETDATA (0x8E)
#define PN532_COMMAND_TGSETMETADATA (0x94)
#define PN532_COMMAND_TGGETINITIATORCOMMAND (0x88)
#define PN532_COMMAND_TGRESPONSETOINITIATOR (0x90)
#define PN532_COMMAND_TGGETTARGETSTATUS (0x8A)

#define PN532_RESPONSE_INDATAEXCHANGE (0x41)
#define PN532_RESPONSE_INLISTPASSIVETARGET (0x4B)


#define PN532_MIFARE_ISO14443A (0x00)
//-----------------------------------------------------------------



//***************************PN532 commands*****************************************//

 void wake_card(void)
{//send wake[] to device
     UART1_write_string_1(wake,24);
}

 void firmware_version(void)
{//send fireware[] to device
    UART1_write_string_1(firmware,9);
}

 //***************************PN532 commands*****************************************//

void ClearBuffer() {
    unsigned char priv;
    for (priv = 0; priv < RXbuffLen; priv++) {
        uartRXbuffer[priv] = '0';
    }
}

void f_enable_interrupts(void){
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}

int main(void)
{
    	DisableWDT();
	INTDisableInterrupts();
    
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

        
        f_init_UARTS();

      //  pr_configure_timeout();
 
        f_enable_interrupts();
    
      __XC_UART = UART2;
    
        UART2_write_string("RFID\n");        
        
    
        while (1)
        {

                if (U2DataAvailable()){
                        U2Unread = 0;
                        switch(U2RxBuf[U2RxHead-1]){
                        case 'A':
                                UART2_write_string("Wake up\n");
                                UART2_write_string_1(wake,24);
                                UART1_write_string_1(wake,24);

                                break;
                        case 'B':
                                UART2_write_string_1(firmware,9);
                                UART2_write_string("Firmware\n");
                                UART1_write_string_1(firmware,9);
                        
                                break;
                      
                        case 'C':
                                UART2_write_string("CommandTp");
                                UART1_write_string_1(WakeIt,6);
                                
                                break;
                        case 'D':
                                UART2_write_string("CommandTp");
                                UART1_write_string_1(CommandTp,6);
                                
                                break;
                      
                            default:
                                    sprintf(U2TxBuf,"[unknow][%c]\n",U2RxBuf);
                                    UART2_write_string(U2TxBuf);
                            break;
                        }
                        memset( U2RxBuf,0,sizeof(U2RxBuf));
                        U2ClearDataAvailable();
                        
                }

                if (U1DataAvailable()){
                        U1Unread = 0;
                        UART2_write_string("RECIEVED");
                        UART2_write_string_1(U1RxBuf, 24);
                        memset( U1RxBuf,0,sizeof(U1RxBuf));
                        U1ClearDataAvailable();
                }

        }
        return 0;
}
        
        
                // if(uartRXbuffer[0] ==0x00) //response command
// {
// UART2_write_string_1('0'); //red LED on
// }
           
// if(uartRXbuffer[0] =='0')
// {
// LATBbits.LATB9=1; //red LED on
// }
// else
// {
// LATBbits.LATB9=0; //red LED off
// }
//// if(uartRXbuffer[13] == 'd')
//// {
// LATBbits.LATB4 = 0;
// }
// if(uartRXbuffer[13] == 'c')
// {
// LATBbits.LATB4 = 1;
// }
// if(uartRXbuffer[14] == 'f')
// {
// LATBbits.LATB0 = 0;
// }
// if(uartRXbuffer[14] == 'e')
// {
// LATBbits.LATB0 = 1;
// }
// if(uartRXbuffer[15] == 'h')
// {
// LATBbits.LATB10 = 0;
// }
// if(uartRXbuffer[15] == 'g')
// {
// LATBbits.LATB10 = 1;
// }
// ClearBuffer();
//
// Delay_ms(500); //for faster response you can decrease delay
//    }//while
