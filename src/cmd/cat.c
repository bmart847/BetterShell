/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Outputs the contents of a file.
	
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

int cat_help();
bool isEnd(unsigned int fatEntry);

int main(int argc, char *argv[])
{
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	unsigned char* fatTable;
	int numEntries = loadFatTable(fatTable);

	char filePath[200] = "";
	unsigned int nextCluster;
	short fileFLC, success;
	unsigned char* sectorBuffer = malloc(BYTES_PER_SECTOR * sizeof(unsigned char*));

	if (argc > 2)
	{
		printf("ERROR: Too many arguments.\n");
		return 0;
	}
	else if(argv[1] == NULL)
	{
		cat_help();
		return 0;
	}
	else if(argv[1][0] == '/')
	{
		strcat(filePath, argv[1]);
	}
	else
	{
		strcat(filePath, share->wdPath);
		if(share->wdSize != 1)
		{
			filePath[strlen(filePath)] = '/';
			filePath[strlen(filePath)] = '\0';
		}
		strcat(filePath, argv[1]);
	}
	
	printf("cat will target file -> %s\n", filePath);

	if (existingDirectory(filePath) != -1) {
		printf("ERROR: Target is a directory.\n");
		return 0;
	}
	else if ((fileFLC = existingFile(filePath)) != -1)
	{
		// Logic for outputting contents will go here
		printf("File Exists!\n");

		do
		{
			success = read_sector(fileFLC, sectorBuffer);
			if(success == -1) { break; }
			printf("%s", sectorBuffer);
			fileFLC++;
		} while (isEnd((unsigned int) fileFLC));
		
		return 0;
	}
	else
	{
		printf("ERROR: Target does not exist on the disk.\n");
	}

	free(sectorBuffer);
	return 0;
}

int cat_help() {
	printf("Help for cat command will go here.\n");
	return(0);
}

bool isEnd(unsigned int fatEntry)
{
	unsigned char i;
	while( i = LAST_CLUSTER_BEGIN; i <= LAST_CLUSTER_END; i++)
	{
		if(fatEntry == (unsigned int) i)
		{
			return true;
		}
	}
	return false;
}