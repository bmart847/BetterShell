/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  print the number of free logical blocks *DISK FREE*.
	
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

int df_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	unsigned char* fatTable = malloc((BYTES_PER_SECTOR * NUM_FAT_SECTORS) * sizeof(unsigned char*));
	int numEntries = loadFatTable(fatTable);
	unsigned int freeCount = 0, fatEntry;

	
	for(int i = 32; i < numEntries; i++)
	{
		fatEntry = get_fat_entry(i, fatTable);
		if(fatEntry == UNUSED)
		{
			freeCount++;
		}
		else
		{
			continue;
		}
	}

	free(fatTable);
	printf("%d Unused Sectors\n", freeCount);
	printf("Total Space: %d Bytes\n", freeCount * BYTES_PER_SECTOR);
	return 0;
}

int df_help()
{
	printf("Help for df command will go here.\n");
	return(0);
}