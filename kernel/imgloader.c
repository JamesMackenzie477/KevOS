#include "imgloader.h"

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

/**
 * Loads the given elf64 file.
 * This should essentially map the file into memory and then add the pointers to the correct kernel functions.
 */
uintptr_t il_load_elf64(posix_header * f)
{
	// Gets the file header.
	elf_header * pfile = (elf_header *)(f + 1);
	// Checks if the file is infact an elf64.
	if (pfile->magic != IL_ELF_MAGIC) return NULL;

	// Parses the file and rebases it.

	kprintf("Entry point: 0x%x\n", ((uintptr_t)pfile) + pfile->entry);
	kprintf("Program header table: 0x%x\n", ((uintptr_t)pfile) + pfile->phoff);
	kprintf("Section header table: 0x%x\n", ((uintptr_t)pfile) + pfile->shoff);
	kprintf("Sections:\n");

	// Gets the section header.
	section_header * psec = il_get_sh(pfile);
	// Iterates through the sections.
	for (int i = 1; psec[i].type != NULL; i++)
	{
		kprintf("- %s\n", il_get_strtab(pfile) + psec[i].name);
	}

	return 1;
}