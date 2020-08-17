#include "GDT.h"

/*
 * This will be used with LGDT to describe the Global Descriptor Table.
 */
GDT_INFO info;

/*
 * Initialises the Global Descriptor Table.
 */
void init_GDT(void)
{
	// Sets the linear address of the GDT.
	info.base_addr = NULL;
	// Sets the size of the GDT.
	info.limit = NULL;
	// Uses LGDT to set the GDT register.
	__set_GDT(&info);
}