/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Functions that will be shared with all subprograms for access
	to shared memory.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// const key_t SHM_KEY = 1234;
int shm_id;

typedef struct
{
	// Current Working Directory
	char wdPath[200];
	unsigned int wdSize;

	// Filename of FAT block file
	char fName[45];
	unsigned int fSize;

	// First Logical Cluster
	short FLC;
	
} sharedMemory;

#ifndef SHARED_H
#define SHARED_H

void dirAdd(char*);
void dirRemove();

void dirSet(char* newPath);
void flcSet(short newFLC);
void filenameSet(char* newPath);

char* dirGet();
short flcGet();
char* filenameGet();

#endif