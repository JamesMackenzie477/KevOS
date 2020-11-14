#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "stdio.h"
#include "keyboard.h"

#define IRTN(_R, _N, _E, _A) _R _N(_A); extern _R _E(_A);

/*
 * Declares all of the interrupts for the IDT to use.
 */
IRTN(void, irq_1, __irq_1, void)
IRTN(void, double_fault, __double_fault, void)
IRTN(void, def_int, __def_int, void)

#endif