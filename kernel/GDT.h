#ifndef _GDT_H
#define _GDT_H

#include "stdio.h"

/*
 * Defines the access byte options for a GDT entry.
 */

#define SEL_CODE 0x9A
#define SEL_DATA 0x92

#define SEL_USER_CODE 0xFA
#define SEL_USER_DATA 0xF2

/*
 * Defines the flags for a GDT entry.
 */

#define GDT_AVAIL		1
#define GDT_PAGE_GRAN	8
#define GDT_PROC_32		4

/*
 * Allows for a simple concatenation of the high limit and flags. 
 */

#define FLAGS_LIMIT_HIGH(LIMIT, FLAGS) ((BYTE_INDEX(LIMIT, 2) & 0xF) | ((FLAGS & 0xF) << 4))

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

void GDT_init(void);

#endif