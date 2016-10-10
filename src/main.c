#include "shellFunctions.h"
#include "fatSupport.h"
#include "pfe.c"

#define SECTOR_SIZE 512

/*
FILE* FILE_SYSTEM_ID;
int BYTES_PER_SECTOR;

extern int read_sector(int sector_number, unsigned char* buffer);
extern int write_sector(int sector_number, unsigned char* buffer);

extern unsigned int  get_fat_entry(int fat_entry_number, unsigned char* fat);
extern void set_fat_entry(int fat_entry_number, int value, unsigned char* fat);
*/

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
