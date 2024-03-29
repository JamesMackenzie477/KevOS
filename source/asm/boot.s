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
stack_bottom:
.align 16
.skip 16384
stack_top:
 
 // Sets up the stack and bridges to the C code.
.section .text

.global __start
.global __read_port
.global __write_port
.global __read_msr
.global __write_msr

.global stack_top

.type __start, @function
.type __read_port, @function
.type __write_port, @function
.type __read_msr, @function
.type __write_msr, @function

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
	mov 4(%esp), %dx
	in %dx, %al
	ret

__write_port:
	mov 4(%esp), %dx
	mov 8(%esp), %al
	out %al, %dx
	ret

__read_msr:
	mov 4(%esp), %ecx
	rdmsr
	mov 8(%esp), %ecx
	mov %eax, (%ecx)
	mov 12(%esp), %ecx
	mov %edx, (%ecx)
	ret

__write_msr:
	mov 4(%esp), %ecx
	mov 8(%esp), %eax
	mov 12(%esp), %edx
	wrmsr
	ret