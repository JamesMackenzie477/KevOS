#ifndef _PFALLOC_H
#define _PFALLOC_H

#include "kernel.h"

#define PAGE_SIZE 4096
#define BYTE_SIZE 8

#define GET_PAGE_NUM(O) ((uint32_t)O / PAGE_SIZE)
#define GET_PAGE_COUNT(BYTES) ((BYTES / PAGE_SIZE) + ((BYTES % PAGE_SIZE) > 0))

#define GET_BYTE_COUNT(BYTES) ((BYTES / BYTE_SIZE) + ((BYTES % BYTE_SIZE) > 0))

#define SET_PAGE_MASK(N) (0x1 << ((N % 8)))
#define PAGE_TO_BYTE(N) (N / 8)

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
uint32_t pfalloc_find_page(void);
void * pfalloc_alloc(void);
void pfalloc_set(uint32_t page_num);
void pfalloc_rel(void * page);

#endif