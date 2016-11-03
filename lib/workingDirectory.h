#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shm_id;

typedef struct {
	char wdPath[200];
	unsigned int wdDepth;
	unsigned int wdSize;
	unsigned int wdOffset;
} workingDir;

void initWorkingDir();
void dirAdd(char*);
void dirRemove();
void dirSet(char*);
char* dirGet();
