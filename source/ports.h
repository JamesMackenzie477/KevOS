#ifndef _PORTS_H
#define _PORTS_H

#include "stdio.h"

/*
 * Allows interaction with processor ports via assembly functions. 
 */
extern uint8_t __read_port(uint16_t);
extern void __write_port(uint16_t, uint8_t);

#endif