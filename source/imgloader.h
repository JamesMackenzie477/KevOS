#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "stdio.h"
#include "paging.h"

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
	char padding[12];
} __attribute__((packed)) posix_header;

/**
 * Defines the elf file header.
 */
typedef struct _elf_header
{
	uint32_t magic;
	uint8_t class;
	uint8_t data;
	uint8_t version;
	uint8_t osabi;
	uint8_t abiver;
	uint8_t pad[7];
	uint16_t type;
	uint16_t machine;
	uint32_t ver;
	uint32_t entry; // entry point of the binary. Lets call it!
	uint32_t phoff;
	uint32_t shoff;
	uint32_t flags;
	uint16_t ehsize;
	uint16_t phentsize;
	uint16_t phnum;
	uint16_t shentsize;
	uint16_t shnum;
	uint16_t shstrndx;
} __attribute__((packed)) elf_header;

/**
 * Defines the elf program header.
 */
typedef struct _program_header
{
	uint32_t type;
	uint32_t offset;
	uint32_t vaddr;
	uint32_t paddr;
	uint32_t filesz;
	uint32_t flags5;
	uint32_t flags6;
	uint32_t flags7;
} __attribute__((packed)) program_header;


/**
 * Defines the elf section header.
 */
typedef struct _section_header
{
	uint32_t name;
	uint32_t type;
	uint32_t flags;
	uint32_t addr;
	uint32_t offset;

	uint32_t flags3;
	uint32_t flags4;
	uint32_t flags5;
	uint32_t flags6;
	uint32_t flags7;
} __attribute__((packed)) section_header;

/**
 * Defines the magic number for ELF files.
 */
#define IL_ELF_MAGIC 0x464C457F

/**
 * Defines the default base for the program.
 */
#define IL_DEF_BASE 0x1000
#define IL_BOOTSTRAP_ADDR 0x2000

#define PT_LOAD 0x1

/**
 * Defines the main entry point of the drivers.
 */
typedef const char * (*entry_t)();

extern uint32_t __r3_execute(uint32_t f, uint32_t s);
extern uint32_t __r3_bootstrap_start;
extern uint32_t __r3_bootstrap_end;
extern uint32_t stack_top;

void il_init(void);
uint32_t * il_load_elf64(posix_header *);
uint32_t test_prog(void);

#endif