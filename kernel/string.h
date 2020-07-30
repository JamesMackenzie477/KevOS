#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _STRING_H
#define _STRING_H

#define STRING_CHARACTER_NOT_FOUND -1

// Declares the interface methods.
size_t strlen(const char* s);
char * format(const char * s, char * r, ...);

#endif