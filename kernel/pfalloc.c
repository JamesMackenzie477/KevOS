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

MBINFO * multibootinfo;

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

// TEMP, will be replaced with a different array so type checking isn't needed.
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

// TEMP, will be replaced with a different array so type checking isn't needed.
uint32_t addr_to_page(void * addr)
{
	uint32_t page_nums = 0;
	// Gets the mapping info array.
	MAPINFO * info = multibootinfo->mmap_addr;
	// Iterates through the array.
	for (int i = 0; i < multibootinfo->mmap_length / sizeof(MAPINFO); i++)
	{
		if (info[i].type == 1)
		{

			if ((uint32_t)addr < (info[i].base_addr + info[i].length))
			{
				return GET_PAGE_NUM(((uint32_t)addr) - page_nums);
			}
		}
		else
		{
			page_nums += info[i].length;
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
	region = *get_first_avail();
	// Calculate the amount of pages available in memory.
	count = (region.length / PAGE_SIZE) / 8;
	// Put the bitmap after the kernel.
	pages = region.base_addr;
	// Clears an area to store the bitmap array.
	for (int i = 0; i < count; i++) pages[i] = 0;
	// Reserves the bitmap area.
	for (int i = 0; i < GET_PAGE_COUNT(count); i++) pfalloc_set(i);

	uint32_t kernel_size = (((uint32_t)&kernel_end) - ((uint32_t)&kernel_start));

	kprintf("kernel page: %d\n", addr_to_page(&kernel_start));
	kprintf("kernel page count: %d\n", GET_PAGE_COUNT(kernel_size));

	// Reserves the kernel area.
	// for (int i = GET_PAGE_NUM(&kernel_start); i < GET_PAGE_COUNT(kernel_size); i++) pfalloc_set(i);
}

uint32_t pfalloc_find_page(void)
{

	for (int i = 0; i < count; i++)
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
 * Allocates and returns a pointer to a page.
 */
void * pfalloc_alloc(void)
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

	uint32_t page_num = pfalloc_find_page();

	// Reserve the page.

	pfalloc_set(page_num);

	// Return the address.

	return page_to_addr(page_num);
}

/*
 * Flips the state of the specified page.
 * Can be used to allocate and release pages.
 * page_num can be anywhere from 0 to count.
 */
void pfalloc_set(uint32_t page_num)
{
	// Sets the page as used.
	pages[PAGE_TO_BYTE(page_num)] ^= SET_PAGE_MASK(page_num);
}

void pfalloc_rel(void * page)
{
	pfalloc_set(GET_PAGE_NUM(page));
}