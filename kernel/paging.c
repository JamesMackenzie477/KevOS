#include "paging.h"

/*
 * Sets the page table entries to a 1:1 virtual to physical mapping.
 */
void init_identity(uint32_t * page_table, uint32_t start)
{
	for(size_t i = start; i < start + MAX_PAGETABLE_ENTRIES; i++) page_table[i] = (i * 0x1000) | 3;
}

/*
 * Sets up the page directory by allocating and defaulting the page tables.
 */
void init_directory(uint32_t * page_directory)
{
	// Stores a pointer to the current table.
	uint32_t * table;
	// Iterates through the entries in the page table.
	for (size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++)
	{
		// Allocates the table.
		table = (uint32_t *)pfalloc_alloc();
		// Defaults the entries.
		init_identity(table, i * MAX_PAGETABLE_ENTRIES);
		// Adds the page table to the page directory.
		page_directory[i] = (uint32_t)table | 3;
	}
}

/*
 * Initialises the paging tables and registers.
 */
void init_paging(void)
{
	// Allocates the page directory.
	uint32_t * page_directory = (uint32_t *)pfalloc_alloc();
	// Initialises the page directory.
	init_directory(page_directory);
	// Sets the page directory address.
	_set_page_dir(page_directory);
	// Enables paging.
	_enable_paging();
}