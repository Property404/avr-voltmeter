#ifndef __ADC_H__
#define __ADC_H__
#include <stdint.h>

typedef struct adc{
	uint8_t ADCL;
	uint8_t ADCH;
	uint8_t ADCSRA;
	uint8_t ADCSRB;
	uint8_t ADMUX;
	uint8_t not_used;
	uint8_t DIDR0;
	uint8_t DIDR1;
}adc_t;
// Set up ADC
void adc_init(void);


// Read in form of a 10-bit value
// (Of course, extended to 16-bit)
uint16_t adc_read(void);
#endif
