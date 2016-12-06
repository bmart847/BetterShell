/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016

	Description:  Functions for manipulation of FAT da

	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#ifndef FAT_H
#define FAT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "fatSupport.h"

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

typedef struct
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


/* File Attribut Constants */
#define READ_ONLY_ATTRIBUTE 0x01 
#define HIDDEN_ATTRIBUTE    0x02
#define SYSTEM_ATTRIBUTE    0x04
#define VOLUME_LABEL	    0x08
#define SUBDIR		    0x10
#define ARCHIVE		    0x20

#define MAX_FILENAME_LENGTH 255

extern char* WORKING_DIRECTORY;
extern int BYTES_PER_SECTOR;

short existingDirectory(char* path);
short existingSubDir(short curFLC, char* target);

char* getEntryName(dirEntry directory);

#endif
