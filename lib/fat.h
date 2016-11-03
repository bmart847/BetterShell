#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Function Prototypes Here */

#ifndef FAT_H
#define FAT_H

extern char* WORKING_DIRECTORY;
extern int BYTES_PER_SECTOR;

typedef struct
{
	char           name[8];
	char           extension[3];
	unsigned char  attributes;
	unsigned char  reserved[2];
	unsigned short creationTime;
	unsigned short creationDate;
	unsigned short lastAccessDate;
	unsigned char  ignored[2];
	unsigned short lastWriteTime;
	unsigned short lastWriteDate;
	unsigned short firstLogicalCluster;
	unsigned int   fileSize;
} dirEntry;

unsigned char* readRootSectors();
void enterDir(char *dirName);
void exitDir();
void pwd();
int existingDirectory(workingDir dir, char* path);
int searchForDir(short currentFLC, char * target);
#endif
