#ifndef _APIC_H
#define _APIC_H

#define IA32_APIC_BASE_MSR 	0x1B
#define IA32_SYSENTER_CS 	0x174
#define IA32_SYSENTER_ESP	0x175
#define IA32_SYSENTER_EIP	0x176

extern void __read_msr(uint32_t msr, uint32_t eax, uint32_t edx);
extern void __write_msr(uint32_t msr, uint32_t eax, uint32_t edx);

#endif