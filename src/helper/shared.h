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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shm_id;

typedef struct _sharedmemory {
	char wdPath[200];
	unsigned int wdSize;
	short FLC;
	char filename[45];
} sharedMemory;

#ifndef SHARED_H
#define SHARED_H

void dirAdd(char*);
void dirRemove();
void dirSet(char*);
char* dirGet();

#endif