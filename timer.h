#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdint.h>

#define TC0_ADDRESS 0x0044
#define TC0_INT_FLAG_REG_ADDRESS 0x0035
#define TC2_ADDRESS 0x00B0
#define TC2_INT_FLAG_REG_ADDRESS 0x0037

typedef struct __timer8_t {
  uint8_t controlA;
  uint8_t controlB;
  uint8_t counter;
  uint8_t outputCompareA;
  uint8_t outputCompareB;
} timer8_t;

// Delay in milliseconds
// Implementation for this function is in delay.c
void delay(uint16_t);

#endif
