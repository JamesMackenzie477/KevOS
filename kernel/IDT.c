#include "IDT.h"

/*
 * This will be used with LIDT to describe the Interrupt Descriptor Table.
 */
static IDT_INFO info;

/*
 * The static Interrupt Descriptor Table.
 */
static IDT_ENTRY table[256] = { 0 };

/*
 * Encodes an entry for the Interrupt Descriptor Table.
 */
void IDT_add_entry(IDT_ENTRY * entry, uint32_t offset, uint16_t selector, uint8_t gate_type)
{
	// Adds the address of the routine.
	entry->offset_low 	= SHORT_INDEX(offset, 0);
	entry->offset_high 	= SHORT_INDEX(offset, 1);

	// Adds the selector.
	entry->selector 	= selector;

	// Zeros the unused part.
	entry->zero 		= NULL;

	entry->type_attr	= (gate_type & 0xF) | ATTR_STORAGE | ATTR_KERNEL | ATTR_PRESENT;
}

/*
 * Initialises the Interrupt Descriptor Table.
 */
void IDT_init(void)
{
	// Attempt to get excpeitons working.

	for (size_t i = 0; i < 0x1F; i++)
	{
		IDT_add_entry(&table[i], (uint32_t)&def_int, DEF_CODE_SEL, GATE_INT | GATE_TRAP);
	}

	// Triggers a divide by zero exception.
	// kprintf("%d\n", 0 / 0);

	// Sets the size of the IDT.
	info.limit = sizeof(table) - 1;
	// Sets the linear address of the IDT.
	info.base_addr = (uint32_t)&table;
	// Uses LIDT to set the IDT register.
	__set_IDT(&info);
}