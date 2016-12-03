#include "shared.h"

const key_t SHM_KEY = 1234;

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

		if(change->wdSize == 0) {
			change->wdPath[0] = '/';
			change->wdPath[1] = '\0';
			change->wdSize = 1;
		}

        shmdt(change);
}

// SHM-SET //

// Sets the current working directory in Shared Memory
void dirSet(char* newPath) {
        sharedMemory* change = shmat(shm_id, 0, 0);
        unsigned int newSize = 0, oldSize = change->wdSize;

        memset(&(change->wdPath), '\0', sizeof(change->wdPath));

        for (newSize = 0; newPath[newSize] != '\0'; newSize++) { }

        strcat(change->wdPath, newPath);
        change->wdSize = newSize;
        shmdt(change);
}

// Sets the filename of the FAT block file in Shared Memory
void filenameSet(char* newPath) {
        sharedMemory* change = shmat(shm_id, 0, 0);
        unsigned int newSize = 0, oldSize = change->fSize;

        memset(&(change->fName), '\0', sizeof(change->fName));

        for (newSize = 0; newPath[newSize] != '\0'; newSize++) { }

        strcat(change->fName, newPath);
        change->fSize = newSize;
        shmdt(change);
}

// Sets the First Logical Cluster
void flcSet(short newFLC) {
        sharedMemory* change = shmat(shm_id, 0, 0);
        change->FLC = newFLC;
        shmdt(change);
}

// SHM-GET //

// Returns string containing current working directory
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

// Returns string containing filename of FAT block file from Shared Memory
char* filenameGet() {
        sharedMemory* access = shmat(shm_id, 0, SHM_RDONLY);
        int i;
        char* tmp = malloc(access->fSize * sizeof(char*));

        for (i = 0; i < access->fSize; i++) {
                tmp[i] = access->fName[i];
        }

        shmdt(access);
        return tmp;
}

// Returns FLC from Shared Memory
short flcGet() {
        sharedMemory* access = shmat(shm_id, 0, SHM_RDONLY);
        short tmp = access->FLC;
        shmdt(access);

        return tmp;
}