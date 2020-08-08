#ifndef _PAGING_H
#define _PAGING_H

#include "stdio.h"
#include "pfalloc.h"

#define MAX_PAGETABLE_ENTRIES 1024

// These are assembly functions that are linked at compile time.
extern void _set_page_dir(uint32_t *);
extern void _enable_paging(void);

void init_paging(void);

#endif