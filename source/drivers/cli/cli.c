#include "cli.h"

/**
 * Main entry point of the program.
 */
int main(void)
{
	char buff[10] = { 0 };
	// Waits for user input.
	while (1)
	{
		// Prints the console string to the screen.
		printf("KevOS> ");
		printf("ls\n");
		printf("cli.bin\n");
		printf("KevOS> fread(&buff, 1, 1)\n");

		size_t r = __fread(&buff, 1, 1);

		printf("r = 0x%x\n", r);
		printf("KevOS> ");
		// Gets the user input.
		// Parses the user input.
		break;
	}
	// Success.
	return 1;
}