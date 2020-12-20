#include "imgloader.h"

/**
 * Loads the given elf64 file.
 * This should essentially map the file into memory and then add the pointers to the correct kernel functions.
 */
void load_elf64(posix_header * f)
{
	// Gets the file.
	uint8_t * pfile = (uint8_t *)(f + 1);
	// Checks if the file is infact an elf64.
	kprintf("%c%c%c", pfile[1], pfile[2], pfile[3]);
}