/* Dagan Martinez
 * EEL4746C Section 1
 * Florida Polytechnic University
 * 2018-04-21
 *
 * This code is part of an "analog" voltmeter
 * Voltage is read through analog pin 0. That voltage is mapped from 0-Vcc to
 * 0-180 degrees as the servo position. A voltage of zero positions the servo
 * at 0 degrees; a voltage of Vcc positions the servo at 180 degrees
 *
 * The servo is connected to VCC, ground, and Port B0 (Digital pin 8)
 */

#include "portio.h"
#include "servo.h"
#include "adc.h"
#include <stdlib.h>

volatile io_port_t* portb = (io_port_t*)PORT_B_ADDRESS;

/* Each time this is run(which is continuously), this checks if the voltage at
 * A0 has changed, if so, it adjusts the servo's position accordingly*/
void callback(void);

int main()
{
	// Intialize analog-to-digital conversion stuff
	adc_init();
	// Use portb, bit 0 for the servo
	servo_init(portb, 0);
	// Start at angle 0
	servo_set(0);
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

		old_value = value;
	}
}
