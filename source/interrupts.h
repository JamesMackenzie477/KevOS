#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "stdio.h"
#include "keyboard.h"

#define IRTN(_R, _N, _E, ...) _R _N(__VA_ARGS__); extern _R _E(__VA_ARGS__);

/*
 * Declares all of the interrupts for the IDT to use.
 */
IRTN(void, irq_1, __irq_1, void)
IRTN(void, page_fault, __page_fault, uint32_t)
IRTN(void, double_fault, __double_fault, void)

extern void int0(void);
extern uint32_t __read_cr2(void);

void interrupt_handler(
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t,
	uint32_t
	);

/**
 * Syscalls.
 */
void 	syscall_printf	(	const char *, 	va_list					);
void 	syscall_return	(	uint32_t value							);
size_t 	syscall_fread	(	char * dst, size_t size, size_t count	);

#endif