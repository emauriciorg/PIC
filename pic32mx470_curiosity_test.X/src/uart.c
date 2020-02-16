
#include <xc.h>
#include <GenericTypeDefs.h>
#include <plib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include<p32xxxx.h>
#include "uart.h"

#ifdef __DEBUG_
char Debug_CMD;
#endif


void initialize_UART_x(char UART_NUM,long int UART_Baud)
{
    switch (UART_NUM)
    {

#ifdef __USE_UART1_
        case UART1:
                     UART_FUNCTION_INIT(1,4,3)
            break;
#endif
        case UART2:
#ifdef __USE_UART2_
                    UART_FUNCTION_INIT(2,4,2)

            break;
#endif
#ifdef __USE_UART3_
        case UART3:
                    UART_FUNCTION_INIT(3,4,1)
            break;
#endif
#ifdef __USE_UART4_
        case UART4:
                    UART_FUNCTION_INIT(4,2,0)
        break;
#endif
#ifdef __USE_UART5_
        case UART5:
                    UART_FUNCTION_INIT(5,4,0)
            break;
#endif
#ifdef __USE_UART6_

        case UART6:

                    UART_FUNCTION_INIT(6,1,0)

            break;
#endif /* __USE_UART6_ */
        default:
            break;
    }

}

#ifdef __USE_UART1_

char u8_toggle = 0;
                         UART_FUNCTION_ISR(1,4)

#endif /* __USE_UART1_ */

#ifdef __USE_UART2_
                       UART_FUNCTION_ISR(2,4)
#endif

#ifdef __USE_UART3_
                        UART_FUNCTION_ISR(3,4)
#endif

#ifdef __USE_UART4_
              //          UART_FUNCTION_ISR(4,2)
#endif

#ifdef __USE_UART5_
                        UART_FUNCTION_ISR(5,4)
#endif




#ifdef __USE_UART1_ // UART1

/*********************UART1 FUNCTIONS*******************************/
UART_FUNCTION_WRITE_CHAR(1)
UART_FUNCTION_WRITE_STRING(1)
UART_FUNCTION_GET(1)
UART_FUNCTION_CLEAR_VARIABLES(1)
UART_FUNCTION_GET_RX_LENGTH(1)
UART_FUNCTION_RECIEVE_DATA_NOT_ISR(1)
UART_STORE_RECIEVED_PACKAGE(1)
IS_PACKAGE_AVAILABLE(1)

#endif /* __USE_UART1_ */



#ifdef __USE_UART2_
/*********************UART2 FUNCTIONS*******************************/
UART_FUNCTION_WRITE_CHAR(2)
UART_FUNCTION_WRITE_STRING(2)
UART_FUNCTION_GET(2)
UART_FUNCTION_CLEAR_VARIABLES(2)
UART_FUNCTION_GET_RX_LENGTH(2)
 UART_FUNCTION_RECIEVE_DATA_NOT_ISR(2)
UART_STORE_RECIEVED_PACKAGE(2)
IS_PACKAGE_AVAILABLE(2)

#endif

#ifdef __USE_UART3_
/*********************UART3 FUNCTIONS*******************************/
UART_FUNCTION_WRITE_CHAR(3)
UART_FUNCTION_WRITE_STRING(3)
UART_FUNCTION_GET(3)
UART_FUNCTION_CLEAR_VARIABLES(3)
UART_FUNCTION_GET_RX_LENGTH(3)
UART_FUNCTION_RECIEVE_DATA_NOT_ISR(3)
UART_STORE_RECIEVED_PACKAGE(3)
IS_PACKAGE_AVAILABLE(3)

#endif /* __USE_UART3_ */

#ifdef __USE_UART4_
/*********************UART3 FUNCTIONS*******************************/
UART_FUNCTION_WRITE_CHAR(4)
UART_FUNCTION_WRITE_STRING(4)
UART_FUNCTION_GET(4)
UART_FUNCTION_CLEAR_VARIABLES(4)
UART_FUNCTION_GET_RX_LENGTH(4)
UART_FUNCTION_RECIEVE_DATA_NOT_ISR(4)
UART_STORE_RECIEVED_PACKAGE(4)
IS_PACKAGE_AVAILABLE(4)
#endif /* __USE_UART4_ */

#ifdef __USE_UART5_
/*********************UART5 FUNCTIONS*******************************/
UART_FUNCTION_WRITE_CHAR(5)
UART_FUNCTION_WRITE_STRING(5)
UART_FUNCTION_GET(5)
UART_FUNCTION_CLEAR_VARIABLES(5)
UART_FUNCTION_GET_RX_LENGTH(5)
UART_FUNCTION_RECIEVE_DATA_NOT_ISR(5)
UART_STORE_RECIEVED_PACKAGE(5)
IS_PACKAGE_AVAILABLE(5)
#endif /* __USE_UART6_ */


#ifdef __DEBUG_
//---------------------------------------------------------------------------------------------------------------------------------------------
void _mon_putc(char c)
{
    while(!UARTTransmitterIsReady(__debug_port_));
    UARTSendDataByte(__debug_port_, c);
    while(!UARTTransmissionHasCompleted(__debug_port_));

}
#ifdef __DEBUG_
#ifndef PRINT_STDIO
void send_debug_msg(char* str)
{
    while(*str != '\0')
    {
        while(!UARTTransmitterIsReady(__debug_port_));
        UARTSendDataByte(__debug_port_, *str);
        str++;
        while(!UARTTransmissionHasCompleted(__debug_port_));
    }
}
#endif
#endif
char uart_get_command(void)
{
    return Debug_CMD;
}


#endif

unsigned int integer_pow(int x, int n)
{
    unsigned int r = 1;
    while (n--)
    r *= x;
    return r;
}
