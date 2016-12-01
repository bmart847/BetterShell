#include "workingDirectory.h"

// Adds directory 'new' to the end of the working directory
void dirAdd(char* new) {
	sharedMemory* change;
	unsigned int newSize = 0, i;

	for (i = 0; new[i] != '\0'; i++) {}
	newSize = newSize + i;

	change = shmat(shm_id, 0, 0);
	if (change->wdSize != 1) {
		strcat(change->wdPath, "/\0");
		newSize++;
	}

	strcat(change->wdPath, new);
	change->wdSize = change->wdSize + newSize;
	shmdt(change);
}
// Removes one directory from the end of the working directory (for 'cd ..')
void dirRemove() {
	sharedMemory* change = shmat(shm_id, 0, 0);
	int index = change->wdSize - 1, removeSize = 1;
	change->wdPath[index] = '\0';
	while (change->wdPath[index] != '/') {
		change->wdPath[index] = '\0';
		removeSize++;
		index--;
	}
	change->wdPath[index] = '\0';
	change->wdSize = change->wdSize - removeSize;

	do {
		change->wdOffset--;
	} while (change->wdPath[change->wdOffset - 2] != '/');

	shmdt(change);
}

// Sets the working directory to the given string
void dirSet(char* newPath) {
	sharedMemory* change = shmat(shm_id, 0, 0);
	unsigned int newSize = 0, oldSize = change->wdSize, i;

	memset(&(change->wdPath), '\0', sizeof(change->wdPath));

	for (newSize = 0; newPath[newSize] != '\0'; newSize++) { }

	strcat(change->wdPath, newPath);
	change->wdSize = newSize;
	shmdt(change);
}

char* dirGet() {
	sharedMemory* access = shmat(shm_id, 0, SHM_RDONLY);
	int i;
	char* tmp = malloc(access->wdSize * sizeof(char*));

	for (i = 0; i < access->wdSize; i++) {
		tmp[i] = access->wdPath[i];
	}
	shmdt(access);
	return tmp;
}