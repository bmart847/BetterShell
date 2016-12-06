#include "fat.h"

/* Check directoryName recursively by directory if the path exists */
short existingDirectory(char* path)
{
	/* Check if path is the root directory */
	if (path[0] == '/' && strlen(path) == 1)
	{
		/* Path is the Root Directory */
		/* Return the First Logical Cluster of the Root Directory (19) */
		return 19;
	}

	/* Path is not the Root Directory, time to dig deeper */

	/* Declare Variables */
	int index;
	char** dirContents = malloc(MAX_FILENAME_LENGTH * sizeof(char));
	// Let's start at the root
	unsigned short firstLogicalCluster = 19;
	// Duplicate path because it will get modified by strtok()
	char* pathName = malloc(MAX_FILENAME_LENGTH * sizeof(char));
	strcpy(pathName, path); 

	/* Next Step: Figure out the directory's depth from Root */
	int depth = 0;
	char* delim = strtok(pathName, "/\n");

	/* Count the number of directories from Root to pathName */
	while(delim != NULL)
	{
		delim = strtok(NULL, "/");
		depth++;
	}

	/* Load the path into dirContents array */
	// Allocate memory in dirContents container array for new input
	*dirContents = malloc(depth * sizeOf(char));
	// Reset pathName back to path after strtok()
	strcpy(pathName, path);
	delim = strtok(pathName, "/");
	index = 0;
	while (delim!= NULL && delim[0] != "\n")
	{
		*dirContents[index] = strdup(delim);
		delim = strtok(NULL, "/");
		index++;
	}

	/* Check if the path exists as a directory */
	for (index = 0; i < depth; i++)
	{
		firstLogicalCluster = existingSubDir(firstLogicalCluster, dirContents[index]);
		if (firstLogicalCluster == -1)
		{
			/* Directory does not exist */
			free(dirContents);
			return -1;
		}
	}
	
	/* Directory path does exist */
	free(dirContents);
	return firstLogicalCluster;
} 

/* Does the dirName exist inside the directory beginning at curFLC */
short existingSubDir(short curFLC, char* dirName)
{
	printf("Current FLC : %i\n", curFLC);
	/* Declare Variables */
	unsigned char* clusterBuffer;
	int realCluster, fakeCluster;
	int index, done = 0;
	
	while (done == 0)
	{
		/* Allocate more memory */
		clusterBuffer = malloc(512 * sizeof(char));
		/* Read the next fat entry */
		nextCluster = get_fat_entry(curFLC, readFAT12Table(1));

		/* Who da real cluster doe? */
		if (curFLC == 19)
		{
			/* We are in the root directory */
			realCluster = curFLC;
		}
		else
		{
			/* Set Real Cluster to curFLC + Root_Offset (32) */
			realCluster = curFLC + 32 - 1;
		}

		/* Read realCluster's sector */
		read_sector(realCluster, clusterBuffer);

		/* Cycle through the 16 sectors in each cluster (FAT12 Constant Value) */
		for (index = 0; index < 16; index++)
		{
			dirEntry* entry = read_Entry(clusterBuffer + (index * 32));

			if ((unsigned char) entry.name[0] == (0xE5 || 0x40 || 0x80))
			{
				/* The directory entry is currently unused (free) */
			}
			else if ((unsigned char) entry.name[0] == 0x00)
			{
				/* The directory is currently unused, as are all the remaining entries in this directory */
				free(clusterBuffer);
				return -1;
			}
			else if ((unsigned char) entry.name[0] == 0xFF7)
			{
				/* BAD CLUSTER */
				printf("Bad Cluster.\n");
				break;
			}
			else if (entry.attributes == 0x10)
			{
				printf("Found a subdirectory. Name : %s\n", getEntryName(entry));
				if (strcmp(getEntryName(entry), dirName) == 0)
				{
					printf("Found the correct Subdirectory!\n");
					free(clusterBuffer);
					return entry.firstLogicalCluster;
				}
			}
		}
		
		if (fakeCluster != (0x00 || 0xFF0)
		{
			flc = fakeCluster;
		}
	}

	free(clusterBuffer);
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
