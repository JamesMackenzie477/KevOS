#include "sys/pic.h"

void pic_set_imr(uint32_t mask)
{
	__write_port(PIC1_DATA, mask);
	__write_port(PIC2_DATA, mask);
}

void pic_init(void)
{
	uint8_t pic1_mask = __read_port(PIC1_DATA);
	uint8_t pic2_mask = __read_port(PIC2_DATA);

	__write_port(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); __write_port(0x80, 0);
	__write_port(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4); __write_port(0x80, 0);

	__write_port(PIC1_DATA, 0x20); __write_port(0x80, 0);
	__write_port(PIC2_DATA, 0x28); __write_port(0x80, 0);

	__write_port(PIC1_DATA, 4); __write_port(0x80, 0);
	__write_port(PIC2_DATA, 2); __write_port(0x80, 0);

	__write_port(PIC1_DATA, ICW4_8086); __write_port(0x80, 0);
	__write_port(PIC2_DATA, ICW4_8086); __write_port(0x80, 0);

	__write_port(PIC1_DATA, pic1_mask); __write_port(0x80, 0);
	__write_port(PIC2_DATA, pic2_mask); __write_port(0x80, 0);
}