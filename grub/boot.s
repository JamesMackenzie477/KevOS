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
.global __read_port
.global __write_port
.global __read_msr

.type __start, @function
.type __read_port, @function
.type __write_port, @function
.type __read_msr, @function

__start:
	mov $stack_top, %esp
	// Adds the address of the Multiboot information data structure.
	push %ebx
	call kernel_main
	cli
loop:
	hlt
	jmp loop

__read_port:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %dx
	in %dx, %ax
	mov %ebp, %esp
	pop %ebp
	ret

__write_port:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %dx
	mov 12(%esp), %ax
	out %ax, %dx
	mov %ebp, %esp
	pop %ebp
	ret

__read_msr:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %ecx
	mov %eax, 12(%esp)
	mov %edx, 16(%esp)
	mov %ebp, %esp
	pop %ebp
	ret
