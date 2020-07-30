#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _STRING_H
#define _STRING_H

#define STRING_CHARACTER_NOT_FOUND -1

static inline is_num(const char c)
{
	return ((c - 48) < 10);
}

// Declares the interface methods.
size_t strlen(const char* s);
char * format(char * r, const char * s, ...);

#endif