#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "sys/ports.h"
#include "sys/apic.h"

#define IS_LETTER(sc) ((sc < 0x40) && (sc > 0xF))

/*
 * Defines the port numbers for the PS/2 keyboard.
 */
#define PS2_PORT_DATA			0x60
#define PS2_PORT_STATUS			0x64
#define PS2_PORT_COMMAND 		0x64

#define PS2_CON_TEST_PASSED 	0x55
#define PS2_PORT_TEST_PASSED 	0x00

/*
 * PS2 Commands.
 */
#define PS2_CMD_SCAN_CODE	 	0xF0
#define PS2_CMD_ENABLE 			0xF4
#define PS2_CMD_DISABLE 		0xF5

/*
 * PS2 Command responses.
 */
#define PS2_RES_ACK 			0xFA
#define PS2_RES_RESEND 			0xFE
#define PS2_RES_NONE			0x00

#define PS2_STATUS_INPUT 		(1 << 1)
#define PS2_STATUS_OUTPUT 		(1 << 0)

/*
 * Defines the port numbers and commands for the PICs.
 */
#define PIC1			0x20
#define PIC2			0xA0
#define INT_END			0x20

#define OUT_BUFF 		1
#define IS_DATA(S) (S & OUT_BUFF)

/*
 * Masks used to mask scancode depending on keyboard state.
 */

// |    0    |    1    |    2    |    3    |
//    shift    released  numlock   scrllock

#define SHIFT_DOWN 0x2

/*
 * Used to mask new scan codes to find various information.
 */
#define GET_ROW(S) ((S >> 5) & 0x7)
#define GET_COL(S) (S & 0x1F)
#define IS_RELEASED(S) ((S >> 0x8) & 0x1)
#define IS_SHIFTED(S) ((S >> 0x9) & 0x1)

/*
 * Declares the public interface functions.
 */
void keyboard_init(void);
void keyboard_handler(void);
char * poll_keyboard(void);

#endif