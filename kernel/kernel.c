#include "kernel.h"

void test(void)
{
	kprintf("hi");
}

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

	GDT_init(); IDT_init();

	// Initialises the PIC and the APIC.

	pic_init(); // apic_init();

	// Maps the kernel to to it's default virtual address (Higher Half Kernel).

	// paging_map_pages(KERNEL_MAPPING_ADDR, &kernel_start, MAX_PAGETABLE_ENTRIES);

	// Ensures we remain within this function.
	for (;;);
}