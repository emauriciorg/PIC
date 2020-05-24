
/*!
   \file main.c
   \brief "this program uses custom function allocation to jump to specific  functions when the
   the memory is splitted , an example would be a bootloader, in where the application
   migth need to jump to the bootloader or get access to bootloader functions, since
   the app is often compiled independently from bootloader, there is no way to the app
   to know where those functions are(unless a object file is provided)"
   \author mauro r.
   \date 01/01/2020
*/
/****************************************************************************************
*  @CUSTOM ALLOCATED FUNCTIONS
*  @Description: test of the custom allocated function
 *
 * TO DO: find the way to returning back from the function
 * the following warnings doesn't appear with compiler v1.43
 * main.c:47:1: warning: 'region' attribute directive ignored
 * main.c:70:1: warning: 'region' attribute directive ignored
 *
*****************************************************************************************/

#include <stdint.h>

#define RETURNING_TO_MAIN_FUNCTION_USING_FLAG

#define FUNCTION_SHOW_ADDRESS	   0x9D018000
#define MAIN_ADDRESS	0x9D01C000

#pragma region name="function_show"   origin = 0x9D018000 size = 0x2000
#pragma region name="function_main"   origin = 0x9D01C000 size = 0x5000


uint8_t  memory_flag = 0;

/*!
   \brief routine that passes control to a custom allocated function in memory
   \param "Address of the custom allocated function"
   \pre "the custom allocated function shall be defined"
   \post "no jump back is ensured, since the control is given to the custom function"
   \return "none"
*/
void jump_to_custom_function(unsigned long custom_allocated_function_address)
{
	void (*fptr)(void);
	fptr = (void (*)(void))custom_allocated_function_address;
	fptr();

}

int __attribute__((far, region("function_show"))) foo()
{
	sprintf(U1TxBuf,"I am a custom allocated function ");
	UART2_write_string(U1TxBuf);
#ifdef RETURNING_TO_MAIN_FUNCTION_USING_FLAG
	jump_to_custom_function( MAIN_ADDRESS ) ;
#endif
	return 0;
}


void f_enable_interrupts(void){
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableInterrupts();
}


/*main is put into a know location, so bootloader or other function can jump to it
just by calling through a pointer*/
int __attribute__((far, region("function_main"))) main()
{

	f_init_UARTS();
	f_enable_interrupts();

	sprintf(U1TxBuf,"PIC Init... \r\n");
	UART2_write_string(U1TxBuf);

#ifdef RETURNING_TO_MAIN_FUNCTION_USING_FLAG
	if(memory_flag==0)
	{
		memory_flag = 1;
		jump_to_custom_function(FUNCTION_SHOW_ADDRESS);
	}
#else
   	jump_to_custom_function(FUNCTION_SHOW_ADDRESS);
#endif
	//TO DO : well defined memory regions to allow a returning to main program without drawbacks or catch
	// the pointer before jumping to the custom allocated function

 	sprintf(U1TxBuf,"back from custom allocated function");
 	UART2_write_string(U1TxBuf);

 	while (1);

	return 0;
}
