#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shm_id;

typedef struct {
	char wd[200];
    unsigned int wdSize;
    unsigned int depth; // Directory depth, 1 - Root
    unsigned short FLC;
    unsigned int offsetInPathName;
} workingDir;

void initWorkingDir();
void dirAdd(char*);
void dirRemove();

void setDepth(unsigned int depth);
void setFLC(unsigned short FLC);
void setOffset(unsigned int offset);
