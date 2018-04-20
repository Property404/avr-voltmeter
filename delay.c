#include "timer.h"

static void delay_25us()
{
  volatile uint8_t *timer_interrupt_flag=(uint8_t *) TC2_INT_FLAG_REG_ADDRESS;
  volatile timer8_t *timer=(timer8_t *)TC2_ADDRESS;
  timer->counter=245;
  timer->controlA=0x00;
  timer->controlB=0x03;
  while((*timer_interrupt_flag&0x01)==0);
  timer->controlB=0x00;
  *timer_interrupt_flag=(*timer_interrupt_flag)|0x01;
}

void delay(uint16_t x)
{
  uint16_t i;
  x*=40;
  for (i=0;i<x;i++) delay_25us();
}
