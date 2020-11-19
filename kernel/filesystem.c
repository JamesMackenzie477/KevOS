#include "filesystem.h"

/**
 * Stores the current directory of the filesystem.
 */
char path[100];

/**
 * Stores the disk address.
 */
posix_header * disk_addr;

/**
 * Finds the address of the disk in RAM.
 * This is a work in progress and probably shouldn't be done like this.
 * @return A pointer to the disk mapped in memory.
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
			// Actual mapping is aligned to 0x100 bytes.
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
 * Returns the amount of blocks between this header and the next.
 * @param h The header of the item to calculate the block size for.
 * @return The number of blocks to jump to get to the next header.
 */
inline uint32_t fs_get_jump_size(posix_header * h)
{
	// Gets the size of the file.
	uint32_t file_size, size = str_to_int(h->size);
	// Checks the filetype.
	if (h->typeflag == FILETYPE_REGULAR_FILE)
	{
		// Calculates the file block size.
		file_size = (size / sizeof(posix_header)) + (size < sizeof(posix_header));
		// Jumps over the file.
		return 1 + file_size;
	}
	// Jumps over the header.
	return 1;
}

/**
 * Validates the given directory path.
 * @param p The path to check the validity of.
 * @return True if the path exists, False if not.
 */
bool fs_check_path(const char * p)
{
	// Iterates through the files in the disk.
	for (uint32_t i = 0; disk_addr[i].name[0] != 0; i += fs_get_jump_size(&disk_addr[i]))
	{
		// Checks if it's a directory.
		if (disk_addr[i].typeflag == FILETYPE_DIRECTORY)
		{
			// If it's equal to the path then the directory exists.
			if (strcmp(disk_addr[i].name, p) == 0)
			{
				// The directory exists.
				return 1;
			}
		}
	}
	// It doesn't exist.
	return 0;
}

/**
 * Retrieves a file from the file system.
 * @return A pointer to the header of the requested file.
 */
posix_header * fs_get_file(const char * p)
{
	// Iterates through the files in the disk.
	for (uint32_t i = 0; disk_addr[i].name[0] != 0; i += fs_get_jump_size(&disk_addr[i]))
	{
		// Checks if it's a file.
		if (disk_addr[i].typeflag == FILETYPE_REGULAR_FILE)
		{
			// If it's equal to the path then the file. exists.
			if (strcmp(disk_addr[i].name, p) == 0)
			{
				// Returns a pointer to the file.
				return &disk_addr[i];
			}
		}
	}
	// No file found.
	return (posix_header *)-1;
}

/**
 * Changes the current directory of the file system.
 */
bool fs_cd(const char * p)
{
	// Stores the new path.
	char new_path[100];
	// Duplicates the current path.
	strcpy(new_path, path);
	// Appends the new directory.
	strcat(new_path, p);
	// Checks if the path is valid.
	if (fs_check_path(new_path))
	{
		// Updates the current working path.
		strcpy(path, new_path);
		// Success.
		return 1;
	}
	// Directory does not exist.
	return 0;
	// parses the string.
	// root dir? change string.
	// no root append to current string.
	// Path does not exist.
}

/**
 * Prints the files in the current directory.
 */
void fs_ls(void)
{
	// Iterates through the files in the disk.
	for (uint32_t i = 0; disk_addr[i].name[0] != 0; i += fs_get_jump_size(&disk_addr[i]))
	{
		// Checks if it's a file.
		if (disk_addr[i].typeflag == FILETYPE_REGULAR_FILE)
		{
			// If it's equal to the path then the directory exists.
			if (strncmp(disk_addr[i].name, path, strlen(path) - 1) == 0)
			{
				// Prints the filename.
				kprintf("%s\n", disk_addr[i].name);
			}
		}
	}
}

char * fs_dir(void)
{
	return path;
}

/**
 * Initialises the filesystem.
 */
void fs_init(void)
{
	// Gets the address of the disk.
	disk_addr = fs_get_disk_addr();
	// Sets the root directory.
	fs_cd("disk/");
	// Prints the files in the directory.
	fs_ls();
	// Is it an elf 64?
	// Lets link to our kernel methods.
	// Use an image loader to parse the elf64 binary and then map out any function calls.
	// Rebase image?
}