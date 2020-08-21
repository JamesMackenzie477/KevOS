#include "GDT.h"

/*
 * This will be used with LGDT to describe the Global Descriptor Table.
 */
GDT_INFO info;

/*
 * The static Global Descriptor Table.
 */
GDT_ENTRY table[3];


/*
 * Encodes an entry for the Global Dispatch Table.
 */
void encode_entry(GDT_ENTRY * entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	// Adds the limit.
	entry->limit_low = limit & 0xFFFF;

	// Adds the flags.
	entry->flags_limit_high = ((limit >> 16) & 0xF) | ((flags & 0xF) << 4);

	// Adds the base.
	entry->base_low = (base) & 0xFFFF;
	entry->base_mid = (base >> 16) & 0xFF;
	entry->base_high = (base >> 24) & 0xFF;

	// Adds the access byte.
	entry->access = access;
}

/*
 * Initialises the Global Descriptor Table.
 */
void init_GDT(void)
{
	// Adds the default entries to the GDT.
	
	encode_entry(&table[0], 	NULL, 	NULL, 		NULL, NULL);	// Null descriptor.
	encode_entry(&table[1], 	0x0, 	0xFFFFFFFF,	0x9A, 0xC);		// Code selector.
	encode_entry(&table[2], 	0x0, 	0xFFFFFFFF,	0x92, 0xC); 	// Data selector.

	// Sets the size of the GDT.
	info.limit = sizeof(table) - 1;
	// Sets the linear address of the GDT.
	info.base_addr = (uint32_t)&table;
	// Uses LGDT to set the GDT register.
	__set_GDT(&info);
	// Reloads the segment registers.
	__reload_seg_regs();
}