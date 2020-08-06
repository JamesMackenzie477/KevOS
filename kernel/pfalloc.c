#include "pfalloc.h"

/*
 * The bitmap array where we can track page allocation.
 */
uint8_t * pages;

/*
 * The amount of pages stored in the bitmap.
 */
uint32_t count;

/*
 * The region in which we allocate memory.
 */
MAPINFO region;

/*
 * Initialises pfalloc with an array of available memory regions.
 * This function is meant to set up the bitmap while also ignoring the kernel.
 */
void pfalloc_init(MBINFO * mbinfo)
{
	// Calculates the size of the kernel.
	// uint32_t kernel_size = (((uint32_t)&kernel_end) - ((uint32_t)&kernel_start));

	// Gets the memory region.
	// This will be changed to a selection of multiple regions in the future.
	region = mbinfo->mmap_addr[0];

	// Calculate the amount of pages available in memory.
	count = (region.length / PAGE_SIZE) / sizeof(uint8_t);
	// Put the bitmap after the kernel.
	pages = region.base_addr;
	// Clears an area to store the bitmap array.
	for (int i = 0; i < count; i++) pages[i] = 0;
	// Reserves the bitmap area.
	pfalloc_res(pages, count);

	kprintf("%d\n", GET_PAGE_COUNT(count));
	for (int i = 0; i < count; i++)
	{
		kprintf("%x", pages[i]);
	}
}

/*
 * Allocates and returns a pointer to n amount of pages.
 */
void * pfalloc_alloc(void * base, uint32_t pages)
{
	// Allocates the first piece of available memory of the correct size.
	
	switch ((uint32_t)base)
	{
		case PFALLOC_FIRST:
			break;
		default:
			break;
	}

	return NULL;
}

/*
 * Allocates and returns a pointer to n amount of pages.
 */
void * pfalloc_res(void * base, uint32_t size)
{
	// Gets the byte offset from the region.
	uint32_t offset = base - region.base_addr;
	// Gets the page number.
	uint32_t page_num = GET_PAGE_NUM(offset) + 1;

	kprintf("page_num: %d\n", page_num);
	// Gets the page count.
	uint32_t page_count = GET_PAGE_COUNT(size);

	uint32_t page_off = (page_num / 8) + ((page_num % 8) ? 1 : 0);

	// Sets the bits.
	pages[page_off - 1] = pages[page_off - 1] | (0xFF << (8 - (page_num % 8))) & 0xFF;

	// int i = 0;
	// Reserves the pages.
	// for (; i < (page_count / 8); i++) pages[page_off + i] = 0xFF;

	// pages[page_off + i] = pages[page_off + i] | (0xFF << (8 - (page_count % 8))) & 0xFF;

	// Returns the address.
	return base;
}