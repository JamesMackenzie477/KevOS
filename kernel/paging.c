#include "paging.h"

/*
 * Stores the address of the page directory.
 */
uint32_t * page_directory;

/*
 * Maps the specified virtual address to the given physical address.
 */
void paging_map_page(uint32_t virtual, uint32_t physical)
{
	// Calculate the offset into the directory for the virtual address.
	uint32_t dir_off = virtual / SIZE_OF_MEM_REGION;
	// Calculates the offset into the page table.
	uint32_t tab_off = (virtual % SIZE_OF_MEM_REGION) / PAGE_SIZE;
	// Maps the physical page to the virtual one.
	GET_PAGE_TABLE(page_directory[dir_off])[tab_off] = physical | 3;
}

/*
 * Maps a whole table to a whole table size of memory.
 * The addresses must be 4 byte aligned.
 */
void paging_map_pages(uint32_t virtual, uint32_t physical, size_t count)
{
	// Maps n pages.
	for(size_t i = 0; i < count; i++) paging_map_page(virtual + (i * PAGE_SIZE), physical + (i * PAGE_SIZE));
}

/*
 * Sets up the specified page table using the physical address as an offset.
 */
void paging_init_table(uint32_t * page_table, uint32_t physical)
{
	for(size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++) page_table[i] = physical + (i * 0x1000) | 3;
}

/*
 * Sets up the page directory by allocating and defaulting the page tables.
 */
void paging_init_directory(void)
{
	// Stores a pointer to the current table.
	uint32_t * table;
	// Iterates through the entries in the page table.
	for (size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++)
	{
		// Allocates the table.
		table = (uint32_t *)pfalloc_alloc();
		// Defaults the entries.
		paging_init_table(table, i * SIZE_OF_MEM_REGION);
		// Adds the page table to the page directory.
		page_directory[i] = (uint32_t)table | 3;
	}
}

/*
 * Initialises the paging tables and registers.
 */
void paging_init(void)
{
	// Allocates the page directory.
	page_directory = (uint32_t *)pfalloc_alloc();
	// Initialises the page directory.
	paging_init_directory();
	// Sets the page directory address.
	__set_page_dir(page_directory);
	// Enables PAE.
	// We will enable this later.
	// __enable_pae();
	// Enables paging.
	__enable_paging();
}