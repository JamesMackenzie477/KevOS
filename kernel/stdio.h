#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "string.h"

#ifndef _STDIO_H 
#define _STDIO_H

#define VGA_BUFF_ADDR 0xB8000

// Declares the interface methods.
void kprintf(const char * s, ...);

#endif