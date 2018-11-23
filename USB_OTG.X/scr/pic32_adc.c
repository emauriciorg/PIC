#include "pic32_adc.h"
#include <xc.h>
#include <plib.h>
#include "hw_profile.h"
#include <proc/p32mx440f256h.h>


void pic32_adc_initialize(unsigned long int analog_channels_to_enable ){

	CloseADC10();// ensure the ADC is off before setting the configuration

	/*adc_config1 ->AD1CON1*/
	unsigned long int adc_config1 = 
			ADC_MODULE_ON      |
			ADC_FORMAT_INTG    |
			ADC_CLK_AUTO       |
			ADC_AUTO_SAMPLING_ON;
	
	/*adc_config2 ->AD1CON2*/
	unsigned long int adc_config2 = 
			ADC_VREF_AVDD_AVSS     |
			ADC_OFFSET_CAL_DISABLE |
			ADC_SCAN_OFF           |
			ADC_SAMPLES_PER_INT_2  |
			ADC_ALT_BUF_ON         |
			ADC_ALT_INPUT_ON;
	
	/*adc_config1 ->AD1CON3*/
	unsigned long int adc_config3 =
			ADC_SAMPLE_TIME_12      |
			ADC_CONV_CLK_INTERNAL_RC;

	/*adc_configport ->	AD1PCFG*/
	unsigned long int adc_configport = analog_channels_to_enable ;

	/*adc_configscan ->	AD1CSSL*/
	unsigned long int adc_configscan = SKIP_SCAN_ALL;

	pic32_adc_set_channel_setup();
	OpenADC10(adc_config1, adc_config2, adc_config3, adc_configport,adc_configscan ); 
	EnableADC10();

}

uint16_t pic32_adc_set_channel_setup(void){
	SetChanADC10(   ADC_CH0_NEG_SAMPLEA_NVREF | 
			ADC_CH0_POS_SAMPLEA_AN1);
}

uint16_t pic32_adc_read_channel(uint8_t buffer_index){
	// active_buffer = 8 * ((~ReadActiveBufferADC10() & 0x01));// with this function we get the active buffer
	return ReadADC10(buffer_index);
}
  

