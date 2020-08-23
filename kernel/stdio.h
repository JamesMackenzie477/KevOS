#ifndef _STDIO_H 
#define _STDIO_H

#include <stddef.h>
#include "string.h"

#define VGA_BUFF_ADDR 0xB8000
#define VGA_MAX_COLS 80
#define VGA_MAX_LINES 25

/*
 * Allows extraction of a certain type from the index of the given variable.
 */

#define SHORT_INDEX(I, S)	((I >> (S * 16)) & 0xFFFF)
#define BYTE_INDEX(I, S)	((I >> (S * 8)) & 0xFF)

typedef struct _VGA_ENTRY
{
	char character;
	char colour;
} VGA_ENTRY;

// Declares the interface methods.
void stdio_init(void);
void kprintf(const char * s, ...);

#endif