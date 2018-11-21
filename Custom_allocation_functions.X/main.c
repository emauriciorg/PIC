

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

vu16 vu16_led_green_millis;
vu8 turn_on_led_int = 0;

u8  memory_flag=0;
#define RETURNING_TO_MAIN_FUNCTION_USING_FLAG



#define FUNCTION_SHOW_ADDRESS       0x9D018000
#define MAIN_ADDRESS                0x9D01C000


#pragma region name="function_show"      origin=0x9D018000 size=0x2000
#pragma region name="function_main" origin=0x9D01C000 size=0x5000


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



int __attribute__((far, region("function_main"))) main()
{

 
  
    f_init_UARTS(); 
    f_enable_interrupts();
    
    sprintf(U1TxBuf,"PIC Init... \r\n");
    UART2_write_string(U1TxBuf);
    
    
        
#ifdef RETURNING_TO_MAIN_FUNCTION_USING_FLAG
    if(memory_flag==0)
    {   memory_flag=1;
    
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



