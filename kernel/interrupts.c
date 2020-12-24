#include "interrupts.h"

/*
 * This is the default interrupt.
 * Can be used as a placeholder.
 */
void printf(const char * str)
{
	kprintf("%s", str);
}

void double_fault(void)
{
	kprintf("double fault.\n");
	for (;;);
}

void irq_1()
{
	// Calls the keyboard handler.
	keyboard_handler();
}