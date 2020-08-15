#include "kernel.h"

// The entry point of the kernel.
void kernel_main(MBINFO * mbinfo)
{
	// We want to be able to access this wherever in the kernel.
	// multiboot_info = mbinfo;
	// Initialises the vga buffer so we can print to the screen.
	vgainit();
	// Initialises the physical memory manager.
	pfalloc_init(mbinfo);
	// Initialises paging for virtual memory mapping.
	init_paging();
	// Various kernel debug information.
	kprintf("Kernel is mapped at: 0x%x\n", &kernel_start);
	kprintf("Kernel size: %d bytes\n", (((uint32_t)&kernel_end) - ((uint32_t)&kernel_start)));
	kprintf("Free memory starts at: 0x%x\n", &kernel_end);
	kprintf("Multiboot Info: 0x%x\n", mbinfo);
	kprintf("Available pages: %d\n\n", avail_pages());

	// Has the kernel been mapped?
	kprintf("Value at &kernel_start: 0x%x\n", kernel_start);
	kprintf("Value at 0xC0000000: 0x%x\n", *(uint32_t *)(KERNEL_MAPPING_ADDR));
}