#include "stdio.h"

// The entry point of the kernel.
void kernel_main(void)
{
	// Prints a message to the screen.
	kprintf("%c%c%c%c%c %s! This is my SCC.%x project.", 'H', 'e', 'l', 'l', 'o', "world", 300);
}