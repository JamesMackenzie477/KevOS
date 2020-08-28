.section .text

.global __set_GDT
.global __reload_seg_regs
.global __set_IDT
.global __cli_sti
.global __irq_1

.type __set_GDT, @function
.type __reload_seg_regs, @function
.type __set_IDT, @function
.type __cli_sti, @function
.type __irq_1, @function

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

__cli_sti:
	cli
	sti
	ret

/*
 * Assembly wrappers for all of the interrupt handlers.
 */

__irq_1:
	call irq_1
	iret