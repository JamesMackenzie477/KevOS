#include "stdio.h"

// Sets the VGA buffer address.
char * vga_buff = (char *)VGA_BUFF_ADDR;

// Prints a single character to the screen.
void putchar(char c)
{
	// Adds the character to the buffer.
	*vga_buff++ = c;
	// Adds the colour to the buffer.
	*vga_buff++ = 7;
}

// Prints a string to the screen.
void kprintf(const char * s)
{
	// Iterates through the string and prints each character.
	for (size_t i = 0; i < strlen(s); i++) putchar(s[i]);
}

// Returns the length of the specified string.
size_t strlen(const char * s)
{
	// Calculates the returns the string length.
	size_t i; for (i = 0; s[i] != '\0'; i++); return i;
}