// Defines the multiboot header information.
.set MAGIC, 0x1BADB002
.set FLAGS, 0
.set CHECKSUM, -(MAGIC + FLAGS)

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

.type _start, @function
.type _set_page_dir, @function
.type _enable_paging, @function

_start:
	mov $stack_top, %esp
	call kernel_main
	cli
loop:
	hlt
	jmp loop

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