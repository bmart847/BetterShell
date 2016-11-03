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

void dirRemove() {
    workingDir* change = shmat(shm_id, 0, 0);
    int index = change->wdSize - 1, removeSize = 0;
    change->wdPath[index] = '\0';
    while(change->wdPath[index] != '/') {
        change->wdPath[index] = '\0';
        removeSize++;
        index--;
    }
    change->wdSize = change->wdSize - removeSize;
}

// Stub
int main(){
    workingDir* test;
    initWorkingDir();
    test = shmat(shm_id, 0, SHM_RDONLY);
    printf("%s - %i\n", test->wdPath, test->wdSize);
    shmdt(test);
    
    dirAdd("New");
    dirAdd("Folder");
    dirAdd("Path");
    
    test = shmat(shm_id, 0, SHM_RDONLY);
    printf("%s - %i\n", test->wdPath, test->wdSize);
    shmdt(test);
    
    dirRemove();
    dirRemove();
    
    test = shmat(shm_id, 0, SHM_RDONLY);
    printf("%s - %i\n", test->wdPath, test->wdSize);
    shmdt(test);
    return;
}
