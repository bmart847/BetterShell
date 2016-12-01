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

void dirAdd(char*);
void dirRemove();
void dirSet(char*);
char* dirGet();