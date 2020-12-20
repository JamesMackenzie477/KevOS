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
 * Returns the amount of blocks between this header and the next.
 * @param h The header of the item to calculate the block size for.
 * @return The number of blocks to jump to get to the next header.
 */
inline uint32_t fs_get_jump_size(posix_header * h)
{
	// Gets the size of the file.
	uint32_t file_size, size = str_to_int(h->size, 8);
	// Checks the filetype.
	if (h->typeflag == FILETYPE_REGULAR_FILE)
	{
		// Calculates the file block size.
		file_size = (size / sizeof(posix_header)) + ((size % sizeof(posix_header)) > 0);
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
 * Extracts a filename from the given path.
 */
char * fs_filename(char * dst, const char * p)
{
	// Stores the current string pointer and the previous.
	char * res, * prev = NULL;
	// Duplicates the string as it's modified by strtok.
	strcpy(dst, p);
	// Gets the first directory from the path.
	res = strtok(dst, "/");
	// While there's still more depth to the path.
	while (res != NULL)
	{
		// Store the previous result (the filename) so it isn't lost when NULL is returned.
		prev = res;
		// Gets the next part of the path.
		res = strtok(NULL, "/");
	}
	// Returns the filename or NULL if it isn't found.
	return prev;
}

/**
 * Prints the files in the current directory.
 */
void fs_ls(void)
{
	// Stores the filename when requesting each file.
	char filename[100];
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
				kprintf("%s\n", fs_filename(&filename, disk_addr[i].name));
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
	disk_addr = &disk_start;
	// Sets the root directory.
	fs_cd("disk/");
}