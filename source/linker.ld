ENTRY(__start)

SECTIONS
{
	. = 1M;

	kernel_start = .;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		text_start = .;
		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		rodata_start = .;
		*(.rodata)
		disk_start = .;
		*(.disk)
	}
 
	.data BLOCK(4K) : ALIGN(4K)
	{
		data_start = .;
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		bss_start = .;
		*(COMMON)
		*(.bss)
	}

	/* Marks the end of the kernel so we can allocate memory around it. */
	kernel_end = .;
}