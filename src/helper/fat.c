#include "fat.h"

/* Check directoryName recursively by directory if the path exists */
short existingDirectory(char* path)
{
	char* pathName;
	unsigned short firstLogicalCluster = 0;
	
	// Duplicate path because it will get modified
	pathName = path; 

	/* Get deliminator token */
	char* delim;
	delim = strtok(pathName, "/");
	/* Check each directory in the directoryName exists */
	while (delim != NULL)
	{
		firstLogicalCluster = searchForDir(firstLogicalCluster, delim);
		if (firstLogicalCluster == -1)
		{
			/* Directory does not exist */
			return -1;
		}

		/* Get next directory name */
		delim = strtok(NULL, "/");
	}

	/* Directory path does exist */
	return firstLogicalCluster;
}

/* Does the dirName exist inside the directory beginning at curFLC */
short searchForDir(short curFLC, char* dirName)
{
	/* Read Logical Cluster */
	dirEntry* newWorkingDirectory = (dirEntry*) malloc(512 * 9 * sizeof(dirEntry));
	char* fileName;

	unsigned int realCluster;
	printf("Current FLC : %i\n", curFLC);
	if (curFLC == 0)
	{
		/* Root Directory size = numReservedSectors + (sectorsPerFAT * numFATs) */
		//realCluster = 9 * (read_;
	}
	else
	{
		/* Cluster is located at physical address rootRealCluster + curFLC + ((numRootEntries * sizeof(dirEntry)) / BYTES_PER_SECTOR) - 2 */
		//realCluster = 9 * (sectorsPerFAT * numFATS) + curFLC + ((16 * sizeof(dirEntry)) / 16 -2);
	}
	read_sector(realCluster, (unsigned char*) newWorkingDirectory);
	/* Search directory at curFLC for dirName */
	int index;
	for (index = 0; index < 20; index++)
	{
		if ((unsigned char) newWorkingDirectory[index].name[0] == 0xE5)
		{
			/* The directory entry is currently unused (free) */
		}
		else if ((unsigned char) newWorkingDirectory[index].name[0] == 0x00)
		{
			/* The directory is currently unused, as are all the remaining entries in this directory */
			break;
		}
		else if ((unsigned char) newWorkingDirectory[index].name[0] == 0xFF7)
		{
			/* BAD CLUSTER */
			printf("Bad Cluster.\n");
			break;
		}
		else
		{
			printf("New directory entry found. NAME: %s\n", newWorkingDirectory[index].name);
			if (newWorkingDirectory[index].attributes == 0x10)
			{
				/* Found a sub-directory */
				fileName = getEntryName(newWorkingDirectory[index]);
				/* Is this entry dirName? Should be case sensitive? */
				if (strcmp(fileName, dirName) == 0)
				{
					/* Advance curFLC */
					curFLC = newWorkingDirectory[index].firstLogicalCluster;
					free(newWorkingDirectory);
					return curFLC;
				}
			}
		}
	}

	free(fileName);
	free(newWorkingDirectory);
	return -1;
}

/* Create a String from the filename of a dirEntry element */
char* getEntryName(dirEntry directory)
{
	char* fileName;
	int index;

	for (index = 0; index < 11; index++)
	{
		if (index < 8)
		{
			if (directory.name[index] == ' ')
				break;
			fileName[index] = directory.name[index];
		}
		else
		{
			if (directory.extension[index] == ' ')
				break;
			fileName[index] = directory.extension[index];
		}
	}

	return fileName;
}
