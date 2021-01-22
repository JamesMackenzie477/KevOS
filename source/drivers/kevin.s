.section .text

// Macro to create a new system call.
.macro sysdef name id=0 // argc=0

	.global \name
	.type \name, @function

	\name:
		// Understanding the Linux Kernel (Page 409 - Parameter Passing).
		// Registers to be used if arguments are 3 or less. Else we out the rest in a memory region pointed to by the final parameter.

		// .if (\argc == 1)

			// mov 4(%esp), %ebx

		// .elseif (\argc == 2)

			// mov 4(%esp), %ebx
			// mov 8(%esp), %esi

		// .elseif (\argc == 3)

			mov 4(%esp), %ebx
			mov 8(%esp), %esi
			mov 12(%esp), %edi

		// .elseif (\argc > 3)

			// mov 4(%esp), %ebx
			// mov 8(%esp), %esi
			// mov %esp+12, %edi

		// .endif

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
sysdef __printf 0x0 // 2
sysdef __fread 0x2 // 3