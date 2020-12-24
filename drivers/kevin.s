.section .text

// Macro to define interrupt routines.
.macro __int f
.global __int_\f
.type __int_\f, @function
__int_\f:
	int $\f
	ret
.endm

__int 0xFF

.global __printf
.type __printf, @function
__printf:
	mov 4(%esp), %eax
	int $0xFF
	ret