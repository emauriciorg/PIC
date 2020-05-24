/** 
******************************************************************************
* \file    cli.c
* \brief    Entry point file.

******************************************************************************
*/
/* 
	implementation of a cli like parser 
	mainly used for debuggin purposes, to tranfers data a simple
	raw string can be applied
*/
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common_structs.h"
#include "command_list.h"

/*your fancy MCU headers goes here :*/
#include <xc.h>
#include <plib.h>
#include "pic32_uart.h"
#include "pic32_timers.h"

#include "spi.h"

#define CLI_DEBUG_ACTIVE
/*macros to map the whole gpios on the MCU TBD*/
#define GPIO_SET(GPIO_NUMBER) 
#define GPIO_CLEAR(GPIO_NUMBER) 

#ifdef CLI_DEBUG_ACTIVE
	#define CLI_OUT(...)  printf(__VA_ARGS__)
#else
	#define CLI_OUT(...)
#endif

#define PRIME_NUMBER_FOR_LONG_HASH 1009     
#define PRIME_NUMBER_FOR_SHORT_HASH 167
#define MAX_COMMAND_SIZE 20
#define COMMAND_LEVELS  4

uint16_t cli_get_hash (char *string, uint16_t prime_number){
	char  len=strlen(string);
	char  i;
	uint16_t hash=0;
	for (i=0;i<len;i++ ){
		hash+= (string[i]*(i+1)); 	
	}
	hash=hash%prime_number;	
	CLI_OUT("[%s][%x]  ",string,hash );
	return hash;
}

uint8_t cli_find_char(char *string){
	
	char *pch;
	pch = (char *)memchr(string,' ',strlen(string));
	
	if (pch) return pch-string+1;
	
	pch = (char *) memchr(string,'\r',strlen(string));
	
	if (pch) return pch-string+1;

	return 0;
}


uint16_t cli_get_command_id(char * string, uint8_t *index, uint16_t prime_number){
	
	char tmp_command[20];
	memset(tmp_command,0,20);
        
	*index= cli_find_char(string);
	
	if (!(*index)){
		CLI_OUT("\nWhat are you even typing?\n");
		return 0;
	}
	memcpy(tmp_command, string, (*index)-1 );
 	
 	return  cli_get_hash(tmp_command, prime_number);
}



void cli_gpio_handle(uint16_t *gpio_command){
	if (gpio_command[0] == cmd_gpio_hi){
		GPIO_SET(gpio_command[1]);
	}
	if (gpio_command[0] == cmd_gpio_lo){
		GPIO_CLEAR(gpio_command[1]);
	}
}


uint8_t cli_ascii_charhex_to_hex( char  hex_character){
	
	if ( hex_character <= 'F' && hex_character >= 'A') return (hex_character -'A')+10;

	if ( hex_character <= 'f' && hex_character >= 'a') return (hex_character -'f')+10;

	if ( hex_character <= '9' && hex_character >= '0') return (hex_character -'0');

	return 0;
}


uint16_t cli_ascii_streamhex_to_hex(char *stream_pointer, uint8_t stream_length){
	uint32_t hex_result=0;
	while(stream_length &&  ( (stream_pointer[stream_length]) != 0) ){
		hex_result= ( hex_result * 0x10	) + ( cli_ascii_charhex_to_hex(*stream_pointer));
		stream_pointer++;
		stream_length--;
	}
	return hex_result;
}

uint8_t cli_parse_debug_command(char *argv)
{
	
	uint8_t index=0;
	uint16_t hex2dec_result;
	uint16_t command_id[ COMMAND_LEVELS ];
	memset(command_id,0,sizeof(command_id));
	
	command_id[0]= cli_get_command_id(argv, &index, PRIME_NUMBER_FOR_LONG_HASH);
	argv+=index;
	
	switch (command_id[0]){

	case cmd_help:		/*to do: list commands base  using stringizer*/		
				CLI_OUT("\n____________command list____________\n\n ");
				CLI_OUT("turn\t\tgpio\t\tsend\t\tcip\n");
				break;

	case cmd_clear: 	for(index=0;index<28;index++)CLI_OUT("\n\n");	
				break;

       	case cmd_cmdtest:	/*to do , list using argc*/
				printf("argv [%c] argv [%c] argv [%c]\n",argv [0],argv [1],argv [2]);
				break;

	case cmd_hex2dec:	command_id[0]=cli_ascii_streamhex_to_hex(argv, strlen(argv)-1);
				printf("result [%x][%d] \n",command_id[0],command_id[0]  );
				break;

	case cmd_accinit:	//accelerometer_on_start_configuration();
				break;

	case  cmd_adc:		
				CLI_OUT ("ADC1 is %d\n",  pic32_adc_read_channel(0));
				break;

	case cmd_pwm:		hex2dec_result=cli_ascii_streamhex_to_hex(argv, strlen(argv)-1);
				pic32_set_pwm(hex2dec_result,50);
        			break;

        case cmd_duty:		hex2dec_result = cli_ascii_streamhex_to_hex(argv, strlen(argv)-1);
        			CLI_OUT("\nduty set to %d",hex2dec_result);
				SetDCOC3PWM(hex2dec_result);	
				break;

	case cmd_spi_send :    CLI_OUT("Sending spi command \n");
				matrix_led_shutdown_mode();
				break;
	case cmd_spip : 
				matrix_display_test();
	//			spi_send_command();
				break;
	
	case cmd_servo: 	servo_set_timeout(15);
				break;
	default:	
				CLI_OUT("unknow command\n");
				break;
	}
	return 0;
}

void cli_execute_debug_command(void){
	
	if (!pic32_pending_debug_packet()) return;
	cli_parse_debug_command( pic32_get_debug_packet() );
	pi32_flush_debug_packet();
}

/*TODO : define is I need to extract arg outsite commmands -n*/
uint32_t extract_parameters(uint8_t *text_stream){
	uint32_t dec_result = 0;

	while ( ((*text_stream) > '0') && ( (*text_stream) < '9') ){
		dec_result = ((*text_stream)-'0') + (dec_result *10);
		text_stream++;
	}
	return dec_result;

}

