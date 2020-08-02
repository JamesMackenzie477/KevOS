#include "stdio.h"

#ifndef _PAGING_H
#define _PAGING_H

#define MAX_PAGETABLE_ENTRIES 1024

// These are assembly functions that are linked at compile time.
extern void _set_page_dir(uint32_t *);
extern void _enable_paging();

// THIS IS TEMP - WILL BE IMPLEMENTED PROPERLY WHEN MEMORY ALLOCATION WORKS.
uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_table[1024] __attribute__((aligned(4096)));

// Initialises the paging tables and registers.
void init_paging()
{
	// Defaults the page directory entries.
	for(uint32_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++) page_directory[i] = 0x00000002;
	// Defualts the page table entries.
	for(uint32_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++) page_table[i] = (i * 0x1000) | 3;
	// Adds the first page table to the page directory.
	page_directory[0] = ((uint32_t)&page_table) | 3;
	// Sets the page directory address.
	_set_page_dir(page_directory);
	// Enables paging.
	_enable_paging();
}

#endif