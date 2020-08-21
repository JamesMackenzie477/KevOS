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
} __attribute__((packed)) GDT_INFO;

typedef struct _GDT_ENTRY
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t flags_limit_high;
	uint8_t base_high;
} __attribute__((packed)) GDT_ENTRY;

/*
 * Assembly functions.
 */

extern void __set_GDT(GDT_INFO *);
extern void __reload_seg_regs(void);

/*
 * Enables the kernel to interact with the Global Descriptor Table.
 */

void init_GDT(void);

#endif