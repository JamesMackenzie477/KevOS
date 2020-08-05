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
 * Initialises pfalloc with an array of available memory regions.
 * This function is meant to set up the bitmap while also ignoring the kernel.
 */
void pfalloc_init(uint8_t * base, uint32_t size)
{
	pages = base;
	// Calculate the amount of pages available in memory.
	count = size / PAGE_SIZE;
	// Clears an area to store the bitmap array.
	for (int i = 0; i < count; i++) pages[i] = 0;

	// Offsets into the base address to ignore the kernel.
	// Allocate the bitmap using the regions that we are given.
}

/*
 * Allocates and returns a pointer to n amount of pages.
 */
void * pfalloc_alloc(uint32_t pages)
{
	return NULL;
}

/*
 * Allocates and returns a pointer to n amount of pages.
 */
void * pfalloc_res(void * base, uint32_t pages)
{
	return NULL;
}