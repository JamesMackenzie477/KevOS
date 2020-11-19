#ifndef _PIC_H
#define _PIC_H

#include "stdio.h"
#include "ports.h"


#define PIC1 			0x20
#define PIC2 			0xA0
#define PIC1_COMMAND	PIC1
#define PIC2_COMMAND	PIC2
#define PIC1_DATA 		(PIC1+1)
#define PIC2_DATA 		(PIC2+1)

#define ICW1_ICW4	0x01
#define ICW1_INIT	0x10

#define ICW4_8086	0x01


#define IMR_IGNORE_ALL 0xFF

void pic_set_imr(uint32_t mask);
void pic_init(void);

#endif