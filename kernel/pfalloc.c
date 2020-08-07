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
	// Gets the memory region.
	// This will be changed to a selection of multiple regions in the future.
	region = mbinfo->mmap_addr[0];
	// Calculate the amount of pages available in memory.
	count = (region.length / PAGE_SIZE) / 8;
	// Put the bitmap after the kernel.
	pages = region.base_addr;
	// Clears an area to store the bitmap array.
	for (int i = 0; i < count; i++) pages[i] = 0;
	// Reserves the bitmap area.
	for (int i = 0; i < GET_PAGE_COUNT(count); i++) pfalloc_set(i);
	// for (int i = 0; i < count; i++) kprintf("%x", pages[i]);
}

/*
 * Allocates and returns a pointer to n amount of pages.
 */
void * pfalloc_alloc(void * base, uint32_t pages)
{
	// Allocates the first piece of available memory of the correct size.
	
	/*switch ((uint32_t)base)
	{
		case PFALLOC_FIRST:
			break;
		default:
			break;
	}*/

	// Find an available page.

	uint32_t page_num = 0 /*pfalloc_find_page()*/;

	// Reserve the page.

	pfalloc_set(page_num);

	// Return the address.

	return NULL;
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