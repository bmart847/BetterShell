#include "shellFunctions.h"
#include "fatSupport.h"
#include "pfe.h"

#define SECTOR_SIZE 512

/* Main Function (Currently Just Runs Shell) */
int main(int argc, char *argv[]) {

	/* Declare Variables */
	char *input, **cmd;
	unsigned char* boot;            // Boot Sector
	int mostSignificantBits, leastSignificantBits, bytesPerSector, status;

	/* File to open, later allow it to be specified */
	FILE_SYSTEM_ID = fopen("../test/floppy1", "r+");
	BYTES_PER_SECTOR = SECTOR_SIZE; 

	/* Open file */
	if (FILE_SYSTEM_ID == NULL) {
		printf("Could not open the floppy drive or image.\n");
		exit(1);
	}

	/* Read Boot Sector */
	boot = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(unsigned char));
	if(read_sector(0,boot) == -1) {
		printf("Error reading the boot sector.\n");
	}

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
