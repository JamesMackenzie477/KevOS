#include "stdio.h"
#include "paging.h"

typedef struct _MBINFO
{
	uint32_t flags;
	char padd[40]; // NOT NEEDED YET.
	uint32_t mmap_length;
	uint32_t mmap_addr;
} MBINFO;

// The entry point of the kernel.
void kernel_main(MBINFO * mbinfo)
{
	// Initialises paging.
	// init_paging();
	// Initialises the vga buffer.
	vgainit();

	kprintf("WELCOME TO KEVIN...\n");

	// Validates the multiboot flags.
	if (mbinfo->flags & (1<<6))
	{
		kprintf("mbinfo: 0x%x\n", mbinfo);
		kprintf("mbinfo->flags: 0x%x\n", mbinfo->flags);
		kprintf("mbinfo->mmap_length: 0x%x\n", mbinfo->mmap_length);
		kprintf("mbinfo->mmap_addr: 0x%x\n", mbinfo->mmap_addr);
	}
}