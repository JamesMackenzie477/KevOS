#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "stdio.h"

#define OUT_BUFF 1

#define IS_DATA(S) (S & OUT_BUFF)

extern uint8_t __read_port(uint16_t);

void keyboard_handler(void);

#endif