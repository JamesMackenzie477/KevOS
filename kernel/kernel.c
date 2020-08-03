#include "stdio.h"
#include "paging.h"

#define MMAP (1 << 6)
#define VALIDATE_FLAGS(F) (F & MMAP)


typedef struct _MAPINFO
{
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} MAPINFO;

typedef struct _MBINFO
{
	uint32_t flags;
	char padd[40]; // NOT NEEDED YET.
	uint32_t mmap_length;
	MAPINFO * mmap_addr;
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
	if (VALIDATE_FLAGS(mbinfo->flags))
	{
		kprintf("mbinfo: 0x%x\n", mbinfo);
		kprintf("mbinfo->flags: 0x%x\n", mbinfo->flags);
		kprintf("mbinfo->mmap_length: 0x%x\n", mbinfo->mmap_length);
		kprintf("mbinfo->mmap_addr: 0x%x\n", mbinfo->mmap_addr);

		// kprintf("mbinfo->mmap_addr: 0x%x\n", ((MAPINFO *)(mbinfo->mmap_addr + (*(uint32_t *)mbinfo->mmap_addr)))->base_addr);

		MAPINFO * info = mbinfo->mmap_addr;

		for (int i = 0; i < mbinfo->mmap_length / sizeof(MAPINFO); i++)
		{
			kprintf("info[%d].base_addr: 0x%l", i, info[i].base_addr);
			kprintf(" info[%d].length: 0x%x\n", i, info[i].length);
		}

		// kprintf("mbinfo->mmap_addr[0].size: 0x%x\n", info[0].length);

		//info += 0x14 + 0x4;

		// kprintf("mbinfo->mmap_addr[0].size: 0x%x\n", info[1].base_addr);

		/*for (int i = 0; i < mbinfo->mmap_length / sizeof(uint32_t); i++)
		{
			kprintf("0x%x ", ((uint32_t*)mbinfo->mmap_addr)[i]);
		}*/
	}
}