#include "timer.h"
#include "portio.h"
#include "servo.h"
#include <stdlib.h>

volatile io_port_t* portb = (io_port_t*)PORT_B_ADDRESS;
volatile io_port_t* portd = (io_port_t*)PORT_D_ADDRESS;

void callback(void)
{
	static uint8_t a=0;
	static uint8_t s=0;
	a++;
	if(a == 0 || a==128)
	{
		s++;
		servo_set(s);
	}
}

	

int main()
{
	servo_init(portb, 0);
	servo_set(205);
	servo_run(NULL);
}
