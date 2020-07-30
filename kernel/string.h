#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _STRING_H
#define _STRING_H

#define IS_NUM(S, I) ((S[I] - 48) < 10)

#define STRING_CHARACTER_NOT_FOUND -1

static inline is_num(const char * s, size_t i)
{
	return ((s[i] - 48) < 10);
}

// Declares the interface methods.
size_t strlen(const char* s);
char * format(const char * s, char * r, ...);

#endif