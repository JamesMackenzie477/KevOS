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

.global _start
.global _set_page_dir
.global _enable_paging
.global _enable_pae

.type _start, @function
.type _set_page_dir, @function
.type _enable_paging, @function
.type _enable_pae, @function

_start:
	mov $stack_top, %esp
	// Adds the address of the Multiboot information data structure.
	push %ebx
	call kernel_main
	cli
loop:
	hlt
	jmp loop

_enable_pae:
	push %ebp
	mov %esp, %ebp
	mov %cr4, %eax
	or $0x00000010, %eax
	mov %eax, %cr4
	mov %ebp, %esp
	pop %ebp
	ret

_enable_paging:
	push %ebp
	mov %esp, %ebp
	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0
	mov %ebp, %esp
	pop %ebp
	ret

_set_page_dir:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	mov %eax, %cr3
	mov %ebp, %esp
	pop %ebp
	ret