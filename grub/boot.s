// Defines the multiboot header information.
.set MAGIC,		0x1BADB002
.set ALIGN,		1<<0
.set MEM, 		1<<1
.set FLAGS,		ALIGN | MEM
.set CHECKSUM, 	-(MAGIC + FLAGS)

// Creates the multiboot header.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
 
 // Creates a stack so we can use C.
.section .bss
.align 16
.skip 16384
stack_top:
 
 // Sets up the stack and bridges to the C code.
.section .text

.global __start
.global __set_page_dir
.global __enable_paging
.global __enable_pae
.global __set_GDT
.global __reload_seg_regs

.type __start, @function
.type __set_page_dir, @function
.type __enable_paging, @function
.type __enable_pae, @function
.type __set_GDT, @function
.type __reload_seg_regs, @function

__start:
	mov $stack_top, %esp
	// Adds the address of the Multiboot information data structure.
	push %ebx
	call kernel_main
	cli
loop:
	hlt
	jmp loop

__enable_pae:
	push %ebp
	mov %esp, %ebp
	mov %cr4, %eax
	or $0x00000010, %eax
	mov %eax, %cr4
	mov %ebp, %esp
	pop %ebp
	ret

__enable_paging:
	push %ebp
	mov %esp, %ebp
	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0
	mov %ebp, %esp
	pop %ebp
	ret

__set_page_dir:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	mov %eax, %cr3
	mov %ebp, %esp
	pop %ebp
	ret

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