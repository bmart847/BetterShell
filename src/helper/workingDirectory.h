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

/* Don't think we need these to be in shared memory
 *	unsigned int wdDepth;
 *	unsigned int wdSize;
 *	unsigned int wdOffset;
 */
} sharedMemory;

void dirAdd(char*);
void dirRemove();
void dirSet(char*);
char* dirGet();
