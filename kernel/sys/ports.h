#ifndef _PORTIO_H
#define _PORTIO_H

#include "../stdio.h"

/*
 * Allows interaction with processor ports via assembly functions. 
 */
extern uint8_t __read_port(uint16_t);
extern uint8_t __write_port(uint16_t, uint16_t);

#endif