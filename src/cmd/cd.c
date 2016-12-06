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
	/* Declare variables */
	char* newPath;
	short newFLC;

	/* Access shared memory */
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	if (argc == 1)
	{
		/* Change to the home (root) directory */
		dirSet("/");
		filenameSet("");
		flcSet(0);
		return 0;
	}
	else if (argc == 2)
	{
		/* Correct number of arguments, cd to the specified directory */
		if (strcmp(argv[1], "..") == 0)
		{
			dirRemove();
			newFLC = existingDirectory(dirGet());
			if (newFLC != -1)
			{
				flcSet(newFLC);
			}
			else
			{
				/* Not good, dirRemove() should stop at root */
				printf("ERROR: CD failed\n");
				return -1;
			}
		}
		else if (strcmp(argv[1], "/") != 0)
		{
			/* If the specified path is relative, concatonate it onto the working directory. */
			newPath = dirGet();
			strcat(newPath, argv[1]);
			newFLC = existingDirectory(newPath);
			if (newFLC != -1)
			{
				flcSet(newFLC);
				dirAdd(argv[1]);
			}
			else
			{
				/* Directory does not exist */
				printf("Directory does not exist!\n");
			}
		}
		else
		{
			/* Change to the specified absolute path */
			newFLC = existingDirectory(argv[1]);
			if (newFLC == -1)
			{
				/* Directory does not exist */
				printf("Directory does not exist!\n");
			}
			else
			{
				flcSet(newFLC);
				dirSet(argv[1]);
			}
		}
	}
	else
	{
		/* Wrong number of arguments */
		cd_help();
	}

	printf("%s", dirGet());

	return 0;
}

int cd_help() {
	printf("Help for cd command will go here.\n");
	return(0);
}
