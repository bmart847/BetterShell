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
	char** dirContents = malloc(MAX_FILENAME_LENGTH * sizeof(char*));
	// Let's start at the root
	unsigned short firstLogicalCluster = 19;
	// Duplicate path because it will get modified by strtok()
	char* pathName = malloc(MAX_FILENAME_LENGTH * sizeof(char));
	strcpy(pathName, path); 

	/* Next Step: Figure out the directory's depth from Root */
	int depth = 0;
	char* delim = strtok(pathName, "/\0");

	/* Count the number of directories from Root to pathName */
	while(delim != NULL)
	{
		delim = strtok(NULL, "/");
		depth++;
	}

	/* Load the path into dirContents array */
	// Allocate memory in dirContents container array for new input
	*dirContents = malloc(depth * sizeof(char*));
	// Reset pathName back to path after strtok()
	strcpy(pathName, path);
	delim = strtok(pathName, "/");
	index = 0;

	while (delim != NULL && delim[0] != '\0')
	{
		dirContents[index] = strdup(delim);
		delim = strtok(NULL, "/");
		index++;
	}

	/* Check if the path exists as a directory */
	for (index = 0; index < depth; index++)
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
	/* Declare Variables */
	// clusterBuffer needs memory allocated to hold BytesPerSector (512) char's
	unsigned char* clusterBuffer = malloc(512 * sizeof(char*));
	int realCluster, fakeCluster;
	int index, done = 0;
	short flc = curFLC;
	// fatTable needs to be able to hold the size of the fat table, BytesPerSector * SectorsPerFat (512 * 9)
	unsigned char* fatTable = malloc(512 * 9);

	/* Initialize Fat Table */
	for (index = 0; index < 9; index++)
	{
		read_sector(index + 1, &fatTable[512 * index]);
	}

	while (!done)
	{
		/* Read the next fat entry */
		fakeCluster = get_fat_entry(flc, fatTable);

		/* Where da real cluster doe? */
		if (flc == 19 || flc == 0)
		{
			/* We are in the root directory */
			realCluster = 19;
		}
		else
		{
			/* Set Real Cluster to curFLC + Root_Offset (32) */
			realCluster = flc + 32 - 1;
		}

		/* Read realCluster's sector */
		read_sector(realCluster, clusterBuffer);

		/* Cycle through the 16 sectors in each cluster (FAT12 Constant Value) */
		for (index = 0; index < 16; index++)
		{
			dirEntry entry;
			entry = loadDirEntry(clusterBuffer + (index * 32));
			
			if (entry->filename[0] == (0xE5 || 0x40 || 0x80))
			{
				/* The directory entry is currently unused (free) */
				printf("FAT.C : %s is unused.\n", entry->filename);
			}
			else if (entry->filename[0] == UNUSED)
			{
				printf("Entry is unused!\n");

				/* The directory is currently unused, as are all the remaining entries in this directory */
				free(clusterBuffer);
				return -1;
			}
			else if (entry->filename[0] == BAD_CLUSTER)
			{
				/* BAD CLUSTER */
				printf("Bad Cluster.\n");
				break;
			}
			else if (entry->attributes == SUBDIR)
			{
				char* subDirName = malloc(sizeof(char) * MAX_FILENAME_LENGTH);
				strcat(subDirName, getEntryName(*entry));

				printf("FAT.C -- Comparing : %s <---> %s\n", subDirName, dirName);
				printf("FAT.C -- The Entry's First Logical Cluster is : %d\n", entry->firstLogicalCluster);

				if (strcmp(subDirName, dirName) == 0)
				{
					return entry->firstLogicalCluster;
				}
			}
		}

		if ((fakeCluster != 0x00) || (fakeCluster != 0xFF0))
		{
			flc = fakeCluster;
		}
		else
		{
			printf("Did not find %s in the cluster after FLC = %i.\n", dirName, curFLC);
			return -1;
		}
	}

	free(clusterBuffer);
	return -1;
}

