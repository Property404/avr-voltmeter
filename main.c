#include "portio.h"
#include "servo.h"
#include "adc.h"
#include <stdlib.h>
#include <stdbool.h>

volatile io_port_t* portb = (io_port_t*)PORT_B_ADDRESS;
volatile io_port_t* portd = (io_port_t*)PORT_D_ADDRESS;

int main()
{
	portb->ddr = 0x03;
	portb->dataout = 0x00;
	adc_init();

	while(true)
	{
		uint8_t value = (adc_read() >> 8);
		portb->dataout = value;
	}
}

/*
void callback(void)
{
	static uint16_t old_value = 0;
	uint16_t value = adc_read();
	if(old_value != value)
	{
		servo_set((uint8_t)(value>>2));
		old_value = value;
	}

	*/
/*
	static uint8_t a=0;
	static uint8_t s=0;
	a++;
	if(a == 0 || a==128)
	{
		s++;
		servo_set(s);
	}
	*/
/*
}

	

int main()
{
	adc_init();
	servo_init(portb, 0);
	servo_set(0);
	servo_run(callback);
}
*/
