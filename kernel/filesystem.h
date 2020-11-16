#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "stdio.h"

/**
 * Defines the tar file header.
 */
typedef struct _posix_header
{
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
} __attribute__((packed)) posix_header;

void fs_init(void);

#endif