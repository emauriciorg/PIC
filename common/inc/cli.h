#ifndef _MICRO_CLI_H__
#define _MICRO_CLI_H__

#include "common_structs.h"
uint16_t cli_get_hash (char *string, uint16_t prime_number);

uint8_t cli_parse_debug_command(char *string);

void cli_execute_debug_command(void);


#endif
