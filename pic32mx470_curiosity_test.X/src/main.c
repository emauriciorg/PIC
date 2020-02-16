

// PIC32MX470F512H Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config FSRSSEL = PRIORITY_7     // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_24         // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider (1x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRI           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (XT osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_50     // Watchdog Timer Window Size (Window Size is 50%)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is Disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>





#include <stdint.h>
#include <plib.h>
#include "uart.h"
#include <stdio.h>

#define  UART_STAT_BIT U2STAbits
#define  UART_TX_REGISTER U2TXREG

#define ONE_SECOND 0Xf00ff
void delay_tick(uint32_t delay_tick) {
	while(delay_tick-->0);
}

void main(void)
{

//SYS_FREQ
	SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

	TRISB = 0xFF;
	TRISE = 0xFF;

	 TRISBbits.TRISB2  = 0;
	 TRISBbits.TRISB3  = 0;
	 TRISBbits.TRISB10 = 0;

	 LATBbits.LATB2  = 1;
	 LATBbits.LATB3  = 1;
	 LATBbits.LATB10 = 1;
	__XC_UART = 2;

	 PORTSetPinsDigitalIn    (IOPORT_B, BIT_9);
	 PORTSetPinsDigitalOut   (IOPORT_E, BIT_5);



	//WriteString_UART_2("CURIOSITY BOARD\r\n");


	// UART2 , RPD2:Rx, RPD3:Tx, to Driver C

	PPSUnLock;
	PPSInput(1,U2RX,RPB9);
	PPSOutput(2,RPE5,U2TX);
	PPSLock;

	LATBbits.LATB2 =0X00;
	delay_tick(ONE_SECOND);
	LATBbits.LATB2 =0X01;
	initialize_UART_x(UART2,115200);

	while(0){
		LATBbits.LATB2 ^=0X01;
	}


	while(1){
		WriteString_UART_2(__DATE__" "__TIME__"\r\n");
		delay_tick(ONE_SECOND);
		LATBbits.LATB2 ^=0X01;
		delay_tick(ONE_SECOND);
		LATBbits.LATB2 ^=0X01;

		delay_tick(ONE_SECOND);
		LATBbits.LATB3 ^=0X01;
		delay_tick(ONE_SECOND);
		LATBbits.LATB3 ^=0X01;
		delay_tick(ONE_SECOND);

		LATBbits.LATB10 ^=0X01;
		delay_tick(ONE_SECOND);
		LATBbits.LATB10 ^=0X01;
		delay_tick(ONE_SECOND);

	}
}
