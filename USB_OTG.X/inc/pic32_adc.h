#ifndef __PIC32_ADC_H__
#define __PIC32_ADC_H__
#include <stdint.h>

void pic32_adc_initialize(unsigned long int analog_channels_to_enable );
uint16_t pic32_adc_read_channel(uint8_t buffer_index);
uint16_t pic32_adc_set_channel_setup(void);

#endif
