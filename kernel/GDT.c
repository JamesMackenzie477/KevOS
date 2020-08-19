#include "GDT.h"

/*
 * This will be used with LGDT to describe the Global Descriptor Table.
 */
GDT_INFO info;

/*
 * The static Global Descriptor Table.
 */
uint8_t table[0x18];


/*
 * Encodes an entry for the Global Dispatch Table.
 */
void encode_entry(uint8_t * entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	// Adds the limit.
	*(uint16_t 	*)(&entry[0]) = limit & 0xFFFF;

	// Adds the flags.
	*(uint8_t 	*)(&entry[6]) = ((limit >> 16) & 0xF) | ((flags & 0xF) << 4);

	// Adds the base.
	*(uint16_t 	*)(&entry[2]) = (base) & 0xFFFF;
	*(uint8_t 	*)(&entry[4]) = (base >> 16) & 0xFF;
	*(uint8_t 	*)(&entry[7]) = (base >> 24) & 0xFF;

	// Adds the access byte.
	*(uint8_t 	*)(&entry[5]) = access;
}

/*
 * Initialises the Global Descriptor Table.
 */
void init_GDT(void)
{
	// Adds the default entries to the GDT.
	
	encode_entry(&table, 		NULL, 	NULL, 		NULL, NULL);	// Null descriptor.
	encode_entry(&table[0x8], 	0x0, 	0xFFFFF,	0x9A, 0xC);		// Code selector.
	encode_entry(&table[0x10], 	0x0, 	0xFFFFF,	0x92, 0xC); 	// Data selector.

	// Everything above is fine.
	// Somewhere below is causing the issue.

	// Sets the size of the GDT.
	info.limit = sizeof(table);
	// Sets the linear address of the GDT.
	info.base_addr = &table;

	GDT_INFO out;
	memset(&out, 0, sizeof(GDT_INFO));

	kprintf("limit: %d\n", info.limit);
	kprintf("base_addr: 0x%x\n", info.base_addr);

	// Uses LGDT to set the GDT register.
	__set_GDT(&info, &out);

	kprintf("limit: %d\n", out.limit);
	kprintf("base_addr: 0x%x\n", out.base_addr); // RETURNS INCORRECT BASE. This doesn't seem to cause the crash.

	// Reloads the segment registers.
	// __reload_seg_regs();
}