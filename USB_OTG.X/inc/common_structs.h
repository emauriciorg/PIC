#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

/*to do : define a good structure for serial comunication*/
#define UART_STRING_MAX_SIZE  32

typedef struct {
	char *ptr_stream;
	char  in_stream[UART_STRING_MAX_SIZE];
	char  out_stream[UART_STRING_MAX_SIZE+32];
	char  out_len;
	char  pending_parse;
	char  index;
	char  tail;
}st_uart_string; 


#endif /*COMMON_STRUCTS_H*/
