#include "stdio.h"

// The entry point of the kernel.
void kernel_main(void)
{
	char c[100];
	// Prints a message to the screen.
	kprintf(format("Hello %c world!", &c, 'h'));
}