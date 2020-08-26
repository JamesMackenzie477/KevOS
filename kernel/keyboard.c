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
	uint8_t scan_code = __read_port(0x60);
	// Converts the scan code.
	kprintf("scan_code: %s\n", mapping[scan_code]);
}