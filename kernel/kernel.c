#include "kernel.h"

/*
 * The entry point of the kernel.
 * Performs initial setup for all kernel based systems.
 */
void kernel_main(MBINFO * mbinfo)
{
	// Initialises the standard input and output system.

	stdio_init();

	// Initialises page allocation and paging systems.

	pfalloc_init(mbinfo); paging_init();

	// Initialises the keyboard driver.

	keyboard_init();

	// Initialises rings and interrupts.

	GDT_init(); IDT_init(); // WILL FIX LATER.

	// Maps the kernel to to it's default virtual address (Higher Half Kernel).

	// paging_map_pages(KERNEL_MAPPING_ADDR, &kernel_start, MAX_PAGETABLE_ENTRIES);

	// KEYBOARD TESTING

	/*char * k;

	kprintf("Welcome to KevOS...\n");

	for (char * k = poll_keyboard(); ; k = poll_keyboard())
	{
		if (k != NULL) kprintf("%s", k);
	}*/

	// SYSTEM FREEZES AFTER INTERRUPT TRIGGERED.
	// INTERRUPT NEVER MAKES IT BACK FROM EXECUTION.
	// POTENTIAL RESTORATION ISSUE, OR NON NOTIFICATION OF EOI?

	for (;;) kprintf("hi");
}