#ifndef _KERNEL_H
#define _KERNEL_H

#include "stdio.h"
#include "pfalloc.h"
#include "paging.h"

// Used to validate the flags of the multiboot header.
#define MMAP (1 << 6)
#define VALIDATE_FLAGS(F) (F & MMAP)

// These are used to determine the kernel size.
extern uint32_t kernel_start;
extern uint32_t kernel_end;

#endif