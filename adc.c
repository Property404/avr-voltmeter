#include "adc.h"



volatile adc_t *adcs = (adc_t*)0x0078;
volatile uint8_t* PRR = (uint8_t*) 0x64;

// Set up ADC
void adc_init(void)
{
	*PRR = 0x00;
	adcs->ADCSRA = 0x87;
	adcs->ADMUX = 0x40;
}

// Read in form of a 10-bit value
// (Of course, extended to 16-bit)
uint16_t adc_read(void)
{
	adcs->ADCSRA |=
		0x50;
	while((adcs->ADCSRA &
				0x10) == 0);

	// Low value has to be read first
	// according to data sheet
	uint8_t value_low = adcs->ADCL;
	uint16_t value_high = adcs->ADCH & 0x03;
	value_high<<=8;
	return value_high+value_low;
}