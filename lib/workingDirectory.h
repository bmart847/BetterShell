#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shm_id;

typedef struct {
<<<<<<< HEAD
	char wd[200];
    unsigned int wdSize;
=======
	char wdPath[200];
	unsigned int wdDepth;
	unsigned int wdSize;
	unsigned int wdOffset;
>>>>>>> refs/remotes/origin/master
} workingDir;

void initWorkingDir();
void dirAdd(char*);
<<<<<<< HEAD
void dirRemove();
=======
void dirRemove();
void dirSet(char*);
char* dirGet();
>>>>>>> refs/remotes/origin/master
