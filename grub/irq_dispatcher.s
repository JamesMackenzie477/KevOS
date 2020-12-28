.global int0

.text

.macro interrupt irq param=0

	.align 16

	int\irq:

		.if (\param == 0)
			push $0
		.else
			nop
			nop
		.endif

		push $\irq
		pushal
		call interrupt_handler
		popal
		addl $8, %esp
		sti
		iret

		nop
		nop

.endm

.align 16
	nop
	nop

interrupt 0 # Division by zero
interrupt 1 # Single step
interrupt 2 # Non-Maskable Interrupt (NMI)
interrupt 3
interrupt 4
interrupt 5
interrupt 6
interrupt 7
interrupt 8
interrupt 9
interrupt 10
interrupt 11
interrupt 12
interrupt 13
interrupt 14
interrupt 15
interrupt 16
interrupt 17
interrupt 18
interrupt 19
interrupt 20