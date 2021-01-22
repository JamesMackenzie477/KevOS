#include "interrupts.h"

/**
 * Syscall table to be indexed via the handler.
 */
uint32_t syscall_table[] = {
	(uint32_t)&syscall_printf,
	(uint32_t)&syscall_return,
	(uint32_t)&syscall_fread
};

void page_fault(uint32_t err)
{
	kprintf("page fault at address 0x%x ", __read_cr2());
	kprintf("code: 0x%x\n", err);
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

/**
 * Handles system calls.
 */
size_t syscall_fread(char * dst, size_t size, size_t count)
{
	// Stores the amount of characters.
	size_t i;
	// Gets the characters from the keyboard buffer.
	for (i = 0; i < count; i++)
	{
		// Gets the next character from the keyboard buffer.
		uint8_t k = /*keyboard_getc()*/NULL;
		// If a character was pressed then add it to the output.
		if (k) dst[i] = k;
		// Else we return null;
		else return NULL;
	}
	// Returns the amount of characters written.
	return i;
}

/**
 * Handles system calls.
 */
void syscall_return(uint32_t value)
{
	kprintf("RETURN...");
	for(;;);
}

/**
 * Handles system calls.
 */
void syscall_printf(const char * s, va_list f)
{
	stdio_print(s, f);
}