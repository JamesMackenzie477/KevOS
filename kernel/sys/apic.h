#ifndef _APIC_H
#define _APIC_H

#include <cpuid.h>
#include "../stdio.h"

#define CPUID_APIC (1 << 9)

#define CPUID_FEATURES 1

extern void __read_msr(uint32_t msr, uint32_t eax, uint32_t edx);

#define IA32_APIC_BASE_MSR 0x1B

void apic_init(void);

#endif