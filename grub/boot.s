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
.type _start, @function
_start:
	mov $stack_top, %esp
	call kernel_main
	cli
loop:
	hlt
	jmp loop