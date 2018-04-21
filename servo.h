#ifndef __SERVO_H__
#define __SERVO_H__
#include "portio.h"
// Perform initializations
// `port` is the port we're using
// (ie, port B, port D)
// `bit` is the specific bit we're looking at,
void servo_init(volatile io_port_t* port, uint8_t bit);

// Set the position from a value from 0 to 255
void servo_set(uint8_t val);

// This is an infinite loop that controls the PWM
// for the servo. Additionally, it excutes a callback function when
// appropriate. (as to appear that the callback is continuously running)
void servo_run(void (*callback)(void));
#endif
