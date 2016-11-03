#include "fat.h"

void pwd() {
	init->pwd();
	return;
}

void enterDir(char *dirName) {
    workingDir newWD = init;

	if (strcmp(dirName, "..") == 0) {
		/* Move Up Directory */
		newWD.dirRemove();
		init = newWD;
	} else if (dirName[0] == '/') {
		/* Check if dirName is an absolute path, stars with '/' */
		newWD.dirSet(dirName);
		if (strcmp(dirName, "/\0") == 0){
			/* Move to Root */
			init.dirSet(newWD.dirGet());
		}else if (existingDirectory(newWD) == 0) {
			/* dirName as an absolute path exists
			 * Reset init to newWorkingDir */
			init.dirSet(newWD.dirGet());
		} else {
			/* dirName does not exist as an absolute path from root */
			printf("The directory does not exist.");
		}
        
	} else {  /* dirName is a relative path. */
		newWD.dirAdd(dirName);
        
		/* Does dirName exist inside the working directory? */
		if (existingDirectory(newWD) == 0) {
			/* Add new directory name to working directory string */
			init.dirSet(newWD.dirGet());
		} else {			
			/* dirName does not exist as an relative path from current working directory */
			printf("The directory does not exist.");
		}
	}
	return;
}

/* Check directoryName recursively by directory if the path exists */
int existingDirectory(workingDir dir, char* path) {
    char* pathName = (char*) malloc(strlen(path) + 1);
	strcpy(pathName, path);
	string newPath;
	unsigned short firstLogicalCluster = 0;
    
	/* Get deliminator token */
	char* delim;
	delim = strtok(pathName, "/");
	newPath = delim;
	/* Check each directory in the directoryName exists */
	while(delim != NULL) {
		if (searchForDir(&firstLogicalCluster, newPath) == -1) {
			/* Directory does not exist */
			return -1;
		}

		/* Get next directory name */
		delim = strtok(NULL, "/");
		strcat(newPath, "/");
		strcat(newPath, delim);
	}
	
	/* Directory path does exist */
	return 0;
}

/* Does the dirName exist inside the directory beginning at curFLC */
int searchForDir(short* curFLC, char* dirName) {
	/* Read Logical Cluster */
	unsigned char* data = (unsigned char*)malloc(BYTES_PER_SECTOR);
	char* fileName;

	unsigned int realCluster;
	if ((short)curFLC == 0) {
		/* Root Directory size = numReservedSectors + (sectorsPerFAT * numFATs) */
		realCluster = bootSectorData.numReservedSectors + (bootSectorData.sectorsPerFAT * bootSectorData.numFATs);
	} else {
		/* Cluster is located at physical address rootRealCluster + curFLC + ((numRootEntries * sizeof(dirEntry)) / BYTES_PER_SECTOR) - 2 */
		realCluster = (bootSectorData.numReservedSectors + (bootSectorData.sectorsPerFAT * bootSectorData.numFATs)) + ((bootSectorData.numRootEntries * sizeof(dirEntry)) / BYTES_PER_SECTOR) + curFLC - 2;
	}

	read_sector(realCluster, data);
	dirEntry directory = (dirEntry *)data;

	/* Search directory at curFLC for dirName */
	int index;
	for (index = 0; index < 20; index++)
	{
		if ((unsigned char)directoryEntry[k].name[0] == 0xE5) {
			/* The directory entry is currently unused (free) */
		} else if ((unsigned char) directoryEntry[k].name[0] == 0x00) {
			/* The directory is currently unusued, as are all the remaining entries in this directory */
		} else {
			if (dir[index].attributes == 0x10) {
				/* Found a subdirectory */
				fileName = getEntryName(dir[index]);
				/* Is this entry dirName? Should be case sensitive? */
				if (strcmp(fileName, dirName) {
					/* Advance curFLC */
					curFLC = dir[index].firstLogicalCluster;
					free(data);
					return 0;
				}
			}
		}
	}

	free(data);
	return -1;
}

/* Create a String from the filename of a dirEntry element */
char* getEntryName(dirEntry directory) {
	char* fileName;
	int index;

	for (index = 0; index < 11; index++) {
		if (index < 8) {
			if (directory.name[index] == ' ')
				break;
			fileName[index] = directory.name[index];
		} else {
			if (directory.extension[index] == ' ')
				break;
			fileName[index] = directory.extension[index];
		}
	}

	return fileName;
}