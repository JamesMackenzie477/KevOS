#ifndef _KEVIN_H
#define _KEVIN_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/**
 * The address of the shared buffer.
 */
#define SBUFF_ADDR 0x1B0000

/**
 * Defines the various syscalls can can be called.
 */
extern void __printf(const char *, va_list);
extern size_t __fread(char * dst, size_t size, size_t count);

/**
 * Printf wrapper to allow varargs to be passed to the kernel.
 */
void printf(const char *, ...);

#endif