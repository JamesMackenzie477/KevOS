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

	// Adds the keyboard interrupt.
	IDT_add_entry(&table[0x8], (uint32_t)&__irq_1, DEF_CODE_SEL, GATE_INT);

	// Sets the size of the IDT.
	info.limit = sizeof(table) - 1;
	// Sets the linear address of the IDT.
	info.base_addr = (uint32_t)&table;
	// Uses LIDT to set the IDT register.
	__set_IDT(&info);
	// Enables hardware interrupts.
	// __cli_sti();
}