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
	char extension[3];
	unsigned char attributes;
	unsigned char reserved[2];
	unsigned char creationTime[2];
	unsigned char creationDate[2];
	unsigned char lastAccessDate[2];
	unsigned char fatIgnored[2];
	unsigned char lastWriteTime[2];
	unsigned char lastWriteDate[2];
	unsigned short firstLogicalCluster;
	unsigned int fileSize;
} dirEntry;


/* File Attribute Constants */
#define READ_ONLY_ATTRIBUTE 0x01 
#define HIDDEN_ATTRIBUTE    0x02
#define SYSTEM_ATTRIBUTE    0x04
#define VOLUME_LABEL	    0x08
#define SUBDIR		    0x10
#define ARCHIVE		    0x20

/* Cluster Constants */
#define UNUSED			0x00
#define RESERVED_CLUSTER_BEGIN	0xFF0
#define RESERVED_CLUSTER_END	0xFF6
#define BAD_CLUSTER		0xFF7
#define LAST_CLUSTER_BEGIN	0xFF8
#define LAST_CLUSTER_END	0xFFF

#define MAX_FILENAME_LENGTH 255
#define NUM_FAT_SECTORS 9

extern char* WORKING_DIRECTORY;
extern int BYTES_PER_SECTOR;

/* FAT Navigation Functions */
short existingDirectory(char* path);
short existingSubDir(short curFLC, char* target);

short existingFile(char* filepath);

int loadFatTable(unsigned char* buffer); // Return the (number of sectors loaded * BYTES_PER_SECTOR ) / 1.5

/* dirEntry Helpers */
char* getEntryName(dirEntry directory);
dirEntry loadDirEntry(char* entry);

#endif
