#include "sys/shm.h"
#include "sys/ipc.h"
#include "stdio.h"

int shm_id;

typedef struct {
	char* wd;
} workingDir;

void initWorkingDir();


