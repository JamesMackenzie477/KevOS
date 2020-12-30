#include "interrupts.h"

/*
 * This is the default interrupt.
 * Can be used as a placeholder.
 */
void printf(const char * str)
{
	kprintf("%s", str);
}

void double_fault(void)
{
	kprintf("double fault.\n");
	for (;;);
}

void irq_1()
{
	// Calls the keyboard handler.
	keyboard_handler();
}

/**
 * Interrupt dispatcher.
 */
void interrupt_handler(
	uint32_t edi,
	uint32_t esi,
	uint32_t ebp,
	uint32_t esp,
	uint32_t ebx,
	uint32_t edx,
	uint32_t ecx,
	uint32_t eax,
	uint32_t irq,
	uint32_t err)
{
	kprintf("Exception triggered: 0x%x\n", irq);
	//for (;;);
}