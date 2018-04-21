#include "portio.h"
#include "servo.h"
#include "adc.h"
#include <stdlib.h>
#include <stdbool.h>

volatile io_port_t* portb = (io_port_t*)PORT_B_ADDRESS;
volatile io_port_t* portd = (io_port_t*)PORT_D_ADDRESS;

void callback(void);

int main()
{
	// Intialize analog-to-digital conversion stuff
	adc_init();
	// Use portb, bit 0 for the servo
	servo_init(portb, 0);
	// Start at angle 0
	servo_set(255);
	// Run the callback continuously while maintaining the pulse
	servo_run(callback);

	// Never reach this point
	return 0;
}

void callback(void)
{
	// We compare to old value so we're not running servo_set() too much
	// Because we don't want to affect the PWM
	static uint16_t old_value = 0;
	uint16_t value = adc_read();

	if(value != ADC_NOT_READY && value != old_value)
	{
		// Map a 10-bit value to an 8-bit value
		servo_set((uint8_t)(value>>2));
		//servo_set(0);
		old_value = value;
	}
}
