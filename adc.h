#ifndef __ADC_H__
#define __ADC_H__
#include <stdint.h>

#define ADC_NOT_READY 0xFFFF

// Set up ADC
void adc_init(void);

// Read in form of a 10-bit value
// (Of course, extended to 16-bit)
// 
// If there's nothing to read yet, return all 1's
// This way, we don't take too many clock cycles on a slow read so we don't mess with PWM
uint16_t adc_read(void);
#endif
