#ifndef __PORTIO_H__
#define __PORTIO_H__
#include <stdint.h>

#define PORT_B_ADDRESS 0x0023
#define PORT_C_ADDRESS 0x0026
#define PORT_D_ADDRESS 0x0029

typedef struct __io_port_t {
  uint8_t datain;
  uint8_t ddr;
  uint8_t dataout;
} io_port_t;

#endif
