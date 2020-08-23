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

	// Initialises rings and interrupts.

	GDT_init(); IDT_init();

	// Maps the kernel to to it's default virtual address (Higher Half Kernel).

	paging_map_pages(KERNEL_MAPPING_ADDR, &kernel_start, MAX_PAGETABLE_ENTRIES);

	// Various kernel debug information.

	kprintf("Value at &kernel_start: 0x%x\n", kernel_start);
	
	kprintf("Value at 0x%x: 0x%x\n", KERNEL_MAPPING_ADDR, *(uint32_t *)(KERNEL_MAPPING_ADDR));
}