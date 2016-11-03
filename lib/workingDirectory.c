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
	init->wdPath[0] = '/';
	init->wdPath[1] = '\0';
	init->wdSize = 1;
}

void dirAdd(char* new) {
	workingDir* change;
	unsigned int newSize = 1, i;

	for(i = 0; new[i] != '\0'; i++){}
	newSize = newSize + i;

	change = shmat(shm_id, 0, 0);
	strcat(change->wdPath, new);
	strcat(change->wdPath, "/\0");
	change->wdSize = change->wdSize + newSize;
}

// Stub
int main(){
	workingDir* test;
	initWorkingDir();
	test = shmat(shm_id, 0, SHM_RDONLY);
	printf("%s - %i\n", test->wdPath, test->wdSize);
	shmdt(test);

	dirAdd("New");

	test = shmat(shm_id, 0, SHM_RDONLY);
        printf("%s - %i\n", test->wdPath, test->wdSize);
	shmdt(test);

	return;
}
