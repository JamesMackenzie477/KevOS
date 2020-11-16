#include "filesystem.h"

/**
 * Finds the address of the disk in RAM.
 * This is a work in progress and probably shouldn't be done like this.
 */
posix_header * fs_get_disk_addr(void)
{
	// Stores the disk address.
	char * disk_addr;
	// Find the disk in memory.
	for (disk_addr = 0; disk_addr < 0x100000; disk_addr++)
	{
		// Indicator of the disk.
		if (strcmp(disk_addr, "disk/") == 0)
		{
			if (((((uintptr_t)disk_addr) % 0x100) == 0))
			{
				// Returns the address.
				return (posix_header *)disk_addr;
			}
		}
	}
	// Returns 0 if no disk is found.
	return (posix_header *)0;
}

/**
 * Initialises the filesystem.
 */
void fs_init(void)
{
	// Gets the address of the disk.
	posix_header * disk_addr = fs_get_disk_addr();
	// Parses the disk.
	kprintf("%s\n", (((char *)disk_addr) + 0x101));
}