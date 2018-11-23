#include "pic32_uart.h"

#ifdef __DEBUG_
	char Debug_CMD;
#endif


void pic32_uart_initialize(uint8_t UART_NUM,unsigned long UART_Baud){
	
	switch (UART_NUM){
	
	case UART1:
		#ifdef __USE_UART1_
		UART_FUNCTIONS_INIT(1,4,3);//validate TRHOUGH MACROS
		UART_PIN_SETUP(PORTD,BIT_2,BIT_3);
		#endif
		break;
	case UART2:
		#ifdef __USE_UART2_
		UART_FUNCTIONS_INIT(2,3,2);
		UART_PIN_SETUP(PORTF,BIT_4,BIT_5);
		#endif
		break;
#ifdef UART_PLIB_CONFLICT_SOLVE
	case UART3:
		#ifdef __USE_UART3_
		UART_FUNCTIONS_INIT(3,4,1);
		#endif
		break;
	case UART4:
		#ifdef __USE_UART4_
		UART_FUNCTIONS_INIT(4,2,0)
		#endif
		break;
	case UART5:
		#ifdef __USE_UART5_
		UART_FUNCTIONS_INIT(5,4,0);
		#endif
		break;
	case UART6:
		#ifdef __USE_UART6_
		UART_FUNCTIONS_INIT(6,1,0);
		#endif
		break;
#endif
	default:
		break;
	}
}

/*for pps use*/
void uart_set_pins(void){
	PPSUnLock;
	/* PPSInput(4,U2RX,RPF4); */
	/* PPSOutput(3,RPf5,U2TX);*/
	PPSLock;
}


#ifdef __USE_UART1_ // UART1 

	st_uart_set UART1_INST;
	UART_FUNCTION_ISR(1,4)
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
	st_uart_string uart2_instance;
	#ifdef UART2_IS_DEBUG_PORT
	#else
	UART_FUNCTION_ISR(2,4)
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
#endif

#ifdef __USE_UART3_
	#warning "__USE_UART3_ no implemented!"
	st_uart_set UART3_INST; 
	UART_FUNCTION_ISR(3,4)
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
	#warning "__USE_UART4_ no implemented!"
	st_uart_set UART4_INST;
	UART_FUNCTION_ISR(4,2)
	/*********************UART4 FUNCTIONS*******************************/
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
	#warning "__USE_UART5_ no implemented!"
	st_uart_set UART5_INST;
	UART_FUNCTION_ISR(5,4)
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
void _mon_putc(char c){
	while(!UARTTransmitterIsReady(__debug_port_));
	UARTSendDataByte(__debug_port_, c);
	while(!UARTTransmissionHasCompleted(__debug_port_));
}

#ifndef PRINT_STDIO
void DEBUG_MSG(char* str){
	while(*str != '\0'){
		while(!UARTTransmitterIsReady(__debug_port_));
		UARTSendDataByte(__debug_port_, *str);
		str++;
		while(!UARTTransmissionHasCompleted(__debug_port_));
	}
}
#endif

char uart_get_command(void){
	return Debug_CMD;
}


void __ISR(_UART_2_VECTOR, IPL4AUTO) IntUart2Handler(void){
	if (INTGetFlag(INT_SOURCE_UART_RX(UART2) )){
		uart2_instance.in_stream[uart2_instance.tail++] = UARTGetDataByte(UART2);
		INTClearFlag(INT_SOURCE_UART_RX(UART2));    
		pic32_uart2_check_stream(&uart2_instance);
	}                         
	
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) ){
		INTClearFlag(INT_SOURCE_UART_TX(UART2));
	}
}                                 


void pic32_uart2_check_stream(st_uart_string *uart_instance){

	char len = strlen(uart_instance->in_stream);
	char *pch = (char *)memchr(uart_instance->in_stream,'\n',len);
	
	if (pch){
   	     	uart_instance->in_stream[len-1]  = false;
		uart_instance->pending_parse     = true;
		uart_instance->tail              = false; 	
	}else{
		uart_instance->pending_parse =false;
	}

	if ( uart_instance->tail > UART_STRING_MAX_SIZE)
		uart_instance->tail       =false; 	
}

char pic32_pending_debug_packet(void){
	if(!uart2_instance.pending_parse){ 	 
		return false;
	}
	uart2_instance.pending_parse = false;
	return true;	
}

char   *pic32_get_debug_packet(void){
	return 	&(uart2_instance.in_stream[0]);
}

void pi32_flush_debug_packet(void){
	memset(&uart2_instance.in_stream[0],0,sizeof(st_uart_string));
}


#endif 

