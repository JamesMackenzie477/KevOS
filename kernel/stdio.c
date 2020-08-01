#include "stdio.h"

// Sets the VGA buffer address.
char * vga_buff = (char *)VGA_BUFF_ADDR;

// Prints a single character to the screen.
void putchar(char c)
{
	// Adds the character and colour to the buffer.
	*vga_buff++ = c; *vga_buff++ = 7;
}

// Prints a string to the screen.
void kprintf(const char * s, ...)
{
	// Stores the formatted string.
	char c[100];
	// Used to iterate over the varargs.
	va_list args;
	// Sets the address of the varargs.
	va_start(args, s);
	// Formats the string.
	format(&c, s, args);
	// We no longer need the varargs.
	va_end(args);
	// Iterates through the formatted string and prints each character.
	for (size_t i = 0; i < strlen(c); i++) putchar(c[i]);
}