#ifndef _PFALLOC_H
#define _PFALLOC_H

#include "kernel.h"

#define PAGE_SIZE 4096

#define GET_PAGE_NUM(O) (O / PAGE_SIZE)
#define GET_PAGE_COUNT(S) (GET_PAGE_NUM(S) + ((S % PAGE_SIZE) ? 1 : 0))

#define PFALLOC_FIRST -1

typedef struct _MEMORY_REGION
{
	uint32_t * base;
	uint64_t size;
} MEMORY_REGION;

typedef struct _MAPINFO
{
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} MAPINFO;

typedef struct _MBINFO
{
	uint32_t flags;
	char padd[40]; // NOT NEEDED YET.
	uint32_t mmap_length;
	MAPINFO * mmap_addr;
} MBINFO;

// We are storing a pointer to the multiboot header in case it is needed anywhere else.
// MBINFO * multiboot_info;

void pfalloc_init(MBINFO * mbinfo);
void * pfalloc_res(void * base, uint32_t pages);

#endif