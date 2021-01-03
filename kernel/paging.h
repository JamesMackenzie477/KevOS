#ifndef _PAGING_H
#define _PAGING_H

#include "stdio.h"
#include "pfalloc.h"

#define MAX_PAGETABLE_ENTRIES 	1024
#define SIZE_OF_MEM_REGION 		(MAX_PAGETABLE_ENTRIES * PAGE_SIZE)
#define KERNEL_MAPPING_ADDR 	0xC0000000
#define GET_PAGE_TABLE_MASK		0xFFFFFF00

#define GET_PAGE_TABLE(ENTRY) 	((uint32_t *)(ENTRY & GET_PAGE_TABLE_MASK))

/**
 * Gets the base address of the page where the address is found.
 */
#define GET_PAGE_BASE(A) (((uint32_t)A) & 0xFFFFF000)

/**
 * Defines flags for the page entry.
 */
#define PAGE_PRESENT 	0x1
#define PAGE_RW			0x2
#define PAGE_USER		0x4

/*
 * These are assembly functions that are linked at compile time.
 */

extern void __set_page_dir(uint32_t *);
extern void __enable_paging(void);
extern void __enable_pae(void);
extern uint32_t __read_cr0(void);
extern void __write_cr0(uint32_t);

/*
 * Public functions used to interact with the paging system.
 */

void paging_init(void);
uint32_t paging_virtual_to_physical(uint32_t virtual);
void paging_map_page(uint32_t virtual, uint32_t physical, uint32_t flags);
void paging_map_pages(uint32_t virtual, uint32_t physical, size_t count, uint32_t flags);

#endif