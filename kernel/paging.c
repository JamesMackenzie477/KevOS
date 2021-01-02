#include "paging.h"

/*
 * Stores the address of the page directory.
 */
uint32_t * page_directory;

/*
 * Returns the physical address for the corrosponding virtual.
 */
uint32_t paging_virtual_to_physical(uint32_t virtual)
{
	// Calculate the offset into the directory for the virtual address.
	uint32_t dir_off = virtual / SIZE_OF_MEM_REGION;
	// Calculates the offset into the page table.
	uint32_t tab_off = (virtual % SIZE_OF_MEM_REGION) / PAGE_SIZE;
	// WIP...
	uint32_t rem = (virtual % SIZE_OF_MEM_REGION) % PAGE_SIZE;
	// Maps the physical page to the virtual one.
	return (GET_PAGE_TABLE(page_directory[dir_off])[tab_off] & 0xFFFFFF00) + rem;
}

/*
 * Maps the specified virtual address to the given physical address.
 */
void paging_map_page(uint32_t virtual, uint32_t physical, uint32_t flags)
{
	// Checks if the addresses are 4KB aligned.
	if (((virtual % PAGE_SIZE) == 0) && ((physical % PAGE_SIZE) == 0))
	{
		// Calculate the offset into the directory for the virtual address.
		uint32_t dir_off = virtual / SIZE_OF_MEM_REGION;
		// Calculates the offset into the page table.
		uint32_t tab_off = (virtual % SIZE_OF_MEM_REGION) / PAGE_SIZE;
		// WIP...
		uint32_t rem = (virtual % SIZE_OF_MEM_REGION) % PAGE_SIZE;

		// TEMP FIX TO CHANGE DIRECTORY TO USER ONE.
		// Really we should have multiple directories allocated to user more and use these.
		// Maybe a program would use one directory, etc.
		if (flags & PAGE_USER) page_directory[dir_off] |= PAGE_USER;

		// Maps the physical page to the virtual one.
		GET_PAGE_TABLE(page_directory[dir_off])[tab_off] = (physical - rem) | flags;
	}
}

/*
 * Maps a whole table to a whole table size of memory.
 * The addresses must be 4 byte aligned.
 */
void paging_map_pages(uint32_t virtual, uint32_t physical, size_t count, uint32_t flags)
{
	// Maps n pages.
	for(size_t i = 0; i < count; i++) paging_map_page(virtual + (i * PAGE_SIZE), physical + (i * PAGE_SIZE), flags);
}

/*
 * Sets up the specified page table using the physical address as an offset.
 */
static void paging_init_table(uint32_t * page_table, uint32_t physical)
{
	for(size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++) page_table[i] = physical + (i * 0x1000) | 7;
}

/*
 * Sets up the page directory by allocating and defaulting the page tables.
 */
static void paging_init_directory(void)
{
	// Stores a pointer to the current table.
	uint32_t * table;
	// Iterates through the entries in the page table.
	// We should only initialise the kernel area and then
	// add other areas when we allocate the memory. To save space!
	for (size_t i = 0; i < MAX_PAGETABLE_ENTRIES; i++)
	{
		// Allocates the table.
		table = (uint32_t *)pfalloc_alloc();
		// Defaults the entries.
		paging_init_table(table, i * SIZE_OF_MEM_REGION);
		// Adds the page table to the page directory.
		page_directory[i] = (uint32_t)table | 7;
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

	__write_cr0(__read_cr0() | (1 << 16));
}