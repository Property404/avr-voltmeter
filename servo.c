#include "servo.h"
#include "timer.h"
#include <stdlib.h>
//Note: this servo uses TC0
// TC2 is used by delay() in delay.c
static volatile timer8_t* tc0 = (timer8_t*)0x0044;

// Min and max compare values of the servo
// Correspond to 0 to 180 degrees
#define SERVO_LOW 20
#define SERVO_HIGH 80

// This is the port we use for all our servo fuctions
// servo_init sets this (and performs other
// initializations)
static volatile io_port_t* servo_port = NULL;
static uint8_t servo_bit = 0;

// Perform initializations
// `port` is the port we're using
// (ie, port B, port D)
// `bit` is the specific bit we're looking at,
void servo_init(volatile io_port_t* port, uint8_t bit)
{
	servo_bit = bit;
	servo_port = port;
	servo_port->ddr = 1<<bit;

	// Start at 0 degrees
	tc0->outputCompareA = 20;//SERVO_LOW;

	// Select PWM Correct phase mode
	tc0->controlA = 0x81;

	// Set prescaler to 256
	tc0->controlB = 0x04;
}

// Set the position from a value from 0 to 255
void servo_set(uint8_t val)
{
	// Here we're mapping 0-255 to 20-80
	// (Without division!)
	val >>= 2;//now 0-64
	val += SERVO_LOW;// Now 20-84
	val -= 2;// Now 18-82

	// Take care of out-of-range vals
	if(val < SERVO_LOW) val = SERVO_LOW;
	if(val > SERVO_HIGH) val = SERVO_HIGH;

	tc0->outputCompareA = val;
}


// This is an infinite loop that controls the PWM
// for the servo. Additionally, it excutes a callback function when appropriate. (as to appear that the callback is continuously running)
void servo_run(void (*callback)(void))
{
	volatile uint8_t* TIFR0 = (uint8_t*) 0x0035;
	int compare = 0;
	while(1)
	{
		if (compare < 2)
			// Toggle
			servo_port->datain = (1<<servo_bit);
	
		/* Do what we need to do */
		if(callback != NULL)
			callback();

		// Poll
		// Mask for output compare A flag
		while((*TIFR0 & 0x02) == 0);
		// (Clear flag)
		*TIFR0 = 0x02;
		

		compare++;
		if(compare == 4) compare = 0;
	}
		
}
