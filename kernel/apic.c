#include "sys/apic.h"

/*
 * Enables the APIC.
 */
static inline void apic_enable()
{
	// Sets the enable bit of the APIC BASE MSR.
	apic_set_base(apic_get_base() | APIC_ENABLE);

	// kprintf("Value: 0x%x\n", *(uint32_t *)(apic_get_base() + 0xF0));

	// Sets the enable bit of the spurious interrupt vector register.
	*(uint32_t *)(apic_get_base() + 0xF0) |= 0xFF;
}

/*
 * Sets the APIC base MSR.
 */
static inline void apic_set_base(uintptr_t base)
{
	// Writes the base to the register.
	__write_msr(IA32_APIC_BASE_MSR, base, 0);
}

/*
 * Gets the base address of the memory mapped APIC registers.
 */
static inline uintptr_t apic_get_base()
{
	// Contains the result.
	uint32_t eax, edx;
	// Gets the base address of the memory mapped registers.
	__read_msr(IA32_APIC_BASE_MSR, &eax, &edx);
	// Returns the base.
	return eax & IA32_APIC_BASE_MASK;
}

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
	// Enables the APIC.
	apic_enable();
}