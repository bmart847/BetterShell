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
	init->wd[0] = '/';
	init->wd[1] = '\0';
}

void dirAdd(char* new) {
	workingDir* change;
	change = shmat(shm_id, 0, 0);
	strcat(change->wd, new);	
	strcat(change->wd, "/\0");
}

// Stub
int main(){
	workingDir* test;
	initWorkingDir();
	test = shmat(shm_id, 0, SHM_RDONLY);
	printf("%s\n", test->wd);
	shmdt(test);

	dirAdd("New");

	test = shmat(shm_id, 0, SHM_RDONLY);
        printf("%s\n", test->wd);
	shmdt(test);

	return;
}
