#include "root.h"

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
	/* Check if dirName is an absolute path, stars with '/' */
	if (dirName[0] == '/') {
		/* Does dirName as an absolute path exist? */
		if(existingDirectory(dirName) == 0) {
			/* Reset WORKING_DIRECTORY to dirName */
			strcpy(WORKING_DIRECTORY, dirName);
			strcat(WORKING_DIRECTORY, "/");
		} else {
			/* dirName does not exist as an absolute path from root */
			perror("The directory does not exists as an absolute path!");
		}
	} else {  /* dirName is a relative path. */
		/* Does dirName exist inside the working directory? */
		string newDirectory = WORKING_DIRECTORY;
		strcat(newDirectory, '/');
		strcat(newDirectory, dirName);
		if (existingDirectory(newDirectory) == 0) {		
			/* Add new directory name to working directory string */
			strcat(WORKING_DIRECTORY, dirName);
			strcat(WORKING_DIRECTORY, "/");
		} else {			
			/* dirName does not exist as an relative path from current working directory */
			perror("The directory does not exists as an relative path!");
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

int existingDirectory(string* directoryName) {
	unsigned int directoryDepth = 0;
	/* Tokens: strtok() modifies the string, directoryName must be duplicated */
	char* pathName = (char*) malloc(strlen(directoryName) + 1);
	strcpy(pathName, directoryName); 
	/* Get token */
	char* token;
	token = strtok(pathName, "/");
	/* Check each directory in the directoryName exists */
	while(token != NULL) {
		
		
	}

	return 1;
}
