#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "stdio.h"
#include "keyboard.h"

/*
 * Declares all of the interrupts for the IDT to use.
 */
void def_int(void);

extern void __irq_1(void);
extern void __def_int(void);

/*
 * Declares all IRQ interrupt handlers.
 */
void irq_1(void);

#endif