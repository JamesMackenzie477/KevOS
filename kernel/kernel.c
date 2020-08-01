#include "stdio.h"

// The entry point of the kernel.
void kernel_main(void)
{
	char c[100];
	// Prints a message to the screen.
	kprintf(format(&c, "%c%c%c%c%c %s! This is my SCC.%x project.", 'H', 'e', 'l', 'l', 'o', "world", 300));
}