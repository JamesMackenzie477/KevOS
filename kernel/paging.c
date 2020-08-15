#include "paging.h"

/*
 * Stores the address of the page directory.
 */
uint32_t * page_directory;

/*
 * Maps a whole table to a whole table size of memory.
 * The addresses must be 4 byte aligned.
 */
void map_table(uint32_t virtual, uint32_t physical)
{
	// Calculate the offset into the table for the virtual address.
	uint32_t off = virtual / 0x400000;
	// Alters the table.
	init_identity(page_directory[off] & 0xFFFFFFF0, 0, physical);
}

/*
 * Sets the page table entries to a 1:1 virtual to physical mapping.
 */
void init_identity(uint32_t * page_table, uint32_t start, uint32_t base)
{
	for(size_t i = start; i < start + MAX_PAGETABLE_ENTRIES; i++) page_table[i] = base + (i * 0x1000) | 3;
}

/*
 * Sets up the page directory by allocating and defaulting the page tables.
 */
void init_directory()
{
	// Stores a pointer to the current table.
	uint32_t * table;
	// Iterates through the entries in the page table.
	for (size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++)
	{
		// Allocates the table.
		table = (uint32_t *)pfalloc_alloc();
		// Defaults the entries.
		init_identity(table, i * MAX_PAGETABLE_ENTRIES, 0);
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
	page_directory = (uint32_t *)pfalloc_alloc();
	// Initialises the page directory.
	init_directory();
	// Maps the kernel to 0xC0000000.
	map_table(0xC0000000, 0x100000);
	// Sets the page directory address.
	_set_page_dir(page_directory);
	// Enables paging.
	_enable_paging();
}