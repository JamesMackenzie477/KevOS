#ifndef _STRING_H
#define _STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "stdio.h"

#define STRING_CHARACTER_NOT_FOUND -1

static inline bool is_num(const char c)
{
	return ((c - 48) < 10);
}

// Declares the interface methods.
uint32_t str_to_int(const char * str, uint32_t base);
size_t strlen(const char* s);
size_t find(const char * s, char c);
char * strncpy(char * dst, const char * src, size_t n);
char * strcpy(char * dst, const char * src);
char * strrev(char * src);
char * itoa(char * r, uint32_t v, int base);
char specifier_type(const char * s);
size_t specifier_len(const char * s);
char * format(char * r, const char * s, va_list args);
void * memset(void * ptr, int value, size_t num);
size_t strcmp(const char * a, const char * b);
char * strcat(char * dst, const char * src);
char * strtok(char * s, const char * del);

#endif