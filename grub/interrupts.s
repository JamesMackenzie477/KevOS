.section .text

.global __set_GDT
.global __reload_seg_regs
.global __set_IDT
.global __sti
.global __irq_1
.global __def_int

.type __set_GDT, @function
.type __reload_seg_regs, @function
.type __set_IDT, @function
.type __sti, @function
.type __irq_1, @function
.type __def_int, @function

__set_GDT:
	mov 4(%esp), %eax
	lgdt (%eax)
	ret

__reload_seg_regs:
	ljmp $0x08, $reload_cs
reload_cs:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret

__set_IDT:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

__sti:
	sti
	ret

/*
 * Assembly wrappers for all of the interrupt handlers.
 */

__irq_1:
	cli			// Disables interrupts.
	pusha 		// Saves the registers state.
	push %ds 	// Saves the ds register.

	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	call irq_1 	// Handles the interrupt.

	pop %ds 	// Restores the ds register.
	popa 		// Restores the registers state.
	sti 		// Enables interrupts.
	// set piece of memoryregister to certain value and then check it during execution.

	iret		// Special return instruction for interrupts only.

__def_int:
	call irq_1
	iret