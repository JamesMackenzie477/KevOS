#ifndef _IDT_H
#define _IDT_H

#include "stdio.h"
#include "interrupts.h"

#define DEF_CODE_SEL 0x8

#define GATE_INT	0xE
#define GATE_TRAP	0xF
#define GATE_TASK	0x5

#define ATTR_NOT_PRESENT	((0 & 1) << 7)
#define ATTR_PRESENT		((1 & 1) << 7)
#define ATTR_KERNEL			((0 & 3) << 5)
#define ATTR_USER			((3 & 3) << 5)
#define ATTR_STORAGE		((0 & 1) << 4)

typedef struct _IDT_INFO
{
	uint16_t limit;
	uint32_t base_addr;
} __attribute__((packed)) IDT_INFO;

typedef struct _IDT_ENTRY
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_high;
} __attribute__((packed)) IDT_ENTRY;

extern void __set_IDT(IDT_INFO *);

#endif