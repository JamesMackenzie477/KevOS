#include "imgloader.h"

/**
 * Returns the program headers array of the specified elf file.
 */
static inline program_header * il_get_ph(elf_header * pfile)
{
	return (program_header *)(((uintptr_t)pfile) + pfile->phoff);
}

/**
 * Returns the section headers array of the specified elf file.
 */
static inline section_header * il_get_sh(elf_header * pfile)
{
	return (section_header *)(((uintptr_t)pfile) + pfile->shoff);
}

/**
 * Finds the address of the .shstrtab section.
 */
char * il_get_strtab(elf_header * pfile)
{
	// Gets the section header.
	section_header * psec = il_get_sh(pfile);
	// Iterates through the sections.
	for (int i = 1; psec[i].type != NULL; i++)
	{
		// Is it a string table?
		if (psec[i].type == 3)
		{
			// Calculates the string table address.
			char * strtab = (char *)(((uintptr_t)pfile) + psec[i].offset);
			// Compares the section name.
			if (strcmp(strtab + psec[i].name, ".shstrtab") == 0)
			{
				// Returns the table address.
				return strtab;
			}
		}
	}
}

static inline void memcpy(uint8_t * _Dst, uint8_t * _Src, size_t _Sz)
{
	for (int i = 0; i < _Sz; i++)
	{
		_Dst[i] = _Src[i];
	}
}

/**
 * Loads the given elf64 file.
 * This should essentially map the file into memory and then add the pointers to the correct kernel functions.
 */
uint32_t * il_load_elf64(posix_header * f)
{
	// Stores the base address of the program.
	uint32_t * pbase = NULL;
	// Gets the file header.
	elf_header * pfile = (elf_header *)(f + 1);
	// Checks if the file is infact an elf64.
	if (pfile->magic != IL_ELF_MAGIC) return NULL;

	// Parses the file and rebases it.
	// kprintf("Program header table: 0x%x\n", ((uintptr_t)pfile) + pfile->phoff);
	// kprintf("Section header table: 0x%x\n", ((uintptr_t)pfile) + pfile->shoff);

	// kprintf("Headers:\n");
	// Gets the program header.
	program_header * ppro = il_get_ph(pfile);
	// Iterates through the program headers.
	for (int i = 0; ppro[i].type != NULL; i++)
	{
		// kprintf("- Type: 0x%x ", ppro[i].type);
		// kprintf("Offset: 0x%x ", ppro[i].offset);
		// kprintf("Size: 0x%x\n", ppro[i].filesz);
		// Is this a loadable segment?
		if (ppro[i].type == PT_LOAD)
		{
			// Loads the loadable segment.
			// Allocates memory.
			pbase = (uint32_t *)pfalloc_alloc();
			// Moves program into memory.
			memcpy(pbase, ((uintptr_t)pfile) + ppro[i].offset, ppro[i].filesz);
			// Virtualises the memory...
		}
	}

	/*kprintf("Sections:\n");
	// Gets the section header.
	section_header * psec = il_get_sh(pfile);
	// Iterates through the sections.
	for (int i = 1; psec[i].type != NULL; i++)
	{
		kprintf("- %s ", il_get_strtab(pfile) + psec[i].name);
		kprintf("Type: 0x%x ", psec[i].type);
		kprintf("Offset: 0x%x\n", psec[i].offset);
	}*/

	// Calls the entry point.
	kprintf("Calling entry...\n");
	// Sets the virtual base to point to the allocated program in memory.
	paging_map_page(IL_DEF_BASE, paging_virtual_to_physical(pbase), PAGE_PRESENT | PAGE_RW);
	entry_t entry = (entry_t)(pfile->entry);
	kprintf("Program returned: %s\n", entry());
	// Switch to kernel paging dir when we come back. 
	paging_map_page(IL_DEF_BASE, IL_DEF_BASE, PAGE_PRESENT | PAGE_RW);

	// Deallocate program memory.

	return pbase;
}