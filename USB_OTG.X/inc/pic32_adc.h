#ifndef __PIC32_ADC_H__
#define __PIC32_ADC_H__


void pic32_adc_initialize(unsigned long int analog_channels_to_enable );
unsigned int pic32_adc_read_channel(unsigned char buffer_index);
unsigned int pic32_adc_set_channel_setup(void);

#endif
