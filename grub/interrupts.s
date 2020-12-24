.section .text

.global __set_GDT
.global __reload_seg_regs
.global __set_IDT
.global __sti

.type __set_GDT, @function
.type __reload_seg_regs, @function
.type __set_IDT, @function
.type __sti, @function

// Macro to define interrupt routines.
.macro irtn f
.global __\f
.type __\f, @function
__\f:
	cli
	pusha
	push %ds
	push %eax
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	call \f
	pop %eax
	pop %ds
	popa
	sti
	iret
.endm

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

irtn irq_1
irtn double_fault
irtn printf