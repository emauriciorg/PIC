#ifndef __CONFIGURATION_BITS_H__
#define __CONFIGURATION_BITS_H__

// USERID = No Setting
/*#pragma config FSRSSEL   = PRIORITY_7  // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY  = OFF         // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY   = OFF         // Peripheral Pin Select Configuration (Allow multiple reconfigurations)
#pragma config FUSBIDIO  = ON          // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON          // USB VBUS ON Selection (Controlled by USB Module)
*/
// DEVCFG2
#pragma config FPLLIDIV  = DIV_5       // PLL Input Divider (5x Divider)
#pragma config FPLLMUL   = MUL_24      // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV  = DIV_12      // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN    = OFF         // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV  = DIV_1       // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC     = PRIPLL      // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN   = OFF         // Secondary Oscillator Enable (Disabled)
#pragma config IESO      = OFF         // Internal/External Switch Over (Disabled)
#pragma config POSCMOD   = HS          // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC  = OFF         // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV    = DIV_1       // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM     = CSDCMD      // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS     = PS1048576   // Watchdog Timer Postscaler (1:1048576)
//#pragma config WINDIS    = OFF         // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN    = OFF         // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
//#pragma config FWDTWINSZ = WINSZ_25    // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config DEBUG     = OFF         // Background Debugger Enable (Debugger is Disabled)
//#pragma config JTAGEN    = OFF         // JTAG Enable (JTAG Disabled)
#pragma config ICESEL    = ICS_PGx1    // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP       = OFF         // Program Flash Write Protect (Disable)
#pragma config BWP       = OFF         // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP        = OFF         // Code Protect (Protection Disabled)      

#if 0


// PIC32MX440F256H Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)

// DEVCFG2
#pragma config FPLLIDIV = DIV_5         // PLL Input Divider (5x Divider)
#pragma config FPLLMUL = MUL_24         // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (ICE EMUC1/EMUD1 pins shared with PGC1/PGD1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#endif
#endif
