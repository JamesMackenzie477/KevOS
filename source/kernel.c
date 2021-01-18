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
	// Initialises the image loader.
	il_init();

	// Maps the kernel to to it's default virtual address (Higher Half Kernel).
	// paging_map_pages(KERNEL_MAPPING_ADDR, &kernel_start, 	MAX_PAGETABLE_ENTRIES, PAGE_PRESENT | PAGE_RW);
	// Sets the pemissions for the kernel memory regions.
	//paging_map_page(&text_start, 	&text_start, 	PAGE_PRESENT);
	//paging_map_page(&rodata_start, 	&rodata_start, 	PAGE_PRESENT);
	//paging_map_page(&data_start, 	&data_start, 	PAGE_PRESENT | PAGE_RW);
	//paging_map_page(&bss_start, 	&bss_start, 	PAGE_PRESENT | PAGE_RW);

	// kprintf("%s>ls\n", fs_dir());
	// kprintf("%s>", fs_dir());

	// Prints the files in the directory.
	//kprintf("Files:\n");
	//fs_ls();

	// kprintf("\nExecuting %s...\n", "disk/cli.bin");
	// Attempts to load a program.
	/*il_prog img =*/uintptr_t img = il_load_elf64(fs_get_file("disk/cli.bin"));
	// Calls the entry point of the program.
	// il_call_entry(img);
	//if (img) kprintf("Finished executing %s.\n", "disk/cli.bin");

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