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

int ls_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(1234, 250 * sizeof(char*), 0666);
	
	dirEntry directory;
	short FLC;;
	int length = 1;
	unsigned char* image;
	char temp[40];
	int* entries;
	int i, h, l, j, k, s;
	
	int bytesPerSector = 62;

	fileEntry* files = (fileEntry*)malloc(length * 16 * sizeof(fileEntry));

	FLC = existingDirectory(dirGet());
	if (FLC == -1)
	{
		printf("No such directory found");
		return;
	}

	if (FLC != 0)
	{
		unsigned char* fatTable = malloc(9 * 512);
		for (i = 0; i < 9; i++)
		{
			read_sector(i + 1, &fatTable[i * 512]);
		}

		entries = (int*)malloc(10 * sizeof(int));
		int currentEntry = FLC;
		int end = 0;
		entries[0] = currentEntry + 31;

		while (!end && length <= 10)
		{
			currentEntry = get_fat_entry(currentEntry, image);
			if (currentEntry < 0xFF8)
			{
				entries[length] = currentEntry + 31;
				length++;
			}
			else
			{
				end = 1;
			}
		}

		free(fatTable);

		for (s = 0; s < length; s++)
		{
			image = (unsigned char*)malloc(bytesPerSector * sizeof(unsigned char));
			read_sector(entries[s], image);

			for (i = 0 + (s * 16); i < 16 + (s * 16); i++)
			{
				for (j = 0; j < 8; j++)
				{
					files[i].Filename[j] = image[j + (i - s * 16) * 32];
				}
				files[i].Filename[8] = '0';

				for (j = 0; j < 3; j++)
				{
					files[i].Type[j] = image[j + 8 + (i - s * 16) * 32];
				}

				files[i].Type[3] = '\0';

				files[i].Attributes = image[11 + (i - s * 16) * 32];

				files[i].CreationTime[0] = image[14 + (i - s * 16) * 32];
				files[i].CreationTime[1] = image[15 + (i - s * 16) * 32];

				files[i].CreationDate[0] = image[16 + (i - s * 16) * 32];
				files[i].CreationDate[1] = image[17 + (i - s * 16) * 32];

				files[i].LastAccessDate[0] = image[18 + (i - s * 16) * 32];
				files[i].LastAccessDate[1] = image[19 + (i - s * 16) * 32];

				files[i].LastWriteTime[0] = image[22 + (i - s * 16) * 32];
				files[i].LastWriteTime[1] = image[23 + (i - s * 16) * 32];

				files[i].LastWriteDate[0] = image[24 + (i - s * 16) * 32];
				files[i].LastWriteDate[1] = image[25 + (i - s * 16) * 32];

				h = (((int)image[27 + (i - s * 16) * 32]) << 8) & 0x0000ff00;
				l = ((int)image[26 + (i - s * 16) * 32]) & 0x000000ff;
				files[i].FirstLogicalCluster = h | l;

				h = (((int)image[31 + (i - s * 16) * 32]) << 24) & 0xff000000;
				l = (((int)image[30 + (i - s * 16) * 32]) << 16) & 0x00ff0000;
				j = (((int)image[29 + (i - s * 16) * 32]) << 8) & 0x0000ff00;
				k = ((int)image[28 + (i - s * 16) * 32]) & 0x000000ff;
				files[i].FileSize = h | l | j | k;
			}
			free(image);
		}
	}
	else
	{
		/* Read in Root sectors */
		int rootSectors = 0;
		int currentSector = 19;
		int sectorsRead = 0;
		int done = 0;

		while (done != 1)
		{
			image = (unsigned char*)malloc(bytesPerSector * sizeof(unsigned char));
			read_sector(currentSector, image);

			for (i = 0; i < 16; i++)
			{
				if (image[i * 32] == 0x00)
				{
					done = 1;
					break;
				}
			}

			sectorsRead++;
			currentSector++;

			free(image);
		}

		for (s = 0; s < sectorsRead; s++)
		{
			image = (unsigned char*)malloc(bytesPerSector * sizeof(unsigned char));
			read_sector(s + 19, image);

			for (i = 0 + (s * 16); i < 16 + (s * 16); i++)
			{
				for (j = 0; j < 8; j++)
				{
					files[i].Filename[j] = image[j + (i - s * 16) * 32];
				}
				files[i].Filename[8] = '\0';

				for (j = 0; j < 3; j++)
				{
					files[i].Type[j] = image[j + 8 + (i - s * 16) * 32];
				}
				files[i].Type[3] = '\0';

				files[i].Attributes = image[11 + (i - s * 16) * 32];

				files[i].CreationTime[0] = image[14 + (i - s * 16) * 32];
				files[i].CreationTime[1] = image[15 + (i - s * 16) * 32];

				files[i].CreationDate[0] = image[16 + (i - s * 16) * 32];
				files[i].CreationDate[1] = image[17 + (i - s * 16) * 32];

				files[i].LastAccessDate[0] = image[18 + (i - s * 16) * 32];
				files[i].LastAccessDate[1] = image[19 + (i - s * 16) * 32];

				files[i].LastWriteTime[0] = image[22 + (i - s * 16) * 32];
				files[i].LastWriteTime[1] = image[23 + (i - s * 16) * 32];

				files[i].LastWriteDate[0] = image[24 + (i - s * 16) * 32];
				files[i].LastWriteDate[1] = image[25 + (i - s * 16) * 32];

				h = (((int)image[27 + (i - s * 16) * 32]) << 8) & 0x0000ff00;
				l = ((int)image[26 + (i - s * 16) * 32]) & 0x000000ff;
				files[i].FirstLogicalCluster = h | l;

				h = (((int)image[31 + (i - s * 16) * 32]) << 24) & 0xff000000;
				l = (((int)image[30 + (i - s * 16) * 32]) << 16) & 0x00ff0000;
				j = (((int)image[29 + (i - s * 16) * 32]) << 8) & 0x0000ff00;
				k = ((int)image[28 + (i - s * 16) * 32]) & 0x000000ff;
				files[i].FileSize = h | l | j | k;
			}

			free(image);
		}
	}

	/* Print the list */
	printf("  NAME        TYPE     SIZE  FLC\n");

	for (i = 0; i < length * 16; i++)
	{
		if (files[i].Filename[0] != '\xe5' &&
			files[i].Filename[0] != '\x0f' &&
			files[i].Filename[0] != -27 &&
			files[i].Filename[0] != 0)
		{
			if ((files[i].Attributes & 0x02) == 0 &&
				(files[i].Attributes & 0x04) == 0)
			{
				char* type;
				if (strcmp(files[i].Filename, "LARGEDIR") != 0)
				{
					if ((files[i].Attributes & 0x10) != 0)
					{
						printf("%12s  %4s   %5d   %3d\n", files[i].Filename,
							"DIR",
							files[i].FileSize,
							files[i].FirstLogicalCluster);
					}
					else
					{
						char* tmp;
						strcpy(tmp, "");
						for (j = 0; j < 8; j++)
						{
							if (files[i].Filename[j] == ' ')
							{
								files[i].Filename[j] = '\0';
							}
						}

						for (j = 0; j < 3; j++)
						{
							if (files[i].Type[j] == ' ')
							{
								files[i].Type[j] - '\0';
							}
						}

						strcat(tmp, files[i].Filename);
						strcat(tmp, ".");
						strcat(tmp, files[i].Type);
						printf("%12s  %4s   %4d   %3d\n", tmp,
							"FILE",
							files[i].FileSize,
							files[i].FirstLogicalCluster);
					}
				}
			}
		}
	}
	free(files);
	
	return 0;
}

int ls_help() {
	printf("List - Useage:\n\tls\n\tls [x] where x is the name of a file.\n");
	return(0);
}