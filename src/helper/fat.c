#include "fat.h"

/* Check directoryName recursively by directory if the path exists */
short existingDirectory(char* path) {
	char* pathName;
	unsigned short firstLogicalCluster = 0;

//	pathName = path; // Duplicate because strtok() will modify

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
	unsigned char* data = (unsigned char*)malloc(BYTES_PER_SECTOR);
	char* fileName;

	unsigned int realCluster;
	if ((short)curFLC == 0)
	{
		/* Root Directory size = numReservedSectors + (sectorsPerFAT * numFATs) */
		//realCluster = returnRootPhysicalOffset();
	}
	else
	{
		/* Cluster is located at physical address rootRealCluster + curFLC + ((numRootEntries * sizeof(dirEntry)) / BYTES_PER_SECTOR) - 2 */
		//realCluster = returnDirectoryPhysicalOffset() + curFLC;
	}

	read_sector(realCluster, data);
	dirEntry* directory = data;

	/* Search directory at curFLC for dirName */
	int index;
	for (index = 0; index < 20; index++)
	{
		if ((unsigned char)directory[index].name[0] == 0xE5)
		{
			/* The directory entry is currently unused (free) */
		}
		else if ((unsigned char)directory[index].name[0] == 0x00)
		{
			/* The directory is currently unusued, as are all the remaining entries in this directory */
		}
		else
		{
			if (directory[index].attributes == 0x10)
			{
				/* Found a subdirectory */
				fileName = getEntryName(directory[index]);
				/* Is this entry dirName? Should be case sensitive? */
				if (strcmp(fileName, dirName) == 0)
				{
					/* Advance curFLC */
					curFLC = directory[index].firstLogicalCluster;
					free(data);
					return curFLC;
				}
			}
		}
	}

	free(data);
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