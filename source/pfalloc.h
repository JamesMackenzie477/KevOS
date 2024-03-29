#ifndef _PFALLOC_H
#define _PFALLOC_H

#include "stdio.h"

#define PAGE_SIZE 4096
#define BYTE_SIZE 8

#define GET_PAGE_NUM(	O		) (((uint32_t)O) / PAGE_SIZE)
#define GET_PAGE_COUNT(	BYTES 	) ((BYTES / PAGE_SIZE) + ((BYTES % PAGE_SIZE) > 0))
#define GET_BYTE_COUNT(	BYTES 	) ((BYTES / BYTE_SIZE) + ((BYTES % BYTE_SIZE) > 0))
#define SET_PAGE_MASK(	N 		) (0x1 << ((N % 8)))
#define PAGE_TO_BYTE(	N 		) (N / 8)

// These are used to determine the kernel size.
extern uint32_t kernel_start;
extern uint32_t kernel_end;

/*
 * These structure definitions are used to read the multiboot info.
 */

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
	char padd[40];
	uint32_t mmap_length;
	MAPINFO * mmap_addr;
} MBINFO;

/*
 * Public functions used to interact with the memory allocation system.
 */

void 		pfalloc_init		(MBINFO * 	mbinfo 		);
void * 		pfalloc_alloc		(void 					);
void 		pfalloc_release		(uintptr_t 	base_addr	);
void 		pfalloc_set			(uint32_t 	page_num 	);

#endif