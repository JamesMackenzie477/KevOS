#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "stdio.h"
#include "keyboard.h"

#define IRTN(_R, _N, _E, ...) _R _N(__VA_ARGS__); extern _R _E(__VA_ARGS__);

/*
 * Declares all of the interrupts for the IDT to use.
 */
IRTN(void, irq_1, __irq_1, void)
IRTN(void, double_fault, __double_fault, void)
IRTN(void, printf, __printf, const char *)

#endif