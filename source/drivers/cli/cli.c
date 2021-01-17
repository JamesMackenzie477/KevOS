#include "cli.h"

/**
 * Main entry point of the program.
 */
int __start(void)
{
	// Prints a string to the screen.
	printf(
"  _  __           ____   _____\n\
 | |/ /          / __ \\ / ____|\n\
 | ' / _____   _| |  | | (___\n\
 |  < / _ \\ \\ / / |  | |\\___ \\\n\
 | . \\  __/\\ V /| |__| |____) |\n\
 |_|\\_\\___| \\_/  \\____/|_____/ version 0.9\n\n\
--------------------------------------------------------------------------------\n\n\
KevOS>\
"
		);
	// Waits for user input.
	for(;;);
	// Success.
	return 1;
}