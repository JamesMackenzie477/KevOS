#ifndef _KERNEL_H
#define _KERNEL_H

#include "stdio.h"
// #include "paging.h"
#include "pfalloc.h"

#define MMAP (1 << 6)
#define VALIDATE_FLAGS(F) (F & MMAP)

extern uint32_t kernel_start;
extern uint32_t kernel_end;

void kernel_main(MBINFO * mbinfo);

#endif