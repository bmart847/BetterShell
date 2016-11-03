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
	/* Check if dirName is an absolute path, stars with '/' */
	if (dirName[0] == '/') {
        newWD.setDir(dirName);
        newWD.setDepth(1);
        newWD.setFLC(0);
        newWD.setOffset(1);
		
        /* Does dirName as an absolute path exist? */
		if(existingDirectory(newWD, dirName) == 0) {
			/* Reset init to newWorkingDir */
            init = newWD;
		} else {
			/* dirName does not exist as an absolute path from root */
			printf("The directory does not exists as an absolute path.");
		}
        
	} else {  /* dirName is a relative path. */
        dir += strlen(newWD.pathName);
        
		/* Does dirName exist inside the working directory? */
		if (existingDirectory(newWD, dirName) == 0) {
			/* Add new directory name to working directory string */
            init->dirAdd(dirName);
		} else {			
			/* dirName does not exist as an relative path from current working directory */
			printf("The directory does not exists as an relative path.");
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

/********************************************************************************
 * Check directoryName recursively by directory if the path exists
 *******************************************************************************/
int existingDirectory(WorkingDirectory dir, char* path) {
    char* pathName = (char*) malloc(strlen(path) + 1);
	strcpy(pathName, path);
    
    unsigned short firstLogicalCluster = dir->FLC;
    unsigned int offsetInWD = dir->offsetInPathName;
    
	/* Get deliminator token */
	char* delim;
	delim = strtok(pathName, "/");
    
	/* Check each directory in the directoryName exists */
	while(delim != NULL) {
        searchForFolder(firstLogicalCluster, delim);
		
		delim = strtok(NULL, "/");
	}
	
	/* Directory path does exist */
	return 0;
}

int searchForFolder(short currentFLC, char* dirName) {
    unsigned char * sector;
    char ** dirs;
    int     depth;
    int index = 0;
    
    if(dirName[0] == '/' && strlen(dirName) == 1)
        return 0;
}

int searchHarderForFolder(short currentFLC, char ** dirs, int index, int depth) {
    
    return 0;
}
