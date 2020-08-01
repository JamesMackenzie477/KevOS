#include "stdio.h"

// Sets the VGA buffer address.
VGA_ENTRY * vga_buff = (VGA_ENTRY *)VGA_BUFF_ADDR;

int line = 0, column = 0;

// Prints a single character to the screen.
void putchar(char c)
{
	// NEWLINE
	if (c == '\n')
	{
		line++; column = 0;
	}
	else
	{
		// Adds the character and colour to the buffer.
		vga_buff[((line * VGA_MAX_COLUMNS) + column)].character = c;
		vga_buff[((line * VGA_MAX_COLUMNS) + column)].colour = 7;

		if (++column > VGA_MAX_COLUMNS) { column = 0; line++; }
	}
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