/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Creates the specified file in the target directory.
	
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

int touch_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	char filePath[200] = "";

	if(argv[1] == NULL)
	{
		touch_help();
		return 0;
	}
	else if(argv[1][0] == '/')
	{
		strcat(filePath, argv[1]);
	}
	else
	{
		strcat(filePath, share->wdPath);
		strcat(filePath, argv[1]);
	}
	
	printf("Touch will target file -> %s\n", filePath);
	return 0;
}

int touch_help()
{
	printf("Help for touch command will go here.\n");
	return(0);
}