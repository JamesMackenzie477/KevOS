#include "keyboard.h"

/*
 * Mapping table for the scan codes.
 */
static char * mapping[200] = { 0 };

static inline void keyboard_send_cmd(uint8_t cmd, uint8_t data)
{
	__write_port(PS2_PORT_COMMAND, cmd);
	if (!(__read_port(PS2_PORT_STATUS) & 1)) __write_port(PS2_PORT_DATA, data);	
}

static inline uint8_t keyboard_con(uint8_t cmd)
{
	__write_port(PS2_PORT_COMMAND, cmd);
	if (!(__read_port(PS2_PORT_STATUS) & 1)) return -1;
	return __read_port(PS2_PORT_DATA);
}

/*
 * Initialises the keyboard driver.
 */
void keyboard_init(void)
{
	if (keyboard_con(0xAA) != PS2_CON_TEST_PASSED) return;
	if (keyboard_con(0xAB) != PS2_PORT_TEST_PASSED) return;
	if (keyboard_con(0xA9) != PS2_PORT_TEST_PASSED) return;

	kprintf("Test passed.\n");

	keyboard_send_cmd(0xD1, 0xF5);

	//__write_port(PS2_PORT_COMMAND, 0xF5);

	// Sets the scan code set.
	mapping[0x1c] = "enter pressed";
	mapping[0x9c] = "enter released";
}

/*
 * Should be called upon a key press interrupt.
 * Handles the key press.
 */
void keyboard_handler(void)
{
	// Reads the scan code.
	uint8_t scan_code = __read_port(PS2_PORT_DATA);
	// Converts the scan code.
	kprintf("%s ", mapping[scan_code]);
	// Marks the interrupt as complete.
	__write_port(PIC1, INT_END);
}