#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "sys/ports.h"
#include "sys/apic.h"

/*
 * Defines the port numbers for the PS/2 keyboard.
 */
#define PS2_PORT_DATA		0x60
#define PS2_PORT_STATUS		0x64
#define PS2_PORT_COMMAND 	0x64

#define PS2_CON_TEST_PASSED 	0x55
#define PS2_PORT_TEST_PASSED 	0x00

/*
 * Defines the port numbers and commands for the PICs.
 */
#define PIC1			0x20
#define PIC2			0xA0
#define INT_END			0x20

#define OUT_BUFF 		1
#define IS_DATA(S) (S & OUT_BUFF)

/*
 * Declares the public interface functions.
 */
void keyboard_init(void);
void keyboard_handler(void);

#endif