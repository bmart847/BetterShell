#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct _direntry
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

typedef struct _fileentry
{
	char Filename[9];
	char Type[4];
	char Attributes;
	char CreationTime[2];
	char CreationDate[2];
	char LastAccessDate[2];

	char LastWriteTime[2];
	char LastWriteDate[2];
	short FirstLogicalCluster;
	int FileSize;
} fileEntry;


#ifndef FAT_H
#define FAT_H

extern char* WORKING_DIRECTORY;
extern int BYTES_PER_SECTOR;

void pwd();
void enterDir(char *dirName);
short existingDirectory(char* path);
short searchForDir(short curFLC, char* target);
char* getEntryName(dirEntry directory);
void listDirectory();
#endif