#include "paging.h"

/*
 * Stores the address of the page directory.
 */
uint32_t * page_directory;

/*
 * Maps the specified virtual address to the given physical address.
 */
void map_page(uint32_t virtual, uint32_t physical)
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
void map_pages(uint32_t virtual, uint32_t physical, size_t count)
{
	// Maps n pages.
	for(size_t i = 0; i < count; i++) map_page(virtual + (i * PAGE_SIZE), physical + (i * PAGE_SIZE));
}

/*
 * Sets up the specified page table using the physical address as an offset.
 */
void init_table(uint32_t * page_table, uint32_t physical)
{
	for(size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++) page_table[i] = physical + (i * 0x1000) | 3;
}

/*
 * Sets up the page directory by allocating and defaulting the page tables.
 */
void init_directory(void)
{
	// Stores a pointer to the current table.
	uint32_t * table;
	// Iterates through the entries in the page table.
	for (size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++)
	{
		// Allocates the table.
		table = (uint32_t *)pfalloc_alloc();
		// Defaults the entries.
		init_table(table, i * SIZE_OF_MEM_REGION);
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
	// Maps the kernel to to it's default virtual address.
	map_pages(KERNEL_MAPPING_ADDR, &kernel_start, MAX_PAGETABLE_ENTRIES);
	// Sets the page directory address.
	_set_page_dir(page_directory);
	// Enables PAE.
	// We will enable this later.
	// _enable_pae();
	// Enables paging.
	_enable_paging();
}