#include "GDT.h"

/*
 * This will be used with LGDT to describe the Global Descriptor Table.
 */
static GDT_INFO info;

/*
 * The static Global Descriptor Table.
 */
static GDT_ENTRY table[3];

/*
 * Encodes an entry for the Global Descriptor Table.
 */
void GDT_add_entry(GDT_ENTRY * entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	// Adds the limit.
	entry->limit_low 		= SHORT_INDEX(limit, 0);
	// Adds the flags.
	entry->flags_limit_high = FLAGS_LIMIT_HIGH(limit, flags);
	// Adds the base.
	entry->base_low 		= SHORT_INDEX(base, 0);
	entry->base_mid 		= BYTE_INDEX(base, 2);
	entry->base_high 		= BYTE_INDEX(base, 3);
	// Adds the access byte.
	entry->access 			= access;
}

/*
 * Initialises the Global Descriptor Table.
 */
void GDT_init(void)
{
	// Adds the default entries to the GDT.
	
	GDT_add_entry(&table[0], 	NULL, 	NULL, 		NULL, 			NULL);					// Null descriptor.
	GDT_add_entry(&table[1], 	0x0, 	0xFFFFFFFF,	SEL_CODE, 	PAGE_GRAN | PROC_32);	// Code selector.
	GDT_add_entry(&table[2], 	0x0, 	0xFFFFFFFF,	SEL_DATA, 	PAGE_GRAN | PROC_32); 	// Data selector.
	// Task segment. Dummy segment.
	// Multithreading.
	// TAR ro filesystem.

	// Sets the size of the GDT.
	info.limit = sizeof(table) - 1;
	// Sets the linear address of the GDT.
	info.base_addr = (uint32_t)&table;
	// Uses LGDT to set the GDT register.
	__set_GDT(&info);
	// Reloads the segment registers.
	__reload_seg_regs();
}