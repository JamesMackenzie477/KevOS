.section .text

.global __syshandler
.type __syshandler, @function

// Handles calls to sysenter.
__syshandler:
	// Lets index the sysid into an array of system calls and then call the handler with the user stack.
	// Use syscall calling convention, pushing the number of parameters so we can move them onto the kernel stack.
	// Pushes the user stack pointer so stack arguments can be read.
	// Arguments. TEMP!
	push %edx
	push %ecx
	push %edi
	push %esi
	push %ebx
	// Gets the system call table.
	lea syscall_table, %edx
	// Generates the correct offset.
	shl $0x2, %eax
	// Indexes with the syscall id.
	add %eax, %edx
	// Calls the syscall.
	call (%edx)
	// Restores the arguments.
	pop %ebx
	pop %esi
	pop %edi
	pop %ecx
	pop %edx
	sti
	// Returns to usermode.
	sysexit

// Handler wrappers that identify with the id and perform the necessary prolog to set up the arguments for the actul call.
// We should zero 