#ifndef _STRING_H
#define _STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "stdio.h"

#define STRING_CHARACTER_NOT_FOUND -1

static inline is_num(const char c)
{
	return ((c - 48) < 10);
}

// Declares the interface methods.
size_t strlen(const char* s);
size_t find(const char * s, char c);
char * strncpy(char * dst, const char * src, size_t n);
char * strcpy(char * dst, const char * src);
char * strrev(char * src);
char * itoa(char * r, uint64_t v, int base);
char specifier_type(const char * s);
size_t specifier_len(const char * s);
char * format(char * r, const char * s, va_list args);
void * memset(void * ptr, int value, size_t num);

#endif