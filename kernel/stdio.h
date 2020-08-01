#ifndef _STDIO_H 
#define _STDIO_H

#include <stddef.h>
#include "string.h"

#define VGA_BUFF_ADDR 0xB8000
#define VGA_MAX_COLUMNS 80
#define VGA_MAX_LINES 25

typedef struct _VGA_ENTRY
{
	char character;
	char colour;
} VGA_ENTRY;

// Declares the interface methods.
void kprintf(const char * s, ...);

#endif