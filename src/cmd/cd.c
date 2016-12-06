/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Changes the working directory.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/shared.h"

FILE* FILE_SYSTEM_ID;
extern const key_t SHM_KEY;

int cd_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");
	
	if (argc == 1)
	{
		// Change the working directory to root
		dirSet("/");
		filenameSet("");
		flcSet(0);
	}
	else if (argc == 2)
	{
		// CD to the given path name
		dirAdd(argv[1]);
	}
	else
	{
		// Too many args
		cd_help();
	}
	
	return 0;
}

int cd_help() {
	printf("Help for cd command will go here.\n");
	return(0);
}
