#include "stdio.h"
#include "paging.h"

// The entry point of the kernel.
void kernel_main(void)
{
	// Initialises paging.
	init_paging();
	// Initialises the vga buffer.
	vgainit();
	// Prints a message to the screen.
	kprintf("Hello world!\n%s", "Welcome to my SCC.300 project...");
}