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
	GDT_init(); IDT_init();
	// Initialises the PIC and the APIC.
	pic_init(); // apic_init();
	// Initialises the file system.
	fs_init();

	// Maps the kernel to to it's default virtual address (Higher Half Kernel).
	// paging_map_pages(KERNEL_MAPPING_ADDR, &kernel_start, 	MAX_PAGETABLE_ENTRIES, PAGE_PRESENT | PAGE_RW);
	// Sets the pemissions for the kernel memory regions.
	paging_map_page(&text_start, 	&text_start, 	PAGE_PRESENT);
	paging_map_page(&rodata_start, 	&rodata_start, 	PAGE_PRESENT);
	paging_map_page(&data_start, 	&data_start, 	PAGE_PRESENT | PAGE_RW);
	paging_map_page(&bss_start, 	&bss_start, 	PAGE_PRESENT | PAGE_RW);

	kprintf("\nKevinOS v0.0.1\n%s>", fs_dir());

	// scanf() ...
	// if (cmd == "cd") ...
	// fs_cd(dir) ...

	// TODO
	// Memory zones (look at linux implementation).
	// Mapping page directory to itself (lecture slides).
	// Add constants
	// ne2000
	// PCI
	// Ensures we remain within this function.
	for (;;);
}