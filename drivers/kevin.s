.section .text

.global __printf
.global __syscall

.type __printf, @function
.type __syscall, @function

__printf:
	mov 4(%esp), %eax
	int $0xFF
	ret

__syscall:
	mov 4(%esp), %eax
	pop %edx
	mov %esp, %ecx
	sysenter