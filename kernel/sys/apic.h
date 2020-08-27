#ifndef _APIC_H
#define _APIC_H

#include <cpuid.h>
#include "../stdio.h"

#define CPUID_APIC (1 << 9)

#define CPUID_FEATURES 1

extern void __read_msr(uint32_t msr, uint32_t eax, uint32_t edx);
extern void __write_msr(uint32_t msr, uint32_t eax, uint32_t edx);

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MASK 0xFFFFF000

#define APIC_ENABLE (1 << 11)

static inline void apic_set_base(uint32_t base);
static inline uint32_t apic_get_base();

void apic_init(void);

#endif