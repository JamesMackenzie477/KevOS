#include "keyboard.h"

/*
 * Mapping table for the scan codes.
 */
static char * mapping[] =
{
	"Q",
 	"W",
	"E",
	"R",
	"T",
	"Y",
	"U",
	"I",
	"O",
	"P",
	"[",
	"]",
	"\n",
	"lctrl",
	"A",
	"S",
 	"D",
 	"F",
	"G",
	"H",
	"J",
	"K",
	"L",
	";",
	"'",
	"#",
	"lshift",
	"\\",
	"Z",
	"X",
	"C",
	"V",
 	"B",
 	"N",
	"M",
	",",
	".",
	"/",

	"",
	"",
	"",
	" ",
};

/*
 * Receives data from the PS/2 keyboard via the 8042 Controller.
 */
static inline uint8_t keyboard_recv()
{
	// Ensures there is data.
	if (__read_port(PS2_PORT_STATUS) & PS2_STATUS_OUTPUT)
	{
		// Returns the data.
		return __read_port(PS2_PORT_DATA);
	}
	// No data.
	return NULL;
}

/*
 * Sends data to the PS/2 keyboard via the 8042 Controller.
 */
static inline void keyboard_send(uint8_t data)
{
	// Ensures that the input buffer is empty.
	if (!(__read_port(PS2_PORT_STATUS) & PS2_STATUS_INPUT))
	{
		// Writes the data.
		__write_port(PS2_PORT_DATA, data);
	}
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
	//if (keyboard_con(0xAA) != PS2_CON_TEST_PASSED	) return;
	//if (keyboard_con(0xAB) != PS2_PORT_TEST_PASSED	) return;
	//if (keyboard_con(0xA9) != PS2_PORT_TEST_PASSED	) return;

	keyboard_send(PS2_CMD_SCAN_CODE);
	kprintf("PS2_CMD_SCAN_CODE: %d\n", keyboard_recv() == PS2_RES_ACK);
	keyboard_send(2);
	kprintf("2: %d\n", keyboard_recv() == PS2_RES_ACK);

	// Interrupt now gets NULL Because we overwrite the original key.

	// kprintf("0x00: 0x%x\n", keyboard_recv());

	kprintf("VOLATILE\n");


	// KEYBOARD TEST.
	for (;;)
		{
			uint8_t v = keyboard_recv();
			if (v && IS_LETTER(v)) kprintf("%s", mapping[(v - 0x10)]);
		}

	//keyboard_send(PS2_CMD_ENABLE);
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
	//kprintf("0x%x ", scan_code);
	// Marks the interrupt as complete.
	__write_port(PIC1, INT_END);
}