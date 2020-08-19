#include "kernel.h"

// The entry point of the kernel.
void kernel_main(MBINFO * mbinfo)
{
	// Initialises the vga buffer so we can print to the screen.
	vgainit();
	// Initialises the physical memory manager.
	// pfalloc_init(mbinfo);
	// Initialises paging for virtual memory mapping.
	// init_paging();
	// Initialises the Global Descriptor Table.
	init_GDT();

	// Various kernel debug information.

	// Has the kernel been mapped correctly?
	kprintf("Value at &kernel_start: 0x%x\n", kernel_start);
	kprintf("Value at 0x%x: 0x%x\n", KERNEL_MAPPING_ADDR, *(uint32_t *)(KERNEL_MAPPING_ADDR));
}