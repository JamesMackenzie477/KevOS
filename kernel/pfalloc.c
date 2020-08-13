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
			else
			{
				size += info[i].length;
			}
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
	MAPINFO * region = get_first_avail();
	// Calculates the size of the bitmap in bytes.
	length = GET_BYTE_COUNT(get_page_count());
	// Put the bitmap after the kernel.
	pages = region->base_addr;
	// Clears an area to store the bitmap array.
	memset(pages, 0, length);
	// Reserves the bitmap area.
	pfallocnset(0, GET_PAGE_COUNT(length));

	uint32_t kernel_size = (((uint32_t)&kernel_end) - ((uint32_t)&kernel_start));

	kprintf("kernel page: %d\n", addr_to_page(&kernel_start));
	kprintf("kernel page count: %d\n", GET_PAGE_COUNT(kernel_size));

	// Reserves the kernel area.
	pfallocnset(addr_to_page(&kernel_start), GET_PAGE_COUNT(kernel_size));
}

uint32_t pfalloc_find_page(void)
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

void pfallocnset(uint32_t page_num, size_t n)
{
	for (size_t i = 0; i < n; i++) pfalloc_set(page_num + i);
}

void pfalloc_rel(void * page)
{
	pfalloc_set(GET_PAGE_NUM(page));
}