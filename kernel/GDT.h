#ifndef _GDT_H
#define _GDT_H

#include "stdio.h"

/*
 * Defines various specific GDT structures.
 */

typedef struct _GDT_INFO
{
	uint32_t base_addr;
	uint16_t limit;
} GDT_INFO;

typedef struct _GDT_ENTRY
{

} GDT_ENTRY;

/*
 * Assembly functions.
 */

extern void __set_GDT(GDT_INFO *);

/*
 * Enables the kernel to interact with the Global Descriptor Table.
 */

void init_GDT(void);
void encode_entry(uint8_t * entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

#endif