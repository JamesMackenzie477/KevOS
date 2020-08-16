#ifndef _PAGING_H
#define _PAGING_H

#include "stdio.h"
#include "pfalloc.h"

#define MAX_PAGETABLE_ENTRIES 	1024
#define SIZE_OF_MEM_REGION 		(MAX_PAGETABLE_ENTRIES * PAGE_SIZE)
#define KERNEL_MAPPING_ADDR 	0xC0000000
#define GET_PAGE_TABLE_MASK		0xFFFFFFF0

#define GET_PAGE_TABLE(ENTRY) 	((uint32_t *)(ENTRY & GET_PAGE_TABLE_MASK))

/*
 * These are assembly functions that are linked at compile time.
 */

extern void _set_page_dir(uint32_t *);
extern void _enable_paging(void);
extern void _enable_pae(void);

/*
 * Public functions used to interact with the paging system.
 */

void init_paging(void);

#endif