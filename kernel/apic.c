#include "sys/apic.h"

/*
 * Used to check if this system uses an APIC.
 * Returns true if this is the case.
 */
static inline bool apic_check(void)
{
	// Stores the result.
    uint32_t eax, ebx, ecx, edx;
    // Gets the CPU features.
    __get_cpuid(CPUID_FEATURES, &eax, &ebx, &ecx, &edx);
    // Returns true if this system uses an APIC.
    return edx & CPUID_APIC;
}

/*
 * Initialises the first and second APIC.
 */
void apic_init(void)
{
	// Ensures that this sytem supports an APIC.
	if (!apic_check()) return; // Throw error in future.

	uint32_t eax, edx;

	__read_msr(IA32_APIC_BASE_MSR, &eax, &edx);

	// Memory mapped registers seem to be stored at an address which we allocate via pfalloc.
	// This could be a problem...

	kprintf("0x%x\n", (eax & 0xFFFFF000));
}