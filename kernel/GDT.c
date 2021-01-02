#include "GDT.h"

/*
 * This will be used with LGDT to describe the Global Descriptor Table.
 */
static GDT_INFO info;

/*
 * The static Global Descriptor Table.
 */
static GDT_ENTRY table[6];

/*
 * The task state segment.
 */
static TSS_ENTRY tss;

/*
 * Kernel Stack.
 */
static uint32_t stack[4096];

void syscall(void)
{
	kprintf("SYSCALL...");
	for (;;);
}

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

	// Kernel mode.
	GDT_add_entry(&table[1], 	0x0, 	0xFFFFFFFF,	SEL_KER_CODE, 	GDT_PAGE_GRAN | GDT_PROC_32);	// Code selector.
	GDT_add_entry(&table[2], 	0x0, 	0xFFFFFFFF,	SEL_KER_DATA, 	GDT_PAGE_GRAN | GDT_PROC_32); 	// Data selector.

	// User mode.
	GDT_add_entry(&table[3], 	0x0, 	0xFFFFFFFF,	SEL_USR_CODE, 	GDT_PAGE_GRAN | GDT_PROC_32);	// User code selector.
	GDT_add_entry(&table[4], 	0x0, 	0xFFFFFFFF,	SEL_USR_DATA, 	GDT_PAGE_GRAN | GDT_PROC_32); 	// User data selector.

	// Task state segment.
	memset(&tss, 0, sizeof(tss));

	tss.ss0	= SEL_KER_DATA_ID; // Kernel data selector.
	tss.esp0 = &stack;

	//tss.cs = 0x0b;
	//tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x13;

	GDT_add_entry(&table[5], &tss, sizeof(tss), SEL_TSS, NULL);

	// Multithreading.

	// CMD is a usermode task
	// Launch it at start up and then use interrupts to interact with the kernel.
	// Programs get their own stack.
	// Programs get their own page table with the kernel mapped into memory.

	// Sets the parameters for sysenter.
	//__write_msr(IA32_SYSENTER_CS, 	0x8, NULL);
	//__write_msr(IA32_SYSENTER_ESP,	(uint32_t)&stack, NULL);
	//__write_msr(IA32_SYSENTER_EIP,	(uint32_t)&syscall, NULL);

	// kprintf("Interrupts Enabled: %d\n", (__read_eflags() >> 9) & 1);

	// Sets the size of the GDT.
	info.limit = sizeof(table) - 1;
	// Sets the linear address of the GDT.
	info.base_addr = (uint32_t)&table;
	// Uses LGDT to set the GDT register.
	__set_GDT(&info);
	// Reloads the segment registers.
	__reload_seg_regs();
	// Flushes the TSS.
	__tss_flush();
}