.section .text

// Macro to create a new system call.
.macro sysdef name id=0
	.global \name
	.type \name, @function
	\name:
		// Arguments.
		mov 4(%esp), %ebx
		mov 8(%esp), %esi
		mov 12(%esp), %edi
		// The system call id to invoke.
		mov $\id, %eax
		// Tells the kernel the return address.
		pop %edx
		// Passes the user stack to the kernel.
		mov %esp, %ecx
		// Trap to the kernel.
		sysenter	
.endm

// Creates a new syscall called printf that triggers the zeroth system function.
sysdef __printf 0x0
sysdef __fread 0x2