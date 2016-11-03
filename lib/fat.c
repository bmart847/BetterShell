#include "fat.h"

unsigned char* readRootSectors() {
	/* Declare Variables */
 	unsigned char* root;
	int i, br;

	/* Allocate Space */
	root = (unsigned char*) malloc(14 * (BYTES_PER_SECTOR * sizeof(unsigned char)));

	for(i=19;i<33;i++) {
		br = br + read_sector(i, &root[(i-19)*BYTES_PER_SECTOR]);
	}

	return root;
}

void enterDir(char *dirName) {
    workingDir newWD = init;
    char* dir = newWD.wd;

	if (strcmp(dirName, "..") == 0) {
		/* Move Up Directory */

		
	} else if (dirName[0] == '/') {
		/* Check if dirName is an absolute path, stars with '/' */
		newWD.dirSet(dirName);
		newWD.depthSet(1);
		newWD.FLCset(0);
		newWD.offsetSet(1);

		if (strcmp(dirName, "/\0") == 0){
			/* Move to Root */
			init = newWD;
		}else if (existingDirectory(newWD, dirName) == 0) {
			/* dirName as an absolute path exists
			 * Reset init to newWorkingDir */
            init = newWD;
		} else {
			/* dirName does not exist as an absolute path from root */
			printf("The directory does not exist.");
		}
        
	} else {  /* dirName is a relative path. */
        dir += strlen(newWD->pathName);
        
		/* Does dirName exist inside the working directory? */
		if (existingDirectory(newWD, dirName) == 0) {
			/* Add new directory name to working directory string */
            init = newWD;
		} else {			
			/* dirName does not exist as an relative path from current working directory */
			printf("The directory does not exist.");
		}
	}
	return;
}

void exitDir() {
	/* Remove characters from working directory until */
	int i, j;
	for(i=0; WORKING_DIRECTORY[i] != '\0';i++);

	i--;

	do {
		WORKING_DIRECTORY[i] = '\0';
		i--;
	} while(WORKING_DIRECTORY[i] != '/');
	return;
}

void pwd() {
	printf("%s", WORKING_DIRECTORY);
	return;
}

/* Check directoryName recursively by directory if the path exists */
int existingDirectory(workingDir dir, char* path) {
    char* pathName = (char*) malloc(strlen(path) + 1);
	strcpy(pathName, path);
    
    unsigned short firstLogicalCluster = dir->FLC;
    unsigned int offsetInWD = dir->offsetInPathName;
    
	/* Get deliminator token */
	char* delim;
	delim = strtok(pathName, "/");
    
	/* Check each directory in the directoryName exists */
	while(delim != NULL) {
		if (searchForFolder(firstLogicalCluster, delim) == -1) {
			/* Directory does not exist */
			return -1;
		}
		
		/* Get next directory name */
		delim = strtok(NULL, "/");
	}
	
	/* Directory path does exist */
	return 0;
}


int searchForDir(short curFLC, char* dirName) {
	
	int index;
	/* Loop through directory searching for dirName */
	for (index = 0; index < 20; index++)
	{
		if ((unsigned char)directoryEntry[k].name[0] == 0xE5) {
			/* The directory entry is currently unused (free) */
		} else if ((unsigned char) directoryEntry[k].name[0] == 0x00) {
			/* The directory is currently unusued, as are all the remaining entries in this directory */
			break;
		} else {
			
		}
	}
}

