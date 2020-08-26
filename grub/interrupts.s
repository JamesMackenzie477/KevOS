.section .text

.global __set_GDT
.global __reload_seg_regs
.global __set_IDT
.global __enable_ints
.global __irq_1

.type __set_GDT, @function
.type __reload_seg_regs, @function
.type __set_IDT, @function
.type __enable_ints, @function
.type __irq_1, @function

__set_GDT:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	lgdt (%eax)
	mov %ebp, %esp
	pop %ebp
	ret

__reload_seg_regs:
	push %ebp
	mov %esp, %ebp

	ljmp $0x08, $reload_cs
reload_cs:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	mov %ebp, %esp
	pop %ebp
	ret

__set_IDT:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	lidt (%eax)
	mov %ebp, %esp
	pop %ebp
	ret

__enable_ints:
	push %ebp
	mov %esp, %ebp
	sti
	mov %ebp, %esp
	pop %ebp
	ret

/*
 * Assembly wrappers for all of the interrupt handlers.
 */

__irq_1:
	call irq_1
	iret