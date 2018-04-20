#include "timer.h"
#include "portio.h"

volatile io_port_t* portd = (io_port_t*)PORT_D_ADDRESS;

int main()
{
	portd->ddr = 0x04;
	portd->dataout = 0x04;
	while(1)
	{
		//toggle
		portd->datain = 0x04;
		delay(500);
	}
}
