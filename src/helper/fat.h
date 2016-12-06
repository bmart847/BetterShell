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
	char filename[8];
	char extenstion[3];
	unsigned char attributes;
	unsigned char reserved[2];
	unsigned char creationTime[2];
	unsigned char creationDate[2];
	unsigned char lastAccessDate[2];
	unsigned char fatIgnored[2];
	unsigned char lastWriteTime[2];
	unsigned char lastWriteDate[2];
	unsigned short FirstLogicalCluster;
	unsigned int FileSize;
} dirEntry;


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
