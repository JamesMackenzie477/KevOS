#ifndef _KEVIN_H
#define _KEVIN_H

#include <stdarg.h>

/**
 * Defines the various syscalls can can be called.
 */
extern void __printf(const char *, va_list);

/**
 * Printf wrapper to allow varargs to be passed to the kernel.
 */
void printf(const char *, ...);

#endif