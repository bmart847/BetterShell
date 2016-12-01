#include "fat.h"
//#include "shared.h"

void pwd()
{
	printf("%s\n", dirGet());
	return;
}

void enterDir(char *dirName)
{
	char* pathName;

	if (dirName == NULL)
	{
		printf("CD must be handed an argument./n");
		return;
	}
	else if (strcmp(dirName, "..") == 0)
	{
		/* Move Up Directory */
		dirRemove();
	}
	else if (dirName[0] == '/')
	{
		/* Check if dirName is an absolute path, stars with '/' */
		if (strcmp(dirName, "/\0") == 0)
		{
			/* Move to Root */
			dirSet(dirName);
		}
		else if (existingDirectory(dirName) == 0)
		{
			/* dirName as an absolute path exists */
			dirSet(dirName);
		}
		else
		{
			/* dirName does not exist as an absolute path from root */
			printf("The directory does not exist.");
		}

	}
	else
	{
		/* dirName is a relative path. */
		pathName = dirGet();
		strcat(pathName, "/");
		strcat(pathName, dirName);

		/* Does dirName exist inside the working directory? */
		if (existingDirectory(pathName) == 0)
		{
			/* Add new directory name to working directory string */
			dirAdd(dirName);
		}
		else
		{
			/* dirName does not exist as an relative path from current working directory */
			printf("The directory does not exist.");
		}
	}
	return;
}

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

void listDirectory()
{
	dirEntry directory;
	short FLC;;
	int length = 1;
	unsigned char* image;
	char temp[40];
	int* entries;
	int i, h, l, j, k, s;

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
			image = (unsigned char*)malloc(BYTES_PER_SECTOR * sizeof(unsigned char));
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
			image = (unsigned char*)malloc(BYTES_PER_SECTOR * sizeof(unsigned char));
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
			image = (unsigned char*)malloc(BYTES_PER_SECTOR * sizeof(unsigned char));
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

	return;
}
