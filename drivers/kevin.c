#include "kevin.h"

/*
 * Prints a string to the std output.
 */
void printf(const char *)
{
	__syscall(0);
}