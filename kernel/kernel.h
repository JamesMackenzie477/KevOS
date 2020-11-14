#ifndef _KERNEL_H
#define _KERNEL_H

#include "stdio.h"
#include "memory/pfalloc.h"
#include "memory/paging.h"
#include "GDT.h"
#include "IDT.h"
#include "sys/apic.h"

void test(void);

// Used to validate the flags of the multiboot header.
#define MMAP (1 << 6)
#define VALIDATE_FLAGS(F) (F & MMAP)

// These are used to determine the kernel size.
extern uint32_t kernel_start;
extern uint32_t kernel_end;

extern void __disable_pic(void);

#endif