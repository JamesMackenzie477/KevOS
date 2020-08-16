#include "kernel.h"

// The entry point of the kernel.
void kernel_main(MBINFO * mbinfo)
{
	// We want to be able to access this wherever in the kernel.
	// multiboot_info = mbinfo;
	// Initialises the vga buffer so we can print to the screen.
	vgainit();
	// Initialises the physical memory manager.
	pfalloc_init(mbinfo);
	// Initialises paging for virtual memory mapping.
	init_paging();
	
	// Various kernel debug information.
	// Has the kernel been mapped correctly?
	kprintf("Value at &kernel_start: 0x%x\n", kernel_start);
	kprintf("Value at 0x%x: 0x%x\n", KERNEL_MAPPING_ADDR, *(uint32_t *)(KERNEL_MAPPING_ADDR));

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