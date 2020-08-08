#include "paging.h"

uint32_t * page_directory;
uint32_t * page_table;

// Initialises the paging tables and registers.
void init_paging(void)
{
	// Allocates the page directory.
	page_directory = (uint32_t *)pfalloc_alloc();
	// Allocates a page table.
	page_table = (uint32_t *)pfalloc_alloc();
	// Defaults the page directory entries.
	for(uint32_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++)
	{
		page_directory[i] = 0x00000002;
	}
	// Defaults the page table entries.
	// for(uint32_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++) page_table[i] = (i * 0x1000) | 3;
	// Adds the first page table to the page directory.
	// page_directory[0] = ((uint32_t)&page_table) | 3;
	// Sets the page directory address.
	_set_page_dir(page_directory);
	// Enables paging.
	_enable_paging();
}