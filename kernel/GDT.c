#include "GDT.h"

/*
 * This will be used with LGDT to describe the Global Descriptor Table.
 */
GDT_INFO info;

/*
 * The static Global Descriptor Table.
 */
uint8_t table[0x32];


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
	
	encode_entry(&table, 		NULL, 	NULL, 		NULL, NULL);
	encode_entry(&table[0x8], 	0x0, 	0xFFFFF,	0x9A, 0xC);
	encode_entry(&table[0x10], 	0x0, 	0xFFFFF,	0x92, 0xC);

	// Sets the linear address of the GDT.
	info.base_addr = &table;
	// Sets the size of the GDT.
	info.limit = sizeof(table);
	// Uses LGDT to set the GDT register.
	__set_GDT(&info);
}