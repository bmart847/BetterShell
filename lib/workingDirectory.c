#include "workingDirectory.h"

// Initializes the shared memory space used to store the working directory
void initWorkingDir() {
	workingDir *init;
	shm_id = shmget(IPC_PRIVATE, 250*sizeof(char*), IPC_CREAT | 0666);
	if(shm_id < 0) {
		printf("shmget Error\n");
		exit(1);
	}
	printf("Shared memory initialized!\n");
	init = shmat(shm_id, 0, 0);
	init->wdPath[0] = '/';
	init->wdPath[1] = '\0';
	init->wdSize = 1;
	init->wdOffset = 1;
	init->wdFLC = 0;
	shmdt(init);
}

// Adds directory 'new' to the end of the working directory
void dirAdd(char* new) {
	workingDir* change;
	unsigned int newSize = 0, i;

	for(i = 0; new[i] != '\0'; i++){}
	newSize = newSize + i;

	change = shmat(shm_id, 0, 0);
	if(change->wdSize != 1) {
		strcat(change->wdPath, "/\0");
		newSize++;
	}

	strcat(change->wdPath, new);
	change->wdOffset = change->wdSize + 2;
	change->wdSize = change->wdSize + newSize;
	shmdt(change);
}
// Removes one directory from the end of the working directory (for 'cd ..')
void dirRemove() {
	workingDir* change = shmat(shm_id, 0, 0);
	int index = change->wdSize - 1, removeSize = 1;
	change->wdPath[index] = '\0';
	while(change->wdPath[index] != '/') {
		change->wdPath[index] = '\0';
		removeSize++;
		index--;
	}
	change->wdPath[index] = '\0';
	change->wdSize = change->wdSize - removeSize;

        change->wdOffset = change->wdSize;
        do {
            	change->wdOffset--;
        } while(change->wdPath[change->wdOffset-2] != '/');

	shmdt(change);
}

// Sets the working directory to the given string
void dirSet(char* newPath) {
        workingDir* change = shmat(shm_id, 0, 0);
        unsigned int newSize = 0, oldSize = change->wdSize, i;

	memset(&(change->wdPath), '\0', sizeof(change->wdPath));

	change->wdDepth = 0;
        for(newSize = 0; newPath[newSize] != '\0'; newSize++) {
		if(newPath[newSize] == '/') {
			change->wdDepth++;
			change->wdOffset = newSize + 2;
		}
	}

        strcat(change->wdPath, newPath);
        change->wdSize = newSize;
        shmdt(change);
}

// Stub
int main(){
	workingDir* test;
	initWorkingDir();
	test = shmat(shm_id, 0, SHM_RDONLY);
	printf("%s - %i - %i\n", test->wdPath, test->wdSize, test->wdOffset);
	shmdt(test);

	dirAdd("New");
	dirAdd("Folder");
	dirAdd("Path");

	test = shmat(shm_id, 0, SHM_RDONLY);
        printf("%s - %i - %i\n", test->wdPath, test->wdSize, test->wdOffset);
	shmdt(test);

	dirRemove();
	dirRemove();

        test = shmat(shm_id, 0, SHM_RDONLY);
        printf("%s - %i - %i\n", test->wdPath, test->wdSize, test->wdOffset);
        shmdt(test);

	dirSet("/setting/this/dir");

        test = shmat(shm_id, 0, SHM_RDONLY);
        printf("%s - %i - %i\n", test->wdPath, test->wdSize, test->wdOffset);
        shmdt(test);

	return;
}
