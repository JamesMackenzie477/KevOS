#include "interrupts.h"

/*
 * This is the default interrupt.
 * Can be used as a placeholder.
 */
void def_int(void)
{
	kprintf("default interrupt triggered.\n");
	for (;;);
}

void irq_1()
{
	// Calls the keyboard handler.
	keyboard_handler();
}