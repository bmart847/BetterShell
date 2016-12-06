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
	printf("CD called.\n");
	short newFLC = 1;
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	if (argc == 1)
	{
		// Change the working directory to root
		dirSet("/");
		flcSet(19);
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "..") == 0)
		{
			/* Move up one directory level */
			dirRemove();
			newFLC = existingDirectory(dirGet());
			flcSet(newFLC);
		}
		else
		{
			/* CD to the given path name */
			dirAdd(argv[1]);

			newFLC = existingDirectory(dirGet());

			printf("CD : newFLC = %i\n", newFLC);

			/* Check that the new directory actually exists before moving into it */
			if (newFLC != -1)
			{
				flcSet(newFLC);
			}
			else
			{
				printf("The specified directory does not exist\n");
				dirRemove();
				return -1;
			}
		}
	}
	else
	{
		// Too many args
		cd_help();
	}

	printf("Directory : %s\n", dirGet());

	return 0;
}

int cd_help() {
	printf("Help for cd command will go here.\n");
	return(0);
}
