#include "sys/apic.h"

/*
 * Disables the PIC by masking all interrupts.
 * The PIC is outdated so we need to force use of the APIC.
 */
static inline void apic_disable_pic()
{
	pic_set_imr(IMR_IGNORE_ALL);
}

/*
 * Reads the value from the specified APIC register.
 */
uint32_t apic_read_register(uint32_t reg)
{
	// Offsets the base of the APIC memory map by the register number.
	return *(uint32_t *)(apic_get_base() + reg);
}

/*
 * Writes the given value to the specified APIC register.
 */
void apic_write_register(uint32_t reg, uint32_t val)
{
	// Offsets the base of the APIC memory map by the register number.
	*(uint32_t *)(apic_get_base() + reg) = val;
}

/*
 * Enables the APIC.
 */
static inline void apic_enable()
{
	// Sets the enable bit of the APIC BASE MSR.
	// apic_set_base(apic_get_base() | APIC_ENABLE);
	// Sets the enable bit of the spurious interrupt vector register.
	// apic_write_register(REG_SPUR_INT_VECT, apic_read_register(REG_SPUR_INT_VECT) | 0x1FF);
	// Disables the PIC as it is no longer needed.
	apic_disable_pic();
	// Remaps the IRQs.
	// We may need to set up the PIC before enabling the APIC.
	// Clears and enables interrupts.
	__cli_sti();
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
	// if (!apic_check()) return; // Throw error in future.
	// Enables the APIC.
	apic_enable();
}