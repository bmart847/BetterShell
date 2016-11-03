#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shm_id;

typedef struct {
	char wd[200];
    unsigned int wdSize;
} workingDir;

void initWorkingDir();
void dirAdd(char*);
void dirRemove();