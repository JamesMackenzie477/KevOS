#ifndef _GDT_H
#define _GDT_H

#include "stdio.h"

/*
 * Defines various specific GDT structures.
 */

typedef struct _GDT_INFO
{
	uint16_t limit;
	uint32_t base_addr;
} GDT_INFO;

/*
 * Assembly functions.
 */

extern void __set_GDT(GDT_INFO *, GDT_INFO *);
extern void __reload_seg_regs(void);

/*
 * Enables the kernel to interact with the Global Descriptor Table.
 */

void init_GDT(void);
void encode_entry(uint8_t * entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

#endif