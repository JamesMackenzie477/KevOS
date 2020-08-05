#ifndef _PFALLOC_H
#define _PFALLOC_H

#include "stdio.h"

#define PAGE_SIZE 4096

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

void pfalloc_init(uint8_t * base, uint32_t size);

#endif