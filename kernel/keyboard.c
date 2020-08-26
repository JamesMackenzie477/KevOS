#include "keyboard.h"

/*
 * Mapping table for the scan codes.
 */
static char * mapping[200] = { 0 };

/*
 * Initialises the keyboard driver.
 */
void keyboard_init(void)
{
	mapping[0x1c] = "ENTER";
	mapping[0x9c] = "ENTER";
}

/*
 * Should be called upon a key press interrupt.
 * Handles the key press.
 */
void keyboard_handler(void)
{
	keyboard_init();
	// Reads the scan code.
	uint8_t scan_code = __read_port(PORT_DATA);

	// Converts the scan code.
	kprintf("%s ", mapping[scan_code]);

	// Marks the interrupt as complete.
	// This will be a part of the (A)PIC interface in the future.
	__write_port(PIC1, INT_END);
}