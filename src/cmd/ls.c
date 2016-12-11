/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016

	Description:  Lists the entries in the directory or the file/directory entry contents.

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

int ls_help();

int main(int argc, char *argv[])
{
	// TODO: Add second argument to print subdirectory contents 
	/* Validate Arguments */
	if (argc > 2)
	{
		ls_help();
	}

	/* Access Shared Memory */
	shm_id = shmget(1234, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");

	if (FILE_SYSTEM_ID == NULL)
	{
		/* Something went wrong */
		printf("Something went wrong. Shared memory was unable to be initialized from ls\n");
		return -1;
	}

	/* Declare Variables */
	int sectorsPerCluster = 9;
	short FLC = flcGet();
	int length = 1;
	unsigned char* image;
	char temp[40];
	int* entries;
	int i, h, l, j, k, s, done;

	if (FLC == -1)
	{
		/* Directory does not exist, how did you get here? */
		printf("No such directory found.\n");
		return 0;
	}

	/* If FLC is not the Root Directory, read in the directory at FLC */
	if (FLC != 19)
	{
		unsigned char* fatTable = malloc(BYTES_PER_SECTOR * sectorsPerCluster);
		for (i = 0; i < 9; i++)
		{
			read_sector(i + 1, &fatTable[i * BYTES_PER_SECTOR]);
		}

		/* Read entries from the directory starting at FLC */
		entries = (int*) malloc(10 * sizeof(int*));
 		short curEntry = FLC;
		done = 0;
		entries[0] = curEntry + 31;

		while (!done && length <= 10)
		{
			curEntry = get_fat_entry(curEntry, fatTable);

			if (curEntry < 0xFF8)
			{
				entries[length] = curEntry + 31;
				length++;
			}
			else
			{
				done = 1;
			}
		}

		free(fatTable);
	}

	/* Allocate a new dirEntry object array to read in the directory contents */
	dirEntry* file = (dirEntry*) malloc(length * sizeof(dirEntry));

	if (FLC == 19)
	{
		/* Read in Root sectors */
		int rootSectors = 0;
		int currentSector = 19;
		int sectorsRead = 0;
		done = 0;

		while (done != 1)
		{
			image = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(unsigned char*));
			read_sector(currentSector, image);

			for (i = 0; i < 16; i++)
			{
				if (image[i * 32] == 0x00)
				{
					done = 1;
					break;
				}
			}

			currentSector++;
			sectorsRead++;

			free(image);
		}

		for (s = 0; s < sectorsRead; s++)
		{
			image = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(char*));
			read_sector(s + 19, image);

			for (i = 0 + (s * 16); i < 16 + (s * 16); i++)
			{
				for (j = 0; j < 8; j++)
				{
					file[i].filename[j] = image[j + (i - s * 16) * 32];
				}
				file[i].filename[8] = '\0';

				for (j = 0; j < 3; j++)
				{
					file[i].extension[j] = image[j + 8 + (i - s * 16) * 32];
				}
				file[i].extension[3] = '\0';

				file[i].attributes = image[11 + (i - s * 16) * 32];

				file[i].creationTime[0] = image[14 + (i - s * 16) * 32];
				file[i].creationTime[1] = image[15 + (i - s * 16) * 32];

				file[i].creationDate[0] = image[16 + (i - s * 16) * 32];
				file[i].creationDate[1] = image[17 + (i - s * 16) * 32];

				file[i].lastAccessDate[0] = image[18 + (i - s * 16) * 32];
				file[i].lastAccessDate[1] = image[19 + (i - s * 16) * 32];

				file[i].lastWriteTime[0] = image[22 + (i - s * 16) * 32];
				file[i].lastWriteTime[1] = image[23 + (i - s * 16) * 32];

				file[i].lastWriteDate[0] = image[24 + (i - s * 16) * 32];
				file[i].lastWriteDate[1] = image[25 + (i - s * 16) * 32];

				h = (((int) image[27 + (i - s * 16) * 32]) << 8) & 0x0000ff00;
				l = ( (int) image[26 + (i - s * 16) * 32])       & 0x000000ff;
				file[i].firstLogicalCluster = (h | l);

				h = (((int) image[31 + (i - s * 16) * 32]) << 24) & 0xff000000;
				l = (((int) image[30 + (i - s * 16) * 32]) << 16) & 0x00ff0000;
				j = (((int) image[29 + (i - s * 16) * 32]) << 8)  & 0x0000ff00;
				k = ( (int) image[28 + (i - s * 16) * 32])        & 0x000000ff;
				file[i].fileSize = h | l | j | k;
			}
		}
	}
	else
	{
		for (s = 0; s < length; s++)
		{
			image = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(unsigned char*));
			read_sector(entries[s], image);

			for (i = 0 + (s * 16); i < 16 + (s * 16); i++)
			{
				for (j = 0; j < 8; j++)
				{
					file[i].filename[j] = image[j + (i - s * 16) * 32];
				}
				file[i].filename[8] = '0';

				for (j = 0; j < 3; j++)
				{
					file[i].extension[j] = image[j + 8 + (i - s * 16) * 32];
				}

				file[i].extension[3] = '\0';

				file[i].attributes = image[11 + (i - s * 16) * 32];

				file[i].creationTime[0] = image[14 + (i - s * 16) * 32];
				file[i].creationTime[1] = image[15 + (i - s * 16) * 32];

				file[i].creationDate[0] = image[16 + (i - s * 16) * 32];
				file[i].creationDate[1] = image[17 + (i - s * 16) * 32];

				file[i].lastAccessDate[0] = image[18 + (i - s * 16) * 32];
				file[i].lastAccessDate[1] = image[19 + (i - s * 16) * 32];

				file[i].lastWriteTime[0] = image[22 + (i - s * 16) * 32];
				file[i].lastWriteTime[1] = image[23 + (i - s * 16) * 32];

				file[i].lastWriteDate[0] = image[24 + (i - s * 16) * 32];
				file[i].lastWriteDate[1] = image[25 + (i - s * 16) * 32];

				h = (((int) image[27 + (i - s * 16) * 32]) << 8) & 0x0000ff00;
				l = ( (int) image[26 + (i - s * 16) * 32])       & 0x000000ff;
				file[i].firstLogicalCluster = (h | l) + 31; // 31 might be 32 or even 33?

				h = (((int) image[31 + (i - s * 16) * 32]) << 24) & 0xff000000;
				l = (((int) image[30 + (i - s * 16) * 32]) << 16) & 0x00ff0000;
				j = (((int) image[29 + (i - s * 16) * 32]) << 8)  & 0x0000ff00;
				k = ( (int) image[28 + (i - s * 16) * 32])        & 0x000000ff;
				file[i].fileSize = h | l | j | k;
			}
		}
	}

	/* Print the list */
	printf("    NAME       TYPE    SIZE   FLC\n");
	printf("------------  ------  ------  ---\n");

	for (i = 0; i < length * 16; i++)
	{
		if (file[i].filename[0] != '\xe5' &&
			file[i].filename[0] != '\x0f' &&
			file[i].filename[0] != -27 &&
			file[i].filename[0] != 0)
		{
			if ((file[i].attributes & HIDDEN_ATTRIBUTE) == 0 &&
				(file[i].attributes & SYSTEM_ATTRIBUTE) == 0)
			{
				if (strcmp(file[i].filename, "LARGEDIR") != 0)
				{
					if ((file[i].attributes & SUBDIR) != 0)
					{
						printf("%12s  %4s   %5d   %3d\n", file[i].filename,
							"DIR",
							file[i].fileSize,
							file[i].firstLogicalCluster);
					}
					else
					{
						strcpy(temp, "");
						for (j = 0; j < 8; j++)
						{
							if (file[i].filename[j] == ' ')
							{
								file[i].filename[j] = '\0';
							}
						}

						for (j = 0; j < 3; j++)
						{
							if (file[i].extension[j] == ' ')
							{
								file[i].extension[j] = '\0';
							}
						}

						strcat(temp, file[i].filename);
						strcat(temp, ".");
						strcat(temp, file[i].extension);
						printf("%12s  %4s   %4d   %3d\n", temp,
							"FILE",
							file[i].fileSize,
							file[i].firstLogicalCluster);
					}
				}
			}
		}
	}
	return 0;
}

int ls_help() {
	printf("List - Useage:\n\tls\n\tls [x] where x is the name of a file.\n");
	return(0);
}
