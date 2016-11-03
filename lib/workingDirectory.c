#include "workingDirectory.h"

// Initializes the shared memory space used to store the working directory
void initWorkingDir() {
	workingDir *init;
	shm_id = shmget(IPC_PRIVATE, 200*sizeof(char*), IPC_CREAT | 0666);
	if(shm_id < 0) {
		printf("shmget Error\n");
		exit(1);
	}
	printf("Shared memory initialized!\n");
	init = shmat(shm_id, 0, 0);
	init->wd = "/";
}

// Stub
int main(){
	initWorkingDir();
	workingDir *test = shmat(shm_id, 0, SHM_RDONLY);
	printf("%s\n", test->wd);
	return;
}
