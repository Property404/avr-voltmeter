#include "timer.h"
#include "portio.h"
#include "servo.h"
#include <stdlib.h>

volatile io_port_t* portb = (io_port_t*)PORT_B_ADDRESS;
volatile io_port_t* portd = (io_port_t*)PORT_D_ADDRESS;

int main()
{
	servo_init(portb, 0);
	servo_set(64);
	servo_run(NULL);
}
