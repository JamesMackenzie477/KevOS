#ifndef _APIC_H
#define _APIC_H

#include <cpuid.h>
#include "../stdio.h"
#include "pic.h"

#define CPUID_APIC (1 << 9)

#define CPUID_FEATURES 1

extern void __read_msr(uint32_t msr, uint32_t eax, uint32_t edx);
extern void __write_msr(uint32_t msr, uint32_t eax, uint32_t edx);
extern void __sti(void);

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MASK 0xFFFFF000

#define APIC_ENABLE (1 << 11)


/*
 * APIC register definitions.
 */
#define REG_SPUR_INT_VECT 	0xF0
#define REG_EOI				0xB0

/*
 * Used to communicate with the APIC.
 */
uint32_t 	apic_read_register	(uint32_t reg 				);
void 		apic_write_register	(uint32_t reg, uint32_t val	);

static inline void apic_set_base(uint32_t base);
static inline uint32_t apic_get_base();

/*
 * Initialises the APIC.
 * Should be called at system boot.
 */
void apic_init(void);

#endif