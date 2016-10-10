#include "shellFunctions.h"
#include "fatSupport.h"

/* Main Function (Currently Just Runs Shell) */
int main(int argc, char *argv[]) {
	/* Declare Variables */
	char *input, **cmd;
	unsigned char* boot;            // Boot Sector
	int mostSignificantBits, leastSignificantBits, bytesPerSector, status;

	/* Main Shell Logic */
	do {
		/* Shows the prompt */
		printf("> ");

		/* Grab input */
		input = get_line();

		/* Parse input */
		cmd = parseInput(input);

		/* Execute input */
		status = cmdExecute(cmd);

		/* Free memory */
		free(input);
		free(cmd);
	} while (status == 0);
}
