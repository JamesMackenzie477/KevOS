#include "stdio.h"

// Sets the VGA buffer address.
static VGA_ENTRY * vga_buff = (VGA_ENTRY *)VGA_BUFF_ADDR;

/**
 * Stores the column and line index.
 */
static uint32_t line, column;

/**
 * Adds the character to the screen (internal function).
 */
static inline void stdio_vga_put(uint8_t c, uint8_t col)
{
	// Adds the character to the VGA buffer.
	vga_buff[VGA_GET_INDEX(line, column)].character = c;
	vga_buff[VGA_GET_INDEX(line, column)].colour = col;
}

/**
 * Goes to the previous column.
 */
static inline void stdio_vga_prev(void)
{
	if (--column < 0) { column = VGA_MAX_COLS; line--; }
}

/**
 * Goes to the next column.
 */
static inline void stdio_vga_next(void)
{
	if (++column > VGA_MAX_COLS) { column = 0; line++; }
}

/**
 * Clears the screen.
 */
static void stdio_cls(void)
{
	// Iterates through each line in the buffer
	for (int i = 0; i < VGA_MAX_LINES; i++)
	{
		// Iterates through each column.
		for (int y = 0; y < VGA_MAX_COLS; y++)
		{
			// Clears the column.
			stdio_vga_put(NULL, NULL);
		}
	}
	// Resets the line and column counter.
	line = 0; column = 0;
}

/**
 * Creates a newline on the screen.
 */
static inline void stdio_newline(void)
{
	// Goes to the start of the next line.
	line++; column = 0;
}

/**
 * Creates a backspace on the screen.
 */
static inline void stdio_backspace(void)
{
	// Goes to the previous column.
	stdio_vga_prev();
	// Adds the character to the VGA buffer.
	stdio_vga_put(NULL, NULL);
}

/**
 * Adds the character to the screen (internal function).
 */
static inline void stdio_putchar(uint8_t c, uint8_t col)
{
	// Adds the character to the VGA buffer.
	stdio_vga_put(c, col);
	// Goes to the next column.
	stdio_vga_next();
}

// Prints a single character to the screen.
void putchar(char c)
{
	// Checks for special characters.
	switch (c)
	{
		case '\n':
			stdio_newline();
			break;
		case '\t':
			//stdio_tab();
			break;
		case '\b':
			stdio_backspace();
			break;
		default:
			stdio_putchar(c, 9);
			break;
	}
	// Starts a new page.
	// We should really shunt the screen up by one.
	// Buffer old screen so it can be retrieved later.
	if (line > VGA_MAX_LINES) stdio_cls();
}

/**
 * Initialises the VGA buffer.
 */
void stdio_init(void)
{
	// Clears the screen.
	stdio_cls();
}

/**
 * Varargs function that will print the given format string to the standard output.
 */
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

/**
 * Varargs function that will print the given format string to the standard output.
 * Uses va_list for system call use.
 */
void kprintfl(const char * s, va_list f)
{
	// Stores the formatted string.
	char c[100];
	// Formats the string.
	format(&c, s, f);
	// Iterates through the formatted string and prints each character.
	for (size_t i = 0; i < strlen(c); i++) putchar(c[i]);
}