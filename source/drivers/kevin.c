#include "kevin.h"

/**
 * Printf wrapper to allow varargs to be passed to the kernel.
 */
void printf(const char * s, ...)
{
	va_list va;
	va_start(va, s);
	__printf(s, va);
	va_end(va);
}