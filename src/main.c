/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Main function of BetterShell. Runs in parent process.

	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char WORKING_DIRECTORY[200] = "/\0";

FILE* FILE_SYSTEM_ID;
extern int BYTES_PER_SECTOR; 

/* Main Function (Currently Just Runs Shell) */
int main(int argc, char *argv[]) {

	/* Declare Variables */
	char *input, **cmd;
	unsigned char* boot;            // Boot Sector
	int mostSignificantBits, leastSignificantBits, bytesPerSector, status;

	/* File to open, later allow it to be specified */
	FILE_SYSTEM_ID = fopen(argv[1], "r+");

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

	/* Initialize Shared Memory Space for Current Working Directory */
	initWorkingDir();

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
