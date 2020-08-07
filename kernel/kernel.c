#include "kernel.h"

// The entry point of the kernel.
void kernel_main(MBINFO * mbinfo)
{
	// We want to be able to access this wherever in the kernel.
	// multiboot_info = mbinfo;

	// Initialises paging.
	// init_paging();

	// Initialises the vga buffer.
	vgainit();

	// Reserve pages for the kernel.
	pfalloc_init(mbinfo);

	// Various kernel debug information.
	kprintf("\nKernel is mapped at: 0x%x\n", &kernel_start);
	kprintf("Kernel size: %d bytes\n", (((uint32_t)&kernel_end) - ((uint32_t)&kernel_start)));
	kprintf("Free memory starts at: 0x%x\n", &kernel_end);
	kprintf("Multiboot Info: 0x%x\n\n", mbinfo);

	// Allocates a page of 1024 bytes.
	void * page = pfalloc_alloc();

	kprintf("Page allocated at: 0x%x\n", page);

	// Release the page.
	pfalloc_rel(page);

	// Allocates a page of 1024 bytes.
	page = pfalloc_alloc();

	kprintf("Page allocated at: 0x%x\n", page);

	// Release the page.
	pfalloc_rel(page);

	// Checks if memory mappings is included in multiboot info.
	/*if (VALIDATE_FLAGS(mbinfo->flags))
	{
		kprintf("AVAILABLE MEMORY REGIONS\n");
		kprintf("------------------------\n");
		// Gets the mapping info array.
		MAPINFO * info = mbinfo->mmap_addr;
		// Iterates through the array.
		for (int i = 0; i < mbinfo->mmap_length / sizeof(MAPINFO); i++)
		{
			if (info[i].type != 1) continue;
			// Prints avilable memory regions.
			kprintf("info[%d]\n", i);
			kprintf(" - base_addr: 0x%x\n", info[i].base_addr);
			kprintf(" - length: 0x%x\n", info[i].length);
			kprintf(" - type: 0x%x\n", info[i].type);
			kprintf(" - pages: %d\n", info[i].length / 4096);
		}
	}*/
}