/* Check if the specified filepath exists in the fat */
short existingFile(char* filepath, short FLC)
{
	if (strlen(filepath) == 1)
	{
		/* Root is not file */
		return -1;
	}

	unsigned char* image = (unsigned char*) malloc(BYTES_PER_SECTOR * NUM_FAT_SECTORS);
	loadFatTable(image);

	unsigned char* sector;
	int done = 0;

	while (done == 0)
	{
		sector = get_fat_entry(FLC, image);
		unsigned char* cluster = malloc(BYTES_PER_SECTOR * sizeof(char));

		int curSector;


		if (FLC == 19 || FLC == 0)
		{
			curSector = 19;
		}
		else
		{
			curSector = FLC + 33 - 2;
		}

		int count = read_sector(curSector, cluster);

		int index;
		for (index = 0; index < 16; index++)
		{
			dirEntry entry;
			int offset = index * 32;
			entry = loadDirEntry(cluster + offset);

			int matching = 1, count = 0;
			char* testPath = malloc(BYTES_PER_SECTOR * sizeof(char));
			strcpy(testPath, &filepath);
			
			char* token = strtok(testPath, "/");
			while (token != NULL)
			{
				token = strtok(NULL, "/");
				count++;
			}

			if (count == 1)
			{
				if (strcasecmp(entry.filename, filepath) == 0)
				{
					matching = 0;
				}
			}

			if (matching == 0)
			{
				if((entry.attributes & SUBDIR) == SUBDIR)
				{
					/* filepath is a directory */
					done = 1;
					break;
				}
				/* Else, we found our target! */
				return entry.firstLogicalCluster;
			}
		}

		if (cluster > UNUSED && cluster < RESERVED_CLUSTER_BEGIN)
		{
			FLC = cluster;
		}
		else
		{
			/* Unable to locate the specified filepath in the current fat */
			done = 1;
		}
	}

	return -1;
}

/* Load the contents of the FAT Table into buffer and return the number of fat entries */
int loadFatTable(unsigned char* buffer)
{
	int index;
	// index will count the number of fat entries 

	for(index = 1; index < NUM_FAT_SECTORS; index++)
	{
		read_sector(index, buffer + ((index - 1) * BYTES_PER_SECTOR));
	}

	return 2880;
}

/* Create a String from the filename of a dirEntry element */
char* getEntryName(dirEntry directory)
{
	char* fileName = (char*) malloc(11 * sizeof(char));
	int index;

	for (index = 0; index < 11; index++)
	{
		if (index < 8)
		{
			if (directory.filename[index] == ' ')
				break;
			fileName[index] = directory.filename[index];
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

/* Read entry into a dirEntry object */
dirEntry loadDirEntry(char* entry)
{
	dirEntry object;

	int index, offset = 0;

	*object.filename = (char*) malloc(9 * sizeof(char));
	for(index = 0; index < 8; index++)
	{
		if (entry[index] == ' ' || entry[index] == '\0')
		{
			break;
		}
		object.filename[index] = entry[offset + index];
	}
	object.filename[index] = '\0';

	offset = 8;

	*object.extension = (char*) malloc(4 * sizeof(char));
	for(index = 0; index < 3; index++)
	{
		if (entry[offset + index] == ' ' || entry[offset + index] == '\0')
		{
			break;
		}
		object.extension[index] = entry[offset + index];
	}
	object.extension[index] = '\0';

	offset = 11;

	object.attributes = entry[offset];

	offset = 26;

	object.firstLogicalCluster = (((int) entry[offset]) & 0x000000ff) || (((int) entry[offset + 1] << 8) & 0x0000ff00);

	offset = 28;

	object.fileSize = (((int) entry[offset]) & 0x000000ff) || ((((int) entry[offset + 1]) << 8) & 0x0000ff00) || ((((int) entry[offset + 2]) << 16) && 0x00ff0000) || ((((int) entry[offset + 3]) << 24) & 0xff000000);

	return object;
}
