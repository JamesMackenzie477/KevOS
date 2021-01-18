.section .text

.global __set_GDT
.global __reload_seg_regs
.global __set_IDT
.global __sti
.global __tss_flush
.global __r3_execute
.global __read_eflags
.global __r3_bootstrap_start
.global __r3_bootstrap_end

.type __set_GDT, @function
.type __reload_seg_regs, @function
.type __set_IDT, @function
.type __sti, @function
.type __tss_flush, @function
.type __r3_execute, @function
.type __read_eflags, @function

// Macro to define interrupt routines.
.macro irtn f
.global __\f
.type __\f, @function
__\f:
	cli
	/*pusha
	push %ds
	push %eax
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs*/
	call \f
	/*pop %eax
	pop %ds
	popa*/
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

__tss_flush:
   mov $0x2B, %ax
   ltr %ax
   ret

__r3_execute:
	mov $0x23, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp, %eax
	push $0x23
	push %eax
	pushf
	push $0x1B
	push 4(%eax)
	mov 8(%eax), %eax
	iret


.align 0x1000

// Could be its own executable.
__r3_bootstrap_start:
	// Calls the program entry.
	call %eax
	// Cleans up and jumps back to kernel mode.
__no_ret:
	jmp __no_ret

	mov $2, %eax
	sysenter


__r3_bootstrap_end:

.align 0x1000


__read_eflags:
	pushf
	pop %eax
	ret

/*
 * Assembly wrappers for all of the interrupt handlers.
 */

irtn irq_1
irtn page_fault
irtn double_fault
irtn printf