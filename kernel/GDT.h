#ifndef _GDT_H
#define _GDT_H

#include "stdio.h"

/*
 * Defines the access byte options for a GDT entry.
 */

#define SEL_KER_CODE 0x9A
#define SEL_KER_DATA 0x92

#define SEL_USR_CODE 0xFA
#define SEL_USR_DATA 0xF2

#define SEL_TSS 0x89

/*
 * Defines the selector offsets.
 */

#define SEL_KER_DATA_ID 0x10

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

/**
 * Task State Segment.
 */
typedef struct _TSS_ENTRY
{
   uint32_t prev_tss;
   uint32_t esp0;
   uint32_t ss0;
   uint32_t esp1;
   uint32_t ss1;
   uint32_t esp2;
   uint32_t ss2;
   uint32_t cr3;
   uint32_t eip;
   uint32_t eflags;
   uint32_t eax;
   uint32_t ecx;
   uint32_t edx;
   uint32_t ebx;
   uint32_t esp;
   uint32_t ebp;
   uint32_t esi;
   uint32_t edi;
   uint32_t es;         
   uint32_t cs;        
   uint32_t ss;        
   uint32_t ds;        
   uint32_t fs;       
   uint32_t gs;         
   uint32_t ldt;      
   uint16_t trap;
   uint16_t iomap_base;
} __attribute__((packed)) TSS_ENTRY;

/*
 * Assembly functions.
 */

extern void __set_GDT(GDT_INFO *);
extern void __reload_seg_regs(void);
extern void __tss_flush(void);

/*
 * Enables the kernel to interact with the Global Descriptor Table.
 */

void GDT_init(void);

#endif