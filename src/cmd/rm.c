/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Removes the specified file.
	
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

int rm_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	unsigned char* fatTable;
	int numEntries = loadFatTable(fatTable);
	
	char filePath[200] = "";

	char* nullSector;
	blankSector(nullSector);

	if(argv[1] == NULL)
	{
		rm_help();
		free(nullSector);
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
	
	printf("Rm will target file -> %s\n", filePath);

	if (existingDirectory(filePath) != -1) {
		printf("ERROR: Target is a directory.\n");
		free(nullSector);
		return 0;
	}
	else if ((fileFLC = existingFile(filePath)) != -1)
	{
		// Logic for outputting contents will go here
		printf("File Exists!\n");

		do
		{
			success = write_sector(fileFLC, nullSector);
			if(success == -1) { break; }
			fileFLC = (short) get_fat_entry(fileFLC, fatTable);
		} while (isEnd((unsigned int) fileFLC) != 1);
		free(nullSector);
		return 0;
	}
	else
	{
		printf("ERROR: Target does not exist on the disk.\n");
	}
	
	free(nullSector);
	return 0;
}

int rm_help()
{
	printf("Help for rm command will go here.\n");
	return(0);
}

void blankSector(char* buffer)
{
	buffer = malloc(BYTES_PER_SECTOR * sizeof(unsigned char));
	memset(buffer, '\0', sizeof(unsigned char) * BYTES_PER_SECTOR);
	return buffer;
}