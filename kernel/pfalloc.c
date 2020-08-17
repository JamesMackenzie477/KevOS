#include "pfalloc.h"

/*
 * The bitmap array where we can track page allocation.
 */
uint8_t * pages;

/*
 * The amount of pages stored in the bitmap.
 */
uint32_t length;

/*
 * We need this to parse memory mappings in various functions.
 */
MBINFO * multibootinfo;

/*
 * Returns a pointer to the first available region as a MAPINFO structure.
 */
MAPINFO * get_first_avail()
{
	// Gets the mapping info array.
	MAPINFO * info = multibootinfo->mmap_addr;
	// Iterates through the array.
	for (int i = 0; i < multibootinfo->mmap_length / sizeof(MAPINFO); i++)
	{
		if (info[i].type == 1) return info;
	}
}

/*
 * Returns the amount of possible pages in memory.
 */
uint32_t get_page_count()
{
	// Stores the page count.
	uint32_t page_count = 0;
	// Gets the mapping info array.
	MAPINFO * info = multibootinfo->mmap_addr;
	// Iterates through the array.
	for (int i = 0; i < multibootinfo->mmap_length / sizeof(MAPINFO); i++)
	{
		// If the memory region is available.
		if (info[i].type == 1)
		{
			// Increment the page count.
			page_count += (info[i].length / PAGE_SIZE);
		}
	}
	// Returns the calculated page count.
	return page_count;
}

/*
 * Returns the base address of the specified page number.
 */
void * page_to_addr(uint32_t page_num)
{
	uint32_t page_nums = 0;
	// Gets the mapping info array.
	MAPINFO * info = multibootinfo->mmap_addr;
	// Iterates through the array.
	for (int i = 0; i < multibootinfo->mmap_length / sizeof(MAPINFO); i++)
	{
		if (info[i].type == 1)
		{
			page_nums += GET_PAGE_NUM(info[i].length);
			if (page_num < page_nums)
			{
				return (void *)(info[i].base_addr + ((page_num - (page_nums - GET_PAGE_NUM(info[i].length))) * PAGE_SIZE));
			}
		}
	}
	return (void *)-1;
}

/*
 * Returns the page number where the specified address lies.
 */
uint32_t addr_to_page(void * addr)
{
	uint32_t jump, size = 0;

	// Gets the mapping info array.
	MAPINFO * info = multibootinfo->mmap_addr;
	// Iterates through the array.
	for (int i = 0; i < multibootinfo->mmap_length / sizeof(MAPINFO); i++)
	{
		if (info[i].type == 1)
		{
			if ((uint32_t)addr < (info[i].base_addr + info[i].length))
			{
				jump = info[i].base_addr - size;
				return GET_PAGE_NUM(((uint32_t)addr) - jump);
			}
			else size += info[i].length;
		}
	}
	return -1;
}

/*
 * Initialises pfalloc with an array of available memory regions.
 * This function is meant to set up the bitmap while also ignoring the kernel.
 */
void pfalloc_init(MBINFO * mbinfo)
{
	multibootinfo = mbinfo;
	// Gets the first available.
	// I'm hoping there's nothing important stored at the base.
	MAPINFO * region = get_first_avail();
	// Calculates the size of the bitmap in bytes.
	length = GET_BYTE_COUNT(get_page_count());
	// Put the bitmap after the kernel.
	pages = region->base_addr;
	// Clears an area to store the bitmap array.
	memset(pages, 0, length);
	// Reserves the bitmap area.
	// This is a temporary fix as the first available memory region seems to include a lot of data that we cannot overwrite.
	// I will most probably change this interface to ignore the first memory section in the future.
	pfallocnset(0, 159/*GET_PAGE_COUNT(length)*/);
	// Calculates the kernel size.
	uint32_t kernel_size = (((uint32_t)&kernel_end) - ((uint32_t)&kernel_start));
	// Reserves the kernel area.
	pfallocnset(addr_to_page(&kernel_start), GET_PAGE_COUNT(kernel_size));
}

/*
 * Finds the first available page and returns the page number.
 * This function is O(n), we need to implement something quicker.
 */
uint32_t pfalloc_first_avail(void)
{

	for (int i = 0; i < length; i++)
	{
		// Does this byte have free pages?
		// if (__builtin_ffs(~pages[i]))
		{
			// return (i*8)+(__builtin_ffs(~pages[i]) - 1);
			for (int b = 0; b < 8; b++)
			{
				// Is this a free page?
				if ((~pages[i] >> b) & 1)
				{
					return (i*8)+b;
				}
			}
		}
	}
}

/*
 * Allocates and returns a pointer to the first available page.
 */
void * pfalloc_alloc(void)
{
	// We will try to keep track of free pages in the future for speed.
	// Find an available page.
	uint32_t page_num = pfalloc_first_avail();
	// Reserve the page.
	pfalloc_set(page_num);
	// Return the address.
	// May implement abiltity to map the page before hand.
	// This can save us memory in the future.
	return page_to_addr(page_num);
}

/*
 * Flips the state of the specified page.
 * Can be used to allocate and release pages.
 */
void pfalloc_set(uint32_t page_num)
{
	// Sets the page as used.
	pages[PAGE_TO_BYTE(page_num)] ^= SET_PAGE_MASK(page_num);
}

/*
 * Sets n pages from page_num.
 */
void pfallocnset(uint32_t page_num, size_t n)
{
	for (size_t i = 0; i < n; i++) pfalloc_set(page_num + i);
}

/*
 * Returns the amount of available pages in physical memory.
 * This is a temporary implementation and should be chnaged to deal with a global not a count loop.
 */
uint32_t avail_pages(void)
{
	uint32_t avail = 0;

	for (int i = 0; i < length; i++)
	{
		// Does this byte have free pages?
		// if (__builtin_ffs(~pages[i]))
		{
			// return (i*8)+(__builtin_ffs(~pages[i]) - 1);
			for (int b = 0; b < 8; b++)
			{
				// Is this a free page?
				if ((~pages[i] >> b) & 1)
				{
					avail += 1;
				}
			}
		}
	}
	return avail;
}