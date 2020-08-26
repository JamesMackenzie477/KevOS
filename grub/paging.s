.section .text

.global __set_page_dir
.global __enable_paging
.global __enable_pae

.type __set_page_dir, @function
.type __enable_paging, @function
.type __enable_pae, @function

__enable_pae:
	push %ebp
	mov %esp, %ebp
	mov %cr4, %eax
	or $0x00000010, %eax
	mov %eax, %cr4
	mov %ebp, %esp
	pop %ebp
	ret

__enable_paging:
	push %ebp
	mov %esp, %ebp
	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0
	mov %ebp, %esp
	pop %ebp
	ret

__set_page_dir:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	mov %eax, %cr3
	mov %ebp, %esp
	pop %ebp
	ret